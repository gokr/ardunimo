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

#ifndef VMSM_SDK_H_
#define VMSM_SDK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "vmsys.h"
#include "vmpromng.h"

/* Search all SMs in removable & phone memory and compare their versions while loading. The newest one will be loaded. */
#define MRE_SM_LOAD_VER_CMP

/* SM is being loaded. */
#define VM_SM_MSG_LOAD 		(1)

/* Invoker is querying for entries of SM API. */
#define VM_SM_MSG_QUERY		(5)

/* SM is being unloaded. */
#define VM_SM_MSG_UNLOAD 		(9)


/* Definitions of SM's return value */
#define VM_SM_SUCCESS 						(0)	 	/* SM operation success */
#define VM_SM_FAILED 						(-1)		/* SM operation failed */
#define VM_SM_PARAM_ERROR 				    (-2)		/* SM parameter error */
#define VM_SM_FILE_NOT_FOUND 				(-3)		/* SM file not found */
#define VM_SM_INVALID_INVOKER 				(-4)		/* SM invalid invoker */
#define VM_SM_CREATE_FAILED 				(-5)		/* SM failed to create pcb */
#define VM_SM_CREATE_COPY_FAILED 			(-6)		/* SM failed to create copy */
#define VM_SM_MSG_FAILED 					(-7) 	/* SM failed to handle messages */
#define VM_SM_NAME_MISMATCH 				(-8) 	/* SM name mis-match with name in file tag */
#define VM_SM_MEMORY_INSUFFICIENT		    (-9) 	    /* SM memory insifficient */

/* SM flag to identify PCB's type, phase out*/
enum {
	MRE_APP = 0,   /* app launch vsm */
	MRE_SM         /* vsm launch vsm (not support) */
};


typedef struct _vm_sm_info_t {
	VMCHAR version[6];
} vm_sm_info_t;

VMINT vm_sm_query_info(VMSTR sm_name, vm_sm_info_t * sm_info);

#ifdef __LINKIT_SDK__

typedef VMINT (*vm_get_sym_entry_t)(char* symbol);
extern vm_get_sym_entry_t vm_get_sym_entry;

/* Definitions for explicit SM invoking */
typedef void (*void_void_t)(void);
typedef VMINT (*int_void_t)(void);
typedef VMINT (*int_int_t)(VMINT);

/* Macros for SM */
#define SM_PROCESS_BEGIN() {\
	if (((int_int_t)vm_get_sym_entry("vm_sm_set_sb_by_ptr"))((VMINT)handle_smevt) == 0) {

#define SM_PROCESS_RETURN() ((void_void_t)vm_get_sym_entry("vm_sm_reset_sb"))();

#define SM_PROCESS_END() SM_PROCESS_RETURN() } }

#define SM_CALLBACK_BEGIN() {\
	if (((int_void_t)vm_get_sym_entry("vm_sm_set_sb_for_invoker"))() == 0) { 

#define SM_CALLBACK_END() SM_PROCESS_END()

#define SM_SAFE_CALLBACK(PTR) \
	SM_CALLBACK_BEGIN() \
	PTR; \
	SM_CALLBACK_END()

#define SM_SAFE_CALLBACK_RETURN(PTR, RET) \
	SM_CALLBACK_BEGIN() \
	RET = PTR; \
	SM_CALLBACK_END()

/* Macros for SM STUB */
#define SM_INVOKE_BEGIN(SM)  {\
	if (((int_int_t)vm_get_sym_entry("vm_sm_set_sb_by_handle"))(SM) == 0) {

#define SM_INVOKE_END() SM_PROCESS_END()

#define SM_SAFE_INVOKE(SM, PTR) \
	SM_INVOKE_BEGIN(SM) \
	PTR; \
	SM_INVOKE_END() 

#define SM_SAFE_INVOKE_RETURN(SM, PTR, RET) \
	SM_INVOKE_BEGIN(SM) \
	RET = PTR; \
	SM_INVOKE_END() 

#endif


/*****************************************************************************
 * FUNCTION
 *  vm_sm_reg_callback
 * DESCRIPTION
 *  register SM system event callback function.
 * PARAMETERS
 *  smHandler : [IN] callback function pointer.
 * RETURN VALUES
 *  
 *****************************************************************************/
void vm_sm_reg_callback(VMINT (*smHandler)(VMINT message, VMINT param));


/*****************************************************************************
 * FUNCTION
 *  vm_sm_get_filename
 * DESCRIPTION
 *  Get running sm full path (UCS2).
 * PARAMETERS
 *  filename : [OUT] sm file name, get memory form invoker.
 * RETURN VALUES
 *  VM_SM_SUCCESS : If successful.
 *  VM_SM_FAILED : If unsuccessful.
 *****************************************************************************/
VMINT vm_sm_get_filename(VMWSTR filename);

/*****************************************************************************
 * FUNCTION
 *  vm_sm_load
 * DESCRIPTION
 *  load sm file.
 * PARAMETERS
 *  sm_name : [IN] sm file name without suffix.
 * RETURN VALUES
 *  >0 : sm handle.
 *  VM_SM_FAILED : If unsuccessful.
 *  VM_SM_PARAM_ERROR : If unsuccessful.
 *  VM_SM_FILE_NOT_FOUND : If unsuccessful.
 *  VM_SM_FAILED : If unsuccessful.
 *  VM_SM_CREATE_FAILED : If unsuccessful.
 *  VM_SM_CREATE_COPY_FAILED : If unsuccessful.
 *  VM_SM_MSG_FAILED : If unsuccessful.
 *  VM_SM_NAME_MISMATCH : If unsuccessful.
 * SEE ALSO
 *  vm_sm_loadw
 *  vm_sm_unload
 * EXAMPLE
 * <code>
 * VMINT sm_hdl = vm_sm_load("sm_charge");
 * if (sm_hdl > 0)
 * {
 * 	...
 * }
 * vm_sm_unload(sm_hdl);
 * </code>
 *****************************************************************************/
VMINT vm_sm_load(VMSTR sm_name);


/*****************************************************************************
 * FUNCTION
 *  vm_sm_loadw
 * DESCRIPTION
 *  load sm file use unicorn.
 * PARAMETERS
 *  sm_name : [IN] sm file name without suffix.
 * RETURN VALUES
 *  >0 : sm handle.
 *  VM_SM_FAILED : If unsuccessful.
 *  VM_SM_PARAM_ERROR : If unsuccessful.
 *  VM_SM_FILE_NOT_FOUND : If unsuccessful.
 *  VM_SM_FAILED : If unsuccessful.
 *  VM_SM_CREATE_FAILED : If unsuccessful.
 *  VM_SM_CREATE_COPY_FAILED : If unsuccessful.
 *  VM_SM_MSG_FAILED : If unsuccessful.
 *  VM_SM_NAME_MISMATCH : If unsuccessful.
 * SEE ALSO
 *  vm_sm_load
 *****************************************************************************/
VMINT vm_sm_loadw(VMWSTR sm_name);


/*****************************************************************************
 * FUNCTION
 *  vm_sm_get_func_entry
 * DESCRIPTION
 *  get function pointer form sm file.
 * PARAMETERS
 *  sm_hdl : [IN] sm file handler.
 *  api_id : [IN] app id provide by sm headfile.
 * RETURN VALUES
 *  >0 : If successful.
 *  NULL : If unsuccessful.
 * EXAMPLE
 * <code>
 * VMINT sm_hdl = vm_sm_load("sm_charge");
 * func_t func_ptr = NULL;
 * if (sm_hdl > 0)
 * {
 * 	func_ptr = vm_sm_get_func_entry(sm_hdl, id_func);
 * 	if (func_ptr)
 * 	{
 * 		func_ptr(x, y, z);
 * 	}
 * }
 * vm_sm_unload(sm_hdl);
 * </code>
 *****************************************************************************/
VMINT vm_sm_get_func_entry(VMINT sm_hdl, VMINT api_id);


/*****************************************************************************
 * FUNCTION
 *  vm_sm_unload
 * DESCRIPTION
 *  unload sm file.
 * PARAMETERS
 *  sm_hdl : [IN] sm file handler.
 * RETURN VALUES
 *  VM_SM_SUCCESS : If successful.
 *  VM_SM_FAILED : If unsuccessful.
 * SEE ALSO
 *  vm_sm_load
 * EXAMPLE
 * <code>
 * VMINT sm_hdl = vm_sm_load("sm_charge");
 * if (sm_hdl > 0)
 * {
 * 	...
 * }
 * vm_sm_unload(sm_hdl);
 * </code>
 *****************************************************************************/
VMINT vm_sm_unload(VMINT sm_hdl);


/*****************************************************************************
 * FUNCTION
 *  vm_sm_reg_msg_proc
 * DESCRIPTION
 *  register msg proc handle
 * PARAMETERS
 *  proc : [IN] proc handle
 * RETURN VALUES
 *   void
 *****************************************************************************/
void vm_sm_reg_msg_proc(VM_MESSAGE_PROC proc);


/*****************************************************************************
 * FUNCTION
 *  vm_sm_get_handle_by_package_name
 * DESCRIPTION
 *  get handle
 * PARAMETERS
 *  name : [IN] package name of vsm file.
 * RETURN VALUES
 *  handle : If successful.
 *  0 : If unsuccessful.
 *****************************************************************************/
VMINT vm_sm_get_handle_by_package_name(VMSTR name);


VMINT vm_sm_set_sb_by_ptr(VMINT ptr);
VMINT vm_sm_reset_sb(void);
void vm_sm_exit(void);
VMINT vm_sm_set_sb_for_invoker(void);
VMINT vm_sm_set_sb_by_handle(VMINT sm_hdl);


#ifdef __cplusplus
}
#endif 

#endif /* VMSM_SDK_H_ */
