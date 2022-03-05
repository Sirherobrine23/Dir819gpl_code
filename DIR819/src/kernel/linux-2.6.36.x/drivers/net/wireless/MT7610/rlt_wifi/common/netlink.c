/*
 * drivers/net/wireless/MT7610/rlt_wifi/common/netlink.c
 *
 * Author:Hefuhua <hefuhua@163.com>
 * Date:  29 ÆßÔÂ 2014
 * Time:  16:44:52
 *
 *  Copyright (c), 1991-2014, T&W ELECTRONICS(SHENTHEN) Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Changelog
 */

#include <linux/netlink.h>
#include <net/sock.h>
#include "netlink.h"

/******************************************************************
 *                               LOCAL VAR                        *
 ******************************************************************/
static unsigned int pid = 0;			// target pid in userspace
static struct sock *pst_nl_sock = NULL;	// the netlink socket pointer
static struct proc_dir_entry *proc_pid = NULL; 	// pid proc entry pointer

/*******************************************************************
 *                                STRUCT                           *
 *******************************************************************/
typedef struct netlink_msg_payload {	/* valid message body struct */
	unsigned int cmd;	// operation command
	unsigned int len;	// length of msg exclude the terminatiing character '\0'
	char msg[];			// message content
} NL_MSG_PAYLOAD, *PNL_MSG_PAYLOAD;


/********************************************************************
 * Desc: there is a common routine using to receive messages from userspace
 *
 * @buff: data buffer from userspace
 *
 * @return: received message size
 * @author: rongwei
 * @data:	2014/05/16
 *******************************************************************/
static int tbs_netlink_recv_msg( struct sk_buff *buff )
{
	return 0;
}

/********************************************************************
 * Desc: this routine mainly is response to send a unicast messages to userspace
 *
 * @cmd: operation command
 * @content: valid message content
 *
 * @return: the number of bytes sent if success, other is -1
 * @author: rongwei
 * @data:	2014/05/16
 *******************************************************************/
int tbs_netlink_send_msg( int cmd, char *content )
{
	int iRet = 0;
	int content_len = 0;		 // contene length
	struct sk_buff *skb = NULL;	 // socket control block pointer
	struct nlmsghdr *nlh = NULL; // netlink header pointer
	NL_MSG_PAYLOAD	payload;	 // message payload

	/* caculate the content length not include the size of the cmd and len field in valid message payload.
	 * the main purpose is convenition to copy the valid message content and control info separately 
	 * by 4-byte alignment
	 */
	if( content )
	{
		content_len = strlen( content ) ; // not include the terminating '\0' character at the end of content
	}
	
	/* alloc an free memery space which be used to load the entire message include netlink message head
	 * and valid message body used by application in userspace
	 */
	skb = alloc_skb( NLMSG_SPACE( sizeof( NL_MSG_PAYLOAD ) + content_len ), GFP_KERNEL );
	if( !skb )
	{
		printk( "[%s(%d)] fail to alloc skb_buff!\n", __FUNCTION__, __LINE__ );
		return -1; 
	}

	/* init the netlink message head */
	nlh = nlmsg_put( skb, 0, 0, 0, sizeof( NL_MSG_PAYLOAD ) + content_len, 0 );
	NETLINK_CB( skb ).pid = 0;		 // set the src pid to zero when send from kernel to userspace
	NETLINK_CB( skb ).dst_group = 0; // set the netlink group to zero if it don't belong to any one 
	
	/* copy the message body */
	payload.cmd = cmd;
	payload.len = content_len;
	memcpy( NLMSG_DATA( nlh ), &payload, sizeof( NL_MSG_PAYLOAD ) );	// keep 4-byte alignment
	if( content )
	{
		memcpy( NLMSG_DATA( nlh ) + sizeof( NL_MSG_PAYLOAD ), content, content_len );
	}

	/* send an unicast message to userspace */
	iRet = netlink_unicast( pst_nl_sock, skb, pid, 0 );
	
	return iRet;
}

/********************************************************************
 * Desc: this routine is response to read proc entry
 *
 * @return: 0(success), -1(Fail)
 * @author: rongwei
 * @data:	2014/05/16
 *******************************************************************/
static int proc_pid_read( char *buf, char **start, off_t offset, int len, int *eof, void *data )
{
	int iRet = 0;
	iRet = snprintf( buf, len, "%d", pid );

	return iRet;
}

/********************************************************************
 * Desc: this routine is response to wirte proc entry
 *
 * @return: length of data writed in proc entry
 * @author: rongwei
 * @data:	2014/05/16
 *******************************************************************/
static ssize_t proc_pid_write( struct file *filp, const char __user *buf,unsigned long len, void *data )
{
	int iRet = 0;
	iRet = sscanf( buf, "%d", &pid );
	
	return len;
}

/********************************************************************
 * Desc: this routine mainly is response to complete this two action below: 
 * 1.create an netlink socket that is response to communicate with userspace
 * 2.create a proc entry that used to store pid of netlink socket in userspace
 *
 * @protocol: netlink protocol
 * @pid_entry_name: proc entry name
 *
 * @return: netlink socket pointer if success, other is NULL
 * @author: rongwei
 * @data:	2014/05/16
 *******************************************************************/
int tbs_netlink_sock_create( int protocol, char *pid_entry_name )
{	
	pst_nl_sock = netlink_kernel_create( &init_net, protocol, 0, tbs_netlink_recv_msg, NULL, THIS_MODULE );
	if( !pst_nl_sock )
	{
		printk( "[%s(%d)] fail to create netlink socket in wireless driver!\n", __FUNCTION__, __LINE__ );
		return -1;
	}

	proc_pid = create_proc_entry( pid_entry_name, 0644, NULL );	// create proc entry to store pid
	proc_pid->read_proc = proc_pid_read;	// read proc entry
	proc_pid->write_proc = proc_pid_write;	// write proc entry

	return 0;
}

/********************************************************************
 * Desc: destroy the created netlink socket
 *
 * @pid_entry_name: proc entry name
 *
 * @author: rongwei
 * @data:	2014/05/16
 *******************************************************************/
void tbs_netlink_sock_destroy( char *pid_entry_name )
{
	if( pst_nl_sock )
	{
		netlink_kernel_release( pst_nl_sock );		// close netlink socket
	}

	if( proc_pid )
	{
		remove_proc_entry( pid_entry_name, NULL );	// remove pid proc entry
	}
}



