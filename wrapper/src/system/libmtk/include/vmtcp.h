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

#ifndef VMTCP_SDK_H
#define VMTCP_SDK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "vmsys.h"

/* tcp connected */
#define VM_TCP_EVT_CONNECTED	1

/* write status */
#define VM_TCP_EVT_CAN_WRITE	2

/* read status */
#define VM_TCP_EVT_CAN_READ		3

/* broken status */
#define VM_TCP_EVT_PIPE_BROKEN	4

/* not find host */
#define VM_TCP_EVT_HOST_NOT_FOUND	5

/* tcp pipe closed */
#define VM_TCP_EVT_PIPE_CLOSED	6

/* no enough resource to create tcp connection */
#define VM_TCP_ERR_NO_ENOUGH_RES	-1

/* create tcp connection failed */
#define VM_TCP_ERR_CREATE_FAILED	-2

/* use cmnet to connect */
#define VM_TCP_APN_CMNET		(1)

/* use cmwap to connect */
#define VM_TCP_APN_CMWAP		(2)

/* use wifi to connect */
#define VM_TCP_APN_WIFI		(3)

/* only use cmnet to connect */
#define VM_TCP_APN_CMNET_ONLY (4)

/* only use cmwap to connect */
#define VM_TCP_APN_CMWAP_ONLY (5)

/* only use when conbined with vm_dtacct_set */
//#define VM_APN_USER_DEFINE (6)

/* wifi hot spot account id */
#define VM_APN_WIFI_HS (7)

/* wifi ap mode account id */
#define VM_APN_AP_MODE (8)




/*****************************************************************************
 * FUNCTION
 *    vm_tcp_connect
 * DESCRIPTION
 *  create tcp connection.
 * PARAMETERS
 *  host : [IN] dest host ip.
 *  port : [IN] dest host port.
 *  apn : [IN] apn id, only support VM_TCP_APN_CMNET,VM_TCP_APN_CMWAP,VM_TCP_APN_WIFI.
 *  callback : [IN] callback function for tcp connection.
 * RETURNS
 *  create tcp success or not.
 * RETURN VALUES
 *  tcp handle, if value >=0, that is right, else is wrong
 * EXAMPLE
 * <code>
 *  static VMINT g_hl_tcp_hd;
 *  void hl_tcp_connect(void)
 *  {
 *      vm_enable_proxy(FALSE);
 *      g_hl_tcp_hd = vm_tcp_connect("www.mediatek.com", 80, VM_TCP_APN_CMNET, hl_tcp_conn_cb);
 *  }
 * </code>
*****************************************************************************/
VMINT vm_tcp_connect(const char* host, const VMINT port, const VMINT apn,
	void (*callback)(VMINT handle, VMINT event));

/*****************************************************************************
 * FUNCTION
 *    vm_tcp_connect
 * DESCRIPTION
 *  create tcp connection.
 * PARAMETERS
 *  host : [IN] dest host ip.
 *  port : [IN] dest host port.
 *  apn : [IN] apn id, only support VM_TCP_APN_CMNET,VM_TCP_APN_CMWAP,VM_TCP_APN_WIFI.
 *  user_data : [IN] user_data.
 *  callback : [IN] callback function for tcp connection.
 * RETURNS
 *  create tcp success or not.
 * RETURN VALUES
 *  tcp handle, if value >=0, that is right, else is wrong
 * EXAMPLE
 * <code>
 *  static VMINT g_hl_tcp_hd;
 *  void hl_tcp_conn_cb_ex(VMINT handle, VMINT event, void* user_data)
 *  {
 *      char* my_data = (char*)user_data;
 *      switch (event)
 *      {
 *          case VM_TCP_EVT_CONNECTED:
 *              vm_tcp_close(handle);
 *              return;
 *          default:
 *              return;
 *      }
 *  }
 *  void hl_tcp_connect(void)
 *  {
 *      char* my_data;
 *      my_data = (char*)vm_malloc(10);
 *      strcpy(my_data, "aa");
 *      vm_enable_proxy(FALSE);
 *      g_hl_tcp_hd = vm_tcp_connect_ex("www.mediatek.com", 80, VM_TCP_APN_CMNET, (void*)my_data, hl_tcp_conn_cb_ex);
 *  }
 * </code>
*****************************************************************************/
VMINT vm_tcp_connect_ex(const char* host, const VMINT port, const VMINT apn, void *user_data, 
	void (*callback)(VMINT handle, VMINT event, void *user_data));


/*****************************************************************************
 * FUNCTION
 *    vm_tcp_close
 * DESCRIPTION
 *  close tcp connection.
 * PARAMETERS
 *  handle : [IN] tcp handle.
 * EXAMPLE
 * <code>
 *  void hl_tcp_conn_cb(VMINT handle, VMINT event)
 *  {
 *      switch (event)
 *      {
 *          case VM_TCP_EVT_CONNECTED:
 *              vm_tcp_close(handle);
 *              return;
 *          default:
 *              return;
 *      }
 *  }
 * </code>
*****************************************************************************/
void vm_tcp_close(VMINT handle);

#define VM_TCP_READ_EOF				(-1)

/*****************************************************************************
 * FUNCTION
 *    vm_tcp_read
 * DESCRIPTION
 *  read data from tcp connection.
 * PARAMETERS
 *  handle : [IN] tcp handle.
 *  buf : [OUT] data buffer.
 *  len : [OUT] data length.
 * RETURNS
 *  read data size.
 * RETURN VALUES
 *  read size, if value = VM_TCP_READ_EOF, means finishing reading.
 * EXAMPLE
 * <code>
 *  void hl_tcp_conn_cb(VMINT handle, VMINT event)
 *  {
 *      char buf[100];
 *      VMINT nread, nwrite;
 *      switch (event)
 *      {
 *          case VM_TCP_EVT_CONNECTED:
 *              nwrite = vm_tcp_write(
 *                          handle,
 *                          "GET www.mediatek.com HTTP/1.1\r\nHost: www.mediatek.com\r\n\r\n",
 *                          strlen("GET www.mediatek.com HTTP/1.1\r\nHost: www.mediatek.com\r\n\r\n"));
 *              break;
 *          case VM_TCP_EVT_CAN_READ:
 *              memset(buf, 0, 100);
 *              nread = vm_tcp_read(handle, buf, 100);
 *              vm_tcp_close(handle);
 *              return;
 *          default:
 *              return;
 *      }
 *      return;
 *  }
 * </code>
*****************************************************************************/
VMINT vm_tcp_read(VMINT handle, void* buf, VMINT len);

/*****************************************************************************
 * FUNCTION
 *    vm_tcp_write
 * DESCRIPTION
 *  write data to tcp connection.
 * PARAMETERS
 *  handle : [IN] tcp handle.
 *  buf : [IN] data to write.
 *  len : [IN] data length.
 * RETURNS
 *  write data success or not.
 * RETURN VALUES
 *  if value >= 0 , it is right, else is wrong.
 * EXAMPLE
 * <code>
 *  void hl_tcp_conn_cb(VMINT handle, VMINT event)
 *  {
 *      VMINT nwrite;
 *      switch (event)
 *      {
 *          case VM_TCP_EVT_CONNECTED:
 *              nwrite = vm_tcp_write(
 *                          handle,
 *                          "GET www.mediatek.com HTTP/1.1\r\nHost: www.mediatek.com\r\n\r\n",
 *                          strlen("GET www.mediatek.com HTTP/1.1\r\nHost: www.mediatek.com\r\n\r\n"));
 *              break;
 *          default:
 *              return;
 *      }
 *      return;
 *  }
 * </code>
*****************************************************************************/
VMINT vm_tcp_write(VMINT handle, void* buf, VMINT len);

VMINT vm_tcp_get_soc_id(VMINT hdl);

/*****************************************************************************
 * FUNCTION
 *    vm_tcp_connect_sync
 * DESCRIPTION
 *  create tcp connection.
 * PARAMETERS
 *  pi: [IN] dest host ip. format is "123.123.123.123"
 *  port : [IN] dest host port.
 *  apn : [IN] apn id.
  * RETURNS
 *  create tcp success or not.
 * RETURN VALUES
 *  tcp handle, if value >=0, that is right, else is wrong
 * EXAMPLE
 * <code>
 *  static VMINT g_tcp_sync_hd;
 *  void hl_tcp_sync(void)
 *  {
 *      g_tcp_sync_hd = vm_tcp_connect_sync("172.21.90.164", 80, VM_TCP_APN_CMNET);
 *  }
 * </code>
*****************************************************************************/
VMINT vm_tcp_connect_sync(const char* ip, const VMINT port, VMINT apn);
/*****************************************************************************
 * FUNCTION
 *    vm_tcp_read_sync
 * DESCRIPTION
 *  read data from tcp connection.
 * PARAMETERS
 *  handle : [IN] tcp handle.
 *  buf : [OUT] data buffer.
 *  len : [OUT] data length.
 * RETURNS
 *  read data size.
 * RETURN VALUES
 *  read size, if value = VM_TCP_READ_EOF, means finishing reading.
 * EXAMPLE
 * <code>
 *  static VMINT g_tcp_sync_hd;
 *  void hl_tcp_sync(void)
 *  {
 *      VMINT read_data;
 *      VMBYTE buf[1024];
 *      VMINT ret;
 *      g_tcp_sync_hd = vm_tcp_connect_sync("172.21.90.164", 80, VM_TCP_APN_CMNET);
 *      read_data = vm_tcp_read_sync(g_tcp_sync_hd, buf, 1024);
 *      ret = vm_tcp_close_sync(g_tcp_sync_hd);
 *  }
 * </code>
*****************************************************************************/
VMINT vm_tcp_read_sync(VMINT handle, void* buf, VMINT len);
/*****************************************************************************
 * FUNCTION
 *    vm_tcp_write_sync
 * DESCRIPTION
 *  write data to tcp connection.
 * PARAMETERS
 *  handle : [IN] tcp handle.
 *  buf : [IN] data to write.
 *  len : [IN] data length.
 * RETURNS
 *  write data success or not.
 * RETURN VALUES
 *  if value >= 0 , it is right, else is wrong.
 * EXAMPLE
 * <code>
 * static VMINT g_tcp_sync_hd;
 * #define send ("GET / HTTP/1.1\r\nHost: www.mediatek.com:80\r\n\r\n")
 * void hl_tcp_sync(void)
 * {
 *    VMINT read_data;
 *    VMINT ret;
 *    g_tcp_sync_hd = vm_tcp_connect_sync("172.21.90.164", 80, VM_TCP_APN_CMNET);
 *    ret = vm_tcp_write_sync(g_tcp_sync_hd, send, strlen(send));
 *    ret = vm_tcp_close_sync(g_tcp_sync_hd);
 * }
 * </code>
*****************************************************************************/
VMINT vm_tcp_write_sync(VMINT handle, void* buf, VMINT len);
/*****************************************************************************
 * FUNCTION
 *    vm_tcp_close_sync
 * DESCRIPTION
 *  close tcp connection.
 * PARAMETERS
 *  handle : [IN] tcp handle.
 * EXAMPLE
 * <code>
 *  static VMINT g_tcp_sync_hd;
 *  void hl_tcp_sync(void)
 *  {
 *      g_tcp_sync_hd = vm_tcp_connect_sync("172.21.90.164", 80, VM_TCP_APN_CMNET);
 *      ret = vm_tcp_close_sync(g_tcp_sync_hd);
 *  }
 * </code>
*****************************************************************************/
VMINT vm_tcp_close_sync(VMINT handle);

/* Http server event */
typedef enum
{
    VM_SOC_SVR_EVT_ACCEPT,  /* Notify for accept */
    VM_SOC_SVR_EVT_READ,    /* Notify for read */
    VM_SOC_SVR_EVT_WRITE,   /* Notify for write */
    VM_SOC_SVR_EVT_CLOSED,  /* Notify for close */
    VM_SOC_SVR_EVT_ACTIVED, /* Notify for actived */
    VM_SOC_SVR_EVT_DEACTIVATED, /* Notify for deactived */
    VM_SOC_SVR_EVT_FAILED,  /* Notify for failed */
    VM_SOC_SVR_EVT_MAX
}vm_http_server_evt_t;

/*****************************************************************************
 * FUNCTION
 *    vm_soc_svr_init
 * DESCRIPTION
 *  Initiate server socket 
 * PARAMETERS
 *  apn : [IN] apn id.
 *  port: [IN] the port of server
 *  user_data: [IN] user's data, engine can pass it to callback
 *  callback:   [IN] app's callback function
 * RETURNS
 *  if successed return server handle, else return error code
 * EXAMPLE
 * <code>
 *  static VMINT svr_async_hdl;
 *  static VMINT clt_async_hdl;
 *  #define MAX_SIZE 1024*2
 *  VMBYTE buf[MAX_SIZE] = {0};
 *  static void svr_callback_async_cb(VMINT handle, VMINT event, VMINT param, void *user_data)
 *  {
 *  
 *      if (handle == svr_async_hdl || -8 == svr_async_hdl)
 *      {
 *          vm_trace("evt[%d]", event);
 *  
 *          switch (event)
 *          {
 *          case VM_SOC_SVR_EVT_ACTIVED:
 *              {
 *                  svr_async_hdl = handle;
 *                  vm_trace("ACTIVED");
 *                  vm_trace("[async svr] shdl[%d] [%d]", svr_async_hdl, (VMINT)user_data);
 *              }
 *              break;
 *          case VM_SOC_SVR_EVT_ACCEPT:
 *              {
 *                  clt_async_hdl = param;
 *                  vm_trace("ACCEPTED");
 *                  vm_trace("[async svr] chdl[%d] [%d]", clt_async_hdl, (VMINT)user_data);
 *              }
 *              break;
 *          case VM_SOC_SVR_EVT_READ:
 *              {
 *                  VMINT ret = 0;
 *                  ret = vm_soc_svr_read(svr_async_hdl, clt_async_hdl, buf, MAX_SIZE);
 *                  vm_trace("READ [%d/%d]", ret, MAX_SIZE);
 *                  ret = vm_soc_svr_send(svr_async_hdl, clt_async_hdl, "abc", 3);
 *                  vm_trace("SENT [%d]", ret);
 *                  vm_soc_svr_close_client(clt_async_hdl);
 *              }
 *              break;
 *          case VM_SOC_SVR_EVT_WRITE:
 *              break;
 *          case VM_SOC_SVR_EVT_CLOSED:
 *              break;
 *          default:
 *              break;
 *          }
 *      }
 *  }
 *  void hl_tcp_srv(void)
 *  {
 *      svr_async_hdl = vm_soc_svr_init(1, 3501, (void*)1, svr_callback_async_cb);
 *  }
 * </code>
*****************************************************************************/
VMINT vm_soc_svr_init(VMINT apn, VMINT port, void *user_data, void (*callback)(VMINT handle, VMINT event, VMINT param, void *user_data));

/*****************************************************************************
 * FUNCTION
 *    vm_soc_svr_send
 * DESCRIPTION
 *  Send data
 * PARAMETERS
 *  s_hdl : [IN]server handle.
 *  c_hdl: [IN] client handle.
 *  data: [IN] data to be sent
 *  len:   [IN] data length
 * RETURNS
 *  if >=0 means number of bytes sent, else send failed
 * EXAMPLE
 * <code>
 *  static VMINT svr_async_hdl;
 *  static VMINT clt_async_hdl;
 *  #define MAX_SIZE 1024*2
 *  VMBYTE buf[MAX_SIZE] = {0};
 *  static void svr_callback_async_cb(VMINT handle, VMINT event, VMINT param, void *user_data)
 *  {
 *  
 *      if (handle == svr_async_hdl || -8 == svr_async_hdl)
 *      {
 *          vm_trace("evt[%d]", event);
 *  
 *          switch (event)
 *          {
 *          case VM_SOC_SVR_EVT_ACTIVED:
 *              {
 *                  svr_async_hdl = handle;
 *                  vm_trace("ACTIVED");
 *                  vm_trace("[async svr] shdl[%d] [%d]", svr_async_hdl, (VMINT)user_data);
 *              }
 *              break;
 *          case VM_SOC_SVR_EVT_ACCEPT:
 *              {
 *                  clt_async_hdl = param;
 *                  vm_trace("ACCEPTED");
 *                  vm_trace("[async svr] chdl[%d] [%d]", clt_async_hdl, (VMINT)user_data);
 *              }
 *              break;
 *          case VM_SOC_SVR_EVT_READ:
 *              {
 *                  VMINT ret = 0;
 *                  ret = vm_soc_svr_read(svr_async_hdl, clt_async_hdl, buf, MAX_SIZE);
 *                  vm_trace("READ [%d/%d]", ret, MAX_SIZE);
 *                  ret = vm_soc_svr_send(svr_async_hdl, clt_async_hdl, "abc", 3);
 *                  vm_trace("SENT [%d]", ret);
 *                  vm_soc_svr_close_client(clt_async_hdl);
 *              }
 *              break;
 *          case VM_SOC_SVR_EVT_WRITE:
 *              break;
 *          case VM_SOC_SVR_EVT_CLOSED:
 *              break;
 *          default:
 *              break;
 *          }
 *      }
 *  }
 *  void hl_tcp_srv(void)
 *  {
 *      svr_async_hdl = vm_soc_svr_init(1, 3501, (void*)1, svr_callback_async_cb);
 *  }
 * </code>
*****************************************************************************/
VMINT vm_soc_svr_send(VMINT s_hdl, VMINT c_hdl, const void *data, VMUINT len);

/*****************************************************************************
 * FUNCTION
 *    vm_soc_svr_read
 * DESCRIPTION
 *  Read data
 * PARAMETERS
 *  s_hdl : [IN]server handle.
 *  c_hdl: [IN] client handle.
 *  data: [IN] data to be sent
 *  len:   [IN] data length
 * RETURNS
 *  if >=0 means number of bytes received, else receive failed
 * EXAMPLE
 * <code>
 *  static VMINT svr_async_hdl;
 *  static VMINT clt_async_hdl;
 *  #define MAX_SIZE 1024*2
 *  VMBYTE buf[MAX_SIZE] = {0};
 *  static void svr_callback_async_cb(VMINT handle, VMINT event, VMINT param, void *user_data)
 *  {
 *  
 *      if (handle == svr_async_hdl || -8 == svr_async_hdl)
 *      {
 *          vm_trace("evt[%d]", event);
 *  
 *          switch (event)
 *          {
 *          case VM_SOC_SVR_EVT_ACTIVED:
 *              {
 *                  svr_async_hdl = handle;
 *                  vm_trace("ACTIVED");
 *                  vm_trace("[async svr] shdl[%d] [%d]", svr_async_hdl, (VMINT)user_data);
 *              }
 *              break;
 *          case VM_SOC_SVR_EVT_ACCEPT:
 *              {
 *                  clt_async_hdl = param;
 *                  vm_trace("ACCEPTED");
 *                  vm_trace("[async svr] chdl[%d] [%d]", clt_async_hdl, (VMINT)user_data);
 *              }
 *              break;
 *          case VM_SOC_SVR_EVT_READ:
 *              {
 *                  VMINT ret = 0;
 *                  ret = vm_soc_svr_read(svr_async_hdl, clt_async_hdl, buf, MAX_SIZE);
 *                  vm_trace("READ [%d/%d]", ret, MAX_SIZE);
 *                  ret = vm_soc_svr_send(svr_async_hdl, clt_async_hdl, "abc", 3);
 *                  vm_trace("SENT [%d]", ret);
 *                  vm_soc_svr_close_client(clt_async_hdl);
 *              }
 *              break;
 *          case VM_SOC_SVR_EVT_WRITE:
 *              break;
 *          case VM_SOC_SVR_EVT_CLOSED:
 *              break;
 *          default:
 *              break;
 *          }
 *      }
 *  }
 *  void hl_tcp_srv(void)
 *  {
 *      svr_async_hdl = vm_soc_svr_init(1, 3501, (void*)1, svr_callback_async_cb);
 *  }
 * </code>
*****************************************************************************/
VMINT vm_soc_svr_read(VMINT s_hdl, VMINT c_hdl, void *data, VMUINT len);

/*****************************************************************************
 * FUNCTION
 *    vm_soc_svr_close_client
 * DESCRIPTION
 *  Close client
 * PARAMETERS
 *  c_hdl: [IN] client handle.
 * RETURNS
 * If return 0 means success, else fail.
 * EXAMPLE
 * <code>
 *  static VMINT svr_async_hdl;
 *  static VMINT clt_async_hdl;
 *  #define MAX_SIZE 1024*2
 *  VMBYTE buf[MAX_SIZE] = {0};
 *  static void svr_callback_async_cb(VMINT handle, VMINT event, VMINT param, void *user_data)
 *  {
 *  
 *      if (handle == svr_async_hdl || -8 == svr_async_hdl)
 *      {
 *          vm_trace("evt[%d]", event);
 *  
 *          switch (event)
 *          {
 *          case VM_SOC_SVR_EVT_ACTIVED:
 *              {
 *                  svr_async_hdl = handle;
 *                  vm_trace("ACTIVED");
 *                  vm_trace("[async svr] shdl[%d] [%d]", svr_async_hdl, (VMINT)user_data);
 *              }
 *              break;
 *          case VM_SOC_SVR_EVT_ACCEPT:
 *              {
 *                  clt_async_hdl = param;
 *                  vm_trace("ACCEPTED");
 *                  vm_trace("[async svr] chdl[%d] [%d]", clt_async_hdl, (VMINT)user_data);
 *              }
 *              break;
 *          case VM_SOC_SVR_EVT_READ:
 *              {
 *                  VMINT ret = 0;
 *                  ret = vm_soc_svr_read(svr_async_hdl, clt_async_hdl, buf, MAX_SIZE);
 *                  vm_trace("READ [%d/%d]", ret, MAX_SIZE);
 *                  ret = vm_soc_svr_send(svr_async_hdl, clt_async_hdl, "abc", 3);
 *                  vm_trace("SENT [%d]", ret);
 *                  vm_soc_svr_close_client(clt_async_hdl);
 *              }
 *              break;
 *          case VM_SOC_SVR_EVT_WRITE:
 *              break;
 *          case VM_SOC_SVR_EVT_CLOSED:
 *              break;
 *          default:
 *              break;
 *          }
 *      }
 *  }
 *  void hl_tcp_srv(void)
 *  {
 *      svr_async_hdl = vm_soc_svr_init(1, 3501, (void*)1, svr_callback_async_cb);
 *  }
 * </code>
*****************************************************************************/
VMINT vm_soc_svr_close_client(VMINT c_hdl);

/*****************************************************************************
 * FUNCTION
 *    vm_soc_svr_deinit
 * DESCRIPTION
 *  Deinit socket server
 * PARAMETERS
 *  handle: [IN] server handle.
 * RETURNS
 * 0
 * EXAMPLE
 * <code>
 *  static VMINT svr_async_hdl;
 *  static VMINT clt_async_hdl;
 *  #define MAX_SIZE 1024*2
 *  VMBYTE buf[MAX_SIZE] = {0};
 *  static void svr_callback_async_cb(VMINT handle, VMINT event, VMINT param, void *user_data)
 *  {
 *  
 *      if (handle == svr_async_hdl || -8 == svr_async_hdl)
 *      {
 *          vm_trace("evt[%d]", event);
 *  
 *          switch (event)
 *          {
 *          case VM_SOC_SVR_EVT_ACTIVED:
 *              {
 *                  svr_async_hdl = handle;
 *                  vm_trace("ACTIVED");
 *                  vm_trace("[async svr] shdl[%d] [%d]", svr_async_hdl, (VMINT)user_data);
 *              }
 *              break;
 *          case VM_SOC_SVR_EVT_ACCEPT:
 *              {
 *                  clt_async_hdl = param;
 *                  vm_trace("ACCEPTED");
 *                  vm_trace("[async svr] chdl[%d] [%d]", clt_async_hdl, (VMINT)user_data);
 *              }
 *              break;
 *          case VM_SOC_SVR_EVT_READ:
 *              {
 *                  VMINT ret = 0;
 *                  ret = vm_soc_svr_read(svr_async_hdl, clt_async_hdl, buf, MAX_SIZE);
 *                  vm_trace("READ [%d/%d]", ret, MAX_SIZE);
 *                  ret = vm_soc_svr_send(svr_async_hdl, clt_async_hdl, "abc", 3);
 *                  vm_trace("SENT [%d]", ret);
 *                  vm_soc_svr_close_client(clt_async_hdl);
 *                  vm_soc_svr_deinit(svr_async_hdl);
 *              }
 *              break;
 *          case VM_SOC_SVR_EVT_WRITE:
 *              break;
 *          case VM_SOC_SVR_EVT_CLOSED:
 *              break;
 *          default:
 *              break;
 *          }
 *      }
 *  }
 *  void hl_tcp_srv(void)
 *  {
 *      svr_async_hdl = vm_soc_svr_init(1, 3501, (void*)1, svr_callback_async_cb);
 *  }
 * </code>
*****************************************************************************/
VMINT vm_soc_svr_deinit(VMINT handle);

/*****************************************************************************
 * FUNCTION
 *    vm_soc_svr_get_soc_id
 * DESCRIPTION
 *  Get the socket id of the server
 * PARAMETERS
 *  handle: [IN] server handle.
 * RETURNS
 * return -2 if failed, else return the socket id
 * EXAMPLE
 * <code>
 *  static VMINT svr_async_hdl;
 *  static VMINT clt_async_hdl;
 *  #define MAX_SIZE 1024*2
 *  VMBYTE buf[MAX_SIZE] = {0};
 *  static void svr_callback_async_cb(VMINT handle, VMINT event, VMINT param, void *user_data)
 *  {
 *      VMINT svr_soc_id;
 *      if (handle == svr_async_hdl || -8 == svr_async_hdl)
 *      {
 *          vm_trace("evt[%d]", event);
 *  
 *          switch (event)
 *          {
 *          case VM_SOC_SVR_EVT_ACTIVED:
 *              {
 *                  svr_async_hdl = handle;
 *                  svr_soc_id = vm_soc_svr_get_soc_id(svr_async_hdl);
 *                  vm_trace("ACTIVED");
 *                  vm_trace("[async svr] shdl[%d] soc_id[%d] [%d]", svr_async_hdl, svr_soc_id, (VMINT)user_data);
 *              }
 *              break;
 *          case VM_SOC_SVR_EVT_ACCEPT:
 *              {
 *                  clt_async_hdl = param;
 *                  vm_trace("ACCEPTED");
 *                  vm_trace("[async svr] chdl[%d] [%d]", clt_async_hdl, (VMINT)user_data);
 *              }
 *              break;
 *          case VM_SOC_SVR_EVT_READ:
 *              {
 *                  VMINT ret = 0;
 *                  ret = vm_soc_svr_read(svr_async_hdl, clt_async_hdl, buf, MAX_SIZE);
 *                  vm_trace("READ [%d/%d]", ret, MAX_SIZE);
 *                  ret = vm_soc_svr_send(svr_async_hdl, clt_async_hdl, "abc", 3);
 *                  vm_trace("SENT [%d]", ret);
 *                  vm_soc_svr_close_client(clt_async_hdl);
 *                  vm_soc_svr_deinit(svr_async_hdl);
 *              }
 *              break;
 *          case VM_SOC_SVR_EVT_WRITE:
 *              break;
 *          case VM_SOC_SVR_EVT_CLOSED:
 *              break;
 *          default:
 *              break;
 *          }
 *      }
 *  }
 *  void hl_tcp_srv(void)
 *  {
 *      svr_async_hdl = vm_soc_svr_init(1, 3501, (void*)1, svr_callback_async_cb);
 *  }
 * </code>
*****************************************************************************/
VMINT vm_soc_svr_get_soc_id(VMINT handle);


/*****************************************************************************
 * FUNCTION
 *    vm_soc_svr_init_sync
 * DESCRIPTION
 *  Initiate socket server synchronously
 * PARAMETERS
 *  apn: [IN] apn id.
 *  port: [IN]  port number associate to the server.
 * RETURNS
 *  if successed return server handle, else return error code
 * EXAMPLE
 * <code>
 *  void hl_tcp_sync_srv(void)
 *  {
 *      vm_sockaddr_struct addr;
 *      VMINT ret;
 *      char buf[1024] = {0};
 *      VMINT hdl_c;
 *      VMINT hdl_s = vm_soc_svr_init_sync(1, 3500);
 *      hdl_c = vm_soc_svr_accept_sync(hdl_s, &addr);
 *      ret = vm_soc_svr_read_sync(hdl_c, buf, 1024);
 *      ret = vm_soc_svr_send_sync(hdl_c, "aaa", 3);
 *      vm_soc_svr_close_client_sync(hdl_c);
 *  }
 * </code>
*****************************************************************************/
VMINT vm_soc_svr_init_sync(VMINT apn, VMINT port);

/*****************************************************************************
 * FUNCTION
 *    vm_soc_svr_accept_sync
 * DESCRIPTION
 *  Waits for the incoming connections and return a socket handle
 *  of new connection.
 * PARAMETERS
 *  s_hdl: [IN] server handle.
 *  addr: [IN]  address of foreign host
 * RETURNS
 *  if successed return a socket handle, else return error code
 * EXAMPLE
 * <code>
 *  void hl_tcp_sync_srv(void)
 *  {
 *      vm_sockaddr_struct addr;
 *      VMINT ret;
 *      char buf[1024] = {0};
 *      VMINT hdl_c;
 *      VMINT hdl_s = vm_soc_svr_init_sync(1, 3500);
 *      hdl_c = vm_soc_svr_accept_sync(hdl_s, &addr);
 *      ret = vm_soc_svr_read_sync(hdl_c, buf, 1024);
 *      ret = vm_soc_svr_send_sync(hdl_c, "aaa", 3);
 *      vm_soc_svr_close_client_sync(hdl_c);
 *  }
 * </code>
*****************************************************************************/
VMINT vm_soc_svr_accept_sync(VMINT s_hdl, vm_sockaddr_struct *addr);

/*****************************************************************************
 * FUNCTION
 *    vm_soc_svr_send_sync
 * DESCRIPTION
 *  sends data to a host which already connected previously.
 * PARAMETERS
 *  c_hdl: [IN] apn id.
 *  data: [IN]  data to be sent.
 *  len: [IN]   data length
 * RETURNS
 *  if >=0 means number of bytes sent, else sent failed
 * EXAMPLE
 * <code>
 *  void hl_tcp_sync_srv(void)
 *  {
 *      vm_sockaddr_struct addr;
 *      VMINT ret;
 *      char buf[1024] = {0};
 *      VMINT hdl_c;
 *      VMINT hdl_s = vm_soc_svr_init_sync(1, 3500);
 *      hdl_c = vm_soc_svr_accept_sync(hdl_s, &addr);
 *      ret = vm_soc_svr_read_sync(hdl_c, buf, 1024);
 *      ret = vm_soc_svr_send_sync(hdl_c, "aaa", 3);
 *      vm_soc_svr_close_client_sync(hdl_c);
 *  }
 * </code>
*****************************************************************************/
VMINT vm_soc_svr_send_sync(VMINT c_hdl, const void *data, VMUINT len);

/*****************************************************************************
 * FUNCTION
 *    vm_soc_svr_read_sync
 * DESCRIPTION
 *  Read data synchronously
 * PARAMETERS
 *  c_hdl: [IN] client handle.
 *  data: [IN]  buffer for read data.
 *  len:  [IN}  buffer length
 * RETURNS
 *  if >=0 means number of bytes read, else read failed
 * EXAMPLE
 * <code>
 *  void hl_tcp_sync_srv(void)
 *  {
 *      vm_sockaddr_struct addr;
 *      VMINT ret;
 *      char buf[1024] = {0};
 *      VMINT hdl_c;
 *      VMINT hdl_s = vm_soc_svr_init_sync(1, 3500);
 *      hdl_c = vm_soc_svr_accept_sync(hdl_s, &addr);
 *      ret = vm_soc_svr_read_sync(hdl_c, buf, 1024);
 *      ret = vm_soc_svr_send_sync(hdl_c, "aaa", 3);
 *      vm_soc_svr_close_client_sync(hdl_c);
 *  }
 * </code>
*****************************************************************************/
VMINT vm_soc_svr_read_sync(VMINT c_hdl, void *data, VMUINT len);

/*****************************************************************************
 * FUNCTION
 *    vm_soc_svr_close_client_sync
 * DESCRIPTION
 *  Close client socket synchronously
 * PARAMETERS
 *  c_hdl  [IN]   Client handle
 * RETURNS
 * If return 0 means success, else fail.
 * EXAMPLE
 * <code>
 *  void hl_tcp_sync_srv(void)
 *  {
 *      vm_sockaddr_struct addr;
 *      VMINT ret;
 *      char buf[1024] = {0};
 *      VMINT hdl_c;
 *      VMINT hdl_s = vm_soc_svr_init_sync(1, 3500);
 *      hdl_c = vm_soc_svr_accept_sync(hdl_s, &addr);
 *      ret = vm_soc_svr_read_sync(hdl_c, buf, 1024);
 *      ret = vm_soc_svr_send_sync(hdl_c, "aaa", 3);
 *      vm_soc_svr_close_client_sync(hdl_c);
 *  }
 * </code>
*****************************************************************************/
VMINT vm_soc_svr_close_client_sync(VMINT c_hdl);

/*****************************************************************************
 * FUNCTION
 *    vm_soc_svr_deinit_sync
 * DESCRIPTION
 *  Deinitiate socket server synchronously
 * PARAMETERS
 *  s_hdl   [IN]     server handle
 * RETURNS
 *  if return 0 means operate successfully, else failed
 * EXAMPLE
 * <code>
 *  void hl_tcp_sync_srv(void)
 *  {
 *      vm_sockaddr_struct addr;
 *      VMINT ret;
 *      char buf[1024] = {0};
 *      VMINT hdl_c;
 *      VMINT hdl_s = vm_soc_svr_init_sync(1, 3500);
 *      hdl_c = vm_soc_svr_accept_sync(hdl_s, &addr);
 *      ret = vm_soc_svr_read_sync(hdl_c, buf, 1024);
 *      ret = vm_soc_svr_send_sync(hdl_c, "aaa", 3);
 *      vm_soc_svr_close_client_sync(hdl_c);
 *      vm_soc_svr_deinit_sync(hdl_s);
 *  }
 * </code>
*****************************************************************************/
VMINT vm_soc_svr_deinit_sync(VMINT s_hdl);


#ifdef __cplusplus
}
#endif

#endif /* VMTCP_SDK_H */

