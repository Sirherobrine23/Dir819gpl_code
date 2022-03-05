/**********************************************************************
 Copyright (c), 1991-2011, T&W ELECTRONICS(SHENTHEN) Co., Ltd.
 MT7620 LEDs Driver                     by xiachaoren 2013-06-25
**********************************************************************/

#include <linux/kernel.h>
#include <linux/module.h>
#include <asm/mach-ralink/rt_mmap.h>
#include <linux/net.h>
#include <led.h>
#include <gpio.h>
#include <autoconf.h>

extern struct led_dev mt7620a_leds[];                   /* Defined in product.c */
extern void PHY_led_ops(unsigned int port, unsigned int optcode);/* LAN Led Control */

static void mt7620a_led_on(struct led_dev *dev)
{
	unsigned int port;
	unsigned int reg;

/*增加针对AC750的判断*/
#ifdef  CONFIG_RALINK_MT7620A
	if((dev->gpio>=GPIO40)&&(dev->gpio<=GPIO44))//针对以前的PAN灯进行处理
	{
		port =  (unsigned int)(dev->gpio - GPIO40);//判断GPIO口
		PHY_led_ops(port, led_on_trig);//开启GPIO模式
		gpio_config(dev->gpio, GPIO_OUT);//设置方向
	}
#else
	if((dev->name >= led_lan_1) && (dev->name <= led_lan_5)) {
		port = (unsigned int)(dev->name - led_lan_1);
		PHY_led_ops(port, led_on_trig);
		gpio_config(dev->gpio, GPIO_OUT);
	}
#endif
	if(dev->gpio < GPIO73) {
		if(GPIO72 == dev->gpio) {
			reg = reg_read32(CR_GPIO_SHARE);
			if(0 == (reg & BIT(13))) {
				reg |= BIT(13);
				reg_write32(CR_GPIO_SHARE, reg);
			}
		}
	    gpio_write(dev->gpio, dev->level);
	}
}

static void mt7620a_led_off(struct led_dev *dev)
{
	unsigned int port;
	unsigned int reg;

#ifdef  CONFIG_RALINK_MT7620A
	if((dev->gpio>=GPIO40)&&(dev->gpio<=GPIO44))//判断LAN灯范围
	{
		port =  (unsigned int)(dev->gpio - GPIO40);//判断LAN口
		PHY_led_ops(port, led_off_trig);//开启GPIO模式
		gpio_config(dev->gpio, GPIO_OUT);//配置GPIO模式
	}
#else
	if((dev->name >= led_lan_1) && (dev->name <= led_lan_5)) {
		port = (unsigned int)(dev->name - led_lan_1);
		PHY_led_ops(port, led_off_trig);
		gpio_config(dev->gpio, GPIO_OUT);
	}
#endif
	if(dev->gpio < GPIO73) {
		if(GPIO72 == dev->gpio) {
			reg = reg_read32(CR_GPIO_SHARE);
			if(0 == (reg & BIT(13))) {
				reg |= BIT(13);
				reg_write32(CR_GPIO_SHARE, reg);
			}
		}
   		if(dev->level) {
			gpio_write(dev->gpio, GPIO_LEVEL_LOW);
		} else {
			gpio_write(dev->gpio, GPIO_LEVEL_HIGH);
		}
	}
}

struct led_hw_handler hw_handler = {
	mt7620a_led_on,
	mt7620a_led_off,
};

static int __init mt7620a_led_init(void)
{
	unsigned int i;
	int ret;
	struct led_dev *dev;

	ret = led_hw_handle_register(&hw_handler);/* Register hardware on/off handler to core */
	if(ret < 0){
		printk("Error:fail to register hw_handler.\n");
		goto out;
	}
	printk("Register led device for mt7620a leds \n");
	for(i = 0; mt7620a_leds[i].name != led_end; i++){/* Register LED devices */
		dev = &mt7620a_leds[i];
		gpio_config(dev->gpio, GPIO_OUT);                
		mt7620a_led_off(dev); /* turn off led default */
		ret = led_dev_register(dev);
		if(ret<0){
			printk("Error:fail to register led_table[%d].\n", i);
			break;
		}
		printk(" %02d", (unsigned int)dev->name);
	}
	printk("\n");

out:
	return ret;
}

static void __exit mt7620a_led_exit(void)
{
	struct led_dev *dev;
	int i;
	int ret;

	for(i=0; mt7620a_leds[i].name != led_end;i++) {/* Unregister LED devices */
		dev = &mt7620a_leds[i];
		ret = led_dev_unregister(dev);
		if(ret < 0){
			printk("Error:fail to unregister led_table[%d]\n",i);
		}
	}
	ret = led_hw_handle_unregister(&hw_handler);/* Unregister hardware on/off handler */
	if(ret < 0){
		printk(KERN_ERR "Error:fail to unregister hw_handler.\n");
	}
}

module_init(mt7620a_led_init);
module_exit(mt7620a_led_exit);

MODULE_AUTHOR("xiachaoren");
MODULE_DESCRIPTION("MT7620A LEDs driver");
MODULE_LICENSE("GPL");
