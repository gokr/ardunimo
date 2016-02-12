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
/*****************************************************************************
 *
 * Filename:
 * ---------
 *    vmtsloader.h
 *
 * Project:
 * --------
 *    MAUI
 *
 * Description:
 * ------------
 *    tiny system driver loader.
 *
 * Author:
 * -------
 *    
 *
 *============================================================================
 *             HISTORY
 * Below this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *------------------------------------------------------------------------------
 * $Revision$
 * $Modtime$
 * $Log$
 *
 * 05 28 2014 zhiwei.yang
 * [MAUI_03492870] [Car Kit] GPS feature update
 * .
 *
 * 05 26 2014 zhiwei.yang
 * [MAUI_03492870] [Car Kit] GPS feature update
 * .
 *
 * 05 20 2014 zhiwei.yang
 * [MAUI_03492870] [Car Kit] GPS feature update
 * .
 *
 * 04 21 2014 nan.zhao
 * [MAUI_03493340] Check in LINKIT SDK
 * .
 *
 * 04 18 2014 zhiwei.yang
 * [MAUI_03488298] [MRE]tiny system check in
 * .
 * 
 *------------------------------------------------------------------------------
 * Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *============================================================================
 ****************************************************************************/

#ifndef _VM_TSLOADER_SDK_H
#define _VM_TSLOADER_SDK_H

#ifdef __cplusplus
extern "C" {
#endif

/* Definitions of tiny system driver loader return value */
#define VM_TS_LOAD_ERR_UNKNOWN  (-1)  /* tiny system driver load failed */
#define VM_TS_LOAD_ERR_FORMAT   (-2)  /* tiny system driver load file format error */
#define VM_TS_LOAD_ERR_IO       (-3)  /* tiny system driver load file IO error */
#define VM_TS_LOAD_ERR_MEMORY   (-4)  /* tiny system driver memory not enough */
#define VM_TS_LOAD_ERR_MAXSIZE  (-5)  /* tiny system driver load driver too much */

/*****************************************************************************
 * FUNCTION
 *  vm_ts_driver_load
 * DESCRIPTION
 * this interface used in AP mode, it allow the application load another appliction into memory, the loaded application will run on tiny mode.
 * the first parameter is the file path to load, the second parameter is shared memory size,  the memory can be accessed by both AP mode 
 * application(vm_ts_driver_get_mem) and tiny mode application(vm_ts_get_mem), so it can used by sharing data. this interface only load 
 * the application into memory,  and the loaded application will auto run when system switch to tiny mode.  
 * You can load the tiny mode application in vm_main, or when you received VM_MSG_CREATE msg; and you also need unload the tiny mode
 * application use vm_ts_driver_free when you want exit or not need tiny mode application anymore.
 * PARAMETERS
 *  fileName : [IN] tiny system driver file without suffix or fullpath.
 *  size : size of shared memory
 * RETURN VALUES
 *  >=0 : tiny driver handle.
 *  VM_TS_LOAD_ERR_UNKNOWN : If unsuccessful.
 *  VM_TS_LOAD_ERR_FORMAT : If unsuccessful.
 *  VM_TS_LOAD_ERR_IO : If unsuccessful.
 *  VM_TS_LOAD_ERR_MEMORY : If unsuccessful.
 *  VM_TS_LOAD_ERR_MAXSIZE : If unsuccessful.
 * EXAMPLE
 * <code>
 * // this interface allow application to load tiny mode driver into RAM,  and the driver will auto launch when system 
 * // switch to tiny mode, 
 * VMINT hdl = -1;
 * void handle_sysevt(VMINT message, VMINT param) {
 *	switch (message) {
 *	case VM_MSG_LOAD_TINY:
 *	       hdl = vm_ts_driver_load(wszBuf,512);
 *		
 *           if (hdl < 0)
 *           {
 * 	           vm_log_fatal("failed to load tiny driver");
 *            }
 *		break;
 *	case VM_MSG_QUIT:
 *		if(hdl>=0)
 *		{
 *			vm_ts_driver_free(hdl);
 *			hdl = -1;
 *		}
 *		break;	
 *	}
 * }
 * </code>
 *****************************************************************************/
VMINT vm_ts_driver_load(VMWSTR fileName, VMINT size);

/*****************************************************************************
 * FUNCTION
 *  vm_ts_driver_free
 * DESCRIPTION
 *  this interface used in AP mode, unload tiny system driver, you need unload the tiny driver when you not used it or 
 *  your application exit
 * PARAMETERS
 *  handle : [IN] tiny system driver file handler, get from vm_ts_driver_load
 * RETURN VALUES
 *  NULL
 * SEE ALSO
 *  vm_ts_driver_load
 * EXAMPLE
 * <code>
 * void handle_sysevt(VMINT message, VMINT param) {
 *	switch (message) {
 *	case VM_MSG_CREATE:
 *		break;
 *	case VM_MSG_QUIT:
 *		if(hdl>=0)
 *		{
 *			vm_ts_driver_free(hdl);
 *			hdl = -1;
 *		}
 *		break;	
 *	}
 * }
 * </code>
 *****************************************************************************/
void vm_ts_driver_free(VMINT handle);

/*****************************************************************************
 * FUNCTION
 *  vm_ts_driver_get_mem
 * DESCRIPTION
 *  this interface used in AP mode, get share memory pointer form tiny driver, when system switch tiny mode to ap mode, it will
 *  receive msg of VM_MSG_AP_MODE, you can use this interface to get memory address to get data.
 * PARAMETERS
 *  handle : [IN] tiny driver file handler get from vm_ts_driver_load
 * RETURN VALUES
 *  >0 : shared memory address
 *  NULL : no memory shared
 * SEE ALSO
 *  vm_ts_driver_load
 * EXAMPLE
 * <code>
 * void* share_mem = NULL;
 * void handle_sysevt(VMINT message, VMINT param) {
 *	switch (message) {
 *	case VM_MSG_CREATE:
 *		break;
 *	case VM_MSG_SUSPEND_TO_AP_MODE:
 *		if(hdl>=0)
 *		{
 *			share_mem = (VMCHAR *)vm_ts_driver_get_mem(hdl);
 *			// use the data in the memory
 *		}
 *		break;	
 *	case VM_MSG_QUIT:
 *		if(hdl>=0)
 *		{
 *			vm_ts_driver_free(hdl);
 *			hdl = -1;
 *		}
 *		break;	
 *	}
 * }
 * </code>
 *****************************************************************************/
void* vm_ts_driver_get_mem(VMINT handle);

/*****************************************************************************
 * FUNCTION
 *  vm_ts_driver_get_handle
 * DESCRIPTION
 *  get tiny app handle when return AP mode from Hibernation mode
 * PARAMETERS
 *  void
 * RETURN VALUES
 *  >=0 : handle
 *  <0 : not find the handle
 * EXAMPLE
 * <code>
 * void* share_mem = NULL;
 * void handle_sysevt(VMINT message, VMINT param) {
 *	switch (message) {
 *	case VM_MSG_CREATE:
 *		break;
 *	case VM_MSG_HIBERNATION_TO_AP_MODE:
 *             hdl = vm_ts_driver_get_handle();
 *		if(hdl>=0)
 *		{
 *			share_mem = (VMCHAR *)vm_ts_driver_get_mem(hdl);
 *			// use the data in the memory
 *		}
 *		break;	
 *	case VM_MSG_QUIT:
 *		if(hdl>=0)
 *		{
 *			vm_ts_driver_free(hdl);
 *			hdl = -1;
 *		}
 *		break;	
 *	}
 * }
 * </code>
 *****************************************************************************/
VMINT vm_ts_driver_get_handle(void);

#ifdef __cplusplus
}
#endif 
#endif
