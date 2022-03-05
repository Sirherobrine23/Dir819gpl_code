/*
#####netspy_proc_module.c
*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>
#include <linux/socket.h>
#include <linux/in.h>
#include <linux/inet.h>

#include <linux/netspy_proc.h>


#define MODULE_VERSION__ "1.0"
#define MODULE_NAME "NETSPY IPPORT proc module"


static struct proc_dir_entry *netspy_file;
unsigned int ipport_tbl_index;
T_NETSPY_IPPORT_FCTL_p pNetSpy_data;
T_NETSPY_IPPORT_FCTL_ netspy_data;
unsigned short netspy_ipid_index;
////////////////////////////////////////////////////////////////////////////
//these enum for command parse

enum ParseState1 {
	PS_WHITESPACE,
	PS_TOKEN,
	PS_STRING,
	PS_ESCAPE
};

enum ParseState1 stackedState1;

/*
static int string_to_hex1(char *string, unsigned char *key, int len)
{
	char tmpBuf[4];
	int idx, ii=0;
	for (idx=0; idx<len; idx+=2) {
		tmpBuf[0] = string[idx];
		tmpBuf[1] = string[idx+1];
		tmpBuf[2] = 0;

		key[ii++] = (unsigned char) simple_strtol(tmpBuf, (char**)NULL, 16);
	}
	return 1;
}
*/

void parseargs1(char *argstr, int *argc_p, char **argv, char** resid)
{
	int argc = 0;
	char c;
	enum ParseState1 lastState = PS_WHITESPACE;

	/* tokenize the argstr */
	while ((c = *argstr) != 0) 
		{
		enum ParseState1 newState;

		if (c == ';' && lastState != PS_STRING && lastState != PS_ESCAPE)
			break;

		if (lastState == PS_ESCAPE) 
			{
			newState = stackedState1;
			} 
		else if (lastState == PS_STRING) 
			{
			if (c == '"') 
				{
				newState = PS_WHITESPACE;
				*argstr = 0;
				} 
			else 
				{
				newState = PS_STRING;
				}
			} 
		else if ((c == ' ') || (c == '\t')) 
			{
			/* whitespace character */
			*argstr = 0;
			newState = PS_WHITESPACE;
			} 
		else if (c == '"') 
			{
			newState = PS_STRING;
			*argstr++ = 0;
			argv[argc++] = argstr;
			} 
		else if (c == '\\') 
			{
			stackedState1 = lastState;
			newState = PS_ESCAPE;
			} 
		else 
			{
			/* token */
			if (lastState == PS_WHITESPACE) 
				{
				argv[argc++] = argstr;
				}
			newState = PS_TOKEN;
			}

		lastState = newState;
		argstr++;
		}


	argv[argc] = NULL;
	if (argc_p != NULL)
		*argc_p = argc;

	if (*argstr == ';') 
		{
		*argstr++ = '\0';
		}
	*resid = argstr;
}

#define ISDIGITAL(c) (c >= '0' && c <= '9')
__inline static int atoi( char *s) 
{
	int i=0;
	char *p=s;
	while (ISDIGITAL((*p)))
		{
		i = i*10 + *p - '0';
		p++;
		}
	return i;
}


static int proc_read_netspy_ipport(char *page, char **start, off_t off,
                                int count, int *eof, void *data)
{
	//int len;
	//T_IPPORT_FCTL_ENTRY *p_tmp_data;
	
	printk("IPPORT NETSPY information:is_Rule_Enable=%d\n",pNetSpy_data->is_Rule_Enable);


#if 0
	for (len=0;len<MAX_NETSPY_ENTRY;len++)
		{
		p_tmp_data=&pNetSpy_data->lan_ipport_entry_tbl[len];
		if (p_tmp_data->netspy_sip && p_tmp_data->netspy_sport)
			{
			    printk("id=%d: sip=%08x,sport=%08x,dip=%08x,dport=%08x,protocol=%08x,seqnum=%08x\n\r",
			    len,p_tmp_data->netspy_sip,
			    p_tmp_data->netspy_sport,p_tmp_data->netspy_dip,
			    p_tmp_data->netspy_dport,p_tmp_data->netspy_protocol,
			    p_tmp_data->netspy_seqnum);
			}
		}
			    
#endif
  	return 0;
}


static void reinit_netspy_ipport(void)
{
	//unsigned int  i;
	//T_IPPORT_FCTL_ENTRY *pData;
	ipport_tbl_index=0;
         /*
	for(i=0;i<MAX_NETSPY_ENTRY;i++)
	{
		pData=&(pNetSpy_data->lan_ipport_entry_tbl[i]);
		pData->netspy_sip=0;
		pData->netspy_sport=0;
		pData->netspy_dip=0;
		pData->netspy_dport=0;
		pData->netspy_protocol=0;
		pData->netspy_seqnum=0;
	}
	*/
	return;
}


static int proc_write_netspy_ipport(struct file *file, const char *buffer,
                                 unsigned long count, void *data)
{
	char buf[300];
	int argc,i=0;
	char *argv[128];
	char *resid;
	memset(argv,0,sizeof(argv));
	i=strlen(buffer);
	if (i>300)
		i=300;
	if (buffer && !copy_from_user(buf, buffer,i))
		{
		buf[299]=0;
		
		parseargs1(buf, &argc, argv, &resid);
#if 0//for test	
		printk("the count is %d\n\r",argc);
		printk("buffer=%s\n\r",buffer);
		while (argc--)
			{
			printk("argv[%d]=%s\n\r",argc+1,argv[argc]);
			}
#endif		
		if (!strcmp(argv[0],"wan"))
			{
            			if (argc<2) return count;
            			if (atoi(argv[1]))
            			{
            				pNetSpy_data->is_Rule_Enable=atoi(argv[1]);
            			}
            			else
            			{
            				pNetSpy_data->is_Rule_Enable=0;
            				return count;
            			}
            			reinit_netspy_ipport();
            			return count;
			}
		/*
		if (!strcmp(argv[0],"lan"))
			{
			unsigned int netspy_sip, netspy_sport;
			unsigned int netspy_dip,netspy_dport,netspy_protocol;
			T_IPPORT_FCTL_ENTRY *pData;
			if (argc<6) return count;
			netspy_sip=atoi(argv[1]); 
			netspy_sport=atoi(argv[2]); 
			netspy_dip=atoi(argv[3]);  	
			netspy_dport=atoi(argv[4]); 	
			netspy_protocol=atoi(argv[5]); 
			
			pData=&(pNetSpy_data->lan_ipport_entry_tbl[ipport_tbl_index]);
			    
			pData->netspy_sip=netspy_sip;
			pData->netspy_sport=netspy_sport;
			pData->netspy_dip=netspy_dip;
			pData->netspy_dport=netspy_dport;
			pData->netspy_protocol=netspy_protocol;
			
			ipport_tbl_index++;
			return count;
			}
        
		if (!strcmp(argv[0],"reset"))
			{
			reinit_netspy_ipport();
			}
			*/
		}
		return count;
}


static int __init init_netspy_ipport(void)
{

	pNetSpy_data = &netspy_data;
	/* Create the proc entry and make it readable and writeable by all - 0666 */
	printk("---->luotao ipport netspy test Driver.....-->\n");
	netspy_file = create_proc_entry("ipport_netspy", 0666, NULL);
  	if(netspy_file == NULL) {
		return -ENOMEM;
	}

/* set the default value of our data to Default. This way a read operation on
 * /proc/helloworld will return something. */
	memset(pNetSpy_data,0,sizeof(T_NETSPY_IPPORT_FCTL_));
	pNetSpy_data->is_Rule_Enable = 0;
	netspy_ipid_index=1;
	reinit_netspy_ipport();

  	netspy_file->data = pNetSpy_data;
  	netspy_file->read_proc = proc_read_netspy_ipport;
 	netspy_file->write_proc = proc_write_netspy_ipport;
  	//netspy_file->owner = THIS_MODULE;

  	printk(KERN_INFO "%s %s initialized\n",MODULE_NAME, MODULE_VERSION__);
  	return 0;
}

static void __exit cleanup_netspy_ipport(void)
{
  remove_proc_entry("ipport_netspy", NULL);

  printk(KERN_INFO "%s %s removed\n", MODULE_NAME, MODULE_VERSION__);
}


module_exit(cleanup_netspy_ipport);
module_init(init_netspy_ipport);

MODULE_AUTHOR("luotao");
MODULE_DESCRIPTION("netspy proc module");
MODULE_LICENSE("GPL");
