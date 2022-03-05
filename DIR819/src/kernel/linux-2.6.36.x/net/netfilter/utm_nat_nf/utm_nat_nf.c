/*----------------------------------------------------------------------------
;
;    Project : 
;    Creator : George Lin
;    File    : utm_nat.c
;    Abstract:  
;
;       Modification History:
;       By              Date     Ver.   Modification Description
;       --------------- -------- -----  --------------------------------------
;       George          2012-0621
;*****************************************************************************/
#include <linux/init.h>
#include <linux/version.h>
#include <linux/config.h>
#include <linux/module.h>
#include <linux/kernel.h>   
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/proc_fs.h>
#include <linux/fcntl.h>    
#include <asm/system.h>

#include <linux/skbuff.h>
#include <linux/list.h>
#include <utm_nat_nf.h>
#include <linux/jhash.h>
#include <net/ip.h>
#include <linux/kernel.h>
#include <linux/jiffies.h>
#include <linux/timer.h>
#include <linux/unistd.h>

#include <linux/ipv6.h>
#include <net/ipv6.h>
#include <net/ip6_checksum.h>
#include <net/addrconf.h>

#include <linux/netfilter.h>
#include <linux/netfilter_ipv6.h>
#include <linux/netfilter_ipv4.h>
#include <linux/netdevice.h>
#include <linux/inet.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("George Lin");
MODULE_DESCRIPTION("UTM NAT NF module");

#define MAX_PROC_SIZE 1000

static u_int32_t __utm_proxy_port=8888;
static u_int32_t __hook_port=80;
static char __local_lan_device[10]="br0";

#ifdef LITTLE_ENDIAN
#define UTM_PROXY_PORT be16_to_cpu(__utm_proxy_port)
#else
#define UTM_PROXY_PORT __utm_proxy_port
#endif

#define LOCAL_LAN_DEVICE __local_lan_device

#ifdef LITTLE_ENDIAN
#define HOOK_PORT be16_to_cpu(__hook_port)
#else
#define HOOK_PORT __hook_port
#endif

#define UTM_NAT_MSEC_TIMEOUT 7200000//2HR, value of connection timeout 
#define UTM_NAT_SEC_TIMEOUT UTM_NAT_MSEC_TIMEOUT/1000

#define TIME_OUT_POLLING_ENABLE 0
#define TIME_OUT_DRIVEN_ENABLE 1
#define JHASH_ENABLE 1
#define HASH_TABLE_COMPLEXITY 8//2012.07.19, Sitecom request this level
#define RAMSIZE 32*1024
#define DIVISOR_1 16
#define DIVISOR_2 32//32 bits
#define SIZE_OF_POINTER sizeof(int*)*8 //in bits

struct hlist_head* utm_nat_hash=NULL;//hash table
u_int32_t utm_nat_htable_size=((RAMSIZE/DIVISOR_1)*(SIZE_OF_POINTER/DIVISOR_2))/HASH_TABLE_COMPLEXITY;//How many buckets in hash table
static u_int32_t utm_nat_index=0;//Total count in hash table_size
static u_int32_t rx_enable=1, tx_enable=1;
char proc_data[MAX_PROC_SIZE];
static struct nf_hook_ops utm_nat_hook_rx, utm_nat_hook_tx;
static struct nf_hook_ops ipv4_test;
#if JHASH_ENABLE
static int utm_nat_rnd_init = 0;
static unsigned int utm_nat_hash_rnd = 0;
#endif

#define UTM_NAT_HASH_CONN_MAX utm_nat_htable_size*HASH_TABLE_COMPLEXITY

#if TIME_OUT_POLLING_ENABLE
struct timer_list utm_nat_timer;//for counting timeout 
#endif

struct in6_addr utm_proxy_ip = {{.u6_addr8 = {0x20,0x01,0x0d,0xb8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01}}};	

DEFINE_RWLOCK(utm_nat_lock);//RW LOCK for synchronization

#if DEBUG
static void hex_dump(void *buf, int len)
{
    int i;

    for (i = 0 ; i < len; i++)
    {
	UTM_PRINTK(1,"%02x", ((u8*)buf)[i]);
	if (i%2)
	    UTM_PRINTK(1," ");
	if (15 == i%16)
	    UTM_PRINTK(1,"\n");
    }
    UTM_PRINTK(1,"\n");
}

static void skb_dump(char *name, struct sk_buff *skb)
{
    UTM_PRINTK(1,"+++++++++++++++++++++++++++\n"
	"%s SKB dump skb=%p, data=%p, tail=%p, len=%d\n",
	name, skb, skb->data, skb->tail, skb->len);
    UTM_PRINTK(1,">> data:\n");
    hex_dump(skb->data, skb->len);
    UTM_PRINTK(1,"\n-------------------------\n");
}
#endif

/*****************************************************************
* NAME:    utm_nat_timeout_check
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:
* OUTPUT:   
* Author: George Lin 2012-0621
* Modify:   
******************************************************************/
#if TIME_OUT_POLLING_ENABLE
static inline void
utm_nat_timeout_check(void)
{
    UTM_PRINTK(4,"%s\n", __FUNCTION__);
    UTM_PRINTK(4,"0x%x\n",jiffies);		
    
    struct utm_nat_tuple_hash *h;
    struct hlist_node *node;
    int i;
    
    if(utm_nat_hash==NULL)
    {
	return 0;
    }

    write_lock_bh(&utm_nat_lock);
    for(i=0; i<utm_nat_htable_size; i++)
    {	    
	if(hlist_empty(&utm_nat_hash[i]))
	    continue;

timeout_free:
	hlist_for_each_entry(h, node, &utm_nat_hash[i], utm_list) 
	{
	    if(jiffies - h->tuple.timestamp > (UTM_NAT_SEC_TIMEOUT)*HZ)
	    {
		/*delete entry in table*/
		hlist_del(&h->utm_list);
		kfree(h);
		utm_nat_index --;
		goto timeout_free;
	    }
	}  
    }
    write_unlock_bh(&utm_nat_lock);
    setup_timer(&utm_nat_timer, utm_nat_timeout_check, 0);
    mod_timer(&utm_nat_timer, jiffies+msecs_to_jiffies(UTM_NAT_MSEC_TIMEOUT));
}
#endif

/*****************************************************************
* NAME:    print_ipv6_addr
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:
* OUTPUT:   
* Author: George Lin 2012-0621
* Modify:   
******************************************************************/
static inline void
print_ipv6_addr(struct in6_addr addr)
{
    printk("%s\n", __FUNCTION__);
    u_int32_t* val= (u_int32_t*)&(addr);
    printk("addr:0x%x 0x%x 0x%x 0x%x\n", val[0], val[1], val[2], val[3]);

}

/*****************************************************************
* NAME:    print_tuple
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:
* OUTPUT:   
* Author: George Lin 2012-0621
* Modify:   
******************************************************************/
static inline void
print_tuple(struct utm_nat_tuple tuple)
{
    printk("%s\n", __FUNCTION__);
    print_ipv6_addr(tuple.org_saddr);
    print_ipv6_addr(tuple.org_daddr);
    printk("org_sport:0x%x\n", tuple.org_sport);
    printk("org_dport:0x%x\n", tuple.org_dport);

    printk("rx_fin:0x%x\n", tuple.rx_fin);
    printk("rx_fin_ack:0x%x\n", tuple.rx_fin_ack);
    printk("tx_fin:0x%x\n", tuple.tx_fin);
    printk("tx_fin_ack:0x%x\n", tuple.tx_fin_ack);
}

/*****************************************************************
* NAME:    utm_nat_get_tuple
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:
* OUTPUT:   
* Author: George Lin 2012-0621
* Modify:   
******************************************************************/
static inline void
utm_nat_get_tuple(const struct ipv6hdr *iph,
		  const struct tcphdr *hdr,
		  struct utm_nat_tuple *tuple,
		  struct sk_buff *skb)
{
    //UTM_PRINTK(1,"%s\n", __FUNCTION__);
    tuple->org_saddr = iph->saddr;
    tuple->org_daddr = iph->daddr;
    tuple->org_sport = hdr->source;
    tuple->org_dport = hdr->dest;
    tuple->timestamp = jiffies;
}

/*****************************************************************
* NAME:    utm_nat_tuple_equal
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:
* OUTPUT:   
* Author: George Lin 2012-0621
* Modify:   
******************************************************************/   
static inline int
utm_nat_tuple_equal(const struct utm_nat_tuple *t1,
		      const struct utm_nat_tuple *t2)
{
    UTM_PRINTK(3,"%s\n", __FUNCTION__);
    //print_tuple(*t1);
    //print_tuple(*t2);
    if((t1->org_sport == t2->org_sport)&&
        (t1->org_dport == t2->org_dport)&&  
	ipv6_addr_equal(&(t1->org_saddr), &(t2->org_saddr))&&
	ipv6_addr_equal(&(t1->org_daddr), &(t2->org_daddr))
	   )
	return 1;
    else 
	return 0;
}

/*****************************************************************
* NAME:    utm_nat_inverse_tuple_equal
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:
* OUTPUT:   
* Author: George Lin 2012-0621
* Modify:   
******************************************************************/   
static inline int
utm_nat_inverse_tuple_equal(const struct utm_nat_tuple *t1,
		      const struct utm_nat_tuple *t2)
{
    UTM_PRINTK(3,"%s\n", __FUNCTION__);
    //print_tuple(*t1);
    //print_tuple(*t2);
    if((t1->org_dport == t2->org_sport)&&
	ipv6_addr_equal(&(t1->org_daddr), &(t2->org_saddr))
	   )
	return 1;
    else 
	return 0;
}

/*****************************************************************
* NAME:    hash_conntrack
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:
* OUTPUT:   
* Author: George Lin 2012-0621
* Modify:   
******************************************************************/
static u_int32_t hash_conntrack(const struct utm_nat_tuple *tuple)
{
	/*It generate the hash value*/
#if JHASH_ENABLE	
    
	u_int32_t* val= (u_int32_t*)&(tuple->org_saddr);

	UTM_PRINTK(3,"%s\n", __FUNCTION__);

	return (jhash_3words(val[0]+val[1],
		    val[2]+val[3],
		    (u_int32_t)(ntohs(tuple->org_sport)),
		    utm_nat_hash_rnd)%utm_nat_htable_size);
#else
	int key=0;
	u_int32_t* val= (u_int32_t*)&(tuple->org_saddr);

	UTM_PRINTK(3,"%s\n", __FUNCTION__);

	key = ((val[0] + val[1] + val[2] + val[3] + ((u_int32_t)(ntohs(tuple->org_sport)) & 0xffff)) & 0x7fffffff) % utm_nat_htable_size;
	return key;
#endif
}

/*****************************************************************
* NAME:    hash_inverse_conntrack
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:
* OUTPUT:   
* Author: George Lin 2012-0621
* Modify:   
******************************************************************/
static u_int32_t hash_inverse_conntrack(const struct utm_nat_tuple *tuple)
{
	/*It generate the inverse hash value*/
#if JHASH_ENABLE	
    
	u_int32_t* val= (u_int32_t*)&(tuple->org_daddr);

	UTM_PRINTK(3,"%s\n", __FUNCTION__);

	return (jhash_3words(val[0]+val[1],
		    val[2]+val[3],
		    (u_int32_t)(ntohs(tuple->org_dport)),
		    utm_nat_hash_rnd)%utm_nat_htable_size);
#else
	int key=0;
	u_int32_t* val= (u_int32_t*)&(tuple->org_daddr);

	UTM_PRINTK(3,"%s\n", __FUNCTION__);

	key = ((val[0] + val[1] + val[2] + val[3] + ((u_int32_t)(ntohs(tuple->org_dport)) & 0xffff)) & 0x7fffffff) % utm_nat_htable_size;
	return key;
#endif
}

/*****************************************************************
* NAME:    utm_nat_hash_init
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author: George Lin 2012-0621
* Modify:   
******************************************************************/
static int utm_nat_hash_init(struct hlist_head** pptr, unsigned int table_size)
{
	int i;
	struct hlist_head* ptr;

	UTM_PRINTK(1,"%s\n", __FUNCTION__);
	
	ptr=(struct hlist_head *)kmalloc(
		sizeof(struct hlist_head)*table_size, GFP_ATOMIC);
	if(!ptr)
	{
	    UTM_PRINTK(1,"failed to allocate utm_nat hash table\n");
	    return 0;
	}

	for(i=0; i<table_size; i++)
	{
	    INIT_HLIST_HEAD(&ptr[i]);
	}

	*pptr=ptr;
	
	return 1;
}

/*****************************************************************
* NAME:    utm_nat_hash_clean
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author: George Lin 2012-0621
* Modify:   
******************************************************************/
static int utm_nat_hash_clean()
{
	int i=0;
	struct utm_nat_tuple_hash *h;
	struct hlist_node *node;
	UTM_PRINTK(1,"%s\n", __FUNCTION__);
	
	write_lock_bh(&utm_nat_lock);
	for(i=0; i<utm_nat_htable_size; i++)
	{
	    if(hlist_empty(&utm_nat_hash[i]))
		continue;
free_check:
	    hlist_for_each_entry(h, node, &utm_nat_hash[i], utm_list) 
	    {
		hlist_del(&h->utm_list);
		kfree(h);
		goto free_check;
	    }   
	}
	write_unlock_bh(&utm_nat_lock);
	
	return 1;
}

/*****************************************************************
* NAME:    utm_nat_hash_exit
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author: George Lin 2012-0621
* Modify:   
******************************************************************/
static int utm_nat_hash_exit(struct hlist_head** ptr)
{
	int i=0;
	struct utm_nat_tuple_hash *h;
	struct hlist_node *node;
	UTM_PRINTK(1,"%s\n", __FUNCTION__);
	
	write_lock_bh(&utm_nat_lock);
	for(i=0; i<utm_nat_htable_size; i++)
	{
	    if(hlist_empty(&utm_nat_hash[i]))
		continue;
free_check:
	    hlist_for_each_entry(h, node, &utm_nat_hash[i], utm_list) 
	    {
		hlist_del(&h->utm_list);
		kfree(h);
		goto free_check;
	    }   
	}
	write_unlock_bh(&utm_nat_lock);
	kfree(*ptr);
	
#if JHASH_ENABLE
	utm_nat_rnd_init = 0;
	utm_nat_hash_rnd = 0;
#endif
	return 1;
}

/*****************************************************************
* NAME:    utm_nat_conn_create
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author: George Lin 2012-0621
* Modify:   
******************************************************************/
static int utm_nat_conn_create(struct utm_nat_tuple* tuple)
{
	unsigned int hash;
	struct utm_nat_tuple_hash *h=NULL;
	struct hlist_node *node=NULL;
	struct utm_nat_tuple_hash *ptr=NULL;
	int i=0;

	UTM_PRINTK(3,"+++++\n");
	UTM_PRINTK(3,"%s\n", __FUNCTION__);
	UTM_PRINTK(3,"utm_nat_index:0x%x\n", utm_nat_index);

	//print_tuple(*tuple);
	hash = hash_conntrack(tuple);/*count hash value*/
	UTM_PRINTK(3,"hash:0x%x\n", hash);

	write_lock_bh(&utm_nat_lock);

	/*check the entry is equal or not in table*/
	hlist_for_each_entry(h, node, &utm_nat_hash[hash], utm_list)
	if(utm_nat_tuple_equal(tuple, &h->tuple))
	{	
	    UTM_PRINTK(3,"%s tuple equal\n", __FUNCTION__);
	    h->tuple.timestamp = tuple->timestamp;
	    write_unlock_bh(&utm_nat_lock);
	    return 0;
	}

#if TIME_OUT_DRIVEN_ENABLE
	/*check there is an entry expire or not*/
	for(i=0; i<utm_nat_htable_size; i++)
	{	    
	    if(hlist_empty(&utm_nat_hash[i]))
		continue;

	    hlist_for_each_entry(h, node, &utm_nat_hash[i], utm_list) 
	    {
		if(jiffies - h->tuple.timestamp > (UTM_NAT_SEC_TIMEOUT)*HZ)
		{
		    /*delete entry which is expired in table*/
		    hlist_del(&h->utm_list);
		    utm_nat_index --;
		    /*add entry in table and do not re-allocate memory*/
		    hlist_add_head(&h->utm_list,&utm_nat_hash[hash]);
		    utm_nat_index ++;
		    h->tuple = *tuple;
		    write_unlock_bh(&utm_nat_lock);
		    return 0;
		}
	    }  
	}
#endif
	if(utm_nat_index >= UTM_NAT_HASH_CONN_MAX)
	{
	    write_unlock_bh(&utm_nat_lock);
	    return 1;//Drop it
	}
	/*add new entry in table*/	
	ptr=(struct utm_nat_tuple_hash*)kmalloc(sizeof(struct utm_nat_tuple_hash), GFP_ATOMIC);
	hlist_add_head(&ptr->utm_list,&utm_nat_hash[hash]);
	ptr->tuple = *tuple;
	utm_nat_index++;
	write_unlock_bh(&utm_nat_lock);
	return 0;
}

/*****************************************************************
* NAME:    utm_nat_conn_delete
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author: George Lin 2012-0621
* Modify:   
******************************************************************/
static int utm_nat_conn_delete(struct utm_nat_tuple* tuple)
{
	unsigned int hash;
	struct utm_nat_tuple_hash *h=NULL;
	struct hlist_node *node=NULL;

	UTM_PRINTK(3,"+++++\n");
	UTM_PRINTK(3,"%s\n", __FUNCTION__);
	UTM_PRINTK(3,"utm_nat_index:0x%x\n", utm_nat_index);

	//print_tuple(*tuple);
	hash = hash_conntrack(tuple);/*count hash value*/
	UTM_PRINTK(3,"hash:0x%x\n", hash);

	/*check the entry in table*/
	write_lock_bh(&utm_nat_lock);
	hlist_for_each_entry(h, node, &utm_nat_hash[hash], utm_list)
	if(utm_nat_tuple_equal(tuple, &h->tuple))//we only handle the packet on track
	{	
	    UTM_PRINTK(3,"%s tuple equal\n", __FUNCTION__);	
	    /*delete entry in table*/
	    hlist_del(&h->utm_list);
	    kfree(h);
	    utm_nat_index --;
	    write_unlock_bh(&utm_nat_lock);    
	    return 0;
	}
	else
	{
	    write_unlock_bh(&utm_nat_lock);
	    return 1;//drop the packet, because there is no track for the FIN/RST.
	}

	write_unlock_bh(&utm_nat_lock);
	return 1;//Anyway, drop the packet.
}

/*****************************************************************
* NAME:    utm_nat_inverse_conn_delete
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author: George Lin 2012-0621
* Modify:   
******************************************************************/
static int utm_nat_inverse_conn_delete(struct utm_nat_tuple* tuple)
{
	unsigned int hash;
	struct utm_nat_tuple_hash *h=NULL;
	struct hlist_node *node=NULL;

	UTM_PRINTK(3,"+++++\n");
	UTM_PRINTK(3,"%s\n", __FUNCTION__);
	UTM_PRINTK(3,"utm_nat_index:0x%x\n", utm_nat_index);

	//print_tuple(*tuple);
	hash = hash_inverse_conntrack(tuple);/*count hash value*/
	UTM_PRINTK(3,"hash:0x%x\n", hash);

	/*check the entry in table*/
	write_lock_bh(&utm_nat_lock);
	hlist_for_each_entry(h, node, &utm_nat_hash[hash], utm_list)
	if(utm_nat_inverse_tuple_equal(tuple, &h->tuple))//we only handle the packet on track
	{	
	    UTM_PRINTK(3,"%s tuple equal\n", __FUNCTION__);	
	    /*delete entry in table*/
	    hlist_del(&h->utm_list);
	    kfree(h);
	    utm_nat_index --;
	    write_unlock_bh(&utm_nat_lock);
	    return 0;
	}
	else
	{
	    write_unlock_bh(&utm_nat_lock);
	    return 1;//drop the packet, because there is no track for the FIN/RST.
	}

	write_unlock_bh(&utm_nat_lock);
	return 1;//Anyway, drop the packet.
}

/*****************************************************************
* NAME:    utm_nat_conn_lookup
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author: George Lin 2012-0621
* Modify:   
******************************************************************/
static struct utm_nat_tuple* utm_nat_conn_lookup(struct utm_nat_tuple* tuple)
{
	unsigned int hash;
	struct utm_nat_tuple_hash *h=NULL;
	struct hlist_node *node=NULL;

	UTM_PRINTK(3,"+++++\n");
	UTM_PRINTK(3,"%s\n", __FUNCTION__);
	UTM_PRINTK(3,"utm_nat_index:0x%x\n", utm_nat_index);

	//print_tuple(*tuple);
	hash = hash_conntrack(tuple);/*count hash value*/
	UTM_PRINTK(3,"hash:0x%x\n", hash);

	/*check the entry in table*/
	read_lock_bh(&utm_nat_lock);
	hlist_for_each_entry(h, node, &utm_nat_hash[hash], utm_list)
	if(utm_nat_tuple_equal(tuple, &h->tuple))//we only handle the packet on track
	{	
	    UTM_PRINTK(3,"%s tuple equal\n", __FUNCTION__);
	    h->tuple.timestamp = tuple->timestamp;
	    read_unlock_bh(&utm_nat_lock);
	    return &(h->tuple);
	}
	read_unlock_bh(&utm_nat_lock);
	return NULL;//drop the packet if there is no entry in the table
}

/*****************************************************************
* NAME:    utm_nat_inverse_conn_lookup
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author: George Lin 2012-0621
* Modify:   
******************************************************************/
static struct utm_nat_tuple* utm_nat_inverse_conn_lookup_and_get(struct utm_nat_tuple* tuple, 
    struct utm_nat_tuple* target_tuple)
{
	unsigned int hash;
	struct utm_nat_tuple_hash *h=NULL;
	struct hlist_node *node=NULL;

	UTM_PRINTK(3,"+++++\n");
	UTM_PRINTK(3,"%s\n", __FUNCTION__);

	//print_tuple(*tuple);
	hash = hash_inverse_conntrack(tuple);/*count hash value*/
	UTM_PRINTK(3,"hash:0x%x\n", hash);
	
	read_lock_bh(&utm_nat_lock);

	/*check the entry in table*/
	hlist_for_each_entry(h, node, &utm_nat_hash[hash], utm_list)
	if(utm_nat_inverse_tuple_equal(tuple, &h->tuple))//we only handle the packet on track
	{	
	    UTM_PRINTK(3,"%s tuple equal\n", __FUNCTION__);
	    //UTM_PRINTK(1,"inverse look up success\n");
	    h->tuple.timestamp = tuple->timestamp;

	    /*Get the tuple*/
	    *target_tuple = (h->tuple);
	    read_unlock_bh(&utm_nat_lock);
	    return &(h->tuple);
	}

	read_unlock_bh(&utm_nat_lock);
	return NULL;//drop the packet if there is no entry in the table
}

/*****************************************************************
* NAME:    _utm_nat_rx_handler
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author: George Lin 2012-0621
* Modify:   
******************************************************************/
#if LINUX_VERSION_CODE <= KERNEL_VERSION(2,6,25)
unsigned int _utm_nat_rx_handler(unsigned int hooknum, struct sk_buff **pskb, const struct net_device *in, const struct net_device *out, int (*okfn)(struct sk_buff *))
#else
unsigned int _utm_nat_rx_handler(unsigned int hooknum, struct sk_buff *skb, const struct net_device *in, const struct net_device *out, int (*okfn)(struct sk_buff *))
#endif
{
#if LINUX_VERSION_CODE <= KERNEL_VERSION(2,6,25)
	struct sk_buff *skb = *pskb;
#endif
	struct tcphdr *nhdr;
	struct utm_nat_tuple tuple;
	struct utm_nat_tuple* target=NULL;
	struct ipv6hdr *ipv6_header=(struct ipv6hdr *)skb->data;
	unsigned char nexthdr;
	u_int32_t* tcpflaghdr;
	u_int32_t tcpflag;
	int offset;
	u_int32_t tcp_offset=sizeof(struct ipv6hdr);
	u_int32_t csum;	
	
	if(rx_enable!=1)
	{
		return NF_ACCEPT;
	}

	/* Only handle packets from wireless lan or lan interface. Otherwise, skip it. */
	if((strcmp(skb->dev->name, LOCAL_LAN_DEVICE)!=0))
	{
		return NF_ACCEPT;
	}
	
	if(ipv6_header==NULL)
	{
		UTM_PRINTK(4,"This is not a IPv6 packet. Just skip it\n");
		return NF_ACCEPT;
	}
	
	/* Calculate IPv6 header length (offset). */
	nexthdr = ipv6_header->nexthdr;
	if(ipv6_ext_hdr(nexthdr)) 
	{
		offset = ipv6_skip_exthdr(skb, sizeof(struct ipv6hdr), &nexthdr);
		if(offset < 0)
		{
			return NF_ACCEPT;
		}	
	} 
	else
	{	
		offset = sizeof(struct ipv6hdr);
	}    

	/* Points to TCP header */
	nhdr = (struct tcphdr *)(skb->data + offset);
	
	tcpflaghdr = (u_int32_t*) nhdr;
	tcpflag = tcpflaghdr[3];

	/* If the packet is not a HTTP packets (i.e. TCP, port 80), just skip it. */
	if(nexthdr!=IPPROTO_TCP || nhdr->dest!=HOOK_PORT)
	{
	    return NF_ACCEPT;
	}

	/* Fill tuple information from skb. */
	utm_nat_get_tuple(ipv6_header, nhdr, &tuple, skb);

	if(TCP_FLAG_ACT(tcpflag)&TCP_FLAG_SYN)
	{
	    /* If receiving a TCP SYN packet, lookup, reset timestamp or create the entry. */
	    if(utm_nat_conn_create(&tuple)==UTM_NAT_RX_DROP)
	    {
			return NF_DROP;
	    }
	}
	else if((TCP_FLAG_ACT(tcpflag)&TCP_FLAG_RST))
	{
		/*Delete the connection when RST is received*/
		if(utm_nat_conn_delete(&tuple)==UTM_NAT_RX_DROP)
		{
			return NF_DROP;
		}
	}
	else
	{
		/*lookup and reset timestamp*/
		if((target = utm_nat_conn_lookup(&tuple))==NULL)
		{
			return NF_DROP;
		}

		if((TCP_FLAG_ACT(tcpflag)&TCP_FLAG_FIN))
		{
			target->rx_fin=1;
		}
		
		if((TCP_FLAG_ACT(tcpflag)&TCP_FLAG_ACK) && target->tx_fin==1)
		{
			target->rx_fin_ack=1;
		}

		if(target->rx_fin==1 && target->rx_fin_ack==1 && target->tx_fin==1 && target->tx_fin_ack==1)
		{
			if(utm_nat_conn_delete(&tuple)==UTM_NAT_RX_DROP)
			{
				return NF_DROP;
			}
		}
	}

	/* Modify packet's saddr and port, recalculate TCP checksum, and then redirect it to utmproxy. */
	ipv6_header->daddr = utm_proxy_ip;
	//print_ipv6_addr(ipv6_header->daddr);
	nhdr->dest = UTM_PROXY_PORT;
	nhdr->check = 0;
	csum = csum_ipv6_magic(&ipv6_header->saddr, 
		&ipv6_header->daddr, 
		skb->len - offset,
		nexthdr,
		csum_partial(nhdr, skb->len-offset, 0));
	nhdr->check = csum;
	return NF_ACCEPT;
}

/*****************************************************************
* NAME:    _utm_tx_handler
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author: George Lin 2012-0621
* Modify:   
******************************************************************/
#if LINUX_VERSION_CODE <= KERNEL_VERSION(2,6,25)
unsigned int _utm_nat_tx_handler(unsigned int hooknum, struct sk_buff **pskb, const struct net_device *in, const struct net_device *out, int (*okfn)(struct sk_buff *))
#else
unsigned int _utm_nat_tx_handler(unsigned int hooknum, struct sk_buff *skb, const struct net_device *in, const struct net_device *out, int (*okfn)(struct sk_buff *))
#endif
{
#if LINUX_VERSION_CODE <= KERNEL_VERSION(2,6,25)
	struct sk_buff *skb = *pskb;
#endif
	struct tcphdr *nhdr;
	struct utm_nat_tuple tuple, target_tuple;
	struct utm_nat_tuple* target=NULL;
	struct ipv6hdr *ipv6_header=(struct ipv6hdr *)skb->data;
	unsigned char nexthdr;
	u_int32_t* tcpflaghdr;
	u_int32_t tcpflag;
	int offset;
	u_int32_t tcp_offset=sizeof(struct ipv6hdr);
	u_int32_t csum;
	
	if(tx_enable!=1)
	{
		return NF_ACCEPT;
	}

	if(ipv6_header==NULL)
	{
		UTM_PRINTK(4,"This is not a IPv6 packet. Just skip it\n");
		return NF_ACCEPT;
	}
		
	/* Calculate IPv6 header length (offset). */
	nexthdr = ipv6_header->nexthdr;
	if(ipv6_ext_hdr(nexthdr)) 
	{
		offset = ipv6_skip_exthdr(skb, sizeof(struct ipv6hdr), &nexthdr);
		if (offset < 0)
		{
			return NF_ACCEPT;
		}
	} 
	else
	{
	    offset = sizeof(struct ipv6hdr);
	}
	
	/* Points to TCP header */
	nhdr = (struct tcphdr *)(skb->data + offset);
	tcpflaghdr = (u_int32_t*) nhdr;
	tcpflag = tcpflaghdr[3];

	/* If the packet is not a TCP packet from UTM proxy, just skip it. */
	if(nexthdr != IPPROTO_TCP || nhdr->source != UTM_PROXY_PORT)
	{
		return NF_ACCEPT;
	}

	/* Fill tuple information from skb. */
	utm_nat_get_tuple(ipv6_header, nhdr, &tuple, skb);

	//print_tuple(tuple);

	/* If packet's source ip is not UTM_PROXY_IP, just skip it. */
	if(memcmp(&(tuple.org_saddr), &(utm_proxy_ip),sizeof(struct in6_addr))!=0)
	{
		return NF_ACCEPT;
	}

	if((TCP_FLAG_ACT(tcpflag) & TCP_FLAG_RST))
	{
		/* If receiving TCP RST packet, find out specific entry from table and delete it. */
		if(utm_nat_inverse_conn_delete(&tuple)==UTM_NAT_TX_DROP)
		{
			return NF_DROP;
		}
	}
	else
	{
		if((target=utm_nat_inverse_conn_lookup_and_get(&tuple, &target_tuple))==NULL)
		{
			return NF_DROP;
		}

		if((TCP_FLAG_ACT(tcpflag)&TCP_FLAG_FIN))
		{
			target->tx_fin=1;
		}

		if((TCP_FLAG_ACT(tcpflag)&TCP_FLAG_ACK) && tuple.rx_fin!=0)
		{
			target->tx_fin_ack=1;
		}

		if(target->rx_fin==1 && target->rx_fin_ack==1 && target->tx_fin==1 && target->tx_fin_ack==1)
		{
			if(utm_nat_inverse_conn_delete(&tuple)==UTM_NAT_TX_DROP)
			{
				return NF_DROP;
			}
		}
	}

	/* Modify packet's saddr and port, recalculate TCP checksum, and then send it out . */
	ipv6_header->saddr = target_tuple.org_daddr;
	nhdr->source = target_tuple.org_dport;
	nhdr->check = 0;
	csum = ~csum_ipv6_magic(&ipv6_header->saddr, 
		&ipv6_header->daddr, 
		skb->len - offset,
		nexthdr, 
		0);
	nhdr->check = csum;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,25)
	skb->csum_start = skb_transport_header(skb) - skb->head;
#endif
	skb->csum_offset = offsetof(struct tcphdr,check);
	skb->ip_summed = CHECKSUM_PARTIAL;
	return NF_ACCEPT;
}

/*****************************************************************
* NAME:    read_proc
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author: George Lin 2012-0621
* Modify:   
******************************************************************/
static int read_proc(char* buff, char** start, off_t off, int count, int* eof, void* data)
{	
	struct utm_nat_tuple_hash *h;
	struct hlist_node *node;
	int i;
	int total_count=0;

	printk("%s\n", __FUNCTION__);
	printk("DBG_LV:0x%x\n", DBG_LV);
	if(utm_nat_hash==NULL)
	    return 0;

	read_lock_bh(&utm_nat_lock);
	for(i=0; i<utm_nat_htable_size; i++)
	{
	    hlist_for_each_entry(h, node, &utm_nat_hash[i], utm_list) 
	    {
		printk("hash:0x%x\n", i);
		print_tuple(h->tuple);
		total_count ++;
		printk("\n\n");
	    }  
	}
	read_unlock_bh(&utm_nat_lock);
	printk("==========\n");
	printk("Total tuple count:0x%x\n", total_count);
	printk("utm_nat_index:0x%x\n", utm_nat_index);
	printk("UTM_NAT_HASH_CONN_MAX:0x%x\n", UTM_NAT_HASH_CONN_MAX);
	printk("LOCAL_LAN_DEVICE:%s\n",__local_lan_device);
	printk("UTM_PROXY_PORT:%d\n",__utm_proxy_port);
	printk("HOOK_PORT:%d\n",__hook_port);
	print_ipv6_addr(utm_proxy_ip);
#if JHASH_ENABLE
	printk("utm_nat_hash_rnd:0x%x\n", utm_nat_hash_rnd);
#endif
	printk("\n\n");

	return 0;
}

/*****************************************************************
* NAME:    write_proc
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author: George Lin 2012-0621
* Modify:   
******************************************************************/
static int write_proc(struct file* file, const char* buf, int count, void* data)
{
	int i=0, cmd=0, option=0;

	if(copy_from_user(proc_data, buf, count))
	    return -EFAULT;

	for(i=0;i<count;i++)
	{
		if(i==0)
		    cmd=(int)simple_strtol(&proc_data[i],NULL,10);
		if(i==2)
		    option=(int)simple_strtol(&proc_data[i],NULL,10);
	}

	printk("cmd:%d , option:%d\n", cmd, option);

	printk("\n");

	switch(cmd)
	{
	    case 0:
		if(option < 1)
		    DBG_LV = 1;
		else
		    DBG_LV=option;
		printk("DBG_LV:%d\n", DBG_LV);
		break;
	    case 1:
		if(option!=0)
		    rx_enable = 1;
		else
		    rx_enable = 0;
		printk("rx_enable:%d\n",rx_enable);
		break;
	    case 2:		
		if(option!=0)
		    tx_enable = 1;
		else
		    tx_enable = 0;
		printk("tx_enable:%d\n",tx_enable);
		break;
	    case 3:
		if(option==0)
		{
		    strcpy(__local_lan_device, &proc_data[4]);
		    printk("LOCAL_LAN_DEVICE:%s\n", __local_lan_device);
		}
		else if(option==1)
		{
		    in6_pton(&proc_data[4], -1, (u8*)&utm_proxy_ip,-1, NULL);
		    print_ipv6_addr(utm_proxy_ip);
		}
		else if(option==2)
		{
		    __utm_proxy_port=(int)simple_strtol(&proc_data[4],NULL,10);
		    printk("UTM_PROXY_PORT:%d\n", __utm_proxy_port);    
		}		
		else if(option==3)
		{
		    __hook_port=(int)simple_strtol(&proc_data[4],NULL,10);
		    printk("HOOK_PORT:%d\n", __hook_port);    
		}
		break;
	    case 4:
		utm_nat_hash_clean();
		break;
	    default:
		break;
	}

	return count;
}

/*****************************************************************
* NAME:    utm_nat_init_driver
* ---------------------------------------------------------------
* FUNCTION: Init function of utm_nat module
* INPUT:    void
* OUTPUT:   0 or 1
* Author:   George Lin 2012-0621
* Modify:   
******************************************************************/
static int __init utm_nat_init_driver(void)
{
	struct proc_dir_entry *ent;
	
	UTM_PRINTK(1,"Start %s\n", __FUNCTION__);
	
	if(utm_nat_hash_init(&utm_nat_hash,utm_nat_htable_size))
	{
	    UTM_PRINTK(1,"utm_nat hash table 0x%x allocate OK\n", utm_nat_htable_size);
	}
	else
	{	
	    UTM_PRINTK(1,"utm_nat hash table 0x%x create fail\n", utm_nat_htable_size);
	    return 0;
	}
	    
	ent=create_proc_entry("UTM_NAT", S_IFREG|S_IRWXU, NULL);

#if JHASH_ENABLE
	if(!utm_nat_rnd_init){
	    get_random_bytes(&utm_nat_hash_rnd,4);
	    utm_nat_rnd_init=1;
	}
#endif 

	if(!ent)
	{
	    UTM_PRINTK(1,"create proc fail\n");
	    utm_nat_hash_exit(&utm_nat_hash);
	    return 0;
	}
	else
	{
	    ent->write_proc = write_proc;
	    ent->read_proc = read_proc;
	}

	utm_nat_hook_rx.hook = _utm_nat_rx_handler;
	utm_nat_hook_rx.hooknum = 0;
	utm_nat_hook_rx.pf = PF_INET6;
	utm_nat_hook_rx.priority = NF_IP6_PRI_FIRST;

	utm_nat_hook_tx.hook = _utm_nat_tx_handler;
	utm_nat_hook_tx.hooknum = 4;
	utm_nat_hook_tx.pf = PF_INET6;
	utm_nat_hook_tx.priority = NF_IP6_PRI_FIRST;

	nf_register_hook(&utm_nat_hook_rx);
	nf_register_hook(&utm_nat_hook_tx);

#if TIME_OUT_POLLING_ENABLE
	setup_timer(&utm_nat_timer, utm_nat_timeout_check, 0);
	mod_timer(&utm_nat_timer, jiffies+msecs_to_jiffies(UTM_NAT_MSEC_TIMEOUT));
#endif
	return 0;
}

/*****************************************************************
* NAME:    utm_nat_cleanup_driver
* ---------------------------------------------------------------
* FUNCTION: Exit function of utm_nat module
* INPUT:    void
* OUTPUT:   void
* Author:   George Lin 2012-0621
* Modify:   
******************************************************************/
static void __exit utm_nat_cleanup_driver(void)
{
	int ret;

	UTM_PRINTK(1,"Stop %s\n", __FUNCTION__);

	nf_unregister_hook(&utm_nat_hook_rx);
	nf_unregister_hook(&utm_nat_hook_tx);
	remove_proc_entry("UTM_NAT",NULL);
#if TIME_OUT_POLLING_ENABLE
	ret = del_timer(&utm_nat_timer);
#endif

#if TIME_OUT_POLLING_ENABLE
	if(ret)/*It fails to delete the timer at first time, so we do twice*/
	{
	    UTM_PRINTK(1, "The timer is failed to delete\n");
	    
	    ret = del_timer(&utm_nat_timer);
	    if(ret==0)
		UTM_PRINTK(1, "The timer is success to delete\n");

	}
#endif
	
	if(utm_nat_hash_exit(&utm_nat_hash))
	{
	    UTM_PRINTK(1,"utm_nat hash table free OK\n");
	}
	else
	{
	    UTM_PRINTK(1,"utm_nat hash table free FAIL\n");
	}
	
}

module_init(utm_nat_init_driver);
module_exit(utm_nat_cleanup_driver);
