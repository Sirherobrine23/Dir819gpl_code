/*
 ***************************************************************************
 * Ralink Tech Inc.
 * 4F, No. 2 Technology 5th Rd.
 * Science-based Industrial Park
 * Hsin-chu, Taiwan, R.O.C.
 *
 * (c) Copyright 2002-2006, Ralink Technology, Inc.
 *
 * All rights reserved. Ralink's source code is an unpublished work and the
 * use of a copyright notice does not imply otherwise. This source code
 * contains confidential trade secret material of Ralink Tech. Any attempt
 * or participation in deciphering, decoding, reverse engineering or in any
 * way altering the source code is stricitly prohibited, unless the prior
 * written consent of Ralink Technology, Inc. is obtained.
 ***************************************************************************

    Module Name:
    mtr_ioctl.h

    Abstract:

    Revision History:
    Who         When            What
    --------    ----------      ----------------------------------------------
    Name        Date            Modification logs
    Steven Liu  2007-02-15      Initial version
*/

#ifndef	__MTR_IOCTL_H__
#define	__MTR_IOCTL_H__

#include "common.h"

#define MTR_ADD_MAC_UL_ENTRY              (0)
#define MTR_ADD_MAC_DL_ENTRY              (1)
#define MTR_DEL_MAC_UL_ENTRY              (2)
#define MTR_DEL_MAC_DL_ENTRY              (3)
#define MTR_ADD_IP_UL_ENTRY               (4)
#define MTR_ADD_IP_DL_ENTRY               (5)
#define MTR_DEL_IP_UL_ENTRY               (6)
#define MTR_DEL_IP_DL_ENTRY               (7)

#define MTR_ADD_SYN_ENTRY                 (8)
#define MTR_DEL_SYN_ENTRY                 (9)
#define MTR_ADD_FIN_ENTRY                 (10)
#define MTR_DEL_FIN_ENTRY		  (11)
#define MTR_ADD_UDP_ENTRY                 (12)
#define MTR_DEL_UDP_ENTRY                 (13)
#define MTR_ADD_ICMP_ENTRY                (14)
#define MTR_DEL_ICMP_ENTRY		  (15)

#define MTR_CLEAN_TBL                     (16)
#define MTR_GET_CHIP_VER		  (17)
#define MTR_GET_ALL_ENTRIES               (18)

#define MTR_DEVNAME                     "mtr0"
#define MTR_MAJOR                       (250)


enum MtrInterval {
	_1MS=0,
	_10MS=1,
	_50MS=2,
	_100MS=3,
	_500MS=4,
	_1000MS=5,
	_5000MS=6,
	_10000MS=7
};

enum MtrResult {
	MTR_SUCCESS=0,
	MTR_FAIL=1,
	MTR_TBL_FULL=2
};

enum Rt2880ChipVer { //MTR feature not support in RT2880-Shuttle & RT2880-MP
	RT2880_MP2=0x200,
};

enum RalinkChipId {
    RT2880=0,
    RT3052=1,
    RT2883=2,
    RT3883=3,
    RT3350=4,
    RT3352=5,
    RT6855=6
};

struct mtr_args {
    unsigned char  mac[6];
    enum MtrResult result;
    unsigned long  ip_s; /* Start Ip Address */
    unsigned long  ip_e; /* End Ip Address */
    unsigned long  mg_num; /* meter group */
    unsigned short token_rate;
    unsigned short bk_size;
    unsigned char  mtr_mode; /* Byte meter/Pkt meter mode */
    enum MtrInterval mtr_intval;
    unsigned int   chip_ver;
    unsigned int   chip_id;
};

struct mtr_list_args {
    enum MtrResult   result;
    unsigned int     num_of_entries:16;
    struct mtr_args  entries[0];
};

int MtrRegIoctlHandler(void);
void MtrUnRegIoctlHandler(void);

#endif
