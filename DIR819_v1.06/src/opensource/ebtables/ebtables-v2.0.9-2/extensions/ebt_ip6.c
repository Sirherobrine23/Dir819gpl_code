/* ebt_ip6
 * 
 * Authors:
 * Kuo-Lang Tseng <kuo-lang.tseng@intel.com>
 * Manohar Castelino <manohar.castelino@intel.com>
 *
 * Summary:
 * This is just a modification of the IPv4 code written by 
 * Bart De Schuymer <bdschuym@pandora.be>
 * with the changes required to support IPv6
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <netdb.h>
#include "../include/ebtables_u.h"
/*
 modify for ebtables independent compiler, after kernel code merge should be recover

#include <linux/netfilter_bridge/ebt_ip6.h>
*/
#include "../include/linux/netfilter_bridge/ebt_ip6.h"

#define IP_SOURCE '1'
#define IP_DEST   '2'
#define IP_TCLASS '3'
#define IP_PROTO  '4'
#define IP_SPORT  '5'
#define IP_DPORT  '6'

static struct option opts[] =
{
	{ "ip6-source"           , required_argument, 0, IP_SOURCE },
	{ "ip6-src"              , required_argument, 0, IP_SOURCE },
	{ "ip6-destination"      , required_argument, 0, IP_DEST   },
	{ "ip6-dst"              , required_argument, 0, IP_DEST   },
	{ "ip6-traffic-class"    , required_argument, 0, IP_TCLASS },
	{ "ip6-tclass"           , required_argument, 0, IP_TCLASS },
	{ "ip6-protocol"         , required_argument, 0, IP_PROTO  },
	{ "ip6-proto"            , required_argument, 0, IP_PROTO  },
	{ "ip6-source-port"      , required_argument, 0, IP_SPORT  },
	{ "ip6-sport"            , required_argument, 0, IP_SPORT  },
	{ "ip6-destination-port" , required_argument, 0, IP_DPORT  },
	{ "ip6-dport"            , required_argument, 0, IP_DPORT  },
	{ 0 }
};

/* transform a protocol and service name into a port number */
static uint16_t parse_port(const char *protocol, const char *name)
{
	struct servent *service;
	char *end;
	int port;

	port = strtol(name, &end, 10);
	if (*end != '\0') {
		if (protocol && 
		    (service = getservbyname(name, protocol)) != NULL)
			return ntohs(service->s_port);
	}
	else if (port >= 0 || port <= 0xFFFF) {
		return port;
	}
	ebt_print_error("Problem with specified %s port '%s'", 
			protocol?protocol:"", name);
	return 0;
}

static void
parse_port_range(const char *protocol, const char *portstring, uint16_t *ports)
{
	char *buffer;
	char *cp;
	
	buffer = strdup(portstring);
	if ((cp = strchr(buffer, ':')) == NULL)
		ports[0] = ports[1] = parse_port(protocol, buffer);
	else {
		*cp = '\0';
		cp++;
		ports[0] = buffer[0] ? parse_port(protocol, buffer) : 0;
		if (ebt_errormsg[0] != '\0')
			return;
		ports[1] = cp[0] ? parse_port(protocol, cp) : 0xFFFF;
		if (ebt_errormsg[0] != '\0')
			return;
		
		if (ports[0] > ports[1])
			ebt_print_error("Invalid portrange (min > max)");
	}
	free(buffer);
}

static void print_port_range(uint16_t *ports)
{
	if (ports[0] == ports[1])
		printf("%d ", ports[0]);
	else
		printf("%d:%d ", ports[0], ports[1]);
}

/*********************************************************
   merge form MediaTek 2.6.22 SDK, expand nefilter_bridge
 support ip range, port range and tos, dhcp rage
  by laiyuhang 2012-5-17
**********************************************************/
#if 1
/* support tclass range */
static uint8_t parse_tc(const char *protocol, const char *name)
{
	char *end;
	int tc;

	tc = strtol(name, &end, 10);
	if (tc >= 0 && tc <= 0xFF) {
		return (uint8_t)tc;
	}
	ebt_print_error2("Problem with specified IPv6 traffic class");
	return 0;
}

static void
parse_tc_range(const char *protocol, const char *tcstring, uint8_t *tcs)
{
	char *buffer;
	char *cp;
	
	buffer = strdup(tcstring);
	if ((cp = strchr(buffer, ':')) == NULL)
		tcs[0] = tcs[1] = parse_tc(protocol, buffer);
	else {
		*cp = '\0';
		cp++;
		tcs[0] = buffer[0] ? parse_tc(protocol, buffer) : 0;
		if (ebt_errormsg[0] != '\0')
			return;
		tcs[1] = cp[0] ? parse_tc(protocol, cp) : 0xFFFF;
		if (ebt_errormsg[0] != '\0')
			return;
		
		if (tcs[0] > tcs[1])
			ebt_print_error("Invalid tcrange (min > max)");
	}
	free(buffer);
}

static void print_tc_range(uint8_t *tcs)
{
	if (tcs[0] == tcs[1])
		printf("%d ", tcs[0]);
	else
		printf("%d:%d ", tcs[0], tcs[1]);
}
#endif
/* end merge */

static void print_help()
{
	printf(
"ip6 options:\n"
"--ip6-src    [!] address[/mask]: ipv6 source specification\n"
"--ip6-dst    [!] address[/mask]: ipv6 destination specification\n"
/*********************************************************
   merge form MediaTek 2.6.22 SDK, expand nefilter_bridge
 support ip range, port range and tos, dhcp rage
  by laiyuhang 2012-5-17
**********************************************************/
#if 1
"--ip6-tclass [!] tclass[:tclass]:ipv6 traffic class specification\n"
"--ip6-proto  [!] protocol[:protocol]    : ipv6 protocol specification\n"
#else
"--ip6-tclass [!] tclass        : ipv6 traffic class specification\n"
"--ip6-proto  [!] protocol      : ipv6 protocol specification\n"
#endif
/* end merge */
"--ip6-sport  [!] port[:port]   : tcp/udp source port or port range\n"
"--ip6-dport  [!] port[:port]   : tcp/udp destination port or port range\n");
}

static void init(struct ebt_entry_match *match)
{
	struct ebt_ip6_info *ipinfo = (struct ebt_ip6_info *)match->data;

	ipinfo->invflags = 0;
	ipinfo->bitmask = 0;
}

#define OPT_SOURCE 0x01
#define OPT_DEST   0x02
#define OPT_TCLASS 0x04
#define OPT_PROTO  0x08
#define OPT_SPORT  0x10
#define OPT_DPORT  0x20
static int parse(int c, char **argv, int argc, const struct ebt_u_entry *entry,
   unsigned int *flags, struct ebt_entry_match **match)
{
	struct ebt_ip6_info *ipinfo = (struct ebt_ip6_info *)(*match)->data;
#if 0 /* merge by laiyuhang 2012-05-17 */
	char *end;
	long int i;
#else
	char *end, *end2, *cp;
	long int i, i2;
#endif

	switch (c) {
	case IP_SOURCE:
		ebt_check_option2(flags, OPT_SOURCE);
		ipinfo->bitmask |= EBT_IP6_SOURCE;
		if (ebt_check_inverse2(optarg)) {
		    ipinfo->invflags |= EBT_IP6_SOURCE;
		}
		ebt_parse_ip6_address(optarg, &ipinfo->saddr, &ipinfo->smsk);
		break;

	case IP_DEST:
		ebt_check_option2(flags, OPT_DEST);
		ipinfo->bitmask |= EBT_IP6_DEST;
		if (ebt_check_inverse2(optarg)) {
			ipinfo->invflags |= EBT_IP6_DEST;
		}
		ebt_parse_ip6_address(optarg, &ipinfo->daddr, &ipinfo->dmsk);
		break;

	case IP_SPORT:
	case IP_DPORT:
		if (c == IP_SPORT) {
			ebt_check_option2(flags, OPT_SPORT);
			ipinfo->bitmask |= EBT_IP6_SPORT;
			if (ebt_check_inverse2(optarg))
				ipinfo->invflags |= EBT_IP6_SPORT;
		} else {
			ebt_check_option2(flags, OPT_DPORT);
			ipinfo->bitmask |= EBT_IP6_DPORT;
			if (ebt_check_inverse2(optarg))
				ipinfo->invflags |= EBT_IP6_DPORT;
		}
		if (c == IP_SPORT)
			parse_port_range(NULL, optarg, ipinfo->sport);
		else
			parse_port_range(NULL, optarg, ipinfo->dport);
		break;

	case IP_TCLASS:
#if 0 /* merge by laiyuhang 2012-05-12 */
		ebt_check_option2(flags, OPT_TCLASS);
		if (ebt_check_inverse2(optarg))
			ipinfo->invflags |= EBT_IP6_TCLASS;
		i = strtol(optarg, &end, 16);
		if (i < 0 || i > 255 || *end != '\0')
			ebt_print_error2("Problem with specified IPv6 traffic class");
		ipinfo->tclass = i;
		ipinfo->bitmask |= EBT_IP6_TCLASS;
		break;
#else
		ebt_check_option2(flags, OPT_TCLASS);
		ipinfo->bitmask |= EBT_IP6_TCLASS;
		if (ebt_check_inverse2(optarg))
			ipinfo->invflags |= EBT_IP6_TCLASS;
		parse_tc_range(NULL, optarg, ipinfo->tclass);
		break;
#endif

	case IP_PROTO:
#if 0 /* merge by laiyuhang 2012-05-12 */
		ebt_check_option2(flags, OPT_PROTO);
		if (ebt_check_inverse2(optarg))
			ipinfo->invflags |= EBT_IP6_PROTO;
		i = strtoul(optarg, &end, 10);
		if (*end != '\0') {
			struct protoent *pe;

			pe = getprotobyname(optarg);
			if (pe == NULL)
				ebt_print_error("Unknown specified IP protocol - %s", argv[optind - 1]);
			ipinfo->protocol = pe->p_proto;
		} else {
			ipinfo->protocol = (unsigned char) i;
		}
#else
		if((cp = strchr(optarg, ':')) == NULL){
			i = strtoul(optarg, &end, 10);
			if (*end != '\0') {
				struct protoent *pe;

				pe = getprotobyname(optarg);
				if (pe == NULL)
					ebt_print_error("Unknown specified IP protocol - %s", argv[optind - 1]);
				ipinfo->protocol[0] = pe->p_proto;
			} else {
				ipinfo->protocol[0] = (unsigned char) i;
			}
			ipinfo->protocol[1] = ipinfo->protocol[0];
		}
		else{
			*cp = '\0';
			cp++;
			i = strtoul(optarg, &end, 10);
			i2 = strtoul(cp, &end2, 10);
			if((*end != '\0') || (*end2 != '\0')) {
				struct protoent *pe;
				struct protoent *pe2;

				pe = getprotobyname(optarg);
				pe2 = getprotobyname(cp);
				if ((pe == NULL) || (pe2 == NULL))
					ebt_print_error("Unknown specified IP protocol - %s", argv[optind - 1]);
				ipinfo->protocol[0] = pe->p_proto;
				ipinfo->protocol[1] = pe2->p_proto;
			}
			else{
				ipinfo->protocol[0] = (unsigned char) i;
				ipinfo->protocol[1] = (unsigned char) i2;
			}
		}
#endif
		ipinfo->bitmask |= EBT_IP6_PROTO;
		break;
	default:
		return 0;
	}
	return 1;
}

static void final_check(const struct ebt_u_entry *entry,
   const struct ebt_entry_match *match, const char *name,
   unsigned int hookmask, unsigned int time)
{
	struct ebt_ip6_info *ipinfo = (struct ebt_ip6_info *)match->data;

	if (entry->ethproto != ETH_P_IPV6 || entry->invflags & EBT_IPROTO) {
		ebt_print_error("For IPv6 filtering the protocol must be "
		            "specified as IPv6");
	} else if (ipinfo->bitmask & (EBT_IP6_SPORT|EBT_IP6_DPORT) &&
		(!(ipinfo->bitmask & EBT_IP6_PROTO) ||
		ipinfo->invflags & EBT_IP6_PROTO ||
#if 0 /* merge by laiyuhang 2012-05-12 */
		(ipinfo->protocol!=IPPROTO_TCP &&
		 ipinfo->protocol!=IPPROTO_UDP &&
		 ipinfo->protocol!=IPPROTO_SCTP &&
		 ipinfo->protocol!=IPPROTO_DCCP)))
#else
		(ipinfo->protocol[0]!=IPPROTO_TCP && ipinfo->protocol[1]!=IPPROTO_TCP &&
		 ipinfo->protocol[0]!=IPPROTO_UDP && ipinfo->protocol[1]!=IPPROTO_UDP &&
		 ipinfo->protocol[0]!=IPPROTO_SCTP && ipinfo->protocol[1]!=IPPROTO_SCTP &&
		 ipinfo->protocol[0]!=IPPROTO_DCCP && ipinfo->protocol[1]!=IPPROTO_DCCP)))
#endif
		ebt_print_error("For port filtering the IP protocol must be "
				"either 6 (tcp), 17 (udp), 33 (dccp) or "
				"132 (sctp)");
}

static void print(const struct ebt_u_entry *entry,
   const struct ebt_entry_match *match)
{
	struct ebt_ip6_info *ipinfo = (struct ebt_ip6_info *)match->data;

	if (ipinfo->bitmask & EBT_IP6_SOURCE) {
		printf("--ip6-src ");
		if (ipinfo->invflags & EBT_IP6_SOURCE)
			printf("! ");
		printf("%s", ebt_ip6_to_numeric(&ipinfo->saddr));
		printf("/%s ", ebt_ip6_to_numeric(&ipinfo->smsk));
	}
	if (ipinfo->bitmask & EBT_IP6_DEST) {
		printf("--ip6-dst ");
		if (ipinfo->invflags & EBT_IP6_DEST)
			printf("! ");
		printf("%s", ebt_ip6_to_numeric(&ipinfo->daddr));
		printf("/%s ", ebt_ip6_to_numeric(&ipinfo->dmsk));
	}
	if (ipinfo->bitmask & EBT_IP6_TCLASS) {
#if 0 /* merge by laiyuhang 2012-05-12 */
		printf("--ip6-tclass ");
		if (ipinfo->invflags & EBT_IP6_TCLASS)
			printf("! ");
		printf("0x%02X ", ipinfo->tclass);
#else
		printf("--ip6-tclass ");
		if (ipinfo->invflags & EBT_IP6_TCLASS)
			printf("! ");
		print_tc_range(ipinfo->tclass);
#endif
	}
	if (ipinfo->bitmask & EBT_IP6_PROTO) {
		struct protoent *pe;
#if 1 /* merge by laiyuhang 2012-05-12 */
		struct protoent *pe2;
#endif

		printf("--ip6-proto ");
		if (ipinfo->invflags & EBT_IP6_PROTO)
			printf("! ");
#if 0 /* merge by laiyuhang 2012-05-12 */
		pe = getprotobynumber(ipinfo->protocol);
		if (pe == NULL) {
			printf("%d ", ipinfo->protocol);
		} else {
			printf("%s ", pe->p_name);
		}
#else
		if(ipinfo->protocol[0] == ipinfo->protocol[1]){
			pe = getprotobynumber(ipinfo->protocol[0]);
			if(pe == NULL)
				printf("%d ", ipinfo->protocol[0]);
			else
				printf("%s ", pe->p_name);
		}
		else{
			pe = getprotobynumber(ipinfo->protocol[0]);
			pe2 = getprotobynumber(ipinfo->protocol[1]);
			if((pe == NULL) || (pe2 == NULL))
				printf("%d:%d ", ipinfo->protocol[0], ipinfo->protocol[1]);
			else
				printf("%s:%s ", pe->p_name, pe2->p_name);
		}
#endif
	}
	if (ipinfo->bitmask & EBT_IP6_SPORT) {
		printf("--ip6-sport ");
		if (ipinfo->invflags & EBT_IP6_SPORT)
			printf("! ");
		print_port_range(ipinfo->sport);
	}
	if (ipinfo->bitmask & EBT_IP6_DPORT) {
		printf("--ip6-dport ");
		if (ipinfo->invflags & EBT_IP6_DPORT)
			printf("! ");
		print_port_range(ipinfo->dport);
	}
}

static int compare(const struct ebt_entry_match *m1,
   const struct ebt_entry_match *m2)
{
	struct ebt_ip6_info *ipinfo1 = (struct ebt_ip6_info *)m1->data;
	struct ebt_ip6_info *ipinfo2 = (struct ebt_ip6_info *)m2->data;

	if (ipinfo1->bitmask != ipinfo2->bitmask)
		return 0;
	if (ipinfo1->invflags != ipinfo2->invflags)
		return 0;
	if (ipinfo1->bitmask & EBT_IP6_SOURCE) {
		if (!IN6_ARE_ADDR_EQUAL(&ipinfo1->saddr, &ipinfo2->saddr))
			return 0;
		if (!IN6_ARE_ADDR_EQUAL(&ipinfo1->smsk, &ipinfo2->smsk))
			return 0;
	}
	if (ipinfo1->bitmask & EBT_IP6_DEST) {
		if (!IN6_ARE_ADDR_EQUAL(&ipinfo1->daddr, &ipinfo2->daddr))
			return 0;
		if (!IN6_ARE_ADDR_EQUAL(&ipinfo1->dmsk, &ipinfo2->dmsk))
			return 0;
	}
	if (ipinfo1->bitmask & EBT_IP6_TCLASS) {
#if 0 /* merge by laiyuhang 2012-05-12 */
		if (ipinfo1->tclass != ipinfo2->tclass)
			return 0;
#else
		if (ipinfo1->tclass[0] != ipinfo2->tclass[0] ||
		   ipinfo1->tclass[1] != ipinfo2->tclass[1])
			return 0;
#endif
	}
#if 0 /* merge by laiyuhang 2012-05-12 */
	if (ipinfo1->bitmask & EBT_IP6_PROTO) {
		if (ipinfo1->protocol != ipinfo2->protocol)
			return 0;
	}
#else
	if (ipinfo1->bitmask & EBT_IP6_PROTO) {
		if (ipinfo1->protocol[0] != ipinfo2->protocol[0] ||
			ipinfo1->protocol[1] != ipinfo2->protocol[1])
			return 0;
	}
#endif
	if (ipinfo1->bitmask & EBT_IP6_SPORT) {
		if (ipinfo1->sport[0] != ipinfo2->sport[0] ||
		   ipinfo1->sport[1] != ipinfo2->sport[1])
			return 0;
	}
	if (ipinfo1->bitmask & EBT_IP6_DPORT) {
		if (ipinfo1->dport[0] != ipinfo2->dport[0] ||
		   ipinfo1->dport[1] != ipinfo2->dport[1])
			return 0;
	}
	return 1;
}

static struct ebt_u_match ip6_match =
{
	.name		= EBT_IP6_MATCH,
	.size		= sizeof(struct ebt_ip6_info),
	.help		= print_help,
	.init		= init,
	.parse		= parse,
	.final_check	= final_check,
	.print		= print,
	.compare	= compare,
	.extra_ops	= opts,
};

void _init(void)
{
	ebt_register_match(&ip6_match);
}
