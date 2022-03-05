/************************************************************************
 *
 *	Copyright (C) 2006 Trendchip Technologies, Corp.
 *	All Rights Reserved.
 *
 * Trendchip Confidential; Need to Know only.
 * Protected as an unpublished work.
 *
 * The computer program listings, specifications and documentation
 * herein are the property of Trendchip Technologies, Co. and shall
 * not be reproduced, copied, disclosed, or used in whole or in part
 * for any reason without the prior express written permission of
 * Trendchip Technologeis, Co.
 *
 *************************************************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/spinlock.h>
#include <linux/interrupt.h>
#include <linux/signal.h>
#include <linux/sched.h>
#include <linux/mm.h>
#include <linux/init.h>
#include <linux/timer.h>
#include <linux/delay.h>
#include <linux/proc_fs.h>
#include <linux/dma-mapping.h>
#include <linux/mii.h>
#include <asm/io.h>
#include <asm/tc3162/tc3162.h>
#include <asm/tc3162/ledcetrl.h>
#include <asm/tc3162/TCIfSetQuery_os.h>
#include <linux/if_vlan.h>

#include "tcconsole.h"
// #include "tcswitch.h"

#ifdef TC_CONSOLE_ENABLE  /*Ryan_20091019*/
u8 dmt_NewVersion = 0;
static u8 tcc_mac_addr[] = {0x00, 0x00, 0xaa, 0xbb, 0xcc, 0xff};
static char tcc_cmd[1024]={0};
static int tcconsole_timeout=720;/*Default is 3 mins = 3x60x4 */
atomic_t tcconsole_port_num = ATOMIC_INIT(-1); // TODO: Fixme!

extern struct net_device *switch_dev[];

extern int tc3262_gmac_tx(struct sk_buff *skb, struct net_device *dev);
extern int mt751x_ethdev2port(struct net_device *dev);


static tcconsole_uart_timeout_t tcc_uart_timeout={0, 0, 0};
/* ADSL RTS dump function */
void getTcconsoleFile(void)
{
	/*For tcconsole, function prototype of MAC and DMT have to be matched*/
	dmt_NewVersion = 1;
}

/*_____________________________________________________________________________
 **      function name: isTCConsolePkt
 **      descriptions:
 **		Use to check transmit packet that is used for tcconsole packet.
 **      parameters:
 **         skb: socket buffer to send
 **
 **      global:
 **         None
 **
 **      return:
 **         1: Packets is belongs to tcconsole packet.
 **         0: Normal packets
 **
 **      call:
 **
 **      revision:
 **      1. Here 2010/03/18
 **____________________________________________________________________________
 */
int isTCConsolePkt(struct sk_buff *skb)
{
	if(skb->data[12] == 0xaa) {
		skb->mark |= SKBUF_TCCONSOLE;
		return 1;
	}
	return 0;
}/*end isTCConsolePkt*/

/*_____________________________________________________________________________
 **      function name: tcconsole_pro_idx
 **      descriptions:
 **		Find out the tc console proto index of socket buffer that we must to
 **		skip the vlan header.
 **
 **      parameters:
 **         skb: socket buffer to send
 **         vlan_level: VLan level
 **
 **      global:
 **         None
 **
 **      return:
 **		   The index of tc console protocl.
 **
 **      call:
 **         None
 **
 **      revision:
 **      1. Here 2010/03/18
 **____________________________________________________________________________
 */
int tcconsole_pro_idx(struct sk_buff *skb, int *vlan_level)
{
	int i=0;
	int proto_idx=0;
	int idx = (VLAN_ETH_ALEN<<1); /*VLAN_ETH_ALEN * 2=12*/
	*vlan_level=0;
	proto_idx=idx;
	for(i=1; i<=MAX_VLAN_LAYER; i++){
		if(skb->data[idx]==0x81 && skb->data[idx+1]==0x00){
			*vlan_level=i;
			idx+=VLAN_HLEN;
		}
		else{
			break;
		}
	}
	if(*vlan_level!=0)
		proto_idx += (VLAN_HLEN<<(*vlan_level-1));
	return proto_idx;
}/*end tcconsole_pro_idx*/

int tcconsole_proc(struct sk_buff *skb)
{
	int tc_pro_idx=0;
	int tcc_cmd_idx=0;
	int rm_len=0;
	int vlan_level=0;
	int cur_port;

	tc_pro_idx=tcconsole_pro_idx(skb, &vlan_level);
	if ((skb->data[tc_pro_idx] == 0xaa) && (skb->data[tc_pro_idx+1] == 0xaa)) {
		if (adsl_dev_ops) {
			tcc_cmd_idx=tc_pro_idx+2;
			switch(skb->data[tcc_cmd_idx]){
				case MAC_RTS_START:
					getTcconsoleFile();
					/*Store the tcconsole client mac address*/
					memcpy(tcc_mac_addr,skb->data+ETH_ALEN, ETH_ALEN);
					printk(KERN_INFO "tconsole start, port name: %s\n",
							skb->dev->name);
					cur_port = mt751x_ethdev2port(skb->dev);
					if (cur_port >= 0) {
						printk(KERN_INFO "[Check] port number: %d,"
								" port name: %s\n",
								cur_port, switch_dev[cur_port]->name);
						atomic_set(&tcconsole_port_num, cur_port);
					} else {
						printk(KERN_ERR "failed while get tcconsole port.\n");
					}
					break;
				case MAC_RTS_STOP:
					tcc_uart_timeout.sendUart=0;
					break;
				case MAC_RTS_CONSOLE_ON:
					tcc_uart_timeout.sendUart=1;
					tcc_uart_timeout.timeout=0;
					tcc_uart_timeout.rcvpkt=0;
					break;
				case MAC_RTS_CONSOLE_CMD:
					memcpy(tcc_cmd, skb->data + tcc_cmd_idx + 1,
							skb->len - tcc_cmd_idx);
					tcconsole_cmd(tcc_cmd, strlen(tcc_cmd));
					break;
				default:
					break;
			}
			tcc_uart_timeout.rcvpkt++;
			/*if there is inclued vlan header, we must be strip the vlan header
			 * before to send upper layer*/
			if((vlan_level==1) || (vlan_level==2)){
				rm_len= (VLAN_HLEN<<(vlan_level-1));
				memmove(skb->data+rm_len, skb->data, (VLAN_ETH_ALEN<<1));
				skb_pull(skb, rm_len);
			}
			if (adsl_dev_ops) {
				if (adsl_dev_ops->rts_rcv) {
					adsl_dev_ops->rts_rcv((struct sk_buff *)skb->data);
				}
			}
			// adsl_dev_ops->rts_rcv((struct sk_buff *)skb->data);
		}
		dev_kfree_skb_any(skb);
	} else{
		return 0;
	}
	return 1;
}

/*_____________________________________________________________________________
 **      function name: tcconsole_chk
 **      descriptions:
 **        The periodic check the tcconsole packet is timeout or not, if there
 **      is no tcconsole packet to send and timeout occurt, we will be disable the
 **		uart message to send ethernet.
 **
 **      parameters:
 **         None
 **
 **      global:
 **         tcc_uart_timeout
 **
 **      return:
 **         None
 **
 **      call:
 **		   None
 **
 **      revision:
 **      1. Here 2010/09/23
 **____________________________________________________________________________
 */
#if 0
static void tcconsole_chk(void)
{
	/*There is no tcconsole packet.*/
	if(tcc_uart_timeout.sendUart == 0)
		return;
	local_bh_disable();
	/*
	 * printk("rcv:%d timeout:%d\r\n", tcc_uart_timeout.rcvpkt,
	 *         tcc_uart_timeout.timeout );
	 */
	if(tcc_uart_timeout.rcvpkt==0 && tcc_uart_timeout.sendUart==1){
		if(tcc_uart_timeout.timeout == tcconsole_timeout){
			/*disable uart message to send ethernet*/
			tcc_uart_timeout.sendUart=0;
			tcc_uart_timeout.timeout=0;
		}
		else{
			tcc_uart_timeout.timeout++;
		}
	}
	else{
		/*Got tcconsole pkt so reset timeout*/
		tcc_uart_timeout.timeout=0;
	}
	/*Clear the counter*/
	tcc_uart_timeout.rcvpkt=0;
	local_bh_enable();
}
#endif

/*_____________________________________________________________________________
 **      function name: uart_msg_to_tcconsole
 **      descriptions:
 **			Encapsulate the console message to tcconsole packet then send to
 **		tcconsole utilty.
 **
 **      parameters:
 **         msg: console message
 **         len: length of console mesage
 **
 **      global:
 **         tcc_uart_timeout
 **
 **      return:
 **         None
 **
 **      call:
 **         skbmgr_dev_alloc_skb2k
 **         tc3162_mac_tx
 **         tc3262_gmac_tx
 **
 **      revision:
 **      1. Here 2010/09/26
 **____________________________________________________________________________
 */
void uart_msg_to_tcconsole(char* msg, int len)
{
	char console_data_head[15]={0};
	int tcc_pro_len=sizeof(console_data_head);
	int pktLen=0;
	int cur_port;
	struct sk_buff *skb_tmp = NULL;

	if(tcc_uart_timeout.sendUart==0){
		return;
	}

	cur_port = atomic_read(&tcconsole_port_num);
	if (cur_port < 0) {
		printk(KERN_ERR "tcconsole cannot determine which port to"
				" communicate with\n");
		return;
	}

	skb_tmp = skbmgr_dev_alloc_skb2k();
	if(skb_tmp != NULL) {
		memcpy(console_data_head, tcc_mac_addr, ETH_ALEN);
		memcpy(console_data_head+ETH_ALEN, switch_dev[cur_port]->dev_addr,
				ETH_ALEN);
		console_data_head[12] = 0xaa;
		console_data_head[13] = 0xaa;
		console_data_head[14] = MAC_RTS_CONSOLE_DATA;
		memcpy(skb_tmp->data, console_data_head, tcc_pro_len);
		memcpy(skb_tmp->data + tcc_pro_len, msg, len);
		pktLen = tcc_pro_len + len;
		if (pktLen < ETH_ZLEN) {
			memset(skb_tmp->data + pktLen, 0, ETH_ZLEN - pktLen);
			pktLen = ETH_ZLEN;
		}
		skb_put(skb_tmp, pktLen);
		tc3262_gmac_tx(skb_tmp, switch_dev[cur_port]);
	}
}
EXPORT_SYMBOL(uart_msg_to_tcconsole);

static int eth_tcc_timeout_read_proc(char *page, char **start, off_t off,
		int count, int *eof, void *data)
{
	int len;

	len = sprintf(page, "%04d\n", tcconsole_timeout);
	len -= off;
	*start = page + off;

	if (len > count)
		len = count;
	else
		*eof = 1;

	if (len < 0)
		len = 0;

	return len;
}

static int eth_tcc_timeout_write_proc(struct file *file, const char *buffer,
		unsigned long count, void *data)
{
	char val_string[32];

	if (count > sizeof(val_string) - 1)
		return -EINVAL;

	if (copy_from_user(val_string, buffer, count))
		return -EFAULT;

	val_string[count] = '\0';

	tcconsole_timeout = simple_strtoul(val_string, NULL, 10);
	return count;
}

void create_tcconsole_proc(void)
{
	struct proc_dir_entry *eth_proc;

	eth_proc = create_proc_entry("tc3162/tcconsole_timeout", 0, NULL);
	if (!eth_proc) {
		printk("failed while create TC console proc entry!!!\n");
		return;
	}
	eth_proc->read_proc = eth_tcc_timeout_read_proc;
	eth_proc->write_proc = eth_tcc_timeout_write_proc;
}

void delete_tcconsole_proc(void)
{
	remove_proc_entry("tc3162/tcconsole_timeout", 0);
}
#endif
