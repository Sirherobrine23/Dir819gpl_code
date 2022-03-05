#ifndef _XT_EXTLOG_H_target
#define _XT_EXTLOG_H_target

enum {
	XT_TCP=1,
	XT_UDP=2,
	XT_TCP_UDP=4
};

struct extlog_target_info {
    char proto; //0:tcp, 1: udp, 2:tcp&udp
    char portrange[12]; //port range
};

#endif /*_IPT_MARK_H_target*/

