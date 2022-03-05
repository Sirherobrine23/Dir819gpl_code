/*
 *	Forwarding database
 *	Linux ethernet bridge
 *
 *	Authors:
 *	Lennert Buytenhek		<buytenh@gnu.org>
 *
 *	This program is free software; you can redistribute it and/or
 *	modify it under the terms of the GNU General Public License
 *	as published by the Free Software Foundation; either version
 *	2 of the License, or (at your option) any later version.
 */

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/rculist.h>
#include <linux/spinlock.h>
#include <linux/times.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/jhash.h>
#include <linux/random.h>
#include <linux/slab.h>
#include <asm/atomic.h>
#include <asm/unaligned.h>
#include "br_private.h"

static struct kmem_cache *br_fdb_cache __read_mostly;
static int fdb_insert(struct net_bridge *br, struct net_bridge_port *source,
		      const unsigned char *addr);

static u32 fdb_salt __read_mostly;
#ifdef CONFIG_LOOPBACK_CHECK
extern void switch_port_power_mng(int,int);
extern int gLoopbackPort;
extern int gLoopbackAppReady;
extern void PHY_power_ops(unsigned int port, int optcode);
extern void ei_addr_table_init(void);
#endif

int __init br_fdb_init(void)
{
	br_fdb_cache = kmem_cache_create("bridge_fdb_cache",
					 sizeof(struct net_bridge_fdb_entry),
					 0,
					 SLAB_HWCACHE_ALIGN, NULL);
	if (!br_fdb_cache)
		return -ENOMEM;

	get_random_bytes(&fdb_salt, sizeof(fdb_salt));
	return 0;
}

void br_fdb_fini(void)
{
	kmem_cache_destroy(br_fdb_cache);
}


/* if topology_changing then use forward_delay (default 15 sec)
 * otherwise keep longer (default 5 minutes)
 */
static inline unsigned long hold_time(const struct net_bridge *br)
{
	return br->topology_change ? br->forward_delay : br->ageing_time;
}

static inline int has_expired(const struct net_bridge *br,
				  const struct net_bridge_fdb_entry *fdb)
{
	return !fdb->is_static &&
		time_before_eq(fdb->ageing_timer + hold_time(br), jiffies);
}

static inline int br_mac_hash(const unsigned char *mac)
{
	/* use 1 byte of OUI cnd 3 bytes of NIC */
	u32 key = get_unaligned((u32 *)(mac + 2));
	return jhash_1word(key, fdb_salt) & (BR_HASH_SIZE - 1);
}

static void fdb_rcu_free(struct rcu_head *head)
{
	struct net_bridge_fdb_entry *ent
		= container_of(head, struct net_bridge_fdb_entry, rcu);
	kmem_cache_free(br_fdb_cache, ent);
}

static inline void fdb_delete(struct net_bridge_fdb_entry *f)
{
	hlist_del_rcu(&f->hlist);
	call_rcu(&f->rcu, fdb_rcu_free);
}

void br_fdb_changeaddr(struct net_bridge_port *p, const unsigned char *newaddr)
{
	struct net_bridge *br = p->br;
	int i;

	spin_lock_bh(&br->hash_lock);

	/* Search all chains since old address/hash is unknown */
	for (i = 0; i < BR_HASH_SIZE; i++) {
		struct hlist_node *h;
		hlist_for_each(h, &br->hash[i]) {
			struct net_bridge_fdb_entry *f;

			f = hlist_entry(h, struct net_bridge_fdb_entry, hlist);
			if (f->dst == p && f->is_local) {
				/* maybe another port has same hw addr? */
				struct net_bridge_port *op;
				list_for_each_entry(op, &br->port_list, list) {
					if (op != p &&
					    !compare_ether_addr(op->dev->dev_addr,
								f->addr.addr)) {
						f->dst = op;
						goto insert;
					}
				}

				/* delete old one */
				fdb_delete(f);
				goto insert;
			}
		}
	}
 insert:
	/* insert new address,  may fail if invalid address or dup. */
	fdb_insert(br, p, newaddr);

	spin_unlock_bh(&br->hash_lock);
}

void br_fdb_cleanup(unsigned long _data)
{
	struct net_bridge *br = (struct net_bridge *)_data;
	unsigned long delay = hold_time(br);
	unsigned long next_timer = jiffies + br->ageing_time;
	int i;

	spin_lock_bh(&br->hash_lock);
	for (i = 0; i < BR_HASH_SIZE; i++) {
		struct net_bridge_fdb_entry *f;
		struct hlist_node *h, *n;

		hlist_for_each_entry_safe(f, h, n, &br->hash[i], hlist) {
			unsigned long this_timer;
			if (f->is_static)
				continue;
			this_timer = f->ageing_timer + delay;
			if (time_before_eq(this_timer, jiffies))
				fdb_delete(f);
			else if (time_before(this_timer, next_timer))
				next_timer = this_timer;
		}
	}
	spin_unlock_bh(&br->hash_lock);

	mod_timer(&br->gc_timer, round_jiffies_up(next_timer));
}

/* Completely flush all dynamic entries in forwarding database.*/
void br_fdb_flush(struct net_bridge *br)
{
	int i;

	spin_lock_bh(&br->hash_lock);
	for (i = 0; i < BR_HASH_SIZE; i++) {
		struct net_bridge_fdb_entry *f;
		struct hlist_node *h, *n;
		hlist_for_each_entry_safe(f, h, n, &br->hash[i], hlist) {
			if (!f->is_static)
				fdb_delete(f);
		}
	}
	spin_unlock_bh(&br->hash_lock);
}

/* Flush all entries refering to a specific port.
 * if do_all is set also flush static entries
 */
void br_fdb_delete_by_port(struct net_bridge *br,
			   const struct net_bridge_port *p,
			   int do_all)
{
	int i;

	spin_lock_bh(&br->hash_lock);
	for (i = 0; i < BR_HASH_SIZE; i++) {
		struct hlist_node *h, *g;

		hlist_for_each_safe(h, g, &br->hash[i]) {
			struct net_bridge_fdb_entry *f
				= hlist_entry(h, struct net_bridge_fdb_entry, hlist);
			if (f->dst != p)
				continue;

			if (f->is_static && !do_all)
				continue;
			/*
			 * if multiple ports all have the same device address
			 * then when one port is deleted, assign
			 * the local entry to other port
			 */
			if (f->is_local) {
				struct net_bridge_port *op;
				list_for_each_entry(op, &br->port_list, list) {
					if (op != p &&
					    !compare_ether_addr(op->dev->dev_addr,
								f->addr.addr)) {
						f->dst = op;
						goto skip_delete;
					}
				}
			}

			fdb_delete(f);
		skip_delete: ;
		}
	}
	spin_unlock_bh(&br->hash_lock);
}

/* No locking or refcounting, assumes caller has rcu_read_lock */
struct net_bridge_fdb_entry *__br_fdb_get(struct net_bridge *br,
					  const unsigned char *addr)
{
	struct hlist_node *h;
	struct net_bridge_fdb_entry *fdb;

	hlist_for_each_entry_rcu(fdb, h, &br->hash[br_mac_hash(addr)], hlist) {
		if (!compare_ether_addr(fdb->addr.addr, addr)) {
			if (unlikely(has_expired(br, fdb)))
				break;
			return fdb;
		}
	}

	return NULL;
}

#if defined(CONFIG_ATM_LANE) || defined(CONFIG_ATM_LANE_MODULE)
/* Interface used by ATM LANE hook to test
 * if an addr is on some other bridge port */
int br_fdb_test_addr(struct net_device *dev, unsigned char *addr)
{
	struct net_bridge_fdb_entry *fdb;
	int ret;

	if (!br_port_exists(dev))
		return 0;

	rcu_read_lock();
	fdb = __br_fdb_get(br_port_get_rcu(dev)->br, addr);
	ret = fdb && fdb->dst->dev != dev &&
		fdb->dst->state == BR_STATE_FORWARDING;
	rcu_read_unlock();

	return ret;
}
#endif /* CONFIG_ATM_LANE */

/*
 * Fill buffer with forwarding table records in
 * the API format.
 */
int br_fdb_fillbuf(struct net_bridge *br, void *buf,
		   unsigned long maxnum, unsigned long skip)
{
	struct __fdb_entry *fe = buf;
	int i, num = 0;
	struct hlist_node *h;
	struct net_bridge_fdb_entry *f;

	memset(buf, 0, maxnum*sizeof(struct __fdb_entry));

	rcu_read_lock();
	for (i = 0; i < BR_HASH_SIZE; i++) {
		hlist_for_each_entry_rcu(f, h, &br->hash[i], hlist) {
			if (num >= maxnum)
				goto out;

			if (has_expired(br, f))
				continue;

			if (skip) {
				--skip;
				continue;
			}

			/* convert from internal format to API */
			memcpy(fe->mac_addr, f->addr.addr, ETH_ALEN);

			/* due to ABI compat need to split into hi/lo */
			fe->port_no = f->dst->port_no;
			fe->port_hi = f->dst->port_no >> 8;

			fe->is_local = f->is_local;
			if (!f->is_static)
				fe->ageing_timer_value = jiffies_to_clock_t(jiffies - f->ageing_timer);
			++fe;
			++num;
		}
	}

 out:
	rcu_read_unlock();

	return num;
}

/*
 * TBS_TAG : by Tangqiang 2012-3-19
 * Desc : Merge force url from E8PonV3
 */
extern struct net *get_net_ns_by_pid(pid_t pid);
int br_fdb_ifname_get_mac(char *ifname, int port_no, struct list_head *plisthead)
{
        int i;
        struct net_device *dev = __dev_get_by_name(get_net_ns_by_pid(current->pid), ifname);
        struct net_bridge *br = netdev_priv(dev);
        struct hlist_node *h;
        struct net_bridge_fdb_entry *f;
        MAC_LIST *pstmac;

        rcu_read_lock();
        for (i = 0; i < BR_HASH_SIZE; i++) {
                hlist_for_each_entry_rcu(f, h, &br->hash[i], hlist) {
                        if (has_expired(br, f))
                                continue;
                        if((f->is_local == 0)&&(f->dst->port_no==port_no))
                        {
                                pstmac = (MAC_LIST *)kmalloc(sizeof(MAC_LIST), GFP_ATOMIC);
                                if(pstmac) {
                                        memcpy(pstmac->mac, f->addr.addr, ETH_ALEN);
                                        list_add(&pstmac->list, plisthead);
                                }
                        }
                }
        }

        rcu_read_unlock();
        return 1;
}
EXPORT_SYMBOL_GPL(br_fdb_ifname_get_mac);

static inline struct net_bridge_fdb_entry *fdb_find(struct hlist_head *head,
						    const unsigned char *addr)
{
	struct hlist_node *h;
	struct net_bridge_fdb_entry *fdb;

	hlist_for_each_entry_rcu(fdb, h, head, hlist) {
		if (!compare_ether_addr(fdb->addr.addr, addr))
			return fdb;
	}
	return NULL;
}

static struct net_bridge_fdb_entry *fdb_create(struct hlist_head *head,
					       struct net_bridge_port *source,
					       const unsigned char *addr,
					       int is_local)
{
	struct net_bridge_fdb_entry *fdb;

	fdb = kmem_cache_alloc(br_fdb_cache, GFP_ATOMIC);
	if (fdb) {
		memcpy(fdb->addr.addr, addr, ETH_ALEN);
		hlist_add_head_rcu(&fdb->hlist, head);

		fdb->dst = source;
		fdb->is_local = is_local;
		fdb->is_static = is_local;
		fdb->ageing_timer = jiffies;
	}
	return fdb;
}

static int fdb_insert(struct net_bridge *br, struct net_bridge_port *source,
		  const unsigned char *addr)
{
	struct hlist_head *head = &br->hash[br_mac_hash(addr)];
	struct net_bridge_fdb_entry *fdb;

	if (!is_valid_ether_addr(addr))
		return -EINVAL;

	fdb = fdb_find(head, addr);
	if (fdb) {
		/* it is okay to have multiple ports with same
		 * address, just use the first one.
		 */
		if (fdb->is_local)
			return 0;
		br_warn(br, "adding interface %s with same address "
		       "as a received packet\n",
		       source->dev->name);
		fdb_delete(fdb);
	}

	if (!fdb_create(head, source, addr, 1))
		return -ENOMEM;

	return 0;
}

int br_fdb_insert(struct net_bridge *br, struct net_bridge_port *source,
		  const unsigned char *addr)
{
	int ret;

	spin_lock_bh(&br->hash_lock);
	ret = fdb_insert(br, source, addr);
	spin_unlock_bh(&br->hash_lock);
	return ret;
}

int br_fdb_update(struct net_bridge *br, struct net_bridge_port *source,
		   const unsigned char *addr)
{
	struct hlist_head *head = &br->hash[br_mac_hash(addr)];
	struct net_bridge_fdb_entry *fdb;
#ifdef CONFIG_LOOPBACK_CHECK
        unsigned   long   irqflag;
        int loopPort = 0;
        int powerDownId;
#endif
	/* some users want to always flood. */
	if (hold_time(br) == 0)
		return;

	/* ignore packets unless we are using this port */
	if (!(source->state == BR_STATE_LEARNING ||
	      source->state == BR_STATE_FORWARDING))
		return;

	fdb = fdb_find(head, addr);
	if (likely(fdb))
	{
		/* attempt to update an entry for a local interface */
		if (unlikely(fdb->is_local))
		{
#ifdef CONFIG_LOOPBACK_CHECK
            if (gLoopbackAppReady && memcmp(source->dev->name,"eth",3) == 0)
			{
                loopPort = source->dev->name[3] - '0';//Wan dev name number is 1, Lan dev name number is 2~5
                loopPort--; //turn to port id (0~4)
                powerDownId = loopPort;
                if (powerDownId >= 0)
				{
                    local_irq_save(irqflag);
					PHY_power_ops(powerDownId,0); //port id is should be 0~4
					ei_addr_table_init();
                    local_irq_restore(irqflag);
                    gLoopbackPort = gLoopbackPort | (1 << loopPort);
                    printk("#####################%s %d eth%d is loopback!\n",__FUNCTION__,__LINE__,loopPort);
                }
            }
#endif
			if (net_ratelimit())
			{
				br_warn(br, "received packet on %s with "
					"own address as source address\n",
					source->dev->name);
			}
			return -1;

		}
		else
		{
			/* fastpath: update of existing entry */
#ifdef CONFIG_LOOPBACK_CHECK
			if(memcmp(source->dev->name,"eth",3) == 0)
			{
				/*if other port packet,we must free it*/
				if(source->dev->ifindex != fdb->dst->dev->ifindex &&
                    jiffies - fdb->ageing_timer < 3*HZ)
				{
					return -1;
				}
			}
#endif
			fdb->dst = source;
			fdb->ageing_timer = jiffies;
		}
	}
	else
	{
		spin_lock(&br->hash_lock);
		if (!fdb_find(head, addr))
			fdb_create(head, source, addr, 0);
		/* else  we lose race and someone else inserts
		 * it first, don't bother updating
		 */
		spin_unlock(&br->hash_lock);
	}
	return 0;
}

/*
 * TBS_TAG:add by pengyao 2012-05-23
 * Desc: support IGMP SNOOPING
 */
#if defined(CONFIG_IGMP_SNOOPING)

static void mc_debuginfo(struct net_bridge *br)
{
	struct net_bridge_mc_fdb_entry *dst;
	int cnt = 0;

	printk("\n=============================================================\n");
    #if 1
	list_for_each_entry_rcu(dst, &br->mc_list, list) {
        printk("brport:%d, host_mac:"NMACQUAD_FMT", filtermode:%d, srcip:"NIPQUAD_FMT", group:"NIPQUAD_FMT"\n",
//		dst->dst->port_no, NMACQUAD(dst->addr.addr), NMACQUAD(dst->host.addr),
        dst->dst->port_no,NMACQUAD(dst->host.addr),
        dst->src_entry.filt_mode, NIPQUAD(dst->src_entry.src.s_addr),
        NIPQUAD(dst->group_addr.s_addr));
		cnt++;
	}
    #endif
	printk("Total: %d\n", cnt);
	printk("=============================================================\n");
}

int br_mc_fdb_update(struct net_bridge *br, struct net_bridge_port *prt,unsigned char *host, int mode,
    struct in_addr *src, unsigned int *group)
{
	struct net_bridge_mc_fdb_entry *dst;
	int ret = 0;
	int filt_mode;
    if (br_igmp_debug)
    {
        mc_debuginfo(br);
        printk("--- update mc entry ---, mode:%d, group:"NIPQUAD_FMT", host_mac:"NMACQUAD_FMT", srcip:"NIPQUAD_FMT"\n",
            mode, NIPQUAD(group), NMACQUAD(host), NIPQUAD(src->s_addr));
    }

    if(mode == SNOOP_IN_ADD)
      filt_mode = MCAST_INCLUDE;
    else
      filt_mode = MCAST_EXCLUDE;

	list_for_each_entry_rcu(dst, &br->mc_list, list) {
	    if ((src->s_addr == dst->src_entry.src.s_addr) &&
                (filt_mode == dst->src_entry.filt_mode) &&
		(!memcmp(&dst->host, host, ETH_ALEN)) &&
            (dst->dst == prt) && (dst->group_addr.s_addr == *group))
        {
			dst->tstamp = jiffies + QUERY_TIMEOUT*HZ;
		    ret = 1;
    	    }
	    /* patch for igmp report flooding by robo */
	       else if ((0 == dst->src_entry.src.s_addr) &&
	                (MCAST_EXCLUDE == dst->src_entry.filt_mode)) {
	           dst->tstamp = jiffies + QUERY_TIMEOUT*HZ;
	       }
	}

	return ret;
}

#if 1 /*support igmp snooping timeout dengyanbing 2012-09-17*/
static void query_timeout(unsigned long ptr)
{
	struct net_bridge_mc_fdb_entry *dst;
	struct list_head *tmp;
	struct list_head *lh;
	struct net_bridge *br;

	br = (struct net_bridge *) ptr;

	spin_lock_bh(&br->mcl_lock);
	list_for_each_safe_rcu(lh, tmp, &br->mc_list) {
	    dst = (struct net_bridge_mc_fdb_entry *) list_entry(lh, struct net_bridge_mc_fdb_entry, list);

		//gxw / 2014-06-26 / add
		//防止jiffies快溢出时删除未超时的组播路由,导致组播中断
		if ((dst->tstamp - QUERY_TIMEOUT*HZ > dst->tstamp)
			&& (dst->tstamp - QUERY_TIMEOUT*HZ < jiffies)) {
			continue;
		}

		if(jiffies > dst->tstamp){
    		list_del_rcu(&dst->list);
    		kfree(dst);
	    }
	}
	spin_unlock_bh(&br->mcl_lock);

	mod_timer(&br->igmp_timer, jiffies + TIMER_CHECK_TIMEOUT*HZ);
}
#endif


static struct net_bridge_mc_fdb_entry *br_mc_fdb_get(struct net_bridge *br, struct net_bridge_port *prt,unsigned char *host,
    int mode, struct in_addr *src, unsigned int *group)
{
	struct net_bridge_mc_fdb_entry *dst;
	int filt_mode;

    if(mode == SNOOP_IN_CLEAR)
      filt_mode = MCAST_INCLUDE;
    else
      filt_mode = MCAST_EXCLUDE;

	list_for_each_entry_rcu(dst, &br->mc_list, list) {
	    if ((!memcmp(&dst->host, host, ETH_ALEN)) &&
            (filt_mode == dst->src_entry.filt_mode) &&
            (dst->src_entry.src.s_addr == src->s_addr) &&
            (dst->group_addr.s_addr == *group))
        {
			if (dst->dst == prt)
		    	return dst;
	    }
	}

	return NULL;
}

extern mac_addr upnp_addr;

/*
 *the difference between br_mc_fdb_add_by_host and br_mc_fdb_add
 *is that, the mc_list maintained by br_mc_fdb_add_by_host is sorted
 *by host,with host-sorted mc_list, it would be easy to conclude
 *whether a multi-cast packet from the group source which has been
 *excluded should be forward or deliver(see mc_forward in br_input.c)
 */
int br_mc_fdb_add_by_host(struct net_bridge *br, struct net_bridge_port *prt, unsigned char *host,
    int mode, struct in_addr *src, unsigned int *group)
{
    struct net_bridge_mc_fdb_entry *mc_fdb;
    struct list_head *lh;
    struct net_bridge_mc_fdb_entry *dst;

    if(!br || !prt || !host)
        return 0;

    if((SNOOP_IN_ADD != mode) && (SNOOP_EX_ADD != mode))
        return 0;

    if (br_igmp_debug)
    {
    	mc_debuginfo(br);
        printk("--- add mc entry ---, mode:%d, group:"NIPQUAD_FMT", host_mac:"NMACQUAD_FMT", srcip:"NIPQUAD_FMT"\n",
            mode, NIPQUAD(group), NMACQUAD(host), NIPQUAD(src->s_addr));
    }

	if (br_mc_fdb_update(br, prt, host, mode, src, group))
	    return 0;

	mc_fdb = kmalloc(sizeof(struct net_bridge_mc_fdb_entry), GFP_KERNEL);
	if (!mc_fdb)
	    return ENOMEM;

	memcpy(mc_fdb->host.addr, host, ETH_ALEN);
	memcpy(&mc_fdb->src_entry, src, sizeof(struct in_addr));
	mc_fdb->src_entry.filt_mode =
                  (mode == SNOOP_IN_ADD) ? MCAST_INCLUDE : MCAST_EXCLUDE;
	mc_fdb->dst = prt;
	mc_fdb->tstamp = jiffies + QUERY_TIMEOUT*HZ;

    mc_fdb->group_addr.s_addr = *group;
	spin_lock_bh(&br->mcl_lock);
	//list_add_tail_rcu(&mc_fdb->list, &br->mc_list);
	__list_for_each_rcu(lh, &br->mc_list) {
	    dst = (struct net_bridge_mc_fdb_entry *) list_entry(lh, struct net_bridge_mc_fdb_entry, list);
        if (!memcmp(&(dst->host), host, 6)){
            break;
        }
    }

    //found
    if (lh != &(br->mc_list)){
        list_add_rcu(&mc_fdb->list, lh);
    }
    //find none,add at tail
    else{
        list_add_tail_rcu(&mc_fdb->list, &br->mc_list);
    }
	spin_unlock_bh(&br->mcl_lock);
#if 1 /*support igmp snooping timeout dengyanbing 2012-09-17*/
	if (!br->start_timer) {
    	    init_timer(&br->igmp_timer);
	    br->igmp_timer.expires = jiffies + TIMER_CHECK_TIMEOUT*HZ;
	    br->igmp_timer.function = query_timeout;
	    br->igmp_timer.data = (unsigned long) br;
	    add_timer(&br->igmp_timer);
	    br->start_timer = 1;
	}
#endif
	return 1;
}

int br_mc_fdb_add(struct net_bridge *br, struct net_bridge_port *prt, unsigned char *host, int mode,
    struct in_addr *src, unsigned int *group)
{
	struct net_bridge_mc_fdb_entry *mc_fdb;

    if(!br || !prt || !host)
        return 0;

    if((SNOOP_IN_ADD != mode) && (SNOOP_EX_ADD != mode))
        return 0;

    if (br_igmp_debug)
    {
    	mc_debuginfo(br);
        printk("--- add mc entry ---, mode:%d, group:"NIPQUAD_FMT", host_mac:"NMACQUAD_FMT", srcip:"NIPQUAD_FMT"\n",
            mode, NIPQUAD(group), NMACQUAD(host), NIPQUAD(src->s_addr));
    }

	if (br_mc_fdb_update(br, prt, host, mode, src, group))
	    return 0;

	mc_fdb = kmalloc(sizeof(struct net_bridge_mc_fdb_entry), GFP_KERNEL);
	if (!mc_fdb)
	    return ENOMEM;

	memcpy(mc_fdb->host.addr, host, ETH_ALEN);
	memcpy(&mc_fdb->src_entry, src, sizeof(struct in_addr));
	mc_fdb->src_entry.filt_mode =
                  (mode == SNOOP_IN_ADD) ? MCAST_INCLUDE : MCAST_EXCLUDE;
	mc_fdb->dst = prt;
	mc_fdb->tstamp = jiffies + QUERY_TIMEOUT*HZ;

    mc_fdb->group_addr.s_addr = *group;

	spin_lock_bh(&br->mcl_lock);
	list_add_tail_rcu(&mc_fdb->list, &br->mc_list);
	spin_unlock_bh(&br->mcl_lock);
#if 1 /*support igmp snooping timeout dengyanbing 2012-09-17*/
	if (!br->start_timer) {
    	    init_timer(&br->igmp_timer);
	    br->igmp_timer.expires = jiffies + TIMER_CHECK_TIMEOUT*HZ;
	    br->igmp_timer.function = query_timeout;
	    br->igmp_timer.data = (unsigned long) br;
	    add_timer(&br->igmp_timer);
	    br->start_timer = 1;
	}
#endif
	return 1;
}

void br_mc_fdb_cleanup(struct net_bridge *br)
{
	struct net_bridge_mc_fdb_entry *dst;
	struct net_bridge_mc_fdb_entry *tmp;

	spin_lock_bh(&br->mcl_lock);
	list_for_each_entry_safe(dst, tmp, &br->mc_list, list) {
	    list_del_rcu(&dst->list);
	    kfree(dst);
	}
	spin_unlock_bh(&br->mcl_lock);
}

/*
void br_mc_fdb_remove_grp(struct net_bridge *br, struct net_bridge_port *prt, unsigned char *dest)
{
	struct net_bridge_mc_fdb_entry *dst;
	struct list_head *lh;
	struct list_head *tmp;

	spin_lock_bh(&br->mcl_lock);
	list_for_each_safe_rcu(lh, tmp, &br->mc_list) {
	    dst = (struct net_bridge_mc_fdb_entry *) list_entry(lh, struct net_bridge_mc_fdb_entry, list);
	    if ((!memcmp(&dst->addr, dest, ETH_ALEN)) && (dst->dst == prt)) {
		list_del_rcu(&dst->list);
		kfree(dst);
	    }
	}
	spin_unlock_bh(&br->mcl_lock);
}
*/

int br_mc_fdb_remove(struct net_bridge *br, struct net_bridge_port *prt, unsigned char *host, int mode,
    struct in_addr *src, unsigned int *group)
{
	struct net_bridge_mc_fdb_entry *mc_fdb;

    if((SNOOP_IN_CLEAR != mode) && (SNOOP_EX_CLEAR != mode))
    	return 0;

    if (br_igmp_debug)
    {
    	mc_debuginfo(br);
        printk("--- remove mc entry ---, mode:%d, group:"NIPQUAD_FMT", host_mac:"NMACQUAD_FMT", srcip:"NIPQUAD_FMT"\n",
            mode, NIPQUAD(group), NMACQUAD(host), NIPQUAD(src->s_addr));
    }

	if ((mc_fdb = br_mc_fdb_get(br, prt, host, mode, src, group))) {
	    spin_lock_bh(&br->mcl_lock);
	    list_del_rcu(&mc_fdb->list);
	    kfree(mc_fdb);
	    spin_unlock_bh(&br->mcl_lock);

	    return 1;
	}

	return 0;
}

struct net_bridge_mc_fdb_entry *br_mc_fdb_find(struct net_bridge *br, struct net_bridge_port *prt,
    unsigned char *host, struct in_addr *src, unsigned int *group)
{
	struct net_bridge_mc_fdb_entry *dst;

	list_for_each_entry_rcu(dst, &br->mc_list, list) {
	    if ((!memcmp(&dst->host, host, ETH_ALEN)) &&
            (dst->src_entry.src.s_addr == src->s_addr) &&
            (dst->group_addr.s_addr == *group))
        {
			if (dst->dst == prt)
		    	return dst;
	    }
	}

	return NULL;
}

/*
 * TBS_TAG: by pengyao 2012-2-28
 * Desc:br_mc_fdb_delete_by_port
 */
void br_mc_fdb_delete_by_port(struct net_bridge *br,
			   const struct net_bridge_port *p,
			   int do_all)
{
	struct net_bridge_mc_fdb_entry *dst;
	struct list_head *lh;
    struct list_head *tmp;

    if (br_igmp_debug)
    {
    	mc_debuginfo(br);
        printk("--- delete mc fdb by port ---, bridge_port: %s\n", p->dev->name);
    }

	spin_lock_bh(&br->mcl_lock);
	list_for_each_prev_safe(lh, tmp, &br->mc_list) {
	    dst = (struct net_bridge_mc_fdb_entry *) list_entry(lh, struct net_bridge_mc_fdb_entry, list);

        if(dst->dst != p)
            continue;

        if(dst->is_static && !do_all)
            continue;

	    list_del_rcu(&dst->list);
        kfree(dst);
	}

	spin_unlock_bh(&br->mcl_lock);
}

/*
 * TBS_TAG: end
 */
#endif /* CONFIG_IGMP_SNOOPING */
/*
 * TBS_END_TAG
 */
