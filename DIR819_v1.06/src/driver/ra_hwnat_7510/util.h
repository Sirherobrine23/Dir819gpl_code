/*
    Module Name:
    util.h

    Abstract:

    Revision History:
    Who         When            What
    --------    ----------      ----------------------------------------------
    Name        Date            Modification logs
    Steven Liu  2007-01-25      Initial version
*/

#ifndef _UTIL_WANTED
#define _UTIL_WANTED

#include <linux/ip.h>
#include <linux/tcp.h>
#include <linux/udp.h>
#include "foe_fdb.h"
#include <asm/tc3162/tc3162.h>
/*
 * DEFINITIONS AND MACROS
 */
#define PHYS_TO_K1(physaddr) KSEG1ADDR(physaddr)

#ifdef TCSUPPORT_RA_HWNAT
#define RegRead(reg)              (uint32_t)regRead32(PHYS_TO_K1(reg))
#define RegWrite(reg, wdata)      regWrite32(PHYS_TO_K1(reg), wdata)
#define SWAP32(x) \
    ((uint32_t)( \
    (((uint32_t)(x) & (uint32_t) 0x000000ffUL) << 24) | \
    (((uint32_t)(x) & (uint32_t) 0x0000ff00UL) <<  8) | \
    (((uint32_t)(x) & (uint32_t) 0x00ff0000UL) >>  8) | \
    (((uint32_t)(x) & (uint32_t) 0xff000000UL) >> 24) )
#else

#define RegRead(phys) (*(volatile uint32_t *)PHYS_TO_K1(phys))
#if 0
#define RegWrite(phys, val)                        \
        do {			\
		printk("Set %08X to %08X\n", (phys), (val));      \
		(*(volatile uint32_t *)PHYS_TO_K1(phys)) = (val); \
        }while(0)
#else
#define RegWrite(phys, val)  ((*(volatile uint32_t *)PHYS_TO_K1(phys)) = (val))
#endif
#endif

/*
 * TYPEDEFS AND STRUCTURES
 */


/*
 * EXPORT FUNCTION
 */
uint8_t *Ip2Str(uint32_t ip);
void MacReverse(uint8_t * Mac);
void RegModifyBits(uint32_t Addr, uint32_t Data, uint32_t Offset, uint32_t Len);
void CalIpRange(uint32_t StartIp, uint32_t EndIp, uint8_t * M, uint8_t * E);
void FoeToOrgTcpHdr(IN struct FoeEntry *foe_entry, IN struct iphdr *iph,
		    OUT struct tcphdr *th);
void FoeToOrgUdpHdr(IN struct FoeEntry *foe_entry, IN struct iphdr *iph,
		    OUT struct udphdr *uh);
void FoeToOrgIpHdr(IN struct FoeEntry *foe_entry, OUT struct iphdr *iph);
void PpeIpv6PktRebuild(struct sk_buff *skb, struct FoeEntry *foe_entry);
void PpeIpv4PktRebuild(struct sk_buff *skb, struct iphdr *iph,
		       struct FoeEntry *foe_entry);
unsigned int Str2Ip(IN char *str);

#endif
