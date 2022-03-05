/*
 * MTD SPI driver for ST M25Pxx flash chips
 *
 * Author: Mike Lavender, mike@steroidmicros.com
 *
 * Copyright (c) 2005, Intec Automation Inc.
 *
 * Some parts are based on lart.c by Abraham Van Der Merwe
 *
 * Cleaned up and generalized based on mtd_dataflash.c
 *
 * This code is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/interrupt.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include <linux/mtd/mtd.h>
#include <linux/mtd/partitions.h>
#include <linux/delay.h>
#include <linux/version.h>
#include <linux/mtd/map.h>
#include <linux/mtd/gen_probe.h>
#include <linux/semaphore.h>
#include <linux/slab.h>
#include <linux/spi/spi.h>
#include <linux/spi/flash.h>
#include <asm/mach-ralink/rt_mmap.h>
#include "spi_flash.h"
#include <linux/magic.h>
#include <linux/types.h>
#include <linux/xattr.h>
#include "../fs/squashfs/squashfs_fs.h"

//#include <gpio.h>
//#include <flash_layout.h>
/******************************************************************************
 * SPI FLASH elementray definition and function
 ******************************************************************************/

/* SPICFG register bit field */
#define SPICFG_LSBFIRST                 (0<<8)
#define SPICFG_MSBFIRST                 (1<<8)

#define SPICFG_RXCLKEDGE_FALLING        (1<<5)          /* rx on the falling edge of the SPICLK signal */
#define SPICFG_TXCLKEDGE_FALLING        (1<<4)          /* tx on the falling edge of the SPICLK signal */

#define SPICFG_SPICLK_DIV2              (0<<0)          /* system clock rat / 2  */
#define SPICFG_SPICLK_DIV4              (1<<0)          /* system clock rat / 4  */
#define SPICFG_SPICLK_DIV8              (2<<0)          /* system clock rat / 8  */
#define SPICFG_SPICLK_DIV16             (3<<0)          /* system clock rat / 16  */
#define SPICFG_SPICLK_DIV32             (4<<0)          /* system clock rat / 32  */
#define SPICFG_SPICLK_DIV64             (5<<0)          /* system clock rat / 64  */
#define SPICFG_SPICLK_DIV128            (6<<0)          /* system clock rat / 128 */

#define SPICFG_SPICLKPOL                (1<<6)          /* spi clk*/

#define SPICFG_ADDRMODE                 (1 << 12)
#define SPICFG_RXENVDIS                 (1<<11)
#define SPICFG_RXCAP                    (1<<10)
#define SPICFG_SPIENMODE                (1<<9)

/* SPICTL register bit field */
#define SPICTL_HIZSDO                   (1<<3)
#define SPICTL_STARTWR                  (1<<2)
#define SPICTL_STARTRD                  (1<<1)
#define SPICTL_SPIENA_LOW               (0<<0)          /* #cs low active */
#define SPICTL_SPIENA_HIGH              (1<<0)


/* SPI COMMAND MODE */
#define SPICTL_START                            (1<<4)
#define SPIFIFO_TX_FULL                         (1 << 17)
#define SPIFIFO_RX_EMPTY                        (1 << 18)
#define SPIINT_SPIDONE                          (1<<0)
#define SPIINT_ILLSPI                           (1<<1)
#define SPIINT_RX_EMPTY_RD                      (1<<2)
#define SPIINT_TX_FULL_WR                       (1<<3)
#define SPIINT_DMA_EMPTY_RD                     (1<<4)
#define SPIINT_DMA_FULL_WR                      (1<<5)
/* SPI USER MODE */
#define SPIUSR_SINGLE                           0x1
#define SPIUSR_DUAL                                     0x2
#define SPIUSR_QUAD                                     0x4
#define SPIUSR_NO_DATA                          0x0
#define SPIUSR_READ_DATA                        0x1
#define SPIUSR_WRITE_DATA                       0x2
#define SPIUSR_NO_DUMMY                         0x0
#define SPIUSR_ONE_DUMMY                        0x1
#define SPIUSR_TWO_DUMMY                        0x2
#define SPIUSR_THREE_DUMMY                      0x3
#define SPIUSR_NO_MODE                          0x0
#define SPIUSR_ONE_MODE                         0x1
#define SPIUSR_NO_ADDR                          0x0
#define SPIUSR_ONE_BYTE_ADDR            0x1
#define SPIUSR_TWO_BYTE_ADDR            0x2
#define SPIUSR_THREE_BYTE_ADDR          0x3
#define SPIUSR_FOUR_BYTE_ADDR           0x4
#define SPIUSR_NO_INSTRU                        0x0
#define SPIUSR_ONE_INSTRU                       0x1

/* SPIARB register bit field */
#define SPIARB_ARB_EN                   (1<<31)

#ifdef RALINK_SPI_CS0_HIGH_ACTIVE
#define SPIARB_SPI0_ACTIVE_MODE         1
#else
#define SPIARB_SPI0_ACTIVE_MODE         0
#endif

#ifdef RALINK_SPI_CS1_HIGH_ACTIVE
#define SPIARB_SPI1_ACTIVE_MODE         1
#else
#define SPIARB_SPI1_ACTIVE_MODE         0
#endif

#define SPI_FIFO_SIZE                   16
#define SPIC_READ_BYTES                 (1<<0)
#define SPIC_WRITE_BYTES                (1<<1)
#define SPIC_USER_MODE                  (1<<2)
#define SPIC_4B_ADDR                    (1<<3)

#define reg_read32(reg)         (*((volatile unsigned int *)(reg)))
#define reg_write32(reg, value) (*(volatile unsigned int *)(reg) = (volatile unsigned int)(value))

static spinlock_t spi_lock = SPIN_LOCK_UNLOCKED;
static struct semaphore spi_sem;
static struct timer_list spi_timer;
static wait_queue_head_t spi_wq;
struct mtd_info *minfo = NULL;
static struct spi_flash_params *spi_dev;
static const char *part_probes[] = {"cmdlinepart", "RedBoot", NULL};
//int image_update_pending = -1; /* Do not schdule while in image upgrade procedure */
int image_update_pending = 1; /*Sudenghai 2014-3-19, 不采用定时器方式，一般情况下写太慢*/


#ifdef CONFIG_MTD_PARAM_FIX
#define MTD_BOOT_PART_SIZE  0x30000
#define MTD_ROOTFS_PART_SIZE	0x30000
#define	MTD_KERN_PART_SIZE	0x30000
#define MTD_MULTILANG_PART_SIZE  0x20000

static struct mtd_partition tbs_partitions[] = {
    {
            .name       =         "boot",
            .size       =         MTD_BOOT_PART_SIZE,
            .offset     =         0,
    },
    {
            .name       =         "kernel",
            .size       =         MTD_KERN_PART_SIZE,
            .offset     =         MTD_BOOT_PART_SIZE,
    },
    {
            .name       =         "rootfs",
            .size       =         MTD_ROOTFS_PART_SIZE,
            .offset     =         MTD_KERN_PART_SIZE,
    },
	{
            .name       =         "multilang",
            .size       =         MTD_ROOTFS_PART_SIZE,
            .offset     =         MTD_KERN_PART_SIZE,
    }
};
#endif

static int spic_busy_wait(void)
{
	unsigned int mips_bus_feq = 200 * 1000 * 1000;
	unsigned int spi_wait_nsec = (8 * 1000 / ((mips_bus_feq / 1000 / 1000 / SPICFG_SPICLK_DIV8) )) >> 1;
	do {
		if((reg_read32(RALINK_SPI0_STAT_REG) & 0x01) == 0) {
			return 0;
		}
	} while (spi_wait_nsec >> 1);
	printk("%s: fail \n", __func__);
	return -1;
}

static int raspi_cmd(u8 cmd, u32 addr, u8 mode, u8 *buf, size_t len, const u32 user, const int flag)
{
	unsigned int reg;
	unsigned int count;
	unsigned long flags;
	int retval = 0;
	
	
	//printf("code = %x, addr = %x, mode = %x, buf = %x, size = %d, user = %x, flag = %x\n", cmd, addr, mode, buf, n_buf, user, flag);
	spin_lock_irqsave(&spi_lock, flags);
	reg = reg_read32(RALINK_SPI0_CFG_REG);
	reg |= (SPICFG_SPIENMODE | SPICFG_RXENVDIS);
	reg_write32(RALINK_SPI0_CFG_REG, reg);
	reg_write32(RALINK_SPI0_DATA_REG, cmd);
	reg_write32(RALINK_SPIMODE_REG, (mode << 24));
	if(flag & SPIC_4B_ADDR) {
		reg_write32(RALINK_SPI0_ADDR_REG, addr);
	} else {
		reg_write32(RALINK_SPI0_ADDR_REG, (addr << 8));
	}
	reg_write32(RALINK_SPIBS_REG, len);
	if(flag & SPIC_USER_MODE) {
		reg_write32(RALINK_SPIUSER_REG, user);
	} else {
		reg_write32(RALINK_SPIUSER_REG, 0);
	}
	reg_write32(RALINK_SPI0_CTL_REG, SPICTL_START);
	if(flag & SPIC_READ_BYTES) {/* Read */
		if(NULL == buf) {
			printk("NULL pointer\n");
			return -1;
		}
		for(retval = 0; retval < len; ) {
			do {
				reg = (u32) (reg_read32(RALINK_SPIFIFOSTAT_REG) & 0xff);
			}while(reg == 0);
			for(count = reg; count > 0; count--) {
				buf[retval++] = (unsigned char)reg_read32(RALINK_SPIRXFIFO_REG);
			}
		}
	} else if (flag & SPIC_WRITE_BYTES) {/* Write */
		if(buf == 0) {
			printk("NULL pointer\n");
			return -1;
		}
		if(len <= SPI_FIFO_SIZE) {
			count = len;
		} else {
			count = SPI_FIFO_SIZE;
		}
		for(retval = 0; retval < len; ) {
			while(count--) {
				reg_write32(RALINK_SPITXFIFO_REG, buf[retval++]);
			}
			do {
				reg = ((reg_read32(RALINK_SPIFIFOSTAT_REG ) & 0xff00) >> 8);
			} while(reg >= SPI_FIFO_SIZE);
			count = SPI_FIFO_SIZE - reg;
			if((retval + count) > len) {
				count = len - retval;
			}
		}
	}
	if(spic_busy_wait()) {
		retval = -1;
	}
	reg_read32(RALINK_SPI0_CFG_REG) &= ~(SPICFG_SPIENMODE | SPICFG_RXENVDIS);
	spin_unlock_irqrestore(&spi_lock, flags);
	
	return retval;
}

static void spi_poll_write_done(void)
{
	unsigned char reg;
	unsigned int i;
	
	for(i = 0; i < 0xFFFF; i++) {
		raspi_cmd(CMD_RDSR, 0, 0, &reg, 1, 0, SPIC_READ_BYTES);
		if(SR_WIP != (reg & SR_WIP)) {
			break;
		}
	}
	if(0xFFFF == i) {
		printk("%s: Timed out!\n", __func__);
	}
}

static void spi_check_write_done(unsigned long v)
{
	unsigned char reg;

	raspi_cmd(CMD_RDSR, 0, 0, &reg, 1, 0, SPIC_READ_BYTES);
	if(0 == (reg & SR_WIP)) {
		if(waitqueue_active(&spi_wq)) {
			wake_up(&spi_wq);
		}		
	} else {
		mod_timer(&spi_timer, jiffies + 10);
	}
}

static void spi_wait_write_process(signed long timeout)
{
	DECLARE_WAITQUEUE(wait, current);
	set_current_state(TASK_UNINTERRUPTIBLE);
	add_wait_queue(&spi_wq, &wait);
	mod_timer(&spi_timer, jiffies + timeout);
	schedule();
	remove_wait_queue(&spi_wq, &wait);
}


/****************************************************************************/
/*
 * Erase an address range on the flash chip.  The address range may extend
 * one or more erase sectors.  Return an error is there is a problem erasing.
 */
static int mtd_spi_erase(struct mtd_info *mtd, struct erase_info *instr)
{
	size_t size = 0;
	int ret_val = -EINVAL;
	signed long timeout = HZ / 5;
	
	//printk("%s: addr:%x len:%x\n", __func__, instr->addr, instr->len);	
	if(instr->addr + instr->len > mtd->size) {/* sanity checks */
		printk("%s: address out of range!\n", __func__);
		goto out;
	}	
	for(size = 0; size < instr->len; size += mtd->erasesize) {/* now erase those sectors */
		down(&spi_sem);
		raspi_cmd(CMD_WREN, 0, 0, 0, 0, 0, 0);
		raspi_cmd(CMD_BE, (instr->addr + size), 0, 0, 0, 0, 0);
		printk(".");
		if(image_update_pending > 0) {
			timeout /= 2;
		}
		spi_wait_write_process(timeout);/* Do schedule in waiting time */
		up(&spi_sem);
	}
	ret_val = 0;
out:
	if(0 != ret_val) {
		instr->state = MTD_ERASE_FAILED;
	} else {
		instr->state = MTD_ERASE_DONE;
	}
	if(instr->callback) {
		instr->callback(instr);
	}

	return ret_val;
}


/*
 * Read an address range from the flash chip.  The address range
 * may be any size provided it is within the physical boundaries.
 */
static int mtd_spi_read(struct mtd_info *mtd, loff_t from, size_t len, size_t *retlen, u_char *buf)
{
	int ret_val = -EINVAL;
	
//	printk("%s: from:%x len:%x \n", __func__, from, len);
	if((from + len > mtd->size) || (len <= 0)) {/* sanity checks */
		printk("The length is out of flash space.\n");
		goto out;
	}	
	ret_val = -EIO;
	down(&spi_sem);
	*retlen = raspi_cmd(CMD_READ, from, 0, buf, len, 0, SPIC_READ_BYTES);
	up(&spi_sem);
	if(*retlen == len) {
		ret_val = 0;
	}	
out:
	return ret_val;
}

/*
 * Write an address range to the flash chip.  Data must be written in
 * FLASH_PAGESIZE chunks.  The address range may be any size provided
 * it is within the physical boundaries.
 */
static int mtd_spi_write(struct mtd_info *mtd, loff_t to, size_t len, size_t *retlen, const u_char *buf)
{
	size_t page_offset;
	size_t writelen = 0;
	size_t prog_size;
	int ret_val = 0;
	int rc = 0;
	
//	fldebug("%s: to:%x len:%x \n", __func__, to, len);
	if(len == 0) {/* sanity checks */
		goto out;
	}
	if(to + len > mtd->size) {
		printk("%s: end address %llx + %#x out of flash space!\n", __func__, to, (unsigned int)len);
		return -EINVAL;
	}
	page_offset = (size_t)to % spi_dev->page_size;/* what page do we start with? */
	
	ret_val = -EIO;
	for(writelen = 0; writelen < len; ) {
		prog_size = len - writelen;
		if(prog_size > (spi_dev->page_size - page_offset)) {
			prog_size = spi_dev->page_size - page_offset;
		}
		down(&spi_sem);
		raspi_cmd(CMD_WREN, 0, 0, 0, 0, 0, 0);
		rc = raspi_cmd(CMD_PP, to + writelen, 0, (u8 *)buf + writelen, prog_size, 0, SPIC_WRITE_BYTES);
		if((writelen & 0xFFFF) == 0) {
			//printk("#");
		}
		if((writelen & 0x8000) == 0) {
			if((image_update_pending <= 0) && (writelen > 0)) {
				spi_wait_write_process(10);/* Do schdule in waiting time */
			} else {
				spi_poll_write_done();
			}			
		} else {
			spi_poll_write_done();
		}
		up(&spi_sem);
		if(rc < prog_size) {
			printk("%s: rc:%x page_size:%x\n", __func__, rc, prog_size);
			goto err;
		}
		writelen += rc;
		page_offset = 0;
	}
	ret_val = 0;
err:
	*retlen = writelen;
out:

	return ret_val; 
}
#ifdef CONFIG_MTD_PARAM_FIX
static uint64_t lookup_flash_rootfs_offset(struct mtd_info *mtd, struct spi_flash_params *flash)
{
	uint64_t off = 0 , len = 0, start = 0;
	unsigned char buf[512] = { 0 };
	struct squashfs_super_block *squashfsb = NULL;
	int i_flag = 0;

	squashfsb = (void *) buf;
	start = MTD_BOOT_PART_SIZE;

	for (off = start; off < flash->chip_size; off += (64 * 1024)) 
	{		
		memset(buf, 0xe5, sizeof(buf));
		/*
		 * Read block 0 to test for romfs and cramfs superblock
		 */
		if (mtd->read(mtd, off, sizeof(buf), &len, buf) ||
		    len != sizeof(buf))
		{
			continue;
		}
		//printk("squashfsb->s_magic=%x, off=0x%012llx\n", le32_to_cpu(squashfsb->s_magic), off);


		if (le32_to_cpu(squashfsb->s_magic) == SQUASHFS_MAGIC) 
		{
			i_flag = 1;
			//printk("squashfsb->s_magic=%x\n", squashfsb->s_magic);
			//printk("%s: squash filesystem found at block %d, offset=0x%012llx\n", mtd->name, off/mtd->erasesize, off);
			printk("%s: squash filesystem found at block , offset=0x%012llx\n", mtd->name, off);
			break;
		}
	}

	if(i_flag)
	{	
		return off;
	}

	return 0;

}
#endif
/****************************************************************************/
/*
 * board specific setup should have ensured the SPI clock used here
 * matches what the READ command supports, at least until this driver
 * understands FAST_READ (for clocks over 25 MHz).
 */ 
static int spi_init(void)
{
	struct mtd_partition *mtd_parts;
	unsigned long flash_id = 0;
	unsigned int temp;	
	int np, i, ret_val = -ENOMEM;
#ifdef CONFIG_MTD_PARAM_FIX
	uint64_t rootfs_offset = 0;
#endif
	minfo = kzalloc(sizeof(struct mtd_info), GFP_KERNEL);
	if(NULL == minfo) {
		printk("%s: Failed to allocate memory for MTD device\n", __func__);
		goto out;
	}
	setup_timer(&spi_timer, spi_check_write_done, (unsigned long)minfo);
	init_waitqueue_head(&spi_wq);	
	sema_init(&spi_sem, 1);
	down(&spi_sem);
	#if 0
	temp = reg_read32(CR_RSTCTRL_REG);
	temp |= RALINK_SPI_RST;/* reset spi block */
	reg_write32(CR_RSTCTRL_REG, temp);
	udelay(1);
	temp &= ~(RALINK_SPI_RST);
	reg_write32(CR_RSTCTRL_REG, temp);
	reg_write32(RALINK_SPI0_CFG_REG, SPICFG_MSBFIRST | SPICFG_TXCLKEDGE_FALLING | SPICFG_SPICLK_DIV8 | SPICFG_SPICLKPOL);
	reg_write32(RALINK_SPI0_CTL_REG, SPICTL_HIZSDO | SPICTL_SPIENA_HIGH);
	#endif	
	raspi_cmd(CMD_RDID, 0, 0, (unsigned char *)(&temp), sizeof(temp), 0, SPIC_READ_BYTES);
	up(&spi_sem);
	flash_id = ((temp & 0xff) << 16) | (temp & 0xff00) | ((temp >> 16) & 0xff);
	for(i = 0; ; i++) {
		spi_dev = (struct spi_flash_params *)&flash_table[i];
		if((flash_id == spi_dev->id) || (0 == spi_dev->id)) {
			break;
		}
	}
	minfo->size      = spi_dev->chip_size;
	minfo->erasesize = spi_dev->erasesize;
	minfo->type      = MTD_NORFLASH;
	minfo->erase     = mtd_spi_erase;
	minfo->write     = mtd_spi_write;
	minfo->read      = mtd_spi_read;
	minfo->flags     = MTD_CAP_NORFLASH;
	minfo->name      = "spi_flash";
	minfo->writesize = 1;
	minfo->owner     = THIS_MODULE;	
	printk("FLASH: %2ld MB %s at mode %d\r\n", (spi_dev->chip_size >> 20), spi_dev->name, spi_dev->mode);
#ifdef CONFIG_MTD_PARAM_FIX
	rootfs_offset = lookup_flash_rootfs_offset(minfo, &flash_table[i]);

	if(rootfs_offset > 0)
	{
		for(i = 0; i < ARRAY_SIZE(tbs_partitions); i++)
		{
			if(0 == strcmp(tbs_partitions[i].name, "kernel"))
			{				
				tbs_partitions[i].offset = MTD_BOOT_PART_SIZE;
				tbs_partitions[i].size = (uint64_t)(rootfs_offset - MTD_BOOT_PART_SIZE);
			}

			if(0 == strcmp(tbs_partitions[i].name, "rootfs"))
			{
				tbs_partitions[i].offset = rootfs_offset;
				tbs_partitions[i].size = spi_dev->chip_size - rootfs_offset - MTD_MULTILANG_PART_SIZE;
			}
			if(0 == strcmp(tbs_partitions[i].name, "multilang"))
			{
				tbs_partitions[i].offset = spi_dev->chip_size - MTD_MULTILANG_PART_SIZE;
				tbs_partitions[i].size = MTD_MULTILANG_PART_SIZE;
			}
			//printk("%s:%d rootfs offset=0x%012llx\n", __FUNCTION__, __LINE__, tbs_partitions[i].offset);
			//printk("%s:%d rootfs size=0x%012llx\n", __FUNCTION__, __LINE__, tbs_partitions[i].size);
		}
		
		add_mtd_partitions(minfo, tbs_partitions, ARRAY_SIZE(tbs_partitions));
		
		ret_val = 0;
	}
	else
	{
		printk("%s: No partitions found\n", __func__);
	}
#else
	np = parse_mtd_partitions(minfo, part_probes, &mtd_parts, 0);
	if(np > 0) {		
		add_mtd_partitions(minfo, mtd_parts, np);
		ret_val = 0;
   	} else {
		printk("%s: No partitions found\n", __func__);
	}
#endif
out:
	return ret_val;
}

static void __exit spi_exit(void)
{
    /* Do nothing */
}



module_init(spi_init);
module_exit(spi_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jerry Xia");
MODULE_DESCRIPTION("MTD SPI driver for Ralink flash chips");


