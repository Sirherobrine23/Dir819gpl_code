/* 
 * Description: EBTables time extension module for userspace.
 *  Authors:  Song Wang <songw@broadcom.com>, ported from FTOS patch netfilter/iptables
 *           The following is the original disclaimer.
 *
 * Shared library add-on to iptables for FTOS
 *
 * (C) 2000 by Matthew G. Marsh <mgm@paktronix.com>
 *
 * This program is distributed under the terms of GNU GPL v2, 1991
 *
 * libipt_FTOS.c borrowed heavily from libipt_TOS.c  11/09/2000
 *
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>

#include "../include/ebtables_u.h"
/*
 modify for ebtables independent compiler, after kernel code merge should be recover

#include <linux/netfilter_bridge/ebt_ftos_t.h>
*/
#include "../include/linux/netfilter_bridge/ebt_ftos_t.h"
/* end modify */
/*********************************************************
   merge form MediaTek 2.6.22 SDK, expand nefilter_bridge
 support pppoe package tos settings
  by laiyuhang 2012-5-17
**********************************************************/

static struct option opts[] =
{
	{ "set-ftos" , required_argument, 0, '1' },
	{ 0 }
};

static void print_help()
{
	printf(
	"ftos target options:\n"
	" --set-ftos value[/mask]     : Set tos value\n");
}

static void init(struct ebt_entry_target *target)
{
	struct ebt_ftos_info *ftosinfo =
	   (struct ebt_ftos_info *)target->data;

	ftosinfo->target = EBT_CONTINUE;
	ftosinfo->mask = 0xff;
}

static void
parse_ftos(const unsigned char *s, struct ebt_ftos_info *ftosinfo){
	char *buffer;
	char *end, *cp;

	buffer = strdup(s);
	if ((cp = strchr(buffer, '/')) == NULL){
		ftosinfo->ftos = strtol(buffer, &end, 0);
		ftosinfo->mask = 0xff;
	}
	else {
		*cp = '\0';
		cp++;
		ftosinfo->ftos = buffer[0] ? strtol(buffer, &end, 0) : 0;
		if (ebt_errormsg[0] != '\0')
			return;
		ftosinfo->mask = cp[0] ? strtol(cp, &end, 0) : 0xFF;
		if (ebt_errormsg[0] != '\0')
			return;
	}
	free(buffer);
}

static int parse(int c, char **argv, int argc,
   const struct ebt_u_entry *entry, unsigned int *flags,
   struct ebt_entry_target **target)
{
	struct ebt_ftos_info *ftosinfo =
	   (struct ebt_ftos_info *)(*target)->data;
	char *end;

	switch (c) {
	case '1':
		parse_ftos(optarg, ftosinfo);
		break;

	 default:
		return 0;
	}

	return 1;
}

static void final_check(const struct ebt_u_entry *entry,
   const struct ebt_entry_target *target, const char *name,
   unsigned int hookmask, unsigned int time)
{

}

static void print(const struct ebt_u_entry *entry,
   const struct ebt_entry_target *target)
{
	struct ebt_ftos_info *ftosinfo =
	   (struct ebt_ftos_info *)target->data;

	printf("--set-ftos 0x%x/0x%x", ftosinfo->ftos, ftosinfo->mask);

}

static int compare(const struct ebt_entry_target *t1,
   const struct ebt_entry_target *t2)
{
	struct ebt_ftos_info *ftosinfo1 =
	   (struct ebt_ftos_info *)t1->data;
	struct ebt_ftos_info *ftosinfo2 =
	   (struct ebt_ftos_info *)t2->data;

	return ftosinfo1->ftos == ftosinfo2->ftos &&
	ftosinfo1->mask == ftosinfo2->mask;
}

static struct ebt_u_target ftos_target =
{
	.name		= EBT_FTOS_TARGET,
	.size		= sizeof(struct ebt_ftos_info),
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
	ebt_register_target(&ftos_target);
}
/* end merge */
/* above code is the original code
static int ftos_supplied;

static struct option opts[] =
{
	{ "ftos-target" , required_argument, 0, FTOS_TARGET },
	{ "set-ftos"    , required_argument, 0, FTOS_SETFTOS },
	{ "wmm-ftos", no_argument, 0 , FTOS_WMMFTOS },
	{ "8021q-ftos", no_argument, 0 , FTOS_8021QFTOS },
	{ 0 }
};

static void print_help()
{
	printf(
	"ftos target options:\n"
	" --set-ftos value     : Set TOS byte in IP packet header \n"
	"			 This value can be in decimal (ex: 32)\n"
	"			 in hex (ex: 0x20)\n"
	" --ftos-target target : ACCEPT, DROP, RETURN or CONTINUE\n");
}

static void init(struct ebt_entry_target *target)
{
	struct ebt_ftos_t_info *ftosinfo =
	   (struct ebt_ftos_t_info *)target->data;

	ftosinfo->target = EBT_CONTINUE;
	ftosinfo->ftos = 0;
	ftos_supplied = 0;
}

#define OPT_FTOS_TARGET   0x01
#define OPT_FTOS_SETFTOS  0x02
#define OPT_FTOS_WMMFTOS      0x04
#define OPT_FTOS_8021QFTOS    0x08

static int
parse(int c, char **argv, int argc,
   const struct ebt_u_entry *entry, unsigned int *flags,
   struct ebt_entry_target **target)
{
	struct ebt_ftos_t_info *ftosinfo =
	   (struct ebt_ftos_t_info *)(*target)->data;
	char *end;

	switch (c) {
	case FTOS_TARGET:
		ebt_check_option(flags, FTOS_TARGET);
		if (FILL_TARGET(optarg, ftosinfo->target))
			ebt_print_error("Illegal --ftos-target target");
		break;
	case FTOS_SETFTOS:
		ebt_check_option(flags, FTOS_SETFTOS);
		ftosinfo->ftos = (u_int8_t)strtoul(optarg, &end, 0);
        ftosinfo->ftos_set = OPT_FTOS_SETFTOS;
		if (*end != '\0' || end == optarg)
			ebt_print_error("Bad FTOS value '%s'", optarg);
		ftos_supplied = 1;
                break;
    case FTOS_WMMFTOS:
        ebt_check_option(flags, OPT_FTOS_SETFTOS);
        ftosinfo->ftos_set = FTOS_WMMFTOS;
        //printf("LEON DEBUG: wmm-ftos..........\n");
        ftos_supplied = 1;
        break;
    case FTOS_8021QFTOS:
        ebt_check_option(flags, OPT_FTOS_8021QFTOS);
        ftosinfo->ftos_set = FTOS_8021QFTOS;
        //printf("LEON DEBUG: 8021q-ftos..........\n");
        ftos_supplied = 1;
        break;
	 default:
		return 0;
	}
	return 1;
}

static void
final_check(const struct ebt_u_entry *entry,
   const struct ebt_entry_target *target, const char *name,
   unsigned int hookmask, unsigned int time)
{
	struct ebt_ftos_t_info *ftosinfo = (struct ebt_ftos_t_info *)target->data;

	if (time == 0 && ftos_supplied == 0)
		ebt_print_error("No ftos value supplied");
	if (BASE_CHAIN && ftosinfo->target == EBT_RETURN)
		ebt_print_error("--ftos-target RETURN not allowed on base chain");
}


// Prints out the targinfo. 
static void 
print(const struct ebt_u_entry *entry,
   const struct ebt_entry_target *target)
{
	const struct ebt_ftos_t_info *ftosinfo = (const struct ebt_ftos_t_info*)target->data;
    if(ftosinfo->ftos_set == FTOS_WMMFTOS)
        printf("WMM mapping to Tos");
    else if(ftosinfo->ftos_set == FTOS_8021QFTOS)
        printf("802.1Q mapping to Tos");
    else
	printf("TOS set 0x%x", ftosinfo->ftos);

	if (ftosinfo->target == EBT_ACCEPT)
		return;
	printf(" --ftos-target %s", TARGET_NAME(ftosinfo->target));
}

static int 
compare(const struct ebt_entry_target *t1,
  	 const struct ebt_entry_target *t2)
{
	struct ebt_ftos_t_info *ftosinfo1 =
	   (struct ebt_ftos_t_info *)t1->data;
	struct ebt_ftos_t_info *ftosinfo2 =
	   (struct ebt_ftos_t_info *)t2->data;

	return ftosinfo1->target == ftosinfo2->target &&
	   ftosinfo1->ftos == ftosinfo2->ftos &&
	   ftosinfo1->ftos_set == ftosinfo2->ftos_set;
}

#if 0
// Saves the union ipt_targinfo in parsable form to stdout. 
static void
save(const struct ipt_ip *ip, const struct ipt_entry_target *target)
{
	const struct ipt_FTOS_info *finfo =
		(const struct ipt_FTOS_info *)target->data;

	printf("--set-ftos 0x%02x ", finfo->ftos);
}
#endif

static
struct  ebt_u_target ftos_target = 
{
    EBT_FTOS_TARGET,
    sizeof(struct ebt_ftos_t_info),
    print_help,
    init,
    parse,
    final_check,
    print,
    compare,
    opts
};

void _init(void)
{
	ebt_register_target(&ftos_target);
}
*/
