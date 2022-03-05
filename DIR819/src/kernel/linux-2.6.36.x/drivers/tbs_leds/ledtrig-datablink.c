/*
 * LED DataBlink Trigger
 *
 * 亮灭时序:灭0.05s，亮0.02s，高频率调用，不循环
 * 
 * by Su Denghai 2014-2-12
 */
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/timer.h>
#include <linux/sched.h>
#include <led.h>
#include <linux/slab.h>

static unsigned int blinking_seq[16] = {70, 30, 0}; /*亮灭时序:灭0.05s，亮0.02s，高频率调用，不循环*/

struct datablink_trig_data {
	struct led_dev *led;
	unsigned int phase;
	signed long cycle_time; /* 保存一次触发的时间周期，默认设置好 */
	signed long ttl;   /* 一次触发整个存活时间(毫秒), 触发以后循环递减，LED_TRIG_TTL_MAX表示无限循环 */	
	const unsigned int *flash_seq;      /* 一次循环的亮灭时间 */
	struct timer_list blink_timer;
	int blink_pending;
};

/***************************************************
     亮灭交替完成整个时序，再使用定时器循环
 ***************************************************/
static void led_blink_timer_handler(unsigned long data)
{
	unsigned int t = jiffies;
	struct led_dev *led = (struct led_dev *)data;
	struct datablink_trig_data *td = led->trigger_data;
	
	if(!td)	{
		return;
	} else if((!led->cur_trig) || (td->phase > 12)) {
		goto out;
	} else {
		if(td->flash_seq[td->phase] < 1) {
			td->phase = 0;
		}		
		if(td->ttl < LED_TRIG_TTL_MAX) {
			if((td->ttl > 0) && (td->ttl >= td->flash_seq[td->phase])) {
				td->ttl -= td->flash_seq[td->phase];
			} else {/* Run out of cycle time */
				leddebug("%s: led %d OUT!\n", __func__, td->led->name);
				goto out;
			}
		}
	}
	if(td->phase & 1) {/* 奇数周期亮灯 */
		if(led_off_trig != led->cur_trig->name) {
			led_set_on(led);
		}
	} else {/* 偶数周期灭灯 */
		led_set_off(led);
	}
	t += msecs_to_jiffies(td->flash_seq[td->phase]);
	td->phase++;
	mod_timer(&td->blink_timer, t);
	return;
out:
	td->phase = 0;	
	td->blink_pending = 0;
}

static void datablink_trig_activate(struct led_dev *led)
{
	struct datablink_trig_data *td;

	if(led->trigger_data == NULL) 	/* dataflash_trig_data 已经被清理掉 */
	{
		td = kzalloc(sizeof(*td), GFP_KERNEL);
		if (!td)
			return;

		led->trigger_data = td;
	
		td->led = led;
		td->flash_seq = blinking_seq;
		td->cycle_time = 100;

		/* 闪烁定时器设置 */
		setup_timer(&td->blink_timer,
			    led_blink_timer_handler, (unsigned long)led);
	}
	else
	{
		td = led->trigger_data;
		if((0 == td->blink_pending) && /* check if this led is working already */
			(td->led->cur_trig) && /* check if blinking trig is registered */
			((led_blinking_trig == td->led->cur_trig->name) || (led_on_trig == td->led->cur_trig->name))) {
			td->blink_pending = 1;
			td->phase = 0;
			td->ttl = td->cycle_time;
			led_blink_timer_handler((unsigned long)led);
		}
	}
}

static void datablink_trig_deactivate(struct led_dev *led)
{
	/* do nothing */
}

static struct led_trigger datablink_led_trigger = {
	.name     = led_blinking_trig,
	.activate = datablink_trig_activate,
	.deactivate = datablink_trig_deactivate,
};

static int __init datablink_trig_init(void)
{
	return led_trigger_register(&datablink_led_trigger);
}

static void __exit datablink_trig_exit(void)
{
	led_trigger_unregister(&datablink_led_trigger);
}



module_init(datablink_trig_init);
module_exit(datablink_trig_exit);

MODULE_AUTHOR("Su Denghai");
MODULE_DESCRIPTION("Data Blink LED trigger");
MODULE_LICENSE("GPL");
