#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include <libnetfilter_conntrack/libnetfilter_conntrack.h>
#ifdef TBS_FLUSH_CONNTRACK_OTHER

static int cb(enum nf_conntrack_msg_type type,
	      struct nf_expect *exp,
	      void *data)
{
	char buf[1024];

	nfexp_snprintf(buf, 1024, exp, NFCT_T_UNKNOWN, NFCT_O_DEFAULT, 0);
	printf("%s\n", buf);

	return NFCT_CB_CONTINUE;
}
#endif
int main()
{
    #ifdef TBS_FLUSH_CONNTRACK_OTHER

	int ret;
	struct nfct_handle *h;
	struct nf_conntrack *master;
	struct nf_expect *exp;

	master = nfct_new();
	if (!master) {
		perror("nfct_new");
		exit(EXIT_FAILURE);
	}

	nfct_set_attr_u8(master, ATTR_L3PROTO, AF_INET);
	nfct_set_attr_u32(master, ATTR_IPV4_SRC, inet_addr("4.4.4.4"));
	nfct_set_attr_u32(master, ATTR_IPV4_DST, inet_addr("5.5.5.5"));

	nfct_set_attr_u8(master, ATTR_L4PROTO, IPPROTO_TCP);
	nfct_set_attr_u16(master, ATTR_PORT_SRC, htons(10240));
	nfct_set_attr_u16(master, ATTR_PORT_DST, htons(10241));

	exp = nfexp_new();
	if (!exp) {
		perror("nfexp_new");
		exit(EXIT_FAILURE);
	}

	nfexp_set_attr(exp, ATTR_EXP_MASTER, master);

	h = nfct_open(EXPECT, 0);
	if (!h) {
		perror("nfct_open");
		return -1;
	}

	nfexp_callback_register(h, NFCT_T_ALL, cb, NULL);
	ret = nfexp_query(h, NFCT_Q_GET, exp);

	printf("TEST: get expectation (%d)(%s)\n", ret, strerror(errno));

	if (ret == -1)
		exit(EXIT_FAILURE);

	exit(EXIT_SUCCESS);
    #endif
}
