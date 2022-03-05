/*
 *
 *  Copyright:
 *          Copyright (c) 2004, 2005 SFNT Finland Oy.
 */

#include "sshincludes.h"
#include "sshikev2-initiator.h"
#include "sshikev2-util.h"

#define SSH_DEBUG_MODULE "SshIkev2StringPacketPayload"


/* Notify payloads to packet descriptions */
const SshKeywordStruct ssh_ikev2_notify_payload_to_string_table[] = {
  { "N(RESERVED)", SSH_IKEV2_NOTIFY_RESERVED },
  { "N(UNSUPPORTED_CRITICAL_PAYLOAD)",
    SSH_IKEV2_NOTIFY_UNSUPPORTED_CRITICAL_PAYLOAD },
  { "N(INVALID_IKE_SPI)", 
    SSH_IKEV2_NOTIFY_INVALID_IKE_SPI },
  { "N(INVALID_MAJOR_VERSION)", 
    SSH_IKEV2_NOTIFY_INVALID_MAJOR_VERSION },
  { "N(INVALID_SYNTAX)", 
    SSH_IKEV2_NOTIFY_INVALID_SYNTAX },
  { "N(INVALID_MESSAGE_ID)", 
    SSH_IKEV2_NOTIFY_INVALID_MESSAGE_ID },
  { "N(INVALID_SPI)", 
    SSH_IKEV2_NOTIFY_INVALID_SPI },
  { "N(NO_PROPOSAL_CHOSEN)", 
    SSH_IKEV2_NOTIFY_NO_PROPOSAL_CHOSEN },
  { "N(INVALID_KE_PAYLOAD)", 
    SSH_IKEV2_NOTIFY_INVALID_KE_PAYLOAD },
  { "N(AUTHENTICATION_FAILED)", 
    SSH_IKEV2_NOTIFY_AUTHENTICATION_FAILED },
  { "N(SINGLE_PAIR_REQUIRED)", 
    SSH_IKEV2_NOTIFY_SINGLE_PAIR_REQUIRED },
  { "N(NO_ADDITIONAL_SAS)", 
    SSH_IKEV2_NOTIFY_NO_ADDITIONAL_SAS },
  { "N(INTERNAL_ADDRESS_FAILURE)", 
    SSH_IKEV2_NOTIFY_INTERNAL_ADDRESS_FAILURE },
  { "N(FAILED_CP_REQUIRED)", 
    SSH_IKEV2_NOTIFY_FAILED_CP_REQUIRED },
  { "N(TS_UNACCEPTABLE)", 
    SSH_IKEV2_NOTIFY_TS_UNACCEPTABLE },
  { "N(INVALID_SELECTORS)", 
    SSH_IKEV2_NOTIFY_INVALID_SELECTORS },
  { "N(UNACCEPTABLE_ADDRESS)", 
    SSH_IKEV2_NOTIFY_UNACCEPTABLE_ADDRESS },
  { "N(UNEXPECTED_NAT_DETECTED)", 
    SSH_IKEV2_NOTIFY_UNEXPECTED_NAT_DETECTED },
  { "N(INITIAL_CONTACT)", 
    SSH_IKEV2_NOTIFY_INITIAL_CONTACT },
  { "N(SET_WINDOW_SIZE)", 
    SSH_IKEV2_NOTIFY_SET_WINDOW_SIZE },
  { "N(ADDITIONAL_TS_POSSIBLE)", 
    SSH_IKEV2_NOTIFY_ADDITIONAL_TS_POSSIBLE },
  { "N(IPCOMP_SUPPORTED)", 
    SSH_IKEV2_NOTIFY_IPCOMP_SUPPORTED },
  { "N(NAT_DETECTION_SOURCE_IP)", 
    SSH_IKEV2_NOTIFY_NAT_DETECTION_SOURCE_IP },
  { "N(NAT_DETECTION_DESTINATION_IP)",
    SSH_IKEV2_NOTIFY_NAT_DETECTION_DESTINATION_IP },
  { "N(COOKIE)", 
    SSH_IKEV2_NOTIFY_COOKIE },
  { "N(USE_TRANSPORT_MODE)", 
    SSH_IKEV2_NOTIFY_USE_TRANSPORT_MODE },
  { "N(HTTP_CERT_LOOKUP_SUPPORTED)",
    SSH_IKEV2_NOTIFY_HTTP_CERT_LOOKUP_SUPPORTED },
  { "N(REKEY_SA)", 
    SSH_IKEV2_NOTIFY_REKEY_SA },
  { "N(ESP_TFC_PADDING_NOT_SUPPORTED)",
    SSH_IKEV2_NOTIFY_ESP_TFC_PADDING_NOT_SUPPORTED },
  { "N(NON_FIRST_FRAGMENTS_ALSO)", 
    SSH_IKEV2_NOTIFY_NON_FIRST_FRAGMENTS_ALSO },
  { "N(MOBIKE_SUPPORTED)", 
    SSH_IKEV2_NOTIFY_MOBIKE_SUPPORTED },
  { "N(ADDITIONAL_IP4_ADDRESS)", 
    SSH_IKEV2_NOTIFY_ADDITIONAL_IP4_ADDRESS },
  { "N(ADDITIONAL_IP6_ADDRESS)", 
    SSH_IKEV2_NOTIFY_ADDITIONAL_IP6_ADDRESS },
  { "N(NO_ADDITIONAL_ADDRESSES)", 
    SSH_IKEV2_NOTIFY_NO_ADDITIONAL_ADDRESSES },
  { "N(UPDATE_SA_ADDRESSES)", 
    SSH_IKEV2_NOTIFY_UPDATE_SA_ADDRESSES },
  { "N(COOKIE2)", 
    SSH_IKEV2_NOTIFY_COOKIE2 },
  { "N(NO_NATS_ALLOWED)", 
    SSH_IKEV2_NOTIFY_NO_NATS_ALLOWED },
  { "N(MULTIPLE_AUTH_SUPPORTED)", 
    SSH_IKEV2_NOTIFY_MULTIPLE_AUTH_SUPPORTED },
  { "N(ANOTHER_AUTH_FOLLOWS)", 
    SSH_IKEV2_NOTIFY_ANOTHER_AUTH_FOLLOWS },
  { NULL, 0 }
};

/* Packet payloads to packet descriptions */
const SshKeywordStruct ssh_ikev2_packets_payload_to_string_table[] = {
  { "NONE",  
    SSH_IKEV2_PAYLOAD_TYPE_NONE },
  { "SA",  
    SSH_IKEV2_PAYLOAD_TYPE_SA },
  { "KE",  
    SSH_IKEV2_PAYLOAD_TYPE_KE },
  { "IDi",  
    SSH_IKEV2_PAYLOAD_TYPE_ID_I },
  { "IDr",  
    SSH_IKEV2_PAYLOAD_TYPE_ID_R },
  { "CERT",  
    SSH_IKEV2_PAYLOAD_TYPE_CERT },
  { "CERTREQ",  
    SSH_IKEV2_PAYLOAD_TYPE_CERT_REQ },
  { "AUTH",  
    SSH_IKEV2_PAYLOAD_TYPE_AUTH },
  { "Nonce",  
    SSH_IKEV2_PAYLOAD_TYPE_NONCE },
  { "Notify",  
    SSH_IKEV2_PAYLOAD_TYPE_NOTIFY },
  { "DEL",  
    SSH_IKEV2_PAYLOAD_TYPE_DELETE },
  { "Vid",  
    SSH_IKEV2_PAYLOAD_TYPE_VID },
  { "TSi",  
    SSH_IKEV2_PAYLOAD_TYPE_TS_I },
  { "TSr",  
    SSH_IKEV2_PAYLOAD_TYPE_TS_R },
  { "ENC",  
    SSH_IKEV2_PAYLOAD_TYPE_ENCRYPTED },
  { "CP",  
    SSH_IKEV2_PAYLOAD_TYPE_CONF },
  { "EAP",  
    SSH_IKEV2_PAYLOAD_TYPE_EAP },
  { NULL, 0 }
};


const char *
ssh_ikev2_notify_payload_to_string(SshIkev2NotifyMessageType type)
{
  const char *name;

  name = ssh_find_keyword_name(ssh_ikev2_notify_payload_to_string_table, 
                               type);
  if (name == NULL)
    return "unknown";
  
  return name;
}

const char *
ssh_ikev2_packet_payload_to_string(SshIkev2PayloadType type)
{
  const char *name;

  name = ssh_find_keyword_name(ssh_ikev2_packets_payload_to_string_table, 
                               type);
  if (name == NULL)
    return "unknown";

  return name;
}

