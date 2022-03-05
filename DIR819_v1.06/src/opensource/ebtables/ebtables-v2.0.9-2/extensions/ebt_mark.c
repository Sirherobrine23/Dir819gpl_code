#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "../include/ebtables_u.h"
#include "../include/linux/netfilter_bridge/ebt_mark_t.h"

static int mark_supplied;


static struct option opts[] =
{
	{ "mark-target" , required_argument, 0, MARK_TARGET },
	{ "set-mark"    , required_argument, 0, MARK_SETMARK },
	{ "mark-set"    , required_argument, 0, MARK_SETMARK },
	{ "mark-or"     , required_argument, 0, MARK_ORMARK  },
	{ "mark-and"    , required_argument, 0, MARK_ANDMARK },
	{ "mark-xor"    , required_argument, 0, MARK_XORMARK },
	{ 0 }
};

static void print_help()
{
	printf(
	"mark target options:\n"
	" --mark-set value[/mask]     : Set nfmark value ( nfmark = (nfmark & ~mask) | (mark & mask)) \n"
	" --mark-or  value     : Or nfmark with value (nfmark |= value)\n"
	" --mark-and value     : And nfmark with value (nfmark &= value)\n"
	" --mark-xor value     : Xor nfmark with value (nfmark ^= value)\n"
	" --mark-target target : ACCEPT, DROP, RETURN or CONTINUE\n");
}

static void init(struct ebt_entry_target *target)
{
	struct ebt_mark_t_info *markinfo =
	   (struct ebt_mark_t_info *)target->data;

	markinfo->target = EBT_ACCEPT;
	markinfo->mark = 0;
    markinfo->mask = 0; /* add by laiyuhang 2012-05-17: for police route mask request */
	mark_supplied = 0;
}


static int parse(int c, char **argv, int argc,
   const struct ebt_u_entry *entry, unsigned int *flags,
   struct ebt_entry_target **target)
{
	struct ebt_mark_t_info *markinfo =
	   (struct ebt_mark_t_info *)(*target)->data;
	char *end = NULL;

	switch (c) {
	case MARK_TARGET:
		{ int tmp;
		ebt_check_option2(flags, OPT_MARK_TARGET);
		if (FILL_TARGET(optarg, tmp))
			ebt_print_error2("Illegal --mark-target target");
		/* the 4 lsb are left to designate the target */
		markinfo->target = (markinfo->target & ~EBT_VERDICT_BITS) | (tmp & EBT_VERDICT_BITS);
		}
		return 1;
	case MARK_SETMARK:
		ebt_check_option2(flags, OPT_MARK_SETMARK);
		if (*flags & (OPT_MARK_ORMARK|OPT_MARK_ANDMARK|OPT_MARK_XORMARK))
			ebt_print_error2("--mark-set cannot be used together with specific --mark option");
/*****************************************************************
  add for police route request, optarg will splite by '/', head
  will save as mark, tail will save as mask
  by laiyuhang 2012-05-18
*****************************************************************/
        markinfo->mark = strtoul (optarg, &end, 0);
        if (*end == '/')
            markinfo->mask = strtoul (end+1, &end, 0);
        else
            markinfo->mask = 0;

        if (*end != '\0' || end == optarg)
	        ebt_print_error2("Bad MARK value '%s'", optarg);

        goto end;
/* end add */
                break;
	case MARK_ORMARK:
		ebt_check_option2(flags, OPT_MARK_ORMARK);
		if (*flags & (OPT_MARK_SETMARK|OPT_MARK_ANDMARK|OPT_MARK_XORMARK))
			ebt_print_error2("--mark-or cannot be used together with specific --mark option");
		markinfo->target = (markinfo->target & EBT_VERDICT_BITS) | MARK_OR_VALUE;
                break;
	case MARK_ANDMARK:
		ebt_check_option2(flags, OPT_MARK_ANDMARK);
		if (*flags & (OPT_MARK_SETMARK|OPT_MARK_ORMARK|OPT_MARK_XORMARK))
			ebt_print_error2("--mark-and cannot be used together with specific --mark option");
		markinfo->target = (markinfo->target & EBT_VERDICT_BITS) | MARK_AND_VALUE;
                break;
	case MARK_XORMARK:
		ebt_check_option2(flags, OPT_MARK_XORMARK);
		if (*flags & (OPT_MARK_SETMARK|OPT_MARK_ANDMARK|OPT_MARK_ORMARK))
			ebt_print_error2("--mark-xor cannot be used together with specific --mark option");
		markinfo->target = (markinfo->target & EBT_VERDICT_BITS) | MARK_XOR_VALUE;
                break;
	 default:
		return 0;
	}

/*********************************************************************
  mutual code:
  if the optarg include non-numeric character or miss parameter values
  return error
  but new mark-set style has been checked before, so will jump this
  check and goto end.
  by laiyuhang 2012-05-18
**********************************************************************/
	markinfo->mark = strtoul(optarg, &end, 0);
	if (*end != '\0' || end == optarg)
		ebt_print_error2("Bad MARK value '%s'", optarg);

end:
	mark_supplied = 1;
	return 1;
}

static void final_check(const struct ebt_u_entry *entry,
   const struct ebt_entry_target *target, const char *name,
   unsigned int hookmask, unsigned int time)
{
	struct ebt_mark_t_info *markinfo =
	   (struct ebt_mark_t_info *)target->data;

	if (time == 0 && mark_supplied == 0) {
		ebt_print_error("No mark value supplied");
	} else if (BASE_CHAIN && (markinfo->target|~EBT_VERDICT_BITS) == EBT_RETURN)
		ebt_print_error("--mark-target RETURN not allowed on base chain");
}

static void print(const struct ebt_u_entry *entry,
   const struct ebt_entry_target *target)
{
	struct ebt_mark_t_info *markinfo =
	   (struct ebt_mark_t_info *)target->data;
	int tmp;

	tmp = markinfo->target & ~EBT_VERDICT_BITS;
	if (tmp == MARK_SET_VALUE)
		printf("--mark-set");
	else if (tmp == MARK_OR_VALUE)
		printf("--mark-or");
	else if (tmp == MARK_XOR_VALUE)
		printf("--mark-xor");
	else if (tmp == MARK_AND_VALUE)
		printf("--mark-and");
	else
		ebt_print_error("oops, unknown mark action, try a later version of ebtables");
	printf(" 0x%lx", markinfo->mark);

    if(markinfo->mask)
        printf("/0x%lx", markinfo->mask);

	tmp = markinfo->target | ~EBT_VERDICT_BITS;
	printf(" --mark-target %s", TARGET_NAME(tmp));
}

static int compare(const struct ebt_entry_target *t1,
   const struct ebt_entry_target *t2)
{
	struct ebt_mark_t_info *markinfo1 =
	   (struct ebt_mark_t_info *)t1->data;
	struct ebt_mark_t_info *markinfo2 =
	   (struct ebt_mark_t_info *)t2->data;

	return markinfo1->target == markinfo2->target &&
	   markinfo1->mark == markinfo2->mark;
}

static struct ebt_u_target mark_target =
{
	.name		= EBT_MARK_TARGET,
	.size		= sizeof(struct ebt_mark_t_info),
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
	ebt_register_target(&mark_target);
}
