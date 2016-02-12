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
 * vmpwr_sdk.h
 *
 * Project:
 * --------
 *  MAUI
 *
 * Description:
 * ------------
 *  pwr
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
#ifndef VM_PRW_SDK_H
#define VM_PRW_SDK_H
#ifdef __cplusplus
extern "C"{
#endif/*__cplusplus*/
#include "vmsys.h"

typedef enum
{
	  VM_MAINLCD_BRIGHTNESS_LEVEL0   =0  ,  /* TURN OFF*/
    VM_MAINLCD_BRIGHTNESS_LEVEL1  ,
    VM_MAINLCD_BRIGHTNESS_LEVEL2  ,
    VM_MAINLCD_BRIGHTNESS_LEVEL3  ,
    VM_MAINLCD_BRIGHTNESS_LEVEL4  ,
    VM_MAINLCD_BRIGHTNESS_LEVEL5  ,
	  VM_MAINLCD_BRIGHTNESS_LEVEL6	,
    VM_MAINLCD_BRIGHTNESS_LEVEL7  ,
    VM_MAINLCD_BRIGHTNESS_LEVEL8  ,
    VM_MAINLCD_BRIGHTNESS_LEVEL9	,
    VM_MAINLCD_BRIGHTNESS_LEVEL10	,
    VM_MAINLCD_BRIGHTNESS_LEVEL11 ,
    VM_MAINLCD_BRIGHTNESS_LEVEL12 ,
    VM_MAINLCD_BRIGHTNESS_LEVEL13 ,
    VM_MAINLCD_BRIGHTNESS_LEVEL14 ,
    VM_MAINLCD_BRIGHTNESS_LEVEL15 ,
    VM_MAINLCD_BRIGHTNESS_LEVEL16 ,
    VM_MAINLCD_BRIGHTNESS_LEVEL17 ,
    VM_MAINLCD_BRIGHTNESS_LEVEL18 ,
    VM_MAINLCD_BRIGHTNESS_LEVEL19 ,
    VM_MAINLCD_BRIGHTNESS_LEVEL20 ,
    VM_MAINLCD_BRIGHTNESS_20LEVEL_MAX /* DO NOT USE THIS */
} vm_mainlcd_brightness_level_enum;

typedef enum {
	turn_on_mode = 0, 				/*turn on saving mode */
	turn_off_mode					/*turn off saving mode*/
} power_saving_mode_enum;

/*****************************************************************************
 * FUNCTION
 *  vm_mode_block
 * DESCRIPTION
 *  Disable the system switch to Tiny mode, usually used when you want the device keep in Normal mode.
 * PARAMETERS
 *  void
 * RETURNS
 * void
 *****************************************************************************/ 
void vm_mode_block(void);

/*****************************************************************************
 * FUNCTION
 *  vm_mode_unblock
 * DESCRIPTION
 *  Enable the system switch to Tiny mode 
 * PARAMETERS
 *  void
 * RETURNS
 *  void
 *****************************************************************************/ 
void vm_mode_unblock(void);

/*****************************************************************************
 * FUNCTION
 *  vm_get_battery_level
 * DESCRIPTION
 *  get handset battery level 
 * PARAMETERS
 *  void
 * RETURNS
 *  battery level  .depend on the target config, return value maybe one of 0,25,50,75,100
 * or one of 0,33,66,100
 *****************************************************************************/ 
VMINT vm_get_battery_level(void) ;


/*****************************************************************************
 * FUNCTION
 *  vm_charbat_is_charging
 * DESCRIPTION
 *  is charging or not 
 * PARAMETERS
 *  void
 * RETURNS
 *  Return VM_TRUE if battery is charging or return VM_FALSE
 *****************************************************************************/ 
VMBOOL vm_charbat_is_charging(void);

/*****************************************************************************
 * FUNCTION
 *  vm_set_mainlcd_brightness
 * DESCRIPTION
 *  set handset main LCD brightness 
 * PARAMETERS
 *  vm_mainlcd_brightness_level_enum 
 * RETURNS
 * NO 
 *****************************************************************************/ 
void vm_set_mainlcd_brightness(vm_mainlcd_brightness_level_enum brighness_level);

/*****************************************************************************
 * FUNCTION
 *  vm_get_mainlcd_brightness
 * DESCRIPTION
 *  get handset main LCD brightness 
 * PARAMETERS
 *  NULL 
 * RETURNS
 * an unsigned int value
 *****************************************************************************/ 
VMINT vm_get_mainlcd_brightness(void);
/*****************************************************************************
 * FUNCTION
 *  vm_switch_power_saving_mode
 * DESCRIPTION
 *  settign saving mode.
 *	LinkIt default value is turn_on_mode, when app is set to background running or 
 *	exit, or receives INACTIVE message, the mode also should be set as turn_on_mode.
 *  turn_on_mode: LCD will off when no action occurs in a period time.
 *  turn_off_mode: LCD will keep on,only when app is on fore-ground running, can 
 *					it set the mode. 
 * PARAMETERS
 *  mode : whether open the saving mode
 * RETURNS
 *  if succeed ,return 0, otherwise,return error code
 *****************************************************************************/ 
VMINT vm_switch_power_saving_mode(power_saving_mode_enum mode);

/*****************************************************************************
 * FUNCTION
 *  vm_switch_backlight
 * DESCRIPTION
 *  turn on /off backlight
 * PARAMETERS
 * turn_on
 * 1: turn on the backlight
 * 0: turn off the backlight       
 * RETURNS
 *  
 *****************************************************************************/
void vm_switch_backlight(VMINT turn_on);

/*****************************************************************************
 * FUNCTION
 *  vm_disable_auto_screen_lock
 * DESCRIPTION
 *  diable auto screen lock function. 	
 * PARAMETERS
 *  NONE.
 * RETURNS
 *  void
 *****************************************************************************/ 
void vm_disable_auto_screen_lock(void);

/*****************************************************************************
 * FUNCTION
 *  vm_enable_auto_screen_lock
 * DESCRIPTION
 *  enable auto screen lock function. 	
 * PARAMETERS
 *  NONE.
 * RETURNS
 *  void
 *****************************************************************************/ 
void vm_enable_auto_screen_lock(void);

/*****************************************************************************
 * FUNCTION
 *  vm_reboot_normal_start
 * DESCRIPTION
 *  Launch normal shutdown flow.
 * PARAMETERS
 *  NONE.
 * RETURNS
 *  void
 *****************************************************************************/
void vm_reboot_normal_start(void);

/*****************************************************************************
 * FUNCTION
 *  vm_shutdown_normal_start
 * DESCRIPTION
 *  Launch normal shutdown flow.
 *  It plays shutdown animation and emit deinit events normally.
 * PARAMETERS
 *  trigger_man_app_id  : [IN] The ID of the application who triggers shutdown.
 * RETURNS
 *  void
 *****************************************************************************/
void vm_shutdown_normal_start(VMUINT16 trigger_man_app_id);

typedef enum
{
    /* switch finish */
    VM_FLY_MODE_SWITCH_FINISH,
    
    VM_FLY_MODE_EVENT_END
} vm_fly_mode_event_enum;

/* fly mode event structure */
typedef struct
{
    /* Event id */
    VMUINT16 evt_id; 
    /* Event structure size */
    VMUINT16 size; 
    /* User data pointer */
    void *user_data;
    /* resule */
    VMUINT16 result;	
}vm_fly_mode_event_struct;

/* fly mode switch callback */
typedef VMINT (*vm_fly_mode_cb)(vm_fly_mode_event_struct * evt, void * user_data);

/*****************************************************************************
 * FUNCTION
 *  vm_fly_mode_is_switching
 * DESCRIPTION
 *  get fly mode switch is running or not
 * PARAMETERS
 *  void
 * RETURNS
 *  0 : not switching  1 : switching
 *****************************************************************************/
extern VMBOOL vm_fly_mode_is_switching(void);

/*****************************************************************************
 * FUNCTION
 *  vm_fly_mode_is_network_service_available
 * DESCRIPTION
 *  check if having available network service including GSM and WLAN. 
 * PARAMETERS
 *  void
 * RETURNS
 *  MMI_FALSE in flight mode
 *  MMI_TRUE  not in flight mode
 *****************************************************************************/
extern VMBOOL vm_fly_mode_is_network_service_available(void);

/*****************************************************************************
 * FUNCTION
 *  vm_fly_mode_switch
 * DESCRIPTION
 *  Switch to flight mode or back to normal mode 
 *  If check_sim is MMI_TRUE, the phone will only turn on RF of inserted SIM
 * PARAMETERS
 *  flight_mode_on      : [IN] is switch to flight mode
 *  check_sim           : [IN] is switch the RF according to SIM insert status
 *  callback            : [IN] mode switch callback
 *  user_data           : [IN] the user data in callback
 * RETURNS
 *  MMI_BOOL
 *****************************************************************************/
extern VMBOOL vm_fly_mode_switch(VMBOOL flight_mode_on, VMBOOL check_sim, vm_fly_mode_cb callback, void *user_data);

#ifdef __cplusplus
}
#endif/*__cplusplus*/

#endif/*VM_PRW_SDK_H*/
