/*
 * LED DataBlink Trigger
 *
 * ����ʱ��:��0.05s����0.02s����Ƶ�ʵ��ã���ѭ��
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

static unsigned int blinking_seq[16] = {70, 30, 0}; /*����ʱ��:��0.05s����0.02s����Ƶ�ʵ��ã���ѭ��*/

struct datablink_trig_data {
	struct led_dev *led;
	unsigned int phase;
	signed long cycle_time; /* ����һ�δ�����ʱ�����ڣ�Ĭ�����ú� */
	signed long ttl;   /* һ�δ����������ʱ��(����), �����Ժ�ѭ���ݼ���LED_TRIG_TTL_MAX��ʾ����ѭ�� */	
	const unsigned int *flash_seq;      /* һ��ѭ��������ʱ�� */
	struct timer_list blink_timer;
	int blink_pending;
};

/***************************************************
     �������������ʱ����ʹ�ö�ʱ��ѭ��
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
	if(td->phase & 1) {/* ������������ */
		if(led_off_trig != led->cur_trig->name) {
			led_set_on(led);
		}
	} else {/* ż��������� */
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

	if(led->trigger_data == NULL) 	/* dataflash_trig_data �Ѿ�������� */
	{
		td = kzalloc(sizeof(*td), GFP_KERNEL);
		if (!td)
			return;

		led->trigger_data = td;
	
		td->led = led;
		td->flash_seq = blinking_seq;
		td->cycle_time = 100;

		/* ��˸��ʱ������ */
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
