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

#ifndef VMTSSYS_SDK_H_
#define VMTSSYS_SDK_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef NULL
#define NULL 0
#endif

typedef unsigned char VMUINT8;
typedef unsigned short VMUINT16;
typedef unsigned int VMUINT;
typedef unsigned long VMUINT32;


typedef  unsigned long long VMUINT64 ;
typedef  long long VMINT64 ;


typedef char VMINT8;
typedef short VMINT16;
typedef int  VMINT;
typedef long  VMINT32;

typedef VMUINT8 VMUCHAR;
typedef VMUINT16 VMUWCHAR;
typedef VMUINT8 * VMUSTR;
typedef VMUINT16 * VMUWSTR;

typedef VMINT8 VMCHAR;
typedef VMINT16 VMWCHAR;
typedef VMINT8 * VMSTR;
typedef VMINT16 * VMWSTR;

typedef unsigned char VMBYTE;
typedef unsigned short VMUSHORT;
typedef short VMSHORT;

typedef float VMFLOAT;

typedef VMINT VMBOOL;


typedef struct
{
    VMUINT8 unused;
}*vm_ts_timerid;

#ifndef BIT
#define BIT(i)		(1U << i)
#endif

#ifndef KHZ
#define KHZ(x)					((x) * 1000)
#endif

#ifndef MHZ
#define MHZ(x)					(KHZ(x) * 1000)
#endif

typedef int VM_TS_BSSS_MODE;
#define	VM_TS_BTSS_SUSPEND		0xcafebabe    /* suspend mode */
#define	VM_TS_BTSS_HIBERNATION	0xfee1dead    /* hibernation mode */
#define	VM_TS_BTSS_INVALID_MODE	0xDEADFA11    /* invalid mode */

/* For mode swith and blocker */
typedef enum _VM_TS_BTSS_CLIENT{
	VM_TS_BTSS_CLIENT_MEMORY_DUMP = BIT(0), /* memdump */
	VM_TS_BTSS_CLIENT_TIMER = BIT(1),		/* timer */
	VM_TS_BTSS_CLIENT_LOG = BIT(2),         /* log */
	VM_TS_BTSS_CLIENT_KEYPAD = BIT(3),      /* keypad */
	VM_TS_BTSS_CLIENT_DEF_INT = BIT(4),     /* define INT */
	VM_TS_BTSS_CLIENT_CUST = BIT(30),       /* cust */
}VM_TS_BTSS_CLIENT;


/* DOM-NOT_FOR_SDK-BEGIN */
void vm_ts_assert(VMSTR file, VMINT line);
void* vm_ts_csci_addr(char* key);
/* DOM-NOT_FOR_SDK-END */


/* prototype of timer callback function */
typedef void (*vm_ts_timer_func_ptr)(void *param_ptr);

/* prototype of msg handler callback function */
typedef void* (*vm_ts_service_hdlr_t)(VMINT func_id);

/* prototype of callback function when exit tiny mode */
typedef void (*vm_ts_exit_hdlr_t)(void);

typedef void (*vm_ts_swatch_pedometer_cb)(void* data);

/*****************************************************************************
 * FUNCTION
 * vm_ts_irq_mask
 * DESCRIPTION
 *  This interface used in tiny mode, Mask the I bit of the processor. Note this function must be used in pairs with vm_ts_irq_restore.
 *  And more, the I bit mask time should not exceed 5ms.
 * PARAMETERS
 *  
 * RETURN VALUES
 * mask status of the current I bit, it should be an input parameter of vm_ts_irq_restore
 * EXAMPLE
 * <code>
 * VMUIN32 savedMask;
 * savedMask = vm_ts_irq_mask();
 *      ... // your code need to protect
 * vm_ts_irq_restore(savedMask);
 * 
 * </code>
 *****************************************************************************/
VMUINT32 vm_ts_irq_mask(void);

/*****************************************************************************
 * FUNCTION
 * vm_ts_irq_restore
 * DESCRIPTION
 *  This interface used in tiny mode, restore the I bit of the processor. Note, this function must be used in pairs with  vm_ts_irq_mask.
 * PARAMETERS
 *  saved_mask:[in] the return value of  vm_ts_irq_mask
 * RETURN VALUES
 * EXAMPLE
 * <code>
 * VMUIN32 savedMask;
 * savedMask = vm_ts_irq_mask();
 *      ... // your code need to protect
 * vm_ts_irq_restore(savedMask);
 * 
 * </code>
 *****************************************************************************/
void vm_ts_irq_restore(VMUINT32 saved_mask);

/*****************************************************************************
 * FUNCTION
 * vm_ts_take_protect
 * DESCRIPTION
 *  To get system thread protect. Note this function must be used in pairs with vm_ts_give_protect.
 * PARAMETERS
 *   None
 * RETURN VALUES
 *  protect status which should be a parameter of vm_ts_give_protect.
 * EXAMPLE
 * <code>
 * VMUIN32 ret;
 * ret = vm_ts_take_protect ();
 *      ... // your code need to protect
 * vm_ts_give_protect(ret);
 * 
 * </code>
 *****************************************************************************/
VMUINT32 vm_ts_take_protect(void);

/*****************************************************************************
 * FUNCTION
 * vm_ts_give_protect
 * DESCRIPTION
 *  To give the protect. Note, this function must be used in pairs with  vm_ts_take_protect.
 * PARAMETERS
 *  saved_mask :[in] the return value of  vm_ts_take_protect
 * RETURN VALUES
 *  none
 * EXAMPLE
 * <code>
 * VMUIN32 ret;
 * ret = vm_ts_take_protect ();
 *      ... // your code need to protect
 * vm_ts_give_protect(ret);
 * 
 * </code>
 *****************************************************************************/
void vm_ts_give_protect(VMUINT32 saved_mask);

/*****************************************************************************
* FUNCTION
*  vm_ts_create_timer 
* DESCRIPTION
*  This interface used in tiny mode, create a timer.
* PARAMETERS
*  timer_name : [IN] timer name. It's used for debug only, and only the 
*                first 8 characters retain.
* RETURN VALUES
*  Success:        timer pointer.
*  Error:          system enter fatal error handling.
*****************************************************************************/
vm_ts_timerid vm_ts_create_timer(VMINT8 *timer_name);

/*****************************************************************************
* FUNCTION
*  vm_ts_set_timer 
* DESCRIPTION
*  This interface used in tiny mode, start a timer. this will cancel previous set timeout event , and start a new one.
* PARAMETERS
*  timer_ptr : [IN] timer pointer.
*  handler_func_ptr: [IN] pointer of timeout handler, it will be called after 
*                    timeout happens
*  handler_param_ptr: [IN] user supply argument for handler_func_ptr
*  delay: [IN] timeout duration in terms of time ticks, the maximum value is 0xFFFFFFFF
*  reschedule_time: [IN] reset delay to reschedule_time after timeout happens.
*                   If it's zero, no reschedule happens and the timer is one-shot.
*                   Otherwise, it's a periodic timer.
* RETURN VALUES
*  N/A
*****************************************************************************/
void vm_ts_set_timer(vm_ts_timerid timer_ptr, vm_ts_timer_func_ptr handler_func_ptr,void *handler_param_ptr, VMUINT32 delay, VMUINT32 reshedule_time);

/*****************************************************************************
* FUNCTION
*  vm_ts_cancel_timer 
* DESCRIPTION
*  This interface used in tiny mode, cancel a timer.  Please note that canceling timer inside HISR may cancel a timer which is 
*  in expired stage but the callback function not yet been serviced.
* PARAMETERS
*  ext_timer  : [IN] timer pointer.
* RETURN VALUES
*  N/A
*****************************************************************************/
void vm_ts_cancel_timer(vm_ts_timerid timer_ptr);

/*****************************************************************************
* FUNCTION
*  vm_ts_get_mem 
* DESCRIPTION
*  This interface used in tiny mode, get shared memory address
* RETURN VALUES
*  pointer of shared memory, NULL means there is no shared memory
*****************************************************************************/
void* vm_ts_get_mem(void);

/*****************************************************************************
* FUNCTION
*  vm_ts_get_mem_size 
* DESCRIPTION
*  This interface used in tiny mode, get shared memory size
* RETURN VALUES
*  size of shared memory
*****************************************************************************/
VMINT vm_ts_get_mem_size(void);

/*****************************************************************************
* FUNCTION
*  vm_ts_log_int 
* DESCRIPTION
*  This interface used in tiny mode, log function for application, for reducing code size, we not support formatted 
*  output of log, this function can output three integer and on string
* PARAMETERS
*  str  : [IN] string to output. 
*  i : [IN] integer to output
*  j : [IN] integer to output
*  k : [IN] integer to output
*****************************************************************************/
void vm_ts_log_int(VMSTR str, VMINT i, VMINT j, VMINT k);

/*****************************************************************************
* FUNCTION
*  vm_ts_log_float 
* DESCRIPTION
*  This interface used in tiny mode, log function for application, for reducing code size, we not support formatted 
*  output of log, this function can output three float number and on string
* PARAMETERS
*  str  : [IN] string to output. 
*  i : [IN] float number to output
*  j : [IN] float number to output
*  k : [IN] float number to output 
*****************************************************************************/
void vm_ts_log_float(VMSTR str, VMFLOAT i, VMFLOAT j, VMFLOAT k);

/*****************************************************************************
* FUNCTION
*  vm_ts_log_hex
* DESCRIPTION
*  This interface used in tiny mode, log function for application, for reducing code size, we not support formatted 
*  output of log, this function can output three unsigned integer and one string
* PARAMETERS
*  str  : [IN] string to output, the max size is 64 bytes, more then it will cut off.
*  i : [IN] integer to output
*  j : [IN] integer to output
*  k : [IN] integer to output
*****************************************************************************/
void vm_ts_log_hex(VMSTR str, VMUINT i, VMUINT j, VMUINT k);

/*****************************************************************************
* FUNCTION
*  vm_ts_get_mode 
* DESCRIPTION
*  This interface used in tiny mode, get current tiny mode
*																AP system			Tiny Suspend				Tiny Hibernation
*	PSRAM power down?							No						No									Yes
*	PSRAM  can enter standby?			Yes						Yes									N/A
*	Access PSRAM									Yes						No									No
*	Switch mode latency						N/A	 					40 ms								1 sec
*	CPU performance								FULL speed		26MHz								32KHz
*	Power consumption							High					Low									Lowest
*	Scenario											Run						Second level sleep	Minute level sleep
*
* PARAMETERS
*  N/A
* RETURN VALUES
* VM_TS_BTSS_SUSPEND
* VM_TS_BTSS_HIBERNATION
* VM_TS_BTSS_INVALID_MODE
*****************************************************************************/
VM_TS_BSSS_MODE vm_ts_get_mode(void);

/*****************************************************************************
* FUNCTION
*  vm_ts_mode_block 
* DESCRIPTION
*  This interface used in tiny mode, disable tiny system from entering AP system, use this when preparing shared information
* PARAMETERS
*  client  : [IN] please refer VM_TS_BTSS_CLIENT
*****************************************************************************/
void vm_ts_mode_block(VM_TS_BTSS_CLIENT client);

/*****************************************************************************
* FUNCTION
*  vm_ts_mode_unblock 
* DESCRIPTION
*  This interface used in tiny mode, enable tiny system from entering AP system
* PARAMETERS
*  client  : [IN] please refer VM_TS_BTSS_CLIENT
*****************************************************************************/
void vm_ts_mode_unblock(VM_TS_BTSS_CLIENT client);

/*****************************************************************************
* FUNCTION
*  vm_ts_switch_to_ap_mode 
* DESCRIPTION
*  This interface used in tiny mode, trigger entering AP system
* PARAMETERS
*  client  : [IN] please refer VM_TS_BTSS_CLIENT
*****************************************************************************/
void vm_ts_switch_to_ap_mode(VM_TS_BTSS_CLIENT client);

/*****************************************************************************
* FUNCTION
*  vm_ts_requirement 
* DESCRIPTION
*  This interface used in tiny mode, request CPU frequency, scale down CPU frequency according to system requirement 
*  OR for power saving , set different voltage for different frequency
* PARAMETERS
*  hz  : [IN] only support 32KHz and 26MHz
* RETURN VALUES
*  the number to set, unit is Hz
 * EXAMPLE
 * <code>
 * vm_ts_requirement(MHZ(100))
 * vm_ts_requirement(-1*MHZ(100))
*****************************************************************************/
void vm_ts_requirement(VMINT hz);

/*****************************************************************************
* FUNCTION
*  vm_ts_get_freq 
* DESCRIPTION
*  This interface used in tiny mode, to get current CPU speed 
* RETURN VALUES
*  current CPU's speed, the unit is Hz and maximum frequency is 26MHz
*****************************************************************************/
VMINT vm_ts_get_freq(void);

/*****************************************************************************
* FUNCTION
*  VM_TS_ASSERT 
* DESCRIPTION
*  This interface used in tiny mode, debug for assert
* RETURN VALUES
*  N/A
*****************************************************************************/
#ifdef __MRE_DEBUG__
	#define VM_TS_ASSERT(expr) do {if(!(expr)) vm_ts_assert((VMSTR)__FILE__, __LINE__); } while (0)
#else
	#define VM_TS_ASSERT(expr) do {if(!(expr)) {} } while (0)
#endif

/*****************************************************************************
* FUNCTION
*  vm_ts_reg_service 
* DESCRIPTION
*  This interface used in tiny mode, driver app can register service for other app use
* PARAMETERS
*  name  : [IN] server name, must less the 8 charactors
*  hdlr : [IN] service handler
* RETURN VALUES
*  TRUE : if register success
*  FALSE : failed
*****************************************************************************/
VMBOOL vm_ts_reg_service(char* name, vm_ts_service_hdlr_t hdlr);

/*****************************************************************************
* FUNCTION
*  vm_ts_get_service 
* DESCRIPTION
*  This interface used in tiny mode, app can get service form the app that had been
*  register service to engine.
* PARAMETERS
*  service_name : [IN] server name register to engine use vm_ts_reg_service
*  func_id : [IN] function id that server provide
* RETURN VALUES
*  function interface pointer
*****************************************************************************/
void* vm_ts_get_service(char* service_name, VMINT func_id );

/*****************************************************************************
* FUNCTION
*  vm_ts_reg_service 
* DESCRIPTION
*  This interface used in tiny mode, the handler will invoke before exit tiny mode
* PARAMETERS
*  hdlr : [IN] exit handler
* RETURN VALUES
*  TRUE : if register success
*  FALSE : failed
*****************************************************************************/
VMBOOL vm_ts_reg_exit_hdlr(vm_ts_exit_hdlr_t hdlr);

/*****************************************************************************
* FUNCTION
*  vm_ts_get_systicks 
* DESCRIPTION
*  This interface used in tiny mode, return elapsed system ticks from boot up
* PARAMETERS
*  N/A
* RETURN VALUES
*  elapsed system ticks from boot up
*****************************************************************************/
VMUINT32 vm_ts_get_systicks(void);

/*****************************************************************************
* FUNCTION
*  vm_ts_updata_screen 
* DESCRIPTION
*  This interface used in tiny mode, refresh the LCD screen, please use it after update the display buffer.
* PARAMETERS
*  startx : [IN] update area left up point x
*  starty : [IN] update area left up point y
*  endx : [IN] update area right down point x
*  endy : [IN] update area right down point y
* RETURN VALUES
*  0 success
*****************************************************************************/
VMUINT8 vm_ts_updata_screen(VMUINT16 startx, VMUINT16 starty, VMUINT16 endx, VMUINT16 endy);

/*****************************************************************************
* FUNCTION
*  vm_ts_get_tiny_fb_size 
* DESCRIPTION
*  This interface used in tiny mode, get display buffer size.
* PARAMETERS
*  N/A
* RETURN VALUES
*  size of display buffer in byte
*****************************************************************************/
VMUINT32 vm_ts_get_tiny_fb_size();

/*****************************************************************************
* FUNCTION
*  vm_ts_get_display_buffer 
* DESCRIPTION
*  This interface used in tiny mode, get display buffer pointer
* PARAMETERS
*  N/A
* RETURN VALUES
*  display buffer pointer
*****************************************************************************/
VMUINT8* vm_ts_get_display_buffer();

void vm_ts_swatch_pedometer_resgiter_callback(vm_ts_swatch_pedometer_cb cb);

#ifdef __cplusplus
}
#endif 

#endif /* VMSYS_SDK_H_ */
