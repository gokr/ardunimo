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
 * vmpromng.c
 *
 * Project:
 * --------
 *   MAUI
 *
 * Description:
 * ------------
 *   
 *
 * Author:
 * -------
 * 
 *
*==============================================================================
 *             HISTORY
 * Below this line, this part is controlled by PVCS VM. DO NOT MODIFY!! 
 *------------------------------------------------------------------------------
 * $Log$
 *
 * 04 18 2012 feng.lin
 * [MAUI_03152588] MRE requirement of downloading and playing video file
 * .
 *
 * 03 22 2012 feng.lin
 * [MAUI_03152588] MRE requirement of downloading and playing video file
 * .
 *
 * *------------------------------------------------------------------------------
 * Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!! 
 *============================================================================== 
 *******************************************************************************/

#ifndef VM_DA_SDK_H
#define VM_DA_SDK_H


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "vmsys.h"

typedef enum
{
    VM_WPS_DL_STATUS_DOWNLOADING,  /* downloading is in progress */
    VM_WPS_DL_STATUS_COMPLETE,     /* complete downloading */
    VM_WPS_DL_STATUS_ABORT         /* downloading is aborted */
}vm_wps_dl_status_enum;

typedef enum
{
    VM_WPS_OK,                             /* Success */
    VM_WPS_ERROR_UNKNOWN,   	            /* Unknonw error */
    VM_WPS_ERROR_SEND,                     /* Fail to write content */
    VM_WPS_ERROR_INVALID_PARAM,            /* Invalid parameters */
    VM_WPS_ERROR_INVALID_HEADER,           /* Invalid headers */
    VM_WPS_ERROR_INVALID_CHANNEL_ID,       /* Invalid channel ID */
    VM_WPS_ERROR_INVALID_REQUEST_ID,       /* Invalid request ID */
    VM_WPS_ERROR_INVALID_SEQUENCE_NUM,     /* Incorrect sequence number in MSG_ID_WPS_READ_CONTENT_REQ and MSG_ID_WPS_POST_CONTENT_RES */
    VM_WPS_ERROR_INVALID_DEFAULT_PROFILE,  /* Invalid default profile */   
    VM_WPS_ERROR_INACTIVE_CHANNEL,         /* Inactive channel */
    VM_WPS_ERROR_INVALID_CONN_TYPE,        /* Invalid connection type */
    VM_WPS_ERROR_NO_RESOURCE,              /* Resource limitation */
    VM_WPS_ERROR_ACCESS_DENY,              /* Access deny */
    VM_WPS_ERROR_PENDING_REQ_EXIST,        /* Pending request exists */
    VM_WPS_ERROR_FILE_ACCESS,              /* File system operation error */
    VM_WPS_ERROR_REQ_ABORT,                /* Request aborted */
    VM_WPS_ERROR_NOT_FOUND,                /* Not found */
    VM_WPS_ERROR_REQ_MSG_TOO_LARGE,        /* Message header is too large */
    VM_WPS_ERROR_REQ_NOT_SUPPORT,          /* Request is not supported */
    VM_WPS_ERROR_DNS_RESOLVE,              /* DNS error */
    VM_WPS_ERROR_USE_PROXY,                /* Proxy error */
    VM_WPS_ERROR_NOT_READY                 /* WPS is not ready yet */
}vm_wps_result_error_enum;

typedef enum
{
    VM_SRV_DA_DOWNLOAD_STOP = 0, /* download of operation */
    VM_SRV_DA_DOWNLOAD_PAUSE, /* pause of operation */
    VM_SRV_DA_DOWNLOAD_RESUME, /* resume of operation */
    
    VM_SRV_DA_DOWNLOAD_STOP_END_OF_ENUM /* stop of operation */
}vm_srv_da_download_cause_enum;


typedef struct
{
    VMINT hdl;
    vm_wps_dl_status_enum status;
    VMUINT32 curr_size;
    VMUINT32 total_size;
    VMWSTR savepath;
    vm_wps_result_error_enum cause;
    void *user_data;
} vm_srv_da_download_progress_struct;

/* callback function for progress */
typedef void (*vm_srv_da_http_progress_funcptr_type)(vm_srv_da_download_progress_struct * pgs);

typedef struct
{
    const VMWCHAR *url;/*url for download [IN] */
    VMINT apn;/* apn, refer to vmsock.h, such as VM_TCP_APN_WIFI, VM_TCP_APN_CMNET... [IN] */
    VMINT show_confirm; /* show confirm or not, 0 show, else not [IN] */
    VMWSTR file_path;
    void * user_data;
    vm_srv_da_http_progress_funcptr_type dl_progress; /* callback of download progress [IN] */ 
}vm_srv_da_start_download_struct;

/* callback function for operation */
typedef void (*vm_srv_da_http_op_funcptr_type)(VMINT hdl, vm_srv_da_download_cause_enum cause);


/****************************************************************************** 
 * FUNCTION
 *  vm_da_http_start_download
 * DESCRIPTION
 *  start a download.
 * PARAMETERS
 *  arg  :    [IN]   refer to vm_srv_da_start_download_struct
 * RETURNS
 *  VMINT job handle if > 0, failure if less than 0, 
 ******************************************************************************/
VMINT vm_da_http_start_download(vm_srv_da_start_download_struct * arg);

/****************************************************************************** 
 * FUNCTION
 *  vm_da_http_dl_operation
 * DESCRIPTION
 *  operation of download agent.
 * PARAMETERS
 *  hdl  :  [IN] download job handler
 *  cause  :  [IN] refer to vm_srv_da_download_cause_enum
 * RETURNS
 *  VMINT 0 if successful, else failure
 ******************************************************************************/
VMINT vm_da_http_dl_operation(VMINT hdl, vm_srv_da_download_cause_enum cause);

/****************************************************************************** 
 * FUNCTION
 *  vm_da_display_download_list
 * DESCRIPTION
 *  display download list.
 * RETURNS
 *  VMINT 0 if successful, else failure
 ******************************************************************************/
VMINT vm_da_display_download_list(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* VM_DA_SDK_H */

