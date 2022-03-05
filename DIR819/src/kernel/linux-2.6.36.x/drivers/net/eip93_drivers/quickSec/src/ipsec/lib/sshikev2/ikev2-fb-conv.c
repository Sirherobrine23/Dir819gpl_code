/**
   File:	ikev2-fb-conv.c

   @copyright:	Copyright (c) 2005 SFNT Finland Oy
   		All rights reserved.

   Conversion routines of IKE identifiers between IKEv1 and IKEv2.  

*/

#include "sshincludes.h"
#include "sshikev2-initiator.h"
#include "sshikev2-exchange.h"
#include "sshikev2-payloads.h"
#include "ikev2-internal.h"
#include "sshikev2-util.h"

#ifdef SSHDIST_IKEV1
#include "isakmp.h"
#include "isakmp_doi.h"
#include "isakmp_util.h"

#include "ikev2-fb.h"

#define SSH_DEBUG_MODULE "SshIkev2FallbackConv"

/* Mapping between SshIkeProtocolIdentifiers and their names. */
const SshKeywordStruct ikev2_fb_ike_protocol_identifiers[] =
{
  {"Reserved",  SSH_IKE_PROTOCOL_RESERVED},
  {"ISAKMP",    SSH_IKE_PROTOCOL_ISAKMP},
  {"AH",        SSH_IKE_PROTOCOL_IPSEC_AH},
  {"ESP",       SSH_IKE_PROTOCOL_IPSEC_ESP},
  {"IPComp",    SSH_IKE_PROTOCOL_IPCOMP},
  {NULL, 0},
};

/* Mapping between SshIkeAttributeAuthMethValues and their names. */
const SshKeywordStruct ikev2_fb_ike_authentication_methods[] =
{
  {"Reserved",                0 /* SSH_IKE_VALUES_AUTH_METH_RESERVED */},
  {"Pre-shared keys",         SSH_IKE_VALUES_AUTH_METH_PRE_SHARED_KEY},
  {"DSS signatures",          SSH_IKE_VALUES_AUTH_METH_DSS_SIGNATURES},
  {"RSA signatures",          SSH_IKE_VALUES_AUTH_METH_RSA_SIGNATURES},
  {"RSA encryption",          SSH_IKE_VALUES_AUTH_METH_RSA_ENCRYPTION},
  {"RSA encryption revised",  SSH_IKE_VALUES_AUTH_METH_RSA_ENCRYPTION_REVISED},
#ifdef REMOVED_BY_DOI_DRAFT_07
  {"GSSAPI",                  SSH_IKE_VALUES_AUTH_METH_GSSAPI},
#endif

#ifdef SSHDIST_CRYPT_ECP
  { "ECP DSA 256 bit group", SSH_IKE_VALUES_AUTH_METH_ECP_DSA_256 },
  { "ECP DSA 384 bit group", SSH_IKE_VALUES_AUTH_METH_ECP_DSA_384 },
  { "ECP DSA 521 bit group", SSH_IKE_VALUES_AUTH_METH_ECP_DSA_521 },
#endif /* SSHDIST_CRYPT_ECP */

#ifdef SSHDIST_IKE_XAUTH
  {"XAUTH I pre-shared keys",
   SSH_IKE_VALUES_AUTH_METH_XAUTH_I_PRE_SHARED},
  {"XAUTH R pre-shared keys",
   SSH_IKE_VALUES_AUTH_METH_XAUTH_R_PRE_SHARED},
  {"XAUTH I DSS signatures",
   SSH_IKE_VALUES_AUTH_METH_XAUTH_I_DSS_SIGNATURES},
  {"XAUTH R DSS signatures",
   SSH_IKE_VALUES_AUTH_METH_XAUTH_R_DSS_SIGNATURES},
  {"XAUTH I RSA signatures",
   SSH_IKE_VALUES_AUTH_METH_XAUTH_I_RSA_SIGNATURES},
  {"XAUTH R RSA signatures",
   SSH_IKE_VALUES_AUTH_METH_XAUTH_R_RSA_SIGNATURES},
  {"XAUTH I RSA encryption",
   SSH_IKE_VALUES_AUTH_METH_XAUTH_I_RSA_ENCRYPTION},
  {"XAUTH R RSA encryption",
   SSH_IKE_VALUES_AUTH_METH_XAUTH_R_RSA_ENCRYPTION},
  {"XAUTH I RSA encryption revised",
   SSH_IKE_VALUES_AUTH_METH_XAUTH_I_RSA_ENCRYPTION_REVISED},
  {"XAUTH R RSA encryption revised",
   SSH_IKE_VALUES_AUTH_METH_XAUTH_R_RSA_ENCRYPTION_REVISED},
#endif /* SSHDIST_IKE_XAUTH */
  {NULL, 0},
};


/* Conversion of IKEv2 transform identifiers to their IKEv1 counterparts */

SshIkeIpsecESPTransformIdentifiers
ikev2_fb_v2_id_to_v1_esp_id(SshIkev2TransformID transform_id)
{
  switch (transform_id)
    {
    case SSH_IKEV2_TRANSFORM_ENCR_DES_IV64:
      return SSH_IKE_IPSEC_ESP_TRANSFORM_ESP_DES_IV64;
    case SSH_IKEV2_TRANSFORM_ENCR_DES:
      return SSH_IKE_IPSEC_ESP_TRANSFORM_ESP_DES;
    case SSH_IKEV2_TRANSFORM_ENCR_3DES:
      return SSH_IKE_IPSEC_ESP_TRANSFORM_ESP_3DES;
    case SSH_IKEV2_TRANSFORM_ENCR_RC5:
      return SSH_IKE_IPSEC_ESP_TRANSFORM_ESP_RC5;
    case SSH_IKEV2_TRANSFORM_ENCR_IDEA:
      return SSH_IKE_IPSEC_ESP_TRANSFORM_ESP_IDEA;
    case SSH_IKEV2_TRANSFORM_ENCR_CAST:
      return SSH_IKE_IPSEC_ESP_TRANSFORM_ESP_CAST;
    case SSH_IKEV2_TRANSFORM_ENCR_BLOWFISH:
      return SSH_IKE_IPSEC_ESP_TRANSFORM_ESP_BLOWFISH;




    case SSH_IKEV2_TRANSFORM_ENCR_3IDEA:
      return SSH_IKE_IPSEC_ESP_TRANSFORM_ESP_3IDEA;
    case SSH_IKEV2_TRANSFORM_ENCR_DES_IV32:
      return SSH_IKE_IPSEC_ESP_TRANSFORM_ESP_DES_IV32;
    case SSH_IKEV2_TRANSFORM_ENCR_NULL:
      return SSH_IKE_IPSEC_ESP_TRANSFORM_ESP_NULL;
    case SSH_IKEV2_TRANSFORM_ENCR_AES_CBC:
      return SSH_IKE_IPSEC_ESP_TRANSFORM_ESP_AES;
    case SSH_IKEV2_TRANSFORM_ENCR_AES_CTR:
      return SSH_IKE_IPSEC_ESP_TRANSFORM_ESP_AES_CTR;
#ifdef SSHDIST_CRYPT_RIJNDAEL
#ifdef SSHDIST_CRYPT_MODE_GCM
    case SSH_IKEV2_TRANSFORM_ENCR_AES_GCM_8:
      return SSH_IKE_IPSEC_ESP_TRANSFORM_ESP_AES_GCM_8;
    case SSH_IKEV2_TRANSFORM_ENCR_AES_GCM_12:
      return SSH_IKE_IPSEC_ESP_TRANSFORM_ESP_AES_GCM_12;
    case SSH_IKEV2_TRANSFORM_ENCR_AES_GCM_16:
      return SSH_IKE_IPSEC_ESP_TRANSFORM_ESP_AES_GCM_16;
#endif /*  SSHDIST_CRYPT_MODE_GCM */
#endif /* SSHDIST_CRYPT_RIJNDAEL */
    default:
      return -1;
    }
}

SshIkeIpsecAHTransformIdentifiers
ikev2_fb_v2_id_to_v1_ah_id(SshIkev2TransformID transform_id)
{
  switch (transform_id)
    {
    case SSH_IKEV2_TRANSFORM_AUTH_HMAC_MD5_96:
      return SSH_IKE_IPSEC_AH_TRANSFORM_AH_MD5;
    case SSH_IKEV2_TRANSFORM_AUTH_HMAC_SHA1_96:
      return SSH_IKE_IPSEC_AH_TRANSFORM_AH_SHA;
    case SSH_IKEV2_TRANSFORM_AUTH_HMAC_SHA256_128:
      return SSH_IKE_IPSEC_AH_TRANSFORM_AH_SHA2_256;
    case SSH_IKEV2_TRANSFORM_AUTH_HMAC_SHA384_192:
      return SSH_IKE_IPSEC_AH_TRANSFORM_AH_SHA2_384;
    case SSH_IKEV2_TRANSFORM_AUTH_HMAC_SHA512_256:
      return SSH_IKE_IPSEC_AH_TRANSFORM_AH_SHA2_512;
    case SSH_IKEV2_TRANSFORM_AUTH_DES_MAC:
      return SSH_IKE_IPSEC_AH_TRANSFORM_AH_DES;
    case SSH_IKEV2_TRANSFORM_AUTH_AES_XCBC_96:
#ifdef SSHDIST_CRYPT_XCBCMAC
      /* Fall-through to default: if the distribution define is not set */
      return SSH_IKE_IPSEC_AH_TRANSFORM_AH_XCBC_AES;
#endif /* SSHDIST_CRYPT_XCBCMAC */
#ifdef SSHDIST_CRYPT_MODE_GCM
    case SSH_IKEV2_TRANSFORM_AUTH_AES_128_GMAC_128:
      return SSH_IKE_IPSEC_AH_TRANSFORM_AH_AES_128_GMAC;
    case SSH_IKEV2_TRANSFORM_AUTH_AES_192_GMAC_128:
      return SSH_IKE_IPSEC_AH_TRANSFORM_AH_AES_192_GMAC;
    case SSH_IKEV2_TRANSFORM_AUTH_AES_256_GMAC_128:
      return SSH_IKE_IPSEC_AH_TRANSFORM_AH_AES_256_GMAC;
#endif /* SSHDIST_CRYPT_MODE_GCM */
    default:
      return -1;
    }
}

SshIkeIpsecAttributeAuthAlgorithmValues
ikev2_fb_v2_id_to_v1_auth_id(SshIkev2TransformID transform_id)
{
  switch (transform_id)
    {
    case SSH_IKEV2_TRANSFORM_AUTH_HMAC_MD5_96:
      return IPSEC_VALUES_AUTH_ALGORITHM_HMAC_MD5;
    case SSH_IKEV2_TRANSFORM_AUTH_HMAC_SHA1_96:
      return IPSEC_VALUES_AUTH_ALGORITHM_HMAC_SHA_1;
    case SSH_IKEV2_TRANSFORM_AUTH_HMAC_SHA256_128:
      return IPSEC_VALUES_AUTH_ALGORITHM_HMAC_SHA2_256;
    case SSH_IKEV2_TRANSFORM_AUTH_HMAC_SHA384_192:
      return IPSEC_VALUES_AUTH_ALGORITHM_HMAC_SHA2_384;
    case SSH_IKEV2_TRANSFORM_AUTH_HMAC_SHA512_256:
      return IPSEC_VALUES_AUTH_ALGORITHM_HMAC_SHA2_512;
    case SSH_IKEV2_TRANSFORM_AUTH_DES_MAC:
      return IPSEC_VALUES_AUTH_ALGORITHM_DES_MAC;
    case SSH_IKEV2_TRANSFORM_AUTH_KPDK_MD5:
      return IPSEC_VALUES_AUTH_ALGORITHM_KPDK;
    case SSH_IKEV2_TRANSFORM_AUTH_AES_XCBC_96:
#ifdef SSHDIST_CRYPT_XCBCMAC
      /* Fall-through to default: if the distribution define is not set */
      return IPSEC_VALUES_AUTH_ALGORITHM_XCBC_AES;
#endif /* SSHDIST_CRYPT_XCBCMAC */
#ifdef SSHDIST_CRYPT_MODE_GCM
    case SSH_IKEV2_TRANSFORM_AUTH_AES_128_GMAC_128:
      return IPSEC_VALUES_AUTH_ALGORITHM_AES_128_GMAC;
    case SSH_IKEV2_TRANSFORM_AUTH_AES_192_GMAC_128:
      return IPSEC_VALUES_AUTH_ALGORITHM_AES_192_GMAC;
    case SSH_IKEV2_TRANSFORM_AUTH_AES_256_GMAC_128:
      return IPSEC_VALUES_AUTH_ALGORITHM_AES_256_GMAC;
#endif /* SSHDIST_CRYPT_MODE_GCM */
    default:
      return -1;
    }
}

SshIkeAttributeHashAlgValues
ikev2_fb_v2_id_to_v1_hash_id(SshIkev2TransformID transform_id)
{
  switch (transform_id)
    {
    case SSH_IKEV2_TRANSFORM_PRF_HMAC_MD5:
      return SSH_IKE_VALUES_HASH_ALG_MD5;
    case SSH_IKEV2_TRANSFORM_PRF_HMAC_SHA1:
      return SSH_IKE_VALUES_HASH_ALG_SHA;
    case SSH_IKEV2_TRANSFORM_PRF_HMAC_SHA256:
      return SSH_IKE_VALUES_HASH_ALG_SHA2_256;
    case SSH_IKEV2_TRANSFORM_PRF_HMAC_SHA384:
      return SSH_IKE_VALUES_HASH_ALG_SHA2_384;
    case SSH_IKEV2_TRANSFORM_PRF_HMAC_SHA512:
      return SSH_IKE_VALUES_HASH_ALG_SHA2_512;
    case SSH_IKEV2_TRANSFORM_PRF_HMAC_TIGER:
      return SSH_IKE_VALUES_HASH_ALG_TIGER;
    case SSH_IKEV2_TRANSFORM_PRF_AES128_CBC:
    default:
      return -1;
    }
}

SshIkeAttributeGrpDescValues
ikev2_fb_v2_id_to_v1_group_id(SshIkev2TransformID transform_id)
{
  switch (transform_id)
    {
    case SSH_IKEV2_TRANSFORM_D_H_NONE:
      return 0;
    case SSH_IKEV2_TRANSFORM_D_H_MODP_768:
      return IPSEC_VALUES_GRP_DESC_DEFAULT_768;
    case SSH_IKEV2_TRANSFORM_D_H_MODP_1024:
      return IPSEC_VALUES_GRP_DESC_DEFAULT_1024;
    case SSH_IKEV2_TRANSFORM_D_H_EC2N_155:
      return IPSEC_VALUES_GRP_DESC_DEFAULT_EC2N_155;
    case SSH_IKEV2_TRANSFORM_D_H_EC2N_185:
      return IPSEC_VALUES_GRP_DESC_DEFAULT_EC2N_185;
    case SSH_IKEV2_TRANSFORM_D_H_MODP_1536:
      return IPSEC_VALUES_GRP_DESC_DEFAULT_1536;
    case SSH_IKEV2_TRANSFORM_D_H_MODP_2048:
      return 14;
    case SSH_IKEV2_TRANSFORM_D_H_MODP_3072:
      return 15;
    case SSH_IKEV2_TRANSFORM_D_H_MODP_4096:
      return 16;
    case SSH_IKEV2_TRANSFORM_D_H_MODP_6144:
      return 17;
    case SSH_IKEV2_TRANSFORM_D_H_MODP_8192:
      return 18;
#ifdef SSHDIST_CRYPT_ECP
    case SSH_IKEV2_TRANSFORM_D_H_EC_MODP_256:
      return 19;
    case SSH_IKEV2_TRANSFORM_D_H_EC_MODP_384:
      return 20;
    case SSH_IKEV2_TRANSFORM_D_H_EC_MODP_521:
      return 21;
#endif /* SSHDIST_CRYPT_ECP */
    case SSH_IKEV2_TRANSFORM_D_H_MODP_RFC5114_1024_160:
      return 22;
    case SSH_IKEV2_TRANSFORM_D_H_MODP_RFC5114_2048_224:
      return 23;
    case SSH_IKEV2_TRANSFORM_D_H_MODP_RFC5114_2048_256:
      return 24;
    case SSH_IKEV2_TRANSFORM_D_H_MAX:
    default:
      return -1;
    }
}

SshIkeAttributeEncrAlgValues
ikev2_fb_v2_id_to_v1_encr_id(SshIkev2TransformID transform_id)
{
  switch (transform_id)
    {
    case SSH_IKEV2_TRANSFORM_ENCR_DES:
      return SSH_IKE_VALUES_ENCR_ALG_DES_CBC;
    case SSH_IKEV2_TRANSFORM_ENCR_3DES:
      return SSH_IKE_VALUES_ENCR_ALG_3DES_CBC;
    case SSH_IKEV2_TRANSFORM_ENCR_RC5:
      return SSH_IKE_VALUES_ENCR_ALG_RC5_R16_B64_CBC;
    case SSH_IKEV2_TRANSFORM_ENCR_IDEA:
      return SSH_IKE_VALUES_ENCR_ALG_IDEA_CBC;
    case SSH_IKEV2_TRANSFORM_ENCR_CAST:
      return SSH_IKE_VALUES_ENCR_ALG_CAST_CBC;
    case SSH_IKEV2_TRANSFORM_ENCR_BLOWFISH:
      return SSH_IKE_VALUES_ENCR_ALG_BLOWFISH_CBC;




    case SSH_IKEV2_TRANSFORM_ENCR_AES_CBC:
      return SSH_IKE_VALUES_ENCR_ALG_AES_CBC;
#ifdef SSHDIST_CRYPT_RIJNDAEL
#ifdef SSHDIST_CRYPT_MODE_GCM
    case SSH_IKEV2_TRANSFORM_ENCR_AES_GCM_8:
      return SSH_IKE_IPSEC_ESP_TRANSFORM_ESP_AES_GCM_8;
    case SSH_IKEV2_TRANSFORM_ENCR_AES_GCM_12:
      return SSH_IKE_IPSEC_ESP_TRANSFORM_ESP_AES_GCM_12;
    case SSH_IKEV2_TRANSFORM_ENCR_AES_GCM_16:
      return SSH_IKE_IPSEC_ESP_TRANSFORM_ESP_AES_GCM_16;
    case SSH_IKEV2_TRANSFORM_ENCR_NULL_AUTH_AES_GMAC:
      return SSH_IKE_IPSEC_ESP_TRANSFORM_ESP_NULL_AUTH_AES_GMAC;
#endif /*  SSHDIST_CRYPT_MODE_GCM */
#endif /* SSHDIST_CRYPT_RIJNDAEL */
    case SSH_IKEV2_TRANSFORM_ENCR_3IDEA:
    case SSH_IKEV2_TRANSFORM_ENCR_DES_IV32:
    case SSH_IKEV2_TRANSFORM_ENCR_NULL:
    case SSH_IKEV2_TRANSFORM_ENCR_AES_CTR:
    case SSH_IKEV2_TRANSFORM_ENCR_DES_IV64:
    default:
      return -1;
    }
}

/***********************************************************************/

/* Conversion of IKEv1 transform identifiers to their IKEv2 counterparts */

SshIkev2TransformID
ikev2_fb_v1_esp_id_to_v2_id(SshIkeIpsecESPTransformIdentifiers esp_id)
{
  switch (esp_id)
    {
    case SSH_IKE_IPSEC_ESP_TRANSFORM_ESP_DES_IV64:
      return SSH_IKEV2_TRANSFORM_ENCR_DES_IV64;
    case SSH_IKE_IPSEC_ESP_TRANSFORM_ESP_DES:
      return SSH_IKEV2_TRANSFORM_ENCR_DES;
    case SSH_IKE_IPSEC_ESP_TRANSFORM_ESP_3DES:
      return SSH_IKEV2_TRANSFORM_ENCR_3DES;
    case SSH_IKE_IPSEC_ESP_TRANSFORM_ESP_RC5:
      return SSH_IKEV2_TRANSFORM_ENCR_RC5;
    case SSH_IKE_IPSEC_ESP_TRANSFORM_ESP_IDEA:
      return SSH_IKEV2_TRANSFORM_ENCR_IDEA;
    case SSH_IKE_IPSEC_ESP_TRANSFORM_ESP_CAST:
      return SSH_IKEV2_TRANSFORM_ENCR_CAST;
    case SSH_IKE_IPSEC_ESP_TRANSFORM_ESP_BLOWFISH:
      return SSH_IKEV2_TRANSFORM_ENCR_BLOWFISH;




    case SSH_IKE_IPSEC_ESP_TRANSFORM_ESP_3IDEA:
      return SSH_IKEV2_TRANSFORM_ENCR_3IDEA;
    case SSH_IKE_IPSEC_ESP_TRANSFORM_ESP_DES_IV32:
      return SSH_IKEV2_TRANSFORM_ENCR_DES_IV32;
    case SSH_IKE_IPSEC_ESP_TRANSFORM_ESP_NULL:
      return SSH_IKEV2_TRANSFORM_ENCR_NULL;
    case SSH_IKE_IPSEC_ESP_TRANSFORM_ESP_AES:
      return SSH_IKEV2_TRANSFORM_ENCR_AES_CBC;
    case SSH_IKE_IPSEC_ESP_TRANSFORM_ESP_AES_CTR:
      return SSH_IKEV2_TRANSFORM_ENCR_AES_CTR;
#ifdef SSHDIST_CRYPT_RIJNDAEL
#ifdef SSHDIST_CRYPT_MODE_GCM
    case SSH_IKE_IPSEC_ESP_TRANSFORM_ESP_AES_GCM_8:
      return SSH_IKEV2_TRANSFORM_ENCR_AES_GCM_8;
    case SSH_IKE_IPSEC_ESP_TRANSFORM_ESP_AES_GCM_12:
      return SSH_IKEV2_TRANSFORM_ENCR_AES_GCM_12;
    case SSH_IKE_IPSEC_ESP_TRANSFORM_ESP_AES_GCM_16:
      return SSH_IKEV2_TRANSFORM_ENCR_AES_GCM_16;
#endif /*  SSHDIST_CRYPT_MODE_GCM */
#endif /* SSHDIST_CRYPT_RIJNDAEL */
    default:
      SSH_DEBUG(SSH_D_FAIL, ("Unknown ESP transform identifier %d", esp_id));
      return -1;
    }
}

SshIkev2TransformID
ikev2_fb_v1_ah_id_to_v2_id(SshIkeIpsecAHTransformIdentifiers ah_id)
{
  switch (ah_id)
    {
    case SSH_IKE_IPSEC_AH_TRANSFORM_AH_MD5:
      return SSH_IKEV2_TRANSFORM_AUTH_HMAC_MD5_96;
    case SSH_IKE_IPSEC_AH_TRANSFORM_AH_SHA:
      return SSH_IKEV2_TRANSFORM_AUTH_HMAC_SHA1_96;
    case SSH_IKE_IPSEC_AH_TRANSFORM_AH_SHA2_256:
      return SSH_IKEV2_TRANSFORM_AUTH_HMAC_SHA256_128;
    case SSH_IKE_IPSEC_AH_TRANSFORM_AH_SHA2_384:
      return SSH_IKEV2_TRANSFORM_AUTH_HMAC_SHA384_192;
    case SSH_IKE_IPSEC_AH_TRANSFORM_AH_SHA2_512:
      return SSH_IKEV2_TRANSFORM_AUTH_HMAC_SHA512_256;
    case SSH_IKE_IPSEC_AH_TRANSFORM_AH_DES:
      return SSH_IKEV2_TRANSFORM_AUTH_DES_MAC;
#ifdef SSHDIST_CRYPT_XCBCMAC
    case SSH_IKE_IPSEC_AH_TRANSFORM_AH_XCBC_AES:
      return SSH_IKEV2_TRANSFORM_AUTH_AES_XCBC_96;
#endif /* SSHDIST_CRYPT_XCBCMAC */
#ifdef SSHDIST_CRYPT_MODE_GCM
    case SSH_IKE_IPSEC_AH_TRANSFORM_AH_AES_128_GMAC:
      return SSH_IKEV2_TRANSFORM_AUTH_AES_128_GMAC_128;
    case SSH_IKE_IPSEC_AH_TRANSFORM_AH_AES_192_GMAC:
      return SSH_IKEV2_TRANSFORM_AUTH_AES_192_GMAC_128;
    case SSH_IKE_IPSEC_AH_TRANSFORM_AH_AES_256_GMAC:
      return SSH_IKEV2_TRANSFORM_AUTH_AES_256_GMAC_128;
#endif /* SSHDIST_CRYPT_MODE_GCM */
    default:
      SSH_DEBUG(SSH_D_FAIL, ("Unknown AH transform identifier %d", ah_id));
      return -1;
    }
}

SshIkev2TransformID
ikev2_fb_v1_auth_id_to_v2_id(SshIkeIpsecAttributeAuthAlgorithmValues
			     auth_id)
{
  switch (auth_id)
    {
    case IPSEC_VALUES_AUTH_ALGORITHM_HMAC_MD5:
      return SSH_IKEV2_TRANSFORM_AUTH_HMAC_MD5_96;
    case IPSEC_VALUES_AUTH_ALGORITHM_HMAC_SHA_1:
      return SSH_IKEV2_TRANSFORM_AUTH_HMAC_SHA1_96;
    case IPSEC_VALUES_AUTH_ALGORITHM_HMAC_SHA2_256:
      return SSH_IKEV2_TRANSFORM_AUTH_HMAC_SHA256_128;
    case IPSEC_VALUES_AUTH_ALGORITHM_HMAC_SHA2_384:
      return SSH_IKEV2_TRANSFORM_AUTH_HMAC_SHA384_192;
    case IPSEC_VALUES_AUTH_ALGORITHM_HMAC_SHA2_512:
      return SSH_IKEV2_TRANSFORM_AUTH_HMAC_SHA512_256;
    case IPSEC_VALUES_AUTH_ALGORITHM_DES_MAC:
      return SSH_IKEV2_TRANSFORM_AUTH_DES_MAC;
    case IPSEC_VALUES_AUTH_ALGORITHM_KPDK:
      return SSH_IKEV2_TRANSFORM_AUTH_KPDK_MD5;
#ifdef SSHDIST_CRYPT_XCBCMAC
    case IPSEC_VALUES_AUTH_ALGORITHM_XCBC_AES:
      return SSH_IKEV2_TRANSFORM_AUTH_AES_XCBC_96;
#endif /* SSHDIST_CRYPT_XCBCMAC */
#ifdef SSHDIST_CRYPT_MODE_GCM
    case IPSEC_VALUES_AUTH_ALGORITHM_AES_128_GMAC:
      return SSH_IKEV2_TRANSFORM_AUTH_AES_128_GMAC_128;
    case IPSEC_VALUES_AUTH_ALGORITHM_AES_192_GMAC:
      return SSH_IKEV2_TRANSFORM_AUTH_AES_192_GMAC_128;
    case IPSEC_VALUES_AUTH_ALGORITHM_AES_256_GMAC:
      return SSH_IKEV2_TRANSFORM_AUTH_AES_256_GMAC_128;
#endif /* SSHDIST_CRYPT_MODE_GCM */
    default:
      SSH_DEBUG(SSH_D_FAIL, ("Unknown Auth transform identifier %d", auth_id));
      return -1;
    }
}

SshIkev2TransformID
ikev2_fb_v1_hash_id_to_v2_prf_id(SshIkeAttributeHashAlgValues hash_id)
{
  switch (hash_id)
    {
    case SSH_IKE_VALUES_HASH_ALG_MD5:
      return SSH_IKEV2_TRANSFORM_PRF_HMAC_MD5;
    case SSH_IKE_VALUES_HASH_ALG_SHA:
      return SSH_IKEV2_TRANSFORM_PRF_HMAC_SHA1;
    case SSH_IKE_VALUES_HASH_ALG_SHA2_256:
      return SSH_IKEV2_TRANSFORM_PRF_HMAC_SHA256;
    case SSH_IKE_VALUES_HASH_ALG_SHA2_384:
      return SSH_IKEV2_TRANSFORM_PRF_HMAC_SHA384;
    case SSH_IKE_VALUES_HASH_ALG_SHA2_512:
      return SSH_IKEV2_TRANSFORM_PRF_HMAC_SHA512;
    case SSH_IKE_VALUES_HASH_ALG_TIGER:
      return SSH_IKEV2_TRANSFORM_PRF_HMAC_TIGER;
    default:
      SSH_DEBUG(SSH_D_FAIL, ("Unknown IKE hash alg identifier %d", hash_id));
      return -1;
    }
}

SshIkev2TransformID
ikev2_fb_v1_hash_id_to_v2_integ_id(SshIkeAttributeHashAlgValues hash_id)
{
  switch (hash_id)
    {
    case SSH_IKE_VALUES_HASH_ALG_MD5:
      return SSH_IKEV2_TRANSFORM_AUTH_HMAC_MD5_96;
    case SSH_IKE_VALUES_HASH_ALG_SHA:
      return SSH_IKEV2_TRANSFORM_AUTH_HMAC_SHA1_96;
    case SSH_IKE_VALUES_HASH_ALG_SHA2_256:
      return SSH_IKEV2_TRANSFORM_AUTH_HMAC_SHA256_128;
    case SSH_IKE_VALUES_HASH_ALG_SHA2_384:
      return SSH_IKEV2_TRANSFORM_AUTH_HMAC_SHA384_192;
    case SSH_IKE_VALUES_HASH_ALG_SHA2_512:
      return SSH_IKEV2_TRANSFORM_AUTH_HMAC_SHA512_256;
    case SSH_IKE_VALUES_HASH_ALG_TIGER:
    default:
      SSH_DEBUG(SSH_D_FAIL, ("Unknown IKE hash alg identifier %d", hash_id));
      return -1;
    }
}

SshIkev2TransformID
ikev2_fb_v1_group_id_to_v2_id(SshIkeAttributeGrpDescValues group_id)
{
  switch (group_id)
    {
    case IPSEC_VALUES_GRP_DESC_DEFAULT_768:
      return SSH_IKEV2_TRANSFORM_D_H_MODP_768;
    case IPSEC_VALUES_GRP_DESC_DEFAULT_1024:
      return SSH_IKEV2_TRANSFORM_D_H_MODP_1024;
    case IPSEC_VALUES_GRP_DESC_DEFAULT_EC2N_155:
      return SSH_IKEV2_TRANSFORM_D_H_EC2N_155;
    case IPSEC_VALUES_GRP_DESC_DEFAULT_EC2N_185:
      return SSH_IKEV2_TRANSFORM_D_H_EC2N_185;
    case IPSEC_VALUES_GRP_DESC_DEFAULT_1536:
      return SSH_IKEV2_TRANSFORM_D_H_MODP_1536;
    case 14:
      return SSH_IKEV2_TRANSFORM_D_H_MODP_2048;
    case 15:
      return SSH_IKEV2_TRANSFORM_D_H_MODP_3072;
    case 16:
      return SSH_IKEV2_TRANSFORM_D_H_MODP_4096;
    case 17:
      return SSH_IKEV2_TRANSFORM_D_H_MODP_6144;
    case 18:
      return SSH_IKEV2_TRANSFORM_D_H_MODP_8192;
#ifdef SSHDIST_CRYPT_ECP
    case 19: 
      return SSH_IKEV2_TRANSFORM_D_H_EC_MODP_256;
    case 20: 
     return SSH_IKEV2_TRANSFORM_D_H_EC_MODP_384;
    case 21: 
      return SSH_IKEV2_TRANSFORM_D_H_EC_MODP_521;
#endif /* SSHDIST_CRYPT_ECP */
    case 22:
      return SSH_IKEV2_TRANSFORM_D_H_MODP_RFC5114_1024_160;
    case 23:
      return SSH_IKEV2_TRANSFORM_D_H_MODP_RFC5114_2048_224;
    case 24:
      return SSH_IKEV2_TRANSFORM_D_H_MODP_RFC5114_2048_256;
    default:
      SSH_DEBUG(SSH_D_FAIL, ("Unknown DH group identifier %d", group_id));
      return -1;
    }
}

SshIkev2TransformID
ikev2_fb_v1_encr_id_to_v2_id(SshIkeAttributeEncrAlgValues encr_id)
{
  switch (encr_id)
    {
    case SSH_IKE_VALUES_ENCR_ALG_DES_CBC:
      return SSH_IKEV2_TRANSFORM_ENCR_DES;
    case SSH_IKE_VALUES_ENCR_ALG_3DES_CBC:
      return SSH_IKEV2_TRANSFORM_ENCR_3DES;
    case SSH_IKE_VALUES_ENCR_ALG_RC5_R16_B64_CBC:
      return SSH_IKEV2_TRANSFORM_ENCR_RC5;
    case SSH_IKE_VALUES_ENCR_ALG_IDEA_CBC:
      return SSH_IKEV2_TRANSFORM_ENCR_IDEA;
    case SSH_IKE_VALUES_ENCR_ALG_CAST_CBC:
      return SSH_IKEV2_TRANSFORM_ENCR_CAST;
    case SSH_IKE_VALUES_ENCR_ALG_BLOWFISH_CBC:
      return SSH_IKEV2_TRANSFORM_ENCR_BLOWFISH;




    case SSH_IKE_VALUES_ENCR_ALG_AES_CBC:
      return SSH_IKEV2_TRANSFORM_ENCR_AES_CBC;
    default:
      SSH_DEBUG(SSH_D_FAIL, ("Unknown IKE encryption identifier %d", encr_id));
      return -1;
    }
}

SshIkev2Error
ikev2_fb_v1_notify_message_type_to_v2_error_code(SshIkeNotifyMessageType code)
{
  switch (code)
    {
    case SSH_IKE_NOTIFY_MESSAGE_CONNECTED:
      return SSH_IKEV2_ERROR_OK;
    case SSH_IKE_NOTIFY_MESSAGE_INVALID_PAYLOAD_TYPE:
      return SSH_IKEV2_ERROR_INVALID_SYNTAX;
    case SSH_IKE_NOTIFY_MESSAGE_INVALID_MAJOR_VERSION:
      return SSH_IKEV2_ERROR_INVALID_MAJOR_VERSION;
    case SSH_IKE_NOTIFY_MESSAGE_NO_PROPOSAL_CHOSEN:
      return SSH_IKEV2_ERROR_NO_PROPOSAL_CHOSEN;
    case SSH_IKE_NOTIFY_MESSAGE_TIMEOUT:
      return SSH_IKEV2_ERROR_TIMEOUT;
    case SSH_IKE_NOTIFY_MESSAGE_OUT_OF_MEMORY:
      return SSH_IKEV2_ERROR_OUT_OF_MEMORY;
    case SSH_IKE_NOTIFY_MESSAGE_CERTIFICATE_UNAVAILABLE:
    case SSH_IKE_NOTIFY_MESSAGE_INVALID_SIGNATURE:
    case SSH_IKE_NOTIFY_MESSAGE_AUTHENTICATION_FAILED:
      return SSH_IKEV2_ERROR_AUTHENTICATION_FAILED;
    default:
      return SSH_IKEV2_ERROR_INVALID_SYNTAX;
    }
}

#ifdef SSHDIST_IKE_CERT_AUTH
SshIkeCertificateEncodingType
ikev2_fb_v1_cert_encoding_to_v2(SshIkev2CertEncoding encoding)
{
  switch (encoding)
    {
    case SSH_IKEV2_CERT_PKCS7_WRAPPED_X_509:
      return SSH_IKE_CERTIFICATE_ENCODING_PKCS7;
    case SSH_IKEV2_CERT_PGP:
      return SSH_IKE_CERTIFICATE_ENCODING_PGP;
    case SSH_IKEV2_CERT_DNS_SIGNED_KEY:
      return SSH_IKE_CERTIFICATE_ENCODING_DNS;
    case SSH_IKEV2_CERT_X_509:
      return SSH_IKE_CERTIFICATE_ENCODING_X509_SIG;
    case SSH_IKEV2_CERT_KERBEROS_TOKEN:
      return SSH_IKE_CERTIFICATE_ENCODING_KERBEROS;
    case SSH_IKEV2_CERT_CRL:
      return SSH_IKE_CERTIFICATE_ENCODING_CRL;
    case SSH_IKEV2_CERT_ARL:
      return SSH_IKE_CERTIFICATE_ENCODING_ARL;
    case SSH_IKEV2_CERT_SPKI:
      return SSH_IKE_CERTIFICATE_ENCODING_SPKI;
    case SSH_IKEV2_CERT_X_509_ATTRIBUTE:
      return SSH_IKE_CERTIFICATE_ENCODING_X509_ATTR;
    case SSH_IKEV2_CERT_RAW_RSA_KEY:
    case SSH_IKEV2_CERT_HASH_AND_URL_X509:
    case SSH_IKEV2_CERT_HASH_AND_URL_X509_BUNDLE:
    default:
      return SSH_IKE_CERTIFICATE_ENCODING_NONE;
    }
}

SshIkev2CertEncoding
ikev2_fb_v2_cert_encoding_to_v1(SshIkeCertificateEncodingType encoding)
{
  switch (encoding)
    {
    case SSH_IKE_CERTIFICATE_ENCODING_PKCS7:
      return SSH_IKEV2_CERT_PKCS7_WRAPPED_X_509;
    case SSH_IKE_CERTIFICATE_ENCODING_PGP:
      return SSH_IKEV2_CERT_PGP;
    case SSH_IKE_CERTIFICATE_ENCODING_DNS:
      return SSH_IKEV2_CERT_DNS_SIGNED_KEY;
    case SSH_IKE_CERTIFICATE_ENCODING_X509_SIG:
      return SSH_IKEV2_CERT_X_509;
    case SSH_IKE_CERTIFICATE_ENCODING_KERBEROS:
      return SSH_IKEV2_CERT_KERBEROS_TOKEN;
    case SSH_IKE_CERTIFICATE_ENCODING_CRL:
      return SSH_IKEV2_CERT_CRL;
    case SSH_IKE_CERTIFICATE_ENCODING_ARL:
      return SSH_IKEV2_CERT_ARL;
    case SSH_IKE_CERTIFICATE_ENCODING_SPKI:
      return SSH_IKEV2_CERT_SPKI;
    case SSH_IKE_CERTIFICATE_ENCODING_X509_ATTR:
      return SSH_IKEV2_CERT_X_509_ATTRIBUTE;
    case SSH_IKE_CERTIFICATE_ENCODING_X509_KE:
    case SSH_IKE_CERTIFICATE_ENCODING_NONE:
    default:
      return -1;
    }
}
#endif /* SSHDIST_IKE_CERT_AUTH */
#endif /* SSHDIST_IKEV1 */
