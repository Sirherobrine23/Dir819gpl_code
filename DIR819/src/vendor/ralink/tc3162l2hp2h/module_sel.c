#include <linux/module.h>
#include <asm/tc3162/tc3162.h>
#include <linux/proc_fs.h>

#define SYS_HAS_USBHOST (1<<0)
#define SYS_HAS_2GMAC 	(1<<1)
#define SYS_HAS_WIFI 	(1<<2)
#define SYS_HAS_PTM 	(1<<3)
#define SYS_HAS_HWNAT 	(1<<4)
#define SYS_HAS_USB_DEVICE 	(1<<4)

#define  USBHOST_PROC	"tc3162/sys_has_usbhost"
#define  GMAC2_PROC		"tc3162/sys_has_2gmac"
#define  WIFI_PROC		"tc3162/sys_has_wifi"
#define  PTM_PROC		"tc3162/sys_has_ptm"
#define  HWNAT_PROC		"tc3162/sys_has_hwnat"
#define  USB_DEVICE_PROC	"tc3162/sys_has_usb_device"
#define  HW_CONF_REG 	0xbfb0008c

unsigned char module_sel;

char isRT63365E1 = 0;
char check_rt63365ver1(void){
	return isRT63365E1;
}
EXPORT_SYMBOL(check_rt63365ver1);

//define global variables for unrelease-source-code module (such as tcvlantag) to use as compile options.
int wanAtmSupported;
int wanPtmSupported;
int wanEtherSupported;
int wanXponSupported;
int wanMultiServiceSupported;
EXPORT_SYMBOL(wanAtmSupported);
EXPORT_SYMBOL(wanPtmSupported);
EXPORT_SYMBOL(wanEtherSupported);
EXPORT_SYMBOL(wanXponSupported);
EXPORT_SYMBOL(wanMultiServiceSupported);

static void init_wan_mode_support(void)
{
#if defined(TCSUPPORT_WAN_ATM)
    wanAtmSupported=1;
#else
    wanAtmSupported=0;
#endif

#if defined(TCSUPPORT_WAN_PTM)
    wanPtmSupported=1;
#else
    wanPtmSupported=0;
#endif

#if defined(TCSUPPORT_WAN_ETHER)
    wanEtherSupported=1;
#else
    wanEtherSupported=0;
#endif

#if defined(TCSUPPORT_WAN_GPON) || defined(TCSUPPORT_WAN_EPON)
	wanXponSupported=1;
#else
	wanXponSupported=0;
#endif

#if defined(TCSUPPORT_MULTISERVICE_ON_WAN)
	wanMultiServiceSupported=1;
#else
	wanMultiServiceSupported=0;
#endif

}

static int need_wifi_read_proc(char *buf, char **start, off_t off, int count,
                 int *eof, void *data)
{	
	return 0;
}
static int need_usbhost_read_proc(char *buf, char **start, off_t off, int count,
                 int *eof, void *data)
{	
	return 0;
}
static int need_2gmac_read_proc(char *buf, char **start, off_t off, int count,
                 int *eof, void *data)
{	
	return 0;
}

static int need_ptm_read_proc(char *buf, char **start, off_t off, int count,
                 int *eof, void *data)
{	
	return 0;
}
static int need_hwnat_read_proc(char *buf, char **start, off_t off, int count,
                 int *eof, void *data)
{	
	return 0;
}

static int need_usbdev_read_proc(char *buf, char **start, off_t off, int count,
                 int *eof, void *data)
{	
	return 0;
}
static int __init ra_modsel_init(void)
{
	unsigned int x;

	init_wan_mode_support();

	if(isTC3182){
		x = VPint(HW_CONF_REG);
		printk("3182 config value %x\n",x);
		if((x&(1<<8)) == 0){ //tc3182 ldv
			printk("System has only 2gmac \n");
			module_sel = SYS_HAS_2GMAC;
		}else{
			if(((x&(1<<10)) == 0) &&
				(x&((1<<20)|(1<<21)|(1<<22)|(1<<23))) == ((1<<21)|(1<<22)|(1<<23))){
				printk("System has wifi, usb and 1gmac \n");
				module_sel = SYS_HAS_USBHOST | SYS_HAS_WIFI ;
			}else{
				printk("System has wifi,usb and 2gmac \n");
				module_sel = SYS_HAS_USBHOST | SYS_HAS_2GMAC | SYS_HAS_WIFI ;
			}
		}
		module_sel |= SYS_HAS_USB_DEVICE;
	}else if (isRT65168) {
		module_sel = SYS_HAS_USBHOST | SYS_HAS_2GMAC | SYS_HAS_WIFI | SYS_HAS_PTM | SYS_HAS_HWNAT;
	}else if (isRT63365) {
		module_sel = SYS_HAS_USBHOST | SYS_HAS_WIFI | SYS_HAS_HWNAT;
		if ( (VPint(0xbfb00064) & (0xffff)) == 0x0 )
			isRT63365E1 = 1;
	}else if (isRT63260) {
		if(VPint(HW_CONF_REG) & (1<<9)){
			module_sel = SYS_HAS_USB_DEVICE;	
		}else{
			module_sel = 0;	
		}
	}else{//3162u now support 1 gmac , usb host
			module_sel = SYS_HAS_USBHOST | SYS_HAS_WIFI | SYS_HAS_USB_DEVICE;
	}

	if(module_sel & SYS_HAS_WIFI)
	 	create_proc_read_entry(WIFI_PROC, 0, NULL, need_wifi_read_proc, NULL);
	if(module_sel & SYS_HAS_2GMAC) 
	 	create_proc_read_entry(GMAC2_PROC, 0, NULL, need_2gmac_read_proc, NULL);
	if(module_sel & SYS_HAS_USBHOST) 
	 	create_proc_read_entry(USBHOST_PROC, 0, NULL, need_usbhost_read_proc, NULL);
	if(module_sel & SYS_HAS_PTM)
	 	create_proc_read_entry(PTM_PROC, 0, NULL, need_ptm_read_proc, NULL);
	if(module_sel & SYS_HAS_HWNAT)
	 	create_proc_read_entry(HWNAT_PROC, 0, NULL, need_hwnat_read_proc, NULL);
	if(module_sel & SYS_HAS_USB_DEVICE)
	 	create_proc_read_entry(USB_DEVICE_PROC, 0, NULL, need_usbdev_read_proc, NULL);

	return 0;
}
 
static void __exit ra_modsel_exit(void){
	if(module_sel & SYS_HAS_WIFI)
		remove_proc_entry(WIFI_PROC, 0);
	if(module_sel & SYS_HAS_2GMAC) 
		remove_proc_entry(GMAC2_PROC, 0);
	if(module_sel & SYS_HAS_USBHOST) 
		remove_proc_entry(USBHOST_PROC, 0);
	if(module_sel & SYS_HAS_PTM)
		remove_proc_entry(PTM_PROC, 0);
	if(module_sel & SYS_HAS_HWNAT)
		remove_proc_entry(HWNAT_PROC, 0);
	if(module_sel & SYS_HAS_USB_DEVICE)
		remove_proc_entry(USB_DEVICE_PROC, 0);
}
module_init(ra_modsel_init);
module_exit(ra_modsel_exit);

MODULE_LICENSE("GPL");
