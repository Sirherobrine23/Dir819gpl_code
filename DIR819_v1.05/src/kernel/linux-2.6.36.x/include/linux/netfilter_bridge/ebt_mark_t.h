#ifndef __LINUX_BRIDGE_EBT_MARK_T_H
#define __LINUX_BRIDGE_EBT_MARK_T_H

/* The target member is reused for adding new actions, the
 * value of the real target is -1 to -NUM_STANDARD_TARGETS.
 * For backward compatibility, the 4 lsb (2 would be enough,
 * but let's play it safe) are kept to designate this target.
 * The remaining bits designate the action. By making the set
 * action 0xfffffff0, the result will look ok for older
 * versions. [September 2006] */
#define MARK_SET_VALUE (0xfffffff0)
#define MARK_OR_VALUE  (0xffffffe0)
#define MARK_AND_VALUE (0xffffffd0)
#define MARK_XOR_VALUE (0xffffffc0)

/***************************************
 Move from extensions/ebt_mark.c
***************************************/
#define MARK_TARGET  '1'
#define MARK_SETMARK '2'
#define MARK_ORMARK  '3'
#define MARK_ANDMARK '4'
#define MARK_XORMARK '5'

#define OPT_MARK_TARGET   0x01
#define OPT_MARK_SETMARK  0x02
#define OPT_MARK_ORMARK   0x04
#define OPT_MARK_ANDMARK  0x08
#define OPT_MARK_XORMARK  0x10
/* end */

struct ebt_mark_t_info {
	unsigned long mark;
    unsigned long mask; /* TBS_TAG: by laiyuahng 2012-05-21 Desc:add member for ebtable mark mask function */
	/* EBT_ACCEPT, EBT_DROP, EBT_CONTINUE or EBT_RETURN */
	int target;
};
#define EBT_MARK_TARGET "mark"

#endif
