/*
 * Shared library add-on to iptables to add TPROXY target support.
 *
 * Copyright (C) 2002-2008 BalaBit IT Ltd.
 */
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#include <xtables.h>
#include <linux/netfilter/x_tables.h>
#include <linux/netfilter/xt_TPROXY.h>

static const struct option tproxy_tg_opts[] = {
	{ .name = "on-port", .has_arg = 1, .val = '1'},
	{ .name = "on-ip", .has_arg = 1, .val = '2'},
	{ .name = "tproxy-mark", .has_arg = 1, .val = '3'},
	{NULL},
};

enum {
	PARAM_ONPORT = 1 << 0,
	PARAM_ONIP = 1 << 1,
	PARAM_MARK = 1 << 2,
};

static void tproxy_tg_help(void)
{
	printf(
"TPROXY target options:\n"
"  --on-port port		    Redirect connection to port, or the original port if 0\n"
"  --on-ip ip			    Optionally redirect to the given IP\n"
"  --tproxy-mark value[/mask]	    Mark packets with the given value/mask\n\n");
}

static void parse_tproxy_lport(const char *s, struct xt_tproxy_target_info *info)
{
	unsigned int lport;

	if (xtables_strtoui(s, NULL, &lport, 0, UINT16_MAX))
		info->lport = htons(lport);
	else
		xtables_param_act(XTF_BAD_VALUE, "TPROXY", "--on-port", s);
}

static void parse_tproxy_laddr(const char *s, struct xt_tproxy_target_info *info)
{
	struct in_addr *laddr;

	if ((laddr = xtables_numeric_to_ipaddr(s)) == NULL)
		xtables_param_act(XTF_BAD_VALUE, "TPROXY", "--on-ip", s);

	info->laddr = laddr->s_addr;
}

static void parse_tproxy_mark(char *s, struct xt_tproxy_target_info *info)
{
	unsigned int value, mask = UINT32_MAX;
	char *end;

	if (!xtables_strtoui(s, &end, &value, 0, UINT32_MAX))
		xtables_param_act(XTF_BAD_VALUE, "TPROXY", "--tproxy-mark", s);
	if (*end == '/')
		if (!xtables_strtoui(end + 1, &end, &mask, 0, UINT32_MAX))
			xtables_param_act(XTF_BAD_VALUE, "TPROXY", "--tproxy-mark", s);
	if (*end != '\0')
		xtables_param_act(XTF_BAD_VALUE, "TPROXY", "--tproxy-mark", s);

	info->mark_mask = mask;
	info->mark_value = value;
}

static int tproxy_tg_parse(int c, char **argv, int invert, unsigned int *flags,
			const void *entry, struct xt_entry_target **target)
{
	struct xt_tproxy_target_info *tproxyinfo = (void *)(*target)->data;

	switch (c) {
	case '1':
		xtables_param_act(XTF_ONLY_ONCE, "TPROXY", "--on-port", *flags & PARAM_ONPORT);
		xtables_param_act(XTF_NO_INVERT, "TPROXY", "--on-port", invert);
		parse_tproxy_lport(optarg, tproxyinfo);
		*flags |= PARAM_ONPORT;
	case '2':
		xtables_param_act(XTF_ONLY_ONCE, "TPROXY", "--on-ip", *flags & PARAM_ONIP);
		xtables_param_act(XTF_NO_INVERT, "TPROXY", "--on-ip", invert);
		parse_tproxy_laddr(optarg, tproxyinfo);
		*flags |= PARAM_ONIP;
	case '3':
		xtables_param_act(XTF_ONLY_ONCE, "TPROXY", "--tproxy-mark", *flags & PARAM_MARK);
		xtables_param_act(XTF_NO_INVERT, "TPROXY", "--tproxy-mark", invert);
		parse_tproxy_mark(optarg, tproxyinfo);
		*flags |= PARAM_MARK;
	default:
		return 0;
	}

	return 1;
}

static void tproxy_tg_check(unsigned int flags)
{
	if (!(flags & PARAM_ONPORT))
		xtables_error(PARAMETER_PROBLEM,
			   "TPROXY target: Parameter --on-port is required");
}

static void tproxy_tg_print(const void *ip, const struct xt_entry_target *target,
			 int numeric)
{
	const struct xt_tproxy_target_info *info = (const void *)target->data;
	printf("TPROXY redirect %s:%u mark 0x%x/0x%x",
	       xtables_ipaddr_to_numeric((const struct in_addr *)&info->laddr),
	       ntohs(info->lport), (unsigned int)info->mark_value,
	       (unsigned int)info->mark_mask);
}

static void tproxy_tg_save(const void *ip, const struct xt_entry_target *target)
{
	const struct xt_tproxy_target_info *info = (const void *)target->data;

	printf("--on-port %u ", ntohs(info->lport));
	printf("--on-ip %s ",
	       xtables_ipaddr_to_numeric((const struct in_addr *)&info->laddr));
	printf("--tproxy-mark 0x%x/0x%x ",
	       (unsigned int)info->mark_value, (unsigned int)info->mark_mask);
}

static void
tproxy_tg_print6(const void *ip, const struct xt_entry_target *target,
                 int numeric)
{
        const struct xt_tproxy_target_info_v1 *info =
                (const void *)target->data;

        printf(" TPROXY redirect %s:%u mark 0x%x/0x%x",
               xtables_ip6addr_to_numeric(&info->laddr.in6),
               ntohs(info->lport), (unsigned int)info->mark_value,
               (unsigned int)info->mark_mask);
}

static void
tproxy_tg_save6(const void *ip, const struct xt_entry_target *target)
{
        const struct xt_tproxy_target_info_v1 *info;

        info = (const void *)target->data;
        printf(" --on-port %u", ntohs(info->lport));
        printf(" --on-ip %s", xtables_ip6addr_to_numeric(&info->laddr.in6));
        printf(" --tproxy-mark 0x%x/0x%x",
               (unsigned int)info->mark_value, (unsigned int)info->mark_mask);
}

static void parse_tproxy_lport6(const char *s, struct xt_tproxy_target_info_v1 *info)
{
	unsigned int lport;

	if (xtables_strtoui(s, NULL, &lport, 0, UINT16_MAX))
		info->lport = htons(lport);
	else
		xtables_param_act(XTF_BAD_VALUE, "TPROXY", "--on-port", s);
}

static void parse_tproxy_laddr6(const char *s, struct xt_tproxy_target_info_v1 *info)
{
	//struct in6_addr in6addr;
	struct in6_addr *laddr;
	//int ret = 0;
#if 0
	ret = inet_pton(AF_INET6, s, (void *)&in6addr);
	if (0 == ret)
	{
		printf("inet_pton error...\n");
	}
#endif

	//if ((laddr = xtables_numeric_to_ipaddr(s)) == NULL)
	if ((laddr = xtables_numeric_to_ip6addr(s)) == NULL)
		xtables_param_act(XTF_BAD_VALUE, "TPROXY", "--on-ip", s);

	//info->laddr = laddr->s_addr;
	//info->laddr.in6 = in6addr;
	memcpy(&info->laddr.in6, laddr, XT_ALIGN(sizeof(struct in6_addr)));
	//memcpy(info->laddr.ip, laddr->in6_u.u6_addr8, XT_ALIGN(sizeof(char)*16));
	printf("laddr:%s\n", xtables_ip6addr_to_numeric(&info->laddr.in6));
}

static void parse_tproxy_mark6(char *s, struct xt_tproxy_target_info_v1 *info)
{
	unsigned int value, mask = UINT32_MAX;
	char *end;

	if (!xtables_strtoui(s, &end, &value, 0, UINT32_MAX))
		xtables_param_act(XTF_BAD_VALUE, "TPROXY", "--tproxy-mark", s);
	if (*end == '/')
		if (!xtables_strtoui(end + 1, &end, &mask, 0, UINT32_MAX))
			xtables_param_act(XTF_BAD_VALUE, "TPROXY", "--tproxy-mark", s);
	if (*end != '\0')
		xtables_param_act(XTF_BAD_VALUE, "TPROXY", "--tproxy-mark", s);

	info->mark_mask = mask;
	info->mark_value = value;
}

static int tproxy_tg_parse6(int c, char **argv, int invert, unsigned int *flags,
			const void *entry, struct xt_entry_target **target)
{
	struct xt_tproxy_target_info_v1 *tproxyinfo = (void *)(*target)->data;

	switch (c) {
	case '1':
		xtables_param_act(XTF_ONLY_ONCE, "TPROXY", "--on-port", *flags & PARAM_ONPORT);
		xtables_param_act(XTF_NO_INVERT, "TPROXY", "--on-port", invert);
		parse_tproxy_lport6(optarg, tproxyinfo);
		*flags |= PARAM_ONPORT;
		break;
	case '2':
		xtables_param_act(XTF_ONLY_ONCE, "TPROXY", "--on-ip", *flags & PARAM_ONIP);
		xtables_param_act(XTF_NO_INVERT, "TPROXY", "--on-ip", invert);
		parse_tproxy_laddr6(optarg, tproxyinfo);
		*flags |= PARAM_ONIP;
		break;
	case '3':
		xtables_param_act(XTF_ONLY_ONCE, "TPROXY", "--tproxy-mark", *flags & PARAM_MARK);
		xtables_param_act(XTF_NO_INVERT, "TPROXY", "--tproxy-mark", invert);
		parse_tproxy_mark6(optarg, tproxyinfo);
		*flags |= PARAM_MARK;
		break;
	default:
		return 0;
	}

	return 1;
}
static struct xtables_target tproxy_tg_reg[] = {
	{
		.name	       = "TPROXY",
		.family	       = NFPROTO_IPV4,
		.version       = XTABLES_VERSION,
		.size	       = XT_ALIGN(sizeof(struct xt_tproxy_target_info)),
		.userspacesize = XT_ALIGN(sizeof(struct xt_tproxy_target_info)),
		.help	       = tproxy_tg_help,
		.parse	       = tproxy_tg_parse,
		.final_check   = tproxy_tg_check,
		.print	       = tproxy_tg_print,
		.save	       = tproxy_tg_save,
		.extra_opts    = tproxy_tg_opts,
	},
	{
                .name          = "TPROXY",
                .revision      = 1,
                .family        = NFPROTO_IPV6,
                .version       = XTABLES_VERSION,
                .size          = XT_ALIGN(sizeof(struct xt_tproxy_target_info_v1)),
                .userspacesize = XT_ALIGN(sizeof(struct xt_tproxy_target_info_v1)),
                .help          = tproxy_tg_help,
                .parse         = tproxy_tg_parse6,
                .print         = tproxy_tg_print6,
                .save          = tproxy_tg_save6,
                .extra_opts    = tproxy_tg_opts,
        },
};

void _init(void)
{
	//xtables_register_target(&tproxy_tg_reg);
	xtables_register_targets(&tproxy_tg_reg, ARRAY_SIZE(tproxy_tg_reg));
}
