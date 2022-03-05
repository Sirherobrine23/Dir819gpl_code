/**********************************************************************
 Copyright (c), 1991-2012, T&W ELECTRONICS(SHENTHEN) Co., Ltd.
 TBS GPIO DRIVER FOR MT7620  create by xiachaoren on 2013-06-06
**********************************************************************/

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/module.h>
#include <linux/spinlock.h>
#include <led.h> /* for leddebug */
#include <gpio.h>

extern struct gpio_dev mt7620a_gpios[];
static struct spinlock gpio_lock;

static struct gpio_dev *get_gpio_para(gpio_idx index, unsigned long *pins)
{
	struct gpio_dev *dev = NULL;
	if(index >= GPIO_END) {
		goto out;
	}
    if(index < GPIO24) {/* 0 ~ 23 */
    	dev = &mt7620a_gpios[0];
    	*pins = 1 << index;
    } else if(index < GPIO40) {/* 24 ~ 39 */
    	dev = &mt7620a_gpios[1];
    	*pins = 1 << (index - GPIO24);
    } else if(index < GPIO72) {/* 40 ~ 71 */
		dev = &mt7620a_gpios[2];
		*pins = 1 << (index - GPIO40);
   	} else if(index < GPIO80) {/* 72 */
   		dev = &mt7620a_gpios[3];
   		*pins = 1 << (index - GPIO72);
	} else {/* Others */
		dev = &mt7620a_gpios[4];
		*pins = 1 << (index - GPIO80);
	}
out:
    return dev;
}

void gpio_config(int gpio_num, int gpio_func)
{
	struct gpio_dev *dev = NULL;
	unsigned long pins = 0;
	unsigned long flags;
	unsigned long value;

	dev = get_gpio_para(gpio_num, &pins);
	if(NULL != dev) {
		if(dev->group < GPIO_GROUP4) {
			spin_lock_irqsave(&gpio_lock, flags);
			value = reg_read32(dev->ctrl_addr);
			value &= ~(pins);
			reg_write32(dev->ctrl_addr, value);
			value = reg_read32(dev->dir_addr);
			if(GPIO_OUT == gpio_func) { /* 0 - GPIO input mode 1 - GPIO output mode */
				value |= pins;
			} else {
				value &= ~(pins);
			}
			reg_write32(dev->dir_addr, value);
			spin_unlock_irqrestore(&gpio_lock, flags);
		}
	}
}

static unsigned long gpio_data_grp1 = 0;
void gpio_write(int gpio_num, gpio_level level)
{
	struct gpio_dev *dev = NULL;
	unsigned long pins = 0;
	unsigned long flags;
	unsigned long value;

	dev = get_gpio_para(gpio_num, &pins);
	if(0 != dev) {
		leddebug("GPIO_NUM=%d, level=%d, group=%d, pins=%#x\n", gpio_num, level, dev->group, pins);
		spin_lock_irqsave(&gpio_lock, flags);
		switch(dev->group) {
			case 0:
			case 2:
			case 3:
			value = reg_read32(dev->data_addr);
			break;

			case 1:/* values read from PIN39~24 are not synchronized */
			value = gpio_data_grp1;
			break;

			default:
			goto out;
		}
		if(GPIO_LEVEL_HIGH == level) {
			value |= pins;
		} else {
			value &= ~pins;
		}
		reg_write32(dev->data_addr, value);
		if(1 == dev->group) {
			gpio_data_grp1 = value;
		}
out:
		spin_unlock_irqrestore(&gpio_lock, flags);
	}
}

gpio_level gpio_read(int gpio_num)
{
	gpio_level level = GPIO_LEVEL_HIGH;
    struct gpio_dev *dev = NULL;
    unsigned long pins;
	unsigned long value;

	dev = get_gpio_para(gpio_num, &pins);
	if(NULL != dev) {
		if(dev->group < GPIO_GROUP4) {
			value = reg_read32(dev->data_addr);
			if(0 == (value & pins)) {
				level = GPIO_LEVEL_LOW;
			}
		}
    }
    return level;
}

/* read interrupt status register */
int gpio_get_ins(int gpio_num)
{
	struct gpio_dev *dev = NULL;
	unsigned long pins;
	unsigned long value;
	unsigned long flags;
	int ret_val = 0;

	dev = get_gpio_para(gpio_num, &pins);
	if(NULL != dev) {
		if(dev->group < GPIO_GROUP4) {/* GPIO 0~72 support interrupt ONLY */
			spin_lock_irqsave(&gpio_lock, flags);
			value = reg_read32(dev->isr_addr);
			if(value & pins) {
				reg_write32(dev->isr_addr, value);
				ret_val = 1;
			}
			spin_unlock_irqrestore(&gpio_lock, flags);
		}
	}
    return ret_val;
}

/* GPIO edge interrupt mode */
void gpio_set_edge(int gpio_num, unsigned char edge)
{
	struct gpio_dev *dev = NULL;
	unsigned long pins;
	unsigned long flags;
	unsigned long value;

	dev = get_gpio_para(gpio_num, &pins);
	if(NULL != dev) {
		if(dev->group < GPIO_GROUP4) {/* GPIO 0~72 support interrupt ONLY */
			spin_lock_irqsave(&gpio_lock, flags);
			value = reg_read32(dev->edge_addr);
			if(IRQF_TRIGGER_FALLING == edge) {
				value |= pins;
			} else {/* IRQF_TRIGGER_NONE */
				value &= ~pins;
			}
			reg_write32(dev->edge_addr, value);/*write edge interrupt reg*/
			spin_unlock_irqrestore(&gpio_lock, flags);
		}
	}
}

static __init int gpio_init(void)
{
	spin_lock_init(&gpio_lock);
	
	return 0;
}

module_init(gpio_init);

EXPORT_SYMBOL_GPL(gpio_config);
EXPORT_SYMBOL_GPL(gpio_write);
EXPORT_SYMBOL_GPL(gpio_read);
EXPORT_SYMBOL_GPL(gpio_get_ins);
EXPORT_SYMBOL_GPL(gpio_set_edge);

MODULE_AUTHOR("Xia Chaoren");
MODULE_DESCRIPTION("MT7620A led driver");
MODULE_LICENSE("GPL");

