/*
 * File name: product.c 
 * 
 * Note: for MTK7620A configuration file
 *  
 * Author: 2014-1-21 Sudenghai
 */

#ifndef __LINUX_MT7620A_PRODUCT_H_INCLUDED
#define __LINUX_MT7620A_PRODUCT_H_INCLUDED


#include <gpio.h>
#include <led.h>
#include <btn.h>

struct gpio_dev mt7620a_gpios[] = {
	{GPIO_GROUP0, 0xB0000628, 0xB0000624, 0xB0000620, 0xB000060C, 0xB0000600},
	{GPIO_GROUP1, 0xB0000650, 0xB000064C, 0xB0000648, 0xB0000644, 0xB0000638},
	{GPIO_GROUP2, 0xB0000678, 0xB0000674, 0xB0000670, 0xB000066C, 0xB0000660},
	{GPIO_GROUP3, 0xB00006A0, 0xB000069C, 0xB0000698, 0xB0000694, 0xB0000688},
	{GPIO_GROUP4, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000},
};

struct led_dev mt7620a_leds[] = {
	{led_wlan, 		GPIO72, GPIO_LEVEL_LOW, led_off_trig, LED_BOOT_OFF, led_off_trig, 0},/*2.4G灯位是GPIO引出来，而5.8G灯位是芯片直接引出来的*/
	{led_wps, 		GPIO39, GPIO_LEVEL_LOW, led_off_trig, LED_BOOT_OFF, led_off_trig, 0},
//	{led_usb, 		GPIO11, GPIO_LEVEL_LOW, led_off_trig, LED_BOOT_OFF, led_off_trig, 0},
//	{led_lan_1, 	GPIO40, GPIO_LEVEL_LOW, led_off_trig, LED_BOOT_OFF, led_off_trig, 0},
//	{led_lan_2, 	GPIO41, GPIO_LEVEL_LOW, led_off_trig, LED_BOOT_OFF, led_off_trig, 0},
//	{led_lan_3, 	GPIO42, GPIO_LEVEL_LOW, led_off_trig, LED_BOOT_OFF, led_off_trig, 0},
//	{led_lan_4,		GPIO43, GPIO_LEVEL_LOW, led_off_trig, LED_BOOT_OFF, led_off_trig, 0},
	{led_internet, 	GPIO40, GPIO_LEVEL_LOW, led_off_trig, LED_BOOT_OFF, led_off_trig, 0},
	{led_end, 		GPIO_END, GPIO_LEVEL_HIGH,led_off_trig, LED_BOOT_OFF, led_off_trig, 0},
};
//同时兼容多按键的问题
struct btn_dev mt7620a_btns[] = 
{
	{
		.name  = btn_reset,
		.gpio  = GPIO12,
		.level = BTN_LEVEL_LOW,
		.iogroup = "",
	},
	{
		.name  = btn_wps,
		.gpio  = GPIO02,
		.level = BTN_LEVEL_LOW,
		.iogroup = "",
	},

	{
		.name  = btn_end,
	},
};


#endif /* __LINUX_MT7620A_PRODUCT_H_INCLUDED */

