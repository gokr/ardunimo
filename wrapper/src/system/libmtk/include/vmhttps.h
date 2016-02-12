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
 
#ifndef VMHTTPS_SDK_H
#define VMHTTPS_SDK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "vmsys.h"

/*************************************************************************
 * WPS SERVICE  -- MACRO's And Typedef's structure definition
 ************************************************************************/

#define MRE_WPS_MAX_CONTENT_TYPE_LEN        256

/* Connection type constants */

#define MRE_WPS_CONN_TYPE_HTTP    1         
#define MRE_WPS_CONN_TYPE_WSP_CL  2         
#define MRE_WPS_CONN_TYPE_WSP_CO  3         
#define MRE_WPS_CONN_TYPE_TLS     4         

/* HTTP method constants */

#define MRE_WPS_HTTP_METHOD_GET     0x40    
#define MRE_WPS_HTTP_METHOD_HEAD    0x42    
#define MRE_WPS_HTTP_METHOD_POST    0x60   
#define MRE_WPS_HTTP_METHOD_PUT     0x61    
#define MRE_WPS_HTTP_METHOD_DELETE  0x43    

/* HTTP request options */

#define MRE_WPS_HTTP_OPTION_NO_CACHE                  0x00000001  
#define MRE_WPS_HTTP_OPTION_DO_NOT_CACHE_REPLY        0x00000002  
#define MRE_WPS_HTTP_OPTION_ALWAYS_CACHE              0x00000004  
#define MRE_WPS_HTTP_OPTION_CACHE_ONLY                0x00000008  
#define MRE_WPS_HTTP_OPTION_STALE_CACHE               0x00000010  
#define MRE_WPS_HTTP_OPTION_DO_NOT_HANDLE_SERVER_AUTH 0x00008000  
#define MRE_WPS_HTTP_OPTION_DO_NOT_HANDLE_PROXY_AUTH  0x00010000  
#define MRE_WPS_HTTP_OPTION_DO_NOT_REDIRECT           0x00020000  
#define MRE_WPS_HTTP_OPTION_USE_LARGE_PIPE            0x40000000  
#define MRE_WPS_HTTP_OPTION_FS_COMMIT                 0x80000000  
#define MRE_WPS_HTTP_OPTION_NO_NOT_ADD_COOKIE 0x00400000

/* HTTP authentication constants */

#define MRE_WPS_HTTP_AUTH_SERVER                 1  
#define MRE_WPS_HTTP_AUTH_PROXY                  2  

#define MRE_WPS_HTTP_AUTH_TYPE_BASIC             1
#define MRE_WPS_HTTP_AUTH_TYPE_DIGEST            2


/* Protocol constants */

#define MRE_WPS_PROTOCOL_WSP_CL         1   
#define MRE_WPS_PROTOCOL_WSP_CL_WTLS    2   
#define MRE_WPS_PROTOCOL_WSP_CO         3   
#define MRE_WPS_PROTOCOL_WSP_CO_WTLS    4   
#define MRE_WPS_PROTOCOL_HTTP           5   
#define MRE_WPS_PROTOCOL_HTTP_TLS       6   
#define MRE_WPS_PROTOCOL_HTTP_SSL       7   
#define MRE_WPS_PROTOCOL_CACHE          8   
#define MRE_WPS_PROTOCOL_FILE           9   
#define MRE_WPS_PROTOCOL_OTHER          10  


#define MRE_WPS_READY_STATUS_NULL           0  /* MMI WPS is not ready to service */
#define MRE_WPS_READY_STATUS_OK             1  /* MMI WPS is ready to service */


/* used to indicate the result and error code of a request. */

#define  MRE_WPS_OK                            0 /* Success */
#define  MRE_WPS_ERROR_UNKNOWN                 1 /* Unknonw error */
#define  MRE_WPS_ERROR_SEND                    2 /* Fail to write content */
#define  MRE_WPS_ERROR_INVALID_PARAM           3 /* Invalid parameters */
#define  MRE_WPS_ERROR_INVALID_HEADER          4 /* Invalid headers */
#define  MRE_WPS_ERROR_INVALID_CHANNEL_ID      5 /* Invalid channel ID */
#define  MRE_WPS_ERROR_INVALID_REQUEST_ID      6 /* Invalid request ID */
#define  MRE_WPS_ERROR_INVALID_SEQUENCE_NUM    7 /* Incorrect sequence number in MSG_ID_WPS_READ_CONTENT_REQ and MSG_ID_WPS_POST_CONTENT_RES */
#define  MRE_WPS_ERROR_INVALID_DEFAULT_PROFILE 8 /* Invalid default profile */   
#define  MRE_WPS_ERROR_INACTIVE_CHANNEL        9 /* Inactive channel */
#define  MRE_WPS_ERROR_INVALID_CONN_TYPE       10 /* Invalid connection type */
#define  MRE_WPS_ERROR_NO_RESOURCE             11 /* Resource limitation */
#define  MRE_WPS_ERROR_ACCESS_DENY             12 /* Access deny */
#define  MRE_WPS_ERROR_PENDING_REQ_EXIST       13 /* Pending request exists */
#define  MRE_WPS_ERROR_FILE_ACCESS             14 /* File system operation error */
#define  MRE_WPS_ERROR_REQ_ABORT               15 /* Request aborted */
#define  MRE_WPS_ERROR_NOT_FOUND               16 /* Not found */
#define  MRE_WPS_ERROR_REQ_MSG_TOO_LARGE       17 /* Message header is too large */
#define  MRE_WPS_ERROR_REQ_NOT_SUPPORT         18 /* Request is not supported */
#define  MRE_WPS_ERROR_DNS_RESOLVE             19 /* DNS error */
#define  MRE_WPS_ERROR_USE_PROXY               20 /* Proxy error */
#define  MRE_WPS_ERROR_NOT_READY               21 /* WPS is not ready yet */
#define  MRE_WPS_ERROR_NO_CNTXT_AVAILABLE      22 /* WPS free context not available, try after some time*/
#define  MRE_WPS_ERROR_CNTXT_NOT_REGISTERED    23 /* when availing WPS service without register context*/

/* This enum is used to specify the reply data format in a WSP/HTTP request. */
typedef enum
{
    /* Use peer buffer to convey replied content. */
    MRE_WPS_DATA_TYPE_BUFFER,
    /* Store replied content in  specified file path directly with downloading 
       progress indication while this is specified as reply_type of 
       MSG_ID_WPS_HTTP_REQ. */
    MRE_WPS_DATA_TYPE_FILE,
    /* Store replied content in specified file path directly without downloading 
       progress indication while this is specified as reply_type of 
       MSG_ID_WPS_HTTP_REQ. */
    MRE_WPS_DATA_TYPE_FILE_NO_PROG_IND,
    /* Resume a download previously. WPS will append the content in the file 
       specified in the request. */
    MRE_WPS_DATA_TYPE_FILE_RESUME,
    /* multipart/form-data, pass to post_type when do posting for multipart/form-data */
    MRE_WPS_DATA_TYPE_MULTIPART,
} mre_wps_data_type_enum;

/* vm_wps_content_t is the unit of multipart */
typedef struct {
  VMUINT32    contentTypelen;     /* The content type length */
  /* These two fields correspond to the following header: *  Content-Type: contentType; charset="charset"  * In case of multipart/form-data, each part has such a header. */
  VMUINT8 *    contentType;

  VMUINT32    namelen;     /* The name length */
  /* These two fields are used in case of multipart/form-data,  * and are then included with each part as follows: *   Content-Disposition: form-data; name="name"; filename="fileName" */
  VMUINT8 *   name;
  VMUINT32   fileNamelen;     /* The fileName name length */
  VMUINT8 *   fileName;/* Its an attribute of Content-Disposition. But not the multipart file name */

  VMUINT32    charset;
  VMUINT32    dataType; /* One of MRE_WPS_DATA_TYPE_BUFFER or MRE_WPS_DATA_TYPE_FILE. */
  VMUINT32    dataLen;  
  VMUINT32    filepathNamelen;     /* The fileName name length */
  VMWCHAR * filepathName;/* Absolute multipart filepath along with its name. */
} vm_wps_content_t;

/* the structure used for vm_https_send_req_ext. */
typedef struct
{
    VMUINT32 request_url_len;     /* The request URL length */
    VMUINT8 * request_url;         /* The request URL */
    VMUINT32 request_header_len;  /* The request header length */
    VMUINT8 * request_header;      /* The request header */

    /* The post segment buffer length when post_type is specified as 
       MRE_WPS_DATA_TYPE_BUFFER. It is mandatory is method is POST/PUT and post_type
       is MRE_WPS_DATA_TYPE_BUFFER. */
    VMUINT32 post_segment_len;

    /* The post data segment. It is mandatory is method is POST/PUT and 
       post_type is MRE_WPS_DATA_TYPE_BUFFER. */
    VMUINT8 * post_segment;
    /*To support Posting of multipart data */
    VMUINT32 num_entries; /*no. of multipart entries*/
    vm_wps_content_t * content; /*application should allocate memory for each vm_wps_content_t  and fill the info */   
} vm_wps_http_req_var_struct;


/*************************************************************************
 * WPS SERVICE  -- Callback function prototype
 ************************************************************************/

 /* 
 * Response to the channel configuration request, and if the result is 
 * successful, then the channel ID will be used n the HTTP/WSP request.
 */
typedef void (*mre_wps_send_set_channel_rsp_cb)( VMUINT32 req_id,
                                                 VMUINT8  channel_id,
                                                 VMUINT8  result);

/* 
 * Response to channel remove request. If the channel ID in request is 
 * invalid or some pending request of this channel exists, then an error is 
 * replied.
 */
typedef void (*mre_wps_unset_channel_rsp_cb)( VMUINT8 channel_id,
                                              VMUINT8 result);


/* 
 * Response to release all request.
 */
typedef void (*mre_wps_send_release_all_req_rsp_cb)( VMUINT8 result);


/* 
 * Notifying applcation about WPS agent termination. 
 * app should clear all information at its end, and can start again
 */
typedef void (*mre_wps_send_wps_termination_ind_cb)(void);

/* 
 * Response to the HTTP/WSP request. new_url is used to hold the new URL 
 * that was used to retrieve this reply If the original request was 
 * redirected. If the reply_type in MSG_ID_WPS_HTTP_REQ is 
 * WPS_DATA_TYPE_BUFFER, then the more flag is used to indicate if 
 * application needs to use MSG_ID_WPS_READ_CONTENT_REQ to retrieve 
 * remaining content.
 *
 * The new_url if available, reply_header if available, and reply_segment 
 */
typedef void (*mre_wps_send_http_rsp_cb)( VMUINT16 request_id,  /* request ID */
                                          VMUINT8  result,      /* Result (wps_result_error_enum) */
                                          VMUINT16 status,      /* HTTP response codes */
                                          VMINT32  cause,       /* Error cause if result is not ok */
                                          VMUINT8  protocol,    /* Network protocol used to retrieve content. Please refer to the Protocol Constants */
                                          VMUINT8  content_type_len,
                                          VMUINT8 *content_type,      /* The type of replied content.. max 256 characters including NULL */
                                          VMUINT32 content_length,    /* The length of replied content. Incase the content length is unknown, use the more field to know whether there is more data*/
                                          VMINT32  more,              /* Indicate if more data is needed to be retrieved. */
                                          VMUINT32 new_url_len,       /* The length of new redirected URL */
                                          VMUINT8 *new_url,           /* The new redirected URL */
                                          VMUINT32 reply_header_len,  /* The length of replied header */
                                          VMUINT8 *reply_header,      /* The replied header */
                                          VMUINT32 reply_segment_len, /* The reply segment buffer length when reply_type is specified as WPS_DATA_TYPE_BUFFER. It is mandatory when reply_type is  WPS_DATA_TYPE_BUFFER. */
                                          VMUINT8 *reply_segment );

/* 
 * Response to the MSG_ID_WPS_READ_CONTENT_REQ. The seq_num must be the same 
 * as the one in the corresponding MSG_ID_WPS_READ_CONTENT_REQ. The more 
 * flag is used to indicate if application needs to use 
 * MSG_ID_WPS_READ_CONTENT_REQ to retrieve remaining content.
 */
typedef void (*mre_wps_send_read_content_rsp_cb)( VMUINT16 request_id,          /* Request ID */
                                                  VMUINT8  seq_num,             /* Sequence number (for debug purpose) */
                                                  VMUINT8  result,              /* Result (wps_result_error_enum) */
                                                  VMINT32  more,                /* Indicate if more data is needed to be retrieved. */
                                                  VMUINT32 reply_segment_len,   /* The reply segment buffer length */
                                                  VMUINT8 *reply_segment        /* The reply segment buffer */);



/* 
 * Response to the cancel request.
 */
typedef void (*mre_wps_send_cancel_rsp_cb)( VMUINT16 request_id,
                                            VMUINT8  result);


/* 
 * Response to status query reqeust. If the status is WPS_READY_STATUS_NULL,
 * then WPS will send MSG_ID_WPS_READY_IND to the module who submit 
 * MSG_ID_WPS_STATUS_QUERY_REQ
 */
typedef void (*mre_wps_send_status_query_rsp_cb)( VMUINT8 status);

/* 
 * post data indication
 */
typedef void (*mre_wps_post_ind_cb)(VMUINT16 request_id, VMUINT8 seq_num, VMUINT8 result);

/*************************************************************************
 * WPS SERVICE  -- INTERFACE FUNCTION PROTOTYPE
 ************************************************************************/

/*****************************************************************************
 * FUNCTION
 *  vm_https_is_supported
 * DESCRIPTION
 *  query whether the https is supported by platform
 * RETURNS
 *  0 means successfully, non-zero is NOT SUPPORT.
 *****************************************************************************/
VMINT vm_https_is_supported(void);

/*****************************************************************************
 * FUNCTION
 *  vm_https_register_wps_cntxt_and_callback
 * DESCRIPTION
 *  This function is to register callback function
 * PARAMETERS
 *  apn                      :[IN]  APN enum, VM_TCP_APN_CMNET/VM_TCP_APN_CMWAP/VM_TCP_APN_WIFI
 *  set_channel_rsp_cb       :[IN]  set channel callback
 *  unset_channel_cb         :[IN]  unset channel callback
 *  release_all_req_cb       :[IN]  release all request callback
 *  terminal_ind_cb          :[IN]  terminal req callback
 *  http_rsp_cb              :[IN]  http request callback
 *  read_content_rsp_cb      :[IN]  read content callback
 *  cancel_rsp_cb            :[IN]  cancel req callback
 *  status_query_rsp_cb      :[IN]  status query callback
 * RETURNS
 *  0 success
 *****************************************************************************/
VMUINT8 vm_https_register_wps_cntxt_and_callback(
                        VMINT apn,
                        mre_wps_send_set_channel_rsp_cb set_channel_rsp_cb,
                        mre_wps_unset_channel_rsp_cb unset_channel_cb,
                        mre_wps_send_release_all_req_rsp_cb release_all_req_cb,
                        mre_wps_send_wps_termination_ind_cb terminal_ind_cb,
                        mre_wps_send_http_rsp_cb http_rsp_cb,
                        mre_wps_send_read_content_rsp_cb read_content_rsp_cb,
                        mre_wps_send_cancel_rsp_cb cancel_rsp_cb,
                        mre_wps_send_status_query_rsp_cb status_query_rsp_cb);


/*****************************************************************************
 * FUNCTION
 *  vm_https_send_set_channel_req
 * DESCRIPTION
 *  Configure a dedicated channel for HTTP/WSP requests. An channel can be 
 *  configured to use proxy while  use_proxy is true. When use_proxy is true, 
 *  prx_ip, prx_port, username, and password will be used to communicate with 
 *  proxy server, thus prx_ip must not be 0.0.0.0 and if prx_port value 0 
 *  means use default proxy port 8080. When the conn_type is 
 *  WPS_CONN_TYPE_WSP_CO or WPS_CONN_TYPE_WSP_CL, then use_proxy is true 
 *  default. However, if application simply wants to use current activated 
 *  setting used in WAP, then just set use_default as true and ignore all 
 *  other parameters. 
 *  Static_header (if necessary) must be filled in 
 *  WAP_PROF_CONN_TYPE_WSP_CO and the first WSP request  of some dedicated 
 *  channel with connection type WSP_CONN_TYPE_WSP_CL. If application doesn't 
 *  specify static_header, then WPS will use the value currently used by WAP.
 *  
 * PARAMETERS
 *  req_id  :       [IN] Request ID
 *  use_proxy  :    [IN] Use proxy or not 
 *  prx_ip  :       [IN] Proxy IP address
 *  prx_port  :     [IN] Proxy port number. 0 means default proxy 8080.
 *  username  :     [IN] Username for the proxy. Only ASCII is allowed and NULL terminated
 *  username_len  : [IN] length should not exceed 40 character excluding NULL character
 *  password  :     [IN] Password for the proxy. Only ASCII is allowed and NULL terminated.
 *  password_len  : [IN] length should not exceed 40 character excluding NULL character
 *  server_auth_username  :    [IN] Username for the origin server. Only ASCII is allowed and NULL terminated.
 *  server_auth_username_len : [IN] length should not exceed 128 character excluding NULL character
 *  server_auth_password  :    [IN] length should not exceed 128 character excluding NULL character
 *  server_auth_password_len : [IN] length should not exceed 40 character excluding NULL character
 *  static_header_len  :       [IN] The length of static header 
 *  static_header  :           [IN] static header      
 * RETURNS
 *  void
 *****************************************************************************/
VMUINT8 vm_https_send_set_channel_req( 
                                        VMUINT16 req_id,    /* Request ID */
                                        VMUINT8 use_proxy,   /* Use proxy or not */
                                        VMUINT8 prx_ip[4],  /* Proxy IP address */
                                        VMUINT16 prx_port,  /* Proxy port number. 0 means default proxy 8080. */
                                        VMUINT8 *username,  /* Username for the proxy. Only ASCII is allowed and NULL terminated. */
                                        VMUINT8 username_len, /*length should not exceed 40 character excluding NULL character*/
                                        VMUINT8 *password,    /* Password for the proxy. Only ASCII is allowed and NULL terminated. */
                                        VMUINT8 password_len, /*length should not exceed 40 character excluding NULL character*/
                                        VMUINT8 *server_auth_username, /* Username for the origin server. Only ASCII is allowed and NULL terminated. */
                                        VMUINT8 server_auth_username_len, /*length should not exceed 128 character excluding NULL character*/
                                        VMUINT8 *server_auth_password,    /* Password for the origin server. Only ASCII is allowed and NULL terminated. */
                                        VMUINT8 server_auth_password_len, /*length should not exceed 40 character excluding NULL character*/
                                        VMUINT32 static_header_len,   /* The length of static header */
                                        VMUINT8 *static_header       /* static header */ );


/*****************************************************************************
 * FUNCTION
 *  vm_https_send_unset_channel_req
 * DESCRIPTION
 *  this function is  to send unset channel request information to WPS
 * PARAMETERS
 *  channel_id            :  [IN]        channel ID   
 * RETURNS
 *  void
 *****************************************************************************/
 VMUINT8 vm_https_send_unset_channel_req(VMUINT8 channel_id );


/*****************************************************************************
 * FUNCTION
 *  vm_https_send_req
 * DESCRIPTION
 *  this function is to send a HTTP/WSP request.
 * PARAMETERS
    request_id,           : [IN]    Request ID 
    method,               : [IN]    HTTP Method Constant
    option,               : [IN]    HTTP request options
    reply_type,           : [IN]    Reply type (wps_data_type_enum) 
                                  The file path used to store replied content when reply_type is specified 
                                  as WPS_DATA_TYPE_FILE, WPS_DATA_TYPE_FILE_NO_PROG_IND or 
                                  WPS_DATA_TYPE_FILE_RESUME. 
                                  Max. buffer size that reading side suggests when reply_type is specified 
                                  as WPS_DATA_TYPE_BUFFER. 
    reply_segment_len,    : [IN]     
    request_url_len,      : [IN]    The request URL length 
    *request_url,         : [IN]    The request URL 
    request_header_len    : [IN]    The request header length 
    *request_header,      : [IN]    The request header 
                                  The post segment buffer length when post_type is specified as 
                                  WPS_DATA_TYPE_BUFFER. It is mandatory is method is POST/PUT and post_type
                                  is WPS_DATA_TYPE_BUFFER. 
    post_segment_len,     : [IN]         
    *post_segment         : [IN]       
 * RETURNS
 *  void
 *****************************************************************************/
VMUINT8 vm_https_send_req(      VMUINT16 request_id, /* Request ID */
                                VMUINT8 method,      /* HTTP Method Constant */
                                VMUINT32 option,     /* HTTP request options */
                                VMUINT8 reply_type,  /* Reply type (wps_data_type_enum) */
                                VMUINT32 reply_segment_len,
                                VMUINT32 request_url_len, /* The request URL length */
                                VMUINT8 *request_url,     /* The request URL */
                                VMUINT32 request_header_len, /* The request header length */
                                VMUINT8 *request_header,     /* The request header */
                                VMUINT32 post_segment_len,
                                VMUINT8 *post_segment );


/*****************************************************************************
 * FUNCTION
 *  vm_https_send_read_content_req
 * DESCRIPTION
 *  this function is to send request to continue to read HTTP/WSP reply content.
 * PARAMETERS
 *  request_id         :  [IN]    Request ID    
 *  seq_num            :  [IN]    Sequence number (for debug purpose)    
 *  read_segnemtn_len  :  [IN]    Segnemtn Length       
 * RETURNS
 *  void
 *****************************************************************************/
VMUINT8 vm_https_send_read_content_req(    VMUINT16 request_id,/* Request ID */
                                            VMUINT8 seq_num,    /* Sequence number (for debug purpose) */
                                            VMUINT32 read_segnemtn_len);


/*****************************************************************************
 * FUNCTION
 *  vm_https_send_cancel_req
 * DESCRIPTION
 *  this function is to send a request to cancel an incomplete WSP/HTTP request.
 * PARAMETERS
 *  request_id            :  [IN]    Request ID         
 * RETURNS
 *  void
 *****************************************************************************/
VMUINT8 vm_https_send_cancel_req( VMUINT16 request_id );


/*****************************************************************************
 * FUNCTION
 *  vm_https_send_req_ext
 * DESCRIPTION
 *  this function is to send a HTTP/WSP request.
 * CALLS
 *  
 * PARAMETERS
 *  request_id : [IN] Request ID
 *  method : [IN] HTTP Method Constant
 *  option : [IN] HTTP request options
 *  reply_type : [IN] reply type (mre_wps_data_type_enum)
 *  reply_segment_len : [IN] length of repy segment
 *  more_post : [IN] if are still some data need to be posted next time, please set 1
 *  post_type : [IN] refer to mre_wps_data_type_enum
 *  req : [IN] request data, refer to vm_wps_http_req_var_struct
 *  cb : [IN] callback of post status
 * RETURNS
 *  VMINT
 *****************************************************************************/
 VMINT vm_https_send_req_ext(VMUINT16 request_id, 
                                                VMUINT8 method, 
                                                VMUINT32 option, 
                                                VMUINT8 reply_type, 
                                                VMUINT32 reply_segment_len,
                                                VMBYTE more_post,
                                                VMUINT8 post_type,
                                                const vm_wps_http_req_var_struct * req,
                                                mre_wps_post_ind_cb cb);

/*****************************************************************************
* FUNCTION
*  vm_https_send_post_content_res
* DESCRIPTION
*  this function is to to handle continuous content post of a HTTP request.
* PARAMETERS
*  request_id : [IN] Request ID
*  seq_num : [IN] sequence id
*  more : [IN] need more send or not
*  post_segment_len : [IN]         
*  post_segment : [IN]         
* RETURNS
*  VMINT
*****************************************************************************/
VMINT vm_https_send_post_content_res(VMUINT16 request_id,       
                                        VMUINT8 seq_num,           
                                        VMBYTE more,               
                                        VMUINT32 post_segment_len, 
                                        VMUINT8* post_segment);



/* DOM-NOT_FOR_SDK-BEGIN */
/*************************************************************************
 * Backup, please do not use them, only For old version's  APP.
 ************************************************************************/
/* Please do not use mre_https_init any more, no need to use it.*/
//#define mre_https_register_wps_cntxt_and_callback( a,b,c,d,e,f,g,h) vm_https_register_wps_cntxt_and_callback( 1,a,b,c,d,e,f,g,h)
//#define mre_https_send_set_channel_req(a,b,c,d,e,f,g,h,i,j,k,l,m,n) vm_https_send_set_channel_req(a,b,c,d,e,f,g,h,i,j,k,l,m,n)
//#define mre_https_send_unset_channel_req(a) vm_https_send_unset_channel_req(a)
//#define mre_https_send_req(a,b,c,d,e,f,g,h,i,j,k,l) vm_https_send_req(b,c,d,e,f,g,h,i,j,k,l)
//#define mre_https_send_read_content_req(a,b,c,d) vm_https_send_read_content_req(b,c,d)
//#define mre_https_send_cancel_req(a,b) vm_https_send_cancel_req(b)
/* DOM-NOT_FOR_SDK-END */

#ifdef __cplusplus
}
#endif 

#endif /* VMHTTPS_SDK_H */
