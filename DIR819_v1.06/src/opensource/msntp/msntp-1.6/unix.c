/*  Copyright (C) 1996 N.M. Maclaren
    Copyright (C) 1996 The University of Cambridge

This includes code that really should have been part of ANSI/ISO C, but was
left out for historical reasons (despite requests to define ftty), plus
the get_lock() and log_message() functions. */



#include "header.h"

#include <sys/types.h>
#include <unistd.h>
#include <syslog.h>

#define UNIX
#include "kludges.h"
#undef UNIX



void do_nothing (int seconds) {

/* Wait for a fixed period, possibly uninterruptibly.  This should not wait
for less than the specified period, if that can be avoided. */

    sleep((unsigned int)(seconds+2));          /* +2 is enough for POSIX */
}



int ftty (FILE *file) {

/* Return whether the file is attached to an interactive device. */

    return isatty(fileno(file));
}

#if defined(DISPLAY_MSG)||defined(SUPPORT_DAEMON_MODE)
/***************************************************************/
void set_lock (int lock) {

/* Check that we have enough privileges to reset the time and that no other
updating msntp process is running, but don't bother with fancy interlocking.
This function is really only to permit the daemon mode to be restarted in a
cron job and improve the diagnostics; it can be replaced by a 'return'
statement if it causes implementation difficulties.  Note that there is little
point in clearing the lock under Unix, but do so anyway. */

    FILE *file;
    long pid;

    if (lockname == NULL || lockname[0] == '\0') return;
    if (lock) {
        errno = 0;
        if ((file = fopen(lockname,"r")) != NULL &&
                fscanf(file,"%ld",&pid) == 1 && kill(pid,0) == 0) {
            if (verbose || isatty(STDIN_FILENO) || isatty(STDOUT_FILENO))
                fatal(0,"another msntp process is currently running",NULL);
            else
                fatal(0,NULL,NULL);
        }
        if (file != NULL) fclose(file);
        errno = 0;
        if ((file = fopen(lockname,"w")) == NULL ||
#ifdef DISPLAY_MSG       
             fprintf(file,"%ld\n",(long)getpid()) <= 0 ||
#endif
             ferror(file) || fclose(file) != 0)
            fatal(1,"unable to write PID to %s",lockname);
        adjust_time(0.0,1,0.0);
    } else {
        errno = 0;
        if (remove(lockname) != 0)
            fatal(1,"unable to remove the msntp lockname %s",lockname);
    }
}       
#endif

#ifdef _SUPPORT_DAEMON_MODE 
void log_message (const char *message) {

/* Log a message, crudely.  This is used in only one place, but could
be used more widely. */

    syslog(LOG_DAEMON|LOG_WARNING,"%s",message);
}
#endif
