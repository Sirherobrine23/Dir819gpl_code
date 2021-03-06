/* Port-triggering target.
 *
 * Copyright (C) 2003, CyberTAN Corporation
 * All Rights Reserved.
 */

/* Shared library add-on to iptables to add port-trigger support. */

#include <stdio.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include <iptables.h>
#include <linux/netfilter_ipv4/ip_tables.h>
#include <linux/netfilter_ipv4/ip_nat_rule.h>
#include <linux/netfilter_ipv4/ipt_TRIGGER.h>

/* Function which prints out usage message. */
static void
help(void)
{
	printf(
"TRIGGER v%s options:\n"
" --trigger-type (dnat|in|out)\n"
"				Trigger type\n"
" --trigger-mproto proto\n"
"				Trigger protocol\n"
" --trigger-match port[-port]\n"
"				Trigger destination port range\n"
" --trigger-rproto proto\n"
"               Related protocol\n"
" --trigger-relate port[-port]\n"
"				Related destination Port range.\n\n",
IPTABLES_VERSION);
}

static struct option opts[] = {
	{ "trigger-type", 1, 0, '1' },
	{ "trigger-mproto", 1, 0, '2' },
	{ "trigger-rproto", 1, 0, '3' },
	{ "trigger-match", 1, 0, '4' },
	{ "trigger-relate", 1, 0, '5' },
	{ 0 }
};

/* Initialize the target. */
static void
init(struct ipt_entry_target *t, unsigned int *nfcache)
{
	/* Can't cache this */
	*nfcache |= NFC_UNKNOWN;
}

/* Parses ports */
static void
parse_ports(const char *arg, u_int16_t *ports)
{
	const char *dash;
	int port;

	port = atoi(arg);
	if (port == 0 || port > 65535)
		exit_error(PARAMETER_PROBLEM, "Port range `%s' invalid\n", arg);

	dash = strchr(arg, '-');
	if (!dash)
		ports[0] = ports[1] = port;
	else {
		int maxport;

    	maxport = atoi(dash + 1);
		if (maxport == 0 || maxport > 65535)
			exit_error(PARAMETER_PROBLEM,
				   "Port range `%s' invalid\n", dash+1);
		if (maxport < port)
			exit_error(PARAMETER_PROBLEM,
				   "Port range `%s' invalid\n", arg);
		ports[0] = port;
		ports[1] = maxport;
	}
}


/* Function which parses command options; returns true if it
   ate an option */
static int
parse(int c, char **argv, int invert, unsigned int *flags,
      const struct ipt_entry *entry,
      struct ipt_entry_target **target)
{
	struct ipt_trigger_info *info = (struct ipt_trigger_info *)(*target)->data;

	switch (c) {
    /* --trigger-type */
	case '1':
		if (!strcasecmp(optarg, "dnat"))
			info->type = IPT_TRIGGER_DNAT;
		else if (!strcasecmp(optarg, "in"))
			info->type = IPT_TRIGGER_IN;
		else if (!strcasecmp(optarg, "out"))
			info->type = IPT_TRIGGER_OUT;
		else
			exit_error(PARAMETER_PROBLEM,
				   "unknown type `%s' specified", optarg);
		return 1;

    /* --trigger-mproto */
    case '2':
		if (!strcasecmp(optarg, "tcp"))
			info->mproto = IPPROTO_TCP;
		else if (!strcasecmp(optarg, "udp"))
			info->mproto = IPPROTO_UDP;
		else if (!strcasecmp(optarg, "all"))
			info->mproto = 0;
		else
			exit_error(PARAMETER_PROBLEM,
				   "unknown protocol `%s' specified", optarg);
		return 1;

    /* --trigger-rproto */
	case '3':
		if (!strcasecmp(optarg, "tcp"))
			info->rproto = IPPROTO_TCP;
		else if (!strcasecmp(optarg, "udp"))
			info->rproto = IPPROTO_UDP;
		else if (!strcasecmp(optarg, "all"))
			info->rproto = 0;
		else
			exit_error(PARAMETER_PROBLEM,
				   "unknown protocol `%s' specified", optarg);
		return 1;

    /* --trigger-match */
	case '4':
		if (check_inverse(optarg, &invert, &optind, 0))
			exit_error(PARAMETER_PROBLEM,
				   "Unexpected `!' after --trigger-match");

		parse_ports(optarg, info->ports.mport);
		return 1;

    /* --trigger-relate */
	case '5':
		if (check_inverse(optarg, &invert, &optind, 0))
			exit_error(PARAMETER_PROBLEM,
				   "Unexpected `!' after --trigger-relate");

		parse_ports(optarg, info->ports.rport);
		*flags |= IP_NAT_RANGE_PROTO_SPECIFIED;
		return 1;

	default:
		return 0;
	}
}

/* Final check; don't care. */
static void final_check(unsigned int flags)
{

}

/* Prints out the targinfo. */
static void
print(const struct ipt_ip *ip,
      const struct ipt_entry_target *target,
      int numeric)
{
	struct ipt_trigger_info *info = (struct ipt_trigger_info *)target->data;

	printf("TRIGGER ");
	if (info->type == IPT_TRIGGER_DNAT)
		printf("type:dnat ");
	else if (info->type == IPT_TRIGGER_IN)
		printf("type:in ");
	else if (info->type == IPT_TRIGGER_OUT)
		printf("type:out ");

    if (info->type == IPT_TRIGGER_OUT)
    {
        if (info->mproto == IPPROTO_TCP)
    		printf("mproto:tcp ");
    	else if (info->mproto == IPPROTO_UDP)
    		printf("mproto:udp ");
        else
            printf("mproto:all ");

    	printf("match:%hu", info->ports.mport[0]);
    	if (info->ports.mport[1] > info->ports.mport[0])
    		printf("-%hu", info->ports.mport[1]);
    	printf(" ");
    }

    if (info->ports.rport[0] > 0)
    {
        if (info->rproto == IPPROTO_TCP)
    		printf("rproto:tcp ");
    	else if (info->rproto == IPPROTO_UDP)
    		printf("rproto:udp ");
        else
            printf("rproto:all ");

    	printf("relate:%hu", info->ports.rport[0]);
    	if (info->ports.rport[1] > info->ports.rport[0])
    		printf("-%hu", info->ports.rport[1]);
    	printf(" ");
    }
}

/* Saves the union ipt_targinfo in parsable form to stdout. */
static void
save(const struct ipt_ip *ip, const struct ipt_entry_target *target)
{
	struct ipt_trigger_info *info = (struct ipt_trigger_info *)target->data;

    printf("--trigger-type ");
    if (info->type == IPT_TRIGGER_DNAT)
		printf("dnat ");
	else if (info->type == IPT_TRIGGER_IN)
		printf("in ");
	else if (info->type == IPT_TRIGGER_OUT)
		printf("out ");

    if (info->type == IPT_TRIGGER_OUT)
    {
        printf("--trigger-mproto ");
    	if (info->mproto == IPPROTO_TCP)
    		printf("tcp ");
    	else if (info->mproto == IPPROTO_UDP)
    		printf("udp ");
        else
            printf("all ");
        printf("--trigger-match %hu-%hu ", info->ports.mport[0], info->ports.mport[1]);
    }

    if (info->ports.rport[0] > 0)
    {
        printf("--trigger-rproto ");
    	if (info->rproto == IPPROTO_TCP)
    		printf("tcp ");
    	else if (info->rproto == IPPROTO_UDP)
    		printf("udp ");
        else
            printf("all ");
    	printf("--trigger-relate %hu-%hu ", info->ports.rport[0], info->ports.rport[1]);
    }
}

static struct iptables_target trigger =
{
    .next       = NULL,
    .revision   = 0,
	.name		= "TRIGGER",
	.version	= IPTABLES_VERSION,
	.size		= IPT_ALIGN(sizeof(struct ipt_trigger_info)),
	.userspacesize	= IPT_ALIGN(sizeof(struct ipt_trigger_info)),
	.help		= &help,
	.init		= &init,
	.parse		= &parse,
	.final_check	= &final_check,
	.print		= &print,
	.save		= &save,
	.extra_opts	= opts
};


void _init(void)
{
	register_target(&trigger);
}

