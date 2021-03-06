/*
    Copyright (C) 2002-2005  Thomas Ries <tries@gmx.net>

    This file is part of Siproxd.
    
    Siproxd is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.
    
    Siproxd is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    
    You should have received a copy of the GNU General Public License
    along with Siproxd; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA 
*/
#include "config.h"

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <signal.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <net/if.h>
#include <sys/ioctl.h>

#ifdef _SOLARIS2
# include <sys/sockio.h>
#endif

#include <sys/types.h>
#include <pwd.h>

#include <osipparser2/osip_parser.h>

#include "siproxd.h"
#include "log.h"

/*added by xuezhongbo for ALG v2 2007.11.06:10:58*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/param.h>
#include <sys/ioctl.h>
#include <net/if_arp.h>
#include <net/if.h>
#include <sys/param.h>
/*end added*/

static char const ident[]="$Id: utils.c,v 1.41 2005/01/08 10:05:13 hb9xar Exp $";

/* configuration storage */
extern struct siproxd_config configuration;

extern int h_errno;


/*
 * resolve a hostname and return in_addr
 * handles its own little DNS cache.
 *
 * RETURNS
 *	STS_SUCCESS on success
 *	STS_FAILURE on failure
 */
int get_ip_by_host(char *hostname, struct in_addr *addr) {
   int i, j;
   time_t t;
   struct hostent *hostentry;
#if defined(HAVE_GETHOSTBYNAME_R)
   struct hostent result_buffer;
   char tmp[GETHOSTBYNAME_BUFLEN];
#endif
   int error;
   static struct {
      time_t timestamp;
      struct in_addr addr;
      char hostname[HOSTNAME_SIZE+1];
   } dns_cache[DNS_CACHE_SIZE];
   static int cache_initialized=0;

   if (hostname == NULL) {
      ERROR("get_ip_by_host: NULL hostname requested");
      return STS_FAILURE;
   }

   if (addr == NULL) {
      ERROR("get_ip_by_host: NULL in_addr passed");
      return STS_FAILURE;
   }

   /* first time: initialize DNS cache */
   if (cache_initialized == 0) {
      DEBUGC(DBCLASS_DNS, "initializing DNS cache (%i entries)", DNS_CACHE_SIZE);
      memset(dns_cache, 0, sizeof(dns_cache));
      cache_initialized=1;
   }

   time(&t);
   /* clean expired entries */
   for (i=0; i<DNS_CACHE_SIZE; i++) {
      if (dns_cache[i].hostname[0]=='\0') continue;
      if ( (dns_cache[i].timestamp+DNS_MAX_AGE) < t ) {
         DEBUGC(DBCLASS_DNS, "cleaning DNS cache (entry %i)", i);
         memset (&dns_cache[i], 0, sizeof(dns_cache[0]));
      }
   }

   /*
    * search requested entry in cache
    */
   for (i=0; i<DNS_CACHE_SIZE; i++) {
      if (dns_cache[i].hostname[0]=='\0') continue; /* empty */
      if (strcmp(hostname, dns_cache[i].hostname) == 0) { /* match */
         memcpy(addr, &dns_cache[i].addr, sizeof(struct in_addr));
         DEBUGC(DBCLASS_DNS, "DNS lookup - from cache: %s -> %s",
	        hostname, utils_inet_ntoa(*addr));
         return STS_SUCCESS;
      }
   }
   
   /* did not find it in cache, so I have to resolve it */

   /* need to deal with reentrant versions of gethostbyname_r()
    * as we may use threads... */
#if defined(HAVE_GETHOSTBYNAME_R)

   /* gethostbyname_r() with 3 arguments (e.g. osf/1) */
   #if defined(HAVE_FUNC_GETHOSTBYNAME_R_3)
   gethostbyname_r(hostname,		/* the FQDN */
		   &result_buffer,	/* the result buffer */ 
		   &hostentry
		   );
   if (hostentry == NULL) error = h_errno;

   /* gethostbyname_r() with 5 arguments (e.g. solaris, linux libc5) */
   #elif defined(HAVE_FUNC_GETHOSTBYNAME_R_5)
   hostentry = gethostbyname_r(hostname,        /* the FQDN */
			       &result_buffer,  /* the result buffer */
			       tmp,
			       GETHOSTBYNAME_BUFLEN,
			       &error);

   /* gethostbyname_r() with 6 arguments (e.g. linux glibc) */
   #elif defined(HAVE_FUNC_GETHOSTBYNAME_R_6)
   gethostbyname_r(hostname,        /* the FQDN */
		   &result_buffer,  /* the result buffer */
		   tmp,
		   GETHOSTBYNAME_BUFLEN,
		   &hostentry,
		   &error);
   #else
      #error "gethostbyname_r() with 3, 5 or 6 arguments supported only"
   #endif   
#elif defined(HAVE_GETHOSTBYNAME)
   hostentry=gethostbyname(hostname);
   if (hostentry == NULL) error = h_errno;
#else
   #error "need gethostbyname() or gethostbyname_r()"
#endif

   if (hostentry==NULL) {
      /*
       * Some errors just tell us that there was no IP resolvable.
       * From the manpage:
       *   HOST_NOT_FOUND
       *      The specified host is unknown.
       *   HOST_NOT_FOUND
       *      The specified host is unknown.
       *   NO_ADDRESS or NO_DATA
       *      The requested name is valid but does not have an IP
       *      address.
       */
      if ((error == HOST_NOT_FOUND) ||
          (error == NO_ADDRESS) ||
          (error == NO_DATA)) {
#ifdef HAVE_HSTRERROR
         DEBUGC(DBCLASS_DNS, "gethostbyname(%s) failed: h_errno=%i [%s]",
                hostname, h_errno, hstrerror(error));
#else
         DEBUGC(DBCLASS_DNS, "gethostbyname(%s) failed: h_errno=%i",
                hostname, error);
#endif
      } else {
#ifdef HAVE_HSTRERROR
         ERROR("gethostbyname(%s) failed: h_errno=%i [%s]",
               hostname, h_errno, hstrerror(h_errno));
#else
         ERROR("gethostbyname(%s) failed: h_errno=%i",hostname, h_errno);
#endif
      }
      return STS_FAILURE;
   }

   memcpy(addr, hostentry->h_addr, sizeof(struct in_addr));
   DEBUGC(DBCLASS_DNS, "DNS lookup - resolved: %s -> %s",
          hostname, utils_inet_ntoa(*addr));

   /*
    * find an empty slot in the cache
    */
   j=0;
   for (i=0; i<DNS_CACHE_SIZE; i++) {
      if (dns_cache[i].hostname[0]=='\0') break;
      if (dns_cache[i].timestamp < t) {
         /* remember oldest entry */
         t=dns_cache[i].timestamp;
	 j=i;
      }
   }
   /* if no empty slot found, take oldest one */
   if (i >= DNS_CACHE_SIZE) i=j;

   /*
    * store the result in the cache
    */
   DEBUGC(DBCLASS_DNS, "DNS lookup - store into cache, entry %i)", i);
   memset(&dns_cache[i], 0, sizeof(dns_cache[0]));
   strncpy(dns_cache[i].hostname, hostname, HOSTNAME_SIZE);
   time(&dns_cache[i].timestamp);
   memcpy(&dns_cache[i].addr, addr, sizeof(struct in_addr));

   return STS_SUCCESS;
}


/*
 * Secure enviroment:
 * If running as root, put myself into a chroot jail and
 * change UID/GID to user as requested in config file
 */
void secure_enviroment (void) {
   int sts;
   struct passwd *passwd=NULL;

   DEBUGC(DBCLASS_CONFIG,"running w/uid=%i, euid=%i, gid=%i, egid=%i",
          getuid(), geteuid(), getgid(), getegid());

   if ((getuid()==0) || (geteuid()==0)) {
      /*
       * preparation - after chrooting there will be NOTHING more around
       */
      if (configuration.user) passwd=getpwnam(configuration.user);

      /*
       * change root directory into chroot jail
       */
      if (configuration.chrootjail) {
         /* !!!
          * Before chrooting I must at least once trigger the resolver
          * as it loads some dynamic libraries. Once chrootet
          * these libraries will *not* be found and gethostbyname()
          * calls will simply fail (return NULL pointer and h_errno=0).
          * Also (at least for FreeBSD) syslog() needs to be called
          * before chroot()ing - this is done in main() by an INFO().
          * Took me a while to figure THIS one out
          */
         struct in_addr dummy;
         get_ip_by_host("localhost", &dummy);
         DEBUGC(DBCLASS_CONFIG,"chrooting to %s",
                configuration.chrootjail);
         sts = chroot(configuration.chrootjail);
	 if (sts != 0) DEBUGC(DBCLASS_CONFIG,"chroot(%s) failed: %s",
	                      configuration.chrootjail, strerror(errno));
         chdir("/");
      }

      /*
       * change user ID and group ID 
       */
      if (passwd) {
         DEBUGC(DBCLASS_CONFIG,"changing uid/gid to %s",
                configuration.user);
         sts = setgid(passwd->pw_gid);
         DEBUGC(DBCLASS_CONFIG,"changed gid to %i - %s",
	        passwd->pw_gid, (sts==0)?"Ok":"Failed");

         sts = setegid(passwd->pw_gid);
         DEBUGC(DBCLASS_CONFIG,"changed egid to %i - %s",
	        passwd->pw_gid, (sts==0)?"Ok":"Failed");

/* don't set the real user id - as we need to elevate privs
   when setting up an RTP masquerading tunnel */
/*&&& Actually this is no longer true (7-Jul-2004/xar) */
//         sts = setuid(passwd->pw_uid);
//         DEBUGC(DBCLASS_CONFIG,"changed uid to %i - %s",
//	        passwd->pw_uid, (sts==0)?"Ok":"Failed");

         sts = seteuid(passwd->pw_uid);
         DEBUGC(DBCLASS_CONFIG,"changed euid to %i - %s",
	        passwd->pw_uid, (sts==0)?"Ok":"Failed");
      }
   }
}


/*
 * get_ip_by_ifname:
 * fetches own IP address by its interface name
 *
 * STS_SUCCESS on returning a valid IP and interface is UP
 * STS_FAILURE if interface is DOWN or other problem
 */
int get_ip_by_ifname(char *ifname, struct in_addr *retaddr) {
   struct ifreq ifr;
   struct sockaddr_in *sin = (struct sockaddr_in *)&ifr.ifr_addr;
   int sockfd;
   int i, j;
   int ifflags, isup;
   time_t t;
   static struct {
      time_t timestamp;
      struct in_addr ifaddr;	/* IP */
      int isup;			/* interface is UP */
      char ifname[IFNAME_SIZE+1];
   } ifaddr_cache[IFADR_CACHE_SIZE];
   static int cache_initialized=0;

   if (ifname == NULL) {
      WARN("get_ip_by_ifname: got NULL ifname passed - please check config"
           "file ('if_inbound' and 'if_outbound')");
      return STS_FAILURE;
   }

   /* first time: initialize ifaddr cache */
   if (cache_initialized == 0) {
      DEBUGC(DBCLASS_DNS, "initializing ifaddr cache (%i entries)", 
             IFADR_CACHE_SIZE);
      memset(ifaddr_cache, 0, sizeof(ifaddr_cache));
      cache_initialized=1;
   }

   if (retaddr) memset(retaddr, 0, sizeof(struct in_addr));

/*del by xuezhongbo for not use cache on 20091008*/
#if 0
   time(&t);
   /* clean expired entries */
   for (i=0; i<IFADR_CACHE_SIZE; i++) {
      if (ifaddr_cache[i].ifname[0]=='\0') continue;
      if ( (ifaddr_cache[i].timestamp+IFADR_MAX_AGE) < t ) {
         DEBUGC(DBCLASS_DNS, "cleaning ifaddr cache (entry %i)", i);
         memset (&ifaddr_cache[i], 0, sizeof(ifaddr_cache[0]));
      }
   }

   /*
    * search requested entry in cache
    */
   for (i=0; i<IFADR_CACHE_SIZE; i++) {
      if (ifaddr_cache[i].ifname[0]=='\0') continue;
      if (strcmp(ifname, ifaddr_cache[i].ifname) == 0) { /* match */
         if (retaddr) memcpy(retaddr, &ifaddr_cache[i].ifaddr,
                             sizeof(struct in_addr));
         DEBUGC(DBCLASS_DNS, "ifaddr lookup - from cache: %s -> %s %s",
	        ifname, utils_inet_ntoa(ifaddr_cache[i].ifaddr),
                (ifaddr_cache[i].isup)? "UP":"DOWN");
         return (ifaddr_cache[i].isup)? STS_SUCCESS: STS_FAILURE;
      } /* if */
   } /* for i */
#endif
/*end del*/

   /* not found in cache, go and get it */
   memset(&ifr, 0, sizeof(ifr));

   if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
      ERROR("Error in socket: %s\n",strerror(errno));
      return STS_FAILURE;
   }

   strcpy(ifr.ifr_name, ifname);
   sin->sin_family = AF_INET;

   /* get interface flags */
   if(ioctl(sockfd, SIOCGIFFLAGS, &ifr) != 0) {
     /* ERROR("Error in ioctl SIOCGIFFLAGS: %s [%s]\n",
            strerror(errno), ifname);*/
      close(sockfd);
      return STS_FAILURE;
   } 
   ifflags=ifr.ifr_flags;

   /* get address */
   if(ioctl(sockfd, SIOCGIFADDR, &ifr) != 0) {
      /*ERROR("Error in ioctl SIOCGIFADDR: %s (interface %s)\n",
      strerror(errno), ifname);*/
      close(sockfd);
      return STS_FAILURE;
   } 

   if (ifflags & IFF_UP) isup=1;
   else isup=0;

#if 0
   DEBUGC(DBCLASS_DNS, "get_ip_by_ifname: if %s has IP:%s (flags=%x) %s",
          ifname, utils_inet_ntoa(sin->sin_addr), ifflags,
          (isup)? "UP":"DOWN");
#endif

/*del by xuezhongbo for not use cache on 20091008*/
#if 0
   /*
    *find an empty slot in the cache
    */
   j=0;
   for (i=0; i<IFADR_CACHE_SIZE; i++) {
      if (ifaddr_cache[i].ifname[0]=='\0') break;
      if (ifaddr_cache[i].timestamp < t) {
         /* remember oldest entry */
         t=ifaddr_cache[i].timestamp;
	 j=i;
      }
   }
   /* if no empty slot found, take oldest one */
   if (i >= IFADR_CACHE_SIZE) i=j;

   /*
    * store the result in the cache
    */
   DEBUGC(DBCLASS_DNS, "ifname lookup - store into cache, entry %i)", i);
   memset(&ifaddr_cache[i], 0, sizeof(ifaddr_cache[0]));
   strncpy(ifaddr_cache[i].ifname, ifname, IFNAME_SIZE);
   ifaddr_cache[i].timestamp=t;
   memcpy(&ifaddr_cache[i].ifaddr, &sin->sin_addr, sizeof(sin->sin_addr));
   ifaddr_cache[i].isup=isup;
#endif
/*end del*/

   if (retaddr) memcpy(retaddr, &sin->sin_addr, sizeof(sin->sin_addr));

   close(sockfd);
   return (isup)? STS_SUCCESS : STS_FAILURE;
}


/*
 * utils_inet_ntoa:
 * implements an inet_ntoa()
 *
 * Returns pointer to a static character string.
 */
char *utils_inet_ntoa(struct in_addr in) {
#if defined(HAVE_INET_NTOP)
   static char string[INET_ADDRSTRLEN];
   if ((inet_ntop(AF_INET, &in, string, INET_ADDRSTRLEN)) == NULL) {
      ERROR("inet_ntop() failed: %s\n",strerror(errno));
      string[0]='\0';
   }
   return string;
#elif defined(HAVE_INET_NTOA)
   return inet_ntoa(in);
#else
#error "need inet_ntop() or inet_ntoa()"
#endif
}

/*
 * utils_inet_aton:
 * implements an inet_aton()
 *
 * converts the string in *cp and stores it into inp
 * Returns != 0 on success
 */
int  utils_inet_aton(const char *cp, struct in_addr *inp) {
#if defined(HAVE_INET_PTON)
   return inet_pton (AF_INET, cp, inp);
#elif defined(HAVE_INET_ATON)
   return inet_aton(cp, inp);
#else
#error "need inet_pton() or inet_aton()"
#endif
}

void get_local_ip(char *ip, struct in_addr *local_ip) {
   /* Returns the local IP address used to reach ip. */
   int sock;
   struct in_addr addr;
   struct sockaddr_in local;
   struct sockaddr_in remote;
   int namelen;

   sock = socket(AF_INET, SOCK_DGRAM, 0);
   if (sock < 0) {
      perror("socket");
   }

   memset((char *) &remote, 0, sizeof(remote));
   remote.sin_family = AF_INET;
  

   if (INADDR_NONE == inet_addr(ip))
   {
       get_ip_by_host(ip, &addr);
	   remote.sin_addr.s_addr = addr.s_addr;
   }
   else
   remote.sin_addr.s_addr = inet_addr(ip);

   if (connect(sock, (struct sockaddr *) &remote, sizeof(remote))) {
      perror("connect");
   }

   namelen = sizeof(local);
   if (getsockname(sock, (struct sockaddr *) &local,
		   (socklen_t *) &namelen) < 0) {
      perror("getsockname");
   }

   if (close(sock)) {
      perror("close");
   }

   memcpy(local_ip, &local.sin_addr, sizeof(struct in_addr));
}

/*added by xuezhongbo for ALG v2 2007.11.06:10:51*/
/*
return -1 err
return >0 ok
*/
#if 0
int get_netmask_by_ip(char *netmask,struct in_addr* addr)
{
struct ifconf ifc;
struct ifreq buf[100];
int sock = 0;
int len = 0;
int interfacenum=0;


sock = socket(AF_INET,SOCK_DGRAM,0);
if(sock < 0) 
  return sock;

 len = sizeof(buf);
 ifc.ifc_len = len;
 ifc.ifc_buf = buf;
 if(ioctl(sock,SIOCGIFCONF,&ifc)<0) {
   if(errno!=EINVAL)
    printf("ioctl error\n");
   return -1;
 }else {
 if(ifc.ifc_len == len)
  {
  printf("buf is too short\n");
  return -1;
  }
 }

interfacenum = ifc.ifc_len / sizeof(struct ifreq);
while(interfacenum>0)
{
 interfacenum--;
 printf ("net device %s\n", buf[interfacenum].ifr_name);

 /*Get IP of the net card */
            if (!(ioctl (sock, SIOCGIFADDR, (char *) &buf[interfacenum])))
                {
                 puts ("IP address is:");
                 printf("%s\n",inet_ntoa(((struct sockaddr_in*)(&buf[interfacenum].ifr_addr))->sin_addr));
                 puts("");
                   //puts (buf[intrface].ifr_addr.sa_data);
                 if(memcmp(addr,((struct sockaddr_in*)(&buf[interfacenum].ifr_addr))->sin_addr,sizeof(struct in_addr))==0)
                 	{
                 	//get the netmask
                        if (!(ioctl (sock, SIOCGIFNETMASK, (char *) &buf[interfacenum])))              
                        	{
                        	 printf("get the mask %s\n",
					   inet_ntoa(((struct sockaddr_in*)(&buf[interfacenum].ifr_addr))->sin_addr));
				 return 1;
                        	}
				else
				{
				  printf("get netmask err\n");
				}
                 	}
                }
            else {
               char str[256];
               sprintf (str, "cpm: ioctl device %s", buf[interfacenum].ifr_name);
               perror (str);
               return -1;
		}
}
close(sock);
}
#else

/*added by xuezhongbo for ALG v2 2007.11.06:10:51*/
int get_netmask_by_addr(char *netmask,struct in_addr* addr)
{
struct ifconf ifc;
struct ifreq buf[100];
int sock = 0;
int len = 0;
int interfacenum=0;

sock = socket(AF_INET,SOCK_DGRAM,0);
if(sock < 0) 
  return sock;

if((netmask==NULL)||(addr==NULL))
	return -1;

 len = sizeof(buf);
 ifc.ifc_len = len;
 ifc.ifc_buf = (char *)buf;
 
 if(ioctl(sock,SIOCGIFCONF,&ifc)<0) {
   if(errno!=EINVAL)
    {
       ERROR("ioctl error\n");
       return -1;
   }
 }else {
 if(ifc.ifc_len == len)
  {
    ERROR("buf is too short\n");
    return -1;
  }
 }

interfacenum = ifc.ifc_len / sizeof(struct ifreq);
while(interfacenum>0)
{
 interfacenum--;
 DEBUGC(DBCLASS_BABBLE,"net device %s and the index %d\n", buf[interfacenum].ifr_name,if_nametoindex(buf[interfacenum].ifr_name));
 
 /*Get IP of the net card */
            if (!(ioctl (sock, SIOCGIFADDR, (char *) &buf[interfacenum])))
                {
                 DEBUGC(DBCLASS_BABBLE,"IP address is:");
                 DEBUGC(DBCLASS_BABBLE,"%s\n",inet_ntoa(((struct sockaddr_in*)(&buf[interfacenum].ifr_addr))->sin_addr));
                 puts("");
                   //puts (buf[intrface].ifr_addr.sa_data);
                 if(memcmp((char *)addr,(char *)(&(((struct sockaddr_in*)(&buf[interfacenum].ifr_addr))->sin_addr)),sizeof(struct in_addr))==0)
                 	{
                 	//get the netmask
                        if (!(ioctl (sock, SIOCGIFNETMASK, (char *) &buf[interfacenum])))              
                        	{
                        	 DEBUGC(DBCLASS_BABBLE,"get the mask %s\n",
					   inet_ntoa(((struct sockaddr_in*)(&buf[interfacenum].ifr_addr))->sin_addr));
				 return 1;
                        	}
				else
				{
				  ERROR("get netmask err\n");
				}
                 	}
                }
            else {
               char str[256];
               sprintf (str, "cpm: ioctl device %s", buf[interfacenum].ifr_name);
               perror (str);
               return -1;
		}
}
close(sock);
return 1;
}
#endif
/*end added*/

/*added by xuezhongbo for ALG v2 2007.11.07:8:58*/
int get_index_by_addr(int *index,struct in_addr* addr)
{
struct ifconf ifc;
struct ifreq buf[100];
int sock = 0;
int len = 0;
int interfacenum=0;

sock = socket(AF_INET,SOCK_DGRAM,0);
if(sock < 0) 
  return sock;

if((index==NULL)||(addr==NULL))
	return -1;

 len = sizeof(buf);
 ifc.ifc_len = len;
 ifc.ifc_buf = (char *)buf;
 
 if(ioctl(sock,SIOCGIFCONF,&ifc)<0) {
   if(errno!=EINVAL)
    {
       ERROR("ioctl error\n");
       return -1;
   }
 }else {
 if(ifc.ifc_len == len)
  {
    ERROR("buf is too short\n");
    return -1;
  }
 }

interfacenum = ifc.ifc_len / sizeof(struct ifreq);
while(interfacenum>0)
{
 interfacenum--;
 DEBUGC(DBCLASS_BABBLE,"net device %s and the index %d\n", buf[interfacenum].ifr_name,if_nametoindex(buf[interfacenum].ifr_name));
 
 /*Get IP of the net card */
            if (!(ioctl (sock, SIOCGIFADDR, (char *) &buf[interfacenum])))
                {
                 DEBUGC(DBCLASS_BABBLE,"IP address is:");
                 DEBUGC(DBCLASS_BABBLE,"%s\n",inet_ntoa(((struct sockaddr_in*)(&buf[interfacenum].ifr_addr))->sin_addr));
                 puts("");
                   //puts (buf[intrface].ifr_addr.sa_data);
                 if(memcmp((char *)addr,(char *)(&(((struct sockaddr_in*)(&buf[interfacenum].ifr_addr))->sin_addr)),sizeof(struct in_addr))==0)
                 	{
                 	  *index = if_nametoindex(buf[interfacenum].ifr_name);
                       return 1;
                 	}
                }
            else {
               char str[256];
               sprintf (str, "cpm: ioctl device %s", buf[interfacenum].ifr_name);
               perror (str);
               return -1;
		}
}
close(sock);
return 1;
}
/*end added*/

/*add by xuezhongbo for get ori dst on 20080322*/
int bcmsystem (char *command)
{
   int pid = 0, status = 0;

   /* printf("dnsprobe: %s\n",command); */
   if ( command == 0 )
      return 1;

   pid = vfork();
   if ( pid == -1 )
      return -1;

   if ( pid == 0 ) {
      char *argv[4];
      argv[0] = "sh";
      argv[1] = "-c";
      argv[2] = command;
      argv[3] = 0;
      execve("/bin/sh", argv, environ);
      exit(127);
   }

   /* wait for child process return */
   do {
      if ( waitpid(pid, &status, WUNTRACED) == -1 ) {
         if ( errno != EINTR )
            return -1;
      } else  {
         return status;
	}
   } while ( 1 );

   return status;
}
/*end add*/
