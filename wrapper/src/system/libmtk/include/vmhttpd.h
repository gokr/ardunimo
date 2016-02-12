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

/*******************************************************************************
 * Filename:
 * ---------
 * vmhttpd_sdk.h
 *
 * Project:
 * --------
 *  MAUI
 *
 * Description:
 * ------------
 *  LinkIt app and http task communicate header file
 *
 * Author:
 * -------
 * jianying.li(mtk81091)
 *
*==============================================================================
 *             HISTORY
 * Below this line, this part is controlled by PVCS VM. DO NOT MODIFY!! 
 *------------------------------------------------------------------------------
* *------------------------------------------------------------------------------
 * Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!! 
 *============================================================================== 
*******************************************************************************/
#ifndef VM_HTTPD_SDK_H
#define VM_HTTPD_SDK_H
#ifdef __cplusplus
extern "C"{
#endif/*__cplusplus*/
#include "vmsys.h"
/*VM_CGI_MAX_PARAM*/
/*VM_CGI_MAX_COMMAND_LINE_LEN*/
#define VM_CGI_MAX_COMMAND_LINE_LEN 250

/*vm_httpsrv_error_enum*/
typedef enum
{
	VM_HTTPSRV_ERR_NO_ERROR                    = 0,//operator suceed
	VM_HTTPSRV_ERR_STATE_ERROR                 = -1,//state of http is mess
	VM_HTTPSRV_ERR_GET_MEM_FAIL                = -2,//memory is not enough
	VM_HTTPSRV_ERR_CONNECT_NETWORK_FAIL        = -3,//network is not ready
	VM_HTTPSRV_ERR_FD_INIT_FAIL                = -4,//file disciptor init fail
	VM_HTTPSRV_ERR_GET_HOSTNAME_FAIL           = -5,//invalid host name
	VM_HTTPSRV_ERR_SRV_INIT_FAIL               = -6,//server init fail
	VM_HTTPSRV_ERR_ERROR_FD_NUMBER             = -7,//file diciptor abnormal
	VM_HTTPSRV_ERR_OTHERS                      = -65535,// other errors
	VM_HTTPSRV_ERR_CODE                        = -65536//end mark
}vm_httpsrv_error_enum;
/*the struct of app parameter */
typedef struct vm_cgi_app_param
{
    VMINT8 command_line[VM_CGI_MAX_COMMAND_LINE_LEN];// memory for string which was reference by argv
} vm_cgi_app_param;

/*the struct of the parameter with system message VM_MSG_HTTPD */
typedef struct vm_cgi_launch_param
{
    VMUINT32 hc_handle; //http connection handler, actually, a pointer to hc
    vm_cgi_app_param param;//used by app, this struct is fill with command line, which is comes from client
}vm_cgi_launch_param;

/*****************************************************************************
 * FUNCTION
 *  vm_inet_httpd_start
 * DESCRIPTION
 *  this is for launch http server
 * PARAMETERS
 *  port: [IN]the port to start
 *  root_dir:[IN] the root dir
 *  cgi_pattern:[IN] the cgi pattern
 * RETURNS
 *  httpsrv_error_enum:return VM_HTTPSRV_ERR_NO_ERROR, success, othersize, fail 
 * EXAMPLE
 * <code>
 * vm_inet_httpd_start(80, "C:\\@httpsrv", "**.vxp");
 * </code>
 *****************************************************************************/
extern vm_httpsrv_error_enum vm_inet_httpd_start(VMUINT32 port, VMINT8* root_dir, VMINT8* cgi_pattern);

/*****************************************************************************
 * FUNCTION
 *  vm_inet_httpd_stop
 * DESCRIPTION
 *  this is for stop http server
 * PARAMETERS
 *  N/A
 * RETURNS
 *  httpsrv_error_enum:return VM_HTTPSRV_ERR_NO_ERROR, success, othersize, fail
 * EXAMPLE 
 * <code>
 * vm_inet_httpd_stop();
 * </code>
 *****************************************************************************/
extern vm_httpsrv_error_enum vm_inet_httpd_stop(void);

/*****************************************************************************
 * FUNCTION
 *  vm_inet_httpd_restart
 * DESCRIPTION
 *  this is for restart http server
 * PARAMETERS
 *  port:  [IN]the port to restart                     
 *  root_dir:[IN]the root dir
 *  cgi_pattern:[IN]the cgi pattern
 * RETURNS
 *  httpsrv_error_enum:return VM_HTTPSRV_ERR_NO_ERROR, success, othersize, fail
 * EXAMPLE 
 * <code>
 * vm_inet_httpd_restart(80, "C:\\@httpsrv", "**.vxp");
 * </code>
 *****************************************************************************/
extern vm_httpsrv_error_enum vm_inet_httpd_restart(VMUINT32 port, VMINT8* root_dir, VMINT8* cgi_pattern);

/*****************************************************************************
 * FUNCTION
 *  vm_inet_httpd_cgi_job_finish
 * DESCRIPTION
 *  call this api to notify http server when cgi app finished the job.
 * PARAMETERS
 *  hc_handle:[IN]   when launch LinkIt app, will send VM_MSG_HTTPD,and the parameter with this msg
 *  is the pointer of vm_cgi_launch_param ; app can get hc_handle from vm_cgi_launch_param ,so app should 
 *  save the handle,a lot of api will use hc_handle as parameter                    
 * RETURNS
 *  N/A
 * EXAMPLE 
 * <code>
 * void httpd_cgi_app_demo(VMUINT32 hc_handle, VMCHAR* command_line)
 * {
 *   VMCHAR* request_method;
 *   VMCHAR* query_string;
 *   VMCHAR* content_length;
 *   VMINT32 con_len;
 *   VMCHAR* content_data;
 *   VMCHAR output_buffer[256];
 *   if (command_line && command_line[0] != '\0')
 *   {
 *       ///TODO: parse command line, and do some thing you need, config setting according to command_line
 *   }
 *
 *   request_method = vm_inet_httpd_getenv(hc_handle,"REQUEST_METHOD");
 *   
 *   if (request_method && strcmp(request_method, "GET") == 0)
 *   {
 *       query_string = vm_inet_httpd_getenv(hc_handle,"QUERY_STRING");
 *       ///TODO: parse query_string, and do some thing you need. for example, config setting according to query_string
 *  }
 *   else if (request_method && strcmp(request_method, "POST") == 0)
 *   {
 *       content_length = vm_inet_httpd_getenv(hc_handle,"CONTENT_LENGTH");
 *       if (content_length && sscanf(content_length,"%ld",&con_len) == 1)
 *       {
 *           content_data = vm_malloc(con_len + 1);
 *           if (content_data)
 *           {
 *               vm_inet_httpd_read(hc_handle, content_data, con_len);
 *               ///TODO: parse content_data, and do some thing you need. for example, config setting according to content_data
 *               vm_free(content_data);
 *          }
 *       }
 *   }
 *
 *   //output the config result to client, let end user knows the config result.
 *
 *   //write message header
 *   sprintf(output_buffer, "Content-Type:text/html\n\n");
 *   vm_inet_httpd_write(hc_handle, output_buffer, strlen(output_buffer));
 *   sprintf(output_buffer, "<html>\n");
 *   vm_inet_httpd_write(hc_handle, output_buffer, strlen(output_buffer));
 *   sprintf(output_buffer, "<head>\n<title>Response</title>\n</head>\n");
 *   vm_inet_httpd_write(hc_handle, write_buffer, strlen(output_buffer));
 *
 *   //write body.
 *    sprintf(output_buffer, "<body>\n");
 *    vm_inet_httpd_write(hc_handle, output_buffer, strlen(output_buffer));
 *    sprintf(output_buffer, "<p>Dear, your configration be saved suceed.\n");
 *    vm_inet_httpd_write(hc_handle, output_buffer, strlen(output_buffer));
 *    sprintf(output_buffer, "</body>\n</html>\n");
 *    vm_inet_httpd_write(my_app_param.hc_handle, output_buffer, strlen(output_buffer));
 *
 *    //please remember to give a notification to httpd when job is finished.
 *    vm_inet_httpd_cgi_job_finish(hc_handle);
 * </code>
 *****************************************************************************/
extern void vm_inet_httpd_cgi_job_finish(VMUINT32 hc_handle);

/*****************************************************************************
 * FUNCTION
 *  vm_inet_httpd_read
 * DESCRIPTION
 * this api is used to read the data which is comes from client, it is used to instead of stand I/O stream.
 * PARAMETERS
 *  hc_handle: [IN] hc_handle,comes from the parameter with VM_MSG_HTTPD                    
 *  buf:[IN/OUT]the buf to hold the read data
 *  buf_size:[IN]the buf size
 * RETURNS
 *  the actually read size
 * EXAMPLE 
 * <code>
 *   void httpd_cgi_app_demo(VMUINT32 hc_handle, VMCHAR* command_line)
 *    {
 *        VMCHAR* content_length;
 *        VMINT32 con_len;
 *        content_length = vm_inet_httpd_getenv(hc_handle,"CONTENT_LENGTH");
 *        if (content_length && sscanf(content_length,"%ld",&con_len) == 1)
 *        {
 *            content_data = vm_malloc(con_len + 1);
 *            if (content_data)
 *            {
 *                vm_inet_httpd_read(hc_handle, content_data, con_len);
 *                ///TODO: parse content_data, and do some thing you need. for example, config setting according to content_data
 *                vm_free(content_data);
 *            }
 *        }
 *    }
 * </code>
 *****************************************************************************/
extern VMINT32 vm_inet_httpd_read(VMUINT32 hc_handle, VMINT8* buf, VMINT32 buf_size);

/*****************************************************************************
 * FUNCTION
 *  vm_inet_httpd_write
 * DESCRIPTION
 *  this api is used to write the data to client, it is used to instead of stand I/O stream.
 * PARAMETERS
 *  hc_handle: [IN] hc_handle,comes from the parameter with VM_MSG_HTTPD                       
 *  buf:[IN]  the data write to httpd
 *  content_size:[IN]the data size
 * RETURNS
 *  the actually write size
 * EXAMPLE 
 * <code>
 *    VMCHAR output_buffer[256];
 *    sprintf(output_buffer, "Content-Type:text/html\n\n");
 *    vm_inet_httpd_write(hc_handle, output_buffer, strlen(output_buffer));
 * </code>
 *****************************************************************************/
extern VMINT32 vm_inet_httpd_write(VMUINT32 hc_handle, VMINT8* buf, VMINT32 content_size);

/*****************************************************************************
 * FUNCTION
 *  vm_inet_httpd_getenv
 * DESCRIPTION
 * this api is get enviroment varible, it's same as other plateform in CGI.
 * PARAMETERS
 *  hc_handle:[IN]hc_handle,comes from the parameter with VM_MSG_HTTPD 
 *  name:[IN]the env name                      
 * RETURNS
 *  the env string
 * EXAMPLE 
 * <code>
 *   void httpd_cgi_app_demo(VMUINT32 hc_handle, VMCHAR* command_line)
 *    {
 *        VMCHAR* content_length;
 *        VMINT32 con_len;
 *        content_length = vm_inet_httpd_getenv(hc_handle,"CONTENT_LENGTH");
 *        if (content_length && sscanf(content_length,"%ld",&con_len) == 1)
 *        {
 *            content_data = vm_malloc(con_len + 1);
 *            if (content_data)
 *            {
 *                vm_inet_httpd_read(hc_handle, content_data, con_len);
 *                ///TODO: parse content_data, and do some thing you need. for example, config setting according to content_data
 *                vm_free(content_data);
 *            }
 *        }
 *    }
 * </code>
 *****************************************************************************/
extern VMINT8* vm_inet_httpd_getenv(VMUINT32 hc_handle, VMINT8* name);

/*****************************************************************************
 * FUNCTION
 *  vm_inet_httpd_enable_ssl
 * DESCRIPTION
 * this api can enable httpd for SSL. Then it can support https.
 * Important
 *  1. Must start http server after enable ssl. Https server must run with http server.
 *  2. Push your https html into http server source path. Emxaple "E:/httpd". 
 *      If some html files can't be get by http server, you can push them into "E:/httpd/https". We will protect the files of "(httpd sourcepath)/https".
 *      Example: 
 *         input : http://127.0.0.1/user/index.html output: index.html
 *         input : https://127.0.0.1/user/index.html output: index.html
 *         input : http://127.0.0.1/https/index.html output: 403 forbidden
 *         input : https://127.0.0.1/user/index.html output: index.html
 *  3. Support base64 and binary certificate file provide by openssl.exe or certificate authority. 
 *      Don't support cermake.exe certificate file. This is xyssl open source limitation.
 * PARAMETERS
 * port : [IN] https port
 * cer_dir : [IN] The directory for https server certificate files. You must be include "httpd_ca.cer" / "httpd_server.cer" / "httpd_server.key". Total three files and can't change names.
 * peer_CN: [IN] The name of client certificate which one https server need verify. Example "HTTPD_CLIENT".
 * server_key_passwd : [IN] Pass word of "httpd_server.key" file. Your private key file need a password for protection.
 * RETURNS
 *  void
 * EXAMPLE
 * <code>
 *   vm_inet_httpd_enable_ssl(443, E:/https, HTTPD_CLIENT, 1234);
 *   vm_inet_httpd_start(80, E:/httpd, **.vxp);
 * </code>
 *****************************************************************************/
extern void vm_inet_httpd_enable_ssl(VMUINT32 port, VMINT8* cer_dir, VMINT8* peer_cn, VMINT8* server_key_passwd);

/*****************************************************************************
 * FUNCTION
 * vm_inet_httpd_disable_ssl
 * DESCRIPTION
 * this api can disable httpd for SSL. Then it can't support https.
 * PARAMETERS
 * N/A
 * RETURNS
 *  void
 * EXAMPLE
 * <code>
 *    vm_inet_httpd_stop();
 *    vm_inet_httpd_disable_ssl();
 * </code>
 *****************************************************************************/
extern void vm_inet_httpd_disable_ssl();

#ifdef __cplusplus
}
#endif/*__cplusplus*/

#endif/*VM_HTTPD_SDK_H*/