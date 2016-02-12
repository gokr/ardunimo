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

/*******************************************************************************
 * Filename:
 * ---------
 * vmthread_sdk.h
 *
 * Project:
 * --------
 *	 MAUI
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
 *			   HISTORY
 * Below this line, this part is controlled by PVCS VM. DO NOT MODIFY!! 
 *------------------------------------------------------------------------------
 * $Log$
 *
 * 01 24 2014 zhiwei.yang
 * [MAUI_03477387] [Blocking]Stuck on uploading screen while uploading image from file manager
 * .
 *
 * 01 20 2014 xiufeng.zhang
 * [MAUI_03479763] [IOT]Merge IOT code to 11C
 * .
 *
 * 01 20 2014 xiufeng.zhang
 * [MAUI_03479763] [IOT]Merge IOT code to 11C
 * .
 *
 * 01 17 2014 xiufeng.zhang
 * [MAUI_03479763] [IOT]Merge IOT code to 11C
 * .
 *
 * *------------------------------------------------------------------------------
 * Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!! 
 *============================================================================== 
 *******************************************************************************/

#ifndef VMTHREAD_SDK_H
#define VMTHREAD_SDK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "vmsys.h"

#ifdef C2NIM
#@
type
  VM_THREAD_HANDLE* = VMUINT32  # thread handle, return by vm_thread_create 
  VM_SIGNAL_ID* = VMUINT32      # signal id, return by vm_signal_init 
@#
#endif

#ifndef C2NIM
/* thread handle, return by vm_thread_create */
#define VM_THREAD_HANDLE  VMUINT32

/* signal id, return by vm_signal_init */
#define VM_SIGNAL_ID      VMUINT32
#endif

/* wake up by the signal */
#define VM_SIGNAL_RESULT_SUCCESS      0
/* time out */
#define VM_SIGNAL_RESULT_TIMEOUT      1
/* wake up forcely without the signal */
#define VM_SIGNAL_RESULT_CANCEL       2


/* used for storing message. */
typedef struct
{
    VMUINT16 message_id;              /* the value of message id */
    void* user_data;                  /* the content data of the message */  
}VM_MSG_STRUCT;

typedef struct
{
    VMUINT8 unused;
} ggg;

typedef ggg *vm_taskid;


typedef struct _vm_mutex_list_note
{
	VMUINT8 unused;
}vm_mutex_list_note;

/* used for creating mutex. */
typedef struct
{
	VMUINT32 guard;                     /* system used, initialyze when ivoking vm_mutex_create. */
	vm_mutex_list_note* mutex_info;     /* system used, initialyze when ivoking vm_mutex_create. */
}vm_thread_mutex_struct;


/*****************************************************************************
 * FUNCTION
 *  VM_THREAD_FUNC
 * DESCRIPTION
 *  Thread main function type, and the thread will be closed when it returned.
 * PARAMETERS
 *  thread_handle         [IN]       The thread handler, used for thread management
 *  user_data               [IN]       The create param transfer to main function.
 * RETURNS
 *  return 
 *****************************************************************************/
typedef VMINT32 (*VM_THREAD_FUNC)(VM_THREAD_HANDLE thread_handle, void* user_data);

/*****************************************************************************
 * FUNCTION
 *  vm_thread_create
 * DESCRIPTION
 *  used for create a thread.
 * PARAMETERS
 *  thread_function   [IN]   The thread main function.
 *  data                   [IN]   The param of thread_function.
 *  priority               [IN]    Thread priority, 
 *                                    1 is the highest priority, 255 is the lowest priority, and main thread's priority 
 *                                    is higher than 129 and lower than 128. 0 is default priority lower than main thread.
 * RETURNS
 *  return The handle of the creating thread.
 *
 * Example
 * <code>
 *
 * VMINT vm_sub_thread_proc(VM_THREAD_HANDLE thread_handle, void* user_data)
 * {
 * 	 //do_some_thing();
 * 	 return 0;
 * }
 *		
 * vm_thread_create(vm_sub_thread_proc, NULL, 0 );
 *
 * </code>
 *****************************************************************************/
extern VM_THREAD_HANDLE vm_thread_create(VM_THREAD_FUNC thread_function, void* data,VMUINT8 priority);

/*****************************************************************************
 * FUNCTION
 *  vm_thread_get_current_handle
 * DESCRIPTION
 *  used for get thread handle. this API does not support in main thread.
 * PARAMETERS
 *  None
 * RETURNS
 *  return  The handle of current thread.
 * SEE ALSO
 *  vm_thread_get_main_handle
 *****************************************************************************/                    
extern VM_THREAD_HANDLE vm_thread_get_current_handle(void);

/*****************************************************************************
 * FUNCTION
 *  vm_thread_get_main_handle
 * DESCRIPTION
 *  used for get main thread handle.
 * PARAMETERS
 *  None
 * RETURNS
 *  return  The handle of main thread.
 * SEE ALSO
 *  vm_thread_get_current_handle
 *****************************************************************************/
extern VM_THREAD_HANDLE vm_thread_get_main_handle(void);

/*****************************************************************************
 * FUNCTION
 *  vm_thread_send_msg
 * DESCRIPTION
 *  used for sending msg between threads.
 * PARAMETERS
 *  thread         [IN]       The thread handler of reciever.
 *  msg_id        [IN]       The message id to be send.
 *  user_data    [IN]       The customer data of the message.
 * RETURNS
 *  None.
 *
 * Example
 * <code>
 * VMINT32 vm_sub_thread_proc(VM_THREAD_HANDLE thread_handle, void* user_data)
 * {
 *    VM_THREAD_HANDLE main_handle;
 * 	//do_some_thing();
 *    main_handle = vm_thread_get_main_handle();
 * 	vm_thread_send_msg(main_handle, MSG_ID_XXX, NULL);
 * 	return 0;
 * }
 * </code>
 *****************************************************************************/
extern void vm_thread_send_msg(VM_THREAD_HANDLE thread_handle, VMUINT32 msg_id, void* user_data);

/*****************************************************************************
 * FUNCTION
 *  vm_thread_get_msg
 * DESCRIPTION
 *  used for read msg from ext msg queue, and it will be blocked if the queue is empty.
 * PARAMETERS
 *  msg                        [OUT]    The msg content.
 * RETURNS
 *  None 
 *
 * Example
 * <code>
 * VMINT vm_sub_thread_proc(VM_THREAD_HANDLE thread_handle, void* user_data)
 * {
 * 	 VM_MSG_STRUCT msg;
 *
 * 	 vm_thread_get_msg(&msg);
 *     if (msg.message_id == MSG_ID_XXX)
 *     {
 * 		//do_some_thing();
 *     }
 * 	 return 0;
 * }
 * </code>
 *****************************************************************************/
extern void vm_thread_get_msg(VM_MSG_STRUCT* msg);

/*****************************************************************************
 * FUNCTION
 *  vm_signal_init
 * DESCRIPTION
 *  Initial a signal for thread communication.
 * PARAMETERS
 *  None
 * RETURNS
 *  The signal id of create.
 *	 
 * Example
 * <code>
 * VM_SIGNAL_ID s_id;
 *
 *
 * VMINT vm_sub_thread_proc(VM_THREAD_HANDLE thread_handle, void* user_data)
 * {
 *	 //do_some_thing();
 *
 *	 // wait main thread handle MSG_ID_XXX.
 *	 vm_signal_wait(s_id);
 *	 do_other_thing();
 *	 return 0;
 * }
 *
 * void handle_sysevt(VMINT message, VMINT param)
 * {
 *	 switch (message)
 *	 {
 *		 case VM_MSG_CREATE: 
 *			 //create signal.
 *			 s_id = vm_signal_init();
 * 			sub_thread_proc(vm_sub_thread_proc, NULL,  0 );
 *
 *			 break;
 *		 case VM_MSG_QUIT:
 * 			 //release signal.
 *			 vm_signal_deinit(s_id);
 *			 break;
 *		 case VM_MSG_XXX:
 *			 handle_xxx_msg();
 *			 //post signal
 *			 vm_signal_post(s_id);
 *			 break;
 *		 }
 *	 }
 * }
 *
 * </code>
 *****************************************************************************/
extern VM_SIGNAL_ID vm_signal_init(void);

/*****************************************************************************
 * FUNCTION
 *  vm_signal_clean
 * DESCRIPTION
 *  The id of the signal which was clean.
 * PARAMETERS
 *  None
 * RETURNS
 *  The signal id of create.
 *****************************************************************************/
extern void vm_signal_clean(VM_SIGNAL_ID s_id);

/*****************************************************************************
 * FUNCTION
 *  vm_signal_post
 * DESCRIPTION
 *  post a signal then all the threads, which are waiting for it, will be waken up. 
 *  the signal id is get from vm_signal_init(void)
 * PARAMETERS
 *  The id of the signal which was post.
 * RETURNS
 *  None.
 * EXAMPLE
 * <code>
 * VM_SIGNAL_ID s_id;
 *
 *
 * VMINT vm_sub_thread_proc(VM_THREAD_HANDLE thread_handle, void* user_data)
 * {
 *	 //do_some_thing();
 *
 *	 // wait main thread handle MSG_ID_XXX.
 *	 vm_signal_wait(s_id);
 *	 do_other_thing();
 *	 return 0;
 * }
 *
 * void handle_sysevt(VMINT message, VMINT param)
 * {
 *	 switch (message)
 *	 {
 *		 case VM_MSG_CREATE: 
 *			 //create signal.
 *			 s_id = vm_signal_init();
 * 			sub_thread_proc(vm_sub_thread_proc, NULL,  0 );
 *
 *			 break;
 *		 case VM_MSG_QUIT:
 * 			 //release signal.
 *			 vm_signal_deinit(s_id);
 *			 break;
 *		 case VM_MSG_XXX:
 *			 handle_xxx_msg();
 *			 //post signal
 *			 vm_signal_post(s_id);
 *			 break;
 *		 }
 *	 }
 * }
 *
 * </code>
 *****************************************************************************/
extern void vm_signal_post(VM_SIGNAL_ID s_id);

/*****************************************************************************
 * FUNCTION
 *  vm_signal_wait
 * DESCRIPTION
 *  wait a signal then the thread will getting blocking if the signal was not set. 
 *  then it will geting wake up when other thread post the signal.
 *  and this API only support in sub-thread, it can't be invoke from main thread.
 * PARAMETERS
 *  the waiting for signal id.
 * RETURNS
 *  VM_SIGNAL_RESULT_SUCCESS, if it is wake up by the signal.
 *  VM_SIGNAL_RESULT_CANCEL, if it is wake up forcely without the signal, FW doesn't suply force waking up API.
 * EXAMPLE
 * <code>
 * VM_SIGNAL_ID s_id;
 *
 *
 * VMINT vm_sub_thread_proc(VM_THREAD_HANDLE thread_handle, void* user_data)
 * {
 *	 //do_some_thing();
 *
 *	 // wait main thread handle MSG_ID_XXX.
 *	 vm_signal_wait(s_id);
 *	 do_other_thing();
 *	 return 0;
 * }
 *
 * void handle_sysevt(VMINT message, VMINT param)
 * {
 *	 switch (message)
 *	 {
 *		 case VM_MSG_CREATE: 
 *			 //create signal.
 *			 s_id = vm_signal_init();
 * 			sub_thread_proc(vm_sub_thread_proc, NULL,  0 );
 *
 *			 break;
 *		 case VM_MSG_QUIT:
 * 			 //release signal.
 *			 vm_signal_deinit(s_id);
 *			 break;
 *		 case VM_MSG_XXX:
 *			 handle_xxx_msg();
 *			 //post signal
 *			 vm_signal_post(s_id);
 *			 break;
 *		 }
 *	 }
 * }
 *
 * </code>
 *****************************************************************************/
extern VMINT32 vm_signal_wait(VM_SIGNAL_ID s_id);

/*****************************************************************************
 * FUNCTION
 *  vm_signal_timedwait
 * DESCRIPTION
 *  wait a signal then the thread will getting blocking if the signal was not set. 
 *  then it will geting wake up when other thread post the signal.
 *  and this API only support in sub-thread, it can't be invoke from main task.
 * PARAMETERS
 *  s_id:             [IN] the waiting for signal id.
 *  time_count:   [IN] the max time to wait..(microsecond)
 * RETURNS
 *  VM_SIGNAL_RESULT_SUCCESS, if it is wake up by the signal.
 *  VM_SIGNAL_RESULT_TIMEOUT, if time out.
 *  VM_SIGNAL_RESULT_CANCEL, if it is wake up forcely without the signal.
 *****************************************************************************/
extern VMINT32 vm_signal_timedwait(VM_SIGNAL_ID s_id, VMUINT32 time_count);

/*****************************************************************************
 * FUNCTION
 *  vm_signal_deinit
 * DESCRIPTION
 *  destory a signal when app will not use it any more.
 * PARAMETERS
 *  the signal id of deinit.
 * RETURNS
 *  None
 * EXAMPLE
 * <code>
 * VM_SIGNAL_ID s_id;
 *
 *
 * VMINT vm_sub_thread_proc(VM_THREAD_HANDLE thread_handle, void* user_data)
 * {
 *	 //do_some_thing();
 *
 *	 // wait main thread handle MSG_ID_XXX.
 *	 vm_signal_wait(s_id);
 *	 do_other_thing();
 *	 return 0;
 * }
 *
 * void handle_sysevt(VMINT message, VMINT param)
 * {
 *	 switch (message)
 *	 {
 *		 case VM_MSG_CREATE: 
 *			 //create signal.
 *			 s_id = vm_signal_init();
 * 			sub_thread_proc(vm_sub_thread_proc, NULL,  0 );
 *
 *			 break;
 *		 case VM_MSG_QUIT:
 * 			 //release signal.
 *			 vm_signal_deinit(s_id);
 *			 break;
 *		 case VM_MSG_XXX:
 *			 handle_xxx_msg();
 *			 //post signal
 *			 vm_signal_post(s_id);
 *			 break;
 *		 }
 *	 }
 * }
 *
 * </code>*****************************************************************************/
extern void vm_signal_deinit(VM_SIGNAL_ID s_id);

/*****************************************************************************
 * FUNCTION
 *	vm_mutex_create
 * DESCRIPTION
 *	create a mutex. And it need not destroy, 
 * PARAMETERS
 *	mutex		  : [OUT]		the mutex that needs to create.
 * RETURNS
 *	void
 * Example
 * <code>
 * static vm_thread_mutex_struct my_mutex;
 *
 * VMINT vm_sub_thread1_proc(VM_THREAD_HANDLE thread_handle, void* user_data)
 * {
 *      vm_mutex_create(&my_mutex);
 *      vm_mutex_lock(&my_mutex);
 *      //access global data;
 *      change_global_data();
 *      vm_mutex_unlock(&my_mutex);
 *  }
 *
 * VMINT vm_sub_thread2_proc(VM_THREAD_HANDLE thread_handle, void* user_data)
 * {
 *      do_some_thing();
 *      vm_mutex_lock(&my_mutex);     //suppose my_mutex has already been created.
 *      //access global data;
 *      change_global_data();
 *      vm_mutex_unlock(&my_mutex);
 *  } 
 * </code>
 *****************************************************************************/
extern void vm_mutex_create(vm_thread_mutex_struct *mutex);

/*****************************************************************************
 * FUNCTION
 *	vm_mutex_lock
 * DESCRIPTION
 *	get the mutex.
 * PARAMETERS
 *	mutex : [IN] The mutex
 * RETURNS
 *	void
 * Example
 * <code>
 * static vm_thread_mutex_struct my_mutex;
 *
 * VMINT vm_sub_thread1_proc(VM_THREAD_HANDLE thread_handle, void* user_data)
 * {
 *      vm_mutex_create(&my_mutex);
 *      vm_mutex_lock(&my_mutex);
 *      //access global data;
 *      change_global_data();
 *      vm_mutex_unlock(&my_mutex);
 *  }
 *
 * VMINT vm_sub_thread2_proc(VM_THREAD_HANDLE thread_handle, void* user_data)
 * {
 *      do_some_thing();
 *      vm_mutex_lock(&my_mutex);     //suppose my_mutex has already been created.
 *      //access global data;
 *      change_global_data();
 *      vm_mutex_unlock(&my_mutex);
 *  } 
 * </code>
 *****************************************************************************/
extern void vm_mutex_lock(vm_thread_mutex_struct *mutex);

/*****************************************************************************
 * FUNCTION
 *	vm_mutex_unlock
 * DESCRIPTION
 *	release the mutex.
 * PARAMETERS
 *	mutex  : [IN] The mutex
 * RETURNS
 *	void
 * Example
 * <code>
 * static vm_thread_mutex_struct my_mutex;
 *
 * VMINT vm_sub_thread1_proc(VM_THREAD_HANDLE thread_handle, void* user_data)
 * {
 *      vm_mutex_create(&my_mutex);
 *      vm_mutex_lock(&my_mutex);
 *      //access global data;
 *      change_global_data();
 *      vm_mutex_unlock(&my_mutex);
 *  }
 *
 * VMINT vm_sub_thread2_proc(VM_THREAD_HANDLE thread_handle, void* user_data)
 * {
 *      do_some_thing();
 *      vm_mutex_lock(&my_mutex);     //suppose my_mutex has already been created.
 *      //access global data;
 *      change_global_data();
 *      vm_mutex_unlock(&my_mutex);
 *  } 
 * </code>
 *****************************************************************************/
extern void vm_mutex_unlock(vm_thread_mutex_struct *mutex);

/*****************************************************************************
 * FUNCTION
 *	vm_thread_sleep
 * DESCRIPTION
 *	sleep one thread.
 * PARAMETERS
 *	timeout  : [IN] time to sleep (milli_secs)
 * RETURNS
 *	void
 * <code>
 *
 * VMINT vm_sub_thread_proc(VM_THREAD_HANDLE thread_handle, void* user_data)
 * {
 *      //do someting
 *      vm_thread_sleep(3000);
 *  }
 *
 * </code>
 *****************************************************************************/
extern void vm_thread_sleep(VMUINT32 timeout);

#ifdef __cplusplus
}
#endif

#endif /* VMXML_SDK_H */ 

