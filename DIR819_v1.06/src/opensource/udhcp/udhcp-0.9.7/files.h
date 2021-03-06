/* files.h */
#ifndef _FILES_H
#define _FILES_H

#define MAX_INTERFACES	6
//#define MAX_KEYWORDS	(19 + MAX_CLIENT_CLS_COUNT * 4)
#define MAX_KEYWORDS	(21 + MAX_CLIENT_CLS_COUNT * 6)

struct config_keyword {
	char keyword[14];
	int (*handler)(char *line, void *var);
	void *var;
	char def[30];
};

struct config_kw_arr {
	struct config_keyword keywords[MAX_KEYWORDS];
};

int read_config(char *file);
void write_leases(int ifid);
void read_leases(char *file, int ifid);

int read_vendor_id_config(char *file);
#endif
