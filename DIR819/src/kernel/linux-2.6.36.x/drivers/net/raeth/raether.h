#ifndef RA2882ETHEND_H
#define RA2882ETHEND_H

#ifdef DSP_VIA_NONCACHEABLE
#define ESRAM_BASE	0xa0800000	/* 0x0080-0000  ~ 0x00807FFF */
#else
#define ESRAM_BASE	0x80800000	/* 0x0080-0000  ~ 0x00807FFF */
#endif

#define RX_RING_BASE	((int)(ESRAM_BASE + 0x7000))
#define TX_RING_BASE	((int)(ESRAM_BASE + 0x7800))
#define NR_PORTS                5

#if defined(CONFIG_RALINK_RT2880)
#define NUM_TX_RINGS 	1
#else
#define NUM_TX_RINGS 	4
#endif
#ifdef MEMORY_OPTIMIZATION
#ifdef CONFIG_RAETH_ROUTER
#define NUM_RX_DESC     128
#define NUM_TX_DESC    	128
#elif CONFIG_RT_3052_ESW
#define NUM_RX_DESC     64
#define NUM_TX_DESC     64
#else
#define NUM_RX_DESC     128
#define NUM_TX_DESC     128
#endif
//#define NUM_RX_MAX_PROCESS 32
#define NUM_RX_MAX_PROCESS 64
#else
#if defined (CONFIG_RAETH_ROUTER)
#define NUM_RX_DESC     256
#define NUM_TX_DESC    	256
#elif defined (CONFIG_RT_3052_ESW)
#define NUM_RX_DESC     256
#define NUM_TX_DESC     256
#else
#define NUM_RX_DESC     256
#define NUM_TX_DESC     256
#endif
#if defined(CONFIG_RALINK_RT3883) || defined(CONFIG_RALINK_MT7620)
#define NUM_RX_MAX_PROCESS 2
#else
#define NUM_RX_MAX_PROCESS 16
#endif
#endif

//#define DEV_NAME        "eth2"
#define DEV_NAME        "eth"
#define DEV2_NAME       "eth3"

#if defined (CONFIG_RALINK_RT6855A) || defined (CONFIG_RALINK_MT7621)
#define GMAC0_OFFSET    0xE000
#define GMAC2_OFFSET    0xE006
#else
#define GMAC0_OFFSET    0x28 
#define GMAC2_OFFSET    0x22
#endif
#define GMAC1_OFFSET    0x2E

#if defined(CONFIG_RALINK_RT6855A)
#define IRQ_ENET0	22
#else
#define IRQ_ENET0	3 	/* hardware interrupt #3, defined in RT2880 Soc Design Spec Rev 0.03, pp43 */
#define GSW_AGC             (GSW_ARL_BASE + 0x0C)
#define GSW_MFC     		(GSW_ARL_BASE + 0x10)
#define GSW_VTC     		(GSW_ARL_BASE + 0x14)
#define GSW_ATAI            (GSW_ARL_BASE + 0x74)/* Address Table Access I Register */
#define GSW_ATAII           (GSW_ARL_BASE + 0x78)/* Address Table Access II Register */
#define GSW_ATWD            (GSW_ARL_BASE + 0x7C)/* Address Table Write Data Register */
#define GSW_ATC             (GSW_ARL_BASE + 0x80)/* Address Table Control Register */
#define GSW_TSRAI           (GSW_ARL_BASE + 0x84)/* Table Search Read Address-I Register */
#define GSW_TSRAII          (GSW_ARL_BASE + 0x88)/* Table Search Read Address-II Register */
#define GSW_ATRD            (GSW_ARL_BASE + 0x8C)/* Address Table Read Data Register */
#endif

#define CONFIG_ETHERNET_DEBUG             1
#ifdef CONFIG_ETHERNET_DEBUG
extern unsigned long dump_mask;
#define etdebug(fmt, args...) printk(fmt, ##args)
#define DUMP_RX_UNTAG                     0x01
#define DUMP_RX_TAG                       0x02
#define DUMP_TX_UNTAG                     0x04
#define DUMP_TX_TAG                       0x08
#define DUMP_ALL_UNTAG                    0x05
#define DUMP_ALL_TAG                      0x0A
#define DUMP_ALL                          0x0F
#else
#define etdebug(fmt, args...)
#endif

/*
* TBS_TAG: by Huangzheng 2014-10-16
* Desc:将下行流 nfmark 标记为0x80,上行流不标记默认
*          为0x0,以用于Qos区分上下行
*/

/*上下行标记的bit位*/
#define UP_DOWN_NFMARK_BIT                (7)
/*上下行mark标记mask*/
#define UP_DOWN_NFMARK_MASK     (0x1UL<<UP_DOWN_NFMARK_BIT)

/*上行/下行转成:mask+NFMARK表示*/
#define UP_DOWN_NFMARK(iUpOrDown) \
        (UP_DOWN_NFMARK_MASK&(iUpOrDown<<UP_DOWN_NFMARK_BIT))

#define BASIC_NFMARK_DOWN (UP_DOWN_NFMARK(0x1UL))

/*TBS_END_TAG*/


#define FE_INT_STATUS_REG (*(volatile unsigned long *)(FE_INT_STATUS))
#define FE_INT_STATUS_CLEAN(reg) (*(volatile unsigned long *)(FE_INT_STATUS)) = reg

//#define RAETH_DEBUG
#ifdef RAETH_DEBUG
#define RAETH_PRINT(fmt, args...) printk(KERN_INFO fmt, ## args)
#else
#define RAETH_PRINT(fmt, args...) { }
#endif

struct net_device_stats *ra_get_stats(struct net_device *dev);

void ei_tx_timeout(struct net_device *dev);
int rather_probe(struct net_device *dev);
int ei_open(struct net_device *dev);
int ei_close(struct net_device *dev);

int ra2882eth_init(void);
void ra2882eth_cleanup_module(void);

void ei_xmit_housekeeping(unsigned long data);

u32 mii_mgr_read(u32 phy_addr, u32 phy_register, u32 *read_data);
u32 mii_mgr_write(u32 phy_addr, u32 phy_register, u32 write_data);
void fe_sw_init(void);

#endif
