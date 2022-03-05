/*
 * This is a module which is used for rejecting packets.
 */

/* (C) 1999-2001 Paul `Rusty' Russell
 * (C) 2002-2004 Netfilter Core Team <coreteam@netfilter.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#include <linux/module.h>
#include <linux/skbuff.h>
#include <linux/slab.h>
#include <linux/ip.h>
#include <linux/udp.h>
#include <linux/icmp.h>
#include <net/icmp.h>
#include <net/ip.h>
#include <net/tcp.h>
#include <net/route.h>
#include <net/dst.h>
#include <linux/netfilter/x_tables.h>
#include <linux/netfilter_ipv4/ip_tables.h>
#include <linux/netfilter_ipv4/ipt_REJECT.h>
#ifdef CONFIG_BRIDGE_NETFILTER
#include <linux/netfilter_bridge.h>
#endif

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Netfilter Core Team <coreteam@netfilter.org>");
MODULE_DESCRIPTION("Xtables: packet \"rejection\" target for IPv4");


static void send_reset_netgear(struct sk_buff *oldskb)
{
	struct iphdr *iph = NULL;
	struct tcphdr *tcph;
	//int needs_ack;

    if (!skb_make_writable(oldskb, oldskb->len))
        return;

	iph = (struct iphdr *)skb_network_header(oldskb);
	tcph = (struct tcphdr *)((u_int32_t*)iph + iph->ihl);

	/* Truncate to length (no data) */
	skb_trim(oldskb, iph->ihl*4 + sizeof(struct tcphdr));
	iph->tot_len = htons(oldskb->len);

	/* Reset flags */
	((u_int8_t *)tcph)[13] = 0;
	tcph->rst = 1;
	tcph->ack = 1;

	tcph->window = 0;
	tcph->urg_ptr = 0;

	/* Adjust TCP checksum */
	tcph->check = 0;
	tcph->check = tcp_v4_check(sizeof(struct tcphdr),
				   iph->saddr,
				   iph->daddr,
				   csum_partial((char *)tcph,
						sizeof(struct tcphdr), 0));

	/* Adjust IP TTL, DF */
	//iph->ttl = dst_metric(nskb->dst, RTAX_HOPLIMIT);
	/* Set DF, id = 0 */
	iph->frag_off = htons(IP_DF);
	//iph->id = 0;

	/* Adjust IP checksum */
	iph->check = 0;
	iph->check = ip_fast_csum((unsigned char *)iph, 
					   iph->ihl);

    return;
}


static inline struct rtable *route_reverse(struct sk_buff *skb, int hook)
{
        struct iphdr *iph = (struct iphdr *)skb_network_header(skb);
        struct dst_entry *odst;
        struct flowi fl = {};
        struct rtable *rt;
        /* We don't require ip forwarding to be enabled to be able to
         * send a RST reply for bridged traffic. */
        if (hook != NF_INET_FORWARD
#ifdef CONFIG_BRIDGE_NETFILTER
            || (skb->nf_bridge && skb->nf_bridge->mask & BRNF_BRIDGED)
#endif
           ) {
		   		/*源IP*/
                fl.nl_u.ip4_u.daddr = iph->saddr;
                if (hook == NF_INET_LOCAL_IN)
                        fl.nl_u.ip4_u.saddr = iph->daddr;
                fl.nl_u.ip4_u.tos = RT_TOS(iph->tos);

                if (ip_route_output_key(&init_net, &rt, &fl) != 0)
                        return NULL;
        } else {
                /* non-local src, find valid iif to satisfy
                 * rp-filter when calling ip_route_input. */
                fl.nl_u.ip4_u.daddr = iph->daddr;
                if (ip_route_output_key(&init_net, &rt, &fl) != 0)
                        return NULL; 

                odst = skb_dst(skb);
                if (ip_route_input(skb, iph->saddr, iph->daddr,
                                   RT_TOS(iph->tos), rt->dst.dev) != 0) {
                        dst_release(&rt->dst);
                        return NULL;
                }
                dst_release(&rt->dst);
                rt = (struct rtable *)skb_dst(skb);
                skb_dst_set(skb, odst);
        }
 
      if (rt->dst.error) {
                dst_release(&rt->dst);
                rt = NULL;
        }

        return rt;
}


/* Send RST reply */
static void send_reset(struct sk_buff *oldskb, int hook)
{
	struct sk_buff *nskb;
	const struct iphdr *oiph;
	struct iphdr *niph;
	const struct tcphdr *oth;
	struct tcphdr _otcph, *tcph;
	unsigned int addr_type;

	/* IP header checks: fragment. */
	if (ip_hdr(oldskb)->frag_off & htons(IP_OFFSET))
		return;

	oth = skb_header_pointer(oldskb, ip_hdrlen(oldskb),
				 sizeof(_otcph), &_otcph);
	if (oth == NULL)
		return;

	/* No RST for RST. */
	if (oth->rst)
		return;

	/* Check checksum */
	if (nf_ip_checksum(oldskb, hook, ip_hdrlen(oldskb), IPPROTO_TCP))
		return;
	oiph = ip_hdr(oldskb);

	nskb = alloc_skb(sizeof(struct iphdr) + sizeof(struct tcphdr) +
			 LL_MAX_HEADER, GFP_ATOMIC);
	if (!nskb)
		return;

	skb_reserve(nskb, LL_MAX_HEADER);

	skb_reset_network_header(nskb);
	niph = (struct iphdr *)skb_put(nskb, sizeof(struct iphdr));
	niph->version	= 4;
	niph->ihl	= sizeof(struct iphdr) / 4;
	niph->tos	= 0;
	niph->id	= 0;
	niph->frag_off	= htons(IP_DF);
	niph->protocol	= IPPROTO_TCP;
	niph->check	= 0;
	niph->saddr	= oiph->daddr;
	niph->daddr	= oiph->saddr;

	tcph = (struct tcphdr *)skb_put(nskb, sizeof(struct tcphdr));
	memset(tcph, 0, sizeof(*tcph));
	tcph->source	= oth->dest;
	tcph->dest	= oth->source;
	tcph->doff	= sizeof(struct tcphdr) / 4;
    tcph->window = oth->window;

	if (oth->ack)
		tcph->seq = oth->ack_seq;
	else {
		tcph->ack_seq = htonl(ntohl(oth->seq) + oth->syn + oth->fin +
				      oldskb->len - ip_hdrlen(oldskb) -
				      (oth->doff << 2));
		tcph->ack = 1;
	}

	tcph->rst	= 1;
	tcph->check = ~tcp_v4_check(sizeof(struct tcphdr), niph->saddr,
				    niph->daddr, 0);
	nskb->ip_summed = CHECKSUM_PARTIAL;
	nskb->csum_start = (unsigned char *)tcph - nskb->head;
	nskb->csum_offset = offsetof(struct tcphdr, check);

	addr_type = RTN_UNSPEC;
	if (hook != NF_INET_FORWARD
#ifdef CONFIG_BRIDGE_NETFILTER
	    || (nskb->nf_bridge && nskb->nf_bridge->mask & BRNF_BRIDGED)
#endif
	   )
		addr_type = RTN_LOCAL;

	/* ip_route_me_harder expects skb->dst to be set */
	skb_dst_set_noref(nskb, skb_dst(oldskb));

	nskb->protocol = htons(ETH_P_IP);
	if (ip_route_me_harder(nskb, addr_type))
		goto free_nskb;

	niph->ttl	= dst_metric(skb_dst(nskb), RTAX_HOPLIMIT);

	/* "Never happens" */
	if (nskb->len > dst_mtu(skb_dst(nskb)))
		goto free_nskb;

	nf_ct_attach(nskb, oldskb);

	ip_local_out(nskb);
	return;

 free_nskb:
	kfree_skb(nskb);
}

static void send_block_site_page(struct sk_buff *oldskb, int hook)
{
    struct sk_buff *nskb;
    struct tcphdr otcph, *tcph;
    struct iphdr *iph = (struct iphdr *)skb_network_header(oldskb);
    struct iphdr *new_iph = NULL;
    u_int16_t tmp_port;
    u_int32_t tmp_addr;
    int needs_ack;
    char *dptr = NULL;
    struct rtable *rt;

	unsigned char *web_block_page = "HTTP/1.0 200 OK\nContent-type: text/html\r\nData: Thu, 01 Jan 1970 00:00:00 GMT\r\nConnection: close\r\nLast-modified: Sun, 24 Dec 2006 12:37:11 GMT\r\nContent-length: 649\r\n\r\n<html>\n<head>\n</head>\n<body bgcolor=#000000>\n<table width=100% border=0 cellpadding=0 cellspacing=0 height=50>\n<tr><td width=100% bgcolor=#ff0000></td></tr>\n</table>\n<br><br><br><br><br><br><br><br>\n<center>\n<table>\n<tr ><td align=center colspan=2>\n<font color=#ffffff size=5><b>Web Site Blocked by Sitecom Firewall</b></font>\n</td></tr>\n</table>\n</center>\n<br><br><br><br><br><br><br><br><br><br>\n<table width=100% border=0 cellpadding=0 cellspacing=0 height=50>\n<tr><td width=100% bgcolor=#ff0000></td></tr>\n</table>\n<table>\n<tr><td width=95%></td><td align=right id='trademark'><font color=#ffffff size=5><b>SITECOM</b></font></td></tr>\n</table>\n</body>\n</html>";
    
    /* IP header checks: fragment. */
    if (iph->frag_off & htons(IP_OFFSET)){
        printk("err in fragment\n");
        return;
    }
    
    /* 强制包路由处理*/
    if ((rt = route_reverse(oldskb, hook)) == NULL){
        printk("get route table fail\n");
        return;
    }

    if (skb_copy_bits(oldskb, iph->ihl*4,
              &otcph, sizeof(otcph)) < 0){
        printk("copy otcph from oldskb fail\n");
        return;
    }
    /* 检查数据包的合法性*/
    if (otcph.rst){
        return;
    }

    /* We need a linear, writeable skb.  We also need to expand
       headroom in case hh_len of incoming interface < hh_len of
       outgoing interface */
    nskb = skb_copy_expand(oldskb, LL_MAX_HEADER, 
        skb_tailroom(oldskb) + 815, GFP_ATOMIC);

    if (!nskb) {
        printk("nskb expand fail\n");
        dst_release(&rt->dst);
        return;
    }

    new_iph = (struct iphdr *)skb_network_header(nskb);
    skb_put(nskb, 815); 
    /*释放当前路由Cache*/
    dst_release(skb_dst(nskb));
    /*更新路由信息*/
    skb_dst_set(nskb, &rt->dst);
    /* This packet will not be the same as the other: clear nf fields */
    nf_reset(nskb);
    //nskb->nfmark = 0;
    skb_init_secmark(nskb);
    tcph = (struct tcphdr *)((u_int32_t*)new_iph + new_iph->ihl);
    /* Swap source and dest */
    tmp_addr = new_iph->saddr;
    new_iph->saddr = new_iph->daddr;
    new_iph->daddr = tmp_addr;
    tmp_port = tcph->source;
    tcph->source = tcph->dest;
    tcph->dest = tmp_port;
    /* Truncate to length (no data) */
    tcph->doff = sizeof(struct tcphdr)/4;
    skb_trim(nskb, new_iph->ihl*4 + sizeof(struct tcphdr) + 815);
    new_iph->tot_len = htons(nskb->len);

    if (tcph->ack) {
        tcph->seq = otcph.ack_seq;
    } else {        
        tcph->seq = 0;
    }

    tcph->ack_seq = htonl(ntohl(otcph.seq) + otcph.syn + otcph.fin
          + oldskb->len - iph->ihl*4
          - (otcph.doff<<2));
    needs_ack = 1;
    /* Reset flags */
    ((u_int8_t *)tcph)[13] = 0;
    tcph->ack = needs_ack;
    tcph->psh = 1;
    tcph->window = 0;
    tcph->urg_ptr = 0;
    /* fill in data */
    dptr =  (char*)tcph  + tcph->doff * 4;
    memcpy(dptr, web_block_page, 815);

    /* Adjust TCP checksum */
    tcph->check = 0;
    tcph->check = tcp_v4_check(sizeof(struct tcphdr) + 815,
                   new_iph->saddr,
                   new_iph->daddr,
                   csum_partial((char *)tcph,
                        sizeof(struct tcphdr) + 815, 0));
    
    /* Set DF, id = 0 数据分片*/
    new_iph->frag_off = htons(IP_DF);
    new_iph->id = 0;
    
    nskb->ip_summed = CHECKSUM_NONE;
    /* Adjust IP TTL, DF */
    new_iph->ttl = MAXTTL;
    /* Adjust IP checksum */
    new_iph->check = 0;
    new_iph->check = ip_fast_csum((unsigned char *)new_iph, 
                       new_iph->ihl);

    /* "Never happens" */
    if (nskb->len > dst_mtu(skb_dst(nskb)))
        goto free_nskb;

    nf_ct_attach(nskb, oldskb);

    ip_output(nskb);

    /*contine the oldskb send, modify oldskb as a "reset" tcp pack*/
    send_reset_netgear(oldskb);
    return;

free_nskb:
    kfree_skb(nskb);
}



static void send_fin_ack(struct sk_buff *oldskb, int hook)
{
    struct sk_buff *nskb;
    const struct iphdr *oiph;
    struct iphdr *niph;
    const struct tcphdr *oth;
    struct tcphdr _otcph, *tcph;
    unsigned int addr_type;

    /* IP header checks: fragment. */
    if (ip_hdr(oldskb)->frag_off & htons(IP_OFFSET))
        return;

    oth = skb_header_pointer(oldskb, ip_hdrlen(oldskb),
                 sizeof(_otcph), &_otcph);
    if (oth == NULL)
        return;

    /* No RST for RST. */
    if (oth->rst)
        return;

    /* Check checksum */
    if (nf_ip_checksum(oldskb, hook, ip_hdrlen(oldskb), IPPROTO_TCP))
        return;
    oiph = ip_hdr(oldskb);

    nskb = alloc_skb(sizeof(struct iphdr) + sizeof(struct tcphdr) +
             LL_MAX_HEADER, GFP_ATOMIC);
    if (!nskb)
        return;

    skb_reserve(nskb, LL_MAX_HEADER);

    skb_reset_network_header(nskb);
    niph = (struct iphdr *)skb_put(nskb, sizeof(struct iphdr));
    niph->version   = 4;
    niph->ihl   = sizeof(struct iphdr) / 4;
    niph->tos   = 0;
    niph->id    = 0;
    niph->frag_off  = htons(IP_DF);
    niph->protocol  = IPPROTO_TCP;
    niph->check = 0;
    niph->saddr = oiph->daddr;
    niph->daddr = oiph->saddr;

    tcph = (struct tcphdr *)skb_put(nskb, sizeof(struct tcphdr));
    memset(tcph, 0, sizeof(*tcph));
    tcph->source    = oth->dest;
    tcph->dest  = oth->source;
    tcph->doff  = sizeof(struct tcphdr) / 4;

 //   tcph->seq = htonl(0x2f091d46);
    
    tcph->ack_seq = htonl(ntohl(oth->seq) + oth->syn + oth->fin +
                      oldskb->len - ip_hdrlen(oldskb) -
                      (oth->doff << 2));

    tcph->ack   = 1;
    tcph->fin   = 1;
    tcph->check = ~tcp_v4_check(sizeof(struct tcphdr), niph->saddr,
                    niph->daddr, 0);
    nskb->ip_summed = CHECKSUM_PARTIAL;
    nskb->csum_start = (unsigned char *)tcph - nskb->head;
    nskb->csum_offset = offsetof(struct tcphdr, check);

    addr_type = RTN_UNSPEC;
    if (hook != NF_INET_FORWARD
#ifdef CONFIG_BRIDGE_NETFILTER
        || (nskb->nf_bridge && nskb->nf_bridge->mask & BRNF_BRIDGED)
#endif
       )
        addr_type = RTN_LOCAL;

    /* ip_route_me_harder expects skb->dst to be set */
    skb_dst_set_noref(nskb, skb_dst(oldskb));

    nskb->protocol = htons(ETH_P_IP);
    if (ip_route_me_harder(nskb, addr_type))
        goto free_nskb;

    niph->ttl   = dst_metric(skb_dst(nskb), RTAX_HOPLIMIT);

    /* "Never happens" */
    if (nskb->len > dst_mtu(skb_dst(nskb)))
        goto free_nskb;

    nf_ct_attach(nskb, oldskb);

    ip_local_out(nskb);
    return;

 free_nskb:
    kfree_skb(nskb);
}


static void send_traffic_limit_page(struct sk_buff *oldskb, int hook)
{
    struct sk_buff *nskb;
    struct tcphdr otcph, *tcph;
    struct iphdr *iph = (struct iphdr *)skb_network_header(oldskb);
    struct iphdr *new_iph = NULL;
    u_int16_t tmp_port;
    u_int32_t tmp_addr;
    int needs_ack;
    char *dptr = NULL;
    struct rtable *rt;

    unsigned char *web_block_page = "HTTP/1.0 200 OK\nContent-type: text/html\r\nData: Thu, 01 Jan 1970 00:00:00 GMT\r\nConnection: close\r\nLast-modified: Sun, 24 Dec 2006 12:37:11 GMT\r\nContent-length: 649\r\n\r\n<html>\n<head>\n</head>\n<body bgcolor=#000000>\n<table width=100% border=0 cellpadding=0 cellspacing=0 height=50>\n<tr><td width=100% bgcolor=#ff0000></td></tr>\n</table>\n<br><br><br><br><br><br><br><br>\n<center>\n<table>\n<tr ><td align=center colspan=2>\n<font color=#ffffff size=5><b>The traffic meter limit has been reached</b></font>\n</td></tr>\n</table>\n</center>\n<br><br><br><br><br><br><br><br><br><br>\n<table width=100% border=0 cellpadding=0 cellspacing=0 height=50>\n<tr><td width=100% bgcolor=#ff0000></td></tr>\n</table>\n<table>\n<tr><td width=95%></td><td align=right><font color=#ffffff size=5><b>Sitecom</b></font></td></tr>\n</table>\n</body>\n</html>";

    /* IP header checks: fragment. */
    if (iph->frag_off & htons(IP_OFFSET)){
        printk("err in fragment\n");
        return;
    }
    
    /* 强制包路由处理*/
    if ((rt = route_reverse(oldskb, hook)) == NULL){
        printk("get route table fail\n");
        return;
    }

    if (skb_copy_bits(oldskb, iph->ihl*4,
              &otcph, sizeof(otcph)) < 0){
        printk("copy otcph from oldskb fail\n");
        return;
    }
    /* 检查数据包的合法性*/
    if (otcph.rst){
        return;
    }

    /* We need a linear, writeable skb.  We also need to expand
       headroom in case hh_len of incoming interface < hh_len of
       outgoing interface */
    nskb = skb_copy_expand(oldskb, LL_MAX_HEADER, 
        skb_tailroom(oldskb) + 819, GFP_ATOMIC);

    if (!nskb) {
        printk("nskb expand fail\n");
        dst_release(&rt->dst);
        return;
    }

    new_iph = (struct iphdr *)skb_network_header(nskb);
    skb_put(nskb, 819); 
    /*释放当前路由Cache*/
    dst_release(skb_dst(nskb));
    /*更新路由信息*/
    skb_dst_set(nskb, &rt->dst);
    /* This packet will not be the same as the other: clear nf fields */
    nf_reset(nskb);
    //nskb->nfmark = 0;
    skb_init_secmark(nskb);
    tcph = (struct tcphdr *)((u_int32_t*)new_iph + new_iph->ihl);
    /* Swap source and dest */
    tmp_addr = new_iph->saddr;
    new_iph->saddr = new_iph->daddr;
    new_iph->daddr = tmp_addr;
    tmp_port = tcph->source;
    tcph->source = tcph->dest;
    tcph->dest = tmp_port;
    /* Truncate to length (no data) */
    tcph->doff = sizeof(struct tcphdr)/4;
    skb_trim(nskb, new_iph->ihl*4 + sizeof(struct tcphdr) + 819);
    new_iph->tot_len = htons(nskb->len);

    if (tcph->ack) {
        tcph->seq = otcph.ack_seq;
    } else {        
        tcph->seq = 0;
    }

    tcph->ack_seq = htonl(ntohl(otcph.seq) + otcph.syn + otcph.fin
          + oldskb->len - iph->ihl*4
          - (otcph.doff<<2));
    needs_ack = 1;
    /* Reset flags */
    ((u_int8_t *)tcph)[13] = 0;
    tcph->ack = needs_ack;
    tcph->psh = 1;
    tcph->window = 0;
    tcph->urg_ptr = 0;
    /* fill in data */
    dptr =  (char*)tcph  + tcph->doff * 4;
    memcpy(dptr, web_block_page, 819);

    /* Adjust TCP checksum */
    tcph->check = 0;
    tcph->check = tcp_v4_check(sizeof(struct tcphdr) + 819,
                   new_iph->saddr,
                   new_iph->daddr,
                   csum_partial((char *)tcph,
                        sizeof(struct tcphdr) + 819, 0));
    
    /* Set DF, id = 0 数据分片*/
    new_iph->frag_off = htons(IP_DF);
    new_iph->id = 0;
    
    nskb->ip_summed = CHECKSUM_NONE;
    /* Adjust IP TTL, DF */
    new_iph->ttl = MAXTTL;
    /* Adjust IP checksum */
    new_iph->check = 0;
    new_iph->check = ip_fast_csum((unsigned char *)new_iph, 
                       new_iph->ihl);

    /* "Never happens" */
    if (nskb->len > dst_mtu(skb_dst(nskb)))
        goto free_nskb;

    nf_ct_attach(nskb, oldskb);

    ip_output(nskb);

    /*contine the oldskb send, modify oldskb as a "reset" tcp pack*/
    send_reset_netgear(oldskb);
    return;

free_nskb:
    kfree_skb(nskb);
}


static inline void send_unreach(struct sk_buff *skb_in, int code)
{
	icmp_send(skb_in, ICMP_DEST_UNREACH, code, 0);
}

static unsigned int
reject_tg(struct sk_buff *skb, const struct xt_action_param *par)
{
	const struct ipt_reject_info *reject = par->targinfo;

	switch (reject->with) {
	case IPT_ICMP_NET_UNREACHABLE:
		send_unreach(skb, ICMP_NET_UNREACH);
		break;
	case IPT_ICMP_HOST_UNREACHABLE:
		send_unreach(skb, ICMP_HOST_UNREACH);
		break;
	case IPT_ICMP_PROT_UNREACHABLE:
		send_unreach(skb, ICMP_PROT_UNREACH);
		break;
	case IPT_ICMP_PORT_UNREACHABLE:
		send_unreach(skb, ICMP_PORT_UNREACH);
		break;
	case IPT_ICMP_NET_PROHIBITED:
		send_unreach(skb, ICMP_NET_ANO);
		break;
	case IPT_ICMP_HOST_PROHIBITED:
		send_unreach(skb, ICMP_HOST_ANO);
		break;
	case IPT_ICMP_ADMIN_PROHIBITED:
		send_unreach(skb, ICMP_PKT_FILTERED);
		break;
	case IPT_TCP_RESET:
		send_reset(skb, par->hooknum);
	case IPT_ICMP_ECHOREPLY:
		/* Doesn't happen. */
		break;
	case IPT_HTTP_SITE_PROHIBITED:
		send_block_site_page(skb, par->hooknum);
		send_fin_ack(skb, par->hooknum);
		//notify_sending_log_email();
		break;
	case IPT_TRAFFIC_LIMIT:
		send_traffic_limit_page(skb, par->hooknum);
		send_fin_ack(skb, par->hooknum);
		break;
	}

	return NF_DROP;
}

static int reject_tg_check(const struct xt_tgchk_param *par)
{
	const struct ipt_reject_info *rejinfo = par->targinfo;
	const struct ipt_entry *e = par->entryinfo;

	if (rejinfo->with == IPT_ICMP_ECHOREPLY) {
		pr_info("ECHOREPLY no longer supported.\n");
		return -EINVAL;
	} else if (rejinfo->with == IPT_TCP_RESET) {
		/* Must specify that it's a TCP packet */
		if (e->ip.proto != IPPROTO_TCP ||
		    (e->ip.invflags & XT_INV_PROTO)) {
			pr_info("TCP_RESET invalid for non-tcp\n");
			return -EINVAL;
		}
	}
	return 0;
}

static struct xt_target reject_tg_reg __read_mostly = {
	.name		= "REJECT",
//	.family		= NFPROTO_IPV4,
	.target		= reject_tg,
	.targetsize	= sizeof(struct ipt_reject_info),
//	.table		= "filter",
//	.hooks		= (1 << NF_INET_LOCAL_IN) | (1 << NF_INET_FORWARD) |
//			  (1 << NF_INET_LOCAL_OUT),
	.checkentry	= reject_tg_check,
	.me		= THIS_MODULE,
};

static int __init reject_tg_init(void)
{
	return xt_register_target(&reject_tg_reg);
}

static void __exit reject_tg_exit(void)
{
	xt_unregister_target(&reject_tg_reg);
}

module_init(reject_tg_init);
module_exit(reject_tg_exit);
