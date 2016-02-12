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

#ifndef VM_BTGATT_SDK_H
#define VM_BTGATT_SDK_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "vmsys.h"

#define VM_ATT_HANDLE VMUINT16


typedef VMUINT32 VM_GATT_CHAR_PROPERTIES;
#define VM_GATT_CHAR_PROP_BROADCAST         0x01
#define VM_GATT_CHAR_PROP_READ              0x02
#define VM_GATT_CHAR_PROP_WRITE_WO_RESPONSE 0x04
#define VM_GATT_CHAR_PROP_WRITE             0x08
#define VM_GATT_CHAR_PROP_NOTIFY            0x10
#define VM_GATT_CHAR_PROP_INDICATE          0x20
#define VM_GATT_CHAR_PROP_SIGNED_WRITE      0x40
#define VM_GATT_EXT_PROP                    0x80

typedef VMUINT32 VM_GATT_PERMISSION;
#define VM_GATT_PERM_READ                   (1 << 0) /* bit 0 */
#define VM_GATT_PERM_READ_ENCRYPTED         (1 << 1) /* bit 1 */
#define VM_GATT_PERM_READ_ENC_MITM          (1 << 2) /* bit 2 */
#define VM_GATT_PERM_WRITE                  (1 << 4) /* bit 4 */
#define VM_GATT_PERM_WRITE_ENCRYPTED        (1 << 5) /* bit 5 */
#define VM_GATT_PERM_WRITE_ENC_MITM         (1 << 6) /* bit 6 */
#define VM_GATT_PERM_WRITE_SIGNED           (1 << 7) /* bit 7 */
#define VM_GATT_PERM_WRITE_SIGNED_MITM      (1 << 8) /* bit 8 */


typedef enum
{
    VM_OS_STATUS_SUCCESS	= 0,
    VM_OS_STATUS_FAILED	    = 1,
}VM_OS_STATUS;

typedef enum
{
    VM_CONNECTION_PRIORITY_DEFAULT,
    VM_CONNECTION_PRIORITY_HIGH_SPEED,
    VM_CONNECTION_PRIORITY_LOW_POWER,
    VM_CONNECTION_PRIORITY_BALANCE
}VM_CONN_PRIO_ENUM;


typedef enum
{
	VM_GATTC_ADV_INTERVAL_DEFAULT,
	VM_GATTC_ADV_INTERVAL_FAST_CONN,
  VM_GATTC_ADV_INTERVAL_REDUCE_POWER
}vm_gattc_adv_interval_enum;


#define VM_BD_ADDR_SIZE 6
typedef struct _VM_BD_ADDR
{
    VMUINT8 addr[VM_BD_ADDR_SIZE];
}VM_BD_ADDR;

#define VM_ATT_MAX_VALUE_LEN 512
typedef struct
{
    VMUINT16 len;
    VMUINT8 value[VM_ATT_MAX_VALUE_LEN];
}VM_ATT_VALUE;


typedef struct
{
    /* the len can only be 2, 4, or 16 */
    VMUINT8 len;
    VMUINT8 uuid[16];
}VM_BT_UUID;
typedef struct
{
    VM_BT_UUID uuid;
    VMUINT8 inst;
}VM_ATT_UUID;
typedef struct
{
    VM_ATT_UUID uuid;
    VMUINT8 is_primary;
}VM_GATT_SVC_UUID;



typedef struct 
{
   VMUINT8 uu[16];
}vm_bt_uuid_struct;

typedef struct
{
    void *reg_ctx;
    void *conn_ctx;
}vm_gatt_conn_struct;

typedef struct
{
    vm_gatt_conn_struct *conn;
    VM_BD_ADDR *bd_addr;
    VMBOOL connected;
    VMBOOL is_ind;
} vm_gattsrv_conn_struct;

/****************************************************************************
* data define
****************************************************************************/
/** BT-GATT Server callback structure. */

/** Callback invoked in response to register */
typedef void (*vmt_register_server_callback)(void *reg_ctx, VM_OS_STATUS status, vm_bt_uuid_struct *app_uuid);

/** Callback indicating that a remote device has connected or been disconnected */
typedef void (*vmt_connection_callback)(vm_gatt_conn_struct *conn, VMBOOL connected, VM_BD_ADDR *bd_addr);

/** Callback triggered in response to listen */
typedef void (*vmt_listen_callback)(void *reg_ctx, VM_OS_STATUS status);

/** Callback invoked in response to create_service */
typedef void (*vmt_service_added_callback)(VM_OS_STATUS status, void *reg_ctx,
                VM_GATT_SVC_UUID *srvc_id, VM_ATT_HANDLE srvc_handle);

/** Callback indicating that an included service has been added to a service */
typedef void (*vmt_included_service_added_callback)(VM_OS_STATUS status, void *reg_ctx,
                VM_ATT_HANDLE srvc_handle, VM_ATT_HANDLE incl_srvc_handle);

/** Callback invoked when a characteristic has been added to a service */
typedef void (*vmt_characteristic_added_callback)(VM_OS_STATUS status, void *reg_ctx,
                VM_ATT_UUID *uuid, VM_ATT_HANDLE srvc_handle, VM_ATT_HANDLE char_handle);

/** Callback invoked when a descriptor has been added to a characteristic */
typedef void (*vmt_descriptor_added_callback)(VM_OS_STATUS status, void *reg_ctx,
                VM_ATT_UUID *uuid, VM_ATT_HANDLE srvc_handle, VM_ATT_HANDLE descr_handle);

/** Callback invoked in response to start_service */
typedef void (*vmt_service_started_callback)(VM_OS_STATUS status, void *reg_ctx,
                                         VM_ATT_HANDLE srvc_handle);

/** Callback invoked in response to stop_service */
typedef void (*vmt_service_stopped_callback)(VM_OS_STATUS status, void *reg_ctx,
                                         VM_ATT_HANDLE srvc_handle);

/** Callback triggered when a service has been deleted */
typedef void (*vmt_service_deleted_callback)(VM_OS_STATUS status, void *reg_ctx,
                                         VM_ATT_HANDLE srvc_handle);

/**
 * Callback invoked when a remote device has requested to read a characteristic
 * or descriptor. The application must respond by calling send_response
 */
typedef void (*vmt_request_read_callback)(vm_gatt_conn_struct *conn, VMUINT16 trans_id, VM_BD_ADDR *bd_addr,
                                      VM_ATT_HANDLE attr_handle, VMUINT16 offset, VMBOOL is_long);

/**
 * Callback invoked when a remote device has requested to write to a
 * characteristic or descriptor.
 */
typedef void (*vmt_request_write_callback)(vm_gatt_conn_struct *conn, VMUINT16 trans_id, VM_BD_ADDR *bd_addr,
                                       VM_ATT_HANDLE attr_handle, VM_ATT_VALUE *value, VMUINT16 offset,
                                       VMBOOL need_rsp, VMBOOL is_prep);

/** Callback invoked when a previously prepared write is to be executed */
typedef void (*vmt_request_exec_write_callback)(vm_gatt_conn_struct *conn, VMUINT16 trans_id,
                                            VM_BD_ADDR *bd_addr, VMBOOL cancel);

/**
 * Callback triggered in response to send_response if the remote device
 * sends a confirmation.
 */
typedef void (*vmt_response_confirmation_callback)(VM_OS_STATUS status, VM_ATT_HANDLE handle);

/** Callback triggered in response to read_tx_power */
typedef void (*vmt_read_tx_power_callback)(void *reg_ctx, VM_OS_STATUS status, VM_BD_ADDR *bd_addr, VMUINT8 tx_power);

typedef void (*vmt_research_service_callback)(vm_gatt_conn_struct *conn, VM_OS_STATUS status, VM_BD_ADDR *bd_addr);
typedef void (*vmt_connection_ext_callback)(vm_gattsrv_conn_struct *conn);
typedef struct
{
    vmt_register_server_callback        register_server_cb;
    vmt_connection_callback             connection_cb;
    vmt_listen_callback                 listen_cb;    
    vmt_service_added_callback          service_added_cb;
    vmt_included_service_added_callback included_service_added_cb;
    vmt_characteristic_added_callback   characteristic_added_cb;
    vmt_descriptor_added_callback       descriptor_added_cb;
    vmt_service_started_callback        service_started_cb;
    vmt_service_stopped_callback        service_stopped_cb;
    vmt_service_deleted_callback        service_deleted_cb;
    vmt_request_read_callback           request_read_cb;
    vmt_request_write_callback          request_write_cb;
    vmt_request_exec_write_callback     request_exec_write_cb;
    vmt_response_confirmation_callback  response_confirmation_cb;
    vmt_read_tx_power_callback          read_tx_power_cb;
    vmt_connection_ext_callback         connection_ext_cb;
}vm_gatts_callback_struct;

/*****************************************************************************
 * FUNCTION
 *  vm_gatts_register
 * DESCRIPTION
 *  Registers a GATT server application with the stack
 * PARAMETERS
 *  uuid [IN] : BT UUID
 *  callback [IN] : the pointer of callback structure 
 * RETURNS
 *  failure if less than 0, else successful
 *****************************************************************************/
VMINT vm_gatts_register(vm_bt_uuid_struct *uuid, vm_gatts_callback_struct *callback);

/*****************************************************************************
 * FUNCTION
 *  vm_gatts_deregister
 * DESCRIPTION
 *  Unregister a server application from the stack
 * PARAMETERS
 *  reg_ctx [IN] : the context of gatt server
 * RETURNS
 *  failure if less than 0, else successful
 *****************************************************************************/
VMINT vm_gatts_deregister(void *reg_ctx);

/*****************************************************************************
 * FUNCTION
 *  vm_gatts_connect
 * DESCRIPTION
 *  Create a connection to a remote peripheral
 * PARAMETERS
 *  reg_ctx [IN] : 
 *  bd_addr [IN] : 
 *  direct [IN] : 
 * RETURNS
 *  failure if less than 0, else successful
 *****************************************************************************/
VMINT vm_gatts_connect(void *reg_ctx, VM_BD_ADDR *bd_addr, VMBOOL direct);

/*****************************************************************************
 * FUNCTION
 *  vm_gatts_disconnect
 * DESCRIPTION
 *  Disconnect an established connection or cancel a pending one
 * PARAMETERS
 *  conn [IN] : 
 *  bd_addr [IN] : 
 * RETURNS
 *  failure if less than 0, else successful
 *****************************************************************************/
VMINT vm_gatts_disconnect(vm_gatt_conn_struct *conn, VM_BD_ADDR *bd_addr);

/*****************************************************************************
 * FUNCTION
 *  vm_gatts_listen
 * DESCRIPTION
 *  Start or stop a listen for connection
 * PARAMETERS
 *  reg_ctx [IN] : 
 *  start [IN] : 
 * RETURNS
 *  failure if less than 0, else successful
 *****************************************************************************/
VMINT vm_gatts_listen(void *reg_ctx, VMBOOL start);

VMINT vm_gatts_set_adv_data(void *reg_ctx, VMBOOL set_scan_rsp, VMBOOL include_name, VMBOOL include_txpower, 
                                VMUINT16 min_interval, VMUINT16 max_interval, VMUINT16 appearance,
                                VMUINT16 manufacturer_len, VMCHAR *manufacturer_data,
                                VMUINT16 service_data_len, VMCHAR *service_data,
                                VMUINT16 service_uuid_len, VMCHAR *service_uuid);
/*****************************************************************************
 * FUNCTION
 *  vm_gatts_add_service
 * DESCRIPTION
 *  Create a new service
 * PARAMETERS
 *  reg_ctx [IN] : 
 *  srvc_id [IN] : 
 *  num_handles [IN] : 
 * RETURNS
 *  failure if less than 0, else successful
 *****************************************************************************/
VMINT vm_gatts_add_service(void *reg_ctx, VM_GATT_SVC_UUID *srvc_id, VMUINT16 num_handles);

/*****************************************************************************
 * FUNCTION
 *  vm_gatts_add_included_service
 * DESCRIPTION
 *  Assign an included service to it's parent service
 * PARAMETERS
 *  reg_ctx [IN] : 
 *  service_handle [IN] : 
 *  included_handle [IN] : 
 * RETURNS
 *  failure if less than 0, else successful
 *****************************************************************************/
VMINT vm_gatts_add_included_service(void *reg_ctx, VM_ATT_HANDLE service_handle, VM_ATT_HANDLE included_handle);

/*****************************************************************************
 * FUNCTION
 *  vm_gatts_add_characteristic
 * DESCRIPTION
 *  Add a characteristic to a service
 * PARAMETERS
 *  reg_ctx [IN] : 
 *  service_handle [IN] : 
 *  uuid [IN] : 
 *  properties [IN] : 
 *  permission [IN] : 
 * RETURNS
 *  failure if less than 0, else successful
 *****************************************************************************/
VMINT vm_gatts_add_characteristic(void *reg_ctx, 
                                  VM_ATT_HANDLE service_handle, VM_ATT_UUID *uuid,
                                  VM_GATT_CHAR_PROPERTIES properties, VM_GATT_PERMISSION permission);

/*****************************************************************************
 * FUNCTION
 *  vm_gatts_add_descriptor
 * DESCRIPTION
 *  Add a descriptor to a given service
 * PARAMETERS
 *  reg_ctx [IN] : 
 *  service_handle [IN] : 
 *  uuid [IN] : 
 *  permission [IN] : 
 * RETURNS
 *  failure if less than 0, else successful
 *****************************************************************************/
VMINT vm_gatts_add_descriptor(void *reg_ctx, VM_ATT_HANDLE service_handle,
                              VM_ATT_UUID *uuid, VM_GATT_PERMISSION permission);

/*****************************************************************************
 * FUNCTION
 *  vm_gatts_start_service
 * DESCRIPTION
 *  Starts a local service
 * PARAMETERS
 *  reg_ctx [IN] : 
 *  service_handle [IN] : 
 *  transport [IN] : 
 * RETURNS
 *  failure if less than 0, else successful
 *****************************************************************************/
VMINT vm_gatts_start_service(void *reg_ctx, VM_ATT_HANDLE service_handle,
                             VMUINT8 transport);

/*****************************************************************************
 * FUNCTION
 *  vm_gatts_stop_service
 * DESCRIPTION
 *  Stops a local service
 * PARAMETERS
 *  reg_ctx [IN] : 
 *  service_handle [IN] : 
 * RETURNS
 *  failure if less than 0, else successful
 *****************************************************************************/
VMINT vm_gatts_stop_service(void *reg_ctx, VM_ATT_HANDLE service_handle);

/*****************************************************************************
 * FUNCTION
 *  vm_gatts_delete_service
 * DESCRIPTION
 *  Delete a local service
 * PARAMETERS
 *  reg_ctx [IN] : 
 *  service_handle [IN] : 
 * RETURNS
 *  failure if less than 0, else successful
 *****************************************************************************/
VMINT vm_gatts_delete_service(void *reg_ctx, VM_ATT_HANDLE service_handle);

/*****************************************************************************
 * FUNCTION
 *  vm_gatts_send_indication
 * DESCRIPTION
 *  Send value indication to a remote device
 * PARAMETERS
 *  conn [IN] : 
 *  attribute_handle [IN] :  
 *  need_confirm [IN] : 
 *  value [IN] :  
 * RETURNS
 *  failure if less than 0, else successful
 *****************************************************************************/
VMINT vm_gatts_send_indication(vm_gatt_conn_struct *conn, VM_ATT_HANDLE attribute_handle,
                               VMBOOL need_confirm, VM_ATT_VALUE *value);

/*****************************************************************************
 * FUNCTION
 *  vm_gatts_send_response
 * DESCRIPTION
 *  Send a response to a read/write operation
 * PARAMETERS
 *  conn [IN] : 
 *  trans_id [IN] :  
 *  status [IN] : 
 *  handle [IN] :  
 *  value [IN] :  
 * RETURNS
 *  failure if less than 0, else successful
 *****************************************************************************/
VMINT vm_gatts_send_response(vm_gatt_conn_struct *conn, VMUINT16 trans_id,
                             VMUINT8 status, VM_ATT_HANDLE handle, VM_ATT_VALUE *value);


/*****************************************************************************
 * FUNCTION
 *  vm_gatts_read_tx_power
 * DESCRIPTION
 *  Request tx power for a given remote device
 * PARAMETERS
 *  reg_ctx [IN] : 
 *  bd_addr [IN] :  
 * RETURNS
 *  failure if less than 0, else successful
 *****************************************************************************/
VMINT vm_gatts_read_tx_power(void *reg_ctx, VM_BD_ADDR *bd_addr);



/****************************************************************************
* data define
****************************************************************************/
/* authentication requirement */
typedef VMUINT8 VM_GATTC_AUTH_REQ;
#define VM_GATTC_AUTH_REQ_NONE              0
#define VM_GATTC_AUTH_REQ_NO_MITM           1   /* unauthenticated encryption */
#define VM_GATTC_AUTH_REQ_MITM              2   /* authenticated encryption */
#define VM_GATTC_AUTH_REQ_SIGNED_NO_MITM    3
#define VM_GATTC_AUTH_REQ_SIGNED_MITM       4

typedef VMUINT8 VM_GATTC_WRITE_TYPE;
#define VM_GATTC_WRITE_TYPE_NO_RSP          1
#define VM_GATTC_WRITE_TYPE_REQUEST         2
#define VM_GATTC_WRITE_TYPE_PREPARE         3

typedef VMUINT8 VM_GATTC_DEV_TYPE;
#define VM_GATTC_DEV_TYPE_UNKNOWN           0
#define VM_GATTC_DEV_TYPE_LE                1
#define VM_GATTC_DEV_TYPE_BR_EDR            2
#define VM_GATTC_DEV_TYPE_BR_EDR_LE         3



typedef struct
{
    VM_GATT_SVC_UUID *svc_uuid;
    VM_ATT_UUID *ch_uuid;
}vm_gattc_char_struct;

typedef struct
{
    VM_GATT_SVC_UUID *svc_uuid;
    VM_ATT_UUID *ch_uuid;
    VM_ATT_UUID *descr_uuid;
}vm_gattc_descr_struct;

/** BT-GATT Client callback structure. */

/** Callback invoked in response to register */
typedef void (*vmt_register_client_callback)(void *reg_ctx, VM_OS_STATUS status, vm_bt_uuid_struct *app_uuid);

/** Callback for scan results */
typedef void (*vmt_scan_result_callback)(void *reg_ctx, VM_BD_ADDR *bd_addr, VMINT32 rssi, VMUINT8 eir_len, VMUINT8 *eir);

/** Callback indicating that a remote device has connected or been disconnected */
//typedef void (*vmt_connection_callback)(vm_gatt_conn_struct *conn, VMBOOL connected, VM_BD_ADDR *bd_addr);

/** Callback triggered in response to listen */
//typedef void (*vmt_listen_callback)(void *reg_ctx, VM_OS_STATUS status);

/** Callback triggered in response to set_adv_data */
typedef void (*vmt_set_adv_data_callback)(void *reg_ctx, VM_OS_STATUS status);

/**
 * Invoked in response to search_service when the GATT service search
 * has been completed.
 */
typedef void (*vmt_search_complete_callback)(vm_gatt_conn_struct *conn, VM_OS_STATUS status);

/** Reports GATT services on a remote device */
typedef void (*vmt_search_result_callback)(vm_gatt_conn_struct *conn, VM_GATT_SVC_UUID *uuid);

/** GATT characteristic enumeration result callback */
typedef void (*vmt_get_characteristic_callback)(vm_gatt_conn_struct *conn, VM_OS_STATUS status,
                                vm_gattc_char_struct *ch, VM_GATT_CHAR_PROPERTIES properties);

/** GATT descriptor enumeration result callback */
typedef void (*vmt_get_descriptor_callback)(vm_gatt_conn_struct *conn, VM_OS_STATUS status, vm_gattc_descr_struct *descr);

/** GATT included service enumeration result callback */
typedef void (*vmt_get_included_service_callback)(vm_gatt_conn_struct *conn, VM_OS_STATUS status,
                                VM_GATT_SVC_UUID *svc_uuid, VM_GATT_SVC_UUID *incl_svc_uuid);

/** Callback invoked in response to [de]register_for_notification */
typedef void (*vmt_register_for_notification_callback)(void *reg_ctx, VM_OS_STATUS status, 
                                VM_BD_ADDR *bd_addr, vm_gattc_char_struct *ch);

/**
 * Remote device notification callback, invoked when a remote device sends
 * a notification or indication that a client has registered for.
 */
typedef void (*vmt_notify_callback)(vm_gatt_conn_struct *conn, VM_BD_ADDR *bd_addr,
                                vm_gattc_char_struct *ch, VM_ATT_VALUE *value, VMBOOL is_notify);

/** Reports result of a GATT read operation */
typedef void (*vmt_read_characteristic_callback)(vm_gatt_conn_struct *conn, VM_OS_STATUS status,
                                vm_gattc_char_struct *ch, VM_ATT_VALUE *value);

/** GATT write characteristic operation callback */
typedef void (*vmt_write_characteristic_callback)(vm_gatt_conn_struct *conn, VM_OS_STATUS status,
                                vm_gattc_char_struct *ch);

/** Callback invoked in response to read_descriptor */
typedef void (*vmt_read_descriptor_callback)(vm_gatt_conn_struct *conn, VM_OS_STATUS status,
                                vm_gattc_descr_struct *descr, VM_ATT_VALUE *value);                                

/** Callback invoked in response to write_descriptor */
typedef void (*vmt_write_descriptor_callback)(vm_gatt_conn_struct *conn, VM_OS_STATUS status,
                                vm_gattc_descr_struct *descr);    

/** GATT execute prepared write callback */
typedef void (*vmt_execute_write_callback)(vm_gatt_conn_struct *conn, VM_OS_STATUS status);

/** Callback triggered in response to read_remote_rssi */
typedef void (*vmt_read_remote_rssi_callback)(void *reg_ctx, VM_OS_STATUS status, VM_BD_ADDR *bd_addr, VMINT32 rssi);

/** Callback triggered in response to get_device_type */
typedef void (*vmt_get_device_type_callback)(void *reg_ctx, VM_OS_STATUS status, VM_BD_ADDR *bd_addr, VM_GATTC_DEV_TYPE dev_type);

/* status : Used by message handler to return result of request */

typedef struct
{
    vmt_register_client_callback            register_client_cb;
    vmt_scan_result_callback                scan_result_cb;
    vmt_connection_callback                 connection_cb;
    vmt_listen_callback                     listen_cb;
    vmt_set_adv_data_callback               set_adv_data_cb;
    vmt_search_complete_callback            search_complete_cb;
    vmt_search_result_callback              search_result_cb;
    vmt_get_characteristic_callback         get_characteristic_cb;
    vmt_get_descriptor_callback             get_descriptor_cb;
    vmt_get_included_service_callback       get_included_service_cb;
    vmt_register_for_notification_callback  register_for_notification_cb;
    vmt_notify_callback                     notify_cb;
    vmt_read_characteristic_callback        read_characteristic_cb;
    vmt_write_characteristic_callback       write_characteristic_cb;
    vmt_read_descriptor_callback            read_descriptor_cb;
    vmt_write_descriptor_callback           write_descriptor_cb;
    vmt_execute_write_callback              execute_write_cb;
    vmt_read_remote_rssi_callback           read_remote_rssi_cb;
    vmt_get_device_type_callback            get_device_type_cb;
    vmt_research_service_callback           research_service_cb; 
    vmt_connection_ext_callback             connection_ext_cb;
}vm_gattc_callback_struct;

/****************************************************************************
* function define
****************************************************************************/
/*****************************************************************************
 * FUNCTION
 *  vm_gattc_register
 * DESCRIPTION
 *  Registers a GATT client application with the stack
 * PARAMETERS
 *  app_uuid [IN] : BT UUID
 *  callback [IN] : the pointer of callback structure 
 * RETURNS
 *  failure if less than 0, else successful
 *****************************************************************************/
VMINT vm_gattc_register(vm_bt_uuid_struct *app_uuid, vm_gattc_callback_struct *callback);

/*****************************************************************************
 * FUNCTION
 *  vm_gattc_deregister
 * DESCRIPTION
 *  Unregister a client application from the stack
 * PARAMETERS
 *  reg_ctx [IN] : 
 * RETURNS
 *  failure if less than 0, else successful
 *****************************************************************************/
VMINT vm_gattc_deregister(void *reg_ctx);

/*****************************************************************************
 * FUNCTION
 *  vm_gattc_scan
 * DESCRIPTION
 *  Start or stop LE device scanning
 * PARAMETERS
 *  reg_ctx [IN] : 
 *  start [IN] : 
 * RETURNS
 *  failure if less than 0, else successful
 *****************************************************************************/
VMINT vm_gattc_scan(void *reg_ctx, VMBOOL start);

/*****************************************************************************
 * FUNCTION
 *  vm_gattc_connect
 * DESCRIPTION
 *  Create a connection to a remote LE or dual-mode device
 * PARAMETERS
 *  reg_ctx [IN] : 
 *  bd_addr [IN] : 
 *  direct [IN] : 
 * RETURNS
 *  failure if less than 0, else successful
 *****************************************************************************/
VMINT vm_gattc_connect(void *reg_ctx, VM_BD_ADDR *bd_addr, VMBOOL direct);

/*****************************************************************************
 * FUNCTION
 *  vm_gattc_disconnect
 * DESCRIPTION
 *  Disconnect a remote device or cancel a pending connection
 * PARAMETERS
 *  conn [IN] : 
 *  bd_addr [IN] : 
 * RETURNS
 *  failure if less than 0, else successful
 *****************************************************************************/
VMINT vm_gattc_disconnect(vm_gatt_conn_struct *conn, VM_BD_ADDR *bd_addr);

/*****************************************************************************
 * FUNCTION
 *  vm_gattc_listen
 * DESCRIPTION
 *  Start or stop a listen for connection
 * PARAMETERS
 *  reg_ctx [IN] : 
 *  start [IN] : 
 * RETURNS
 *  failure if less than 0, else successful
 *****************************************************************************/
VMINT vm_gattc_listen(void *reg_ctx, VMBOOL start);

/*****************************************************************************
 * FUNCTION
 *  vm_gattc_set_adv_data
 * DESCRIPTION
 *  Set advertise data
 * PARAMETERS
 *  reg_ctx [IN] : 
 *  set_scan_rsp [IN] : 
 *  include_name [IN] : 
 *  include_txpower [IN] : 
 *  min_interval [IN] : 
 *  max_interval [IN] : 
 *  appearance [IN] : 
 *  manufacturer_len [IN] : 
 *  manufacturer_data [IN] : 
 *  service_data_len [IN] : 
 *  service_data [IN] : 
 *  service_uuid_len [IN] : 
 *  service_uuid [IN] : 
 * RETURNS
 *  failure if less than 0, else successful
 *****************************************************************************/
VMINT vm_gattc_set_adv_data(void *reg_ctx, VMBOOL set_scan_rsp, VMBOOL include_name, VMBOOL include_txpower, 
                                VMUINT16 min_interval, VMUINT16 max_interval, VMUINT16 appearance,
                                VMUINT16 manufacturer_len, VMCHAR *manufacturer_data,
                                VMUINT16 service_data_len, VMCHAR *service_data,
                                VMUINT16 service_uuid_len, VMCHAR *service_uuid);

/*****************************************************************************
 * FUNCTION
 *  vm_gattc_refresh
 * DESCRIPTION
 *  Clear the attribute cache for a given device
 * PARAMETERS
 *  reg_ctx [IN] : 
 *  bd_addr [IN] :  
 * RETURNS
 *  failure if less than 0, else successful
 *****************************************************************************/
VMINT vm_gattc_refresh(void *reg_ctx, VM_BD_ADDR *bd_addr);

/*****************************************************************************
 * FUNCTION
 *  vm_gattc_search_service
 * DESCRIPTION
 *  Enumerate all GATT services on a connected device.
 *  Optionally, the results can be filtered for a given UUID.
 * PARAMETERS
 *  conn [IN] : 
 *  uuid [IN] :  
 * RETURNS
 *  failure if less than 0, else successful
 *****************************************************************************/
VMINT vm_gattc_search_service(vm_gatt_conn_struct *conn, vm_bt_uuid_struct *uuid);

/*****************************************************************************
 * FUNCTION
 *  vm_gattc_get_included_service
 *  Enumerate included services for a given service.
 *  Set start_incl_srvc_id to NULL to get the first included service.
 * PARAMETERS
 *  conn [IN] : 
 *  svc_uuid [IN] :  
 *  incl_svc_uuid [IN] : 
 * RETURNS
 *  failure if less than 0, else successful
 *****************************************************************************/
VMINT vm_gattc_get_included_service(vm_gatt_conn_struct *conn, VM_GATT_SVC_UUID *svc_uuid, 
                                VM_GATT_SVC_UUID *incl_svc_uuid);

/*****************************************************************************
 * FUNCTION
 *  vm_gattc_get_characteristic
 * DESCRIPTION
 *  Enumerate characteristics for a given service.
 *  Set start_char_uuid to NULL to get the first characteristic.
 * PARAMETERS
 *  conn [IN] : 
 *  svc_uuid [IN] :  
 *  start_char_uuid [IN] : 
 * RETURNS
 *  failure if less than 0, else successful
 *****************************************************************************/
VMINT vm_gattc_get_characteristic(vm_gatt_conn_struct *conn, VM_GATT_SVC_UUID *svc_uuid, VM_ATT_UUID *start_char_uuid);

/*****************************************************************************
 * FUNCTION
 *  vm_gattc_get_descriptor
 * DESCRIPTION
 *  Enumerate descriptors for a given characteristic.
 *  Set start_descr_id to NULL to get the first descriptor.
 * PARAMETERS
 *  conn [IN] : 
 *  char_info [IN] :  
 *  start_descr_uuid [IN] : 
 * RETURNS
 *  failure if less than 0, else successful
 *****************************************************************************/
VMINT vm_gattc_get_descriptor(vm_gatt_conn_struct *conn, vm_gattc_char_struct *char_info, VM_ATT_UUID *start_descr_uuid);

/*****************************************************************************
 * FUNCTION
 *  vm_gattc_read_characteristic
 * DESCRIPTION
 *  Read a characteristic on a remote device 
 * PARAMETERS
 *  conn [IN] : 
 *  ch [IN] :  
 *  auth_req [IN] : 
 * RETURNS
 *  failure if less than 0, else successful
 *****************************************************************************/
VMINT vm_gattc_read_characteristic(vm_gatt_conn_struct *conn, vm_gattc_char_struct *ch, VM_GATTC_AUTH_REQ auth_req);

/*****************************************************************************
 * FUNCTION
 *  vm_gattc_write_characteristic
 * DESCRIPTION
 *  Write a remote characteristic 
 * PARAMETERS
 *  conn [IN] : 
 *  ch [IN] :  
 *  value [IN] : 
 *  write_type [IN] : 
 *  auth_req [IN] : 
 * RETURNS
 *  failure if less than 0, else successful
 *****************************************************************************/
VMINT vm_gattc_write_characteristic(vm_gatt_conn_struct *conn, vm_gattc_char_struct *ch, 
                                VM_ATT_VALUE *value, VM_GATTC_WRITE_TYPE write_type, VM_GATTC_AUTH_REQ auth_req);

/*****************************************************************************
 * FUNCTION
 *  vm_gattc_read_descriptor
 * DESCRIPTION
 *  Read the descriptor for a given characteristic  
 * PARAMETERS
 *  conn [IN] : 
 *  descr [IN] :  
 *  auth_req [IN] : 
 * RETURNS
 *  failure if less than 0, else successful
 *****************************************************************************/
VMINT vm_gattc_read_descriptor(vm_gatt_conn_struct *conn, vm_gattc_descr_struct *descr, VM_GATTC_AUTH_REQ auth_req);

/*****************************************************************************
 * FUNCTION
 *  vm_gattc_write_descriptor
 * DESCRIPTION
 *  Write a remote descriptor for a given characteristic 
 * PARAMETERS
 *  conn [IN] : 
 *  descr [IN] :  
 *  value [IN] : 
 *  write_type [IN] : 
 *  auth_req [IN] :  
 * RETURNS
 *  failure if less than 0, else successful
 *****************************************************************************/
VMINT vm_gattc_write_descriptor(vm_gatt_conn_struct *conn, vm_gattc_descr_struct *descr, 
                                VM_ATT_VALUE *value, VM_GATTC_WRITE_TYPE write_type, VM_GATTC_AUTH_REQ auth_req);

/*****************************************************************************
 * FUNCTION
 *  vm_gattc_execute_write
 * DESCRIPTION
 *  Execute a prepared write operation
 * PARAMETERS
 *  conn [IN] : 
 *  exeute [IN] :  
 * RETURNS
 *  failure if less than 0, else successful
 *****************************************************************************/
VMINT vm_gattc_execute_write(vm_gatt_conn_struct *conn, VMUINT8 exeute);

/*****************************************************************************
 * FUNCTION
 *  vm_gattc_register_for_notification
 * DESCRIPTION
 *  Register to receive notifications or indications for a given
 *  characteristic
 * PARAMETERS
 *  reg_ctx [IN] : 
 *  bd_addr [IN] :  
 *  ch [IN] : 
 * RETURNS
 *  failure if less than 0, else successful
 *****************************************************************************/
VMINT vm_gattc_register_for_notification(void *reg_ctx, VM_BD_ADDR *bd_addr, vm_gattc_char_struct *ch);

/*****************************************************************************
 * FUNCTION
 *  vm_gattc_deregister_for_notification
 * DESCRIPTION
 *  Deregister a previous request for notifications/indications
 * PARAMETERS
 *  reg_ctx [IN] : 
 *  bd_addr [IN] :  
 *  ch [IN] : 
 * RETURNS
 *  failure if less than 0, else successful
 *****************************************************************************/
VMINT vm_gattc_deregister_for_notification(void *reg_ctx, VM_BD_ADDR *bd_addr, vm_gattc_char_struct *ch);

/*****************************************************************************
 * FUNCTION
 *  vm_gattc_read_remote_rssi
 * DESCRIPTION
 *  Request RSSI for a given remote device
 * PARAMETERS
 *  reg_ctx [IN] : 
 *  bd_addr [IN] :  
 * RETURNS
 *  failure if less than 0, else successful
 *****************************************************************************/
VMINT vm_gattc_read_remote_rssi(void *reg_ctx, VM_BD_ADDR *bd_addr);

/*****************************************************************************
 * FUNCTION
 *  vm_gattc_get_device_type
 * DESCRIPTION
 *  Determine the type of the remote device (LE, BR/EDR, Dual-mode)
 * PARAMETERS
 *  reg_ctx [IN] : 
 *  bd_addr [IN] :  
 * RETURNS
 *  failure if less than 0, else successful
 *****************************************************************************/
VMINT vm_gattc_get_device_type(void *reg_ctx, VM_BD_ADDR *bd_addr);
typedef enum
{
    VM_TYPE_UNKNOW = (0),
    VM_TYPE_SERVICE,
    VM_TYPE_CHARACTERISTIC,
    VM_TYPE_DESCRIPTOR,
    VM_TYPE_INCLUDE_SRV,
} vm_decl_type_enum;


typedef struct _VMListEntry
{
    struct _VMListEntry *Flink;
    struct _VMListEntry *Blink;

} VMListEntry;

/* Structure used to store GATT profile services.
 * This structure should be vaild after receiving factory_srvs_got_cb with success state.
*/
typedef struct
{
    VMListEntry   srvlist;
    VMBOOL        bInitialized;
} vm_gatts_srvs_lst_struct;


typedef struct
{
    vm_decl_type_enum       type;
    VMUINT8                 *uuid;
    VMUINT8                 isprimary;
    VM_GATT_CHAR_PROPERTIES    prop;
    VM_GATT_PERMISSION         permission;
}vm_gatts_profile_srv_decl_struct;

typedef struct
{
    VMListEntry                 declnode;
    vm_decl_type_enum           type;
    VM_ATT_UUID                 uuid;
    VM_ATT_HANDLE               handle;
    VM_ATT_HANDLE               srvhandle;
    VM_ATT_HANDLE               charhandle;
    VMUINT8                     isprimary;
    VM_GATT_CHAR_PROPERTIES     prop;
    VM_GATT_PERMISSION          permission;
    VMUINT16                    handlenum;
}vm_gatts_service_decl_struct;


// callback function for vm_gatts_profile_factory_get_services
typedef void (*vm_factory_srvs_got_callback)(VM_OS_STATUS status, void* reg_ctx);

// callback function for vm_gatts_profile_factory_clear_services
typedef void (*vm_factory_srvs_cleared_callback)(VM_OS_STATUS status, void* reg_ctx);

// callback function for vm_gatts_profile_factory_add_services
typedef void (*vm_factory_srvs_added_callback)(VM_OS_STATUS status, void* reg_ctx);

// callback function for vm_gatts_profile_factory_delete_services
typedef void (*vm_factory_srvs_deleted_callback)(VM_OS_STATUS status, void* reg_ctx);


//Gatts profile factory callback.
typedef struct
{ 
    vm_factory_srvs_got_callback       factory_srvs_got_cb;
    vm_factory_srvs_cleared_callback   factory_srvs_cleared_cb;
    vm_factory_srvs_added_callback     factory_srvs_added_cb;
    vm_factory_srvs_deleted_callback   factory_srvs_deleted_cb;
}vm_gatts_factory_callback_struct;


//Register gatts profile callback. Callback functions about add-services will be replaced by this register function.
VMINT vm_gatts_profile_factory_register(vm_bt_uuid_struct* uuid, vm_gatts_callback_struct* gatts_cb, 
                                                                    vm_gatts_factory_callback_struct* factory_cb);
//Deregister a server application from the stack.
VMINT vm_gatts_profile_factory_deregister(void* reg_ctx);

//Get gatts profile services by profile id. gatts_services_struct fill be filled without handle.
// VM_OS_STATUS
VMINT vm_gatts_profile_factory_get_services(void* reg_ctx, VMINT32 id, vm_gatts_srvs_lst_struct* services);

//Clear used resource in profile factory. If this function is called, the parameter service structure will be set to empty.
VMINT vm_gatts_profile_factory_clear_services(void* reg_ctx, const vm_gatts_srvs_lst_struct* services);

//Add gatts profile services  to gatt stack.
VMINT vm_gatts_profile_factory_add_services(void* reg_ctx, const vm_gatts_srvs_lst_struct* services);

//Delete gatts profile services from gatt stack.
VMINT vm_gatts_profile_factory_delete_services(void* reg_ctx, const vm_gatts_srvs_lst_struct* services);

//Create service declare list before add service
VMINT vm_gatts_profile_factory_create_srv_list(vm_gatts_profile_srv_decl_struct *srv_list, VMUINT32 decl_num);

//Delete service from profile table
// VM_OS_STATUS
VMINT vm_gatts_profile_factory_delete_srv_list(VMINT32 profile_id);
                             

/*****************************************************************************
 * FUNCTION
 *  vm_gattc_conn_param_update
 * DESCRIPTION
 *  send connection interval to client
 * PARAMETERS
 *  profile_id           [IN]  please see gattprofilesrvdeclaration.c    
 *  bd_addr              [IN]  remote device's address           
 *  connectionPriority   [IN]  if need high transfer speed, please pass CONNECTION_PRIORITY_HIGH_SPEED; 
 *                             if need Low power, please pass CONNECTION_PRIORITY_LOW_POWER;default:CONNECTION_PRIORITY_LOW_POWER
 * RETURNS
 *  failure if less than 0, else successful
 *****************************************************************************/
VMINT vm_gattc_conn_param_update(VMUINT32 profile_id, VMCHAR *bd_addr, VM_CONN_PRIO_ENUM connectionPriority);


/*****************************************************************************
 * FUNCTION
 *  vm_gattc_set_adv_interval
 * DESCRIPTION
 *  send advertise interval to client
 * PARAMETERS
 *  profile_id            [IN]  please see gattprofilesrvdeclaration.c, and pass your Profile ID   
 *  adv_interval          [IN]   adv interval pattern    
 *            
 * RETURNS
 *  failure if less than 0, else successful
 *****************************************************************************/
VMINT vm_gattc_set_adv_interval(VMUINT32 profile_id, vm_gattc_adv_interval_enum adv_interval);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* VM_BTCM_SDK_H */


