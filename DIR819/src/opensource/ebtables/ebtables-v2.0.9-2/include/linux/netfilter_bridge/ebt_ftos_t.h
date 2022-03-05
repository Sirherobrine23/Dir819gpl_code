#ifndef __LINUX_BRIDGE_EBT_FTOS_T_H
#define __LINUX_BRIDGE_EBT_FTOS_T_H
/*********************************************************
   merge form MediaTek 2.6.22 SDK, expand nefilter_bridge
 support pppoe package tos settings
  by laiyuhang 2012-5-17
**********************************************************/
#if 1
struct ebt_ftos_info
{
	unsigned char ftos;
	unsigned char mask;
    int target;
};
#else
struct ebt_ftos_t_info
{
    int           ftos_set;
	unsigned char ftos;
	// EBT_ACCEPT, EBT_DROP or EBT_CONTINUE or EBT_RETURN
	int target;
};

#define FTOS_TARGET       0x01
#define FTOS_SETFTOS      0x02
#define FTOS_WMMFTOS      0x04
#define FTOS_8021QFTOS    0x08

#define DSCP_MASK_SHIFT   5
#define PRIO_LOC_NFMARK   16
#define PRIO_LOC_NFMASK   7
#endif

#define EBT_FTOS_TARGET "ftos"

#endif
