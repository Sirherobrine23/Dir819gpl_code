/*
 * (C) Copyright 2003
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

/*
 * This file contains the configuration parameters for the RT2880 board.
 */

#ifndef __CONFIG_H
#define __CONFIG_H

#include "sdram_layout.h"

#ifndef __MT7620A_AUTOCONF_H__
#define __MT7620A_AUTOCONF_H__
#include "../../cpu/mt7620a/autoconf.h"
#endif

#define CONFIG_RT2880_ETH		1	/* Enable built-in 10/100 Ethernet */

#define CONFIG_MIPS32			1	/* MIPS 4Kc CPU core	*/
#define CONFIG_MT7620A			1

/* boot args for kernel*/
#define CONFIG_CMDLINE_TAG	   1	     /* enable passing of ATAGs	 */

//#ifdef CONFIG_MT7620A_SPI_FLASH
#if 1
#define SPI_FLASH 				1
#else
#define CFI_FLASH               1
#define CFG_FLASH_CFI_DRIVER_MT7620A 1
#define CFG_FLASH_CFI           1
#endif

//CONFIG_INCA_IP
#define FPGA_BOARD_CLOCK_RATE 	25000000
#define PALMCHIP_CLOCK_DIVISOR 	16
#define FPGA_BOARD_CLOCK_DIVISOR 32

/* allowed values: 100000000, 133000000, and 150000000 */
/* for CFG_HZ only */
#define CPU_CLOCK_RATE			600000000 

#define SERIAL_CLOCK_DIVISOR 	16

#define CONFIG_BOOTDELAY		2	/* autoboot after 2 seconds	*/

#define CONFIG_BAUDRATE			115200

#define CONFIG_SERVERIP 		192.168.1.3
#define CONFIG_IPADDR 			192.168.1.1
#define CONFIG_ETHADDR 			"00:AA:BB:CC:DD:10"
/* valid baudrates */
#define CFG_BAUDRATE_TABLE	{ 9600, 19200, 38400, 57600, 115200 }

#define CONFIG_BOOTCOMMAND		"bootm" //"run flash_self"

#include <cmd_confdefs.h>

/*
 * Miscellaneous configurable options
 */
#define	CFG_LONGHELP				/* undef to save memory      */

#define	CFG_PROMPT				"MT7620# "

#define	CFG_CBSIZE				256		/* Console I/O Buffer Size   */
#define	CFG_PBSIZE 				(CFG_CBSIZE+sizeof(CFG_PROMPT)+16)  /* Print Buffer Size */
#define	CFG_MAXARGS				16		/* max number of command args*/
#define CFG_BOOTPARAMS_LEN		128*1024
#define CFG_HZ					CPU_CLOCK_RATE/2

#define CFG_SDRAM_BASE			0x80000000
#define CFG_SDRAM_SIZE 			( ( 1 << 20 ) * 64 ) //64MB sdram
#define CONFIG_LOADADDR  		( CFG_SDRAM_BASE + KERNEL_OFFSET )

//#define REG32(reg)             	(*((volatile unsigned int *)(reg)))
//#define REGWRITE32(reg, value) 	(*(volatile unsigned int *)(reg) = (volatile unsigned int)(value))

/* 
 * for TEST 
 */
#define CFG_CONSOLE_INFO_QUIET	

#define	CFG_LOAD_ADDR			0x80100000	/* default load address	*/
#define CFG_HTTP_DL_ADDR		0x80300000
#define CFG_SPINAND_LOAD_ADDR	0x80c00000
#define CFG_MEMTEST_START		0x80100000
#define CFG_MEMTEST_END			0x80400000


#define CFG_EMBEDED_SRAM_START 	0xA0800000
#define CFG_EMBEDED_SRAM_FOR_RXRING0_DESC 0xA0800000
#define CFG_EMBEDED_SRAM_FOR_TXRING0_DESC 0xA0800100
#define CFG_EMBEDED_SRAM_FOR_TXRING1_DESC 0xA0800200
#define CFG_EMBEDED_SRAM_BUF_START 0xA0800300
#define CFG_EMBEDED_SRAM_SDP0_BUF_START 0xA0804000
#define CFG_EMBEDED_SRAM_END   0xA0807FFF

/*-----------------------------------------------------------------------
 * FLASH and environment organization
 */
#define CFG_MAX_FLASH_BANKS			1	/* max number of memory banks */
#define CFG_MAX_FLASH_SECT			(263)	/* max number of sectors on one chip */

#define PHYS_FLASH_START			0xBC000000 /* Flash Bank #2 */
#define PHYS_FLASH_1				0xBC000000 /* Flash Bank #1 */

/* The following #defines are needed to get flash environment right */
#define	CFG_MONITOR_BASE			TEXT_BASE
#define	CFG_MONITOR_LEN				(192 << 10)
#define CFG_INIT_SP_OFFSET			0x400000
#define CFG_FLASH_BASE				PHYS_FLASH_1

#ifdef SPI_FLASH
#define CONFIG_BOOTARGS			"console=ttyS0,115200 root=31:2 mtdparts=spi_flash:"
#endif

/* timeout values are in ticks */
#define CFG_FLASH_ERASE_TOUT	(15UL * CFG_HZ) /* Timeout for Flash Erase */
#define CFG_FLASH_WRITE_TOUT	(5 * CFG_HZ) /* Timeout for Flash Write */
#define CFG_ETH_AN_TOUT			(5 * CFG_HZ) /* Timeout for Flash Write */
#define CFG_ETH_LINK_UP_TOUT	(5 * CFG_HZ) /* Timeout for Flash Write */
#define CFG_FLASH_STATE_DISPLAY_TOUT  (2 * CFG_HZ) /* Timeout for Flash Write */


#if 0//defined(SMALL_UBOOT_PARTITION)
#define CFG_BOOTLOADER_SIZE	0x20000
#define CFG_CONFIG_SIZE		0x10000
#define CFG_FACTORY_SIZE	0x00000
#else
#define CFG_BOOTLOADER_SIZE	0x30000
#define CFG_CONFIG_SIZE		0x10000
#endif

#if 0
#define CFG_FACTORY_SIZE	0x10000
#define CFG_ENV_ADDR		(CFG_FLASH_BASE + CFG_BOOTLOADER_SIZE)
#define CFG_FACTORY_ADDR	(CFG_FLASH_BASE + CFG_BOOTLOADER_SIZE + CFG_CONFIG_SIZE)
#define CFG_KERN_ADDR		(CFG_FLASH_BASE + (CFG_BOOTLOADER_SIZE + CFG_CONFIG_SIZE + CFG_FACTORY_SIZE))
#define CFG_ENV_SECT_SIZE	CFG_CONFIG_SIZE
#define CFG_ENV_SIZE		0x1000
#endif

#define CONFIG_FLASH_16BIT

#define CONFIG_NR_DRAM_BANKS	1
//#define CONFIG_NET_MULTI
#define CFG_RX_ETH_BUFFER		60

/*-----------------------------------------------------------------------
 * Cache Configuration
 */
#define CFG_DCACHE_SIZE		(16*1024)
#define CFG_ICACHE_SIZE		(16*1024)
#define CFG_CACHELINE_SIZE	16
/*
 * Lexra Cache Control Register fields
 */
#define CCTL_DINVAL             		0x00000001
#define CCTL_IINVAL             		0x00000002
#define CCTL_ILOCK              		0x0000000c
#define CCTL_IRAMFILL4          		0x00000010
#define CCTL_IRAMOFF            		0x00000020

#define RALINK_SYSCTL_BASE              0xB0000000
#define RALINK_TIMER_BASE               0xB0000100
#define RALINK_INTCL_BASE               0xB0000200
#define RALINK_MEMCTRL_BASE             0xB0000300
#define RALINK_RBUS_MATRIXCTL_BASE      0xB0000400
#define RALINK_UART_BASE                0xB0000500
#define RALINK_PIO_BASE                 0xB0000600
#define RALINK_NAND_CTRL_BASE           0xB0000810
#define RALINK_I2C_BASE                 0xB0000900
#define RALINK_I2S_BASE                 0xB0000A00
#define RALINK_SPI_BASE                 0xB0000B00
#define RALINK_UART_LITE_BASE           0xB0000C00
#define RALINK_MIPS_CNT_BASE            0xB0000D00
#define RALINK_PCM_BASE                 0xB0002000
#define RALINK_GDMA_BASE                0xB0002800
#define RALINK_CRYPTO_ENGING_BASE       0xB0004000
#define RALINK_FRAME_ENGINE_BASE        0xB0100000
#define RALINK_ETH_SW_BASE              0xB0110000
#define RALINK_USB_DEV_BASE             0xB0120000
#define RALINK_PCI_BASE                 0xB0140000
#define RALINK_11N_MAC_BASE             0xB0180000
#define RALINK_USB_HOST_BASE            0xB01C0000
#define RALINK_MCNT_CFG                 0xB0000D00
#define RALINK_COMPARE                  0xB0000D04
#define RALINK_COUNT                    0xB0000D08

#define RALINK_CPLLCFG0_REG				(RALINK_SYSCTL_BASE+0x54)
#define RALINK_CPLLCFG1_REG				(RALINK_SYSCTL_BASE+0x58)

/*
 * System Controller	(0x00300000)
 *   Offset
 *   0x10  -- SYSCFG		System Configuration Register
 *   0x30  -- CLKCFG1		Clock Configuration Register
 *   0x34  -- RSTCTRL		Reset Control Register
 *   0x38  -- RSTSTAT		Reset Status Register 
 *   0x60  -- GPIOMODE		GPIO Mode Control Register 
 */
//sys
#define RALINK_SYSCFG_REVID             (RALINK_SYSCTL_BASE+0x0C)
#define RALINK_SYSCFG_REG				(RALINK_SYSCTL_BASE+0x10)
#define RALINK_SYSCFG1_REG				(RALINK_SYSCTL_BASE+0x14)
#define RALINK_CLKCFG1_REG				(RALINK_SYSCTL_BASE+0x30)
#define RALINK_RSTCTRL_REG				(RALINK_SYSCTL_BASE+0x34)
#define RALINK_RSTSTAT_REG				(RALINK_SYSCTL_BASE+0x38)
#define RALINK_SYSCLKCFG_REG  			(RALINK_SYSCTL_BASE+0x3c)
#define RALINK_GPIOMODE_REG				(RALINK_SYSCTL_BASE+0x60)

//pio
#define RALINK_PRGIO_ADDR       		(RALINK_SYSCTL_BASE + 0x600) // Programmable I/O
#define RALINK_REG_PIOINT       		(RALINK_PRGIO_ADDR + 0)
#define RALINK_REG_PIOEDGE      		(RALINK_PRGIO_ADDR + 0x04)
#define RALINK_REG_PIORENA      		(RALINK_PRGIO_ADDR + 0x08)
#define RALINK_REG_PIOFENA      		(RALINK_PRGIO_ADDR + 0x0C)
#define RALINK_REG_PIODATA      		(RALINK_PRGIO_ADDR + 0x20)
#define RALINK_REG_PIODIR       		(RALINK_PRGIO_ADDR + 0x24)

//Interrupt Controller
#define RALINK_INTCTL_SYSCTL            (1<<0)
#define RALINK_INTCTL_TIMER0            (1<<1)
#define RALINK_INTCTL_WDTIMER           (1<<2)
#define RALINK_INTCTL_ILL_ACCESS        (1<<3)
#define RALINK_INTCTL_PCM               (1<<4)
#define RALINK_INTCTL_UART              (1<<5)
#define RALINK_INTCTL_PIO               (1<<6)
#define RALINK_INTCTL_DMA               (1<<7)
#define RALINK_INTCTL_PC                (1<<9)
#define RALINK_INTCTL_I2S               (1<<10)
#define RALINK_INTCTL_SPI               (1<<11)
#define RALINK_INTCTL_UARTLITE          (1<<12)
#define RALINK_INTCTL_CRYPTO            (1<<13)
#define RALINK_INTCTL_ESW               (1<<17)
#define RALINK_INTCTL_UHST              (1<<18)
#define RALINK_INTCTL_UDEV              (1<<19)
#define RALINK_INTCTL_GLOBAL            (1<<31)

//Reset Control Register
#define RALINK_SYS_RST                  (1<<0)
#define RALINK_TIMER_RST                (1<<8)
#define RALINK_INTC_RST                 (1<<9)
#define RALINK_MC_RST                   (1<<10)
#define RALINK_PCM_RST                  (1<<11)
#define RALINK_UART_RST                 (1<<12)
#define RALINK_PIO_RST                  (1<<13)
#define RALINK_DMA_RST                  (1<<14)
#define RALINK_I2C_RST                  (1<<16)
#define RALINK_I2S_RST                  (1<<17)
#define RALINK_SPI_RST                  (1<<18)
#define RALINK_UARTL_RST                (1<<19)
#define RALINK_FE_RST                   (1<<21)
#define RALINK_UHST_RST                 (1<<22)
#define RALINK_ESW_RST                  (1<<23)
#define RALINK_EPHY_RST                 (1<<24)
#define RALINK_UDEV_RST                 (1<<25)
#define RALINK_PCIE0_RST                (1<<26)
#define RALINK_PCIE1_RST                (1<<27)
#define RALINK_MIPS_CNT_RST             (1<<28)
#define RALINK_CRYPTO_RST               (1<<29)

//Clock Conf Register
#define RALINK_UPHY1_CLK_EN     		(1<<22)
#define RALINK_UPHY0_CLK_EN     		(1<<25)

/* CPLL related */
#define RALINK_CPLLCFG0_REG				(RALINK_SYSCTL_BASE+0x54)
#define RALINK_CPLLCFG1_REG				(RALINK_SYSCTL_BASE+0x58)
#define CPLL_SW_CONFIG                  (0x1UL << 31)
#define CPLL_MULT_RATIO_SHIFT           16
#define CPLL_MULT_RATIO                 (0x7UL << CPLL_MULT_RATIO_SHIFT)
#define CPLL_DIV_RATIO_SHIFT            10
#define CPLL_DIV_RATIO                  (0x3UL << CPLL_DIV_RATIO_SHIFT)
#define BASE_CLOCK                      40      /* Mhz */

#define RALINK_TIMER_STAT               (RALINK_TIMER_BASE + 0x00)
#define RALINK_TIMER0_LOAD              (RALINK_TIMER_BASE + 0x10)
#define RALINK_TIMER0_VAL               (RALINK_TIMER_BASE + 0x14)
#define RALINK_TIMER0_CTRL              (RALINK_TIMER_BASE + 0x18)
#define RALINK_TIMER1_LOAD              (RALINK_TIMER_BASE + 0x20)
#define RALINK_TIMER1_VAL               (RALINK_TIMER_BASE + 0x24)
#define RALINK_TIMER1_CTRL              (RALINK_TIMER_BASE + 0x28)

//SPI
#define RALINK_SPI0_STAT_REG            (RALINK_SPI_BASE + 0x00)
#define RALINK_SPI0_CFG_REG             (RALINK_SPI_BASE + 0x10)
#define RALINK_SPI0_CTL_REG             (RALINK_SPI_BASE + 0x14)
#define RALINK_SPI0_DATA_REG            (RALINK_SPI_BASE + 0x20)
#define RALINK_SPI0_ADDR_REG            (RALINK_SPI_BASE + 0x24)
#define RALINK_SPIBS_REG                (RALINK_SPI_BASE + 0x28)
#define RALINK_SPIUSER_REG              (RALINK_SPI_BASE + 0x2C)
#define RALINK_SPITXFIFO_REG            (RALINK_SPI_BASE + 0x30)
#define RALINK_SPIRXFIFO_REG            (RALINK_SPI_BASE + 0x34)
#define RALINK_SPIFIFOSTAT_REG          (RALINK_SPI_BASE + 0x38)
#define RALINK_SPIMODE_REG              (RALINK_SPI_BASE + 0x3c)
#define RALINK_SPI1_STAT_REG            (RALINK_SPI_BASE + 0x40)
#define RALINK_SPI1_CFG_REG             (RALINK_SPI_BASE + 0x50)
#define RALINK_SPI1_CTL_REG             (RALINK_SPI_BASE + 0x54)
#define RALINK_SPI1_DATA_REG            (RALINK_SPI_BASE + 0x60)
#define RALINK_SPI_DMA                  (RALINK_SPI_BASE + 0x80)
#define RALINK_SPI_DMA_STAT             (RALINK_SPI_BASE + 0x84)
#define RALINK_SPI_ARB_REG              (RALINK_SPI_BASE + 0xF0)

/*kurtis:define DDR parameter here for better performance*/
#ifdef ON_BOARD_DDR2
#define DDR_CFG0_REG					RALINK_MEMCTRL_BASE+0x40
#define RAS_OFFSET	23
#define TRFC_OFFSET	13
#define TRFI_OFFSET	0
//#ifdef  ON_BOARD_32BIT_DRAM_BUS
//#define BL_VALUE	2//BL=4
//#else
#define BL_VALUE	3 //BL=8
//#endif

#define CAS_OFFSET	4
#define BL_OFFSET	0
#define AdditiveLatency_OFFSET 3
#endif //DDR

/*
* for USB
*/
#ifdef RALINK_USB
#define CONFIG_USB_OHCI		1
#define CONFIG_SYS_USB_OHCI_MAX_ROOT_PORTS	2
#define CONFIG_SYS_USB_OHCI_REGS_BASE		0x101C1000
#define CONFIG_SYS_USB_OHCI_SLOT_NAME		"rt3680"
#define CONFIG_USB_EHCI		1
#define CONFIG_USB_STORAGE    1
#define CONFIG_DOS_PARTITION
#define LITTLEENDIAN
#define CONFIG_CRC32_VERIFY
#endif /* RALINK_USB */

#endif	/* __CONFIG_H */
