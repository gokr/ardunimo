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

#ifndef VMCONN_SDK_H
#define VMCONN_SDK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "vmsys.h"


#define VM_MAX_SOCK_ADDR_LEN 28

/* Socket address struct */
typedef struct 
{
    VMINT16	addr_len; /* address length */
    VMUINT16	port; /* port number */
    VMUINT8	addr[VM_MAX_SOCK_ADDR_LEN]; /* address */
} vm_sockaddr_struct;


/* only use when conbined with vm_dtacct_set */
#define VM_APN_USER_DEFINE (6)


/* APN information struct */
typedef struct  
{
	VMINT		apn_info_id;    /* indicate use proxy or not, 1 means use */
	VMINT		proxy_port;     /* proxy port */
	VMCHAR     operator_id[8];  /* empty string */
	VMCHAR     operator_name[64];   /* empty string */
	VMCHAR     proxy_ip[16];    /* proxy ip address */
	VMCHAR     apn_proxy[32];   /* empty string */
	VMCHAR     apn_no_proxy[32];    /* empty string */
	VMCHAR     user_name[16];   /* proxy auth. ID */
	VMCHAR     pass_word[16];   /* proxy auto. password */
}vm_apn_info_ext;


/*****************************************************************************
 * FUNCTION
 *    vm_is_support_wifi
 * DESCRIPTION
 *  query wifi support.
 * RETURNS
 *  support or not support wifi.
 * RETURN VALUES
 *  TRUE : support wifi
 *  FALSE : not support wifi
*****************************************************************************/
VMINT vm_is_support_wifi(void);


/*****************************************************************************
 * FUNCTION
 *    vm_wifi_is_connected
 * DESCRIPTION
 *  query wifi contect.
 * RETURNS
 *  contected or not contected wifi.
 * RETURN VALUES
 *  TRUE : wifi contect.
 *  FALSE : wifi not contected.
*****************************************************************************/
VMINT vm_wifi_is_connected(void);


/*****************************************************************************
 * FUNCTION
 *  vm_get_apn_info
 * DESCRIPTION
 *  Get Apn info after network connected
 * PARAMETERS
 *  current_apn_info : [OUT] apn info of current connection
 * RETURNS
 *  0 means successful
 * RETURN VALUES
 *  0 : successful
*****************************************************************************/
VMINT vm_get_apn_info(vm_apn_info_ext *current_apn_info);

/*****************************************************************************
 * FUNCTION
 *    vm_get_default_apn_info
 * DESCRIPTION
 *  get current default apn infomation.
 * RETURNS
 *  avaliable or not.
 * RETURN VALUES
 *  0 sucess, else failure
*****************************************************************************/
VMINT vm_get_default_apn_info( vm_apn_info_ext *apn_info);


#define VM_SOC_DNS_MAX_ADDR 5

/* Socket return codes, negative values stand for errors */
typedef enum
{
    VM_E_SOC_SUCCESS           = 0,     /* success */
    VM_E_SOC_ERROR             = -1,    /* error */
    VM_E_SOC_WOULDBLOCK        = -2,    /* not done yet */
    VM_E_SOC_LIMIT_RESOURCE    = -3,    /* limited resource */
    VM_E_SOC_INVALID_SOCKET    = -4,    /* invalid socket */
    VM_E_SOC_INVALID_ACCOUNT   = -5,    /* invalid account id */
    VM_E_SOC_NAMETOOLONG       = -6,    /* address too long */
    VM_E_SOC_ALREADY           = -7,    /* operation already in progress */
    VM_E_SOC_OPNOTSUPP         = -8,    /* operation not support */
    VM_E_SOC_CONNABORTED       = -9,    /* Software caused connection abort */
    VM_E_SOC_INVAL             = -10,   /* invalid argument */
    VM_E_SOC_PIPE              = -11,   /* broken pipe */
    VM_E_SOC_NOTCONN           = -12,   /* socket is not connected */
    VM_E_SOC_MSGSIZE           = -13,   /* msg is too long */
    VM_E_SOC_BEARER_FAIL       = -14,   /* bearer is broken */
    VM_E_SOC_CONNRESET         = -15,   /* TCP half-write close, i.e., FINED */
    VM_E_SOC_DHCP_ERROR        = -16,   /* DHCP error */
    VM_E_SOC_IP_CHANGED        = -17,   /* IP has changed */
    VM_E_SOC_ADDRINUSE         = -18,   /* address already in use */
    VM_E_SOC_CANCEL_ACT_BEARER = -19    /* cancel the activation of bearer */
} vm_soc_error_enum;

/* dns query result struct */
typedef struct
{
    VMUINT address[VM_SOC_DNS_MAX_ADDR];    /* ip address */
    VMINT num;
    VMINT error_cause; /* vm_ps_cause_enum */
}vm_soc_dns_result;
/*
VMINT vm_soc_get_host_by_name(const VMCHAR * host,
                                                            VMBYTE * addr,
                                                            VMBYTE * addr_len,
                                                            VMINT (*callback)(VMBYTE * addr, VMINT addr_len));
*/          
    
/*****************************************************************************
 * FUNCTION
 *  vm_soc_get_host_by_name
 * DESCRIPTION
 *  this function retrieves IP addresses associated with the specified host name. 
 * PARAMETERS
 * apn : [IN] 
 * host : [IN] domain to be resolved.
 * result : [OUT] DNS parsed result.
 * callback : [IN] point to the callback.
 * RETURNS
 *  success if 0, else failure.
 * RETURN VALUES
 *  VM_E_SOC_SUCCESS :			     Get IP address successfully, result is filled.
 *  VM_E_SOC_WOULDBLOCK :		     wait response from network, result could be gotten from callback.
 *  VM_E_SOC_INVAL :			         invalid arguments: null domain_name, etc.
 *  VM_E_SOC_ERROR :			         unspecified error
 *  VM_E_SOC_LIMIT_RESOURCE :		 socket resources not available
 *  VM_E_SOC_INVALID_ACCOUNT :      invalid data account id
 * EXAMPLE
 * <code>
 *  VMINT vat_vmsock_gethost_cb(vm_soc_dns_result *dns)
 *  {
 *      return FALSE;
 *  }
 *  void vat_vmsock_gethost_1(VATExt *po)
 *  {
 *      VMINT ret = -1;
 *      VMINT apn = VM_TCP_APN_CMNET;
 *      vm_soc_dns_result dns;
 *      if (vm_wifi_is_connected()) {
 *          apn = VM_TCP_APN_WIFI;
 *      }
 *      ret = vm_soc_get_host_by_name(apn, "www.mediatek.com", &dns, vat_vmsock_gethost_cb);
 *  
 *      switch (ret) {
 *          case VM_E_SOC_SUCCESS:
 *              break;
 *          case VM_E_SOC_WOULDBLOCK:
 *              break;
 *          default:
 *              break;
 *      }
 *  }
 * </code>
*****************************************************************************/
VMINT vm_soc_get_host_by_name(VMINT apn, 
                                                                            const VMCHAR * host, 
                                                                            vm_soc_dns_result * result, 
                                                                            VMINT (*callback)(vm_soc_dns_result *));
                                                                            
/*****************************************************************************
 * FUNCTION
 *  vm_soc_get_host_by_name_ex
 * DESCRIPTION
 *  this function retrieves IP addresses associated with the specified host name. 
 * PARAMETERS
 * apn : [IN] 
 * host : [IN] domain to be resolved.
 * result : [OUT] DNS parsed result.
 * callback : [IN] point to the callback.
 * RETURNS
 *  handle if more than 0, else failure.
 * EXAMPLE
 * <code>
 * VMINT vat_vmsock_gethost_cb_ex(VMINT handle, vm_soc_dns_result *dns, void *user_data)
 * {
 *     return FALSE;
 * }
 * void vat_vmsock_gethost_ex(VATExt *po)
 * {
 *     VMINT ret = -1;
 *     VMINT apn = VM_TCP_APN_CMNET;
 *     vm_soc_dns_result dns;
 *     if (vm_wifi_is_connected()) {
 *         apn = VM_TCP_APN_WIFI;
 *     }
 *     ret = vm_soc_get_host_by_name_ex(apn, "www.mediatek.com", &dns, vat_vmsock_gethost_cb_ex, NULL);
 * 
 *     switch (ret) {
 *         case VM_E_SOC_SUCCESS:
 *             break;
 *         case VM_E_SOC_WOULDBLOCK:
 *             break;
 *         default:
 *             break;
 *     }
 * }
 * </code>
*****************************************************************************/
VMINT vm_soc_get_host_by_name_ex(VMINT apn, 
                                 const VMCHAR * host, 
                                 vm_soc_dns_result * result, 
                                 VMINT (*callback)(VMINT, vm_soc_dns_result *, void *), void *user_data);
/*****************************************************************************
 * FUNCTION
 *  vm_get_encoded_dtacct_id
 * DESCRIPTION
 *  this function retrieves data account id. 
 * PARAMETERS
 * apn : [IN] apn id, only support VM_TCP_APN_CMNET, VM_TCP_APN_WIFI
 * dtacct_id : [OUT] point to data account id.
 * RETURNS
 *  success if 0, else failure.
 * RETURN VALUES
 *  VM_E_SOC_SUCCESS :               Get IP address successfully, result is filled.
 *  VM_E_SOC_INVAL :                     invalid arguments: null domain_name, etc.
 *  VM_E_SOC_INVALID_ACCOUNT :      invalid data account id
 * EXAMPLE
 * <code>
 *  void vat_vmsock_dtacct_1(void)
 *  {
 *      VMINT ret = -1;
 *      VMINT apn = VM_TCP_APN_CMNET;
 *      VMUINT dtacct_id;
 *  
 *      if (vm_wifi_is_connected()) {
 *          apn = VM_TCP_APN_WIFI;
 *      }
 *  
 *      ret = vm_get_encoded_dtacct_id(apn, &dtacct_id);
 *      if (ret == VM_E_SOC_SUCCESS) {
 *      }
 *      else {
 *      }
 *  }
 * </code>
*****************************************************************************/
VMINT vm_get_encoded_dtacct_id(VMINT apn, VMUINT * dtacct_id);






/* MAC address length */
#define VM_WLAN_LOC_MAC_ADDR_LEN 6
/* Maximum ap list number */
#define VM_WLAN_LOC_MAX_AP_LIST_NUM 30

/* Wlan scan error */
typedef enum
{
    VM_WLAN_LOC_ERR_LOGICAL = -7,  /* wlan is inactive state */
    VM_WLAN_LOC_ERR_INTERNAL,       /* Internal error */
    VM_WLAN_LOC_ERR_BUSY,           /* Can't create a new scan job */
    VM_WLAN_LOC_ERR_BAD_PARAM,      /* bad parameter */
    VM_WLAN_LOC_ERR_NO_RESOURCE,    /* allocate resource failed */
    VM_WLAN_LOC_ERR_NOT_SUPPORT,    /* project doesn't support wlan */
    VM_WLAN_LOC_ERR_NO_AUTHORIZATION,
    VM_WLAN_LOC_ERR_SUCCESS = 0
}vm_wlan_loc_error_t;

/* Wlan scan result */
typedef enum
{
    VM_WLAN_LOC_SCAN_RESULT_SUCCESS = 0,   /* WLAN scan success */
    VM_WLAN_LOC_SCAN_RESULT_FAILED,        /* WLAN scan failed */
    VM_WLAN_LOC_SCAN_RESULT_ABORTED,       /* WLAN scan service is aborted */
    VM_WLAN_LOC_SCAN_RESULT_TOTAL
} vm_wlan_loc_scan_result_enum;

/* wlan connected information struct */
typedef struct
{
    VMUINT8 bssid[VM_WLAN_LOC_MAC_ADDR_LEN]; /* MAC address */
    VMINT rssi;     /* rssi information */
}vm_wlan_loc_supc_abm_bss_info_struct;

typedef struct
{
    const vm_wlan_loc_supc_abm_bss_info_struct * ap_list[VM_WLAN_LOC_MAX_AP_LIST_NUM]; /* bss info array */
    VMINT handle;
    vm_wlan_loc_scan_result_enum result;     /* scan result enum */
    VMUINT8 ap_list_num;/* total num of searched ap list */
}vm_wlan_loc_data_t;


/*****************************************************************************
 * FUNCTION
 *  vm_wlan_loc_search
 * DESCRIPTION
 *  The function is used to scan the AP list for applications.
 * PARAMETERS
 *  callback    :   [IN]    scan result callback notify function for APP
 *  user_data   :   [IN]    application piggyback data
 * RETURNS
 *  return value >= 0 : search handle id created successfully.
 *  return value < 0 : failure
 * RETURN VALUES
 *  VM_WLAN_LOC_ERR_BUSY : busy, could retry later
 *  VM_WLAN_LOC_ERR_NO_RESOURCE : no avalible resource
 *  VM_WLAN_LOC_ERR_NOT_SUPPORT : platform dose not support
 * EXAMPLE
 * <code>
 *  static VMINT g_wlan_hd;
 *  void vat_vmsock_wlan_search_cb(vm_wlan_loc_data_t *wlan_data, void *user_data)
 *  {
 *       switch (wlan_data->result) {
 *          case VM_WLAN_LOC_SCAN_RESULT_SUCCESS:
 *          {
 *              vm_wlan_loc_search_abort(g_wlan_hd);
 *              break;
 *          }
 *          case VM_WLAN_LOC_SCAN_RESULT_FAILED:
 *              vm_wlan_loc_search_abort(g_wlan_hd);
 *              break;
 *          case VM_WLAN_LOC_SCAN_RESULT_ABORTED:
 *              g_wlan_hd = -1;
 *              break;
 *          default:
 *              break;
 *      }
 *  }
 *  void vat_vmsock_wlan_search_1(void)
 *  {
 *      VMINT ret = -1;
 *  
 *      ret = vm_wlan_loc_search(vat_vmsock_wlan_search_cb, NULL);
 *      if (VM_WLAN_LOC_ERR_NOT_SUPPORT != ret && 0 <= ret) {
 *          g_wlan_hd = ret;
 *      }
 *  }
 * </code>
*****************************************************************************/
VMINT vm_wlan_loc_search(void (*callback)(vm_wlan_loc_data_t * data, void * user_data), void * user_data);

/*****************************************************************************
 * FUNCTION
 *  vm_wlan_loc_search_abort
 * DESCRIPTION
 *  The function is used to abort the scanning AP list process for applications.
 * PARAMETERS
 *  handle  :   [IN]    created handle id from calling vm_wlan_loc_search
 * RETURNS
 *  success if 0, else failure.
 * RETURN VALUES
 *  VM_WLAN_LOC_ERR_BAD_PARAM : invalid input param
 *  VM_WLAN_LOC_ERR_NO_RESOURCE : no avalible resource
 *  VM_WLAN_LOC_ERR_NOT_SUPPORT : platform dose not support
 * EXAMPLE
 * <code>
 *  static VMINT g_wlan_hd;
 *  void vat_vmsock_wlan_search_cb(vm_wlan_loc_data_t *wlan_data, void *user_data)
 *  {
 *       switch (wlan_data->result) {
 *          case VM_WLAN_LOC_SCAN_RESULT_SUCCESS:
 *          {
 *              vm_wlan_loc_search_abort(g_wlan_hd);
 *              break;
 *          }
 *          case VM_WLAN_LOC_SCAN_RESULT_FAILED:
 *              vm_wlan_loc_search_abort(g_wlan_hd);
 *              break;
 *          case VM_WLAN_LOC_SCAN_RESULT_ABORTED:
 *              g_wlan_hd = -1;
 *              break;
 *          default:
 *              break;
 *      }
 *  }
 *  void vat_vmsock_wlan_search_1(void)
 *  {
 *      VMINT ret = -1;
 *  
 *      ret = vm_wlan_loc_search(vat_vmsock_wlan_search_cb, NULL);
 *      if (VM_WLAN_LOC_ERR_NOT_SUPPORT != ret && 0 <= ret) {
 *          g_wlan_hd = ret;
 *      }
 *  }
 * </code>
 *****************************************************************************/
VMINT vm_wlan_loc_search_abort(VMINT handle);

/*****************************************************************************
 * FUNCTION
 *  vm_wlan_loc_get_connected_info
 * DESCRIPTION
 *  The function get info form ap which connected already
 * PARAMETERS
 * rssi : [OUT] rssi
 * bssid : [OUT] bssid
 * RETURNS
 *  success if 0, else failure.
 * RETURN VALUES
 *  VM_WLAN_LOC_ERR_BAD_PARAM : invalid input param
 *  VM_WLAN_LOC_ERR_NOT_SUPPORT : platform dose not support
 *  VM_WLAN_LOC_ERR_LOGICAL : maybe not connected
 * EXAMPLE
 * <code>
 * void hl_wlan_get_conn_info(void)
 *   {
 *      vm_wlan_loc_supc_abm_bss_info_struct info;
 *      vm_wlan_loc_get_connected_info(&info);
 *   }
 * </code>
*****************************************************************************/
VMINT vm_wlan_loc_get_connected_info(vm_wlan_loc_supc_abm_bss_info_struct * info);

/* Preload app query and download states */
typedef enum
{
    E_PRELOAD_QUERYING,         /* Querying information */
    E_PRELOAD_AVAILABLE_UPDATE, /* There is available update */
    E_PRELOAD_NO_UPDATE,        /* No update */
    E_PRELOAD_CONNECTING,       /* Connecting network */
    E_PRELOAD_CONNECTED,        /* Network connected */
    E_PRELOAD_DOWNLOADING,      /* Downloading */
    E_PRELOAD_DOWNLOADED,       /* App downloaded */
    E_PRELOAD_HOST_NOT_FOUND,   /* host can not be found */
    E_PRELOAD_PIPE_CLOSED,      /* Pipe is closed */
    E_PRELOAD_PIPE_BROKEN,      /* Pipe is broken */
    E_PRELOAD_FAILURE,          /* Other failed */
    E_PRELOAD_ERR_PATH,         /* download destination path error */
    E_PRELOAD_ABORT,            /* Action is abort */
}vm_preload_state_e;

/* Preload query information */
typedef struct
{
    VMUINT app_id;      /* app id */
//    VMCHAR ver[8];
//    VMCHAR imsi[32];
//    VMCHAR imei[32];
    VMCHAR * ua;       /* User-Agent */ 
    /*
    VMCHAR sc[16];
    VMBYTE skb;
    VMBYTE stch;
    VMBYTE sgs;
    VMBYTE scs;
    VMINT w;
    VMINT h;
    */
}vm_preload_query_info_t;

/* Common info */
typedef struct
{
    vm_preload_state_e state;   /* query or download states */
    void * user_data;           /* user data */
}vm_common_t;


/*
state in below
E_PRELOAD_DOWNLOADING,
E_PRELOAD_DOWNLOADED,
*/
/* received data information */
typedef struct
{
    vm_common_t head;       /* Common info */
    VMINT received;         /* received data size */
    VMINT total;            /* Total data size */
}vm_preload_recv_data_t;

/*****************************************************************************
 * FUNCTION
 *  vm_preload_query
 * DESCRIPTION
 *  Query information of preload app
 * PARAMETERS
 * apn  [IN]    apn id
 * url  [IN]    server url
 * port [IN]    server port
 * info [IN]    query information
 * callback [IN]    query result callback
 * user_data    [IN]    user data
 * RETURNS
 *  query handle if success.
 * EXAMPLE
 * <code>
 *  static VMINT preload_handle;
 *  void callback(VMINT hdl,void * para)
 *  {
 *      vm_common_t * data = (vm_common_t *)para;
 *  
 *      if (E_PRELOAD_AVAILABLE_UPDATE == data->state)
 *      {
 *          vm_preload_download(hdl, get_app_tmp_path(), callback, NULL);
 *      }
 *      if (E_PRELOAD_DOWNLOADING == data->state)
 *      {
 *          vm_preload_recv_data_t * info = (vm_preload_recv_data_t *)para;
 *          vm_trace("PRELOAD [%d/%d]", info->received, info->total);
 *      }
 *      return;
 *  }
 *  void hl_preload(void)
 *  {
 *      static VMINT ret = 0;
 *      vm_preload_query_info_t info;
 *  
 *      info.app_id = 0x0100a4;
 *      info.ua = (VMCHAR*)vm_malloc(32);
 *      sprintf(info.ua, "app_id=%d&ver=%s", 0x0100a4, "0.0.1");
 *      ret = vm_preload_query(VM_TCP_APN_CMNET, 
 *          (const VMCHAR *)"http://www.mediatek.com/games/AppsUpdate",
 *          80, 
 *          (const vm_preload_query_info_t *)&info, 
 *          callback, 
 *          (void *)0x12341234);
 *      if (ret > 0)
 *          preload_handle = ret;
 *  }
 * </code>
*****************************************************************************/
VMINT vm_preload_query(VMINT apn,
                       const VMCHAR * url, 
                       VMINT port,
                       const vm_preload_query_info_t * info,
                       void (*callback)(VMINT hdl, void * para), 
                       void * user_data);
/*****************************************************************************
 * FUNCTION
 *  vm_preload_download_ex
 * DESCRIPTION
 *  Download preload application
 * PARAMETERS
 * hdl  [IN]    preload query handle
 * data  [IN]    destination path
 * bDLA    [IN]     use download agent or not
 * callback [IN]    download state callback
 * user_data    [IN]    user data
 * RETURNS
 *  return 0 if success, else return error code.
 * EXAMPLE
 * <code>
 *  static VMINT preload_handle;
 *  void callback(VMINT hdl,void * para)
 *  {
 *      vm_common_t * data = (vm_common_t *)para;
 *  
 *      if (E_PRELOAD_AVAILABLE_UPDATE == data->state)
 *      {
 *          vm_preload_download_ex(hdl, get_app_tmp_path(), FALSE, callback, NULL);
 *      }
 *      if (E_PRELOAD_DOWNLOADING == data->state)
 *      {
 *          vm_preload_recv_data_t * info = (vm_preload_recv_data_t *)para;
 *          vm_trace("PRELOAD [%d/%d]", info->received, info->total);
 *      }
 *      return;
 *  }
 *  void hl_preload(void)
 *  {
 *      static VMINT ret = 0;
 *      vm_preload_query_info_t info;
 *  
 *      info.app_id = 0x0100a4;
 *      info.ua = (VMCHAR*)vm_malloc(32);
 *      sprintf(info.ua, "app_id=%d&ver=%s", 0x0100a4, "0.0.1");
 *      ret = vm_preload_query(VM_TCP_APN_CMNET, 
 *          (const VMCHAR *)"http://www.mediatek.com/games/AppsUpdate",
 *          80, 
 *          (const vm_preload_query_info_t *)&info, 
 *          callback, 
 *          (void *)0x12341234);
 *      if (ret > 0)
 *          preload_handle = ret;
 *  }
 * </code>
*****************************************************************************/    
VMINT vm_preload_download_ex(VMINT hdl, const VMWCHAR * data, VMBOOL bDLA,void (*callback)(VMINT hdl, void * para), void * user_data);

/*****************************************************************************
 * FUNCTION
 *  vm_preload_download
 * DESCRIPTION
 *  Download preload application
 * PARAMETERS
 * hdl  [IN]    preload query handle
 * data  [IN]    destination path
 * callback [IN]    download state callback
 * user_data    [IN]    user data
 * RETURNS
 *  return 0 if success, else return error code.
 * EXAMPLE
 * <code>
 *  static VMINT preload_handle;
 *  void callback(VMINT hdl,void * para)
 *  {
 *      vm_common_t * data = (vm_common_t *)para;
 *  
 *      if (E_PRELOAD_AVAILABLE_UPDATE == data->state)
 *      {
 *          vm_preload_download(hdl, get_app_tmp_path(), callback, NULL);
 *      }
 *      if (E_PRELOAD_DOWNLOADING == data->state)
 *      {
 *          vm_preload_recv_data_t * info = (vm_preload_recv_data_t *)para;
 *          vm_trace("PRELOAD [%d/%d]", info->received, info->total);
 *      }
 *      return;
 *  }
 *  void hl_preload(void)
 *  {
 *      static VMINT ret = 0;
 *      vm_preload_query_info_t info;
 *  
 *      info.app_id = 0x0100a4;
 *      info.ua = (VMCHAR*)vm_malloc(32);
 *      sprintf(info.ua, "app_id=%d&ver=%s", 0x0100a4, "0.0.1");
 *      ret = vm_preload_query(VM_TCP_APN_CMNET, 
 *          (const VMCHAR *)"http://www.mediatek.com/games/AppsUpdate",
 *          80, 
 *          (const vm_preload_query_info_t *)&info, 
 *          callback, 
 *          (void *)0x12341234);
 *      if (ret > 0)
 *          preload_handle = ret;
 *  }
 * </code>
*****************************************************************************/
VMINT vm_preload_download(VMINT hdl, const VMWCHAR * data, void (*callback)(VMINT hdl, void * para), void * user_data);

/*****************************************************************************
 * FUNCTION
 *  vm_preload_cancel
 * DESCRIPTION
 *  Cancel preload query
 * PARAMETERS
 * hdl  [IN]    preload query handle
 * RETURNS
 *  return 0 if success, else return error code.
 * EXAMPLE
 * <code>
 *  static VMINT preload_handle;
 *  void callback(VMINT hdl,void * para)
 *  {
 *      vm_common_t * data = (vm_common_t *)para;
 *  
 *      if (E_PRELOAD_AVAILABLE_UPDATE == data->state)
 *      {
 *          vm_preload_download(hdl, get_app_tmp_path(), callback, NULL);
 *      }
 *      if (E_PRELOAD_DOWNLOADING == data->state)
 *      {
 *          vm_preload_recv_data_t * info = (vm_preload_recv_data_t *)para;
 *          vm_trace("PRELOAD [%d/%d]", info->received, info->total);
 *      }
 *      return;
 *  }
 *  void hl_preload(void)
 *  {
 *      static VMINT ret = 0;
 *      vm_preload_query_info_t info;
 *  
 *      info.app_id = 0x0100a4;
 *      info.ua = (VMCHAR*)vm_malloc(32);
 *      sprintf(info.ua, "app_id=%d&ver=%s", 0x0100a4, "0.0.1");
 *      ret = vm_preload_query(VM_TCP_APN_CMNET, 
 *          (const VMCHAR *)"http://www.mediatek.com/games/AppsUpdate",
 *          80, 
 *          (const vm_preload_query_info_t *)&info, 
 *          callback, 
 *          (void *)0x12341234);
 *      if (ret > 0)
 *          preload_handle = ret;
 *      vm_preload_cancel(preload_handle);
 *  }
 * </code>
*****************************************************************************/
VMINT vm_preload_cancel(VMINT hdl);

/* network enum */
typedef enum
{
    VM_NETWORK_NONE = 0, /* No bit-wise operation for none case */
    VM_GSM = 0x0100, /* GSM protocol */
    VM_WCDMA = 0x0200, /* WCDMA protocol */
    VM_NETWORK_END_OF_ENUM /* reserved */
}vm_network_enum_t;

/*****************************************************************************
 * FUNCTION
 *  vm_srv_nw_info_get_protocol
 * DESCRIPTION
 *  Get the protocol of current network.
 * PARAMETERS
 *  sim_card : [IN] SIM index, eg: 0x1-SIM1, 0x2-SIM2
 * RETURNS
 *  vm_network_enum_t
 * RETURN VALUES
 *  VM_GSM, VM_WCDMA, failure if less than 0
 * EXAMPLE
 * <code>
 * void hl_nw_sample_1(void)
 *   {
 *       VMINT nw;
 *       nw = vm_srv_nw_info_get_protocol(0x1);
 *   }
 * </code>
 *****************************************************************************/
VMINT vm_srv_nw_info_get_protocol(VMINT sim_card);

/* network capability enum */
typedef enum
{
    VM_NETWORK_CAPABILITY_NONE = 0,
    VM_GPRS  = 0x0010,      /* GPRS */
    VM_EDGE  = 0x0020,      /* EDGE */
    VM_HSDPA = 0x0040,      /* HSDPA */
    VM_HSUPA = 0x0080,      /* HSUPA */
    VM_NETWORK_CAPABILITY_END_OF_ENUM
} vm_network_capability_enum;

/*****************************************************************************
 * FUNCTION
 *  vm_srv_nw_info_get_protocol
 * DESCRIPTION
 *  Query if current channel supports the capability.
 * PARAMETERS
 *  sim         : [IN] Which protocol layer of SIM
 *  type        : [IN] Protocol capability. refer to vm_network_capability_enum
 * RETURNS
 *  -1: no authorization
 *  -2: invalid param
 *  not support if 0, else support.
 * EXAMPLE
 * <code>
 * void hl_nw_sample_2(void)
 *   {
 *       VMINT nw;
 *       nw = vm_srv_nw_info_channel_supports(0x1, VM_HSDPA);
 *   }
 * </code>
 *****************************************************************************/
VMINT vm_srv_nw_info_channel_supports(VMINT sim_card, vm_network_capability_enum type);


typedef enum
{
    VM_NW_INFO_SA_SEARCHING,       /* Searching network */
    VM_NW_INFO_SA_NO_SERVICE,      /* No service */
    VM_NW_INFO_SA_LIMITED_SERVICE, /* Limited service, emergency call only */
    VM_NW_INFO_SA_FULL_SERVICE,    /* Full service */

    VM_NW_INFO_SA_END_OF_ENUM
} vm_nw_info_service_availability_enum_t;
/*****************************************************************************
 * FUNCTION
 *  vm_srv_nw_info_get_service_availability
 * DESCRIPTION
 *  Get the service availability status.
 *  If the network is disabled, the return value is invalid.
 * PARAMETERS
 *  sim_card : [IN] SIM index, eg: 0x1-SIM1, 0x2-SIM2
 * RETURNS
 *  vm_nw_info_service_availability_enum_t
 * RETURN VALUES
 *  VM_NW_INFO_SA_SEARCHING, etc, failure if less than 0
 * EXAMPLE
 * <code>
 * void hl_nw_sample_1(void)
 *   {
 *       VMINT nw;
 *       nw = vm_nw_info_get_service_availability(0x1);
 *   }
 * </code>
 *****************************************************************************/
VMINT vm_srv_nw_info_get_service_availability(VMINT sim_card);

/*
 *  This enum contains a set of bit masks to test the status of data network.
 */
typedef enum
{
    VM_NW_INFO_SIM_DN_STATUS_NONE             = 0x00,   /* No coverage */
    VM_NW_INFO_SIM_DN_STATUS_COVERAGE         = 0x01,   /* In coverage */
    VM_NW_INFO_SIM_DN_STATUS_ATTACHED         = 0x02,   /* Attached */
    VM_NW_INFO_SIM_DN_STATUS_PDP_ACTIVATED    = 0x04,   /* PDP activated */
    VM_NW_INFO_SIM_DN_STATUS_UPLINK           = 0x08,   /* DN uplink */
    VM_NW_INFO_SIM_DN_STATUS_DOWNLINK         = 0x10,   /* DN downlink */
    VM_NW_INFO_SIM_DN_STATUS_END_OF_ENUM
} vm_nw_info_sim_dn_status_enum;

/*****************************************************************************
 * FUNCTION
 *  vm_srv_nw_info_get_sim_dn_status
 * DESCRIPTION
 *  Get current data network status.
 * PARAMETERS
 *  sim_card         : [IN] Which protocol layer of SIM
 * RETURNS
 *  A bit set of vm_nw_info_sim_dn_status_enum.
 * SEE ALSO
 *  vm_nw_info_sim_dn_status_enum
 *****************************************************************************/
VMINT vm_srv_nw_info_get_sim_dn_status(VMINT sim_card);

/*****************************************************************************
 * FUNCTION
 *  vm_dtacct_set
 * DESCRIPTION
 *  set the current data account info that got from vm_dtacct_select. if app need to do connection 
 *  use this data account of the sim_id, VM_APN_USER_DEFINE should be passed as apn param. eg, 
 *  vm_tcp_connect(xx, xxx, VM_APN_USER_DEFINE, xxxx);
 * PARAMETERS
 *  sim_id : [IN] SIM index, eg: 0-SIM1, 1-SIM2, ...
 *  dtacct : [IN] account id
 * RETURN VALUES
 *  success if 0, else failure.
 * EXAMPLE
 * <code>
 * VMINT hl_dtacct_cb(VMUINT32 dtacct)
 * {
 *    vm_dtacct_set(0, dtacct);
 * }
 * void hl_dtacct_sample(void)
 * {
 *      vm_dtacct_select(0, hl_dtacct_cb);
 * }
 *</code>
 *****************************************************************************/
VMINT vm_dtacct_set(VMINT sim_id, VMUINT32 dtacct);

/*****************************************************************************
 * FUNCTION
 *  vm_dtacct_select
 * DESCRIPTION
 *  show the current available data account list of the required sim_id. call back app when user selected
 *  one of them. app may record this data account value, for the vm_dtacct_set if necessary.
 * PARAMETERS
 *  sim_id : [IN] SIM index, eg: 0-SIM1, 1-SIM2, ...
 *  dtacct : [IN] account id
 * RETURN VALUES
 *  success if 0, else failure.
 * EXAMPLE
 * <code>
 * VMINT hl_dtacct_cb(VMUINT32 dtacct)
 * {
 *    vm_dtacct_set(0, dtacct);
 * }
 * void hl_dtacct_sample(void)
 * {
 *      vm_dtacct_select(0, hl_dtacct_cb);
 * }
 * </code>
 *****************************************************************************/
VMINT vm_dtacct_select(VMINT sim_id, VMINT (*callback)(VMUINT32 dtacct));



typedef enum 
{
    VM_RES_TYPE_TCP,
    VM_RES_TYPE_UDP,
    VM_RES_TYPE_HTTP,
    VM_RES_TYPE_HTTPS
}vm_res_type_t;

/*****************************************************************************
 * FUNCTION
 *  vm_cbm_hold_bearer
 * DESCRIPTION
 *  hold the bearer.
 * PARAMETERS
 *  type : [IN] vm_res_type_t
 *  hdl : [IN] TCP : hdl = vm_tcp_connect
 *               UDP : hdl = vm_udp_create
 *               HTTP : hdl = vm_http_get_current_handle
 *                         hdl = vm_http_fetch_handle
 *               HTTPS : channel id
 * RETURN VALUES
 *  success if 0, failure if less than 0
 * EXAMPLE
 * <code>
 *  static VMINT g_tcp_hd;
 *  void tcp_cb(VMINT handle, VMINT event)
 *  {
 *      VMINT ret = 0;
 *      if (VM_TCP_EVT_CONNECTED == event || VM_TCP_EVT_CAN_WRITE == event)
 *      {
 *          ret = vm_cbm_hold_bearer(VM_RES_TYPE_TCP, handle);
 *          ret = vm_tcp_write(handle, "GET / HTTP/1.1\r\nHOST:www.mediate.com:80\r\n\r\n", strlen("GET / HTTP/1.1\r\nHOST:www.mediate.com:80\r\n\r\n"));
 *      }
 *      if (VM_TCP_EVT_CAN_READ == event)
 *      {
 *          VMCHAR buf[2048] = {0};
 *          ret = vm_tcp_read(handle, buf, 2048);
 *          vm_tcp_close(handle);
 *      }
 *  }
 *  void handle_keyevt(VMINT event, VMINT keycode) {
 *  {
 *      if (VM_KEY_EVENT_UP == event)
 *      {
 *          if (VM_KEY_VOL_UP == keycode || 
 *              VM_KEY_UP == keycode)
 *          {
 *              g_tcp_hd = vm_tcp_connect("http://www.mediatek.com", 80, VM_TCP_APN_CMNET, tcp_cb);
 *          }
 *          if (VM_KEY_VOL_DOWN == keycode || 
 *              VM_KEY_DOWN == keycode)
 *          {
 *              vm_cbm_release_bearer();
 *          }
 *      }
 *  }
 * </code>
 *****************************************************************************/
VMINT vm_cbm_hold_bearer(vm_res_type_t type, VMINT hdl);

/*****************************************************************************
 * FUNCTION
 *  vm_cbm_release_bearer
 * DESCRIPTION
 *  hold the bearer.
 * RETURN VALUES
 *  success if 0, failure if less than 0
 * EXAMPLE
 * <code>
 *  static VMINT g_tcp_hd;
 *  void tcp_cb(VMINT handle, VMINT event)
 *  {
 *      VMINT ret = 0;
 *      if (VM_TCP_EVT_CONNECTED == event || VM_TCP_EVT_CAN_WRITE == event)
 *      {
 *          ret = vm_cbm_hold_bearer(VM_RES_TYPE_TCP, handle);
 *          ret = vm_tcp_write(handle, "GET / HTTP/1.1\r\nHOST:www.mediate.com:80\r\n\r\n", strlen("GET / HTTP/1.1\r\nHOST:www.mediate.com:80\r\n\r\n"));
 *      }
 *      if (VM_TCP_EVT_CAN_READ == event)
 *      {
 *          VMCHAR buf[2048] = {0};
 *          ret = vm_tcp_read(handle, buf, 2048);
 *          vm_tcp_close(handle);
 *      }
 *  }
 *  void handle_keyevt(VMINT event, VMINT keycode) {
 *  {
 *      if (VM_KEY_EVENT_UP == event)
 *      {
 *          if (VM_KEY_VOL_UP == keycode || 
 *              VM_KEY_UP == keycode)
 *          {
 *              g_tcp_hd = vm_tcp_connect("http://www.mediatek.com", 80, VM_TCP_APN_CMNET, tcp_cb);
 *          }
 *          if (VM_KEY_VOL_DOWN == keycode || 
 *              VM_KEY_DOWN == keycode)
 *          {
 *              vm_cbm_release_bearer();
 *          }
 *      }
 *  }
 * </code>
 *****************************************************************************/
VMINT vm_cbm_release_bearer(void);

/* Data account profile maximum size */
#define VM_SRV_DTCNT_PROF_MAX     (32)
/* Data account address maximum size */
#define VM_SRV_DTCNT_IP_MAX     (64)

/* Data account information */
typedef struct
{
    VMUINT8 APN[VM_SRV_DTCNT_PROF_MAX];    /* account name */
    VMUINT8 PrimaryAddr[VM_SRV_DTCNT_IP_MAX];    /* Primary DNS IP Address (ASCII) */
    VMUINT8 use_proxy;   /* use proxy flag */
    VMUINT8 UserName[VM_SRV_DTCNT_PROF_MAX];         /* User string of a Data Account (ASCII) */
    VMUINT8 Passwd[VM_SRV_DTCNT_PROF_MAX];             /* Password for a Data Account (ASCII) */
    VMUINT8 px_addr[VM_SRV_DTCNT_IP_MAX];         /* proxy addr string IP format (ASCII)*/
    VMUINT16 px_port;                                        /* proxy port */
}vm_dtcnt_info_t;

/*****************************************************************************
 * FUNCTION
 *  vm_set_cust_apn_info
 * DESCRIPTION
 *  set customized apn info. if successful, it will output data account(*dtacct) which value could be 
 * passed to 'vm_dtacct_set'. VM_APN_USER_DEFINE should be the param when do operation of network.
 * PARAMETERS
 *  info : [IN] refer to vm_dtcnt_info_t
 *  dtacct : [OUT] data account id
 * RETURN VALUES
 *  success if 0, else failure.
 * EXAMPLE
 * <code>
 *  static VMINT g_hdl;
 *  void callback(VMINT handle, VMINT event)
 *  {
 *      vm_trace("cnt cb[%d][%d]", handle, event);
 *  }
 *  void handle_keyevt(VMINT event, VMINT keycode) {
 *      vm_dtcnt_info_t info = {0};
 *      if (VM_KEY_EVENT_UP == event)
 *      {
 *          if (VM_KEY_UP == keycode || 
 *              VM_KEY_VOL_UP == keycode)
 *          {
 *              VMUINT32 dtacct = 0;
 *              VMINT ret = 0;
 *              strcpy(info.APN, "cust apn");
 *              strcpy(info.px_addr, "10.0.0.172");
 *              info.px_port = 80;
 *              info.use_proxy = 1;
 *              ret = vm_set_cust_apn_info(&info, &dtacct);
 *              ret = vm_dtacct_set(0, dtacct);
 *              ret = vm_get_cust_apn_info(&info);
 *              if (0 != strcmp(info.px_addr, "0.0.0.0") && 0 != info.px_port)
 *              {
 *                  ret = vm_tcp_connect((const char*)info.px_addr, info.px_port, 6, callback);
 *                  if (ret >= 0)
 *                  {
 *                      g_hdl = ret;
 *                  }
 *              }
 *              else
 *              {
 *                  ret = vm_tcp_connect((const char*)"www.mediatek.com", 80, 6, callback);
 *                  if (ret >= 0)
 *                  {
 *                      g_hdl = ret;
 *                  }
 *              }
 *              ret = 0;
 *          }
 *          if (VM_KEY_DOWN == keycode || 
 *              VM_KEY_VOL_DOWN == keycode)
 *          {
 *              VMINT ret = 0;
 *              ret = vm_get_cust_apn_info(&info);
 *              vm_tcp_close(g_hdl);
 *              ret = 0;
 *          }
 *      }
 *  }
 * </code>
 *****************************************************************************/
VMINT vm_set_cust_apn_info(const vm_dtcnt_info_t * info, VMUINT32 * dtacct);

/*****************************************************************************
 * FUNCTION
 *  vm_get_cust_apn_info
 * DESCRIPTION
 *  get customized apn info. 
 * PARAMETERS
 *  info : [IN] refer to vm_dtcnt_info_t
 * RETURN VALUES
 *  success if 0, else failure.
 * EXAMPLE
 * <code>
 *  static VMINT g_hdl;
 *  void callback(VMINT handle, VMINT event)
 *  {
 *      vm_trace("cnt cb[%d][%d]", handle, event);
 *  }
 *  void handle_keyevt(VMINT event, VMINT keycode) {
 *      vm_dtcnt_info_t info = {0};
 *      if (VM_KEY_EVENT_UP == event)
 *      {
 *          if (VM_KEY_UP == keycode || 
 *              VM_KEY_VOL_UP == keycode)
 *          {
 *              VMUINT32 dtacct = 0;
 *              VMINT ret = 0;
 *              strcpy(info.APN, "cust apn");
 *              strcpy(info.px_addr, "10.0.0.172");
 *              info.px_port = 80;
 *              info.use_proxy = 1;
 *              ret = vm_set_cust_apn_info(&info, &dtacct);
 *              ret = vm_dtacct_set(0, dtacct);
 *              ret = vm_get_cust_apn_info(&info);
 *              if (0 != strcmp(info.px_addr, "0.0.0.0") && 0 != info.px_port)
 *              {
 *                  ret = vm_tcp_connect((const char*)info.px_addr, info.px_port, 6, callback);
 *                  if (ret >= 0)
 *                  {
 *                      g_hdl = ret;
 *                  }
 *              }
 *              else
 *              {
 *                  ret = vm_tcp_connect((const char*)"www.mediatek.com", 80, 6, callback);
 *                  if (ret >= 0)
 *                  {
 *                      g_hdl = ret;
 *                  }
 *              }
 *              ret = 0;
 *          }
 *          if (VM_KEY_DOWN == keycode || 
 *              VM_KEY_VOL_DOWN == keycode)
 *          {
 *              VMINT ret = 0;
 *              ret = vm_get_cust_apn_info(&info);
 *              vm_tcp_close(g_hdl);
 *              ret = 0;
 *          }
 *      }
 *  }
 * </code>
 *****************************************************************************/
VMINT vm_get_cust_apn_info(vm_dtcnt_info_t * info);


/*****************************************************************************
 * FUNCTION
 *  vm_wlan_perfer
 * DESCRIPTION
 *  disable wlan perfer. 
 * PARAMETERS
 *  disable : [IN] disable if no-zero, or else is default.
 * RETURN VALUES
 *  success if 0, else failure.
 * EXAMPLE
 * <code>
 *  static void tst_cb(VMINT i, VMINT j)
 *  {
 *  }
 *  void handle_keyevt(VMINT event, VMINT keycode) {
 *  
 *      VMINT ret = 0;
 *      VMUINT id;
 *      if (VM_KEY_EVENT_UP == event && 
 *          VM_KEY_VOL_UP == keycode)
 *          {
 *              ret = vm_wlan_perfer(1);
 *              vm_get_encoded_dtacct_id(VM_TCP_APN_CMNET, &id);
 *              vm_trace("prefer 1[%d][0x%x]", ret, id);
 *          }
 *      if (VM_KEY_EVENT_UP == event && 
 *          VM_KEY_VOL_UP == keycode)
 *          {
 *              ret = vm_wlan_perfer(0);
 *              vm_get_encoded_dtacct_id(VM_TCP_APN_CMNET, &id);
 *              vm_trace("prefer 0[%d][0x%x]", ret, id);
 *          }
 *      ret = vm_tcp_connect((VMCHAR*)"www.mediatek.com", 80, 1, tst_cb);
 *      vm_trace("connect [%d]", ret);
 *  }
 * </code>
 *****************************************************************************/
VMINT vm_wlan_perfer(VMINT disable);

#ifdef __cplusplus
}
#endif

#endif /* VMCONN_SDK_H */
