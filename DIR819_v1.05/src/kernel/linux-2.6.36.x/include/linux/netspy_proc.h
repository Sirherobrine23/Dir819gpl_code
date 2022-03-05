
//#define MAX_NETSPY_ENTRY 1024
//#define MAX_NETSPY_ENTRY 10240
/*
typedef struct netspy_fctl_ipport_entry
{
       unsigned int netspy_sip;
	unsigned int netspy_sport;
	unsigned int netspy_dip;
	unsigned int netspy_dport;
	unsigned int netspy_protocol;
	unsigned int netspy_seqnum;
}T_IPPORT_FCTL_ENTRY;
*/
//netspy ctrol struct
typedef struct netspy_ipport_fctl_
{
	unsigned short is_Rule_Enable;
	//T_IPPORT_FCTL_ENTRY lan_ipport_entry_tbl[MAX_NETSPY_ENTRY];
}T_NETSPY_IPPORT_FCTL_, *T_NETSPY_IPPORT_FCTL_p;
