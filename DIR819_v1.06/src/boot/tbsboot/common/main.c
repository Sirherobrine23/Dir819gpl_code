/*
 * (C) Copyright 2000
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * Add to readline cmdline-editing by
 * (C) Copyright 2005
 * JinHua Luo, GuangDong Linux Center, <luo.jinhua@gd-linux.com>
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */


#include <common.h>
#include <command.h>
#include <net.h>
#include <tbs_common.h>
#ifdef CMD_TCP
#include <tcp.h>
#endif
/*add by huangshuangbang for entering bootloader while press reset button 20110827 start*/
#define RESET_CMD 
/*add by huangshuangbang for entering bootloader while press reset button 20110827 end*/

DECLARE_GLOBAL_DATA_PTR;

/*add by huangshuangbang for entering bootloader while press reset button 20110827 start*/
#ifdef RESET_CMD
extern int button_pressed(void);
#endif
/*add by huangshuangbang for entering bootloader while press reset button 20110827 end*/

#define MAX_DELAY_STOP_STR 32

extern void udelay (unsigned long usec);
extern char * strcpy(char * dest,const char *src);
extern size_t strlen(const char * s);
static int parse_line (char *, char *[]);
extern int flash_read_buf(flash_info_t * info, void* addr, unsigned char ** buf, int len);
extern int do_reset(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[]);
extern void tbs_calc_sum_addr(unsigned char *cp, unsigned long *res,unsigned int size);
#ifdef CONFIG_DOUBLE_BACKUP
extern int  sysdata_save(sys_config_t * syscfg);
#endif

char        console_buffer[CFG_CBSIZE];		/* console I/O buffer	*/

static char * delete_char (char *buffer, char *p, int *colp, int *np, int plen);
static char erase_seq[] = "\b \b";		/* erase sequence	*/
static char   tab_seq[] = "        ";		/* used to expand TABs	*/

int MoreUpdate = 0;

#define	endtick(seconds) (get_ticks() + (uint64_t)(seconds) * get_tbclk())

static __inline__ int abortboot(int bootdelay)
{
	int abort = 0;

/*add by huangshuangbang for entering bootloader while press reset button 20110827 start*/
	#ifdef RESET_CMD
		int reset_flg = 1;
	#endif
/*add by huangshuangbang for entering bootloader while press reset button 20110827 end*/

	printf("Hit Space or Enter key to stop autoboot: %2d ", bootdelay);
	//add by chenzanhui test
	//bootdelay = 0;
	//abort =1;
	while ((bootdelay > 0) && (!abort))
	{
		int i;

		--bootdelay;
		/* delay 100 * 10ms */
		for (i=0; !abort && i<100; ++i)
		{
			if (pause())
			{	/* we got Space or Enter key press	*/
				abort  = 1;	/* don't auto boot	*/
				bootdelay = 0;	/* no more delay	*/

				(void) getc();  /* consume input	*/

				break;
			}
			
			/*add by huangshuangbang for entering bootloader while press reset button 20110827 start*/
			#ifdef RESET_CMD	
			if(reset_flg && button_pressed())
			{
				if(i == 99)
				{
					abort  = 1;	
					bootdelay = 0;
				}
			} else {
				reset_flg = 0;	
			}
			#endif	
			/*add by huangshuangbang for entering bootloader while press reset button 20110827 end*/
			udelay (5000);
		}
		printf ("\b\b\b%2d ", bootdelay);
	}
	putc ('\n');

	return abort;
}


/****************************************************************************/

void main_loop (void)
{
        static char lastcommand[CFG_CBSIZE] = { 0, };

#ifdef CONFIG_BOOTDELAY
	int bootdelay = CONFIG_BOOTDELAY;
#else
	int bootdelay = 30;
#endif


#ifdef CONFIG_BOOTCOMMAND
	char s[] = { CONFIG_BOOTCOMMAND "\0" };
#else
	char s[] = "bootm";
#endif

	int len;
	int rc = 1;
	int flag;
	sys_config_t* syscfg;
	unsigned long crc_checksum;
	unsigned char *buf;

#ifdef IMAGE_CHECKSUM
	udp_send();
#endif

	buf = ( unsigned char * )CONFIG_LOADADDR;

	/*
	 *  Boot Command Processing
	 */

	if ( ( MoreUpdate == 0 ) && ( bootdelay >= 0 ) && s && !abortboot (bootdelay) )
	{
		/*image crc32 checksum*/
		syscfg =( sys_config_t * )SYSCFG_OFFSET;
		if(is_sysdata(syscfg))
		{
			printf("Checking image, please wait ...\n");
#ifdef CONFIG_DOUBLE_BACKUP
			if( syscfg->image_mark == 0 )
			{
				flash_read_buf( info , ( unsigned int * )( CFG_FLASH_BASE + syscfg->layout.zone_offset[ZONE_KERNEL_FIRST] ) , &buf , syscfg->first_image_len );
				tbs_calc_sum_addr( buf , &crc_checksum , syscfg->first_image_len );

				if( syscfg->first_image_checksum == crc_checksum )
				{
					printf("First image checksum validation successful. Now boot first image...\n");
				}
				else
				{
					printf("First image checksum validation wrong !\n");
					flash_read_buf( info , ( unsigned int * )( CFG_FLASH_BASE + syscfg->layout.zone_offset[ZONE_KERNEL_SECOND] ) , &buf , syscfg->second_image_len );
					tbs_calc_sum_addr( buf , &crc_checksum , syscfg->second_image_len );

					if( syscfg->second_image_checksum == crc_checksum )
					{
						printf("Second image checksum validation successful. Now boot second image...\n");
						syscfg->image_mark = 1;
						sysdata_save(syscfg);
						prepare_tags();
					}
					else
					{
						printf("Second image checksum validation wrong, too !\n");
						printf("Boot failed!\n");
						goto order_loop;
					}
				}
			}
			else if( syscfg->image_mark == 1 )
			{
				flash_read_buf( info , ( unsigned int * )( CFG_FLASH_BASE + syscfg->layout.zone_offset[ZONE_KERNEL_SECOND] ) , &buf, syscfg->second_image_len );
				tbs_calc_sum_addr( buf , &crc_checksum , syscfg->second_image_len );

				if( syscfg->second_image_checksum == crc_checksum )
				{
					printf("Second image checksum validation successful. Now boot second image...\n");
				}
				else
				{
					printf("Second image checksum validation wrong !\n");

					flash_read_buf( info , ( unsigned int * )( CFG_FLASH_BASE + syscfg->layout.zone_offset[ZONE_KERNEL_FIRST] ) , &buf , syscfg->first_image_len );
					tbs_calc_sum_addr( buf , &crc_checksum , syscfg->first_image_len);

					if( syscfg->first_image_checksum == crc_checksum )
					{
						printf("First image checksum validation successful. Now boot first image...\n");
						syscfg->image_mark = 0;
						sysdata_save(syscfg);
						prepare_tags();
					}
					else
					{
						printf("First image checksum validation wrong, too !\n");
						printf("Boot failed!\n");
						goto order_loop;
					}
				}
			}
#else

#ifdef IMAGE_CHECKSUM
				flash_read_buf( info , ( unsigned int * )( CFG_FLASH_BASE + syscfg->layout.zone_offset[ZONE_KERNEL_FIRST] ) , &buf , syscfg->first_image_len );
				tbs_calc_sum_addr( buf , &crc_checksum , syscfg->first_image_len );

				if( syscfg->first_image_checksum != crc_checksum )
				{
					printf("Checksum validation wrong!\n");
					printf("Boot failed!\n");
					goto order_loop;
				}
				else
				{
					printf("Checksum validation successful!\n");
				}
#endif

#endif
		}

		run_command (s, 0);
	}

	/*
	 * Main Loop for Monitor Command Processing
	 */

order_loop:

#ifdef CMD_TCP
#ifndef RT3052
	tbs_tcp();
#endif
#endif

	for (;;) {

		len = readline (CFG_PROMPT);
		flag = 0;	/* assume no special flags for now */
		if (len > 0)
			strcpy (lastcommand, console_buffer);
		else if (len == 0)
			flag |= CMD_FLAG_REPEAT;

		if (len == -1)
			puts ("<INTERRUPT>\n");
		else
			rc = run_command (lastcommand, flag);

		if (rc <= 0) {
			/* invalid command or not repeatable, forget it */
			lastcommand[0] = 0;
		}
	}

}

/****************************************************************************/

/*
 * Prompt for input and read a line.
 * If  CONFIG_BOOT_RETRY_TIME is defined and retry_time >= 0,
 * time out when time goes past endtime (timebase time in ticks).
 * Return:	number of read characters
 *		-1 if break
 *		-2 if timed out
 */
int readline (const char *const prompt)
{

	char   *p = console_buffer;
	int	n = 0;				/* buffer index		*/
	int	plen = 0;			/* prompt length	*/
	int	col;				/* output column cnt	*/
	char	c;

	/* print prompt */
	if (prompt) {
		plen = strlen (prompt);
		puts (prompt);
	}
	col = plen;

	for (;;) {
		c = getc();
		if( c == 0 )
		{
#ifdef CMD_TCP
			eth_rx();
#endif
			continue;
		}
		/*
		 * Special character handling
		 */
		switch (c) {
		case '\r':				/* Enter		*/
		case '\n':
			*p = '\0';
			puts ("\r\n");
			return (p - console_buffer);

		case '\0':				/* nul			*/
			continue;

		case 0x03:				/* ^C - break		*/
			console_buffer[0] = '\0';	/* discard input */
			return (-1);

		case 0x15:				/* ^U - erase line	*/
			while (col > plen) {
				puts (erase_seq);
				--col;
			}
			p = console_buffer;
			n = 0;
			continue;

		case 0x17:				/* ^W - erase word 	*/
			p=delete_char(console_buffer, p, &col, &n, plen);
			while ((n > 0) && (*p != ' ')) {
				p=delete_char(console_buffer, p, &col, &n, plen);
			}
			continue;

		case 0x08:				/* ^H  - backspace	*/
		case 0x7F:				/* DEL - backspace	*/
			p=delete_char(console_buffer, p, &col, &n, plen);
			continue;

		default:
			/*
			 * Must be a normal character then
			 */
			if (n < CFG_CBSIZE-2) {
				if (c == '\t') {	/* expand TABs		*/

					puts (tab_seq+(col&07));
					col += 8 - (col&07);
				} else {
					++col;		/* echo input		*/
					putc (c);
				}
				*p++ = c;
				++n;
			} else {			/* Buffer full		*/
				putc ('\a');
			}
		}
	}

}

/****************************************************************************/

#ifndef CONFIG_CMDLINE_EDITING
static char * delete_char (char *buffer, char *p, int *colp, int *np, int plen)
{
	char *s;

	if (*np == 0) {
		return (p);
	}

	if (*(--p) == '\t') {			/* will retype the whole line	*/
		while (*colp > plen) {
			puts (erase_seq);
			(*colp)--;
		}
		for (s=buffer; s<p; ++s) {
			if (*s == '\t') {
				puts (tab_seq+((*colp) & 07));
				*colp += 8 - ((*colp) & 07);
			} else {
				++(*colp);
				putc (*s);
			}
		}
	} else {
		puts (erase_seq);
		(*colp)--;
	}
	(*np)--;
	return (p);
}
#endif /* CONFIG_CMDLINE_EDITING */

/****************************************************************************/

int parse_line (char *line, char *argv[])
{
	int nargs = 0;

#ifdef DEBUG_PARSER
	printf ("parse_line: \"%s\"\n", line);
#endif
	while (nargs < CFG_MAXARGS) {

		/* skip any white space */
		while ((*line == ' ') || (*line == '\t')) {
			++line;
		}

		if (*line == '\0') {	/* end of line, no more args	*/
			argv[nargs] = NULL;
#ifdef DEBUG_PARSER
		printf ("parse_line: nargs=%d\n", nargs);
#endif
			return (nargs);
		}

		argv[nargs++] = line;	/* begin of argument string	*/

		/* find end of string */
		while (*line && (*line != ' ') && (*line != '\t')) {
			++line;
		}

		if (*line == '\0') {	/* end of line, no more args	*/
			argv[nargs] = NULL;
#ifdef DEBUG_PARSER
		printf ("parse_line: nargs=%d\n", nargs);
#endif
			return (nargs);
		}

		*line++ = '\0';		/* terminate current arg	 */
	}

	printf ("** Too many args (max. %d) **\n", CFG_MAXARGS);

#ifdef DEBUG_PARSER
	printf ("parse_line: nargs=%d\n", nargs);
#endif
	return (nargs);
}

/****************************************************************************/

static void process_macros (const char *input, char *output)
{
	char c, prev;
	const char *varname_start = NULL;
	int inputcnt = strlen (input);
	int outputcnt = CFG_CBSIZE;
	int state = 0;		/* 0 = waiting for '$'  */

	/* 1 = waiting for '(' or '{' */
	/* 2 = waiting for ')' or '}' */
	/* 3 = waiting for '''  */

	prev = '\0';		/* previous character   */

	while (inputcnt && outputcnt) {
		c = *input++;
		inputcnt--;

		if (state != 3) {
			/* remove one level of escape characters */
			if ((c == '\\') && (prev != '\\')) {
				if (inputcnt-- == 0)
					break;
				prev = c;
				c = *input++;
			}
		}

		switch (state) {
		case 0:	/* Waiting for (unescaped) $    */
			if ((c == '\'') && (prev != '\\')) {
				state = 3;
				break;
			}
			if ((c == '$') && (prev != '\\')) {
				state++;
			} else {
				*(output++) = c;
				outputcnt--;
			}
			break;
		case 1:	/* Waiting for (        */
			if (c == '(' || c == '{') {
				state++;
				varname_start = input;
			} else {
				state = 0;
				*(output++) = '$';
				outputcnt--;

				if (outputcnt) {
					*(output++) = c;
					outputcnt--;
				}
			}
			break;
		case 2:	/* Waiting for )        */
			if (c == ')' || c == '}') {
				int i;
				char envname[CFG_CBSIZE], *envval;
				int envcnt = input - varname_start - 1;	/* Varname # of chars */

				/* Get the varname */
				for (i = 0; i < envcnt; i++) {
					envname[i] = varname_start[i];
				}
				envname[i] = 0;

				/* Get its value */
				envval ="";// getenv (envname);

				/* Copy into the line if it exists */
				if (envval != NULL)
					while ((*envval) && outputcnt) {
						*(output++) = *(envval++);
						outputcnt--;
					}
				/* Look for another '$' */
				state = 0;
			}
			break;
		case 3:	/* Waiting for '        */
			if ((c == '\'') && (prev != '\\')) {
				state = 0;
			} else {
				*(output++) = c;
				outputcnt--;
			}
			break;
		}
		prev = c;
	}

	if (outputcnt)
		*output = 0;

}

/****************************************************************************
 * returns:
 *	1  - command executed, repeatable
 *	0  - command executed but not repeatable, interrupted commands are
 *	     always considered not repeatable
 *	-1 - not executed (unrecognized, bootd recursion or too many args)
 *           (If cmd is NULL or "" or longer than CFG_CBSIZE-1 it is
 *           considered unrecognized)
 *
 * WARNING:
 *
 * We must create a temporary copy of the command since the command we get
 * may be the result from getenv(), which returns a pointer directly to
 * the environment data, which may change magicly when the command we run
 * creates or modifies environment variables (like "bootp" does).
 */

int run_command (const char *cmd, int flag)
{
	cmd_tbl_t *cmdtp;
	char cmdbuf[CFG_CBSIZE];	/* working copy of cmd		*/
	char *token;			/* start of token in cmdbuf	*/
	char *sep;			/* end of token (separator) in cmdbuf */
	char finaltoken[CFG_CBSIZE];
	char *str = cmdbuf;
	char *argv[CFG_MAXARGS + 1];	/* NULL terminated	*/
	int argc, inquotes;
	int repeatable = 1;
	int rc = 0;


	clear_ctrlc();		/* forget any previous Control C */

	if (!cmd || !*cmd) {
		return -1;	/* empty command */
	}

	if (strlen(cmd) >= CFG_CBSIZE) {
		puts ("## Command too long!\n");
		return -1;
	}

	strcpy (cmdbuf, cmd);

	/* Process separators and check for invalid
	 * repeatable commands
	 */

	while (*str) {

		/*
		 * Find separator, or string end
		 * Allow simple escape of ';' by writing "\;"
		 */
		for (inquotes = 0, sep = str; *sep; sep++) {
			if ((*sep=='\'') &&
			    (*(sep-1) != '\\'))
				inquotes=!inquotes;

			if (!inquotes &&
			    (*sep == ';') &&	/* separator		*/
			    ( sep != str) &&	/* past string start	*/
			    (*(sep-1) != '\\'))	/* and NOT escaped	*/
				break;
		}

		/*
		 * Limit the token to data between separators
		 */
		token = str;
		if (*sep) {
			str = sep + 1;	/* start of command for next pass */
			*sep = '\0';
		}
		else
			str = sep;	/* no more commands for next pass */


		/* find macros in this token and replace them */
		process_macros (token, finaltoken);

		/* Extract arguments */
		if ((argc = parse_line (finaltoken, argv)) == 0) {
			rc = -1;	/* no command at all */
			continue;
		}

		/* Look up command in command table */
		if ((cmdtp = find_cmd(argv[0])) == NULL) {
			printf ("Unknown command '%s' - try 'help'\n", argv[0]);
			rc = -1;	/* give up after bad command */
			continue;
		}

		/* found - check max args */
		if (argc > cmdtp->maxargs) {
			printf ("Usage:\n%s\n", cmdtp->usage);
			rc = -1;
			continue;
		}


		/* OK - call function to do the command */
		if ((cmdtp->cmd) (cmdtp, flag, argc, argv) != 0) {
			rc = -1;
		}

		repeatable &= cmdtp->repeatable;

		/* Did the user stop this? */
		if (had_ctrlc ())
			return 0;	/* if stopped then not repeatable */
	}

	return rc ? rc : repeatable;
}


