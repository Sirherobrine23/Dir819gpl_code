/* -- updatedd: updatedd.h --
 *
 * Copyright (C) 2002, 2003, 2004 Philipp Benner
 *
 * This file is part of UpdateDD - http://updatedd.philipp-benner.de.
 *
 * UpdateDD is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * any later version.
 *
 * UpdateDD is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with UpdateDD; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
#ifndef UPDATEDD_H
#define UPDATEDD_H

#define BUFSIZE		256

#define LIB_MAIN	"_dyndns"
#define LIB_GETRETMSG	"_get_retmsg"

typedef int	(*lib_main)	(int, char**);
typedef char *	(*lib_getretmsg)(void);


/* Logging Levels for the module. */
#define	DDNS_FATAL								0
#define DDNS_DEBUG								10

extern void logMsg (int level,char* fmt,...);

#endif
