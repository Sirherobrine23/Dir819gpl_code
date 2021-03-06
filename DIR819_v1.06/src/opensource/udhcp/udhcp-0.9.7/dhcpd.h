/* dhcpd.h */
#ifndef _DHCPD_H
#define _DHCPD_H

#include <netinet/ip.h>
#include <netinet/udp.h>

#include "leases.h"
#include "autoconf.h"

/************************************/
/* Defaults _you_ may want to tweak */
/************************************/

/* the period of time the client is allowed to use that address */
#define LEASE_TIME              (60*60*24*10) /* 10 days of seconds */

/* where to find the DHCP server configuration file */
#define DHCPD_CONF_FILE         "/etc/udhcpd.conf"

#define DHCPD_DEBUG
#ifdef DHCPD_DEBUG
#define DHCPD_TRACE(fmt, args...) printf("\n[%s, %d]"fmt"\n", __FUNCTION__, __LINE__, ##args);
#else
#define DHCPD_TRACE
#endif
#define DHCPD_VENDORID_CONF_FILE         "/var/udhcpd_vendorid.conf"
#define DEF_VENDOR_ID "Computer"
#define MAX_VENDOR_IDS		80
#define MAX_VENDOR_ID_LEN	64
#define MAX_CLIENT_CLS_COUNT 16
#define MAX_HOSTNAME_LEN    64

/*****************************************************************/
/* Do not modify below here unless you know what you are doing!! */
/*****************************************************************/

/* DHCP protocol -- see RFC 2131 */
#define SERVER_PORT		67
#define CLIENT_PORT		68

#define DHCP_MAGIC		0x63825363

/* DHCP option codes (partial list) */
#define DHCP_PADDING		0x00
#define DHCP_SUBNET		0x01
#define DHCP_TIME_OFFSET	0x02
#define DHCP_ROUTER		0x03
#define DHCP_TIME_SERVER	0x04
#define DHCP_NAME_SERVER	0x05
#define DHCP_DNS_SERVER		0x06
#define DHCP_LOG_SERVER		0x07
#define DHCP_COOKIE_SERVER	0x08
#define DHCP_LPR_SERVER		0x09
#define DHCP_HOST_NAME		0x0c
#define DHCP_BOOT_SIZE		0x0d
#define DHCP_DOMAIN_NAME	0x0f
#define DHCP_SWAP_SERVER	0x10
#define DHCP_ROOT_PATH		0x11
#define DHCP_IP_TTL		0x17
#define DHCP_MTU		0x1a
#define DHCP_BROADCAST		0x1c
#define DHCP_NTP_SERVER		0x2a
#define DHCP_VENDOR_SPEC_INFO	0x2b
#define DHCP_WINS_SERVER	0x2c
#define DHCP_REQUESTED_IP	0x32
#define DHCP_LEASE_TIME		0x33
#define DHCP_OPTION_OVER	0x34
#define DHCP_MESSAGE_TYPE	0x35
#define DHCP_SERVER_ID		0x36
#define DHCP_PARAM_REQ		0x37
#define DHCP_MESSAGE		0x38
#define DHCP_MAX_SIZE		0x39
#define DHCP_T1			0x3a
#define DHCP_T2			0x3b
#define DHCP_VENDOR		0x3c
#define DHCP_CLIENT_ID		0x3d
#define DHCP_6RD_PREFIX      0xd4

#ifdef ENABLE_OPT250
#define DHCP_MICROSOFT		0xfa
#endif

#define DHCP_Classless_StaticRoute 0x79

#ifdef ENABLE_OPT125
#define DHCP_VI_VENDOR_SPEC 0x7d
#endif

#define DHCP_PRIVATE_240		0xF0

#define DHCP_END		0xFF


#define BOOTREQUEST		1
#define BOOTREPLY		2

#define ETH_10MB		1
#define ETH_10MB_LEN		6

#define DHCPDISCOVER		1
#define DHCPOFFER		2
#define DHCPREQUEST		3
#define DHCPDECLINE		4
#define DHCPACK			5
#define DHCPNAK			6
#define DHCPRELEASE		7
#define DHCPINFORM		8

#define BROADCAST_FLAG		0x8000

#define OPTION_FIELD		0
#define FILE_FIELD		1
#define SNAME_FIELD		2

/* miscellaneous defines */
#define TRUE			1
#define FALSE			0
#define MAC_BCAST_ADDR		(unsigned char *) "\xff\xff\xff\xff\xff\xff"
#define OPT_CODE 0
#define OPT_LEN 1
#define OPT_DATA 2

struct option_set {
	unsigned char *data;
	struct option_set *next;
};

typedef struct category_config_info {
   char *category;
   u_int32_t enable;
   u_int32_t start;
   u_int32_t end;
   u_int32_t dns; /* network order */
   struct option_set *options;	
} CATE_CFG_INFO, *pCATE_CFG_INFO;

//radar
struct static_lease {
	uint8_t *mac;
	uint32_t *ip;
	struct static_lease *next;
};

struct server_config_t {
	u_int32_t server;		/* Our IP, in network order */
	u_int32_t start;		/* Start address of leases, network order */
	u_int32_t end;			/* End of leases, network order */
	struct option_set *options;	/* List of DHCP options loaded from the config file */
	char *interface;		/* The name of the interface to use */
	int ifindex;			/* Index number of the interface to use */
	unsigned char arp[6];		/* Our arp address */
	unsigned long lease;		/* lease time in seconds (host order) */
	unsigned long max_leases; 	/* maximum number of leases (including reserved address) */
	char remaining; 		/* should the lease file be interpreted as lease time remaining, or
			 		 * as the time the lease expires */
	unsigned long auto_time; 	/* how long should udhcpd wait before writing a config file.
					 * if this is zero, it will only write one on SIGUSR1 */
	unsigned long decline_time; 	/* how long an address is reserved if a client returns a
				    	 * decline message */
	unsigned long conflict_time; 	/* how long an arp conflict offender is leased for */
	unsigned long offer_time; 	/* how long an offered address is reserved */
	unsigned long min_lease; 	/* minimum lease a client can request*/
	char *lease_file;
	char *pidfile;
    char *opchfile;
	char *notify_file;		/* What to run whenever leases are written */
	u_int32_t siaddr;		/* next server bootp option */
	char *sname;			/* bootp server name */
	char *boot_file;		/* bootp boot file option */
	int  active;
	unsigned long inflease_time; 	/* how long is infinite leasetime */
  struct dhcpOfferedAddr *leases;

    struct category_config_info CateInfo[MAX_CLIENT_CLS_COUNT];
//radar
	struct static_lease *static_leases; /* List of ip/mac pairs to assign static leases */
};

struct vendor_id_config_t {
    char vendorid[MAX_VENDOR_ID_LEN];
};

extern struct vendor_id_config_t vendor_id_config[MAX_VENDOR_IDS];

extern struct server_config_t server_config[];
extern struct dhcpOfferedAddr *leases;
extern int no_of_ifaces;

//gxw / 2014-12-03 / add
extern unsigned long current_time;


void dhcp_log(char *szFmt, ...);

#endif
