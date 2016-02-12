/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2005
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

#ifndef _VMSSL_SDK_H_
#define _VMSSL_SDK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "vmsys.h"



#define VM_SSL_VERIFY_NONE                    0 /* peer certificate is not checked (default), this is insecure and SHOULD be avoided. */
#define VM_SSL_VERIFY_OPTIONAL             1 /* peer certificate is checked, however the 
                                                                handshake continues even if verification failed; */
#define VM_SSL_VERIFY_REQUIRED             2 /* peer *must* present a valid certificate, handshake is aborted if verification failed. */



/* connected status */
#define VM_SSL_EVT_CONNECTED	1

/* write status */
#define VM_SSL_EVT_CAN_WRITE	2

/* read status */
#define VM_SSL_EVT_CAN_READ		3

/* broken status */
#define VM_SSL_EVT_PIPE_BROKEN	4

/* not find host */
#define VM_SSL_EVT_HOST_NOT_FOUND	5

/* tcp pipe closed */
#define VM_SSL_EVT_PIPE_CLOSED	6

/* ssl handshake failed */
#define VM_SSL_EVT_HANDSHAKE_FAILED  7

/* ssl certificate failed */
#define VM_SSL_EVT_CERTIFICATE_VALIDATION_FAILED  8


/*
 * Rteurn Errror Values from Xyssl Library
 */
#define VM_XYSSL_ADP_ERR_SSL_FEATURE_UNAVAILABLE               -0x1000
#define VM_XYSSL_ADP_ERR_SSL_BAD_INPUT_DATA                	-0x1800
#define VM_XYSSL_ADP_ERR_SSL_INVALID_MAC                       -0x2000
#define VM_XYSSL_ADP_ERR_SSL_INVALID_RECORD                	-0x2800
#define VM_XYSSL_ADP_ERR_SSL_INVALID_MODULUS_SIZE          	-0x3000
#define VM_XYSSL_ADP_ERR_SSL_UNKNOWN_CIPHER                    -0x3800
#define VM_XYSSL_ADP_ERR_SSL_NO_CIPHER_CHOSEN                  -0x4000
#define VM_XYSSL_ADP_ERR_SSL_NO_SESSION_FOUND                  -0x4800
#define VM_XYSSL_ADP_ERR_SSL_NO_CLIENT_CERTIFICATE             -0x5000
#define VM_XYSSL_ADP_ERR_SSL_CERTIFICATE_TOO_LARGE             -0x5800
#define VM_XYSSL_ADP_ERR_SSL_CERTIFICATE_REQUIRED              -0x6000
#define VM_XYSSL_ADP_ERR_SSL_BAD_HS_SERVER_HELLO_DONE          -0xC000
#define VM_XYSSL_ADP_ERR_SSL_BAD_HS_CLIENT_KEY_EXCHANGE        -0xC800
#define VM_XYSSL_ADP_ERR_SSL_BAD_HS_CERTIFICATE_VERIFY         -0xD000
#define VM_XYSSL_ADP_ERR_SSL_BAD_HS_CHANGE_CIPHER_SPEC         -0xD800
#define VM_XYSSL_ADP_ERR_SSL_BAD_HS_FINISHED                   -0xE000


/*
*     XYSSL VERIFY RESULT ERROR VALUES
*/
#define VM_XYSSL_ADP_BADCERT_EXPIRED             0x01  /**< The certificate validity has expired. */
#define VM_XYSSL_ADP_BADCERT_REVOKED             0x02  /**< The certificate has been revoked (is on a CRL). */
#define VM_XYSSL_ADP_BADCERT_CN_MISMATCH         0x04  /**< The certificate Common Name (CN) does not match with the expected CN. */
#define VM_XYSSL_ADP_BADCERT_NOT_TRUSTED         0x08  /**< The certificate is not correctly signed by the trusted CA. */


/*
*     XYSSL X509 ERROR VALUES
*/
#define VM_XYSSL_ADP_ERR_X509_FEATURE_UNAVAILABLE              -0x0020
#define VM_XYSSL_ADP_ERR_X509_CERT_INVALID_PEM                 -0x0040
#define VM_XYSSL_ADP_ERR_X509_CERT_INVALID_FORMAT              -0x0060
#define VM_XYSSL_ADP_ERR_X509_CERT_INVALID_VERSION             -0x0080
#define VM_XYSSL_ADP_ERR_X509_CERT_INVALID_SERIAL              -0x00A0
#define VM_XYSSL_ADP_ERR_X509_CERT_INVALID_ALG                 -0x00C0
#define VM_XYSSL_ADP_ERR_X509_CERT_INVALID_NAME                -0x00E0
#define VM_XYSSL_ADP_ERR_X509_CERT_INVALID_DATE                -0x0100
#define VM_XYSSL_ADP_ERR_X509_CERT_INVALID_PUBKEY              -0x0120
#define VM_XYSSL_ADP_ERR_X509_CERT_INVALID_SIGNATURE           -0x0140
#define VM_XYSSL_ADP_ERR_X509_CERT_INVALID_EXTENSIONS          -0x0160
#define VM_XYSSL_ADP_ERR_X509_CERT_UNKNOWN_VERSION             -0x0180
#define VM_XYSSL_ADP_ERR_X509_CERT_UNKNOWN_SIG_ALG             -0x01A0
#define VM_XYSSL_ADP_ERR_X509_CERT_UNKNOWN_PK_ALG              -0x01C0
#define VM_XYSSL_ADP_ERR_X509_CERT_SIG_MISMATCH                -0x01E0
#define VM_XYSSL_ADP_ERR_X509_CERT_VERIFY_FAILED               -0x0200
#define VM_XYSSL_ADP_ERR_X509_KEY_INVALID_PEM                  -0x0220
#define VM_XYSSL_ADP_ERR_X509_KEY_INVALID_VERSION              -0x0240
#define VM_XYSSL_ADP_ERR_X509_KEY_INVALID_FORMAT               -0x0260
#define VM_XYSSL_ADP_ERR_X509_KEY_INVALID_ENC_IV               -0x0280
#define VM_XYSSL_ADP_ERR_X509_KEY_UNKNOWN_ENC_ALG              -0x02A0
#define VM_XYSSL_ADP_ERR_X509_KEY_PASSWORD_REQUIRED            -0x02C0
#define VM_XYSSL_ADP_ERR_X509_KEY_PASSWORD_MISMATCH            -0x02E0
#define VM_XYSSL_ADP_ERR_X509_POINT_ERROR                      -0x0300
#define VM_XYSSL_ADP_ERR_X509_VALUE_TO_LENGTH                  -0x0320


/*
*    XYSSL BASE64 ERROR VALUES
*/
#define XYSSL_ADP_ERR_BASE64_BUFFER_TOO_SMALL               -0x0010
#define XYSSL_ADP_ERR_BASE64_INVALID_CHARACTER              -0x0012




/*
*     XYSSL VERIFY RESULT ERROR VALUES
*/
#define XYSSL_ADP_BADCERT_EXPIRED             0x01  /**< The certificate validity has expired. */
#define XYSSL_ADP_BADCERT_REVOKED             0x02  /**< The certificate has been revoked (is on a CRL). */
#define XYSSL_ADP_BADCERT_CN_MISMATCH         0x04  /**< The certificate Common Name (CN) does not match with the expected CN. */
#define XYSSL_ADP_BADCERT_NOT_TRUSTED         0x08  /**< The certificate is not correctly signed by the trusted CA. */


typedef struct _vm_ssl_cntx{
    VMCHAR* host;                                                 /* host to which connection will be made */
    VMINT port;                                                       /* port at which connection will be made */
    void (*connection_callback)(VMINT handle, VMINT event);     /* callback funtion to notify app about actions, like in vm_tcp_connect */
    VMINT authmod;                                                /* what type of certification verification is required: NONE, OPTIONAL, REQUIRED */
    VMCHAR *ua;
}vm_ssl_cntx;

/*****************************************************************************
 * FUNCTION
 *   vm_ssl_is_support
 * DESCRIPTION
 *   query if ssl be supported 
 * PARAMETERS
 *  void
 * RETURNS
 *  non-zero value if successfully, else not support. 
*****************************************************************************/
VMINT vm_ssl_is_support(void);


/*****************************************************************************
 * FUNCTION
 *   vm_ssl_connect
 * DESCRIPTION
 *   create a ssl connection 
 * PARAMETERS
 *  ctx : [IN]  ssl context, refer to vm_ssl_cntx
 * RETURNS
 *  non-negative handle if successfully, and error code if failed to create. 
*****************************************************************************/
VMINT vm_ssl_connect(const vm_ssl_cntx *ctx);


/*****************************************************************************
 * FUNCTION
 *   vm_ssl_load_ca_chain_cert
 * DESCRIPTION
 *   load ca_chain certification 
 * PARAMETERS
 *  handle : [IN]  ssl handle
 *  cert_buf : [IN]  cert data, the raw data get from resource of app 
 *  buf_len : [IN]  length of cert data.
 * RETURNS
 *  0 if successfully, else failed. 
 * RETURN VALUES
 *  XYSSL X509 ERROR VALUES
*****************************************************************************/
VMINT vm_ssl_load_ca_chain_cert(VMINT handle, const void *cert_buf, VMINT buf_len);

/*****************************************************************************
 * FUNCTION
 *  vm_ssl_read
 * DESCRIPTION
 *  read data from ssl connection.
 * PARAMETERS
 *  handle : [IN] ssl handle.
 *  buf : [OUT] data buffer.
 *  len : [IN] data length.
 * RETURNS
 *  read data size.
 * RETURN VALUES
 *  read size
*****************************************************************************/
VMINT vm_ssl_read(VMINT handle, VMUINT8 *buf, VMINT len);  


/*****************************************************************************
 * FUNCTION
 *  vm_ssl_write
 * DESCRIPTION
 *  write data from ssl connection.
 * PARAMETERS
 *  handle : [IN] ssl handle.
 *  buf : [OUT] data buffer.
 *  len : [IN] data length.
 * RETURNS
 *  read data size.
 * RETURN VALUES
 *  read size
*****************************************************************************/
VMINT vm_ssl_write(VMINT handle, const VMUINT8 *buf, VMINT len);


/*****************************************************************************
 * FUNCTION
 *   vm_ssl_close
 * DESCRIPTION
 *  close ssl connection.
 * PARAMETERS
 *  handle : [IN] ssl handle.
*****************************************************************************/
VMINT vm_ssl_close(VMINT handle);     

/*****************************************************************************
 * FUNCTION
 *   vm_ssl_get_verify_result
 * DESCRIPTION
 *  get the verify result.
 * PARAMETERS
 *  handle : [IN] ssl handle.
 * RETURNS
 *  result
 * RETURN VALUES
 *  0 if successful, or a combination of:
 *  XYSSL VERIFY RESULT ERROR VALUES
*****************************************************************************/
VMINT vm_ssl_get_verify_result(VMINT handle);     


/*****************************************************************************
 * FUNCTION
 *  vm_ssl_base64_encode
 *  Call this function with *dlen = 0 to obtain the required buffer size in *dlen
 * DESCRIPTION
 *  base64 encode.
 * PARAMETERS
 *  dst : [OUT] destination buffer.
 *  dlen : [OUT] size of the buffer.
 *  src : [IN] source buffer.
 *  slen : [IN] amount of data to be encoded.
 * RETURNS
 *  result
 * RETURN VALUES
 *  0 if successful, or XYSSL_ERR_BASE64_BUFFER_TOO_SMALL.
 *  *dlen is always updated to reflect the amount of data that has (or would have) been written.
*****************************************************************************/
VMINT vm_ssl_base64_encode(VMBYTE *dst, VMINT *dlen, VMBYTE *src, VMINT slen);     

/*****************************************************************************
* FUNCTION
*  vm_ssl_base64_decode
*  Call this function with *dlen = 0 to obtain the required buffer size in *dlen
* DESCRIPTION
*  base64 decode.
* PARAMETERS
*  dst : [OUT] destination buffer.
*  dlen : [OUT] size of the buffer.
*  src : [IN] source buffer.
*  slen : [IN] amount of data to be decoded.
* RETURNS
*  result
* RETURN VALUES
*  0 if successful, XYSSL_ERR_BASE64_BUFFER_TOO_SMALL, or
*  XYSSL_ERR_BASE64_INVALID_DATA if the input data is not
*  correct. *dlen is always updated to reflect the amount
*  of data that has (or would have) been written.
*****************************************************************************/
VMINT vm_ssl_base64_decode(VMBYTE *dst, VMINT *dlen, VMBYTE *src, VMINT  slen);   

/*****************************************************************************
* FUNCTION
*   vm_ssl_sha1_hmac
* DESCRIPTION
*  get the verify result.
* PARAMETERS
*  key : [IN] HMAC secret key.
*  keylen : [IN] length of the HMAC key.
*  input : [IN] buffer holding the  data.
*  ilen : [IN] length of the input data.
*  output : [OUT] HMAC-SHA-1 result.
* RETURNS
*  result
*****************************************************************************/
VMINT vm_ssl_sha1_hmac(VMBYTE *key, VMINT keylen, VMBYTE *input, VMINT ilen, VMBYTE output[20]);     

#ifdef __cplusplus
}
#endif

#endif /*_VMSSL_SDK_H_*/

