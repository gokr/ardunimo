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

#ifndef VMTIMER_SDK_H_
#define VMTIMER_SDK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "vmsys.h"

typedef enum
{
	
	VM_TIMER_MTK_TIMER_NO_FREE = -5,
	VM_TIMER_ERROR_OF_PROCESS,
	VM_TIMER_ERROR_OF_RES ,
	VM_TIMER_ERROR_OF_MEM ,
	VM_TIMER_ERROR ,
	VM_TIMER_OK
} vm_timer_error_t;

typedef struct
{
    VMUINT8 unused;
}*vm_kal_timerid;

/* prototype of timer callback function */
typedef void (*vm_kal_timer_func_ptr)(void *param_ptr);

/*callback function VM_TIMERPROC_T */
typedef void (*VM_TIMERPROC_T)(VMINT tid);

/*callback function for high priority timer */
typedef void (*vm_timer_func_ptr)(void *);

/*****************************************************************************
 * FUNCTION
 *  vm_create_timer
 * DESCRIPTION
 *  create timer. 
 *  Once the timer is created, it will be looply called till user delete it. It is a non-aligned timer, so it is a precise timer and will be stopped
 *  when the LCD backlight is off. For one application , the max number of this kind of timer is 10 
 * PARAMETERS
 *  millisec : [IN] the length if the interval. The unit of interval is millisecond
 *  timerproc : [IN] the callback function when the timer is over time
 * RETURNS
 *  The timer handle,the handle >0 when succeed,otherwise, handle <0
 * EAMPLE
 * <code>
 * void customer_timer_example_proc(VMINT tid)
 * {
 *     static VMINT s_restore_num = 0;
 *     s_restore_num++;
 *     if(s_restore_num > 10)
 *     {
 *         vm_delete_timer(tid);
 *     }
 * }
 *
 * void customer_run_timer(void)
 * {
 *      VMINT timer_id = 0;
 *      timer_id = vm_create_timer(1000, (VM_TIMERPROC_T)customer_timer_example_proc);
 *      if(timer_id < 0)
 *      {
 *          vm_log_debug("customer_run_timer create timer fail");
 *      }
 * }
 * </code>
 *****************************************************************************/
VMINT vm_create_timer(VMUINT32 millisec, VM_TIMERPROC_T timerproc);


/*****************************************************************************
 * FUNCTION
 *  vm_delete_timer
 * DESCRIPTION
 *  delete the timer created by vm_create_timer
 * PARAMETERS
 *  timerid  : [IN] the timer handler
 * RETURNS
 *   succeed when return 0,otherwise, fail
 * EXAMPLE
 * <code>
 * refer from vm_create_timer code example
 * </code>
 *****************************************************************************/
VMINT vm_delete_timer(VMINT timerid);



/*****************************************************************************
 * FUNCTION
 *  vm_create_timer_ex
 * DESCRIPTION
 *  create timer. 
 *  Once the timer is created, it will be looply called till user delete it. It is an aligned timer, so it is not a precise timer. but it will still work
 *  when the LCD backlight is off. For one application , the max number of this kind of timer is 10 
 * PARAMETERS
 *  millisec : [IN] the length if the interval. The unit of interval is millisecond
 *  timerproc : [IN] the callback function when the timer is over time
 * RETURNS
 *  The timer handle,the handle >0 when succeed,otherwise, handle <0
 * EAMPLE
 * <code>
 * void customer_timer_example_proc_ex(VMINT tid)
 * {
 *     static VMINT s_restore_num = 0;
 *     s_restore_num++;
 *     if(s_restore_num > 10)
 *     {
 *         vm_delete_timer_ex(tid);
 *     }
 * }
 *
 * void customer_run_timer_ex(void)
 * {
 *      VMINT timer_id = 0;
 *      timer_id = vm_create_timer_ex(1000, (VM_TIMERPROC_T)customer_timer_example_proc_ex);
 *      if(timer_id < 0)
 *      {
 *         vm_log_debug("customer_run_timer_ex create timer fail!");
 *      }
 * }
 * </code>
 *****************************************************************************/
VMINT vm_create_timer_ex(VMUINT32 millisec, VM_TIMERPROC_T timerproc);


/*****************************************************************************
 * FUNCTION
 *  vm_delete_timer_ex
 * DESCRIPTION
 *  delete the timer created by vm_create_timer_ex
 * PARAMETERS
 *  timerid : [IN]  the timer handler
 * RETURNS
 *   succeed when return 0,otherwise, fail
 * EXAMPLE
 * <code>
 * refer from vm_create_timer_ex code example
 * </code>
 *****************************************************************************/
VMINT vm_delete_timer_ex(VMINT timerid);

/*****************************************************************************
* FUNCTION
*  vm_create_kal_timer 
* DESCRIPTION
*  This interface used to create a kal timer, the priority higher than mmi task, it is related with interrupt.
* PARAMETERS
*  timer_name : [IN] timer name. It's used for debug only, and only the 
*                first 8 characters retain.
* RETURN VALUES
*  Success:        timer pointer.
*  Error:          system enter fatal error handling.
*****************************************************************************/
vm_kal_timerid vm_create_kal_timer(VMINT8 *timer_name);

/*****************************************************************************
* FUNCTION
*  vm_set_kal_timer 
* DESCRIPTION
*  This interface used to start a timer. this will cancel previous set timeout event , and start a new one.
* PARAMETERS
*  timer_ptr : [IN] timer pointer.
*  handler_func_ptr: [IN] pointer of timeout handler, it will be called after 
*                    timeout happens, not use LinkIt API
*  handler_param_ptr: [IN] user supply argument for handler_func_ptr
*  delay: [IN] timeout duration in terms of time ticks, the maximum value is 0xFFFFFFFF
*  reschedule_time: [IN] reset delay to reschedule_time after timeout happens.
*                   If it's zero, no reschedule happens and the timer is one-shot.
*                   Otherwise, it's a periodic timer.
* RETURN VALUES
*  pointer of timder id, NULL means failed to create
*****************************************************************************/
void vm_set_kal_timer(vm_kal_timerid timer_ptr, vm_kal_timer_func_ptr handler_func_ptr,void *handler_param_ptr, VMUINT32 delay, VMUINT32 reshedule_time);

/*****************************************************************************
* FUNCTION
*  vm_cancel_kal_timer 
* DESCRIPTION
*  This interface used to cancel a timer.  Please note that canceling timer inside HISR may cancel a timer which is 
*  in expired stage but the callback function not yet been serviced.
* PARAMETERS
*  ext_timer  : [IN] timer pointer.
* RETURN VALUES
*  pointer of timder id, NULL means failed to create
*****************************************************************************/
void vm_cancel_kal_timer(vm_kal_timerid timer_ptr);

/*****************************************************************************
 * FUNCTION
 *  vm_timer_start_high_priority_timer
 * DESCRIPTION
 *  start a timer
 * PARAMETERS
 *  callback : [IN] the callback function when the timer is over time
 *  userdata : [IN] user data
 *  millisec : [IN] delay time
 *  alignment : [IN] align or non-align
 * RETURN VALUES
 *	FALSE is failed, TRUE is success
 *****************************************************************************/
VMBOOL vm_timer_start_high_priority_timer(vm_timer_func_ptr callback,void *userdata,VMUINT32 millisec,VMUINT16 alignment);

/*****************************************************************************
 * FUNCTION
 *  vm_timer_block_precise_timer_callback
 * DESCRIPTION
 *  when gpio after sleep in, the callback will be called, return >=0, precise timer stop when LCD backlight off, else not stop
 *  it is for  vm_create_timer type timer.
 * PARAMETERS
 *  userdata : [IN] user data
 * RETURN VALUES
 *	>= 0 precise timer stop, < 0 precise timer not stop when LCD backlight off
 *****************************************************************************/
typedef VMINT (*vm_timer_block_precise_timer_callback)(void *user_data);

/*****************************************************************************
 * FUNCTION
 *  vm_timer_register_block_precise_timer
 * DESCRIPTION
 *  register block precise timer
 * PARAMETERS
 *  callback : [IN] the callback function when gpio after sleep in
 *  userdata : [IN] user data
 * RETURN VALUES
 *	<0 is failed, >= 0 is success
 *****************************************************************************/
VMINT vm_timer_register_block_precise_timer(vm_timer_block_precise_timer_callback callback, void* user_data);


/*****************************************************************************
 * FUNCTION
 *  vm_create_timer_ts
 * DESCRIPTION
 *  create timer. 
 *  It is similar with vm_create_timer, but only added a parameter : ignore_by_ts. if ignore_by_ts is set as VM_TRUE, its function is same with vm_create_timer,
 *  if project support tiny system, the timer will be ignore, the system can enter tiny system. if ignore_by_ts is set as VM_FALSE, the system cant enter hibernation tiny mode,
 *  but can enter suspend tiny mode if millisec more than 1800. Delete timer using vm_delete_timer.
 * PARAMETERS
 *  millisec : [IN] the length if the interval. The unit of interval is millisecond
 *  timerproc : [IN] the callback function when the timer is over time
 *  ignore_by_ts : [IN] whether the timer is ignored by system when enter tiny system
 * RETURNS
 *  The timer handle,the handle >0 when succeed,otherwise, handle <0
 *****************************************************************************/
VMINT vm_create_timer_ts(VMUINT32 millisec, VM_TIMERPROC_T timerproc, VMBOOL ignore_by_ts);


/*****************************************************************************
 * FUNCTION
 *  vm_create_timer_ex_ts
 * DESCRIPTION
 *  create timer. 
 *  It is similar with vm_create_timer_ex, but only added a parameter : ignore_by_ts. if ignore_by_ts is set as VM_TRUE, its function is same with vm_create_timer,
 *  if project support tiny system, the timer will be ignore, the system can enter tiny system. if ignore_by_ts is set as VM_FALSE, the system cant enter hibernation tiny mode,
 *  but can enter suspend tiny mode if millisec more than 1800. Delete timer using vm_delete_timer_ex.
 * PARAMETERS
 *  millisec : [IN] the length if the interval. The unit of interval is millisecond
 *  timerproc : [IN] the callback function when the timer is over time
 *  ignore_by_ts : [IN] whether the timer is ignored by system when enter tiny system
 * RETURNS
 *  The timer handle,the handle >0 when succeed,otherwise, handle <0
 *****************************************************************************/
VMINT vm_create_timer_ex_ts(VMUINT32 millisec, VM_TIMERPROC_T timerproc, VMBOOL ignore_by_ts);


#ifdef __cplusplus
}
#endif

#endif
