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
#ifndef VM_BTNOTIFY_SDK_H
#define VM_BTNOTIFY_SDK_H


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "vmsys.h"
#include "vmbtcm.h"

#define VM_BT_NOTIFY_MRE_FILE_NAME_LENTH 50
#define VM_BT_NOTIFY_MRE_MAX_DATA_LENTH (2047 - 30)
#define VM_MAX_IOER (16)

/* mre callback data type */
typedef enum
{
    VM_SRV_BT_NOTI_MRE_DATA_TYPE_BUFFER = 0,
    VM_SRV_BT_NOTI_MRE_DATA_TYPE_FILE
}vm_srv_bt_noti_mre_data_type_enum;


typedef enum
{
    VM_SRV_BT_NOTIFY_RET_NO_ERROR = 0,
    VM_SRV_BT_NOTIFY_RET_UNKNOWN_ERROR = -1000,    /* unknown error */
    VM_SRV_BT_NOTIFY_RET_FILE_NOT_EXIST,           /* file not exist */
    VM_SRV_BT_NOTIFY_RET_FILE_INTEGRITY_ERROR,     /* file length error */
    VM_SRV_BT_NOTIFY_RET_LINK_DISCONNECTED,
    VM_SRV_BT_NOTIFY_RET_MRE_PARSE_PARA_ERROR,
    VM_SRV_BT_NOTIFY_RET_MAP_FILE_PARSE_PARA_ERROR
} vm_srv_bt_notify_ret_code;


/* mre callback struct */
typedef struct
{
    VMCHAR sender[VM_MAX_IOER];                         /* sender id for FP */
    VMCHAR receiver[VM_MAX_IOER];                       /* receiver id for SP */
    VMINT32 err_code;                               /* error code */
    VMINT  data_type;  /* data type, 0 for buffer, 1 for file */
    union
    {
        VMWCHAR file_path[VM_BT_NOTIFY_MRE_FILE_NAME_LENTH]; /* file path */
        struct
        {
            VMUINT8  buf[VM_BT_NOTIFY_MRE_MAX_DATA_LENTH]; /* buffer address */
            VMUINT16 len; /* buffer length */
        }buffer;
    }data;
    vm_srv_bt_cm_bt_addr bt_addr; /* bt addr */
}vm_srv_bt_noti_callback_struct;


/* The bt notification callback mre engine */
typedef void (*vm_srv_bt_noti_callback)(vm_srv_bt_noti_callback_struct *data);

/*****************************************************************************
 * FUNCTION
 *  vm_srv_bt_noti_check_connection
 * DESCRIPTION
 *  check the connection status.
 * RETURNS
 *  VMINT : 0 is connection succesfully else no connection
 *****************************************************************************/
VMINT vm_srv_bt_noti_check_connection(void);

/*****************************************************************************
 * FUNCTION
 *  vm_srv_bt_noti_register_mre_callback
 * DESCRIPTION
 *  regist the callback, it will be called while here is a notify from spp service
 * PARAMETERS
 *  bt_addr             :           [IN] bt address
 *  sender [IN]:          the id of yourself (sender id)
 *  cb [IN]:          callback
 * RETURNS
 *  VMINT : 0 is succesful else failure
 *****************************************************************************/
VMINT vm_srv_bt_noti_register_callback(const vm_srv_bt_cm_bt_addr *bt_addr, const VMCHAR sender[VM_MAX_IOER], vm_srv_bt_noti_callback cb);

/* MREE sender_id data_type data_len data CANNOT EXCEED VM_BT_NOTIFY_MRE_MAX_DATA_LENTH */

/*****************************************************************************
 * FUNCTION
 *  vm_srv_bt_noti_send_cmd_ext
 * DESCRIPTION
 *  send data to the other side. this API will conbine the param to string, the total size could not exceed the VM_BT_NOTIFY_MRE_MAX_DATA_LENTH.
 *  or the -4 will be return.
 * PARAMETERS
 *  bt_addr             :           [IN] bt address
 *  reader [IN]:          whose id you want to send.
 *  data_type [IN]:          refer to vm_srv_bt_noti_mre_data_type_enum
 *  data [IN]:          what data want to be sent
 *  len [IN]:          sending data length
 * RETURNS
 *  VMINT : 0 is succesful else failure
 *****************************************************************************/
VMINT vm_srv_bt_noti_send_cmd_ext(const vm_srv_bt_cm_bt_addr *bt_addr, const VMCHAR reader[VM_MAX_IOER], VMINT data_type, const VMBYTE *data, VMINT len);

/*****************************************************************************
 * FUNCTION
 *  vm_srv_bt_noti_send_ex
 * DESCRIPTION
 *  send data to the other side. this API will conbine the param to string, the total size could not exceed the VM_BT_NOTIFY_MRE_MAX_DATA_LENTH.
 *  or the -4 will be return.
 * PARAMETERS
 *  bt_addr             :           [IN] bt address
 *  sender [IN]:          whose id you want to send.
 *  receiver [IN]:          whose id you want to read.
 *  data_type [IN]:          refer to vm_srv_bt_noti_mre_data_type_enum
 *  data [IN]:          what data want to be sent
 *  len [IN]:          sending data length
 * RETURNS
 *  VMINT : 0 is succesful else failure
 *****************************************************************************/
VMINT vm_srv_bt_noti_send_ex(const vm_srv_bt_cm_bt_addr *bt_addr, const VMCHAR sender[VM_MAX_IOER], const VMCHAR receiver[VM_MAX_IOER], VMINT data_type, const VMBYTE *data, VMINT len);

/*****************************************************************************
 * FUNCTION
 *  vm_bt_noti_check_channel_valid
 * DESCRIPTION
 *  This function is to check validation context channel
 * PARAMETERS
 *  cntx_chnl         :           [IN] channel index
 * RETURNS
 *  VMINT : 0 is valid else failure
 *****************************************************************************/
VMINT vm_bt_noti_check_channel_valid(VMINT cntx_chnl);


/*****************************************************************************
 * FUNCTION
 *  vm_bt_noti_get_bt_device_addr
 * DESCRIPTION
 *  This function is to get bt device address from context channel
 * PARAMETERS
 *  cntx_chnl         :           [IN] channel index
 * RETURNS
 *  VMINT : 0 is succesful else failure
 *****************************************************************************/
VMINT vm_bt_noti_get_bt_device_addr(VMINT cntx_chnl, vm_srv_bt_cm_bt_addr *bt_addr);

#define vm_srv_bt_noti_register_mre_callback vm_srv_bt_noti_register_callback  


/*****************************************************************************
 * FUNCTION
 *  vm_bt_noti_deregister_callback
 * DESCRIPTION
 *  This function is to deregister callback,
 * PARAMETERS
 *  bt_addr         :           [IN] bt device address
 *  cb_ptr          :           [IN] srv_bt_noti_callback cb_ptr
 * RETURNS
 *  VMINT : 0 is succesful else failure
 *****************************************************************************/
VMINT vm_bt_noti_deregister_callback(vm_srv_bt_cm_bt_addr *bt_addr, vm_srv_bt_noti_callback cb_ptr);

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* VM_BTNOTIFY_SDK_H */

