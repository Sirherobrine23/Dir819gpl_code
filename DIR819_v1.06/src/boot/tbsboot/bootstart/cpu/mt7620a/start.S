        
#include <config.h>
#include <version.h>
#include <asm/regdef.h>
#include <asm/mipsregs.h>
#include "../../../cpu/mt7620a/autoconf.h"

/*
 * LEAF - declare leaf routine
 */
#define LEAF(symbol)                                    \
                .globl  symbol;                         \
                .align  2;                              \
                .type   symbol,@function;               \
                .ent    symbol,0;                       \
symbol:         .frame  sp,0,ra

/*
 * END - mark end of function
 */
#define END(function)                                   \
                .end    function;                       \
                .size   function,.-function
                
#define UART_PRINT(msg)                                 \
		la   t5, msg;\
		1:      lbu  t6, 0(t5);\
		beqz t6, 2f;\
		addu t5, 1;\
		li	 s7, RALINK_UART_LITE_BASE;\
		sw   t6, 0x04(s7);\
        j 1b;\
        nop;\
 2:		nop;\
 		nop
		

#if 1
#define DISPLAYLED(d0,d1) 	nop
#else
#define DISPLAYLED(d0,d1) \
    la v0, GPIOBASE; \
    li t5, d0; \
	li t6, d1; \
	sw t5, 0x4(v0); \
2:  addi t6, -1; \
	bnez t6, 2b;\
	nop; \
	nop
#endif

//	Noop_Delay  <iteration> <register,default T1>, For All production
	.macro Noop_Delay iter reg=t1
		li		\reg,\iter
		li		t0, 0x1
	1:
		subu	\reg, t0
		nop
		bnez	\reg, 1b
		nop			
	.endm



        .text
        .set noreorder
		.globl _start              
_start:
		/* Initialize GOT pointer.*/	
		bal     beginning
		nop	
		.word   _GLOBAL_OFFSET_TABLE_
beginning:
		lw      gp, 0(ra)
		nop

		mfc0	t2, CP0_STATUS
		li		t3, 0x04/* Set up Status register */
		mtc0	t3, CP0_STATUS	
		mtc0	zero, CP0_WATCHLO/* Disable watch exceptions */
		li		t3, 0x03
		mtc0	t3, CP0_WATCHHI/* Clear Watch Status bits */
		mtc0	zero, CP0_CAUSE/* Setup cause register (clear cause code)  */
		mfc0	t2, CP0_CONFIG/* Set KSeg0 to cacheable */		
		li		t1, ~(0x07)
		and		t2, t2, t1
		ori		t2, t2, 0x03
		mtc0	t2, CP0_CONFIG
		mtc0	zero, CP0_COUNT/* Clear Count register */
		li		t2, -1
		mtc0	t2, CP0_COMPARE
		
		mfc0	t2, CP0_CONFIG, 1
		sll		t3, t2, 0x0A
		srl		t3, 29
		beqz	t3, icache_done
		nop
		li		t6, 2
		sllv	t3, t6, t3/* Now have true I cache line size in bytes */
		sll		t4, t2, 0x07
		srl		t4, 29
		li		t6, 64
		sllv	t4, t6, t4/* I cache sets per way */
		sll		t5, t2, 13
		srl		t5, 29/* I cache Assoc (-1) */
		add		t5, 1
		mul		t4, t4, t5/* Total number of sets */
		lui		t6, 0x8000/* Get a KSeg0 address for cacheops */
		mtc0	zero, CP0_TAGLO/* Clear TagLo registers */
		mtc0	zero, CP0_TAGHI/* Clear TagHi registers */
		move	t7, t4
icache_loop:		
		cache	0x8, 0(t6)
		add		t7, -1/* Decrement set counter */
		bnez	t7, icache_loop
		add		t6, t3/* Get next line address */
icache_done:
		sll		t3, t2, 19
		srl		t3, 29
		beqz	t3, dcache_done
		nop
		li		t6, 2
		sllv	t3, t6, t3/* Now have true D cache line size in bytes */
		sll		t4, t2, 16
		srl		t4, 29
		li		t6, 64
		sllv	t4, t6, t4/* D cache sets per way */
		sll		t5, t2, 22
		srl		t5, 29/* D cache Assoc (-1) */
		add		t5, 1
		mul		t4, t4, t5/* Get total number of sets */
		lui		t6, 0x8000/* Get a KSeg0 address for cacheops */
		mtc0	zero, CP0_TAGLO/* Clear TagLo registers */
		mtc0	zero, CP0_TAGHI/* Clear TagHi registers */
		mtc0	zero, CP0_TAGLO, 2/* Clear TagLo registers */
		mtc0	zero, CP0_TAGHI, 2/* Clear TagHi registers */
		move	t7, t4
dcache_loop:
		cache	0x9, 0(t6)
		add		t7, -1/* Decrement set counter */
		bnez	t7, dcache_loop
		add		t6, t3/* Get next line address */
dcache_done:
		mfc0	t2, CP0_CONFIG, 2/* Isolate L2 Cache Line Size */
		sll		t3, t2, 24
		srl		t3, 28
		beqz	t3, l2_cache_done/* Skip ahead if No L2 Cache */
		nop
		li		t6, 2
		sllv	t3, t6, t3/* Now have true L2 Cache line size in bytes */
		sll		t4, t2, 20
		srl		t4, 28
		li		t6, 64
		sllv	t4, t6, t4/* D Cache Sets per way */
		sll		t5, t2, 28/*  Isolate L2 Cache Associativity */
		srl		t5, 28/* Cache Assoc (-1) */
		add		t5, 1
		mul		t4, t4, t5/* Get total number of sets */
		lui		t6, 0x8000/* Get a KSeg0 address for cacheops */
		mtc0	zero, CP0_TAGLO, 4/* Clear L23TagLo register */
		mtc0	zero, CP0_TAGHI, 4/* Clear L23TagHi register */
		move	t7, t4/* L2 Cache Index Store Tag Cache Op */
l2_cache_loop:	
		cache	0xB, 0(t6)
		add		t7, -1/* Decrement set counter */
		bnez	t7, l2_cache_loop
		add		t6, t3 /* Get next line address */
l2_cache_done:
		mfc0	t3, CP0_CONFIG/* Determine if we have a TLB */
		sll		t3, 22
		srl		t3, 29
		li		t7, 0x1/* MT = 1  => TLB */
		bne		t3, t7, tlb_done
		nop
		mfc0 	t2, CP0_CONFIG, 1/* .word 0x400a8001 */
		sll		t3, t2, 1
		srl		t3, 26/* Number of TLB entries (-1) */
		mtc0	zero, CP0_ENTRYLO0/* EntryLo0 */
		mtc0	zero, CP0_ENTRYLO1/* EntryLo1 */
		mtc0	zero, CP0_PAGEMASK/* PageMask */
		mtc0	zero, CP0_WIRED/* Wired */
		li		t4, CFG_SDRAM_BASE
tlb_loop:
		mtc0	t3, CP0_INDEX/* Index register */
		mtc0	t4, CP0_ENTRYHI/* EntryHi */
		ssnop /* .word 0x00000040 */
		ssnop /* .word 0x00000040 */
		TLBWI
		add		t4, (2<<13)/* Add 8K to the address to avoid TLB conflict with previous entry */
		bnez	t3, tlb_loop
		add		t3, -1
tlb_done:
		
		la		s1, RALINK_SYSCTL_BASE
		lw		t1, 0x38(s1)
		srl		t1, t1, 0x01
		andi	t1, t1, 0x03
		bnez	t1, CPLL_DONE
		nop
		li		t6, CPLL_MULTI_RATIO_CFG
		sll		t6, t6, 0x02
		ori		t6, t6, 0x0
		sll		t6, t6, 0x06
		ori		t6, t6, CPLL_SSC_CFG
init_cpu_pll:
		la		t8, RALINK_CPLLCFG1_REG
		lw		t1, 0(t8)/* check AUX1[12] and AUX0[11] */
		li		t2, (1 << 12)
		and		t2, t6, t2
		move	t5, zero
		li		t4, (1 << 25)/* t4=1<<25, AUX1 as clock source */
		bnez	t2, init_pll_1
		nop
		li		t3, (1 << 11)
		and		t3, t6, t3
		li		t4, (1 << 24)/* t4=1<<24, AUX0 as clock source */
		movz	t4, zero, t3
init_pll_1:
		lw		t1, 0(t8)/* Switch clock source from CPU PLL to AUX1 */
		li		t2, ~(0x3 << 24)
		and		t1, t1, t2
		li		t2, (1 << 24)/* choose 480Mhz for backup clock source */
		movn	t2, zero, t4
		or		t1, t1, t2
		or		t1, t1, t4
		sw		t1, 0(t8)
		bnez	t4, CPLL_DONE 	
		nop
		
		la		t7, RALINK_CPLLCFG0_REG
		lw		t1, 0(t7)/* read CPLLCFG0 before SW_CFG = 1 */
		li		t2, (1 << 31)
		lw		t3, 0(t7)/* apply new params */
		or		t3, t3, t2
		sw		t3, 0(t7)
		nop

		lw		t2, 0(t8)/* Power down CPU PLL */
		li		t3, (1 << 26)
		or		t2, t2, t3
		sw		t2, 0(t8)
		and		t2, t6, 0x3F/* Set new CPU PLL freq & SSC */
		sll		t2, t2, 4
		srl		t3, t6, 6
		and		t3, t3, 0x3
		sll		t3, t3, 10	
		srl		t4, t6, 8
		and		t4, t4, 0x7
		sll		t4, t4, 16
		or		t2, t2, t3
		or		t2, t2, t4
		li		t3, ~((0x7 << 16) | (0x3 << 10) | (0x1F << 4))
		and		t1, t1, t3
		or		t1, t1, t2
		li		t5, (1 << 31)
		or		t1, t1, t5
		sw		t1, 0(t7)
		nop

		lw		t1, 0(t8)/* Power up CPU PLL */
		li		t2, ~(1 << 26)
		and		t1, t1, t2
		sw		t1, 0(t8)
		nop
		li		t2, (1 << 23)/* Polling CPU PLL PD Signal */
init_pll_2:
		lw		t1, 0(t8)
		nop	
		and		t1, t1, t2
		beqz	t1, init_pll_2
		nop

		lw		t1, 0(t8)/* Switch clock source from CPU_CLK_AUX0/AUX1 to CPU PLL */
		li		t2, ~(0x3 << 24)
		and		t1, t1, t2
		sw		t1, 0(t8)
		nop
CPLL_DONE:		
		nop
 		li		s2, 0x40A0A
		sw		s2, 0x3C(s1)/* Adjust CPU Freq from 60Mhz to 600Mhz(or CPLL freq stored from EE) */	
		Noop_Delay 39000 /* Delay 200 us */
		lw		t6, 0x60(s1)/* Init Uart Lite */
		nop
		and 	t6, ~((3 << 21) | (0xF << 16) | (1 << 11) | (0xF << 7) | (1 << 5))/* enable normal function spi, uartl, jtag, mdio, ge1 */
		or		t6, (2 << 21) | (1 << 20) | (0x2 << 18) | (0x2 << 16) | (1 << 13) | (1 << 12) | (0x2 << 7) | (1 << 0)/* set PERST_N, NAND|SD, MDIO pin to GPIO MODE *//* Disable P5_MAC_TO_PHY_MODE */
		sw		t6, 0x60(s1)/* Set GPIO mode */
		nop


		li      t2, (RALINK_EPHY_RST | RALINK_ESW_RST | RALINK_FE_RST | RALINK_UARTL_RST | RALINK_DMA_RST | RALINK_UART_RST | RALINK_MC_RST)
		sw      t2, 0x34(s1)/* Reset Uart1 Lite Uart0 ethernet phy, ethernet switch, frame engine */
		nop
#if 0
        sw      zero, 0x34(s1)/* Reset pin to 0 */
        la      s7, RALINK_UART_LITE_BASE
        sw      zero, 0x08(s7)/* Disable Uart Lite Interrupt */
        sw      zero, 0x10(s7)/* Disable FIFO control */
        li      t0, (1 << 7) | (3 << 0) /* LCR_DLAB | 8 bits transfer */
        sw      t0, 0x14(s7)/* Line Control Register */
        li      t1, 22//(40*1000*1000/16/ CONFIG_BAUDRATE)/* SERIAL_CLOCK_DIVISOR = 16 */
        sw      t1, 0x2C(s7)/* Clock Divider Divisor Latch Low */
        sw      zero, 0x30(s7)/* Clock Divider Divisor Latch High */
        li      t0, (3 << 0)/* 8 bits transfer */
        sw      t0, 0x14(s7)/* Line Control Register */
        li      t3, (1 << 6)
        li      t2, 0x54/* T */
        sw      t2, 0x04(s7)
        nop
#endif

		lw		t2, 0x14(s1)/* SDR and DDR initialization */
		nop
		and		t2, ~(0xFFF << 16)/* Use default SYSCFG1 setting */
		or		t2, (0x260 << 16)
		sw		t2, 0x14(s1)
		nop		
		sw		zero, 0x34(s1)/* Reset pin to 0 */
		nop
		li		t4, (1 << 21)
DDR_READY:
		li		s6, RALINK_MEMCTRL_BASE
		lw		t0, 0x44(s6)
		nop
		and		t2, t0, t4
		beqz	t2, DDR_READY
		nop/* Wait till reg DDR_CFG1 bit 21 equal to 1 (ready) */
		
		lw		t0, 0x48(s6)/* DDR_CFG2 */
		nop
		and		t0, ~((1 << 30) | (7 << 4))

		//or		t0, (3 << 4)/* ON_BOARD_DDR1 */
		or		t0, (4 << 4)/* ON_BOARD_DDR2 */
		or		t0, (1 << 30)/* ON_BOARD_DDR2 */
		or 		t0, (1<<11)/* ON_BOARD_DDR2 */
		sw		t0, 0x48(s6)
		nop
		
		lw		t2, 0x4C(s6)/* DDR_CFG3 */
		//and	t2, ~((1 << 10) | ( 7 << 3))/* ON_BOARD_DDR1 */
		and 	t2, ~(1<<6)/* ON_BOARD_DDR2 */
		or		t2, (1<<2)/* ON_BOARD_DDR2 */
#if 0		
		or		t2, 0x1
		sw		t2, 0x4C(s6)
		nop
#endif
		
		lw		t1, 0x50(s6)
		li		t2, ~(0x1F | 0xF0)
		and		t1, t1, t2

		ori 	t1, t1, 9 /* ON_BOARD_DDR2 && 512Mbit*/
		sw		t1, 0x50(s6)
		nop
#if 0		
/* Memory size and width settings */		
		//li		t6, 0x332A3434/* 128Mbit *//* 0x222E2324 256M */
		li 		t6, 0x22322323 /* ON_BOARD_DDR2 && 512Mbit*/ 
		or		t6, (1 << 17)/* 16 bits width */
		and		t6, ~(1 << 16)/* 16 bits width */
		and		t6, ~(3 << 12)/* Total width */
		or		t6, (2 << 12)/* ON_BOARD_16BIT_DRAM_BUS */
		sw		t6, 0x44(s6)
		nop
		j		SDRAM_INIT_DOWN
		nop
#endif	

		//li		t4, 2/* ON_BOARD_128M_DRAM_COMPONENT, 2=256M *///////////////////////
		li		t4, 1 /* ON_BOARD_DDR2 && 1=512M*/
		sll		t2, t4, 1
		sll		t2, t2, 2
		lui     t0, %hi(DDR2_CFG2_TBL) /* DDR1_ => DDR2_ */
		ori     t0, t0, %lo(DDR2_CFG2_TBL)
		addu    t0, t0, t2
		lw      t7, 0(t0)
		nop
		lui     t0, %hi(DDR2_CFG3_TBL)
		ori     t0, t0, %lo(DDR2_CFG3_TBL)
		addu    t0, t0, t2
		lw      t8, 0(t0)
		nop
		lui     t0, %hi(DDR2_CFG4_TBL)
		ori     t0, t0, %lo(DDR2_CFG4_TBL)
		addu    t0, t0, t2
		lw      t9, 0(t0)
		nop
		lui     t0, %hi(DDR2_CFG0_TBL)
		ori     t0, t0, %lo(DDR2_CFG0_TBL)
		addu    t0, t0, t2
		lw      t5, 0(t0)
		nop
		lui     t0, %hi(DDR2_CFG1_TBL)
		ori     t0, t0, %lo(DDR2_CFG1_TBL)
		addu    t0, t0, t2
		lw      s8, 0(t0)
		nop
		la		t0, RALINK_MEMCTRL_BASE
		sw		t7, 0x48(t0)//RALINK_DDR_CFG2
		nop
		sw		t8, 0x4C(t0)//RALINK_DDR_CFG3
		nop
		sw		t9, 0x50(t0)//RALINK_DDR_CFG4
		nop

//#if defined(ON_BOARD_DDR2)
		li		t1, 0x40404848
		sw		t1, 0x68(t0)//RALINK_DDR_CFG10
		nop
//#endif	

		sw		t5, 0x40(t0)//RALINK_DDR_CFG0
		nop
		sw		s8, 0x44(t0)//RALINK_DDR_CFG1
		nop		

		//li		t4, 0x24218618/* use aggressive cfg	//0x35A26500 */
		li 		t4, 0x249AA2E5 /* ON_BOARD_DDR2 && 512M*/

tRFCinit:
		la		t0, RALINK_MEMCTRL_BASE
		lw		t1, 0x1C(t0)
		nop
		and		t1, 0xFF000000
		or		t1, 0x01
		sw		t1, 0x1C(t0)
		nop
		lw		t1, 0x18(t0)
		nop
		or		t1, 0x10
		sw		t1, 0x18(t0)
		nop

		li		s5, RALINK_PIO_BASE
		li		t6, 0x00FF807F
		nop
		sw		t6, 0x24(s5)
		nop
		li		t6, 0xFFFFFFFF
		nop
		sw		t6, 0x2C(s5)
		nop
		la		s7,	RALINK_UART_LITE_BASE
		li		t9, 0x42 /* B */
		sw		t9, 0x04(s7)
		
//#if 0
		li 		t9, RALINK_SYSCTL_BASE + 0x0034
		lw 		t1, 0(t9)
	 	nop

		//2880 -> 3052 reset Frame Engine from 18 to 21
		or 		t1, 1 << 21
		sw 		t1, 0(t9)
		nop
		and		t1, ~(1 << 21)
		sw 		t1, 0(t9)
		nop
		nop
		nop
//#endif

#if 0
		li      t0, CFG_SDRAM_BASE/* Calculate RAM_SIZE, save it to sp */
		//li		t1, 0x10000000/* Maxium size is 256Mb */
		li		t1, 0x20000000/* Maxium size is 512Mb */
		li		sp, 4
		move	t6, t1
ram_wloop:		
		addu	t5, t0, t6
		nor		t4, zero, t6
		sw		t4, 0(t5)/* Run a simple memory test for determine the RAM size */
		bgt		t6, sp, ram_wloop
		srl		t6, t6, 1
ram_cmploop:
		addu	t5, t0, sp
		lw		t4, 0(t5)
		nor		t6, zero, sp
		bne		t4, t6, ram_size_exit
		nop
		sll		sp, sp, 1
		ble		sp, t1, ram_cmploop
		nop
ram_size_exit:
		srl		sp, sp, 1
#endif

		mfc0	t9, CP0_CONFIG
		li		t0, CONF_CM_UNCACHED
		mtc0	t0, CP0_CONFIG
		nop
		nop
		nop

	 	/* Set new stack pointer	
	 	 */
		li		t0, CFG_SDRAM_BASE + CFG_SDRAM_SIZE - SDRAM_SIZE + SP_OFFSET
		move	sp, t0			/* sp now adjusted to new one */

		li		t0, TEXT_BASE_BOOTSTART
		la		t3, in_ram
		nop
		lw		t2, -12(t3)	 	/* t2 <-- uboot_end_data	*/
		nop
		
		li		a2, CFG_SDRAM_BASE + CFG_SDRAM_SIZE - SDRAM_SIZE + BOOTSTART_OFFSET
		move	t1, a2			/* the new bootstart addr */

		/* Fix GOT pointer:
		 */
		move	t6, gp
		sub		gp, TEXT_BASE_BOOTSTART /* gp <-- offer set from bootstart */
		add		gp, a2			/* gp now adjusted to new one */
		sub		t6, gp, t6		/* t6 <-- relocation offset	*/

		/* Copy to ram
		 */
copy_to_ram:
		lw		t3, 0(t0)		/* t0 <-- old bootstart */
		sw		t3, 0(t1)		/* t1 <-- new bootstart */
		addu	t0, 4
		ble		t0, t2, copy_to_ram
		addu	t1, 4			/* delay slot */

		/* Jump to where we've relocated ourselves.
		 */
		addi	t0, a2, in_ram - _start
		j		t0
		nop

		.word	uboot_end_data
		.word	uboot_end
		.word	num_got_entries

in_ram:
		/* Now we want to update GOT
		 */
		lw		t3, -4(t0)		/* t3 <-- num_got_entries */
		nop
		addi	t4, gp, 8		/* Skipping first two entries */
		li		t2, 2			/* The Same as count from 2 */
		
gp_copy:
		lw		t1, 0(t4)
		nop
		beqz	t1, gp_loop
		add		t1, t6			/* t6 <-- the offer set value  */
		sw		t1, 0(t4)
		
gp_loop:
		addi	t2, 1
		blt		t2, t3, gp_copy
		addi	t4, 4			/* delay slot */
		
#if 0
		la      t9, mips_cache_reset	
		jalr    t9
		nop
#endif

		li		t9, CONF_CM_CACHABLE_NONCOHERENT
		mtc0	t9, CP0_CONFIG
		mtc0	t9, CP0_CONFIG
		nop
		nop
		nop

		/* Clear BSS
		 */
		lw		t1, -12(t0)		/* t1 <-- uboot_end_data	*/
		lw		t2, -8(t0)		/* t2 <-- uboot_end	*/
		move 	a0, t1			/* a0 <-- the pass parameter */
		add		t1, t6			/* adjust pointers */
		add		t2, t6			/* adjust pointers */

		sub		t1, 4
clean_bss_loop:	
		addi	t1, 4
		bltl	t1, t2, clean_bss_loop
		sw		zero, 0(t1)		/* delay slot */

		la		t9, uncompress_bootloader_second 
		j		t9
		nop

/* Exception handlers
 */
romReserved:
        b romReserved
romExcHandle:
        b romExcHandle	

  .text
  .global SDR_CFG0_TBL
SDR_CFG0_TBL:

  .word 0x51B283B3, 0x51B283B3
  .word 0x51B283B3, 0x51B283B3
  .word 0x51B283B3, 0x51B283B3
  .word 0x51B283B3, 0x51B283B3
  .text
  .global SDR_CFG1_TBL
SDR_CFG1_TBL:

  .word 0xC00103A9, 0xC00103A9
  .word 0xC01103A9, 0xC01103A9
  .word 0xC01203A9, 0xC01203A9
  .word 0xC02203A9, 0xC02203A9

  .text
  .global DDR1_CFG0_TBL
DDR1_CFG0_TBL:
/* 200MHZ */		/* 160MHZ */
  .word 0x34A1EB94, 0x239964A1/* 8MB */
  .word 0x34A1EB94, 0x239964A1/* 16MB */
  .word 0x34A1E5CA, 0x239964A1/* 32MB */
  .word 0x3421E5CA, 0x239984A1/* 64MB */
  .word 0x241B05CA, 0x239AB4A1/* 128MB */


  .text
  .global DDR1_CFG1_TBL
DDR1_CFG1_TBL:
/* 200MHZ */		/* 160MHZ */
  .word 0x20262324, 0x20262323/* 8MB */
  .word 0x202A2324, 0x202A2323/* 16MB */
  .word 0x202E2324, 0x202E2323/* 32MB */
  .word 0x20322324, 0x20322323/* 64MB */
  .word 0x20362334, 0x20362333/* 128MB */

  .text
/* 200MHZ */		/* 160MHZ */
DDR1_CFG2_TBL:
  .word 0x28000033, 0x00000033
  .word 0x28000033, 0x00000033
  .word 0x28000033, 0x00000033
  .word 0x28000033, 0x00000033
  .word 0x28000033, 0x00000033

DDR1_CFG3_TBL:
  .word 0x00000002, 0x00000002
  .word 0x00000002, 0x00000002
  .word 0x00000002, 0x00000002
  .word 0x00000002, 0x00000002
  .word 0x00000002, 0x00000002
DDR1_CFG4_TBL:
  .word 0x00000000, 0x00000000
  .word 0x00000000, 0x00000000
  .word 0x00000000, 0x00000000
  .word 0x00000000, 0x00000000
  .word 0x00000000, 0x00000000

  .text
  .global DDR2_CFG0_TBL
DDR2_CFG0_TBL:

  .word 0x2519E2E5, 0x23918250
  .word 0x249AA2E5, 0x239A2250
  .word 0x249B42E5, 0x2392A250
  .word 0x249CE2E5, 0x24140250

  .text
  .global DDR2_CFG1_TBL
DDR2_CFG1_TBL:

  .word 0x222E2323, 0x222E2322
  .word 0x22322323, 0x22322322
  .word 0x22362323, 0x22362322
  .word 0x223A2323, 0x223A2322

  .text
DDR2_CFG2_TBL:
  .word 0x68000C43, 0x40000A43
  .word 0x68000C43, 0x40000A43
  .word 0x68000C43, 0x40000A43
  .word 0x68000C43, 0x40000A43

  .text
DDR2_CFG3_TBL:

  .word 0x00000416, 0x00000416
  .word 0x00000416, 0x00000416
  .word 0x00000416, 0x00000416
  .word 0x00000416, 0x00000416

  .text
DDR2_CFG4_TBL:

  .word 0x0000000A, 0x00000006
  .word 0x0000000A, 0x00000008
  .word 0x0000000A, 0x00000008
  .word 0x0000000A, 0x00000008
