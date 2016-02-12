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
#ifndef VMJAVA_SDK_H_
#define VMJAVA_SDK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "vmsys.h"
#include "vmpromng.h"

#define MMI_MRE_MAX_ID_LEN 32
#define MMI_MRE_MAX_URL_LEN 128

typedef enum
{
    VM_RESULT_OK,
    VM_RESULT_FAILED
} vm_process_result_enum;

typedef enum
{
    VM_CMD_JAVA_INSTALL,
    VM_CMD_JAVA_REMOVE,
    VM_CMD_JAVA_START,
    VM_CMD_END
} vm_cmd_enum;

typedef void (*vm_java_report_status_t)( vm_process_result_enum error_code, VMSTR mids_storage_id);

typedef struct
{
    VMCHAR mids_storage_id[MMI_MRE_MAX_ID_LEN];              /* App software ID */
    VMINT16 pkg_install_path[MMI_MRE_MAX_URL_LEN];           /* Install file path */
    VMCHAR pkg_network_url[MMI_MRE_MAX_URL_LEN];             /* network package url */
    VM_P_HANDLE process_handle;
    vm_java_report_status_t vm_java_report_status;
} vm_cmd_info_struct;

void vm_process_java_app( vm_cmd_enum cmd, vm_cmd_info_struct *info);

VMINT vm_java_is_removed(VMSTR mids_storage_id);

#ifdef __cplusplus
}
#endif 

#endif /* VMJAVA_SDK_H_ */
