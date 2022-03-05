
#include <linux/module.h>
#include <linux/skbuff.h>
#include <linux/ip.h>
#include <net/checksum.h>
#include <net/dsfield.h>

#include <linux/netfilter/x_tables.h>
#include <linux/netfilter/xt_extlog.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("wujunyong");
MODULE_DESCRIPTION("Xtables: another method of log information");
MODULE_ALIAS("ipt_extlog");
MODULE_ALIAS("ip6t_extlog");

char opts[3][10]={"tcp", "udp", "tcp_udp"};
extern int scrlog_printk(const char * fmt, ...);

static unsigned int extlogexe(struct sk_buff *skb, const struct xt_target_param *par)
{
    struct timeval tv;
    __kernel_time_t timenow;
    static __kernel_time_t pretime=0;
    static char preproto=0;
    static char preportrang[10]={0};
    const struct extlog_target_info *markinfo = par->targinfo;
    
    do_gettimeofday(&tv);
    timenow=tv.tv_sec;
    if((timenow-pretime<3)&&(markinfo->proto==preproto)&&(!strcmp(preportrang, markinfo->portrange)))
    {
        return XT_CONTINUE;
    }
    pretime=timenow;
    preproto=markinfo->proto;
    strcpy(preportrang, markinfo->portrange);
    
    scrlog_printk("[Block Services]blocked %s port %s\n", opts[(markinfo->proto)-1], markinfo->portrange);
    
    return XT_CONTINUE;
}

static bool extlog_check(const struct xt_tgchk_param *par)
{
	const struct extlog_target_info *markinfo = par->targinfo;

	if (!((markinfo->proto& XT_TCP)|| (markinfo->proto & XT_UDP) || (markinfo->proto & XT_TCP_UDP))) 
        {
            printk(KERN_WARNING "MARK: unknown proto %u\n",markinfo->proto);
            return false;
        }
	return true;
}

#ifdef CONFIG_COMPAT
struct compat_extlog_target_info {
    char proto; //0:tcp, 1: udp, 2:tcp&udp
    char portrange[12]; //port range
};

static void extlog_compat_from_user(void *dst, void *src)
{
	const struct compat_extlog_target_info *cm = src;
	struct extlog_target_info m = {
		.proto	= cm->proto,
		.portrange   = cm->portrange,
	};
	memcpy(dst, &m, sizeof(m));
}

static int extlog_compat_to_user(void __user *dst, void *src)
{
	const struct extlog_target_info *m = src;
	struct compat_extlog_target_info cm = {
		.proto	= m->protp,
		.portrange	= m->portrange,
	};
	return copy_to_user(dst, &cm, sizeof(cm)) ? -EFAULT : 0;
}
#endif /* CONFIG_COMPAT */


static struct xt_target extlog[] __read_mostly = {
	{
		.name		= "EXTLOG",
		.family		= NFPROTO_IPV4,
		.revision	= 0,
		.checkentry	= extlog_check,
		.target		= extlogexe,
		.targetsize	= sizeof(struct extlog_target_info),
#ifdef CONFIG_COMPAT
		.compatsize	= sizeof(struct compat_extlog_target_info),
		.compat_from_user = extlog_compat_from_user,
		.compat_to_user	= extlog_compat_to_user,
#endif
		.table		= "filter",
		.me		= THIS_MODULE,
	},
};

static int __init extlog_init(void)
{
	return xt_register_targets(extlog, ARRAY_SIZE(extlog));
}

static void __exit extlog_exit(void)
{
	xt_unregister_targets(extlog, ARRAY_SIZE(extlog));
}

module_init(extlog_init);
module_exit(extlog_exit);
