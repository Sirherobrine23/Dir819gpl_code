/*
 *	Handle incoming frames
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

#include <linux/slab.h>
#include <linux/kernel.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/netfilter_bridge.h>
#include "br_private.h"


/*
 * TBS_TAG: by pengyao 2012-05-23
 * Desc: add IGMP Snooping support
 */
#if defined(CONFIG_IGMP_SNOOPING)
#include <linux/if_vlan.h>
#include <linux/timer.h>
#include <linux/igmp.h>
#include <linux/ip.h>
#endif
#if defined(CONFIG_BR_MLD_SNOOP)
#include "br_mld.h"
#endif
/*
 * TBS_TAG: add pengyao 20130720
 * Desc: for pppoe proxy
 */
union ip_array {
    unsigned int ip_addr;
    unsigned char ip_ar[4];
};
/*
 * TBS_END_TAG
 */
/* Bridge group multicast address 802.1d (pg 51). */
const u8 br_group_address[ETH_ALEN] = { 0x01, 0x80, 0xc2, 0x00, 0x00, 0x00 };

/*************************************************************************
功能: 对于进入本机的vlan 数据，移除VLAN 头，进入协议栈处理
参数: skb
返回: netif_receive_skb(skb);
备注:
*************************************************************************/
static int br_pass_frame_up_finish(struct sk_buff *skb)
{
#ifdef CONFIG_NETFILTER_DEBUG
	skb->nf_debug = 0;
#endif
#if 1
	/* If pass up to IP, remove VLAN header */
	if (skb->protocol == __constant_htons(ETH_P_8021Q)) {
		unsigned short proto;
		struct vlan_hdr *vhdr = (struct vlan_hdr *)(skb->data);

        /* make sure protocol is correct before passing up */
        proto = vhdr->h_vlan_encapsulated_proto;

		skb = skb_share_check(skb, GFP_ATOMIC);
		if (skb) {
			memmove(skb->data - ETH_HLEN + VLAN_HLEN,
				skb->data - ETH_HLEN, 12);
			skb_pull(skb, VLAN_HLEN);
			skb->mac_header+= VLAN_HLEN;
		}
		/* 重置skb->protocol为vlan标签后面接的协议类型，之前的protocol为0x8100(即ETH_P_8021Q)*/
		skb->protocol = proto;
		/* TODO: do we need to assign skb->priority? */
	}
#endif
	return netif_receive_skb(skb);
}

static int br_pass_frame_up(struct sk_buff *skb)
{
	struct net_device *indev, *brdev = BR_INPUT_SKB_CB(skb)->brdev;
	struct net_bridge *br = netdev_priv(brdev);
	struct br_cpu_netstats *brstats = this_cpu_ptr(br->stats);

	u64_stats_update_begin(&brstats->syncp);
	brstats->rx_packets++;
	brstats->rx_bytes += skb->len;
	u64_stats_update_end(&brstats->syncp);

	indev = skb->dev;
	skb->dev = brdev;

	return NF_HOOK(NFPROTO_BRIDGE, NF_BR_LOCAL_IN, skb, indev, NULL,
		       br_pass_frame_up_finish);
}


/*
 * TBS_TAG: by pengyao 2012-05-23
 * Desc: add IGMP Snooping support
 */
#if 0
void DumpPacket(char *tag,struct sk_buff *skb)
{
    int i=0;
	char *s;
	s=skb->data-14;
    printk("\n###############################################\n");
    printk("\n****** %s ******\n",tag);
	for(i=0;i<14;i++)
		printk("%02x ",*s++);
    for(i=0;i<skb->len;i++)
    {
             if( i%16 == 0)
                     printk("\n0x%08x:",i);
             if( i%4 == 0)
                     printk(" ");

             printk("%02x ",skb->data[i]);
     }

     printk("\n\n###############################################\n\n");
     printk("\n\n");
}
#endif
#if defined(CONFIG_IGMP_SNOOPING)
static void addr_conv(unsigned char *in, unsigned char * out)
{
    sprintf(out, "%02x%02x%02x%02x%02x%02x", in[0], in[1], in[2], in[3], in[4], in[5]);
}

mac_addr upnp_addr = {{0x01, 0x00, 0x5e, 0x7f, 0xff, 0xfa}};
mac_addr sys1_addr = {{0x01, 0x00, 0x5e, 0x00, 0x00, 0x01}};
mac_addr sys2_addr = {{0x01, 0x00, 0x5e, 0x00, 0x00, 0x02}};
mac_addr ospf1_addr = {{0x01, 0x00, 0x5e, 0x00, 0x00, 0x05}};
mac_addr ospf2_addr = {{0x01, 0x00, 0x5e, 0x00, 0x00, 0x06}};
mac_addr ripv2_addr = {{0x01, 0x00, 0x5e, 0x00, 0x00, 0x09}};
mac_addr sys_addr = {{0xff, 0xff, 0xff, 0xff, 0xff, 0xff}};

/* Define ipv6 multicast mac address to let them pass through control filtering.
 * All ipv6 multicast mac addresses start with 0x33 0x33. So control_filter
 * only need to compare the first 2 bytes of the address.
 */
mac_addr ipv6_mc_addr = {{0x33, 0x33, 0x00, 0x00, 0x00, 0x00}}; /* only the left two bytes are significant */

static int control_filter(unsigned char *dest, struct iphdr *pip)
{

#if 0
    if (  ( (!memcmp(dest, &upnp_addr, ETH_ALEN))
           && (!memcmp(&pip->daddr, upnp_ip_addr, sizeof(struct in_addr))))
        || ( (!memcmp(dest, &sys1_addr, ETH_ALEN))
            && (!memcmp(&pip->daddr, sys1_ip_addr, sizeof(struct in_addr))))
        || ( (!memcmp(dest, &sys2_addr, ETH_ALEN))
            && (!memcmp(&pip->daddr, sys2_ip_addr, sizeof(struct in_addr))))
        || ( (!memcmp(dest, &ospf1_addr, ETH_ALEN))
            && (!memcmp(&pip->daddr, ospf1_ip_addr, sizeof(struct in_addr))))
        || ( (!memcmp(dest, &ospf2_addr, ETH_ALEN))
            && (!memcmp(&pip->daddr, ospf2_ip_addr, sizeof(struct in_addr))))
        || ( (!memcmp(dest, &ripv2_addr, ETH_ALEN))
            && (!memcmp(&pip->daddr, ripv2_ip_addr, sizeof(struct in_addr))))
        || (!memcmp(dest, &sys_addr, ETH_ALEN))
        || (!memcmp(dest, &ipv6_mc_addr, 2)) )
        return 0;
#else
    if ((!memcmp(dest, &upnp_addr, ETH_ALEN)) ||
            (!memcmp(dest, &sys1_addr, ETH_ALEN)) ||
            (!memcmp(dest, &sys2_addr, ETH_ALEN)) ||
            (!memcmp(dest, &ospf1_addr, ETH_ALEN)) ||
            (!memcmp(dest, &ospf2_addr, ETH_ALEN)) ||
            (!memcmp(dest, &sys_addr, ETH_ALEN)) ||
            (!memcmp(dest, &ripv2_addr, ETH_ALEN)) ||
            (!memcmp(dest, &ipv6_mc_addr, 2)))
        return 0;
#endif
    else
        return 1;
}

static inline void brcm_conv_ip_to_mac(char *ipa, char *maca)
{
    maca[0] = 0x01;
    maca[1] = 0x00;
    maca[2] = 0x5e;
    maca[3] = 0x7F & ipa[1];
    maca[4] = ipa[2];
    maca[5] = ipa[3];

    return;
}

static void br_process_igmpv3(struct net_bridge *br, struct sk_buff *skb, struct igmpv3_report *report)
{
    struct igmpv3_grec *grec;
    int i;
    struct in_addr src;
    union ip_array igmpv3_mcast;
    int num_src;
    unsigned char tmp[6];
    struct net_bridge_mc_fdb_entry *mc_fdb;

    if(report) {
        grec = &report->grec[0];
        for(i = 0; i < ntohs(report->ngrec); i++) {
            igmpv3_mcast.ip_addr = grec->grec_mca;
            brcm_conv_ip_to_mac(igmpv3_mcast.ip_ar, tmp);
            switch(grec->grec_type) {
                case IGMPV3_MODE_IS_INCLUDE:
                case IGMPV3_CHANGE_TO_INCLUDE:
                case IGMPV3_ALLOW_NEW_SOURCES:
                    for(num_src = 0; num_src < ntohs(grec->grec_nsrcs); num_src++) {
                        src.s_addr = grec->grec_src[num_src];
                        mc_fdb = br_mc_fdb_find(br, br_port_get_rcu(skb->dev), eth_hdr(skb)->h_source,
                            &src, &grec->grec_mca);
#if 0
                        if((NULL != mc_fdb) &&
                                (mc_fdb->src_entry.filt_mode == MCAST_EXCLUDE)) {
                            br_mc_fdb_remove(br, br_port_get_rcu(skb->dev), tmp, eth_hdr(skb)->h_source, SNOOP_EX_CLEAR, &src);
                        }
#else
                        if(NULL != mc_fdb){
                            if (mc_fdb->src_entry.filt_mode == MCAST_EXCLUDE)
                                br_mc_fdb_remove(br, br_port_get_rcu(skb->dev), eth_hdr(skb)->h_source,
                                SNOOP_EX_CLEAR, &src, &grec->grec_mca);
                            else if (ip_hdr(skb)->daddr != IGMP_ALL_HOSTS)
                                br_mc_fdb_update(br, br_port_get_rcu(skb->dev), eth_hdr(skb)->h_source,
                                SNOOP_IN_ADD, &src, &grec->grec_mca);
                        }
#endif
                        else {
                            br_mc_fdb_add_by_host(br, br_port_get_rcu(skb->dev), eth_hdr(skb)->h_source,
                                SNOOP_IN_ADD, &src, &grec->grec_mca);
                        }
                    }

                    if(0 == ntohs(grec->grec_nsrcs)) {
                        src.s_addr = 0;
                        br_mc_fdb_remove(br, br_port_get_rcu(skb->dev), eth_hdr(skb)->h_source, SNOOP_EX_CLEAR,
                            &src, &grec->grec_mca);
                    }
                    break;

                case IGMPV3_MODE_IS_EXCLUDE:
                case IGMPV3_CHANGE_TO_EXCLUDE:
                case IGMPV3_BLOCK_OLD_SOURCES:
                    for(num_src = 0; num_src < ntohs(grec->grec_nsrcs); num_src++) {
                        src.s_addr = grec->grec_src[num_src];
                        mc_fdb = br_mc_fdb_find(br, br_port_get_rcu(skb->dev), eth_hdr(skb)->h_source, &src,
                            &grec->grec_mca);
#if 0
                        if((NULL != mc_fdb) &&
                                (mc_fdb->src_entry.filt_mode == MCAST_INCLUDE)) {
                            br_mc_fdb_remove(br, br_port_get_rcu(skb->dev), tmp, eth_hdr(skb)->h_source, SNOOP_IN_CLEAR, &src);
                        }
#else
                        if(NULL != mc_fdb) {
                            if (mc_fdb->src_entry.filt_mode == MCAST_INCLUDE)
                                br_mc_fdb_remove(br, br_port_get_rcu(skb->dev), eth_hdr(skb)->h_source, SNOOP_IN_CLEAR,
                                &src, &grec->grec_mca);
                            else if (ip_hdr(skb)->daddr != IGMP_ALL_HOSTS)
                                br_mc_fdb_update(br, br_port_get_rcu(skb->dev), eth_hdr(skb)->h_source,  SNOOP_EX_ADD,
                                &src, &grec->grec_mca);
                        }
#endif
                        else {
                            br_mc_fdb_add_by_host(br, br_port_get_rcu(skb->dev), eth_hdr(skb)->h_source, SNOOP_EX_ADD,
                                &src, &grec->grec_mca);
                        }
                    }

                    if(0 == ntohs(grec->grec_nsrcs)) {
                        src.s_addr = 0;
                        br_mc_fdb_add_by_host(br, br_port_get_rcu(skb->dev), eth_hdr(skb)->h_source, SNOOP_EX_ADD,
                            &src, &grec->grec_mca);
                    }
                    break;
            }
            grec = (struct igmpv3_grec *)((char *)grec + IGMPV3_GRP_REC_SIZE(grec));
        }
    }
    return;
}

void multicast2unicast(struct sk_buff *skb, unsigned char *host)
{
    unsigned char *dest = eth_hdr(skb)->h_dest;
    memcpy(dest,host,6);
    return;
}


int mc_forward(struct net_bridge *br, struct sk_buff *skb, unsigned char *dest,int forward)
{
    struct net_bridge_mc_fdb_entry *dst;
    struct net_bridge_mc_fdb_entry fdb;
    struct net_bridge_mc_fdb_entry *dst_tmp = &fdb;
    int status = 0;
    int filter_past = 0;    //info for exclude mode
    struct sk_buff *skb2;
    struct net_bridge_port *p;
    //unsigned char tmp[6];
    const unsigned char bad_mac[ETH_ALEN];
    struct igmpv3_report *report;
    struct iphdr *pip = ip_hdr(skb);
    struct in_addr src;
    unsigned char igmp_type = 0;
    unsigned char mcaddr[6]={0};
    struct igmphdr *igmp_gen = NULL;

    if (!igmpsnooping)
        return 0;

    memcpy(mcaddr,dest,6);
    /*
       if ((igmpsnooping == SNOOPING_BLOCKING_MODE) && control_filter(dest))
       status = 1;
    */

    if(pip->version != 4)
        return 0;

    if (control_filter(mcaddr, pip))
        status = 1;

	//if(printk_ratelimit())
    	//printk("mc forward  proto = %d  proxy = %d\n", skb->data[9], br->proxy);

    if (skb->data[9] == IPPROTO_IGMP) {
        // For proxy; need to add some intelligence here
        if (!br->proxy) {
            if(pip->ihl == 5) {
                igmp_gen = (struct igmphdr *)&skb->data[20];
            } else {
                igmp_gen = (struct igmphdr *)&skb->data[24];
            }

            igmp_type = igmp_gen->type;
            if (((igmp_type == IGMPV2_HOST_MEMBERSHIP_REPORT) ||
                (igmp_type == IGMP_HOST_MEMBERSHIP_REPORT)) &&
                    (skb->protocol == __constant_htons(ETH_P_IP))) {
                src.s_addr = 0;
                br_mc_fdb_add_by_host(br, br_port_get_rcu(skb->dev), eth_hdr(skb)->h_source, SNOOP_EX_ADD,
                    &src, &igmp_gen->group);
                if (ip_hdr(skb)->daddr != IGMP_ALL_HOSTS)
                {
                    br_mc_fdb_update(br, br_port_get_rcu(skb->dev), eth_hdr(skb)->h_source, SNOOP_EX_ADD,
                        &src, &igmp_gen->group);
                }
            }
            else if((igmp_type == IGMPV3_HOST_MEMBERSHIP_REPORT) &&
                    (skb->protocol == __constant_htons(ETH_P_IP)))
            {
                report = (struct igmpv3_report *)igmp_gen;

                if(report) {
                br_process_igmpv3(br, skb, report);
                }
            }
            else if (igmp_type == IGMP_HOST_LEAVE_MESSAGE)
            {
                src.s_addr = 0;
                br_mc_fdb_remove(br, br_port_get_rcu(skb->dev), eth_hdr(skb)->h_source, SNOOP_EX_CLEAR,
                    &src, &igmp_gen->group);
            }
            else
                ;
        }
        return 0;
    }

    memset(&fdb, 0, sizeof(fdb));
    memset(&bad_mac, 0, sizeof(bad_mac));
    list_for_each_entry_rcu(dst, &br->mc_list, list) {

        if (pip->daddr == dst->group_addr.s_addr) {

            //filter mode as include
            if((dst->src_entry.filt_mode == MCAST_INCLUDE) &&
                    (pip->saddr == dst->src_entry.src.s_addr)) {
                goto deliver_or_forward;
            }
            //filter mode as exclude
            else if(dst->src_entry.filt_mode == MCAST_EXCLUDE) {
                if(0 == dst->src_entry.src.s_addr){
                    goto deliver_or_forward;
                }
                else if(pip->saddr == dst->src_entry.src.s_addr) {
                    status = 1;
                    filter_past = 0;
                }
            }

            /*
             *because mc_list is host-sorted, another host comes
             *with a different host mac.if it comes to another
             *host fdb-entry, it's time to conclude whether a
             *group source is exclude by pre-host
             */
            if (memcmp(&(dst_tmp->host), &(dst->host), ETH_ALEN)){
                if ((memcmp(&(dst_tmp->host), bad_mac, ETH_ALEN))
                        && (dst_tmp->src_entry.filt_mode == MCAST_EXCLUDE)
                        && filter_past == 1){
                    filter_past = 0;
                    dst = dst_tmp;
                    goto deliver_or_forward;
                }

                dst_tmp = dst ;
            }

            continue;
deliver_or_forward:
            if (!dst->dst->dirty) {
                if (forward){
                  	//printk("include mode br_forward to %s\n", dst->dst->dev->name);
                    br_forward(dst->dst, skb, skb);
                }
                else
                {
                    skb2 = skb_clone(skb, GFP_ATOMIC);
                    br_deliver(dst->dst, skb2);
                }
            }


            dst->dst->dirty = 1;
            status = 1;

            dst_tmp = dst;
            filter_past = 1;

        }
    }

    if (status) {
        list_for_each_entry_rcu(p, &br->port_list, list) {
            p->dirty = 0;
        }
    }

    if ((!forward) && (status))
        kfree_skb(skb);

    return status;
}

#endif
/*
 * TBS_END_TAG
 */

/*2016-08-12 linsd add for wlan guest isolate */
#if defined (CONFIG_BR_WLAN_BLOCK_RELAY)
#define RT_WLAN_INT_2G "ra1"
#define RT_WLAN_INT_5G "rai1"
extern int br_wlan_block_relay_enable;
#endif 
/*2016-08-12 end*/

/* note: already called with rcu_read_lock */
int br_handle_frame_finish(struct sk_buff *skb)
{
	const unsigned char *dest = eth_hdr(skb)->h_dest;
	struct net_bridge_port *p = br_port_get_rcu(skb->dev);
	struct net_bridge *br;
	struct net_bridge_fdb_entry *dst = NULL;
	#ifndef CONFIG_IGMP_SNOOPING
	struct net_bridge_mdb_entry *mdst;
	#endif
	struct sk_buff *skb2;

	if (!p || p->state == BR_STATE_DISABLED)
		goto drop;

	/* insert into forwarding database after filtering to avoid spoofing */
	br = p->br;

#ifdef CONFIG_LOOPBACK_CHECK
	if(br_fdb_update(br, p, eth_hdr(skb)->h_source) == -1)
	{
		goto drop;
	}
#else
	br_fdb_update(br, p, eth_hdr(skb)->h_source);
#endif

	if (is_multicast_ether_addr(dest) &&
	    br_multicast_rcv(br, p, skb))
		goto drop;

	if (p->state == BR_STATE_LEARNING)
		goto drop;

	BR_INPUT_SKB_CB(skb)->brdev = br->dev;

	/* The packet skb2 goes to the local host (NULL to skip). */
	skb2 = NULL;

	if (br->dev->flags & IFF_PROMISC)
		skb2 = skb;

/*
 * TBS_TAG: by pengyao 2012-05-23
 * Desc:Add IGMP Snooping support
 */
#if defined(CONFIG_BR_MLD_SNOOP)
	if((0x33 == dest[0]) && (0x33 == dest[1])) {
		br->dev->stats.multicast++;
        skb2 = skb;

		br_mld_process_info(br, skb);
		if (br_mld_mc_forward(br, skb, dest, 1))
		{
            if(!skb2)
                kfree_skb(skb );

            skb = NULL;
		}

	} else
#endif
/*
 * TBS_TAG_END
 */

	if (is_multicast_ether_addr(dest)) {
/*
 * TBS_TAG: by pengyao 2012-05-23
 * Desc:Add IGMP Snooping support
 */
#define MULTICAST_MAC(mac) 	   ((mac[0]==0x01)&&(mac[1]==0x00)&&(mac[2]==0x5e))
#if defined(CONFIG_IGMP_SNOOPING)

        skb2 = skb;

        if (igmpsnooping && MULTICAST_MAC(dest) &&
            ntohs(skb->protocol) == ETH_P_IP)
        {
            //printk("----in %s:%d, igmpsnooping enable\n", __FILE__, __LINE__);
            if (mc_forward(br, skb, (unsigned char*)dest, 1))
            {
                //printk("----in %s:%d, mc_forward success\n", __FILE__, __LINE__);
                if(!skb2)
                    kfree_skb(skb);

                skb = NULL;
            }
            else
            {
                //如果是igmp报文需要转发，泛洪到其他接口
                //printk("----in %s:%d, mc_forward fail\n", __FILE__, __LINE__);
            }
        }
#else
		mdst = br_mdb_get(br, skb);
		if (mdst || BR_INPUT_SKB_CB_MROUTERS_ONLY(skb)) {
			if ((mdst && !hlist_unhashed(&mdst->mglist)) ||
			    br_multicast_is_router(br))
				skb2 = skb;
			br_multicast_forward(mdst, skb, skb2);
			skb = NULL;
			if (!skb2)
				goto out;
		} else
			skb2 = skb;
#endif
/*
 * TBS_END_TAG
 */
		br->dev->stats.multicast++;
	} else if ((dst = __br_fdb_get(br, dest)) && dst->is_local) {
		skb2 = skb;
		/* Do not forward the packet since it's local. */
		skb = NULL;
	}

	if (skb) {
		if (dst)
		{
/*2016-08-12 linsd add for wlan isolate */
#if defined (CONFIG_BR_WLAN_BLOCK_RELAY)
			if (br_wlan_block_relay_enable)
			{
				if((!memcmp(skb->dev->name,RT_WLAN_INT_2G,sizeof(RT_WLAN_INT_2G)-1))
					||(!memcmp(skb->dev->name,RT_WLAN_INT_5G,sizeof(RT_WLAN_INT_5G)-1)))
					goto drop;
			}
#endif
			br_forward(dst->dst, skb, skb2);
		}
		else
			br_flood_forward(br, skb, skb2);
	}

	if (skb2)
		return br_pass_frame_up(skb2);

out:
	return 0;
drop:
	kfree_skb(skb);
	goto out;
}

/* note: already called with rcu_read_lock */
static int br_handle_local_finish(struct sk_buff *skb)
{
	struct net_bridge_port *p = br_port_get_rcu(skb->dev);

	br_fdb_update(p->br, p, eth_hdr(skb)->h_source);
	return 0;	 /* process further */
}

/* Does address match the link local multicast address.
 * 01:80:c2:00:00:0X
 */
static inline int is_link_local(const unsigned char *dest)
{
	__be16 *a = (__be16 *)dest;
	static const __be16 *b = (const __be16 *)br_group_address;
	static const __be16 m = cpu_to_be16(0xfff0);

	return ((a[0] ^ b[0]) | (a[1] ^ b[1]) | ((a[2] ^ b[2]) & m)) == 0;
}

/*
 * Return NULL if skb is handled
 * note: already called with rcu_read_lock
 */
struct sk_buff *br_handle_frame(struct sk_buff *skb)
{
	struct net_bridge_port *p;
	const unsigned char *dest = eth_hdr(skb)->h_dest;
	int (*rhook)(struct sk_buff *skb);

	if (skb->pkt_type == PACKET_LOOPBACK)
		return skb;

	if (!is_valid_ether_addr(eth_hdr(skb)->h_source))
		goto drop;

	skb = skb_share_check(skb, GFP_ATOMIC);
	if (!skb)
		return NULL;

	p = br_port_get_rcu(skb->dev);

#ifdef CONFIG_SOCKET_BIND_BRPORT
    /* TBS_TAG: by Sudenghai 2014-2-28*/
    struct iphdr *ip;
    ip = ip_hdr(skb);
    /*skb->recvif为空，直接设置成*/
	if(skb->recvif[0] == '\0' ||
			/*skb->recvif不为空，且为igmp报文，skb->recvif在__netif_receive_skb函数中已经设置成了端口设备，则在这里替换为桥设备，igmp进程要用到*/
			((strcmp(skb->recvif, skb->dev->name) == 0) && (ip->protocol == IPPROTO_IGMP)))
    {    	
    	/*替换成桥设备，例如br0*/
    	strncpy(skb->recvif, p->br->dev->name, sizeof(skb->recvif) - 1);
    }
		
#endif

	if (unlikely(is_link_local(dest))) {
		/* Pause frames shouldn't be passed up by driver anyway */
		if (skb->protocol == htons(ETH_P_PAUSE))
			goto drop;

		/* If STP is turned off, then forward */
		if (p->br->stp_enabled == BR_NO_STP && dest[5] == 0)
			goto forward;

		if (NF_HOOK(NFPROTO_BRIDGE, NF_BR_LOCAL_IN, skb, skb->dev,
			    NULL, br_handle_local_finish))
			return NULL;	/* frame consumed by filter */
		else
			return skb;	/* continue processing */
	}

forward:
	switch (p->state) {
	case BR_STATE_FORWARDING:
		rhook = rcu_dereference(br_should_route_hook);
		if (rhook != NULL) {
			if (rhook(skb))
				return skb;
			dest = eth_hdr(skb)->h_dest;
		}
		/* fall through */
	case BR_STATE_LEARNING:
		if (!compare_ether_addr(p->br->dev->dev_addr, dest))
			skb->pkt_type = PACKET_HOST;

		NF_HOOK(NFPROTO_BRIDGE, NF_BR_PRE_ROUTING, skb, skb->dev, NULL,
			br_handle_frame_finish);
		break;
	default:
drop:
		kfree_skb(skb);
	}
	return NULL;
}
