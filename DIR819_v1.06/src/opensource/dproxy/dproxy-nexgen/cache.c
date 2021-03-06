/*
  **
  ** cache.c - cache handling routines
  **
  ** Part of the dproxy package by Matthew Pratt. 
  **
  ** Copyright 1999 Matthew Pratt <mattpratt@yahoo.com>
  **
  ** This software is licensed under the terms of the GNU General 
  ** Public License (GPL). Please see the file COPYING for details.
  ** 
  **
*/
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/file.h>
#include <ctype.h>
#include <unistd.h>

#include "cache.h"
#include "new_conf.h"

/** function prototypes for private functions*/
static int cache_byname(FILE * , char *, char *);

/*****************************************************************************
 *  search for a host by its name.
 *  
 *    This function first searches the cache for an entry. If the entry 
 *    was not found there, we will look into a dhcp "leases" file.
 * 
 *  @arg name  - name to find.
 *  @arg ip    - pointer to a buffer where to put the ip adress.
 *  
 *  @return 0 if an entry was found, 1 if not.
*****************************************************************************/
int cache_lookup_name(char *name, char ip[BUF_SIZE], char* configfile)
{
	FILE * fp;

	debug( "cache_lookup_name(%s)\n", name);

	/** check the cache */
	if( (fp = fopen(configfile, "r")) != NULL) {
		int result = 0;
		result = cache_byname(fp,name, ip); 
		fclose(fp);   
		if( result > 0 ) {
			return 1;
		}
	}

	return 0;
}
/*****************************************************************************
 * lookup a hostname in the cache file.
 *
 * This function will not lock the cache ! 
 * 
 *  @arg fp    - open file pointer for the cache file.
 *  @arg name  - name to find.
 *  @arg ip    - pointer to a buffer where to put the ip adress.
 *  
 *  @return 0 if an entry was found, 1 if not.
 *****************************************************************************/
static int cache_byname(FILE * fp, char *name, char ip[BUF_SIZE])
{

  char line[BUF_SIZE];
  char *token;
  int i = 0;

  ip[0] = 0;

  /** make shure we are at the start of the cache */
  rewind(fp);

  while( fgets(line, BUF_SIZE, fp) ){
	 token = strtok( line, " ");
	 if( !strcasecmp( token, name) ){
		token = strtok( NULL, " ");
		while( (isalnum(*token) || (*token=='.')) && (i<BUF_SIZE-1) ) ip[i++] = *token++;
		ip[i] = 0;
		return 1;
	 }
  }
 
  return 0;
}

/*****************************************************************************/
int cache_lookup_ip(char *ip, char result[BUF_SIZE], char* configfile)
{
  FILE *fp;
  char line[BUF_SIZE];
  char *token;
  int i = 0;

  if( ip[0] == 0 )return 0;
  result[0] = 0;
  
	fp = fopen(configfile, "r");
  if(!fp)return 0;
  while( fgets(line, BUF_SIZE, fp) ){
	 strtok( line, " ");
	 token = strtok( NULL, " ");
	 if( !strncasecmp( token, ip, strlen(ip) ) ){
		while( isalnum(line[i]) || (line[i]=='.') )
			{
				result[i] = line[i];
				++i;
			}
		result[i] = 0;
		fclose(fp);
		return 1;
	 }
  }
  fclose(fp);
  
  return 0;
}
/*****************************************************************************
* save the name to the list.
* 
*
*****************************************************************************/
void cache_name_append(char *name, char *ip, char* configfile)
{

  FILE *fp;
  char dummy[BUF_SIZE];

	fp = fopen(configfile, "a");
  if(!fp){
	 debug("Could not open cache file '%s' for writing\n",
				configfile);
	 return;
  }

  /** check if another process already added this host to the cache */
  if( cache_byname(fp, name, dummy) != 0 ) {
	  fclose(fp);
	  return;
  }

  /** make shure that we at the end of the file. */
  fseek(fp,0,SEEK_END);

  /** write new entry */
  fprintf( fp, "%s %s %ld\n", name, ip, time(NULL) );

  fclose(fp);
}
/*****************************************************************************/
void cache_purge(int older_than)
{
    FILE *in_fp, *out_fp,*fp_default;
    char line[BUF_SIZE];
    char old_cache[1024];
    char *name, *ip, *time_made;
    ST_LAN_INFO *pLanInfo;

    if(g_stConfig.pLanInfo != NULL)
    {
        for (pLanInfo = g_stConfig.pLanInfo; pLanInfo; pLanInfo = pLanInfo->pNext)
        {
            in_fp = fopen(pLanInfo->szCacheFile, "r");
            if(!in_fp)
            {
                debug_perror("Could not open old cache file\n");
                /*return;*/
            }

            if( in_fp )
            {
                sprintf( old_cache, "%s.old", pLanInfo->szCacheFile );	
                if( rename(pLanInfo->szCacheFile, old_cache ) < 0 )
                {
                    debug_perror("Could not move cache file\n");
                    fclose(in_fp);
                    return;
                }
            }

            out_fp = fopen(pLanInfo->szCacheFile , "w");	
            if(!out_fp)
            {
                if( in_fp )
                {
                    fclose(in_fp);
                }
                debug_perror("Could not open new cache file\n");
                return;
            }

            cache_add_hosts_entries(out_fp);
            if( in_fp )
            {
                while( fgets(line, BUF_SIZE, in_fp) )
                {
                    name = strtok( line, " ");
                    ip = strtok( NULL, " ");
                    time_made = strtok( NULL, " ");
	
                    if(!time_made)
                        continue;
                    if( time(NULL) - atoi( time_made ) < older_than )
                        fprintf( out_fp, "%s %s %s", name, ip, time_made );
                }
                fclose(in_fp);	
                unlink(old_cache);
            }
            fclose(out_fp);
    	}
	}

    if( (fp_default = fopen(DEFAULT_CACHE_FILE, "r")) != NULL)
    {
        sprintf( old_cache, "%s.old", DEFAULT_CACHE_FILE);
        if( rename( DEFAULT_CACHE_FILE, old_cache ) < 0 )
        {
            debug_perror("Could not move cache file");
            fclose(fp_default);
            return;
        }

        out_fp = fopen( DEFAULT_CACHE_FILE , "w");
        if(!out_fp)
        {
            if( fp_default )
            {
                fclose(fp_default);
            }
            debug_perror("Could not open new cache file");
            return;
        }

        cache_add_hosts_entries(out_fp);

        if( fp_default )
        {
            while( fgets(line, BUF_SIZE, fp_default) )
            {
                name = strtok( line, " ");
                ip = strtok( NULL, " ");
                time_made = strtok( NULL, " ");
                if(!time_made)
                    continue;

		  if( time(NULL) - atoi( time_made ) < older_than )
                    fprintf( out_fp, "%s %s %s", name, ip, time_made );
						  
            }

            fclose(fp_default);
            unlink(old_cache);
        }

        fclose(out_fp);
    }
}

/*****************************************************************************/
void cache_add_hosts_entries(FILE *cache_file)
{
  FILE *hosts_fp;
  char line[BUF_SIZE];
  char *ip, *name;

	hosts_fp = fopen(g_stConfig.szHostFile, "r");

	if( !hosts_fp ) {
		debug_perror("can not open 'hosts'-file \n");
		return;
	}

  while( fgets(line, BUF_SIZE, hosts_fp) ){
	 line[strlen(line) - 1] = 0; /* get rid of '\n' */
	 ip = strtok( line, " \t");
	 if( ip == NULL ) continue;  /* ignore blank lines */
	 if( ip[0] == '#' )continue; /* ignore comments */
	 while( (name = strtok( NULL, " \t" )) ){
	   if(name[0] == '#')break;
		fprintf( cache_file, "%s %s %ld\n", name, ip, 0L );
	 }
	 
  }
  fclose(hosts_fp);
}



