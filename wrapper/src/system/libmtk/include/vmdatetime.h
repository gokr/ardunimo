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
 * vmdatetime_sdk.h
 *
 * Project:
 * --------
 *  MAUI
 *
 * Description:
 * ------------
 *  date time
 *
 * Author:
 * -------
 * 
 *
*==============================================================================
 *             HISTORY
 * Below this line, this part is controlled by PVCS VM. DO NOT MODIFY!! 
 *------------------------------------------------------------------------------
* *------------------------------------------------------------------------------
 * Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!! 
 *============================================================================== 
*******************************************************************************/
#ifndef VM_DATETIME_SDK_H
#define VM_DATETIME_SDK_H
#ifdef __cplusplus
extern "C"{
#endif/*__cplusplus*/
#include "vmsys.h"
/*vm_time_t*/
typedef struct vm_time_t {
	VMINT year;		/*year*/
	VMINT mon;		/* month, begin from 1	*/
	VMINT day;		/* day,begin from  1 */
	VMINT hour;		/* house, 24-hour	*/
	VMINT min;		/* minute	*/
	VMINT sec;		/* second	*/
} vm_time_t;


/*****************************************************************************
 * FUNCTION
 *  vm_get_time
 * DESCRIPTION
 *  get current system time 
 * PARAMETERS
 *  time : [OUT] time structure
 * RETURNS
 *  if succeed, return 0, otherwise return -1
 *****************************************************************************/ 
VMINT vm_get_time(vm_time_t* time);

/*****************************************************************************
 * FUNCTION
 *  vm_set_time
 * DESCRIPTION
 *  set system time 
 * PARAMETERS
 *  time : [IN] time structure
 * RETURNS
 *  if succeed, return 0, otherwise return -1
 *****************************************************************************/ 
VMINT vm_set_time(vm_time_t* time);

/*****************************************************************************
 * FUNCTION
 *  vm_get_sys_time_zone
 * DESCRIPTION
 *  get system time zone 
 * PARAMETERS
 *  void
 * RETURNS
 *  GMT value
 *****************************************************************************/ 
float vm_get_sys_time_zone(void);

/*****************************************************************************
 * FUNCTION
 *  vm_get_curr_utc
 * DESCRIPTION
 * Get the time(the rtc time,not the utc) since the Epoch (00:00:00 UTC, January 1, 1970),
 * measured in seconds.phase out, replace by vm_get_rtc()
 * PARAMETERS
 *  utc : [OUT] point to the time in seconds.
 * RETURNS
 *  if succeed, return 0, otherwise failure.
 *****************************************************************************/
VMINT vm_get_curr_utc(VMUINT * utc);

/*****************************************************************************
 * FUNCTION
 *  vm_get_rtc
 * DESCRIPTION
 * Get the time since the Epoch (00:00:00 UTC, January 1, 1970),
 * measured in seconds.
 * PARAMETERS
 *  utc : [OUT] point to the time in seconds.
 * RETURNS
 *  if succeed, return 0, otherwise failure.
 *****************************************************************************/
VMINT vm_get_rtc(VMUINT * rtc);

/*****************************************************************************
 * FUNCTION
 *  vm_get_tick_count
 * DESCRIPTION
 *  get millisecond number from the system power on till now
 * PARAMETERS
 *  void
 * RETURNS
 *  millisecond number from the system power on till now
 *****************************************************************************/ 
VMINT vm_get_tick_count(void);

/* DOM-NOT_FOR_SDK-BEGIN */
/*****************************************************************************
 * FUNCTION
 *    get_today_from_2000
 * DESCRIPTION
 *  get the number of day from 2000/01/01 to now. 
 * RETURNS
 *  number of day, -1 means failed.
 *****************************************************************************/
VMINT get_today_from_2000(void);
/* DOM-NOT_FOR_SDK-END */

/*****************************************************************************
 * FUNCTION
 *    vm_ust_get_current_time
 * DESCRIPTION
 *  get microsecond from the system power on till now. 
 * RETURNS
 *  microsecond number from the system power on till now
 *<code>
 * start = vm_ust_get_current_time();
 *</code>
 *****************************************************************************/
VMUINT32 vm_ust_get_current_time();

/*****************************************************************************
 * FUNCTION
 *    vm_ust_get_duration
 * DESCRIPTION
 *    get the duration from start to end
 * RETURNS
 *    the duration 
 *<code>
 * start = vm_ust_get_current_time();
 * ...
 * end = vm_ust_get_current_time();
 * duration = vm_ust_get_duration(start,end);
 *</code>
 *****************************************************************************/
 VMUINT32 vm_ust_get_duration(VMUINT32 start,VMUINT32 end);
 
#ifdef __cplusplus
}
#endif/*__cplusplus*/

#endif/*VM_DATETIME_SDK_H*/