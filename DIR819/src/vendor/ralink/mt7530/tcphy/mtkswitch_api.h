/*
** $Id: $
*/
/************************************************************************
 *
 *	Copyright (C) 2012 Mediatek Inc.
 *	All Rights Reserved.
 *
 * Mediatek Confidential; Need to Know only.
 * Protected as an unpublished work.
 *
 * The computer program listings, specifications and documentation
 * herein are the property of Trendchip Technologies, Co. and shall
 * not be reproduced, copied, disclosed, or used in whole or in part
 * for any reason without the prior express written permission of
 * Mediatek Inc.
 *
 *************************************************************************/
/*
** $Log$
**
 */

#ifndef _GMAC_MT7530_API_H_
#define _GMAC_MT7530_API_H_

#include <linux/types.h>

#ifdef TCSUPPORT_MT7530_SWITCH_API



/************************************************************************
*                          C O N S T A N T S
*************************************************************************
*/

#define MT7530_TOTAL_PORTS	(7)
#define MT7530_QUEUE_NUM	(8)

/************************************************************************
*                            M A C R O S
*************************************************************************
*/


/************************************************************************
*                         D A T A   T Y P E S
*************************************************************************
*/

////#define MT7530_V1_USE_RT62806_MIB
//#define MT7530_MIBCNT_VER	(1)	// MT7530 MIB cnt similar to previous RT62806
#define MT7530_MIBCNT_VER	(2)	// new MT7530 MIB cnt based on SW_team request


typedef enum
{
#if (MT7530_MIBCNT_VER == 1)
	MIB_ID_TX_DROP_CNT = 0x4000,
	MIB_ID_TX_UCAST_CNT = 0x4004,
	MIB_ID_TX_MCAST_CNT = 0x4008,
	MIB_ID_TX_BCAST_CNT = 0x400C,
	MIB_ID_TX_COL_CNT = 0x4010,
	MIB_ID_TX_SCOL_CNT = 0x4014,
	MIB_ID_TX_MCOL_CNT = 0x4018,
	MIB_ID_TX_DEFER_CNT = 0x401C,
	MIB_ID_TX_LCOL_CNT = 0x4020,
	MIB_ID_TX_XCOL_CNT = 0x4024,
	MIB_ID_TX_PAUSE_CNT = 0x4028,
	MIB_ID_RSV1 = 0x402C,
	MIB_ID_RX_DROP_CNT = 0x4030,
	MIB_ID_RX_FILTER_CNT = 0x4034,
	MIB_ID_RX_UCAST_CNT = 0x4038,
	MIB_ID_RX_MCAST_CNT = 0x403C,
	MIB_ID_RX_BCAST_CNT = 0x4040,
	MIB_ID_RX_ALIGN_ERR_CNT = 0x4044,
	MIB_ID_RX_FCS_ERR_CNT = 0x4048,
	MIB_ID_RX_UNDERSIZE_CNT = 0x404C,
	MIB_ID_RX_FRAG_ERR_CNT = 0x4050,
	MIB_ID_RX_OVERSIZE_CNT = 0x4054,
	MIB_ID_RX_JABB_ERR_CNT = 0x4058,
	MIB_ID_RX_PAUSE_CNT = 0x405C,
	MIB_ID_BX_PKT_64_CNT = 0x4060,
	MIB_ID_BX_PKT_65TO127_CNT = 0x4064,
	MIB_ID_BX_PKT_128TO255_CNT = 0x4068,
	MIB_ID_BX_PKT_256TO511_CNT = 0x406C,
	MIB_ID_BX_PKT_512TO1023_CNT = 0x4070,
	MIB_ID_BX_PKT_1024TOMAX_CNT = 0x4074,
	MIB_ID_RSV2 = 0x4078,
	MIB_ID_RSV3 = 0x407C,
	MIB_ID_TX_OCT_CNT_L = 0x4080,	//MIB_ID_TX_OCT_CNT_H/MIB_ID_TX_OCT_CNT_L
	MIB_ID_TX_OCT_CNT_H = 0x4084,	//MIB_ID_TX_OCT_CNT_H/MIB_ID_TX_OCT_CNT_L
	MIB_ID_RX_OCT_CNT_L = 0x4088,	//MIB_ID_RX_OCT_CNT_H/MIB_ID_RX_OCT_CNT_L
	MIB_ID_RX_OCT_CNT_H = 0x408C,	//MIB_ID_RX_OCT_CNT_H/MIB_ID_RX_OCT_CNT_L
	MIB_ID_RX_CTRL_DROP_CNT = 0x4090,
	MIB_ID_RX_ING_DROP_CNT = 0x4094,
	MIB_ID_RX_ARL_DROP_CNT = 0x4098,
	MIB_ID_RSV4 = 0x409C,
#endif
#if (MT7530_MIBCNT_VER == 2)
	MIB_ID_TX_DROP_CNT = 0x4000,
	MIB_ID_TX_CRC_CNT = 0x4004,
	MIB_ID_TX_UCAST_CNT = 0x4008,
	MIB_ID_TX_MCAST_CNT = 0x400C,
	MIB_ID_TX_BCAST_CNT = 0x4010,
	MIB_ID_TX_COL_CNT = 0x4014,
	MIB_ID_TX_SCOL_CNT = 0x4018,
	MIB_ID_TX_MCOL_CNT = 0x401C,
	MIB_ID_TX_DEFER_CNT = 0x4020,
	MIB_ID_TX_LCOL_CNT = 0x4024,
	MIB_ID_TX_XCOL_CNT = 0x4028,
	MIB_ID_TX_PAUSE_CNT = 0x402C,
	MIB_ID_TX_PKT_64_CNT = 0x4030,
	MIB_ID_TX_PKT_65TO127_CNT = 0x4034,
	MIB_ID_TX_PKT_128TO255_CNT = 0x4038,
	MIB_ID_TX_PKT_256TO511_CNT = 0x403C,
	MIB_ID_TX_PKT_512TO1023_CNT = 0x4040,
	MIB_ID_TX_PKT_1024TOMAX_CNT = 0x4044,
	MIB_ID_TX_OCT_CNT_L = 0x4048,
	MIB_ID_TX_OCT_CNT_H = 0x404C,

	MIB_ID_RX_DROP_CNT = 0x4060,
	MIB_ID_RX_FILTER_CNT = 0x4064,
	MIB_ID_RX_UCAST_CNT = 0x4068,
	MIB_ID_RX_MCAST_CNT = 0x406C,
	MIB_ID_RX_BCAST_CNT = 0x4070,
	MIB_ID_RX_ALIGN_ERR_CNT = 0x4074,
	MIB_ID_RX_FCS_ERR_CNT = 0x4078,
	MIB_ID_RX_UNDERSIZE_CNT = 0x407C,
	MIB_ID_RX_FRAG_ERR_CNT = 0x4080,
	MIB_ID_RX_OVERSIZE_CNT = 0x4084,
	MIB_ID_RX_JABB_ERR_CNT = 0x4088,
	MIB_ID_RX_PAUSE_CNT = 0x408C,
	MIB_ID_RX_PKT_64_CNT = 0x4090,
	MIB_ID_RX_PKT_65TO127_CNT = 0x4094,
	MIB_ID_RX_PKT_128TO255_CNT = 0x4098,
	MIB_ID_RX_PKT_256TO511_CNT = 0x409C,
	MIB_ID_RX_PKT_512TO1023_CNT = 0x40A0,
	MIB_ID_RX_PKT_1024TOMAX_CNT = 0x40A4,
	MIB_ID_RX_OCT_CNT_L = 0x40A8,	//MIB_ID_RX_OCT_CNT_H/MIB_ID_RX_OCT_CNT_L
	MIB_ID_RX_OCT_CNT_H = 0x40AC,	//MIB_ID_RX_OCT_CNT_H/MIB_ID_RX_OCT_CNT_L
	MIB_ID_RX_CTRL_DROP_CNT = 0x40B0,
	MIB_ID_RX_ING_DROP_CNT = 0x40B4,
	MIB_ID_RX_ARL_DROP_CNT = 0x40B8,
#endif
} mt7530_switch_api_MibCntType;

typedef enum
{
	OCTMODE_OFF = 0,
	OCTMODE_BAD_ONLY,
	OCTMODE_GOOD_ONLY,
	OCTMODE_BAD_GOOD_BOTH,
} mt7530_switch_api_RxTxOctMode;

typedef enum
{
	BXMODE_OFF = 0,
	BXMODE_TX_ONLY,
	BXMODE_RX_ONLY,
	BXMODE_TX_RX_BOTH,
} mt7530_switch_api_BxPktMode;

typedef struct mt7530_switch_api_backPressure_s
{
	u8 Enable;
	u32 time;
	u16 MaxQueueThreshold;
	u16 MinQueueThreshold;
} mt7530_switch_api_backPressure_t, *mt7530_switch_api_backPressure_ptr;

typedef struct mt7530_switch_DropPolicy_s
{
	u16 greenPacketDropQueueMaxThr;
	u16 greenPacketDropQueueMinThr;
	u16 yellowPacketDropQueueMaxThr;
	u16 yellowPacketDropQueueMinThr;
	u8 greenPacketDropMax_p;
	u8 yellowPacketDropMaxn_p;
	u8 QueueDropW_q;
	u8 DropPrecdenceColourMarking;
} mt7530_switch_DropPolicy_t, *mt7530_switch_DropPolicy_ptr;

typedef struct mt7530_switch_api_trafficDescriptor_s
{
	u32 CIR;
	u32 PIR;
	u32 CBS;
	u32 PBS;
	u8 colourMode;
	u8 ingressColourMarking;
	u8 engressColourMarking;
	u8 meterType;
	u8 direction;	// 0:TX, 1:RX
} mt7530_switch_api_trafficDescriptor_t, *mt7530_switch_api_trafficDescriptor_ptr;

typedef struct
{
	u32 seconds;
	u32 nanoseconds;
} mt7530_switch_api_timestamp;

typedef struct
{
	mt7530_switch_api_timestamp tstamp;
	u8 msg_type;
	u8 seq_id;
} mt7530_switch_api_timestamp_fifo;

/************************************************************************
*              F U N C T I O N   D E C L A R A T I O N S
*************************************************************************
*/

// user API start from ID 0x0010
/************** Wayne *************/
int macMT7530GetBrglearningInd(u8 port);
int macMT7530SetBrglearningInd(u8 port, u8 Ind);
int macMT7530GetPortBrgInd(u8 port, u8 *Ind);
int macMT7530SetPortBrgInd(u8 port, u8 Ind);
int macMT7530GetDiscardUnknownMacInd(u8 port);
int macMT7530SetDiscardUnknownMacInd(u8 port, u8 Ind);
int macMT7530GetAgeTime(u32 *outptr_MaxAgeTime);
int macMT7530SetAgeTime(u32 MaxAgeTime);
int macMT7530GetPortMac(u8 port, u8 *outptr_PortMac);	// "u8 portMac[6];
int macMT7530GetPortStatus(u8 port);

int macMT7530GetMIBCounter(mt7530_switch_api_MibCntType MibCntType, u8 port, u32 *outptr_Cnt);
int macMT7530GetPortTxSuccFramesCnt(u8 port, u32 *outptr_Cnt);
int macMT7530GetPortRxSuccFramesCnt(u8 port, u32 *outptr_Cnt);
int macMT7530GetPortRxDelayFramesCnt(u8 port, u32 *outptr_Cnt);
int macMT7530GetPortTxDelayFramesCnt(u8 port, u32 *outptr_Cnt);
int macMT7530GetPortRxDropFramesCnt(u8 port, u32 *outptr_Cnt);
int macMT7530GetPortTxDropFramesCnt(u8 port, u32 *outptr_Cnt);
int macMT7530GetPortRxLackDropPktCnt(u8 port, u32 *outptr_Cnt);
int macMT7530GetPortTxLackDropPktCnt(u8 port, u32 *outptr_Cnt);
int macMT7530GetPortRxOctetsCnt(u8 port, u32 *outptr_Cnt);
int macMT7530GetPortTxOctetsCnt(u8 port, u32 *outptr_Cnt);
int macMT7530GetPortRxPktsCnt(u8 port, u32 *outptr_Cnt);
int macMT7530GetPortTxPktsCnt(u8 port, u32 *outptr_Cnt);
int macMT7530GetPortRxBroadPktsCnt(u8 port, u32 *outptr_Cnt);
int macMT7530GetPortTxBroadPktsCnt(u8 port, u32 *outptr_Cnt);
int macMT7530GetPortRxMultiPktsCnt(u8 port, u32 *outptr_Cnt);
int macMT7530GetPortTxMultiPktsCnt(u8 port, u32 *outptr_Cnt);
int macMT7530GetPortRxCRCPktsCnt(u8 port, u32 *outptr_Cnt);
int macMT7530GetPortTxCRCPktsCnt(u8 port, u32 *outptr_Cnt);
int macMT7530GetPortRxUnderSizePktsCnt(u8 port, u32 *outptr_Cnt);
int macMT7530GetPortTxUnderSizePktsCnt(u8 port, u32 *outptr_Cnt);
int macMT7530GetPortRxOverSizePktsCnt(u8 port, u32 *outptr_Cnt);
int macMT7530GetPortTxOverSizePktsCnt(u8 port, u32 *outptr_Cnt);
int macMT7530GetPortRx64PktsCnt(u8 port, u32 *outptr_Cnt);
int macMT7530GetPortTx64PktsCnt(u8 port, u32 *outptr_Cnt);
int macMT7530GetPortRx127PktsCnt(u8 port, u32 *outptr_Cnt);
int macMT7530GetPortTx127PktsCnt(u8 port, u32 *outptr_Cnt);
int macMT7530GetPortRx255PktsCnt(u8 port, u32 *outptr_Cnt);
int macMT7530GetPortTx255PktsCnt(u8 port, u32 *outptr_Cnt);
int macMT7530GetPortRx511PktsCnt(u8 port, u32 *outptr_Cnt);
int macMT7530GetPortTx511PktsCnt(u8 port, u32 *outptr_Cnt);
int macMT7530GetPortRx1023PktsCnt(u8 port, u32 *outptr_Cnt);
int macMT7530GetPortTx1023PktsCnt(u8 port, u32 *outptr_Cnt);
int macMT7530GetPortRx1518PktsCnt(u8 port, u32 *outptr_Cnt);
int macMT7530GetPortTx1518PktsCnt(u8 port, u32 *outptr_Cnt);

int macMT7530ResetPMCountersAndTCAs(void);
int macMT7530GetPortRxOctetsFramesCnt(u8 port, u8 flag, u16 tci, u32 *outptr_Cnt);
int macMT7530GetPortTxOctetsFramesCnt(u8 port, u8 flag, u16 tci, u32 *outptr_Cnt);
int macMT7530GetPortRxFramesCnt(u8 port, u8 flag, u16 tci, u32 *outptr_Cnt);
int macMT7530GetPortTxFramesCnt(u8 port, u8 flag, u16 tci, u32 *outptr_Cnt);
int macMT7530GetPortRxBroadFramesCnt(u8 port, u8 flag, u16 tci, u32 *outptr_Cnt);
int macMT7530GetPortTxBroadFramesCnt(u8 port, u8 flag, u16 tci, u32 *outptr_Cnt);
int macMT7530GetPortRxMultiFramesCnt(u8 port, u8 flag, u16 tci, u32 *outptr_Cnt);
int macMT7530GetPortTxMultiFramesCnt(u8 port, u8 flag, u16 tci, u32 *outptr_Cnt);
int macMT7530GetPortRxCRCFramesCnt(u8 port, u8 flag, u16 tci, u32 *outptr_Cnt);
int macMT7530GetPortTxCRCFramesCnt(u8 port, u8 flag, u16 tci, u32 *outptr_Cnt);
int macMT7530GetPortRxUnderSizeFramesCnt(u8 port, u8 flag, u16 tci, u32 *outptr_Cnt);
int macMT7530GetPortTxUnderSizeFramesCnt(u8 port, u8 flag, u16 tci, u32 *outptr_Cnt);
int macMT7530GetPortRxOverSizeFramesCnt(u8 port, u8 flag, u16 tci, u32 *outptr_Cnt);
int macMT7530GetPortTxOverSizeFramesCnt(u8 port, u8 flag, u16 tci, u32 *outptr_Cnt);
int macMT7530GetPortRx64FramesCnt(u8 port, u8 flag, u16 tci, u32 *outptr_Cnt);
int macMT7530GetPortTx64FramesCnt(u8 port, u8 flag, u16 tci, u32 *outptr_Cnt);
int macMT7530GetPortRx127FramesCnt(u8 port, u8 flag, u16 tci, u32 *outptr_Cnt);
int macMT7530GetPortTx127FramesCnt(u8 port, u8 flag, u16 tci, u32 *outptr_Cnt);
int macMT7530GetPortRx255FramesCnt(u8 port, u8 flag, u16 tci, u32 *outptr_Cnt);
int macMT7530GetPortTx255FramesCnt(u8 port, u8 flag, u16 tci, u32 *outptr_Cnt);
int macMT7530GetPortRx511FramesCnt(u8 port, u8 flag, u16 tci, u32 *outptr_Cnt);
int macMT7530GetPortTx511FramesCnt(u8 port, u8 flag, u16 tci, u32 *outptr_Cnt);
int macMT7530GetPortRx1023FramesCnt(u8 port, u8 flag, u16 tci, u32 *outptr_Cnt);
int macMT7530GetPortTx1023FramesCnt(u8 port, u8 flag, u16 tci, u32 *outptr_Cnt);
int macMT7530GetPortRx1518FramesCnt(u8 port, u8 flag, u16 tci, u32 *outptr_Cnt);
int macMT7530GetPortTx1518FramesCnt(u8 port, u8 flag, u16 tci, u32 *outptr_Cnt);

int macMT7530GetMLDQueryProcess(u8 port, u8 *upStatus, u8 *downStatus);
int macMT7530SetMLDQueryProcess(u8 port, u8 upStatus, u8 downStatus);

/************** Kenny/Reid *************/
int macMT7530SetQueuePriority(u16 priority, u8 queueId);
int macMT7530GetMaximumQueueSize(u8 queueId);
int macMT7530SetAllocatedQueueSize(u16 AllocatedQueueSize, u8 queueId);
int macMT7530GetAllocatedQueueSize(u8 queueId);
int macMT7530GetDiscardBlockCounter(u8 queueId);
int macMT7530SetWeight(u8 weight, u8 queueId, u8 port);
int macMT7530GetWeight(u8 queueId, u8 port);
int macMT7530SetBackPressure(mt7530_switch_api_backPressure_t *backPressure_p, u8 queueId, u8 port);
int macMT7530GetBackPressure(mt7530_switch_api_backPressure_t *backPressure_p, u8 queueId, u8 port);
int macMT7530SetDropPolicy(u8 port, u8 queueId, mt7530_switch_DropPolicy_t *DropPolicy);
int macMT7530GetDropPolicy(u8 port, u8 queueId, mt7530_switch_DropPolicy_t *outptr_DropPolicy);
int macMT7530SetTrafficDescriptor(u8 port, mt7530_switch_api_trafficDescriptor_t *trafficDescriptor_p);
int macMT7530GetTrafficDescriptor(u8 port, mt7530_switch_api_trafficDescriptor_t *outptr_trafficDescriptor_p);
int macMT7530CleanTrafficDescriptor(u8 port, u8 direction);

/************** Lisa *************/
int macMT7530SetAutoDetection(u8 AutoDetction, u8 port);
int macMT7530GetAutoDetection(u8 *outptr_AutoDetction, u8 port);
int macMT7530SetLoopbackConf(u8 enable, u8 port);
int macMT7530GetLoopbackConf(u8 *outptr_mode, u8 port);
int macMT7530GetConfigurationStatus(u8 port);
int macMT7530SetMaxFrameSize(u16 MaxFrameSize, u8 port);
int macMT7530GetMaxFrameSize(u16 *outptr_MaxFrameSize, u8 port);
int macMT7530SetDTEDCEInd(u8 ind, u8 port);
int macMT7530GetDTEDCEInd(u8 *outptr_ind, u8 port);
int macMT7530SetPauseTime(u16 pauseTime, u8 port);
int macMT7530GetPauseTime(u16 *outptr_pauseTime, u8 port);

int macMT7530GetFCSErrors(u8 port, u32 *outptr_Cnt);
int macMT7530GetExcessiveCollisionCounter(u8 port, u32 *outptr_Cnt);
int macMT7530GetLateCollisionCounter(u8 port, u32 *outptr_Cnt);
int macMT7530GetFramesTooLong(u8 port, u32 *outptr_Cnt);
int macMT7530GetBufferOverflowsRx(u8 port, u32 *outptr_Cnt);
int macMT7530GetBufferOverflowsTx(u8 port, u32 *outptr_Cnt);
int macMT7530GetSingleCollisionFrameCounter(u8 port, u32 *outptr_Cnt);
int macMT7530GetMultipleCollisionsFrameCounter(u8 port, u32 *outptr_Cnt);
int macMT7530GetSQECounter(u8 port, u32 *outptr_Cnt);
int macMT7530GetDeferredTxCounter(u8 port, u32 *outptr_Cnt);
int macMT7530GetInternalMACTxErrorCounter(u8 port, u32 *outptr_Cnt);
int macMT7530GetCarrierSenseErrorCounter(u8 port, u32 *outptr_Cnt);
int macMT7530GetAlignmentErrorCounter(u8 port, u32 *outptr_Cnt);
int macMT7530GetInternalMACRxErrorCounter(u8 port, u32 *outptr_Cnt);
int macMT7530GetFragments(u8 port, u32 *outptr_Cnt);
int macMT7530GetJabbers(u8 port, u32 *outptr_Cnt);

/************** Lightman *************/
int macMT7530GetPortMacLimit(u8 port);
int macMT7530SetPortMacLimit(u8 port, u32 cnt);
int macMT7530SetPortSpeedMode(u8 port, u8 mode);
int macMT7530GetPortRxPacketsDiscardsCnt(u8 port, u32 *outptr_Cnt);
int macMT7530GetPortTxPacketsDiscardsCnt(u8 port, u32 *outptr_Cnt);
int macMT7530GetPortChangedCnt(u8 port, u32 *outptr_Cnt);
int macMT7530GetPortPause(u8 port);
int macMT7530SetPortPause(u8 port, u8 enable);
int macMT7530GetPortPolicingEnable(u8 port);
int macMT7530SetPortPolicingEnable(u8 port, u8 enable);
int macMT7530GetPortPolicing(u8 port, u32 *outptr_cir, u32 *outptr_cbs, u32 *outptr_ebs);
int macMT7530SetPortPolicing(u8 port, u32 cir, u32 cbs, u32 ebs);
int macMT7530GetPortRatelimitingEnable(u8 port);
int macMT7530SetPortRatelimitingEnable(u8 port, u8 enable);
int macMT7530GetPortRatelimiting(u8 port, u32 *outptr_cir, u32 *outptr_pir);
int macMT7530SetPortRatelimiting(u8 port, u32 cir, u32 pir);
int macMT7530GetPortLoopDetect(u8 port);
int macMT7530SetPortLoopDetect(u8 port, u8 enable);
int macMT7530SetPortDisableLooped(u8 port, u8 enable);
int macMT7530GetPortActive(u8 port);
int macMT7530SetPortActive(u8 port, u8 enable);
int macMT7530GetPortAutoNegState(u8 port);
int macMT7530PortAutoNegActive(u8 port, u8 enable);
int macMT7530PortAutoNegRestartAutoConfig(u8 port);
int macMT7530GetEthPortAutoNegFailure(u8 port);
int macMT7530GetEthPortLos(u8 port);
int macMT7530GetEthPortFailure(u8 port);
int macMT7530GetEthPortCongestion(u8 port);

/************** John *************/
int macMT7530GetTxTimestamp(mt7530_switch_api_timestamp_fifo *tx_ts);
int macMT7530GetRxTimestamp(mt7530_switch_api_timestamp_fifo *rx_ts);
int macMT7530GetCurrTime(mt7530_switch_api_timestamp *ts);
int macMT7530SetCurrTime(int type, mt7530_switch_api_timestamp *ts);
int macMT7530SSetOffset(int opt, mt7530_switch_api_timestamp *ts);
int macMT7530GetPTPState(int *outptr_EnablePort);
int macMT7530SetPTPState(int EnablePort);

/************** Lidong Hu *************/
int macMT7530VLan_Entry_Enable(u16 vid, u8 sw);
int macMT7530VLan_Entry_SetETag(u16 vid, u8 port, u8 etag);
int macMT7530VLan_Entry_GetETag(u16 vid, u8 port, u8* outptr_etag);
int macMT7530VLan_Entry_SetSTag(u16 vid, u8 port, u8 stag);
int macMT7530VLan_Entry_GetSTag(u16 vid, u8 port, u8* outptr_stag);
int macMT7530VLan_Port_AddSTag(u8 port, u8 stag, u16 vid);
int macMT7530VLan_Entry_SetETagMode(u16 vid, u8 etag_mode);

// =========== internal API start from ID 0x1000 ============
int macMT7530EnableMIBCounter(u32 enable);
int macMT7530ClearMIBCounter(void);
int macMT7530SetRxOctMode(mt7530_switch_api_RxTxOctMode mode);
int macMT7530SetTxOctMode(mt7530_switch_api_RxTxOctMode mode);
int macMT7530SetBxPktMode(mt7530_switch_api_BxPktMode mode);




// =========== debug API start from ID 0x7F00 =============
int macMT7530APIDbgDumpEn(u32 DbgDump_enable);

int macMT7530doP6Cal(void);




/************************************************************************
*                        P U B L I C   D A T A
*************************************************************************
*/




#endif // #ifdef TCSUPPORT_MT7530_SWITCH_API

#endif // #ifndef _GMAC_MT7530_API_H_

