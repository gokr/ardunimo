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

#ifndef VMTOUCH_SDK_H
#define VMTOUCH_SDK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "vmsys.h"

typedef enum
{
    VM_MULTI_TOUCH_ERR_NO_RES = -7, /* no avalible resource */
    VM_MULTI_TOUCH_ERR_PARAM, /* input invalid parameter */
    VM_MULTI_TOUCH_ERR_NO_MEMORY, /* no memmory */
    VM_MULTI_TOUCH_ERR_NO_DISK, /* driver path failure */
    VM_MULTI_TOUCH_ERR_EXCEPTION, /* exception */
    VM_MULTI_TOUCH_ERR_NOT_SUPPORT, /* platform dose not support */
    VM_MULTI_TOUCH_ERR_NOT_AUTHORIZED, /* no authrization */
    VM_MULTI_TOUCH_ERR_SUCCESS = 0 /* success */
}vm_multi_touch_error_t;


/* Touch screen mode */
typedef enum
{
    /* Single touch mode, just send one finger event to application, this is default behavior */
    VM_SINGLE_TOUCH,
    /* Multi-touch mode, send several events to application, according to how many fingers on the screen, at most it is five */
    VM_MULTI_TOUCH,
    /* Total touch event total, no need to handle this */
    VM_MULTI_TOUCH_TOTAL
} vm_touch_mode;


/* structure of Point */
typedef struct
{
    /* x coordinate */
    VMINT16 x;
    /* x coordinate */
    VMINT16 y;
} vm_pen_point_struct;

/* The touch position structure */
typedef struct
{
    /* The coordinates of this event */
    vm_pen_point_struct pos;
    /* The timestamp of this event */
    VMUINT32 timestamp;
} vm_touch_pos_struct;

/*
 *  Each finger touch data information
 *  Example:
 *  typedef struct
 *  {
 *      vm_pen_point_struct down_pos; // ((200, 110), 29999)
 *      VMUINT16 merge_num; // 2
 *      vm_pen_point_struct* merge_points; // ((200, 200), 30010), ((200, 250), 30020)
 *      VMUINT16* merge_area; // (50, 40)
 *  } mmi_touch_data_struct;
 */
typedef struct
{
    VMUINT16 id; /* finger id */
    VMINT  event; /* current touch event */
    vm_touch_pos_struct currpos; /* current touch info */
    VMUINT16 area; /* current finger area */
    VMINT pre_event; /* previous touch event */
    vm_touch_pos_struct pre_pos; /* previous touch info */
    vm_touch_pos_struct down_pos; /* pen down info */
    VMUINT16 merge_num;  /* if there are several pen move events, we will send several pen move events together to application */
    vm_touch_pos_struct* merge_points; /* pen move events array */
    VMUINT16* merge_area; /* related pen move area */
} vm_multi_touch_data_struct;

typedef struct 
{
    /* The finger number of this event, at most it is five */
    VMUINT16 touch_num;
    /* The touch data of each event */
    vm_multi_touch_data_struct * touch_data;
}vm_multi_touch_event_struct;

/*****************************************************************************
 * FUNCTION
 *  vm_multi_touch_get_mode
 * DESCRIPTION
 *  get current screen touch mode
 * PARAMETERS
 *  void
 * RETURNS
 *  VMINT
 *****************************************************************************/
VMINT vm_multi_touch_get_mode(void);

/*****************************************************************************
 * FUNCTION
 *  vm_multi_touch_set_mode
 * DESCRIPTION
 *  set touch screen mode
 * PARAMETERS
 *  mode : [IN] the parameter should be vm_touch_mode, single or multiple
 * RETURNS
 *  VMINT
 *****************************************************************************/
VMINT vm_multi_touch_set_mode(vm_touch_mode mode);

/*****************************************************************************
 * <GROUP  CallbackFunctions>
 * FUNCTION
 *  vm_multi_touch_proc_t
 * DESCRIPTION
 * PARAMETERS
 *  param : [IN] vm_multi_touch_event_struct.
 *  user_data : [IN] user data.
 * RETURNS
 *  VMINT
 *****************************************************************************/
typedef VMINT (*vm_multi_touch_proc_t) (vm_multi_touch_event_struct * evt_info, void * user_data);

/*****************************************************************************
 * FUNCTION
 *  vm_touch_register_proc
 * DESCRIPTION
 *  Register touch proc by screen level, no need to reset, the single touch event or
 * PARAMETERS
 *  proc : [IN] the proc, the event in the proc should be vm_multi_touch_event_struct.
 *  user_data : [IN] user data, framework will send this user_data to your proc
 * RETURNS
 *  vm_touch_register_proc
 *****************************************************************************/
VMINT vm_multi_touch_register_proc(vm_multi_touch_proc_t proc, void *user_data);


/*****************************************************************************
 * FUNCTION
 *  vm_pen_configure_sampling_period
 * DESCRIPTION
 *  Config sampling period of Event-based
 * PARAMETERS
 *  sp         :[IN]        (Pen Event)Sampling period in pen-moving (multiple of 10ms)
 * RETURNS
 *  VMINT
 * RETURN VALUES
 *  0 : success
 *  non-zero : failure
 *  -1 : no authorization
 *****************************************************************************/
VMINT vm_pen_configure_sampling_period(VMUINT sp);

/*****************************************************************************
 * FUNCTION
 *  vm_is_finger_touch_version
 * DESCRIPTION
 *  Check whether the phone support finger touch feature or not.
 * PARAMETERS
 *  void
 * RETURN VALUES
 *  TRUE : Supports finger touch feature.
 *  FALSE : Not support.
 *****************************************************************************/
VMINT vm_is_finger_touch_version(void);

/*****************************************************************************
 * FUNCTION
 *  vm_is_support_pen_touch
 * DESCRIPTION
 *  Check whether the phone support touch panel or not.
 * PARAMETERS
 *  void
 * RETURN VALUES
 *  TRUE : Supports touch panel.
 *  FALSE : Not support.
 *****************************************************************************/
VMINT vm_is_support_pen_touch(void);

/* Pen events supported by MRE. */

/* Pen down event */
#define VM_PEN_EVENT_TAP				1
/* Pen release event */
#define VM_PEN_EVENT_RELEASE			2
/* Pen move event */
#define VM_PEN_EVENT_MOVE				3
 /* Pen long tap event. 
    Note:
    1. LongTap handler is invoked when  the pen is tapped for a period of time
        and stays at the same place where it is tapped down. 
    2. If pen move happen after pen down, there will be no pen LongTap event.
    3. Pen long tap can only happen one time at most.*/
#define VM_PEN_EVENT_LONG_TAP			4
/* Pen double click event */
#define VM_PEN_EVENT_DOUBLE_CLICK		5
/* Pen repeat event. 
    Note:
    1. Repeat can happen after LongTap or move or another repeat.
    2. Repeat event's coordinate will follow the previous events.*/
#define VM_PEN_EVENT_REPEAT			6
/* Pen abort event */
#define VM_PEN_EVENT_ABORT          7

/*****************************************************************************
 * <GROUP  CallbackFunctions>
 *
 * FUNCTION
 *  vm_pen_handler_t
 * DESCRIPTION
 *  
 * PARAMETERS
 *  event : [IN] Key event.
 *  x : [IN] x coordinate.
 *  y : [IN] y coordinate.
 * RETURNS
 *  void
 *****************************************************************************/
typedef void (*vm_pen_handler_t)(VMINT event, VMINT x, VMINT y);

/*****************************************************************************
 * FUNCTION
 *  vm_reg_pen_callback
 * DESCRIPTION
 *  Registers pen event handler.
 * PARAMETERS
 *  handler : [IN] Pen event handler.
 * RETURNS
 *  void
 *****************************************************************************/
void vm_reg_pen_callback(vm_pen_handler_t handler);

#ifdef __cplusplus
}
#endif

#endif /* VMTOUCH_SDK_H */ 

