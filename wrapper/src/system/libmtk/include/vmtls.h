/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2006
*
*  BY OPENING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
*  THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
*  RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO BUYER ON
*  AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
*  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
*  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
*  NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
*  SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
*  SUPPLIED WITH THE MEDIATEK SOFTWARE, AND BUYER AGREES TO LOOK ONLY TO SUCH
*  THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO
*  NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S
*  SPECIFICATION OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
*
*  BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE
*  LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
*  AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
*  OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY BUYER TO
*  MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE. 
*
*  THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE
*  WITH THE LAWS OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT OF
*  LAWS PRINCIPLES.  ANY DISPUTES, CONTROVERSIES OR CLAIMS ARISING THEREOF AND
*  RELATED THERETO SHALL BE SETTLED BY ARBITRATION IN SAN FRANCISCO, CA, UNDER
*  THE RULES OF THE INTERNATIONAL CHAMBER OF COMMERCE (ICC).
*
*****************************************************************************/

#ifndef VM_TLS_SDK_H
#define VM_TLS_SDK_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "vmsys.h"
#include "vmsock.h"

typedef enum {
    VM_TLS_ERR_NONE                   = 0,   /* No error. */
    VM_TLS_ERR_WOULDBLOCK             = -1,  /* Operation cannot complete now. */
    VM_TLS_ERR_NO_FREE_CTX            = -2,  /* No free global context slots. */
    VM_TLS_ERR_NO_MEMORY              = -3,  /* Allocate memory failed. */
    VM_TLS_ERR_INVALID_CONTEXT        = -4,  /* Invalid global context id. */
    VM_TLS_ERR_INVALID_CIPHER         = -5,  /* Invalid cipher enum value. */
    VM_TLS_ERR_EXCESS_MAX_CIPHERS     = -6,  /* Too many ciphers. */
    VM_TLS_ERR_INVALID_PARAMS         = -7,  /* Invalid parameter. */
    VM_TLS_ERR_INVALID_ROOT_CERT      = -8,  /* Invalid root certificate id. */
    VM_TLS_ERR_INVALID_PRIV_KEY       = -9,  /* Invalid private key id. */
    VM_TLS_ERR_INVALID_PERSONAL_CERT  = -10, /* Invalid personal certificate id. */
    VM_TLS_ERR_INVALID_FILE_TYPE      = -11, /* Invalid file encoding type. */
    VM_TLS_ERR_INVALID_AUTH_MODE      = -12, /* Invalid client auth mode. */
    VM_TLS_ERR_EXCESS_MAX_AUTH_MODES  = -13, /* Too many client auth modes. */
    VM_TLS_ERR_ALREADY                = -14, /* The operation is progressing. */
    VM_TLS_ERR_HANDSHAKED             = -15, /* Handshaked completed. */
    VM_TLS_ERR_INVALID_SOCK_ID        = -16, /* Invalid socket id. */
    VM_TLS_ERR_NO_CONN_CTX            = -17, /* No associated connection context. */
    VM_TLS_ERR_HANDSHAKING            = -18, /* Opreation denied when connection is handshaking. */
    VM_TLS_ERR_REHANDSHAKING          = -19, /* Connection is rehandshaking. */
    VM_TLS_ERR_REHANDSHAKED           = -20, /* TLS auto re-handshaked completed. */
    VM_TLS_ERR_SHUTDOWNED             = -21, /* Opreation denied when connection is shutdowned. */
    VM_TLS_ERR_REQ_HANDSHAKE          = -22, /* TLS peer requested handshake. */
    VM_TLS_ERR_NEED_HANDSHAKE         = -23, /* Need handshake first. */
    VM_TLS_ERR_REHANDSHAKE_REJ        = -24, /* Peer rejects our renegotiation, connection still valid. */
    VM_TLS_ERR_CONN_CLOSED            = -25, /* Connection closed by peer. */
    VM_TLS_ERR_IO_ERROR               = -26, /* Lower-layer IO error. */
    VM_TLS_ERR_OP_DENIED              = -27, /* Operation denied due to incorrect state. */
    VM_TLS_ERR_READ_REQUIRED          = -28, /* Application data need to be read before processing rehandshake. */
    VM_TLS_ERR_CERT_VALIDATE          = -29, /* Certificate validation failed. */
    VM_TLS_ERR_PRNG_FAIL              = -30, /* Set PRNG failed. */
    VM_TLS_ERR_WAITING_CERT           = -32, /* Waiting certificate confirm from CERTMAN. */
    VM_TLS_ERR_FILESYS                = -33, /* File system operation failed. */
    VM_TLS_ERR_TASK_NOT_READY         = -34, /* TLS task not ready, waiting for CERTMAN confirm message. */
    VM_TLS_ERR_SSL_INTERNAL           = -100,/* SSL layer internal error. */
    VM_TLS_ERR_SOC_INTERNAL           = -101,/* Socket layer internal error. */
    VM_TLS_ERR_CERTMAN_INTERNAL       = -102 /* Certman internal error. */
} vm_tls_error_enum;

typedef enum {
    VM_TLS_ALL_VERSIONS = 0, /* ALL supported SSL/TLS versions */
    VM_SSLv2 = 0x01u << 0,   /* SSLv2 */
    VM_SSLv3 = 0x01u << 1,   /* SSLv3 */
    VM_TLSv1 = 0x01u << 2,   /* TLSv1 */
    VM_TLS_UNKNOWN_VERSION = 0xffu /* Unknown */
} vm_tls_version_enum;

typedef enum {
    VM_TLS_CLIENT_SIDE = 0, /* Client side */
    VM_TLS_SERVER_SIDE = 1  /* Server side */
} vm_tls_side_enum;

typedef enum {
    VM_TLS_NULL_MD5                = 0,  /* 0x0001, TLS_RSA_WITH_NULL_MD5. */
    VM_TLS_EXP_RC4_MD5             = 1,  /* 0x0003, TLS_RSA_EXPORT_WITH_RC4_40_MD5.(*) */
    VM_TLS_RC4_MD5                 = 2,  /* 0x0004, TLS_RSA_WITH_RC4_128_MD5. */
    VM_TLS_RC4_SHA                 = 3,  /* 0x0005, TLS_RSA_WITH_RC4_128_SHA, TLS Profile MUST. */
    VM_TLS_EXP_DES_CBC_SHA         = 4,  /* 0x0008, TLS_RSA_EXPORT_WITH_DES40_CBC_SHA.(*) */
    VM_TLS_DES_CBC_SHA             = 5,  /* 0x0009, TLS_RSA_WITH_DES_CBC_SHA. */
    VM_TLS_DES_CBC3_SHA            = 6,  /* 0x000A, TLS_RSA_WITH_3DES_EDE_CBC_SHA, TLS Profile MUST. */
    VM_TLS_EXP_EDH_DSS_DES_CBC_SHA = 7,  /* 0x0011, TLS_DHE_DSS_EXPORT_WITH_DES40_CBC_SHA.(*) */
    VM_TLS_EDH_DSS_CBC_SHA         = 8,  /* 0x0012, TLS_DHE_DSS_WITH_DES_CBC_SHA. */
    VM_TLS_EDH_DSS_DES_CBC3_SHA    = 9,  /* 0x0013, TLS_DHE_DSS_WITH_3DES_EDE_CBC_SHA. */
    VM_TLS_EXP_EDH_RSA_DES_CBC_SHA = 10, /* 0x0014, TLS_DHE_RSA_EXPORT_WITH_DES40_CBC_SHA.(*) */
    VM_TLS_EDH_RSA_DES_CBC_SHA     = 11, /* 0x0015, TLS_DHE_RSA_WITH_DES_CBC_SHA. */
    VM_TLS_EDH_RSA_DES_CBC3_SHA    = 12, /* 0x0016, TLS_DHE_RSA_WITH_3DES_EDE_CBC_SHA. */
    VM_TLS_EXP_ADH_RC4_MD5         = 13, /* 0x0017, TLS_DH_anon_EXPORT_WITH_RC4_40_MD5.(*) */
    VM_TLS_ADH_RC4_MD5             = 14, /* 0x0018, TLS_DH_anon_WITH_RC4_128_MD5. */
    VM_TLS_EXP_ADH_DES_CBC_SHA     = 15, /* 0x0019, TLS_DH_anon_EXPORT_WITH_DES40_CBC_SHA.(*) */
    VM_TLS_ADH_DES_CBC_SHA         = 16, /* 0x001A, TLS_DH_anon_WITH_DES_CBC_SHA. */
    VM_TLS_ADH_DES_CBC3_SHA        = 17, /* 0x001B, TLS_DH_anon_WITH_3DES_EDE_CBC_SHA. */
 
    VM_TLS_AES128_SHA              = 18, /* 0x002F, TLS_RSA_WITH_AES_128_CBC_SHA. */
    VM_TLS_AES256_SHA              = 19, /* 0x0035, TLS_RSA_WITH_AES_256_CBC_SHA. */

    VM_TLS_EXP1024_DES_CBC_SHA     = 20, /* 0x0062, TLS_RSA_EXPORT1024_WITH_DES_CBC_SHA. */
    VM_TLS_EXP1024_RC4_SHA         = 21, /* 0x0064, TLS_RSA_EXPORT1024_WITH_RC4_56_SHA. */
    VM_TLS_DHE_DSS_RC4_SHA         = 22, /* 0x0066, TLS_DHE_DSS_WITH_RC4_128_SHA. */

    VM_TLS_ECDH_SECT163K1_RC4_SHA  = 23, /* 0xC002 in RFC 4492, TLS_ECDH_ECDSA_WITH_RC4_128_SHA. */
    VM_TLS_ECDH_SECT163K1_NULL_SHA = 24, /* 0xC001 in RFC 4492, TLS_ECDH_ECDSA_WITH_NULL_SHA. */

    VM_TLS_PSK_AES128_SHA          = 25, /* 0x008C in RFC 4279, TLS_PSK_WITH_AES_128_CBC_SHA. */
    VM_TLS_PSK_DES_CBC3_SHA        = 26, /* 0x008B in RFC 4279, TLS_PSK_WITH_3DES_EDE_CBC_SHA. */
    VM_TLS_UNKNOWN_CIPHER,
    VM_TLS_TOTAL_CIPHER_NUM = VM_TLS_UNKNOWN_CIPHER
} vm_tls_cipher_enum ;

typedef enum {
    VM_TLS_NULL_WITH_NULL_NULL                = 0x0000, /* (NULL, NULL, NULL)*/

    VM_TLS_RSA_WITH_NULL_MD5                  = 0x0001, /* (RSA, NULL, MD5) */
    VM_TLS_RSA_WITH_NULL_SHA                  = 0x0002, /* (RSA, NULL, SHA) */
    VM_TLS_RSA_EXPORT_WITH_RC4_40_MD5         = 0x0003, /* (RSA_EXPORT, RC4_40), MD5, TLS 1.0 */
    VM_TLS_RSA_WITH_RC4_128_MD5               = 0x0004, /* (RSA, RC4_128, MD5) */
    VM_TLS_RSA_WITH_RC4_128_SHA               = 0x0005, /* (RSA, RC4_128, SHA) */
    VM_TLS_RSA_EXPORT_WITH_RC2_CBC_40_MD5     = 0x0006, /* (RSA_EXPORT, RC2_CBC_40, MD5), TLS 1.0 */
    VM_TLS_RSA_WITH_IDEA_CBC_SHA              = 0x0007, /* (RSA, IDEA_CBC, SHA) */
    VM_TLS_RSA_EXPORT_WITH_DES40_CBC_SHA      = 0x0008, /* (RSA_EXPORT, DES40_CBC, SHA), TLS 1.0 */
    VM_TLS_RSA_WITH_DES_CBC_SHA               = 0x0009, /* (RSA, DES_CBC, SHA) */
    VM_TLS_RSA_WITH_3DES_EDE_CBC_SHA          = 0x000A, /* (RSA, 3DES_EDE_CBC, SHA) */

    VM_TLS_DH_DSS_EXPORT_WITH_DES40_CBC_SHA   = 0x000B, /* (DH_DSS_EXPORT, DES40_CBC, SHA), TLS 1.0 */
    VM_TLS_DH_DSS_WITH_DES_CBC_SHA            = 0x000C, /* (DH_DSS, DES_CBC, SHA) */
    VM_TLS_DH_DSS_WITH_3DES_EDE_CBC_SHA       = 0x000D, /* (DH_DSS, 3DES_EDE_CBC, SHA) */
    VM_TLS_DH_RSA_EXPORT_WITH_DES40_CBC_SHA   = 0x000E, /* (DH_RSA_EXPORT, DES40_CBC, SHA), TLS 1.0 */
    VM_TLS_DH_RSA_WITH_DES_CBC_SHA            = 0x000F, /* (DH_RSA, DES_CBC, SHA) */
    VM_TLS_DH_RSA_WITH_3DES_EDE_CBC_SHA       = 0x0010, /* (DH_RSA, 3DES_EDE_CBC, SHA) */
    VM_TLS_DHE_DSS_EXPORT_WITH_DES40_CBC_SHA  = 0x0011, /* (DHE_DSS_EXPORT, DES40_CBC, SHA), TLS 1.0 */
    VM_TLS_DHE_DSS_WITH_DES_CBC_SHA           = 0x0012, /* (DHE_DSS, DES_CBCi, SHA) */
    VM_TLS_DHE_DSS_WITH_3DES_EDE_CBC_SHA      = 0x0013, /* (DHE_DSS, 3DES_EDE_CBC, SHA) */
    VM_TLS_DHE_RSA_EXPORT_WITH_DES40_CBC_SHA  = 0x0014, /* (DHE_RSA_EXPORT, DES40_CBC, SHA), TLS 1.0 */
    VM_TLS_DHE_RSA_WITH_DES_CBC_SHA           = 0x0015, /* (DHE_RSA, DES_CBCi, SHA) */
    VM_TLS_DHE_RSA_WITH_3DES_EDE_CBC_SHA      = 0x0016, /* (DHE_RSA, 3DES_EDE_CBC, SHA) */

    VM_TLS_DH_anon_EXPORT_WITH_RC4_40_MD5     = 0x0017, /* (DH_anon_EXPORT, RC4_40, MD5), TLS 1.0 */
    VM_TLS_DH_anon_WITH_RC4_128_MD5           = 0x0018, /* (DH_anon, RC4_128, MD5) */
    VM_TLS_DH_anon_EXPORT_WITH_DES40_CBC_SHA  = 0x0019, /* (DH_anon, DES40_CBC, SHA), TLS 1.0 */
    VM_TLS_DH_anon_WITH_DES_CBC_SHA           = 0x001A, /* (DH_anon, DES_CBC, SHA) */
    VM_TLS_DH_anon_WITH_3DES_EDE_CBC_SHA      = 0x001B, /* (DH_anon, DES_CBC, SHA) */

    VM_TLS_KRB5_WITH_DES_CBC_SHA              = 0x001E, /* (Kerberos, DES_CBC, SHA) */
    VM_TLS_KRB5_WITH_3DES_EDE_CBC_SHA         = 0x001F, /* (Kerberos, 3DES_EDE_CBC, SHA) */
    VM_TLS_KRB5_WITH_RC4_128_SHA              = 0x0020, /* (Kerberos, RC4_128, SHA) */
    VM_TLS_KRB5_WITH_IDEA_CBC_SHA             = 0x0021, /* (Kerberos, IDEA_CBC, SHA) */
    VM_TLS_KRB5_WITH_DES_CBC_MD5              = 0x0022, /* (Kerberos, DES_CBC, MD5) */
    VM_TLS_KRB5_WITH_3DES_EDE_CBC_MD5         = 0x0023, /* (Kerberos, 3DES_EDE_CBC, MD5) */
    VM_TLS_KRB5_WITH_RC4_128_MD5              = 0x0024, /* (Kerberos, RC4_128, MD5) */
    VM_TLS_KRB5_WITH_IDEA_CBC_MD5             = 0x0025, /* (Kerberos, IDEA_CBC, MD5) */

    VM_TLS_KRB5_EXPORT_WITH_DES_CBC_40_SHA    = 0x0026, /* (Kerberos, DES_CBC_40, SHA), MUST NOT */
    VM_TLS_KRB5_EXPORT_WITH_RC2_CBC_40_SHA    = 0x0027, /* (Kerberos, RC2_CBC_40, SHA),  MUST NOT */
    VM_TLS_KRB5_EXPORT_WITH_RC4_40_SHA        = 0x0028, /* (Kerberos, RC4_40, SHA), MUST NOT */
    VM_TLS_KRB5_EXPORT_WITH_DES_CBC_40_MD5    = 0x0029, /* (Kerberos, DES_DBC_40, MD5), MUST NOT */
    VM_TLS_KRB5_EXPORT_WITH_RC2_CBC_40_MD5    = 0x002A, /* (Kerberos, RC2_CBC_40, MD5),  MUST NOT */
    VM_TLS_KRB5_EXPORT_WITH_RC4_40_MD5        = 0x002B, /* (Kerberos, RC4_40, MD5),  MUST NOT */

    VM_TLS_RSA_WITH_AES_128_CBC_SHA           = 0x002F, /* (RSA, AES_128_CBC, SHA) */
    VM_TLS_DH_DSS_WITH_AES_128_CBC_SHA        = 0x0030, /* (DH_DSS, AES_128_CBC, SHA) */
    VM_TLS_DH_RSA_WITH_AES_128_CBC_SHA        = 0x0031, /* (DH_RSA, AES_128_CBC, SHA) */
    VM_TLS_DHE_DSS_WITH_AES_128_CBC_SHA       = 0x0032, /* (DHE_DSS, AES_128_CBC, SHA)  */
    VM_TLS_DHE_RSA_WITH_AES_128_CBC_SHA       = 0x0033, /* (DHE_RSA, AES_128_CBC, SHA) */
    VM_TLS_DH_anon_WITH_AES_128_CBC_SHA       = 0x0034, /* (DH_anon, AES_128_CBC, SHA) */
    VM_TLS_RSA_WITH_AES_256_CBC_SHA           = 0x0035, /* (RSA, AES_256_CBC, SHA) */
    VM_TLS_DH_DSS_WITH_AES_256_CBC_SHA        = 0x0036, /* (DH_DSS, AES_256_CBC, SHA) */
    VM_TLS_DH_RSA_WITH_AES_256_CBC_SHA        = 0x0037, /* (DHE_RSA, AES_256_CBC, SHA) */
    VM_TLS_DHE_DSS_WITH_AES_256_CBC_SHA       = 0x0038, /* (DHE_RSA, AES_256_CBC, SHA) */
    VM_TLS_DHE_RSA_WITH_AES_256_CBC_SHA       = 0x0039, /* (DH_anon, AES_256_CBC, SHA) */
    VM_TLS_DH_anon_WITH_AES_256_CBC_SHA       = 0x003A, /* (DH_anon, AES_256_CBC, SHA) */
    VM_TLS_CIPHER_UNKNOWN                     = 0xFFFF
} vm_tls_ciphersuites_enum;


typedef enum {
    VM_TLS_FILETYPE_PEM = 0, /* PEM encoding */
    VM_TLS_FILETYPE_DER      /* DER encoding */
} vm_tls_filetype_enum;

typedef enum {
    VM_TLS_CLIENT_AUTH_BEGIN,
    VM_TLS_CLIENT_AUTH_RSA_CLIENT, /* RSA client side */
    VM_TLS_CLIENT_AUTH_RSA_SERVER, /* RSA server side */
    VM_TLS_CLIENT_AUTH_DSS_CLIENT, /* DSS(DSA) cient side */
    VM_TLS_CLIENT_AUTH_DSS_SERVER, /* DSS(DSA) server side */
    VM_TLS_CLIENT_AUTH_END = 0xff
} vm_tls_auth_mode_enum;


typedef enum {
    VM_TLS_ENC_ALGO_UNKNOWN,
    VM_TLS_ENC_ALGO_NULL,      /* NULL */

    VM_TLS_ENC_ALGO_DES_40,    /* DES 40 */
    VM_TLS_ENC_ALGO_DES,       /* DES(56) */
    VM_TLS_ENC_ALGO_3DES,      /* 3DES */

    VM_TLS_ENC_ALGO_RC5,       /* RC5 */
    VM_TLS_ENC_ALGO_RC5_56,    /* RC5_56 */

    VM_TLS_ENC_ALGO_AES_128,   /* AES_128 */
    VM_TLS_ENC_ALGO_AES_192,   /* AES_192,  new for OpenSSL */
    VM_TLS_ENC_ALGO_AES_256,   /* AES_256 */

    VM_TLS_ENC_ALGO_ARC4_40,   /* RC4_40 */
    VM_TLS_ENC_ALGO_ARC4_56,   /* RC4_56, new for OpenSSL */
    VM_TLS_ENC_ALGO_ARC4_64,   /* RC4_64, new for OpenSSL */
    VM_TLS_ENC_ALGO_ARC4_128,  /* RC4_128 */

    VM_TLS_ENC_ALGO_ARC2_40,   /* RC2_40 */
    VM_TLS_ENC_ALGO_ARC2_56,   /* RC2_56, new for OpenSSL */
    VM_TLS_ENC_ALGO_ARC2_64,   /* RC4_64 */
    VM_TLS_ENC_ALGO_ARC2_128   /* RC2_128 */
} vm_tls_encryption_enum;

typedef enum {
    VM_TLS_KEY_ALGO_UNKNOWN,
    VM_TLS_KEY_ALGO_RSA,            /* RSA */
    VM_TLS_KEY_ALGO_RSA_EXPORT,     /* RSA_EXPORT */
    VM_TLS_KEY_ALGO_DH,             /* DH */
    VM_TLS_KEY_ALGO_DH_EXPORT,      /* DH_EXPORT */
    VM_TLS_KEY_ALGO_DHE,            /* DH */
    VM_TLS_KEY_ALGO_DHE_EXPORT,     /* DH_EXPORT */
    VM_TLS_KEY_ALGO_ECDH,           /* ECDH */
    VM_TLS_KEY_ALGO_ECDHE,          /* ECDHE */
    VM_TLS_KEY_ALGO_ECMQV,          /* ECMQV */
    VM_TLS_KEY_ALGO_DSA,            /* DSA */
    VM_TLS_KEY_ALGO_PSK,            /* PSK */
    VM_TLS_KEY_ALGO_DHE_PSK,        /* DHE_PSK */
    VM_TLS_KEY_ALGO_RSA_PSK,        /* RSA_PSK */
    VM_TLS_KEY_ALGO_MAX
} vm_tls_key_exchange_enum;

typedef enum {
    VM_TLS_AUTH_ALGO_UNKNOWN,
    VM_TLS_AUTH_ALGO_ANON,      /* ANON */
    VM_TLS_AUTH_ALGO_RSA,       /* RSA */
    VM_TLS_AUTH_ALGO_DSS,       /* DSS */
    VM_TLS_AUTH_ALGO_ECDSA,     /* ECDSA */
    VM_TLS_AUTH_ALGO_PSK        /* PSK */
} vm_tls_auth_enum;

typedef enum {
    VM_TLS_HASH_UNKNOWN,
    VM_TLS_HASH_MD2,       /* MD2 */
    VM_TLS_HASH_MD4,       /* MD4 */
    VM_TLS_HASH_MD5,       /* MD5 */
    VM_TLS_HASH_SHA1,      /* SHA1 */
    VM_TLS_HASH_SHA224,    /* SHA224 */
    VM_TLS_HASH_SHA256,    /* SHA256 */
    VM_TLS_HASH_SHA384,    /* SHA384 */
    VM_TLS_HASH_SHA512     /* SHA512 */
} vm_tls_hash_enum;

typedef struct {
    vm_tls_version_enum version;     /* SSL version number */
    vm_tls_encryption_enum enc;      /* bulk encryption algrotithm */
    vm_tls_key_exchange_enum key_ex; /* key exchange algorithm */
    vm_tls_auth_enum auth;           /* authentication algorithm */
    vm_tls_hash_enum hash;           /* message digest algorithm */
} vm_tls_cipher_info_struct;


/* Socket Type */
typedef enum
{
    VM_SOC_SOCK_STREAM = 0,  /* stream socket, TCP */
    VM_SOC_SOCK_DGRAM,       /* datagram socket, UDP */
    VM_SOC_SOCK_SMS,         /* SMS bearer */
    VM_SOC_SOCK_RAW          /* raw socket */
} vm_socket_type_enum;

typedef enum {
    VM_TLS_HANDSHAKE_READY    = 0x01u << 0, /* The connection is ready for performing handshake. */
    VM_TLS_HANDSHAKE_DONE     = 0x01u << 1, /* Handshake procedure is finished, success or failure. */
    VM_TLS_READ               = 0x01u << 2, /* There is data for reading. */
    VM_TLS_WRITE              = 0x01u << 3, /* There is buffer for writing. */
    VM_TLS_CLOSE              = 0x01u << 4  /* The SSL connection is closed. */
} vm_tls_event_enum;

typedef enum {
    VM_TLS_ALERT_LV_WARNING = 1, /* Warning alert. */
    VM_TLS_ALERT_LV_FATAL = 2    /* Fatal alert, application MUST terminate the connection immediately. */
} vm_tls_alert_level_enum;

typedef enum {
    VM_TLS_ALERT_CLOSE_NOTIFY                = 0,  /* Peer shuts down the connection. */
    VM_TLS_ALERT_UNEXPECTED_MESSAGE          = 10, /* Received an unexped mesage, always a fatal. */
    VM_TLS_ALERT_BAD_RECORD_MAC              = 20, /* Bad MAC, always a fatal. */
    VM_TLS_ALERT_DECRYPTION_FAILED           = 21, /* Decryption failed, always a fatal. */
    VM_TLS_ALERT_RECORD_OVERFLOW             = 22, /* Record size exceeds the limitation, always a fatal. */
    VM_TLS_ALERT_DECOMPRESSION_FAILURE       = 30, /* Deccompression failed, always a fatal. */
    VM_TLS_ALERT_HANDSHAKE_FAILURE           = 40, /* Handshake failed, fatal. */
    VM_TLS_ALERT_NOCERTIFICATE_RESERVED      = 41, /* Response to a certification request if no appropriate certificate is available, SSLv3 only. */
    VM_TLS_ALERT_BAD_CERTIFICATE             = 42, /* A certificate was corrupt, signatures that did not verify correctly. */
    VM_TLS_ALERT_UNSUPPORTED_CERTIFICATE     = 43, /* Unsupported certificate type. */
    VM_TLS_ALERT_CERTIFICATE_REVOKED         = 44, /* Received a revoked certificate from peer. */
    VM_TLS_ALERT_CERTIFICATE_EXPIRED         = 45, /* A certificate has expired or not yet valid. */
    VM_TLS_ALERT_CERTIFICATE_UNKNOWN         = 46, /* Some unspecificate issue in processing the certificate.  */
    VM_TLS_ALERT_ILLEGAL_PARAMETER           = 47, /* Illegal parameter in the message, always a fatal. */
    VM_TLS_ALERT_UNKNOWN_CA                  = 48, /* The certificate chain cannot be verified successfully due to untrusted CA, always a fatal. */
    VM_TLS_ALERT_ACCESS_DENIED               = 49, /* sender decided not to proceed with negotiation when access control was applied, always a fatal. */
    VM_TLS_ALERT_DECODE_ERROR                = 50, /* The field in a message is incorrect, always a fatal. */
    VM_TLS_ALERT_DECRYPT_ERROR               = 51, /* a handshake cryptographic operation failed, including verify a signature, decrypt a key exchange, or validate a finished mesasge. */
    VM_TLS_ALERT_EXPORT_RESTRICTION_RESERVED = 60, /* A negotiation not in compliance with export restrictions was detected. */
    VM_TLS_ALERT_PROTOCOL_VERSION            = 70, /* The protocol version proposed by client is not supported by server side, always a fatal. */
    VM_TLS_ALERT_INSUFFICIENT_SECURITY       = 71, /* The server requires cphers more secure than those supported by the client, always a fatal. */
    VM_TLS_ALERT_INTERNAL_ERROR              = 80, /* An internal error unrelated to the peer, always a fatal. */
    VM_TLS_ALERT_USER_CANCELLED              = 90, /* The handshake is canceled for some reason unrelated to a protocol failure, generally a warning. */
    VM_TLS_ALERT_NO_RENEGOTIATION            = 100 /* When peer suggest to renegotiate again but local rejects it, always a warning. */
} vm_tls_alert_desc_enum;

typedef enum {
    VM_TLS_USER_REJECT          = 0, /* User rejects the invalid certificate. */
    VM_TLS_USER_ACCEPT_ONCE     = 1, /* User accepts the invalid certificate for this time */
    VM_TLS_USER_ACCEPT_FOREVER  = 2  /* User accepts the invalid cert forever */
} vm_tls_inval_cert_action;

typedef struct
{
    vm_socket_type_enum	sock_type; /* socket type */
    VMINT16	addr_len; /* address length */
    VMUINT16	port; /* port number */
    VMUINT8	addr[VM_MAX_SOCK_ADDR_LEN];
}vm_sockaddr_ex_struct;

typedef struct {
    VMUINT32 len;   /* The size of the certificate in bytes */
    VMUINT8 *data;  /* Data of the certficate in DER format */
} vm_tls_cert_struct;

#define VM_MSG_ID_APP_SOC_NOTIFY_IND 0
#define VM_MSG_ID_APP_TLS_NOTIFY_IND 1
#define VM_MSG_ID_APP_TLS_ALERT_IND 2
#define VM_MSG_ID_APP_TLS_INVALID_CERT_IND 3
#define VM_MSG_ID_APP_TLS_CLIENT_AUTH_IND 4

#define VM_TLS_EVT_PARAM_HEADER \
    VMINT msg; \
    VMINT res_id; \
    VMINT soc_id
    
typedef struct 
{
    VM_TLS_EVT_PARAM_HEADER;
}vm_tls_event_struct;


/* event */
typedef enum
{
    VM_SOC_READ    = 0x01,  /* Notify for read */
    VM_SOC_WRITE   = 0x02,  /* Notify for write */
    VM_SOC_ACCEPT  = 0x04,  /* Notify for accept */
    VM_SOC_CONNECT = 0x08,  /* Notify for connect */
    VM_SOC_CLOSE   = 0x10   /* Notify for close */
} vm_soc_event_enum;

typedef struct
{
    VM_TLS_EVT_PARAM_HEADER;
    vm_soc_event_enum  event_type;   /* vm_soc_event_enum */
    VMINT result;       /* notification result. KAL_TRUE: success, KAL_FALSE: error */
    VMINT error_cause;  /* vm_soc_error_enum used only when EVENT is close/connect */
    VMINT detail_cause; /* refer to ps_cause_enum if error_cause is
                                  * VM_SOC_BEARER_FAIL */
}vm_tls_soc_notify_ind_struct;

/***************************************************************************
 * <GROUP Structures>
 *
 * Indication to app for a common event.
 * Local parameter of MSG_ID_APP_TLS_NOTIFY_IND.
 ***************************************************************************/
typedef struct
{
    VM_TLS_EVT_PARAM_HEADER;
    vm_tls_event_enum  event;         /* Reported event from TLS task.
    Applications should verifiy the event type and calls the corresponding
    handler.

    * VM_TLS_HANDSHAKE_READY is an indication of the result of connection context
    creation procedure. vm_tls_new_conn() might return TLS_ERR_WAITING_CERT for
    loading certificates and waiting response from MOD_CERTMAN. After received
    this message, application can then call vm_tls_handshake() to start TLS
    handshake procedure.

    * VM_TLS_HANDSHAKE_DONE is an indication of the handshake result procedure.
    Application can call vm_tls_read() to receive data from or call tls_write() to
    send data to the peer.

    * For VM_TLS_READ, application should call vm_tls_read() repeatedly until
    WOULDBLOCK returned.

    * For VM_TLS_WRITE, application is allowed to transmit the holding data by
    calling vm_tls_write().

    * For VM_TLS_CLOSE, application should call vm_tls_delete_conn() to de-associate
    the connection with a socket id.
    */
    VMINT        result;        /* Success or failure of the notification. */
    VMINT       error;         /* Error code. */
    VMINT       detail_cause;  /* Detail error cause. */
} vm_tls_notify_ind_struct;

/***************************************************************************
 * <GROUP Structures>
 *
 * Indication to app for received an alert from peer.
 * Local parameter of MSG_ID_APP_TLS_ALERT_IND.
 ***************************************************************************/
typedef struct
{
    VM_TLS_EVT_PARAM_HEADER;
    vm_tls_alert_level_enum  alert_level;  /* Alert level. */
    vm_tls_alert_desc_enum   alert_desc;   /* Alert description. */
    VMINT             error;        /* Error code. */
    VMINT             cause;        /* Detail error cause. */
} vm_tls_alert_ind_struct;

/***************************************************************************
 * <GROUP Structures>
 *
 * Indication of invalid certificate.
 * Local parameter of MSG_ID_APP_TLS_INVALID_CERT_IND.
 ***************************************************************************/
typedef struct
{
    VM_TLS_EVT_PARAM_HEADER;
    VMINT        result;        /* TRUE: user confirms to proceed the handshake against the received invalid certificate */
    vm_tls_inval_cert_action action;  /* User's decision */
} vm_tls_invalid_cert_ind_struct;

#define VM_TLS_MAX_CLIENT_AUTH         (7)
/***************************************************************************
 * <GROUP Structures>
 *
 * Indication of client authentication request freom server.
 * Local parameter of MSG_ID_APP_TLS_CLIENT_AUTH_IND.
 ***************************************************************************/
typedef struct
{
    VM_TLS_EVT_PARAM_HEADER;
    VMINT            result;    /* TRUE: user selects a positive answer to the client authentication */
    VMINT           auth_mode_num; /* auth modes in the following auth_modes array */
    vm_tls_auth_mode_enum  auth_modes[VM_TLS_MAX_CLIENT_AUTH]; /* authmodes in the certificate request message from server */
    VMUINT          identity_id;   /* user selected certificate id.  This field would be zero if no user certificate meets the criteria in the certificate request message. */
} vm_tls_client_auth_ind_struct;

typedef void (*callback_t)(vm_tls_event_struct * data);


VMINT vm_tls_new_ctx(vm_tls_version_enum ver, vm_socket_type_enum sock_type, VMINT apn, vm_tls_side_enum side, callback_t cb);
VMINT vm_tls_delete_ctx(VMINT res_id);
VMINT vm_tls_set_ciphers(VMINT res_id, const vm_tls_cipher_enum ciphers[], VMINT num);
VMINT vm_tls_set_verify(VMINT res_id, VMUINT32 cert_id[], VMINT cert_num, vm_tls_filetype_enum type);
VMINT vm_tls_set_client_auth(VMINT res_id, vm_tls_auth_mode_enum modes[], VMINT num);
VMINT vm_tls_set_identity(VMINT res_id, VMUINT32 cert_id);

VMINT vm_tls_new_conn(VMINT res_id, vm_sockaddr_ex_struct * faddr);
VMINT vm_tls_delete_conn(VMINT res_id);
VMINT vm_tls_get_cipher(VMINT res_id, vm_tls_ciphersuites_enum *cipher);
VMINT vm_tls_get_cipher_info(VMINT res_id, vm_tls_cipher_info_struct *cipher_info);
VMINT vm_tls_get_peer_cert(VMINT res_id, vm_tls_cert_struct *cert);
VMINT vm_tls_check_invalid_cert(VMINT res_id, VMINT onoff);
VMINT vm_tls_set_null_client_auth(VMINT res_id);
VMINT vm_tls_check_peer_name(VMINT res_id, const VMCHAR * name);
VMINT vm_tls_auto_rehandshake(VMINT res_id, VMINT onoff);
VMINT vm_tls_handshake(VMINT res_id);
VMINT vm_tls_rehandshake(VMINT res_id);
VMINT vm_tls_read(VMINT res_id, void* buf, VMINT32 len);
VMINT vm_tls_write(VMINT res_id, const void* buf, VMINT32 len);
VMINT vm_tls_shutdown(VMINT res_id);
VMINT vm_tls_connect(VMINT res_id, vm_sockaddr_ex_struct * faddr);
VMINT vm_tls_soc_connect(VMINT res_id, vm_sockaddr_ex_struct * faddr);
VMINT vm_tls_log_plaintext(VMINT onoff);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* VM_TLS_SDK_H */

