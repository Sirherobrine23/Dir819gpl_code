#ifndef __LINUX_BRIDGE_EBT_VLAN_H
#define __LINUX_BRIDGE_EBT_VLAN_H

#define EBT_VLAN_ID	0x01
#define EBT_VLAN_PRIO	0x02
#define EBT_VLAN_ENCAP	0x04
#define EBT_VLAN_MASK (EBT_VLAN_ID | EBT_VLAN_PRIO | EBT_VLAN_ENCAP)
#define EBT_VLAN_MATCH "vlan"

struct ebt_vlan_info {
/*********************************************************
   merge form MediaTek 2.6.22 SDK, expand nefilter_bridge
 support vlanid range and priority range match
  by laiyuhang 2012-5-17
**********************************************************/
#if 1 	
	uint16_t id[2];		/* VLAN ID {1-4095} */
	uint8_t prio[2];		/* VLAN User Priority {0-7} */
#else
	uint16_t id;		/* VLAN ID {1-4095} */
	uint8_t prio;		/* VLAN User Priority {0-7} */
#endif
/* end merge */
	__be16 encap;		/* VLAN Encapsulated frame code {0-65535} */
	uint8_t bitmask;		/* Args bitmask bit 1=1 - ID arg,
				   bit 2=1 User-Priority arg, bit 3=1 encap*/
	uint8_t invflags;		/* Inverse bitmask  bit 1=1 - inversed ID arg, 
				   bit 2=1 - inversed Pirority arg */
};

#endif
