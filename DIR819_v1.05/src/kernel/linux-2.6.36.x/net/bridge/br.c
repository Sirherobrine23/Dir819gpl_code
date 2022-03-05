/*
 *	Generic parts
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

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/init.h>
#include <linux/llc.h>
#include <net/llc.h>
#include <net/stp.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/types.h>

#include "br_private.h"

#ifdef PHY_SWITCH_POWER_ON_OFF
static struct proc_dir_entry * proc_port_power;//

/*TODO by Sudenghai 2014-03-10
 *实现控制switch每个端口power on/off，这样客户端网卡才有断开和连接的效果
 */
extern void PHY_power_ops(unsigned int port, int optcode);

static void power_up(unsigned int port)
{
	PHY_power_ops(port, 1);
}
static void power_down(unsigned int port)
{
	PHY_power_ops(port, 0);
}

void switch_port_power_mng(int port,int opcode)
{
    if (port < 0 || port > 4)
    {
        printk(KERN_ERR "%s:unkown port(%d)\n", __func__, port);
        return;
    }

    if (opcode)     /* up */
        power_up(port);
    else
        power_down(port);
}
EXPORT_SYMBOL(switch_port_power_mng);

void dev_to_port_power_mng(char *dev_name, int opcode)
{
	int port;
	int dev_id;
	if(dev_name && (strlen(dev_name) > 3) 
				&& (0 == strncmp(dev_name, "eth", 3)))
	{
		dev_id = dev_name[3] - '0';
		if (dev_id < 1 || dev_id > 5)
	    {
	        printk(KERN_ERR "%s:unkown dev id(%d)\n", __func__, port);
	        return;
	    }

		/*eth1 is always WAN dev*/
#ifdef CONFIG_WAN_AT_P4 
		/*实现设备名eth1~eht5 到端口4~0的转换*/
	    port = ((5 - dev_id) > 0) ? (5 - dev_id) : (dev_id - 5);
#else //CONFIG_WAN_AT_P0
		/*实现设备名eth1~eht5 到端口0~4的转换*/
		port = dev_id-1;
#endif

	    switch_port_power_mng(port, opcode);
	}
}
EXPORT_SYMBOL(dev_to_port_power_mng);

void dev_to_all_port_power_mng(char *dev_name, int opcode)
{
	int port;
	int dev_id;
	if(dev_name && (strlen(dev_name) > 3) 
				&& (0 == strncmp(dev_name, "eth", 3)))
	{
		dev_id = dev_name[3] - '0';
		if (dev_id < 1 || dev_id > 5)
	    {
	        printk(KERN_ERR "%s:unkown dev id(%d)\n", __func__, port);
	        return;
	    }

		/*单独eth1 - WAN down/up*/
		if(1 == dev_id)
		{
			/*eth1 is always WAN dev*/
#ifdef CONFIG_WAN_AT_P4 
			/*实现设备名eth1~eht5 到端口4~0的转换*/
		    port = ((5 - dev_id) > 0) ? (5 - dev_id) : (dev_id - 5);
#else //CONFIG_WAN_AT_P0
			/*实现设备名eth1~eht5 到端口0~4的转换*/
			port = dev_id-1;
#endif
			switch_port_power_mng(port, opcode);
		}
		else
		{
#ifdef CONFIG_WAN_AT_P4 
			for(port=0; port<4; port++)
#else //CONFIG_WAN_AT_P0
			for(port=4; port>0; port--)
#endif
			{
				switch_port_power_mng(port, opcode);
			}
		}

	}
}
EXPORT_SYMBOL(dev_to_all_port_power_mng);

static int port_power_proc_write( struct file *filp, const char __user *buf,unsigned long len, void *data )
{
	int ret;
	char str_buf[256];
	int port = -1;
	int on_off = -1;

	if(len > 255)
	{
		printk("Error. Sample: echo 0 1 > /proc/port_power \n");
		return len;
	}

	copy_from_user(str_buf,buf,len);
	str_buf[len] = '\0';

	ret = sscanf(str_buf,"%d %d", &port, &on_off);
	if(ret == -1 || !(port >= 0 && port <= 4) || !(0 == on_off || 1 == on_off))
	{
		printk("Error. Sample: echo 0 1 > /proc/port_power \n");
		return len;
	}

	//printk("Set:port %d, on_off %d\n", port, on_off);
	switch_port_power_mng(port, on_off);

	return len;
}

#endif

#ifdef CONFIG_LOOPBACK_CHECK
static struct proc_dir_entry * loopbackCheckDir;
static struct proc_dir_entry * loopbackport;
static struct proc_dir_entry * loop_port_restore;
static struct proc_dir_entry * loopback_app_ready;


int gLoopbackPort = 0;
int gLoopPortHangup = 0;
int gLoopbackAppReady = 1;

static int loopbackport_read_proc(char *buf,char **start,off_t off,int count,int *eof,void *data)
{
	int len;
	len = sprintf(buf,"0x%08x\n", gLoopbackPort);
	return len;
}

static int loopbackport_write_proc(struct file *file,const char __user *buffer,
		unsigned long count,void *data)
{
	char tempbuf[8] = {0};
	int port_to_clear = 0;
	unsigned long irqflag;

	if(count == 0)
		return -EFAULT;

	if(copy_from_user(&tempbuf,buffer,sizeof(tempbuf))) {
		printk(KERN_ERR "loopbackport: failed to copy from user\n");
		return -EFAULT;
	}

	port_to_clear = tempbuf[0] - '0';
	if(count == 2 && (port_to_clear >= 0 && port_to_clear <= 9)) {
		gLoopbackPort &= ~(1 << port_to_clear);
		gLoopPortHangup |= (1 << port_to_clear);
	}
	else {
		printk(KERN_ERR "loopbackport: invalid port(%d) to clear, count: %d\n", port_to_clear, count);
		return -EFAULT;
	}
	return count;
}

static int loop_port_restore_read_proc(char *buf,char **start,off_t off,int count,int *eof,void *data)
{
	int len;
	len = sprintf(buf,"0x%08x\n", gLoopPortHangup);
	return len;
}

static int loop_port_restore_write_proc(struct file *file,const char __user *buffer,
		unsigned long count,void *data)
{
    struct net_device *dev = NULL;
    struct net *net = NULL;
	char tempbuf[8] = {0};
	int port_to_clear = 0;
	unsigned long irqflag;
	int powerRestoreId;

	if(count == 0)
		return -EFAULT;

	if(copy_from_user(&tempbuf,buffer,sizeof(tempbuf))) {
		printk(KERN_ERR "loop_port_restore: failed to copy from user\n");
		return -EFAULT;
	}

	/*port is 0~4, WAN is always 0 port and is dev eth1*/
	port_to_clear = tempbuf[0] - '0';
	if(count == 2 && (port_to_clear >= 0 && port_to_clear <= 9)) {
	
		powerRestoreId = port_to_clear+1;//Wan dev name number is 1, Lan dev name number is 2~5
		
		if (gLoopPortHangup & (1 << port_to_clear)) {
			gLoopPortHangup &= ~(1 << port_to_clear);
/*
			local_irq_save(irqflag);
			switch_port_power_mng(powerRestoreId, 1);
			local_irq_restore(irqflag);
*/
			/*遍历netdevice*/
			for_each_net(net) {
				for_each_netdev(net, dev) {
					if(powerRestoreId == (dev->name[3] - '0'))
					{
						rtnl_lock();
						dev_open(dev);
						rtnl_unlock();
					}
				}
			}
		}
	}
	else {
		printk(KERN_ERR "loop_port_restore: invalid port(%d) to restore, count: %d\n", port_to_clear, count);
		return -EFAULT;
	}
	return count;
}

static int loopback_app_ready_read_proc(char *buf,char **start,off_t off,int count,int *eof,void *data)
{
	int len;
	len = sprintf(buf,"%d\n", gLoopbackAppReady);
	return len;
}

static int loopback_app_ready_write_proc(struct file *file,const char __user *buffer,
		unsigned long count,void *data)
{
	char tempbuf[8] = {0};

	if(count == 0)
		return -EFAULT;

	if(copy_from_user(&tempbuf,buffer,sizeof(tempbuf))) {
		printk(KERN_ERR "loopbackport: failed to copy from user\n");
		return -EFAULT;
	}

	gLoopbackAppReady = tempbuf[0] - '0';

	return count;
}

#endif
int (*br_should_route_hook)(struct sk_buff *skb);

static const struct stp_proto br_stp_proto = {
	.rcv	= br_stp_rcv,
};

static struct pernet_operations br_net_ops = {
	.exit	= br_net_exit,
};


/* TBS_TAG: by pengyao 2012-05-23 Desc:support MLD SNOOPING */
#if defined(CONFIG_BR_MLD_SNOOP)
#include "br_mld.h"
#endif

/*
 * TBS_TAG:add by pengyao 2012-05-23
 * Desc: support IGMP SNOOPING
 */
#if defined(CONFIG_IGMP_SNOOPING)
int igmpsnooping = 0;
int multicast2unicastEn = 0;
#endif

#if defined(CONFIG_IGMP_SNOOPING) || defined(CONFIG_BR_MLD_SNOOP)
int br_igmp_debug = 0;
EXPORT_SYMBOL(br_igmp_debug);
int br_mcast_to_unicast = 1;
struct proc_dir_entry *proc_snooping;
static int debug_proc_read(char *page, char **start, off_t off,
			  int count, int *eof, void *data)
{
        char *out = page;
        int len = 0;
        struct net_device *dev = NULL;
        struct net_bridge *bridge = NULL;
        struct net_bridge_mc_fdb_entry *mc_entry = NULL;
        struct net *net = NULL;
        //struct net_device *dev = v;
        struct net_br_mld_mc_fdb_entry *dst = NULL;
        struct net_bridge *br = NULL;

        out += sprintf(out, "debug=%d\n", br_igmp_debug);
        out += sprintf(out, "mc_2_unicast=%d\n", br_mcast_to_unicast);
#ifdef CONFIG_IGMP_SNOOPING
        out += sprintf(out, "igmpsnooping=%d\n", igmpsnooping);
        out += sprintf(out, "filt_mode\t sip\t\t mcast port\t ageing timer\t group\n");
#endif

        /*遍历netdevice*/
        for_each_net(net) {
            for_each_netdev(net, dev) {
                if (dev->priv_flags & IFF_EBRIDGE)
                {
                    bridge = netdev_priv(dev);

#ifdef CONFIG_IGMP_SNOOPING
                    list_for_each_entry(mc_entry, &bridge->mc_list, list) {
                        out += sprintf(out, "%s\t "NIPQUAD_FMT"\t %s\t\t %lu\t\t "
                                    //"%02x:%02x:%02x:%02x:%02x:%02x\n",
                                    NIPQUAD_FMT"\n",
                                    (mc_entry->src_entry.filt_mode == MCAST_EXCLUDE)?"MCAST_EXCLUDE":"MCAST_INCLUDE",
                                    NIPQUAD(mc_entry->src_entry.src.s_addr),
                                    mc_entry->dst->dev->name,
                                    (jiffies + QUERY_TIMEOUT*HZ - mc_entry->tstamp)/HZ,
                                    //mc_entry->addr.addr[0], mc_entry->addr.addr[1], mc_entry->addr.addr[2],
                                    //mc_entry->addr.addr[3], mc_entry->addr.addr[4], mc_entry->addr.addr[5]);
                                    NIPQUAD(mc_entry->group_addr.s_addr));
                    }
#endif

                }   /*IFF_EBRIDGE*/
            }   /*for_each_netdev*/
        }   /*for_each_net*/

#ifdef CONFIG_BR_MLD_SNOOP
        out += sprintf(out, "mldsnooping=%d\n", br_mld_snooping);
        out += sprintf(out, "bridge	device	group		   reporter          mode  source timeout\n");
#endif

         /*遍历netdevice*/
        for_each_net(net) {
            for_each_netdev(net, dev) {
                if (dev->priv_flags & IFF_EBRIDGE)
                {
                        br = netdev_priv(dev);
#ifdef CONFIG_BR_MLD_SNOOP
                        list_for_each_entry_rcu(dst, &br->mld_mc_list, list) {
                               out += sprintf(out, "%s %6s    ", br->dev->name, dst->dst->dev->name);
                               out += sprintf(out, "%02x:%02x:%02x:%02x:%02x:%02x   ",
                               dst->addr.addr[0], dst->addr.addr[1],
                               dst->addr.addr[2], dst->addr.addr[3],
                               dst->addr.addr[4], dst->addr.addr[5]);

                               out += sprintf(out, "%02x:%02x:%02x:%02x:%02x:%02x   ",
                               dst->host.addr[0], dst->host.addr[1],
                               dst->host.addr[2], dst->host.addr[3],
                               dst->host.addr[4], dst->host.addr[5]);

                               out += sprintf(out, "%2s  %04x:%04x:%04x:%04x   %d\n",
                               (dst->src_entry.filt_mode == MCAST_EXCLUDE) ?
                               "EX" : "IN",
                               dst->src_entry.src.s6_addr32[0],
                               dst->src_entry.src.s6_addr32[1],
                               dst->src_entry.src.s6_addr32[2],
                               dst->src_entry.src.s6_addr32[3],
                               (int) (dst->tstamp - jiffies)/HZ);
                        }
#endif
                }   /*IFF_EBRIDGE*/
            }   /*for_each_netdev*/
        }   /*for_each_net*/

        len = out - page;
        len -= off;
        if (len < count) {
            *eof = 1;
            if (len <= 0)
                return 0;
        } else
            len = count;

        *start = page + off;
        return len;
}


static int debug_proc_write( struct file *filp, const char __user *buf,unsigned long len, void *data )
{
	int ret;
	char str_buf[256];
	char action[20] = {0};
	int val = 0;

	if(len > 255)
	{
		printk("Error. Sample: echo debug 1 > /proc/debug \n");
		return len;
	}

	if (copy_from_user(str_buf,buf,len))
        return -EFAULT;

	str_buf[len] = '\0';

	ret = sscanf(str_buf, "%s %d", action, (int*)&val);
	if(ret == -1 || val < 0 )
	{
		printk("Error.Sample: echo debug 1 > /proc/debug \n");
		return len;
	}
	if (strcmp(action, "debug") == 0)
	{
    	br_igmp_debug = val;
	}
    else if (strcmp(action, "mc") == 0)
    {
        br_mcast_to_unicast = val;
    }
#ifdef CONFIG_IGMP_SNOOPING
    else if (strcmp(action, "igmpsnooping") == 0)
    {
        igmpsnooping = val;
    }
#endif

#ifdef CONFIG_BR_MLD_SNOOP
    else if (strcmp(action, "mldsnooping") == 0)
    {
        br_mld_snooping = val;
    }
#endif

	return len;
}
#endif  /*CONFIG_IGMP_SNOOPING*/
/*
 * TBS_END_TAG
 */
/*2016-08-12 linsd add for wlan guest isolate */
#if defined(CONFIG_BR_WLAN_BLOCK_RELAY)
	int br_wlan_block_relay_enable=0;
	struct proc_dir_entry *procwlanblockrelay=NULL;
	static int br_wlanblockread_proc(char *page, char **start, off_t off, 
			int count, int *eof, void *data)
	{
		int len;
		len = sprintf(page, "wlanblock:%c\n\n",br_wlan_block_relay_enable+'0');
		if (len <= off+count) *eof = 1;
		  *start = page + off;
		  len -= off;
		  if (len>count) len = count;
		  if (len<0) len = 0;
		  return len;
	}
	static int br_wlanblockwrite_proc(struct file *file, const char *buffer,
				  unsigned long count, void *data)
	{
		  unsigned char block_tmp; 
		  if (count < 2) 
			return -EFAULT;
		  
		if (buffer && !copy_from_user(&block_tmp, buffer, 1)) {
			br_wlan_block_relay_enable = block_tmp - '0';
			if(br_wlan_block_relay_enable)
			{
				br_wlan_block_relay_enable=1;
			}
			else
				br_wlan_block_relay_enable=0;	
				return count;
		  }
		return -EFAULT;
	}
#endif
/*2016-08-12 linsd add end*/

static int __init br_init(void)
{
	int err;

	err = stp_proto_register(&br_stp_proto);
	if (err < 0) {
		pr_err("bridge: can't register sap for STP\n");
		return err;
	}

	err = br_fdb_init();
	if (err)
		goto err_out;

	err = register_pernet_subsys(&br_net_ops);
	if (err)
		goto err_out1;

	err = br_netfilter_init();
	if (err)
		goto err_out2;

	err = register_netdevice_notifier(&br_device_notifier);
	if (err)
		goto err_out3;

#ifdef CONFIG_LOOPBACK_CHECK
        loopbackCheckDir = proc_mkdir("loopbackcheck", NULL);
        if ( loopbackCheckDir == NULL )
        {
            printk("create loopback proc error\n");
            return 0;
        }

        if((loopbackport = create_proc_entry("loopbackport",S_IRUGO | S_IWUSR,loopbackCheckDir)) != NULL)
        {
            loopbackport->read_proc = loopbackport_read_proc;
            loopbackport->write_proc = loopbackport_write_proc;
        }

        if((loop_port_restore = create_proc_entry("loop_port_restore",S_IRUGO | S_IWUSR,loopbackCheckDir)) != NULL)
        {
            loop_port_restore->read_proc = loop_port_restore_read_proc;
            loop_port_restore->write_proc = loop_port_restore_write_proc;
        }
        if((loopback_app_ready = create_proc_entry("loopback_app_ready",S_IRUGO | S_IWUSR,loopbackCheckDir)) != NULL)
        {
            loopback_app_ready->read_proc = loopback_app_ready_read_proc;
            loopback_app_ready->write_proc = loopback_app_ready_write_proc;
        }
#endif

	err = br_netlink_init();
	if (err)
		goto err_out4;

	brioctl_set(br_ioctl_deviceless_stub);

#if defined(CONFIG_ATM_LANE) || defined(CONFIG_ATM_LANE_MODULE)
	br_fdb_test_addr_hook = br_fdb_test_addr;
#endif


/* TBS_TAG:add by pengyao 2012-05-23 Desc: support IGMP SNOOPING */
#if defined(CONFIG_IGMP_SNOOPING)
    proc_snooping = create_proc_entry( "multicast_snooping", 0644, init_net.proc_net);
    proc_snooping->read_proc  = debug_proc_read;
    proc_snooping->write_proc = debug_proc_write;
#endif

/* TBS_TAG:add by pengyao 2012-05-23 Desc: support MLD SNOOPING */
#if defined(CONFIG_BR_MLD_SNOOP)
	br_mld_snooping_init();
#endif

#ifdef PHY_SWITCH_POWER_ON_OFF
	proc_port_power = create_proc_entry( "port_power", 0644, NULL);                
	proc_port_power->write_proc  = port_power_proc_write;
#endif

/*2016-08-12 linsd add proc control*/
#if defined (CONFIG_BR_WLAN_BLOCK_RELAY)
			procwlanblockrelay = create_proc_entry("br_wlanblock", 0, NULL);
			if(procwlanblockrelay) {
				procwlanblockrelay->read_proc = br_wlanblockread_proc;
				procwlanblockrelay->write_proc = br_wlanblockwrite_proc;
			}
#endif

	return 0;

err_out4:
	unregister_netdevice_notifier(&br_device_notifier);
err_out3:
	br_netfilter_fini();
err_out2:
	unregister_pernet_subsys(&br_net_ops);
err_out1:
	br_fdb_fini();
err_out:
	stp_proto_unregister(&br_stp_proto);
	return err;
}

static void __exit br_deinit(void)
{
	stp_proto_unregister(&br_stp_proto);

	br_netlink_fini();
	unregister_netdevice_notifier(&br_device_notifier);
	brioctl_set(NULL);

	unregister_pernet_subsys(&br_net_ops);

	rcu_barrier(); /* Wait for completion of call_rcu()'s */

	br_netfilter_fini();
#if defined(CONFIG_ATM_LANE) || defined(CONFIG_ATM_LANE_MODULE)
	br_fdb_test_addr_hook = NULL;
#endif

	br_fdb_fini();

}

EXPORT_SYMBOL(br_should_route_hook);

module_init(br_init)
module_exit(br_deinit)
MODULE_LICENSE("GPL");
MODULE_VERSION(BR_VERSION);
