/*
    Copyright (C) 2002-2008  Thomas Ries <tries@gmx.net>

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

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>

#include <osipparser2/osip_parser.h>

#include "siproxd.h"
#include "log.h"

static char const ident[]="$Id: readconf.c,v 1.43 2008/02/02 17:10:58 hb9xar Exp $";

/* configuration storage */
extern struct siproxd_config configuration;

/* prototypes used locally only */
static int parse_config (FILE *configfile, cfgopts_t cfgopts[], char *filter);


/* try to open (whichever is found first):
 *	<name>
 *	$HOME/.<name>rc
 *	/etc/<name>.conf
 *	/usr/etc/<name>.conf
 *	/usr/local/etc/<name>.conf
 *
 *	cfgopts: control array for the parser. defined keywors and types
 *	filter:  passed to parse_config (read there for details)
 *
 * RETURNS
 *	STS_SUCCESS on success
 *	STS_FAILURE on error
 */
int read_config(char *name, int search, cfgopts_t cfgopts[], char *filter) {
   int sts;
   FILE *configfile=NULL;
   int i;
   char tmp[256];
   const char *completion[] = {
	"%s/.%src",		/* this one is special... (idx=0)*/
	SIPROXDCONFPATH "/%s.conf",
	"/etc/%s.conf",
	"/usr/etc/%s.conf",
	"/usr/local/etc/%s.conf",
	NULL };


   DEBUGC(DBCLASS_CONFIG,"trying to read config file");

   /* shall I search the config file myself ? */
   if (search != 0) {
      /* yup, try to find it */
      for (i=0; completion[i]!=NULL; i++) {
	 switch (i) {
	 case 0:
            sprintf(tmp,completion[i],getenv("HOME"),name);
	    break;
	 default:
            sprintf(tmp,completion[i],name);
	    break;
	 }
	 DEBUGC(DBCLASS_CONFIG,"... trying %s",tmp);
         configfile = fopen(tmp,"r");
	 if (configfile==NULL) continue;
	 break; /* got config file */
      }
   } else {
         /* don't search it, just try the one given file */
	 DEBUGC(DBCLASS_CONFIG,"... trying %s",name);
         configfile = fopen(name,"r");
   }

   /* config file not found or unable to open for read */
   if (configfile==NULL) {
      ERROR ("could not open config file: %s", strerror(errno));
      return STS_FAILURE;
   }

   sts = parse_config(configfile, cfgopts, filter);
   fclose(configfile);

   /*
    * Post-process configuration variables that have conditions that
    * must be met; warn if we have to adjust any.
    */
   if (configuration.rtp_port_low & 0x01) {
      /* rtp_port_low must be an even number... */
      configuration.rtp_port_low = (configuration.rtp_port_low + 1) & ~0x01;
      WARN("rtp_port_low should be an even number; it's been rounded up to %i",
	   configuration.rtp_port_low);
   }
   if (configuration.rtp_port_high & 0x01) {
      /* rtp_high_port should be either the top RTP port allowed, */
      /* or the top RTCP port allowed.  If the latter, then reset */
      /* to the former... Don't need a warning here.  It's okay.  */
      configuration.rtp_port_high = configuration.rtp_port_high & ~0x01;
      DEBUGC(DBCLASS_CONFIG, "rounded rtp_port_high down to %i",
	     configuration.rtp_port_high);
   }

   return sts;
}


/*
 * parse configuration file
 *
 * configfile            - file STREAM to open config file
 *
 * configoptions         - control structure for config parser
 *
 * filter = NULL         - no filtering done
 * filter = "plugin_xxx" - only consider keywords starting
 *                         with "plugin_xxx", skip the rest.
 *                         PLugins set this to load their scope
 *                         of config options
 * filter = ""           - read main configuration, skipp everything
 *                         starting with "plugin_" (hardwired).
 *
 * RETURNS
 *	STS_SUCCESS on success
 *	STS_FAILURE on error
 */
static int parse_config (FILE *configfile, cfgopts_t configoptions[],
                         char *filter) {
   char buff[1024];
   char *ptr;
   int i, k;
   int num;
   size_t len;
   char *tmpptr;
   char *eqsign;

   while (fgets(buff,sizeof(buff),configfile) != NULL) {
      /* life insurance */
      buff[sizeof(buff)-1]='\0';

      /* strip New line & CR if present */
      for (i=1; i<=2; i++) {
         if ((buff[strlen(buff)-i]=='\n') || (buff[strlen(buff)-i]=='\r')) {
            buff[strlen(buff)-i]='\0';
         }
      }

      /* strip emtpy lines */
      if (strlen(buff) == 0) continue;

      /* strip comments and line with only whitespaces */
      for (i=0;i<strlen(buff);i++) {
         if ((buff[i] == ' ') || (buff[i] == '\t')) continue;
         if (buff[i] =='#') i=strlen(buff);
         break;
      }
      if (i == strlen(buff)) continue;


      /* search for token separator '=' */
      eqsign = strchr(buff, '=');
      if (eqsign == NULL) {
         ERROR("Syntax error in config file [%s]", buff);
         continue;
      }


      /* keyword filtering: 
       * filter = NULL         - no filtering done
       * filter = "plugin_xxx" - only consider keywords starting
       *                         with "plugin_xxx", skip the rest.
       *                         PLugins set this to load their scope
       *                         of config options
       * filter = ""           - read main configuration, skipp everything
       *                         starting with "plugin_" (hardwired).
       */
      if (filter) {
         /* filter == "": skip all plugin config entries */
         if (filter[0] == '\0') {
            ptr=strstr(buff,"plugin_");
            if (ptr && (ptr < eqsign)) {
               DEBUGC(DBCLASS_CONFIG,"skipped: \"%s\"",buff);
               continue;
            }
         /* filter == "something": only consider "somethingxxxxx" */
         } else {
            ptr=strstr(buff, filter);
            if ((ptr==NULL) || (ptr > eqsign)) {
               DEBUGC(DBCLASS_CONFIG,"skipped: \"%s\"",buff);
               continue;
            }
         }
      } /* filter == NULL */

      DEBUGC(DBCLASS_CONFIG,"cfg line:\"%s\"",buff);

      /* scan for known keyword */
      for (k=0; configoptions[k].keyword != NULL; k++) {
         if ((ptr=strstr(buff, configoptions[k].keyword)) != NULL) {
            ptr += strlen(configoptions[k].keyword);
            DEBUGC(DBCLASS_CONFIG,"got keyword:\"%s\"",
	                          configoptions[k].keyword);

	    /* check for argument separated by '=' */
            if ((ptr=strchr(ptr,'=')) == NULL) {;
	       ERROR("argument missing to config parameter %s",
	             configoptions[k].keyword);
	       break;
            }
	    do {ptr++;} while (*ptr == ' '); /* skip spaces after '=' */
            
            DEBUGC(DBCLASS_CONFIG,"got argument:\"%s\"",ptr);

	    num=0;
	    if (strlen(ptr) <= 0) {
	       WARN("empty argument in config file, line:\"%s\"",buff);
	       break;
            }

            switch (configoptions[k].type) {

	    //
            // Integer4
            //
	    case TYP_INT4:
	         num=sscanf(ptr,"%i",(int*)configoptions[k].dest);
                 DEBUGC(DBCLASS_BABBLE,"INT4=%i",*(int*)configoptions[k].dest);
	      break;	    

	    //
	    // String
	    //
	    case TYP_STRING:
	         /* the %as within sscanf seems to be not too portable.
                  * it is supposed to allocate the memory
                  * num=sscanf(ptr,"%as",(char**)configoptions[k].dest);
                  */

		 /* figure out the amount of space we need */
	         len=strlen(ptr)+1; /* include terminating zero!*/
                 tmpptr=(char*)malloc(len);
                 memcpy(configoptions[k].dest, &tmpptr, sizeof(tmpptr));
	         num=sscanf(ptr,"%s",tmpptr);
                 DEBUGC(DBCLASS_BABBLE,"STRING=%s",
                         *(char**)configoptions[k].dest);
	      break;	    

	    //
	    // String array
	    //
	    case TYP_STRINGA:
            {
		 /* figure out the amount of space we need */
                 char **dst;
                 int used=((stringa_t*)(configoptions[k].dest))->used;
		 // do I hace space left?
                 if (used<=CFG_STRARR_SIZE){
	            len=strlen(ptr)+1; /* include terminating zero!*/
                    tmpptr=(char*)malloc(len);
		    dst=&((stringa_t*)(configoptions[k].dest))->
                         string[used];
                    memcpy(dst, &tmpptr, sizeof(tmpptr));
	            num=sscanf(ptr,"%s",tmpptr);
		    DEBUGC(DBCLASS_BABBLE,"STRINGA[%i]=%s", used, (char*) (
			   ((stringa_t*)(configoptions[k].dest))->string[used]) );
		    ((stringa_t*)(configoptions[k].dest))->used++;
                 } else {
		    ERROR("no more space left in config string array %s",
                          configoptions[k].keyword);
                 }
	      break;
            }

	    default:
	      break;
	    }
	    if (num == 0) {
	       ERROR("illegal format in config file, line:\"%s\"",buff);
	    }

            break;
	 }
      } // for configoptions

      /*
       * complain if we hit a unknown keyword
       */
       if (configoptions[k].keyword == NULL) {
	  //ERROR("unknown keyword in config file, line:\"%s\"",buff);
       }
   } // while
   return STS_SUCCESS;
}


int make_default_config(void){
   memset (&configuration, 0, sizeof(configuration));
   configuration.sip_listen_port=SIP_PORT;
   configuration.default_expires=DEFAULT_EXPIRES;
   configuration.rtp_input_dejitter=DEFAULT_DEJITTER;
   configuration.rtp_output_dejitter=DEFAULT_DEJITTER;

   return STS_SUCCESS;
}
