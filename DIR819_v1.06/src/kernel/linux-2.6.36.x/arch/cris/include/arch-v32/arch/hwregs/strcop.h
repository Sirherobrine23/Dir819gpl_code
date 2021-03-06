// $Id: //WIFI_SOC/MP/SDK_4_2_0_0/RT288x_SDK/source/linux-2.6.36.x/arch/cris/include/arch-v32/arch/hwregs/strcop.h#1 $

// Streamcop meta-data configuration structs

struct strcop_meta_out {
	unsigned char  csumsel  : 3;
	unsigned char  ciphsel  : 3;
	unsigned char  ciphconf : 2;
	unsigned char  hashsel  : 3;
	unsigned char  hashconf : 1;
	unsigned char  hashmode : 1;
	unsigned char  decrypt  : 1;
	unsigned char  dlkey    : 1;
	unsigned char  cbcmode  : 1;
};

struct strcop_meta_in {
	unsigned char  dmasel     : 3;
	unsigned char  sync       : 1;
	unsigned char  res1       : 5;
	unsigned char  res2;
};

// Source definitions

enum {
	src_none = 0,
	src_dma  = 1,
	src_des  = 2,
	src_sha1 = 3,
	src_csum = 4,
	src_aes  = 5,
	src_md5  = 6,
	src_res  = 7
};

// Cipher definitions

enum {
	ciph_des = 0,
	ciph_3des = 1,
	ciph_aes = 2
};

// Hash definitions

enum {
	hash_sha1 = 0,
	hash_md5 = 1
};

enum {
	hash_noiv = 0,
	hash_iv = 1
};


