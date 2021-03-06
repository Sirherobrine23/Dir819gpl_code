/* $Id: ipfwrdr.h,v 1.3 2011/02/20 23:43:41 nanard Exp $ */
/*
 * MiniUPnP project
 * http://miniupnp.free.fr/ or http://miniupnp.tuxfamily.org/
 * (c) 2009 Jardel Weyrich 
 * This software is subject to the conditions detailed
 * in the LICENCE file provided within the distribution
 */

#ifndef __IPFWRDR_H__
#define __IPFWRDR_H__

#include "../commonrdr.h"

int add_redirect_rule2(
	const char * ifname,	// src interface (external)
	unsigned short eport,	// src port (external)
	const char * iaddr,		// dst address (internal)
	unsigned short iport,	// dst port (internal)
	int proto,
	const char * desc);

int add_filter_rule2(
	const char * ifname, 
	const char * iaddr,
	unsigned short eport, 
	unsigned short iport,
	int proto, 
	const char * desc);

#if 0

//
// get_redirect_rule() gets internal IP and port from
// interface, external port and protocl
//
int get_redirect_rule(
	const char * ifname,
	unsigned short eport,
	int proto,
	char * iaddr, 
	int iaddrlen, 
	unsigned short * iport,
	char * desc, 
	int desclen,
	u_int64_t * packets,
	u_int64_t * bytes);

int get_redirect_rule_by_index(
	int index,
	char * ifname, 
	unsigned short * eport,
	char * iaddr, 
	int iaddrlen, 
	unsigned short * iport,
	int * proto, 
	char * desc, 
	int desclen,
	u_int64_t * packets, 
	u_int64_t * bytes);

#endif

//
// delete_redirect_rule()
//
int delete_redirect_rule(const char * ifname, unsigned short eport, int proto);

//
// delete_filter_rule()
//
int delete_filter_rule(const char * ifname, unsigned short eport, int proto);

int clear_redirect_rules(void);

#endif
