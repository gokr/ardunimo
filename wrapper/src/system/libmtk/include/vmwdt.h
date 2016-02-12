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

#ifndef VMWDT_SDK_H
#define VMWDT_SDK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "vmsys.h"

void vm_assert(VMSTR file, VMINT line);

/*****************************************************************************
 * FUNCTION
 *  vm_wdt_start
 * DESCRIPTION
 *  start a watch dog
 * PARAMETERS
 *  millisec  : [IN]   watch dog reset time
 * RETURN VALUES
 *  >=0 : the handle of watch dog
 *  <0 : error
 * EXAMPLE
 * <code>
 * VMINT handle = vm_wdt_start(1000);
 * // do somting
 * vm_wdt_feed(handle);
 * // finish doing
 * vm_wdt_stop(handle);
 * </code>
 *****************************************************************************/
VMINT vm_wdt_start(VMUINT tick);

/*****************************************************************************
 * FUNCTION
 *  vm_wdt_feed
 * DESCRIPTION
 *  feed watch
 * PARAMETERS
 *  handle  : [IN]   watch dog handle that vm_wdt_start returned.
 * RETURN
 *  void
 * EXAMPLE
 * <code>
 * VMINT handle = vm_wdt_start(1000);
 * // do somting
 * vm_wdt_feed(handle);
 * // finish doing
 * vm_wdt_stop(handle);
 *****************************************************************************/
void vm_wdt_feed(VMINT handle);

/*****************************************************************************
 * FUNCTION
 *  vm_wdt_stop
 * DESCRIPTION
 *  stop watch dog
 * PARAMETERS
 *  handle  : [IN]   watch dog handle that vm_wdt_start returned.
 * RETURN
 *  void
 * EXAMPLE
 * <code>
 * VMINT handle = vm_wdt_start(1000);
 * // do somting
 * vm_wdt_feed(handle);
 * // finish doing
 * vm_wdt_stop(handle);
 *****************************************************************************/
void vm_wdt_stop(VMINT handle);


/*****************************************************************************
 * FUNCTION
 *  VM_ASSERT
 * DESCRIPTION
 *  assert the phone if the expression is false
 * PARAMETERS
 *  expr  : [IN]   expression to check
 * RETURN VALUES
 *  N/A
 *****************************************************************************/
#ifdef __LINKIT_DEBUG__
#ifdef WIN32
	#define VM_ASSERT(__expr__) \
	do {                        \
	    if (!(__expr__))        \
	    {                       \
	        _asm {int 3}        \
	    }                       \
	} while (0)
#else
	#define VM_ASSERT(expr) do {if(!(expr)) vm_assert((VMSTR)__FILE__, __LINE__); } while (0)
#endif
#else
	#define VM_ASSERT(expr) do {if(!(expr)) {} } while (0)
#endif

#ifdef __cplusplus
}
#endif

#endif /* VMWDT_SDK_H */ 

