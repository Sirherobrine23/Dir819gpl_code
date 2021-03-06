/**********************************************************************
 Copyright (c), 1991-2011, T&W ELECTRONICS(SHENTHEN) Co., Ltd.

 文件名称 : leds-rt63368.c
 文件描述 : 本文件为RT63368 ADSL方案LED驱动程序

 修订记录 :
          1 创建 : pengyao
            日期 : 2012-05-25
            描述 :
**********************************************************************/

#include <linux/kernel.h>
#include <linux/module.h>
#include <led.h>
#include <gpio.h>
#include <autoconf.h>

extern struct led_dev led_table[];                   /* 定义在product.c中 */
extern unsigned long pci_base_addr[NR_WLAN_CHIPS];   /* 定义在gpio.c中 */
void rt_led_on(struct led_dev *led)
{
	unsigned int port, value;
	unsigned long reg;
	
	if((led->name >= led_lan_1) && (led->name <= led_lan_5)) {
		port = (unsigned int)(led->name - led_lan_1);
		PHY_led_ops(port, LED_BOOT_ON);
		#ifdef CONFIG_TCPHY
		port += RT63368_GPIO07;
		gpio_config(port, GPIO_OUT);
		gpio_write(port, led->level);
		#endif
	} else if(led_wlan_1 == led->name) {
		reg = pci_base_addr[0];
		if(0 != reg) {
			leddebug("pci_base_addr=%#x\n", reg);
			value = REG32(reg + WLAN_ASIC_VER_ID);/* Read mac base address register first */
			reg += WLAN_LED_CONFIG;
			value = REG32(reg);
			if(value & (1 << 30)) {/* LED polarity active HIGH */
				value &= ~(0x03 << 28); /* LED_ACT_N off */
			} else { /* LED polarity active LOW */
				value |= (0x03 << 28); /* LED_ACT_N always on */
			}
			REGWRITE32(reg, value); /* 0x30031432 */
		} else {
			leddebug("pci_base_addr not registered yet!\n");
		}
	} else if(led_wlan_2 == led->name) {
		reg = pci_base_addr[NR_WLAN_CHIPS - 1];
		if(0 != reg) {
			leddebug("pci_base_addr=%#x\n", reg);
			value = REG32(reg + WLAN_ASIC_VER_ID);/* Read mac base address register first */
			reg += WLAN_LED_CONFIG;
			value = REG32(reg);
			if(value & (1 << 30)) {/* LED polarity active HIGH */
				value &= ~(0x03 << 28); /* LED_ACT_N off */
			} else { /* LED polarity active LOW */
				value |= (0x03 << 28); /* LED_ACT_N always on */
			}
			REGWRITE32(reg, value); /* 0x30031432 */
		} else {
			leddebug("pci_base_addr not registered yet!\n");
		}
	} else {
	    gpio_write(led->gpio, led->level);
	}
}

void rt_led_off(struct led_dev *led)
{
	unsigned int port, value;
	unsigned long reg;
	
	if((led->name >= led_lan_1) && (led->name <= led_lan_5)) {
		port = (unsigned int)(led->name - led_lan_1);
		PHY_led_ops(port, LED_BOOT_OFF);
		#ifdef CONFIG_TCPHY
		port += RT63368_GPIO07;
		gpio_config(port, GPIO_OUT);
		if(GPIO_LEVEL_HIGH == led->level) {
			gpio_write(port, GPIO_LEVEL_LOW);
		} else {
			gpio_write(port, GPIO_LEVEL_HIGH);
		}
		#endif
	} else if(led_wlan_1 == led->name) {
		reg = pci_base_addr[0];
		if(0 != reg) {
			leddebug("pci_base_addr=%#x\n", reg);
			value = REG32(reg + WLAN_ASIC_VER_ID);/* Read mac base address register first */
			reg += WLAN_LED_CONFIG;
			value = REG32(reg);
			if(value & (1 << 30)) {/* LED polarity active HIGH */
				value |= (0x03 << 28); /* LED_ACT_N always on */
			} else { /* LED polarity active LOW */
				value &= ~(0x03 << 28); /* LED_ACT_N off */
			}
			REGWRITE32(reg, value); /* 0x31432 */
		} else {
			leddebug("pci_base_addr not registered yet!\n");
		}
	} else if(led_wlan_2 == led->name) {
		reg = pci_base_addr[NR_WLAN_CHIPS - 1];
		if(0 != reg) {
			leddebug("pci_base_addr=%#x\n", reg);
			value = REG32(reg + WLAN_ASIC_VER_ID);/* Read mac base address register first */
			reg += WLAN_LED_CONFIG;
			value = REG32(reg);
			if(value & (1 << 30)) {/* LED polarity active HIGH */
				value |= (0x03 << 28); /* LED_ACT_N always on */
			} else { /* LED polarity active LOW */
				value &= ~(0x03 << 28); /* LED_ACT_N off */
			}
			REGWRITE32(reg, value); /* 0x31432 */
		} else {
			leddebug("pci_base_addr not registered yet!\n");
		}
	} else {
		if(led->level) {
			gpio_write(led->gpio, GPIO_LEVEL_LOW);
		} else {
			gpio_write(led->gpio, GPIO_LEVEL_HIGH);
		}
	}
}

struct led_hw_handler hw_handler = {
	rt_led_on, 
	rt_led_off,
};

int __init rt63368_led_init(void)
{
	unsigned int i;
	int ret;

	ret = led_core_init();/* 初始化LED CORE */
	if(ret < 0) {
		goto out;
	}
	/* 把handler注册到LED CORE。注意:要先注册hanlder，再注册LED。*/
	ret = led_hw_handle_register(&hw_handler);
	if(ret<0){
		printk(KERN_ERR "Error:fail to register hw_handler.\n");
		goto out;
	}
	printk("Register led device for %s:", PRODUCT);
	/* 把LED注册到LED CORE */
	for(i=0; led_table[i].name != led_end;i++){
		gpio_config(led_table[i].gpio, GPIO_OUT);
		ret = led_dev_register(&led_table[i]);
		if(ret<0){
			printk(KERN_ERR "Error:fail to register led_table[%d].\n",i);
			break;
		}
		printk(" %02d", (unsigned int)led_table[i].name);		
	}
	printk("\n");
	for(i = 0; i < NR_WLAN_CHIPS; i++) {
		printk("PCIE IO base address[%d]=0x%lX\n", i, pci_base_addr[i]);
	}
out:	
	return ret;
}

void __exit rt63368_led_exit(void)
{
	int i;
	int ret;

	/* 先注销LED，再注销handler */
	for(i=0; led_table[i].name != led_end;i++){
		ret = led_dev_unregister(&led_table[i]);
		if(ret<0){
			printk(KERN_ERR "Error:fail to unregister led_table[%d]\n",i);
		}
	}

	ret = led_hw_handle_unregister(&hw_handler);

	if(ret<0){
		printk(KERN_ERR "Error:fail to unregister hw_handler.\n");
	}
	led_core_exit();
}

module_init(rt63368_led_init);
module_exit(rt63368_led_exit);
MODULE_AUTHOR("xiachaoren");
MODULE_LICENSE("GPL");
