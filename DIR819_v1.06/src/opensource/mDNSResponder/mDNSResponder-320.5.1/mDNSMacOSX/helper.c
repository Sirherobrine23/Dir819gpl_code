/* -*- Mode: C; tab-width: 4 -*-
 *
 * Copyright (c) 2007 Apple Inc. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <sys/cdefs.h>
#include <arpa/inet.h>
#include <bsm/libbsm.h>
#include <net/if.h>
#include <net/route.h>
#include <net/if_dl.h>
#include <net/if_types.h>
#include <netinet/in.h>
#include <netinet/if_ether.h>
#include <netinet6/in6_var.h>
#include <netinet6/nd6.h>
#include <netinet6/ipsec.h>
#include <sys/ioctl.h>
#include <sys/param.h>
#include <sys/socket.h>
#include <asl.h>
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <Security/Security.h>
#include <SystemConfiguration/SystemConfiguration.h>
#include <SystemConfiguration/SCDynamicStore.h>
#include <SystemConfiguration/SCPreferencesSetSpecific.h>
#include <SystemConfiguration/SCDynamicStoreCopySpecific.h>
#include <TargetConditionals.h>
#include <IOKit/pwr_mgt/IOPMLib.h>
#include <net/bpf.h>

#include "mDNSEmbeddedAPI.h"
#include "dns_sd.h"
#include "dnssd_ipc.h"
#include "libpfkey.h"
#include "helper.h"
#include "helpermsgServer.h"
#include "helper-server.h"
#include "ipsec_options.h"
#include "P2PPacketFilter.h"

#ifndef RTF_IFSCOPE
#define RTF_IFSCOPE 0x1000000
#endif

#if TARGET_OS_EMBEDDED
#ifndef MDNS_NO_IPSEC
#define MDNS_NO_IPSEC 1
#endif
#define NO_CFUSERNOTIFICATION 1
#define NO_SECURITYFRAMEWORK 1
#endif

// Embed the client stub code here, so we can access private functions like ConnectToServer, create_hdr, deliver_request
#include "../mDNSShared/dnssd_ipc.c"
#include "../mDNSShared/dnssd_clientstub.c"

typedef struct sadb_x_policy *ipsec_policy_t;

uid_t mDNSResponderUID;
gid_t mDNSResponderGID;
static const char kTunnelAddressInterface[] = "lo0";

void
debug_(const char *func, const char *fmt, ...)
	{
	char buf[2048];
	va_list ap;

	va_start(ap, fmt);
	vsnprintf(buf, sizeof(buf), fmt, ap);
	va_end(ap);
	helplog(ASL_LEVEL_DEBUG, "%s: %s", func, buf);
	}

static int
authorized(audit_token_t *token)
	{
	int ok = 0;
	pid_t pid = (pid_t)-1;
	uid_t euid = (uid_t)-1;

	audit_token_to_au32(*token, NULL, &euid, NULL, NULL, NULL, &pid, NULL,
	    NULL);
	ok = (euid == mDNSResponderUID || euid == 0);
	if (!ok)
		helplog(ASL_LEVEL_NOTICE,
		    "Unauthorized access by euid=%lu pid=%lu",
		    (unsigned long)euid, (unsigned long)pid);
	return ok;
	}

kern_return_t
do_mDNSExit(__unused mach_port_t port, audit_token_t token)
	{
	debug("entry");
	if (!authorized(&token))
		goto fin;
	helplog(ASL_LEVEL_INFO, "exit");
	exit(0);

fin:
	debug("fin");
	return KERN_SUCCESS;
	}

kern_return_t do_mDNSRequestBPF(__unused mach_port_t port, audit_token_t token)
	{
	if (!authorized(&token)) return KERN_SUCCESS;
	DNSServiceRef ref;
	DNSServiceErrorType err = ConnectToServer(&ref, 0, send_bpf, NULL, NULL, NULL);
	if (err) { helplog(ASL_LEVEL_ERR, "do_mDNSRequestBPF: ConnectToServer %d", err); return err; }
	
	char *ptr;
	size_t len = sizeof(DNSServiceFlags);
	ipc_msg_hdr *hdr = create_hdr(send_bpf, &len, &ptr, 0, ref);
	if (!hdr) { DNSServiceRefDeallocate(ref); return kDNSServiceErr_NoMemory; }
	put_flags(0, &ptr);
	deliver_request(hdr, ref);		// Will free hdr for us
	DNSServiceRefDeallocate(ref);
	update_idle_timer();
	return KERN_SUCCESS;
	}

kern_return_t do_mDNSPowerRequest(__unused mach_port_t port, int key, int interval, int *err, audit_token_t token)
	{
	*err = -1;
	if (!authorized(&token)) { *err = kmDNSHelperNotAuthorized; goto fin; }

	CFArrayRef events = IOPMCopyScheduledPowerEvents();
	if (events)
		{
		int i;
		CFIndex count = CFArrayGetCount(events);
		for (i=0; i<count; i++)
			{
			CFDictionaryRef dict = CFArrayGetValueAtIndex(events, i);
			CFStringRef id = CFDictionaryGetValue(dict, CFSTR(kIOPMPowerEventAppNameKey));
			if (CFEqual(id, CFSTR("mDNSResponderHelper")))
				{
				CFDateRef   EventTime = CFDictionaryGetValue(dict, CFSTR(kIOPMPowerEventTimeKey));
				CFStringRef EventType = CFDictionaryGetValue(dict, CFSTR(kIOPMPowerEventTypeKey));
				IOReturn result = IOPMCancelScheduledPowerEvent(EventTime, id, EventType);
				//helplog(ASL_LEVEL_ERR, "Deleting old event %s");
				if (result) helplog(ASL_LEVEL_ERR, "IOPMCancelScheduledPowerEvent %d failed %d", i, result);
				}
			}
		CFRelease(events);
		}

	if (key < 0)			// mDNSPowerRequest(-1,-1) means "clear any stale schedules" (see above)
		*err = 0;
	else if (key == 0)		// mDNSPowerRequest(0, 0) means "sleep now"
		{
		IOReturn r = IOPMSleepSystem(IOPMFindPowerManagement(MACH_PORT_NULL));
		if (r) { usleep(100000); helplog(ASL_LEVEL_ERR, "IOPMSleepSystem %d", r); }
		*err = r;
		}
	else if (key > 0)
		{
		CFDateRef w = CFDateCreate(NULL, CFAbsoluteTimeGetCurrent() + interval);
		if (w)
			{
			IOReturn r = IOPMSchedulePowerEvent(w, CFSTR("mDNSResponderHelper"), key ? CFSTR(kIOPMAutoWake) : CFSTR(kIOPMAutoSleep));
			if (r) { usleep(100000); helplog(ASL_LEVEL_ERR, "IOPMSchedulePowerEvent(%d) %d %x", interval, r, r); }
			*err = r;
			CFRelease(w);
			}
		}
fin:
	update_idle_timer();
	return KERN_SUCCESS;
	}

kern_return_t do_mDNSSetLocalAddressCacheEntry(__unused mach_port_t port, int ifindex, int family, v6addr_t ip, ethaddr_t eth, int *err, audit_token_t token)
	{
	#define IPv6FMTSTRING "%02X%02X:%02X%02X:%02X%02X:%02X%02X:%02X%02X:%02X%02X:%02X%02X:%02X%02X"
	#define IPv6FMTARGS  ip[0], ip[1], ip[2], ip[3], ip[4], ip[5], ip[6], ip[7], ip[8], ip[9], ip[10], ip[11], ip[12], ip[13], ip[14], ip[15] 
	#if 0
	if (family == 4)
		helplog(ASL_LEVEL_ERR, "do_mDNSSetLocalAddressCacheEntry %d IPv%d %d.%d.%d.%d %02X:%02X:%02X:%02X:%02X:%02X",
			ifindex, family, ip[0], ip[1], ip[2], ip[3], eth[0], eth[1], eth[2], eth[3], eth[4], eth[5]);
	else
		helplog(ASL_LEVEL_ERR, "do_mDNSSetLocalAddressCacheEntry %d IPv%d " IPv6FMTSTRING " %02X:%02X:%02X:%02X:%02X:%02X",
			ifindex, family, IPv6FMTARGS, eth[0], eth[1], eth[2], eth[3], eth[4], eth[5]);
	#endif

	*err = -1;
	if (!authorized(&token)) { *err = kmDNSHelperNotAuthorized; goto fin; }

	static int s = -1, seq = 0;
	if (s < 0)
		{
		s = socket(PF_ROUTE, SOCK_RAW, 0);
		if (s < 0) helplog(ASL_LEVEL_ERR, "do_mDNSSetLocalAddressCacheEntry: socket(PF_ROUTE, SOCK_RAW, 0) failed %d (%s)", errno, strerror(errno));
		}

	if (s >= 0)
		{
		struct timeval tv;
		gettimeofday(&tv, 0);
		if (family == 4)
			{
			struct { struct rt_msghdr hdr; struct sockaddr_inarp dst; struct sockaddr_dl sdl; } rtmsg;
			memset(&rtmsg, 0, sizeof(rtmsg));

			rtmsg.hdr.rtm_msglen         = sizeof(rtmsg);
			rtmsg.hdr.rtm_version        = RTM_VERSION;
			rtmsg.hdr.rtm_type           = RTM_ADD;
			rtmsg.hdr.rtm_index          = ifindex;
			rtmsg.hdr.rtm_flags          = RTF_HOST | RTF_STATIC | RTF_IFSCOPE;
			rtmsg.hdr.rtm_addrs          = RTA_DST | RTA_GATEWAY;
			rtmsg.hdr.rtm_pid            = 0;
			rtmsg.hdr.rtm_seq            = seq++;
			rtmsg.hdr.rtm_errno          = 0;
			rtmsg.hdr.rtm_use            = 0;
			rtmsg.hdr.rtm_inits          = RTV_EXPIRE;
			rtmsg.hdr.rtm_rmx.rmx_expire = tv.tv_sec + 30;

			rtmsg.dst.sin_len            = sizeof(rtmsg.dst);
			rtmsg.dst.sin_family         = AF_INET;
			rtmsg.dst.sin_port           = 0;
			rtmsg.dst.sin_addr.s_addr    = *(in_addr_t*)ip;
			rtmsg.dst.sin_srcaddr.s_addr = 0;
			rtmsg.dst.sin_tos            = 0;
			rtmsg.dst.sin_other          = 0;

			rtmsg.sdl.sdl_len            = sizeof(rtmsg.sdl);
			rtmsg.sdl.sdl_family         = AF_LINK;
			rtmsg.sdl.sdl_index          = ifindex;
			rtmsg.sdl.sdl_type           = IFT_ETHER;
			rtmsg.sdl.sdl_nlen           = 0;
			rtmsg.sdl.sdl_alen           = ETHER_ADDR_LEN;
			rtmsg.sdl.sdl_slen           = 0;

			// Target MAC address goes in rtmsg.sdl.sdl_data[0..5]; (See LLADDR() in /usr/include/net/if_dl.h)
			memcpy(rtmsg.sdl.sdl_data, eth, sizeof(ethaddr_t));

			int len = write(s, (char *)&rtmsg, sizeof(rtmsg));
			if (len < 0)
				helplog(ASL_LEVEL_ERR, "do_mDNSSetLocalAddressCacheEntry: write(%d) interface %d address %d.%d.%d.%d seq %d result %d errno %d (%s)",
					sizeof(rtmsg), ifindex, ip[0], ip[1], ip[2], ip[3], rtmsg.hdr.rtm_seq, len, errno, strerror(errno));
			len = read(s, (char *)&rtmsg, sizeof(rtmsg));
			if (len < 0 || rtmsg.hdr.rtm_errno)
				helplog(ASL_LEVEL_ERR, "do_mDNSSetLocalAddressCacheEntry: read (%d) interface %d address %d.%d.%d.%d seq %d result %d errno %d (%s) %d",
					sizeof(rtmsg), ifindex, ip[0], ip[1], ip[2], ip[3], rtmsg.hdr.rtm_seq, len, errno, strerror(errno), rtmsg.hdr.rtm_errno);

			*err = 0;
			}
		else
			{
			struct { struct rt_msghdr hdr; struct sockaddr_in6 dst; struct sockaddr_dl sdl; } rtmsg;
			memset(&rtmsg, 0, sizeof(rtmsg));

			rtmsg.hdr.rtm_msglen         = sizeof(rtmsg);
			rtmsg.hdr.rtm_version        = RTM_VERSION;
			rtmsg.hdr.rtm_type           = RTM_ADD;
			rtmsg.hdr.rtm_index          = ifindex;
			rtmsg.hdr.rtm_flags          = RTF_HOST | RTF_STATIC | RTF_IFSCOPE;
			rtmsg.hdr.rtm_addrs          = RTA_DST | RTA_GATEWAY;
			rtmsg.hdr.rtm_pid            = 0;
			rtmsg.hdr.rtm_seq            = seq++;
			rtmsg.hdr.rtm_errno          = 0;
			rtmsg.hdr.rtm_use            = 0;
			rtmsg.hdr.rtm_inits          = RTV_EXPIRE;
			rtmsg.hdr.rtm_rmx.rmx_expire = tv.tv_sec + 30;

			rtmsg.dst.sin6_len           = sizeof(rtmsg.dst);
			rtmsg.dst.sin6_family        = AF_INET6;
			rtmsg.dst.sin6_port          = 0;
			rtmsg.dst.sin6_flowinfo      = 0;
			rtmsg.dst.sin6_addr          = *(struct in6_addr*)ip;
			rtmsg.dst.sin6_scope_id      = ifindex;

			rtmsg.sdl.sdl_len            = sizeof(rtmsg.sdl);
			rtmsg.sdl.sdl_family         = AF_LINK;
			rtmsg.sdl.sdl_index          = ifindex;
			rtmsg.sdl.sdl_type           = IFT_ETHER;
			rtmsg.sdl.sdl_nlen           = 0;
			rtmsg.sdl.sdl_alen           = ETHER_ADDR_LEN;
			rtmsg.sdl.sdl_slen           = 0;

			// Target MAC address goes in rtmsg.sdl.sdl_data[0..5]; (See LLADDR() in /usr/include/net/if_dl.h)
			memcpy(rtmsg.sdl.sdl_data, eth, sizeof(ethaddr_t));

			int len = write(s, (char *)&rtmsg, sizeof(rtmsg));
			if (len < 0)
				helplog(ASL_LEVEL_ERR, "do_mDNSSetLocalAddressCacheEntry: write(%d) interface %d address " IPv6FMTSTRING " seq %d result %d errno %d (%s)",
					sizeof(rtmsg), ifindex, IPv6FMTARGS, rtmsg.hdr.rtm_seq, len, errno, strerror(errno));
			len = read(s, (char *)&rtmsg, sizeof(rtmsg));
			if (len < 0 || rtmsg.hdr.rtm_errno)
				helplog(ASL_LEVEL_ERR, "do_mDNSSetLocalAddressCacheEntry: read (%d) interface %d address " IPv6FMTSTRING " seq %d result %d errno %d (%s) %d",
					sizeof(rtmsg), ifindex, IPv6FMTARGS, rtmsg.hdr.rtm_seq, len, errno, strerror(errno), rtmsg.hdr.rtm_errno);

			*err = 0;
			}

		}

fin:
	update_idle_timer();
	return KERN_SUCCESS;
	}

kern_return_t do_mDNSNotify(__unused mach_port_t port, const char *title, const char *msg, audit_token_t token)
	{
	if (!authorized(&token)) return KERN_SUCCESS;

#ifndef NO_CFUSERNOTIFICATION
	static const char footer[] = "(Note: This message only appears on machines with 17.x.x.x IP addresses ??? i.e. at Apple ??? not on customer machines.)";
	CFStringRef alertHeader  = CFStringCreateWithCString(NULL, title,  kCFStringEncodingUTF8);
	CFStringRef alertBody    = CFStringCreateWithCString(NULL, msg,    kCFStringEncodingUTF8);
	CFStringRef alertFooter  = CFStringCreateWithCString(NULL, footer, kCFStringEncodingUTF8);
	CFStringRef alertMessage = CFStringCreateWithFormat(NULL, NULL, CFSTR("%@\r\r%@"), alertBody, alertFooter);
	CFRelease(alertBody);
	CFRelease(alertFooter);
	int err = CFUserNotificationDisplayNotice(0.0, kCFUserNotificationStopAlertLevel, NULL, NULL, NULL, alertHeader, alertMessage, NULL);
	if (err) helplog(ASL_LEVEL_ERR, "CFUserNotificationDisplayNotice returned %d", err);
	CFRelease(alertHeader);
	CFRelease(alertMessage);
#else
	(void)title;
	(void)msg;
#endif /* NO_CFUSERNOTIFICATION */

	update_idle_timer();
	return KERN_SUCCESS;
	}

kern_return_t
do_mDNSDynamicStoreSetConfig(__unused mach_port_t port, int key,
    const char* subkey, vm_offset_t value, mach_msg_type_number_t valueCnt,
    audit_token_t token)
	{
	CFStringRef sckey = NULL;
	Boolean release_sckey = FALSE;
	CFDataRef bytes = NULL;
	CFPropertyListRef plist = NULL;
	SCDynamicStoreRef store = NULL;

	debug("entry");
	if (!authorized(&token)) goto fin;

	switch ((enum mDNSDynamicStoreSetConfigKey)key)
		{
		case kmDNSMulticastConfig:
			sckey = CFSTR("State:/Network/" kDNSServiceCompMulticastDNS);
			break;
		case kmDNSDynamicConfig:
			sckey = CFSTR("State:/Network/DynamicDNS");
			break;
		case kmDNSPrivateConfig:
			sckey = CFSTR("State:/Network/" kDNSServiceCompPrivateDNS);
			break;
		case kmDNSBackToMyMacConfig:
			sckey = CFSTR("State:/Network/BackToMyMac");
			break;
		case kmDNSSleepProxyServersState:
			{
			CFMutableStringRef tmp = CFStringCreateMutable(kCFAllocatorDefault, 0);
			CFStringAppend(tmp, CFSTR("State:/Network/Interface/"));
			CFStringAppendCString(tmp, subkey, kCFStringEncodingUTF8);
			CFStringAppend(tmp, CFSTR("/SleepProxyServers"));
			sckey = CFStringCreateCopy(kCFAllocatorDefault, tmp);
			release_sckey = TRUE;
			CFRelease(tmp);
			break;
			}
		default:
			debug("unrecognized key %d", key);
			goto fin;
		}
	if (NULL == (bytes = CFDataCreateWithBytesNoCopy(NULL, (void *)value,
	    valueCnt, kCFAllocatorNull)))
		{
		debug("CFDataCreateWithBytesNoCopy of value failed");
		goto fin;
		}
	if (NULL == (plist = CFPropertyListCreateFromXMLData(NULL, bytes,
	    kCFPropertyListImmutable, NULL)))
		{
		debug("CFPropertyListCreateFromXMLData of bytes failed");
		goto fin;
		}
	CFRelease(bytes);
	bytes = NULL;
	if (NULL == (store = SCDynamicStoreCreate(NULL,
	    CFSTR(kmDNSHelperServiceName), NULL, NULL)))
		{
		debug("SCDynamicStoreCreate failed: %s", SCErrorString(SCError()));
		goto fin;
		}
	SCDynamicStoreSetValue(store, sckey, plist);
	debug("succeeded");

fin:
	if (NULL != bytes)
		CFRelease(bytes);
	if (NULL != plist)
		CFRelease(plist);
	if (NULL != store)
		CFRelease(store);
	if (release_sckey && sckey)
		CFRelease(sckey);
	vm_deallocate(mach_task_self(), value, valueCnt);
	update_idle_timer();
	return KERN_SUCCESS;
	}

char usercompname[MAX_DOMAIN_LABEL+1] = {0}; // the last computer name the user saw
char userhostname[MAX_DOMAIN_LABEL+1] = {0}; // the last local host name the user saw
char lastcompname[MAX_DOMAIN_LABEL+1] = {0}; // the last computer name saved to preferences
char lasthostname[MAX_DOMAIN_LABEL+1] = {0}; // the last local host name saved to preferences

#ifndef NO_CFUSERNOTIFICATION
static CFStringRef CFS_OQ = NULL;
static CFStringRef CFS_CQ = NULL;
static CFStringRef CFS_Format = NULL;
static CFStringRef CFS_ComputerName = NULL;
static CFStringRef CFS_ComputerNameMsg = NULL;
static CFStringRef CFS_LocalHostName = NULL;
static CFStringRef CFS_LocalHostNameMsg = NULL;
static CFStringRef CFS_Problem = NULL;

static CFUserNotificationRef gNotification    = NULL;
static CFRunLoopSourceRef    gNotificationRLS = NULL;

static void NotificationCallBackDismissed(CFUserNotificationRef userNotification, CFOptionFlags responseFlags)
	{
	debug("entry");
	(void)responseFlags;	// Unused
	if (userNotification != gNotification) helplog(ASL_LEVEL_ERR, "NotificationCallBackDismissed: Wrong CFUserNotificationRef");
	if (gNotificationRLS)
		{
		// Caution: don't use CFRunLoopGetCurrent() here, because the currently executing thread may not be our "CFRunLoopRun" thread.
		// We need to explicitly specify the desired CFRunLoop from which we want to remove this event source.
		CFRunLoopRemoveSource(gRunLoop, gNotificationRLS, kCFRunLoopDefaultMode);
		CFRelease(gNotificationRLS);
		gNotificationRLS = NULL;
		CFRelease(gNotification);
		gNotification = NULL;
		}
	// By dismissing the alert, the user has conceptually acknowleged the rename.
	// (e.g. the machine's name is now officially "computer-2.local", not "computer.local".)
	// If we get *another* conflict, the new alert should refer to the 'old' name
	// as now being "computer-2.local", not "computer.local"
	usercompname[0] = 0;
	userhostname[0] = 0;
	lastcompname[0] = 0;
	lasthostname[0] = 0;
	update_idle_timer();
	unpause_idle_timer();
	}

static void ShowNameConflictNotification(CFMutableArrayRef header, CFStringRef subtext)
	{
	CFMutableDictionaryRef dictionary = CFDictionaryCreateMutable(NULL, 0, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);
	if (!dictionary) return;

	debug("entry");

	CFDictionarySetValue(dictionary, kCFUserNotificationAlertHeaderKey, header);
	CFDictionarySetValue(dictionary, kCFUserNotificationAlertMessageKey, subtext);

	CFURLRef urlRef = CFURLCreateWithFileSystemPath(NULL, CFSTR("/System/Library/CoreServices/mDNSResponder.bundle"), kCFURLPOSIXPathStyle, true);
	if (urlRef) { CFDictionarySetValue(dictionary, kCFUserNotificationLocalizationURLKey, urlRef); CFRelease(urlRef); }

	if (gNotification)	// If notification already on-screen, update it in place
		CFUserNotificationUpdate(gNotification, 0, kCFUserNotificationCautionAlertLevel, dictionary);
	else				// else, we need to create it
		{
		SInt32 error;
		gNotification = CFUserNotificationCreate(NULL, 0, kCFUserNotificationCautionAlertLevel, &error, dictionary);
		if (!gNotification || error) { helplog(ASL_LEVEL_ERR, "ShowNameConflictNotification: CFUserNotificationRef: Error %d", error); return; }
		gNotificationRLS = CFUserNotificationCreateRunLoopSource(NULL, gNotification, NotificationCallBackDismissed, 0);
		if (!gNotificationRLS) { helplog(ASL_LEVEL_ERR,"ShowNameConflictNotification: RLS"); CFRelease(gNotification); gNotification = NULL; return; }
		// Caution: don't use CFRunLoopGetCurrent() here, because the currently executing thread may not be our "CFRunLoopRun" thread.
		// We need to explicitly specify the desired CFRunLoop to which we want to add this event source.
		CFRunLoopAddSource(gRunLoop, gNotificationRLS, kCFRunLoopDefaultMode);
		debug("gRunLoop=%p gNotification=%p gNotificationRLS=%p", gRunLoop, gNotification, gNotificationRLS);
		pause_idle_timer();
		}

	CFRelease(dictionary);
	}

static CFMutableArrayRef GetHeader(const char* oldname, const char* newname, const CFStringRef msg, const char* suffix)
	{
	CFMutableArrayRef alertHeader = NULL;

	const CFStringRef cfoldname = CFStringCreateWithCString(NULL, oldname,  kCFStringEncodingUTF8);
	// NULL newname means we've given up trying to construct a name that doesn't conflict
	const CFStringRef cfnewname = newname ? CFStringCreateWithCString(NULL, newname,  kCFStringEncodingUTF8) : NULL;
	// We tag a zero-width non-breaking space at the end of the literal text to guarantee that, no matter what
	// arbitrary computer name the user may choose, this exact text (with zero-width non-breaking space added)
	// can never be one that occurs in the Localizable.strings translation file.
	if (!cfoldname)
		helplog(ASL_LEVEL_ERR,"Could not construct CFStrings for old=%s", newname);
	else if (newname && !cfnewname)
		helplog(ASL_LEVEL_ERR,"Could not construct CFStrings for new=%s", newname);
	else
		{
		const CFStringRef s1 = CFStringCreateWithFormat(NULL, NULL, CFS_Format, cfoldname, suffix);
		const CFStringRef s2 = cfnewname ? CFStringCreateWithFormat(NULL, NULL, CFS_Format, cfnewname, suffix) : NULL;

		alertHeader = CFArrayCreateMutable(NULL, 0, &kCFTypeArrayCallBacks);

		if (!s1)
			helplog(ASL_LEVEL_ERR, "Could not construct secondary CFString for old=%s", oldname);
		else if (cfnewname && !s2)
			helplog(ASL_LEVEL_ERR, "Could not construct secondary CFString for new=%s", newname);
		else if (!alertHeader)
			helplog(ASL_LEVEL_ERR, "Could not construct CFArray for notification");
		else
			{
			// Make sure someone is logged in.  We don't want this popping up over the login window
			uid_t uid;
			gid_t gid;
			CFStringRef userName = SCDynamicStoreCopyConsoleUser(NULL, &uid, &gid);
			if (userName)
				{
				CFRelease(userName);
				CFArrayAppendValue(alertHeader, msg); // Opening phrase of message, provided by caller
				CFArrayAppendValue(alertHeader, CFS_OQ); CFArrayAppendValue(alertHeader, s1); CFArrayAppendValue(alertHeader, CFS_CQ);
				CFArrayAppendValue(alertHeader, CFSTR(" is already in use on this network. "));
				if (s2)
					{
					CFArrayAppendValue(alertHeader, CFSTR("The name has been changed to "));
					CFArrayAppendValue(alertHeader, CFS_OQ); CFArrayAppendValue(alertHeader, s2); CFArrayAppendValue(alertHeader, CFS_CQ);
					CFArrayAppendValue(alertHeader, CFSTR("."));
					}
				else
					CFArrayAppendValue(alertHeader, CFSTR("All attempts to find an available name by adding a number to the name were also unsuccessful."));
				}
			}
		if (s1)          CFRelease(s1);
		if (s2)          CFRelease(s2);
		}
	if (cfoldname) CFRelease(cfoldname);
	if (cfnewname) CFRelease(cfnewname);

	return alertHeader;
	}
#endif /* ndef NO_CFUSERNOTIFICATION */

static void update_notification(void)
	{
#ifndef NO_CFUSERNOTIFICATION
	debug("entry ucn=%s, uhn=%s, lcn=%s, lhn=%s", usercompname, userhostname, lastcompname, lasthostname);
	if (!CFS_OQ)
		{
		// Note: the "\xEF\xBB\xBF" byte sequence in the CFS_Format string is the UTF-8 encoding of the zero-width non-breaking space character.
		// By appending this invisible character on the end of literal names, we ensure the these strings cannot inadvertently match any string
		// in the localization file -- since we know for sure that none of our strings in the localization file contain the ZWNBS character.
		//
		// For languages that are written right to left, when we mix English (host names could be in english with brackets etc. and the
		// rest in Arabic) we need unicode markups for proper formatting. The Unicode sequence 202C (UTF8 E2 80 AC), 200E (UTF8 E2 80 8E) and
		// 202B (UTF8 E2 80 AB) helps with the formatting. See <rdar://problem/8629082> for more details.
		CFS_OQ               = CFStringCreateWithCString(NULL, "???\xE2\x80\xAB",  kCFStringEncodingUTF8);
		CFS_CQ               = CFStringCreateWithCString(NULL, "\xE2\x80\xAC???",  kCFStringEncodingUTF8);
		CFS_Format           = CFStringCreateWithCString(NULL, "%@%s\xEF\xBB\xBF\xE2\x80\x8E", kCFStringEncodingUTF8);
		CFS_ComputerName     = CFStringCreateWithCString(NULL, "The name of your computer ",  kCFStringEncodingUTF8);
		CFS_ComputerNameMsg  = CFStringCreateWithCString(NULL, "To change the name of your computer, "
			"open System Preferences and click Sharing, then type the name in the Computer Name field.",  kCFStringEncodingUTF8);
		CFS_LocalHostName    = CFStringCreateWithCString(NULL, "This computer???s local hostname ",  kCFStringEncodingUTF8);
		CFS_LocalHostNameMsg = CFStringCreateWithCString(NULL, "To change the local hostname, "
			"open System Preferences and click Sharing, then click ???Edit??? and type the name in the Local Hostname field.",  kCFStringEncodingUTF8);
		CFS_Problem          = CFStringCreateWithCString(NULL, "This may indicate a problem with the local network. "
			"Please inform your network administrator.",  kCFStringEncodingUTF8);
		}

	if (!usercompname[0] && !userhostname[0])
		{
		if (gNotificationRLS)
			{
			debug("canceling notification %p", gNotification);
			CFUserNotificationCancel(gNotification);
			unpause_idle_timer();
			}
		}
	else
		{
		CFMutableArrayRef header = NULL;
		CFStringRef* subtext = NULL;
		if (userhostname[0] && !lasthostname[0]) // we've given up trying to construct a name that doesn't conflict
			{
			header = GetHeader(userhostname, NULL, CFS_LocalHostName, ".local");
			subtext = &CFS_Problem;
			}
		else if (usercompname[0])
			{
			header = GetHeader(usercompname, lastcompname, CFS_ComputerName, "");
			subtext = &CFS_ComputerNameMsg;
			}
		else
			{
			header = GetHeader(userhostname, lasthostname, CFS_LocalHostName, ".local");
			subtext = &CFS_LocalHostNameMsg;
			}	
		ShowNameConflictNotification(header, *subtext);
		CFRelease(header);
		}
#endif
	}

kern_return_t
do_mDNSPreferencesSetName(__unused mach_port_t port, int key, const char* old, const char* new, audit_token_t token)
	{
	SCPreferencesRef session = NULL;
	Boolean ok = FALSE;
	Boolean locked = FALSE;
	CFStringRef cfstr = NULL;
	char* user = NULL;
	char* last = NULL;
	Boolean needUpdate = FALSE;

	debug("entry %s old=%s new=%s", key==kmDNSComputerName ? "ComputerName" : (key==kmDNSLocalHostName ? "LocalHostName" : "UNKNOWN"), old, new);
	if (!authorized(&token)) goto fin;

	switch ((enum mDNSPreferencesSetNameKey)key)
		{
		case kmDNSComputerName:
			user = usercompname;
			last = lastcompname;
			break;
		case kmDNSLocalHostName:
			user = userhostname;
			last = lasthostname;
			break;
		default:
			debug("unrecognized key: %d", key);
			goto fin;
		}

	if (!last)
		{
		helplog(ASL_LEVEL_ERR, "%s: no last ptr", __func__);
		goto fin;
		}

	if (!user)
		{
		helplog(ASL_LEVEL_ERR, "%s: no user ptr", __func__);
		goto fin;
		}

	if (0 == strncmp(old, new, MAX_DOMAIN_LABEL+1))
		{
		// old and new are same means the config changed i.e, the user has set something in the preferences pane.
		// This means the conflict has been resolved. We need to dismiss the dialogue.
		if (last[0] && 0 != strncmp(last, new, MAX_DOMAIN_LABEL+1))
			{
			last[0] = 0;
			user[0] = 0;
			needUpdate = TRUE;
			}
		goto fin;
		}
	else
		{
		// old and new are not same, this means there is a conflict. For the first conflict, we show
		// the old value and the new value. For all subsequent conflicts, while the dialogue is still
		// up, we do a real time update of the "new" value in the dialogue. That's why we update just
		// "last" here and not "user".
		if (strncmp(last, new, MAX_DOMAIN_LABEL+1))
			{
			strncpy(last, new, MAX_DOMAIN_LABEL);
			needUpdate = TRUE;
			}
		}

	// If we are not showing the dialogue, we need to remember the first "old" value so that
	// we maintain the same through the lifetime of the dialogue. Subsequence conflicts don't
	// update the "old" value.
	if (!user[0])
		{
		strncpy(user, old, MAX_DOMAIN_LABEL);
		needUpdate = TRUE;
		}

	if (!new[0]) // we've given up trying to construct a name that doesn't conflict
		goto fin;

	cfstr = CFStringCreateWithCString(NULL, new, kCFStringEncodingUTF8);

	session = SCPreferencesCreate(NULL, CFSTR(kmDNSHelperServiceName), NULL);

	if (cfstr == NULL || session == NULL)
		{
		debug("SCPreferencesCreate failed");
		goto fin;
		}
	if (!SCPreferencesLock(session, 0))
		{
		debug("lock failed");
		goto fin;
		}
	locked = TRUE;

	switch ((enum mDNSPreferencesSetNameKey)key)
	{
	case kmDNSComputerName:
		{
		// We want to write the new Computer Name to System Preferences, without disturbing the user-selected
		// system-wide default character set used for things like AppleTalk NBP and NETBIOS service advertising.
		// Note that this encoding is not used for the computer name, but since both are set by the same call,
		// we need to take care to set the name without changing the character set.
		CFStringEncoding encoding = kCFStringEncodingUTF8;
		CFStringRef unused = SCDynamicStoreCopyComputerName(NULL, &encoding);
		if (unused) { CFRelease(unused); unused = NULL; }
		else encoding = kCFStringEncodingUTF8;
		
		ok = SCPreferencesSetComputerName(session, cfstr, encoding);
		}
		break;
	case kmDNSLocalHostName:
		ok = SCPreferencesSetLocalHostName(session, cfstr);
		break;
	default:
		break;
	}

	if (!ok || !SCPreferencesCommitChanges(session) ||
	    !SCPreferencesApplyChanges(session))
		{
		debug("SCPreferences update failed");
		goto fin;
		}
	debug("succeeded");

fin:
	if (NULL != cfstr)
		CFRelease(cfstr);
	if (NULL != session)
		{
		if (locked)
			SCPreferencesUnlock(session);
		CFRelease(session);
		}
	update_idle_timer();
	if (needUpdate) update_notification();
	return KERN_SUCCESS;
	}

enum DNSKeyFormat
	{
	formatNotDNSKey, formatDdnsTypeItem, formatDnsPrefixedServiceItem, formatBtmmPrefixedServiceItem
	};

// On Mac OS X on Intel, the four-character string seems to be stored backwards, at least sometimes.
// I suspect some overenthusiastic inexperienced engineer said, "On Intel everything's backwards,
// therefore I need to add some byte swapping in this API to make this four-character string backwards too."
// To cope with this we allow *both* "ddns" and "sndd" as valid item types.

static const char dnsprefix[] = "dns:";
static const char ddns[] = "ddns";
static const char ddnsrev[] = "sndd";
static const char btmmprefix[] = "btmmdns:";

#ifndef NO_SECURITYFRAMEWORK
static enum DNSKeyFormat
getDNSKeyFormat(SecKeychainItemRef item, SecKeychainAttributeList **attributesp)
	{
	static UInt32 tags[4] =
		{
		kSecTypeItemAttr, kSecServiceItemAttr, kSecAccountItemAttr, kSecLabelItemAttr
		};
	static SecKeychainAttributeInfo attributeInfo =
		{
		sizeof(tags)/sizeof(tags[0]), tags, NULL
		};
	SecKeychainAttributeList *attributes = NULL;
	enum DNSKeyFormat format;
	Boolean malformed = FALSE;
	OSStatus status = noErr;
	int i = 0;

	*attributesp = NULL;
	if (noErr != (status = SecKeychainItemCopyAttributesAndData(item,
	    &attributeInfo, NULL, &attributes, NULL, NULL)))
		{
		debug("SecKeychainItemCopyAttributesAndData %d - skipping",
		    status);
		goto skip;
		}
	if (attributeInfo.count != attributes->count)
		malformed = TRUE;
	for (i = 0; !malformed && i < (int)attributeInfo.count; ++i)
		if (attributeInfo.tag[i] != attributes->attr[i].tag)
			malformed = TRUE;
	if (malformed)
		{
		debug(
       "malformed result from SecKeychainItemCopyAttributesAndData - skipping");
		goto skip;
		}
		
	debug("entry (\"%.*s\", \"%.*s\", \"%.*s\")",
	    (int)attributes->attr[0].length, attributes->attr[0].data,
	    (int)attributes->attr[1].length, attributes->attr[1].data,
	    (int)attributes->attr[2].length, attributes->attr[2].data);
	if (attributes->attr[1].length >= MAX_ESCAPED_DOMAIN_NAME +
	    sizeof(dnsprefix)-1)
		{
		debug("kSecServiceItemAttr too long (%u) - skipping",
		    (unsigned int)attributes->attr[1].length);
		goto skip;
		}
	if (attributes->attr[2].length >= MAX_ESCAPED_DOMAIN_NAME)
		{
		debug("kSecAccountItemAttr too long (%u) - skipping",
		    (unsigned int)attributes->attr[2].length);
		goto skip;
		}
	if (attributes->attr[1].length >= sizeof(dnsprefix)-1 &&
	    0 == strncasecmp(attributes->attr[1].data, dnsprefix,
	    sizeof(dnsprefix)-1))
		format = formatDnsPrefixedServiceItem;
	else if (attributes->attr[1].length >= sizeof(btmmprefix)-1 &&
	    0 == strncasecmp(attributes->attr[1].data, btmmprefix, sizeof(btmmprefix)-1))
		format = formatBtmmPrefixedServiceItem;
	else if (attributes->attr[0].length == sizeof(ddns)-1 &&
	    0 == strncasecmp(attributes->attr[0].data, ddns, sizeof(ddns)-1))
		format = formatDdnsTypeItem;
	else if (attributes->attr[0].length == sizeof(ddnsrev)-1 &&
	    0 == strncasecmp(attributes->attr[0].data, ddnsrev, sizeof(ddnsrev)-1))
		format = formatDdnsTypeItem;
	else
		{
		debug("uninterested in this entry");
		goto skip;
		}
	*attributesp = attributes;
	debug("accepting this entry");
	return format;

skip:
	SecKeychainItemFreeAttributesAndData(attributes, NULL);
	return formatNotDNSKey;
	}

// Insert the attributes as defined by mDNSKeyChainAttributes
static CFPropertyListRef
getKeychainItemInfo(SecKeychainItemRef item,
    SecKeychainAttributeList *attributes, enum DNSKeyFormat format)
	{
	CFMutableArrayRef entry = NULL;
	CFDataRef data = NULL;
	OSStatus status = noErr;
	UInt32 keylen = 0;
	void *keyp = 0;

	if (NULL == (entry = CFArrayCreateMutable(NULL, 0,
	    &kCFTypeArrayCallBacks)))
		{
		debug("CFArrayCreateMutable failed");
		goto error;
		}

	// Insert the Account attribute (kmDNSKcWhere)
	switch ((enum DNSKeyFormat)format)
	{
	case formatDdnsTypeItem:
		data = CFDataCreate(kCFAllocatorDefault,
		    attributes->attr[1].data, attributes->attr[1].length);
		break;
	case formatDnsPrefixedServiceItem:
	case formatBtmmPrefixedServiceItem:
		data = CFDataCreate(kCFAllocatorDefault,
		    attributes->attr[1].data, attributes->attr[1].length);
		break;
	default:
		assert("unknown DNSKeyFormat value");
		break;
		}
	if (NULL == data)
		{
		debug("CFDataCreate for attr[1] failed");
		goto error;
		}
	CFArrayAppendValue(entry, data);
	CFRelease(data);

	// Insert the Where attribute (kmDNSKcAccount)
	if (NULL == (data = CFDataCreate(kCFAllocatorDefault,
	    attributes->attr[2].data, attributes->attr[2].length)))
		{
		debug("CFDataCreate for attr[2] failed");
		goto error;
		}
	CFArrayAppendValue(entry, data);
	CFRelease(data);

	// Insert the Key attribute (kmDNSKcKey)
	if (noErr != (status = SecKeychainItemCopyAttributesAndData(item, NULL,
	    NULL, NULL, &keylen, &keyp)))
		{
		debug("could not retrieve key for \"%.*s\": %d",
		    (int)attributes->attr[1].length, attributes->attr[1].data,
		    status);
		goto error;
		}
	data = CFDataCreate(kCFAllocatorDefault, keyp, keylen);
	SecKeychainItemFreeAttributesAndData(NULL, keyp);
	if (NULL == data)
		{
		debug("CFDataCreate for keyp failed");
		goto error;
		}
	CFArrayAppendValue(entry, data);
	CFRelease(data);

	// Insert the Name attribute (kmDNSKcName)
	if (NULL == (data = CFDataCreate(kCFAllocatorDefault,
	    attributes->attr[3].data, attributes->attr[3].length)))
		{
		debug("CFDataCreate for attr[3] failed");
		goto error;
		}
	CFArrayAppendValue(entry, data);
	CFRelease(data);
	return entry;

error:
	if (NULL != entry)
		CFRelease(entry);
	return NULL;
	}
#endif

kern_return_t
do_mDNSKeychainGetSecrets(__unused mach_port_t port, __unused unsigned int *numsecrets,
    __unused vm_offset_t *secrets, __unused mach_msg_type_number_t *secretsCnt, __unused int *err,
    __unused audit_token_t token)
	{
#ifndef NO_SECURITYFRAMEWORK
	CFWriteStreamRef stream = NULL;
	CFDataRef result = NULL;
	CFPropertyListRef entry = NULL;
	CFMutableArrayRef keys = NULL;
	SecKeychainRef skc = NULL;
	SecKeychainItemRef item = NULL;
	SecKeychainSearchRef search = NULL;
	SecKeychainAttributeList *attributes = NULL;
	enum DNSKeyFormat format;
	OSStatus status = 0;

	debug("entry");
	*err = 0;
	*numsecrets = 0;
	*secrets = (vm_offset_t)NULL;
	if (!authorized(&token))
		{
		*err = kmDNSHelperNotAuthorized;
		goto fin;
		}
	if (NULL == (keys = CFArrayCreateMutable(NULL, 0,
	    &kCFTypeArrayCallBacks)))
		{
		debug("CFArrayCreateMutable failed");
		*err = kmDNSHelperCreationFailed;
		goto fin;
		}
	if (noErr != (status = SecKeychainCopyDefault(&skc)))
		{
		*err = kmDNSHelperKeychainCopyDefaultFailed;
		goto fin;
		}
	if (noErr != (status = SecKeychainSearchCreateFromAttributes(skc, kSecGenericPasswordItemClass, NULL, &search)))
		{
		*err = kmDNSHelperKeychainSearchCreationFailed;
		goto fin;
		}
	for (status = SecKeychainSearchCopyNext(search, &item);
	     noErr == status;
	     status = SecKeychainSearchCopyNext(search, &item))
		{
		if (formatNotDNSKey != (format = getDNSKeyFormat(item,
		    &attributes)) &&
		    NULL != (entry = getKeychainItemInfo(item, attributes,
		    format)))
			{
			CFArrayAppendValue(keys, entry);
			CFRelease(entry);
			}
		SecKeychainItemFreeAttributesAndData(attributes, NULL);
		CFRelease(item);
		}
	if (errSecItemNotFound != status)
		helplog(ASL_LEVEL_ERR, "%s: SecKeychainSearchCopyNext failed: %d",
		    __func__, status);
	if (NULL == (stream =
	    CFWriteStreamCreateWithAllocatedBuffers(kCFAllocatorDefault,
	    kCFAllocatorDefault)))
		{
		*err = kmDNSHelperCreationFailed;
		debug("CFWriteStreamCreateWithAllocatedBuffers failed");
		goto fin;
		}
	CFWriteStreamOpen(stream);
	if (0 == CFPropertyListWriteToStream(keys, stream,
	    kCFPropertyListBinaryFormat_v1_0, NULL))
		{
		*err = kmDNSHelperPListWriteFailed;
		debug("CFPropertyListWriteToStream failed");
		goto fin;
		}
	result = CFWriteStreamCopyProperty(stream,
	    kCFStreamPropertyDataWritten);
	if (KERN_SUCCESS != vm_allocate(mach_task_self(), secrets,
	    CFDataGetLength(result), VM_FLAGS_ANYWHERE))
		{
		*err = kmDNSHelperCreationFailed;
		debug("vm_allocate failed");
		goto fin;
		}
	CFDataGetBytes(result, CFRangeMake(0, CFDataGetLength(result)),
	    (void *)*secrets);
	*secretsCnt = CFDataGetLength(result);
	*numsecrets = CFArrayGetCount(keys);
	debug("succeeded");

fin:
	debug("returning %u secrets", *numsecrets);
	if (NULL != stream)
		{
		CFWriteStreamClose(stream);
		CFRelease(stream);
		}
	if (NULL != result)
		CFRelease(result);
	if (NULL != keys)
		CFRelease(keys);
	if (NULL != search)
		CFRelease(search);
	if (NULL != skc)
		CFRelease(skc);
	update_idle_timer();
	return KERN_SUCCESS;
#else
	return KERN_FAILURE;
#endif
	}

#ifndef MDNS_NO_IPSEC
typedef enum _mDNSTunnelPolicyWhich
	{
	kmDNSTunnelPolicySetup,
	kmDNSTunnelPolicyTeardown,
	kmDNSTunnelPolicyGenerate
	} mDNSTunnelPolicyWhich;

// For kmDNSTunnelPolicySetup, you can setup IPv6-in-IPv6 tunnel or IPv6-in-IPv4 tunnel
// kmDNSNoTunnel is used for other Policy types
typedef enum _mDNSTunnelType
	{
	kmDNSNoTunnel,
	kmDNSIPv6IPv4Tunnel,
	kmDNSIPv6IPv6Tunnel
	} mDNSTunnelType;

static const uint8_t kWholeV6Mask = 128;
static const uint8_t kZeroV6Mask  = 0;

static int
doTunnelPolicy(mDNSTunnelPolicyWhich which, mDNSTunnelType type,
	       v6addr_t loc_inner, uint8_t loc_bits,
	       v4addr_t loc_outer, uint16_t loc_port, 
	       v6addr_t rmt_inner, uint8_t rmt_bits,
	       v4addr_t rmt_outer, uint16_t rmt_port,
		   v6addr_t loc_outer6, v6addr_t rmt_outer6);

static int
aliasTunnelAddress(v6addr_t address)
	{
	struct in6_aliasreq ifra_in6;
	int err = 0;
	int s = -1;

	if (0 > (s = socket(AF_INET6, SOCK_DGRAM, 0)))
		{
		helplog(ASL_LEVEL_ERR, "socket(AF_INET6, ...) failed: %s",
		    strerror(errno));
		err = kmDNSHelperDatagramSocketCreationFailed;
		goto fin;
		}
	memset(&ifra_in6, 0, sizeof(ifra_in6));
	strlcpy(ifra_in6.ifra_name, kTunnelAddressInterface,
	    sizeof(ifra_in6.ifra_name));
	ifra_in6.ifra_lifetime.ia6t_vltime = ND6_INFINITE_LIFETIME;
	ifra_in6.ifra_lifetime.ia6t_pltime = ND6_INFINITE_LIFETIME;

	ifra_in6.ifra_addr.sin6_family = AF_INET6;
	ifra_in6.ifra_addr.sin6_len = sizeof(struct sockaddr_in6);
	memcpy(&(ifra_in6.ifra_addr.sin6_addr), address,
	    sizeof(ifra_in6.ifra_addr.sin6_addr));

	ifra_in6.ifra_prefixmask.sin6_family = AF_INET6;
	ifra_in6.ifra_prefixmask.sin6_len = sizeof(struct sockaddr_in6);
	memset(&(ifra_in6.ifra_prefixmask.sin6_addr), 0xFF,
	    sizeof(ifra_in6.ifra_prefixmask.sin6_addr));

	if (0 > ioctl(s, SIOCAIFADDR_IN6, &ifra_in6))
		{
		helplog(ASL_LEVEL_ERR,
		    "ioctl(..., SIOCAIFADDR_IN6, ...) failed: %s",
		    strerror(errno));
		err = kmDNSHelperInterfaceCreationFailed;
		goto fin;
		}

	v6addr_t zero = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0	};
	err = doTunnelPolicy(kmDNSTunnelPolicyGenerate, kmDNSNoTunnel,
	    address, kWholeV6Mask, NULL, 0,
	    zero, kZeroV6Mask, NULL, 0, NULL, NULL);

fin:
	if (0 <= s)
		close(s);
	return err;
	}

static int
unaliasTunnelAddress(v6addr_t address)
	{
	struct in6_ifreq ifr;
	int err = 0;
	int s = -1;

	if (0 > (s = socket(AF_INET6, SOCK_DGRAM, 0)))
		{
		helplog(ASL_LEVEL_ERR, "socket(AF_INET6, ...) failed: %s",
		    strerror(errno));
		err = kmDNSHelperDatagramSocketCreationFailed;
		goto fin;
		}
	memset(&ifr, 0, sizeof(ifr));
	strlcpy(ifr.ifr_name, kTunnelAddressInterface, sizeof(ifr.ifr_name));
	ifr.ifr_ifru.ifru_addr.sin6_family = AF_INET6;
	ifr.ifr_ifru.ifru_addr.sin6_len = sizeof(struct sockaddr_in6);
	memcpy(&(ifr.ifr_ifru.ifru_addr.sin6_addr), address,
	    sizeof(ifr.ifr_ifru.ifru_addr.sin6_addr));

	if (0 > ioctl(s, SIOCDIFADDR_IN6, &ifr))
		{
		helplog(ASL_LEVEL_ERR,
		    "ioctl(..., SIOCDIFADDR_IN6, ...) failed: %s",
		    strerror(errno));
		err = kmDNSHelperInterfaceDeletionFailed;
		goto fin;
		}

	v6addr_t zero = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	err = doTunnelPolicy(kmDNSTunnelPolicyTeardown, kmDNSNoTunnel,
	    address, kWholeV6Mask, NULL, 0,
	    zero, kZeroV6Mask, NULL, 0, NULL, NULL);

fin:
	if (0 <= s)
		close(s);
	return err;
	}
#endif /* ifndef MDNS_NO_IPSEC */

int
do_mDNSAutoTunnelInterfaceUpDown(__unused mach_port_t port, int updown,
    v6addr_t address, audit_token_t token)
	{
#ifndef MDNS_NO_IPSEC
	debug("entry");
	if (!authorized(&token)) goto fin;

	switch ((enum mDNSUpDown)updown)
		{
		case kmDNSUp:
			aliasTunnelAddress(address);
			break;
		case kmDNSDown:
			unaliasTunnelAddress(address);
			break;
		default:
			goto fin;
		}
	debug("succeeded");

fin:
#else
	(void)port; (void)updown; (void)address; (void)token;
#endif
	update_idle_timer();
	return KERN_SUCCESS;
	}

#ifndef MDNS_NO_IPSEC

static const char g_racoon_config_dir[] = "/var/run/racoon/";
static const char g_racoon_config_dir_old[] = "/etc/racoon/remote/";

CF_EXPORT CFDictionaryRef _CFCopySystemVersionDictionary(void);
CF_EXPORT const CFStringRef _kCFSystemVersionBuildVersionKey;

// Major version  6 is 10.2.x (Jaguar)
// Major version  7 is 10.3.x (Panther)
// Major version  8 is 10.4.x (Tiger)
// Major version  9 is 10.5.x (Leopard)
// Major version 10 is 10.6.x (SnowLeopard)
static int MacOSXSystemBuildNumber(char* letter_out, int* minor_out)
	{
	int major = 0, minor = 0;
	char letter = 0, buildver[256]="<Unknown>";
	CFDictionaryRef vers = _CFCopySystemVersionDictionary();
	if (vers)
		{
		CFStringRef cfbuildver = CFDictionaryGetValue(vers, _kCFSystemVersionBuildVersionKey);
		if (cfbuildver) CFStringGetCString(cfbuildver, buildver, sizeof(buildver), kCFStringEncodingUTF8);
		sscanf(buildver, "%d%c%d", &major, &letter, &minor);
		CFRelease(vers);
		}
	else
		helplog(ASL_LEVEL_NOTICE, "_CFCopySystemVersionDictionary failed");
	
	if (!major) { major=10; letter = 'A'; minor = 190; helplog(ASL_LEVEL_NOTICE, "Note: No Major Build Version number found; assuming 10A190"); }
	if (letter_out) *letter_out = letter;
	if (minor_out) *minor_out = minor;
	return(major);
	}
	
static int UseOldRacoon()
	{
	static int g_oldRacoon = -1;

	if (g_oldRacoon == -1)
		{
		char letter = 0;
		int minor = 0;
		g_oldRacoon = (MacOSXSystemBuildNumber(&letter, &minor) < 10);
		debug("%s", g_oldRacoon?"old":"new");
		}

	return g_oldRacoon;
	}
	
static int RacoonSignal()
	{
	return UseOldRacoon() ? SIGHUP : SIGUSR1;
	}
	
static const char* GetRacoonConfigDir()
	{
	return UseOldRacoon() ? g_racoon_config_dir_old : g_racoon_config_dir;
	}
	
static const char* GetOldRacoonConfigDir()
	{
	return UseOldRacoon() ? NULL : g_racoon_config_dir_old;
	}
	
static const char racoon_config_file[] = "anonymous.conf";
static const char racoon_config_file_orig[] = "anonymous.conf.orig";

static const char configHeader[] = "# BackToMyMac\n";

static int IsFamiliarRacoonConfiguration(const char* racoon_config_path)
	{
	int fd = open(racoon_config_path, O_RDONLY);
	debug("entry %s", racoon_config_path);
	if (0 > fd)
		{
		helplog(ASL_LEVEL_NOTICE, "open \"%s\" failed: %s", racoon_config_path, strerror(errno));
		return 0;
		}
	else
		{
		char header[sizeof(configHeader)] = {0};
		ssize_t bytesRead = read(fd, header, sizeof(header)-1);
		close(fd);
		if (bytesRead != sizeof(header)-1) return 0;
		return (0 == memcmp(header, configHeader, sizeof(header)-1));
		}
	}

static void
revertAnonymousRacoonConfiguration(const char* dir)
	{
	if (!dir) return;
	
	debug("entry %s", dir);

	char racoon_config_path[64];
	strlcpy(racoon_config_path, dir, sizeof(racoon_config_path));
	strlcat(racoon_config_path, racoon_config_file, sizeof(racoon_config_path));

	struct stat s;
	int ret = stat(racoon_config_path, &s);
	debug("stat(%s): %d errno=%d", racoon_config_path, ret, errno);
	if (ret == 0)
		{
		if (IsFamiliarRacoonConfiguration(racoon_config_path))
			{
			helplog(ASL_LEVEL_INFO, "\"%s\" looks familiar, unlinking", racoon_config_path);
			unlink(racoon_config_path);
			}
		else
			{
			helplog(ASL_LEVEL_NOTICE, "\"%s\" does not look familiar, leaving in place", racoon_config_path);
			return;
			}
		}
	else if (errno != ENOENT)
		{
		helplog(ASL_LEVEL_NOTICE, "stat failed for \"%s\", leaving in place: %s", racoon_config_path, strerror(errno));
		return;
		}

	char racoon_config_path_orig[64];
	strlcpy(racoon_config_path_orig, dir, sizeof(racoon_config_path_orig));
	strlcat(racoon_config_path_orig, racoon_config_file_orig, sizeof(racoon_config_path_orig));

	ret = stat(racoon_config_path_orig, &s);
	debug("stat(%s): %d errno=%d", racoon_config_path_orig, ret, errno);
	if (ret == 0)
		{
		if (0 > rename(racoon_config_path_orig, racoon_config_path))
			helplog(ASL_LEVEL_NOTICE, "rename \"%s\" \"%s\" failed: %s", racoon_config_path_orig, racoon_config_path, strerror(errno));
		else
			debug("reverted \"%s\" to \"%s\"", racoon_config_path_orig, racoon_config_path);
		}
	else if (errno != ENOENT)
		{
		helplog(ASL_LEVEL_NOTICE, "stat failed for \"%s\", leaving in place: %s", racoon_config_path_orig, strerror(errno));
		return;
		}
	}

static void
moveAsideAnonymousRacoonConfiguration(const char* dir)
	{
	if (!dir) return;
	
	debug("entry %s", dir);
	
	char racoon_config_path[64];
	strlcpy(racoon_config_path, dir, sizeof(racoon_config_path));
	strlcat(racoon_config_path, racoon_config_file, sizeof(racoon_config_path));
	
	struct stat s;
	int ret = stat(racoon_config_path, &s);
	if (ret == 0)
		{
		if (IsFamiliarRacoonConfiguration(racoon_config_path))
			{
			helplog(ASL_LEVEL_INFO, "\"%s\" looks familiar, unlinking", racoon_config_path);
			unlink(racoon_config_path);
			}
		else
			{
			char racoon_config_path_orig[64];
			strlcpy(racoon_config_path_orig, dir, sizeof(racoon_config_path_orig));
			strlcat(racoon_config_path_orig, racoon_config_file_orig, sizeof(racoon_config_path_orig));
			if (0 > rename(racoon_config_path, racoon_config_path_orig)) // If we didn't write it, move it to the side so it can be reverted later
				helplog(ASL_LEVEL_NOTICE, "rename \"%s\" to \"%s\" failed: %s", racoon_config_path, racoon_config_path_orig, strerror(errno));
			else
				debug("successfully renamed \"%s\" to \"%s\"", racoon_config_path, racoon_config_path_orig);
			}
		}
	else if (errno != ENOENT)
		{
		helplog(ASL_LEVEL_NOTICE, "stat failed for \"%s\", leaving in place: %s", racoon_config_path, strerror(errno));
		return;
		}
	}

static int
ensureExistenceOfRacoonConfigDir(const char* const racoon_config_dir)
	{
	struct stat s;
	int ret = stat(racoon_config_dir, &s);
	if (ret != 0)
		{
		if (errno != ENOENT)
			{
			helplog(ASL_LEVEL_ERR, "stat of \"%s\" failed (%d): %s",
				racoon_config_dir, ret, strerror(errno));
			return -1;
			}
		else
			{
			ret = mkdir(racoon_config_dir, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
			if (ret != 0)
				{
				helplog(ASL_LEVEL_ERR, "mkdir \"%s\" failed: %s",
					racoon_config_dir, strerror(errno));
				return -1;
				}
			else
				helplog(ASL_LEVEL_INFO, "created directory \"%s\"", racoon_config_dir);
			}
		}
	else if (!(s.st_mode & S_IFDIR))
		{
		helplog(ASL_LEVEL_ERR, "\"%s\" is not a directory!",
			racoon_config_dir);
		return -1;
		}
	
	return 0;
	}

static int
createAnonymousRacoonConfiguration(const char *fqdn)
	{
	static const char config1[] =
	  "remote anonymous {\n"
	  "  exchange_mode aggressive;\n"
	  "  doi ipsec_doi;\n"
	  "  situation identity_only;\n"
	  "  verify_identifier off;\n"
	  "  generate_policy on;\n"
	  "  shared_secret keychain_by_id \"";
	static const char config2[] =
	  "\";\n"
	  "  nonce_size 16;\n"
	  "  lifetime time 15 min;\n"
	  "  initial_contact on;\n"
	  "  support_proxy on;\n"
	  "  nat_traversal force;\n"
	  "  proposal_check claim;\n"
	  "  proposal {\n"
	  "    encryption_algorithm aes;\n"
	  "    hash_algorithm sha1;\n"
	  "    authentication_method pre_shared_key;\n"
	  "    dh_group 2;\n"
	  "    lifetime time 15 min;\n"
	  "  }\n"
	  "}\n\n"
	  "sainfo anonymous { \n"
	  "  pfs_group 2;\n"
	  "  lifetime time 10 min;\n"
	  "  encryption_algorithm aes;\n"
	  "  authentication_algorithm hmac_sha1;\n"
	  "  compression_algorithm deflate;\n"
	  "}\n";
	char tmp_config_path[64];
	char racoon_config_path[64];
	const char* const racoon_config_dir = GetRacoonConfigDir();
	const char* const racoon_config_dir_old = GetOldRacoonConfigDir();
	int fd = -1;
	
	debug("entry");
	
	if (0 > ensureExistenceOfRacoonConfigDir(racoon_config_dir))
		return -1;

	strlcpy(tmp_config_path, racoon_config_dir, sizeof(tmp_config_path));
	strlcat(tmp_config_path, "tmp.XXXXXX", sizeof(tmp_config_path));

	fd = mkstemp(tmp_config_path);

	if (0 > fd)
		{
		helplog(ASL_LEVEL_ERR, "mkstemp \"%s\" failed: %s",
		    tmp_config_path, strerror(errno));
		return -1;
		}
	write(fd, configHeader, sizeof(configHeader)-1);
	write(fd, config1, sizeof(config1)-1);
	write(fd, fqdn, strlen(fqdn));
	write(fd, config2, sizeof(config2)-1);
	close(fd);

	strlcpy(racoon_config_path, racoon_config_dir, sizeof(racoon_config_path));
	strlcat(racoon_config_path, racoon_config_file, sizeof(racoon_config_path));

	moveAsideAnonymousRacoonConfiguration(racoon_config_dir_old);
	moveAsideAnonymousRacoonConfiguration(racoon_config_dir);

	if (0 > rename(tmp_config_path, racoon_config_path))
		{
		unlink(tmp_config_path);
		helplog(ASL_LEVEL_ERR, "rename \"%s\" \"%s\" failed: %s",
		    tmp_config_path, racoon_config_path, strerror(errno));
		revertAnonymousRacoonConfiguration(racoon_config_dir_old);
		revertAnonymousRacoonConfiguration(racoon_config_dir);
		return -1;
		}

	debug("successfully renamed \"%s\" \"%s\"", tmp_config_path, racoon_config_path);
	return 0;
	}

static int
notifyRacoon(void)
	{
	debug("entry");
	static const char racoon_pid_path[] = "/var/run/racoon.pid";
	char buf[] = "18446744073709551615"; /* largest 64-bit integer */
	char *p = NULL;
	ssize_t n = 0;
	unsigned long m = 0;
	int fd = open(racoon_pid_path, O_RDONLY);

	if (0 > fd)
		{
		debug("open \"%s\" failed, and that's OK: %s", racoon_pid_path,
		    strerror(errno));
		return kmDNSHelperRacoonNotificationFailed;
		}
	n = read(fd, buf, sizeof(buf)-1);
	close(fd);
	if (1 > n)
		{
		debug("read of \"%s\" failed: %s", racoon_pid_path,
		    n == 0 ? "empty file" : strerror(errno));
		return kmDNSHelperRacoonNotificationFailed;
		}
	buf[n] = '\0';
	m = strtoul(buf, &p, 10);
	if (*p != '\0' && !isspace(*p))
		{
		debug("invalid PID \"%s\" (around '%c')", buf, *p);
		return kmDNSHelperRacoonNotificationFailed;
		}
	if (2 > m)
		{
		debug("refusing to kill PID %lu", m);
		return kmDNSHelperRacoonNotificationFailed;
		}
	if (0 != kill(m, RacoonSignal()))
		{
		debug("Could not signal racoon (%lu): %s", m, strerror(errno));
		return kmDNSHelperRacoonNotificationFailed;
		}
	debug("Sent racoon (%lu) signal %d", m, RacoonSignal());
	return 0;
	}

static void
closefds(int from)
	{
	int fd = 0;
	struct dirent entry, *entryp = NULL;
	DIR *dirp = opendir("/dev/fd");

	if (dirp == NULL)
		{
		/* fall back to the erroneous getdtablesize method */
		for (fd = from; fd < getdtablesize(); ++fd)
			close(fd);
		return;
		}
	while (0 == readdir_r(dirp, &entry, &entryp) && NULL != entryp)
		{
		fd = atoi(entryp->d_name);
		if (fd >= from && fd != dirfd(dirp))
			close(fd);
		}
	closedir(dirp);
	}

static int
startRacoonOld(void)
	{
	debug("entry");
	char * const racoon_args[] = { "/usr/sbin/racoon", "-e", NULL 	};
	ssize_t n = 0;
	pid_t pid = 0;
	int status = 0;

	if (0 == (pid = fork()))
		{
		closefds(0);
		execve(racoon_args[0], racoon_args, NULL);
		helplog(ASL_LEVEL_ERR, "execve of \"%s\" failed: %s",
		    racoon_args[0], strerror(errno));
		exit(2);
		}
	helplog(ASL_LEVEL_NOTICE, "racoon (pid=%lu) started",
	    (unsigned long)pid);
	n = waitpid(pid, &status, 0);
	if (-1 == n)
		{
		helplog(ASL_LEVEL_ERR, "Unexpected waitpid failure: %s",
		    strerror(errno));
		return kmDNSHelperRacoonStartFailed;
		}
	else if (pid != n)
		{
		helplog(ASL_LEVEL_ERR, "Unexpected waitpid return value %d",
		    (int)n);
		return kmDNSHelperRacoonStartFailed;
		}
	else if (WIFSIGNALED(status))
		{
		helplog(ASL_LEVEL_ERR,
		    "racoon (pid=%lu) terminated due to signal %d",
		    (unsigned long)pid, WTERMSIG(status));
		return kmDNSHelperRacoonStartFailed;
		}
	else if (WIFSTOPPED(status))
		{
		helplog(ASL_LEVEL_ERR,
		    "racoon (pid=%lu) has stopped due to signal %d",
		    (unsigned long)pid, WSTOPSIG(status));
		return kmDNSHelperRacoonStartFailed;
		}
	else if (0 != WEXITSTATUS(status))
		{
		helplog(ASL_LEVEL_ERR,
		    "racoon (pid=%lu) exited with status %d",
		    (unsigned long)pid, WEXITSTATUS(status));
		return kmDNSHelperRacoonStartFailed;
		}
	debug("racoon (pid=%lu) daemonized normally", (unsigned long)pid);
	return 0;
	}

// constant and structure for the racoon control socket
#define VPNCTL_CMD_PING 0x0004
typedef struct vpnctl_hdr_struct
	{
	u_int16_t msg_type;
	u_int16_t flags;
	u_int32_t cookie;
	u_int32_t reserved;
	u_int16_t result;
	u_int16_t len;
	} vpnctl_hdr;

static int
startRacoon(void)
	{
	debug("entry");
	int fd = socket(PF_UNIX, SOCK_STREAM, 0);
	if (0 > fd)
		{
		helplog(ASL_LEVEL_ERR, "Could not create endpoint for racoon control socket: %d %s",
			errno, strerror(errno));
		return kmDNSHelperRacoonStartFailed;
		}

	struct sockaddr_un saddr;
	memset(&saddr, 0, sizeof(saddr));
	saddr.sun_family = AF_UNIX;
	saddr.sun_len = sizeof(saddr);
	static const char racoon_control_sock_path[] = "/var/run/vpncontrol.sock";
	strcpy(saddr.sun_path, racoon_control_sock_path);
	int result = connect(fd, (struct sockaddr*) &saddr, saddr.sun_len);
	if (0 > result)
		{
		helplog(ASL_LEVEL_ERR, "Could not connect racoon control socket %s: %d %s",
			racoon_control_sock_path, errno, strerror(errno));
		return kmDNSHelperRacoonStartFailed;
		}
	
	u_int32_t btmm_cookie = 0x4d4d5442;
	vpnctl_hdr h = { VPNCTL_CMD_PING, 0, btmm_cookie, 0, 0, 0 };
	size_t bytes = 0;
	ssize_t ret = 0;
	
	while (bytes < sizeof(vpnctl_hdr))
		{
		ret = write(fd, ((unsigned char*)&h)+bytes, sizeof(vpnctl_hdr) - bytes);
		if (ret == -1)
			{
			helplog(ASL_LEVEL_ERR, "Could not write to racoon control socket: %d %s",
				errno, strerror(errno));
			return kmDNSHelperRacoonStartFailed;
			}
		bytes += ret;
		}
	
	int nfds = fd + 1;
	fd_set fds;
	int counter = 0;
	struct timeval tv;
	bytes = 0;
	h.cookie = 0;
	
	for (counter = 0; counter < 100; counter++)
		{
		FD_ZERO(&fds);
		FD_SET(fd, &fds);
		tv = (struct timeval){ 0, 10000 }; // 10 milliseconds * 100 iterations = 1 second max wait time

		result = select(nfds, &fds, (fd_set*)NULL, (fd_set*)NULL, &tv);
		if (result > 0)
			{
			if (FD_ISSET(fd, &fds))
				{
				ret = read(fd, ((unsigned char*)&h)+bytes, sizeof(vpnctl_hdr) - bytes);
				
				if (ret == -1)
					{
					helplog(ASL_LEVEL_ERR, "Could not read from racoon control socket: %d %s",
						strerror(errno));
					break;
					}
				bytes += ret;
				if (bytes >= sizeof(vpnctl_hdr)) break;
				}
			else
				{
				debug("select returned but fd_isset not on expected fd\n");
				}
			}
		else if (result < 0)
			{
			debug("select returned %d errno %d %s\n", result, errno, strerror(errno));
			if (errno != EINTR) break;
			}
		}
	
	close(fd);
	
	if (bytes < sizeof(vpnctl_hdr) || h.cookie != btmm_cookie) return kmDNSHelperRacoonStartFailed;

	debug("racoon started");
	return 0;
	}

static int
kickRacoon(void)
	{
	if ( 0 == notifyRacoon() )
		return 0;
	return UseOldRacoon() ? startRacoonOld() : startRacoon();
	}

#endif /* ndef MDNS_NO_IPSEC */

int
do_mDNSConfigureServer(__unused mach_port_t port, int updown, const char *fqdn, audit_token_t token)
	{
#ifndef MDNS_NO_IPSEC
	debug("entry");
	if (!authorized(&token)) goto fin;

	switch ((enum mDNSUpDown)updown)
		{
		case kmDNSUp:
			if (0 != createAnonymousRacoonConfiguration(fqdn)) goto fin;
			break;
		case kmDNSDown:
			revertAnonymousRacoonConfiguration(GetOldRacoonConfigDir());
			revertAnonymousRacoonConfiguration(GetRacoonConfigDir());
			break;
		default:
			goto fin;
		}

	if (0 != kickRacoon())
		goto fin;
	debug("succeeded");

fin:
#else
	(void)port; (void)updown; (void)fqdn; (void)token;
#endif
	update_idle_timer();
	return KERN_SUCCESS;
	}

#ifndef MDNS_NO_IPSEC

static unsigned int routeSeq = 1;

static int
setupTunnelRoute(v6addr_t local, v6addr_t remote)
	{
	struct
		{
		struct rt_msghdr    hdr;
		struct sockaddr_in6 dst;
		struct sockaddr_in6 gtwy;
		} msg;
	int err = 0;
	int s = -1;

	if (0 > (s = socket(PF_ROUTE, SOCK_RAW, AF_INET)))
		{
		helplog(ASL_LEVEL_ERR, "socket(PF_ROUTE, ...) failed: %s",
		    strerror(errno));
		err = kmDNSHelperRoutingSocketCreationFailed;
		goto fin;
		}
	memset(&msg, 0, sizeof(msg));
	msg.hdr.rtm_msglen = sizeof(msg);
	msg.hdr.rtm_type = RTM_ADD;
	/* The following flags are set by `route add -inet6 -host ...` */
	msg.hdr.rtm_flags = RTF_UP | RTF_GATEWAY | RTF_HOST | RTF_STATIC;
	msg.hdr.rtm_version = RTM_VERSION;
	msg.hdr.rtm_seq = routeSeq++;
	msg.hdr.rtm_addrs = RTA_DST | RTA_GATEWAY;
	msg.hdr.rtm_inits = RTV_MTU;
	msg.hdr.rtm_rmx.rmx_mtu = 1280;

	msg.dst.sin6_len = sizeof(msg.dst);
	msg.dst.sin6_family = AF_INET6;
	memcpy(&msg.dst.sin6_addr, remote, sizeof(msg.dst.sin6_addr));

	msg.gtwy.sin6_len = sizeof(msg.gtwy);
	msg.gtwy.sin6_family = AF_INET6;
	memcpy(&msg.gtwy.sin6_addr, local, sizeof(msg.gtwy.sin6_addr));

	/* send message, ignore error when route already exists */
	if (0 > write(s, &msg, msg.hdr.rtm_msglen))
		{
		int errno_ = errno;

		debug("write to routing socket failed: %s", strerror(errno_));
		if (EEXIST != errno_)
			{
			err = kmDNSHelperRouteAdditionFailed;
			goto fin;
			}
		}

fin:
	if (0 <= s)
		close(s);
	return err;
	}

static int
teardownTunnelRoute(v6addr_t remote)
	{
	struct
		{
		struct rt_msghdr    hdr;
		struct sockaddr_in6 dst;
		} msg;
	int err = 0;
	int s = -1;

	if (0 > (s = socket(PF_ROUTE, SOCK_RAW, AF_INET)))
		{
		helplog(ASL_LEVEL_ERR, "socket(PF_ROUTE, ...) failed: %s",
		    strerror(errno));
		err = kmDNSHelperRoutingSocketCreationFailed;
		goto fin;
		}
	memset(&msg, 0, sizeof(msg));

	msg.hdr.rtm_msglen = sizeof(msg);
	msg.hdr.rtm_type = RTM_DELETE;
	msg.hdr.rtm_version = RTM_VERSION;
	msg.hdr.rtm_seq = routeSeq++;
	msg.hdr.rtm_addrs = RTA_DST;

	msg.dst.sin6_len = sizeof(msg.dst);
	msg.dst.sin6_family = AF_INET6;
	memcpy(&msg.dst.sin6_addr, remote, sizeof(msg.dst.sin6_addr));
	if (0 > write(s, &msg, msg.hdr.rtm_msglen))
		{
		int errno_ = errno;

		debug("write to routing socket failed: %s", strerror(errno_));
		if (ESRCH != errno_)
			{
			err = kmDNSHelperRouteDeletionFailed;
			goto fin;
			}
		}

fin:
	if (0 <= s)
		close(s);
	return err;
	}

static int
v4addr_to_string(v4addr_t addr, char *buf, size_t buflen)
	{
	if (NULL == inet_ntop(AF_INET, addr, buf, buflen))
		{
		helplog(ASL_LEVEL_ERR, "inet_ntop failed: %s",
		    strerror(errno));
		return kmDNSHelperInvalidNetworkAddress;
		}
	else
		return 0;
	}

static int
v6addr_to_string(v6addr_t addr, char *buf, size_t buflen)
	{
	if (NULL == inet_ntop(AF_INET6, addr, buf, buflen))
		{
		helplog(ASL_LEVEL_ERR, "inet_ntop failed: %s",
		    strerror(errno));
		return kmDNSHelperInvalidNetworkAddress;
		}
	else
		return 0;
	}

/* Caller owns object returned in `policy' */
static int
generateTunnelPolicy(mDNSTunnelPolicyWhich which, mDNSTunnelType type, int in,
		     v4addr_t src, uint16_t src_port,
		     v4addr_t dst, uint16_t dst_port,
			 v6addr_t src6, v6addr_t dst6,
		     ipsec_policy_t *policy, size_t *len)
	{
	char srcs[INET_ADDRSTRLEN], dsts[INET_ADDRSTRLEN];
	char srcs6[INET6_ADDRSTRLEN], dsts6[INET6_ADDRSTRLEN];
	char buf[512];
	char *inOut = in ? "in" : "out";
	ssize_t n = 0;
	int err = 0;

	*policy = NULL;
	*len = 0;

	switch (which)
	{
	case kmDNSTunnelPolicySetup:
		if (type == kmDNSIPv6IPv4Tunnel)
			{
			if (0 != (err = v4addr_to_string(src, srcs, sizeof(srcs))))
				goto fin;
			if (0 != (err = v4addr_to_string(dst, dsts, sizeof(dsts))))
				goto fin;
			n = snprintf(buf, sizeof(buf),
		    	"%s ipsec esp/tunnel/%s[%u]-%s[%u]/require",
		    	inOut, srcs, src_port, dsts, dst_port);
			}
		else if (type == kmDNSIPv6IPv6Tunnel)
			{
			if (0 != (err = v6addr_to_string(src6, srcs6, sizeof(srcs6))))
				goto fin;
			if (0 != (err = v6addr_to_string(dst6, dsts6, sizeof(dsts6))))
				goto fin;
			n = snprintf(buf, sizeof(buf),
		    	"%s ipsec esp/tunnel/%s-%s/require",
		    	inOut, srcs6, dsts6);
			}
		break;
	case kmDNSTunnelPolicyTeardown:
		n = strlcpy(buf, inOut, sizeof(buf));
		break;
	case kmDNSTunnelPolicyGenerate:
		n = snprintf(buf, sizeof(buf), "%s generate", inOut);
		break;
	default:
		err = kmDNSHelperIPsecPolicyCreationFailed;
		goto fin;
		}

	if (n >= (int)sizeof(buf))
		{
		err = kmDNSHelperResultTooLarge;
		goto fin;
		}

	debug("policy=\"%s\"", buf);
	if (NULL == (*policy = (ipsec_policy_t)ipsec_set_policy(buf, n)))
		{
		helplog(ASL_LEVEL_ERR,
		    "Could not create IPsec policy from \"%s\"", buf);
		err = kmDNSHelperIPsecPolicyCreationFailed;
		goto fin;
		}
	*len = ((ipsec_policy_t)(*policy))->sadb_x_policy_len * 8;

fin:
	return err;
	}

static int
sendPolicy(int s, int setup,
	   struct sockaddr *src, uint8_t src_bits,
	   struct sockaddr *dst, uint8_t dst_bits,
	   ipsec_policy_t policy, size_t len)
	{
	static unsigned int policySeq = 0;
	int err = 0;

	debug("entry, setup=%d", setup);
	if (setup)
		err = pfkey_send_spdadd(s, src, src_bits, dst, dst_bits, -1,
		    (char *)policy, len, policySeq++);
	else
		err = pfkey_send_spddelete(s, src, src_bits, dst, dst_bits, -1,
		    (char *)policy, len, policySeq++);
	if (0 > err)
		{
		helplog(ASL_LEVEL_ERR, "Could not set IPsec policy: %s",
		    ipsec_strerror());
		err = kmDNSHelperIPsecPolicySetFailed;
		goto fin;
		}
	else
		err = 0;
	debug("succeeded");

fin:
	return err;
	}

static int
removeSA(int s, struct sockaddr *src, struct sockaddr *dst)
	{
	int err = 0;

	debug("entry");
	err = pfkey_send_delete_all(s, SADB_SATYPE_ESP, IPSEC_MODE_ANY, src, dst);
	if (0 > err)
		{
		helplog(ASL_LEVEL_ERR, "Could not remove IPsec SA: %s", ipsec_strerror());
		err = kmDNSHelperIPsecRemoveSAFailed;
		goto fin;
		}
	err = pfkey_send_delete_all(s, SADB_SATYPE_ESP, IPSEC_MODE_ANY, dst, src);
	if (0 > err)
		{
		helplog(ASL_LEVEL_ERR, "Could not remove IPsec SA: %s", ipsec_strerror());
		err = kmDNSHelperIPsecRemoveSAFailed;
		goto fin;
		}
	else
	  err = 0;

	debug("succeeded");

fin:
	return err;
	}

static int
doTunnelPolicy(mDNSTunnelPolicyWhich which, mDNSTunnelType type,
	       v6addr_t loc_inner, uint8_t loc_bits,
	       v4addr_t loc_outer, uint16_t loc_port, 
	       v6addr_t rmt_inner, uint8_t rmt_bits,
	       v4addr_t rmt_outer, uint16_t rmt_port,
		   v6addr_t loc_outer6, v6addr_t rmt_outer6)
	{
	struct sockaddr_in6 sin6_loc;
	struct sockaddr_in6 sin6_rmt;
	ipsec_policy_t policy = NULL;
	size_t len = 0;
	int s = -1;
	int err = 0;

	debug("entry");
	if (0 > (s = pfkey_open()))
		{
		helplog(ASL_LEVEL_ERR,
		    "Could not create IPsec policy socket: %s",
		    ipsec_strerror());
		err = kmDNSHelperIPsecPolicySocketCreationFailed;
		goto fin;
		}

	memset(&sin6_loc, 0, sizeof(sin6_loc));
	sin6_loc.sin6_len = sizeof(sin6_loc);
	sin6_loc.sin6_family = AF_INET6;
	sin6_loc.sin6_port = htons(0);
	memcpy(&sin6_loc.sin6_addr, loc_inner, sizeof(sin6_loc.sin6_addr));

	memset(&sin6_rmt, 0, sizeof(sin6_rmt));
	sin6_rmt.sin6_len = sizeof(sin6_rmt);
	sin6_rmt.sin6_family = AF_INET6;
	sin6_rmt.sin6_port = htons(0);
	memcpy(&sin6_rmt.sin6_addr, rmt_inner, sizeof(sin6_rmt.sin6_addr));

	int setup = which != kmDNSTunnelPolicyTeardown;

	if (0 != (err = generateTunnelPolicy(which, type, 1,
	    rmt_outer, rmt_port,
	    loc_outer, loc_port,
		rmt_outer6, loc_outer6,
	    &policy, &len)))
		goto fin;
	if (0 != (err = sendPolicy(s, setup,
	    (struct sockaddr *)&sin6_rmt, rmt_bits,
	    (struct sockaddr *)&sin6_loc, loc_bits,
	    policy, len)))
		goto fin;
	if (NULL != policy)
		{
		free(policy);
		policy = NULL;
		}
	if (0 != (err = generateTunnelPolicy(which, type, 0,
	    loc_outer, loc_port,
	    rmt_outer, rmt_port,
		loc_outer6, rmt_outer6,
	    &policy, &len)))
		goto fin;
	if (0 != (err = sendPolicy(s, setup,
	    (struct sockaddr *)&sin6_loc, loc_bits,
	    (struct sockaddr *)&sin6_rmt, rmt_bits,
	    policy, len)))
		goto fin;

	if (which == kmDNSTunnelPolicyTeardown)
		{
		if (rmt_port)		// Outer tunnel is IPv4
			{
			if (loc_outer && rmt_outer)
				{
				struct sockaddr_in sin_loc;
				struct sockaddr_in sin_rmt;
				memset(&sin_loc, 0, sizeof(sin_loc));
				sin_loc.sin_len = sizeof(sin_loc);
				sin_loc.sin_family = AF_INET;
				memcpy(&sin_loc.sin_addr, loc_outer, sizeof(sin_loc.sin_addr));
		
				memset(&sin_rmt, 0, sizeof(sin_rmt));
				sin_rmt.sin_len = sizeof(sin_rmt);
				sin_rmt.sin_family = AF_INET;
				memcpy(&sin_rmt.sin_addr, rmt_outer, sizeof(sin_rmt.sin_addr));
				if (0 != (err = removeSA(s, (struct sockaddr *)&sin_loc, (struct sockaddr *)&sin_rmt)))
					goto fin;
				}
			}
		else
			{
			if (loc_outer6 && rmt_outer6)
				{
				struct sockaddr_in6 sin6_lo;
				struct sockaddr_in6 sin6_rm;

				memset(&sin6_lo, 0, sizeof(sin6_lo));
				sin6_lo.sin6_len = sizeof(sin6_lo);
				sin6_lo.sin6_family = AF_INET6;
				memcpy(&sin6_lo.sin6_addr, loc_outer6, sizeof(sin6_lo.sin6_addr));
		
				memset(&sin6_rm, 0, sizeof(sin6_rm));
				sin6_rm.sin6_len = sizeof(sin6_rm);
				sin6_rm.sin6_family = AF_INET6;
				memcpy(&sin6_rm.sin6_addr, rmt_outer6, sizeof(sin6_rm.sin6_addr));
				if (0 != (err = removeSA(s, (struct sockaddr *)&sin6_lo, (struct sockaddr *)&sin6_rm)))
					goto fin;
				}
			}
		}


	debug("succeeded");

fin:
	if (s >= 0)
		pfkey_close(s);
	if (NULL != policy)
		free(policy);
	return err;
	}

#endif /* ndef MDNS_NO_IPSEC */

int
do_mDNSAutoTunnelSetKeys(__unused mach_port_t port, int replacedelete,
    v6addr_t loc_inner, v6addr_t loc_outer6, uint16_t loc_port,
    v6addr_t rmt_inner, v6addr_t rmt_outer6, uint16_t rmt_port,
    const char *id, int *err, audit_token_t token)
	{
#ifndef MDNS_NO_IPSEC
	static const char config[] =
	  "%s"
	  "remote %s [%u] {\n"
	  "  disconnect_on_idle idle_timeout 600 idle_direction idle_outbound;\n"
	  "  exchange_mode aggressive;\n"
	  "  doi ipsec_doi;\n"
	  "  situation identity_only;\n"
	  "  verify_identifier off;\n"
	  "  generate_policy on;\n"
	  "  my_identifier user_fqdn \"%s\";\n"
	  "  shared_secret keychain \"%s\";\n"
	  "  nonce_size 16;\n"
	  "  lifetime time 15 min;\n"
	  "  initial_contact on;\n"
	  "  support_proxy on;\n"
	  "  nat_traversal force;\n"
	  "  proposal_check claim;\n"
	  "  proposal {\n"
	  "    encryption_algorithm aes;\n"
	  "    hash_algorithm sha1;\n"
	  "    authentication_method pre_shared_key;\n"
	  "    dh_group 2;\n"
	  "    lifetime time 15 min;\n"
	  "  }\n"
	  "}\n\n"
	  "sainfo address %s any address %s any {\n"
	  "  pfs_group 2;\n"
	  "  lifetime time 10 min;\n"
	  "  encryption_algorithm aes;\n"
	  "  authentication_algorithm hmac_sha1;\n"
	  "  compression_algorithm deflate;\n"
	  "}\n\n"
	  "sainfo address %s any address %s any {\n"
	  "  pfs_group 2;\n"
	  "  lifetime time 10 min;\n"
	  "  encryption_algorithm aes;\n"
	  "  authentication_algorithm hmac_sha1;\n"
	  "  compression_algorithm deflate;\n"
	  "}\n";
	char path[PATH_MAX] = "";
	char li[INET6_ADDRSTRLEN], lo[INET_ADDRSTRLEN], lo6[INET6_ADDRSTRLEN],
	    ri[INET6_ADDRSTRLEN], ro[INET_ADDRSTRLEN], ro6[INET6_ADDRSTRLEN];
	FILE *fp = NULL;
	int fd = -1;
	char tmp_path[PATH_MAX] = "";
	v4addr_t loc_outer, rmt_outer;

	debug("entry");
	*err = 0;
	if (!authorized(&token))
		{
		*err = kmDNSHelperNotAuthorized;
		goto fin;
		}
	switch ((enum mDNSAutoTunnelSetKeysReplaceDelete)replacedelete)
	{
	case kmDNSAutoTunnelSetKeysReplace:
	case kmDNSAutoTunnelSetKeysDelete:
		break;
	default:
		*err = kmDNSHelperInvalidTunnelSetKeysOperation;
		goto fin;
		}

	if (0 != (*err = v6addr_to_string(loc_inner, li, sizeof(li))))
		goto fin;
	if (0 != (*err = v6addr_to_string(rmt_inner, ri, sizeof(ri))))
		goto fin;

	debug("loc_inner=%s rmt_inner=%s", li, ri);
	if (!rmt_port)
		{
		loc_outer[0] = loc_outer[1] = loc_outer[2] = loc_outer[3] = 0;
		rmt_outer[0] = rmt_outer[1] = rmt_outer[2] = rmt_outer[3] = 0;

		if (0 != (*err = v6addr_to_string(loc_outer6, lo6, sizeof(lo6))))
			goto fin;
		if (0 != (*err = v6addr_to_string(rmt_outer6, ro6, sizeof(ro6))))
			goto fin;
		debug("IPv6 outer tunnel: loc_outer6=%s rmt_outer6=%s", lo6, ro6);
		if ((int)sizeof(path) <= snprintf(path, sizeof(path),
	    	"%s%s.conf", GetRacoonConfigDir(), ro6))
			{
			*err = kmDNSHelperResultTooLarge;
			goto fin;
			}
		}
	else
		{
		loc_outer[0] = loc_outer6[0];
		loc_outer[1] = loc_outer6[1];
		loc_outer[2] = loc_outer6[2];
		loc_outer[3] = loc_outer6[3];

		rmt_outer[0] = rmt_outer6[0];
		rmt_outer[1] = rmt_outer6[1];
		rmt_outer[2] = rmt_outer6[2];
		rmt_outer[3] = rmt_outer6[3];

		if (0 != (*err = v4addr_to_string(loc_outer, lo, sizeof(lo))))
			goto fin;
		if (0 != (*err = v4addr_to_string(rmt_outer, ro, sizeof(ro))))
			goto fin;
		debug("IPv4 outer tunnel: loc_outer=%s loc_port=%u rmt_outer=%s rmt_port=%u",
	    	lo, loc_port, ro, rmt_port);

		if ((int)sizeof(path) <= snprintf(path, sizeof(path),
	    	"%s%s.%u.conf", GetRacoonConfigDir(), ro,
	    	rmt_port))
			{
			*err = kmDNSHelperResultTooLarge;
			goto fin;
			}
		}



	if (kmDNSAutoTunnelSetKeysReplace == replacedelete)
		{
		if (0 > ensureExistenceOfRacoonConfigDir(GetRacoonConfigDir()))
			{
			*err = kmDNSHelperRacoonConfigCreationFailed;
			goto fin;
			}
		if ((int)sizeof(tmp_path) <=
		    snprintf(tmp_path, sizeof(tmp_path), "%s.XXXXXX", path))
			{
			*err = kmDNSHelperResultTooLarge;
			goto fin;
			}       
		if (0 > (fd = mkstemp(tmp_path)))
			{
			helplog(ASL_LEVEL_ERR, "mkstemp \"%s\" failed: %s",
			    tmp_path, strerror(errno));
			*err = kmDNSHelperRacoonConfigCreationFailed;
			goto fin;
			}
		if (NULL == (fp = fdopen(fd, "w")))
			{
			helplog(ASL_LEVEL_ERR, "fdopen: %s",
			    strerror(errno));
			*err = kmDNSHelperRacoonConfigCreationFailed;
			goto fin;
			}
		fd = -1;
		fprintf(fp, config, configHeader, (!rmt_port ? ro6 : ro), rmt_port, id, id, ri, li, li, ri);
		fclose(fp);
		fp = NULL;
		if (0 > rename(tmp_path, path))
			{
			helplog(ASL_LEVEL_ERR,
			    "rename \"%s\" \"%s\" failed: %s",
			    tmp_path, path, strerror(errno));
			*err = kmDNSHelperRacoonConfigCreationFailed;
			goto fin;
			}
		}
	else
		{
		if (0 != unlink(path))
			debug("unlink \"%s\" failed: %s", path,
			    strerror(errno));
		}

	if (0 != (*err = doTunnelPolicy(kmDNSTunnelPolicyTeardown, kmDNSNoTunnel,
	    loc_inner, kWholeV6Mask, loc_outer, loc_port,
	    rmt_inner, kWholeV6Mask, rmt_outer, rmt_port, loc_outer6, rmt_outer6)))
		goto fin;
	if (kmDNSAutoTunnelSetKeysReplace == replacedelete &&
	    0 != (*err = doTunnelPolicy(kmDNSTunnelPolicySetup, (!rmt_port ? kmDNSIPv6IPv6Tunnel : kmDNSIPv6IPv4Tunnel),
	        loc_inner, kWholeV6Mask, loc_outer, loc_port,
		rmt_inner, kWholeV6Mask, rmt_outer, rmt_port, loc_outer6, rmt_outer6)))
		goto fin;

	if (0 != (*err = teardownTunnelRoute(rmt_inner)))
		goto fin;
	if (kmDNSAutoTunnelSetKeysReplace == replacedelete &&
		0 != (*err = setupTunnelRoute(loc_inner, rmt_inner)))
		goto fin;

	if (kmDNSAutoTunnelSetKeysReplace == replacedelete &&
		0 != (*err = kickRacoon()))
		goto fin;

	debug("succeeded");

fin:
	if (NULL != fp)
		fclose(fp);
	if (0 <= fd)
		close(fd);
	unlink(tmp_path);
#else
	(void)replacedelete; (void)loc_inner; (void)loc_outer6; (void)loc_port; (void)rmt_inner;
	(void)rmt_outer6; (void)rmt_port; (void)id; (void)token;
	
	*err = kmDNSHelperIPsecDisabled;
#endif /* MDNS_NO_IPSEC */
	update_idle_timer();
	return KERN_SUCCESS;
	}

kern_return_t
do_mDNSSendWakeupPacket(__unused mach_port_t port, unsigned ifid, const char *eth_addr, const char *ip_addr, int iteration, audit_token_t token)
	{
	int bpf_fd, i, j;
	struct ifreq ifr;
	char ifname[IFNAMSIZ];
	char packet[512];
	char *ptr = packet;
	char bpf_device[12];
    struct ether_addr *ea;
	(void) ip_addr; // unused
	(void) iteration; // unused
	(void) token; // unused

	if (if_indextoname(ifid, ifname) == NULL)
		{
		helplog(ASL_LEVEL_ERR, "do_mDNSSendWakeupPacket invalid interface index %u", ifid);
		return errno;
		}

    ea = ether_aton(eth_addr);
	if (ea == NULL)
		{
		helplog(ASL_LEVEL_ERR, "do_mDNSSendWakeupPacket invalid ethernet address %s", eth_addr);
		return errno;
		}

	for (i = 0; i < 100; i++)
		{
        snprintf(bpf_device, sizeof(bpf_device), "/dev/bpf%d", i);
		bpf_fd = open(bpf_device, O_RDWR, 0);
		if (bpf_fd == -1)
			continue;
		else break;
		}

	if (bpf_fd == -1)
		{
		helplog(ASL_LEVEL_ERR, "do_mDNSSendWakeupPacket cannot find a bpf device");
		return ENXIO;
		}

	memset(&ifr, 0, sizeof(ifr));
	strlcpy(ifr.ifr_name, ifname, sizeof(ifr.ifr_name));

	if (ioctl(bpf_fd, BIOCSETIF, (char *)&ifr) < 0)
		{
		helplog(ASL_LEVEL_ERR, "do_mDNSSendWakeupPacket BIOCSETIF failed %s", strerror(errno));
		return errno;
		}

	// 0x00 Destination address
    for (i=0; i<6; i++) *ptr++ = ea->octet[i];

    // 0x06 Source address (Note: Since we don't currently set the BIOCSHDRCMPLT option, BPF will fill in the real interface address for us)
    for (i=0; i<6; i++) *ptr++ = 0;

    // 0x0C Ethertype (0x0842)
    *ptr++ = 0x08;
    *ptr++ = 0x42;

    // 0x0E Wakeup sync sequence
    for (i=0; i<6; i++) *ptr++ = 0xFF;

    // 0x14 Wakeup data
    for (j=0; j<16; j++) for (i=0; i<6; i++) *ptr++ = ea->octet[i];

    // 0x74 Password
    for (i=0; i<6; i++) *ptr++ = 0;

	if (write(bpf_fd, packet, ptr - packet) < 0)
		{
		helplog(ASL_LEVEL_ERR, "do_mDNSSendWakeupPacket write failed %s", strerror(errno));
		return errno;
		}
	helplog(ASL_LEVEL_INFO, "do_mDNSSendWakeupPacket sent unicast eth_addr %s, ip_addr %s", eth_addr, ip_addr);
	// Send a broadcast one to handle ethernet switches that don't flood forward packets with
	// unknown mac addresses.
	for (i=0; i<6; i++) packet[i] = 0xFF;
	if (write(bpf_fd, packet, ptr - packet) < 0)
		{
		helplog(ASL_LEVEL_ERR, "do_mDNSSendWakeupPacket write failed %s", strerror(errno));
		return errno;
		}
	helplog(ASL_LEVEL_INFO, "do_mDNSSendWakeupPacket sent broadcast eth_addr %s, ip_addr %s", eth_addr, ip_addr);
	close(bpf_fd);
	return KERN_SUCCESS;
	}

// Open the specified port for protocol in the P2P firewall.
kern_return_t
do_mDNSPacketFilterControl(__unused mach_port_t port, uint32_t command, const char * ifname, uint16_t servicePort, uint16_t protocol, audit_token_t token)
	{
	(void) token; // unused
	int	error;
	kern_return_t result = KERN_SUCCESS;

	helplog(ASL_LEVEL_INFO, "do_mDNSPacketFilterControl: command %d ifname %s, servicePort 0x%x, protocol %d", 
			command, ifname, servicePort, protocol);

	switch (command)
		{
		case PF_SET_RULES:
			error = P2PPacketFilterAddBonjourRuleSet(ifname, servicePort, protocol);
			if (error)
				{
				helplog(ASL_LEVEL_ERR, "P2PPacketFilterAddBonjourRuleSet failed %s", strerror(error));
				result = KERN_FAILURE;
				}
			break;

		case PF_CLEAR_RULES:
			error = P2PPacketFilterClearBonjourRules();
			if (error)
				{
				helplog(ASL_LEVEL_ERR, "P2PPacketFilterClearBonjourRules failed %s", strerror(error));
				result = KERN_FAILURE;
				}
			break;

		default:
			helplog(ASL_LEVEL_ERR, "do_mDNSPacketFilterControl: invalid command %d", command);
			result = KERN_INVALID_ARGUMENT;
			break;
		}

	return result;
	}

