/*
 * Copyright (C) 2010 Realtek Semiconductor Corp.
 * All Rights Reserved.
 *
 * This program is the proprietary software of Realtek Semiconductor
 * Corporation and/or its licensors, and only be used, duplicated,
 * modified or distributed under the authorized license from Realtek.
 *
 * ANY USE OF THE SOFTWARE OTHER THAN AS AUTHORIZED UNDER
 * THIS LICENSE OR COPYRIGHT LAW IS PROHIBITED.
 *
 * $Revision: 28620 $
 * $Date: 2012-05-07 13:16:01 +0800 (星期一, 07 五月 2012) $
 *
 * Purpose : RTK switch high-level API for RTL8367/RTL8367B
 * Feature : Here is a list of all functions and variables in this module.
 *
 */
#include <linux/string.h>
#include <linux/errno.h>
#include "rtl8367b_asicdrv_acl.h"
#include "rtl8367b_asicdrv.h"
#include "rtl8367b_asicdrv_dot1x.h"
#include "rtl8367b_asicdrv_qos.h"
#include "rtl8367b_asicdrv_scheduling.h"
#include "rtl8367b_asicdrv_fc.h"
#include "rtl8367b_asicdrv_port.h"
#include "rtl8367b_asicdrv_phy.h"
#include "rtl8367b_asicdrv_igmp.h"
#include "rtl8367b_asicdrv_unknownMulticast.h"
#include "rtl8367b_asicdrv_rma.h"
#include "rtl8367b_asicdrv_vlan.h"
#include "rtl8367b_asicdrv_lut.h"
#include "rtl8367b_asicdrv_led.h"
#include "rtl8367b_asicdrv_svlan.h"
#include "rtl8367b_asicdrv_meter.h"
#include "rtl8367b_asicdrv_inbwctrl.h"
#include "rtl8367b_asicdrv_storm.h"
#include "rtl8367b_asicdrv_misc.h"
#include "rtl8367b_asicdrv_portIsolation.h"
#include "rtl8367b_asicdrv_cputag.h"
#include "rtl8367b_asicdrv_trunking.h"
#include "rtl8367b_asicdrv_mirror.h"
#include "rtl8367b_asicdrv_mib.h"
#include "rtl8367b_asicdrv_interrupt.h"
#include "rtl8367b_asicdrv_green.h"
#include "rtl8367b_asicdrv_eee.h"
#include "rtl8367b_asicdrv_eav.h"
#include "rtl8367b_asicdrv_hsb.h"
#include "rtk_api.h"
#include "rtk_api_ext.h"
#include "rtk_error.h"


//#define DELAY_800MS_FOR_CHIP_STATABLE() {  }

unsigned short ChipData10[][2]= {
{0x1B03, 0x0876}, {0x1200, 0x7FC4}, {0x0301, 0x0026}, {0x1722, 0x0E14},
{0x205F, 0x0002}, {0x2059, 0x1A00}, {0x205F, 0x0000}, {0x207F, 0x0002},
{0x2077, 0x0000}, {0x2078, 0x0000}, {0x2079, 0x0000}, {0x207A, 0x0000},
{0x207B, 0x0000}, {0x207F, 0x0000}, {0x205F, 0x0002}, {0x2053, 0x0000},
{0x2054, 0x0000}, {0x2055, 0x0000}, {0x2056, 0x0000}, {0x2057, 0x0000},
{0x205F, 0x0000}, {0x12A4, 0x110A}, {0x12A6, 0x150A}, {0x13F1, 0x0013},
{0x13F4, 0x0010}, {0x13F5, 0x0000}, {0x0018, 0x0F00}, {0x0038, 0x0F00},
{0x0058, 0x0F00}, {0x0078, 0x0F00}, {0x0098, 0x0F00}, {0x12B6, 0x0C02},
{0x12B7, 0x030F}, {0x12B8, 0x11FF}, {0x12BC, 0x0004}, {0x1362, 0x0115},
{0x1363, 0x0002}, {0x1363, 0x0000}, {0x133F, 0x0030}, {0x133E, 0x000E},
{0x221F, 0x0007}, {0x221E, 0x002D}, {0x2218, 0xF030}, {0x221F, 0x0007},
{0x221E, 0x0023}, {0x2216, 0x0005}, {0x2215, 0x00B9}, {0x2219, 0x0044},
{0x2215, 0x00BA}, {0x2219, 0x0020}, {0x2215, 0x00BB}, {0x2219, 0x00C1},
{0x2215, 0x0148}, {0x2219, 0x0096}, {0x2215, 0x016E}, {0x2219, 0x0026},
{0x2216, 0x0000}, {0x2216, 0x0000}, {0x221E, 0x002D}, {0x2218, 0xF010},
{0x221F, 0x0007}, {0x221E, 0x0020}, {0x2215, 0x0D00}, {0x221F, 0x0000},
{0x221F, 0x0000}, {0x2217, 0x2160}, {0x221F, 0x0001}, {0x2210, 0xF25E},
{0x221F, 0x0007}, {0x221E, 0x0042}, {0x2215, 0x0F00}, {0x2215, 0x0F00},
{0x2216, 0x7408}, {0x2215, 0x0E00}, {0x2215, 0x0F00}, {0x2215, 0x0F01},
{0x2216, 0x4000}, {0x2215, 0x0E01}, {0x2215, 0x0F01}, {0x2215, 0x0F02},
{0x2216, 0x9400}, {0x2215, 0x0E02}, {0x2215, 0x0F02}, {0x2215, 0x0F03},
{0x2216, 0x7408}, {0x2215, 0x0E03}, {0x2215, 0x0F03}, {0x2215, 0x0F04},
{0x2216, 0x4008}, {0x2215, 0x0E04}, {0x2215, 0x0F04}, {0x2215, 0x0F05},
{0x2216, 0x9400}, {0x2215, 0x0E05}, {0x2215, 0x0F05}, {0x2215, 0x0F06},
{0x2216, 0x0803}, {0x2215, 0x0E06}, {0x2215, 0x0F06}, {0x2215, 0x0D00},
{0x2215, 0x0100}, {0x221F, 0x0001}, {0x2210, 0xF05E}, {0x221F, 0x0000},
{0x2217, 0x2100}, {0x221F, 0x0000}, {0x220D, 0x0003}, {0x220E, 0x0015},
{0x220D, 0x4003}, {0x220E, 0x0006}, {0x221F, 0x0000}, {0x2200, 0x1340},
{0x133F, 0x0010}, {0x12A0, 0x0058}, {0x12A1, 0x0058}, {0x133E, 0x000E},
{0x133F, 0x0030}, {0x221F, 0x0000}, {0x2210, 0x0166}, {0x221F, 0x0000},
{0x133E, 0x000E}, {0x133F, 0x0010}, {0x133F, 0x0030}, {0x133E, 0x000E},
{0x221F, 0x0005}, {0x2205, 0xFFF6}, {0x2206, 0x0080}, {0x2205, 0x8B6E},
{0x2206, 0x0000}, {0x220F, 0x0100}, {0x2205, 0x8000}, {0x2206, 0x0280},
{0x2206, 0x28F7}, {0x2206, 0x00E0}, {0x2206, 0xFFF7}, {0x2206, 0xA080},
{0x2206, 0x02AE}, {0x2206, 0xF602}, {0x2206, 0x0153}, {0x2206, 0x0201},
{0x2206, 0x6602}, {0x2206, 0x80B9}, {0x2206, 0xE08B}, {0x2206, 0x8CE1},
{0x2206, 0x8B8D}, {0x2206, 0x1E01}, {0x2206, 0xE18B}, {0x2206, 0x8E1E},
{0x2206, 0x01A0}, {0x2206, 0x00E7}, {0x2206, 0xAEDB}, {0x2206, 0xEEE0},
{0x2206, 0x120E}, {0x2206, 0xEEE0}, {0x2206, 0x1300}, {0x2206, 0xEEE0},
{0x2206, 0x2001}, {0x2206, 0xEEE0}, {0x2206, 0x2166}, {0x2206, 0xEEE0},
{0x2206, 0xC463}, {0x2206, 0xEEE0}, {0x2206, 0xC5E8}, {0x2206, 0xEEE0},
{0x2206, 0xC699}, {0x2206, 0xEEE0}, {0x2206, 0xC7C2}, {0x2206, 0xEEE0},
{0x2206, 0xC801}, {0x2206, 0xEEE0}, {0x2206, 0xC913}, {0x2206, 0xEEE0},
{0x2206, 0xCA30}, {0x2206, 0xEEE0}, {0x2206, 0xCB3E}, {0x2206, 0xEEE0},
{0x2206, 0xDCE1}, {0x2206, 0xEEE0}, {0x2206, 0xDD00}, {0x2206, 0xEEE2},
{0x2206, 0x0001}, {0x2206, 0xEEE2}, {0x2206, 0x0100}, {0x2206, 0xEEE4},
{0x2206, 0x8860}, {0x2206, 0xEEE4}, {0x2206, 0x8902}, {0x2206, 0xEEE4},
{0x2206, 0x8C00}, {0x2206, 0xEEE4}, {0x2206, 0x8D30}, {0x2206, 0xEEEA},
{0x2206, 0x1480}, {0x2206, 0xEEEA}, {0x2206, 0x1503}, {0x2206, 0xEEEA},
{0x2206, 0xC600}, {0x2206, 0xEEEA}, {0x2206, 0xC706}, {0x2206, 0xEE85},
{0x2206, 0xEE00}, {0x2206, 0xEE85}, {0x2206, 0xEF00}, {0x2206, 0xEE8B},
{0x2206, 0x6750}, {0x2206, 0xEE8B}, {0x2206, 0x6632}, {0x2206, 0xEE8A},
{0x2206, 0xD448}, {0x2206, 0xEE8A}, {0x2206, 0xD548}, {0x2206, 0xEE8A},
{0x2206, 0xD649}, {0x2206, 0xEE8A}, {0x2206, 0xD7F8}, {0x2206, 0xEE8B},
{0x2206, 0x85E2}, {0x2206, 0xEE8B}, {0x2206, 0x8700}, {0x2206, 0xEEFF},
{0x2206, 0xF600}, {0x2206, 0xEEFF}, {0x2206, 0xF7FC}, {0x2206, 0x04F8},
{0x2206, 0xE08B}, {0x2206, 0x8EAD}, {0x2206, 0x2023}, {0x2206, 0xF620},
{0x2206, 0xE48B}, {0x2206, 0x8E02}, {0x2206, 0x2877}, {0x2206, 0x0225},
{0x2206, 0xC702}, {0x2206, 0x26A1}, {0x2206, 0x0281}, {0x2206, 0xB302},
{0x2206, 0x8496}, {0x2206, 0x0202}, {0x2206, 0xA102}, {0x2206, 0x27F1},
{0x2206, 0x0228}, {0x2206, 0xF902}, {0x2206, 0x2AA0}, {0x2206, 0x0282},
{0x2206, 0xB8E0}, {0x2206, 0x8B8E}, {0x2206, 0xAD21}, {0x2206, 0x08F6},
{0x2206, 0x21E4}, {0x2206, 0x8B8E}, {0x2206, 0x0202}, {0x2206, 0x80E0},
{0x2206, 0x8B8E}, {0x2206, 0xAD22}, {0x2206, 0x05F6}, {0x2206, 0x22E4},
{0x2206, 0x8B8E}, {0x2206, 0xE08B}, {0x2206, 0x8EAD}, {0x2206, 0x2305},
{0x2206, 0xF623}, {0x2206, 0xE48B}, {0x2206, 0x8EE0}, {0x2206, 0x8B8E},
{0x2206, 0xAD24}, {0x2206, 0x08F6}, {0x2206, 0x24E4}, {0x2206, 0x8B8E},
{0x2206, 0x0227}, {0x2206, 0x6AE0}, {0x2206, 0x8B8E}, {0x2206, 0xAD25},
{0x2206, 0x05F6}, {0x2206, 0x25E4}, {0x2206, 0x8B8E}, {0x2206, 0xE08B},
{0x2206, 0x8EAD}, {0x2206, 0x260B}, {0x2206, 0xF626}, {0x2206, 0xE48B},
{0x2206, 0x8E02}, {0x2206, 0x830D}, {0x2206, 0x021D}, {0x2206, 0x6BE0},
{0x2206, 0x8B8E}, {0x2206, 0xAD27}, {0x2206, 0x05F6}, {0x2206, 0x27E4},
{0x2206, 0x8B8E}, {0x2206, 0x0281}, {0x2206, 0x4402}, {0x2206, 0x045C},
{0x2206, 0xFC04}, {0x2206, 0xF8E0}, {0x2206, 0x8B83}, {0x2206, 0xAD23},
{0x2206, 0x30E0}, {0x2206, 0xE022}, {0x2206, 0xE1E0}, {0x2206, 0x2359},
{0x2206, 0x02E0}, {0x2206, 0x85EF}, {0x2206, 0xE585}, {0x2206, 0xEFAC},
{0x2206, 0x2907}, {0x2206, 0x1F01}, {0x2206, 0x9E51}, {0x2206, 0xAD29},
{0x2206, 0x20E0}, {0x2206, 0x8B83}, {0x2206, 0xAD21}, {0x2206, 0x06E1},
{0x2206, 0x8B84}, {0x2206, 0xAD28}, {0x2206, 0x42E0}, {0x2206, 0x8B85},
{0x2206, 0xAD21}, {0x2206, 0x06E1}, {0x2206, 0x8B84}, {0x2206, 0xAD29},
{0x2206, 0x36BF}, {0x2206, 0x34BF}, {0x2206, 0x022C}, {0x2206, 0x31AE},
{0x2206, 0x2EE0}, {0x2206, 0x8B83}, {0x2206, 0xAD21}, {0x2206, 0x10E0},
{0x2206, 0x8B84}, {0x2206, 0xF620}, {0x2206, 0xE48B}, {0x2206, 0x84EE},
{0x2206, 0x8ADA}, {0x2206, 0x00EE}, {0x2206, 0x8ADB}, {0x2206, 0x00E0},
{0x2206, 0x8B85}, {0x2206, 0xAD21}, {0x2206, 0x0CE0}, {0x2206, 0x8B84},
{0x2206, 0xF621}, {0x2206, 0xE48B}, {0x2206, 0x84EE}, {0x2206, 0x8B72},
{0x2206, 0xFFBF}, {0x2206, 0x34C2}, {0x2206, 0x022C}, {0x2206, 0x31FC},
{0x2206, 0x04F8}, {0x2206, 0xFAEF}, {0x2206, 0x69E0}, {0x2206, 0x8B85},
{0x2206, 0xAD21}, {0x2206, 0x42E0}, {0x2206, 0xE022}, {0x2206, 0xE1E0},
{0x2206, 0x2358}, {0x2206, 0xC059}, {0x2206, 0x021E}, {0x2206, 0x01E1},
{0x2206, 0x8B72}, {0x2206, 0x1F10}, {0x2206, 0x9E2F}, {0x2206, 0xE48B},
{0x2206, 0x72AD}, {0x2206, 0x2123}, {0x2206, 0xE18B}, {0x2206, 0x84F7},
{0x2206, 0x29E5}, {0x2206, 0x8B84}, {0x2206, 0xAC27}, {0x2206, 0x10AC},
{0x2206, 0x2605}, {0x2206, 0x0205}, {0x2206, 0x23AE}, {0x2206, 0x1602},
{0x2206, 0x0535}, {0x2206, 0x0282}, {0x2206, 0x30AE}, {0x2206, 0x0E02},
{0x2206, 0x056A}, {0x2206, 0x0282}, {0x2206, 0x75AE}, {0x2206, 0x0602},
{0x2206, 0x04DC}, {0x2206, 0x0282}, {0x2206, 0x04EF}, {0x2206, 0x96FE},
{0x2206, 0xFC04}, {0x2206, 0xF8F9}, {0x2206, 0xE08B}, {0x2206, 0x87AD},
{0x2206, 0x2321}, {0x2206, 0xE0EA}, {0x2206, 0x14E1}, {0x2206, 0xEA15},
{0x2206, 0xAD26}, {0x2206, 0x18F6}, {0x2206, 0x27E4}, {0x2206, 0xEA14},
{0x2206, 0xE5EA}, {0x2206, 0x15F6}, {0x2206, 0x26E4}, {0x2206, 0xEA14},
{0x2206, 0xE5EA}, {0x2206, 0x15F7}, {0x2206, 0x27E4}, {0x2206, 0xEA14},
{0x2206, 0xE5EA}, {0x2206, 0x15FD}, {0x2206, 0xFC04}, {0x2206, 0xF8F9},
{0x2206, 0xE08B}, {0x2206, 0x87AD}, {0x2206, 0x233A}, {0x2206, 0xAD22},
{0x2206, 0x37E0}, {0x2206, 0xE020}, {0x2206, 0xE1E0}, {0x2206, 0x21AC},
{0x2206, 0x212E}, {0x2206, 0xE0EA}, {0x2206, 0x14E1}, {0x2206, 0xEA15},
{0x2206, 0xF627}, {0x2206, 0xE4EA}, {0x2206, 0x14E5}, {0x2206, 0xEA15},
{0x2206, 0xE2EA}, {0x2206, 0x12E3}, {0x2206, 0xEA13}, {0x2206, 0x5A8F},
{0x2206, 0x6A20}, {0x2206, 0xE6EA}, {0x2206, 0x12E7}, {0x2206, 0xEA13},
{0x2206, 0xF726}, {0x2206, 0xE4EA}, {0x2206, 0x14E5}, {0x2206, 0xEA15},
{0x2206, 0xF727}, {0x2206, 0xE4EA}, {0x2206, 0x14E5}, {0x2206, 0xEA15},
{0x2206, 0xFDFC}, {0x2206, 0x04F8}, {0x2206, 0xF9E0}, {0x2206, 0x8B87},
{0x2206, 0xAD23}, {0x2206, 0x38AD}, {0x2206, 0x2135}, {0x2206, 0xE0E0},
{0x2206, 0x20E1}, {0x2206, 0xE021}, {0x2206, 0xAC21}, {0x2206, 0x2CE0},
{0x2206, 0xEA14}, {0x2206, 0xE1EA}, {0x2206, 0x15F6}, {0x2206, 0x27E4},
{0x2206, 0xEA14}, {0x2206, 0xE5EA}, {0x2206, 0x15E2}, {0x2206, 0xEA12},
{0x2206, 0xE3EA}, {0x2206, 0x135A}, {0x2206, 0x8FE6}, {0x2206, 0xEA12},
{0x2206, 0xE7EA}, {0x2206, 0x13F7}, {0x2206, 0x26E4}, {0x2206, 0xEA14},
{0x2206, 0xE5EA}, {0x2206, 0x15F7}, {0x2206, 0x27E4}, {0x2206, 0xEA14},
{0x2206, 0xE5EA}, {0x2206, 0x15FD}, {0x2206, 0xFC04}, {0x2206, 0xF8FA},
{0x2206, 0xEF69}, {0x2206, 0xE08B}, {0x2206, 0x86AD}, {0x2206, 0x2146},
{0x2206, 0xE0E0}, {0x2206, 0x22E1}, {0x2206, 0xE023}, {0x2206, 0x58C0},
{0x2206, 0x5902}, {0x2206, 0x1E01}, {0x2206, 0xE18B}, {0x2206, 0x651F},
{0x2206, 0x109E}, {0x2206, 0x33E4}, {0x2206, 0x8B65}, {0x2206, 0xAD21},
{0x2206, 0x22AD}, {0x2206, 0x272A}, {0x2206, 0xD400}, {0x2206, 0x01BF},
{0x2206, 0x34F2}, {0x2206, 0x022C}, {0x2206, 0xA2BF}, {0x2206, 0x34F5},
{0x2206, 0x022C}, {0x2206, 0xE0E0}, {0x2206, 0x8B67}, {0x2206, 0x1B10},
{0x2206, 0xAA14}, {0x2206, 0xE18B}, {0x2206, 0x660D}, {0x2206, 0x1459},
{0x2206, 0x0FAE}, {0x2206, 0x05E1}, {0x2206, 0x8B66}, {0x2206, 0x590F},
{0x2206, 0xBF85}, {0x2206, 0x6102}, {0x2206, 0x2CA2}, {0x2206, 0xEF96},
{0x2206, 0xFEFC}, {0x2206, 0x04F8}, {0x2206, 0xF9FA}, {0x2206, 0xFBEF},
{0x2206, 0x79E2}, {0x2206, 0x8AD2}, {0x2206, 0xAC19}, {0x2206, 0x2DE0},
{0x2206, 0xE036}, {0x2206, 0xE1E0}, {0x2206, 0x37EF}, {0x2206, 0x311F},
{0x2206, 0x325B}, {0x2206, 0x019E}, {0x2206, 0x1F7A}, {0x2206, 0x0159},
{0x2206, 0x019F}, {0x2206, 0x0ABF}, {0x2206, 0x348E}, {0x2206, 0x022C},
{0x2206, 0x31F6}, {0x2206, 0x06AE}, {0x2206, 0x0FF6}, {0x2206, 0x0302},
{0x2206, 0x0470}, {0x2206, 0xF703}, {0x2206, 0xF706}, {0x2206, 0xBF34},
{0x2206, 0x9302}, {0x2206, 0x2C31}, {0x2206, 0xAC1A}, {0x2206, 0x25E0},
{0x2206, 0xE022}, {0x2206, 0xE1E0}, {0x2206, 0x23EF}, {0x2206, 0x300D},
{0x2206, 0x311F}, {0x2206, 0x325B}, {0x2206, 0x029E}, {0x2206, 0x157A},
{0x2206, 0x0258}, {0x2206, 0xC4A0}, {0x2206, 0x0408}, {0x2206, 0xBF34},
{0x2206, 0x9E02}, {0x2206, 0x2C31}, {0x2206, 0xAE06}, {0x2206, 0xBF34},
{0x2206, 0x9C02}, {0x2206, 0x2C31}, {0x2206, 0xAC1B}, {0x2206, 0x4AE0},
{0x2206, 0xE012}, {0x2206, 0xE1E0}, {0x2206, 0x13EF}, {0x2206, 0x300D},
{0x2206, 0x331F}, {0x2206, 0x325B}, {0x2206, 0x1C9E}, {0x2206, 0x3AEF},
{0x2206, 0x325B}, {0x2206, 0x1C9F}, {0x2206, 0x09BF}, {0x2206, 0x3498},
{0x2206, 0x022C}, {0x2206, 0x3102}, {0x2206, 0x83C5}, {0x2206, 0x5A03},
{0x2206, 0x0D03}, {0x2206, 0x581C}, {0x2206, 0x1E20}, {0x2206, 0x0207},
{0x2206, 0xA0A0}, {0x2206, 0x000E}, {0x2206, 0x0284}, {0x2206, 0x17AD},
{0x2206, 0x1817}, {0x2206, 0xBF34}, {0x2206, 0x9A02}, {0x2206, 0x2C31},
{0x2206, 0xAE0F}, {0x2206, 0xBF34}, {0x2206, 0xC802}, {0x2206, 0x2C31},
{0x2206, 0xBF34}, {0x2206, 0xC502}, {0x2206, 0x2C31}, {0x2206, 0x0284},
{0x2206, 0x52E6}, {0x2206, 0x8AD2}, {0x2206, 0xEF97}, {0x2206, 0xFFFE},
{0x2206, 0xFDFC}, {0x2206, 0x04F8}, {0x2206, 0xBF34}, {0x2206, 0xDA02},
{0x2206, 0x2CE0}, {0x2206, 0xE58A}, {0x2206, 0xD3BF}, {0x2206, 0x34D4},
{0x2206, 0x022C}, {0x2206, 0xE00C}, {0x2206, 0x1159}, {0x2206, 0x02E0},
{0x2206, 0x8AD3}, {0x2206, 0x1E01}, {0x2206, 0xE48A}, {0x2206, 0xD3D1},
{0x2206, 0x00BF}, {0x2206, 0x34DA}, {0x2206, 0x022C}, {0x2206, 0xA2D1},
{0x2206, 0x01BF}, {0x2206, 0x34D4}, {0x2206, 0x022C}, {0x2206, 0xA2BF},
{0x2206, 0x34CB}, {0x2206, 0x022C}, {0x2206, 0xE0E5}, {0x2206, 0x8ACE},
{0x2206, 0xBF85}, {0x2206, 0x6702}, {0x2206, 0x2CE0}, {0x2206, 0xE58A},
{0x2206, 0xCFBF}, {0x2206, 0x8564}, {0x2206, 0x022C}, {0x2206, 0xE0E5},
{0x2206, 0x8AD0}, {0x2206, 0xBF85}, {0x2206, 0x6A02}, {0x2206, 0x2CE0},
{0x2206, 0xE58A}, {0x2206, 0xD1FC}, {0x2206, 0x04F8}, {0x2206, 0xE18A},
{0x2206, 0xD1BF}, {0x2206, 0x856A}, {0x2206, 0x022C}, {0x2206, 0xA2E1},
{0x2206, 0x8AD0}, {0x2206, 0xBF85}, {0x2206, 0x6402}, {0x2206, 0x2CA2},
{0x2206, 0xE18A}, {0x2206, 0xCFBF}, {0x2206, 0x8567}, {0x2206, 0x022C},
{0x2206, 0xA2E1}, {0x2206, 0x8ACE}, {0x2206, 0xBF34}, {0x2206, 0xCB02},
{0x2206, 0x2CA2}, {0x2206, 0xE18A}, {0x2206, 0xD3BF}, {0x2206, 0x34DA},
{0x2206, 0x022C}, {0x2206, 0xA2E1}, {0x2206, 0x8AD3}, {0x2206, 0x0D11},
{0x2206, 0xBF34}, {0x2206, 0xD402}, {0x2206, 0x2CA2}, {0x2206, 0xFC04},
{0x2206, 0xF9A0}, {0x2206, 0x0405}, {0x2206, 0xE38A}, {0x2206, 0xD4AE},
{0x2206, 0x13A0}, {0x2206, 0x0805}, {0x2206, 0xE38A}, {0x2206, 0xD5AE},
{0x2206, 0x0BA0}, {0x2206, 0x0C05}, {0x2206, 0xE38A}, {0x2206, 0xD6AE},
{0x2206, 0x03E3}, {0x2206, 0x8AD7}, {0x2206, 0xEF13}, {0x2206, 0xBF34},
{0x2206, 0xCB02}, {0x2206, 0x2CA2}, {0x2206, 0xEF13}, {0x2206, 0x0D11},
{0x2206, 0xBF85}, {0x2206, 0x6702}, {0x2206, 0x2CA2}, {0x2206, 0xEF13},
{0x2206, 0x0D14}, {0x2206, 0xBF85}, {0x2206, 0x6402}, {0x2206, 0x2CA2},
{0x2206, 0xEF13}, {0x2206, 0x0D17}, {0x2206, 0xBF85}, {0x2206, 0x6A02},
{0x2206, 0x2CA2}, {0x2206, 0xFD04}, {0x2206, 0xF8E0}, {0x2206, 0x8B85},
{0x2206, 0xAD27}, {0x2206, 0x2DE0}, {0x2206, 0xE036}, {0x2206, 0xE1E0},
{0x2206, 0x37E1}, {0x2206, 0x8B73}, {0x2206, 0x1F10}, {0x2206, 0x9E20},
{0x2206, 0xE48B}, {0x2206, 0x73AC}, {0x2206, 0x200B}, {0x2206, 0xAC21},
{0x2206, 0x0DAC}, {0x2206, 0x250F}, {0x2206, 0xAC27}, {0x2206, 0x0EAE},
{0x2206, 0x0F02}, {0x2206, 0x84CC}, {0x2206, 0xAE0A}, {0x2206, 0x0284},
{0x2206, 0xD1AE}, {0x2206, 0x05AE}, {0x2206, 0x0302}, {0x2206, 0x84D8},
{0x2206, 0xFC04}, {0x2206, 0xEE8B}, {0x2206, 0x6800}, {0x2206, 0x0402},
{0x2206, 0x84E5}, {0x2206, 0x0285}, {0x2206, 0x2804}, {0x2206, 0x0285},
{0x2206, 0x4904}, {0x2206, 0xEE8B}, {0x2206, 0x6800}, {0x2206, 0xEE8B},
{0x2206, 0x6902}, {0x2206, 0x04F8}, {0x2206, 0xF9E0}, {0x2206, 0x8B85},
{0x2206, 0xAD26}, {0x2206, 0x38D0}, {0x2206, 0x0B02}, {0x2206, 0x2B4D},
{0x2206, 0x5882}, {0x2206, 0x7882}, {0x2206, 0x9F2D}, {0x2206, 0xE08B},
{0x2206, 0x68E1}, {0x2206, 0x8B69}, {0x2206, 0x1F10}, {0x2206, 0x9EC8},
{0x2206, 0x10E4}, {0x2206, 0x8B68}, {0x2206, 0xE0E0}, {0x2206, 0x00E1},
{0x2206, 0xE001}, {0x2206, 0xF727}, {0x2206, 0xE4E0}, {0x2206, 0x00E5},
{0x2206, 0xE001}, {0x2206, 0xE2E0}, {0x2206, 0x20E3}, {0x2206, 0xE021},
{0x2206, 0xAD30}, {0x2206, 0xF7F6}, {0x2206, 0x27E4}, {0x2206, 0xE000},
{0x2206, 0xE5E0}, {0x2206, 0x01FD}, {0x2206, 0xFC04}, {0x2206, 0xF8FA},
{0x2206, 0xEF69}, {0x2206, 0xE08B}, {0x2206, 0x86AD}, {0x2206, 0x2212},
{0x2206, 0xE0E0}, {0x2206, 0x14E1}, {0x2206, 0xE015}, {0x2206, 0xAD26},
{0x2206, 0x9CE1}, {0x2206, 0x85E0}, {0x2206, 0xBF85}, {0x2206, 0x6D02},
{0x2206, 0x2CA2}, {0x2206, 0xEF96}, {0x2206, 0xFEFC}, {0x2206, 0x04F8},
{0x2206, 0xFAEF}, {0x2206, 0x69E0}, {0x2206, 0x8B86}, {0x2206, 0xAD22},
{0x2206, 0x09E1}, {0x2206, 0x85E1}, {0x2206, 0xBF85}, {0x2206, 0x6D02},
{0x2206, 0x2CA2}, {0x2206, 0xEF96}, {0x2206, 0xFEFC}, {0x2206, 0x0464},
{0x2206, 0xE48C}, {0x2206, 0xFDE4}, {0x2206, 0x80CA}, {0x2206, 0xE480},
{0x2206, 0x66E0}, {0x2206, 0x8E70}, {0x2206, 0xE076}, {0x2205, 0xE142},
{0x2206, 0x0701}, {0x2205, 0xE140}, {0x2206, 0x0405}, {0x220F, 0x0000},
{0x221F, 0x0000}, {0x2200, 0x1340}, {0x133E, 0x000E}, {0x133F, 0x0010},
{0x13EB, 0x11BB}, {0x2097, 0xA11F}, 
 };

unsigned short ChipData11[][2]= {
{0x1B03, 0x0876}, {0x1200, 0x7FC4}, {0x1305, 0xC000}, {0x121E, 0x03CA},
{0x1233, 0x0352}, {0x1234, 0x0064}, {0x1237, 0x0096}, {0x1238, 0x0078},
{0x1239, 0x0084}, {0x123A, 0x0030}, {0x205F, 0x0002}, {0x2059, 0x1A00},
{0x205F, 0x0000}, {0x207F, 0x0002}, {0x2077, 0x0000}, {0x2078, 0x0000},
{0x2079, 0x0000}, {0x207A, 0x0000}, {0x207B, 0x0000}, {0x207F, 0x0000},
{0x205F, 0x0002}, {0x2053, 0x0000}, {0x2054, 0x0000}, {0x2055, 0x0000},
{0x2056, 0x0000}, {0x2057, 0x0000}, {0x205F, 0x0000}, {0x133F, 0x0030},
{0x133E, 0x000E}, {0x221F, 0x0005}, {0x2205, 0x8B86}, {0x2206, 0x800E},
{0x221F, 0x0000}, {0x133F, 0x0010}, {0x12A3, 0x2200}, {0x6107, 0xE58B},
{0x6103, 0xA970}, {0x0018, 0x0F00}, {0x0038, 0x0F00}, {0x0058, 0x0F00},
{0x0078, 0x0F00}, {0x0098, 0x0F00}, {0x133F, 0x0030}, {0x133E, 0x000E},
{0x221F, 0x0005}, {0x2205, 0x8B6E}, {0x2206, 0x0000}, {0x220F, 0x0100},
{0x2205, 0xFFF6}, {0x2206, 0x0080}, {0x2205, 0x8000}, {0x2206, 0x0280},
{0x2206, 0x2BF7}, {0x2206, 0x00E0}, {0x2206, 0xFFF7}, {0x2206, 0xA080},
{0x2206, 0x02AE}, {0x2206, 0xF602}, {0x2206, 0x0153}, {0x2206, 0x0201},
{0x2206, 0x6602}, {0x2206, 0x8044}, {0x2206, 0x0201}, {0x2206, 0x7CE0},
{0x2206, 0x8B8C}, {0x2206, 0xE18B}, {0x2206, 0x8D1E}, {0x2206, 0x01E1},
{0x2206, 0x8B8E}, {0x2206, 0x1E01}, {0x2206, 0xA000}, {0x2206, 0xE4AE},
{0x2206, 0xD8EE}, {0x2206, 0x85C0}, {0x2206, 0x00EE}, {0x2206, 0x85C1},
{0x2206, 0x00EE}, {0x2206, 0x8AFC}, {0x2206, 0x07EE}, {0x2206, 0x8AFD},
{0x2206, 0x73EE}, {0x2206, 0xFFF6}, {0x2206, 0x00EE}, {0x2206, 0xFFF7},
{0x2206, 0xFC04}, {0x2206, 0xF8E0}, {0x2206, 0x8B8E}, {0x2206, 0xAD20},
{0x2206, 0x0302}, {0x2206, 0x8050}, {0x2206, 0xFC04}, {0x2206, 0xF8F9},
{0x2206, 0xE08B}, {0x2206, 0x85AD}, {0x2206, 0x2548}, {0x2206, 0xE08A},
{0x2206, 0xE4E1}, {0x2206, 0x8AE5}, {0x2206, 0x7C00}, {0x2206, 0x009E},
{0x2206, 0x35EE}, {0x2206, 0x8AE4}, {0x2206, 0x00EE}, {0x2206, 0x8AE5},
{0x2206, 0x00E0}, {0x2206, 0x8AFC}, {0x2206, 0xE18A}, {0x2206, 0xFDE2},
{0x2206, 0x85C0}, {0x2206, 0xE385}, {0x2206, 0xC102}, {0x2206, 0x2DAC},
{0x2206, 0xAD20}, {0x2206, 0x12EE}, {0x2206, 0x8AE4}, {0x2206, 0x03EE},
{0x2206, 0x8AE5}, {0x2206, 0xB7EE}, {0x2206, 0x85C0}, {0x2206, 0x00EE},
{0x2206, 0x85C1}, {0x2206, 0x00AE}, {0x2206, 0x1115}, {0x2206, 0xE685},
{0x2206, 0xC0E7}, {0x2206, 0x85C1}, {0x2206, 0xAE08}, {0x2206, 0xEE85},
{0x2206, 0xC000}, {0x2206, 0xEE85}, {0x2206, 0xC100}, {0x2206, 0xFDFC},
{0x2206, 0x0400}, {0x2205, 0xE142}, {0x2206, 0x0701}, {0x2205, 0xE140},
{0x2206, 0x0405}, {0x220F, 0x0000}, {0x221F, 0x0000}, {0x133E, 0x000E},
{0x133F, 0x0010}, {0x13EB, 0x11BB}, {0x207F, 0x0002}, {0x2073, 0x1D22},
{0x207F, 0x0000}, {0x133F, 0x0030}, {0x133E, 0x000E}, {0x2200, 0x1340},
{0x133E, 0x000E}, {0x133F, 0x0010}, {0x2080, 0x1940}, {0x2097, 0xA100},
};

const unsigned char filter_templateField[RTL8367B_ACLTEMPLATENO][RTL8367B_ACLRULEFIELDNO] = {
    {ACL_DMAC0,   			ACL_DMAC1, 		 	ACL_DMAC2, 	 		ACL_SMAC0,   		ACL_SMAC1, 			ACL_SMAC2, 			ACL_ETHERTYPE, 		ACL_FIELD_SELECT15},
    {ACL_IP4SIP0, 			ACL_IP4SIP1, 		ACL_IP4DIP0, 		ACL_IP4DIP1, 		ACL_FIELD_SELECT13, ACL_FIELD_SELECT14, ACL_FIELD_SELECT02, ACL_FIELD_SELECT15},
    {ACL_IP6SIP0WITHIPV4,	ACL_IP6SIP1WITHIPV4,ACL_FIELD_SELECT03, ACL_FIELD_SELECT04, ACL_FIELD_SELECT05,	ACL_FIELD_SELECT06, ACL_FIELD_SELECT07,	ACL_FIELD_SELECT08},
    {ACL_IP6DIP0WITHIPV4,	ACL_IP6DIP1WITHIPV4,ACL_FIELD_SELECT09, ACL_FIELD_SELECT10, ACL_FIELD_SELECT11,	ACL_FIELD_SELECT12, ACL_FIELD_SELECT13,	ACL_FIELD_SELECT14},
    {ACL_VIDRANGE,			ACL_IPRANGE, 		ACL_PORTRANGE,  	ACL_CTAG,  			ACL_STAG, 			ACL_FIELD_SELECT13, ACL_FIELD_SELECT14,	ACL_FIELD_SELECT15}
};

const unsigned char filter_advanceCaretagField[RTL8367B_ACLTEMPLATENO][2] = {
    {TRUE,		7},
    {TRUE,		7},
    {FALSE,		0},
    {FALSE,		0},
    {TRUE,		7},
};

const unsigned char filter_fieldTemplateIndex[FILTER_FIELD_END][RTK_FILTER_FIELD_USED_MAX] = {
	{0x00, 0x01,0x02},
	{0x03, 0x04,0x05},
	{0x06},
	{0x43},
	{0x44},
	{0x10, 0x11},
	{0x12, 0x13},
	{0x24},
	{0x25},
	{0x35},
	{0x35},
	{0x20, 0x21,0x22,0x23},
	{0x30, 0x31,0x32,0x33},
	{0x26},
	{0x27},
	{0x14},
	{0x15},
	{0x16},
	{0x14},
	{0x15},
	{0x14},
	{0x14},
	{0x14},
	{0x40},
	{0x41},
	{0x42},
	{0x14},
	{0x15},
	{0x16},
	{0x22},
	{0x23},
	{0x24},
	{0x25},
	{0x26},
	{0x27},
	{0x32},
	{0x33},
	{0x34},
	{0x35},
	{0x36},
	{0x37},
	{0x47},
    {0xFF} /* Pattern Match */
};

const unsigned char filter_fieldSize[FILTER_FIELD_END] = {
    3, 3, 1, 1, 1,
    2, 2, 1, 1, 1, 1, 4, 4, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    8
};

const unsigned short field_selector[RTL8367B_FIELDSEL_FORMAT_NUMBER][2] =
{
    {FIELDSEL_FORMAT_DEFAULT, 0},    /* Field Selector 0 */
    {FIELDSEL_FORMAT_DEFAULT, 0},    /* Field Selector 1 */
    {FIELDSEL_FORMAT_IPPAYLOAD, 12}, /* Field Selector 2 */
    {FIELDSEL_FORMAT_IPV6, 10},      /* Field Selector 3 */
    {FIELDSEL_FORMAT_IPV6, 8},       /* Field Selector 4 */
    {FIELDSEL_FORMAT_IPV4, 0},       /* Field Selector 5 */
    {FIELDSEL_FORMAT_IPV4, 8},       /* Field Selector 6 */
    {FIELDSEL_FORMAT_IPV6, 0},       /* Field Selector 7 */
    {FIELDSEL_FORMAT_IPV6, 6},       /* Field Selector 8 */
    {FIELDSEL_FORMAT_IPV6, 26},      /* Field Selector 9 */
    {FIELDSEL_FORMAT_IPV6, 24},      /* Field Selector 10 */
    {FIELDSEL_FORMAT_DEFAULT, 0},    /* Field Selector 11 */
    {FIELDSEL_FORMAT_IPV4, 6},       /* Field Selector 12 */
    {FIELDSEL_FORMAT_IPPAYLOAD, 0},  /* Field Selector 13 */
    {FIELDSEL_FORMAT_IPPAYLOAD, 2},  /* Field Selector 14 */
    {FIELDSEL_FORMAT_DEFAULT, 0}     /* Field Selector 15 */
};

/* Function Name:
 *      rtk_rate_shareMeter_set
 * Description:
 *      Set meter configuration
 * Input:
 *      index       - shared meter index
 *      rate        - rate of share meter
 *      ifg_include - include IFG or not, ENABLE:include DISABLE:exclude
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_FILTER_METER_ID  - Invalid meter
 *      RT_ERR_RATE             - Invalid rate
 *      RT_ERR_INPUT            - Invalid input parameters
 * Note:
 *      The API can set shared meter rate and ifg include for each meter.
 *      The rate unit is 1 kbps and the range is from 8k to 1048568k.
 *      The granularity of rate is 8 kbps. The ifg_include parameter is used
 *      for rate calculation with/without inter-frame-gap and preamble.
 */
int rtk_rate_shareMeter_set(rtk_meter_id_t index, rtk_rate_t rate, rtk_enable_t ifg_include)
{
    int ret_val;

    if (index >= RTL8367B_METERNO)
        return RT_ERR_FILTER_METER_ID;

    if (rate > RTL8367B_QOS_RATE_INPUT_MAX || rate < RTL8367B_QOS_RATE_INPUT_MIN)
        return RT_ERR_RATE ;

    if (ifg_include >= RTK_ENABLE_END)
        return RT_ERR_INPUT;

    if ((ret_val = rtl8367b_setAsicShareMeter(index, rate >> 3, ifg_include)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_rate_shareMeter_get
 * Description:
 *      Get meter configuration
 * Input:
 *      index        - shared meter index
 * Output:
 *      pRate        - pointer of rate of share meter
 *      pIfg_include - include IFG or not, ENABLE:include DISABLE:exclude
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_FILTER_METER_ID  - Invalid meter
 * Note:
 *      The API can get shared meter rate and ifg include for each meter.
 *      The rate unit is 1 kbps and the granularity of rate is 8 kbps.
 *      The ifg_include parameter is used for rate calculation with/without inter-frame-gap and preamble
 */
int rtk_rate_shareMeter_get(rtk_meter_id_t index, rtk_rate_t *pRate , rtk_enable_t *pIfg_include)
{
    int ret_val;
    unsigned int regData;

    if (index > RTL8367B_METERNO)
        return RT_ERR_FILTER_METER_ID;

    if ((ret_val = rtl8367b_getAsicShareMeter(index, &regData, pIfg_include)) != RT_ERR_OK)
        return ret_val;

    *pRate = regData<<3;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_rate_shareMeterBucket_set
 * Description:
 *      Set meter Bucket Size
 * Input:
 *      index        - shared meter index
 *      bucket_size  - Bucket Size
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_INPUT            - Error Input
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_FILTER_METER_ID  - Invalid meter
 * Note:
 *      The API can set shared meter bucket size.
 */
int rtk_rate_shareMeterBucket_set(rtk_meter_id_t index, unsigned int bucket_size)
{
    int ret_val;

    if (index > RTL8367B_METERNO)
        return RT_ERR_FILTER_METER_ID;

    if(bucket_size > RTL8367B_METERBUCKETSIZEMAX)
        return RT_ERR_INPUT;

    if ((ret_val = rtl8367b_setAsicShareMeterBucketSize(index, bucket_size)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_rate_shareMeterBucket_get
 * Description:
 *      Get meter Bucket Size
 * Input:
 *      index        - shared meter index
 * Output:
 *      pBucket_size - Bucket Size
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_FILTER_METER_ID  - Invalid meter
 * Note:
 *      The API can get shared meter bucket size.
 */
int rtk_rate_shareMeterBucket_get(rtk_meter_id_t index, unsigned int *pBucket_size)
{
    int ret_val;

    if (index > RTL8367B_METERNO)
        return RT_ERR_FILTER_METER_ID;

    if ((ret_val = rtl8367b_getAsicShareMeterBucketSize(index, pBucket_size)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_rate_igrBandwidthCtrlRate_set
 * Description:
 *      Set port ingress bandwidth control
 * Input:
 *      port        - Port id
 *      rate        - Rate of share meter
 *      ifg_include - include IFG or not, ENABLE:include DISABLE:exclude
 *      fc_enable   - enable flow control or not, ENABLE:use flow control DISABLE:drop
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID 		- Invalid port number.
 *      RT_ERR_ENABLE 		- Invalid IFG parameter.
 *      RT_ERR_INBW_RATE 	- Invalid ingress rate parameter.
 * Note:
 *      The rate unit is 1 kbps and the range is from 8k to 1048568k. The granularity of rate is 8 kbps.
 *      The ifg_include parameter is used for rate calculation with/without inter-frame-gap and preamble.
 */
int rtk_rate_igrBandwidthCtrlRate_set(unsigned int port, rtk_rate_t rate,  rtk_enable_t ifg_include, rtk_enable_t fc_enable)
{
    int ret_val;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if ((rate > RTL8367B_QOS_RATE_INPUT_MAX) || (rate < RTL8367B_QOS_RATE_INPUT_MIN))
        return RT_ERR_INBW_RATE ;

    if (ifg_include >= RTK_ENABLE_END)
        return RT_ERR_ENABLE;

    if ((ret_val = rtl8367b_setAsicPortIngressBandwidth(port, rate>>3, ifg_include,fc_enable)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_rate_igrBandwidthCtrlRate_get
 * Description:
 *      Get port ingress bandwidth control
 * Input:
 *      port - Port id
 * Output:
 *      pRate           - Rate of share meter
 *      pIfg_include    - Rate's calculation including IFG, ENABLE:include DISABLE:exclude
 *      pFc_enable      - enable flow control or not, ENABLE:use flow control DISABLE:drop
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID 		- Invalid port number.
 *      RT_ERR_INPUT 		- Invalid input parameters.
 * Note:
 *     The rate unit is 1 kbps and the range is from 8k to 1048568k. The granularity of rate is 8 kbps.
 *     The ifg_include parameter is used for rate calculation with/without inter-frame-gap and preamble.
 */
int rtk_rate_igrBandwidthCtrlRate_get(unsigned int port, rtk_rate_t *pRate, rtk_enable_t *pIfg_include, rtk_enable_t *pFc_enable)
{
    int ret_val;
    unsigned int regData;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if ((ret_val = rtl8367b_getAsicPortIngressBandwidth(port, &regData, pIfg_include, pFc_enable)) != RT_ERR_OK)
        return ret_val;

    *pRate = regData<<3;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_rate_egrBandwidthCtrlRate_set
 * Description:
 *      Set port egress bandwidth control
 * Input:
 *      port        - Port id
 *      rate        - Rate of egress bandwidth
 *      ifg_include - include IFG or not, ENABLE:include DISABLE:exclude
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID 		- Invalid port number.
 *      RT_ERR_INPUT 		- Invalid input parameters.
 *      RT_ERR_QOS_EBW_RATE - Invalid egress bandwidth/rate
 * Note:
 *     The rate unit is 1 kbps and the range is from 8k to 1048568k. The granularity of rate is 8 kbps.
 *     The ifg_include parameter is used for rate calculation with/without inter-frame-gap and preamble.
 */
int rtk_rate_egrBandwidthCtrlRate_set( unsigned int port, rtk_rate_t rate,  rtk_enable_t ifg_include)
{
    int ret_val;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if ((rate > RTL8367B_QOS_RATE_INPUT_MAX) || (rate < RTL8367B_QOS_RATE_INPUT_MIN))
        return RT_ERR_QOS_EBW_RATE ;

    if (ifg_include >= RTK_ENABLE_END)
        return RT_ERR_ENABLE;

    if ((ret_val = rtl8367b_setAsicPortEgressRate(port, rate>>3)) != RT_ERR_OK)
        return ret_val;

    if ((ret_val = rtl8367b_setAsicPortEgressRateIfg(ifg_include)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_rate_egrBandwidthCtrlRate_get
 * Description:
 *      Get port egress bandwidth control
 * Input:
 *      port - Port id
 * Output:
 *      pRate           - Rate of egress bandwidth
 *      pIfg_include    - Rate's calculation including IFG, ENABLE:include DISABLE:exclude
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID 		- Invalid port number.
 *      RT_ERR_INPUT 		- Invalid input parameters.
 * Note:
 *     The rate unit is 1 kbps and the range is from 8k to 1048568k. The granularity of rate is 8 kbps.
 *     The ifg_include parameter is used for rate calculation with/without inter-frame-gap and preamble.
 */
int rtk_rate_egrBandwidthCtrlRate_get(unsigned int port, rtk_rate_t *pRate, rtk_enable_t *pIfg_include)
{
    int ret_val;
    unsigned int regData;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if ((ret_val = rtl8367b_getAsicPortEgressRate(port, &regData)) != RT_ERR_OK)
        return ret_val;

    *pRate = regData << 3;

    if ((ret_val = rtl8367b_getAsicPortEgressRateIfg((unsigned int*)pIfg_include)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}


/* Function Name:
 *      rtk_rate_egrQueueBwCtrlEnable_get
 * Description:
 *      Get enable status of egress bandwidth control on specified queue.
 * Input:
 *      unit    - unit id
 *      port    - port id
 *      queue   - queue id
 * Output:
 *      pEnable - Pointer to enable status of egress queue bandwidth control
 * Return:
 *      RT_ERR_OK
 *      RT_ERR_FAILED
 *      RT_ERR_PORT_ID          - invalid port id
 *      RT_ERR_QUEUE_ID         - invalid queue id
 *      RT_ERR_NULL_POINTER     - input parameter may be null pointer
 * Note:
 *      None
 */
int rtk_rate_egrQueueBwCtrlEnable_get(unsigned int port, rtk_qid_t queue, rtk_enable_t *pEnable)
{
    int ret_val;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    /*for whole port function, the queue value should be 0xFF*/
    if (queue != RTK_WHOLE_SYSTEM)
        return RT_ERR_QUEUE_ID;

    if ((ret_val = rtl8367b_getAsicAprEnable(port,pEnable))!=RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_rate_egrQueueBwCtrlEnable_set
 * Description:
 *      Set enable status of egress bandwidth control on specified queue.
 * Input:
 *      port   - port id
 *      queue  - queue id
 *      enable - enable status of egress queue bandwidth control
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK
 *      RT_ERR_FAILED
 *      RT_ERR_PORT_ID          - invalid port id
 *      RT_ERR_QUEUE_ID         - invalid queue id
 *      RT_ERR_INPUT            - invalid input parameter
 * Note:
 *      None
 */
int rtk_rate_egrQueueBwCtrlEnable_set(unsigned int port, rtk_qid_t queue, rtk_enable_t enable)
{
    int ret_val;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    /*for whole port function, the queue value should be 0xFF*/
    if (queue != RTK_WHOLE_SYSTEM)
        return RT_ERR_QUEUE_ID;

    if (enable>=RTK_ENABLE_END)
        return RT_ERR_INPUT;

    if ((ret_val = rtl8367b_setAsicAprEnable(port,enable))!=RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_rate_egrQueueBwCtrlRate_get
 * Description:
 *      Get rate of egress bandwidth control on specified queue.
 * Input:
 *      port  - port id
 *      queue - queue id
 *      pIndex - shared meter index
 * Output:
 *      pRate - pointer to rate of egress queue bandwidth control
 * Return:
 *      RT_ERR_OK
 *      RT_ERR_FAILED
 *      RT_ERR_PORT_ID          - invalid port id
 *      RT_ERR_QUEUE_ID         - invalid queue id
 *      RT_ERR_FILTER_METER_ID  - Invalid meter id
 * Note:
 *    The actual rate control is set in shared meters.
 *    The unit of granularity is 8Kbps.
 */
int rtk_rate_egrQueueBwCtrlRate_get(unsigned int port, rtk_qid_t queue, rtk_meter_id_t *pIndex)
{
    int ret_val;
    unsigned int offset_idx;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if (queue >= RTK_MAX_NUM_OF_QUEUE)
        return RT_ERR_QUEUE_ID;


    if ((ret_val=rtl8367b_getAsicAprMeter(port,queue,&offset_idx))!=RT_ERR_OK)
        return ret_val;

    *pIndex = offset_idx + ((port%4)*8);

     return RT_ERR_OK;
}


/* Function Name:
 *      rtk_rate_egrQueueBwCtrlRate_set
 * Description:
 *      Set rate of egress bandwidth control on specified queue.
 * Input:
 *      port  - port id
 *      queue - queue id
 *      index - shared meter index
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK
 *      RT_ERR_FAILED
 *      RT_ERR_PORT_ID          - invalid port id
 *      RT_ERR_QUEUE_ID         - invalid queue id
 *      RT_ERR_FILTER_METER_ID  - Invalid meter id
 * Note:
 *    The actual rate control is set in shared meters.
 *    The unit of granularity is 8Kbps.
 */
int rtk_rate_egrQueueBwCtrlRate_set(unsigned int port, rtk_qid_t queue, rtk_meter_id_t index)
{
    int ret_val;
    unsigned int offset_idx;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if (queue >= RTK_MAX_NUM_OF_QUEUE)
        return RT_ERR_QUEUE_ID;

    if (index>=RTK_MAX_NUM_OF_METER)
        return RT_ERR_FILTER_METER_ID;

    if (index < ((port%4)*8) ||  index > (7 + (port%4)*8))
        return RT_ERR_FILTER_METER_ID;

    offset_idx = index - ((port%4)*8);

    if ((ret_val=rtl8367b_setAsicAprMeter(port,queue,offset_idx))!=RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}


/* Function Name:
 *      rtk_qos_init
 * Description:
 *      Configure Qos default settings with queue number assigment to each port.
 * Input:
 *      queueNum - Queue number of each port.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_QUEUE_NUM 	- Invalid queue number.
 *      RT_ERR_INPUT 		- Invalid input parameters.
 * Note:
 *      This API will initialize related Qos setting with queue number assigment.
 *      The queue number is from 1 to 8.
 */
int rtk_qos_init(rtk_queue_num_t queueNum)
{
    const unsigned short g_prioritytToQid[8][8]= {
            {0, 0,0,0,0,0,0,0},
            {0, 0,0,0,7,7,7,7},
            {0, 0,0,0,1,1,7,7},
            {0, 0,1,1,2,2,7,7},
            {0, 0,1,1,2,3,7,7},
            {0, 0,1,1,2,3,4,7},
            {0, 0,1,2,3,4,5,7},
            {0,1,2,3,4,5,6,7}
    };

    const unsigned int g_priorityDecision[8] = {0x01, 0x80,0x04,0x02,0x20,0x40,0x10,0x08};
    const unsigned int g_prioritytRemap[8] = {0,1,2,3,4,5,6,7};

    int ret_val;
    unsigned int qmapidx;
    unsigned int priority;
    unsigned int priDec;
    unsigned int port;
    unsigned int dscp;

    if (queueNum <= 0 || queueNum > RTL8367B_QUEUENO)
        return RT_ERR_QUEUE_NUM;

    /*Set Output Queue Number*/
    if (RTL8367B_QUEUENO == queueNum)
        qmapidx = 0;
    else
        qmapidx = queueNum;

    for (port = 0; port < RTK_MAX_NUM_OF_PORT; port++)
    {
        if ((ret_val = rtl8367b_setAsicOutputQueueMappingIndex(port, qmapidx)) != RT_ERR_OK)
            return ret_val;
    }

    /*Set Priority to Qid*/
    for (priority = 0; priority < RTL8367B_PRIMAX; priority++)
    {
        if ((ret_val = rtl8367b_setAsicPriorityToQIDMappingTable(qmapidx, priority, g_prioritytToQid[qmapidx][priority])) != RT_ERR_OK)
            return ret_val;
    }

    /*Set Flow Control Type to Ingress Flow Control*/
    if ((ret_val = rtl8367b_setAsicFlowControlSelect(FC_INGRESS)) != RT_ERR_OK)
        return ret_val;


    /*Priority Decision Order*/
    for (priDec = 0;priDec < PRIDEC_END;priDec++)
    {
        if ((ret_val = rtl8367b_setAsicPriorityDecision(priDec, g_priorityDecision[priDec])) != RT_ERR_OK)
            return ret_val;
    }

    /*Set Port-based Priority to 0*/
    for (port = 0;port < RTK_MAX_NUM_OF_PORT;port++)
    {
        if ((ret_val = rtl8367b_setAsicPriorityPortBased(port, 0)) != RT_ERR_OK)
            return ret_val;
    }

    /*Disable 1p Remarking*/
    for (port = 0; port < RTK_MAX_NUM_OF_PORT; port++)
    {
        if ((ret_val = rtl8367b_setAsicRemarkingDot1pAbility(port, DISABLE)) != RT_ERR_OK)
            return ret_val;
    }

    /*Disable DSCP Remarking*/
    if ((ret_val = rtl8367b_setAsicRemarkingDscpAbility(DISABLE)) != RT_ERR_OK)
        return ret_val;

    /*Set 1p & DSCP  Priority Remapping & Remarking*/
    for (priority = 0; priority < RTL8367B_PRIMAX; priority++)
    {
        if ((ret_val = rtl8367b_setAsicPriorityDot1qRemapping(priority, g_prioritytRemap[priority])) != RT_ERR_OK)
            return ret_val;

        if ((ret_val = rtl8367b_setAsicRemarkingDot1pParameter(priority, 0)) != RT_ERR_OK)
            return ret_val;

        if ((ret_val = rtl8367b_setAsicRemarkingDscpParameter(priority, 0)) != RT_ERR_OK)
            return ret_val;
    }

    /*Set DSCP Priority*/
    for (dscp = 0; dscp < 63; dscp++)
    {
        if ((ret_val = rtl8367b_setAsicPriorityDscpBased(dscp, 0)) != RT_ERR_OK)
            return ret_val;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_qos_priSel_set
 * Description:
 *      Configure the priority order among different priority mechanism.
 * Input:
 *      pPriDec - Priority assign for port, dscp, 802.1p, cvlan, svlan, acl based priority decision.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK              		- OK
 *      RT_ERR_FAILED          		- Failed
 *      RT_ERR_SMI             		- SMI access error
 *      RT_ERR_QOS_SEL_PRI_SOURCE 	- Invalid priority decision source parameter.
 * Note:
 *      ASIC will follow user priority setting of mechanisms to select mapped queue priority for receiving frame.
 *      If two priority mechanisms are the same, the ASIC will chose the highest priority from mechanisms to
 *      assign queue priority to receiving frame.
 *      The priority sources are:
 *      - PRIDEC_PORT
 *      - PRIDEC_ACL
 *      - PRIDEC_DSCP
 *      - PRIDEC_1Q
 *      - PRIDEC_1AD
 *      - PRIDEC_CVLAN
 *      - PRIDEC_DA
 *      - PRIDEC_SA
 */
int rtk_qos_priSel_set(rtk_priority_select_t *pPriDec)
{
    int ret_val;
    unsigned int port_pow;
    unsigned int dot1q_pow;
    unsigned int dscp_pow;
    unsigned int acl_pow;
    unsigned int svlan_pow;
    unsigned int cvlan_pow;
    unsigned int smac_pow;
    unsigned int dmac_pow;
    unsigned int i;

    if (pPriDec->port_pri > 8 || pPriDec->dot1q_pri > 8 || pPriDec->acl_pri > 8 || pPriDec->dscp_pri > 8 ||
       pPriDec->cvlan_pri > 8 || pPriDec->svlan_pri > 8 || pPriDec->dmac_pri > 8 || pPriDec->smac_pri > 8)
        return RT_ERR_QOS_SEL_PRI_SOURCE;

    port_pow = 1;
    for (i = pPriDec->port_pri; i > 0; i--)
        port_pow = (port_pow)*2;

    dot1q_pow = 1;
    for (i = pPriDec->dot1q_pri; i > 0; i--)
        dot1q_pow = (dot1q_pow)*2;

    acl_pow = 1;
    for (i = pPriDec->acl_pri; i > 0; i--)
        acl_pow = (acl_pow)*2;

    dscp_pow = 1;
    for (i = pPriDec->dscp_pri; i > 0; i--)
        dscp_pow = (dscp_pow)*2;

    svlan_pow = 1;
    for (i = pPriDec->svlan_pri; i > 0; i--)
        svlan_pow = (svlan_pow)*2;

    cvlan_pow = 1;
    for (i = pPriDec->cvlan_pri; i > 0; i--)
        cvlan_pow = (cvlan_pow)*2;

    dmac_pow = 1;
    for (i = pPriDec->dmac_pri; i > 0; i--)
        dmac_pow = (dmac_pow)*2;

    smac_pow = 1;
    for (i = pPriDec->smac_pri; i > 0; i--)
        smac_pow = (smac_pow)*2;

    if ((ret_val = rtl8367b_setAsicPriorityDecision(PRIDEC_PORT, port_pow)) != RT_ERR_OK)
        return ret_val;

    if ((ret_val = rtl8367b_setAsicPriorityDecision(PRIDEC_ACL, acl_pow)) != RT_ERR_OK)
        return ret_val;

    if ((ret_val = rtl8367b_setAsicPriorityDecision(PRIDEC_DSCP, dscp_pow)) != RT_ERR_OK)
        return ret_val;

    if ((ret_val = rtl8367b_setAsicPriorityDecision(PRIDEC_1Q, dot1q_pow)) != RT_ERR_OK)
        return ret_val;

    if ((ret_val = rtl8367b_setAsicPriorityDecision(PRIDEC_1AD, svlan_pow)) != RT_ERR_OK)
        return ret_val;

    if ((ret_val = rtl8367b_setAsicPriorityDecision(PRIDEC_CVLAN, cvlan_pow)) != RT_ERR_OK)
        return ret_val;

    if ((ret_val = rtl8367b_setAsicPriorityDecision(PRIDEC_DA, dmac_pow)) != RT_ERR_OK)
        return ret_val;

    if ((ret_val = rtl8367b_setAsicPriorityDecision(PRIDEC_SA, smac_pow)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_qos_priSel_get
 * Description:
 *      Get the priority order configuration among different priority mechanism.
 * Input:
 *      None
 * Output:
 *      pPriDec - Priority assign for port, dscp, 802.1p, cvlan, svlan, acl based priority decision .
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 * Note:
 *      ASIC will follow user priority setting of mechanisms to select mapped queue priority for receiving frame.
 *      If two priority mechanisms are the same, the ASIC will chose the highest priority from mechanisms to
 *      assign queue priority to receiving frame.
 *      The priority sources are:
 *      - PRIDEC_PORT,
 *      - PRIDEC_ACL,
 *      - PRIDEC_DSCP,
 *      - PRIDEC_1Q,
 *      - PRIDEC_1AD,
 *      - PRIDEC_CVLAN,
 *      - PRIDEC_DA,
 *      - PRIDEC_SA,
 */
int rtk_qos_priSel_get(rtk_priority_select_t *pPriDec)
{
    int ret_val;
    unsigned int i;
    unsigned int port_pow;
    unsigned int dot1q_pow;
    unsigned int dscp_pow;
    unsigned int acl_pow;
    unsigned int svlan_pow;
    unsigned int cvlan_pow;
    unsigned int smac_pow;
    unsigned int dmac_pow;

    if ((ret_val = rtl8367b_getAsicPriorityDecision(PRIDEC_PORT, &port_pow)) != RT_ERR_OK)
        return ret_val;

    if ((ret_val = rtl8367b_getAsicPriorityDecision(PRIDEC_ACL, &acl_pow)) != RT_ERR_OK)
        return ret_val;

    if ((ret_val = rtl8367b_getAsicPriorityDecision(PRIDEC_DSCP, &dscp_pow)) != RT_ERR_OK)
        return ret_val;

    if ((ret_val = rtl8367b_getAsicPriorityDecision(PRIDEC_1Q, &dot1q_pow)) != RT_ERR_OK)
        return ret_val;

    if ((ret_val = rtl8367b_getAsicPriorityDecision(PRIDEC_1AD, &svlan_pow)) != RT_ERR_OK)
        return ret_val;

    if ((ret_val = rtl8367b_getAsicPriorityDecision(PRIDEC_CVLAN, &cvlan_pow)) != RT_ERR_OK)
        return ret_val;

    if ((ret_val = rtl8367b_getAsicPriorityDecision(PRIDEC_DA, &dmac_pow)) != RT_ERR_OK)
        return ret_val;

    if ((ret_val = rtl8367b_getAsicPriorityDecision(PRIDEC_SA, &smac_pow)) != RT_ERR_OK)
        return ret_val;

    for (i = 31; i >= 0; i--)
    {
        if (port_pow & (1 << i))
        {
            pPriDec->port_pri = i;
            break;
        }
    }

    for (i = 31; i >= 0; i--)
    {
        if (dot1q_pow & (1 << i))
        {
            pPriDec->dot1q_pri = i;
            break;
        }
    }

    for (i = 31; i >= 0; i--)
    {
        if (acl_pow & (1 << i))
        {
            pPriDec->acl_pri = i;
            break;
        }
    }

    for (i = 31; i >= 0; i--)
    {
        if (dscp_pow & (1 << i))
        {
            pPriDec->dscp_pri = i;
            break;
        }
    }

    for (i = 31; i >= 0; i--)
    {
        if (svlan_pow & (1 << i))
        {
            pPriDec->svlan_pri = i;
            break;
        }
    }

    for (i = 31;i  >= 0; i--)
    {
        if (cvlan_pow & (1 << i))
        {
            pPriDec->cvlan_pri = i;
            break;
        }
    }

    for (i = 31; i >= 0; i--)
    {
        if (dmac_pow&(1<<i))
        {
            pPriDec->dmac_pri = i;
            break;
        }
    }

    for (i = 31; i >= 0; i--)
    {
        if (smac_pow & (1 << i))
        {
            pPriDec->smac_pri = i;
            break;
        }
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_qos_1pPriRemap_set
 * Description:
 *      Configure 1Q priorities mapping to internal absolute priority.
 * Input:
 *      dot1p_pri   - 802.1p priority value.
 *      int_pri     - internal priority value.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK              	- OK
 *      RT_ERR_FAILED          	- Failed
 *      RT_ERR_SMI             	- SMI access error
 *      RT_ERR_INPUT 			- Invalid input parameters.
 *      RT_ERR_VLAN_PRIORITY 	- Invalid 1p priority.
 *      RT_ERR_QOS_INT_PRIORITY - Invalid priority.
 * Note:
 *      Priority of 802.1Q assignment for internal asic priority, and it is used for queue usage and packet scheduling.
 */
int rtk_qos_1pPriRemap_set(rtk_pri_t dot1p_pri, rtk_pri_t int_pri)
{
    int ret_val;

    if (int_pri > RTL8367B_PRIMAX)
        return  RT_ERR_QOS_INT_PRIORITY;

    if (dot1p_pri > RTL8367B_PRIMAX || int_pri > RTL8367B_PRIMAX)
        return  RT_ERR_VLAN_PRIORITY;

    if ((ret_val = rtl8367b_setAsicPriorityDot1qRemapping(dot1p_pri, int_pri)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_qos_1pPriRemap_get
 * Description:
 *      Get 1Q priorities mapping to internal absolute priority.
 * Input:
 *      dot1p_pri - 802.1p priority value .
 * Output:
 *      pInt_pri - internal priority value.
 * Return:
 *      RT_ERR_OK              	- OK
 *      RT_ERR_FAILED          	- Failed
 *      RT_ERR_SMI             	- SMI access error
 *      RT_ERR_VLAN_PRIORITY 	- Invalid priority.
 *      RT_ERR_QOS_INT_PRIORITY - Invalid priority.
 * Note:
 *      Priority of 802.1Q assigment for internal asic priority, and it is uesed for queue usage and packet scheduling.
 */
int rtk_qos_1pPriRemap_get(rtk_pri_t dot1p_pri, rtk_pri_t *pInt_pri)
{
    int ret_val;

    if (dot1p_pri > RTL8367B_PRIMAX)
        return  RT_ERR_QOS_INT_PRIORITY;

    if ((ret_val = rtl8367b_getAsicPriorityDot1qRemapping(dot1p_pri, pInt_pri)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_qos_dscpPriRemap_set
 * Description:
 *      Map dscp value to internal priority.
 * Input:
 *      dscp    - Dscp value of receiving frame
 *      int_pri - internal priority value .
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK              	- OK
 *      RT_ERR_FAILED          	- Failed
 *      RT_ERR_SMI             	- SMI access error
 *      RT_ERR_INPUT 			- Invalid input parameters.
 *      RT_ERR_QOS_DSCP_VALUE 	- Invalid DSCP value.
 *      RT_ERR_QOS_INT_PRIORITY - Invalid priority.
 * Note:
 *      The Differentiated Service Code Point is a selector for router's per-hop behaviors. As a selector, there is no implication that a numerically
 *      greater DSCP implies a better network service. As can be seen, the DSCP totally overlaps the old precedence field of TOS. So if values of
 *      DSCP are carefully chosen then backward compatibility can be achieved.
 */
int rtk_qos_dscpPriRemap_set(unsigned int dscp, rtk_pri_t int_pri)
{
    int ret_val;

    if (int_pri > RTL8367B_PRIMAX )
        return RT_ERR_QOS_INT_PRIORITY;

    if (dscp > RTL8367B_DSCPMAX)
        return RT_ERR_QOS_DSCP_VALUE;

    if ((ret_val = rtl8367b_setAsicPriorityDscpBased(dscp, int_pri)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_qos_dscpPriRemap_get
 * Description:
 *      Get dscp value to internal priority.
 * Input:
 *      dscp - Dscp value of receiving frame
 * Output:
 *      pInt_pri - internal priority value.
 * Return:
 *      RT_ERR_OK              	- OK
 *      RT_ERR_FAILED          	- Failed
 *      RT_ERR_SMI             	- SMI access error
 *      RT_ERR_QOS_DSCP_VALUE 	- Invalid DSCP value.
 * Note:
 *      The Differentiated Service Code Point is a selector for router's per-hop behaviors. As a selector, there is no implication that a numerically
 *      greater DSCP implies a better network service. As can be seen, the DSCP totally overlaps the old precedence field of TOS. So if values of
 *      DSCP are carefully chosen then backward compatibility can be achieved.
 */
int rtk_qos_dscpPriRemap_get(unsigned int dscp, rtk_pri_t *pInt_pri)
{
    int ret_val;

    if (dscp > RTL8367B_DSCPMAX)
        return RT_ERR_QOS_DSCP_VALUE;

    if ((ret_val = rtl8367b_getAsicPriorityDscpBased(dscp, pInt_pri)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_qos_portPri_set
 * Description:
 *      Configure priority usage to each port.
 * Input:
 *      port - Port id.
 *      int_pri - internal priority value.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK              	- OK
 *      RT_ERR_FAILED          	- Failed
 *      RT_ERR_SMI             	- SMI access error
 *      RT_ERR_PORT_ID 			- Invalid port number.
 *      RT_ERR_QOS_SEL_PORT_PRI - Invalid port priority.
 *      RT_ERR_QOS_INT_PRIORITY - Invalid priority.
 * Note:
 *      The API can set priority of port assignments for queue usage and packet scheduling.
 */
int rtk_qos_portPri_set(unsigned int port, rtk_pri_t int_pri)
{
    int ret_val;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if (int_pri > RTL8367B_PRIMAX )
        return RT_ERR_QOS_INT_PRIORITY;

    if ((ret_val = rtl8367b_setAsicPriorityPortBased(port, int_pri)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_qos_portPri_get
 * Description:
 *      Get priority usage to each port.
 * Input:
 *      port - Port id.
 * Output:
 *      pInt_pri - internal priority value.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID 		- Invalid port number.
 *      RT_ERR_INPUT 		- Invalid input parameters.
 * Note:
 *      The API can get priority of port assignments for queue usage and packet scheduling.
 */
int rtk_qos_portPri_get(unsigned int port, rtk_pri_t *pInt_pri)
{
    int ret_val;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if ((ret_val = rtl8367b_getAsicPriorityPortBased(port, pInt_pri)) != RT_ERR_OK)
        return ret_val;


    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_qos_queueNum_set
 * Description:
 *      Set output queue number for each port.
 * Input:
 *      port    - Port id.
 *      index   - Mapping queue number (1~8)
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID 		- Invalid port number.
 *      RT_ERR_QUEUE_NUM 	- Invalid queue number.
 * Note:
 *      The API can set the output queue number of the specified port. The queue number is from 1 to 8.
 */
int rtk_qos_queueNum_set(unsigned int port, rtk_queue_num_t queue_num)
{
    int ret_val;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if ((0 == queue_num) || (queue_num > RTL8367B_QUEUENO))
        return RT_ERR_FAILED;

    if (RTL8367B_QUEUENO == queue_num)
        queue_num = 0;

    if ((ret_val = rtl8367b_setAsicOutputQueueMappingIndex(port, queue_num)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_qos_queueNum_get
 * Description:
 *      Get output queue number.
 * Input:
 *      port - Port id.
 * Output:
 *      pQueue_num - Mapping queue number
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID 		- Invalid port number.
 * Note:
 *      The API will return the output queue number of the specified port. The queue number is from 1 to 8.
 */
int rtk_qos_queueNum_get(unsigned int port, rtk_queue_num_t *pQueue_num)
{
    int ret_val;
    unsigned int qidx;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if ((ret_val = rtl8367b_getAsicOutputQueueMappingIndex(port, &qidx)) != RT_ERR_OK)
        return ret_val;

    if (0 == qidx)
        *pQueue_num = 8;
    else
        *pQueue_num = qidx;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_qos_priMap_set
 * Description:
 *      Set output queue number for each port.
 * Input:
 *      queue_num   - Queue number usage.
 *      pPri2qid    - Priority mapping to queue ID.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK              	- OK
 *      RT_ERR_FAILED          	- Failed
 *      RT_ERR_SMI             	- SMI access error
 *      RT_ERR_INPUT 			- Invalid input parameters.
 *      RT_ERR_QUEUE_NUM 		- Invalid queue number.
 *      RT_ERR_QUEUE_ID 		- Invalid queue id.
 *      RT_ERR_PORT_ID 			- Invalid port number.
 *      RT_ERR_QOS_INT_PRIORITY - Invalid priority.
 * Note:
 *      ASIC supports priority mapping to queue with different queue number from 1 to 8.
 *      For different queue numbers usage, ASIC supports different internal available queue IDs.
 */
int rtk_qos_priMap_set(rtk_queue_num_t queue_num, rtk_qos_pri2queue_t *pPri2qid)
{
    int ret_val;
    unsigned int pri;

    if ((0 == queue_num) || (queue_num > RTL8367B_QUEUENO))
        return RT_ERR_QUEUE_NUM;

    for (pri = 0; pri <= RTL8367B_PRIMAX; pri++)
    {
        if (pPri2qid->pri2queue[pri] > RTL8367B_QIDMAX)
            return RT_ERR_QUEUE_ID;

        if ((ret_val = rtl8367b_setAsicPriorityToQIDMappingTable(queue_num - 1, pri, pPri2qid->pri2queue[pri])) != RT_ERR_OK)
            return ret_val;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_qos_priMap_get
 * Description:
 *      Get priority to queue ID mapping table parameters.
 * Input:
 *      queue_num - Queue number usage.
 * Output:
 *      pPri2qid - Priority mapping to queue ID.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT 		- Invalid input parameters.
 *      RT_ERR_QUEUE_NUM 	- Invalid queue number.
 * Note:
 *      The API can return the mapping queue id of the specified priority and queue number.
 *      The queue number is from 1 to 8.
 */
int rtk_qos_priMap_get(rtk_queue_num_t queue_num, rtk_qos_pri2queue_t *pPri2qid)
{
    int ret_val;
    unsigned int pri;

    if ((0 == queue_num) || (queue_num > RTL8367B_QUEUENO))
        return RT_ERR_QUEUE_NUM;

    for (pri = 0; pri <= RTL8367B_PRIMAX; pri++)
    {
        if ((ret_val = rtl8367b_getAsicPriorityToQIDMappingTable(queue_num-1, pri, &pPri2qid->pri2queue[pri])) != RT_ERR_OK)
            return ret_val;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_qos_schedulingQueue_set
 * Description:
 *      Set weight and type of queues in dedicated port.
 * Input:
 *      port        - Port id.
 *      pQweights   - The array of weights for WRR/WFQ queue (0 for STRICT_PRIORITY queue).
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK              	- OK
 *      RT_ERR_FAILED          	- Failed
 *      RT_ERR_SMI             	- SMI access error
 *      RT_ERR_PORT_ID 			- Invalid port number.
 *      RT_ERR_QOS_QUEUE_WEIGHT - Invalid queue weight.
 * Note:
 *      The API can set weight and type, strict priority or weight fair queue (WFQ) for
 *      dedicated port for using queues. If queue id is not included in queue usage,
 *      then its type and weight setting in dummy for setting. There are priorities
 *      as queue id in strict queues. It means strict queue id 5 carrying higher priority
 *      than strict queue id 4. The WFQ queue weight is from 1 to 128, and weight 0 is
 *      for strict priority queue type.
 */
int rtk_qos_schedulingQueue_set(unsigned int port, rtk_qos_queue_weights_t *pQweights)
{
    int ret_val;
    unsigned int qid;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_FAILED;


    for (qid = 0; qid < RTL8367B_QUEUENO; qid ++)
    {

        if (pQweights->weights[qid] > QOS_WEIGHT_MAX)
            return RT_ERR_QOS_QUEUE_WEIGHT;

        if (0 == pQweights->weights[qid])
        {
            if ((ret_val = rtl8367b_setAsicQueueType(port, qid, QTYPE_STRICT)) != RT_ERR_OK)
                return ret_val;
        }
        else
        {
            if ((ret_val = rtl8367b_setAsicQueueType(port, qid, QTYPE_WFQ)) != RT_ERR_OK)
                return ret_val;

            if ((ret_val = rtl8367b_setAsicWFQWeight(port,qid, pQweights->weights[qid])) != RT_ERR_OK)
                return ret_val;
        }
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_qos_schedulingQueue_get
 * Description:
 *      Get weight and type of queues in dedicated port.
 * Input:
 *      port - Port id.
 * Output:
 *      pQweights - The array of weights for WRR/WFQ queue (0 for STRICT_PRIORITY queue).
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT 		- Invalid input parameters.
 *      RT_ERR_PORT_ID 		- Invalid port number.
 * Note:
 *      The API can get weight and type, strict priority or weight fair queue (WFQ) for dedicated port for using queues.
 *      The WFQ queue weight is from 1 to 128, and weight 0 is for strict priority queue type.
 */
int rtk_qos_schedulingQueue_get(unsigned int port, rtk_qos_queue_weights_t *pQweights)
{
    int ret_val;
    unsigned int qid,qtype,qweight;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_FAILED;

    for (qid = 0; qid < RTL8367B_QUEUENO; qid++)
    {
        if ((ret_val = rtl8367b_getAsicQueueType(port, qid, &qtype)) != RT_ERR_OK)
            return ret_val;

        if (QTYPE_STRICT == qtype)
        {
            pQweights->weights[qid] = 0;
        }
        else if (QTYPE_WFQ == qtype)
        {
            if ((ret_val = rtl8367b_getAsicWFQWeight(port, qid, &qweight)) != RT_ERR_OK)
                return ret_val;
            pQweights->weights[qid] = qweight;
        }
    }
    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_qos_1pRemarkEnable_set
 * Description:
 *      Set 1p Remarking state
 * Input:
 *      port        - Port id.
 *      enable      - State of per-port 1p Remarking
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID 		- Invalid port number.
 *      RT_ERR_ENABLE 		- Invalid enable parameter.
 * Note:
 *      The API can enable or disable 802.1p remarking ability for whole system.
 *      The status of 802.1p remark:
 *      - DISABLED
 *      - ENABLED
 */
int rtk_qos_1pRemarkEnable_set(unsigned int port, rtk_enable_t enable)
{
    int ret_val;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_FAILED;

    if (enable >= RTK_ENABLE_END)
        return RT_ERR_INPUT;

    if ((ret_val = rtl8367b_setAsicRemarkingDot1pAbility(port, enable)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_qos_1pRemarkEnable_get
 * Description:
 *      Get 802.1p remarking ability.
 * Input:
 *      port - Port id.
 * Output:
 *      pEnable - Status of 802.1p remark.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID 		- Invalid port number.
 * Note:
 *      The API can get 802.1p remarking ability.
 *      The status of 802.1p remark:
 *      - DISABLED
 *      - ENABLED
 */
int rtk_qos_1pRemarkEnable_get(unsigned int port, rtk_enable_t *pEnable)
{
    int ret_val;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_FAILED;

    if ((ret_val = rtl8367b_getAsicRemarkingDot1pAbility(port, pEnable)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_qos_1pRemark_set
 * Description:
 *      Set 802.1p remarking parameter.
 * Input:
 *      int_pri     - Internal priority value.
 *      dot1p_pri   - 802.1p priority value.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK              	- OK
 *      RT_ERR_FAILED          	- Failed
 *      RT_ERR_SMI             	- SMI access error
 *      RT_ERR_VLAN_PRIORITY 	- Invalid 1p priority.
 *      RT_ERR_QOS_INT_PRIORITY - Invalid priority.
 * Note:
 *      The API can set 802.1p parameters source priority and new priority.
 */
int rtk_qos_1pRemark_set(rtk_pri_t int_pri, rtk_pri_t dot1p_pri)
{
    int ret_val;

    if (int_pri > RTL8367B_PRIMAX )
        return RT_ERR_QOS_INT_PRIORITY;

    if (dot1p_pri > RTL8367B_PRIMAX)
        return RT_ERR_VLAN_PRIORITY;

    if ((ret_val = rtl8367b_setAsicRemarkingDot1pParameter(int_pri, dot1p_pri)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_qos_1pRemark_get
 * Description:
 *      Get 802.1p remarking parameter.
 * Input:
 *      int_pri - Internal priority value.
 * Output:
 *      pDot1p_pri - 802.1p priority value.
 * Return:
 *      RT_ERR_OK              	- OK
 *      RT_ERR_FAILED          	- Failed
 *      RT_ERR_SMI             	- SMI access error
 *      RT_ERR_QOS_INT_PRIORITY - Invalid priority.
 * Note:
 *      The API can get 802.1p remarking parameters. It would return new priority of ingress priority.
 */
int rtk_qos_1pRemark_get(rtk_pri_t int_pri, rtk_pri_t *pDot1p_pri)
{
    int ret_val;

    if (int_pri > RTL8367B_PRIMAX )
        return RT_ERR_QOS_INT_PRIORITY;

    if ((ret_val = rtl8367b_getAsicRemarkingDot1pParameter(int_pri, pDot1p_pri)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_qos_dscpRemarkEnable_set
 * Description:
 *      Set DSCP remarking ability.
 * Input:
 *      port    - Port id.
 *      enable  - status of DSCP remark.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK              	- OK
 *      RT_ERR_FAILED          	- Failed
 *      RT_ERR_SMI             	- SMI access error
 *      RT_ERR_PORT_ID 			- Invalid port number.
 *      RT_ERR_QOS_INT_PRIORITY - Invalid priority.
 *      RT_ERR_ENABLE 			- Invalid enable parameter.
 * Note:
 *      The API can enable or disable DSCP remarking ability for whole system.
 *      The status of DSCP remark:
 *      - DISABLED
 *      - ENABLED
 */
int rtk_qos_dscpRemarkEnable_set(unsigned int port, rtk_enable_t enable)
{
    int ret_val;

    /*for whole system function, the port value should be 0xFF*/
    if (port != RTK_WHOLE_SYSTEM)
        return RT_ERR_PORT_ID;

    if (enable >= RTK_ENABLE_END)
        return RT_ERR_INPUT;

    if ((ret_val = rtl8367b_setAsicRemarkingDscpAbility(enable)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_qos_dscpRemarkEnable_get
 * Description:
 *      Get DSCP remarking ability.
 * Input:
 *      port - Port id.
 * Output:
 *      pEnable - status of DSCP remarking.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID 		- Invalid port number.
 * Note:
 *      The API can get DSCP remarking ability.
 *      The status of DSCP remark:
 *      - DISABLED
 *      - ENABLED
 */
int rtk_qos_dscpRemarkEnable_get(unsigned int port, rtk_enable_t *pEnable)
{
    int ret_val;

    /*for whole system function, the port value should be 0xFF*/
    if (port != RTK_WHOLE_SYSTEM)
        return RT_ERR_PORT_ID;

    if ((ret_val = rtl8367b_getAsicRemarkingDscpAbility(pEnable)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_qos_dscpRemark_set
 * Description:
 *      Set DSCP remarking parameter.
 * Input:
 *      int_pri - Internal priority value.
 *      dscp    - DSCP value.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK              	- OK
 *      RT_ERR_FAILED          	- Failed
 *      RT_ERR_SMI             	- SMI access error
 *      RT_ERR_QOS_INT_PRIORITY - Invalid priority.
 *      RT_ERR_QOS_DSCP_VALUE 	- Invalid DSCP value.
 * Note:
 *      The API can set DSCP value and mapping priority.
 */
int rtk_qos_dscpRemark_set(rtk_pri_t int_pri, unsigned int dscp)
{
    int ret_val;

    if (int_pri > RTL8367B_PRIMAX )
        return RT_ERR_QOS_INT_PRIORITY;

    if (dscp > RTL8367B_DSCPMAX)
        return RT_ERR_QOS_DSCP_VALUE;

    if ((ret_val = rtl8367b_setAsicRemarkingDscpParameter(int_pri, dscp)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}


/* Function Name:
 *      rtk_qos_dscpRemark_get
 * Description:
 *      Get DSCP remarking parameter.
 * Input:
 *      int_pri - Internal priority value.
 * Output:
 *      Dscp - DSCP value.
 * Return:
 *      RT_ERR_OK              	- OK
 *      RT_ERR_FAILED          	- Failed
 *      RT_ERR_SMI             	- SMI access error
 *      RT_ERR_QOS_INT_PRIORITY - Invalid priority.
 * Note:
 *      The API can get DSCP parameters. It would return DSCP value for mapping priority.
 */
int rtk_qos_dscpRemark_get(rtk_pri_t int_pri, unsigned int *pDscp)
{
    int ret_val;

    if (int_pri > RTL8367B_PRIMAX )
        return RT_ERR_QOS_INT_PRIORITY;

    if ((ret_val = rtl8367b_getAsicRemarkingDscpParameter(int_pri, pDscp)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_trap_unknownUnicastPktAction_set
 * Description:
 *      Set unknown unicast packet action configuration.
 * Input:
 *      type            - Unknown unicast packet type.
 *      ucast_action    - Unknown unicast action.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK              	- OK
 *      RT_ERR_FAILED          	- Failed
 *      RT_ERR_SMI             	- SMI access error
 *      RT_ERR_NOT_ALLOWED 		- Invalid action.
 *      RT_ERR_INPUT 			- Invalid input parameters.
 * Note:
 *      This API can set unknown unicast packet action configuration.
 *      (1) The unknown unicast packet type is as following:
 *          - UCAST_UNKNOWNDA
 *          - UCAST_UNKNOWNSA
 *          - UCAST_UNMATCHSA
 *      (2) The unknown unicast action is as following:
 *          - UCAST_ACTION_FORWARD
 *          - UCAST_ACTION_DROP
 *          - UCAST_ACTION_TRAP2CPU
 */
int rtk_trap_unknownUnicastPktAction_set(rtk_trap_ucast_type_t type, rtk_trap_ucast_action_t ucast_action)
{
    int ret_val;

    if (type >= UCAST_END)
        return RT_ERR_INPUT;

    if (ucast_action >= UCAST_ACTION_END)
        return RT_ERR_INPUT;


    switch (type)
    {
        case UCAST_UNKNOWNDA:
            if ((ret_val = rtl8367b_setAsicPortUnknownDaBehavior(ucast_action)) != RT_ERR_OK)
                return ret_val;
            break;
        case UCAST_UNKNOWNSA:
            if ((ret_val = rtl8367b_setAsicPortUnknownSaBehavior(ucast_action)) != RT_ERR_OK)
                return ret_val;
            break;
        case UCAST_UNMATCHSA:
            if ((ret_val = rtl8367b_setAsicPortUnmatchedSaBehavior(ucast_action)) != RT_ERR_OK)
                return ret_val;
            break;
        default:
            break;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_trap_unknownUnicastPktAction_get
 * Description:
 *      Get unknown unicast packet action configuration.
 * Input:
 *      type - unknown unicast packet type.
 * Output:
 *      pUcast_action - unknown unicast action.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT 		- Invalid input parameters.
 * Note:
 *      This API can get unknown unicast packet action configuration.
 *      (1) The unknown unicast packet type is as following:
 *          - UCAST_UNKNOWNDA
 *          - UCAST_UNKNOWNSA
 *          - UCAST_UNMATCHSA
 *      (2) The unknown unicast action is as following:
 *          - UCAST_ACTION_FORWARD
 *          - UCAST_ACTION_DROP
 *          - UCAST_ACTION_TRAP2CPU
 */
int rtk_trap_unknownUnicastPktAction_get(rtk_trap_ucast_type_t type, rtk_trap_ucast_action_t *pUcast_action)
{
    int ret_val;

    if (type >= UCAST_END)
        return RT_ERR_INPUT;

    switch (type)
    {
        case UCAST_UNKNOWNDA:
            if ((ret_val = rtl8367b_getAsicPortUnknownDaBehavior(pUcast_action)) != RT_ERR_OK)
                return ret_val;
            break;
        case UCAST_UNKNOWNSA:
            if ((ret_val = rtl8367b_getAsicPortUnknownSaBehavior((unsigned int*)pUcast_action)) != RT_ERR_OK)
                return ret_val;
            break;
        case UCAST_UNMATCHSA:
            if ((ret_val = rtl8367b_getAsicPortUnmatchedSaBehavior((unsigned int*)pUcast_action)) != RT_ERR_OK)
                return ret_val;
            break;
        default:
            break;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_trap_rmaAction_set
 * Description:
 *      Set reserved multicast address frame trap to CPU.
 * Input:
 *      pRma_frame - Reserved multicast address.
 *      rma_action - RMA action.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK              	- OK
 *      RT_ERR_FAILED          	- Failed
 *      RT_ERR_SMI             	- SMI access error
 *      RT_ERR_NOT_ALLOWED 		- Invalid action.
 *      RT_ERR_INPUT 			- Invalid input parameters.
 * Note:
 *      There are 48 types of Reserved Multicast Address frame for application usage.
 *      (1) They are as following definition.
 *      - DMAC                        Assignment
 *      - 01-80-C2-00-00-00           Bridge Group Address
 *      - 01-80-C2-00-00-01           IEEE Std 802.3, 1988 Edition Full Duplex PAUSE operation
 *      - 01-80-C2-00-00-02           IEEE Std 802.3ad Slow Protocols-Multicast Address
 *      - 01-80-C2-00-00-03           IEEE Std 802.1X PAE address
 *      - 01-80-C2-00-00-04           Undefined 802.1 bridge address 04
 *      - 01-80-C2-00-00-05           Undefined 802.1 bridge address 05
 *      - 01-80-C2-00-00-06           Undefined 802.1 bridge address 06
 *      - 01-80-C2-00-00-07           Undefined 802.1 bridge address 07
 *      - 01-80-C2-00-00-08           Provider Bridge Group Address
 *      - 01-80-C2-00-00-09           Undefined 802.1 bridge address 09
 *      - 01-80-C2-00-00-0A           Undefined 802.1 bridge address 0A
 *      - 01-80-C2-00-00-0B           Undefined 802.1 bridge address 0B
 *      - 01-80-C2-00-00-0C           Undefined 802.1 bridge address 0C
 *      - 01-80-C2-00-00-0D           Provider Bridge GVRP Address
 *      - 01-80-C2-00-00-0E           IEEE Std 802.1ab Link Layer Discovery Protocol Multicast address
 *      - 01-80-C2-00-00-0F           Undefined 802.1 bridge address
 *      - 01-80-C2-00-00-10           All LANs Bridge Management Group Address
 *      - 01-80-C2-00-00-11~1F        Undefined address 11~1F
 *      - 01-80-C2-00-00-20           GMRP Address
 *      - 01-80-C2-00-00-21           GVRP address
 *      - 01-80-C2-00-00-22~2F        Undefined GARP address 22~2F
 *      (2) The RMA action is as following:
 *      - RMA_ACTION_FORWARD
 *      - RMA_ACTION_TRAP2CPU
 *      - RMA_ACTION_DROP
 *      - RMA_ACTION_FORWARD_EXCLUDE_CPU
 */
int rtk_trap_rmaAction_set(rtk_mac_t *pRma_frame, rtk_trap_rma_action_t rma_action)
{
    int ret_val;
    rtl8367b_rma_t rmacfg;

    if (pRma_frame->octet[0] != 0x01 && pRma_frame->octet[1] != 0x80 && pRma_frame->octet[2] != 0xC2
        && pRma_frame->octet[3] != 0 && pRma_frame->octet[4] != 0 && pRma_frame->octet[5] > 0x2F)
        return RT_ERR_RMA_ADDR;

    if (rma_action >= RMA_ACTION_END)
        return RT_ERR_RMA_ACTION;

    if ((ret_val = rtl8367b_getAsicRma(pRma_frame->octet[5], &rmacfg)) != RT_ERR_OK)
        return ret_val;

    rmacfg.operation = rma_action;

    if ((ret_val = rtl8367b_setAsicRma(pRma_frame->octet[5], &rmacfg)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_trap_rmaAction_get
 * Description:
 *      Get reserved multicast address frame trap to CPU.
 * Input:
 *      type - unknown unicast packet type.
 * Output:
 *      pRma_action - RMA action.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT 		- Invalid input parameters.
 * Note:
 *      The API can retrieved RMA configuration.
 *      (1) They are as following definition.
 *      - DMAC                        Assignment
 *      - 01-80-C2-00-00-00           Bridge Group Address
 *      - 01-80-C2-00-00-01           IEEE Std 802.3, 1988 Edition Full Duplex PAUSE operation
 *      - 01-80-C2-00-00-02           IEEE Std 802.3ad Slow Protocols-Multicast Address
 *      - 01-80-C2-00-00-03           IEEE Std 802.1X PAE address
 *      - 01-80-C2-00-00-04           Undefined 802.1 bridge address 04
 *      - 01-80-C2-00-00-05           Undefined 802.1 bridge address 05
 *      - 01-80-C2-00-00-06           Undefined 802.1 bridge address 06
 *      - 01-80-C2-00-00-07           Undefined 802.1 bridge address 07
 *      - 01-80-C2-00-00-08           Provider Bridge Group Address
 *      - 01-80-C2-00-00-09           Undefined 802.1 bridge address 09
 *      - 01-80-C2-00-00-0A           Undefined 802.1 bridge address 0A
 *      - 01-80-C2-00-00-0B           Undefined 802.1 bridge address 0B
 *      - 01-80-C2-00-00-0C           Undefined 802.1 bridge address 0C
 *      - 01-80-C2-00-00-0D           Provider Bridge GVRP Address
 *      - 01-80-C2-00-00-0E           IEEE Std 802.1ab Link Layer Discovery Protocol Multicast address
 *      - 01-80-C2-00-00-0F           Undefined 802.1 bridge address
 *      - 01-80-C2-00-00-10           All LANs Bridge Management Group Address
 *      - 01-80-C2-00-00-11~1F        Undefined address 11~1F
 *      - 01-80-C2-00-00-20           GMRP Address
 *      - 01-80-C2-00-00-21           GVRP address
 *      - 01-80-C2-00-00-22~2F        Undefined GARP address 22~2F
 *      (2) The RMA action is as following:
 *      - RMA_ACTION_FORWARD
 *      - RMA_ACTION_TRAP2CPU
 *      - RMA_ACTION_DROP
 *      - RMA_ACTION_FORWARD_EXCLUDE_CPU
 */
int rtk_trap_rmaAction_get(rtk_mac_t *pRma_frame, rtk_trap_rma_action_t *pRma_action)
{
    int ret_val;
    rtl8367b_rma_t rmacfg;

    if (pRma_frame->octet[0] != 0x01 && pRma_frame->octet[1] != 0x80 && pRma_frame->octet[2] != 0xC2
        && pRma_frame->octet[3] !=0 && pRma_frame->octet[4] != 0 && pRma_frame->octet[5] > 0x2F)
        return RT_ERR_RMA_ADDR;

    if ((ret_val = rtl8367b_getAsicRma(pRma_frame->octet[5], &rmacfg)) != RT_ERR_OK)
        return ret_val;

    *pRma_action = rmacfg.operation;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_trap_igmpCtrlPktAction_set
 * Description:
 *      Set IGMP/MLD trap function
 * Input:
 *      type        - IGMP/MLD packet type.
 *      igmp_action - IGMP/MLD action.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT 		- Invalid input parameters.
 *      RT_ERR_NOT_ALLOWED 	- Invalid igmp action.
 * Note:
 *      This API can set both IPv4 IGMP/IPv6 MLD with/without PPPoE header trapping function.
 *      All 4 kinds of IGMP/MLD function can be set seperately.
 *      (1) The IGMP/MLD packet type is as following:
 *          - IGMP_IPV4
 *          - IGMP_PPPOE_IPV4
 *          - IGMP_MLD
 *          - IGMP_PPPOE_MLD
 *      (2) The IGMP/MLD action is as following:
 *          - IGMP_ACTION_FORWARD
 *          - IGMP_ACTION_TRAP2CPU
 *          - IGMP_ACTION_DROP
 *          - IGMP_ACTION_FORWARD_EXCLUDE_CPU
 */
int rtk_trap_igmpCtrlPktAction_set(rtk_igmp_type_t type, rtk_trap_igmp_action_t igmp_action)
{
    int   ret_val;
    unsigned int          igmp_op;
    unsigned int      port;

    if (type >= IGMP_TYPE_END)
        return RT_ERR_INPUT;

    if (igmp_action >= IGMP_ACTION_END)
        return RT_ERR_NOT_ALLOWED;

    switch (igmp_action)
    {
        case IGMP_ACTION_FORWARD:
            igmp_op = PROTOCOL_OP_FLOOD;
            break;
        case IGMP_ACTION_TRAP2CPU:
            igmp_op = PROTOCOL_OP_TRAP;
            break;
        case IGMP_ACTION_DROP:
            igmp_op = PROTOCOL_OP_DROP;
            break;
        case IGMP_ACTION_FORWARD_EXCLUDE_CPU:
            return RT_ERR_CHIP_NOT_SUPPORTED;
        case IGMP_ACTION_ASIC:
            igmp_op = PROTOCOL_OP_ASIC;
            break;
        default:
            return RT_ERR_CHIP_NOT_SUPPORTED;
    }

    switch (type)
    {
        case IGMP_MLD:
            for(port = 0; port <= RTK_PORT_ID_MAX; port++)
            {
                if ((ret_val = rtl8367b_setAsicMLDv1Opeartion(port, igmp_op)) != RT_ERR_OK)
                    return ret_val;
                if ((ret_val = rtl8367b_setAsicMLDv2Opeartion(port, igmp_op)) != RT_ERR_OK)
                    return ret_val;
            }
            break;
        case IGMP_IPV4:
            for(port = 0; port <= RTK_PORT_ID_MAX; port++)
            {
                if ((ret_val = rtl8367b_setAsicIGMPv1Opeartion(port, igmp_op)) != RT_ERR_OK)
                    return ret_val;
                if ((ret_val = rtl8367b_setAsicIGMPv2Opeartion(port, igmp_op)) != RT_ERR_OK)
                    return ret_val;
                if ((ret_val = rtl8367b_setAsicIGMPv3Opeartion(port, igmp_op)) != RT_ERR_OK)
                    return ret_val;
            }
            break;
        case IGMP_PPPOE_IPV4:
        case IGMP_PPPOE_MLD:
        default:
            return RT_ERR_CHIP_NOT_SUPPORTED;
    }

    return RT_ERR_OK;
}


/* Function Name:
 *      rtk_trap_igmpCtrlPktAction_get
 * Description:
 *      Get IGMP/MLD trap function
 * Input:
 *      type - IGMP/MLD packet type.
 * Output:
 *      pIgmp_action - IGMP/MLD action.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT 		- Invalid input parameters.
 * Note:
 *      This API can get both IPv4 IGMP/IPv6 MLD with/without PPPoE header trapping function.
 *      (1) The IGMP/MLD packet type is as following:
 *          - IGMP_IPV4
 *          - IGMP_PPPOE_IPV4
 *          - IGMP_MLD
 *          - IGMP_PPPOE_MLD
 *      (2) The IGMP/MLD action is as following:
 *          - IGMP_ACTION_FORWARD
 *          - IGMP_ACTION_TRAP2CPU
 *          - IGMP_ACTION_DROP
 *          - IGMP_ACTION_FORWARD_EXCLUDE_CPU
 */
int rtk_trap_igmpCtrlPktAction_get(rtk_igmp_type_t type, rtk_trap_igmp_action_t *pIgmp_action)
{
    int   ret_val;
    unsigned int          igmp_op;

    if (type >= IGMP_TYPE_END)
        return RT_ERR_INPUT;

    switch (type)
    {
        case IGMP_IPV4:
            if ((ret_val = rtl8367b_getAsicIGMPv1Opeartion(0, &igmp_op)) != RT_ERR_OK)
                return ret_val;
            break;
        case IGMP_PPPOE_IPV4:
            return RT_ERR_CHIP_NOT_SUPPORTED;
        case IGMP_MLD:
            if ((ret_val = rtl8367b_getAsicMLDv1Opeartion(0, &igmp_op)) != RT_ERR_OK)
                return ret_val;
            break;
        case IGMP_PPPOE_MLD:
            return RT_ERR_CHIP_NOT_SUPPORTED;
        default:
            return RT_ERR_CHIP_NOT_SUPPORTED;
    }

    switch(igmp_op)
    {
        case PROTOCOL_OP_ASIC:
            *pIgmp_action = IGMP_ACTION_ASIC;
            break;
        case PROTOCOL_OP_FLOOD:
            *pIgmp_action = IGMP_ACTION_FORWARD;
            break;
        case PROTOCOL_OP_TRAP:
            *pIgmp_action = IGMP_ACTION_TRAP2CPU;
            break;
        case PROTOCOL_OP_DROP:
            *pIgmp_action = IGMP_ACTION_DROP;
            break;
        default:
            return RT_ERR_CHIP_NOT_SUPPORTED;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_trap_unknownMcastPktAction_set
 * Description:
 *      Set behavior of unknown multicast
 * Input:
 *      port            - Port id.
 *      type            - unknown multicast packet type.
 *      mcast_action    - unknown multicast action.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID 		- Invalid port number.
 *      RT_ERR_NOT_ALLOWED 	- Invalid action.
 *      RT_ERR_INPUT 		- Invalid input parameters.
 * Note:
 *      When receives an unknown multicast packet, switch may trap, drop or flood this packet
 *      (1) The unknown multicast packet type is as following:
 *          - MCAST_L2
 *          - MCAST_IPV4
 *          - MCAST_IPV6
 *      (2) The unknown multicast action is as following:
 *          - MCAST_ACTION_FORWARD
 *          - MCAST_ACTION_DROP
 *          - MCAST_ACTION_TRAP2CPU
 */
int rtk_trap_unknownMcastPktAction_set(unsigned int port, rtk_mcast_type_t type, rtk_trap_mcast_action_t mcast_action)
{
    int ret_val;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if (type >= MCAST_END)
        return RT_ERR_INPUT;

    if (mcast_action >= MCAST_ACTION_END)
        return RT_ERR_INPUT;


    switch (type)
    {
        case MCAST_L2:
            if (MCAST_ACTION_ROUTER_PORT == mcast_action)
                return RT_ERR_INPUT;
            if ((ret_val = rtl8367b_setAsicUnknownL2MulticastBehavior(port, mcast_action)) != RT_ERR_OK)
                return ret_val;
            break;
        case MCAST_IPV4:
            if ((ret_val = rtl8367b_setAsicUnknownIPv4MulticastBehavior(port, mcast_action)) != RT_ERR_OK)
                return ret_val;
            break;
        case MCAST_IPV6:
            if ((ret_val = rtl8367b_setAsicUnknownIPv6MulticastBehavior(port, mcast_action)) != RT_ERR_OK)
                return ret_val;
            break;
        default:
            break;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_trap_unknownMcastPktAction_get
 * Description:
 *      Get behavior of unknown multicast
 * Input:
 *      type - unknown multicast packet type.
 * Output:
 *      pMcast_action - unknown multicast action.
 * Return:
 *      RT_ERR_OK              	- OK
 *      RT_ERR_FAILED          	- Failed
 *      RT_ERR_SMI             	- SMI access error
 *      RT_ERR_PORT_ID 			- Invalid port number.
 *      RT_ERR_NOT_ALLOWED 		- Invalid operation.
 *      RT_ERR_INPUT 			- Invalid input parameters.
 * Note:
 *      When receives an unknown multicast packet, switch may trap, drop or flood this packet
 *      (1) The unknown multicast packet type is as following:
 *          - MCAST_L2
 *          - MCAST_IPV4
 *          - MCAST_IPV6
 *      (2) The unknown multicast action is as following:
 *          - MCAST_ACTION_FORWARD
 *          - MCAST_ACTION_DROP
 *          - MCAST_ACTION_TRAP2CPU
 */
int rtk_trap_unknownMcastPktAction_get(unsigned int port, rtk_mcast_type_t type, rtk_trap_mcast_action_t *pMcast_action)
{
    int ret_val;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if (type >= MCAST_END)
        return RT_ERR_INPUT;

    switch (type)
    {
        case MCAST_L2:
            if ((ret_val = rtl8367b_getAsicUnknownL2MulticastBehavior(port, pMcast_action)) != RT_ERR_OK)
                return ret_val;
            break;
        case MCAST_IPV4:
            if ((ret_val = rtl8367b_getAsicUnknownIPv4MulticastBehavior(port, pMcast_action)) != RT_ERR_OK)
                return ret_val;
            break;
        case MCAST_IPV6:
            if ((ret_val = rtl8367b_getAsicUnknownIPv6MulticastBehavior(port, (unsigned int*)pMcast_action)) != RT_ERR_OK)
                return ret_val;
            break;
        default:
            break;
    }
    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_trap_ethernetAv_set
 * Description:
 *      Set Ethetnet AV.
 * Input:
 *      enable - enable trap
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK              	- OK
 *      RT_ERR_FAILED          	- Failed
 *      RT_ERR_SMI             	- SMI access error
 *      RT_ERR_PORT_ID 			- Invalid port number.
 *      RT_ERR_QOS_INT_PRIORITY - Invalid priority.
 *      RT_ERR_ENABLE 			- Invalid enable parameter.
 * Note:
 *      The API can enable or disable ethernet AV function. If the function is enabled,
 *      packets with ethernet type 0x88F7 will be trap to CPU with time stamp.
 *      The status of Ethernet AV:
 *      - DISABLED
 *      - ENABLED
 */
int rtk_trap_ethernetAv_set(rtk_enable_t enable)
{
    int ret_val;
    unsigned int port;

    if (enable >= RTK_ENABLE_END)
        return RT_ERR_INPUT;

    for(port = 0; port <= RTK_PORT_ID_MAX; port++)
    {
        if ((ret_val = rtl8367b_setAsicEavEnable(port, enable)) != RT_ERR_OK)
            return ret_val;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_trap_ethernetAv_get
 * Description:
 *      Get ethernet AV setup.
 * Input:
 * Output:
 *      pEnable - status of ethernet AV.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID 		- Invalid port number.
 * Note:
 *      The API can get ethernet AV status. If the function is enabled,
 *      packets with ethernet type 0x88F7 will be trap to CPU with time stamp.
 *      The status of Ethernet AV:
 *      - DISABLED
 *      - ENABLED
 */
int rtk_trap_ethernetAv_get(rtk_enable_t *pEnable)
{
    int ret_val;

    if ((ret_val = rtl8367b_getAsicEavEnable(0, pEnable)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_storm_controlRate_set
 * Description:
 *      Set per-port storm filter control rate.
 * Input:
 *      port        - Port id
 *      storm_type  - Storm filter control type
 *      rate        - Rate of storm filter control
 *      ifg_include - include IFG or not, ENABLE:include DISABLE:exclude
 *      mode        - Mode
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK              		- OK
 *      RT_ERR_FAILED          		- Failed
 *      RT_ERR_SMI             		- SMI access error
 *      RT_ERR_PORT_ID 				- Invalid port number.
 *      RT_ERR_INPUT 				- Invalid input parameters.
 *      RT_ERR_SFC_UNKNOWN_GROUP 	- unknown storm filter group.
 *      RT_ERR_ENABLE 				- Invalid IFG parameter
 *      RT_ERR_RATE 				- Invalid rate
 * Note:
 *      This API can set per-port stomr filter control rate.
 *      The storm filter control type can be:
 *          - STORM_GROUP_UNKNOWN_UNICAST
 *          - STORM_GROUP_UNKNOWN_MULTICAST
 *          - STORM_GROUP_MULTICAST
 *          - STORM_GROUP_BROADCAST
 *      The rate unit is 1 kbps and the range is from 8k to 1048568k. The granularity of rate is 8 kbps.
 *      The ifg_include parameter is used for rate calculation with/without inter-frame-gap and preamble.
 *      In mode 0:
 *      Use rate to assign storm control rate.
 *      Use ifg_include to control inter-frame-gap include or not.
 *      In mode 1:
 *      Use rate to assign storm control shared meter index.
 *      Use ifg_include to be storm control enable/disable parameter.
 */
int rtk_storm_controlRate_set(unsigned int port, rtk_rate_storm_group_t storm_type, rtk_rate_t rate, rtk_enable_t ifg_include, rtk_mode_t mode)
{
    int ret_val;
    unsigned int enable;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if (storm_type >= STORM_GROUP_END)
        return RT_ERR_SFC_UNKNOWN_GROUP;

    if (mode >= MODE_END)
        return RT_ERR_INPUT;

    if (mode == MODE0)
    {
        if (rate > RTL8367B_QOS_RATE_INPUT_MAX || rate < RTL8367B_QOS_RATE_INPUT_MIN || (rate % RTL8367B_QOS_GRANULARTY_UNIT_KBPS))
            return RT_ERR_RATE ;

        if (RTL8367B_QOS_RATE_INPUT_MAX == rate)
            enable = FALSE;
        else
            enable = TRUE;

        switch (storm_type)
        {
            case STORM_GROUP_UNKNOWN_UNICAST:
                if ((ret_val = rtl8367b_setAsicStormFilterUnknownUnicastEnable(port, enable)) != RT_ERR_OK)
                    return ret_val;
                if (enable)
                {
                    if ((ret_val = rtl8367b_setAsicStormFilterUnknownUnicastMeter(port, STORM_UNUC_INDEX)) != RT_ERR_OK)
                        return ret_val;
                    if ((ret_val = rtl8367b_setAsicShareMeter(STORM_UNUC_INDEX, rate >> 3, ifg_include)) != RT_ERR_OK)
                        return ret_val;
                }
                break;
            case STORM_GROUP_UNKNOWN_MULTICAST:
                if ((ret_val = rtl8367b_setAsicStormFilterUnknownMulticastEnable(port, enable)) != RT_ERR_OK)
                    return ret_val;
                if (enable)
                {
                    if ((ret_val = rtl8367b_setAsicStormFilterUnknownMulticastMeter(port,STORM_UNMC_INDEX)) != RT_ERR_OK)
                        return ret_val;
                    if ((ret_val = rtl8367b_setAsicShareMeter(STORM_UNMC_INDEX, rate >> 3, ifg_include)) != RT_ERR_OK)
                        return ret_val;
                }
                break;
            case STORM_GROUP_MULTICAST:
                if ((ret_val = rtl8367b_setAsicStormFilterMulticastEnable(port, enable)) != RT_ERR_OK)
                    return ret_val;
                if (enable)
                {
                    if ((ret_val = rtl8367b_setAsicStormFilterMulticastMeter(port, STORM_MC_INDEX)) != RT_ERR_OK)
                        return ret_val;
                    if ((ret_val = rtl8367b_setAsicShareMeter(STORM_MC_INDEX, rate >> 3, ifg_include)) != RT_ERR_OK)
                        return ret_val;
                }
                break;
            case STORM_GROUP_BROADCAST:
                if ((ret_val = rtl8367b_setAsicStormFilterBroadcastEnable(port, enable)) != RT_ERR_OK)
                    return ret_val;
                if (enable)
                {
                    if ((ret_val = rtl8367b_setAsicStormFilterBroadcastMeter(port, STORM_BC_INDEX)) != RT_ERR_OK)
                        return ret_val;
                    if ((ret_val = rtl8367b_setAsicShareMeter(STORM_BC_INDEX, rate >> 3, ifg_include)) != RT_ERR_OK)
                        return ret_val;
                }
            default:
                break;
        }
    }
    else
    {
        /*Use rate to assign storm control shared meter index in mode 1.*/
        if (rate >= RTK_MAX_NUM_OF_METER)
            return RT_ERR_FILTER_METER_ID;

        /*Use ifg_include to be storm control enable/disable parameter in mode 1.*/
        enable = ifg_include;

        switch (storm_type)
        {
            case STORM_GROUP_UNKNOWN_UNICAST:
                if ((ret_val = rtl8367b_setAsicStormFilterUnknownUnicastEnable(port,enable))!=RT_ERR_OK)
                    return ret_val;
                if ((ret_val = rtl8367b_setAsicStormFilterUnknownUnicastMeter(port,rate))!=RT_ERR_OK)
                    return ret_val;
                break;
            case STORM_GROUP_UNKNOWN_MULTICAST:
                if ((ret_val = rtl8367b_setAsicStormFilterUnknownMulticastEnable(port,enable))!=RT_ERR_OK)
                    return ret_val;
                if ((ret_val = rtl8367b_setAsicStormFilterUnknownMulticastMeter(port,rate))!=RT_ERR_OK)
                    return ret_val;
                break;
            case STORM_GROUP_MULTICAST:
                if ((ret_val = rtl8367b_setAsicStormFilterMulticastEnable(port,enable))!=RT_ERR_OK)
                    return ret_val;
                if ((ret_val = rtl8367b_setAsicStormFilterMulticastMeter(port,rate))!=RT_ERR_OK)
                    return ret_val;
                break;
            case STORM_GROUP_BROADCAST:
                if ((ret_val = rtl8367b_setAsicStormFilterBroadcastEnable(port,enable))!=RT_ERR_OK)
                    return ret_val;
                if ((ret_val = rtl8367b_setAsicStormFilterBroadcastMeter(port,rate))!=RT_ERR_OK)
                    return ret_val;
            default:
                break;
        }
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_storm_controlRate_get
 * Description:
 *      Get per-port packet storm filter control rate.
 * Input:
 *      port        - Port id
 *      storm_type  - Storm filter control type.
 *      mode        - Mode
 * Output:
 *      pRate           - Rate of storm filter control.
 *      pIfg_include    - Rate's calculation including IFG, ENABLE:include DISABLE:exclude
 * Return:
 *      RT_ERR_OK              		- OK
 *      RT_ERR_FAILED          		- Failed
 *      RT_ERR_SMI             		- SMI access error
 *      RT_ERR_PORT_ID 				- Invalid port number.
 *      RT_ERR_INPUT 				- Invalid input parameters.
 *      RT_ERR_SFC_UNKNOWN_GROUP 	- unknown storm filter group.
 * Note:
 *      The storm filter control type can be:
 *          - STORM_GROUP_UNKNOWN_UNICAST
 *          - STORM_GROUP_UNKNOWN_MULTICAST
 *          - STORM_GROUP_MULTICAST
 *          - STORM_GROUP_BROADCAST
 *      In mode 0:
 *      pRate is assigned to get storm control rate.
 *      pIfg_include is assigned to get inter-frame-gap include or not.
 *      In mode 1:
 *      pRate is assigned to get storm control shared meter index.
 *      pIfg_include is assigned to get storm control enable/disable parameter.
 */
int rtk_storm_controlRate_get(unsigned int port, rtk_rate_storm_group_t storm_type, rtk_rate_t *pRate, rtk_enable_t *pIfg_include, rtk_mode_t mode)
{
    int ret_val;
    unsigned int enable;
    unsigned int index;
    unsigned int regData;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if (storm_type >= STORM_GROUP_END)
        return RT_ERR_SFC_UNKNOWN_GROUP;

    if (mode >= MODE_END)
        return RT_ERR_INPUT;

    if (mode == MODE0)
    {
        switch (storm_type)
        {
            case STORM_GROUP_UNKNOWN_UNICAST:
                if ((ret_val = rtl8367b_getAsicStormFilterUnknownUnicastEnable(port, &enable)) != RT_ERR_OK)
                    return ret_val;
                if (enable)
                {
                    if ((ret_val = rtl8367b_getAsicStormFilterUnknownUnicastMeter(port, &index)) != RT_ERR_OK)
                        return ret_val;
                    if ((ret_val = rtl8367b_getAsicShareMeter(index, &regData, pIfg_include)) != RT_ERR_OK)
                        return ret_val;
                    *pRate = regData << 3;
                }
                else
                {
                    *pRate = 0x1FFFF << 3;
                }
                break;
            case STORM_GROUP_UNKNOWN_MULTICAST:
                if ((ret_val = rtl8367b_getAsicStormFilterUnknownMulticastEnable(port, &enable)) != RT_ERR_OK)
                    return ret_val;
                if (enable)
                {
                    if ((ret_val = rtl8367b_getAsicStormFilterUnknownMulticastMeter(port, &index)) != RT_ERR_OK)
                        return ret_val;
                    if ((ret_val = rtl8367b_getAsicShareMeter(index, &regData, pIfg_include)) != RT_ERR_OK)
                        return ret_val;
                    *pRate = regData << 3;
                }
                else
                {
                    *pRate = 0x1FFFF << 3;
                }
                break;
            case STORM_GROUP_MULTICAST:
                if ((ret_val = rtl8367b_getAsicStormFilterMulticastEnable(port, &enable)) != RT_ERR_OK)
                    return ret_val;
                if (enable)
                {
                    if ((ret_val = rtl8367b_getAsicStormFilterMulticastMeter(port, &index)) != RT_ERR_OK)
                        return ret_val;
                    if ((ret_val = rtl8367b_getAsicShareMeter(index, &regData, pIfg_include)) != RT_ERR_OK)
                        return ret_val;
                    *pRate = regData << 3;
                }
                else
                {
                    *pRate = 0x1FFFF << 3;
                }
                break;
            case STORM_GROUP_BROADCAST:
                if ((ret_val = rtl8367b_getAsicStormFilterBroadcastEnable(port, &enable)) != RT_ERR_OK)
                    return ret_val;
                if (enable)
                {
                    if ((ret_val = rtl8367b_getAsicStormFilterBroadcastMeter(port, &index)) != RT_ERR_OK)
                        return ret_val;
                    if ((ret_val = rtl8367b_getAsicShareMeter(index, &regData, pIfg_include)) != RT_ERR_OK)
                        return ret_val;
                    *pRate = regData << 3;
                }
                else
                {
                    *pRate = 0x1FFFF << 3;
                }
                break;
            default:
                break;
        }
    }
    else
    {
        /*Use pRate to assign storm control shared meter index in mode 1.*/
        /*Use pIfg_include to be storm control enable/disable parameter in mode 1.*/
        switch (storm_type)
        {
            case STORM_GROUP_UNKNOWN_UNICAST:
                if ((ret_val = rtl8367b_getAsicStormFilterUnknownUnicastEnable(port,pIfg_include))!=RT_ERR_OK)
                    return ret_val;
                if ((ret_val = rtl8367b_getAsicStormFilterUnknownUnicastMeter(port,pRate))!=RT_ERR_OK)
                    return ret_val;
                break;
            case STORM_GROUP_UNKNOWN_MULTICAST:
                if ((ret_val = rtl8367b_getAsicStormFilterUnknownMulticastEnable(port,pIfg_include))!=RT_ERR_OK)
                    return ret_val;
                if ((ret_val = rtl8367b_getAsicStormFilterUnknownMulticastMeter(port,pRate))!=RT_ERR_OK)
                    return ret_val;
                break;
            case STORM_GROUP_MULTICAST:
                if ((ret_val = rtl8367b_getAsicStormFilterMulticastEnable(port,pIfg_include))!=RT_ERR_OK)
                    return ret_val;
                if ((ret_val = rtl8367b_getAsicStormFilterMulticastMeter(port,pRate))!=RT_ERR_OK)
                    return ret_val;
                break;
            case STORM_GROUP_BROADCAST:
                if ((ret_val = rtl8367b_getAsicStormFilterBroadcastEnable(port,pIfg_include))!=RT_ERR_OK)
                    return ret_val;
                if ((ret_val = rtl8367b_getAsicStormFilterBroadcastMeter(port,pRate))!=RT_ERR_OK)
                    return ret_val;
                break;
            default:
                break;
        }
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_storm_bypass_set
 * Description:
 *      Set bypass storm filter control configuration.
 * Input:
 *      type    - Bypass storm filter control type.
 *      enable  - Bypass status.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT 		- Invalid input parameters.
 *      RT_ERR_ENABLE 		- Invalid IFG parameter
 * Note:
 *
 *      This API can set per-port bypass stomr filter control frame type including RMA and igmp.
 *      The bypass frame type is as following:
 *      - BYPASS_BRG_GROUP,
 *      - BYPASS_FD_PAUSE,
 *      - BYPASS_SP_MCAST,
 *      - BYPASS_1X_PAE,
 *      - BYPASS_UNDEF_BRG_04,
 *      - BYPASS_UNDEF_BRG_05,
 *      - BYPASS_UNDEF_BRG_06,
 *      - BYPASS_UNDEF_BRG_07,
 *      - BYPASS_PROVIDER_BRIDGE_GROUP_ADDRESS,
 *      - BYPASS_UNDEF_BRG_09,
 *      - BYPASS_UNDEF_BRG_0A,
 *      - BYPASS_UNDEF_BRG_0B,
 *      - BYPASS_UNDEF_BRG_0C,
 *      - BYPASS_PROVIDER_BRIDGE_GVRP_ADDRESS,
 *      - BYPASS_8021AB,
 *      - BYPASS_UNDEF_BRG_0F,
 *      - BYPASS_BRG_MNGEMENT,
 *      - BYPASS_UNDEFINED_11,
 *      - BYPASS_UNDEFINED_12,
 *      - BYPASS_UNDEFINED_13,
 *      - BYPASS_UNDEFINED_14,
 *      - BYPASS_UNDEFINED_15,
 *      - BYPASS_UNDEFINED_16,
 *      - BYPASS_UNDEFINED_17,
 *      - BYPASS_UNDEFINED_18,
 *      - BYPASS_UNDEFINED_19,
 *      - BYPASS_UNDEFINED_1A,
 *      - BYPASS_UNDEFINED_1B,
 *      - BYPASS_UNDEFINED_1C,
 *      - BYPASS_UNDEFINED_1D,
 *      - BYPASS_UNDEFINED_1E,
 *      - BYPASS_UNDEFINED_1F,
 *      - BYPASS_GMRP,
 *      - BYPASS_GVRP,
 *      - BYPASS_UNDEF_GARP_22,
 *      - BYPASS_UNDEF_GARP_23,
 *      - BYPASS_UNDEF_GARP_24,
 *      - BYPASS_UNDEF_GARP_25,
 *      - BYPASS_UNDEF_GARP_26,
 *      - BYPASS_UNDEF_GARP_27,
 *      - BYPASS_UNDEF_GARP_28,
 *      - BYPASS_UNDEF_GARP_29,
 *      - BYPASS_UNDEF_GARP_2A,
 *      - BYPASS_UNDEF_GARP_2B,
 *      - BYPASS_UNDEF_GARP_2C,
 *      - BYPASS_UNDEF_GARP_2D,
 *      - BYPASS_UNDEF_GARP_2E,
 *      - BYPASS_UNDEF_GARP_2F,
 *      - BYPASS_IGMP.
 */
int rtk_storm_bypass_set(rtk_storm_bypass_t type, rtk_enable_t enable)
{
    int ret_val;
    rtl8367b_rma_t rmacfg;

    if (type >= BYPASS_END)
        return RT_ERR_INPUT;

    if (enable >= RTK_ENABLE_END)
        return RT_ERR_INPUT;

    if (type >= 0 && type <= BYPASS_UNDEF_GARP_2F)
    {
        if ((ret_val = rtl8367b_getAsicRma(type, &rmacfg)) != RT_ERR_OK)
            return ret_val;

        rmacfg.discard_storm_filter = enable;

        if ((ret_val = rtl8367b_setAsicRma(type, &rmacfg)) != RT_ERR_OK)
            return ret_val;
    }
    else if(type == BYPASS_IGMP)
    {
        if ((ret_val = rtl8367b_setAsicIGMPBypassStormCTRL(enable)) != RT_ERR_OK)
            return ret_val;
    }
    else
        return RT_ERR_INPUT;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_storm_bypass_get
 * Description:
 *      Get bypass storm filter control configuration.
 * Input:
 *      type - Bypass storm filter control type.
 * Output:
 *      pEnable - Bypass status.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT 		- Invalid input parameters.
 * Note:
 *      This API can get per-port bypass stomr filter control frame type including RMA and igmp.
 *      The bypass frame type is as following:
 *      - BYPASS_BRG_GROUP,
 *      - BYPASS_FD_PAUSE,
 *      - BYPASS_SP_MCAST,
 *      - BYPASS_1X_PAE,
 *      - BYPASS_UNDEF_BRG_04,
 *      - BYPASS_UNDEF_BRG_05,
 *      - BYPASS_UNDEF_BRG_06,
 *      - BYPASS_UNDEF_BRG_07,
 *      - BYPASS_PROVIDER_BRIDGE_GROUP_ADDRESS,
 *      - BYPASS_UNDEF_BRG_09,
 *      - BYPASS_UNDEF_BRG_0A,
 *      - BYPASS_UNDEF_BRG_0B,
 *      - BYPASS_UNDEF_BRG_0C,
 *      - BYPASS_PROVIDER_BRIDGE_GVRP_ADDRESS,
 *      - BYPASS_8021AB,
 *      - BYPASS_UNDEF_BRG_0F,
 *      - BYPASS_BRG_MNGEMENT,
 *      - BYPASS_UNDEFINED_11,
 *      - BYPASS_UNDEFINED_12,
 *      - BYPASS_UNDEFINED_13,
 *      - BYPASS_UNDEFINED_14,
 *      - BYPASS_UNDEFINED_15,
 *      - BYPASS_UNDEFINED_16,
 *      - BYPASS_UNDEFINED_17,
 *      - BYPASS_UNDEFINED_18,
 *      - BYPASS_UNDEFINED_19,
 *      - BYPASS_UNDEFINED_1A,
 *      - BYPASS_UNDEFINED_1B,
 *      - BYPASS_UNDEFINED_1C,
 *      - BYPASS_UNDEFINED_1D,
 *      - BYPASS_UNDEFINED_1E,
 *      - BYPASS_UNDEFINED_1F,
 *      - BYPASS_GMRP,
 *      - BYPASS_GVRP,
 *      - BYPASS_UNDEF_GARP_22,
 *      - BYPASS_UNDEF_GARP_23,
 *      - BYPASS_UNDEF_GARP_24,
 *      - BYPASS_UNDEF_GARP_25,
 *      - BYPASS_UNDEF_GARP_26,
 *      - BYPASS_UNDEF_GARP_27,
 *      - BYPASS_UNDEF_GARP_28,
 *      - BYPASS_UNDEF_GARP_29,
 *      - BYPASS_UNDEF_GARP_2A,
 *      - BYPASS_UNDEF_GARP_2B,
 *      - BYPASS_UNDEF_GARP_2C,
 *      - BYPASS_UNDEF_GARP_2D,
 *      - BYPASS_UNDEF_GARP_2E,
 *      - BYPASS_UNDEF_GARP_2F,
 *      - BYPASS_IGMP.
 */
int rtk_storm_bypass_get(rtk_storm_bypass_t type, rtk_enable_t *pEnable)
{
    int ret_val;
    rtl8367b_rma_t rmacfg;

    if (type >= BYPASS_END)
        return RT_ERR_INPUT;

    if (type >= 0 && type <= BYPASS_UNDEF_GARP_2F)
    {
        if ((ret_val = rtl8367b_getAsicRma(type, &rmacfg)) != RT_ERR_OK)
            return ret_val;

        *pEnable = rmacfg.discard_storm_filter;
    }
    else if(type == BYPASS_IGMP)
    {
        if ((ret_val = rtl8367b_getAsicIGMPBypassStormCTRL(pEnable)) != RT_ERR_OK)
            return ret_val;
    }
    else
        return RT_ERR_INPUT;

    return RT_ERR_OK;
}

static int _rtk_port_FiberModeAbility_set(unsigned int port, rtk_port_phy_ability_t *pAbility)
{
    int   ret_val;

    if (port != RTK_PORT_COMBO_ID)
        return RT_ERR_PORT_ID;

    if( (pAbility->Full_1000 == 1) && (pAbility->Full_100 == 1) && (pAbility->AutoNegotiation == 1) )
    {
        if ((ret_val = rtl8367b_setAsicRegBits(RTL8367B_REG_SDS_CFG4, RTL8367B_CFG_FRC_SDS_MODE_MASK, RTK_FIBER_FORCE_100M1000M)) != RT_ERR_OK)
            return ret_val;

        if ((ret_val = rtl8367b_setAsicRegBits(RTL8367B_REG_SDS_CFG4, RTL8367B_CFG_FRC_SDS_MODE_EN_MASK, 1)) != RT_ERR_OK)
            return ret_val;
    }
    else if(pAbility->Full_1000 == 1)
    {
        if ((ret_val = rtl8367b_setAsicRegBits(RTL8367B_REG_SDS_CFG4, RTL8367B_CFG_FRC_SDS_MODE_MASK, RTK_FIBER_FORCE_1000M)) != RT_ERR_OK)
            return ret_val;

        if ((ret_val = rtl8367b_setAsicRegBits(RTL8367B_REG_SDS_CFG4, RTL8367B_CFG_FRC_SDS_MODE_EN_MASK, 1)) != RT_ERR_OK)
            return ret_val;
    }
    else if(pAbility->Full_100 == 1)
    {
        if ((ret_val = rtl8367b_setAsicRegBits(RTL8367B_REG_SDS_CFG4, RTL8367B_CFG_FRC_SDS_MODE_MASK, RTK_FIBER_FORCE_100M)) != RT_ERR_OK)
            return ret_val;

        if ((ret_val = rtl8367b_setAsicRegBits(RTL8367B_REG_SDS_CFG4, RTL8367B_CFG_FRC_SDS_MODE_EN_MASK, 0)) != RT_ERR_OK)
            return ret_val;
    }

    return RT_ERR_OK;
}

static int _rtk_port_FiberModeAbility_get(unsigned int port, rtk_port_phy_ability_t *pAbility)
{
    int   ret_val;
    unsigned int      speed, auto_detect;

    if (port != RTK_PORT_COMBO_ID)
        return RT_ERR_PORT_ID;

    memset(pAbility, 0x00, sizeof(rtk_port_phy_ability_t));

    if ((ret_val = rtl8367b_getAsicRegBits(RTL8367B_REG_SDS_CFG4, RTL8367B_CFG_FRC_SDS_MODE_MASK, &speed)) != RT_ERR_OK)
        return ret_val;

    if(speed == RTK_FIBER_FORCE_100M1000M)
    {
        pAbility->Full_1000 = 1;
        pAbility->Full_100 = 1;
    }
    else if(speed == RTK_FIBER_FORCE_1000M)
        pAbility->Full_1000 = 1;
    else if(speed == RTK_FIBER_FORCE_100M)
        pAbility->Full_100 = 1;

    if ((ret_val = rtl8367b_getAsicRegBits(RTL8367B_REG_SDS_CFG4, RTL8367B_CFG_FRC_SDS_MODE_EN_MASK, &auto_detect)) != RT_ERR_OK)
        return ret_val;

    if(auto_detect == 1)
        pAbility->AutoNegotiation = 1;
    else
        pAbility->AutoNegotiation = 0;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_port_phyAutoNegoAbility_set
 * Description:
 *      Set ethernet PHY auto-negotiation desired ability.
 * Input:
 *      port        - port id.
 *      pAbility    - Ability structure
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK              	- OK
 *      RT_ERR_FAILED          	- Failed
 *      RT_ERR_SMI             	- SMI access error
 *      RT_ERR_PORT_ID 			- Invalid port number.
 *      RT_ERR_PHY_REG_ID 		- Invalid PHY address
 *      RT_ERR_INPUT 			- Invalid input parameters.
 *      RT_ERR_BUSYWAIT_TIMEOUT - PHY access busy
 * Note:
 *      If Full_1000 bit is set to 1, the AutoNegotiation will be automatic set to 1. While both AutoNegotiation and Full_1000 are set to 0, the PHY speed and duplex selection will
 *      be set as following 100F > 100H > 10F > 10H priority sequence.
 */
int rtk_port_phyAutoNegoAbility_set(unsigned int port, rtk_port_phy_ability_t *pAbility)
{
    int       ret_val;
    unsigned int          phyData;
    unsigned int          phyEnMsk0;
    unsigned int          phyEnMsk4;
    unsigned int          phyEnMsk9;
    rtk_port_media_t    media_type;


    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if (pAbility->Half_10 >= RTK_ENABLE_END || pAbility->Full_10 >= RTK_ENABLE_END ||
       pAbility->Half_100 >= RTK_ENABLE_END || pAbility->Full_100 >= RTK_ENABLE_END ||
       pAbility->Full_1000 >= RTK_ENABLE_END || pAbility->AutoNegotiation >= RTK_ENABLE_END ||
       pAbility->AsyFC >= RTK_ENABLE_END || pAbility->FC >= RTK_ENABLE_END)
        return RT_ERR_INPUT;

    /*for PHY auto mode setup*/
    pAbility->AutoNegotiation = 1;

    if (port == RTK_PORT_COMBO_ID)
    {
        if ((ret_val = rtk_port_phyComboPortMedia_get(port, &media_type)) != RT_ERR_OK)
            return ret_val;

        if(media_type == PORT_MEDIA_FIBER)
        {
            return _rtk_port_FiberModeAbility_set(port, pAbility);
        }
    }

    phyEnMsk0 = 0;
    phyEnMsk4 = 0;
    phyEnMsk9 = 0;

    if (1 == pAbility->Half_10)
    {
        /*10BASE-TX half duplex capable in reg 4.5*/
        phyEnMsk4 = phyEnMsk4 | (1 << 5);

        /*Speed selection [1:0] */
        /* 11=Reserved*/
        /* 10= 1000Mpbs*/
        /* 01= 100Mpbs*/
        /* 00= 10Mpbs*/
        phyEnMsk0 = phyEnMsk0 & (~(1 << 6));
        phyEnMsk0 = phyEnMsk0 & (~(1 << 13));
    }

    if (1 == pAbility->Full_10)
    {
        /*10BASE-TX full duplex capable in reg 4.6*/
        phyEnMsk4 = phyEnMsk4 | (1 << 6);
        /*Speed selection [1:0] */
        /* 11=Reserved*/
        /* 10= 1000Mpbs*/
        /* 01= 100Mpbs*/
        /* 00= 10Mpbs*/
        phyEnMsk0 = phyEnMsk0 & (~(1 << 6));
        phyEnMsk0 = phyEnMsk0 & (~(1 << 13));

        /*Full duplex mode in reg 0.8*/
        phyEnMsk0 = phyEnMsk0 | (1 << 8);

    }

    if (1 == pAbility->Half_100)
    {
        /*100BASE-TX half duplex capable in reg 4.7*/
        phyEnMsk4 = phyEnMsk4 | (1 << 7);
        /*Speed selection [1:0] */
        /* 11=Reserved*/
        /* 10= 1000Mpbs*/
        /* 01= 100Mpbs*/
        /* 00= 10Mpbs*/
        phyEnMsk0 = phyEnMsk0 & (~(1 << 6));
        phyEnMsk0 = phyEnMsk0 | (1 << 13);
    }


    if (1 == pAbility->Full_100)
    {
        /*100BASE-TX full duplex capable in reg 4.8*/
        phyEnMsk4 = phyEnMsk4 | (1 << 8);
        /*Speed selection [1:0] */
        /* 11=Reserved*/
        /* 10= 1000Mpbs*/
        /* 01= 100Mpbs*/
        /* 00= 10Mpbs*/
        phyEnMsk0 = phyEnMsk0 & (~(1 << 6));
        phyEnMsk0 = phyEnMsk0 | (1 << 13);
        /*Full duplex mode in reg 0.8*/
        phyEnMsk0 = phyEnMsk0 | (1 << 8);
    }


    if (1 == pAbility->Full_1000)
    {
        /*1000 BASE-T FULL duplex capable setting in reg 9.9*/
        phyEnMsk9 = phyEnMsk9 | (1 << 9);

        /*Speed selection [1:0] */
        /* 11=Reserved*/
        /* 10= 1000Mpbs*/
        /* 01= 100Mpbs*/
        /* 00= 10Mpbs*/
        phyEnMsk0 = phyEnMsk0 | (1 << 6);
        phyEnMsk0 = phyEnMsk0 & (~(1 << 13));


        /*Auto-Negotiation setting in reg 0.12*/
        phyEnMsk0 = phyEnMsk0 | (1 << 12);

     }

    if (1 == pAbility->AutoNegotiation)
    {
        /*Auto-Negotiation setting in reg 0.12*/
        phyEnMsk0 = phyEnMsk0 | (1 << 12);
    }

    if (1 == pAbility->AsyFC)
    {
        /*Asymetric flow control in reg 4.11*/
        phyEnMsk4 = phyEnMsk4 | (1 << 11);
    }
    if (1 == pAbility->FC)
    {
        /*Flow control in reg 4.10*/
        phyEnMsk4 = phyEnMsk4 | (1 << 10);
    }

    if ((ret_val = rtl8367b_setAsicPHYReg(port, RTL8367B_PHY_PAGE_ADDRESS, 0)) != RT_ERR_OK)
        return ret_val;

    /*1000 BASE-T control register setting*/
    if ((ret_val = rtl8367b_getAsicPHYReg(port, PHY_1000_BASET_CONTROL_REG, &phyData)) != RT_ERR_OK)
        return ret_val;

    phyData = (phyData & (~0x0200)) | phyEnMsk9 ;

    if ((ret_val = rtl8367b_setAsicPHYReg(port, PHY_1000_BASET_CONTROL_REG, phyData)) != RT_ERR_OK)
        return ret_val;

    /*Auto-Negotiation control register setting*/
    if ((ret_val = rtl8367b_getAsicPHYReg(port, PHY_AN_ADVERTISEMENT_REG, &phyData)) != RT_ERR_OK)
        return ret_val;

    phyData = (phyData & (~0x0DE0)) | phyEnMsk4;
    if ((ret_val = rtl8367b_setAsicPHYReg(port, PHY_AN_ADVERTISEMENT_REG, phyData)) != RT_ERR_OK)
        return ret_val;

    /*Control register setting and restart auto*/
    if ((ret_val = rtl8367b_getAsicPHYReg(port, PHY_CONTROL_REG, &phyData)) != RT_ERR_OK)
        return ret_val;

    phyData = (phyData & (~0x3140)) | phyEnMsk0;
    /*If have auto-negotiation capable, then restart auto negotiation*/
    if (1 == pAbility->AutoNegotiation)
    {
        phyData = phyData | (1 << 9);
    }

    if ((ret_val = rtl8367b_setAsicPHYReg(port, PHY_CONTROL_REG, phyData)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_port_phyAutoNegoAbility_get
 * Description:
 *      Get PHY ability through PHY registers.
 * Input:
 *      port - Port id.
 * Output:
 *      pAbility - Ability structure
 * Return:
 *      RT_ERR_OK              	- OK
 *      RT_ERR_FAILED          	- Failed
 *      RT_ERR_SMI             	- SMI access error
 *      RT_ERR_PORT_ID 			- Invalid port number.
 *      RT_ERR_PHY_REG_ID 		- Invalid PHY address
 *      RT_ERR_INPUT 			- Invalid input parameters.
 *      RT_ERR_BUSYWAIT_TIMEOUT - PHY access busy
 * Note:
 *      Get the capablity of specified PHY.
 */
int rtk_port_phyAutoNegoAbility_get(unsigned int port, rtk_port_phy_ability_t *pAbility)
{
    int       ret_val;
    unsigned int          phyData0;
    unsigned int          phyData4;
    unsigned int          phyData9;
    rtk_port_media_t    media_type;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if (port == RTK_PORT_COMBO_ID)
    {
        if ((ret_val = rtk_port_phyComboPortMedia_get(port, &media_type)) != RT_ERR_OK)
            return ret_val;

        if(media_type == PORT_MEDIA_FIBER)
        {
            return _rtk_port_FiberModeAbility_set(port, pAbility);
        }
    }

    if ((ret_val = rtl8367b_setAsicPHYReg(port, RTL8367B_PHY_PAGE_ADDRESS, 0)) != RT_ERR_OK)
        return ret_val;

    /*Control register setting and restart auto*/
    if ((ret_val = rtl8367b_getAsicPHYReg(port, PHY_CONTROL_REG, &phyData0)) != RT_ERR_OK)
        return ret_val;

    /*Auto-Negotiation control register setting*/
    if ((ret_val = rtl8367b_getAsicPHYReg(port, PHY_AN_ADVERTISEMENT_REG, &phyData4)) != RT_ERR_OK)
        return ret_val;

    /*1000 BASE-T control register setting*/
    if ((ret_val = rtl8367b_getAsicPHYReg(port, PHY_1000_BASET_CONTROL_REG, &phyData9)) != RT_ERR_OK)
        return ret_val;

    if (phyData9 & (1 << 9))
        pAbility->Full_1000 = 1;
    else
        pAbility->Full_1000 = 0;

    if (phyData4 & (1 << 11))
        pAbility->AsyFC = 1;
    else
        pAbility->AsyFC = 0;

    if (phyData4 & (1 << 10))
        pAbility->FC = 1;
    else
        pAbility->FC = 0;


    if (phyData4 & (1 << 8))
        pAbility->Full_100 = 1;
    else
        pAbility->Full_100 = 0;

    if (phyData4 & (1 << 7))
        pAbility->Half_100 = 1;
    else
        pAbility->Half_100 = 0;

    if (phyData4 & (1 << 6))
        pAbility->Full_10 = 1;
    else
        pAbility->Full_10 = 0;

    if (phyData4 & (1 << 5))
        pAbility->Half_10 = 1;
    else
        pAbility->Half_10 = 0;


    if (phyData0 & (1 << 12))
        pAbility->AutoNegotiation = 1;
    else
        pAbility->AutoNegotiation = 0;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_port_phyForceModeAbility_set
 * Description:
 *      Set the port speed/duplex mode/pause/asy_pause in the PHY force mode.
 * Input:
 *      port        - port id.
 *      pAbility    - Ability structure
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK              	- OK
 *      RT_ERR_FAILED          	- Failed
 *      RT_ERR_SMI             	- SMI access error
 *      RT_ERR_PORT_ID 			- Invalid port number.
 *      RT_ERR_PHY_REG_ID 		- Invalid PHY address
 *      RT_ERR_INPUT 			- Invalid input parameters.
 *      RT_ERR_BUSYWAIT_TIMEOUT - PHY access busy
 * Note:
 *      If Full_1000 bit is set to 1, the AutoNegotiation will be automatic set to 1.
 *      While both AutoNegotiation and Full_1000 are set to 0, the PHY speed and duplex selection will
 *      be set as following 100F > 100H > 10F > 10H priority sequence.
 *      This API can be used to configure combo port in fiber mode.
 *      The possible parameters in fiber mode are Full_1000 and Full 100.
 *      All the other fields in rtk_port_phy_ability_t will be ignored in fiber port.
 */
int rtk_port_phyForceModeAbility_set(unsigned int port, rtk_port_phy_ability_t *pAbility)
{
     int      ret_val;
     unsigned int         phyData;
     unsigned int         phyEnMsk0;
     unsigned int         phyEnMsk4;
     unsigned int         phyEnMsk9;
     rtk_port_media_t   media_type;

     if (port > RTK_PHY_ID_MAX)
         return RT_ERR_PORT_ID;

     if (pAbility->Half_10 >= RTK_ENABLE_END || pAbility->Full_10 >= RTK_ENABLE_END ||
        pAbility->Half_100 >= RTK_ENABLE_END || pAbility->Full_100 >= RTK_ENABLE_END ||
        pAbility->Full_1000 >= RTK_ENABLE_END || pAbility->AutoNegotiation >= RTK_ENABLE_END ||
        pAbility->AsyFC >= RTK_ENABLE_END || pAbility->FC >= RTK_ENABLE_END)
         return RT_ERR_INPUT;

     if (1 == pAbility->Full_1000)
         return RT_ERR_INPUT;

     if (port == RTK_PORT_COMBO_ID)
     {
         if ((ret_val = rtk_port_phyComboPortMedia_get(port, &media_type)) != RT_ERR_OK)
             return ret_val;

         if(media_type == PORT_MEDIA_FIBER)
         {
             return _rtk_port_FiberModeAbility_set(port, pAbility);
         }
     }

     /*for PHY force mode setup*/
     pAbility->AutoNegotiation = 0;

     phyEnMsk0 = 0;
     phyEnMsk4 = 0;
     phyEnMsk9 = 0;

     if (1 == pAbility->Half_10)
     {
         /*10BASE-TX half duplex capable in reg 4.5*/
         phyEnMsk4 = phyEnMsk4 | (1 << 5);

         /*Speed selection [1:0] */
         /* 11=Reserved*/
         /* 10= 1000Mpbs*/
         /* 01= 100Mpbs*/
         /* 00= 10Mpbs*/
         phyEnMsk0 = phyEnMsk0 & (~(1 << 6));
         phyEnMsk0 = phyEnMsk0 & (~(1 << 13));
     }

     if (1 == pAbility->Full_10)
     {
         /*10BASE-TX full duplex capable in reg 4.6*/
         phyEnMsk4 = phyEnMsk4 | (1 << 6);
         /*Speed selection [1:0] */
         /* 11=Reserved*/
         /* 10= 1000Mpbs*/
         /* 01= 100Mpbs*/
         /* 00= 10Mpbs*/
         phyEnMsk0 = phyEnMsk0 & (~(1 << 6));
         phyEnMsk0 = phyEnMsk0 & (~(1 << 13));

         /*Full duplex mode in reg 0.8*/
         phyEnMsk0 = phyEnMsk0 | (1 << 8);

     }

     if (1 == pAbility->Half_100)
     {
         /*100BASE-TX half duplex capable in reg 4.7*/
         phyEnMsk4 = phyEnMsk4 | (1 << 7);
         /*Speed selection [1:0] */
         /* 11=Reserved*/
         /* 10= 1000Mpbs*/
         /* 01= 100Mpbs*/
         /* 00= 10Mpbs*/
         phyEnMsk0 = phyEnMsk0 & (~(1 << 6));
         phyEnMsk0 = phyEnMsk0 | (1 << 13);
     }


     if (1 == pAbility->Full_100)
     {
         /*100BASE-TX full duplex capable in reg 4.8*/
         phyEnMsk4 = phyEnMsk4 | (1 << 8);
         /*Speed selection [1:0] */
         /* 11=Reserved*/
         /* 10= 1000Mpbs*/
         /* 01= 100Mpbs*/
         /* 00= 10Mpbs*/
         phyEnMsk0 = phyEnMsk0 & (~(1 << 6));
         phyEnMsk0 = phyEnMsk0 | (1 << 13);
         /*Full duplex mode in reg 0.8*/
         phyEnMsk0 = phyEnMsk0 | (1 << 8);
     }


     if (1 == pAbility->Full_1000)
     {
         /*1000 BASE-T FULL duplex capable setting in reg 9.9*/
         phyEnMsk9 = phyEnMsk9 | (1 << 9);

         /*Speed selection [1:0] */
         /* 11=Reserved*/
         /* 10= 1000Mpbs*/
         /* 01= 100Mpbs*/
         /* 00= 10Mpbs*/
         phyEnMsk0 = phyEnMsk0 | (1 << 6);
         phyEnMsk0 = phyEnMsk0 & (~(1 << 13));


         /*Auto-Negotiation setting in reg 0.12*/
         phyEnMsk0 = phyEnMsk0 | (1 << 12);

     }

     if (1 == pAbility->AsyFC)
     {
         /*Asymetric flow control in reg 4.11*/
         phyEnMsk4 = phyEnMsk4 | (1 << 11);
     }
     if (1 == pAbility->FC)
     {
         /*Flow control in reg 4.10*/
         phyEnMsk4 = phyEnMsk4 | ((1 << 10));
     }

     if ((ret_val = rtl8367b_setAsicPHYReg(port, RTL8367B_PHY_PAGE_ADDRESS, 0)) != RT_ERR_OK)
         return ret_val;

     /*1000 BASE-T control register setting*/
     if ((ret_val = rtl8367b_getAsicPHYReg(port, PHY_1000_BASET_CONTROL_REG, &phyData)) != RT_ERR_OK)
         return ret_val;

     phyData = (phyData & (~0x0200)) | phyEnMsk9 ;

     if ((ret_val = rtl8367b_setAsicPHYReg(port, PHY_1000_BASET_CONTROL_REG, phyData)) != RT_ERR_OK)
         return ret_val;

     /*Auto-Negotiation control register setting*/
     if ((ret_val = rtl8367b_getAsicPHYReg(port, PHY_AN_ADVERTISEMENT_REG, &phyData)) != RT_ERR_OK)
         return ret_val;

     phyData = (phyData & (~0x0DE0)) | phyEnMsk4;
     if ((ret_val = rtl8367b_setAsicPHYReg(port, PHY_AN_ADVERTISEMENT_REG, phyData)) != RT_ERR_OK)
         return ret_val;

     /*Control register setting and power off/on*/
     phyData = phyEnMsk0 & (~(1 << 12));
     phyData |= (1 << 11);   /* power down PHY, bit 11 should be set to 1 */
     if ((ret_val = rtl8367b_setAsicPHYReg(port, PHY_CONTROL_REG, phyData)) != RT_ERR_OK)
         return ret_val;

     phyData = phyData & (~(1 << 11));   /* power on PHY, bit 11 should be set to 0*/
     if ((ret_val = rtl8367b_setAsicPHYReg(port, PHY_CONTROL_REG, phyData)) != RT_ERR_OK)
         return ret_val;

     return RT_ERR_OK;
}

/* Function Name:
 *      rtk_port_phyForceModeAbility_get
 * Description:
 *      Get PHY ability through PHY registers.
 * Input:
 *      port - Port id.
 * Output:
 *      pAbility - Ability structure
 * Return:
 *      RT_ERR_OK              	- OK
 *      RT_ERR_FAILED          	- Failed
 *      RT_ERR_SMI             	- SMI access error
 *      RT_ERR_PORT_ID 			- Invalid port number.
 *      RT_ERR_PHY_REG_ID 		- Invalid PHY address
 *      RT_ERR_INPUT 			- Invalid input parameters.
 *      RT_ERR_BUSYWAIT_TIMEOUT - PHY access busy
 * Note:
 *      Get the capablity of specified PHY.
 */
int rtk_port_phyForceModeAbility_get(unsigned int port, rtk_port_phy_ability_t *pAbility)
{
    int       ret_val;
    unsigned int          phyData0;
    unsigned int          phyData4;
    unsigned int          phyData9;
    rtk_port_media_t    media_type;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

     if (port == RTK_PORT_COMBO_ID)
     {
         if ((ret_val = rtk_port_phyComboPortMedia_get(port, &media_type)) != RT_ERR_OK)
             return ret_val;

         if(media_type == PORT_MEDIA_FIBER)
         {
             return _rtk_port_FiberModeAbility_get(port, pAbility);
         }
     }

    if ((ret_val = rtl8367b_setAsicPHYReg(port, RTL8367B_PHY_PAGE_ADDRESS, 0)) != RT_ERR_OK)
        return ret_val;

    /*Control register setting and restart auto*/
    if ((ret_val = rtl8367b_getAsicPHYReg(port, PHY_CONTROL_REG, &phyData0)) != RT_ERR_OK)
        return ret_val;

    /*Auto-Negotiation control register setting*/
    if ((ret_val = rtl8367b_getAsicPHYReg(port, PHY_AN_ADVERTISEMENT_REG, &phyData4)) != RT_ERR_OK)
        return ret_val;

    /*1000 BASE-T control register setting*/
    if ((ret_val = rtl8367b_getAsicPHYReg(port, PHY_1000_BASET_CONTROL_REG, &phyData9)) != RT_ERR_OK)
        return ret_val;

    if (phyData9 & (1 << 9))
        pAbility->Full_1000 = 1;
    else
        pAbility->Full_1000 = 0;

    if (phyData4 & (1 << 11))
        pAbility->AsyFC = 1;
    else
        pAbility->AsyFC = 0;

    if (phyData4 & ((1 << 10)))
        pAbility->FC = 1;
    else
        pAbility->FC = 0;


    if (phyData4 & (1 << 8))
        pAbility->Full_100 = 1;
    else
        pAbility->Full_100 = 0;

    if (phyData4 & (1 << 7))
        pAbility->Half_100 = 1;
    else
        pAbility->Half_100 = 0;

    if (phyData4 & (1 << 6))
        pAbility->Full_10 = 1;
    else
        pAbility->Full_10 = 0;

    if (phyData4 & (1 << 5))
        pAbility->Half_10 = 1;
    else
        pAbility->Half_10 = 0;


    if (phyData0 & (1 << 12))
        pAbility->AutoNegotiation = 1;
    else
        pAbility->AutoNegotiation = 0;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_port_phyStatus_get
 * Description:
 *      Get ethernet PHY linking status
 * Input:
 *      port - Port id.
 * Output:
 *      linkStatus  - PHY link status
 *      speed       - PHY link speed
 *      duplex      - PHY duplex mode
 * Return:
 *      RT_ERR_OK              	- OK
 *      RT_ERR_FAILED          	- Failed
 *      RT_ERR_SMI             	- SMI access error
 *      RT_ERR_PORT_ID 			- Invalid port number.
 *      RT_ERR_PHY_REG_ID 		- Invalid PHY address
 *      RT_ERR_INPUT 			- Invalid input parameters.
 *      RT_ERR_BUSYWAIT_TIMEOUT - PHY access busy
 * Note:
 *      API will return auto negotiation status of phy.
 */
int rtk_port_phyStatus_get(unsigned int port, unsigned int *pLinkStatus, unsigned int *pSpeed, unsigned int *pDuplex)
{
    int ret_val;
    unsigned int phyData;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if ((ret_val = rtl8367b_setAsicPHYReg(port, RTL8367B_PHY_PAGE_ADDRESS, 0)) != RT_ERR_OK)
        return ret_val;

    /*Get PHY status register*/
    if (RT_ERR_OK != rtl8367b_getAsicPHYReg(port, PHY_STATUS_REG, &phyData))
        return RT_ERR_FAILED;

    if (RT_ERR_OK != rtl8367b_getAsicPHYReg(port, PHY_STATUS_REG, &phyData))
        return RT_ERR_FAILED;

    /*check link status*/
    if (phyData & (1<<2))
    {
        *pLinkStatus = 1;

        /*Get PHY resolved register*/
        if ((ret_val = rtl8367b_getAsicPHYReg(port, PHY_RESOLVED_REG, &phyData)) != RT_ERR_OK)
            return ret_val;

        /*check resolution is complete or not*/
        if (!(phyData&(1 << 11)))
            return RT_ERR_BUSYWAIT_TIMEOUT;

        /*check link speed*/
        *pSpeed = (phyData&0xC000) >> 14;

        /*check link duplex*/
        *pDuplex = (phyData&0x2000) >> 13;
    }
    else
    {
        *pLinkStatus = 0;
        *pSpeed = 0;
        *pDuplex = 0;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_port_phyTestMode_set
 * Description:
 *      Set PHY in test mode.
 * Input:
 *      port - port id.
 *      mode - PHY test mode 0:normal 1:test mode 1 2:test mode 2 3: test mode 3 4:test mode 4 5~7:reserved
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK              	- OK
 *      RT_ERR_FAILED          	- Failed
 *      RT_ERR_SMI             	- SMI access error
 *      RT_ERR_PORT_ID 			- Invalid port number.
 *      RT_ERR_BUSYWAIT_TIMEOUT - PHY access busy
 *      RT_ERR_NOT_ALLOWED      - The Setting is not allowed, caused by set more than 1 port in Test mode.
 * Note:
 *      Set PHY in test mode and only one PHY can be in test mode at the same time.
 *      It means API will return FAILED if other PHY is in test mode.
 *      This API only provide test mode 1 & 4 setup, and if users want other test modes,
 *      please contact realtek FAE.
 */
int rtk_port_phyTestMode_set(unsigned int port, rtk_port_phy_test_mode_t mode)
{
    unsigned int          data, i, index, phy, reg;
    int       ret_val;
    const unsigned short ParaTM_1[][2] = { {0x205F,0x0002}, {0x2053,0xAA00}, {0x2054,0xAA00}, {0x2055,0xAA00},
                                         {0x2056,0xAA00}, {0x2057,0xAA00}, {0x205F,0x0002} };

    if (port > RTK_PHY_ID_MAX)
        return RT_ERR_PORT_ID;

    if ( (mode == PHY_TEST_MODE_2) || (mode == PHY_TEST_MODE_3) )
        return RT_ERR_FAILED;

    if (PHY_TEST_MODE_NORMAL != mode)
    {
        /* Other port should be Normal mode */
        for(i = 0; i <= RTK_PHY_ID_MAX; i++)
        {
            if(i != port)
            {
                if ((ret_val = rtl8367b_setAsicPHYReg(i, 31, 0)) != RT_ERR_OK)
                    return ret_val;

                if ((ret_val = rtl8367b_getAsicPHYReg(i, 9, &data)) != RT_ERR_OK)
                    return ret_val;

                if((data & 0xE000) != 0)
                    return RT_ERR_NOT_ALLOWED;
            }
        }
    }

    if (PHY_TEST_MODE_1 == mode)
    {
        for (index = 0; index < (sizeof(ParaTM_1) / ((sizeof(unsigned short))*2)); index++)
        {
            phy = (ParaTM_1[index][0] - 0x2000) / 0x0020;
            reg = (ParaTM_1[index][0] - 0x2000) % 0x0020;
            if ((ret_val = rtl8367b_setAsicPHYReg(phy, reg, ParaTM_1[index][1])) != RT_ERR_OK)
                return ret_val;
        }
    }

    if ((ret_val = rtl8367b_setAsicPHYReg(port, 31, 0)) != RT_ERR_OK)
        return ret_val;

    if ((ret_val = rtl8367b_getAsicPHYReg(port, 9, &data)) != RT_ERR_OK)
        return ret_val;

    data &= ~0xE000;
    data |= (mode << 13);
    if ((ret_val = rtl8367b_setAsicPHYReg(port, 9, data)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_port_phyTestMode_get
 * Description:
 *      Get PHY in which test mode.
 * Input:
 *      port - Port id.
 * Output:
 *      mode - PHY test mode 0:normal 1:test mode 1 2:test mode 2 3: test mode 3 4:test mode 4 5~7:reserved
 * Return:
 *      RT_ERR_OK              	- OK
 *      RT_ERR_FAILED          	- Failed
 *      RT_ERR_SMI             	- SMI access error
 *      RT_ERR_PORT_ID 			- Invalid port number.
 *      RT_ERR_INPUT 			- Invalid input parameters.
 *      RT_ERR_BUSYWAIT_TIMEOUT - PHY access busy
 * Note:
 *      Get test mode of PHY from register setting 9.15 to 9.13.
 */
int rtk_port_phyTestMode_get(unsigned int port, rtk_port_phy_test_mode_t *pMode)
{
    unsigned int      data;
    int   ret_val;

    if (port > RTK_PHY_ID_MAX)
        return RT_ERR_PORT_ID;

    if ((ret_val = rtl8367b_setAsicPHYReg(port, 31, 0)) != RT_ERR_OK)
        return ret_val;

    if ((ret_val = rtl8367b_getAsicPHYReg(port, 9, &data)) != RT_ERR_OK)
        return ret_val;

    *pMode = (data & 0xE000) >> 13;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_port_phy1000BaseTMasterSlave_set
 * Description:
 *      Set PHY control enable MASTER/SLAVE manual configuration.
 * Input:
 *      port - port id.
 *      enable - Manual configuration function 1:enable 0:disable.
 *      masterslave - Manual config mode 1:master 0: slave
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK              	- OK
 *      RT_ERR_FAILED          	- Failed
 *      RT_ERR_SMI             	- SMI access error
 *      RT_ERR_PORT_ID 			- Invalid port number.
 *      RT_ERR_BUSYWAIT_TIMEOUT - PHY access busy
 *      RT_ERR_ENABLE 			- Invalid enable input.
 * Note:
 *      Set enable/disable MASTER/SLAVE manual configuration under 1000Base-T with register 9.12-9.11. If MASTER/SLAVE manual configuration is enabled with MASTER, the
 *      link partner must be set as SLAVE or auto negotiation will fail.
 */
int rtk_port_phy1000BaseTMasterSlave_set(unsigned int port, rtk_enable_t enable, rtk_enable_t masterslave)
{
    int ret_val;
    unsigned int phyData;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if ((ret_val = rtl8367b_setAsicPHYReg(port, RTL8367B_PHY_PAGE_ADDRESS, 0)) != RT_ERR_OK)
        return ret_val;

    if ((ret_val = rtl8367b_getAsicPHYReg(port, PHY_1000_BASET_CONTROL_REG, &phyData)) != RT_ERR_OK)
        return ret_val;

    phyData = (phyData & (~(0x3 << 11))) | (enable << 12) | (masterslave << 11);

    if ((ret_val = rtl8367b_setAsicPHYReg(port, PHY_1000_BASET_CONTROL_REG, phyData)) != RT_ERR_OK)
        return ret_val;

    if ((ret_val = rtl8367b_setAsicPHYReg(port, PHY_1000_BASET_CONTROL_REG, phyData)) != RT_ERR_OK)
        return ret_val;

    /*Restart N-way*/
    if ((ret_val = rtl8367b_getAsicPHYReg(port, PHY_CONTROL_REG, &phyData)) != RT_ERR_OK)
        return ret_val;


    phyData = phyData | (1 << 9);
    if ((ret_val = rtl8367b_setAsicPHYReg(port, PHY_CONTROL_REG, phyData)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_port_macForceLink_set
 * Description:
 *      Set port force linking configuration.
 * Input:
 *      port            - port id.
 *      pPortability    - port ability configuration
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID 		- Invalid port number.
 * Note:
 *      This API can set Port/MAC force mode properties.
 */
int rtk_port_macForceLink_set(unsigned int port, rtk_port_mac_ability_t *pPortability)
{
    int ret_val;
    rtl8367b_port_ability_t ability;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if (pPortability->forcemode >1|| pPortability->speed > 2 || pPortability->duplex > 1 ||
       pPortability->link > 1 || pPortability->nway > 1 || pPortability->txpause > 1 || pPortability->rxpause > 1)
        return RT_ERR_INPUT;

    if ((ret_val = rtl8367b_getAsicPortForceLink(port, &ability)) != RT_ERR_OK)
        return ret_val;

    ability.forcemode = pPortability->forcemode;
    ability.speed     = pPortability->speed;
    ability.duplex    = pPortability->duplex;
    ability.link      = pPortability->link;
    ability.nway      = pPortability->nway;
    ability.txpause   = pPortability->txpause;
    ability.rxpause   = pPortability->rxpause;

    if ((ret_val = rtl8367b_setAsicPortForceLink(port, &ability)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_port_macForceLink_get
 * Description:
 *      Get port force linking configuration.
 * Input:
 *      port - Port id.
 * Output:
 *      pPortability - port ability configuration
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID 		- Invalid port number.
 *      RT_ERR_INPUT 		- Invalid input parameters.
 * Note:
 *      This API can get Port/MAC force mode properties.
 */
int rtk_port_macForceLink_get(unsigned int port, rtk_port_mac_ability_t *pPortability)
{
    int ret_val;
    rtl8367b_port_ability_t ability;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if ((ret_val = rtl8367b_getAsicPortForceLink(port, &ability)) != RT_ERR_OK)
        return ret_val;

    pPortability->forcemode = ability.forcemode;
    pPortability->speed     = ability.speed;
    pPortability->duplex    = ability.duplex;
    pPortability->link      = ability.link;
    pPortability->nway      = ability.nway;
    pPortability->txpause   = ability.txpause;
    pPortability->rxpause   = ability.rxpause;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_port_macForceLinkExt0_set
 * Description:
 *      Set external interface 0 force linking configuration.
 * Input:
 *      mode            - external interface mode
 *      pPortability    - port ability configuration
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT 		- Invalid input parameters.
 * Note:
 *      This API can set external interface 0 force mode properties.
 *      The external interface can be set to:
 *      - MODE_EXT_DISABLE,
 *      - MODE_EXT_RGMII,
 *      - MODE_EXT_MII_MAC,
 *      - MODE_EXT_MII_PHY,
 *      - MODE_EXT_TMII_MAC,
 *      - MODE_EXT_TMII_PHY,
 *      - MODE_EXT_GMII,
 *      - MODE_EXT_RMII_MAC,
 *      - MODE_EXT_RMII_PHY,
 */
int rtk_port_macForceLinkExt0_set(rtk_mode_ext_t mode, rtk_port_mac_ability_t *pPortability)
{
    return rtk_port_macForceLinkExt_set(EXT_PORT_1, mode, pPortability);
}

/* Function Name:
 *      rtk_port_macForceLinkExt0_get
 * Description:
 *      Get external interface 0 force linking configuration.
 * Input:
 *      None
 * Output:
 *      pMode           - external interface mode
 *      pPortability    - port ability configuration
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT 		- Invalid input parameters.
 * Note:
 *      This API can get external interface 0 force mode properties.
 */
int rtk_port_macForceLinkExt0_get(rtk_mode_ext_t *pMode, rtk_port_mac_ability_t *pPortability)
{
    return rtk_port_macForceLinkExt_get(EXT_PORT_1, pMode, pPortability);
}


/* Function Name:
 *      rtk_port_macForceLinkExt1_set
 * Description:
 *      Set external interface 1 force linking configuration.
 * Input:
 *      mode            - external interface mode
 *      pPortability    - port ability configuration
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT 		- Invalid input parameters.
 * Note:
 *      This API can set external interface 1 force mode properties.
 *      The external interface can be set to:
 *      - MODE_EXT_DISABLE,
 *      - MODE_EXT_RGMII,
 *      - MODE_EXT_MII_MAC,
 *      - MODE_EXT_MII_PHY,
 *      - MODE_EXT_TMII_MAC,
 *      - MODE_EXT_TMII_PHY,
 *      - MODE_EXT_GMII,
 *      - MODE_EXT_RMII_MAC,
 *      - MODE_EXT_RMII_PHY,
 */
int rtk_port_macForceLinkExt1_set(rtk_mode_ext_t mode, rtk_port_mac_ability_t *pPortability)
{
    return rtk_port_macForceLinkExt_set(EXT_PORT_0, mode, pPortability);
}

/* Function Name:
 *      rtk_port_macForceLinkExt1_get
 * Description:
 *      Get external interface 1 force linking configuration.
 * Input:
 *      None
 * Output:
 *      pMode           - external interface mode
 *      pPortability    - port ability configuration
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT 		- Invalid input parameters.
 * Note:
 *      This API can get external interface 1 force mode properties.
 */
int rtk_port_macForceLinkExt1_get(rtk_mode_ext_t *pMode, rtk_port_mac_ability_t *pPortability)
{
    return rtk_port_macForceLinkExt_get(EXT_PORT_0, pMode, pPortability);
}

/* Function Name:
 *      rtk_port_macForceLinkExt_set
 * Description:
 *      Set external interface force linking configuration.
 * Input:
 *      port            - external port ID
 *      mode            - external interface mode
 *      pPortability    - port ability configuration
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT 		- Invalid input parameters.
 * Note:
 *      This API can set external interface force mode properties.
 *      The external interface can be set to:
 *      - MODE_EXT_DISABLE,
 *      - MODE_EXT_RGMII,
 *      - MODE_EXT_MII_MAC,
 *      - MODE_EXT_MII_PHY,
 *      - MODE_EXT_TMII_MAC,
 *      - MODE_EXT_TMII_PHY,
 *      - MODE_EXT_GMII,
 *      - MODE_EXT_RMII_MAC,
 *      - MODE_EXT_RMII_PHY,
 */
int rtk_port_macForceLinkExt_set(rtk_ext_port_t port, rtk_mode_ext_t mode, rtk_port_mac_ability_t *pPortability)
{
    int ret_val;
    rtl8367b_port_ability_t ability;
    unsigned int  reg, mask;

    if (port >= EXT_PORT_END)
        return RT_ERR_INPUT;

    if (mode >=MODE_EXT_END)
        return RT_ERR_INPUT;

    if (mode == MODE_EXT_RGMII_33V)
        return RT_ERR_INPUT;

    if (pPortability->forcemode > 1 || pPortability->speed > 2 || pPortability->duplex > 1 ||
       pPortability->link > 1 || pPortability->nway > 1 || pPortability->txpause > 1 || pPortability->rxpause > 1)
        return RT_ERR_INPUT;

    if(port == EXT_PORT_0)
    {
        reg = RTL8367B_REG_DIGITAL_INTERFACE_SELECT;
        mask = RTL8367B_SELECT_GMII_0_MASK;
    }
    else if(port == EXT_PORT_1)
    {
        reg = RTL8367B_REG_DIGITAL_INTERFACE_SELECT;
        mask = RTL8367B_SELECT_GMII_1_MASK;
    }
    else if(port == EXT_PORT_2)
    {
        reg = RTL8367B_REG_DIGITAL_INTERFACE_SELECT_1;
        mask = RTL8367B_SELECT_RGMII_2_MASK;
    }
    else
        return RT_ERR_INPUT;

    if ((ret_val = rtl8367b_setAsicPortExtMode(port, mode)) != RT_ERR_OK)
        return ret_val;

    if ((ret_val = rtl8367b_getAsicPortForceLinkExt( (unsigned int)port, &ability)) != RT_ERR_OK)
        return ret_val;

    ability.forcemode = pPortability->forcemode;
    ability.speed     = pPortability->speed;
    ability.duplex    = pPortability->duplex;
    ability.link      = pPortability->link;
    ability.nway      = pPortability->nway;
    ability.txpause   = pPortability->txpause;
    ability.rxpause   = pPortability->rxpause;

    if ((ret_val = rtl8367b_setAsicPortForceLinkExt( (unsigned int)port, &ability)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_port_macForceLinkExt_get
 * Description:
 *      Set external interface force linking configuration.
 * Input:
 *      port            - external port ID
 * Output:
 *      pMode           - external interface mode
 *      pPortability    - port ability configuration
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT 		- Invalid input parameters.
 * Note:
 *      This API can get external interface force mode properties.
 */
int rtk_port_macForceLinkExt_get(rtk_ext_port_t port, rtk_mode_ext_t *pMode, rtk_port_mac_ability_t *pPortability)
{
    int ret_val;
    rtl8367b_port_ability_t ability;
    unsigned int  reg, mask;

    if (port >= EXT_PORT_END)
        return RT_ERR_INPUT;

    if(port == EXT_PORT_0)
    {
        reg = RTL8367B_REG_DIGITAL_INTERFACE_SELECT;
        mask = RTL8367B_SELECT_GMII_0_MASK;
    }
    else if(port == EXT_PORT_1)
    {
        reg = RTL8367B_REG_DIGITAL_INTERFACE_SELECT;
        mask = RTL8367B_SELECT_GMII_1_MASK;
    }
    else if(port == EXT_PORT_2)
    {
        reg = RTL8367B_REG_DIGITAL_INTERFACE_SELECT_1;
        mask = RTL8367B_SELECT_RGMII_2_MASK;
    }
    else
        return RT_ERR_INPUT;

    if ((ret_val = rtl8367b_getAsicPortExtMode(port, (unsigned int *)pMode)) != RT_ERR_OK)
        return ret_val;

    if ((ret_val = rtl8367b_getAsicPortForceLinkExt( (unsigned int)port, &ability)) != RT_ERR_OK)
        return ret_val;

    pPortability->forcemode = ability.forcemode;
    pPortability->speed     = ability.speed;
    pPortability->duplex    = ability.duplex;
    pPortability->link      = ability.link;
    pPortability->nway      = ability.nway;
    pPortability->txpause   = ability.txpause;
    pPortability->rxpause   = ability.rxpause;

    return RT_ERR_OK;

}

/* Function Name:
 *      rtk_port_macStatus_get
 * Description:
 *      Get port link status.
 * Input:
 *      port - Port id.
 * Output:
 *      pPortstatus - port ability configuration
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID 		- Invalid port number.
 * Note:
 *      This API can get Port/PHY properties.
 */
int rtk_port_macStatus_get(unsigned int port, rtk_port_mac_ability_t *pPortstatus)
{
    int ret_val;
    rtl8367b_port_status_t status;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if ((ret_val = rtl8367b_getAsicPortStatus(port, &status)) != RT_ERR_OK)
        return ret_val;

    pPortstatus->speed     = status.speed;
    pPortstatus->duplex    = status.duplex;
    pPortstatus->link      = status.link;
    pPortstatus->nway      = status.nway;
    pPortstatus->txpause   = status.txpause;
    pPortstatus->rxpause   = status.rxpause;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_port_macLocalLoopbackEnable_set
 * Description:
 *      Set Port Local Loopback. (Redirect TX to RX.)
 * Input:
 *      port    - Port id.
 *      enable  - Loopback state, 0:disable, 1:enable
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID 		- Invalid port number.
 * Note:
 *      This API can enable/disable Local loopback in MAC.
 *      For UTP port, This API will also enable the digital
 *      loopback bit in PHY register for sync of speed between
 *      PHY and MAC. For EXT port, users need to force the
 *      link state by themself.
 */
int rtk_port_macLocalLoopbackEnable_set(unsigned int port, rtk_enable_t enable)
{
    int   ret_val;
    unsigned int      data;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if ((ret_val = rtl8367b_setAsicPortLoopback(port, enable)) != RT_ERR_OK)
        return ret_val;

    if(port <= RTK_PHY_ID_MAX)
    {
        if ((ret_val = rtl8367b_getAsicPHYReg(port, PHY_CONTROL_REG, &data)) != RT_ERR_OK)
            return ret_val;

        if(enable == ENABLED)
            data |= (0x0001 << 14);
        else
            data &= ~(0x0001 << 14);

        if ((ret_val = rtl8367b_setAsicPHYReg(port, PHY_CONTROL_REG, data)) != RT_ERR_OK)
            return ret_val;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_port_macLocalLoopbackEnable_get
 * Description:
 *      Get Port Local Loopback. (Redirect TX to RX.)
 * Input:
 *      port    - Port id.
 * Output:
 *      pEnable  - Loopback state, 0:disable, 1:enable
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID 		- Invalid port number.
 * Note:
 *      None.
 */
int rtk_port_macLocalLoopbackEnable_get(unsigned int port, rtk_enable_t *pEnable)
{
    int ret_val;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if ((ret_val = rtl8367b_getAsicPortLoopback(port, pEnable)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_port_phyReg_set
 * Description:
 *      Set PHY register data of the specific port.
 * Input:
 *      port    - port id.
 *      reg     - Register id
 *      regData - Register data
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_PORT_ID          - Invalid port number.
 *      RT_ERR_PHY_REG_ID       - Invalid PHY address
 *      RT_ERR_BUSYWAIT_TIMEOUT - PHY access busy
 * Note:
 *      This API can set PHY register data of the specific port.
 */
int rtk_port_phyReg_set(unsigned int port, rtk_port_phy_reg_t reg, rtk_port_phy_data_t regData)
{
    int ret_val;

    if (port > RTK_PHY_ID_MAX)
        return RT_ERR_PORT_ID;

    if ((ret_val = rtl8367b_setAsicPHYReg(port, RTL8367B_PHY_PAGE_ADDRESS, 0)) != RT_ERR_OK)
        return ret_val;

    if ((ret_val = rtl8367b_setAsicPHYReg(port, reg, regData)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_port_phyReg_get
 * Description:
 *      Get PHY register data of the specific port.
 * Input:
 *      port    - Port id.
 *      reg     - Register id
 * Output:
 *      pData   - Register data
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_PORT_ID          - Invalid port number.
 *      RT_ERR_PHY_REG_ID       - Invalid PHY address
 *      RT_ERR_BUSYWAIT_TIMEOUT - PHY access busy
 * Note:
 *      This API can get PHY register data of the specific port.
 */
int rtk_port_phyReg_get(unsigned int port, rtk_port_phy_reg_t reg, rtk_port_phy_data_t *pData)
{
    int ret_val;

    if (port > RTK_PHY_ID_MAX)
        return RT_ERR_PORT_ID;

    if ((ret_val = rtl8367b_setAsicPHYReg(port, RTL8367B_PHY_PAGE_ADDRESS, 0)) != RT_ERR_OK)
        return ret_val;

    if ((ret_val = rtl8367b_getAsicPHYReg(port, reg, pData)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_port_backpressureEnable_set
 * Description:
 *      Set the half duplex backpressure enable status of the specific port.
 * Input:
 *      port    - port id.
 *      enable  - Back pressure status.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 *      RT_ERR_ENABLE       - Invalid enable input.
 * Note:
 *      This API can set the half duplex backpressure enable status of the specific port.
 *      The half duplex backpressure enable status of the port is as following:
 *      - DISABLE
 *      - ENABLE
 */
int rtk_port_backpressureEnable_set(unsigned int port, rtk_enable_t enable)
{
    int ret_val;

    if (port != RTK_WHOLE_SYSTEM)
        return RT_ERR_PORT_ID;

    if (enable >= RTK_ENABLE_END)
        return RT_ERR_INPUT;

    if ((ret_val = rtl8367b_setAsicPortJamMode(!enable)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_port_backpressureEnable_get
 * Description:
 *      Get the half duplex backpressure enable status of the specific port.
 * Input:
 *      port - Port id.
 * Output:
 *      pEnable - Back pressure status.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *      This API can get the half duplex backpressure enable status of the specific port.
 *      The half duplex backpressure enable status of the port is as following:
 *      - DISABLE
 *      - ENABLE
 */
int rtk_port_backpressureEnable_get(unsigned int port, rtk_enable_t *pEnable)
{
    int ret_val;
    unsigned int regData;

    if (port != RTK_WHOLE_SYSTEM)
        return RT_ERR_PORT_ID;

    if ((ret_val = rtl8367b_getAsicPortJamMode(&regData)) != RT_ERR_OK)
        return ret_val;

    *pEnable = !regData;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_port_adminEnable_set
 * Description:
 *      Set port admin configuration of the specific port.
 * Input:
 *      port    - port id.
 *      enable  - Back pressure status.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 *      RT_ERR_ENABLE       - Invalid enable input.
 * Note:
 *      This API can set port admin configuration of the specific port.
 *      The port admin configuration of the port is as following:
 *      - DISABLE
 *      - ENABLE
 */
int rtk_port_adminEnable_set(unsigned int port, rtk_enable_t enable)
{
    int ret_val;
    unsigned int      data;

    if (port > RTK_PHY_ID_MAX)
        return RT_ERR_PORT_ID;

    if (enable >= RTK_ENABLE_END)
        return RT_ERR_INPUT;

    if ((ret_val = rtk_port_phyReg_get(port, PHY_CONTROL_REG, &data)) != RT_ERR_OK)
        return ret_val;

    if (ENABLED == enable)
    {
        data &= 0xF7FF;
        data |= 0x0200;
    }
    else if (DISABLED == enable)
    {
        data |= 0x0800;
    }

    if ((ret_val = rtk_port_phyReg_set(port, PHY_CONTROL_REG, data)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_port_adminEnable_get
 * Description:
 *      Get port admin configurationof the specific port.
 * Input:
 *      port - Port id.
 * Output:
 *      pEnable - Back pressure status.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *      This API can get port admin configuration of the specific port.
 *      The port admin configuration of the port is as following:
 *      - DISABLE
 *      - ENABLE
 */
int rtk_port_adminEnable_get(unsigned int port, rtk_enable_t *pEnable)
{
    int ret_val;
    unsigned int      data;

    if (port > RTK_PHY_ID_MAX)
        return RT_ERR_PORT_ID;

    if ((ret_val = rtk_port_phyReg_get(port, PHY_CONTROL_REG, &data)) != RT_ERR_OK)
        return ret_val;

    if ( (data & 0x0800) == 0x0800)
    {
        *pEnable = DISABLED;
    }
    else
    {
        *pEnable = ENABLED;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_port_isolation_set
 * Description:
 *      Set permitted port isolation portmask
 * Input:
 *      port        - port id.
 *      portmask    - Permit port mask
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 *      RT_ERR_PORT_MASK    - Invalid portmask.
 * Note:
 *      This API set the port mask that a port can trasmit packet to of each port
 *      A port can only transmit packet to ports included in permitted portmask
 */
int rtk_port_isolation_set(unsigned int port, rtk_portmask_t portmask)
{
    int ret_val;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if ( portmask.bits[0] > RTK_MAX_PORT_MASK)
        return RT_ERR_PORT_MASK;

    if ((ret_val = rtl8367b_setAsicPortIsolationPermittedPortmask(port, portmask.bits[0])) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_port_isolation_get
 * Description:
 *      Get permitted port isolation portmask
 * Input:
 *      port - Port id.
 * Output:
 *      pPortmask - Permit port mask
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *      This API get the port mask that a port can trasmit packet to of each port
 *      A port can only transmit packet to ports included in permitted portmask
 */
int rtk_port_isolation_get(unsigned int port, rtk_portmask_t *pPortmask)
{
    int ret_val;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if ((ret_val = rtl8367b_getAsicPortIsolationPermittedPortmask(port, &pPortmask->bits[0])) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_port_rgmiiDelayExt0_set
 * Description:
 *      Set RGMII interface 0 delay value for TX and RX.
 * Input:
 *      txDelay - TX delay value, 1 for delay 2ns and 0 for no-delay
 *      rxDelay - RX delay value, 0~7 for delay setup.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      This API can set external interface 0 RGMII delay.
 *      In TX delay, there are 2 selection: no-delay and 2ns delay.
 *      In RX dekay, there are 8 steps for delay tunning. 0 for n0-delay, and 7 for maximum delay.
 */
int rtk_port_rgmiiDelayExt0_set(unsigned int txDelay, unsigned int rxDelay)
{
    return rtk_port_rgmiiDelayExt_set(EXT_PORT_1, txDelay, rxDelay);
}

/* Function Name:
 *      rtk_port_rgmiiDelayExt0_get
 * Description:
 *      Get RGMII interface 0 delay value for TX and RX.
 * Input:
 *      None
 * Output:
 *      pTxDelay - TX delay value
 *      pRxDelay - RX delay value
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT 		- Invalid input parameters.
 * Note:
 *      This API can set external interface 0 RGMII delay.
 *      In TX delay, there are 2 selection: no-delay and 2ns delay.
 *      In RX dekay, there are 8 steps for delay tunning. 0 for n0-delay, and 7 for maximum delay.
 */
int rtk_port_rgmiiDelayExt0_get(unsigned int *pTxDelay, unsigned int *pRxDelay)
{
    return rtk_port_rgmiiDelayExt_get(EXT_PORT_1, pTxDelay, pRxDelay);
}

/* Function Name:
 *      rtk_port_rgmiiDelayExt1_set
 * Description:
 *      Set RGMII interface 1 delay value for TX and RX.
 * Input:
 *      txDelay - TX delay value, 1 for delay 2ns and 0 for no-delay
 *      rxDelay - RX delay value, 0~7 for delay setup.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT 		- Invalid input parameters.
 * Note:
 *      This API can set external interface 1 RGMII delay.
 *      In TX delay, there are 2 selection: no-delay and 2ns delay.
 *      In RX dekay, there are 8 steps for delay tunning. 0 for n0-delay, and 7 for maximum delay.
 */
int rtk_port_rgmiiDelayExt1_set(unsigned int txDelay, unsigned int rxDelay)
{
    return rtk_port_rgmiiDelayExt_set(EXT_PORT_0, txDelay, rxDelay);
}

/* Function Name:
 *      rtk_port_rgmiiDelayExt1_get
 * Description:
 *      Get RGMII interface 1 delay value for TX and RX.
 * Input:
 *      None
 * Output:
 *      pTxDelay - TX delay value
 *      pRxDelay - RX delay value
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT 		- Invalid input parameters.
 * Note:
 *      This API can set external interface 1 RGMII delay.
 *      In TX delay, there are 2 selection: no-delay and 2ns delay.
 *      In RX dekay, there are 8 steps for delay tunning. 0 for n0-delay, and 7 for maximum delay.
 */
int rtk_port_rgmiiDelayExt1_get(unsigned int *pTxDelay, unsigned int *pRxDelay)
{
    return rtk_port_rgmiiDelayExt_get(EXT_PORT_0, pTxDelay, pRxDelay);
}

/* Function Name:
 *      rtk_port_rgmiiDelayExt_set
 * Description:
 *      Set RGMII interface delay value for TX and RX.
 * Input:
 *      txDelay - TX delay value, 1 for delay 2ns and 0 for no-delay
 *      rxDelay - RX delay value, 0~7 for delay setup.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT 		- Invalid input parameters.
 * Note:
 *      This API can set external interface 2 RGMII delay.
 *      In TX delay, there are 2 selection: no-delay and 2ns delay.
 *      In RX dekay, there are 8 steps for delay tunning. 0 for no-delay, and 7 for maximum delay.
 */
int rtk_port_rgmiiDelayExt_set(rtk_ext_port_t port, unsigned int txDelay, unsigned int rxDelay)
{
    int ret_val;
    unsigned int regAddr, regData;

    if ((txDelay > 1) || (rxDelay > 7))
        return RT_ERR_INPUT;

    if (port >= EXT_PORT_END)
        return RT_ERR_INPUT;

    if(port == EXT_PORT_0)
        regAddr = RTL8367B_REG_EXT0_RGMXF;
    else if(port == EXT_PORT_1)
        regAddr = RTL8367B_REG_EXT1_RGMXF;
    else if(port == EXT_PORT_2)
        regAddr = RTL8367B_REG_EXT2_RGMXF;
    else
        return RT_ERR_INPUT;

    if ((ret_val = rtl8367b_getAsicReg(regAddr, &regData)) != RT_ERR_OK)
        return ret_val;

    regData = (regData & 0xFFF0) | ((txDelay << 3) & 0x0008) | (rxDelay & 0x0007);

    if ((ret_val = rtl8367b_setAsicReg(regAddr, regData)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_port_rgmiiDelayExt_get
 * Description:
 *      Get RGMII interface delay value for TX and RX.
 * Input:
 *      None
 * Output:
 *      pTxDelay - TX delay value
 *      pRxDelay - RX delay value
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT 		- Invalid input parameters.
 * Note:
 *      This API can set external interface 2 RGMII delay.
 *      In TX delay, there are 2 selection: no-delay and 2ns delay.
 *      In RX dekay, there are 8 steps for delay tunning. 0 for n0-delay, and 7 for maximum delay.
 */
int rtk_port_rgmiiDelayExt_get(rtk_ext_port_t port, unsigned int *pTxDelay, unsigned int *pRxDelay)
{
    int ret_val;
    unsigned int regAddr, regData;

    if (port >= EXT_PORT_END)
        return RT_ERR_INPUT;

    if(port == EXT_PORT_0)
        regAddr = RTL8367B_REG_EXT0_RGMXF;
    else if(port == EXT_PORT_1)
        regAddr = RTL8367B_REG_EXT1_RGMXF;
    else if(port == EXT_PORT_2)
        regAddr = RTL8367B_REG_EXT2_RGMXF;
    else
        return RT_ERR_INPUT;

    if ((ret_val = rtl8367b_getAsicReg(regAddr, &regData)) != RT_ERR_OK)
        return ret_val;

    *pTxDelay = (regData & 0x0008) >> 3;
    *pRxDelay = regData & 0x0007;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_port_phyEnableAll_set
 * Description:
 *      Set all PHY enable status.
 * Input:
 *      enable - PHY Enable State.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_ENABLE       - Invalid enable input.
 * Note:
 *      This API can set all PHY status.
 *      The configuration of all PHY is as following:
 *      - DISABLE
 *      - ENABLE
 */
int rtk_port_phyEnableAll_set(rtk_enable_t enable)
{
    int ret_val;

    if (enable >= RTK_ENABLE_END)
        return RT_ERR_ENABLE;

    if ((ret_val = rtl8367b_setAsicPortEnableAll(enable)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;

}

/* Function Name:
 *      rtk_port_phyEnableAll_get
 * Description:
 *      Get all PHY enable status.
 * Input:
 *      None
 * Output:
 *      pEnable - PHY Enable State.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 * Note:
 *      This API can set all PHY status.
 *      The configuration of all PHY is as following:
 *      - DISABLE
 *      - ENABLE
 */
int rtk_port_phyEnableAll_get(rtk_enable_t *pEnable)
{
    int ret_val;

    if ((ret_val = rtl8367b_getAsicPortEnableAll(pEnable)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_port_efid_set
 * Description:
 *      Set port-based enhanced filtering database
 * Input:
 *      port - Port id.
 *      efid - Specified enhanced filtering database.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 *      RT_ERR_L2_FID - Invalid fid.
 *      RT_ERR_INPUT - Invalid input parameter.
 *      RT_ERR_PORT_ID - Invalid port ID.
 * Note:
 *      The API can set port-based enhanced filtering database.
 */
int rtk_port_efid_set(unsigned int port, unsigned int efid)
{
    int ret_val;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    /* efid must be 0~7 */
    if (efid > RTK_EFID_MAX)
        return RT_ERR_INPUT;

    if ((ret_val = rtl8367b_setAsicPortIsolationEfid(port, efid))!=RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_port_efid_get
 * Description:
 *      Get port-based enhanced filtering database
 * Input:
 *      port - Port id.
 * Output:
 *      pEfid - Specified enhanced filtering database.
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 *      RT_ERR_INPUT - Invalid input parameters.
 *      RT_ERR_PORT_ID - Invalid port ID.
 * Note:
 *      The API can get port-based enhanced filtering database status.
 */
int rtk_port_efid_get(unsigned int port, unsigned int *pEfid)
{
    int ret_val;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if ((ret_val = rtl8367b_getAsicPortIsolationEfid(port, pEfid))!=RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_port_phyComboPortMedia_set
 * Description:
 *      Set Combo port media type
 * Input:
 *      port    - Port id. (Should be Port 4)
 *      media   - Media (COPPER or FIBER)
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_INPUT            - Invalid input parameters.
 *      RT_ERR_PORT_ID          - Invalid port ID.
 * Note:
 *      The API can Set Combo port media type.
 */
int rtk_port_phyComboPortMedia_set(unsigned int port, rtk_port_media_t media)
{
    int ret_val;

    if (port != RTK_PORT_COMBO_ID)
        return RT_ERR_PORT_ID;

    if (media >= PORT_MEDIA_END)
        return RT_ERR_INPUT;

    if(media == PORT_MEDIA_FIBER)
    {
        if ((ret_val = rtl8367b_setAsicReg(RTL8367B_REG_FIBER_CFG_2, 0x3945))!=RT_ERR_OK)
            return ret_val;

        if ((ret_val = rtl8367b_setAsicReg(RTL8367B_REG_UTP_FIB_DET, 0xd5b9))!=RT_ERR_OK)
            return ret_val;
    }
    else
    {
        if ((ret_val = rtl8367b_setAsicReg(RTL8367B_REG_FIBER_CFG_2, 0x3000))!=RT_ERR_OK)
            return ret_val;

        if ((ret_val = rtl8367b_setAsicReg(RTL8367B_REG_UTP_FIB_DET, 0x11bb))!=RT_ERR_OK)
            return ret_val;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_port_phyComboPortMedia_get
 * Description:
 *      Get Combo port media type
 * Input:
 *      port    - Port id. (Should be Port 4)
 * Output:
 *      pMedia  - Media (COPPER or FIBER)
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_INPUT            - Invalid input parameters.
 *      RT_ERR_PORT_ID          - Invalid port ID.
 * Note:
 *      The API can Set Combo port media type.
 */
int rtk_port_phyComboPortMedia_get(unsigned int port, rtk_port_media_t *pMedia)
{
    int   ret_val;
    unsigned int      data1, data2;

    if (port != RTK_PORT_COMBO_ID)
        return RT_ERR_PORT_ID;

    if ((ret_val = rtl8367b_getAsicReg(RTL8367B_REG_FIBER_CFG_2, &data1))!=RT_ERR_OK)
        return ret_val;

    if ((ret_val = rtl8367b_getAsicReg(RTL8367B_REG_UTP_FIB_DET, &data2))!=RT_ERR_OK)
        return ret_val;

    if ((data1 == 0x3945) && (data2 == 0xd5b9))
        *pMedia = PORT_MEDIA_FIBER;
    else
        *pMedia = PORT_MEDIA_COPPER;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_port_rtctEnable_set
 * Description:
 *      Enable RTCT test
 * Input:
 *      portmask    - Port mask of RTCT enabled port
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_PORT_MASK        - Invalid port mask.
 * Note:
 *      The API can enable RTCT Test
 */
int rtk_port_rtctEnable_set(rtk_portmask_t portmask)
{
    int   ret_val;

    if (portmask.bits[0] >= (0x0001 << RTL8367B_PHYNO))
        return RT_ERR_PORT_MASK;

    if ((ret_val = rtl8367b_setAsicPortRTCT(portmask.bits[0]))!=RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_port_rtctResult_get
 * Description:
 *      Get the result of RTCT test
 * Input:
 *      port        - Port ID
 * Output:
 *      pRtctResult - The result of RTCT result
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_PORT_ID              - Invalid port ID.
 *      RT_ERR_PHY_RTCT_NOT_FINISH  - Testing does not finish.
 * Note:
 *      The API can get RTCT test result.
 *      RTCT test may takes 4.8 seconds to finish its test at most.
 *      Thus, if this API return RT_ERR_PHY_RTCT_NOT_FINISH or
 *      other error code, the result can not be referenced and
 *      user should call this API again until this API returns
 *      a RT_ERR_OK.
 *      The result is stored at pRtctResult->ge_result
 *      pRtctResult->linkType is unused.
 *      The unit of channel length is 2.5cm. Ex. 300 means 300 * 2.5 = 750cm = 7.5M
 */
int rtk_port_rtctResult_get(unsigned int port, rtk_rtctResult_t *pRtctResult)
{
    int               ret_val;
    rtl8367b_port_rtct_result_t result;

    if (port > RTL8367B_PHYIDMAX)
        return RT_ERR_PORT_ID;

    memset(pRtctResult, 0x00, sizeof(rtk_rtctResult_t));
    if ((ret_val = rtl8367b_getAsicPortRTCTResult(port, &result))!=RT_ERR_OK)
        return ret_val;

    pRtctResult->result.ge_result.channelALen = result.channelALen;
    pRtctResult->result.ge_result.channelBLen = result.channelBLen;
    pRtctResult->result.ge_result.channelCLen = result.channelCLen;
    pRtctResult->result.ge_result.channelDLen = result.channelDLen;

    pRtctResult->result.ge_result.channelALinedriver = result.channelALinedriver;
    pRtctResult->result.ge_result.channelBLinedriver = result.channelBLinedriver;
    pRtctResult->result.ge_result.channelCLinedriver = result.channelCLinedriver;
    pRtctResult->result.ge_result.channelDLinedriver = result.channelDLinedriver;

    pRtctResult->result.ge_result.channelAMismatch = result.channelAMismatch;
    pRtctResult->result.ge_result.channelBMismatch = result.channelBMismatch;
    pRtctResult->result.ge_result.channelCMismatch = result.channelCMismatch;
    pRtctResult->result.ge_result.channelDMismatch = result.channelDMismatch;

    pRtctResult->result.ge_result.channelAOpen = result.channelAOpen;
    pRtctResult->result.ge_result.channelBOpen = result.channelBOpen;
    pRtctResult->result.ge_result.channelCOpen = result.channelCOpen;
    pRtctResult->result.ge_result.channelDOpen = result.channelDOpen;

    pRtctResult->result.ge_result.channelAShort = result.channelAShort;
    pRtctResult->result.ge_result.channelBShort = result.channelBShort;
    pRtctResult->result.ge_result.channelCShort = result.channelCShort;
    pRtctResult->result.ge_result.channelDShort = result.channelDShort;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_leaky_vlan_set
 * Description:
 *      Set VLAN leaky.
 * Input:
 *      type - Packet type for VLAN leaky.
 *      enable - Leaky status.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT 		- Invalid input parameters.
 *      RT_ERR_ENABLE       - Invalid enable input
 * Note:
 *      This API can set VLAN leaky for RMA and IGMP/MLD packets.
 *      The leaky frame types are as following:
 *      - LEAKY_BRG_GROUP,
 *      - LEAKY_FD_PAUSE,
 *      - LEAKY_SP_MCAST,
 *      - LEAKY_1X_PAE,
 *      - LEAKY_UNDEF_BRG_04,
 *      - LEAKY_UNDEF_BRG_05,
 *      - LEAKY_UNDEF_BRG_06,
 *      - LEAKY_UNDEF_BRG_07,
 *      - LEAKY_PROVIDER_BRIDGE_GROUP_ADDRESS,
 *      - LEAKY_UNDEF_BRG_09,
 *      - LEAKY_UNDEF_BRG_0A,
 *      - LEAKY_UNDEF_BRG_0B,
 *      - LEAKY_UNDEF_BRG_0C,
 *      - LEAKY_PROVIDER_BRIDGE_GVRP_ADDRESS,
 *      - LEAKY_8021AB,
 *      - LEAKY_UNDEF_BRG_0F,
 *      - LEAKY_BRG_MNGEMENT,
 *      - LEAKY_UNDEFINED_11,
 *      - LEAKY_UNDEFINED_12,
 *      - LEAKY_UNDEFINED_13,
 *      - LEAKY_UNDEFINED_14,
 *      - LEAKY_UNDEFINED_15,
 *      - LEAKY_UNDEFINED_16,
 *      - LEAKY_UNDEFINED_17,
 *      - LEAKY_UNDEFINED_18,
 *      - LEAKY_UNDEFINED_19,
 *      - LEAKY_UNDEFINED_1A,
 *      - LEAKY_UNDEFINED_1B,
 *      - LEAKY_UNDEFINED_1C,
 *      - LEAKY_UNDEFINED_1D,
 *      - LEAKY_UNDEFINED_1E,
 *      - LEAKY_UNDEFINED_1F,
 *      - LEAKY_GMRP,
 *      - LEAKY_GVRP,
 *      - LEAKY_UNDEF_GARP_22,
 *      - LEAKY_UNDEF_GARP_23,
 *      - LEAKY_UNDEF_GARP_24,
 *      - LEAKY_UNDEF_GARP_25,
 *      - LEAKY_UNDEF_GARP_26,
 *      - LEAKY_UNDEF_GARP_27,
 *      - LEAKY_UNDEF_GARP_28,
 *      - LEAKY_UNDEF_GARP_29,
 *      - LEAKY_UNDEF_GARP_2A,
 *      - LEAKY_UNDEF_GARP_2B,
 *      - LEAKY_UNDEF_GARP_2C,
 *      - LEAKY_UNDEF_GARP_2D,
 *      - LEAKY_UNDEF_GARP_2E,
 *      - LEAKY_UNDEF_GARP_2F,
 *      - LEAKY_IGMP,
 *      - LEAKY_IPMULTICAST.
 */
int rtk_leaky_vlan_set(rtk_leaky_type_t type, rtk_enable_t enable)
{
    int ret_val;
    unsigned int port;
    rtl8367b_rma_t rmacfg;

    if (type >= LEAKY_END)
        return RT_ERR_INPUT;

    if (enable >= RTK_ENABLE_END)
        return RT_ERR_INPUT;

    if (type >= 0 && type <= LEAKY_UNDEF_GARP_2F)
    {
        if ((ret_val = rtl8367b_getAsicRma(type, &rmacfg)) != RT_ERR_OK)
            return ret_val;

        rmacfg.vlan_leaky = enable;

        if ((ret_val = rtl8367b_setAsicRma(type, &rmacfg)) != RT_ERR_OK)
            return ret_val;
    }
    else if (LEAKY_IPMULTICAST == type)
    {
        for (port = 0; port <= RTK_PORT_ID_MAX; port++)
        {
            if ((ret_val = rtl8367b_setAsicIpMulticastVlanLeaky(port,enable)) != RT_ERR_OK)
                return ret_val;
        }
    }
    else if (LEAKY_IGMP == type)
    {
        if ((ret_val = rtl8367b_setAsicIGMPVLANLeaky(enable)) != RT_ERR_OK)
            return ret_val;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_leaky_vlan_get
 * Description:
 *      Get VLAN leaky.
 * Input:
 *      type - Packet type for VLAN leaky.
 * Output:
 *      pEnable - Leaky status.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT 		- Invalid input parameters.
 * Note:
 *      This API can get VLAN leaky status for RMA and IGMP/MLD packets.
 *      The leaky frame types are as following:
 *      - LEAKY_BRG_GROUP,
 *      - LEAKY_FD_PAUSE,
 *      - LEAKY_SP_MCAST,
 *      - LEAKY_1X_PAE,
 *      - LEAKY_UNDEF_BRG_04,
 *      - LEAKY_UNDEF_BRG_05,
 *      - LEAKY_UNDEF_BRG_06,
 *      - LEAKY_UNDEF_BRG_07,
 *      - LEAKY_PROVIDER_BRIDGE_GROUP_ADDRESS,
 *      - LEAKY_UNDEF_BRG_09,
 *      - LEAKY_UNDEF_BRG_0A,
 *      - LEAKY_UNDEF_BRG_0B,
 *      - LEAKY_UNDEF_BRG_0C,
 *      - LEAKY_PROVIDER_BRIDGE_GVRP_ADDRESS,
 *      - LEAKY_8021AB,
 *      - LEAKY_UNDEF_BRG_0F,
 *      - LEAKY_BRG_MNGEMENT,
 *      - LEAKY_UNDEFINED_11,
 *      - LEAKY_UNDEFINED_12,
 *      - LEAKY_UNDEFINED_13,
 *      - LEAKY_UNDEFINED_14,
 *      - LEAKY_UNDEFINED_15,
 *      - LEAKY_UNDEFINED_16,
 *      - LEAKY_UNDEFINED_17,
 *      - LEAKY_UNDEFINED_18,
 *      - LEAKY_UNDEFINED_19,
 *      - LEAKY_UNDEFINED_1A,
 *      - LEAKY_UNDEFINED_1B,
 *      - LEAKY_UNDEFINED_1C,
 *      - LEAKY_UNDEFINED_1D,
 *      - LEAKY_UNDEFINED_1E,
 *      - LEAKY_UNDEFINED_1F,
 *      - LEAKY_GMRP,
 *      - LEAKY_GVRP,
 *      - LEAKY_UNDEF_GARP_22,
 *      - LEAKY_UNDEF_GARP_23,
 *      - LEAKY_UNDEF_GARP_24,
 *      - LEAKY_UNDEF_GARP_25,
 *      - LEAKY_UNDEF_GARP_26,
 *      - LEAKY_UNDEF_GARP_27,
 *      - LEAKY_UNDEF_GARP_28,
 *      - LEAKY_UNDEF_GARP_29,
 *      - LEAKY_UNDEF_GARP_2A,
 *      - LEAKY_UNDEF_GARP_2B,
 *      - LEAKY_UNDEF_GARP_2C,
 *      - LEAKY_UNDEF_GARP_2D,
 *      - LEAKY_UNDEF_GARP_2E,
 *      - LEAKY_UNDEF_GARP_2F,
 *      - LEAKY_IGMP,
 *      - LEAKY_IPMULTICAST.
 */
int rtk_leaky_vlan_get(rtk_leaky_type_t type, rtk_enable_t *pEnable)
{
    int ret_val;
    unsigned int port,tmp;
    rtl8367b_rma_t rmacfg;

    if (type >= LEAKY_END)
        return RT_ERR_INPUT;

    if (type >= 0 && type <= LEAKY_UNDEF_GARP_2F)
    {
        if ((ret_val = rtl8367b_getAsicRma(type, &rmacfg)) != RT_ERR_OK)
            return ret_val;

        *pEnable = rmacfg.vlan_leaky;

    }
    else if (LEAKY_IPMULTICAST == type)
    {
        for (port = 0; port <= RTK_PORT_ID_MAX; port++)
        {
            if ((ret_val = rtl8367b_getAsicIpMulticastVlanLeaky(port, &tmp)) != RT_ERR_OK)
                return ret_val;
            if (port>0&&(tmp!=*pEnable))
                return RT_ERR_FAILED;
            *pEnable = tmp;
        }
    }
    else if (LEAKY_IGMP == type)
    {
        if ((ret_val = rtl8367b_getAsicIGMPVLANLeaky(&tmp)) != RT_ERR_OK)
            return ret_val;

        *pEnable = tmp;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_leaky_portIsolation_set
 * Description:
 *      Set port isolation leaky.
 * Input:
 *      type - Packet type for port isolation leaky.
 *      enable - Leaky status.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT 		- Invalid input parameters.
 *      RT_ERR_ENABLE       - Invalid enable input
 * Note:
 *      This API can set port isolation leaky for RMA and IGMP/MLD packets.
 *      The leaky frame types are as following:
 *      - LEAKY_BRG_GROUP,
 *      - LEAKY_FD_PAUSE,
 *      - LEAKY_SP_MCAST,
 *      - LEAKY_1X_PAE,
 *      - LEAKY_UNDEF_BRG_04,
 *      - LEAKY_UNDEF_BRG_05,
 *      - LEAKY_UNDEF_BRG_06,
 *      - LEAKY_UNDEF_BRG_07,
 *      - LEAKY_PROVIDER_BRIDGE_GROUP_ADDRESS,
 *      - LEAKY_UNDEF_BRG_09,
 *      - LEAKY_UNDEF_BRG_0A,
 *      - LEAKY_UNDEF_BRG_0B,
 *      - LEAKY_UNDEF_BRG_0C,
 *      - LEAKY_PROVIDER_BRIDGE_GVRP_ADDRESS,
 *      - LEAKY_8021AB,
 *      - LEAKY_UNDEF_BRG_0F,
 *      - LEAKY_BRG_MNGEMENT,
 *      - LEAKY_UNDEFINED_11,
 *      - LEAKY_UNDEFINED_12,
 *      - LEAKY_UNDEFINED_13,
 *      - LEAKY_UNDEFINED_14,
 *      - LEAKY_UNDEFINED_15,
 *      - LEAKY_UNDEFINED_16,
 *      - LEAKY_UNDEFINED_17,
 *      - LEAKY_UNDEFINED_18,
 *      - LEAKY_UNDEFINED_19,
 *      - LEAKY_UNDEFINED_1A,
 *      - LEAKY_UNDEFINED_1B,
 *      - LEAKY_UNDEFINED_1C,
 *      - LEAKY_UNDEFINED_1D,
 *      - LEAKY_UNDEFINED_1E,
 *      - LEAKY_UNDEFINED_1F,
 *      - LEAKY_GMRP,
 *      - LEAKY_GVRP,
 *      - LEAKY_UNDEF_GARP_22,
 *      - LEAKY_UNDEF_GARP_23,
 *      - LEAKY_UNDEF_GARP_24,
 *      - LEAKY_UNDEF_GARP_25,
 *      - LEAKY_UNDEF_GARP_26,
 *      - LEAKY_UNDEF_GARP_27,
 *      - LEAKY_UNDEF_GARP_28,
 *      - LEAKY_UNDEF_GARP_29,
 *      - LEAKY_UNDEF_GARP_2A,
 *      - LEAKY_UNDEF_GARP_2B,
 *      - LEAKY_UNDEF_GARP_2C,
 *      - LEAKY_UNDEF_GARP_2D,
 *      - LEAKY_UNDEF_GARP_2E,
 *      - LEAKY_UNDEF_GARP_2F,
 *      - LEAKY_IGMP,
 *      - LEAKY_IPMULTICAST.
 */
int rtk_leaky_portIsolation_set(rtk_leaky_type_t type, rtk_enable_t enable)
{
    int ret_val;
    unsigned int port;
    rtl8367b_rma_t rmacfg;

    if (type >= LEAKY_END)
        return RT_ERR_INPUT;

    if (enable >= RTK_ENABLE_END)
        return RT_ERR_INPUT;

    if (type >= 0 && type <= LEAKY_UNDEF_GARP_2F)
    {
        if ((ret_val = rtl8367b_getAsicRma(type, &rmacfg)) != RT_ERR_OK)
            return ret_val;

        rmacfg.portiso_leaky = enable;

        if ((ret_val = rtl8367b_setAsicRma(type, &rmacfg)) != RT_ERR_OK)
            return ret_val;
    }
    else if (LEAKY_IPMULTICAST == type)
    {
        for (port = 0; port < RTK_MAX_NUM_OF_PORT; port++)
        {
            if ((ret_val = rtl8367b_setAsicIpMulticastPortIsoLeaky(port,enable)) != RT_ERR_OK)
                return ret_val;
        }
    }
    else if (LEAKY_IGMP == type)
    {
        if ((ret_val = rtl8367b_setAsicIGMPIsoLeaky(enable)) != RT_ERR_OK)
            return ret_val;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_leaky_portIsolation_get
 * Description:
 *      Get port isolation leaky.
 * Input:
 *      type - Packet type for port isolation leaky.
 * Output:
 *      pEnable - Leaky status.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT 		- Invalid input parameters.
 * Note:
 *      This API can get port isolation leaky status for RMA and IGMP/MLD packets.
 *      The leaky frame types are as following:
 *      - LEAKY_BRG_GROUP,
 *      - LEAKY_FD_PAUSE,
 *      - LEAKY_SP_MCAST,
 *      - LEAKY_1X_PAE,
 *      - LEAKY_UNDEF_BRG_04,
 *      - LEAKY_UNDEF_BRG_05,
 *      - LEAKY_UNDEF_BRG_06,
 *      - LEAKY_UNDEF_BRG_07,
 *      - LEAKY_PROVIDER_BRIDGE_GROUP_ADDRESS,
 *      - LEAKY_UNDEF_BRG_09,
 *      - LEAKY_UNDEF_BRG_0A,
 *      - LEAKY_UNDEF_BRG_0B,
 *      - LEAKY_UNDEF_BRG_0C,
 *      - LEAKY_PROVIDER_BRIDGE_GVRP_ADDRESS,
 *      - LEAKY_8021AB,
 *      - LEAKY_UNDEF_BRG_0F,
 *      - LEAKY_BRG_MNGEMENT,
 *      - LEAKY_UNDEFINED_11,
 *      - LEAKY_UNDEFINED_12,
 *      - LEAKY_UNDEFINED_13,
 *      - LEAKY_UNDEFINED_14,
 *      - LEAKY_UNDEFINED_15,
 *      - LEAKY_UNDEFINED_16,
 *      - LEAKY_UNDEFINED_17,
 *      - LEAKY_UNDEFINED_18,
 *      - LEAKY_UNDEFINED_19,
 *      - LEAKY_UNDEFINED_1A,
 *      - LEAKY_UNDEFINED_1B,
 *      - LEAKY_UNDEFINED_1C,
 *      - LEAKY_UNDEFINED_1D,
 *      - LEAKY_UNDEFINED_1E,
 *      - LEAKY_UNDEFINED_1F,
 *      - LEAKY_GMRP,
 *      - LEAKY_GVRP,
 *      - LEAKY_UNDEF_GARP_22,
 *      - LEAKY_UNDEF_GARP_23,
 *      - LEAKY_UNDEF_GARP_24,
 *      - LEAKY_UNDEF_GARP_25,
 *      - LEAKY_UNDEF_GARP_26,
 *      - LEAKY_UNDEF_GARP_27,
 *      - LEAKY_UNDEF_GARP_28,
 *      - LEAKY_UNDEF_GARP_29,
 *      - LEAKY_UNDEF_GARP_2A,
 *      - LEAKY_UNDEF_GARP_2B,
 *      - LEAKY_UNDEF_GARP_2C,
 *      - LEAKY_UNDEF_GARP_2D,
 *      - LEAKY_UNDEF_GARP_2E,
 *      - LEAKY_UNDEF_GARP_2F,
 *      - LEAKY_IGMP,
 *      - LEAKY_IPMULTICAST.
 */
int rtk_leaky_portIsolation_get(rtk_leaky_type_t type, rtk_enable_t *pEnable)
{
    int ret_val;
    unsigned int port, tmp;
    rtl8367b_rma_t rmacfg;

    if (type >= LEAKY_END)
        return RT_ERR_INPUT;

    if (type >= 0 && type <= LEAKY_UNDEF_GARP_2F)
    {
        if ((ret_val = rtl8367b_getAsicRma(type, &rmacfg)) != RT_ERR_OK)
            return ret_val;

        *pEnable = rmacfg.portiso_leaky;

    }
    else if (LEAKY_IPMULTICAST == type)
    {
        for (port = 0; port < RTK_MAX_NUM_OF_PORT; port++)
        {
            if ((ret_val = rtl8367b_getAsicIpMulticastPortIsoLeaky(port, &tmp)) != RT_ERR_OK)
                return ret_val;
            if (port > 0 &&(tmp != *pEnable))
                return RT_ERR_FAILED;
            *pEnable = tmp;
        }
    }
    else if (LEAKY_IGMP == type)
    {
        if ((ret_val = rtl8367b_getAsicIGMPIsoLeaky(&tmp)) != RT_ERR_OK)
            return ret_val;

        *pEnable = tmp;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_vlan_init
 * Description:
 *      Initialize VLAN.
 * Input:
 *      None
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 * Note:
 *      VLAN is disabled by default. User has to call this API to enable VLAN before
 *      using it. And It will set a default VLAN(vid 1) including all ports and set
 *      all ports PVID to the default VLAN.
 */
int rtk_vlan_init(void)
{
    int ret_val;
    unsigned int i;
    rtl8367b_user_vlan4kentry vlan4K;
    rtl8367b_vlanconfiguser vlanMC;


    /* clean 32 VLAN member configuration */
    for (i = 0; i <= RTL8367B_CVIDXMAX; i++)
    {
        vlanMC.evid = 0;
        vlanMC.mbr = 0;
        vlanMC.fid_msti = 0;
        vlanMC.envlanpol = 0;
        vlanMC.meteridx = 0;
        vlanMC.vbpen = 0;
        vlanMC.vbpri = 0;
        if ((ret_val = rtl8367b_setAsicVlanMemberConfig(i, &vlanMC)) != RT_ERR_OK)
            return ret_val;
    }

    /* Set a default VLAN with vid 1 to 4K table for all ports */
    memset(&vlan4K, 0, sizeof(rtl8367b_user_vlan4kentry));
    vlan4K.vid = 1;
    vlan4K.mbr = RTK_MAX_PORT_MASK;
    vlan4K.untag = RTK_MAX_PORT_MASK;
    vlan4K.fid_msti = 0;
    if ((ret_val = rtl8367b_setAsicVlan4kEntry(&vlan4K)) != RT_ERR_OK)
        return ret_val;


    /* Also set the default VLAN to 32 member configuration index 0 */
    memset(&vlanMC, 0, sizeof(rtl8367b_vlanconfiguser));
    vlanMC.evid = 1;
    vlanMC.mbr = RTK_MAX_PORT_MASK;
    vlanMC.fid_msti = 0;
    if ((ret_val = rtl8367b_setAsicVlanMemberConfig(0, &vlanMC)) != RT_ERR_OK)
            return ret_val;

    /* Set all ports PVID to default VLAN and tag-mode to original */
    for (i = 0; i < RTK_MAX_NUM_OF_PORT; i++)
    {
        if ((ret_val = rtl8367b_setAsicVlanPortBasedVID(i, 0, 0)) != RT_ERR_OK)
            return ret_val;
        if ((ret_val = rtl8367b_setAsicVlanEgressTagMode(i, EG_TAG_MODE_ORI)) != RT_ERR_OK)
            return ret_val;
    }

    /* enable VLAN */
    if ((ret_val = rtl8367b_setAsicVlanFilter(TRUE)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_vlan_set
 * Description:
 *      Set a VLAN entry.
 * Input:
 *      vid - VLAN ID to configure.
 *      mbrmsk - VLAN member set portmask.
 *      untagmsk - VLAN untag set portmask.
 *      fid - filtering database.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_INPUT 		        - Invalid input parameters.
 *      RT_ERR_L2_FID               - Invalid FID.
 *      RT_ERR_VLAN_PORT_MBR_EXIST  - Invalid member port mask.
 *      RT_ERR_VLAN_VID             - Invalid VID parameter.
 * Note:
 *      There are 4K VLAN entry supported. User could configure the member set and untag set
 *      for specified vid through this API. The portmask's bit N means port N.
 *      For example, mbrmask 23=0x17=010111 means port 0,1,2,4 in the member set.
 *      FID is for SVL/IVL usage, specify 0~15, the VLAN would be configured as SVL mode.
 *      If FID is specified as RTK_IVL_MODE_FID, the VLAN would be configured as IVL mode.
 */
int rtk_vlan_set(rtk_vlan_t vid, rtk_portmask_t mbrmsk, rtk_portmask_t untagmsk, unsigned int fid)
{
    int ret_val;
    rtl8367b_user_vlan4kentry vlan4K;

    /* vid must be 0~4095 */
    if (vid > RTL8367B_VIDMAX)
        return RT_ERR_VLAN_VID;

    if (mbrmsk.bits[0] > RTK_MAX_PORT_MASK)
        return RT_ERR_VLAN_PORT_MBR_EXIST;

    if (untagmsk.bits[0] > RTK_MAX_PORT_MASK)
        return RT_ERR_VLAN_PORT_MBR_EXIST;

    /* fid must be 0~15 */
    if ( (fid != RTK_IVL_MODE_FID) && (fid > RTL8367B_FIDMAX) )
        return RT_ERR_L2_FID;

    /* update 4K table */
    memset(&vlan4K, 0, sizeof(rtl8367b_user_vlan4kentry));
    vlan4K.vid = vid;
    vlan4K.mbr = mbrmsk.bits[0];
    vlan4K.untag = untagmsk.bits[0];

    if(fid == RTK_IVL_MODE_FID)
    {
        vlan4K.ivl_svl  = 1;
        vlan4K.fid_msti = 0;
    }
    else
        vlan4K.fid_msti = fid;

    if ((ret_val = rtl8367b_setAsicVlan4kEntry(&vlan4K)) != RT_ERR_OK)
            return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_vlan_get
 * Description:
 *      Get a VLAN entry.
 * Input:
 *      vid - VLAN ID to configure.
 * Output:
 *      pMbrmsk - VLAN member set portmask.
 *      pUntagmsk - VLAN untag set portmask.
 *      pFid - filtering database.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT 		- Invalid input parameters.
 *      RT_ERR_VLAN_VID     - Invalid VID parameter.
 * Note:
 *     The API can get the member set, untag set and fid settings for specified vid.
 */
int rtk_vlan_get(rtk_vlan_t vid, rtk_portmask_t *pMbrmsk, rtk_portmask_t *pUntagmsk, unsigned int *pFid)
{
    int ret_val;
    rtl8367b_user_vlan4kentry vlan4K;

    /* vid must be 0~4095 */
    if (vid > RTL8367B_VIDMAX)
        return RT_ERR_VLAN_VID;

    vlan4K.vid = vid;

    if ((ret_val = rtl8367b_getAsicVlan4kEntry(&vlan4K)) != RT_ERR_OK)
        return ret_val;

    pMbrmsk->bits[0] = vlan4K.mbr;
    pUntagmsk->bits[0] = vlan4K.untag;

    if(vlan4K.ivl_svl == 1)
        *pFid = RTK_IVL_MODE_FID;
    else
        *pFid = vlan4K.fid_msti;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_vlan_mbrCfg_set
 * Description:
 *      Set a VLAN Member Configuration entry by index.
 * Input:
 *      idx     - Index of VLAN Member Configuration.
 *      pMbrcfg - VLAN member Configuration.
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT 		- Invalid input parameters.
 *      RT_ERR_VLAN_VID     - Invalid VID parameter.
 * Note:
 *     Set a VLAN Member Configuration entry by index.
 */
int rtk_vlan_mbrCfg_set(unsigned int idx, rtk_vlan_mbrcfg_t *pMbrcfg)
{
    int           ret_val;

    /* Error check */
    if(pMbrcfg == NULL)
        return RT_ERR_NULL_POINTER;

    if(idx > RTL8367B_CVIDXMAX)
        return RT_ERR_INPUT;

    if(pMbrcfg->evid > RTL8367B_EVIDMAX)
        return RT_ERR_INPUT;

    if(pMbrcfg->mbr > RTL8367B_PORTMASK)
        return RT_ERR_PORT_MASK;

    if(pMbrcfg->fid_msti > RTL8367B_FIDMAX)
        return RT_ERR_L2_FID;

    if(pMbrcfg->envlanpol >= RTK_ENABLE_END)
        return RT_ERR_ENABLE;

    if(pMbrcfg->meteridx > RTL8367B_METERMAX)
        return RT_ERR_FILTER_METER_ID;

    if(pMbrcfg->vbpen >= RTK_ENABLE_END)
        return RT_ERR_ENABLE;

    if(pMbrcfg->vbpri > RTL8367B_PRIMAX)
        return RT_ERR_QOS_INT_PRIORITY;

    if ((ret_val = rtl8367b_setAsicVlanMemberConfig(idx, (rtl8367b_vlanconfiguser *)pMbrcfg)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;

}

/* Function Name:
 *      rtk_vlan_mbrCfg_get
 * Description:
 *      Get a VLAN Member Configuration entry by index.
 * Input:
 *      idx - Index of VLAN Member Configuration.
 * Output:
 *      pMbrcfg - VLAN member Configuration.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT 		- Invalid input parameters.
 *      RT_ERR_VLAN_VID     - Invalid VID parameter.
 * Note:
 *     Get a VLAN Member Configuration entry by index.
 */
int rtk_vlan_mbrCfg_get(unsigned int idx, rtk_vlan_mbrcfg_t *pMbrcfg)
{
    int           ret_val;

    /* Error check */
    if(pMbrcfg == NULL)
        return RT_ERR_NULL_POINTER;

    if(idx > RTL8367B_CVIDXMAX)
        return RT_ERR_INPUT;

    if ((ret_val = rtl8367b_getAsicVlanMemberConfig(idx, (rtl8367b_vlanconfiguser *)pMbrcfg)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *     rtk_vlan_portPvid_set
 * Description:
 *      Set port to specified VLAN ID(PVID).
 * Input:
 *      port - Port id.
 *      pvid - Specified VLAN ID.
 *      priority - 802.1p priority for the PVID.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_PORT_ID              - Invalid port number.
 *      RT_ERR_VLAN_PRIORITY        - Invalid priority.
 *      RT_ERR_VLAN_ENTRY_NOT_FOUND - VLAN entry not found.
 *      RT_ERR_VLAN_VID             - Invalid VID parameter.
 * Note:
 *       The API is used for Port-based VLAN. The untagged frame received from the
 *       port will be classified to the specified VLAN and assigned to the specified priority.
 */
int rtk_vlan_portPvid_set(unsigned int port, rtk_vlan_t pvid, rtk_pri_t priority)
{
    int ret_val;
    int i;
    unsigned int j;
    unsigned int k;
    unsigned int index,empty_idx;
    unsigned int gvidx, proc;
    unsigned int bUsed, pri;
    rtl8367b_user_vlan4kentry vlan4K;
    rtl8367b_vlanconfiguser vlanMC;
    rtl8367b_protocolvlancfg ppb_vlan_cfg;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    /* vid must be 0~4095 */
    if (pvid > RTL8367B_VIDMAX)
        return RT_ERR_VLAN_VID;

    /* priority must be 0~7 */
    if (priority > RTL8367B_PRIMAX)
        return RT_ERR_VLAN_PRIORITY;


      empty_idx = 0xFFFF;

    for (i = RTL8367B_CVIDXMAX; i >= 0; i--)
    {
        if ((ret_val = rtl8367b_getAsicVlanMemberConfig(i, &vlanMC)) != RT_ERR_OK)
            return ret_val;

        if (pvid == vlanMC.evid)
        {
            if ((ret_val = rtl8367b_setAsicVlanPortBasedVID(port, i, priority)) != RT_ERR_OK)
                return ret_val;

            return RT_ERR_OK;
        }
        else if (vlanMC.evid == 0 && vlanMC.mbr == 0)
        {
            empty_idx = i;
        }
    }


    /*
        vid doesn't exist in 32 member configuration. Find an empty entry in
        32 member configuration, then copy entry from 4K. If 32 member configuration
        are all full, then find an entry which not used by Port-based VLAN and
        then replace it with 4K. Finally, assign the index to the port.
    */

    if (empty_idx != 0xFFFF)
    {
        vlan4K.vid = pvid;
        if ((ret_val = rtl8367b_getAsicVlan4kEntry(&vlan4K)) != RT_ERR_OK)
            return ret_val;

        vlanMC.evid = pvid;
        vlanMC.mbr = vlan4K.mbr;
        vlanMC.fid_msti = vlan4K.fid_msti;
        vlanMC.meteridx= vlan4K.meteridx;
        vlanMC.envlanpol= vlan4K.envlanpol;
        vlanMC.vbpen = vlan4K.vbpen;
        vlanMC.vbpri = vlan4K.vbpri;

        if ((ret_val = rtl8367b_setAsicVlanMemberConfig(empty_idx, &vlanMC)) != RT_ERR_OK)
            return ret_val;

        if ((ret_val = rtl8367b_setAsicVlanPortBasedVID(port,empty_idx, priority)) != RT_ERR_OK)
            return ret_val;

        return RT_ERR_OK;
     }

    if ((ret_val = rtl8367b_getAsic1xGuestVidx(&gvidx)) != RT_ERR_OK)
        return ret_val;

    /* 32 member configuration is full, found a unused entry to replace */
    for (i = 0; i <= RTL8367B_CVIDXMAX; i++)
    {
        bUsed = FALSE;

        for (j = 0; j < RTK_MAX_NUM_OF_PORT; j++)
        {
            if ((ret_val = rtl8367b_getAsicVlanPortBasedVID(j, &index, &pri)) != RT_ERR_OK)
                return ret_val;

            if (i == index)/*index i is in use by port j*/
            {
                bUsed = TRUE;
                break;
            }

            if (i == gvidx)
            {
                if ((ret_val = rtl8367b_getAsic1xProcConfig(j, &proc)) != RT_ERR_OK)
                    return ret_val;
                if (DOT1X_UNAUTH_GVLAN == proc )
                {
                    bUsed = TRUE;
                    break;
                }
            }

            for (k = 0; k <= RTL8367B_PROTOVLAN_GIDX_MAX; k++)
            {
                if ((ret_val = rtl8367b_getAsicVlanPortAndProtocolBased(port, k, &ppb_vlan_cfg)) != RT_ERR_OK)
                    return ret_val;
                if (ppb_vlan_cfg.valid == TRUE && ppb_vlan_cfg.vlan_idx == i)
                {
                    bUsed = TRUE;
                    break;
                }
            }
        }

        if (FALSE == bUsed)/*found a unused index, replace it*/
        {
            vlan4K.vid = pvid;
            if ((ret_val = rtl8367b_getAsicVlan4kEntry(&vlan4K)) != RT_ERR_OK)
                return ret_val;
            vlanMC.evid = pvid;
            vlanMC.mbr = vlan4K.mbr;
            vlanMC.fid_msti = vlan4K.fid_msti;
            vlanMC.meteridx= vlan4K.meteridx;
            vlanMC.envlanpol= vlan4K.envlanpol;
            vlanMC.vbpen = vlan4K.vbpen;
            vlanMC.vbpri = vlan4K.vbpri;
            if ((ret_val = rtl8367b_setAsicVlanMemberConfig(i, &vlanMC)) != RT_ERR_OK)
                return ret_val;

            if ((ret_val = rtl8367b_setAsicVlanPortBasedVID(port, i, priority)) != RT_ERR_OK)
                return ret_val;

            return RT_ERR_OK;
        }
    }

    return RT_ERR_FAILED;
}

/* Function Name:
 *      rtk_vlan_portPvid_get
 * Description:
 *      Get VLAN ID(PVID) on specified port.
 * Input:
 *      port - Port id.
 * Output:
 *      pPvid - Specified VLAN ID.
 *      pPriority - 802.1p priority for the PVID.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT 		- Invalid input parameters.
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *     The API can get the PVID and 802.1p priority for the PVID of Port-based VLAN.
 */
int rtk_vlan_portPvid_get(unsigned int port, rtk_vlan_t *pPvid, rtk_pri_t *pPriority)
{
    int ret_val;
    unsigned int index, pri;
    rtl8367b_vlanconfiguser vlanMC;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if ((ret_val = rtl8367b_getAsicVlanPortBasedVID(port, &index, &pri)) != RT_ERR_OK)
        return ret_val;

    if ((ret_val = rtl8367b_getAsicVlanMemberConfig(index, &vlanMC)) != RT_ERR_OK)
        return ret_val;

    *pPvid = vlanMC.evid;
    *pPriority = pri;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_vlan_portIgrFilterEnable_set
 * Description:
 *      Set VLAN ingress for each port.
 * Input:
 *      port - Port id.
 *      igr_filter - VLAN ingress function enable status.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number
 *      RT_ERR_ENABLE       - Invalid enable input
 * Note:
 *      The status of vlan ingress filter is as following:
 *      - DISABLED
 *      - ENABLED
 *      While VLAN function is enabled, ASIC will decide VLAN ID for each received frame and get belonged member
 *      ports from VLAN table. If received port is not belonged to VLAN member ports, ASIC will drop received frame if VLAN ingress function is enabled.
 */
int rtk_vlan_portIgrFilterEnable_set(unsigned int port, rtk_enable_t igr_filter)
{
    int ret_val;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if (igr_filter >= RTK_ENABLE_END)
        return RT_ERR_ENABLE;

    if ((ret_val = rtl8367b_setAsicVlanIngressFilter(port, igr_filter)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_vlan_portIgrFilterEnable_get
 * Description:
 *      Get VLAN Ingress Filter
 * Input:
 *      port        - Port id.
 * Output:
 *      pIgr_filter - VLAN ingress function enable status.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *     The API can Get the VLAN ingress filter status.
 *     The status of vlan ingress filter is as following:
 *     - DISABLED
 *     - ENABLED
 */
int rtk_vlan_portIgrFilterEnable_get(unsigned int port, rtk_enable_t *pIgr_filter)
{
    int ret_val;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if ((ret_val = rtl8367b_getAsicVlanIngressFilter(port, pIgr_filter)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_vlan_portAcceptFrameType_set
 * Description:
 *      Set VLAN accept_frame_type
 * Input:
 *      port                - Port id.
 *      accept_frame_type   - accept frame type
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                       - OK
 *      RT_ERR_FAILED                   - Failed
 *      RT_ERR_SMI                      - SMI access error
 *      RT_ERR_PORT_ID                  - Invalid port number.
 *      RT_ERR_VLAN_ACCEPT_FRAME_TYPE   - Invalid frame type.
 * Note:
 *      The API is used for checking 802.1Q tagged frames.
 *      The accept frame type as following:
 *      - ACCEPT_FRAME_TYPE_ALL
 *      - ACCEPT_FRAME_TYPE_TAG_ONLY
 *      - ACCEPT_FRAME_TYPE_UNTAG_ONLY
 */
int rtk_vlan_portAcceptFrameType_set(unsigned int port, rtk_vlan_acceptFrameType_t accept_frame_type)
{
    int ret_val;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if (accept_frame_type >= ACCEPT_FRAME_TYPE_END)
        return RT_ERR_VLAN_ACCEPT_FRAME_TYPE;

    if ((ret_val = rtl8367b_setAsicVlanAccpetFrameType(port, (rtl8367b_accframetype)accept_frame_type)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_vlan_portAcceptFrameType_get
 * Description:
 *      Get VLAN accept_frame_type
 * Input:
 *      port - Port id.
 * Output:
 *      pAccept_frame_type - accept frame type
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *     The API can Get the VLAN ingress filter.
 *     The accept frame type as following:
 *     - ACCEPT_FRAME_TYPE_ALL
 *     - ACCEPT_FRAME_TYPE_TAG_ONLY
 *     - ACCEPT_FRAME_TYPE_UNTAG_ONLY
 */
int rtk_vlan_portAcceptFrameType_get(unsigned int port, rtk_vlan_acceptFrameType_t *pAccept_frame_type)
{
    int ret_val;
    rtl8367b_accframetype   acc_frm_type;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if ((ret_val = rtl8367b_getAsicVlanAccpetFrameType(port, &acc_frm_type)) != RT_ERR_OK)
        return ret_val;

    *pAccept_frame_type = (rtk_vlan_acceptFrameType_t)acc_frm_type;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_vlan_vlanBasedPriority_set
 * Description:
 *      Set VLAN priority for each CVLAN.
 * Input:
 *      vid - Specified VLAN ID.
 *      priority - 802.1p priority for the PVID.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_VLAN_VID         - Invalid VID parameter.
 *      RT_ERR_VLAN_PRIORITY    - Invalid priority.
 * Note:
 *      This API is used to set priority per VLAN.
 */
int rtk_vlan_vlanBasedPriority_set(rtk_vlan_t vid, rtk_pri_t priority)
{
    int ret_val;
    rtl8367b_user_vlan4kentry vlan4K;

    /* vid must be 0~4095 */
    if (vid > RTL8367B_VIDMAX)
        return RT_ERR_VLAN_VID;

    /* priority must be 0~7 */
    if (priority > RTL8367B_PRIMAX)
        return RT_ERR_VLAN_PRIORITY;

    /* update 4K table */
    vlan4K.vid = vid;
    if ((ret_val = rtl8367b_getAsicVlan4kEntry(&vlan4K)) != RT_ERR_OK)
        return ret_val;

    vlan4K.vbpen = 1;
    vlan4K.vbpri = priority;
    if ((ret_val = rtl8367b_setAsicVlan4kEntry(&vlan4K)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_vlan_vlanBasedPriority_get
 * Description:
 *      Get VLAN priority for each CVLAN.
 * Input:
 *      vid - Specified VLAN ID.
 * Output:
 *      pPriority - 802.1p priority for the PVID.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_VLAN_VID     - Invalid VID parameter.
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *     This API is used to set priority per VLAN.
 */
int rtk_vlan_vlanBasedPriority_get(rtk_vlan_t vid, rtk_pri_t *pPriority)
{
    int ret_val;
    rtl8367b_user_vlan4kentry vlan4K;

    /* vid must be 0~4095 */
    if (vid > RTL8367B_VIDMAX)
        return RT_ERR_VLAN_VID;

    /* update 4K table */
    vlan4K.vid = vid;
    if ((ret_val = rtl8367b_getAsicVlan4kEntry(&vlan4K)) != RT_ERR_OK)
        return ret_val;

    if (vlan4K.vbpen != 1)
        return RT_ERR_FAILED;

    *pPriority = vlan4K.vbpri;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_vlan_protoAndPortBasedVlan_add
 * Description:
 *      Add the protocol-and-port-based vlan to the specified port of device.
 * Input:
 *      port - Port id.
 *      info - Protocol and port based VLAN configuration information.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_PORT_ID          - Invalid port number.
 *      RT_ERR_VLAN_VID         - Invalid VID parameter.
 *      RT_ERR_VLAN_PRIORITY    - Invalid priority.
 *      RT_ERR_TBL_FULL         - Table is full.
 *      RT_ERR_OUT_OF_RANGE     - input out of range.
 * Note:
 *      The incoming packet which match the protocol-and-port-based vlan will use the configure vid for ingress pipeline
 *      The frame type is shown in the following:
 *      - FRAME_TYPE_ETHERNET
 *      - FRAME_TYPE_RFC1042
 *      - FRAME_TYPE_LLCOTHER
 */
int rtk_vlan_protoAndPortBasedVlan_add(unsigned int port, rtk_vlan_protoAndPortInfo_t info)
{
    int ret_val, i;
    unsigned int exist, empty, used;
    rtl8367b_protocolgdatacfg ppb_data_cfg;
    rtl8367b_protocolvlancfg ppb_vlan_cfg;
    rtl8367b_user_vlan4kentry vlan4K;
    rtl8367b_vlanconfiguser vlanMC;
    rtl8367b_provlan_frametype tmp;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if (info.proto_type > RTK_MAX_NUM_OF_PROTO_TYPE)
        return RT_ERR_OUT_OF_RANGE;

    if (info.frame_type >= FRAME_TYPE_END)
        return RT_ERR_OUT_OF_RANGE;

    if (info.cvid >= RTL8367B_VIDMAX)
        return RT_ERR_VLAN_VID;

    if (info.cpri > RTL8367B_PRIMAX)
        return RT_ERR_VLAN_PRIORITY;

    exist = 0xFF;
    empty = 0xFF;
    for (i = RTL8367B_PROTOVLAN_GIDX_MAX; i >= 0; i--)
    {
        if ((ret_val = rtl8367b_getAsicVlanProtocolBasedGroupData(i, &ppb_data_cfg)) != RT_ERR_OK)
            return ret_val;
        tmp = info.frame_type;
        if (ppb_data_cfg.etherType == info.proto_type && ppb_data_cfg.frameType == tmp)
        {
            /*Already exist*/
            exist = i;
            break;
        }
        else if (ppb_data_cfg.etherType == 0 && ppb_data_cfg.frameType == 0)
        {
            /*find empty index*/
            empty = i;
        }
    }

    used = 0xFF;
    /*No empty and exist index*/
    if (0xFF == exist && 0xFF == empty)
        return RT_ERR_TBL_FULL;
    else if (exist<RTL8367B_PROTOVLAN_GROUPNO)
    {
       /*exist index*/
       used = exist;
    }
    else if (empty<RTL8367B_PROTOVLAN_GROUPNO)
    {
        /*No exist index, but have empty index*/
        ppb_data_cfg.frameType = info.frame_type;
        ppb_data_cfg.etherType = info.proto_type;
        if ((ret_val = rtl8367b_setAsicVlanProtocolBasedGroupData(empty, &ppb_data_cfg)) != RT_ERR_OK)
            return ret_val;
        used = empty;
    }
    else
        return RT_ERR_FAILED;

    /*
        Search 32 member configuration to see if the entry already existed.
        If existed, update the priority and assign the index to the port.
    */
    for (i = 0; i <= RTL8367B_CVIDXMAX; i++)
    {
        if ((ret_val = rtl8367b_getAsicVlanMemberConfig(i, &vlanMC)) != RT_ERR_OK)
            return ret_val;
        if (info.cvid == vlanMC.evid)
        {
            if ((ret_val = rtl8367b_getAsicVlanPortAndProtocolBased(port, used, &ppb_vlan_cfg)) != RT_ERR_OK)
                return ret_val;
            if (FALSE == ppb_vlan_cfg.valid)
            {
                ppb_vlan_cfg.vlan_idx = i;
                ppb_vlan_cfg.valid = TRUE;
                ppb_vlan_cfg.priority = info.cpri;
                if ((ret_val = rtl8367b_setAsicVlanPortAndProtocolBased(port, used, &ppb_vlan_cfg)) != RT_ERR_OK)
                    return ret_val;
                return RT_ERR_OK;
            }
            else
                return RT_ERR_VLAN_EXIST;
        }
    }

    /*
        vid doesn't exist in 32 member configuration. Find an empty entry in
        32 member configuration, then copy entry from 4K. If 32 member configuration
        are all full, then find an entry which not used by Port-based VLAN and
        then replace it with 4K. Finally, assign the index to the port.
    */
    for (i = 0; i <= RTL8367B_CVIDXMAX; i++)
    {
        if (rtl8367b_getAsicVlanMemberConfig(i, &vlanMC) != RT_ERR_OK)
            return RT_ERR_FAILED;

        if (vlanMC.evid == 0 && vlanMC.mbr == 0)
        {
            vlan4K.vid = info.cvid;
            if ((ret_val = rtl8367b_getAsicVlan4kEntry(&vlan4K)) != RT_ERR_OK)
                return ret_val;

            vlanMC.evid = info.cvid;
            vlanMC.mbr = vlan4K.mbr;
            vlanMC.fid_msti = vlan4K.fid_msti;
            vlanMC.meteridx= vlan4K.meteridx;
            vlanMC.envlanpol= vlan4K.envlanpol;
            vlanMC.vbpen = vlan4K.vbpen;
            vlanMC.vbpri = vlan4K.vbpri;

            if ((ret_val = rtl8367b_setAsicVlanMemberConfig(i, &vlanMC)) != RT_ERR_OK)
                return ret_val;

            if ((ret_val = rtl8367b_getAsicVlanPortAndProtocolBased(port, used, &ppb_vlan_cfg)) != RT_ERR_OK)
                return ret_val;
            if (FALSE == ppb_vlan_cfg.valid)
            {
                ppb_vlan_cfg.vlan_idx = i;
                ppb_vlan_cfg.valid = TRUE;
                ppb_vlan_cfg.priority = info.cpri;
                if ((ret_val = rtl8367b_setAsicVlanPortAndProtocolBased(port, used, &ppb_vlan_cfg)) != RT_ERR_OK)
                    return ret_val;
                return RT_ERR_OK;
            }
            else
                return RT_ERR_VLAN_EXIST;
        }
    }

    return RT_ERR_FAILED;
}

/* Function Name:
 *      rtk_vlan_protoAndPortBasedVlan_get
 * Description:
 *      Get the protocol-and-port-based vlan to the specified port of device.
 * Input:
 *      port - Port id.
 *      proto_type - protocol-and-port-based vlan protocol type.
 *      frame_type - protocol-and-port-based vlan frame type.
 * Output:
 *      pInfo - Protocol and port based VLAN configuration information.
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_PORT_ID          - Invalid port number.
 *      RT_ERR_OUT_OF_RANGE     - input out of range.
 *      RT_ERR_TBL_FULL         - Table is full.
 * Note:
 *     The incoming packet which match the protocol-and-port-based vlan will use the configure vid for ingress pipeline
 *     The frame type is shown in the following:
 *      - FRAME_TYPE_ETHERNET
 *      - FRAME_TYPE_RFC1042
 *      - FRAME_TYPE_LLCOTHER
 */
int rtk_vlan_protoAndPortBasedVlan_get(unsigned int port, rtk_vlan_proto_type_t proto_type, rtk_vlan_protoVlan_frameType_t frame_type, rtk_vlan_protoAndPortInfo_t *pInfo)
{
    int ret_val;
    unsigned int i;
    unsigned int ppb_idx;
    rtl8367b_vlanconfiguser vlanMC;
    rtl8367b_protocolgdatacfg ppb_data_cfg;
    rtl8367b_protocolvlancfg ppb_vlan_cfg;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if (proto_type > RTK_MAX_NUM_OF_PROTO_TYPE)
        return RT_ERR_OUT_OF_RANGE;

    if (frame_type >= FRAME_TYPE_END)
        return RT_ERR_OUT_OF_RANGE;

   ppb_idx = 0;

    for (i = 0; i<= RTL8367B_PROTOVLAN_GIDX_MAX; i++)
    {
        if ((ret_val = rtl8367b_getAsicVlanProtocolBasedGroupData(i, &ppb_data_cfg)) != RT_ERR_OK)
            return ret_val;

        if (ppb_data_cfg.frameType == frame_type && ppb_data_cfg.etherType == proto_type)
        {
            ppb_idx = i;
            break;
        }
        else if (RTL8367B_PROTOVLAN_GIDX_MAX == i)
            return RT_ERR_TBL_FULL;
    }

    if ((ret_val = rtl8367b_getAsicVlanPortAndProtocolBased(port, ppb_idx, &ppb_vlan_cfg)) != RT_ERR_OK)
        return ret_val;

    if (FALSE == ppb_vlan_cfg.valid)
        return RT_ERR_FAILED;

    if ((ret_val = rtl8367b_getAsicVlanMemberConfig(ppb_vlan_cfg.vlan_idx, &vlanMC)) != RT_ERR_OK)
        return ret_val;

    pInfo->frame_type = frame_type;
    pInfo->proto_type = proto_type;
    pInfo->cvid = vlanMC.evid;
    pInfo->cpri = ppb_vlan_cfg.priority;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_vlan_protoAndPortBasedVlan_del
 * Description:
 *      Delete the protocol-and-port-based vlan from the specified port of device.
 * Input:
 *      port        - Port id.
 *      proto_type  - protocol-and-port-based vlan protocol type.
 *      frame_type  - protocol-and-port-based vlan frame type.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_PORT_ID          - Invalid port number.
 *      RT_ERR_OUT_OF_RANGE     - input out of range.
 *      RT_ERR_TBL_FULL         - Table is full.
 * Note:
 *     The incoming packet which match the protocol-and-port-based vlan will use the configure vid for ingress pipeline
 *     The frame type is shown in the following:
 *      - FRAME_TYPE_ETHERNET
 *      - FRAME_TYPE_RFC1042
 *      - FRAME_TYPE_LLCOTHER
 */
int rtk_vlan_protoAndPortBasedVlan_del(unsigned int port, rtk_vlan_proto_type_t proto_type, rtk_vlan_protoVlan_frameType_t frame_type)
{
    int ret_val;
    unsigned int i, bUsed;
    unsigned int ppb_idx;
    rtl8367b_protocolgdatacfg ppb_data_cfg;
    rtl8367b_protocolvlancfg ppb_vlan_cfg;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if (proto_type > RTK_MAX_NUM_OF_PROTO_TYPE)
        return RT_ERR_OUT_OF_RANGE;

    if (frame_type >= FRAME_TYPE_END)
        return RT_ERR_OUT_OF_RANGE;

   ppb_idx = 0;

    for (i = 0; i<= RTL8367B_PROTOVLAN_GIDX_MAX; i++)
    {
        if ((ret_val = rtl8367b_getAsicVlanProtocolBasedGroupData(i, &ppb_data_cfg)) != RT_ERR_OK)
            return ret_val;

        if (ppb_data_cfg.frameType == frame_type && ppb_data_cfg.etherType == proto_type)
        {
            ppb_idx = i;
            ppb_vlan_cfg.valid = FALSE;
            ppb_vlan_cfg.vlan_idx = 0;
            ppb_vlan_cfg.priority = 0;
            if ((ret_val = rtl8367b_setAsicVlanPortAndProtocolBased(port, ppb_idx, &ppb_vlan_cfg)) != RT_ERR_OK)
                return ret_val;
        }
    }

    bUsed = FALSE;
    for (i = 0; i < RTK_MAX_NUM_OF_PORT; i++)
    {
        if ((ret_val = rtl8367b_getAsicVlanPortAndProtocolBased(i, ppb_idx, &ppb_vlan_cfg)) != RT_ERR_OK)
            return ret_val;

        if (TRUE == ppb_vlan_cfg.valid)
        {
            bUsed = TRUE;
                break;
        }
    }

    if (FALSE == bUsed) /*No Port use this PPB Index, Delete it*/
    {
        ppb_data_cfg.etherType=0;
        ppb_data_cfg.frameType=0;
        if ((ret_val = rtl8367b_setAsicVlanProtocolBasedGroupData(ppb_idx, &ppb_data_cfg)) != RT_ERR_OK)
            return ret_val;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_vlan_protoAndPortBasedVlan_delAll
 * Description:
 *     Delete all protocol-and-port-based vlans from the specified port of device.
 * Input:
 *      port - Port id.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_PORT_ID          - Invalid port number.
 *      RT_ERR_OUT_OF_RANGE     - input out of range.
 * Note:
 *     The incoming packet which match the protocol-and-port-based vlan will use the configure vid for ingress pipeline
 *     Delete all flow table protocol-and-port-based vlan entries.
 */
int rtk_vlan_protoAndPortBasedVlan_delAll(unsigned int port)
{
    int ret_val;
    unsigned int i, j, bUsed[4];
    rtl8367b_protocolgdatacfg ppb_data_cfg;
    rtl8367b_protocolvlancfg ppb_vlan_cfg;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    for (i = 0; i<= RTL8367B_PROTOVLAN_GIDX_MAX; i++)
    {
        ppb_vlan_cfg.valid = FALSE;
        ppb_vlan_cfg.vlan_idx = 0;
        ppb_vlan_cfg.priority = 0;
        if ((ret_val = rtl8367b_setAsicVlanPortAndProtocolBased(port, i, &ppb_vlan_cfg)) != RT_ERR_OK)
            return ret_val;
    }

    bUsed[0] = FALSE;
    bUsed[1] = FALSE;
    bUsed[2] = FALSE;
    bUsed[3] = FALSE;
    for (i = 0; i < RTK_MAX_NUM_OF_PORT; i++)
    {
        for (j = 0; j <= RTL8367B_PROTOVLAN_GIDX_MAX; j++)
        {
            if ((ret_val = rtl8367b_getAsicVlanPortAndProtocolBased(i,j, &ppb_vlan_cfg)) != RT_ERR_OK)
                return ret_val;

            if (TRUE == ppb_vlan_cfg.valid)
            {
                bUsed[j] = TRUE;
            }
        }
    }

    for (i = 0; i<= RTL8367B_PROTOVLAN_GIDX_MAX; i++)
    {
        if (FALSE == bUsed[i]) /*No Port use this PPB Index, Delete it*/
        {
            ppb_data_cfg.etherType=0;
            ppb_data_cfg.frameType=0;
            if ((ret_val = rtl8367b_setAsicVlanProtocolBasedGroupData(i, &ppb_data_cfg)) != RT_ERR_OK)
                return ret_val;
        }
    }



    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_vlan_tagMode_set
 * Description:
 *      Set CVLAN egress tag mode
 * Input:
 *      port        - Port id.
 *      tag_mode    - The egress tag mode.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 *      RT_ERR_INPUT        - Invalid input parameter.
 *      RT_ERR_ENABLE       - Invalid enable input.
 * Note:
 *      The API can set Egress tag mode. There are 4 mode for egress tag:
 *      - VLAN_TAG_MODE_ORIGINAL,
 *      - VLAN_TAG_MODE_KEEP_FORMAT,
 *      - VLAN_TAG_MODE_PRI.
 *      - VLAN_TAG_MODE_REAL_KEEP_FORMAT,
 */
int rtk_vlan_tagMode_set(unsigned int port, rtk_vlan_tagMode_t tag_mode)
{
    int ret_val;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if (tag_mode >= VLAN_TAG_MODE_END)
        return RT_ERR_PORT_ID;

    if ((ret_val = rtl8367b_setAsicVlanEgressTagMode(port, tag_mode)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_vlan_tagMode_get
 * Description:
 *      Get CVLAN egress tag mode
 * Input:
 *      port - Port id.
 * Output:
 *      pTag_mode - The egress tag mode.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *      The API can get Egress tag mode. There are 4 mode for egress tag:
 *      - VLAN_TAG_MODE_ORIGINAL,
 *      - VLAN_TAG_MODE_KEEP_FORMAT,
 *      - VLAN_TAG_MODE_PRI.
 *      - VLAN_TAG_MODE_REAL_KEEP_FORMAT,
 */
int rtk_vlan_tagMode_get(unsigned int port, rtk_vlan_tagMode_t *pTag_mode)
{
    int ret_val;
    rtl8367b_egtagmode  mode;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if ((ret_val = rtl8367b_getAsicVlanEgressTagMode(port, &mode)) != RT_ERR_OK)
        return ret_val;

    *pTag_mode = (rtk_vlan_tagMode_t)mode;
    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_vlan_transparent_set
 * Description:
 *      Set VLAN transparent mode
 * Input:
 *      egr_port        - Egress Port id.
 *      igr_pmask       - Ingress Port Mask.
 *      enabled         - VLAN Transparent. Enabled: Ignore VLAN egress Filtering, Disable: Follow VLAN egress Filtering
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *      None.
 */
int rtk_vlan_transparent_set(unsigned int egr_port, rtk_portmask_t igr_pmask, rtk_enable_t enable)
{
     int ret_val;

     if (egr_port > RTK_PORT_ID_MAX)
         return RT_ERR_PORT_ID;

     if ((ret_val = rtl8367b_setAsicVlanTransparent(enable)) != RT_ERR_OK)
         return ret_val;

     if ((ret_val = rtl8367b_setAsicVlanEgressKeep(egr_port, igr_pmask.bits[0])) != RT_ERR_OK)
         return ret_val;

     return RT_ERR_OK;
}

/* Function Name:
 *      rtk_vlan_transparent_get
 * Description:
 *      Get VLAN transparent mode
 * Input:
 *      egr_port        - Egress Port id.
 * Output:
 *      pIgr_pmask      - Ingress Port Mask
 *      pEnabled        - VLAN Transparent. Enabled: Ignore VLAN egress Filtering, Disable: Follow VLAN egress Filtering
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *      None.
 */
int rtk_vlan_transparent_get(unsigned int egr_port, rtk_portmask_t *pIgr_pmask, rtk_enable_t *pEnable)
{
     int ret_val;
     unsigned int    pmask;

     if (egr_port > RTK_PORT_ID_MAX)
         return RT_ERR_PORT_ID;

     if ((ret_val = rtl8367b_getAsicVlanTransparent(pEnable)) != RT_ERR_OK)
         return ret_val;

     if ((ret_val = rtl8367b_getAsicVlanEgressKeep(egr_port, &pmask)) != RT_ERR_OK)
         return ret_val;

     pIgr_pmask->bits[0] = pmask;
     return RT_ERR_OK;
}

/* Function Name:
 *      rtk_vlan_stg_set
 * Description:
 *      Set spanning tree group instance of the vlan to the specified device
 * Input:
 *      vid - Specified VLAN ID.
 *      stg - spanning tree group instance.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_MSTI         - Invalid msti parameter
 *      RT_ERR_INPUT        - Invalid input parameter.
 *      RT_ERR_VLAN_VID     - Invalid VID parameter.
 * Note:
 *      The API can set spanning tree group instance of the vlan to the specified device.
 */
int rtk_vlan_stg_set(rtk_vlan_t vid, rtk_stg_t stg)
{
    int ret_val;
    rtl8367b_user_vlan4kentry vlan4K;

    /* vid must be 0~4095 */
    if (vid > RTL8367B_VIDMAX)
        return RT_ERR_VLAN_VID;

    /* priority must be 0~15 */
    if (stg > RTL8367B_MSTIMAX)
        return RT_ERR_MSTI;

    /* update 4K table */
    vlan4K.vid = vid;
    if ((ret_val = rtl8367b_getAsicVlan4kEntry(&vlan4K)) != RT_ERR_OK)
        return ret_val;

    vlan4K.fid_msti= stg;
    if ((ret_val = rtl8367b_setAsicVlan4kEntry(&vlan4K)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_vlan_stg_get
 * Description:
 *      Get spanning tree group instance of the vlan to the specified device
 * Input:
 *      vid - Specified VLAN ID.
 * Output:
 *      pStg - spanning tree group instance.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 *      RT_ERR_VLAN_VID     - Invalid VID parameter.
 * Note:
 *      The API can get spanning tree group instance of the vlan to the specified device.
 */
int rtk_vlan_stg_get(rtk_vlan_t vid, rtk_stg_t *pStg)
{
    int ret_val;
    rtl8367b_user_vlan4kentry vlan4K;

    /* vid must be 0~4095 */
    if (vid > RTL8367B_VIDMAX)
        return RT_ERR_VLAN_VID;

    /* update 4K table */
    vlan4K.vid = vid;
    if ((ret_val = rtl8367b_getAsicVlan4kEntry(&vlan4K)) != RT_ERR_OK)
        return ret_val;

    *pStg = vlan4K.fid_msti;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_vlan_portFid_set
 * Description:
 *      Set port-based filtering database
 * Input:
 *      port - Port id.
 *      enable - ebable port-based FID
 *      fid - Specified filtering database.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 *      RT_ERR_L2_FID - Invalid fid.
 *      RT_ERR_INPUT - Invalid input parameter.
 *      RT_ERR_PORT_ID - Invalid port ID.
 * Note:
 *      The API can set port-based filtering database. If the function is enabled, all input
 *      packets will be assigned to the port-based fid regardless vlan tag.
 */
int rtk_vlan_portFid_set(unsigned int port, rtk_enable_t enable, unsigned int fid)
{
    int ret_val;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if (enable>=RTK_ENABLE_END)
        return RT_ERR_ENABLE;

    /* fid must be 0~4095 */
    if (fid > RTK_FID_MAX)
        return RT_ERR_L2_FID;

    if ((ret_val = rtl8367b_setAsicPortBasedFidEn(port, enable))!=RT_ERR_OK)
        return ret_val;

    if ((ret_val = rtl8367b_setAsicPortBasedFid(port, fid))!=RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_vlan_portFid_get
 * Description:
 *      Get port-based filtering database
 * Input:
 *      port - Port id.
 * Output:
 *      pEnable - ebable port-based FID
 *      pFid - Specified filtering database.
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 *      RT_ERR_INPUT - Invalid input parameters.
 *      RT_ERR_PORT_ID - Invalid port ID.
 * Note:
 *      The API can get port-based filtering database status. If the function is enabled, all input
 *      packets will be assigned to the port-based fid regardless vlan tag.
 */
int rtk_vlan_portFid_get(unsigned int port, rtk_enable_t *pEnable, unsigned int *pFid)
{
    int ret_val;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if ((ret_val = rtl8367b_getAsicPortBasedFidEn(port, pEnable))!=RT_ERR_OK)
        return ret_val;

    if ((ret_val = rtl8367b_getAsicPortBasedFid(port, pFid))!=RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_stp_init
 * Description:
 *      Initialize stp module of the specified device
 * Input:
 *      None
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 * Note:
 *      Initialize stp module before calling any vlan APIs
 */
int rtk_stp_init(void)
{
    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_stp_mstpState_set
 * Description:
 *      Configure spanning tree state per each port.
 * Input:
 *      port - Port id
 *      msti - Multiple spanning tree instance.
 *      stp_state - Spanning tree state for msti
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 *      RT_ERR_MSTI         - Invalid msti parameter.
 *      RT_ERR_MSTP_STATE   - Invalid STP state.
 * Note:
 *      System supports per-port multiple spanning tree state for each msti.
 *      There are four states supported by ASIC.
 *      - STP_STATE_DISABLED
 *      - STP_STATE_BLOCKING
 *      - STP_STATE_LEARNING
 *      - STP_STATE_FORWARDING
 */
int rtk_stp_mstpState_set(rtk_stp_msti_id_t msti, unsigned int port, rtk_stp_state_t stp_state)
{
    int ret_val;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if (msti > RTK_MAX_NUM_OF_MSTI)
        return RT_ERR_MSTI;

    if (stp_state >= STP_STATE_END)
        return RT_ERR_MSTP_STATE;

    if ((ret_val = rtl8367b_setAsicSpanningTreeStatus(port, msti, stp_state)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_stp_mstpState_get
 * Description:
 *      Get spanning tree state per each port.
 * Input:
 *      port - Port id.
 *      msti - Multiple spanning tree instance.
 * Output:
 *      pStp_state - Spanning tree state for msti
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 *      RT_ERR_MSTI         - Invalid msti parameter.
 * Note:
 *      System supports per-port multiple spanning tree state for each msti.
 *      There are four states supported by ASIC.
 *      - STP_STATE_DISABLED
 *      - STP_STATE_BLOCKING
 *      - STP_STATE_LEARNING
 *      - STP_STATE_FORWARDING
 */
int rtk_stp_mstpState_get(rtk_stp_msti_id_t msti, unsigned int port, rtk_stp_state_t *pStp_state)
{
    int ret_val;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if ((ret_val = rtl8367b_getAsicSpanningTreeStatus(port, msti, pStp_state)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_l2_init
 * Description:
 *      Initialize l2 module of the specified device.
 * Input:
 *      None
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK          - OK
 *      RT_ERR_FAILED      - Failed
 *      RT_ERR_SMI         - SMI access error
 * Note:
 *      Initialize l2 module before calling any l2 APIs.
 */
int rtk_l2_init(void)
{
    int ret_val;
    unsigned int i;

    if ((ret_val = rtl8367b_setAsicLutIpMulticastLookup(DISABLE)) != RT_ERR_OK)
        return ret_val;

    /*Enable CAM Usage*/
    if ((ret_val = rtl8367b_setAsicLutCamTbUsage(ENABLE)) != RT_ERR_OK)
        return ret_val;

    if ((ret_val = rtl8367b_setAsicLutAgeTimerSpeed(6,2)) != RT_ERR_OK)
        return ret_val;

    for (i = 0; i <= RTK_PORT_ID_MAX; i++)
    {
        if ((ret_val = rtl8367b_setAsicLutLearnLimitNo(i,2112)) != RT_ERR_OK)
            return ret_val;
    }

    return RT_ERR_OK;
}


/* Function Name:
 *      rtk_l2_addr_add
 * Description:
 *      Add LUT unicast entry.
 * Input:
 *      pMac - 6 bytes unicast(I/G bit is 0) mac address to be written into LUT.
 *      pL2_data - Unicast entry parameter
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_PORT_ID          - Invalid port number.
 *      RT_ERR_MAC              - Invalid MAC address.
 *      RT_ERR_L2_FID           - Invalid FID .
 *      RT_ERR_L2_INDEXTBL_FULL - hashed index is full of entries.
 *      RT_ERR_INPUT            - Invalid input parameters.
 * Note:
 *      If the unicast mac address already existed in LUT, it will udpate the status of the entry.
 *      Otherwise, it will find an empty or asic auto learned entry to write. If all the entries
 *      with the same hash value can't be replaced, ASIC will return a RT_ERR_L2_INDEXTBL_FULL error.
 */
int rtk_l2_addr_add(rtk_mac_t *pMac, rtk_l2_ucastAddr_t *pL2_data)
{
    int ret_val;
    unsigned int method;
    rtl8367b_luttb l2Table;

    /* must be unicast address */
    if ((pMac == NULL) || (pMac->octet[0] & 0x1))
        return RT_ERR_MAC;

    if (pL2_data->port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if (pL2_data->ivl >= RTK_ENABLE_END)
        return RT_ERR_INPUT;

    if (pL2_data->cvid > RTL8367B_VIDMAX)
        return RT_ERR_L2_VID;

    if (pL2_data->fid > RTL8367B_FIDMAX)
        return RT_ERR_L2_FID;

    if (pL2_data->is_static>= RTK_ENABLE_END)
        return RT_ERR_INPUT;

    if (pL2_data->sa_block>= RTK_ENABLE_END)
        return RT_ERR_INPUT;

    if (pL2_data->da_block>= RTK_ENABLE_END)
        return RT_ERR_INPUT;

    if (pL2_data->auth>= RTK_ENABLE_END)
        return RT_ERR_INPUT;

    if (pL2_data->efid> RTL8367B_EFIDMAX)
        return RT_ERR_INPUT;

    memset(&l2Table, 0, sizeof(rtl8367b_luttb));

    /* fill key (MAC,FID) to get L2 entry */
    memcpy(l2Table.mac.octet, pMac->octet, ETHER_ADDR_LEN);
    l2Table.ivl_svl     = pL2_data->ivl;
    l2Table.fid         = pL2_data->fid;
    l2Table.cvid_fid    = pL2_data->cvid;
    l2Table.efid        = pL2_data->efid;
    method = LUTREADMETHOD_MAC;
    ret_val = rtl8367b_getAsicL2LookupTb(method, &l2Table);
    if (RT_ERR_OK == ret_val )
    {
        memcpy(l2Table.mac.octet, pMac->octet, ETHER_ADDR_LEN);
        l2Table.ivl_svl     = pL2_data->ivl;
        l2Table.cvid_fid    = pL2_data->cvid;
        l2Table.fid         = pL2_data->fid;
        l2Table.efid        = pL2_data->efid;
        l2Table.spa         = pL2_data->port;
        l2Table.nosalearn   = pL2_data->is_static;
        l2Table.sa_block    = pL2_data->sa_block;
        l2Table.da_block    = pL2_data->da_block;
        l2Table.l3lookup    = 0;
        l2Table.auth        = pL2_data->auth;
        l2Table.age         = 6;
        ret_val = rtl8367b_setAsicL2LookupTb(&l2Table);

        return ret_val;
    }
    else if (RT_ERR_L2_ENTRY_NOTFOUND == ret_val )
    {
        memset(&l2Table, 0, sizeof(rtl8367b_luttb));
        memcpy(l2Table.mac.octet, pMac->octet, ETHER_ADDR_LEN);
        l2Table.ivl_svl     = pL2_data->ivl;
        l2Table.cvid_fid    = pL2_data->cvid;
        l2Table.fid         = pL2_data->fid;
        l2Table.efid        = pL2_data->efid;
        l2Table.spa         = pL2_data->port;
        l2Table.nosalearn   = pL2_data->is_static;
        l2Table.sa_block    = pL2_data->sa_block;
        l2Table.da_block    = pL2_data->da_block;
        l2Table.l3lookup    = 0;
        l2Table.auth        = pL2_data->auth;
        l2Table.age         = 6;

        if ((ret_val = rtl8367b_setAsicL2LookupTb(&l2Table)) != RT_ERR_OK)
            return ret_val;

        method = LUTREADMETHOD_MAC;
        ret_val = rtl8367b_getAsicL2LookupTb(method, &l2Table);
        if (RT_ERR_L2_ENTRY_NOTFOUND == ret_val )
            return RT_ERR_L2_INDEXTBL_FULL;
        else
            return ret_val;
    }
    else
        return ret_val;

}

/* Function Name:
 *      rtk_l2_addr_get
 * Description:
 *      Get LUT unicast entry.
 * Input:
 *      pMac    - 6 bytes unicast(I/G bit is 0) mac address to be written into LUT.
 * Output:
 *      pL2_data - Unicast entry parameter
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_PORT_ID              - Invalid port number.
 *      RT_ERR_MAC                  - Invalid MAC address.
 *      RT_ERR_L2_FID               - Invalid FID .
 *      RT_ERR_L2_ENTRY_NOTFOUND    - No such LUT entry.
 *      RT_ERR_INPUT                - Invalid input parameters.
 * Note:
 *      If the unicast mac address existed in LUT, it will return the port and fid where
 *      the mac is learned. Otherwise, it will return a RT_ERR_L2_ENTRY_NOTFOUND error.
 */
int rtk_l2_addr_get(rtk_mac_t *pMac, rtk_l2_ucastAddr_t *pL2_data)
{
    int ret_val;
    unsigned int method;
    rtl8367b_luttb l2Table;

    /* must be unicast address */
    if ((pMac == NULL) || (pMac->octet[0] & 0x1))
        return RT_ERR_MAC;

    if (pL2_data->fid > RTL8367B_FIDMAX || pL2_data->efid > RTL8367B_EFIDMAX)
        return RT_ERR_L2_FID;

    memset(&l2Table, 0, sizeof(rtl8367b_luttb));

    memcpy(l2Table.mac.octet, pMac->octet, ETHER_ADDR_LEN);
    l2Table.ivl_svl     = pL2_data->ivl;
    l2Table.cvid_fid    = pL2_data->cvid;
    l2Table.fid         = pL2_data->fid;
    l2Table.efid        = pL2_data->efid;
    method = LUTREADMETHOD_MAC;

    if ((ret_val = rtl8367b_getAsicL2LookupTb(method, &l2Table)) != RT_ERR_OK)
        return ret_val;

    memcpy(pL2_data->mac.octet, pMac->octet,ETHER_ADDR_LEN);
    pL2_data->port      = l2Table.spa;
    pL2_data->fid       = l2Table.fid;
    pL2_data->efid      = l2Table.efid;
    pL2_data->ivl       = l2Table.ivl_svl;
    pL2_data->cvid      = l2Table.cvid_fid;
    pL2_data->is_static = l2Table.nosalearn;
    pL2_data->auth      = l2Table.auth;
    pL2_data->sa_block  = l2Table.sa_block;
    pL2_data->da_block  = l2Table.da_block;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_l2_addr_next_get
 * Description:
 *      Get Next LUT unicast entry.
 * Input:
 *      read_method     - The reading method.
 *      port            - The port number if the read_metohd is READMETHOD_NEXT_L2UCSPA
 *      pAddress        - The Address ID
 * Output:
 *      pL2_data - Unicast entry parameter
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_PORT_ID              - Invalid port number.
 *      RT_ERR_MAC                  - Invalid MAC address.
 *      RT_ERR_L2_FID               - Invalid FID .
 *      RT_ERR_L2_ENTRY_NOTFOUND    - No such LUT entry.
 *      RT_ERR_INPUT                - Invalid input parameters.
 * Note:
 *      Get the next unicast entry after the current entry pointed by pAddress.
 *      The address of next entry is returned by pAddress. User can use (address + 1)
 *      as pAddress to call this API again for dumping all entries is LUT.
 */
int rtk_l2_addr_next_get(rtk_l2_read_method_t read_method, unsigned int port, unsigned int *pAddress, rtk_l2_ucastAddr_t *pL2_data)
{
    int   ret_val;
    unsigned int      method;
    rtl8367b_luttb  l2Table;

    /* Error Checking */
    if ((pL2_data == NULL) || (pAddress == NULL))
        return RT_ERR_MAC;

    if(read_method == READMETHOD_NEXT_L2UC)
        method = LUTREADMETHOD_NEXT_L2UC;
    else if(read_method == READMETHOD_NEXT_L2UCSPA)
        method = LUTREADMETHOD_NEXT_L2UCSPA;
    else
        return RT_ERR_INPUT;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if(*pAddress > RTK_MAX_LUT_ADDR_ID )
        return RT_ERR_L2_L2UNI_PARAM;

    memset(&l2Table, 0, sizeof(rtl8367b_luttb));
    l2Table.address = *pAddress;

    if(read_method == READMETHOD_NEXT_L2UCSPA)
        l2Table.spa = port;

    if ((ret_val = rtl8367b_getAsicL2LookupTb(method, &l2Table)) != RT_ERR_OK)
        return ret_val;

    if(l2Table.address < *pAddress)
        return RT_ERR_L2_ENTRY_NOTFOUND;

    memcpy(pL2_data->mac.octet, l2Table.mac.octet, ETHER_ADDR_LEN);
    pL2_data->port      = l2Table.spa;
    pL2_data->fid       = l2Table.fid;
    pL2_data->efid      = l2Table.efid;
    pL2_data->ivl       = l2Table.ivl_svl;
    pL2_data->cvid      = l2Table.cvid_fid;
    pL2_data->is_static = l2Table.nosalearn;
    pL2_data->auth      = l2Table.auth;
    pL2_data->sa_block  = l2Table.sa_block;
    pL2_data->da_block  = l2Table.da_block;

    *pAddress = l2Table.address;

    return RT_ERR_OK;

}

/* Function Name:
 *      rtk_l2_addr_del
 * Description:
 *      Delete LUT unicast entry.
 * Input:
 *      pMac - 6 bytes unicast(I/G bit is 0) mac address to be written into LUT.
 *      fid - Filtering database
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_PORT_ID              - Invalid port number.
 *      RT_ERR_MAC                  - Invalid MAC address.
 *      RT_ERR_L2_FID               - Invalid FID .
 *      RT_ERR_L2_ENTRY_NOTFOUND    - No such LUT entry.
 *      RT_ERR_INPUT                - Invalid input parameters.
 * Note:
 *      If the mac has existed in the LUT, it will be deleted. Otherwise, it will return RT_ERR_L2_ENTRY_NOTFOUND.
 */
int rtk_l2_addr_del(rtk_mac_t *pMac, rtk_l2_ucastAddr_t *pL2_data)
{
    int ret_val;
    unsigned int method;
    rtl8367b_luttb l2Table;

    /* must be unicast address */
    if ((pMac == NULL) || (pMac->octet[0] & 0x1))
        return RT_ERR_MAC;

    if (pL2_data->fid > RTL8367B_FIDMAX || pL2_data->efid > RTL8367B_EFIDMAX)
        return RT_ERR_L2_FID;

    memset(&l2Table, 0, sizeof(rtl8367b_luttb));

    /* fill key (MAC,FID) to get L2 entry */
    memcpy(l2Table.mac.octet, pMac->octet, ETHER_ADDR_LEN);
    l2Table.ivl_svl     = pL2_data->ivl;
    l2Table.cvid_fid    = pL2_data->cvid;
    l2Table.fid         = pL2_data->fid;
    l2Table.efid        = pL2_data->efid;
    method = LUTREADMETHOD_MAC;
    ret_val = rtl8367b_getAsicL2LookupTb(method, &l2Table);
    if (RT_ERR_OK ==  ret_val)
    {
        memcpy(l2Table.mac.octet, pMac->octet, ETHER_ADDR_LEN);
        l2Table.ivl_svl     = pL2_data->ivl;
        l2Table.cvid_fid    = pL2_data->cvid;
	    l2Table.fid = pL2_data->fid;
	    l2Table.efid = pL2_data->efid;
        l2Table.spa = 0;
        l2Table.nosalearn = 0;
        l2Table.sa_block = 0;
        l2Table.da_block = 0;
        l2Table.auth = 0;
        l2Table.age = 0;
        ret_val = rtl8367b_setAsicL2LookupTb(&l2Table);
        return ret_val;
    }
    else
        return ret_val;
}

/* Function Name:
 *      rtk_l2_mcastAddr_add
 * Description:
 *      Add LUT multicast entry.
 * Input:
 *      pMac        - 6 bytes multicast(I/G bit is 1) mac address to be written into LUT.
 *      ivl         - IVL/SVL setting, 1:IVL, 0:SVL
 *      cvid_fid    - CVID or FID for the input LUT entry.
 *      portmask    - Port mask to be forwarded to.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_PORT_ID          - Invalid port number.
 *      RT_ERR_MAC              - Invalid MAC address.
 *      RT_ERR_L2_FID           - Invalid FID .
 *      RT_ERR_L2_VID           - Invalid VID .
 *      RT_ERR_L2_INDEXTBL_FULL - hashed index is full of entries.
 *      RT_ERR_PORT_MASK        - Invalid portmask.
 *      RT_ERR_INPUT            - Invalid input parameters.
 * Note:
 *      If the multicast mac address already existed in the LUT, it will udpate the
 *      port mask of the entry. Otherwise, it will find an empty or asic auto learned
 *      entry to write. If all the entries with the same hash value can't be replaced,
 *      ASIC will return a RT_ERR_L2_INDEXTBL_FULL error.
 */
int rtk_l2_mcastAddr_add(rtk_mac_t *pMac, unsigned int ivl, unsigned int cvid_fid, rtk_portmask_t portmask)
{
    int   ret_val;
    unsigned int      method;
    rtl8367b_luttb  l2Table;

    /* must be L2 multicast address */
    if ((pMac == NULL) || (!(pMac->octet[0] & 0x1)))
        return RT_ERR_MAC;

    if (portmask.bits[0]> RTK_MAX_PORT_MASK)
        return RT_ERR_PORT_MASK;

    if(ivl == 1)
    {
        if (cvid_fid > RTL8367B_VIDMAX)
            return RT_ERR_L2_VID;
    }
    else if(ivl == 0)
    {
        if (cvid_fid > RTL8367B_FIDMAX)
            return RT_ERR_L2_FID;
    }
    else
        return RT_ERR_INPUT;

    memset(&l2Table, 0, sizeof(rtl8367b_luttb));

    /* fill key (MAC,FID) to get L2 entry */
    memcpy(l2Table.mac.octet, pMac->octet, ETHER_ADDR_LEN);
    l2Table.ivl_svl     = ivl;
    l2Table.cvid_fid    = cvid_fid;
    method = LUTREADMETHOD_MAC;
    ret_val = rtl8367b_getAsicL2LookupTb(method, &l2Table);
    if (RT_ERR_OK == ret_val)
    {
        memcpy(l2Table.mac.octet, pMac->octet, ETHER_ADDR_LEN);
        l2Table.ivl_svl     = ivl;
        l2Table.cvid_fid    = cvid_fid;
        l2Table.mbr         = portmask.bits[0];
        l2Table.nosalearn   = 1;
        l2Table.l3lookup    = 0;
        ret_val = rtl8367b_setAsicL2LookupTb(&l2Table);
        return ret_val;
    }
    else if (RT_ERR_L2_ENTRY_NOTFOUND == ret_val)
    {
        memset(&l2Table, 0, sizeof(rtl8367b_luttb));
        memcpy(l2Table.mac.octet, pMac->octet, ETHER_ADDR_LEN);
        l2Table.ivl_svl     = ivl;
        l2Table.cvid_fid    = cvid_fid;
        l2Table.mbr         = portmask.bits[0];
        l2Table.nosalearn   = 1;
        if ((ret_val = rtl8367b_setAsicL2LookupTb(&l2Table)) != RT_ERR_OK)
            return ret_val;

        method = LUTREADMETHOD_MAC;
        ret_val = rtl8367b_getAsicL2LookupTb(method, &l2Table);
        if (RT_ERR_L2_ENTRY_NOTFOUND == ret_val)
            return     RT_ERR_L2_INDEXTBL_FULL;
        else
            return ret_val;

    }
    else
        return ret_val;

}

/* Function Name:
 *      rtk_l2_mcastAddr_get
 * Description:
 *      Get LUT multicast entry.
 * Input:
 *      pMac        - 6 bytes multicast(I/G bit is 1) mac address to be written into LUT.
 *      ivl         - IVL/SVL setting, 1:IVL, 0:SVL
 *      cvid_fid    - Filtering database
 * Output:
 *      pPortmask   - Port mask to be forwarded to.
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_MAC                  - Invalid MAC address.
 *      RT_ERR_L2_FID               - Invalid FID .
 *      RT_ERR_L2_VID               - Invalid VID .
 *      RT_ERR_L2_ENTRY_NOTFOUND    - No such LUT entry.
 *      RT_ERR_INPUT                - Invalid input parameters.
 * Note:
 *      If the multicast mac address existed in the LUT, it will return the port where
 *      the mac is learned. Otherwise, it will return a RT_ERR_L2_ENTRY_NOTFOUND error.
 */
int rtk_l2_mcastAddr_get(rtk_mac_t *pMac, unsigned int ivl, unsigned int cvid_fid, rtk_portmask_t *pPortmask)
{
    int ret_val;
    unsigned int method;
    rtl8367b_luttb l2Table;

    /* must be unicast address */
    if ((pMac == NULL) || !(pMac->octet[0] & 0x1))
        return RT_ERR_MAC;

    if(ivl == 1)
    {
        if (cvid_fid > RTL8367B_VIDMAX)
            return RT_ERR_L2_VID;
    }
    else if(ivl == 0)
    {
        if (cvid_fid > RTL8367B_FIDMAX)
            return RT_ERR_L2_FID;
    }
    else
        return RT_ERR_INPUT;

    memset(&l2Table, 0, sizeof(rtl8367b_luttb));
    memcpy(l2Table.mac.octet, pMac->octet, ETHER_ADDR_LEN);
    l2Table.ivl_svl     = ivl;
    l2Table.cvid_fid    = cvid_fid;
    method = LUTREADMETHOD_MAC;

    if ((ret_val = rtl8367b_getAsicL2LookupTb(method, &l2Table)) != RT_ERR_OK)
        return ret_val;

    pPortmask->bits[0] = l2Table.mbr;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_l2_mcastAddr_next_get
 * Description:
 *      Get Next L2 Multicast entry.
 * Input:
 *      pAddress        - The Address ID
 * Output:
 *      pMac            - Multicast MAC address
 *      pIvl            - IVL/SVL setting, 1:IVL, 0:SVL
 *      pCvid_fid       - CVID or FID
 *      pPortmask       - Member Port Mask
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_L2_ENTRY_NOTFOUND    - No such LUT entry.
 *      RT_ERR_INPUT                - Invalid input parameters.
 * Note:
 *      Get the next L2 multicast entry after the current entry pointed by pAddress.
 *      The address of next entry is returned by pAddress. User can use (address + 1)
 *      as pAddress to call this API again for dumping all multicast entries is LUT.
 */
int rtk_l2_mcastAddr_next_get(unsigned int *pAddress, rtk_mac_t *pMac, unsigned int *pIvl, unsigned int *pCvid_fid, rtk_portmask_t *pPortmask)
{
    int   ret_val;
    rtl8367b_luttb  l2Table;

    /* Error Checking */
    if ((pAddress == NULL) || (pMac == NULL) || (pIvl == NULL) || (pCvid_fid == NULL) || (pPortmask == NULL))
        return RT_ERR_INPUT;

    if(*pAddress > RTK_MAX_LUT_ADDR_ID )
        return RT_ERR_L2_L2UNI_PARAM;

    memset(&l2Table, 0, sizeof(rtl8367b_luttb));
    l2Table.address = *pAddress;

    if ((ret_val = rtl8367b_getAsicL2LookupTb(LUTREADMETHOD_NEXT_L2MC, &l2Table)) != RT_ERR_OK)
        return ret_val;

    if(l2Table.address < *pAddress)
        return RT_ERR_L2_ENTRY_NOTFOUND;

    memcpy(pMac->octet, l2Table.mac.octet, ETHER_ADDR_LEN);
    *pIvl       = l2Table.ivl_svl;
    *pCvid_fid  = l2Table.cvid_fid;
    pPortmask->bits[0] = l2Table.mbr;

    *pAddress = l2Table.address;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_l2_mcastAddr_del
 * Description:
 *      Delete LUT multicast entry.
 * Input:
 *      pMac        - 6 bytes multicast(I/G bit is 1) mac address to be written into LUT.
 *      ivl         - IVL/SVL setting, 1:IVL, 0:SVL
 *      cvid_fid    - Filtering database
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_MAC                  - Invalid MAC address.
 *      RT_ERR_L2_FID               - Invalid FID .
 *      RT_ERR_L2_VID               - Invalid VID .
 *      RT_ERR_L2_ENTRY_NOTFOUND    - No such LUT entry.
 *      RT_ERR_INPUT                - Invalid input parameters.
 * Note:
 *      If the mac has existed in the LUT, it will be deleted. Otherwise, it will return RT_ERR_L2_ENTRY_NOTFOUND.
 */
int rtk_l2_mcastAddr_del(rtk_mac_t *pMac, unsigned int ivl, unsigned int cvid_fid)
{
    int ret_val;
    unsigned int method;
    rtl8367b_luttb l2Table;

    /* must be unicast address */
    if ((pMac == NULL) || !(pMac->octet[0] & 0x1))
        return RT_ERR_MAC;

    if(ivl == 1)
    {
        if (cvid_fid > RTL8367B_VIDMAX)
            return RT_ERR_L2_VID;
    }
    else if(ivl == 0)
    {
        if (cvid_fid > RTL8367B_FIDMAX)
            return RT_ERR_L2_FID;
    }
    else
        return RT_ERR_INPUT;

    memset(&l2Table, 0, sizeof(rtl8367b_luttb));

    /* fill key (MAC,FID) to get L2 entry */
    memcpy(l2Table.mac.octet, pMac->octet, ETHER_ADDR_LEN);
    l2Table.ivl_svl     = ivl;
    l2Table.cvid_fid    = cvid_fid;
    method = LUTREADMETHOD_MAC;
    ret_val = rtl8367b_getAsicL2LookupTb(method, &l2Table);
    if (RT_ERR_OK == ret_val)
    {
        memcpy(l2Table.mac.octet, pMac->octet, ETHER_ADDR_LEN);
        l2Table.ivl_svl     = ivl;
        l2Table.cvid_fid    = cvid_fid;
        l2Table.mbr         = 0;
        l2Table.nosalearn   = 0;
        l2Table.sa_block    = 0;
        l2Table.l3lookup    = 0;
        ret_val = rtl8367b_setAsicL2LookupTb(&l2Table);
        return ret_val;
    }
    else
        return ret_val;
}

/* Function Name:
 *      rtk_l2_ipMcastAddr_add
 * Description:
 *      Add Lut IP multicast entry
 * Input:
 *      dip - Destination IP Address.
 *      sip - Source IP Address.
 *      portmask - Destination port mask.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_PORT_ID          - Invalid port number.
 *      RT_ERR_L2_INDEXTBL_FULL - hashed index is full of entries.
 *      RT_ERR_PORT_MASK        - Invalid portmask.
 *      RT_ERR_INPUT            - Invalid input parameters.
 * Note:
 *      System supports L2 entry with IP multicast DIP/SIP to forward IP multicasting frame as user
 *      desired. If this function is enabled, then system will be looked up L2 IP multicast entry to
 *      forward IP multicast frame directly without flooding.
 */
int rtk_l2_ipMcastAddr_add(unsigned int sip, unsigned int dip, rtk_portmask_t portmask)
{
    int ret_val;
    unsigned int method;
    rtl8367b_luttb l2Table;

    if (portmask.bits[0]> RTK_MAX_PORT_MASK)
        return RT_ERR_PORT_ID;

    l2Table.sip = sip;
    l2Table.dip = dip;
    l2Table.l3lookup = 1;
    method = LUTREADMETHOD_MAC;
    ret_val = rtl8367b_getAsicL2LookupTb(method, &l2Table);
    if (RT_ERR_OK == ret_val)
    {
        l2Table.sip = sip;
        l2Table.dip = dip;
        l2Table.mbr= portmask.bits[0];
        l2Table.nosalearn = 1;
        l2Table.l3lookup = 1;
        ret_val = rtl8367b_setAsicL2LookupTb(&l2Table);
        return ret_val;
    }
    else if (RT_ERR_L2_ENTRY_NOTFOUND == ret_val)
    {
        memset(&l2Table, 0, sizeof(rtl8367b_luttb));
        l2Table.sip = sip;
        l2Table.dip = dip;
        l2Table.mbr= portmask.bits[0];
        l2Table.nosalearn = 1;
        l2Table.l3lookup = 1;
        if ((ret_val = rtl8367b_setAsicL2LookupTb(&l2Table)) != RT_ERR_OK)
            return ret_val;

        method = LUTREADMETHOD_MAC;
        ret_val = rtl8367b_getAsicL2LookupTb(method, &l2Table);
        if (RT_ERR_L2_ENTRY_NOTFOUND == ret_val)
            return     RT_ERR_L2_INDEXTBL_FULL;
        else
            return ret_val;

    }
    else
        return ret_val;

}

/* Function Name:
 *      rtk_l2_ipMcastAddr_get
 * Description:
 *      Get LUT IP multicast entry.
 * Input:
 *      dip - Destination IP Address.
 *      sip - Source IP Address.
 * Output:
 *      pPortmask - Destination port mask.
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_L2_ENTRY_NOTFOUND    - No such LUT entry.
 *      RT_ERR_INPUT                - Invalid input parameters.
 * Note:
 *      The API can get Lut table of IP multicast entry.
 */
int rtk_l2_ipMcastAddr_get(unsigned int sip, unsigned int dip, rtk_portmask_t *pPortmask)
{
    int ret_val;
    unsigned int method;
    rtl8367b_luttb l2Table;

    l2Table.sip = sip;
    l2Table.dip = dip;
    l2Table.l3lookup = 1;
    method = LUTREADMETHOD_MAC;
    if ((ret_val = rtl8367b_getAsicL2LookupTb(method, &l2Table)) != RT_ERR_OK)
        return ret_val;

     pPortmask->bits[0] = l2Table.mbr;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_l2_ipMcastAddr_next_get
 * Description:
 *      Get Next IP Multicast entry.
 * Input:
 *      pAddress        - The Address ID
 * Output:
 *      pSip            - Source IP
 *      pDip            - Destination IP
 *      pPortmask       - Member Port Mask
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_L2_ENTRY_NOTFOUND    - No such LUT entry.
 *      RT_ERR_INPUT                - Invalid input parameters.
 * Note:
 *      Get the next IP multicast entry after the current entry pointed by pAddress.
 *      The address of next entry is returned by pAddress. User can use (address + 1)
 *      as pAddress to call this API again for dumping all IP multicast entries is LUT.
 */
int rtk_l2_ipMcastAddr_next_get(unsigned int *pAddress, unsigned int *pSip, unsigned int *pDip, rtk_portmask_t *pPortmask)
{
    int   ret_val;
    rtl8367b_luttb  l2Table;

    /* Error Checking */
    if ((pAddress == NULL) || (pSip == NULL) || (pDip == NULL) || (pPortmask == NULL))
        return RT_ERR_INPUT;

    if(*pAddress > RTK_MAX_LUT_ADDR_ID )
        return RT_ERR_L2_L2UNI_PARAM;

    memset(&l2Table, 0, sizeof(rtl8367b_luttb));
    l2Table.address = *pAddress;

    if ((ret_val = rtl8367b_getAsicL2LookupTb(LUTREADMETHOD_NEXT_L3MC, &l2Table)) != RT_ERR_OK)
        return ret_val;

    if(l2Table.address < *pAddress)
        return RT_ERR_L2_ENTRY_NOTFOUND;

    *pSip = l2Table.sip;
    *pDip = l2Table.dip;
    pPortmask->bits[0] = l2Table.mbr;

    *pAddress = l2Table.address;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_l2_ipMcastAddr_del
 * Description:
 *      Delete a ip multicast address entry from the specified device.
 * Input:
 *      pMac    - 6 bytes multicast(I/G bit is 1) mac address to be written into LUT.
 *      fid     - Filtering database
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_L2_ENTRY_NOTFOUND    - No such LUT entry.
 *      RT_ERR_INPUT                - Invalid input parameters.
 * Note:
 *      The API can delete a IP multicast address entry from the specified device.
 */
int rtk_l2_ipMcastAddr_del(unsigned int sip, unsigned int dip)
{
    int ret_val;
    unsigned int method;
    rtl8367b_luttb l2Table;

    l2Table.sip = sip;
    l2Table.dip = dip;
    l2Table.l3lookup = 1;
    method = LUTREADMETHOD_MAC;
    ret_val = rtl8367b_getAsicL2LookupTb(method, &l2Table);
    if (RT_ERR_OK == ret_val)
    {
        l2Table.sip = sip;
        l2Table.dip = dip;
        l2Table.mbr= 0;
        l2Table.nosalearn = 0;
        l2Table.l3lookup = 1;
        ret_val = rtl8367b_setAsicL2LookupTb(&l2Table);
        return ret_val;
    }
    else
        return ret_val;
}

/* Function Name:
 *      rtk_l2_flushType_set
 * Description:
 *      Flush L2 mac address by type in the specified device.
 * Input:
 *      type - flush type
 *      vid - VLAN id
 *      portOrTid - port id or trunk id
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 *      RT_ERR_VLAN_VID     - Invalid VID parameter.
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      This function trigger flushing of per-port L2 learning.
 *      When flushing operaton completes, the corresponding bit will be clear.
 *      The flush type as following:
 *      - FLUSH_TYPE_BY_PORT        (physical port)
 *      - FLUSH_TYPE_BY_PORT_VID    (physical port + VID)
 */
int rtk_l2_flushType_set(rtk_l2_flushType_t type, rtk_vlan_t vid, unsigned int portOrTid)
{
    int ret_val;

    if (type>=FLUSH_TYPE_END)
        return RT_ERR_INPUT;

    if (portOrTid > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    switch (type)
    {
        case FLUSH_TYPE_BY_PORT:
            if ((ret_val = rtl8367b_setAsicLutFlushMode(FLUSHMDOE_PORT)) != RT_ERR_OK)
                return ret_val;

            if ((ret_val = rtl8367b_setAsicLutForceFlush(1<<portOrTid)) != RT_ERR_OK)
                return ret_val;

            break;
        case FLUSH_TYPE_BY_PORT_VID:
            if ((ret_val = rtl8367b_setAsicLutFlushMode(FLUSHMDOE_VID)) != RT_ERR_OK)
                return ret_val;

            if ((ret_val = rtl8367b_setAsicLutFlushVid(vid)) != RT_ERR_OK)
                return ret_val;

            if ((ret_val = rtl8367b_setAsicLutForceFlush(1<<portOrTid)) != RT_ERR_OK)
                return ret_val;

            break;
        default:
            break;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_l2_ucastAddr_flush
 * Description:
 *      Flush L2 mac address by type in the specified device (both dynamic and static).
 * Input:
 *      pConfig - flush configuration
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 *      RT_ERR_VLAN_VID     - Invalid VID parameter.
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      flushByVid          - 1: Flush by VID, 0: Don't flush by VID
 *      vid                 - VID (0 ~ 4095)
 *      flushByPort         - 1: Flush by Port, 0: Don't flush by Port
 *      reserved            - Unused
 *      port                - Port ID
 *      flushByMac          - Not Supported
 *      ucastAddr           - Not Supported
 *      flushStaticAddr     - 1: Flush both Static and Dynamic entries, 0: Flush only Dynamic entries
 *      flushAddrOnAllPorts - 1: Flush VID-matched entries at all ports, 0: Flush VID-matched entries per port.
 */
int rtk_l2_ucastAddr_flush(rtk_l2_flushCfg_t *pConfig)
{
    int   ret_val;

    if(pConfig == NULL)
        return RT_ERR_NULL_POINTER;

    if(pConfig->flushByVid >= RTK_ENABLE_END)
        return RT_ERR_ENABLE;

    if(pConfig->flushByPort >= RTK_ENABLE_END)
        return RT_ERR_ENABLE;

    if(pConfig->flushByMac >= RTK_ENABLE_END)
        return RT_ERR_ENABLE;

    if(pConfig->flushStaticAddr >= RTK_ENABLE_END)
        return RT_ERR_ENABLE;

    if(pConfig->flushAddrOnAllPorts >= RTK_ENABLE_END)
        return RT_ERR_ENABLE;

    if(pConfig->vid >= RTL8367B_VIDMAX)
        return RT_ERR_VLAN_VID;

    if(pConfig->port >= RTL8367B_PORTIDMAX)
        return RT_ERR_PORT_ID;

    if(pConfig->flushByVid == ENABLED)
    {
        if ((ret_val = rtl8367b_setAsicLutFlushMode(FLUSHMDOE_VID)) != RT_ERR_OK)
            return ret_val;

        if ((ret_val = rtl8367b_setAsicLutFlushVid(pConfig->vid)) != RT_ERR_OK)
                return ret_val;

        if ((ret_val = rtl8367b_setAsicLutFlushType((pConfig->flushStaticAddr == ENABLED) ? FLUSHTYPE_BOTH : FLUSHTYPE_DYNAMIC)) != RT_ERR_OK)
            return ret_val;

        if(pConfig->flushAddrOnAllPorts == ENABLED)
        {
            if ((ret_val = rtl8367b_setAsicLutForceFlush(RTL8367B_PORTMASK)) != RT_ERR_OK)
                return ret_val;
        }
        else if(pConfig->flushByPort == ENABLED)
        {
            if ((ret_val = rtl8367b_setAsicLutForceFlush(1<<pConfig->port)) != RT_ERR_OK)
                return ret_val;
        }
        else
            return RT_ERR_INPUT;
    }
    else if(pConfig->flushByPort == ENABLED)
    {
        if ((ret_val = rtl8367b_setAsicLutFlushType((pConfig->flushStaticAddr == ENABLED) ? FLUSHTYPE_BOTH : FLUSHTYPE_DYNAMIC)) != RT_ERR_OK)
            return ret_val;

        if ((ret_val = rtl8367b_setAsicLutFlushMode(FLUSHMDOE_PORT)) != RT_ERR_OK)
            return ret_val;

        if ((ret_val = rtl8367b_setAsicLutForceFlush(1<<pConfig->port)) != RT_ERR_OK)
            return ret_val;
    }
    else if(pConfig->flushByMac == ENABLED)
    {
        /* Should use API "rtk_l2_addr_del" to remove a specified entry*/
        return RT_ERR_CHIP_NOT_SUPPORTED;
    }
    else
        return RT_ERR_INPUT;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_l2_flushLinkDownPortAddrEnable_set
 * Description:
 *      Set HW flush linkdown port mac configuration of the specified device.
 * Input:
 *      port - Port id.
 *      enable - link down flush status
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 *      RT_ERR_ENABLE       - Invalid enable input.
 * Note:
 *      The status of flush linkdown port address is as following:
 *      - DISABLED
 *      - ENABLED
 */
int rtk_l2_flushLinkDownPortAddrEnable_set(unsigned int port, rtk_enable_t enable)
{
    int ret_val;

    if (port != RTK_WHOLE_SYSTEM)
        return RT_ERR_PORT_ID;

    if (enable >= RTK_ENABLE_END)
        return RT_ERR_ENABLE;

    if ((ret_val = rtl8367b_setAsicLutLinkDownForceAging(enable)) != RT_ERR_OK)
        return ret_val;


    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_l2_flushLinkDownPortAddrEnable_get
 * Description:
 *      Get HW flush linkdown port mac configuration of the specified device.
 * Input:
 *      port - Port id.
 * Output:
 *      pEnable - link down flush status
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *      The status of flush linkdown port address is as following:
 *      - DISABLED
 *      - ENABLED
 */
int rtk_l2_flushLinkDownPortAddrEnable_get(unsigned int port, rtk_enable_t *pEnable)
{
    int ret_val;

    if (port != RTK_WHOLE_SYSTEM)
        return RT_ERR_PORT_ID;

    if ((ret_val = rtl8367b_getAsicLutLinkDownForceAging(pEnable)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_l2_agingEnable_set
 * Description:
 *      Set L2 LUT aging status per port setting.
 * Input:
 *      port    - Port id.
 *      enable  - Aging status
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 *      RT_ERR_ENABLE       - Invalid enable input.
 * Note:
 *      This API can be used to set L2 LUT aging status per port.
 */
int rtk_l2_agingEnable_set(unsigned int port, rtk_enable_t enable)
{
    int ret_val;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if (enable >= RTK_ENABLE_END)
        return RT_ERR_ENABLE;

    if(enable == 1)
        enable = 0;
    else
        enable = 1;

    if ((ret_val = rtl8367b_setAsicLutDisableAging(port,enable)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_l2_agingEnable_get
 * Description:
 *      Get L2 LUT aging status per port setting.
 * Input:
 *      port - Port id.
 * Output:
 *      pEnable - Aging status
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *      This API can be used to get L2 LUT aging function per port.
 */
int rtk_l2_agingEnable_get(unsigned int port, rtk_enable_t *pEnable)
{
    int ret_val;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if ((ret_val = rtl8367b_getAsicLutDisableAging(port, pEnable)) != RT_ERR_OK)
        return ret_val;

    if(*pEnable == 1)
        *pEnable = 0;
    else
        *pEnable = 1;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_l2_limitLearningCnt_set
 * Description:
 *      Set per-Port auto learning limit number
 * Input:
 *      port    - Port id.
 *      mac_cnt - Auto learning entries limit number
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_PORT_ID              - Invalid port number.
 *      RT_ERR_LIMITED_L2ENTRY_NUM  - Invalid auto learning limit number
 * Note:
 *      The API can set per-port ASIC auto learning limit number from 0(disable learning)
 *      to 8k.
 */
int rtk_l2_limitLearningCnt_set(unsigned int port, rtk_mac_cnt_t mac_cnt)
{
    int ret_val;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if (mac_cnt > RTK_MAX_NUM_OF_LEARN_LIMIT)
        return RT_ERR_LIMITED_L2ENTRY_NUM;

    if ((ret_val = rtl8367b_setAsicLutLearnLimitNo(port, mac_cnt)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_l2_limitLearningCnt_get
 * Description:
 *      Get per-Port auto learning limit number
 * Input:
 *      port - Port id.
 * Output:
 *      pMac_cnt - Auto learning entries limit number
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *      The API can get per-port ASIC auto learning limit number.
 */
int rtk_l2_limitLearningCnt_get(unsigned int port, rtk_mac_cnt_t *pMac_cnt)
{
    int ret_val;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if ((ret_val = rtl8367b_getAsicLutLearnLimitNo(port, pMac_cnt)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_l2_limitLearningCntAction_set
 * Description:
 *      Configure auto learn over limit number action.
 * Input:
 *      port - Port id.
 *      action - Auto learning entries limit number
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 *      RT_ERR_NOT_ALLOWED  - Invalid learn over action
 * Note:
 *      The API can set SA unknown packet action while auto learn limit number is over
 *      The action symbol as following:
 *      - LIMIT_LEARN_CNT_ACTION_DROP,
 *      - LIMIT_LEARN_CNT_ACTION_FORWARD,
 *      - LIMIT_LEARN_CNT_ACTION_TO_CPU,
 */
int rtk_l2_limitLearningCntAction_set(unsigned int port, rtk_l2_limitLearnCntAction_t action)
{
    int ret_val;
    unsigned int data;

    if (port != RTK_WHOLE_SYSTEM)
        return RT_ERR_PORT_ID;

    if ( LIMIT_LEARN_CNT_ACTION_DROP == action )
        data = 1;
    else if ( LIMIT_LEARN_CNT_ACTION_FORWARD == action )
        data = 0;
    else if ( LIMIT_LEARN_CNT_ACTION_TO_CPU == action )
        data = 2;
    else
        return RT_ERR_NOT_ALLOWED;

    if ((ret_val = rtl8367b_setAsicLutLearnOverAct(data)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_l2_limitLearningCntAction_get
 * Description:
 *      Get auto learn over limit number action.
 * Input:
 *      port - Port id.
 * Output:
 *      pAction - Learn over action
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *      The API can get SA unknown packet action while auto learn limit number is over
 *      The action symbol as following:
 *      - LIMIT_LEARN_CNT_ACTION_DROP,
 *      - LIMIT_LEARN_CNT_ACTION_FORWARD,
 *      - LIMIT_LEARN_CNT_ACTION_TO_CPU,
 */
int rtk_l2_limitLearningCntAction_get(unsigned int port, rtk_l2_limitLearnCntAction_t *pAction)
{
    int ret_val;
    unsigned int action;

    if (port != RTK_WHOLE_SYSTEM)
        return RT_ERR_PORT_ID;

    if ((ret_val = rtl8367b_getAsicLutLearnOverAct(&action)) != RT_ERR_OK)
        return ret_val;

    if ( 1 == action )
        *pAction = LIMIT_LEARN_CNT_ACTION_DROP;
    else if ( 0 == action )
        *pAction = LIMIT_LEARN_CNT_ACTION_FORWARD;
    else if ( 2 == action )
        *pAction = LIMIT_LEARN_CNT_ACTION_TO_CPU;
    else
    *pAction = action;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_l2_learningCnt_get
 * Description:
 *      Get per-Port current auto learning number
 * Input:
 *      port - Port id.
 * Output:
 *      pMac_cnt - ASIC auto learning entries number
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *      The API can get per-port ASIC auto learning number
 */
int rtk_l2_learningCnt_get(unsigned int port, rtk_mac_cnt_t *pMac_cnt)
{
    int ret_val;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if ((ret_val = rtl8367b_getAsicLutLearnNo(port, pMac_cnt)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_l2_floodPortMask_set
 * Description:
 *      Set flooding portmask
 * Input:
 *      type - flooding type.
 *      flood_portmask - flooding porkmask
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_MASK    - Invalid portmask.
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      This API can set the flooding mask.
 *      The flooding type is as following:
 *      - FLOOD_UNKNOWNDA
 *      - FLOOD_UNKNOWNMC
 *      - FLOOD_BC
 */
int rtk_l2_floodPortMask_set(rtk_l2_flood_type_t floood_type, rtk_portmask_t flood_portmask)
{
    int ret_val;

    if (floood_type >= FLOOD_END)
        return RT_ERR_INPUT;

    if (flood_portmask.bits[0] > RTK_MAX_PORT_MASK)
        return RT_ERR_PORT_MASK;

    switch (floood_type)
    {
        case FLOOD_UNKNOWNDA:
            if ((ret_val = rtl8367b_setAsicPortUnknownDaFloodingPortmask(flood_portmask.bits[0])) != RT_ERR_OK)
                return ret_val;
            break;
        case FLOOD_UNKNOWNMC:
            if ((ret_val = rtl8367b_setAsicPortUnknownMulticastFloodingPortmask(flood_portmask.bits[0])) != RT_ERR_OK)
                return ret_val;
            break;
        case FLOOD_BC:
            if ((ret_val = rtl8367b_setAsicPortBcastFloodingPortmask(flood_portmask.bits[0])) != RT_ERR_OK)
                return ret_val;
            break;
        default:
            break;
    }

    return RT_ERR_OK;
}
/* Function Name:
 *      rtk_l2_floodPortMask_get
 * Description:
 *      Get flooding portmask
 * Input:
 *      type - flooding type.
 * Output:
 *      pFlood_portmask - flooding porkmask
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *      This API can get the flooding mask.
 *      The flooding type is as following:
 *      - FLOOD_UNKNOWNDA
 *      - FLOOD_UNKNOWNMC
 *      - FLOOD_BC
 */
int rtk_l2_floodPortMask_get(rtk_l2_flood_type_t floood_type, rtk_portmask_t *pFlood_portmask)
{
    int ret_val;

    if (floood_type >= FLOOD_END)
        return RT_ERR_INPUT;

    switch (floood_type)
    {
        case FLOOD_UNKNOWNDA:
            if ((ret_val = rtl8367b_getAsicPortUnknownDaFloodingPortmask(&pFlood_portmask->bits[0])) != RT_ERR_OK)
                return ret_val;
            break;
        case FLOOD_UNKNOWNMC:
            if ((ret_val = rtl8367b_getAsicPortUnknownMulticastFloodingPortmask(&pFlood_portmask->bits[0])) != RT_ERR_OK)
                return ret_val;
            break;
        case FLOOD_BC:
            if ((ret_val = rtl8367b_getAsicPortBcastFloodingPortmask(&pFlood_portmask->bits[0])) != RT_ERR_OK)
                return ret_val;
            break;
        default:
            break;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_l2_localPktPermit_set
 * Description:
 *      Set permittion of frames if source port and destination port are the same.
 * Input:
 *      port - Port id.
 *      permit - permittion status
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 *      RT_ERR_ENABLE       - Invalid permit value.
 * Note:
 *      This API is setted to permit frame if its source port is equal to destination port.
 */
int rtk_l2_localPktPermit_set(unsigned int port, rtk_enable_t permit)
{
    int ret_val;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if (permit >= RTK_ENABLE_END)
        return RT_ERR_ENABLE;

    if ((ret_val = rtl8367b_setAsicPortBlockSpa(port, permit)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_l2_localPktPermit_get
 * Description:
 *      Get permittion of frames if source port and destination port are the same.
 * Input:
 *      port - Port id.
 * Output:
 *      pPermit - permittion status
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *      This API is to get permittion status for frames if its source port is equal to destination port.
 */
int rtk_l2_localPktPermit_get(unsigned int port, rtk_enable_t *pPermit)
{
    int ret_val;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if ((ret_val = rtl8367b_getAsicPortBlockSpa(port, pPermit)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_l2_aging_set
 * Description:
 *      Set LUT agging out speed
 * Input:
 *      aging_time - Agging out time.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_OUT_OF_RANGE     - input out of range.
 * Note:
 *      The API can set LUT agging out period for each entry and the range is from 45s to 458s.
 */
int rtk_l2_aging_set(unsigned int aging_time)
{
    unsigned int i;
    const unsigned int agePara[10][3] = {
        {45, 0, 1}, {88, 0, 2}, {133, 0, 3}, {177, 0, 4}, {221, 0, 5}, {266, 0, 6}, {310, 0, 7},
        {354, 2, 6}, {413, 2, 7}, {458, 3, 7}};

    if (aging_time>agePara[9][0])
        return RT_ERR_OUT_OF_RANGE;

    for (i = 0; i<10; i++)
    {
        if (aging_time<=agePara[i][0])
        {
            return rtl8367b_setAsicLutAgeTimerSpeed(agePara[i][2], agePara[i][1]);
        }
    }

    return RT_ERR_FAILED;
}

/* Function Name:
 *      rtk_l2_aging_get
 * Description:
 *      Get LUT agging out time
 * Input:
 *      None
 * Output:
 *      pEnable - Aging status
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *      The API can get LUT agging out period for each entry.
 */
int rtk_l2_aging_get(unsigned int *pAging_time)
{
    int ret_val;
    unsigned int i,time, speed;
    const unsigned int agePara[10][3] = {
        {45, 0, 1}, {88, 0, 2}, {133, 0, 3}, {177, 0, 4}, {221, 0, 5}, {266, 0, 6}, {310, 0, 7},
        {354, 2, 6}, {413, 2, 7}, {458, 3, 7}};

    if ((ret_val = rtl8367b_getAsicLutAgeTimerSpeed(&time, &speed)) != RT_ERR_OK)
        return ret_val;

    for (i = 0; i<10; i++)
    {
        if (time==agePara[i][2]&&speed==agePara[i][1])
        {
            *pAging_time = agePara[i][0];
            return RT_ERR_OK;
        }
    }

    return RT_ERR_FAILED;
}

/* Function Name:
 *      rtk_l2_ipMcastAddrLookup_set
 * Description:
 *      Set Lut IP multicast lookup function
 * Input:
 *      type - Lookup type for IPMC packet.
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK          - OK
 *      RT_ERR_FAILED      - Failed
 *      RT_ERR_SMI         - SMI access error
 * Note:
 *      This API can work with rtk_l2_ipMcastAddrLookupException_add.
 *      If users set the lookup type to DIP, the group in exception table
 *      will be lookup by DIP+SIP
 *      If users set the lookup type to DIP+SIP, the group in exception table
 *      will be lookup by only DIP
 */
int rtk_l2_ipMcastAddrLookup_set(rtk_l2_lookup_type_t type)
{
    int ret_val;

    if(type == LOOKUP_MAC)
    {
        if((ret_val = rtl8367b_setAsicLutIpMulticastLookup(DISABLE)) != RT_ERR_OK)
            return ret_val;
    }
    else if(type == LOOKUP_SIP_DIP)
    {
        if((ret_val = rtl8367b_setAsicLutIpMulticastLookup(ENABLE)) != RT_ERR_OK)
            return ret_val;

        if ((ret_val = rtl8367b_setAsicLutIpLookupMethod(0))!=RT_ERR_OK)
            return ret_val;
    }
    else if(type == LOOKUP_DIP)
    {
        if((ret_val = rtl8367b_setAsicLutIpMulticastLookup(ENABLE)) != RT_ERR_OK)
            return ret_val;

        if ((ret_val = rtl8367b_setAsicLutIpLookupMethod(1))!=RT_ERR_OK)
            return ret_val;
    }
    else
        return RT_ERR_FAILED;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_l2_ipMcastAddrLookup_get
 * Description:
 *      Get Lut IP multicast lookup function
 * Input:
 *      None.
 * Output:
 *      pType - Lookup type for IPMC packet.
 * Return:
 *      RT_ERR_OK          - OK
 *      RT_ERR_FAILED      - Failed
 *      RT_ERR_SMI         - SMI access error
 * Note:
 *      None.
 */
int rtk_l2_ipMcastAddrLookup_get(rtk_l2_lookup_type_t *pType)
{
    int       ret_val;
    unsigned int          enabled, dip_lookup;

    if((ret_val = rtl8367b_getAsicLutIpMulticastLookup(&enabled)) != RT_ERR_OK)
        return ret_val;

    if ((ret_val = rtl8367b_getAsicLutIpLookupMethod(&dip_lookup))!=RT_ERR_OK)
        return ret_val;

    if(enabled == ENABLE)
    {
        if(dip_lookup == ENABLE)
            *pType = LOOKUP_DIP;
        else
            *pType = LOOKUP_SIP_DIP;
    }
    else
        *pType = LOOKUP_MAC;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_l2_ipMcastAddrLookupException_add
 * Description:
 *      Add an IP Multicast Exception group
 * Input:
 *      ip_addr     - IP address
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK          - OK
 *      RT_ERR_FAILED      - Failed
 *      RT_ERR_SMI         - SMI access error
 *      RT_ERR_TBL_FULL    - Table Full
 * Note:
 *      Add an entry to IP Multicast exception table.
 */
int rtk_l2_ipMcastAddrLookupException_add(unsigned int ip_addr)
{
    unsigned int      empty_idx = 0xFFFF;
    int       index;
    unsigned int        group_addr;
    int   ret_val;

    if( (ip_addr & 0xF0000000) != 0xE0000000)    /* not in 224.0.0.0 ~ 239.255.255.255 */
        return RT_ERR_INPUT;

    for(index = RTL8367B_LUT_IPMCGRP_TABLE_MAX; index >= 0; index--)
    {
        if ((ret_val = rtl8367b_getAsicLutIPMCGroup((unsigned int)index, &group_addr))!=RT_ERR_OK)
            return ret_val;

        if(group_addr == ip_addr)
            return RT_ERR_OK;

        if(group_addr == 0xE0000000) /* Unused */
            empty_idx = (unsigned int)index;
    }

    if(empty_idx == 0xFFFF)
        return RT_ERR_TBL_FULL;

    if ((ret_val = rtl8367b_setAsicLutIPMCGroup(empty_idx, ip_addr))!=RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_l2_ipMcastAddrLookupException_del
 * Description:
 *      Delete an IP Multicast Exception group
 * Input:
 *      ip_addr     - IP address
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK          - OK
 *      RT_ERR_FAILED      - Failed
 *      RT_ERR_SMI         - SMI access error
 *      RT_ERR_TBL_FULL    - Table Full
 * Note:
 *      Delete an entry to IP Multicast exception table.
 */
int rtk_l2_ipMcastAddrLookupException_del(unsigned int ip_addr)
{
    unsigned int      index;
    unsigned int        group_addr;
    int   ret_val;

    if( (ip_addr & 0xF0000000) != 0xE0000000)    /* not in 224.0.0.0 ~ 239.255.255.255 */
        return RT_ERR_INPUT;

    for(index = 0; index <= RTL8367B_LUT_IPMCGRP_TABLE_MAX; index++)
    {
        if ((ret_val = rtl8367b_getAsicLutIPMCGroup(index, &group_addr))!=RT_ERR_OK)
            return ret_val;

        if(group_addr == ip_addr)
        {
            if ((ret_val = rtl8367b_setAsicLutIPMCGroup(index, 0xE0000000))!=RT_ERR_OK)
                return ret_val;

            return RT_ERR_OK;
        }
    }

    return RT_ERR_FAILED;
}

/* Function Name:
 *      rtk_l2_entry_get
 * Description:
 *      Get LUT unicast entry.
 * Input:
 *      pL2_entry - Index field in the structure.
 * Output:
 *      pL2_entry - other fields such as MAC, port, age...
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_L2_EMPTY_ENTRY   - Empty LUT entry.
 *      RT_ERR_INPUT            - Invalid input parameters.
 * Note:
 *      This API is used to get address by index from 1~2112.
 */
int rtk_l2_entry_get(rtk_l2_addr_table_t *pL2_entry)
{
    int ret_val;
    unsigned int method;
    rtl8367b_luttb l2Table;

    if ((pL2_entry->index>RTK_MAX_NUM_OF_LEARN_LIMIT)||(pL2_entry->index<1))
        return RT_ERR_INPUT;

    l2Table.address= pL2_entry->index-1;
    method = LUTREADMETHOD_ADDRESS;
    if ((ret_val = rtl8367b_getAsicL2LookupTb(method, &l2Table)) != RT_ERR_OK)
        return ret_val;

    if ((pL2_entry->index>0x800)&&(l2Table.lookup_hit==0))
         return RT_ERR_L2_EMPTY_ENTRY;

    if(l2Table.l3lookup)
    {
        memset(&pL2_entry->mac, 0, sizeof(rtk_mac_t));
        pL2_entry->is_ipmul  = l2Table.l3lookup;
        pL2_entry->sip       = l2Table.sip;
        pL2_entry->dip       = l2Table.dip;
        pL2_entry->is_static = l2Table.nosalearn;
        pL2_entry->portmask  = l2Table.mbr;
        pL2_entry->fid       = 0;
        pL2_entry->age       = 0;
        pL2_entry->auth      = 0;
        pL2_entry->sa_block  = 0;
    }
    else if(l2Table.mac.octet[0]&0x01)
    {
        memset(&pL2_entry->sip, 0, sizeof(unsigned int));
        memset(&pL2_entry->dip, 0, sizeof(unsigned int));
        pL2_entry->mac.octet[0] = l2Table.mac.octet[0];
        pL2_entry->mac.octet[1] = l2Table.mac.octet[1];
        pL2_entry->mac.octet[2] = l2Table.mac.octet[2];
        pL2_entry->mac.octet[3] = l2Table.mac.octet[3];
        pL2_entry->mac.octet[4] = l2Table.mac.octet[4];
        pL2_entry->mac.octet[5] = l2Table.mac.octet[5];
        pL2_entry->is_ipmul  = l2Table.l3lookup;
        pL2_entry->is_static = l2Table.nosalearn;
        pL2_entry->portmask  = l2Table.mbr;
        pL2_entry->ivl       = l2Table.ivl_svl;
        if(l2Table.ivl_svl == 1) /* IVL */
        {
            pL2_entry->cvid      = l2Table.cvid_fid;
            pL2_entry->fid       = 0;
        }
        else /* SVL*/
        {
            pL2_entry->cvid      = 0;
            pL2_entry->fid       = l2Table.cvid_fid;
        }
        pL2_entry->auth      = l2Table.auth;
        pL2_entry->sa_block  = l2Table.sa_block;
        pL2_entry->age       = 0;
    }
    else if((l2Table.age != 0)||(l2Table.nosalearn == 1))
    {
        memset(&pL2_entry->sip, 0, sizeof(unsigned int));
        memset(&pL2_entry->dip, 0, sizeof(unsigned int));
        pL2_entry->mac.octet[0] = l2Table.mac.octet[0];
        pL2_entry->mac.octet[1] = l2Table.mac.octet[1];
        pL2_entry->mac.octet[2] = l2Table.mac.octet[2];
        pL2_entry->mac.octet[3] = l2Table.mac.octet[3];
        pL2_entry->mac.octet[4] = l2Table.mac.octet[4];
        pL2_entry->mac.octet[5] = l2Table.mac.octet[5];
        pL2_entry->is_ipmul  = l2Table.l3lookup;
        pL2_entry->is_static = l2Table.nosalearn;
        pL2_entry->portmask  = 1<<(l2Table.spa);
        pL2_entry->ivl       = l2Table.ivl_svl;
        pL2_entry->cvid      = l2Table.cvid_fid;
        pL2_entry->fid       = l2Table.fid;
        pL2_entry->auth      = l2Table.auth;
        pL2_entry->sa_block  = l2Table.sa_block;
        pL2_entry->age       = l2Table.age;
    }
    else
       return RT_ERR_L2_EMPTY_ENTRY;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_svlan_init
 * Description:
 *      Initialize SVLAN Configuration
 * Input:
 *      None
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 * Note:
 *      Ether type of S-tag in 802.1ad is 0x88a8 and there are existed ether type 0x9100 and 0x9200 for Q-in-Q SLAN design.
 *      User can set mathced ether type as service provider supported protocol.
 */
int rtk_svlan_init(void)
{
    unsigned int i;
    int ret_val;
    rtl8367b_svlan_memconf_t svlanMemConf;
    rtl8367b_svlan_s2c_t svlanSP2CConf;
    rtl8367b_svlan_mc2s_t svlanMC2SConf;

    /*default use C-priority*/
    if ((ret_val = rtl8367b_setAsicSvlanPrioritySel(SPRISEL_CTAGPRI)) != RT_ERR_OK)
        return ret_val;

    /*Drop SVLAN untag frame*/
    if ((ret_val = rtl8367b_setAsicSvlanIngressUntag(DISABLED)) != RT_ERR_OK)
        return ret_val;

    /*Drop SVLAN unmatch frame*/
    if ((ret_val = rtl8367b_setAsicSvlanIngressUnmatch(DISABLED)) != RT_ERR_OK)
        return ret_val;

    /*Set TPID to 0x88a8*/
    if ((ret_val = rtl8367b_setAsicSvlanTpid(0x88a8)) != RT_ERR_OK)
        return ret_val;

    /*Clean Uplink Port Mask to none*/
    if ((ret_val = rtl8367b_setAsicSvlanUplinkPortMask(0)) != RT_ERR_OK)
        return ret_val;

    /*Clean SVLAN Member Configuration*/
    for (i=0; i<= RTL8367B_SVIDXMAX; i++)
    {
        memset(&svlanMemConf, 0, sizeof(rtl8367b_svlan_memconf_t));
        if ((ret_val = rtl8367b_setAsicSvlanMemberConfiguration(i, &svlanMemConf)) != RT_ERR_OK)
            return ret_val;
    }

    /*Clean C2S Configuration*/
    for (i=0; i<= RTL8367B_C2SIDXMAX; i++)
    {
        if ((ret_val = rtl8367b_setAsicSvlanC2SConf(i, 0,0,0)) != RT_ERR_OK)
            return ret_val;
    }

    /*Clean SP2C Configuration*/
    for (i=0; i <= RTL8367B_SP2CMAX ; i++)
    {
        memset(&svlanSP2CConf, 0, sizeof(rtl8367b_svlan_s2c_t));
        if ((ret_val = rtl8367b_setAsicSvlanSP2CConf(i, &svlanSP2CConf)) != RT_ERR_OK)
            return ret_val;
    }

    /*Clean MC2S Configuration*/
    for (i=0 ; i<= RTL8367B_MC2SIDXMAX; i++)
    {
        memset(&svlanMC2SConf, 0, sizeof(rtl8367b_svlan_mc2s_t));
        if ((ret_val = rtl8367b_setAsicSvlanMC2SConf(i, &svlanMC2SConf)) != RT_ERR_OK)
            return ret_val;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_svlan_servicePort_add
 * Description:
 *      Add one service port in the specified device
 * Input:
 *      port - Port id.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      This API is setting which port is connected to provider switch. All frames receiving from this port must
 *      contain accept SVID in S-tag field.
 */
int rtk_svlan_servicePort_add(unsigned int port)
{
    int ret_val;
    unsigned int pmsk;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if ((ret_val = rtl8367b_getAsicSvlanUplinkPortMask(&pmsk)) != RT_ERR_OK)
        return ret_val;

    pmsk = pmsk | (1<<port);

    if ((ret_val = rtl8367b_setAsicSvlanUplinkPortMask(pmsk)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_svlan_servicePort_get
 * Description:
 *      Get service ports in the specified device.
 * Input:
 *      None
 * Output:
 *      pSvlan_portmask - pointer buffer of svlan ports.
 * Return:
 *      RT_ERR_OK          - OK
 *      RT_ERR_FAILED      - Failed
 *      RT_ERR_SMI         - SMI access error
 * Note:
 *      This API is setting which port is connected to provider switch. All frames receiving from this port must
 *      contain accept SVID in S-tag field.
 */
int rtk_svlan_servicePort_get(rtk_portmask_t *pSvlan_portmask)
{
    int ret_val;

    if ((ret_val = rtl8367b_getAsicSvlanUplinkPortMask(&pSvlan_portmask->bits[0])) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_svlan_servicePort_del
 * Description:
 *      Delete one service port in the specified device
 * Input:
 *      port - Port id.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *      This API is removing SVLAN service port in the specified device.
 */
int rtk_svlan_servicePort_del(unsigned int port)
{
    int ret_val;
    unsigned int pmsk;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if ((ret_val = rtl8367b_getAsicSvlanUplinkPortMask(&pmsk)) != RT_ERR_OK)
        return ret_val;

    pmsk = pmsk & ~(1<<port);

    if ((ret_val = rtl8367b_setAsicSvlanUplinkPortMask(pmsk)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_svlan_tpidEntry_set
 * Description:
 *      Configure accepted S-VLAN ether type.
 * Input:
 *      svlan_tag_id - Ether type of S-tag frame parsing in uplink ports.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameter.
 * Note:
 *      Ether type of S-tag in 802.1ad is 0x88a8 and there are existed ether type 0x9100 and 0x9200 for Q-in-Q SLAN design.
 *      User can set mathced ether type as service provider supported protocol.
 */
int rtk_svlan_tpidEntry_set(rtk_svlan_tpid_t svlan_tag_id)
{
    int ret_val;

    if (svlan_tag_id>RTK_MAX_NUM_OF_PROTO_TYPE)
        return RT_ERR_INPUT;

    if ((ret_val = rtl8367b_setAsicSvlanTpid(svlan_tag_id)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_svlan_tpidEntry_get
 * Description:
 *      Get accepted S-VLAN ether type setting.
 * Input:
 *      None
 * Output:
 *      pSvlan_tag_id -  Ether type of S-tag frame parsing in uplink ports.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 * Note:
 *      This API is setting which port is connected to provider switch. All frames receiving from this port must
 *      contain accept SVID in S-tag field.
 */
int rtk_svlan_tpidEntry_get(rtk_svlan_tpid_t *pSvlan_tag_id)
{
    int ret_val;

    if ((ret_val = rtl8367b_getAsicSvlanTpid(pSvlan_tag_id)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_svlan_priorityRef_set
 * Description:
 *      Set S-VLAN upstream priority reference setting.
 * Input:
 *      ref - reference selection parameter.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameter.
 * Note:
 *      The API can set the upstream SVLAN tag priority reference source. The related priority
 *      sources are as following:
 *      - REF_INTERNAL_PRI,
 *      - REF_CTAG_PRI,
 *      - REF_SVLAN_PRI.
 */
int rtk_svlan_priorityRef_set(rtk_svlan_pri_ref_t ref)
{
    int ret_val;

    if (ref>REF_PRI_END)
        return RT_ERR_INPUT;

    if ((ret_val = rtl8367b_setAsicSvlanPrioritySel(ref)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_svlan_priorityRef_get
 * Description:
 *      Get S-VLAN upstream priority reference setting.
 * Input:
 *      None
 * Output:
 *      pRef - reference selection parameter.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 * Note:
 *      The API can get the upstream SVLAN tag priority reference source. The related priority
 *      sources are as following:
 *      - REF_INTERNAL_PRI,
 *      - REF_CTAG_PRI,
 *      - REF_SVLAN_PRI.
 */
int rtk_svlan_priorityRef_get(rtk_svlan_pri_ref_t *pRef)
{
    int ret_val;

    if ((ret_val = rtl8367b_getAsicSvlanPrioritySel(pRef)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_svlan_memberPortEntry_set
 * Description:
 *      Configure system SVLAN member content
 * Input:
 *      svid - SVLAN id
 *      psvlan_cfg - SVLAN member configuration
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_INPUT            - Invalid input parameter.
 *      RT_ERR_SVLAN_VID        - Invalid SVLAN VID parameter.
 *      RT_ERR_PORT_MASK        - Invalid portmask.
 *      RT_ERR_SVLAN_TABLE_FULL - SVLAN configuration is full.
 * Note:
 *      The API can set system 64 accepted s-tag frame format. Only 64 SVID S-tag frame will be accpeted
 *      to receiving from uplink ports. Other SVID S-tag frame or S-untagged frame will be droped by default setup.
 *      - rtk_svlan_memberCfg_t->svid is SVID of SVLAN member configuration.
 *      - rtk_svlan_memberCfg_t->memberport is member port mask of SVLAN member configuration.
 *      - rtk_svlan_memberCfg_t->fid is filtering database of SVLAN member configuration.
 *      - rtk_svlan_memberCfg_t->priority is priority of SVLAN member configuration.
 */
int rtk_svlan_memberPortEntry_set(rtk_vlan_t svid, rtk_svlan_memberCfg_t *pSvlan_cfg)
{
    int ret_val;
    int i;
    unsigned int empty_idx;
    rtl8367b_svlan_memconf_t svlanMemConf;

    if ((svid > RTL8367B_VIDMAX) || (svid != pSvlan_cfg->svid))
        return RT_ERR_SVLAN_VID;

    if (pSvlan_cfg->svid>RTL8367B_VIDMAX)
        return RT_ERR_SVLAN_VID;

    if (pSvlan_cfg->memberport > RTK_MAX_PORT_MASK)
        return RT_ERR_PORT_MASK;

    if (pSvlan_cfg->untagport > RTK_MAX_PORT_MASK)
        return RT_ERR_PORT_MASK;

    if (pSvlan_cfg->fiden > ENABLED)
        return RT_ERR_ENABLE;

    if (pSvlan_cfg->fid > RTL8367B_FIDMAX)
        return RT_ERR_L2_FID;

    if (pSvlan_cfg->priority > RTL8367B_PRIMAX)
        return RT_ERR_VLAN_PRIORITY;

    if (pSvlan_cfg->efiden > ENABLED)
        return RT_ERR_ENABLE;

    if (pSvlan_cfg->efid > RTL8367B_FIDMAX)
        return RT_ERR_L2_FID;

    empty_idx = 0xFF;

    for (i = 0; i<= RTL8367B_SVIDXMAX; i++)
    {
        if ((ret_val = rtl8367b_getAsicSvlanMemberConfiguration(i, &svlanMemConf)) != RT_ERR_OK)
            return ret_val;

        if (svid == svlanMemConf.vs_svid)
        {
            if(pSvlan_cfg->memberport == 0x00)
                svlanMemConf.vs_svid    = 0;
            else
                svlanMemConf.vs_svid    = pSvlan_cfg->svid;

            svlanMemConf.vs_member      = pSvlan_cfg->memberport;
            svlanMemConf.vs_untag       = pSvlan_cfg->untagport;
            svlanMemConf.vs_force_fid   = pSvlan_cfg->fiden;
            svlanMemConf.vs_fid_msti    = pSvlan_cfg->fid;
            svlanMemConf.vs_priority    = pSvlan_cfg->priority;
            svlanMemConf.vs_efiden      = pSvlan_cfg->efiden;
            svlanMemConf.vs_efid        = pSvlan_cfg->efid;

            if ((ret_val = rtl8367b_setAsicSvlanMemberConfiguration(i, &svlanMemConf)) != RT_ERR_OK)
                return ret_val;

            return RT_ERR_OK;
        }
        else if (svlanMemConf.vs_svid==0 && svlanMemConf.vs_member==0)
        {
            if(i < empty_idx)
                empty_idx = i;
        }
    }

    if (empty_idx != 0xFF)
    {
        memset(&svlanMemConf, 0, sizeof(rtl8367b_svlan_memconf_t));
        svlanMemConf.vs_svid        = pSvlan_cfg->svid;
        svlanMemConf.vs_member      = pSvlan_cfg->memberport;
        svlanMemConf.vs_untag       = pSvlan_cfg->untagport;
        svlanMemConf.vs_force_fid   = pSvlan_cfg->fiden;
        svlanMemConf.vs_fid_msti    = pSvlan_cfg->fid;
        svlanMemConf.vs_priority    = pSvlan_cfg->priority;
        svlanMemConf.vs_efiden      = pSvlan_cfg->efiden;
        svlanMemConf.vs_efid        = pSvlan_cfg->efid;

        if ((ret_val = rtl8367b_setAsicSvlanMemberConfiguration(empty_idx, &svlanMemConf)) != RT_ERR_OK)
        {
            return ret_val;
        }

        return RT_ERR_OK;
    }

    return RT_ERR_SVLAN_TABLE_FULL;
}

/* Function Name:
 *      rtk_svlan_memberPortEntry_get
 * Description:
 *      Get SVLAN member Configure.
 * Input:
 *      svid - SVLAN id
 * Output:
 *      pSvlan_cfg - SVLAN member configuration
 * Return:
 *      RT_ERR_OK                       - OK
 *      RT_ERR_FAILED                   - Failed
 *      RT_ERR_SMI                      - SMI access error
 *      RT_ERR_SVLAN_ENTRY_NOT_FOUND    - specified svlan entry not found.
 *      RT_ERR_INPUT                    - Invalid input parameters.
 * Note:
 *      The API can get system 64 accepted s-tag frame format. Only 64 SVID S-tag frame will be accpeted
 *      to receiving from uplink ports. Other SVID S-tag frame or S-untagged frame will be droped.
 */
int rtk_svlan_memberPortEntry_get(rtk_vlan_t svid, rtk_svlan_memberCfg_t *pSvlan_cfg)
{
    int ret_val;
    unsigned int i;
    rtl8367b_svlan_memconf_t svlanMemConf;

    if (svid > RTL8367B_VIDMAX)
        return RT_ERR_SVLAN_VID;


    for (i = 0; i<= RTL8367B_SVIDXMAX; i++)
    {
        if ((ret_val = rtl8367b_getAsicSvlanMemberConfiguration(i, &svlanMemConf)) != RT_ERR_OK)
            return ret_val;
        if (svid == svlanMemConf.vs_svid)
        {
            pSvlan_cfg->svid        = svlanMemConf.vs_svid;
            pSvlan_cfg->memberport  = svlanMemConf.vs_member;
            pSvlan_cfg->untagport   = svlanMemConf.vs_untag;
            pSvlan_cfg->fiden       = svlanMemConf.vs_force_fid;
            pSvlan_cfg->fid         = svlanMemConf.vs_fid_msti;
            pSvlan_cfg->priority    = svlanMemConf.vs_priority;
            pSvlan_cfg->efiden      = svlanMemConf.vs_efiden;
            pSvlan_cfg->efid        = svlanMemConf.vs_efid;

            return RT_ERR_OK;
        }
    }

    return RT_ERR_SVLAN_ENTRY_NOT_FOUND;

}

/* Function Name:
 *      rtk_svlan_memberPortEntry_adv_set
 * Description:
 *      Configure system SVLAN member by index
 * Input:
 *      idx         - Index (0 ~ 63)
 *      psvlan_cfg  - SVLAN member configuration
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_INPUT            - Invalid input parameter.
 *      RT_ERR_SVLAN_VID        - Invalid SVLAN VID parameter.
 *      RT_ERR_PORT_MASK        - Invalid portmask.
 *      RT_ERR_SVLAN_TABLE_FULL - SVLAN configuration is full.
 * Note:
 *      The API can set system 64 accepted s-tag frame format by index.
 *      - rtk_svlan_memberCfg_t->svid is SVID of SVLAN member configuration.
 *      - rtk_svlan_memberCfg_t->memberport is member port mask of SVLAN member configuration.
 *      - rtk_svlan_memberCfg_t->fid is filtering database of SVLAN member configuration.
 *      - rtk_svlan_memberCfg_t->priority is priority of SVLAN member configuration.
 */
int rtk_svlan_memberPortEntry_adv_set(unsigned int idx, rtk_svlan_memberCfg_t *pSvlan_cfg)
{
    int ret_val;
    rtl8367b_svlan_memconf_t svlanMemConf;

    if (idx > RTL8367B_SVIDXMAX)
        return RT_ERR_SVLAN_ENTRY_INDEX;

    if (pSvlan_cfg->svid>RTL8367B_VIDMAX)
        return RT_ERR_SVLAN_VID;

    if (pSvlan_cfg->memberport > RTK_MAX_PORT_MASK)
        return RT_ERR_PORT_MASK;

    if (pSvlan_cfg->untagport > RTK_MAX_PORT_MASK)
        return RT_ERR_PORT_MASK;

    if (pSvlan_cfg->fiden > ENABLED)
        return RT_ERR_ENABLE;

    if (pSvlan_cfg->fid > RTL8367B_FIDMAX)
        return RT_ERR_L2_FID;

    if (pSvlan_cfg->priority > RTL8367B_PRIMAX)
        return RT_ERR_VLAN_PRIORITY;

    if (pSvlan_cfg->efiden > ENABLED)
        return RT_ERR_ENABLE;

    if (pSvlan_cfg->efid > RTL8367B_FIDMAX)
        return RT_ERR_L2_FID;

    memset(&svlanMemConf, 0, sizeof(rtl8367b_svlan_memconf_t));
    svlanMemConf.vs_svid        = pSvlan_cfg->svid;
    svlanMemConf.vs_member      = pSvlan_cfg->memberport;
    svlanMemConf.vs_untag       = pSvlan_cfg->untagport;
    svlanMemConf.vs_force_fid   = pSvlan_cfg->fiden;
    svlanMemConf.vs_fid_msti    = pSvlan_cfg->fid;
    svlanMemConf.vs_priority    = pSvlan_cfg->priority;
    svlanMemConf.vs_efiden      = pSvlan_cfg->efiden;
    svlanMemConf.vs_efid        = pSvlan_cfg->efid;

    if ((ret_val = rtl8367b_setAsicSvlanMemberConfiguration(idx, &svlanMemConf)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_svlan_memberPortEntry_adv_get
 * Description:
 *      Get SVLAN member Configure by index.
 * Input:
 *      idx         - Index (0 ~ 63)
 * Output:
 *      pSvlan_cfg  - SVLAN member configuration
 * Return:
 *      RT_ERR_OK                       - OK
 *      RT_ERR_FAILED                   - Failed
 *      RT_ERR_SMI                      - SMI access error
 *      RT_ERR_SVLAN_ENTRY_NOT_FOUND    - specified svlan entry not found.
 *      RT_ERR_INPUT                    - Invalid input parameters.
 * Note:
 *      The API can get system 64 accepted s-tag frame format. Only 64 SVID S-tag frame will be accpeted
 *      to receiving from uplink ports. Other SVID S-tag frame or S-untagged frame will be droped.
 */
int rtk_svlan_memberPortEntry_adv_get(unsigned int idx, rtk_svlan_memberCfg_t *pSvlan_cfg)
{
    int ret_val;
    rtl8367b_svlan_memconf_t svlanMemConf;

    if (idx > RTL8367B_SVIDXMAX)
        return RT_ERR_SVLAN_ENTRY_INDEX;

    if ((ret_val = rtl8367b_getAsicSvlanMemberConfiguration(idx, &svlanMemConf)) != RT_ERR_OK)
        return ret_val;

    pSvlan_cfg->svid        = svlanMemConf.vs_svid;
    pSvlan_cfg->memberport  = svlanMemConf.vs_member;
    pSvlan_cfg->untagport   = svlanMemConf.vs_untag;
    pSvlan_cfg->fiden       = svlanMemConf.vs_force_fid;
    pSvlan_cfg->fid         = svlanMemConf.vs_fid_msti;
    pSvlan_cfg->priority    = svlanMemConf.vs_priority;
    pSvlan_cfg->efiden      = svlanMemConf.vs_efiden;
    pSvlan_cfg->efid        = svlanMemConf.vs_efid;

    return RT_ERR_OK;

}

/* Function Name:
 *      rtk_svlan_defaultSvlan_set
 * Description:
 *      Configure default egress SVLAN.
 * Input:
 *      port - Source port
 *      svid - SVLAN id
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                       - OK
 *      RT_ERR_FAILED                   - Failed
 *      RT_ERR_SMI                      - SMI access error
 *      RT_ERR_INPUT                    - Invalid input parameter.
 *      RT_ERR_SVLAN_VID                - Invalid SVLAN VID parameter.
 *      RT_ERR_SVLAN_ENTRY_NOT_FOUND    - specified svlan entry not found.
 * Note:
 *      The API can set port n S-tag format index while receiving frame from port n
 *      is transmit through uplink port with s-tag field
 */
int rtk_svlan_defaultSvlan_set(unsigned int port, rtk_vlan_t svid)
{
    int ret_val;
    unsigned int i;
    rtl8367b_svlan_memconf_t svlanMemConf;

    /* Port ID 0 ~ 7 */
    if(port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    /* svid must be 0~4095 */
    if (svid > RTL8367B_VIDMAX)
        return RT_ERR_SVLAN_VID;

    for (i = 0; i < RTL8367B_SVIDXNO; i++)
    {
        if ((ret_val = rtl8367b_getAsicSvlanMemberConfiguration(i, &svlanMemConf)) != RT_ERR_OK)
            return ret_val;

        if (svid == svlanMemConf.vs_svid)
        {
            if ((ret_val = rtl8367b_setAsicSvlanDefaultVlan(port, i)) != RT_ERR_OK)
                return ret_val;

            return RT_ERR_OK;
        }
    }

    return RT_ERR_SVLAN_ENTRY_NOT_FOUND;
}

/* Function Name:
 *      rtk_svlan_defaultSvlan_get
 * Description:
 *      Get the configure default egress SVLAN.
 * Input:
 *      port - Source port
 * Output:
 *      pSvid - SVLAN VID
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      The API can get port n S-tag format index while receiving frame from port n
 *      is transmit through uplink port with s-tag field
 */
int rtk_svlan_defaultSvlan_get(unsigned int port, rtk_vlan_t *pSvid)
{
    int ret_val;
    unsigned int idx;
    rtl8367b_svlan_memconf_t svlanMemConf;

    /* Port ID 0 ~ 7 */
    if(port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if ((ret_val = rtl8367b_getAsicSvlanDefaultVlan(port, &idx)) != RT_ERR_OK)
        return ret_val;

    if ((ret_val = rtl8367b_getAsicSvlanMemberConfiguration(idx, &svlanMemConf)) != RT_ERR_OK)
        return ret_val;

    *pSvid = svlanMemConf.vs_svid;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_svlan_c2s_add
 * Description:
 *      Configure SVLAN C2S table
 * Input:
 *      vid - VLAN ID
 *      src_port - Ingress Port
 *      svid - SVLAN VID
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port ID.
 *      RT_ERR_SVLAN_VID    - Invalid SVLAN VID parameter.
 *      RT_ERR_VLAN_VID     - Invalid VID parameter.
 *      RT_ERR_OUT_OF_RANGE - input out of range.
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      The API can set system C2S configuration. ASIC will check upstream's VID and assign related
 *      SVID to mathed packet. There are 128 SVLAN C2S configurations.
 */
int rtk_svlan_c2s_add(rtk_vlan_t vid, unsigned int src_port, rtk_vlan_t svid)
{
    int ret_val, i;
    unsigned int empty_idx;
    unsigned int evid, pmsk, svidx, c2s_svidx;
    rtl8367b_svlan_memconf_t svlanMemConf;

    if (vid > RTL8367B_VIDMAX)
        return RT_ERR_VLAN_VID;

    if (svid > RTL8367B_VIDMAX)
        return RT_ERR_SVLAN_VID;

    if(src_port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    empty_idx = 0xFFFF;
    svidx = 0xFFFF;

    for (i = 0; i<= RTL8367B_SVIDXMAX; i++)
    {
        if ((ret_val = rtl8367b_getAsicSvlanMemberConfiguration(i, &svlanMemConf)) != RT_ERR_OK)
            return ret_val;

        if (svid == svlanMemConf.vs_svid)
        {
            svidx = i;
            break;
        }
    }

    if (0xFFFF == svidx)
        return RT_ERR_SVLAN_VID;

    for (i=RTL8367B_C2SIDXMAX; i>=0; i--)
    {
        if ((ret_val = rtl8367b_getAsicSvlanC2SConf(i, &evid, &pmsk, &c2s_svidx)) != RT_ERR_OK)
                return ret_val;

        if (evid == vid)
        {
            /* Check Src_port */
            if(pmsk & (1 << src_port))
            {
                /* Check SVIDX */
                if(c2s_svidx == svidx)
                {
                    /* All the same, do nothing */

                }
                else
                {
                    /* New svidx, remove src_port and find a new slot to add a new enrty */
                    pmsk = pmsk & ~(1 << src_port);
                    if ((ret_val = rtl8367b_setAsicSvlanC2SConf(i, vid, pmsk, svidx)) != RT_ERR_OK)
                        return ret_val;
                }
            }
            else
            {
                if(c2s_svidx == svidx)
                {
                    pmsk = pmsk | (1 << src_port);
                    if ((ret_val = rtl8367b_setAsicSvlanC2SConf(i, vid, pmsk, svidx)) != RT_ERR_OK)
                        return ret_val;

                    return RT_ERR_OK;
                }
            }
        }
        else if (evid==0&&pmsk==0&&c2s_svidx==0)
        {
            empty_idx = i;
        }
    }

    if (0xFFFF != empty_idx)
    {
       if ((ret_val = rtl8367b_setAsicSvlanC2SConf(empty_idx, vid, (1<<src_port), svidx)) != RT_ERR_OK)
           return ret_val;
       return RT_ERR_OK;
    }

    return RT_ERR_OUT_OF_RANGE;
}

/* Function Name:
 *      rtk_svlan_c2s_del
 * Description:
 *      Delete one C2S entry
 * Input:
 *      vid - VLAN ID
 *      src_port - Ingress Port
 *      svid - SVLAN VID
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_VLAN_VID         - Invalid VID parameter.
 *      RT_ERR_PORT_ID          - Invalid port ID.
 *      RT_ERR_OUT_OF_RANGE     - input out of range.
 * Note:
 *      The API can delete system C2S configuration. There are 128 SVLAN C2S configurations.
 */
int rtk_svlan_c2s_del(rtk_vlan_t vid, unsigned int src_port)
{
    int ret_val;
    unsigned int i;
    unsigned int evid, pmsk, svidx;
    if (vid > RTL8367B_VIDMAX)
        return RT_ERR_VLAN_VID;

    if(src_port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    for (i = 0; i <= RTL8367B_C2SIDXMAX; i++)
    {
        if ((ret_val = rtl8367b_getAsicSvlanC2SConf(i, &evid, &pmsk, &svidx)) != RT_ERR_OK)
            return ret_val;

        if (evid == vid)
        {
            if(pmsk & (1 << src_port))
            {
                pmsk = pmsk & ~(1 << src_port);
                if(pmsk == 0)
                {
                    vid = 0;
                    svidx = 0;
                }

                if ((ret_val = rtl8367b_setAsicSvlanC2SConf(i, vid, pmsk, svidx)) != RT_ERR_OK)
                    return ret_val;

                return RT_ERR_OK;
            }
        }
    }

    return RT_ERR_OUT_OF_RANGE;
}

/* Function Name:
 *      rtk_svlan_c2s_get
 * Description:
 *      Get configure SVLAN C2S table
 * Input:
 *      vid - VLAN ID
 *      src_port - Ingress Port
 * Output:
 *      pSvid - SVLAN ID
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 *      RT_ERR_PORT_ID      - Invalid port ID.
 *      RT_ERR_OUT_OF_RANGE - input out of range.
 * Note:
 *     The API can get system C2S configuration. There are 128 SVLAN C2S configurations.
 */
int rtk_svlan_c2s_get(rtk_vlan_t vid, unsigned int src_port, rtk_vlan_t *pSvid)
{
    int ret_val;
    unsigned int i;
    unsigned int evid, pmsk, svidx;
    rtl8367b_svlan_memconf_t svlanMemConf;

    if (vid > RTL8367B_VIDMAX)
        return RT_ERR_VLAN_VID;

    if(src_port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    for (i = 0; i <= RTL8367B_C2SIDXMAX; i++)
    {
        if ((ret_val = rtl8367b_getAsicSvlanC2SConf(i, &evid, &pmsk, &svidx)) != RT_ERR_OK)
            return ret_val;

        if (evid == vid)
        {
            if(pmsk & (1 << src_port))
            {
                if ((ret_val = rtl8367b_getAsicSvlanMemberConfiguration(svidx, &svlanMemConf)) != RT_ERR_OK)
                    return ret_val;

                *pSvid = svlanMemConf.vs_svid;
                return RT_ERR_OK;
            }
        }
    }

    return RT_ERR_OUT_OF_RANGE;
}

/* Function Name:
 *      rtk_svlan_untag_action_set
 * Description:
 *      Configure Action of downstream UnStag packet
 * Input:
 *      action  - Action for UnStag
 *      svid    - The SVID assigned to UnStag packet
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                       - OK
 *      RT_ERR_FAILED                   - Failed
 *      RT_ERR_SMI                      - SMI access error
 *      RT_ERR_SVLAN_VID                - Invalid SVLAN VID parameter.
 *      RT_ERR_SVLAN_ENTRY_NOT_FOUND    - specified svlan entry not found.
 *      RT_ERR_OUT_OF_RANGE             - input out of range.
 *      RT_ERR_INPUT                    - Invalid input parameters.
 * Note:
 *      The API can configure action of downstream Un-Stag packet. A SVID assigned
 *      to the un-stag is also supported by this API. The parameter of svid is
 *      only referenced when the action is set to UNTAG_ASSIGN
 */
int rtk_svlan_untag_action_set(rtk_svlan_untag_action_t action, rtk_vlan_t svid)
{
    int   ret_val;
    unsigned int      i;
    rtl8367b_svlan_memconf_t svlanMemConf;

    if (action >= UNTAG_END)
        return RT_ERR_OUT_OF_RANGE;

    if(action == UNTAG_ASSIGN)
    {
        if (svid > RTL8367B_VIDMAX)
            return RT_ERR_SVLAN_VID;
    }

    if ((ret_val = rtl8367b_setAsicSvlanIngressUntag((unsigned int)action)) != RT_ERR_OK)
        return ret_val;

    if(action == UNTAG_ASSIGN)
    {
        for (i = 0; i < RTL8367B_SVIDXNO; i++)
        {
            if ((ret_val = rtl8367b_getAsicSvlanMemberConfiguration(i, &svlanMemConf)) != RT_ERR_OK)
                return ret_val;

            if (svid == svlanMemConf.vs_svid)
            {
                if ((ret_val = rtl8367b_setAsicSvlanUntagVlan(i)) != RT_ERR_OK)
                    return ret_val;

                return RT_ERR_OK;
            }
        }

        return RT_ERR_SVLAN_ENTRY_NOT_FOUND;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_svlan_untag_action_get
 * Description:
 *      Get Action of downstream UnStag packet
 * Input:
 *      None
 * Output:
 *      pAction  - Action for UnStag
 *      pSvid    - The SVID assigned to UnStag packet
 * Return:
 *      RT_ERR_OK                       - OK
 *      RT_ERR_FAILED                   - Failed
 *      RT_ERR_SMI                      - SMI access error
 *      RT_ERR_SVLAN_VID                - Invalid SVLAN VID parameter.
 *      RT_ERR_SVLAN_ENTRY_NOT_FOUND    - specified svlan entry not found.
 *      RT_ERR_OUT_OF_RANGE             - input out of range.
 *      RT_ERR_INPUT                    - Invalid input parameters.
 * Note:
 *      The API can Get action of downstream Un-Stag packet. A SVID assigned
 *      to the un-stag is also retrieved by this API. The parameter pSvid is
 *      only refernced when the action is UNTAG_ASSIGN
 */
int rtk_svlan_untag_action_get(rtk_svlan_untag_action_t *pAction, rtk_vlan_t *pSvid)
{
    int   ret_val;
    unsigned int      svidx;
    rtl8367b_svlan_memconf_t svlanMemConf;

    if ((ret_val = rtl8367b_getAsicSvlanIngressUntag(pAction)) != RT_ERR_OK)
        return ret_val;

    if(*pAction == UNTAG_ASSIGN)
    {
        if ((ret_val = rtl8367b_getAsicSvlanUntagVlan(&svidx)) != RT_ERR_OK)
            return ret_val;

        if ((ret_val = rtl8367b_getAsicSvlanMemberConfiguration(svidx, &svlanMemConf)) != RT_ERR_OK)
            return ret_val;

        *pSvid = svlanMemConf.vs_svid;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_svlan_unmatch_action_set
 * Description:
 *      Configure Action of downstream Unmatch packet
 * Input:
 *      action  - Action for Unmatch
 *      svid    - The SVID assigned to Unmatch packet
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                       - OK
 *      RT_ERR_FAILED                   - Failed
 *      RT_ERR_SMI                      - SMI access error
 *      RT_ERR_SVLAN_VID                - Invalid SVLAN VID parameter.
 *      RT_ERR_SVLAN_ENTRY_NOT_FOUND    - specified svlan entry not found.
 *      RT_ERR_OUT_OF_RANGE             - input out of range.
 *      RT_ERR_INPUT                    - Invalid input parameters.
 * Note:
 *      The API can configure action of downstream Un-match packet. A SVID assigned
 *      to the un-match is also supported by this API. The parameter of svid is
 *      only refernced when the action is set to UNMATCH_ASSIGN
 */
int rtk_svlan_unmatch_action_set(rtk_svlan_unmatch_action_t action, rtk_vlan_t svid)
{
    int   ret_val;
    unsigned int      i;
    rtl8367b_svlan_memconf_t svlanMemConf;

    if (action >= UNMATCH_END)
        return RT_ERR_OUT_OF_RANGE;

    if (action == UNMATCH_ASSIGN)
    {
        if (svid > RTL8367B_VIDMAX)
            return RT_ERR_SVLAN_VID;
    }

    if ((ret_val = rtl8367b_setAsicSvlanIngressUnmatch((unsigned int)action)) != RT_ERR_OK)
        return ret_val;

    if(action == UNMATCH_ASSIGN)
    {
        for (i = 0; i < RTL8367B_SVIDXNO; i++)
        {
            if ((ret_val = rtl8367b_getAsicSvlanMemberConfiguration(i, &svlanMemConf)) != RT_ERR_OK)
                return ret_val;

            if (svid == svlanMemConf.vs_svid)
            {
                if ((ret_val = rtl8367b_setAsicSvlanUnmatchVlan(i)) != RT_ERR_OK)
                    return ret_val;

                return RT_ERR_OK;
            }
        }

        return RT_ERR_SVLAN_ENTRY_NOT_FOUND;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_svlan_unmatch_action_get
 * Description:
 *      Get Action of downstream Unmatch packet
 * Input:
 *      None
 * Output:
 *      pAction  - Action for Unmatch
 *      pSvid    - The SVID assigned to Unmatch packet
 * Return:
 *      RT_ERR_OK                       - OK
 *      RT_ERR_FAILED                   - Failed
 *      RT_ERR_SMI                      - SMI access error
 *      RT_ERR_SVLAN_VID                - Invalid SVLAN VID parameter.
 *      RT_ERR_SVLAN_ENTRY_NOT_FOUND    - specified svlan entry not found.
 *      RT_ERR_OUT_OF_RANGE             - input out of range.
 *      RT_ERR_INPUT                    - Invalid input parameters.
 * Note:
 *      The API can Get action of downstream Un-match packet. A SVID assigned
 *      to the un-match is also retrieved by this API. The parameter pSvid is
 *      only refernced when the action is UNMATCH_ASSIGN
 */
int rtk_svlan_unmatch_action_get(rtk_svlan_unmatch_action_t *pAction, rtk_vlan_t *pSvid)
{
    int   ret_val;
    unsigned int      svidx;
    rtl8367b_svlan_memconf_t svlanMemConf;

    if ((ret_val = rtl8367b_getAsicSvlanIngressUnmatch(pAction)) != RT_ERR_OK)
        return ret_val;

    if(*pAction == UNMATCH_ASSIGN)
    {
        if ((ret_val = rtl8367b_getAsicSvlanUnmatchVlan(&svidx)) != RT_ERR_OK)
            return ret_val;

        if ((ret_val = rtl8367b_getAsicSvlanMemberConfiguration(svidx, &svlanMemConf)) != RT_ERR_OK)
            return ret_val;

        *pSvid = svlanMemConf.vs_svid;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_svlan_dmac_vidsel_set
 * Description:
 *      Set DMAC CVID selection
 * Input:
 *      port    - Port
 *      enable  - state of DMAC CVID Selection
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK                       - OK
 *      RT_ERR_FAILED                   - Failed
 *      RT_ERR_SMI                      - SMI access error
 *      RT_ERR_SVLAN_VID                - Invalid SVLAN VID parameter.
 *      RT_ERR_SVLAN_ENTRY_NOT_FOUND    - specified svlan entry not found.
 *      RT_ERR_OUT_OF_RANGE             - input out of range.
 *      RT_ERR_INPUT                    - Invalid input parameters.
 * Note:
 *      This API can set DMAC CVID Selection state
 */
int rtk_svlan_dmac_vidsel_set(unsigned int port, rtk_enable_t enable)
{
    int   ret_val;

    if(port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if (enable >= RTK_ENABLE_END)
        return RT_ERR_ENABLE;

    if ((ret_val = rtl8367b_setAsicSvlanDmacCvidSel(port, enable)) != RT_ERR_OK)
            return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_svlan_dmac_vidsel_get
 * Description:
 *      Get DMAC CVID selection
 * Input:
 *      port    - Port
 * Output:
 *      pEnable - state of DMAC CVID Selection
 * Return:
 *      RT_ERR_OK                       - OK
 *      RT_ERR_FAILED                   - Failed
 *      RT_ERR_SMI                      - SMI access error
 *      RT_ERR_SVLAN_VID                - Invalid SVLAN VID parameter.
 *      RT_ERR_SVLAN_ENTRY_NOT_FOUND    - specified svlan entry not found.
 *      RT_ERR_OUT_OF_RANGE             - input out of range.
 *      RT_ERR_INPUT                    - Invalid input parameters.
 * Note:
 *      This API can get DMAC CVID Selection state
 */
int rtk_svlan_dmac_vidsel_get(unsigned int port, rtk_enable_t *pEnable)
{
    int   ret_val;

    if(port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if ((ret_val = rtl8367b_getAsicSvlanDmacCvidSel(port, pEnable)) != RT_ERR_OK)
            return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_svlan_ipmc2s_add
 * Description:
 *      add ip multicast address to SVLAN
 * Input:
 *      svid - SVLAN VID
 *      ipmc - ip multicast address
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                       - OK
 *      RT_ERR_FAILED                   - Failed
 *      RT_ERR_SMI                      - SMI access error
 *      RT_ERR_SVLAN_VID                - Invalid SVLAN VID parameter.
 *      RT_ERR_SVLAN_ENTRY_NOT_FOUND    - specified svlan entry not found.
 *      RT_ERR_OUT_OF_RANGE             - input out of range.
 *      RT_ERR_INPUT                    - Invalid input parameters.
 * Note:
 *      The API can set IP mutlicast to SVID configuration. If upstream packet is IPv4 multicast
 *      packet and DIP is matched MC2S configuration, ASIC will assign egress SVID to the packet.
 *      There are 32 SVLAN multicast configurations for IP and L2 multicast.
 */
int rtk_svlan_ipmc2s_add(unsigned int ipmc, rtk_vlan_t svid)
{
    int ret_val, i;
    unsigned int empty_idx;
    unsigned int svidx;
    rtl8367b_svlan_memconf_t svlanMemConf;
    rtl8367b_svlan_mc2s_t svlanMC2SConf;

    if (svid > RTL8367B_VIDMAX)
        return RT_ERR_SVLAN_VID;

    if ((ipmc&0xF0000000)!=0xE0000000)
        return RT_ERR_INPUT;

    svidx = 0xFFFF;

    for (i = 0; i < RTL8367B_SVIDXNO; i++)
    {
        if ((ret_val = rtl8367b_getAsicSvlanMemberConfiguration(i, &svlanMemConf)) != RT_ERR_OK)
            return ret_val;

        if (svid == svlanMemConf.vs_svid)
        {
            svidx = i;
            break;
        }
    }

    if (0xFFFF == svidx)
            return RT_ERR_SVLAN_ENTRY_NOT_FOUND;


    empty_idx = 0xFFFF;

    for (i = RTL8367B_MC2SIDXMAX; i >= 0; i--)
    {
        if ((ret_val = rtl8367b_getAsicSvlanMC2SConf(i, &svlanMC2SConf)) != RT_ERR_OK)
            return ret_val;

        if (TRUE == svlanMC2SConf.valid)
        {
            if (svlanMC2SConf.format == SVLAN_MC2S_MODE_IP && svlanMC2SConf.sdata==ipmc&&svlanMC2SConf.smask!=0)
            {
                svlanMC2SConf.svidx = svidx;
                if ((ret_val = rtl8367b_setAsicSvlanMC2SConf(i, &svlanMC2SConf)) != RT_ERR_OK)
                    return ret_val;
            }
        }
        else
        {
            empty_idx = i;
        }
    }

    if (empty_idx!=0xFFFF)
    {
        svlanMC2SConf.valid = TRUE;
        svlanMC2SConf.svidx = svidx;
        svlanMC2SConf.format = SVLAN_MC2S_MODE_IP;
        svlanMC2SConf.sdata = ipmc;
        svlanMC2SConf.smask = 0xFFFFFFFF;
        if ((ret_val = rtl8367b_setAsicSvlanMC2SConf(empty_idx, &svlanMC2SConf)) != RT_ERR_OK)
            return ret_val;
        return RT_ERR_OK;
    }

    return RT_ERR_OUT_OF_RANGE;

}

/* Function Name:
 *      rtk_svlan_ipmc2s_del
 * Description:
 *      delete ip multicast address to SVLAN
 * Input:
 *      ipmc - ip multicast address
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_SVLAN_VID        - Invalid SVLAN VID parameter.
 *      RT_ERR_OUT_OF_RANGE     - input out of range.
 * Note:
 *      The API can delete IP mutlicast to SVID configuration. There are 32 SVLAN multicast configurations for IP and L2 multicast.
 */
int rtk_svlan_ipmc2s_del(unsigned int ipmc)
{
    int ret_val;
    unsigned int i;
    rtl8367b_svlan_mc2s_t svlanMC2SConf;

    if ((ipmc&0xF0000000)!=0xE0000000)
        return RT_ERR_INPUT;

    for (i = 0; i <= RTL8367B_MC2SIDXMAX; i++)
    {
        if ((ret_val = rtl8367b_getAsicSvlanMC2SConf(i, &svlanMC2SConf)) != RT_ERR_OK)
            return ret_val;

        if (TRUE == svlanMC2SConf.valid)
        {
            if (svlanMC2SConf.format == SVLAN_MC2S_MODE_IP && svlanMC2SConf.sdata==ipmc&&svlanMC2SConf.smask!=0)
            {
                memset(&svlanMC2SConf, 0, sizeof(rtl8367b_svlan_mc2s_t));
                if ((ret_val = rtl8367b_setAsicSvlanMC2SConf(i, &svlanMC2SConf)) != RT_ERR_OK)
                    return ret_val;
                return RT_ERR_OK;
            }
        }
    }

    return RT_ERR_OUT_OF_RANGE;
}

/* Function Name:
 *      rtk_svlan_ipmc2s_get
 * Description:
 *      Get ip multicast address to SVLAN
 * Input:
 *      ipmc - ip multicast address
 * Output:
 *      pSvid - SVLAN VID
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 *      RT_ERR_OUT_OF_RANGE - input out of range.
 * Note:
 *      The API can get IP mutlicast to SVID configuration. There are 32 SVLAN multicast configurations for IP and L2 multicast.
 */
int rtk_svlan_ipmc2s_get(unsigned int ipmc, rtk_vlan_t *pSvid)
{
    int ret_val;
    unsigned int i;
    rtl8367b_svlan_memconf_t svlanMemConf;
    rtl8367b_svlan_mc2s_t svlanMC2SConf;

    if ((ipmc&0xF0000000)!=0xE0000000)
        return RT_ERR_INPUT;

    for (i = 0; i <= RTL8367B_MC2SIDXMAX; i++)
    {
        if ((ret_val = rtl8367b_getAsicSvlanMC2SConf(i, &svlanMC2SConf)) != RT_ERR_OK)
            return ret_val;

        if (TRUE == svlanMC2SConf.valid && svlanMC2SConf.format == SVLAN_MC2S_MODE_IP && svlanMC2SConf.sdata == ipmc && svlanMC2SConf.smask != 0)
        {
            if ((ret_val = rtl8367b_getAsicSvlanMemberConfiguration(svlanMC2SConf.svidx, &svlanMemConf)) != RT_ERR_OK)
                return ret_val;
            *pSvid = svlanMemConf.vs_svid;
            return RT_ERR_OK;
        }
    }

    return RT_ERR_OUT_OF_RANGE;
}

/* Function Name:
 *      rtk_svlan_l2mc2s_add
 * Description:
 *      Add L2 multicast address to SVLAN
 * Input:
 *      svid - SVLAN VID
 *      mac - L2 multicast address
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                       - OK
 *      RT_ERR_FAILED                   - Failed
 *      RT_ERR_SMI                      - SMI access error
 *      RT_ERR_SVLAN_VID                - Invalid SVLAN VID parameter.
 *      RT_ERR_SVLAN_ENTRY_NOT_FOUND    - specified svlan entry not found.
 *      RT_ERR_OUT_OF_RANGE             - input out of range.
 *      RT_ERR_INPUT                    - Invalid input parameters.
 * Note:
 *      The API can set L2 Mutlicast to SVID configuration. If upstream packet is L2 multicast
 *      packet and DMAC is matched, ASIC will assign egress SVID to the packet. There are 32
 *      SVLAN multicast configurations for IP and L2 multicast.
 */
int rtk_svlan_l2mc2s_add(rtk_vlan_t svid, rtk_mac_t mac)
{
    int ret_val, i;
    unsigned int empty_idx;
    unsigned int svidx, l2add;
    rtl8367b_svlan_memconf_t svlanMemConf;
    rtl8367b_svlan_mc2s_t svlanMC2SConf;

    if (svid > RTL8367B_VIDMAX)
        return RT_ERR_SVLAN_VID;

    if (mac.octet[0]!= 1&&mac.octet[1]!=0)
        return RT_ERR_INPUT;

    memcpy(&l2add, &mac.octet[2],4);

     svidx = 0xFFFF;

    for (i = 0; i < RTL8367B_SVIDXNO; i++)
    {
        if ((ret_val = rtl8367b_getAsicSvlanMemberConfiguration(i, &svlanMemConf)) != RT_ERR_OK)
            return ret_val;

        if (svid == svlanMemConf.vs_svid)
        {
            svidx = i;
            break;
        }
    }

    if (0xFFFF == svidx)
        return RT_ERR_SVLAN_ENTRY_NOT_FOUND;

    empty_idx = 0xFFFF;

    for (i = RTL8367B_MC2SIDXMAX; i >=0; i--)
    {
        if ((ret_val = rtl8367b_getAsicSvlanMC2SConf(i, &svlanMC2SConf)) != RT_ERR_OK)
            return ret_val;

        if (TRUE == svlanMC2SConf.valid)
        {
            if (svlanMC2SConf.format == SVLAN_MC2S_MODE_MAC && svlanMC2SConf.sdata==l2add&&svlanMC2SConf.smask!=0)
            {
                svlanMC2SConf.svidx = svidx;
                if ((ret_val = rtl8367b_setAsicSvlanMC2SConf(i, &svlanMC2SConf)) != RT_ERR_OK)
                    return ret_val;
            }
        }
        else
        {
            empty_idx = i;
        }
    }

    if (empty_idx!=0xFFFF)
    {
        svlanMC2SConf.valid = TRUE;
        svlanMC2SConf.svidx = svidx;
        svlanMC2SConf.format = SVLAN_MC2S_MODE_MAC;
        svlanMC2SConf.sdata = l2add;
        svlanMC2SConf.smask = 0xFFFFFFFF;

        if ((ret_val = rtl8367b_setAsicSvlanMC2SConf(empty_idx, &svlanMC2SConf)) != RT_ERR_OK)
            return ret_val;
        return RT_ERR_OK;
    }

    return RT_ERR_OUT_OF_RANGE;
}

/* Function Name:
 *      rtk_svlan_l2mc2s_del
 * Description:
 *      delete L2 multicast address to SVLAN
 * Input:
 *      mac - L2 multicast address
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_SVLAN_VID        - Invalid SVLAN VID parameter.
 *      RT_ERR_OUT_OF_RANGE     - input out of range.
 * Note:
 *      The API can delete Mutlicast to SVID configuration. There are 32 SVLAN multicast configurations for IP and L2 multicast.
 */
int rtk_svlan_l2mc2s_del(rtk_mac_t mac)
{
    int ret_val;
    unsigned int i;
    unsigned int l2add;
    rtl8367b_svlan_mc2s_t svlanMC2SConf;

      if (mac.octet[0]!= 1&&mac.octet[1]!=0)
        return RT_ERR_INPUT;

    memcpy(&l2add, &mac.octet[2],4);

    for (i = 0; i <= RTL8367B_MC2SIDXMAX; i++)
    {
        if ((ret_val = rtl8367b_getAsicSvlanMC2SConf(i, &svlanMC2SConf)) != RT_ERR_OK)
            return ret_val;

        if (TRUE == svlanMC2SConf.valid)
        {
            if (svlanMC2SConf.format == SVLAN_MC2S_MODE_MAC && svlanMC2SConf.sdata==l2add&&svlanMC2SConf.smask!=0)
            {
                memset(&svlanMC2SConf, 0, sizeof(rtl8367b_svlan_mc2s_t));
                if ((ret_val = rtl8367b_setAsicSvlanMC2SConf(i, &svlanMC2SConf)) != RT_ERR_OK)
                    return ret_val;
                return RT_ERR_OK;
            }
        }
    }

    return RT_ERR_OUT_OF_RANGE;
}

/* Function Name:
 *      rtk_svlan_l2mc2s_get
 * Description:
 *      Get L2 multicast address to SVLAN
 * Input:
 *      mac - L2 multicast address
 * Output:
 *      pSvid - SVLAN VID
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_INPUT            - Invalid input parameters.
 *      RT_ERR_OUT_OF_RANGE     - input out of range.
 * Note:
 *      The API can get L2 mutlicast to SVID configuration. There are 32 SVLAN multicast configurations for IP and L2 multicast.
 */
int rtk_svlan_l2mc2s_get(rtk_mac_t mac, rtk_vlan_t *pSvid)
{
    int ret_val;
    unsigned int i;
    unsigned int l2add;
    rtl8367b_svlan_memconf_t svlanMemConf;
    rtl8367b_svlan_mc2s_t svlanMC2SConf;

    if (mac.octet[0]!= 1&&mac.octet[1]!=0)
        return RT_ERR_INPUT;

    memcpy(&l2add, &mac.octet[2],4);

    for (i = 0; i <= RTL8367B_MC2SIDXMAX; i++)
    {
        if ((ret_val = rtl8367b_getAsicSvlanMC2SConf(i, &svlanMC2SConf)) != RT_ERR_OK)
            return ret_val;

        if (TRUE == svlanMC2SConf.valid)
        {
            if (svlanMC2SConf.format == SVLAN_MC2S_MODE_MAC && svlanMC2SConf.sdata==l2add&&svlanMC2SConf.smask!=0)
            {
                if ((ret_val = rtl8367b_getAsicSvlanMemberConfiguration(svlanMC2SConf.svidx, &svlanMemConf)) != RT_ERR_OK)
                    return ret_val;
                *pSvid = svlanMemConf.vs_svid;

                return RT_ERR_OK;
            }
        }
    }

    return RT_ERR_OUT_OF_RANGE;
}

/* Function Name:
 *      rtk_svlan_sp2c_add
 * Description:
 *      Add system SP2C configuration
 * Input:
 *      cvid        - VLAN ID
 *      dst_port    - Destination port of SVLAN to CVLAN configuration
 *      svid        - SVLAN VID
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 *      RT_ERR_SVLAN_VID    - Invalid SVLAN VID parameter.
 *      RT_ERR_VLAN_VID     - Invalid VID parameter.
 *      RT_ERR_OUT_OF_RANGE - input out of range.
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      The API can add SVID & Destination Port to CVLAN configuration. The downstream frames with assigned
 *      SVID will be add C-tag with assigned CVID if the output port is the assigned destination port.
 *      There are 128 SP2C configurations.
 */
int rtk_svlan_sp2c_add(rtk_vlan_t svid, unsigned int dst_port, rtk_vlan_t cvid)
{
    int ret_val, i;
    unsigned int empty_idx, svidx;
    rtl8367b_svlan_memconf_t svlanMemConf;
    rtl8367b_svlan_s2c_t svlanSP2CConf;

    if (svid > RTL8367B_VIDMAX)
        return RT_ERR_SVLAN_VID;

    if (cvid > RTL8367B_VIDMAX)
        return RT_ERR_VLAN_VID;

      if (dst_port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    svidx = 0xFFFF;

    for (i = 0; i < RTL8367B_SVIDXNO; i++)
    {
        if ((ret_val = rtl8367b_getAsicSvlanMemberConfiguration(i, &svlanMemConf)) != RT_ERR_OK)
            return ret_val;

        if (svid == svlanMemConf.vs_svid)
        {
            svidx = i;
            break;
        }
    }

    if (0xFFFF == svidx)
        return RT_ERR_SVLAN_ENTRY_NOT_FOUND;

    empty_idx = 0xFFFF;

    for (i=RTL8367B_SP2CMAX; i >=0 ; i--)
    {
        if ((ret_val = rtl8367b_getAsicSvlanSP2CConf(i, &svlanSP2CConf)) != RT_ERR_OK)
            return ret_val;

        if ( (svlanSP2CConf.svidx == svidx) && (svlanSP2CConf.dstport == dst_port) && (svlanSP2CConf.valid == 1))
        {
            empty_idx = i;
            break;
        }
        else if (svlanSP2CConf.valid == 0)
        {
            empty_idx = i;
        }
    }

    if (empty_idx!=0xFFFF)
    {
        svlanSP2CConf.valid     = 1;
        svlanSP2CConf.vid       = cvid;
        svlanSP2CConf.svidx     = svidx;
        svlanSP2CConf.dstport   = dst_port;

        if ((ret_val = rtl8367b_setAsicSvlanSP2CConf(empty_idx, &svlanSP2CConf)) != RT_ERR_OK)
            return ret_val;
        return RT_ERR_OK;
    }

    return RT_ERR_OUT_OF_RANGE;

}

/* Function Name:
 *      rtk_svlan_sp2c_get
 * Description:
 *      Get configure system SP2C content
 * Input:
 *      svid 	    - SVLAN VID
 *      dst_port 	- Destination port of SVLAN to CVLAN configuration
 * Output:
 *      pCvid - VLAN ID
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 *      RT_ERR_OUT_OF_RANGE - input out of range.
 *      RT_ERR_PORT_ID      - Invalid port number.
 *      RT_ERR_SVLAN_VID    - Invalid SVLAN VID parameter.
 * Note:
 *     The API can get SVID & Destination Port to CVLAN configuration. There are 128 SP2C configurations.
 */
int rtk_svlan_sp2c_get(rtk_vlan_t svid, unsigned int dst_port, rtk_vlan_t *pCvid)
{
    int ret_val;
    unsigned int i, svidx;
    rtl8367b_svlan_memconf_t svlanMemConf;
    rtl8367b_svlan_s2c_t svlanSP2CConf;

    if (svid > RTL8367B_VIDMAX)
        return RT_ERR_SVLAN_VID;

    if (dst_port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    svidx = 0xFFFF;

    for (i = 0; i < RTL8367B_SVIDXNO; i++)
    {
        if ((ret_val = rtl8367b_getAsicSvlanMemberConfiguration(i, &svlanMemConf)) != RT_ERR_OK)
            return ret_val;

        if (svid == svlanMemConf.vs_svid)
        {
            svidx = i;
            break;
        }
    }

    if (0xFFFF == svidx)
        return RT_ERR_SVLAN_ENTRY_NOT_FOUND;

    for (i = 0; i <= RTL8367B_SP2CMAX; i++)
    {
        if ((ret_val = rtl8367b_getAsicSvlanSP2CConf(i, &svlanSP2CConf)) != RT_ERR_OK)
            return ret_val;

        if ( (svlanSP2CConf.svidx == svidx) && (svlanSP2CConf.dstport == dst_port) && (svlanSP2CConf.valid == 1) )
        {
            *pCvid = svlanSP2CConf.vid;
            return RT_ERR_OK;
        }
    }

    return RT_ERR_OUT_OF_RANGE;
}

/* Function Name:
 *      rtk_svlan_sp2c_del
 * Description:
 *      Delete system SP2C configuration
 * Input:
 *      svid        - SVLAN VID
 *      dst_port    - Destination port of SVLAN to CVLAN configuration
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 *      RT_ERR_SVLAN_VID    - Invalid SVLAN VID parameter.
 *      RT_ERR_OUT_OF_RANGE - input out of range.
 * Note:
 *      The API can delete SVID & Destination Port to CVLAN configuration. There are 128 SP2C configurations.
 */
int rtk_svlan_sp2c_del(rtk_vlan_t svid, unsigned int dst_port)
{
    int ret_val;
    unsigned int i, svidx;
    rtl8367b_svlan_memconf_t svlanMemConf;
    rtl8367b_svlan_s2c_t svlanSP2CConf;

    if (svid > RTL8367B_VIDMAX)
        return RT_ERR_SVLAN_VID;

    if (dst_port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    svidx = 0xFFFF;

    for (i = 0; i < RTL8367B_SVIDXNO; i++)
    {
        if ((ret_val = rtl8367b_getAsicSvlanMemberConfiguration(i, &svlanMemConf)) != RT_ERR_OK)
            return ret_val;

        if (svid == svlanMemConf.vs_svid)
        {
            svidx = i;
            break;
        }
    }

    if (0xFFFF == svidx)
        return RT_ERR_SVLAN_ENTRY_NOT_FOUND;

    for (i = 0; i <= RTL8367B_SP2CMAX; i++)
    {
        if ((ret_val = rtl8367b_getAsicSvlanSP2CConf(i, &svlanSP2CConf)) != RT_ERR_OK)
            return ret_val;

        if ( (svlanSP2CConf.svidx == svidx) && (svlanSP2CConf.dstport == dst_port) && (svlanSP2CConf.valid == 1) )
        {
            svlanSP2CConf.valid     = 0;
            svlanSP2CConf.vid       = 0;
            svlanSP2CConf.svidx     = 0;
            svlanSP2CConf.dstport   = 0;

            if ((ret_val = rtl8367b_setAsicSvlanSP2CConf(i, &svlanSP2CConf)) != RT_ERR_OK)
                return ret_val;
            return RT_ERR_OK;
        }

    }

    return RT_ERR_OUT_OF_RANGE;
}

/* Function Name:
 *      rtk_cpu_enable_set
 * Description:
 *      Set CPU port function enable/disable.
 * Input:
 *      enable - CPU port function enable
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameter.
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *      The API can set CPU port function enable/disable.
 */
int rtk_cpu_enable_set(rtk_enable_t enable)
{
    int ret_val;

    if (enable >= RTK_ENABLE_END)
        return RT_ERR_ENABLE;

    if ((ret_val = rtl8367b_setAsicCputagEnable(enable)) != RT_ERR_OK)
        return ret_val;

    if (DISABLED == enable)
    {
        if ((ret_val = rtl8367b_setAsicCputagPortmask(0)) != RT_ERR_OK)
            return ret_val;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_cpu_enable_get
 * Description:
 *      Get CPU port and its setting.
 * Input:
 *      None
 * Output:
 *      pEnable - CPU port function enable
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_INPUT            - Invalid input parameters.
 *      RT_ERR_L2_NO_CPU_PORT   - CPU port is not exist
 * Note:
 *      The API can get CPU port function enable/disable.
 */
int rtk_cpu_enable_get(rtk_enable_t *pEnable)
{
    int ret_val;

    if ((ret_val = rtl8367b_getAsicCputagEnable(pEnable)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_cpu_tagPort_set
 * Description:
 *      Set CPU port and CPU tag insert mode.
 * Input:
 *      port - Port id.
 *      mode - CPU tag insert for packets egress from CPU port.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameter.
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *      The API can set CPU port and inserting proprietary CPU tag mode (Length/Type 0x8899)
 *      to the frame that transmitting to CPU port.
 *      The inset cpu tag mode is as following:
 *      - CPU_INSERT_TO_ALL
 *      - CPU_INSERT_TO_TRAPPING
 *      - CPU_INSERT_TO_NONE
 */
int rtk_cpu_tagPort_set(unsigned int port, rtk_cpu_insert_t mode)
{
    int ret_val;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_INPUT;

    if (mode >= CPU_INSERT_END)
        return RT_ERR_INPUT;

    if ((ret_val = rtl8367b_setAsicCputagPortmask(1<<port)) != RT_ERR_OK)
        return ret_val;

    if ((ret_val = rtl8367b_setAsicCputagTrapPort(port)) != RT_ERR_OK)
        return ret_val;

    if ((ret_val = rtl8367b_setAsicCputagInsertMode(mode)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_cpu_tagPort_get
 * Description:
 *      Get CPU port and CPU tag insert mode.
 * Input:
 *      None
 * Output:
 *      pPort - Port id.
 *      pMode - CPU tag insert for packets egress from CPU port, 0:all insert 1:Only for trapped packets 2:no insert.
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_INPUT            - Invalid input parameters.
 *      RT_ERR_L2_NO_CPU_PORT   - CPU port is not exist
 * Note:
 *      The API can get configured CPU port and its setting.
 *      The inset cpu tag mode is as following:
 *      - CPU_INSERT_TO_ALL
 *      - CPU_INSERT_TO_TRAPPING
 *      - CPU_INSERT_TO_NONE
 */
int rtk_cpu_tagPort_get(unsigned int *pPort, rtk_cpu_insert_t *pMode)
{
    int ret_val;
    unsigned int i, pmsk, port;

    if ((ret_val = rtl8367b_getAsicCputagPortmask(&pmsk)) != RT_ERR_OK)
        return ret_val;

    if ((ret_val = rtl8367b_getAsicCputagTrapPort(&port)) != RT_ERR_OK)
        return ret_val;

    for (i = 0; i< RTK_MAX_NUM_OF_PORT; i++)
    {
        if ((pmsk&(1<<i))!=0)
        {
            if (i==port)
                *pPort = port;
            else
                return RT_ERR_FAILED;
        }
    }

    if ((ret_val = rtl8367b_getAsicCputagInsertMode(pMode)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_dot1x_unauthPacketOper_set
 * Description:
 *      Set 802.1x unauth action configuration.
 * Input:
 *      port            - Port id.
 *      unauth_action   - 802.1X unauth action.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 *      RT_ERR_INPUT        - Invalid input parameter.
 * Note:
 *      This API can set 802.1x unauth action configuration.
 *      The unauth action is as following:
 *      - DOT1X_ACTION_DROP
 *      - DOT1X_ACTION_TRAP2CPU
 *      - DOT1X_ACTION_GUESTVLAN
 */
int rtk_dot1x_unauthPacketOper_set(unsigned int port, rtk_dot1x_unauth_action_t unauth_action)
{
    int ret_val;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if (unauth_action >= DOT1X_ACTION_END)
        return RT_ERR_DOT1X_PROC;

    if ((ret_val = rtl8367b_setAsic1xProcConfig(port, unauth_action)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_dot1x_unauthPacketOper_get
 * Description:
 *      Get 802.1x unauth action configuration.
 * Input:
 *      port - Port id.
 * Output:
 *      pUnauth_action - 802.1X unauth action.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *      This API can get 802.1x unauth action configuration.
 *      The unauth action is as following:
 *      - DOT1X_ACTION_DROP
 *      - DOT1X_ACTION_TRAP2CPU
 *      - DOT1X_ACTION_GUESTVLAN
 */
int rtk_dot1x_unauthPacketOper_get(unsigned int port, rtk_dot1x_unauth_action_t *pUnauth_action)
{
    int ret_val;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if ((ret_val = rtl8367b_getAsic1xProcConfig(port, pUnauth_action)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_dot1x_eapolFrame2CpuEnable_set
 * Description:
 *      Set 802.1x EAPOL packet trap to CPU configuration
 * Input:
 *      enable - The status of 802.1x EAPOL packet.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_ENABLE       - Invalid enable input.
 * Note:
 *      To support 802.1x authentication functionality, EAPOL frame (ether type = 0x888E) has to
 *      be trapped to CPU.
 *      The status of EAPOL frame trap to CPU is as following:
 *      - DISABLED
 *      - ENABLED
 */
int rtk_dot1x_eapolFrame2CpuEnable_set(rtk_enable_t enable)
{
    int ret_val;
    rtl8367b_rma_t rmacfg;

    if (enable >= RTK_ENABLE_END)
        return RT_ERR_ENABLE;

    if ((ret_val = rtl8367b_getAsicRma(3, &rmacfg)) != RT_ERR_OK)
        return ret_val;

    if (ENABLED == enable)
        rmacfg.operation = RMAOP_TRAP_TO_CPU;
    else if (DISABLED == enable)
        rmacfg.operation = RMAOP_FORWARD;
    else
        return RT_ERR_INPUT;

    if ((ret_val = rtl8367b_setAsicRma(3, &rmacfg)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_dot1x_eapolFrame2CpuEnable_get
 * Description:
 *      Get 802.1x EAPOL packet trap to CPU configuration
 * Input:
 *      None
 * Output:
 *      pEnable - The status of 802.1x EAPOL packet.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      To support 802.1x authentication functionality, EAPOL frame (ether type = 0x888E) has to
 *      be trapped to CPU.
 *      The status of EAPOL frame trap to CPU is as following:
 *      - DISABLED
 *      - ENABLED
 */
int rtk_dot1x_eapolFrame2CpuEnable_get(rtk_enable_t *pEnable)
{
    int ret_val;
    rtl8367b_rma_t rmacfg;

    if ((ret_val = rtl8367b_getAsicRma(3, &rmacfg)) != RT_ERR_OK)
        return ret_val;

    if (RMAOP_TRAP_TO_CPU == rmacfg.operation)
        *pEnable = ENABLED;
    else
        *pEnable = DISABLED;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_dot1x_portBasedEnable_set
 * Description:
 *      Set 802.1x port-based enable configuration
 * Input:
 *      port - Port id.
 *      enable - The status of 802.1x port.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_PORT_ID              - Invalid port number.
 *      RT_ERR_ENABLE               - Invalid enable input.
 *      RT_ERR_DOT1X_PORTBASEDPNEN  - 802.1X port-based enable error
 * Note:
 *      The API can update the port-based port enable register content. If a port is 802.1x
 *      port based network access control "enabled", it should be authenticated so packets
 *      from that port won't be dropped or trapped to CPU.
 *      The status of 802.1x port-based network access control is as following:
 *      - DISABLED
 *      - ENABLED
 */
int rtk_dot1x_portBasedEnable_set(unsigned int port, rtk_enable_t enable)
{
    int ret_val;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if (enable >= RTK_ENABLE_END)
        return RT_ERR_ENABLE;

    if ((ret_val = rtl8367b_setAsic1xPBEnConfig(port,enable)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_dot1x_portBasedEnable_get
 * Description:
 *      Get 802.1x port-based enable configuration
 * Input:
 *      port - Port id.
 * Output:
 *      pEnable - The status of 802.1x port.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *      The API can get the 802.1x port-based port status.
 */
int rtk_dot1x_portBasedEnable_get(unsigned int port, rtk_enable_t *pEnable)
{
    int ret_val;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if ((ret_val = rtl8367b_getAsic1xPBEnConfig(port, pEnable)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_dot1x_portBasedAuthStatus_set
 * Description:
 *      Set 802.1x port-based auth. port configuration
 * Input:
 *      port - Port id.
 *      port_auth - The status of 802.1x port.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_PORT_ID              - Invalid port number.
 *     RT_ERR_DOT1X_PORTBASEDAUTH   - 802.1X port-based auth error
 * Note:
 *      The authenticated status of 802.1x port-based network access control is as following:
 *      - UNAUTH
 *      - AUTH
 */
int rtk_dot1x_portBasedAuthStatus_set(unsigned int port, rtk_dot1x_auth_status_t port_auth)
{
    int ret_val;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

     if (port_auth >= AUTH_STATUS_END)
        return RT_ERR_DOT1X_PORTBASEDAUTH;

    if ((ret_val = rtl8367b_setAsic1xPBAuthConfig(port, port_auth)) != RT_ERR_OK)
        return ret_val;


    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_dot1x_portBasedAuthStatus_get
 * Description:
 *      Get 802.1x port-based auth. port configuration
 * Input:
 *      port - Port id.
 * Output:
 *      pPort_auth - The status of 802.1x port.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *      The API can get 802.1x port-based port auth.information.
 */
int rtk_dot1x_portBasedAuthStatus_get(unsigned int port, rtk_dot1x_auth_status_t *pPort_auth)
{
    int ret_val;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if ((ret_val = rtl8367b_getAsic1xPBAuthConfig(port, pPort_auth)) != RT_ERR_OK)
        return ret_val;
    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_dot1x_portBasedDirection_set
 * Description:
 *      Set 802.1x port-based operational direction configuration
 * Input:
 *      port            - Port id.
 *      port_direction  - Operation direction
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_PORT_ID              - Invalid port number.
 *      RT_ERR_DOT1X_PORTBASEDOPDIR - 802.1X port-based operation direction error
 * Note:
 *      The operate controlled direction of 802.1x port-based network access control is as following:
 *      - BOTH
 *      - IN
 */
int rtk_dot1x_portBasedDirection_set(unsigned int port, rtk_dot1x_direction_t port_direction)
{
    int ret_val;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if (port_direction >= DIRECTION_END)
        return RT_ERR_DOT1X_PORTBASEDOPDIR;

    if ((ret_val = rtl8367b_setAsic1xPBOpdirConfig(port, port_direction)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_dot1x_portBasedDirection_get
 * Description:
 *      Get 802.1X port-based operational direction configuration
 * Input:
 *      port - Port id.
 * Output:
 *      pPort_direction - Operation direction
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *      The API can get 802.1x port-based operational direction information.
 */
int rtk_dot1x_portBasedDirection_get(unsigned int port, rtk_dot1x_direction_t *pPort_direction)
{
    int ret_val;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if ((ret_val = rtl8367b_getAsic1xPBOpdirConfig(port, pPort_direction)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_dot1x_macBasedEnable_set
 * Description:
 *      Set 802.1x mac-based port enable configuration
 * Input:
 *      port - Port id.
 *      enable - The status of 802.1x port.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_PORT_ID              - Invalid port number.
 *      RT_ERR_ENABLE               - Invalid enable input.
 *      RT_ERR_DOT1X_MACBASEDPNEN   - 802.1X mac-based enable error
 * Note:
 *      If a port is 802.1x MAC based network access control "enabled", the incoming packets should
 *       be authenticated so packets from that port won't be dropped or trapped to CPU.
 *      The status of 802.1x MAC-based network access control is as following:
 *      - DISABLED
 *      - ENABLED
 */
int rtk_dot1x_macBasedEnable_set(unsigned int port, rtk_enable_t enable)
{
    int ret_val;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if (enable >= RTK_ENABLE_END)
        return RT_ERR_ENABLE;

    if ((ret_val = rtl8367b_setAsic1xMBEnConfig(port,enable)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_dot1x_macBasedEnable_get
 * Description:
 *      Get 802.1x mac-based port enable configuration
 * Input:
 *      port - Port id.
 * Output:
 *      pEnable - The status of 802.1x port.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *      If a port is 802.1x MAC based network access control "enabled", the incoming packets should
 *      be authenticated so packets from that port wont be dropped or trapped to CPU.
 *      The status of 802.1x MAC-based network access control is as following:
 *      - DISABLED
 *      - ENABLED
 */
int rtk_dot1x_macBasedEnable_get(unsigned int port, rtk_enable_t *pEnable)
{
    int ret_val;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if ((ret_val = rtl8367b_getAsic1xMBEnConfig(port, pEnable)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_dot1x_macBasedAuthMac_add
 * Description:
 *      Add an authenticated MAC to ASIC
 * Input:
 *      port        - Port id.
 *      pAuth_mac   - The authenticated MAC.
 *      fid         - filtering database.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_PORT_ID              - Invalid port number.
 *      RT_ERR_ENABLE               - Invalid enable input.
 *      RT_ERR_DOT1X_MACBASEDPNEN   - 802.1X mac-based enable error
 * Note:
 *      The API can add a 802.1x authenticated MAC address to port. If the MAC does not exist in LUT,
 *      user can't add this MAC to auth status.
 */
int rtk_dot1x_macBasedAuthMac_add(unsigned int port, rtk_mac_t *pAuth_mac, unsigned int fid)
{
    int ret_val;
      unsigned int method;
    rtl8367b_luttb l2Table;

    /* must be unicast address */
    if ((pAuth_mac == NULL) || (pAuth_mac->octet[0] & 0x1))
        return RT_ERR_MAC;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if (fid > RTL8367B_FIDMAX)
        return RT_ERR_L2_FID;

    memset(&l2Table, 0, sizeof(rtl8367b_luttb));

    /* fill key (MAC,FID) to get L2 entry */
    memcpy(l2Table.mac.octet, pAuth_mac->octet, ETHER_ADDR_LEN);
    l2Table.fid = fid;
    method = LUTREADMETHOD_MAC;
    ret_val = rtl8367b_getAsicL2LookupTb(method, &l2Table);
    if ( RT_ERR_OK == ret_val)
    {
        if (l2Table.spa != port)
            return RT_ERR_DOT1X_MAC_PORT_MISMATCH;

        memcpy(l2Table.mac.octet, pAuth_mac->octet, ETHER_ADDR_LEN);
        l2Table.fid = fid;
        l2Table.efid = 0;
        l2Table.auth = 1;
        ret_val = rtl8367b_setAsicL2LookupTb(&l2Table);
        return ret_val;
    }
    else
        return ret_val;

}

/* Function Name:
 *      rtk_dot1x_macBasedAuthMac_del
 * Description:
 *      Delete an authenticated MAC to ASIC
 * Input:
 *      port - Port id.
 *      pAuth_mac - The authenticated MAC.
 *      fid - filtering database.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_MAC          - Invalid MAC address.
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *      The API can delete a 802.1x authenticated MAC address to port. It only change the auth status of
 *      the MAC and won't delete it from LUT.
 */
int rtk_dot1x_macBasedAuthMac_del(unsigned int port, rtk_mac_t *pAuth_mac, unsigned int fid)
{
    int ret_val;
    unsigned int method;
    rtl8367b_luttb l2Table;

    /* must be unicast address */
    if ((pAuth_mac == NULL) || (pAuth_mac->octet[0] & 0x1))
        return RT_ERR_MAC;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if (fid > RTL8367B_FIDMAX)
        return RT_ERR_L2_FID;

    memset(&l2Table, 0, sizeof(rtl8367b_luttb));

    /* fill key (MAC,FID) to get L2 entry */
    memcpy(l2Table.mac.octet, pAuth_mac->octet, ETHER_ADDR_LEN);
    l2Table.fid = fid;
    method = LUTREADMETHOD_MAC;
    ret_val = rtl8367b_getAsicL2LookupTb(method, &l2Table);
    if (RT_ERR_OK == ret_val)
    {
        if (l2Table.spa != port)
            return RT_ERR_DOT1X_MAC_PORT_MISMATCH;

        memcpy(l2Table.mac.octet, pAuth_mac->octet, ETHER_ADDR_LEN);
        l2Table.fid = fid;
        l2Table.auth = 0;
        ret_val = rtl8367b_setAsicL2LookupTb(&l2Table);
        return ret_val;
    }
    else
        return ret_val;

}

/* Function Name:
 *      rtk_dot1x_macBasedDirection_set
 * Description:
 *      Set 802.1x mac-based operational direction configuration
 * Input:
 *      mac_direction - Operation direction
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_INPUT                - Invalid input parameter.
 *      RT_ERR_DOT1X_MACBASEDOPDIR  - 802.1X mac-based operation direction error
 * Note:
 *      The operate controlled direction of 802.1x mac-based network access control is as following:
 *      - BOTH
 *      - IN
 */
int rtk_dot1x_macBasedDirection_set(rtk_dot1x_direction_t mac_direction)
{
    int ret_val;

    if (mac_direction >= DIRECTION_END)
        return RT_ERR_DOT1X_MACBASEDOPDIR;

    if ((ret_val = rtl8367b_setAsic1xMBOpdirConfig(mac_direction)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_dot1x_macBasedDirection_get
 * Description:
 *      Get 802.1x mac-based operational direction configuration
 * Input:
 *      port - Port id.
 * Output:
 *      pMac_direction - Operation direction
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      The API can get 802.1x mac-based operational direction information.
 */
int rtk_dot1x_macBasedDirection_get(rtk_dot1x_direction_t *pMac_direction)
{
    int ret_val;

    if ((ret_val = rtl8367b_getAsic1xMBOpdirConfig(pMac_direction)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      Set 802.1x guest VLAN configuration
 * Description:
 *      Set 802.1x mac-based operational direction configuration
 * Input:
 *      vid - 802.1x guest VLAN ID
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameter.
 * Note:
 *      The operate controlled 802.1x guest VLAN
 */
int rtk_dot1x_guestVlan_set(rtk_vlan_t vid)
{
    int ret_val;
    int i;
    unsigned int empty_idx;
    rtl8367b_user_vlan4kentry vlan4K;
    rtl8367b_vlanconfiguser vlanMC;

    /* vid must be 0~4095 */
    if (vid > RTL8367B_VIDMAX)
        return RT_ERR_VLAN_VID;

    empty_idx = 0xFFFF;

    for (i = RTL8367B_CVIDXMAX; i >=0 ; i--)
    {
        if ((ret_val = rtl8367b_getAsicVlanMemberConfig(i, &vlanMC)) != RT_ERR_OK)
            return ret_val;
        if (vid == vlanMC.evid)
        {
            if ((ret_val = rtl8367b_setAsic1xGuestVidx(i)) != RT_ERR_OK)
                return ret_val;
            return RT_ERR_OK;
        }
        else if (vlanMC.evid == 0 && vlanMC.mbr == 0)
        {
             empty_idx = i;
        }

    }

    /*
        vid doesn't exist in 32 member configuration. Find an empty entry in
        32 member configuration, then copy entry from 4K. If 32 member configuration
        are all full, then find an entry which not used by Port-based VLAN and
        then replace it with 4K. Finally, assign the index to the port.
    */
    if (empty_idx!=0xFFFF)
        {
            vlan4K.vid = vid;
            if ((ret_val = rtl8367b_getAsicVlan4kEntry(&vlan4K)) != RT_ERR_OK)
                return ret_val;

            vlanMC.evid = vid;
            vlanMC.mbr = vlan4K.mbr;
            vlanMC.fid_msti = vlan4K.fid_msti;
            vlanMC.meteridx= vlan4K.meteridx;
            vlanMC.envlanpol= vlan4K.envlanpol;

        if ((ret_val = rtl8367b_setAsicVlanMemberConfig(empty_idx, &vlanMC)) != RT_ERR_OK)
                return ret_val;

            if ((ret_val = rtl8367b_setAsic1xGuestVidx(empty_idx)) != RT_ERR_OK)
                return ret_val;

            return RT_ERR_OK;
        }

    return RT_ERR_FAILED;
}

/* Function Name:
 *      rtk_dot1x_guestVlan_get
 * Description:
 *      Get 802.1x guest VLAN configuration
 * Input:
 *      None
 * Output:
 *      pVid - 802.1x guest VLAN ID
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      The API can get 802.1x guest VLAN information.
 */
int rtk_dot1x_guestVlan_get(rtk_vlan_t *pVid)
{
    int ret_val;
    unsigned int gvidx;
    rtl8367b_vlanconfiguser vlanMC;

    if ((ret_val = rtl8367b_getAsic1xGuestVidx(&gvidx)) != RT_ERR_OK)
        return ret_val;

    if ((ret_val = rtl8367b_getAsicVlanMemberConfig(gvidx, &vlanMC)) != RT_ERR_OK)
        return ret_val;

    *pVid = vlanMC.evid;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_dot1x_guestVlan2Auth_set
 * Description:
 *      Set 802.1x guest VLAN to auth host configuration
 * Input:
 *      enable - The status of guest VLAN to auth host.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameter.
 * Note:
 *      The operational direction of 802.1x guest VLAN to auth host control is as following:
 *      - ENABLED
 *      - DISABLED
 */
int rtk_dot1x_guestVlan2Auth_set(rtk_enable_t enable)
{
    int ret_val;

    if (enable >= RTK_ENABLE_END)
        return RT_ERR_ENABLE;

    if ((ret_val = rtl8367b_setAsic1xGVOpdir(enable)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_dot1x_guestVlan2Auth_get
 * Description:
 *      Get 802.1x guest VLAN to auth host configuration
 * Input:
 *      None
 * Output:
 *      pEnable - The status of guest VLAN to auth host.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      The API can get 802.1x guest VLAN to auth host information.
 */
int rtk_dot1x_guestVlan2Auth_get(rtk_enable_t *pEnable)
{
    int ret_val;

    if ((ret_val = rtl8367b_getAsic1xGVOpdir(pEnable)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_trunk_port_set
 * Description:
 *      Set trunking group available port mask
 * Input:
 *      trk_gid                 - trunk group id
 *      trunk_member_portmask   - Logic trunking member port mask
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_LA_TRUNK_ID  - Invalid trunking group
 *      RT_ERR_PORT_MASK    - Invalid portmask.
 * Note:
 *      The API can set 4 port trunking group enabled port mask. Each port trunking group has max 4 ports.
 *      If enabled port mask has less than 2 ports available setting, then this trunking group function is disabled.
 *      The group port members for trunk group are as following:
 *      - TRUNK_GROUP0: port 0 to port 3.
 *      - TRUNK_GROUP1: port 4 to port 7.
 */
int rtk_trunk_port_set(rtk_trunk_group_t trk_gid, rtk_portmask_t trunk_member_portmask)
{
    int ret_val;
    unsigned int pmsk;

    if (trk_gid>=TRUNK_GROUP2)
        return RT_ERR_LA_TRUNK_ID;

    if (trunk_member_portmask.bits[0] > RTK_MAX_PORT_MASK)
        return RT_ERR_PORT_MASK;

    if ((trunk_member_portmask.bits[0]|RTL8367B_PORT_TRUNK_GROUP_MASK_MASK(trk_gid))!=RTL8367B_PORT_TRUNK_GROUP_MASK_MASK(trk_gid))
        return RT_ERR_PORT_MASK;

    pmsk = (trunk_member_portmask.bits[0]&RTL8367B_PORT_TRUNK_GROUP_MASK_MASK(trk_gid))>>RTL8367B_PORT_TRUNK_GROUP_MASK_OFFSET(trk_gid);

    if ((ret_val = rtl8367b_setAsicTrunkingGroup(trk_gid, pmsk)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_trunk_port_get
 * Description:
 *      Get trunking group available port mask
 * Input:
 *      trk_gid - trunk group id
 * Output:
 *      pTrunk_member_portmask - Logic trunking member port mask
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_LA_TRUNK_ID  - Invalid trunking group
 * Note:
 *      The API can get 4 port trunking group enabled port mask. Each port trunking group has max 4 ports.
 *      If enabled port mask has less than 2 ports available setting, then this trunking group function is disabled.
 *      The group port members for trunk group are as following:
 *      - TRUNK_GROUP0: port 0 to port 3.
 *      - TRUNK_GROUP1: port 4 to port 7.
 */
int rtk_trunk_port_get(rtk_trunk_group_t trk_gid, rtk_portmask_t *pTrunk_member_portmask)
{
    int ret_val;

    unsigned int pmsk;

    if (trk_gid>=TRUNK_GROUP2)
        return RT_ERR_LA_TRUNK_ID;

    if ((ret_val = rtl8367b_getAsicTrunkingGroup(trk_gid, &pmsk)) != RT_ERR_OK)
        return ret_val;

    pTrunk_member_portmask->bits[0] = pmsk<<RTL8367B_PORT_TRUNK_GROUP_MASK_OFFSET(trk_gid);

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_trunk_distributionAlgorithm_set
 * Description:
 *      Set port trunking hash select sources
 * Input:
 *      trk_gid         - trunk group id
 *      algo_bitmask    - Bitmask of the distribution algorithm
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_LA_TRUNK_ID  - Invalid trunking group
 *      RT_ERR_LA_HASHMASK  - Hash algorithm selection error.
 *      RT_ERR_PORT_MASK    - Invalid portmask.
 * Note:
 *      The API can set port trunking hash algorithm sources.
 *      7 bits mask for link aggregation group0 hash parameter selection {DIP, SIP, DMAC, SMAC, SPA}
 *      - 0b0000001: SPA
 *      - 0b0000010: SMAC
 *      - 0b0000100: DMAC
 *      - 0b0001000: SIP
 *      - 0b0010000: DIP
 *      - 0b0100000: TCP/UDP Source Port
 *      - 0b1000000: TCP/UDP Destination Port
 *      Example:
 *      - 0b0000011: SMAC & SPA
 *      - Note that it could be an arbitrary combination or independent set
 */
int rtk_trunk_distributionAlgorithm_set(rtk_trunk_group_t trk_gid, rtk_trunk_hashVal2Port_t algo_bitmask)
{
    int ret_val;

    if (trk_gid != RTK_WHOLE_SYSTEM)
        return RT_ERR_LA_TRUNK_ID;

    if (algo_bitmask.value[0]>=128)
        return RT_ERR_LA_HASHMASK;

    if ((ret_val = rtl8367b_setAsicTrunkingHashSelect(algo_bitmask.value[0])) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_trunk_distributionAlgorithm_get
 * Description:
 *      Get port trunking hash select sources
 * Input:
 *      trk_gid - trunk group id
 * Output:
 *      pAlgo_bitmask -  Bitmask of the distribution algorithm
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_LA_TRUNK_ID  - Invalid trunking group
 * Note:
 *      The API can get port trunking hash algorithm sources.
 */
int rtk_trunk_distributionAlgorithm_get(rtk_trunk_group_t trk_gid, rtk_trunk_hashVal2Port_t *pAlgo_bitmask)
{
    int ret_val;

    if (trk_gid != RTK_WHOLE_SYSTEM)
        return RT_ERR_LA_TRUNK_ID;

    if ((ret_val = rtl8367b_getAsicTrunkingHashSelect((unsigned int*)&pAlgo_bitmask->value[0])) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_trunk_qeueuEmptyStatus_get
 * Description:
 *      Get current output queue if empty status
 * Input:
 *      trk_gid - trunk group id
 * Output:
 *      pPortmask - queue empty port mask, 1 for empty and 0 for not empty
 * Return:
 *      RT_ERR_OK       - OK
 *      RT_ERR_FAILED   - Failed
 *      RT_ERR_SMI      - SMI access error
 * Note:
 *      The API can get queues are empty port mask
 */
int rtk_trunk_qeueuEmptyStatus_get(rtk_portmask_t *pPortmask)
{
    int ret_val;

    if ((ret_val = rtl8367b_getAsicQeueuEmptyStatus(&pPortmask->bits[0])) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_switch_maxPktLen_set
 * Description:
 *      Set the max packet length of the specific unit
 * Input:
 *      len - max packet length
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT 		- Invalid input parameters.
 * Note:
 *      The API can set max packet length of the specific unit to
 *      - MAXPKTLEN_1522B,
 *      - MAXPKTLEN_1536B,
 *      - MAXPKTLEN_1552B,
 *      - MAXPKTLEN_16000B.
 */
int rtk_switch_maxPktLen_set(rtk_switch_maxPktLen_t len)
{
    int ret_val;

    if (len>=MAXPKTLEN_END)
        return RT_ERR_INPUT;

    if ((ret_val = rtl8367b_setAsicMaxLengthInRx(len)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_switch_maxPktLen_get
 * Description:
 *      Get the max packet length of the specific unit
 * Input:
 *      None
 * Output:
 *      pLen - pointer to the max packet length
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 * Note:
 *      The API can set max packet length of the specific unit.
 */
int rtk_switch_maxPktLen_get(rtk_switch_maxPktLen_t *pLen)
{
    int ret_val;

    if ((ret_val = rtl8367b_getAsicMaxLengthInRx(pLen)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_switch_portMaxPktLen_set
 * Description:
 *      Set 2nd max packet length configuration
 * Input:
 *      port    - Port ID
 *      length  - Length(1522 bytes, 1536 bytes, 1552 bytes, 16000 bytes)
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 * Note:
 *      The API can set 2nd max packet length configuration.
 *      The parameter "port" indicates which port would follow 2nd configuration.
 *      If the paramter "length" is as same as 1st configuration, this API
 *      would set the port back to 1st configuration. Users should always use
 *      rtk_switch_maxPktLen_set to setup 1st configuration for whole system
 *      setting and then use rtk_switch_portMaxPktLen_set to setup a per port
 *      configuration.
 */
int rtk_switch_portMaxPktLen_set(unsigned int port, unsigned int length)
{
    rtk_switch_maxPktLen_t  pkt_len, curr_pkt_len;
    int           ret_val;
    unsigned int              maxLength, pmaskGiga, pmask100M;

    if(port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if(length == 1522)
        pkt_len = MAXPKTLEN_1522B;
    else if(length == 1536)
        pkt_len = MAXPKTLEN_1536B;
    else if(length == 1552)
        pkt_len = MAXPKTLEN_1552B;
    else if(length == 16000)
        pkt_len = MAXPKTLEN_16000B;
    else
        return RT_ERR_INPUT;

    if ((ret_val = rtl8367b_getAsicMaxLengthInRx(&curr_pkt_len)) != RT_ERR_OK)
        return ret_val;

    if(curr_pkt_len == pkt_len)
    {
        if ((ret_val = rtl8367b_getAsicMaxLengthAltTxRx(&maxLength, &pmaskGiga, &pmask100M)) != RT_ERR_OK)
            return ret_val;

        pmaskGiga &= ~(0x0001 << port);
        pmask100M &= ~(0x0001 << port);

        if ((ret_val = rtl8367b_setAsicMaxLengthAltTxRx(maxLength, pmaskGiga, pmask100M)) != RT_ERR_OK)
            return ret_val;
    }
    else
    {
        if ((ret_val = rtl8367b_getAsicMaxLengthAltTxRx(&maxLength, &pmaskGiga, &pmask100M)) != RT_ERR_OK)
            return ret_val;

        pmaskGiga |= (0x0001 << port);
        pmask100M |= (0x0001 << port);

        if ((ret_val = rtl8367b_setAsicMaxLengthAltTxRx(pkt_len, pmaskGiga, pmask100M)) != RT_ERR_OK)
            return ret_val;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_switch_portMaxPktLen_get
 * Description:
 *      Get 2nd max packet length configuration
 * Input:
 *      port    - Port ID
 * Output:
 *      pLength  - Length(1522 bytes, 1536 bytes, 1552 bytes, 16000 bytes)
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 * Note:
 *      The API can get 2nd max packet length configuration.
 *      If "port" is not in the 2nd configuration, the setting of
 *      1st configuration woill be returned.
 */
int rtk_switch_portMaxPktLen_get(unsigned int port, unsigned int *pLength)
{
    rtk_switch_maxPktLen_t  curr_pkt_len;
    int           ret_val;
    unsigned int              maxLength, pmaskGiga, pmask100M;

    if(port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if ((ret_val = rtl8367b_getAsicMaxLengthAltTxRx(&maxLength, &pmaskGiga, &pmask100M)) != RT_ERR_OK)
        return ret_val;

    if ((ret_val = rtl8367b_getAsicMaxLengthInRx(&curr_pkt_len)) != RT_ERR_OK)
        return ret_val;

    if(pmaskGiga & (0x0001 << port))
    {
        if(maxLength == MAXPKTLEN_1522B)
            *pLength = 1522;
        else if(maxLength == MAXPKTLEN_1536B)
            *pLength = 1536;
        else if(maxLength == MAXPKTLEN_1552B)
            *pLength = 1552;
        else if(maxLength == MAXPKTLEN_16000B)
            *pLength = 16000;
        else
            return RT_ERR_FAILED;
    }
    else
    {
        if(curr_pkt_len == MAXPKTLEN_1522B)
            *pLength = 1522;
        else if(curr_pkt_len == MAXPKTLEN_1536B)
            *pLength = 1536;
        else if(curr_pkt_len == MAXPKTLEN_1552B)
            *pLength = 1552;
        else if(curr_pkt_len == MAXPKTLEN_16000B)
            *pLength = 16000;
        else
            return RT_ERR_FAILED;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_switch_greenEthernet_set
 * Description:
 *      Set all Ports Green Ethernet state.
 * Input:
 *      enable - Green Ethernet state.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - OK
 *      RT_ERR_FAILED   - Failed
 *      RT_ERR_SMI      - SMI access error
 *      RT_ERR_ENABLE   - Invalid enable input.
 * Note:
 *      This API can set all Ports Green Ethernet state.
 *      The configuration is as following:
 *      - DISABLE
 *      - ENABLE
 */
int rtk_switch_greenEthernet_set(rtk_enable_t enable)
{
    int ret_val;
    unsigned int phy;

    if ((ret_val = rtl8367b_setAsicGreenEthernet(enable))!=RT_ERR_OK)
        return ret_val;

    for (phy=0;phy<=RTK_PHY_ID_MAX;phy++)
    {
        if ((ret_val = rtl8367b_setAsicPowerSaving(phy,enable))!=RT_ERR_OK)
            return ret_val;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_switch_greenEthernet_get
 * Description:
 *      Get all Ports Green Ethernet state.
 * Input:
 *      None
 * Output:
 *      pEnable - Green Ethernet state.
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 * Note:
 *      This API can get Green Ethernet state.
 */
int rtk_switch_greenEthernet_get(rtk_enable_t *pEnable)
{
    int ret_val;
    unsigned int value;
    unsigned int phy;

    if ((ret_val = rtl8367b_getAsicGreenEthernet(&value))!=RT_ERR_OK)
        return ret_val;

    if (value!=1)
    {
        *pEnable = DISABLED;
        return RT_ERR_OK;
    }

    for (phy=0;phy<=RTK_PHY_ID_MAX;phy++)
    {
        if ((ret_val = rtl8367b_getAsicPowerSaving(phy,&value))!=RT_ERR_OK)
            return ret_val;
        if (value!=1)
        {
            *pEnable = DISABLED;
            return RT_ERR_OK;
        }
    }

    *pEnable = ENABLED;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_mirror_portBased_set
 * Description:
 *      Set port mirror function.
 * Input:
 *      mirroring_port          - Monitor port.
 *      pMirrored_rx_portmask   - Rx mirror port mask.
 *      pMirrored_tx_portmask   - Tx mirror port mask.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number
 *      RT_ERR_PORT_MASK    - Invalid portmask.
 * Note:
 *      The API is to set mirror function of source port and mirror port.
 *      The mirror port can only be set to one port and the TX and RX mirror ports
 *      should be identical.
 */
int rtk_mirror_portBased_set(unsigned int mirroring_port, rtk_portmask_t *pMirrored_rx_portmask, rtk_portmask_t *pMirrored_tx_portmask)
{
    int ret_val;
    rtk_enable_t mirRx, mirTx;
    unsigned int i;
      unsigned int source_port;

    if (mirroring_port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if (pMirrored_rx_portmask->bits[0] > RTK_MAX_PORT_MASK)
        return RT_ERR_PORT_MASK;

    if (pMirrored_tx_portmask->bits[0] > RTK_MAX_PORT_MASK)
        return RT_ERR_PORT_MASK;

    /*Only one port for tx & rx mirror*/
    if (pMirrored_tx_portmask->bits[0]!=pMirrored_rx_portmask->bits[0]&&pMirrored_tx_portmask->bits[0]!=0&&pMirrored_rx_portmask->bits[0]!=0)
        return RT_ERR_PORT_MASK;

     /*mirror port != source port*/
    if ((pMirrored_tx_portmask->bits[0]&(1<<mirroring_port))>0||(pMirrored_rx_portmask->bits[0]&(1<<mirroring_port))>0)
        return RT_ERR_PORT_MASK;

   source_port = 0;

   for (i = 0; i< RTK_MAX_NUM_OF_PORT; i++)
   {
        if (pMirrored_tx_portmask->bits[0]&(1<<i))
        {
            source_port = i;
            break;
        }

        if (pMirrored_rx_portmask->bits[0]&(1<<i))
        {
            source_port = i;
            break;
        }
    }

    if ((ret_val = rtl8367b_setAsicPortMirror(source_port, mirroring_port)) != RT_ERR_OK)
        return ret_val;
    if(pMirrored_rx_portmask->bits[0] != 0)
    {
        if ((ret_val = rtl8367b_setAsicPortMirrorMask(pMirrored_rx_portmask->bits[0])) != RT_ERR_OK)
            return ret_val;
    }
    else
    {
        if ((ret_val = rtl8367b_setAsicPortMirrorMask(pMirrored_tx_portmask->bits[0])) != RT_ERR_OK)
            return ret_val;
    }


    if (pMirrored_rx_portmask->bits[0])
        mirRx = ENABLED;
    else
        mirRx = DISABLED;

    if ((ret_val = rtl8367b_setAsicPortMirrorRxFunction(mirRx)) != RT_ERR_OK)
        return ret_val;

    if (pMirrored_tx_portmask->bits[0])
        mirTx = ENABLED;
    else
        mirTx = DISABLED;

    if ((ret_val = rtl8367b_setAsicPortMirrorTxFunction(mirTx)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;

}

/* Function Name:
 *      rtk_mirror_portBased_get
 * Description:
 *      Get port mirror function.
 * Input:
 *      None
 * Output:
 *      pMirroring_port         - Monitor port.
 *      pMirrored_rx_portmask   - Rx mirror port mask.
 *      pMirrored_tx_portmask   - Tx mirror port mask.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT 		- Invalid input parameters.
 * Note:
 *      The API is to get mirror function of source port and mirror port.
 */
int rtk_mirror_portBased_get(unsigned int* pMirroring_port, rtk_portmask_t *pMirrored_rx_portmask, rtk_portmask_t *pMirrored_tx_portmask)
{
    int ret_val;
    unsigned int source_port;
    rtk_enable_t mirRx, mirTx;
    rtk_portmask_t  src_portmask;

    if ((ret_val = rtl8367b_getAsicPortMirror(&source_port, pMirroring_port)) != RT_ERR_OK)
        return ret_val;

    if ((ret_val = rtl8367b_getAsicPortMirrorRxFunction((unsigned int*)&mirRx)) != RT_ERR_OK)
        return ret_val;

    if ((ret_val = rtl8367b_getAsicPortMirrorTxFunction((unsigned int*)&mirTx)) != RT_ERR_OK)
        return ret_val;

    if (DISABLED == mirRx)
        pMirrored_rx_portmask->bits[0]=0;
    else
    {
        pMirrored_rx_portmask->bits[0]=1<<source_port;

        if ((ret_val = rtl8367b_getAsicPortMirrorMask(&(src_portmask.bits[0]))) != RT_ERR_OK)
            return ret_val;

        pMirrored_rx_portmask->bits[0] |= src_portmask.bits[0];
    }

     if (DISABLED == mirTx)
        pMirrored_tx_portmask->bits[0]=0;
    else
    {
        pMirrored_tx_portmask->bits[0]=1<<source_port;

        if ((ret_val = rtl8367b_getAsicPortMirrorMask(&(src_portmask.bits[0]))) != RT_ERR_OK)
            return ret_val;

        pMirrored_tx_portmask->bits[0] |= src_portmask.bits[0];
    }

    return RT_ERR_OK;

}

/* Function Name:
 *      rtk_mirror_portIso_set
 * Description:
 *      Set mirror port isolation.
 * Input:
 *      enable |Mirror isolation status.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_ENABLE       - Invalid enable input
 * Note:
 *      The API is to set mirror isolation function that prevent normal forwarding packets to miror port.
 */
int rtk_mirror_portIso_set(rtk_enable_t enable)
{
    int ret_val;

    if (enable >= RTK_ENABLE_END)
        return RT_ERR_ENABLE;

    if ((ret_val = rtl8367b_setAsicPortMirrorIsolation(enable)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_mirror_portIso_get
 * Description:
 *      Get mirror port isolation.
 * Input:
 *      None
 * Output:
 *      pEnable |Mirror isolation status.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT 		- Invalid input parameters.
 * Note:
 *      The API is to get mirror isolation status.
 */
int rtk_mirror_portIso_get(rtk_enable_t *pEnable)
{
    int ret_val;

    if ((ret_val = rtl8367b_getAsicPortMirrorIsolation(pEnable)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_stat_global_reset
 * Description:
 *      Reset global MIB counter.
 * Input:
 *      None
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 * Note:
 *      Reset MIB counter of ports. API will use global reset while port mask is all-ports.
 */
int rtk_stat_global_reset(void)
{
    int ret_val;

    if ((ret_val = rtl8367b_setAsicMIBsCounterReset(TRUE,FALSE, 0)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_stat_port_reset
 * Description:
 *      Reset per port MIB counter by port.
 * Input:
 *      port - port id.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 * Note:
 *      Reset MIB counter of ports. API will use global reset while port mask is all-ports.
 */
int rtk_stat_port_reset(unsigned int port)
{
    int ret_val;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if ((ret_val = rtl8367b_setAsicMIBsCounterReset(FALSE,FALSE,1<<port)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

#ifdef EMBEDDED_SUPPORT
#else

/* Function Name:
 *      rtk_stat_global_get
 * Description:
 *      Get global MIB counter
 * Input:
 *      cntr_idx - global counter index.
 * Output:
 *      pCntr - global counter value.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT 		- Invalid input parameters.
 * Note:
 *      Get global MIB counter by index definition.
 */
int rtk_stat_global_get(rtk_stat_global_type_t cntr_idx, rtk_stat_counter_t *pCntr)
{
    int ret_val;

    if (cntr_idx!=DOT1D_TP_LEARNED_ENTRY_DISCARDS_INDEX)
        return RT_ERR_STAT_INVALID_GLOBAL_CNTR;

    if ((ret_val = rtl8367b_getAsicMIBsCounter(0, cntr_idx, pCntr)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_stat_global_getAll
 * Description:
 *      Get all global MIB counter
 * Input:
 *      None
 * Output:
 *      pGlobal_cntrs - global counter structure.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT 		- Invalid input parameters.
 * Note:
 *      Get all global MIB counter by index definition.
 */
int rtk_stat_global_getAll(rtk_stat_global_cntr_t *pGlobal_cntrs)
{
    int ret_val;

    if ((ret_val = rtl8367b_getAsicMIBsCounter(0,DOT1D_TP_LEARNED_ENTRY_DISCARDS_INDEX, &pGlobal_cntrs->dot1dTpLearnedEntryDiscards)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

#define MIB_NOT_SUPPORT     (0xFFFF)
static int _get_asic_mib_idx(rtk_stat_port_type_t cnt_idx, RTL8367B_MIBCOUNTER *pMib_idx)
{
    RTL8367B_MIBCOUNTER mib_asic_idx[STAT_PORT_CNTR_END]=
    {
        ifInOctets,                     /* STAT_IfInOctets */
        dot3StatsFCSErrors,             /* STAT_Dot3StatsFCSErrors */
        dot3StatsSymbolErrors,          /* STAT_Dot3StatsSymbolErrors */
        dot3InPauseFrames,              /* STAT_Dot3InPauseFrames */
        dot3ControlInUnknownOpcodes,    /* STAT_Dot3ControlInUnknownOpcodes */
        etherStatsFragments,            /* STAT_EtherStatsFragments */
        etherStatsJabbers,              /* STAT_EtherStatsJabbers */
        ifInUcastPkts,                  /* STAT_IfInUcastPkts */
        etherStatsDropEvents,           /* STAT_EtherStatsDropEvents */
        etherStatsOctets,               /* STAT_EtherStatsOctets */
        etherStatsUnderSizePkts,        /* STAT_EtherStatsUnderSizePkts */
        etherOversizeStats,             /* STAT_EtherOversizeStats */
        etherStatsPkts64Octets,         /* STAT_EtherStatsPkts64Octets */
        etherStatsPkts65to127Octets,    /* STAT_EtherStatsPkts65to127Octets */
        etherStatsPkts128to255Octets,   /* STAT_EtherStatsPkts128to255Octets */
        etherStatsPkts256to511Octets,   /* STAT_EtherStatsPkts256to511Octets */
        etherStatsPkts512to1023Octets,  /* STAT_EtherStatsPkts512to1023Octets */
        etherStatsPkts1024to1518Octets, /* STAT_EtherStatsPkts1024to1518Octets */
        ifInMulticastPkts,              /* STAT_EtherStatsMulticastPkts */
        ifInBroadcastPkts,              /* STAT_EtherStatsBroadcastPkts */
        ifOutOctets,                    /* STAT_IfOutOctets */
        dot3StatsSingleCollisionFrames, /* STAT_Dot3StatsSingleCollisionFrames */
        dot3StatMultipleCollisionFrames,/* STAT_Dot3StatsMultipleCollisionFrames */
        dot3sDeferredTransmissions,     /* STAT_Dot3StatsDeferredTransmissions */
        dot3StatsLateCollisions,        /* STAT_Dot3StatsLateCollisions */
        etherStatsCollisions,           /* STAT_EtherStatsCollisions */
        dot3StatsExcessiveCollisions,   /* STAT_Dot3StatsExcessiveCollisions */
        dot3OutPauseFrames,             /* STAT_Dot3OutPauseFrames */
        MIB_NOT_SUPPORT,                /* STAT_Dot1dBasePortDelayExceededDiscards */
        dot1dTpPortInDiscards,          /* STAT_Dot1dTpPortInDiscards */
        ifOutUcastPkts,                 /* STAT_IfOutUcastPkts */
        ifOutMulticastPkts,             /* STAT_IfOutMulticastPkts */
        ifOutBroadcastPkts,             /* STAT_IfOutBroadcastPkts */
        outOampduPkts,                  /* STAT_OutOampduPkts */
        inOampduPkts,                   /* STAT_InOampduPkts */
        MIB_NOT_SUPPORT,                /* STAT_PktgenPkts */
        inMldChecksumError,             /* STAT_InMldChecksumError */
        inIgmpChecksumError,            /* STAT_InIgmpChecksumError */
        inMldSpecificQuery,             /* STAT_InMldSpecificQuery */
        inMldGeneralQuery,              /* STAT_InMldGeneralQuery */
        inIgmpSpecificQuery,            /* STAT_InIgmpSpecificQuery */
        inIgmpGeneralQuery,             /* STAT_InIgmpGeneralQuery */
        inMldLeaves,                    /* STAT_InMldLeaves */
        inIgmpLeaves,          			/* STAT_InIgmpInterfaceLeaves */
        inIgmpJoinsSuccess,             /* STAT_InIgmpJoinsSuccess */
        inIgmpJoinsFail,                /* STAT_InIgmpJoinsFail */
        inMldJoinsSuccess,              /* STAT_InMldJoinsSuccess */
        inMldJoinsFail,                 /* STAT_InMldJoinsFail */
        inReportSuppressionDrop,        /* STAT_InReportSuppressionDrop */
        inLeaveSuppressionDrop,         /* STAT_InLeaveSuppressionDrop */
        outIgmpReports,                 /* STAT_OutIgmpReports */
        outIgmpLeaves,                  /* STAT_OutIgmpLeaves */
        outIgmpGeneralQuery,            /* STAT_OutIgmpGeneralQuery */
        outIgmpSpecificQuery,           /* STAT_OutIgmpSpecificQuery */
        outMldReports,                  /* STAT_OutMldReports */
        outMldLeaves,                   /* STAT_OutMldLeaves */
        outMldGeneralQuery,             /* STAT_OutMldGeneralQuery */
        outMldSpecificQuery,            /* STAT_OutMldSpecificQuery */
        inKnownMulticastPkts,           /* STAT_InKnownMulticastPkts */
        ifInMulticastPkts,              /* STAT_IfInMulticastPkts */
        ifInBroadcastPkts,              /* STAT_IfInBroadcastPkts */
    };

    if(cnt_idx >= STAT_PORT_CNTR_END)
        return RT_ERR_STAT_INVALID_PORT_CNTR;

    if(mib_asic_idx[cnt_idx] == MIB_NOT_SUPPORT)
        return RT_ERR_CHIP_NOT_SUPPORTED;

    *pMib_idx = mib_asic_idx[cnt_idx];
    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_stat_port_get
 * Description:
 *      Get per port MIB counter by index
 * Input:
 *      port        - port id.
 *      cntr_idx    - port counter index.
 * Output:
 *      pCntr - MIB retrived counter.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 * Note:
 *      Get per port MIB counter by index definition.
 */
int rtk_stat_port_get(unsigned int port, rtk_stat_port_type_t cntr_idx, rtk_stat_counter_t *pCntr)
{
    int       ret_val;
    RTL8367B_MIBCOUNTER mib_idx;
    rtk_stat_counter_t  second_cnt;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if (cntr_idx>=STAT_PORT_CNTR_END)
        return RT_ERR_STAT_INVALID_PORT_CNTR;

    if((ret_val = _get_asic_mib_idx(cntr_idx, &mib_idx)) != RT_ERR_OK)
        return ret_val;

    if(mib_idx == MIB_NOT_SUPPORT)
        return RT_ERR_CHIP_NOT_SUPPORTED;

    if ((ret_val = rtl8367b_getAsicMIBsCounter(port, mib_idx, pCntr)) != RT_ERR_OK)
        return ret_val;

    if(cntr_idx == STAT_EtherStatsMulticastPkts)
    {
        if((ret_val = _get_asic_mib_idx(STAT_IfOutMulticastPkts, &mib_idx)) != RT_ERR_OK)
            return ret_val;

        if((ret_val = rtl8367b_getAsicMIBsCounter(port, mib_idx, &second_cnt)) != RT_ERR_OK)
            return ret_val;

        *pCntr += second_cnt;
    }

    if(cntr_idx == STAT_EtherStatsBroadcastPkts)
    {
        if((ret_val = _get_asic_mib_idx(STAT_IfOutBroadcastPkts, &mib_idx)) != RT_ERR_OK)
            return ret_val;

        if((ret_val = rtl8367b_getAsicMIBsCounter(port, mib_idx, &second_cnt)) != RT_ERR_OK)
            return ret_val;

        *pCntr += second_cnt;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_stat_port_getAll
 * Description:
 *      Get all counters of one specified port in the specified device.
 * Input:
 *      port - port id.
 * Output:
 *      pPort_cntrs - buffer pointer of counter value.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT 		- Invalid input parameters.
 * Note:
 *      Get all MIB counters of one port.
 */
int rtk_stat_port_getAll(unsigned int port, rtk_stat_port_cntr_t *pPort_cntrs)
{
    int ret_val;
    unsigned int mibIndex;
    unsigned long long mibCounter;
    unsigned int *accessPtr;
    /* address offset to MIBs counter */
    const unsigned short mibLength[STAT_PORT_CNTR_END]= {
        2,1,1,1,1,1,1,1,1,
        2,1,1,1,1,1,1,1,1,1,1,
        2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    accessPtr = (unsigned int*)pPort_cntrs;
    for (mibIndex=0;mibIndex<STAT_PORT_CNTR_END;mibIndex++)
    {
        if ((ret_val = rtk_stat_port_get(port, mibIndex, &mibCounter)) != RT_ERR_OK)
        {
            if (ret_val == RT_ERR_CHIP_NOT_SUPPORTED)
                mibCounter = 0;
            else
                return ret_val;
        }

        if (2 == mibLength[mibIndex])
            *(unsigned long long*)accessPtr = mibCounter;
        else if (1 == mibLength[mibIndex])
            *accessPtr = mibCounter;
        else
            return RT_ERR_FAILED;

        accessPtr+=mibLength[mibIndex];
    }

    return RT_ERR_OK;
}

#endif

/* Function Name:
 *      rtk_stat_logging_counterCfg_set
 * Description:
 *      Set the type and mode of Logging Counter
 * Input:
 *      idx     - The index of Logging Counter. Should be even number only.(0,2,4,6,8.....30)
 *      mode    - 32 bits or 64 bits mode
 *      type    - Packet counter or byte counter
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_OUT_OF_RANGE - Out of range.
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT 		- Invalid input parameters.
 * Note:
 *      Set the type and mode of Logging Counter.
 */
int rtk_stat_logging_counterCfg_set(unsigned int idx, rtk_logging_counter_mode_t mode, rtk_logging_counter_type_t type)
{
    int ret_val;

    if(idx > RTL8367B_MIB_MAX_LOG_CNT_IDX)
        return RT_ERR_OUT_OF_RANGE;

    if((idx % 2) == 1)
        return RT_ERR_INPUT;

    if(mode >= LOGGING_MODE_END)
        return RT_ERR_OUT_OF_RANGE;

    if(type >= LOGGING_TYPE_END)
        return RT_ERR_OUT_OF_RANGE;

    if((ret_val = rtl8367b_setAsicMIBsLoggingType((idx / 2), (unsigned int)type)) != RT_ERR_OK)
        return ret_val;

    if((ret_val = rtl8367b_setAsicMIBsLoggingMode((idx / 2), (unsigned int)mode)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_stat_logging_counterCfg_get
 * Description:
 *      Get the type and mode of Logging Counter
 * Input:
 *      idx     - The index of Logging Counter. Should be even number only.(0,2,4,6,8.....30)
 * Output:
 *      pMode   - 32 bits or 64 bits mode
 *      pType   - Packet counter or byte counter
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_OUT_OF_RANGE - Out of range.
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_NULL_POINTER - NULL Pointer
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT 		- Invalid input parameters.
 * Note:
 *      Get the type and mode of Logging Counter.
 */
int rtk_stat_logging_counterCfg_get(unsigned int idx, rtk_logging_counter_mode_t *pMode, rtk_logging_counter_type_t *pType)
{
    int   ret_val;
    unsigned int      type, mode;

    if(idx > RTL8367B_MIB_MAX_LOG_CNT_IDX)
        return RT_ERR_OUT_OF_RANGE;

    if((idx % 2) == 1)
        return RT_ERR_INPUT;

    if(pMode == NULL)
        return RT_ERR_NULL_POINTER;

    if(pType == NULL)
        return RT_ERR_NULL_POINTER;

    if((ret_val = rtl8367b_getAsicMIBsLoggingType((idx / 2), &type)) != RT_ERR_OK)
        return ret_val;

    if((ret_val = rtl8367b_getAsicMIBsLoggingMode((idx / 2), &mode)) != RT_ERR_OK)
        return ret_val;

    *pMode = (rtk_logging_counter_mode_t)mode;
    *pType = (rtk_logging_counter_type_t)type;

    return RT_ERR_OK;
}


/* Function Name:
 *      rtk_stat_logging_counter_reset
 * Description:
 *      Reset Logging Counter
 * Input:
 *      idx     - The index of Logging Counter. (0~31)
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_OUT_OF_RANGE - Out of range.
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 * Note:
 *      Reset Logging Counter.
 */
int rtk_stat_logging_counter_reset(unsigned int idx)
{
    int   ret_val;

    if(idx > RTL8367B_MIB_MAX_LOG_CNT_IDX)
        return RT_ERR_OUT_OF_RANGE;

    if((ret_val = rtl8367b_setAsicMIBsResetLoggingCounter(idx)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_stat_logging_counter_get
 * Description:
 *      Get Logging Counter
 * Input:
 *      idx     - The index of Logging Counter. (0~31)
 * Output:
 *      pCnt    - Logging counter value
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_OUT_OF_RANGE - Out of range.
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 * Note:
 *      Get Logging Counter.
 */
int rtk_stat_logging_counter_get(unsigned int idx, unsigned int *pCnt)
{
    int   ret_val;

    if(idx > RTL8367B_MIB_MAX_LOG_CNT_IDX)
        return RT_ERR_OUT_OF_RANGE;

    if((ret_val = rtl8367b_getAsicMIBsLogCounter(idx, pCnt)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_int_polarity_set
 * Description:
 *      Set interrupt polarity configuration.
 * Input:
 *      type - Interruptpolarity type.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT 		- Invalid input parameters.
 * Note:
 *      The API can set interrupt polarity configuration.
 */
int rtk_int_polarity_set(rtk_int_polarity_t type)
{
    int ret_val;

    if ((ret_val = rtl8367b_setAsicInterruptPolarity(type)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_int_polarity_get
 * Description:
 *      Get interrupt polarity configuration.
 * Input:
 *      None
 * Output:
 *      pType - Interruptpolarity type.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 * Note:
 *      The API can get interrupt polarity configuration.
 */
int rtk_int_polarity_get(rtk_int_polarity_t *pType)
{
    int ret_val;

    if ((ret_val = rtl8367b_getAsicInterruptPolarity(pType)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_int_control_set
 * Description:
 *      Set interrupt trigger status configuration.
 * Input:
 *      type - Interrupt type.
 *      enable - Interrupt status.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT 		- Invalid input parameters.
 *      RT_ERR_ENABLE 		- Invalid enable input.
 * Note:
 *      The API can set interrupt status configuration.
 *      The interrupt trigger status is shown in the following:
 *      - INT_TYPE_LINK_STATUS
 *      - INT_TYPE_METER_EXCEED
 *      - INT_TYPE_LEARN_LIMIT
 *      - INT_TYPE_LINK_SPEED
 *      - INT_TYPE_CONGEST
 *      - INT_TYPE_GREEN_FEATURE
 *      - INT_TYPE_LOOP_DETECT
 *      - INT_TYPE_8051,
 *      - INT_TYPE_CABLE_DIAG,
 *      - INT_TYPE_ACL,
 *      - INT_TYPE_UPS,
 *      - INT_TYPE_SLIENT
 */
int rtk_int_control_set(rtk_int_type_t type, rtk_enable_t enable)
{
    int ret_val;
    unsigned int mask;

    if (type>=INT_TYPE_END)
        return RT_ERR_INPUT;

    if ((ret_val = rtl8367b_getAsicInterruptMask(&mask)) != RT_ERR_OK)
        return ret_val;

    if (ENABLED == enable)
        mask = mask | (1<<type);
    else if (DISABLED == enable)
        mask = mask & ~(1<<type);
    else
        return RT_ERR_INPUT;

    if ((ret_val = rtl8367b_setAsicInterruptMask(mask)) != RT_ERR_OK)
        return ret_val;


    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_int_control_get
 * Description:
 *      Get interrupt trigger status configuration.
 * Input:
 *      type - Interrupt type.
 * Output:
 *      pEnable - Interrupt status.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT 		- Invalid input parameters.
 * Note:
 *      The API can get interrupt status configuration.
 *      The interrupt trigger status is shown in the following:
 *      - INT_TYPE_LINK_STATUS
 *      - INT_TYPE_METER_EXCEED
 *      - INT_TYPE_LEARN_LIMIT
 *      - INT_TYPE_LINK_SPEED
 *      - INT_TYPE_CONGEST
 *      - INT_TYPE_GREEN_FEATURE
 *      - INT_TYPE_LOOP_DETECT
 *      - INT_TYPE_8051,
 *      - INT_TYPE_CABLE_DIAG,
 *      - INT_TYPE_ACL,
 *      - INT_TYPE_UPS,
 *      - INT_TYPE_SLIENT
 */
int rtk_int_control_get(rtk_int_type_t type, rtk_enable_t *pEnable)
{
    int ret_val;
    unsigned int mask;

    if ((ret_val = rtl8367b_getAsicInterruptMask(&mask)) != RT_ERR_OK)
        return ret_val;

    if (0 == (mask&(1<<type)))
        *pEnable=DISABLED;
    else
        *pEnable=ENABLED;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_int_status_set
 * Description:
 *      Set interrupt trigger status to clean.
 * Input:
 *      None
 * Output:
 *      pStatusMask - Interrupt status bit mask.
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 *      RT_ERR_INPUT - Invalid input parameters.
 * Note:
 *      The API can clean interrupt trigger status when interrupt happened.
 *      The interrupt trigger status is shown in the following:
 *      - INT_TYPE_LINK_STATUS    (value[0] (Bit0))
 *      - INT_TYPE_METER_EXCEED   (value[0] (Bit1))
 *      - INT_TYPE_LEARN_LIMIT    (value[0] (Bit2))
 *      - INT_TYPE_LINK_SPEED     (value[0] (Bit3))
 *      - INT_TYPE_CONGEST        (value[0] (Bit4))
 *      - INT_TYPE_GREEN_FEATURE  (value[0] (Bit5))
 *      - INT_TYPE_LOOP_DETECT    (value[0] (Bit6))
 *      - INT_TYPE_8051           (value[0] (Bit7))
 *      - INT_TYPE_CABLE_DIAG     (value[1] (Bit0))
 *      - INT_TYPE_ACL            (value[1] (Bit1))
 *      - INT_TYPE_UPS            (value[1] (Bit2))
 *      - INT_TYPE_SLIENT         (value[1] (Bit3))
 *      The status will be cleared after execute this API.
 */
int rtk_int_status_set(rtk_int_status_t statusMask)
{
    int ret_val;

    if ((ret_val = rtl8367b_setAsicInterruptStatus((unsigned int)((statusMask.value[1] << 8) | statusMask.value[0])))!=RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_int_status_get
 * Description:
 *      Get interrupt trigger status.
 * Input:
 *      None
 * Output:
 *      pStatusMask - Interrupt status bit mask.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT 		- Invalid input parameters.
 * Note:
 *      The API can get interrupt trigger status when interrupt happened.
 *      The interrupt trigger status is shown in the following:
 *      - INT_TYPE_LINK_STATUS    (value[0] (Bit0))
 *      - INT_TYPE_METER_EXCEED   (value[0] (Bit1))
 *      - INT_TYPE_LEARN_LIMIT    (value[0] (Bit2))
 *      - INT_TYPE_LINK_SPEED     (value[0] (Bit3))
 *      - INT_TYPE_CONGEST        (value[0] (Bit4))
 *      - INT_TYPE_GREEN_FEATURE  (value[0] (Bit5))
 *      - INT_TYPE_LOOP_DETECT    (value[0] (Bit6))
 *      - INT_TYPE_8051           (value[0] (Bit7))
 *      - INT_TYPE_CABLE_DIAG     (value[1] (Bit0))
 *      - INT_TYPE_ACL            (value[1] (Bit1))
 *      - INT_TYPE_UPS            (value[1] (Bit2))
 *      - INT_TYPE_SLIENT         (value[1] (Bit3))
 *
 */
int rtk_int_status_get(rtk_int_status_t* pStatusMask)
{
    int   ret_val;
    unsigned int          ims_mask;

    if ((ret_val = rtl8367b_getAsicInterruptStatus(&ims_mask)) != RT_ERR_OK)
        return ret_val;

    pStatusMask->value[0] = (ims_mask & 0x000000FF);
    pStatusMask->value[1] = ((ims_mask & 0x0000FF00) >> 8);

    return RT_ERR_OK;
}

#define ADV_NOT_SUPPORT (0xFFFF)
static int _rtk_int_Advidx_get(rtk_int_advType_t adv_type, unsigned int *pAsic_idx)
{
    unsigned int asic_idx[ADV_END] =
    {
        INTRST_L2_LEARN,
        INTRST_SPEED_CHANGE,
        INTRST_SPECIAL_CONGESTION,
        INTRST_PORT_LINKDOWN,
        INTRST_PORT_LINKUP,
        INTRST_METER0_15,
        INTRST_METER16_31,
        ADV_NOT_SUPPORT,
        ADV_NOT_SUPPORT,
        INTRST_RLDP_LOOPED,
        INTRST_RLDP_RELEASED,
    };

    if(adv_type >= ADV_END)
        return RT_ERR_INPUT;

    if(asic_idx[adv_type] == ADV_NOT_SUPPORT)
        return RT_ERR_CHIP_NOT_SUPPORTED;

    *pAsic_idx = asic_idx[adv_type];
    return RT_ERR_OK;
}
/* Function Name:
 *      rtk_int_advanceInfo_get
 * Description:
 *      Get interrupt advanced information.
 * Input:
 *      adv_type - Advanced interrupt type.
 * Output:
 *      info - Information per type.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT 		- Invalid input parameters.
 * Note:
 *      This API can get advanced information when interrupt happened.
 *      The status will be cleared after execute this API.
 */
int rtk_int_advanceInfo_get(rtk_int_advType_t adv_type, unsigned int *info)
{
    int   ret_val;
    unsigned int          asic_idx;

    if(adv_type >= ADV_END)
        return RT_ERR_INPUT;

    if((ret_val = _rtk_int_Advidx_get(adv_type, &asic_idx)) != RT_ERR_OK)
        return ret_val;

    if((ret_val = rtl8367b_getAsicInterruptRelatedStatus(asic_idx, info)) != RT_ERR_OK)
        return ret_val;

    if((ret_val = rtl8367b_setAsicInterruptRelatedStatus(asic_idx, 0xFFFF)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_led_enable_set
 * Description:
 *      Set Led enable congiuration
 * Input:
 *      group       - LED group id.
 *      portmask    - LED enable port mask.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT 		- Invalid input parameters.
 * Note:
 *      The API can be used to enable LED per port per group.
 */
int rtk_led_enable_set(rtk_led_group_t group, rtk_portmask_t portmask)
{
    int ret_val;

    if (group >= LED_GROUP_END)
        return RT_ERR_INPUT;

    if (portmask.bits[0] >= (1 << (RTK_PHY_ID_MAX + 1)))
        return RT_ERR_INPUT;

    if ((ret_val = rtl8367b_setAsicLedGroupEnable(group, portmask.bits[0])) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_led_enable_get
 * Description:
 *      Get Led enable congiuration
 * Input:
 *      group - LED group id.
 * Output:
 *      pPortmask - LED enable port mask.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT 		- Invalid input parameters.
 * Note:
 *      The API can be used to get LED enable status.
 */
int rtk_led_enable_get(rtk_led_group_t group, rtk_portmask_t *pPortmask)
{
    int ret_val;

    if (group >= LED_GROUP_END)
        return RT_ERR_INPUT;

    if ((ret_val = rtl8367b_getAsicLedGroupEnable(group, &(pPortmask->bits[0]))) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;

}

/* Function Name:
 *      rtk_led_operation_set
 * Description:
 *      Set Led operation mode
 * Input:
 *      mode - LED operation mode.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT 		- Invalid input parameters.
 * Note:
 *      The API can set Led operation mode.
 *      The modes that can be set are as following:
 *      - LED_OP_SCAN,
 *      - LED_OP_PARALLEL,
 *      - LED_OP_SERIAL,
 */
int rtk_led_operation_set(rtk_led_operation_t mode)
{
    int ret_val;
    unsigned int regData;

    if ( mode >= LED_OP_END)
      return RT_ERR_INPUT;

    if ( mode == LED_OP_SCAN)
      return RT_ERR_CHIP_NOT_SUPPORTED;

    switch (mode)
    {
        case LED_OP_PARALLEL:
            regData = LEDOP_PARALLEL;
            break;
        case LED_OP_SERIAL:
            regData = LEDOP_SERIAL;
            break;
        default:
            regData = 0;
            break;
    }

    if ((ret_val = rtl8367b_setAsicLedOperationMode(regData)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_led_operation_get
 * Description:
 *      Get Led operation mode
 * Input:
 *      None
 * Output:
 *      pMode - Support LED operation mode.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT 		- Invalid input parameters.
 * Note:
 *      The API can get Led operation mode.
 *      The modes that can be set are as following:
 *      - LED_OP_SCAN,
 *      - LED_OP_PARALLEL,
 *      - LED_OP_SERIAL,
 */
int rtk_led_operation_get(rtk_led_operation_t *pMode)
{
    int ret_val;
    unsigned int regData;

    if ((ret_val = rtl8367b_getAsicLedOperationMode(&regData)) != RT_ERR_OK)
        return ret_val;

    if (regData == LEDOP_SERIAL)
        *pMode = LED_OP_SERIAL;
    else if (regData ==LEDOP_PARALLEL)
        *pMode = LED_OP_PARALLEL;
    else
       return RT_ERR_FAILED;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_led_mode_set
 * Description:
 *      Set Led to congiuration mode
 * Input:
 *      mode - Support LED mode.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT 		- Invalid input parameters.
 * Note:
 *      There are three LED groups for each port for indicating information about dedicated port.
 *      LED groups are set to indicate different information of port in different mode.
 *
 *      (0) Mode0
 *          - LED0-Link, Activity Indicator. Low for link established. Link/Act Blinks every 43ms when the corresponding port is transmitting or receiving.
 *          - LED1-1000Mb/s Speed Indicator. Low for 1000Mb/s.
 *          - LED2-100Mb/s Speed Indicator. Low for 100Mb/s.
 *
 *      (1) Mode1
 *          - LED0-1000Mb/s Speed/Activity Indicator. Low for 1000Mb/s. Blinks every 43ms when the corresponding port is transmitting or receiving.
 *          - LED1-100Mb/s Speed/Activity Indicator. Low for 100Mb/s. Blinks every 43ms when the corresponding port is transmitting or receiving.
 *          - LED2-10Mb/s Speed/Activity Indicator. Low for 10Mb/s. Blinks every 43ms when the corresponding port is transmitting or receiving.
 *
 *      (2) Mode2
 *          - LED0-Collision, Full duplex Indicator. Blinking every 43ms when collision happens. Low for full duplex, and high for half duplex mode.
 *          - LED1-1000Mb/s Speed/Activity Indicator. Low for 1000Mb/s. Blinks every 43ms when the corresponding port is transmitting or receiving.
 *          - LED2-10/100Mb/s Speed/Activity Indicator. Low for 10/100Mb/s. Blinks every 43ms when the corresponding port is transmitting or receiving.
 *
 *      (3) Mode3
 *          - LED0-10Mb/s Speed/Activity Indicator. Low for 10Mb/s. Blinks every 43ms when the corresponding port is transmitting or receiving.
 *          - LED1-1000Mb/s Speed/Activity Indicator. Low for 1000Mb/s. Blinks every 43ms when the corresponding port is transmitting or receiving.
 *          - LED2-100Mb/s Speed/Activity Indicator. Low for 100Mb/s. Blinks every 43ms when the corresponding port is transmitting or receiving.
 */

int rtk_led_mode_set(rtk_led_mode_t mode)
{
    int ret_val;

    if (mode >= LED_MODE_END)
        return RT_ERR_FAILED;

    if ((ret_val = rtl8367b_setAsicLedGroupMode(mode)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_led_mode_get
 * Description:
 *      Get Led to congiuration mode
 * Input:
 *      None
 * Output:
 *      pMode - Support LED mode.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT 		- Invalid input parameters.
 * Note:
 *      There are three LED groups for each port for indicating information about dedicated port.
 *      LED groups is set to indicate different information of port in different mode.
 */
int rtk_led_mode_get(rtk_led_mode_t *pMode)
{
    int ret_val;

    if ((ret_val = rtl8367b_getAsicLedGroupMode(pMode)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;

}

/* Function Name:
 *      rtk_led_modeForce_set
 * Description:
 *      Set Led group to congiuration force mode
 * Input:
 *      group   - Support LED group id.
 *      mode    - Support LED force mode.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT 		- Invalid input parameters.
 * Note:
 *      The API can force all Leds in the same group to one force mode.
 *      The force modes that can be set are as following:
 *      - LED_FORCE_NORMAL,
 *      - LED_FORCE_BLINK,
 *      - LED_FORCE_OFF,
 *      - LED_FORCE_ON.
 */
int rtk_led_modeForce_set(rtk_led_group_t group, rtk_led_force_mode_t mode)
{
    int ret_val;
    unsigned int port;

    if (group >= LED_GROUP_END)
        return RT_ERR_INPUT;

    if (mode >= LED_FORCE_END)
        return RT_ERR_NOT_ALLOWED;

    for(port = 0; port <= RTK_PORT_ID_MAX; port++)
    {
        if ((ret_val = rtl8367b_setAsicForceLed(port, group, mode)) != RT_ERR_OK)
            return ret_val;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_led_modeForce_get
 * Description:
 *      Get Led group to congiuration force mode
 * Input:
 *      group - Support LED group id.
 *      pMode - Support LED force mode.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT 		- Invalid input parameters.
 * Note:
 *      The API can get forced Led group mode.
 *      The force modes that can be set are as following:
 *      - LED_FORCE_NORMAL,
 *      - LED_FORCE_BLINK,
 *      - LED_FORCE_OFF,
 *      - LED_FORCE_ON.
 */
int rtk_led_modeForce_get(rtk_led_group_t group, rtk_led_force_mode_t *pMode)
{
    int ret_val;

    if ((ret_val = rtl8367b_getAsicForceLed(0, group, pMode)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_led_blinkRate_set
 * Description:
 *      Set LED blinking rate
 * Input:
 *      blinkRate - blinking rate.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT 		- Invalid input parameters.
 * Note:
 *      ASIC support 6 types of LED blinking rates at 43ms, 84ms, 120ms, 170ms, 340ms and 670ms.
 */
int rtk_led_blinkRate_set(rtk_led_blink_rate_t blinkRate)
{
    int ret_val;

    if (blinkRate >= LEDBLINKRATE_END)
        return RT_ERR_FAILED;

    if ((ret_val = rtl8367b_setAsicLedBlinkRate(blinkRate)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_led_blinkRate_get
 * Description:
 *      Get LED blinking rate at mode 0 to mode 3
 * Input:
 *      None
 * Output:
 *      pBlinkRate - blinking rate.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT 		- Invalid input parameters.
 * Note:
 *      There are  6 types of LED blinking rates at 43ms, 84ms, 120ms, 170ms, 340ms and 670ms.
 */
int rtk_led_blinkRate_get(rtk_led_blink_rate_t *pBlinkRate)
{
    int ret_val;

    if ((ret_val = rtl8367b_getAsicLedBlinkRate(pBlinkRate)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_led_groupConfig_set
 * Description:
 *      Set per group Led to congiuration mode
 * Input:
 *      group   - LED group.
 *      config  - LED configuration
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT 		- Invalid input parameters.
 * Note:
 *      The API can set LED indicated information configuration for each LED group with 1 to 1 led mapping to each port.
 *      - Definition  LED Statuses      Description
 *      - 0000        LED_Off           LED pin Tri-State.
 *      - 0001        Dup/Col           Collision, Full duplex Indicator.
 *      - 0010        Link/Act          Link, Activity Indicator.
 *      - 0011        Spd1000           1000Mb/s Speed Indicator.
 *      - 0100        Spd100            100Mb/s Speed Indicator.
 *      - 0101        Spd10             10Mb/s Speed Indicator.
 *      - 0110        Spd1000/Act       1000Mb/s Speed/Activity Indicator.
 *      - 0111        Spd100/Act        100Mb/s Speed/Activity Indicator.
 *      - 1000        Spd10/Act         10Mb/s Speed/Activity Indicator.
 *      - 1001        Spd100 (10)/Act   10/100Mb/s Speed/Activity Indicator.
 *      - 1010        LoopDetect        LoopDetect Indicator.
 *      - 1011        EEE               EEE Indicator.
 *      - 1100        Link/Rx           Link, Activity Indicator.
 *      - 1101        Link/Tx           Link, Activity Indicator.
 *      - 1110        Master            Link on Master Indicator.
 *      - 1111        Act               Activity Indicator. Low for link established.
 */
int rtk_led_groupConfig_set(rtk_led_group_t group, rtk_led_congig_t config)
{
    int ret_val;

    if (LED_GROUP_END <= group)
        return RT_ERR_FAILED;

    if (LED_CONFIG_END <= config)
        return RT_ERR_FAILED;

    if ((ret_val = rtl8367b_setAsicLedIndicateInfoConfig(group, config)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_led_groupConfig_get
 * Description:
 *      Get Led group congiuration mode
 * Input:
 *      group - LED group.
 * Output:
 *      pConfig - LED configuration.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT 		- Invalid input parameters.
 * Note:
 *       The API can get LED indicated information configuration for each LED group.
 */
int rtk_led_groupConfig_get(rtk_led_group_t group, rtk_led_congig_t *pConfig)
{
    int ret_val;

    if (LED_GROUP_END <= group)
        return RT_ERR_FAILED;

    if ((ret_val = rtl8367b_getAsicLedIndicateInfoConfig(group, pConfig)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_led_serialMode_set
 * Description:
 *      Set Led serial mode active congiuration
 * Input:
 *      active - LED group.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT 		- Invalid input parameters.
 * Note:
 *      The API can set LED serial mode active congiuration.
 */
int rtk_led_serialMode_set(rtk_led_active_t active)
{
    int ret_val;

    if ( active >= LED_ACTIVE_END)
        return RT_ERR_INPUT;

     if ((ret_val = rtl8367b_setAsicLedSerialModeConfig(active,1))!=RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_led_serialMode_get
 * Description:
 *      Get Led group congiuration mode
 * Input:
 *      group - LED group.
 * Output:
 *      pConfig - LED configuration.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT 		- Invalid input parameters.
 * Note:
 *       The API can get LED serial mode active configuration.
 */
int rtk_led_serialMode_get(rtk_led_active_t *pActive)
{
    int ret_val;
    unsigned int regData;

    if ((ret_val = rtl8367b_getAsicLedSerialModeConfig(pActive,&regData))!=RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_filter_igrAcl_init
 * Description:
 *      ACL initialization function
 * Input:
 *      None
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_NULL_POINTER - Pointer pFilter_field or pFilter_cfg point to NULL.
 * Note:
 *      This function enable and intialize ACL function
 */
int rtk_filter_igrAcl_init(void)
{
    rtl8367b_acltemplate_t       aclTemp;
    unsigned int                 i, j;
    int          ret;

    if ((ret = rtk_filter_igrAcl_cfg_delAll()) != RT_ERR_OK)
        return ret;

    for(i = 0; i < RTL8367B_ACLTEMPLATENO; i++)
    {
        for(j = 0; j < RTL8367B_ACLRULEFIELDNO;j++)
            aclTemp.field[j] = filter_templateField[i][j];

        if ((ret = rtl8367b_setAsicAclTemplate(i, &aclTemp)) != RT_ERR_OK)
            return ret;
    }

    for(i = 0; i < RTL8367B_FIELDSEL_FORMAT_NUMBER; i++)
    {
        if ((ret = rtl8367b_setAsicFieldSelector(i, field_selector[i][0], field_selector[i][1])) != RT_ERR_OK)
            return ret;
    }

    for(i=0; i < RTL8367B_PORTNO; i++)
    {
        if ((ret = rtl8367b_setAsicAcl(i, TRUE)) != RT_ERR_OK)
            return ret;

        if ((ret = rtl8367b_setAsicAclUnmatchedPermit(i, TRUE)) != RT_ERR_OK)
            return ret;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_filter_igrAcl_field_add
 * Description:
 *      Add comparison rule to an ACL configuration
 * Input:
 *      pFilter_cfg     - The ACL configuration that this function will add comparison rule
 *      pFilter_field   - The comparison rule that will be added.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK              	- OK
 *      RT_ERR_FAILED          	- Failed
 *      RT_ERR_SMI             	- SMI access error
 *      RT_ERR_NULL_POINTER    	- Pointer pFilter_field or pFilter_cfg point to NULL.
 *      RT_ERR_INPUT 			- Invalid input parameters.
 * Note:
 *      This function add a comparison rule (*pFilter_field) to an ACL configuration (*pFilter_cfg).
 *      Pointer pFilter_cfg points to an ACL configuration structure, this structure keeps multiple ACL
 *      comparison rules by means of linked list. Pointer pFilter_field will be added to linked
 *      list keeped by structure that pFilter_cfg points to.
 */
int rtk_filter_igrAcl_field_add(rtk_filter_cfg_t* pFilter_cfg, rtk_filter_field_t* pFilter_field)
{
	unsigned int i;
	rtk_filter_field_t *tailPtr;

    if(NULL == pFilter_cfg || NULL == pFilter_field)
        return RT_ERR_NULL_POINTER;

    if(pFilter_field->fieldType >= FILTER_FIELD_END)
        return RT_ERR_ENTRY_INDEX;

	if(0 == pFilter_field->fieldTemplateNo)
	{
		pFilter_field->fieldTemplateNo = filter_fieldSize[pFilter_field->fieldType];

		for(i = 0; i < pFilter_field->fieldTemplateNo; i++)
		{
			pFilter_field->fieldTemplateIdx[i] = filter_fieldTemplateIndex[pFilter_field->fieldType][i];
		}
	}

    if(NULL == pFilter_cfg->fieldHead)
    {
        pFilter_cfg->fieldHead = pFilter_field;
    }
    else
    {
        if (pFilter_cfg->fieldHead->next == NULL)
        {
            pFilter_cfg->fieldHead->next = pFilter_field;
        }
        else
        {
            tailPtr = pFilter_cfg->fieldHead->next;
            while( tailPtr->next != NULL)
            {
                tailPtr = tailPtr->next;
            }
            tailPtr->next = pFilter_field;
        }
    }

    return RT_ERR_OK;
}

static int _rtk_filter_igrAcl_writeDataField(rtl8367b_aclrule *aclRule, rtk_filter_field_t *fieldPtr)
{
    unsigned int i, tempIdx,fieldIdx, ipValue, ipMask;
    unsigned int ip6addr[RTK_IPV6_ADDR_WORD_LENGTH];
    unsigned int ip6mask[RTK_IPV6_ADDR_WORD_LENGTH];

	for(i = 0; i < fieldPtr->fieldTemplateNo; i++)
	{
		tempIdx = (fieldPtr->fieldTemplateIdx[i] & 0xF0) >> 4;

		aclRule[tempIdx].valid = TRUE;
	}

    switch (fieldPtr->fieldType)
    {
    /* use DMAC structure as representative for mac structure */
    case FILTER_FIELD_DMAC:
    case FILTER_FIELD_SMAC:

		for(i = 0; i < fieldPtr->fieldTemplateNo; i++)
		{
			tempIdx = (fieldPtr->fieldTemplateIdx[i] & 0xF0) >> 4;
			fieldIdx = fieldPtr->fieldTemplateIdx[i] & 0x0F;

			aclRule[tempIdx].data_bits.field[fieldIdx] = fieldPtr->filter_pattern_union.mac.value.octet[5 - i*2] | (fieldPtr->filter_pattern_union.mac.value.octet[5 - (i*2 + 1)] << 8);
			aclRule[tempIdx].care_bits.field[fieldIdx] = fieldPtr->filter_pattern_union.mac.mask.octet[5 - i*2] | (fieldPtr->filter_pattern_union.mac.mask.octet[5 - (i*2 + 1)] << 8);
		}
   		break;
    case FILTER_FIELD_ETHERTYPE:
        for(i = 0; i < fieldPtr->fieldTemplateNo; i++)
        {
            tempIdx = (fieldPtr->fieldTemplateIdx[i] & 0xF0) >> 4;
			fieldIdx = fieldPtr->fieldTemplateIdx[i] & 0x0F;

            aclRule[tempIdx].data_bits.field[fieldIdx] = fieldPtr->filter_pattern_union.etherType.value;
            aclRule[tempIdx].care_bits.field[fieldIdx] = fieldPtr->filter_pattern_union.etherType.mask;
        }
        break;
    case FILTER_FIELD_IPV4_SIP:
    case FILTER_FIELD_IPV4_DIP:

		ipValue = fieldPtr->filter_pattern_union.sip.value;
		ipMask = fieldPtr->filter_pattern_union.sip.mask;

		for(i = 0; i < fieldPtr->fieldTemplateNo; i++)
		{
			tempIdx = (fieldPtr->fieldTemplateIdx[i] & 0xF0) >> 4;
			fieldIdx = fieldPtr->fieldTemplateIdx[i] & 0x0F;

			aclRule[tempIdx].data_bits.field[fieldIdx] = (ipValue & (0xFFFF << (i << 4))) >> (i << 4);
			aclRule[tempIdx].care_bits.field[fieldIdx] = (ipMask & (0xFFFF << (i << 4))) >> (i << 4);
		}
		break;
    case FILTER_FIELD_IPV4_TOS:
        for(i = 0; i < fieldPtr->fieldTemplateNo; i++)
        {
            tempIdx = (fieldPtr->fieldTemplateIdx[i] & 0xF0) >> 4;
            fieldIdx = fieldPtr->fieldTemplateIdx[i] & 0x0F;

            aclRule[tempIdx].data_bits.field[fieldIdx] = fieldPtr->filter_pattern_union.ipTos.value & 0xFF;
            aclRule[tempIdx].care_bits.field[fieldIdx] = fieldPtr->filter_pattern_union.ipTos.mask  & 0xFF;
        }
        break;
    case FILTER_FIELD_IPV4_PROTOCOL:
        for(i = 0; i < fieldPtr->fieldTemplateNo; i++)
        {
            tempIdx = (fieldPtr->fieldTemplateIdx[i] & 0xF0) >> 4;
            fieldIdx = fieldPtr->fieldTemplateIdx[i] & 0x0F;

            aclRule[tempIdx].data_bits.field[fieldIdx] = fieldPtr->filter_pattern_union.protocol.value & 0xFF;
            aclRule[tempIdx].care_bits.field[fieldIdx] = fieldPtr->filter_pattern_union.protocol.mask  & 0xFF;
        }
        break;
    case FILTER_FIELD_IPV6_SIPV6:
    case FILTER_FIELD_IPV6_DIPV6:
        for(i = 0; i < RTK_IPV6_ADDR_WORD_LENGTH; i++)
        {
            ip6addr[i] = fieldPtr->filter_pattern_union.sipv6.value.addr[i];
            ip6mask[i] = fieldPtr->filter_pattern_union.sipv6.mask.addr[i];
        }

		for(i = 0; i < fieldPtr->fieldTemplateNo; i++)
		{
            tempIdx = (fieldPtr->fieldTemplateIdx[i] & 0xF0) >> 4;
			fieldIdx = fieldPtr->fieldTemplateIdx[i] & 0x0F;

            if(i < 2)
            {
                aclRule[tempIdx].data_bits.field[fieldIdx] = ((ip6addr[0] & (0xFFFF << (i * 16))) >> (i * 16));
                aclRule[tempIdx].care_bits.field[fieldIdx] = ((ip6mask[0] & (0xFFFF << (i * 16))) >> (i * 16));
            }
            else
            {
                aclRule[tempIdx].data_bits.field[fieldIdx] = ((ip6addr[3] & (0xFFFF << ((i&1) * 16))) >> ((i&1) * 16));
                aclRule[tempIdx].care_bits.field[fieldIdx] = ((ip6mask[3] & (0xFFFF << ((i&1) * 16))) >> ((i&1) * 16));
            }
		}

		break;
	case FILTER_FIELD_CTAG:
    case FILTER_FIELD_STAG:

        for(i = 0; i < fieldPtr->fieldTemplateNo; i++)
        {
            tempIdx = (fieldPtr->fieldTemplateIdx[i] & 0xF0) >> 4;
            fieldIdx = fieldPtr->fieldTemplateIdx[i] & 0x0F;

            aclRule[tempIdx].data_bits.field[fieldIdx] = (fieldPtr->filter_pattern_union.l2tag.pri.value << 13) | (fieldPtr->filter_pattern_union.l2tag.cfi.value << 12) | fieldPtr->filter_pattern_union.l2tag.vid.value;
            aclRule[tempIdx].care_bits.field[fieldIdx] = (fieldPtr->filter_pattern_union.l2tag.pri.mask << 13) | (fieldPtr->filter_pattern_union.l2tag.cfi.mask << 12) | fieldPtr->filter_pattern_union.l2tag.vid.mask;
        }
        break;
	case FILTER_FIELD_IPV4_FLAG:

        for(i = 0; i < fieldPtr->fieldTemplateNo; i++)
        {
            tempIdx = (fieldPtr->fieldTemplateIdx[i] & 0xF0) >> 4;
            fieldIdx = fieldPtr->fieldTemplateIdx[i] & 0x0F;

            aclRule[tempIdx].data_bits.field[fieldIdx] &= 0x1FFF;
            aclRule[tempIdx].data_bits.field[fieldIdx] |= (fieldPtr->filter_pattern_union.ipFlag.xf.value << 15);
            aclRule[tempIdx].data_bits.field[fieldIdx] |= (fieldPtr->filter_pattern_union.ipFlag.df.value << 14);
            aclRule[tempIdx].data_bits.field[fieldIdx] |= (fieldPtr->filter_pattern_union.ipFlag.mf.value << 13);

            aclRule[tempIdx].care_bits.field[fieldIdx] &= 0x1FFF;
            aclRule[tempIdx].care_bits.field[fieldIdx] |= (fieldPtr->filter_pattern_union.ipFlag.xf.mask << 15);
            aclRule[tempIdx].care_bits.field[fieldIdx] |= (fieldPtr->filter_pattern_union.ipFlag.df.mask << 14);
            aclRule[tempIdx].care_bits.field[fieldIdx] |= (fieldPtr->filter_pattern_union.ipFlag.mf.mask << 13);
        }

        break;
	case FILTER_FIELD_IPV4_OFFSET:

        for(i = 0; i < fieldPtr->fieldTemplateNo; i++)
        {
            tempIdx = (fieldPtr->fieldTemplateIdx[i] & 0xF0) >> 4;
            fieldIdx = fieldPtr->fieldTemplateIdx[i] & 0x0F;

            aclRule[tempIdx].data_bits.field[fieldIdx] &= 0xE000;
            aclRule[tempIdx].data_bits.field[fieldIdx] |= fieldPtr->filter_pattern_union.inData.value;

            aclRule[tempIdx].care_bits.field[fieldIdx] &= 0xE000;
            aclRule[tempIdx].care_bits.field[fieldIdx] |= fieldPtr->filter_pattern_union.inData.mask;
        }

        break;

	case FILTER_FIELD_IPV6_TRAFFIC_CLASS:
        for(i = 0; i < fieldPtr->fieldTemplateNo; i++)
        {
            tempIdx = (fieldPtr->fieldTemplateIdx[i] & 0xF0) >> 4;
            fieldIdx = fieldPtr->fieldTemplateIdx[i] & 0x0F;


            aclRule[tempIdx].data_bits.field[fieldIdx] = fieldPtr->filter_pattern_union.inData.value << 4;
            aclRule[tempIdx].care_bits.field[fieldIdx] = fieldPtr->filter_pattern_union.inData.mask << 4;
        }
        break;
	case FILTER_FIELD_IPV6_NEXT_HEADER:
        for(i = 0; i < fieldPtr->fieldTemplateNo; i++)
        {
            tempIdx = (fieldPtr->fieldTemplateIdx[i] & 0xF0) >> 4;
            fieldIdx = fieldPtr->fieldTemplateIdx[i] & 0x0F;

            aclRule[tempIdx].data_bits.field[fieldIdx] = fieldPtr->filter_pattern_union.inData.value << 8;
            aclRule[tempIdx].care_bits.field[fieldIdx] = fieldPtr->filter_pattern_union.inData.mask << 8;
        }
        break;
    case FILTER_FIELD_TCP_SPORT:
        for(i = 0; i < fieldPtr->fieldTemplateNo; i++)
        {
            tempIdx = (fieldPtr->fieldTemplateIdx[i] & 0xF0) >> 4;
            fieldIdx = fieldPtr->fieldTemplateIdx[i] & 0x0F;

            aclRule[tempIdx].data_bits.field[fieldIdx] = fieldPtr->filter_pattern_union.tcpSrcPort.value;
            aclRule[tempIdx].care_bits.field[fieldIdx] = fieldPtr->filter_pattern_union.tcpSrcPort.mask;
        }
        break;
    case FILTER_FIELD_TCP_DPORT:
        for(i = 0; i < fieldPtr->fieldTemplateNo; i++)
        {
            tempIdx = (fieldPtr->fieldTemplateIdx[i] & 0xF0) >> 4;
            fieldIdx = fieldPtr->fieldTemplateIdx[i] & 0x0F;

            aclRule[tempIdx].data_bits.field[fieldIdx] = fieldPtr->filter_pattern_union.tcpDstPort.value;
            aclRule[tempIdx].care_bits.field[fieldIdx] = fieldPtr->filter_pattern_union.tcpDstPort.mask;
        }
        break;
	case FILTER_FIELD_TCP_FLAG:

        for(i = 0; i < fieldPtr->fieldTemplateNo; i++)
        {
            tempIdx = (fieldPtr->fieldTemplateIdx[i] & 0xF0) >> 4;
            fieldIdx = fieldPtr->fieldTemplateIdx[i] & 0x0F;

            aclRule[tempIdx].data_bits.field[fieldIdx] |= (fieldPtr->filter_pattern_union.tcpFlag.cwr.value << 7);
            aclRule[tempIdx].data_bits.field[fieldIdx] |= (fieldPtr->filter_pattern_union.tcpFlag.ece.value << 6);
            aclRule[tempIdx].data_bits.field[fieldIdx] |= (fieldPtr->filter_pattern_union.tcpFlag.urg.value << 5);
            aclRule[tempIdx].data_bits.field[fieldIdx] |= (fieldPtr->filter_pattern_union.tcpFlag.ack.value << 4);
            aclRule[tempIdx].data_bits.field[fieldIdx] |= (fieldPtr->filter_pattern_union.tcpFlag.psh.value << 3);
            aclRule[tempIdx].data_bits.field[fieldIdx] |= (fieldPtr->filter_pattern_union.tcpFlag.rst.value << 2);
            aclRule[tempIdx].data_bits.field[fieldIdx] |= (fieldPtr->filter_pattern_union.tcpFlag.syn.value << 1);
            aclRule[tempIdx].data_bits.field[fieldIdx] |= fieldPtr->filter_pattern_union.tcpFlag.fin.value;

            aclRule[tempIdx].care_bits.field[fieldIdx] |= (fieldPtr->filter_pattern_union.tcpFlag.cwr.mask << 7);
            aclRule[tempIdx].care_bits.field[fieldIdx] |= (fieldPtr->filter_pattern_union.tcpFlag.ece.mask << 6);
            aclRule[tempIdx].care_bits.field[fieldIdx] |= (fieldPtr->filter_pattern_union.tcpFlag.urg.mask << 5);
            aclRule[tempIdx].care_bits.field[fieldIdx] |= (fieldPtr->filter_pattern_union.tcpFlag.ack.mask << 4);
            aclRule[tempIdx].care_bits.field[fieldIdx] |= (fieldPtr->filter_pattern_union.tcpFlag.psh.mask << 3);
            aclRule[tempIdx].care_bits.field[fieldIdx] |= (fieldPtr->filter_pattern_union.tcpFlag.rst.mask << 2);
            aclRule[tempIdx].care_bits.field[fieldIdx] |= (fieldPtr->filter_pattern_union.tcpFlag.syn.mask << 1);
            aclRule[tempIdx].care_bits.field[fieldIdx] |= fieldPtr->filter_pattern_union.tcpFlag.fin.mask;
        }
        break;
    case FILTER_FIELD_UDP_SPORT:
        for(i = 0; i < fieldPtr->fieldTemplateNo; i++)
        {
            tempIdx = (fieldPtr->fieldTemplateIdx[i] & 0xF0) >> 4;
            fieldIdx = fieldPtr->fieldTemplateIdx[i] & 0x0F;

            aclRule[tempIdx].data_bits.field[fieldIdx] = fieldPtr->filter_pattern_union.udpSrcPort.value;
            aclRule[tempIdx].care_bits.field[fieldIdx] = fieldPtr->filter_pattern_union.udpSrcPort.mask;
        }
        break;
    case FILTER_FIELD_UDP_DPORT:
        for(i = 0; i < fieldPtr->fieldTemplateNo; i++)
        {
            tempIdx = (fieldPtr->fieldTemplateIdx[i] & 0xF0) >> 4;
            fieldIdx = fieldPtr->fieldTemplateIdx[i] & 0x0F;

            aclRule[tempIdx].data_bits.field[fieldIdx] = fieldPtr->filter_pattern_union.udpDstPort.value;
            aclRule[tempIdx].care_bits.field[fieldIdx] = fieldPtr->filter_pattern_union.udpDstPort.mask;
        }
        break;
	case FILTER_FIELD_ICMP_CODE:
        for(i = 0; i < fieldPtr->fieldTemplateNo; i++)
        {
            tempIdx = (fieldPtr->fieldTemplateIdx[i] & 0xF0) >> 4;
            fieldIdx = fieldPtr->fieldTemplateIdx[i] & 0x0F;

            aclRule[tempIdx].data_bits.field[fieldIdx] &= 0xFF00;
            aclRule[tempIdx].data_bits.field[fieldIdx] |= fieldPtr->filter_pattern_union.icmpCode.value;
            aclRule[tempIdx].care_bits.field[fieldIdx] &= 0xFF00;
            aclRule[tempIdx].care_bits.field[fieldIdx] |= fieldPtr->filter_pattern_union.icmpCode.mask;
        }
        break;
	case FILTER_FIELD_ICMP_TYPE:
        for(i = 0; i < fieldPtr->fieldTemplateNo; i++)
        {
            tempIdx = (fieldPtr->fieldTemplateIdx[i] & 0xF0) >> 4;
            fieldIdx = fieldPtr->fieldTemplateIdx[i] & 0x0F;

            aclRule[tempIdx].data_bits.field[fieldIdx] &= 0x00FF;
            aclRule[tempIdx].data_bits.field[fieldIdx] |= (fieldPtr->filter_pattern_union.icmpType.value << 8);
            aclRule[tempIdx].care_bits.field[fieldIdx] &= 0x00FF;
            aclRule[tempIdx].care_bits.field[fieldIdx] |= (fieldPtr->filter_pattern_union.icmpType.mask << 8);
        }
        break;
	case FILTER_FIELD_IGMP_TYPE:
        for(i = 0; i < fieldPtr->fieldTemplateNo; i++)
        {
            tempIdx = (fieldPtr->fieldTemplateIdx[i] & 0xF0) >> 4;
            fieldIdx = fieldPtr->fieldTemplateIdx[i] & 0x0F;

            aclRule[tempIdx].data_bits.field[fieldIdx] = (fieldPtr->filter_pattern_union.igmpType.value << 8);
            aclRule[tempIdx].care_bits.field[fieldIdx] = (fieldPtr->filter_pattern_union.igmpType.mask << 8);
        }
        break;
    case FILTER_FIELD_PATTERN_MATCH:
        for(i = 0; i < fieldPtr->fieldTemplateNo; i++)
        {
            tempIdx = (fieldPtr->fieldTemplateIdx[i] & 0xF0) >> 4;
            fieldIdx = fieldPtr->fieldTemplateIdx[i] & 0x0F;

            aclRule[tempIdx].data_bits.field[fieldIdx] = ((fieldPtr->filter_pattern_union.pattern.value[i/2] >> (16 * (i%2))) & 0x0000FFFF );
            aclRule[tempIdx].care_bits.field[fieldIdx] = ((fieldPtr->filter_pattern_union.pattern.mask[i/2] >> (16 * (i%2))) & 0x0000FFFF );
        }
        break;
    case FILTER_FIELD_VID_RANGE:
    case FILTER_FIELD_IP_RANGE:
    case FILTER_FIELD_PORT_RANGE:
    default:
		tempIdx = (fieldPtr->fieldTemplateIdx[0] & 0xF0) >> 4;
		fieldIdx = fieldPtr->fieldTemplateIdx[0] & 0x0F;

        aclRule[tempIdx].data_bits.field[fieldIdx] = fieldPtr->filter_pattern_union.inData.value;
        aclRule[tempIdx].care_bits.field[fieldIdx] = fieldPtr->filter_pattern_union.inData.mask;
        break;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_filter_igrAcl_cfg_add
 * Description:
 *      Add an ACL configuration to ASIC
 * Input:
 *      filter_id       - Start index of ACL configuration.
 *      pFilter_cfg     - The ACL configuration that this function will add comparison rule
 *      pFilter_action  - Action(s) of ACL configuration.
 * Output:
 *      ruleNum - number of rules written in acl table
 * Return:
 *      RT_ERR_OK              					- OK
 *      RT_ERR_FAILED          					- Failed
 *      RT_ERR_SMI             					- SMI access error
 *      RT_ERR_NULL_POINTER    					- Pointer pFilter_field or pFilter_cfg point to NULL.
 *      RT_ERR_INPUT 							- Invalid input parameters.
 *      RT_ERR_ENTRY_INDEX 						- Invalid filter_id .
 *      RT_ERR_NULL_POINTER 					- Pointer pFilter_action or pFilter_cfg point to NULL.
 *      RT_ERR_FILTER_INACL_ACT_NOT_SUPPORT 	- Action is not supported in this chip.
 *      RT_ERR_FILTER_INACL_RULE_NOT_SUPPORT 	- Rule is not supported.
 * Note:
 *      This function store pFilter_cfg, pFilter_action into ASIC. The starting
 *      index(es) is filter_id.
 */
int rtk_filter_igrAcl_cfg_add(unsigned int filter_id, rtk_filter_cfg_t* pFilter_cfg, rtk_filter_action_t* pFilter_action, rtk_filter_number_t *ruleNum)
{
    int               ret_val;
    unsigned int                  careTagData, careTagMask;
    unsigned int                  i,vidx, svidx, actType, ruleId;
    unsigned int                  aclActCtrl;
    unsigned int                  cpuPort;
    rtk_filter_field_t*         fieldPtr;
    rtl8367b_aclrule            aclRule[RTL8367B_ACLTEMPLATENO];
    rtl8367b_aclrule            tempRule;
    rtl8367b_acl_act_t          aclAct;
    unsigned int                  noRulesAdd;
    rtl8367b_vlanconfiguser     vlanMC;
    unsigned char                   active_portmsk;
    rtl8367b_user_vlan4kentry   vlan4K;
    rtl8367b_svlan_memconf_t    svlan_cfg;

    if(filter_id > RTL8367B_ACLRULEMAX )
        return RT_ERR_ENTRY_INDEX;

    if(NULL == pFilter_cfg)
        return RT_ERR_NULL_POINTER;

    if(NULL == pFilter_action )
        return RT_ERR_NULL_POINTER;

    fieldPtr = pFilter_cfg->fieldHead;

    /* init RULE */
    for(i = 0; i < RTL8367B_ACLTEMPLATENO; i++)
    {
        memset(&aclRule[i], 0, sizeof(rtl8367b_aclrule));

        aclRule[i].data_bits.type= i;
        aclRule[i].care_bits.type= 0x7;
    }

    while(NULL != fieldPtr)
    {
        _rtk_filter_igrAcl_writeDataField(aclRule, fieldPtr);

        fieldPtr = fieldPtr->next;
    }

	/*set care tag mask in User Defined Field 15*/
	/*Follow care tag should not be used while ACL template and User defined fields are fully control by system designer*/
    /*those advanced packet type care tag is used in default template design structure only*/
	careTagData = 0;
	careTagMask = 0;
        active_portmsk = 0;

	for(i = CARE_TAG_TCP; i < CARE_TAG_END; i++)
    {
		if(pFilter_cfg->careTag.tagType[i].mask)
			careTagMask = careTagMask | (1 << (i-CARE_TAG_TCP));

		if(pFilter_cfg->careTag.tagType[i].value)
			careTagData = careTagData | (1 << (i-CARE_TAG_TCP));
    }

	if(careTagData || careTagMask)
	{
		i = 0;
		while(i < RTL8367B_ACLTEMPLATENO)
		{
			if(aclRule[i].valid == 1 && filter_advanceCaretagField[i][0] == TRUE)
			{

				aclRule[i].data_bits.field[filter_advanceCaretagField[i][1]] = careTagData & 0xFFFF;
				aclRule[i].care_bits.field[filter_advanceCaretagField[i][1]] = careTagMask & 0xFFFF;
				break;
			}
			i++;
		}
		/*none of previous used template containing field 15*/
		if(i == RTL8367B_ACLTEMPLATENO)
		{
			i = 0;
			while(i <= RTL8367B_ACLTEMPLATENO)
			{
				if(filter_advanceCaretagField[i][0] == TRUE)
				{
					aclRule[i].data_bits.field[filter_advanceCaretagField[i][1]] = careTagData & 0xFFFF;
					aclRule[i].care_bits.field[filter_advanceCaretagField[i][1]] = careTagMask & 0xFFFF;
					aclRule[i].valid = 1;
					break;
				}
				i++;
			}
		}
	}

	/*Check rule number*/
	noRulesAdd = 0;
    for(i = 0; i < RTL8367B_ACLTEMPLATENO; i++)
    {
		if(1 == aclRule[i].valid)
		{
			noRulesAdd ++;
		}
    }

	*ruleNum = noRulesAdd;

	if((filter_id + noRulesAdd - 1) > RTL8367B_ACLRULEMAX)
	{
		return RT_ERR_ENTRY_INDEX;
	}

	/*set care tag mask in TAG Indicator*/
    careTagData = 0;
	careTagMask = 0;

    for(i = 0; i <= CARE_TAG_IPV6;i++)
    {
        if(0 == pFilter_cfg->careTag.tagType[i].mask )
        {
            careTagMask &=  ~(1 << i);
        }
        else
        {
            careTagMask |= (1 << i);
            if(0 == pFilter_cfg->careTag.tagType[i].value )
                careTagData &= ~(1 << i);
            else
                careTagData |= (1 << i);
        }
    }

    for(i = 0; i < RTL8367B_ACLTEMPLATENO; i++)
    {
        aclRule[i].data_bits.tag_exist = (careTagData) & ACL_RULE_CARETAG_MASK;
        aclRule[i].care_bits.tag_exist = (careTagMask) & ACL_RULE_CARETAG_MASK;
    }

    if(FILTER_FIELD_DATA_RANGE == pFilter_cfg->activeport.dataType)
    {

        if(pFilter_cfg->activeport.rangeStart >= RTL8367B_PORTNO || pFilter_cfg->activeport.rangeEnd >= RTL8367B_PORTNO
          || pFilter_cfg->activeport.rangeEnd > pFilter_cfg->activeport.rangeStart)
            return RT_ERR_INPUT;

        for(i = pFilter_cfg->activeport.rangeStart;i <= pFilter_cfg->activeport.rangeEnd; i++)
            active_portmsk |= 1 << i;

        for(i = 0; i < RTL8367B_ACLTEMPLATENO; i++)
        {
    		if(1 == aclRule[i].valid)
            {
                aclRule[0].data_bits.active_portmsk = active_portmsk;
                aclRule[0].care_bits.active_portmsk = 0xFF;
            }
        }
    }
    else if(FILTER_FIELD_DATA_MASK == pFilter_cfg->activeport.dataType )
    {
        if(pFilter_cfg->activeport.value >= (1 << RTL8367B_PORTNO) || pFilter_cfg->activeport.mask >= (1 << RTL8367B_PORTNO))
            return RT_ERR_INPUT;

        for(i = 0; i < RTL8367B_ACLTEMPLATENO; i++)
        {
    		if(1 == aclRule[i].valid)
    		{
    			aclRule[i].data_bits.active_portmsk = pFilter_cfg->activeport.value;
                aclRule[i].care_bits.active_portmsk = pFilter_cfg->activeport.mask;
    		}
        }
    }
    else
        return RT_ERR_INPUT;

    if(pFilter_cfg->invert >= FILTER_INVERT_END )
        return RT_ERR_INPUT;


	/*Last action gets high priority if actions are the same*/
    memset(&aclAct, 0, sizeof(rtl8367b_acl_act_t));
    aclActCtrl = 0;
    for(actType = 0; actType < FILTER_ENACT_END; actType ++)
    {
        if(pFilter_action->actEnable[actType])
        {
            switch (actType)
            {
            case FILTER_ENACT_INGRESS_CVLAN_INDEX:
                if(pFilter_action->filterIngressCvlanIdx > RTL8367B_CVIDXMAX)
                    return RT_ERR_INPUT;

                aclAct.cact = FILTER_ENACT_CVLAN_TYPE(FILTER_ENACT_CVLAN_INGRESS);
                aclAct.cvidx_cact = pFilter_action->filterIngressCvlanIdx;
                aclActCtrl |= FILTER_ENACT_CVLAN_MASK;
                break;
            case FILTER_ENACT_INGRESS_CVLAN_VID:
                if(pFilter_action->filterIngressCvlanVid > RTL8367B_VIDMAX)
                    return RT_ERR_INPUT;

				/*Search avalid vlan member configuration or create new one*/
				for(vidx = 0; vidx <= RTL8367B_CVIDXMAX; vidx ++)
				{
				    if((ret_val = rtl8367b_getAsicVlanMemberConfig(vidx, &vlanMC)) != RT_ERR_OK)
				        return ret_val;

					if(pFilter_action->filterIngressCvlanVid == vlanMC.evid)
						break;
				}

				/*Did not have existed matched VID, search free entries*/
				if(vidx == (RTL8367B_CVIDXMAX + 1))
				{
					for(vidx = 0; vidx <= RTL8367B_CVIDXMAX; vidx ++)
					{
					    if((ret_val = rtl8367b_getAsicVlanMemberConfig(vidx, &vlanMC)) != RT_ERR_OK)
					        return ret_val;

						if(0 == vlanMC.mbr && 0 == vlanMC.evid)
                        {
                            /* Empty entry, copy member and untag mask from 4K VLAN */
                            vlan4K.vid = pFilter_action->filterIngressCvlanVid;

                            if ((ret_val = rtl8367b_getAsicVlan4kEntry(&vlan4K)) != RT_ERR_OK)
                                return ret_val;

                            if(vlan4K.mbr == 0x00)
                                return RT_ERR_VLAN_EMPTY_ENTRY;

                            vlanMC.evid     = vlan4K.vid;
                            vlanMC.mbr      = vlan4K.mbr;
                            vlanMC.fid_msti = vlan4K.fid_msti;
                            vlanMC.meteridx = vlan4K.meteridx;
                            vlanMC.envlanpol= vlan4K.envlanpol;
                            vlanMC.vbpen    = vlan4K.vbpen;
                            vlanMC.vbpri    = vlan4K.vbpri;

                            if((ret_val = rtl8367b_setAsicVlanMemberConfig(vidx, &vlanMC)) != RT_ERR_OK)
                                return ret_val;

                            break;
                        }
					}

					if(vidx == (RTL8367B_CVIDXMAX + 1))
						return RT_ERR_INPUT;
				}

                aclAct.cact = FILTER_ENACT_CVLAN_TYPE(FILTER_ENACT_CVLAN_INGRESS);
                aclAct.cvidx_cact = vidx;
                aclActCtrl |= FILTER_ENACT_CVLAN_MASK;
                break;
            case FILTER_ENACT_CVLAN_INGRESS:
                if(pFilter_action->filterCvlanIdx > RTL8367B_CVIDXMAX)
                    return RT_ERR_INPUT;

                aclAct.cact = FILTER_ENACT_CVLAN_TYPE(actType);
                aclAct.cvidx_cact = pFilter_action->filterCvlanIdx;
                aclActCtrl |= FILTER_ENACT_CVLAN_MASK;
                break;
            case FILTER_ENACT_CVLAN_EGRESS:
                if(pFilter_action->filterCvlanIdx > RTL8367B_CVIDXMAX)
                    return RT_ERR_INPUT;

                aclAct.cact = FILTER_ENACT_CVLAN_TYPE(actType);
                aclAct.cvidx_cact = pFilter_action->filterCvlanIdx;
                aclActCtrl |= FILTER_ENACT_CVLAN_MASK;
                break;
             case FILTER_ENACT_CVLAN_SVID:

                aclAct.cact = FILTER_ENACT_CVLAN_TYPE(actType);
                aclActCtrl |= FILTER_ENACT_CVLAN_MASK;
                break;
             case FILTER_ENACT_POLICING_1:
                if(pFilter_action->filterPolicingIdx[1] >= (RTL8367B_METERNO * 2))
                    return RT_ERR_INPUT;

                aclAct.cact = FILTER_ENACT_CVLAN_TYPE(actType);
                aclAct.cvidx_cact = pFilter_action->filterPolicingIdx[1];
                aclActCtrl |= FILTER_ENACT_CVLAN_MASK;
                break;

            case FILTER_ENACT_EGRESS_SVLAN_INDEX:
                if(pFilter_action->filterEgressSvlanIdx > RTL8367B_SVIDXMAX )
                    return RT_ERR_INPUT;

                aclAct.sact = FILTER_ENACT_SVLAN_TYPE(FILTER_ENACT_SVLAN_EGRESS);
                aclAct.svidx_sact = pFilter_action->filterEgressSvlanIdx;
                aclActCtrl |= FILTER_ENACT_SVLAN_MASK;
                break;
            case FILTER_ENACT_SVLAN_INGRESS:
            case FILTER_ENACT_SVLAN_EGRESS:

                if(pFilter_action->filterSvlanVid > RTL8367B_VIDMAX)
                    return RT_ERR_INPUT;

                for(svidx = 0; svidx <= RTL8367B_SVIDXMAX; svidx++)
                {
                    if((ret_val = rtl8367b_getAsicSvlanMemberConfiguration(svidx, &svlan_cfg)) != RT_ERR_OK)
				        return ret_val;

                    if(pFilter_action->filterSvlanVid == svlan_cfg.vs_svid)
						break;
                }

                if(svidx == (RTL8367B_SVIDXMAX + 1))
                    return RT_ERR_INPUT;

                aclAct.sact = FILTER_ENACT_SVLAN_TYPE(actType);
				aclAct.svidx_sact = svidx;
                aclActCtrl |= FILTER_ENACT_SVLAN_MASK;
                break;
            case FILTER_ENACT_SVLAN_CVID:

                aclAct.sact = FILTER_ENACT_SVLAN_TYPE(actType);
                aclActCtrl |= FILTER_ENACT_SVLAN_MASK;
				break;
            case FILTER_ENACT_POLICING_2:
                if(pFilter_action->filterPolicingIdx[2] >= (RTL8367B_METERNO * 2))
                    return RT_ERR_INPUT;

                aclAct.sact = FILTER_ENACT_SVLAN_TYPE(actType);
                aclAct.svidx_sact = pFilter_action->filterPolicingIdx[2];
                aclActCtrl |= FILTER_ENACT_SVLAN_MASK;
                break;
            case FILTER_ENACT_POLICING_0:
                if(pFilter_action->filterPolicingIdx[0] >= (RTL8367B_METERNO * 2))
                    return RT_ERR_INPUT;

                aclAct.aclmeteridx = pFilter_action->filterPolicingIdx[0];
                aclActCtrl |= FILTER_ENACT_POLICING_MASK;
                break;
            case FILTER_ENACT_PRIORITY:
            case FILTER_ENACT_1P_REMARK:
                if(pFilter_action->filterPriority > RTL8367B_PRIMAX)
                    return RT_ERR_INPUT;

                aclAct.priact = FILTER_ENACT_PRI_TYPE(actType);
                aclAct.pridx = pFilter_action->filterPriority;
                aclActCtrl |= FILTER_ENACT_PRIORITY_MASK;
                break;
            case FILTER_ENACT_DSCP_REMARK:
                if(pFilter_action->filterPriority > RTL8367B_DSCPMAX)
                    return RT_ERR_INPUT;

                aclAct.priact = FILTER_ENACT_PRI_TYPE(actType);
                aclAct.pridx = pFilter_action->filterPriority;
                aclActCtrl |= FILTER_ENACT_PRIORITY_MASK;
                break;
            case FILTER_ENACT_POLICING_3:
                if(pFilter_action->filterPriority >= (RTL8367B_METERNO * 2))
                    return RT_ERR_INPUT;

                aclAct.priact = FILTER_ENACT_PRI_TYPE(actType);
                aclAct.pridx = pFilter_action->filterPolicingIdx[3];
                aclActCtrl |= FILTER_ENACT_PRIORITY_MASK;
                break;
            case FILTER_ENACT_DROP:

                aclAct.fwdact = FILTER_ENACT_FWD_TYPE(FILTER_ENACT_REDIRECT);
                aclAct.fwdpmask = 0;
                aclActCtrl |= FILTER_ENACT_FWD_MASK;
                break;
            case FILTER_ENACT_REDIRECT:
                if(pFilter_action->filterRedirectPortmask >= (1 << RTK_MAX_NUM_OF_PORT))
                    return RT_ERR_INPUT;

                aclAct.fwdact = FILTER_ENACT_FWD_TYPE(actType);
                aclAct.fwdpmask = pFilter_action->filterRedirectPortmask;
                aclActCtrl |= FILTER_ENACT_FWD_MASK;
                break;
            case FILTER_ENACT_ADD_DSTPORT:
                if(pFilter_action->filterAddDstPortmask >= (1 << RTK_MAX_NUM_OF_PORT))
                    return RT_ERR_INPUT;

                aclAct.fwdact = FILTER_ENACT_FWD_TYPE(actType);
                aclAct.fwdpmask = pFilter_action->filterAddDstPortmask;
                aclActCtrl |= FILTER_ENACT_FWD_MASK;
                break;
            case FILTER_ENACT_MIRROR:

                aclAct.fwdact = FILTER_ENACT_FWD_TYPE(actType);
                aclAct.fwdpmask = pFilter_action->filterAddDstPortmask;
                aclActCtrl |= FILTER_ENACT_FWD_MASK;
                break;
            case FILTER_ENACT_TRAP_CPU:

                aclAct.fwdact = FILTER_ENACT_FWD_TYPE(actType);
                aclActCtrl |= FILTER_ENACT_FWD_MASK;
                break;
            case FILTER_ENACT_COPY_CPU:
                if((ret_val = rtl8367b_getAsicCputagTrapPort(&cpuPort)) != RT_ERR_OK)
                    return ret_val;

                aclAct.fwdact = FILTER_ENACT_FWD_TYPE(FILTER_ENACT_MIRROR);
                aclAct.fwdpmask = 1 << cpuPort;
                aclActCtrl |= FILTER_ENACT_FWD_MASK;
                break;
            case FILTER_ENACT_INTERRUPT:

                aclAct.aclint = TRUE;
                aclActCtrl |= FILTER_ENACT_INTGPIO_MASK;
                break;
            case FILTER_ENACT_GPO:

                aclAct.gpio_en = TRUE;
                aclAct.gpio_pin = pFilter_action->filterPin;
                aclActCtrl |= FILTER_ENACT_INTGPIO_MASK;
                break;
            default:
                return RT_ERR_FILTER_INACL_ACT_NOT_SUPPORT;
            }
        }
    }


	/*check if free ACL rules are enough*/
    for(i = filter_id; i < (filter_id + noRulesAdd); i++)
    {
        if((ret_val = rtl8367b_getAsicAclRule(i, &tempRule)) != RT_ERR_OK )
            return ret_val;

        if(tempRule.valid == TRUE)
        {
            return RT_ERR_TBL_FULL;
        }
    }

	ruleId = 0;
    for(i = 0; i < RTL8367B_ACLTEMPLATENO; i++)
    {
        if(aclRule[i].valid == TRUE)
        {
            /* write ACL action control */
            if((ret_val = rtl8367b_setAsicAclActCtrl(filter_id + ruleId, aclActCtrl)) != RT_ERR_OK )
                return ret_val;
            /* write ACL action */
            if((ret_val = rtl8367b_setAsicAclAct(filter_id + ruleId, &aclAct)) != RT_ERR_OK )
                return ret_val;
            /* write ACL not */
            if((ret_val = rtl8367b_setAsicAclNot(filter_id + ruleId, pFilter_cfg->invert)) != RT_ERR_OK )
                return ret_val;
            /* write ACL rule */
            if((ret_val = rtl8367b_setAsicAclRule(filter_id + ruleId, &aclRule[i])) != RT_ERR_OK )
                return ret_val;

            /* only the first rule will be written with input action control, aclActCtrl of other rules will be zero */
            aclActCtrl = 0;
            memset(&aclAct, 0, sizeof(rtl8367b_acl_act_t));

			ruleId ++;
		}
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_filter_igrAcl_cfg_del
 * Description:
 *      Delete an ACL configuration from ASIC
 * Input:
 *      filter_id   - Start index of ACL configuration.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_FILTER_ENTRYIDX  - Invalid filter_id.
 * Note:
 *      This function delete a group of ACL rules starting from filter_id.
 */
int rtk_filter_igrAcl_cfg_del(unsigned int filter_id)
{

    rtl8367b_aclrule initRule;
    rtl8367b_acl_act_t  initAct;
    int ret;

    if(filter_id > RTL8367B_ACLRULEMAX )
        return RT_ERR_FILTER_ENTRYIDX;

    memset(&initRule, 0, sizeof(rtl8367b_aclrule));
    memset(&initAct, 0, sizeof(rtl8367b_acl_act_t));

    if((ret = rtl8367b_setAsicAclRule(filter_id, &initRule)) != RT_ERR_OK)
        return ret;
    if((ret = rtl8367b_setAsicAclActCtrl(filter_id, FILTER_ENACT_INIT_MASK))!= RT_ERR_OK)
        return ret;
    if((ret = rtl8367b_setAsicAclAct(filter_id, &initAct)) != RT_ERR_OK)
        return ret;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_filter_igrAcl_cfg_delAll
 * Description:
 *      Delete all ACL entries from ASIC
 * Input:
 *      None
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 * Note:
 *      This function delete all ACL configuration from ASIC.
 */
int rtk_filter_igrAcl_cfg_delAll(void)
{
    rtl8367b_aclrule  initRule;
    rtl8367b_acl_act_t   initAct;
    unsigned int            i;
    int     ret;

    memset(&initRule, 0, sizeof(rtl8367b_aclrule));
    memset(&initAct, 0, sizeof(rtl8367b_acl_act_t));

    for(i = 0; i < RTL8367B_ACLRULENO; i++)
    {
        if((ret = rtl8367b_setAsicAclRule(i, &initRule)) != RT_ERR_OK)
            return ret;
        if((ret = rtl8367b_setAsicAclActCtrl(i, FILTER_ENACT_INIT_MASK))!= RT_ERR_OK)
            return ret;
         if ((ret = rtl8367b_setAsicAclAct(i, &initAct)) != RT_ERR_OK)
            return ret;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_filter_igrAcl_cfg_get
 * Description:
 *      Get one ingress acl configuration from ASIC.
 * Input:
 *      filter_id       - Start index of ACL configuration.
 * Output:
 *      pFilter_cfg     - buffer pointer of ingress acl data
 *      pFilter_action  - buffer pointer of ingress acl action
 * Return:
 *      RT_ERR_OK              	- OK
 *      RT_ERR_FAILED          	- Failed
 *      RT_ERR_SMI             	- SMI access error
 *      RT_ERR_NULL_POINTER 	- Pointer pFilter_action or pFilter_cfg point to NULL.
 *      RT_ERR_FILTER_ENTRYIDX 	- Invalid entry index.
 * Note:
 *      This function delete all ACL configuration from ASIC.
 */
int rtk_filter_igrAcl_cfg_get(unsigned int filter_id, rtk_filter_cfg_raw_t *pFilter_cfg, rtk_filter_action_t *pAction)
{
    int               ret_val;
    unsigned int                  i, tmp;
    rtl8367b_aclrule            aclRule;
    rtl8367b_acl_act_t          aclAct;
    unsigned int                  cpuPort;
    rtl8367b_acltemplate_t      type;
    rtl8367b_svlan_memconf_t    svlan_cfg;
    rtl8367b_vlanconfiguser     vlanMC;

    if ((ret_val = rtl8367b_getAsicAclRule(filter_id, &aclRule)) != RT_ERR_OK)
        return ret_val;

    pFilter_cfg->activeport.dataType = FILTER_FIELD_DATA_MASK;
    pFilter_cfg->activeport.value = aclRule.data_bits.active_portmsk;
    pFilter_cfg->activeport.mask = aclRule.care_bits.active_portmsk;

    for(i = 0; i <= CARE_TAG_IPV6; i++)
    {
        if(aclRule.data_bits.tag_exist & (1 << i))
            pFilter_cfg->careTag.tagType[i].value = 1;
        else
            pFilter_cfg->careTag.tagType[i].value = 0;

        if (aclRule.care_bits.tag_exist & (1 << i))
            pFilter_cfg->careTag.tagType[i].mask = 1;
        else
            pFilter_cfg->careTag.tagType[i].mask = 0;
    }

    if(filter_advanceCaretagField[aclRule.data_bits.type][0] == TRUE)
    {
        /* Advanced Care tag setting */
        for(i = CARE_TAG_TCP; i < CARE_TAG_END; i++)
        {
            if(aclRule.data_bits.field[filter_advanceCaretagField[aclRule.data_bits.type][1]] & (0x0001 << (i-CARE_TAG_TCP)) )
                pFilter_cfg->careTag.tagType[i].value = 1;
            else
                pFilter_cfg->careTag.tagType[i].value = 0;

            if(aclRule.care_bits.field[filter_advanceCaretagField[aclRule.data_bits.type][1]] & (0x0001 << (i-CARE_TAG_TCP)) )
                pFilter_cfg->careTag.tagType[i].mask = 1;
            else
                pFilter_cfg->careTag.tagType[i].mask = 0;
        }
    }

    for(i = 0; i < RTL8367B_ACLRULEFIELDNO; i++)
    {
        pFilter_cfg->careFieldRaw[i] = aclRule.care_bits.field[i];
        pFilter_cfg->dataFieldRaw[i] = aclRule.data_bits.field[i];
    }

    if ((ret_val = rtl8367b_getAsicAclNot(filter_id, &tmp))!= RT_ERR_OK)
        return ret_val;

    pFilter_cfg->invert = tmp;

    pFilter_cfg->valid = aclRule.valid;

    memset(pAction, 0, sizeof(rtk_filter_action_t));

    if ((ret_val = rtl8367b_getAsicAclActCtrl(filter_id, &tmp))!= RT_ERR_OK)
        return ret_val;

    if ((ret_val = rtl8367b_getAsicAclAct(filter_id, &aclAct)) != RT_ERR_OK)
        return ret_val;

    if(tmp & FILTER_ENACT_FWD_MASK)
    {
        if(aclAct.fwdact == RTL8367B_ACL_FWD_TRAP )
            pAction->actEnable[FILTER_ENACT_TRAP_CPU] = TRUE;
        else if (aclAct.fwdact == RTL8367B_ACL_FWD_MIRRORFUNTION )
        {
        	pAction->actEnable[FILTER_ENACT_MIRROR] = TRUE;
			pAction->filterAddDstPortmask = aclAct.fwdpmask;
		}
        else if (aclAct.fwdact == RTL8367B_ACL_FWD_REDIRECT)
        {
            if(aclAct.fwdpmask == 0 )
                pAction->actEnable[FILTER_ENACT_DROP] = TRUE;
            else
            {
                pAction->actEnable[FILTER_ENACT_REDIRECT] = TRUE;
                pAction->filterRedirectPortmask = aclAct.fwdpmask;
            }
        }
        else if (aclAct.fwdact == RTL8367B_ACL_FWD_MIRROR)
        {
            if((ret_val = rtl8367b_getAsicCputagTrapPort(&cpuPort)) != RT_ERR_OK)
                return ret_val;
            if (aclAct.fwdpmask == (1 << cpuPort))
            {
                pAction->actEnable[FILTER_ENACT_COPY_CPU] = TRUE;
            }
            else
            {
                pAction->actEnable[FILTER_ENACT_ADD_DSTPORT] = TRUE;
                pAction->filterAddDstPortmask = aclAct.fwdpmask;
            }
        }
        else
        {
            return RT_ERR_FAILED;
        }
    }

    if(tmp & FILTER_ENACT_POLICING_MASK)
    {
        pAction->actEnable[FILTER_ENACT_POLICING_0] = TRUE;
        pAction->filterPolicingIdx[0] = aclAct.aclmeteridx;
    }

    if(tmp & FILTER_ENACT_PRIORITY_MASK)
    {
    	if(aclAct.priact == FILTER_ENACT_PRI_TYPE(FILTER_ENACT_PRIORITY))
        {
        	pAction->actEnable[FILTER_ENACT_PRIORITY] = TRUE;
        	pAction->filterPriority = aclAct.pridx;
    	}
		else if(aclAct.priact == FILTER_ENACT_PRI_TYPE(FILTER_ENACT_1P_REMARK))
        {
        	pAction->actEnable[FILTER_ENACT_1P_REMARK] = TRUE;
        	pAction->filterPriority = aclAct.pridx;
    	}
		else if(aclAct.priact == FILTER_ENACT_PRI_TYPE(FILTER_ENACT_DSCP_REMARK))
        {
        	pAction->actEnable[FILTER_ENACT_DSCP_REMARK] = TRUE;
        	pAction->filterPriority = aclAct.pridx;
    	}
		else if(aclAct.priact == FILTER_ENACT_PRI_TYPE(FILTER_ENACT_POLICING_3))
        {
        	pAction->actEnable[FILTER_ENACT_POLICING_3] = TRUE;
        	pAction->filterPolicingIdx[3]  = aclAct.pridx;
    	}
    }

    if(tmp & FILTER_ENACT_SVLAN_MASK)
    {
    	if(aclAct.sact == FILTER_ENACT_SVLAN_TYPE(FILTER_ENACT_SVLAN_INGRESS))
        {
            if((ret_val = rtl8367b_getAsicSvlanMemberConfiguration(aclAct.svidx_sact, &svlan_cfg)) != RT_ERR_OK)
				return ret_val;

        	pAction->actEnable[FILTER_ENACT_SVLAN_INGRESS] = TRUE;
        	pAction->filterSvlanIdx = aclAct.svidx_sact;
            pAction->filterSvlanVid = svlan_cfg.vs_svid;
    	}
    	else if(aclAct.sact == FILTER_ENACT_SVLAN_TYPE(FILTER_ENACT_SVLAN_EGRESS))
        {
            if((ret_val = rtl8367b_getAsicSvlanMemberConfiguration(aclAct.svidx_sact, &svlan_cfg)) != RT_ERR_OK)
				return ret_val;

        	pAction->actEnable[FILTER_ENACT_SVLAN_EGRESS] = TRUE;
            pAction->filterEgressSvlanIdx = aclAct.svidx_sact;
        	pAction->filterSvlanIdx = aclAct.svidx_sact;
            pAction->filterSvlanVid = svlan_cfg.vs_svid;
    	}
    	else if(aclAct.sact == FILTER_ENACT_SVLAN_TYPE(FILTER_ENACT_SVLAN_CVID))
        	pAction->actEnable[FILTER_ENACT_SVLAN_CVID] = TRUE;
    	else if(aclAct.sact == FILTER_ENACT_SVLAN_TYPE(FILTER_ENACT_POLICING_2))
        {
        	pAction->actEnable[FILTER_ENACT_POLICING_2] = TRUE;
        	pAction->filterPolicingIdx[2]  = aclAct.svidx_sact;
    	}
    }


    if(tmp & FILTER_ENACT_CVLAN_MASK)
    {
        if(aclAct.cact == FILTER_ENACT_CVLAN_TYPE(FILTER_ENACT_CVLAN_INGRESS))
        {
            if((ret_val = rtl8367b_getAsicVlanMemberConfig(aclAct.cvidx_cact, &vlanMC)) != RT_ERR_OK)
                return ret_val;

            pAction->actEnable[FILTER_ENACT_CVLAN_INGRESS] = TRUE;
            pAction->filterCvlanIdx         = aclAct.cvidx_cact;
            pAction->filterIngressCvlanVid  = vlanMC.evid;
            pAction->filterIngressCvlanIdx  = aclAct.cvidx_cact;
        }
        else if(aclAct.cact == FILTER_ENACT_CVLAN_TYPE(FILTER_ENACT_CVLAN_EGRESS))
        {
            pAction->actEnable[FILTER_ENACT_CVLAN_EGRESS] = TRUE;
            pAction->filterCvlanIdx = aclAct.cvidx_cact;
        }
        else if(aclAct.cact == FILTER_ENACT_CVLAN_TYPE(FILTER_ENACT_CVLAN_SVID))
        {
            pAction->actEnable[FILTER_ENACT_CVLAN_SVID] = TRUE;
        }
    	else if(aclAct.cact == FILTER_ENACT_CVLAN_TYPE(FILTER_ENACT_POLICING_1))
        {
        	pAction->actEnable[FILTER_ENACT_POLICING_1] = TRUE;
        	pAction->filterPolicingIdx[1]  = aclAct.cvidx_cact;
    	}
    }

    if(tmp & FILTER_ENACT_INTGPIO_MASK)
    {
		if(TRUE == aclAct.aclint)
		{
			pAction->actEnable[FILTER_ENACT_INTERRUPT] = TRUE;
		}

		if(TRUE == aclAct.gpio_en)
		{
			pAction->actEnable[FILTER_ENACT_GPO] = TRUE;
			pAction->filterPin = aclAct.gpio_pin;
		}
    }

    /* Get field type of RAW data */
    if ((ret_val = rtl8367b_getAsicAclTemplate(aclRule.data_bits.type, &type))!= RT_ERR_OK)
        return ret_val;

    for(i = 0; i < RTL8367B_ACLRULEFIELDNO; i++)
    {
        pFilter_cfg->fieldRawType[i] = type.field[i];
    }/* end of for(i...) */

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_filter_igrAcl_unmatchAction_set
 * Description:
 *      Set action to packets when no ACL configuration match
 * Input:
 *      port    - Port id.
 *      action  - Action.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID 		- Invalid port id.
 *      RT_ERR_INPUT 		- Invalid input parameters.
 * Note:
 *      This function sets action of packets when no ACL configruation matches.
 */
int rtk_filter_igrAcl_unmatchAction_set(unsigned int port, unsigned int action)
{
    int ret;

    if(port > RTL8367B_PORTIDMAX )
        return RT_ERR_PORT_ID;

    if(action >= FILTER_UNMATCH_END)
        return RT_ERR_INPUT;

    if((ret = rtl8367b_setAsicAclUnmatchedPermit(port, action)) != RT_ERR_OK)
       return ret;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_filter_igrAcl_unmatchAction_get
 * Description:
 *      Get action to packets when no ACL configuration match
 * Input:
 *      port    - Port id.
 * Output:
 *      pAction - Action.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port id.
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      This function gets action of packets when no ACL configruation matches.
 */
int rtk_filter_igrAcl_unmatchAction_get(unsigned int port, unsigned int* pAction)
{
    int ret;

    if(port > RTL8367B_PORTIDMAX)
        return RT_ERR_PORT_ID;

    if((ret = rtl8367b_getAsicAclUnmatchedPermit(port, pAction)) != RT_ERR_OK)
       return ret;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_filter_igrAcl_state_set
 * Description:
 *      Set state of ingress ACL.
 * Input:
 *      port    - Port id.
 *      state   - Ingress ACL state.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port id.
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      This function gets action of packets when no ACL configruation matches.
 */
int rtk_filter_igrAcl_state_set(unsigned int port, unsigned int state)
{
    int ret;

    if(port > RTL8367B_PORTIDMAX )
        return RT_ERR_PORT_ID;
    if(state >= RTK_ENABLE_END)
        return RT_ERR_INPUT;

    if((ret = rtl8367b_setAsicAcl(port, state)) != RT_ERR_OK)
       return ret;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_filter_igrAcl_state_get
 * Description:
 *      Get state of ingress ACL.
 * Input:
 *      port    - Port id.
 * Output:
 *      pState  - Ingress ACL state.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port id.
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      This function gets action of packets when no ACL configruation matches.
 */
int rtk_filter_igrAcl_state_get(unsigned int port, unsigned int* pState)
{
    int ret;

    if(port > RTL8367B_PORTIDMAX )
        return RT_ERR_PORT_ID;

    if((ret = rtl8367b_getAsicAcl(port, pState)) != RT_ERR_OK)
       return ret;

    return RT_ERR_OK;
}
/* Function Name:
 *      rtk_filter_igrAcl_template_set
 * Description:
 *      Set template of ingress ACL.
 * Input:
 *      template - Ingress ACL template
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 *      RT_ERR_INPUT           - Invalid input parameters.
 * Note:
 *      This function set ACL template.
 */
int rtk_filter_igrAcl_template_set(rtk_filter_template_t *aclTemplate)
{
    int ret;
    unsigned int idxField;
    rtl8367b_acltemplate_t aclType;

    if(aclTemplate->index >= RTK_MAX_NUM_OF_FILTER_TYPE)
        return RT_ERR_INPUT;

    for(idxField = 0; idxField < RTK_MAX_NUM_OF_FILTER_FIELD; idxField ++)
    {
        if( (aclTemplate->fieldType[idxField] < FILTER_FIELD_RAW_DMAC_15_0      || aclTemplate->fieldType[idxField] > FILTER_FIELD_RAW_CTAG) &&
            (aclTemplate->fieldType[idxField] < FILTER_FIELD_RAW_IPV4_SIP_15_0  || aclTemplate->fieldType[idxField] > FILTER_FIELD_RAW_IPV4_DIP_31_16) &&
            (aclTemplate->fieldType[idxField] < FILTER_FIELD_RAW_IPV6_SIP_15_0  || aclTemplate->fieldType[idxField] > FILTER_FIELD_RAW_IPV6_DIP_31_16) &&
            (aclTemplate->fieldType[idxField] < FILTER_FIELD_RAW_VIDRANGE       || aclTemplate->fieldType[idxField] > FILTER_FIELD_RAW_PORTRANGE) &&
            (aclTemplate->fieldType[idxField] < FILTER_FIELD_RAW_FIELD_SELECT00 || aclTemplate->fieldType[idxField] > FILTER_FIELD_RAW_FIELD_SELECT15) )
            return RT_ERR_INPUT;
    }

    for(idxField = 0; idxField < RTK_MAX_NUM_OF_FILTER_FIELD; idxField ++)
    {
        aclType.field[idxField] = aclTemplate->fieldType[idxField];
    }

    ret = rtl8367b_setAsicAclTemplate(aclTemplate->index, &aclType);

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_filter_igrAcl_template_get
 * Description:
 *      Get template of ingress ACL.
 * Input:
 *      template - Ingress ACL template
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 * Note:
 *      This function gets template of ACL.
 */
int rtk_filter_igrAcl_template_get(rtk_filter_template_t *aclTemplate)
{
    int ret;
    unsigned int idxField;
    rtl8367b_acltemplate_t aclType;

    if(aclTemplate->index >= RTK_MAX_NUM_OF_FILTER_TYPE)
        return RT_ERR_INPUT;

   if((ret = rtl8367b_getAsicAclTemplate(aclTemplate->index, &aclType)) != RT_ERR_OK)
       return ret;

    for(idxField = 0; idxField < RTK_MAX_NUM_OF_FILTER_FIELD; idxField ++)
    {
        aclTemplate->fieldType[idxField] = aclType.field[idxField];
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_filter_igrAcl_field_sel_set
 * Description:
 *      Set user defined field selectors in HSB
 * Input:
 *      index 		- index of field selector 0-15
 *      format 		- Format of field selector
 *      offset 		- Retrieving data offset
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 * Note:
 *      System support 16 user defined field selctors.
 * 		Each selector can be enabled or disable.
 *      User can defined retrieving 16-bits in many predefiend
 * 		standard l2/l3/l4 payload.
 */
int rtk_filter_igrAcl_field_sel_set(unsigned int index, rtk_field_sel_t format, unsigned int offset)
{
    int ret;

    if(index >= RTL8367B_FIELDSEL_FORMAT_NUMBER)
        return RT_ERR_OUT_OF_RANGE;

    if(format >= FORMAT_END)
        return RT_ERR_OUT_OF_RANGE;

    if(offset > RTL8367B_FIELDSEL_MAX_OFFSET)
        return RT_ERR_OUT_OF_RANGE;

    if((ret = rtl8367b_setAsicFieldSelector(index, (unsigned int)format, offset)) != RT_ERR_OK)
       return ret;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_filter_igrAcl_field_sel_get
 * Description:
 *      Get user defined field selectors in HSB
 * Input:
 *      index 	    - index of field selector 0-15
 * Output:
 *      pFormat 	- Format of field selector
 *      pOffset 	- Retrieving data offset
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 * Note:
 *      None.
 */
int rtk_filter_igrAcl_field_sel_get(unsigned int index, rtk_field_sel_t *pFormat, unsigned int *pOffset)
{
    int ret;

    if(index >= RTL8367B_FIELDSEL_FORMAT_NUMBER)
        return RT_ERR_OUT_OF_RANGE;

    if((ret = rtl8367b_getAsicFieldSelector(index, pFormat, pOffset)) != RT_ERR_OK)
       return ret;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_filter_iprange_set
 * Description:
 *      Set IP Range check
 * Input:
 *      index 	    - index of IP Range 0-15
 *      type        - IP Range check type, 0:Delete a entry, 1: IPv4_SIP, 2: IPv4_DIP, 3:IPv6_SIP, 4:IPv6_DIP
 *      upperIp     - The upper bound of IP range
 *      lowerIp     - The lower Bound of IP range
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 *      RT_ERR_OUT_OF_RANGE    - The parameter is out of range
 *      RT_ERR_INPUT           - Input error
 * Note:
 *      upperIp must be larger or equal than lowerIp.
 */
int rtk_filter_iprange_set(unsigned int index, rtk_filter_iprange_t type, unsigned int upperIp, unsigned int lowerIp)
{
    int ret;

    if(index > RTL8367B_ACLRANGEMAX)
		return RT_ERR_OUT_OF_RANGE;

    if(type >= IPRANGE_END)
        return RT_ERR_OUT_OF_RANGE;

    if(lowerIp > upperIp)
        return RT_ERR_INPUT;

    if((ret = rtl8367b_setAsicAclIpRange(index, type, upperIp, lowerIp)) != RT_ERR_OK)
       return ret;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_filter_iprange_get
 * Description:
 *      Set IP Range check
 * Input:
 *      index 	    - index of IP Range 0-15
 * Output:
 *      pType        - IP Range check type, 0:Delete a entry, 1: IPv4_SIP, 2: IPv4_DIP, 3:IPv6_SIP, 4:IPv6_DIP
 *      pUpperIp     - The upper bound of IP range
 *      pLowerIp     - The lower Bound of IP range
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 *      RT_ERR_OUT_OF_RANGE    - The parameter is out of range
 * Note:
 *      None.
 */
int rtk_filter_iprange_get(unsigned int index, rtk_filter_iprange_t *pType, unsigned int *pUpperIp, unsigned int *pLowerIp)
{
    int ret;

    if(index > RTL8367B_ACLRANGEMAX)
		return RT_ERR_OUT_OF_RANGE;

    if((ret = rtl8367b_getAsicAclIpRange(index, pType, pUpperIp, pLowerIp)) != RT_ERR_OK)
       return ret;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_filter_vidrange_set
 * Description:
 *      Set VID Range check
 * Input:
 *      index 	    - index of VID Range 0-15
 *      type        - IP Range check type, 0:Delete a entry, 1: CVID, 2: SVID
 *      upperVid    - The upper bound of VID range
 *      lowerVid    - The lower Bound of VID range
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 *      RT_ERR_OUT_OF_RANGE    - The parameter is out of range
 *      RT_ERR_INPUT           - Input error
 * Note:
 *      upperVid must be larger or equal than lowerVid.
 */
int rtk_filter_vidrange_set(unsigned int index, rtk_filter_vidrange_t type, unsigned int upperVid, unsigned int lowerVid)
{
    int ret;

    if(index > RTL8367B_ACLRANGEMAX)
		return RT_ERR_OUT_OF_RANGE;

    if(type >= VIDRANGE_END)
        return RT_ERR_OUT_OF_RANGE;

    if(lowerVid > upperVid)
        return RT_ERR_INPUT;

    if( (upperVid > RTL8367B_VIDMAX) || (lowerVid > RTL8367B_VIDMAX))
        return RT_ERR_OUT_OF_RANGE;

    if((ret = rtl8367b_setAsicAclVidRange(index, type, upperVid, lowerVid)) != RT_ERR_OK)
       return ret;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_filter_vidrange_get
 * Description:
 *      Get VID Range check
 * Input:
 *      index 	    - index of VID Range 0-15
 * Output:
 *      pType        - IP Range check type, 0:Unused, 1: CVID, 2: SVID
 *      pUpperVid    - The upper bound of VID range
 *      pLowerVid    - The lower Bound of VID range
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 *      RT_ERR_OUT_OF_RANGE    - The parameter is out of range
 * Note:
 *      None.
 */
int rtk_filter_vidrange_get(unsigned int index, rtk_filter_vidrange_t *pType, unsigned int *pUpperVid, unsigned int *pLowerVid)
{
    int ret;

    if(index > RTL8367B_ACLRANGEMAX)
		return RT_ERR_OUT_OF_RANGE;

    if((ret = rtl8367b_getAsicAclVidRange(index, pType, pUpperVid, pLowerVid)) != RT_ERR_OK)
       return ret;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_filter_portrange_set
 * Description:
 *      Set Port Range check
 * Input:
 *      index 	    - index of Port Range 0-15
 *      type        - IP Range check type, 0:Delete a entry, 1: Source Port, 2: Destnation Port
 *      upperPort   - The upper bound of Port range
 *      lowerPort   - The lower Bound of Port range
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 *      RT_ERR_OUT_OF_RANGE    - The parameter is out of range
 *      RT_ERR_INPUT           - Input error
 * Note:
 *      upperPort must be larger or equal than lowerPort.
 */
int rtk_filter_portrange_set(unsigned int index, rtk_filter_portrange_t type, unsigned int upperPort, unsigned int lowerPort)
{
    int ret;

    if(index > RTL8367B_ACLRANGEMAX)
		return RT_ERR_OUT_OF_RANGE;

    if(type >= PORTRANGE_END)
        return RT_ERR_OUT_OF_RANGE;

    if(lowerPort > upperPort)
        return RT_ERR_INPUT;

    if(upperPort > RTL8367B_ACL_PORTRANGEMAX)
        return RT_ERR_INPUT;

    if(lowerPort > RTL8367B_ACL_PORTRANGEMAX)
        return RT_ERR_INPUT;

    if((ret = rtl8367b_setAsicAclPortRange(index, type, upperPort, lowerPort)) != RT_ERR_OK)
       return ret;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_filter_portrange_get
 * Description:
 *      Set Port Range check
 * Input:
 *      index 	    - index of Port Range 0-15
 * Output:
 *      pType       - IP Range check type, 0:Delete a entry, 1: Source Port, 2: Destnation Port
 *      pUpperPort  - The upper bound of Port range
 *      pLowerPort  - The lower Bound of Port range
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 *      RT_ERR_OUT_OF_RANGE    - The parameter is out of range
 *      RT_ERR_INPUT           - Input error
 * Note:
 *      None.
 */
int rtk_filter_portrange_get(unsigned int index, rtk_filter_portrange_t *pType, unsigned int *pUpperPort, unsigned int *pLowerPort)
{
    int ret;

    if(index > RTL8367B_ACLRANGEMAX)
		return RT_ERR_OUT_OF_RANGE;

    if((ret = rtl8367b_getAsicAclPortRange(index, pType, pUpperPort, pLowerPort)) != RT_ERR_OK)
       return ret;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_eee_init
 * Description:
 *      EEE function initialization.
 * Input:
 *      None
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 * Note:
 *      This API is used to initialize EEE status.
 */
int rtk_eee_init(void)
{
    int ret_val;

    if((ret_val = rtl8367b_setAsicRegBit(0x0018, 10, 1)) != RT_ERR_OK)
        return ret_val;

    if((ret_val = rtl8367b_setAsicRegBit(0x0018, 11, 1)) != RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_eee_portEnable_set
 * Description:
 *      Set enable status of EEE function.
 * Input:
 *      port - port id.
 *      enable - enable EEE status.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 *      RT_ERR_PORT_ID - Invalid port number.
 *      RT_ERR_ENABLE - Invalid enable input.
 * Note:
 *      This API can set EEE function to the specific port.
 *      The configuration of the port is as following:
 *      - DISABLE
 *      - ENABLE
 */
int rtk_eee_portEnable_set(unsigned int port, rtk_enable_t enable)
{
    int   ret_val;
    unsigned int      regData;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if (enable>=RTK_ENABLE_END)
        return RT_ERR_INPUT;

    if ((ret_val = rtl8367b_setAsicEee100M(port,enable))!=RT_ERR_OK)
        return ret_val;
    if ((ret_val = rtl8367b_setAsicEeeGiga(port,enable))!=RT_ERR_OK)
        return ret_val;

    if ((ret_val = rtl8367b_setAsicRegBit(RTL8367B_PORT_EEE_CFG_REG(port), RTL8367B_PORT0_EEECFG_EEE_TX_OFFSET, (enable == ENABLED) ? 1 : 0)) != RT_ERR_OK)
        return ret_val;
    if ((ret_val = rtl8367b_setAsicRegBit(RTL8367B_PORT_EEE_CFG_REG(port), RTL8367B_PORT0_EEECFG_EEE_RX_OFFSET, (enable == ENABLED) ? 1 : 0)) != RT_ERR_OK)
        return ret_val;

    if ((ret_val = rtl8367b_setAsicPHYReg(port, RTL8367B_PHY_PAGE_ADDRESS, 7))!=RT_ERR_OK)
        return ret_val;
    if ((ret_val = rtl8367b_setAsicPHYReg(port, 30, 32))!=RT_ERR_OK)
        return ret_val;
    if ((ret_val = rtl8367b_setAsicPHYReg(port, 21, (enable == ENABLED) ? 0x0100 : 0x0000))!=RT_ERR_OK)
        return ret_val;

    if ((ret_val = rtl8367b_setAsicPHYReg(port, RTL8367B_PHY_PAGE_ADDRESS, 0))!=RT_ERR_OK)
        return ret_val;
    if ((ret_val = rtl8367b_getAsicPHYReg(port, 0, &regData))!=RT_ERR_OK)
        return ret_val;
    regData |= 0x0200;
    if ((ret_val = rtl8367b_setAsicPHYReg(port, 0, regData))!=RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_eee_portEnable_get
 * Description:
 *      Get enable status of EEE function
 * Input:
 *      port - Port id.
 * Output:
 *      pEnable - Back pressure status.
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 *      RT_ERR_PORT_ID - Invalid port number.
 * Note:
 *      This API can get EEE function to the specific port.
 *      The configuration of the port is as following:
 *      - DISABLE
 *      - ENABLE
 */

int rtk_eee_portEnable_get(unsigned int port, rtk_enable_t *pEnable)
{
    int ret_val;
    unsigned int regData1, regData2;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if ((ret_val = rtl8367b_getAsicEee100M(port,&regData1))!=RT_ERR_OK)
        return ret_val;
    if ((ret_val = rtl8367b_getAsicEeeGiga(port,&regData2))!=RT_ERR_OK)
        return ret_val;

    if (regData1==1&&regData2==1)
        *pEnable = ENABLED;
    else
        *pEnable = DISABLED;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_igmp_init
 * Description:
 *      This API enables H/W IGMP and set a default initial configuration.
 * Input:
 *      None.
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 * Note:
 *      This API enables H/W IGMP and set a default initial configuration.
 */
int rtk_igmp_init(void)
{
    int ret_val;
    unsigned int port;

    if ((ret_val = rtl8367b_setAsicLutIpMulticastLookup(ENABLED))!=RT_ERR_OK)
        return ret_val;

    if ((ret_val = rtl8367b_setAsicLutIpLookupMethod(1))!=RT_ERR_OK)
        return ret_val;

    if ((ret_val = rtl8367b_setAsicIgmp(ENABLED))!=RT_ERR_OK)
        return ret_val;

    for(port = 0; port <= RTK_PORT_ID_MAX; port++)
    {
        if ((ret_val = rtl8367b_setAsicIGMPv1Opeartion(port, PROTOCOL_OP_ASIC))!=RT_ERR_OK)
            return ret_val;

        if ((ret_val = rtl8367b_setAsicIGMPv2Opeartion(port, PROTOCOL_OP_ASIC))!=RT_ERR_OK)
            return ret_val;

        if ((ret_val = rtl8367b_setAsicIGMPv3Opeartion(port, PROTOCOL_OP_TRAP))!=RT_ERR_OK)
            return ret_val;

        if ((ret_val = rtl8367b_setAsicMLDv1Opeartion(port, PROTOCOL_OP_ASIC))!=RT_ERR_OK)
            return ret_val;

        if ((ret_val = rtl8367b_setAsicMLDv2Opeartion(port, PROTOCOL_OP_TRAP))!=RT_ERR_OK)
            return ret_val;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_igmp_state_set
 * Description:
 *      This API set H/W IGMP state.
 * Input:
 *      enabled     - H/W IGMP state
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 *      RT_ERR_INPUT           - Error parameter
 * Note:
 *      This API set H/W IGMP state.
 */
int rtk_igmp_state_set(rtk_enable_t enabled)
{
    int ret_val;

    if (enabled >= RTK_ENABLE_END)
        return RT_ERR_INPUT;

    if ((ret_val = rtl8367b_setAsicIgmp(enabled))!=RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_igmp_state_get
 * Description:
 *      This API get H/W IGMP state.
 * Input:
 *      None.
 * Output:
 *      pEnabled        - H/W IGMP state
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 *      RT_ERR_INPUT           - Error parameter
 * Note:
 *      This API set current H/W IGMP state.
 */
int rtk_igmp_state_get(rtk_enable_t *pEnabled)
{
    int ret_val;

    if ((ret_val = rtl8367b_getAsicIgmp(pEnabled))!=RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_igmp_static_router_port_set
 * Description:
 *      Configure static router port
 * Input:
 *      portmask    - Static Port mask
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 *      RT_ERR_PORT_MASK       - Error parameter
 * Note:
 *      This API set static router port
 */
int rtk_igmp_static_router_port_set(rtk_portmask_t portmask)
{
    int ret_val;

    if ( portmask.bits[0] > RTK_MAX_PORT_MASK)
        return RT_ERR_PORT_MASK;

    if ((ret_val = rtl8367b_setAsicIGMPStaticRouterPort(portmask.bits[0]))!=RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_igmp_static_router_port_get
 * Description:
 *      Get static router port
 * Input:
 *      None.
 * Output:
 *      pPortmask       - Static port mask
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 *      RT_ERR_PORT_MASK       - Error parameter
 * Note:
 *      This API get static router port
 */
int rtk_igmp_static_router_port_get(rtk_portmask_t *pPortmask)
{
    int ret_val;

    if ((ret_val = rtl8367b_getAsicIGMPStaticRouterPort(&pPortmask->bits[0]))!=RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_igmp_protocol_set
 * Description:
 *      set IGMP/MLD protocol action
 * Input:
 *      port        - Port ID
 *      protocol    - IGMP/MLD protocol
 *      action      - Per-port and per-protocol IGMP action seeting
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 *      RT_ERR_PORT_MASK       - Error parameter
 * Note:
 *      This API set IGMP/MLD protocol action
 */
int rtk_igmp_protocol_set(unsigned int port, rtk_igmp_protocol_t protocol, rtk_trap_igmp_action_t action)
{
    unsigned int      operation;
    int   ret_val;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if(protocol >= PROTOCOL_END)
        return RT_ERR_INPUT;

    if((action >= IGMP_ACTION_END) || (action == IGMP_ACTION_FORWARD_EXCLUDE_CPU))
        return RT_ERR_INPUT;

    switch(action)
    {
        case IGMP_ACTION_FORWARD:
            operation = PROTOCOL_OP_FLOOD;
            break;
        case IGMP_ACTION_TRAP2CPU:
            operation = PROTOCOL_OP_TRAP;
            break;
        case IGMP_ACTION_DROP:
            operation = PROTOCOL_OP_DROP;
            break;
        case IGMP_ACTION_ASIC:
            if( (protocol == PROTOCOL_IGMPv3) || (protocol == PROTOCOL_MLDv2) )
                return RT_ERR_CHIP_NOT_SUPPORTED;
            else
                operation = PROTOCOL_OP_ASIC;
            break;
        default:
            return RT_ERR_INPUT;
    }

    switch(protocol)
    {
        case PROTOCOL_IGMPv1:
            if ((ret_val = rtl8367b_setAsicIGMPv1Opeartion(port, operation))!=RT_ERR_OK)
                return ret_val;

            break;
        case PROTOCOL_IGMPv2:
            if ((ret_val = rtl8367b_setAsicIGMPv2Opeartion(port, operation))!=RT_ERR_OK)
                return ret_val;

            break;
        case PROTOCOL_IGMPv3:
            if ((ret_val = rtl8367b_setAsicIGMPv3Opeartion(port, operation))!=RT_ERR_OK)
                return ret_val;

            break;
        case PROTOCOL_MLDv1:
            if ((ret_val = rtl8367b_setAsicMLDv1Opeartion(port, operation))!=RT_ERR_OK)
                return ret_val;

            break;
        case PROTOCOL_MLDv2:
            if ((ret_val = rtl8367b_setAsicMLDv2Opeartion(port, operation))!=RT_ERR_OK)
                return ret_val;

            break;
        default:
            return RT_ERR_INPUT;

    }

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_igmp_protocol_get
 * Description:
 *      set IGMP/MLD protocol action
 * Input:
 *      port        - Port ID
 *      protocol    - IGMP/MLD protocol
 *      action      - Per-port and per-protocol IGMP action seeting
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 *      RT_ERR_PORT_MASK       - Error parameter
 * Note:
 *      This API set IGMP/MLD protocol action
 */
int rtk_igmp_protocol_get(unsigned int port, rtk_igmp_protocol_t protocol, rtk_trap_igmp_action_t *pAction)
{
    unsigned int      operation;
    int   ret_val;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if(protocol >= PROTOCOL_END)
        return RT_ERR_INPUT;

    switch(protocol)
    {
        case PROTOCOL_IGMPv1:
            if ((ret_val = rtl8367b_getAsicIGMPv1Opeartion(port, &operation))!=RT_ERR_OK)
                return ret_val;

            break;
        case PROTOCOL_IGMPv2:
            if ((ret_val = rtl8367b_getAsicIGMPv2Opeartion(port, &operation))!=RT_ERR_OK)
                return ret_val;

            break;
        case PROTOCOL_IGMPv3:
            if ((ret_val = rtl8367b_getAsicIGMPv3Opeartion(port, &operation))!=RT_ERR_OK)
                return ret_val;

            break;
        case PROTOCOL_MLDv1:
            if ((ret_val = rtl8367b_getAsicMLDv1Opeartion(port, &operation))!=RT_ERR_OK)
                return ret_val;

            break;
        case PROTOCOL_MLDv2:
            if ((ret_val = rtl8367b_getAsicMLDv2Opeartion(port, &operation))!=RT_ERR_OK)
                return ret_val;

            break;
        default:
            return RT_ERR_INPUT;

    }

    switch(operation)
    {
        case PROTOCOL_OP_FLOOD:
            *pAction = IGMP_ACTION_FORWARD;
            break;
        case PROTOCOL_OP_TRAP:
            *pAction = IGMP_ACTION_TRAP2CPU;
            break;
        case PROTOCOL_OP_DROP:
            *pAction = IGMP_ACTION_DROP;
            break;
        case PROTOCOL_OP_ASIC:
            *pAction = IGMP_ACTION_ASIC;
            break;
        default:
            return RT_ERR_FAILED;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_igmp_fastLeave_set
 * Description:
 *      set IGMP/MLD FastLeave state
 * Input:
 *      state       - ENABLED: Enable FastLeave, DISABLED: disable FastLeave
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_INPUT           - Error Input
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 * Note:
 *      This API set IGMP/MLD FastLeave state
 */
int rtk_igmp_fastLeave_set(rtk_enable_t state)
{
    int   ret_val;

    if(state >= RTK_ENABLE_END)
        return RT_ERR_INPUT;

    if ((ret_val = rtl8367b_setAsicIGMPFastLeaveEn((unsigned int)state))!=RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_igmp_fastLeave_get
 * Description:
 *      get IGMP/MLD FastLeave state
 * Input:
 *      None
 * Output:
 *      pState      - ENABLED: Enable FastLeave, DISABLED: disable FastLeave
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_NULL_POINTER    - NULL pointer
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 * Note:
 *      This API get IGMP/MLD FastLeave state
 */
int rtk_igmp_fastLeave_get(rtk_enable_t *pState)
{
    unsigned int      fast_leave;
    int   ret_val;

    if(pState == NULL)
        return RT_ERR_NULL_POINTER;

    if ((ret_val = rtl8367b_getAsicIGMPFastLeaveEn(&fast_leave))!=RT_ERR_OK)
        return ret_val;

    *pState = ((fast_leave == 1) ? ENABLED : DISABLED);
    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_igmp_maxGroup_set
 * Description:
 *      Set per port multicast group learning limit.
 * Input:
 *      port        - Port ID
 *      group       - The number of multicast group learning limit.
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_PORT_ID         - Error Port ID
 *      RT_ERR_OUT_OF_RANGE    - parameter out of range
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 * Note:
 *      This API set per port multicast group learning limit.
 */
int rtk_igmp_maxGroup_set(unsigned int port, unsigned int group)
{
    int   ret_val;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if(group > RTL8367B_IGMP_MAX_GOUP)
		return RT_ERR_OUT_OF_RANGE;

    if ((ret_val = rtl8367b_setAsicIGMPPortMAXGroup(port, group))!=RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_igmp_maxGroup_get
 * Description:
 *      Get per port multicast group learning limit.
 * Input:
 *      port        - Port ID
 * Output:
 *      pGroup      - The number of multicast group learning limit.
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_PORT_ID         - Error Port ID
 *      RT_ERR_NULL_POINTER    - Null pointer
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 * Note:
 *      This API get per port multicast group learning limit.
 */
int rtk_igmp_maxGroup_get(unsigned int port, unsigned int *pGroup)
{
    int   ret_val;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if(pGroup == NULL)
		return RT_ERR_NULL_POINTER;

    if ((ret_val = rtl8367b_getAsicIGMPPortMAXGroup(port, pGroup))!=RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_igmp_currentGroup_get
 * Description:
 *      Get per port multicast group learning count.
 * Input:
 *      port        - Port ID
 * Output:
 *      pGroup      - The number of multicast group learning count.
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_PORT_ID         - Error Port ID
 *      RT_ERR_NULL_POINTER    - Null pointer
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 * Note:
 *      This API get per port multicast group learning count.
 */
int rtk_igmp_currentGroup_get(unsigned int port, unsigned int *pGroup)
{
    int   ret_val;

    if (port > RTK_PORT_ID_MAX)
        return RT_ERR_PORT_ID;

    if(pGroup == NULL)
		return RT_ERR_NULL_POINTER;

    if ((ret_val = rtl8367b_getAsicIGMPPortCurrentGroup(port, pGroup))!=RT_ERR_OK)
        return ret_val;

    return RT_ERR_OK;
}


/*_________________________________________________________________________________________________
 * Function Description:     Set chip to default configuration enviroment
 * Input:      None
 * Output:     None
 * Return:     RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 * Note: The API can set chip registers to default configuration for different release chip model.
 ________________________________________________________________________________________________*/
int rtl8365_chip_init_kernel(void)
{
	unsigned short i;
	unsigned int data = 0;
	int ret_val = -EINVAL;
	unsigned int phy;
	unsigned short (*init_para)[2];
	unsigned short init_size;

	ret_val = rtl8367b_setAsicReg(0x13C2, 0x0249);
    if(RT_ERR_OK != ret_val) {
		goto out;
   	}
	ret_val = rtl8367b_getAsicReg(0x1301, &data);
    if(RT_ERR_OK != ret_val) {
		goto out;
   	}
	if(data & 0xF000) {
		init_para = ChipData11;
		init_size = (sizeof(ChipData11) / ((sizeof(unsigned short))*2));
	} else {
		init_para = ChipData10;
		init_size = (sizeof(ChipData10) / ((sizeof(unsigned short))*2));
	}
	for(phy = 0; phy <= RTK_PHY_ID_MAX; phy++) {/* Analog parameter update. ID:0001 */
		ret_val = rtl8367b_setAsicPHYReg(phy, 31, 0x7);
		if(RT_ERR_OK != ret_val) {
			goto out;
		}
		ret_val = rtl8367b_setAsicPHYReg(phy, 30, 0x2c);
		if(RT_ERR_OK != ret_val) {
			goto out;
		}
		ret_val = rtl8367b_setAsicPHYReg(phy, 25, 0x0504);
		if(RT_ERR_OK != ret_val) {
			goto out;
		}
		ret_val = rtl8367b_setAsicPHYReg(phy, 31, 0x0);
		if(RT_ERR_OK != ret_val) {
			goto out;
		}
	}
	for(i = 0; i < init_size; i++) {
		ret_val = rtl8367b_setAsicReg((unsigned int)init_para[i][0], (unsigned int)init_para[i][1]);
		if(RT_ERR_OK != ret_val) {
			goto out;
		}
	}
	/* Analog parameter update. ID:0002 */
	ret_val = rtl8367b_setAsicPHYReg(1, 31, 0x2);
	if(RT_ERR_OK != ret_val) {
		goto out;
	}
    ret_val = rtl8367b_getAsicPHYReg(1, 17, &data);
	if(RT_ERR_OK != ret_val) {
		goto out;
	}
	data |= 0x01E0;
	ret_val = rtl8367b_setAsicPHYReg(1, 17, data);
	if(RT_ERR_OK != ret_val) {
		goto out;
	}
	ret_val = rtl8367b_setAsicPHYReg(1, 31, 0x0);
	if(RT_ERR_OK != ret_val) {
		goto out;
	}
	ret_val = rtl8367b_setAsicRegBit(RTL8367B_REG_RLDP_CTRL0, 0, 0);
	if(RT_ERR_OK != ret_val) {
		goto out;
	}
	ret_val = rtl8367b_setAsicReg(RTL8367B_REG_CHIP_DEBUG0, 0x0778);
	if(RT_ERR_OK != ret_val) {
		goto out;
	}
	ret_val = rtl8367b_setAsicReg(RTL8367B_REG_CHIP_DEBUG1, 0x7777);
	if(RT_ERR_OK != ret_val) {
		goto out;
	}
	ret_val = rtl8367b_setAsicReg(RTL8367B_REG_CHIP_DEBUG2, 0x01FE);

out:
    return ret_val;
}


