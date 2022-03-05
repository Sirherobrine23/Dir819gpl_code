#include <linux/module.h>
#include <linux/skbuff.h>
#include <linux/in.h>
#include <linux/tcp.h>
#include <linux/ip.h>
#include <net/ip.h>

#include <net/netfilter/nf_conntrack.h>
#include <net/netfilter/nf_conntrack_core.h>
#include <net/netfilter/nf_conntrack_helper.h>
#include <net/netfilter/nf_conntrack_zones.h>
#include <linux/netfilter/nf_conntrack_proto_gre.h>
#include <linux/netfilter/nf_conntrack_pptp.h>

#define NF_CT_PPTP_VERSION "3.1"
#if 0 //del by sudenghai 2014-2-25 for using tbs way
#define PROCFS_NAME "algonoff_l2tp"
#endif
#define L2TP_CONTROL_PORT 1701

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Harald Welte <laforge@gnumonks.org>");
MODULE_DESCRIPTION("Netfilter connection tracking helper module for L2TP");
MODULE_ALIAS("ip_conntrack_l2tp");
MODULE_ALIAS_NFCT_HELPER("l2tp");

#if 0 //del by sudenghai 2014-2-25 for using tbs way
static unsigned char algonoff_l2tp= 0;
#endif

static int conntrack_l2tp_help(struct sk_buff *skb, unsigned int protoff,
		    struct nf_conn *ct, enum ip_conntrack_info ctinfo)
{

   /*
     * TBS_TAG: by Sudenghai 2014-2-25
     * Desc:Add alg switch
     */
    ALG_CHECK_ONOFF(alg_type_l2tp);
    
	#if 0 //del by sudenghai 2014-2-25 for using tbs way
	struct iphdr * iph = (struct iphdr *)skb_network_header(skb);
	extern __be32 alg_ip;

	if((!algonoff_l2tp)&&(alg_ip != iph->saddr)&&(alg_ip != iph->daddr)) {
		printk("DROP L2TP PACKET!\n");
		return NF_DROP;
	}
	#endif

	return NF_ACCEPT;
}

static struct nf_conntrack_expect_policy l2tp_exp_policy =  {
    .max_expected = 2,
    .timeout = 5 * 60
};

static struct nf_conntrack_helper l2tp __read_mostly = {

	.name			= "l2tp",
	.me			= THIS_MODULE,
	.tuple.src.l3num	= AF_INET,
	.tuple.src.u.tcp.port	= cpu_to_be16(L2TP_CONTROL_PORT),
	.tuple.dst.protonum	= IPPROTO_UDP,
	.help			= conntrack_l2tp_help,
	.expect_policy = &l2tp_exp_policy,
};

#if 0 //del by sudenghai 2014-2-25 for using tbs way
/*
user read something from kernel through proc file 
*/
static int proc_debug_read_l2tp(char *buffer, char **buffer_location, off_t offset, int buffer_length, int *eof, void *data)
{
    if (algonoff_l2tp == 1)
    {
        printk("l2tp ALG ON!\n");
    }
    if (algonoff_l2tp == 0)
    {
        printk("l2tp ALG OFF!\n");
    }
    return -1;
}

/*
user write something to kernel through proc file
*/
static int proc_debug_write_l2tp(struct file *file, const char *buffer, unsigned long count, void *data)
{
    char proc_buffer[count];
    memset(proc_buffer, 0, sizeof(proc_buffer));
    if ( copy_from_user(proc_buffer, buffer, count) ) 
    {
        return -EFAULT;
    }
    if(proc_buffer[0] == '1')
    {
        printk("------Enable l2tp ALG function!------ [%s %s %d]\n", __FILE__, __FUNCTION__, __LINE__);
        algonoff_l2tp = 1;
    }
    else if (proc_buffer[0] == '0')
    {
        printk("------Disable l2tp ALG function!------ [%s %s %d]\n", __FILE__, __FUNCTION__, __LINE__);
        algonoff_l2tp = 0;
    }
    else
    {
        printk("Error setting!\n");
    }
    return -1;
}
#endif

static int __init init(void)
{
	int ret = 0;
	#if 0 //del by sudenghai 2014-2-25 for using tbs way
	struct proc_dir_entry* FP_Proc_algonoff_l2tp;
	#endif
	
	ret = nf_conntrack_helper_register(&l2tp);
	if (ret < 0)
	{
		
		return ret;
	}

	#if 0 //del by sudenghai 2014-2-25 for using tbs way
	FP_Proc_algonoff_l2tp = create_proc_entry(PROCFS_NAME,0644, NULL);
	if (FP_Proc_algonoff_l2tp == NULL)
	{
		remove_proc_entry(PROCFS_NAME, NULL);
		printk(KERN_ALERT "Error: Could not initialize /proc/%s\n", PROCFS_NAME);
	}

	FP_Proc_algonoff_l2tp->read_proc = (read_proc_t *)proc_debug_read_l2tp;
	FP_Proc_algonoff_l2tp->write_proc = (write_proc_t *)proc_debug_write_l2tp;
	FP_Proc_algonoff_l2tp->mode = S_IFREG | S_IRUGO;
    FP_Proc_algonoff_l2tp->gid = 0;
    FP_Proc_algonoff_l2tp->uid = 0;
    FP_Proc_algonoff_l2tp->size = 4;
    #endif

	return 0;
	
}

static void __exit fini(void)
{
	#if 0 //del by sudenghai 2014-2-25 for using tbs way
	remove_proc_entry(PROCFS_NAME, NULL);       // add by dym
	#endif
	nf_conntrack_helper_unregister(&l2tp);
}

module_init(init);
module_exit(fini);
