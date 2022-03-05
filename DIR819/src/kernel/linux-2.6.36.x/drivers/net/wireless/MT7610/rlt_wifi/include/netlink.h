/*
 * x:/sitecom_ac750/src/kernel/linux-2.6.36.x/drivers/net/wireless/MT7610/rlt_wifi/include/netlink.h
 *
 * Author:Hefuhua <hefuhua@163.com>
 * Date:  29 ÆßÔÂ 2014
 * Time:  16:46:06
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


#ifndef _NETLINK_H
#define _NETLINK_H 1

/*****************************************************************************
*                                 MACRO                                      *
******************************************************************************/
#define NL_TBS_WLAN0_PID_ENTRY_NAME		"nl_pid_wl0"	/* pid entry name for 2.4G band */
#define NL_TBS_WLAN1_PID_ENTRY_NAME		"nl_pid_wl1"	/* pid entry name for 5.8G band */

/*****************************************************************************
*                                 ENUM                                       *
******************************************************************************/
/* private netlink operate command list */
enum {
	NL_CMD_WLAN_WSC_STATUS_CHG	/* wps status change from unconfigured to configured */
};
/******************************************************************************
 *                                FUNCTION DECLARE                            *
 ******************************************************************************/
extern int tbs_netlink_send_msg( int cmd, char *content );
extern int tbs_netlink_sock_create( int protocol, char *pid_entry_name );
extern void tbs_netlink_sock_destroy( char *pid_entry_name );


#endif /* _NETLINK_H */

