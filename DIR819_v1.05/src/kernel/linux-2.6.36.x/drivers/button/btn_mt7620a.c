/**
 * File name: btn_mt7620a.c
 * Note: MT7620A方案的按钮驱动
 * 
 * Author: Su Denghai
 * Date: 2014-01-06
 **/
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/config.h>
#include <linux/module.h>
#include <linux/signal.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/resource.h>
#include <asm/types.h>
#include <asm/irq.h>
#include <asm/mach-ralink/surfboardint.h>
#include <linux/string.h>

#include <gpio.h>
#include <btn.h>

#define BTN_DEBUG 1

#ifdef BTN_DEBUG
    #define BTN_TRACE printk
#else
    #define BTN_TRACE(str, args...)  do { ; } while(0);
#endif


//如果需要，在group_map[]里面添加自己需要的组合键，填上自己需要对应的GPIO口
//这里只增加了双WPS按键
struct gpio_map group_maps[] = {
        {"wps_wps5g",{GPIO12,GPIO13,GPIO_END,GPIO_END}},
            
        {"btn_end",{GPIO_END,GPIO_END,GPIO_END,GPIO_END}}
};
extern struct btn_dev mt7620a_btns[];  /* 定义在mt7620a_product.c中 */
extern void mt7620a_gpio_mode(int gpio);
extern void mt7620a_gpio_config_input(int gpio);
extern btn_status mt7620a_get_in(int gpio);

//计算按键组合获取索引值
int get_gpio_mapps_index(struct btn_dev *btn)
{
        int j;
       
           for(j=0;j<sizeof(group_maps)/sizeof(struct gpio_map);j++)//遍历数组，找出对应的按键
            {                
                if(j==sizeof(group_maps)/sizeof(struct gpio_map)-1)//如果搜索到最后一个，认为搜索失败
                {
                    return (sizeof(group_maps)/sizeof(struct gpio_map));//返回最大值
                }
                else if(!strcmp(group_maps[j].gpioname,btn->iogroup))//搜索到对应的值
                {
                    
                   break;
                }
            }
            return j;
}
//获取按键状态
//返回按键值
int get_btn_status(struct btn_dev *btn)
{
        int state;
        int j;
	
	if(btn->gpio < GPIO73) {//如果是小于组合按键值，直接读取键值
		state = gpio_read(btn->gpio);   //读取引脚值    
	} 
    else if(btn->gpio == GPIO_GROUPS) //组合按键
        {
               btn->index=get_gpio_mapps_index(btn);
                if(btn->index==sizeof(group_maps)/sizeof(struct gpio_map))//没有搜索到对应值
                {                   
                    return -1;
                } 
            state = gpio_read(group_maps[btn->index].gpio[0]);            //读取引脚值
             for(j=1;j<4;j++)
            {
                if(group_maps[btn->index].gpio[j]!=GPIO_END)//遍历组合引脚
                {
                   state = state&&(gpio_read(group_maps[btn->index].gpio[j]));    //获取状态              
                }
            }
        
	}
    return state;
}
static void gpio_interrupt_ctrl(struct btn_dev *btn, unsigned char enable)
{
	unsigned char edge = IRQF_TRIGGER_NONE;
       int j=0;
	if(enable) {
		if(BTN_LEVEL_HIGH == btn->level) {/* Trigger at rising edge */
			edge = IRQF_TRIGGER_RISING;
		} else {/* Trigger at falling edge */
			edge = IRQF_TRIGGER_FALLING;
		}
	}
    if(btn->gpio == GPIO_GROUPS)//组合按键
    {
           btn->index=get_gpio_mapps_index(btn);//获取索引值
           if(btn->index==sizeof(group_maps)/sizeof(struct gpio_map))//没有找到
            {              
                return ;
            } 
        for(j=0;j<4;j++)//最多支持4个按键同时按下
        {
            if(group_maps[btn->index].gpio[j]!=GPIO_END)//有效的按键才可以
            {               
               gpio_set_edge(group_maps[btn->index].gpio[j], edge);
            }
        }
    }
    else
	gpio_set_edge(btn->gpio, edge);
}

/* 核心驱动通过此函数获得按钮状态 */
btn_status mt7620a_get_status(struct btn_dev *btn)
{
	int state;
        int j;
	
        state = get_btn_status(btn);	//获取状态

	/* 如果是低电平触发 */
	if(btn->level == BTN_LEVEL_LOW)
	{
		if(state == 0)
			return BTN_DOWN;
		else
			return BTN_UP;
	}
	else
	{   /* 如果是高电平触发 */
		if(state == 0)
			return BTN_UP;
		else
			return BTN_DOWN;
	}

}

void mt7620a_button_irq(unsigned long data)
{
    struct btn_dev *btn = (struct btn_dev *)data;
    int state = get_btn_status(btn);//获取状态
    //int state = gpio_read(btn->gpio);

    if ((btn->level == BTN_LEVEL_LOW && !state)
        || (btn->level == BTN_LEVEL_HIGH && state))
    {
        btn->cur_status =  BTN_DOWN;	
		btn_status_query(btn);
    }
    else if ((btn->level == BTN_LEVEL_LOW && state)
        || (btn->level == BTN_LEVEL_HIGH && !state))
    {
		btn->cur_status = BTN_UP;
		BTN_TRACE("button %d up, gpio=%d\n", btn->name, btn->gpio);
    }

    /* Enable IRQ first again */
    gpio_interrupt_ctrl(btn, 1);/* Enable IRQ */
}

irqreturn_t mt7620a_gpio_irq_dispatch(int cpl, void *dev_id)
{
    struct btn_dev *btn = NULL;
	int i,j,k;
	int irq_status=0;

	//gxw / 2014-09-23 / 统一使用.name作为实例结束标记
	for(i = 0; mt7620a_btns[i].name != btn_end; i++) {
		btn = &mt7620a_btns[i];

		if(btn->gpio == GPIO_GROUPS)//组合按键
		{
			btn->index=get_gpio_mapps_index(btn);        //获取索引值          
			if(btn->index==sizeof(group_maps)/sizeof(struct gpio_map))//获取失败
			{
				continue;
			}         
			/*当存在几个低电平时，说明有几个按键按下*/
			irq_status =!(gpio_read(group_maps[btn->index].gpio[0]));
			for(j=1;j<4;j++)
			{
				if(group_maps[btn->index].gpio[j]!=GPIO_END)//遍历引脚
				{

					// if(gpio_get_ins(group_maps[btn->index].gpio[j])) {/* Read IRQ status and make it clean */                		
					//   }
					irq_status = (irq_status)&&(!gpio_read(group_maps[btn->index].gpio[j]));//查询键值是不是都按下了
				                  
				}
			}
			if(irq_status)//如果都按下，说明是组合按键
			{
				gpio_interrupt_ctrl(btn, 0);/* Disable IRQ first */
				mt7620a_button_irq(btn);
			}
		}
		else
		{
			if(gpio_get_ins(btn->gpio)) {/* Read IRQ status and make it clean */
				gpio_interrupt_ctrl(btn, 0);/* Disable IRQ first */
				mt7620a_button_irq(btn);
			}
		}
	}

    return IRQ_HANDLED;
}

static int __init mt7620a_btn_init(void)
{
	int ret;
	int i,j;
	struct btn_dev *btn = NULL;
	
	for(i=0;mt7620a_btns[i].name != btn_end; i++)
	{
		btn = &mt7620a_btns[i];
		
		/* 初始各个BTN设备的初始状态 */
		btn->get_status = mt7620a_get_status;

		btn->cur_status = BTN_UP;

		if(btn->gpio < GPIO73) { /* GPIO 0~72 support interrupt ONLY */
			gpio_config(btn->gpio, GPIO_IN);/* Buttons should be working at GPIO input mode */
			gpio_interrupt_ctrl(btn, 1);/* Enable IRQ */
		}
        else if(btn->gpio ==GPIO_GROUPS ) //组合按键
        {
            j=get_gpio_mapps_index(btn);//获取键值

			if(j==sizeof(group_maps)/sizeof(struct gpio_map))//失败
			{
				return -1;
			}            
			btn->index = j;//用于处理计算group_map的位置

			for(j=0;j<4;j++)
			{
				if(group_maps[btn->index].gpio[j]!=GPIO_END)//遍历组合引脚
				{
					gpio_config(group_maps[btn->index].gpio[j], GPIO_IN);/* Buttons should be working at GPIO input mode */
				}
			}
			gpio_interrupt_ctrl(btn, 1);/* Enable IRQ */
		}
		ret = btn_dev_register(btn);
		if (ret != 0) {
			printk (KERN_ERR "Unable to register btn_dev %d(error %d)\n", btn->name, ret);
			return -1;
		}	
	}

	ret = request_irq(SURFBOARDINT_GPIO, mt7620a_gpio_irq_dispatch, IRQF_SHARED, "TBS_BTN", btn);
	if(ret != 0) {
		printk(KERN_ERR "unable to request IRQ for GPIO (error %d)\n", ret);
	} else {
		printk("TBS button driver for %s initialized, IRQ=%d\n", __FUNCTION__, SURFBOARDINT_GPIO);
	}

	return 0;
}


static void __exit mt7620a_btn_exit(void)
{
	struct btn_dev *btn = NULL;
	int i;

	for(i=0;mt7620a_btns[i].name != btn_end; i++) {
		btn = &mt7620a_btns[i];
		if((btn->gpio < GPIO73)||(btn->gpio == GPIO_GROUPS)) { /* GPIO 0~72 support interrupt ONLY *///组合按键也要算
			gpio_interrupt_ctrl(btn, 0);/* Disable IRQ first */
		}
		btn->cur_status = BTN_START;
		btn->get_status = NULL;
	}
	free_irq(SURFBOARDINT_GPIO, btn);
}

module_init(mt7620a_btn_init);
module_exit(mt7620a_btn_exit);

MODULE_AUTHOR("Su Denghai");
MODULE_DESCRIPTION("Ralink buttons driver");
MODULE_LICENSE("GPL");
