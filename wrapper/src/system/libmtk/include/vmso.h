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

#ifndef VMSO_SDK_H_
#define VMSO_SDK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "vmsys.h"

/* SO is being loaded. */
#define VM_SO_MSG_LOAD 		(1)

/* SO is being unloaded. */
#define VM_SO_MSG_UNLOAD 		(9)

/************************************************************************/

#define VM_SO_SUCCESS 						(0)	 		/* SO operation success */
#define VM_SO_FAILED 						(-1)		/* SO operation failed */
#define VM_SO_PARAM_ERROR 					(-2)		/* SO parameter error */
#define VM_SO_FILE_NOT_FOUND 				(-3)		/* SO file not found */
#define VM_SO_CREATE_FAILED 				(-5)		/* SO failed to create pcb */

/*****************************************************************************
 * FUNCTION
 *  vm_load_library
 * DESCRIPTION
 *  load so file.
 * PARAMETERS
 *  sm_name : [IN] so file name without suffix.
 * RETURN VALUES
 *  >0 : so handle.
 *  <=0 : If unsuccessful.
 * EXAMPLE
 * <code>
 * VMINT so_hdl = vm_load_library("test");
 * if (so_hdl > 0)
 * {
 * 	...
 * }
 * </code>
 *****************************************************************************/
VMINT vm_load_library(VMSTR so_name);


/*****************************************************************************
 * FUNCTION
 *  vm_load_ibraryw
 * DESCRIPTION
 *  load so file.
 * PARAMETERS
 *  name : [IN] so file name without suffix.
 * RETURN VALUES
 *  >0 : so handle.
 *  <=0 : If unsuccessful.
 *****************************************************************************/
VMINT vm_load_libraryw(VMWSTR name);


/*****************************************************************************
 * FUNCTION
 *  vm_get_symbol
 * DESCRIPTION
 *  get function pointer form so file.
 * PARAMETERS
 *  so_hdl : [IN] so file handler.
 *  func_name : [IN] function name string.
 * RETURN VALUES
 *  >0 : If successful.
 *  <=0 : If unsuccessful.
 * EXAMPLE
 * <code>
 * VMINT so_hdl = vm_load_library("test");
 * func_t func_ptr = NULL;
 * if (so_hdl > 0)
 * {
 * 	func_ptr = vm_get_symbol(so_hdl, "func_name");
 * 	if (func_ptr)
 * 	{
 * 		func_ptr(x, y, z);
 * 	}
 * }
 * vm_free_library(so_hdl);
 * </code>
 *****************************************************************************/
VMINT vm_get_symbol(VMINT so_hdl, VMSTR func_name);

/*****************************************************************************
 * FUNCTION
 *  vm_free_library
 * DESCRIPTION
 *  unload so file.
 * PARAMETERS
 *  sm_hdl : [IN] so file handler.
 * RETURN VALUES
 *  >0 : If successful.
 *  <=0 : If unsuccessful.
 * EXAMPLE
 * <code>
 * VMINT so_hdl = vm_load_library("test");
 * if (so_hdl > 0)
 * {
 * 	...
 * }
 * vm_free_library(so_hdl);
 * </code>
 *****************************************************************************/
VMINT vm_free_library(VMINT so_hdl);

#ifdef __cplusplus
}
#endif 

#endif /* VMSO_SDK_H_ */

