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

#ifndef VMNVRAM_SDK_H_
#define VMNVRAM_SDK_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "vmsys.h"

/* NVRAM ID for Sensor */
typedef enum{
	VM_NVRAM_EF_SENSOR_START_LID = 513,     /* begin */
	VM_NVRAM_EF_SENSOR1_LID = VM_NVRAM_EF_SENSOR_START_LID,    /* used for sensor1 */
	VM_NVRAM_EF_ACCELERATOR_SENSOR_LID = VM_NVRAM_EF_SENSOR1_LID,   /* ACCELERATOR has used thi one, others cannot use it */
	VM_NVRAM_EF_SENSOR2_LID,   /* reserved */
	VM_NVRAM_EF_SENSOR3_LID,   /* reserved */
	VM_NVRAM_EF_SENSOR4_LID,   /* reserved */
	VM_NVRAM_EF_SENSOR5_LID,   /* reserved */
	VM_NVRAM_EF_SENSOR6_LID,   /* reserved */
	VM_NVRAM_EF_SENSOR7_LID,   /* reserved */
	VM_NVRAM_EF_SENSOR8_LID,   /* reserved */
	VM_NVRAM_EF_SENSOR9_LID,   /* reserved */
	VM_NVRAM_EF_SENSOR10_LID,  /* reserved */
	VM_NVRAM_EF_SENSOR11_LID,  /* reserved */
	VM_NVRAM_EF_SENSOR12_LID,  /* reserved */
	VM_NVRAM_EF_SENSOR13_LID,  /* reserved */
	VM_NVRAM_EF_SENSOR14_LID,  /* reserved */
	VM_NVRAM_EF_SENSOR15_LID,  /* reserved */
	VM_NVRAM_EF_SENSOR16_LID,  /* reserved */
	VM_NVRAM_EF_SENSOR17_LID,  /* reserved */
	VM_NVRAM_EF_SENSOR18_LID,  /* reserved */
	VM_NVRAM_EF_SENSOR19_LID,  /* reserved */
	VM_NVRAM_EF_SENSOR20_LID   /* reserved */
}vm_nvram_sensor_lid;

/* Max size of NVRAM data */
#define VM_NVRAM_EF_SENSOR_SIZE 512


/*****************************************************************************
 * FUNCTION
 *    vm_nvram_get_data
 * DESCRIPTION
 *  get nvram data from special ID.
 * PARAMETERS
 *  id : [IN] NVRAM ID to get data.
 *  buff : [OUT] data buffer.
 *  size : [IN] size to get
 * RETURNS
 *  get data success or not.
 * RETURN VALUES
 *  <0 : error, other is success
*****************************************************************************/
VMINT vm_nvram_get_data(vm_nvram_sensor_lid id, void* buff, VMUINT size);

/*****************************************************************************
 * FUNCTION
 *    vm_nvram_set_data
 * DESCRIPTION
 *  set nvram data for special ID.
 * PARAMETERS
 *  id : [IN] NVRAM ID to set data.
 *  buff : [IN] data buffer.
 *  size : [IN] size to set
 * RETURNS
 *  set data success or not.
 * RETURN VALUES
 *  <0 : error, other is success
*****************************************************************************/
VMINT vm_nvram_set_data(vm_nvram_sensor_lid id, void* buff, VMUINT size);


#ifdef __cplusplus
}
#endif


#endif



