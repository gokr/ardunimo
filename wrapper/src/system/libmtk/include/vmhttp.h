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

#ifndef VMHTTP_SDK_H_
#define VMHTTP_SDK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "vmsys.h"

#ifdef WIN32
	typedef unsigned int SOCKET_T;
#else
	typedef int SOCKET_T;
#endif


/* Default user-agent when send http req */
#define USER_AGENT "HTTP4MRE/1.3.0(MRE)"

/* size of http req, include http head and body */
#define HTTP_REQUEST_BUFSIZE 			(4096)

/* HTTP response head size, do not include body */
#define HTTP_RESPONSE_HEADSIZE 		(8192)

/* HTTP cache size, enhance the read speed */
#define HTTP_CACHE_SIZE 				(5 * 1024)

/* HTTP state, get get remote host name , param is not used */
#define HTTP_STATE_GET_HOSTNAME		(1)

/* HTTP state, connecting to the host , param is not used */
#define HTTP_STATE_CONNECTING			(2)

/* HTTP state, send the http req , param is percent of sending */
#define HTTP_STATE_SENDING			(3)

/* HTTP state, receive status , param is not used */
#define HTTP_STATE_RECV_STATUS		(4)

/* HTTP state, receive heads , param is not used */
#define HTTP_STATE_RECV_HEADS			(5)

/* HTTP state, receive body , param is not used */
#define HTTP_STATE_RECV_BODY			(6)

/* HTTP session structure */
struct http_session_t {
	SOCKET_T s;								/* SOCKET handle    						*/
	char url[255];							/* Req URL  								*/
	char host[100];							/* Host name    							*/
	VMUINT8 ip_addr[4];						/* Host IP address   						*/
	VMUINT8 ip_addr_len;					/* Length of IP								*/
	int port;								/* Server Port, default is 80				*/
	int nreqbuf;							/* length of Req Buffer  					*/
	char reqbuf[HTTP_REQUEST_BUFSIZE];		/* Req buffer								*/
	int res_code;							/* HTTP response code, <0 means TCP failded */
	int nresbuf;							/* HTTP response Head length          		*/
	VMUINT8 resbuf[HTTP_RESPONSE_HEADSIZE];	/* HTTP response Head buffer         		*/
	int nresbody;							/* HTTP response Body length				*/
	VMUINT8* resbody;						/* HTTP response Body buffer		    	*/
	void (*hook)(int, void*);				/* HTTP callback func, app provide this		*/
	VMWCHAR lasterr[50];					/* Last error string             			*/
};
typedef struct http_session_t http_session_t;


/* HTTP head structure */
struct http_head_t {
	char name[20];				/* Name of head		*/
	char value[100];			/* Value of head    */
};
typedef struct http_head_t http_head_t;


/* HTTP request stucture */
struct http_request_t {
	char url[255];			    /* Address URL				            */
	int nhead;					/* Count of request head                */
	http_head_t *heads;			/* Array pointer of of request head		*/
	int nbody;					/* size of request body (byte)      	*/
	char* body;					/* pointer of request body				*/
};
typedef struct http_request_t http_request_t;


/*******************************************************************************************
  * <GROUP HTTP> 
  * FUNCTION
  *     vm_http_request
  * Description
  *     Start a http request, it's an async method, http response will return from callback function
  * Parameters
  *     request :        [IN] HTTP request pointer, the structure can be local variable
  *     session :        [IN/OUT] HTTP session pointer, the structure should be global memory
  * Returns
  *     0 is successful, otherwise will return following error code:
  *     ASYN_HTTP_REQ_NOT_SUPPORT_METHOD
  *     ASYN_HTTP_REQ_NOT_SUPPORT_HTTP_COMM
  *     ASYN_HTTP_REQ_ONLY_SUPPORT_PROXY
  *     ASYN_HTTP_REQ_NOT_ENOUGH_RESOURCE
  *     ASYN_HTTP_REQ_URL_FORMAT_ERROR
  * EXAMPLE
  * <code>
  *   http_session_t g_hl_ses;
  *   void hl_http_req(void)
  *   {
  *       http_request_t req;
  *       int ret;
  *       memset(&req, 0, sizeof(http_request_t));
  *       memset(&g_hl_ses, 0, sizeof(http_session_t));
  *       strcpy(req.url, "http://www.mediatek.com/");
  *       g_hl_ses.hook = hl_http_hook;
  *       ret = vm_http_request(&req, &g_hl_ses);
  *   }
  * </code>
  *******************************************************************************************/ 
int vm_http_request(http_request_t *request, http_session_t *session);


/*******************************************************************************************
  * <GROUP HTTP> 
  * FUNCTION
  *     get_http_head
  * Description
  *     Get head in HTTP response
  * Parameters
  *     session :           [IN] HTTP request session
  *     name :              [IN] HTTP head name
  *     value :             [IN/OUT] The buffer to store HTTP head value, the maximum size needed is 512 bytes
  * Returns
  *     0 is successful, otherwise will return error code: -1
  * EXAMPLE
  * <code>
  *   void hl_http_hook(int state, void *ses)
  *   {
  *     http_session_t *p_ses;
  *     int ret;
  *     char date[512];
  *     p_ses = (http_session_t*)ses;
  *     ret = get_http_head(p_ses, "Date", date);
  *   }
  * </code>
  *******************************************************************************************/ 
int get_http_head(http_session_t* session, const char* name, char* value);


/*******************************************************************************************
  * <GROUP HTTP> 
  * FUNCTION
  *     get_http_head_number
  * Description
  *     Get Head number
  * Parameters
  *     session :        [IN] HTTP session pointer
  * Returns
  *     number of head
  * EXAMPLE
  * <code>
  *   void hl_http_hook(int state, void *ses)
  *   {
  *     http_session_t *p_ses;
  *     int ret;
  *     p_ses = (http_session_t*)ses;
  *     ret = get_http_head_number(p_ses);
  *   }
  * </code>
  *******************************************************************************************/  
int get_http_head_number(http_session_t* session);


/*******************************************************************************************
  * <GROUP HTTP> 
  * FUNCTION
  *     get_http_head_by_index
  * Description
  *     Get Head name and value by the index
  * Parameters
  *     session :           [IN] HTTP request session
  *     index :             [IN] HTTP head index
  *     name :              [IN/OUT] HTTP head name buffer, the maximum size needed is 255 bytes.
  *     value :             [IN/OUT] HTTP head value, the maximum size needed is 512 bytes
  * Returns
  *     0 is successful, otherwise will return error code: -1
  * EXAMPLE
  * <code>
  *   void hl_http_hook(int state, void *ses)
  *   {
  *     http_session_t *p_ses;
  *     int ret;
  *     char name[255], value[512];
  *     p_ses = (http_session_t*)ses;
  *     ret = get_http_head_by_index(p_ses, 0, name, value);
  *   }
  * </code>
  *******************************************************************************************/   
int get_http_head_by_index(http_session_t* session, int index, char* name, char* value);


/*******************************************************************************************
  * <GROUP HTTP> 
  * FUNCTION
  *     vm_cancel_all_http_sessions
  * Description
  *     Cancel all https sessions, created TCP link will be closed. will not send callback to app after closed
  * Parameters
  *     void
  * Returns
  *     void
  * EXAMPLE
  * <code>
  *   void hl_http_hook(int state, void *ses)
  *   {
  *     http_session_t *p_ses;
  *     int ret;
  *     char name[255], value[512];
  *     p_ses = (http_session_t*)ses;
  *     ret = get_http_head_by_index(p_ses, 0, name, value);
  *     vm_cancel_asyn_http_req(g_hl_http_hd);
  *     vm_cancel_all_http_sessions();
  *     
  *   }
  * </code>
  *******************************************************************************************/   
void vm_cancel_all_http_sessions(void);


/*******************************************************************************************
  * <GROUP HTTP> 
  * FUNCTION
  *     vm_reg_http_notification
  * Description
  *     Register HTTP status call back function.
  * Parameters
  *     f :             [IN] status callback function, state is current state, param is the different meaning in different status, please check Define of HTTP_STATE_XXXX
  * Returns
  *     void
  * EXAMPLE
  * <code>
  *   void hl_http_noti(VMINT state, VMINT param)
  *   {
  *       char perc[6];
  *       switch(state)
  *       {
  *           case HTTP_STATE_SENDING:
  *               vm_sprintf(perc, "%d%%", param);
  *               break;
  *           default:
  *               break;
  *       }
  *   }
  *   void hl_http_req(void)
  *   {
  *       http_request_t req;
  *       int ret;
  *       memset(&req, 0, sizeof(http_request_t));
  *       memset(&g_hl_ses, 0, sizeof(http_session_t));
  *       strcpy(req.url, "http://www.mediatek.com/");
  *       g_hl_ses.hook = hl_http_hook;
  *       vm_reg_http_notification(hl_http_noti);
  *       ret = vm_http_request(&req, &g_hl_ses);
  *   }
  * </code>
  *******************************************************************************************/   
void vm_reg_http_notification(void (*f)(VMINT state, VMINT param));


/*******************************************************************************************
  * <GROUP HTTP> 
  * FUNCTION
  *     vm_enable_proxy
  * Description
  *     Enable/Disalbe HTTP proxy, it's a global setting for MRE env.
  * Parameters
  *     use_proxy :             [IN] TRUE is use proxy, FALSE is not use Proxy
  * Returns
  *     void
  *******************************************************************************************/  
void vm_enable_proxy(VMINT use_proxy);


/* HTTP request method enum */
typedef enum {
	GET = 1, 
	POST, 
	HEAD, 
	PUT, 
	DELETE, 
	TRACE, 
	CONNECT
}HTTP_METHOD;

/* asyn_http_req_t.use_proxy param enum*/
typedef enum 
{
	HTTP_USE_CMNET = 0,				    /* use cmnet APN to connect	*/
	HTTP_USE_CMWAP, 					/* use cmwap APN to connect	*/	
	HTTP_USE_CMNET_PRIORITY,			/* If can't find any cmnet's APN, will use cmwap APN	*/
	HTTP_USE_CMWAP_PRIORITY,			/* If can't find any cmwap's APN, will use cmnet APN */
	HTTP_USE_WIFI						/* Use WIFI to connect */
} VM_HTTP_PROXY_TYPE;

  
/* Async http request structure, enhance http_request */
typedef struct asyn_http_req_t {
	HTTP_METHOD 	req_method;	        /* HTTP_METHOD */
	VMUINT8 		use_proxy;		    /* VM_HTTP_PROXY_TYPE */
	http_request_t* 	http_request;	/* Old http request */
}asyn_http_req_t;


  
/* return value of vm_asyn_http_req, HTTP req success, will sent an async request */
#define ASYN_HTTP_REQ_ACCEPT_SUCCESS								(0)

/* return value of vm_asyn_http_req, Do not support current method */
#define ASYN_HTTP_REQ_NOT_SUPPORT_METHOD						(1)

/* return value of vm_asyn_http_req, Do not support HTTP stack */
#define ASYN_HTTP_REQ_NOT_SUPPORT_HTTP_COMM					(2)

/* return value of vm_asyn_http_req, only support proxy mode */
#define ASYN_HTTP_REQ_ONLY_SUPPORT_PROXY						(3)

/* return value of vm_asyn_http_req, only one HTTP request should be sent, before it finished, could not start another again. */
#define ASYN_HTTP_REQ_NOT_ENOUGH_RESOURCE						(4)

/* return value of vm_asyn_http_req, URL format error */
#define ASYN_HTTP_REQ_URL_FORMAT_ERROR							(5)


/*******************************************************************************************
  * <GROUP HTTP> 
  * FUNCTION
  *     vm_asyn_http_req
  * Description
  *     Start a http request, it's async function.
  * Parameters
  *     request :           [IN] HTTP request, if it's nULL, will return success, but HTTP stack will do nothing.
  *     http_hook :         [IN] Call back function,         
  *     http_state_notify : [IN] HTTP status notify function          
  * Returns
  *     return ASYN_HTTP_REQ_ACCEPT_SUCCESS if success, or return error code, please check define of ASYN_HTTP_REQ_XXX
  * EXAMPLE
  * <code>
  *   void hl_asyn_http_req(void)
  *   {
  *     asyn_http_req_t asyn_req;
  *     http_request_t req;
  *     int ret;
  *     memset(&req, 0, sizeof(http_request_t));
  *     strcpy(req.url, "http://www.mediatek.com/");
  *     asyn_req.http_request = &req;
  *     asyn_req.req_method = GET;
  *     asyn_req.use_proxy = HTTP_USE_CMNET;
  *     ret = vm_asyn_http_req(&asyn_req, hl_http_hook, hl_asyn_http_noti);
  *   }
  * </code>
  *******************************************************************************************/   
VMINT vm_asyn_http_req(asyn_http_req_t *request, void (*http_hook)(VMINT, void*), 
	void (*http_state_notify)(VMINT state, VMINT param, void* session));

/* Get HANDLE successful */
#define VM_GET_AHH_SUCCESS					(0)

/* Can't found the handle */
#define VM_GET_AHH_NO_COMM				(-1)

/* Paramter error */
#define VM_GET_AHH_ERROR_PARAM			(-2)


/*******************************************************************************************
  * <GROUP HTTP> 
  * FUNCTION
  *     vm_get_asyn_http_req_handle
  * Description
  *     Get async request handle
  * Parameters
  *     request :            [IN] HTTP request.
  *     handle :             [IN] http handle.
  * Returns
  *     Is get it successful
  *     VM_GET_AHH_SUCCESS      Get HANDLE successful
  *     VM_GET_AHH_NO_COMM      Can't found the handle
  *     VM_GET_AHH_ERROR_PARAM  Paramter error
  * Example
  * <code>
  * {
  * http_request_t internal_req;
  * 
  * req.http_request = &internal_req;
  * req.req_method = GET;
  * internal_req.nhead = internal_req.nbody = 0;
  * strcpy(internal_req.url, "http://www.mediatek.com");
  * 
  * if (vm_asyn_http_req(&req, http_hook_callback, http_state_callback) == ASYN_HTTP_REQ_ACCEPT_SUCCESS)
  * {
  *     VMINT handle = 0;
  *     vm_get_asyn_http_req_handle(&req, &handle); // Get the handle
  * }  
  * }
  * </code>
  *******************************************************************************************/ 
VMINT vm_get_asyn_http_req_handle(asyn_http_req_t* request, VMINT* handle);



/* return value of vm_cancel_asyn_http_req, Cancel request success */
#define VM_CAH_REQ_SUCCESS			(0)

/* return value of vm_cancel_asyn_http_req, Could not found the reqeust */
#define VM_CAH_REQ_NO_COMM		(-1)


/*******************************************************************************************
  * <GROUP HTTP> 
  * FUNCTION
  *     vm_cancel_asyn_http_req
  * Description
  *     Cancel one http request
  * Parameters
  *     handle :             [IN] http handle, could get it from vm_get_asyn_http_req_handle
  * Returns
  *     VM_CAH_REQ_SUCCESS  Cancel request success
  *     VM_CAH_REQ_NO_COMM  Could not found the reqeust
  * EXAMPLE
  * <code>
  *   void hl_http_hook(int state, void *ses)
  *   {
  *     http_session_t *p_ses;
  *     int ret;
  *     char name[255], value[512];
  *     p_ses = (http_session_t*)ses;
  *     ret = get_http_head_by_index(p_ses, 0, name, value);
  *     vm_cancel_asyn_http_req(g_hl_http_hd);
  *     vm_cancel_all_http_sessions();
  *     
  *   }
  * </code>
  *******************************************************************************************/ 
VMINT vm_cancel_asyn_http_req(VMINT handle);

 
/*******************************************************************************************
  * <GROUP HTTP> 
  * FUNCTION
  *     vm_url_encode_gb2312
  * Description
  *     GB2312 to URL encode
  * Parameters
  *     dst :             [OUT] Dest buffer
  *     size :            [IN] Dest buffer size(byte)
  *     src :             [IN] Source buffer
  * Returns
  *     size of dest string(byte), do not include \0.
  * EXAMPLE
  * <code>
  *   static void hl_http_encode_url(void)
  *   {
  *       VMSTR src = "http://www.≤‚ ‘.com";
  *       VMCHAR des[255];
  *       int ret;
  *       ret = vm_url_encode_gb2312(des,sizeof(des), src);
  *   }
  * </code>
  *******************************************************************************************/  
VMUINT vm_url_encode_gb2312(VMSTR dst, VMUINT size, const VMSTR src);


/*******************************************************************************************
  * <GROUP HTTP> 
  * FUNCTION
  *     vm_url_decode_gb2312
  * Description
  *     URL to GB2312 decode
  * Parameters
  *     dst :             [OUT] Dest buffer
  *     size :            [IN] Dest buffer size(byte)
  *     src :             [IN] Source buffer
  * Returns
  *     size of dest string(byte), do not include \0.
  * EXAMPLE
  * <code>
  *   static void hl_http_decode_url(void)
  *   {
  *       VMSTR src = "http%3a%2f%2fwww.%b2%e2%ca%d4.com";
  *       VMCHAR des[255];
  *       int ret;
  *       ret = vm_url_decode_gb2312(des, sizeof(des), src);
  *   }
  * </code>
  *******************************************************************************************/ 
VMUINT vm_url_decode_gb2312(VMSTR dst, VMUINT size, VMSTR src);


/*******************************************************************************************
  * <GROUP HTTP> 
  * FUNCTION
  *     http_data_receiver
  * Description
  *     HTTP reponse callback function typedef
  * Parameters
  *     handle :       [IN] HTTP handle
  *     p :            [IN] Not used
  * Returns
  *     >0 total length, 0 block, <0 error code.
  *******************************************************************************************/  
typedef VMINT(*http_data_receiver)(VMINT handle, void* p);


/*******************************************************************************************
  * <GROUP HTTP> 
  * FUNCTION
  *     vm_http_reg_receiver
  * Description
  *     Register receiver
  * Parameters
  *     handle :       [IN] HTTP handle
  *     reciever :     [IN] Receive data callback
  * Returns
  *     Is successful
  * EXAMPLE
  * <code>
  *   void hl_http_fetch(void)
  *   {
  *       asyn_http_req_t asyn_req;
  *       http_request_t req;
  *       int ret;
  *       
  *       memset(&req, 0, sizeof(http_request_t));
  *       strcpy(req.url, "http://www.mediatek.com");
  *       asyn_req.http_request = &req;
  *       asyn_req.req_method = GET;
  *       if (vm_wifi_is_connected()) {
  *           asyn_req.use_proxy = HTTP_USE_WIFI;
  *       }
  *       else {
  *           asyn_req.use_proxy = HTTP_USE_CMNET_PRIORITY;
  *       }
  *       g_hl_http_hd = vm_http_fetch_handle(ASYN_HTTP_REQ, &asyn_req);
  *       vm_http_reg_receiver(g_hl_http_hd, hl_data_recv);
  *       ret = vm_asyn_http_req(&asyn_req, NULL, hl_asyn_http_noti);
  *   }
  * </code>
  *******************************************************************************************/  
VMINT vm_http_reg_receiver(VMINT handle, http_data_receiver reciever);


/*******************************************************************************************
  * <GROUP HTTP> 
  * FUNCTION
  *     vm_http_recv_data
  * Description
  *     Receive HTTP Data
  * Parameters
  *     handle :       [IN] HTTP handle
  *     data :         [IN] Buffer pointer
  *     len :          [IN] Buffer size
  * Returns
  *     Received data size
  * EXAMPLE
  * <code>
  *   VMINT hl_data_recv(VMINT handle, void* p)
  *   {
  *     VMINT ret;
  *     VMUINT8 data[1024];
  *     ret = vm_http_recv_data(handle, data, 1024);
  *     return TRUE;
  *   }
  * </code>
  *******************************************************************************************/  
VMINT vm_http_recv_data(VMINT handle, VMUINT8* data, VMINT len);

 
/*******************************************************************************************
  * <GROUP HTTP> 
  * FUNCTION
  *     http_data_sender
  * Description
  *     Callback function of HTTP data callback
  * Parameters
  *     handle :       [IN] HTTP handle
  *     p :            [IN] Not used
  * Returns
  *     >0 total length, 0 block, <0 error code.
  *******************************************************************************************/ 
typedef VMINT(*http_data_sender)(VMINT handle, void* p);


/*******************************************************************************************
  * <GROUP HTTP> 
  * FUNCTION
  *     vm_http_reg_sender
  * Description
  *     Register HTTP datacall back function
  * Parameters
  *     handle :       [IN] HTTP handle
  *     sender :       [IN] Callback function
  * Returns
  *     Is successful
  * EXAMPLE
  * <code>
  *   void hl_http_fetch(void)
  *   {
  *     asyn_http_req_t asyn_req;
  *     http_request_t req;
  *     int ret;
  *     
  *     memset(&req, 0, sizeof(http_request_t));
  *     strcpy(req.url, "http://www.mediatek.com");
  *     asyn_req.http_request = &req;
  *     asyn_req.req_method = GET;
  *     if (vm_wifi_is_connected()) {
  *         asyn_req.use_proxy = HTTP_USE_WIFI;
  *     }
  *     else {
  *         asyn_req.use_proxy = HTTP_USE_CMNET_PRIORITY;
  *     }
  *     g_hl_http_hd = vm_http_fetch_handle(ASYN_HTTP_REQ, &asyn_req);
  *     vm_http_reg_sender(g_hl_http_hd, hl_data_sender);
  *     ret = vm_asyn_http_req(&asyn_req, NULL, hl_asyn_http_noti);
  *   }
  * </code>
  *******************************************************************************************/  
VMINT vm_http_reg_sender(VMINT handle, http_data_sender sender);


/*******************************************************************************************
  * <GROUP HTTP> 
  * FUNCTION
  *     vm_http_send_data
  * Description
  *     Send HTTP data, use this after send http request
  * Parameters
  *     handle :       [IN] HTTP handle
  *     data :         [IN] Buffer of HTTP data
  *     len :          [IN] Length of HTTP data
  * Returns
  *     Is successful
  * EXAMPLE
  * <code>
  *   VMINT hl_data_sender(VMINT handle, void* p)
  *   {
  *       VMUINT8 data[1024];
  *       strcpy(data, "Data data data...");
  *       vm_http_send_data(g_hl_http_hd, data, strlen(data));
  *   }
  * </code>
  *******************************************************************************************/  
VMINT vm_http_send_data(VMINT handle, VMUINT8* data, VMINT len); 


/*******************************************************************************************
  * <GROUP HTTP> 
  * FUNCTION
  *     vm_http_add_header
  * Description
  *     Add http head, APP need to provide name and value memory, call this before start the request.
  *     max length of name+value is 400 bytes
  * Parameters
  *     handle :       [IN] HTTP handle
  *     name :         [IN] name of head
  *     value :        [IN] value of head
  * Returns
  *     Is successful
  * EXAMPLE
  * <code>
  *   void hl_http_fetch(void)
  *   {
  *       asyn_http_req_t asyn_req;
  *       http_request_t req;
  *       int ret;
  *       
  *       memset(&req, 0, sizeof(http_request_t));
  *       strcpy(req.url, "http://www.mediatek.com");
  *       asyn_req.http_request = &req;
  *       asyn_req.req_method = GET;
  *       if (vm_wifi_is_connected()) {
  *           asyn_req.use_proxy = HTTP_USE_WIFI;
  *       }
  *       else {
  *           asyn_req.use_proxy = HTTP_USE_CMNET_PRIORITY;
  *       }
  *       g_hl_http_hd = vm_http_fetch_handle(ASYN_HTTP_REQ, &asyn_req);
  *       vm_http_reg_receiver(g_hl_http_hd, hl_data_recv);
  *       vm_http_add_header(g_hl_http_hd, "Keep-Alive", "115");
  *       vm_http_add_header(g_hl_http_hd, "Connection", "keep-alive");
  *       ret = vm_asyn_http_req(&asyn_req, NULL, hl_asyn_http_noti);
  *   }
  * </code>
  *******************************************************************************************/    
VMINT vm_http_add_header(VMINT handle, VMCHAR* name, VMCHAR* value);


/*******************************************************************************************
  * <GROUP HTTP> 
  * FUNCTION
  *     vm_http_set_body
  * Description
  *     Set HTTP request URL, URL max length is 400 bytes
  * Parameters
  *     handle :       [IN] HTTP handle
  *     url :          [IN] URL pointer, app need to handle this buffer by itself.
  *     len :          [IN] URL size
  * Returns
  *     Is successful
  * EXAMPLE
  * <code>
  *   void hl_http_fetch(void)
  *   {
  *       asyn_http_req_t asyn_req;
  *       http_request_t req;
  *       int ret;
  *       
  *       memset(&req, 0, sizeof(http_request_t));
  *       strcpy(req.url, "http://www.mediatek.com");
  *       asyn_req.http_request = &req;
  *       asyn_req.req_method = GET;
  *       if (vm_wifi_is_connected()) {
  *           asyn_req.use_proxy = HTTP_USE_WIFI;
  *       }
  *       else {
  *           asyn_req.use_proxy = HTTP_USE_CMNET_PRIORITY;
  *       }
  *       g_hl_http_hd = vm_http_fetch_handle(ASYN_HTTP_REQ, &asyn_req);
  *       vm_http_set_url(g_hl_http_hd, "http://www.mediatek.com", strlen("http://www.mediatek.com"));
  *       ret = vm_asyn_http_req(&asyn_req, hl_http_hook, hl_asyn_http_noti);
  *   }
  * </code>
  *******************************************************************************************/   
VMINT vm_http_set_url(VMINT handle, VMCHAR* url, VMINT len);


/*******************************************************************************************
  * <GROUP HTTP> 
  * FUNCTION
  *     vm_http_set_body
  * Description
  *     Set HTTP request body, before start the request, free memory of data after request is sent
  * Parameters
  *     handle :       [IN] HTTP handle
  *     data :         [IN] Body pointer, could be NULL, then body will upload by callback function
  *     len :          [IN] Body size, will write to head's content-length section.
  * Returns
  *     Is successful
  * EXAMPLE
  * <code>
  *   void hl_http_fetch(void)
  *   {
  *       asyn_http_req_t asyn_req;
  *       http_request_t req;
  *       int ret;
  *       
  *       memset(&req, 0, sizeof(http_request_t));
  *       strcpy(req.url, "http://www.mediatek.com");
  *       asyn_req.http_request = &req;
  *       asyn_req.req_method = POST;
  *       if (vm_wifi_is_connected()) {
  *           asyn_req.use_proxy = HTTP_USE_WIFI;
  *       }
  *       else {
  *           asyn_req.use_proxy = HTTP_USE_CMNET_PRIORITY;
  *       }
  *       g_hl_http_hd = vm_http_fetch_handle(ASYN_HTTP_REQ, &asyn_req);
  *       vm_http_reg_sender(g_hl_http_hd, hl_data_sender);
  *       vm_http_set_body(g_hl_http_hd, "Body body body...", strlen("Body body body..."));
  *       ret = vm_asyn_http_req(&asyn_req, hl_http_hook, hl_asyn_http_noti);
  *   }
  * </code>
  *******************************************************************************************/  
VMINT vm_http_set_body(VMINT handle, VMUINT8* data, VMINT len);


typedef enum {
	ASYN_HTTP_REQ = 0, 
	HTTP_REQUEST
} HTTP_HANDLE_TYPE;


/*******************************************************************************************
  * <GROUP HTTP> 
  * FUNCTION
  *     vm_http_fetch_handle
  * Description
  *     Get a valid HTTP, use it when need to config HTTP request by vm_set_http_header(), vm_set_http_body()
  * Parameters
  *     type :       [IN] Type of get http handle
  *     p :          [IN] pointer of asyn_http_req_t
  * Returns
  *     HTTP handle
  * EXAMPLE
  * <code>
  *   void hl_http_fetch(void)
  *   {
  *       asyn_http_req_t asyn_req;
  *       http_request_t req;
  *       int ret;
  *       
  *       memset(&req, 0, sizeof(http_request_t));
  *       strcpy(req.url, "http://www.mediatek.com");
  *       asyn_req.http_request = &req;
  *       asyn_req.req_method = POST;
  *       if (vm_wifi_is_connected()) {
  *           asyn_req.use_proxy = HTTP_USE_WIFI;
  *       }
  *       else {
  *           asyn_req.use_proxy = HTTP_USE_CMNET_PRIORITY;
  *       }
  *       g_hl_http_hd = vm_http_fetch_handle(ASYN_HTTP_REQ, &asyn_req);
  *       vm_http_reg_sender(g_hl_http_hd, hl_data_sender);
  *       ret = vm_asyn_http_req(&asyn_req, hl_http_hook, hl_asyn_http_noti);
  *   }
  * </code>
  *******************************************************************************************/
VMINT vm_http_fetch_handle(VMINT type, void* p);


/*******************************************************************************************
  * <GROUP HTTP> 
  * FUNCTION
  *     vm_http_get_current_handle
  * Description
  *     Get the current handle
  * Parameters
  *     void
  * Returns
  *     HTTP handle
  * EXAMPLE
  * <code>
  *   void hl_http_fetch(void)
  *   {
  *     asyn_http_req_t asyn_req;
  *     http_request_t req;
  *     int ret;
  *     VMINT cur_hd;
  *     memset(&req, 0, sizeof(http_request_t));
  *     strcpy(req.url, "http://www.mediatek.com");
  *     asyn_req.http_request = &req;
  *     asyn_req.req_method = POST;
  *     if (vm_wifi_is_connected()) {
  *         asyn_req.use_proxy = HTTP_USE_WIFI;
  *     }
  *     else {
  *         asyn_req.use_proxy = HTTP_USE_CMNET_PRIORITY;
  *     }
  *     g_hl_http_hd = vm_http_fetch_handle(ASYN_HTTP_REQ, &asyn_req);
  *     cur_hd = vm_http_get_current_handle();
  *   }
  * </code>
  *******************************************************************************************/
VMINT vm_http_get_current_handle(void);


/*******************************************************************************************
  * <GROUP HTTP> 
  * FUNCTION
  *     vm_http_set_current_handle
  * Description
  *     Set the current handle
  * Parameters
  *     handle :       [IN] HTTP handle need to be handle
  * Returns
  *     HTTP handle
  * EXAMPLE
  * <code>
  *   void hl_http_fetch(void)
  *   {
  *     asyn_http_req_t asyn_req;
  *     http_request_t req;
  *     int ret;
  *     VMINT cur_hd;
  *     memset(&req, 0, sizeof(http_request_t));
  *     strcpy(req.url, "http://www.mediatek.com");
  *     asyn_req.http_request = &req;
  *     asyn_req.req_method = POST;
  *     if (vm_wifi_is_connected()) {
  *         asyn_req.use_proxy = HTTP_USE_WIFI;
  *     }
  *     else {
  *         asyn_req.use_proxy = HTTP_USE_CMNET_PRIORITY;
  *     }
  *     cur_hd = vm_http_fetch_handle(ASYN_HTTP_REQ, &asyn_req);
  *     g_hl_http_hd = vm_http_set_current_handle(cur_hd - 1);
  *   }
  * </code>
  *******************************************************************************************/
VMINT vm_http_set_current_handle(VMINT handle);

 
/*******************************************************************************************
  * <GROUP HTTP> 
  * FUNCTION
  *     vm_http_free_handle
  * Description
  *     Release all resource of HTTP, use it after HTTP operate or after cancel the request
  * Parameters
  *     handle :       [IN] HTTP handle
  * Returns
  *     void
  * EXAMPLE
  * <code>
  *   void hl_http_fetch(void)
  *   {
  *       asyn_http_req_t asyn_req;
  *       http_request_t req;
  *       int ret;
  *       VMINT cur_hd;
  *       memset(&req, 0, sizeof(http_request_t));
  *       strcpy(req.url, "http://www.mediatek.com");
  *       asyn_req.http_request = &req;
  *       asyn_req.req_method = POST;
  *       if (vm_wifi_is_connected()) {
  *           asyn_req.use_proxy = HTTP_USE_WIFI;
  *       }
  *       else {
  *           asyn_req.use_proxy = HTTP_USE_CMNET_PRIORITY;
  *       }
  *       cur_hd = vm_http_fetch_handle(ASYN_HTTP_REQ, &asyn_req);
  *       ret = vm_asyn_http_req(&asyn_req, hl_http_hook, hl_asyn_http_noti);
  *       vm_http_free_handle(g_hl_http_hd);
  *   }
  * </code>
  *******************************************************************************************/
void vm_http_free_handle(VMINT handle);

#ifdef __cplusplus
}
#endif

#endif /*VMHTTP_SDK_H_*/
