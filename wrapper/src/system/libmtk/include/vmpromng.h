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

#ifndef	_VM_PRO_MNG_SDK_
#define _VM_PRO_MNG_SDK_

#include "vmsys.h"

#ifdef __cplusplus
extern "C" {
#endif



typedef VMINT VM_P_HANDLE;/*VMINT*/

//process procedure related interfaces

#define	VM_PMNG_OP_OK					        (0)
#define VM_PMNG_PROCESS_NO_EXISTS		        (-1)
#define	VM_PMNG_NO_OP_IN_STATUS			        (-2)
#define VM_PMNG_ERROR_PARAM				        (-3)
#define VM_PMNG_NO_MEM					        (-4)
#define VM_PMNG_ERROR_IO					    (-5)
#define	VM_PMNG_NO_SCHEDULE				        (-6)
#define	VM_PMNG_EXIT						    (-7)
#define	VM_PMNG_CERT_FAIL                       (-8)
#define	VM_PMNG_ERROR_FUNLST                    (-9)

#define VM_PMNG_SEC_TAG_PLATFORM_PARAM_DISMATCH (-10)
#define	VM_PMNG_SEC_APP_TIMESTAMP_ERROR	        (-11)
#define	VM_PMNG_SEC_IMSI_DISMATCH				(-12)
#define	VM_PMNG_SEC_BAN_LIST_APP				(-13)
#define VM_PMNG_SEC_INVALIDATE_APP				(-14)
#define VM_PMNG_SEC_CERT_OMREDUE				(-15)
#define VM_PMNG_SEC_CERT_SMALL_SYS_MEM		    (-16)

#define VM_PMNG_WAIT_ASM                        (-17)
#define VM_PMNG_NOT_SUPPORT_VP                  (-18)
#define VM_PMNG_ONLY_ONE_FOREGROUND             (-19)
#define VM_PMNG_MAX_APP_NUM_REACHED             (-20)

#define	VM_PMNG_CUR_HANDLE				(0x0f)

#define VM_PMNG_KERNEL_HANDLE			(0)

#define VM_MAX_PATH                     261 /*VM_MAX_PATH*/
/*VM_PROCESS_STATUS*/
typedef enum 
{
    VM_PMNG_UNLOAD = 0,			/* state that loaded to memory but not started */
    VM_PMNG_FOREGROUND, 		/*  state of foreground running */
    VM_PMNG_BACKGROUND,			/*state of background running */ 
    VM_PMNG_STARTING,      /*state of starting */ 
    VM_PMNG_CLOSING,      /*state of closing */ 
    VM_PMNG_INACTIVE,    /*state of inactive */ 
    VM_PMNG_MAX_NUM      /*max status */ 
}VM_PROCESS_STATUS;

typedef enum
{
    VM_QUIT_NORMAL,
    VM_QUIT_MASS_STORAGE,
    VM_QUIT_CARD_PLUG_OUT,
    VM_QUIT_LANGUAGE_CHANGE    
}VM_QUIT_TYPE;
/*vm_process_property*/
typedef struct
{
    VM_P_HANDLE         pHandle;/*process's handle*/
    VMINT               appID;/*appid*/
    VM_PROCESS_STATUS   status;/*VM_PROCESS_STATUS*/
    VM_P_HANDLE         pParentHandle;/*parent's handle*/
    VMINT               type;/*not used*/
    VMINT               reserved[5];/*not used*/
    VMWCHAR             filePath[VM_MAX_PATH];/*path*/
}vm_process_property;

typedef struct {
	VMINT (*sys_event_filter)(VMINT message, VMINT param);
	VMINT (*pen_event_filter)(VMINT pen_event, VMINT x, VMINT y);
	VMINT (*key_event_filter)(VMINT key_event, VMINT key_code);
} _event_filter_t;

/* LinkIt module structure */
typedef struct
{
    VMUINT   mod_core_base       : 1;//base
    VMUINT   mod_core_sandbox    : 1;//sandbox
    VMUINT   mod_core_resmgr     : 1;//resource manager
    VMUINT   mod_core_safety     : 1;//safety
    VMUINT   mod_core_commu      : 1;//communication
    VMUINT   mod_core_sm         : 1;//share module,use for ADS,RVCT
    VMUINT   mod_core_so         : 1;//share object,for RVCT,GCC
    VMUINT   mod_lib_appres      : 1;//app resource
    VMUINT   mod_lib_c           : 1;//c library
    VMUINT   mod_lib_chset       : 1;//char set
    VMUINT   mod_lib_defgame     : 1;
    VMUINT   mod_lib_ddraw       : 1;//direct draw
    VMUINT   mod_lib_gfxold      : 1;
    VMUINT   mod_lib_image       : 1;//graphic
    VMUINT   mod_lib_http        : 1;//http
    VMUINT   mod_lib_ime         : 1;//ime
    VMUINT   mod_lib_ini         : 1;
    VMUINT   mod_lib_log         : 1;//log
    VMUINT   mod_lib_mullang     : 1;//multi-language
    VMUINT   mod_lib_network     : 1;//network
    VMUINT   mod_lib_vip         : 1;
    VMUINT   mod_lib_vip_vg      : 1;
    VMUINT   mod_lib_xml         : 1;//xml
    VMUINT   mod_sal_audio       : 1;//audio
    VMUINT   mod_sal_bitstream   : 1;//bit stream
    VMUINT   mod_sal_camera      : 1;//camera
    VMUINT   mod_sal_cell        : 1;//cell
    VMUINT   mod_sal_che_des     : 1;//CHE DES
    VMUINT   mod_sal_che_md5     : 1;//CHE MD5
    VMUINT   mod_sal_che_sha1    : 1;//CHE SHA1
    VMUINT   mod_sal_gps         : 1;//gps
    VMUINT   mod_sal_mms         : 1;//mms
    VMUINT   mod_sal_phonebook   : 1;//phonebook
    VMUINT   mod_sal_sensor      : 1;//sensor
    VMUINT   mod_sal_sim         : 1;//sim
    VMUINT   mod_sal_sms         : 1;//sms
    VMUINT   mod_sal_socket      : 1;//socket
    VMUINT   mod_sal_status      : 1;//status bar
    VMUINT   mod_sal_tele        : 1;//telephone
    VMUINT   mod_sal_timer       : 1;//timer
    VMUINT   mod_sal_video       : 1;//video
    VMUINT   mod_sal_wallpaper   : 1;
    VMUINT   mod_sal_wps         : 1;//https
    VMUINT   mod_app_launch      : 1;//launch app
    VMUINT   mod_sal_payment     : 1;//payment
}vm_module_struct;
/*****************************************************************************
* FUNCTION
*    vm_main
* DESCRIPTION
*  This is entry function of application and application must implement it.
*****************************************************************************/
void vm_main(void);

/**
 * the message of asking for application to repaint screen.
 */
#define VM_MSG_PAINT			1

/**
 * the message of application state from inactive to active.
 */
#define VM_MSG_ACTIVE			2

/**
 * the message of application state from active to inactive.
 */
#define VM_MSG_INACTIVE		3

/**
 * the message of creation of application
 */
#define VM_MSG_CREATE			4

/**
 * the message of quit of application
 */
#define VM_MSG_QUIT			5

/**
 * the message of application state from foreground running to background running.
 */
#define VM_MSG_HIDE			6

/**
 * the message to notify application memory card has been plug out.
 */
#define VM_MSG_CARD_PLUG_OUT		7

/**
 * the message when screen rotate.
 */
#define VM_MSG_SCREEN_ROTATE 8

/**
 * the message of application when foreground running and receive PUSH Message.
 */
#define VM_MSG_PUSH			9

/*when cgi start LinkIt app with cmd,will send VM_MSG_HTTP*/
#define VM_MSG_HTTPD       10

/**
 * when AP mode application launch success, it will receive this message, in this message app need load tiny system driver
 */
#define VM_MSG_LOAD_TINY			12

/**
 * when system switch form suspend mode to AP mode, app will receive this message, and app need deal with the share data
 */
#define VM_MSG_SUSPEND_TO_AP_MODE			13

/**
 * when system switch form hibernation mode to AP mode, app will receive this message, and app need get tiny system driver handle,  and  deal with the share data
 */
#define VM_MSG_HIBERNATION_TO_AP_MODE			14

#define VM_MSG_CELL_INFO_CHANGE       15

/**
 * when the battery is low
 */
#define VM_MSG_LOW_BATTERY			16

/**
 * when the network info status changed
 */
#define VM_MSG_NW_INFO_STATUS_CHANGED			17

#define VM_MSG_USB_CHARGER_IN                          18 /* when usb charger plug in, will send this event to app */


#define VM_MSG_USB_CHARGER_OUT                          19 /* when usb charger plug out, will send this event to app */
/**
 * when the power off
 */
#define VM_MSG_SHUTDOWN			20

/**
 * atci message 
 */
#define VM_MSG_ATCI_IND			60001

/**
 * atci message response
 */
#define VM_MSG_ATCI_RSP			60002


#define VM_MSG_RESTART_PARENT  100


/*LinkIt user ID, corresponding to the value : a string with max length 20(unit:VMCHAR)    e.g. 100973*/
#define MRE_SYS_SUBSCRIBER_ID		(1) 

/*LinkIt system user agent, corresponding to the value : a string with max length 20(unit:VMCHAR)    e.g. Gionee-A10*/
#define MRE_SYS_EQUIPMENT_ID		(2)

/*LinkIt version,corresponding to the value : a string with max length 12(unit:VMCHAR) 
 *naming rule :"main version number.sub-version number.release number",e.g. 1.2.6 */
#define MRE_SYS_VERSION				(3)

/*platform version,corresponding to the value :a string with max length 30(unit:VMCHAR). e.g. MT6225_08A_VERSION*/
#define MRE_SYS_HOST_VERSION		(4)

/*Max memory that LinkIt can get,corresponding to the value :a string with max length 6(unit:VMCHAR), it can be change to
*number by atoi function(unit:KB), the memory is the sum of LinkIt system memory and app memory. e.g. 800*/
#define MRE_SYS_HOST_MAX_MEM		(5)

/*LinkIt system home path,corresponding to the value :a string with max length 30(unit:VMCHAR),e.g. C:\LinkIt*/
#define MRE_SYS_HOME_DIR			(6)

/*platform build date and time :a string with max length 30(unit:VMCHAR). e.g. 2012/02/09 11:47*/
#define MRE_SYS_BUILD_DATE_TIME		(7)

/*platform release branch and info. e.g. 11B NEUTRON52_12864*/
#define MRE_SYS_RELEASE_BRANCH		(8)

#define VM_PROF_NORMAL_MODE     0   /* normal mode */
#define VM_PROF_MEETING_MODE    1   /* Meeting mode */
#define VM_PROF_SILENT_MODE     2   /* Silnet mode */
#define VM_PROF_HEADSET_MODE    3   /* Headset mode */
#define VM_PROF_BLUETOOTH_MODE  4   /* Bluetooth profile */

/* builtin sm struct */
typedef struct _vm_sm_builtin_struct
{
    VMINT8 file_name[32]; /* sm file name */
    VMUINT address;        /* sm memory address */
} vm_sm_builtin_struct;

/* DOM-NOT_FOR_SDK-BEGIN */

#define VM_MSG_CONFIRM_EXIT     1001
#define VM_MSG_FORCE_FREE     1002


/**
 *  The reason of HIDE or PAINT Event
 */
enum {
	SCREEN_POPUP = 0, 	/* HIDE or PAINT cause of POPUP£¬like incoming call, sms, input method, etc. */
	USER_END_KEY		/* HIDE cause of END key */
};

/**
 * System event structure
 */
typedef struct _vm_sysevt_param_t
{
	VMINT evt_cause; 	/* Reason of the event */
	void * evt_detail; 	/* reserved */
} vm_sysevt_param_t;

/* DOM-NOT_FOR_SDK-END */

/*****************************************************************************
* FUNCTION
 *    vm_reg_sysevt_callback
 * DESCRIPTION
 *  register system message callback function.must be called in vm_main()
 * PARAMETERS
 *  f : [IN] callback function.
*****************************************************************************/
void vm_reg_sysevt_callback(void (*f)(VMINT message, VMINT param));

/*****************************************************************************
* FUNCTION
*    vm_exit_app
* DESCRIPTION
*  LinkIt application call this function to quit. 
*****************************************************************************/
void vm_exit_app(void);

/* DOM-NOT_FOR_SDK-BEGIN */
// do not support this function
/*****************************************************************************
* FUNCTION
*    vm_exit_and_update_app
* DESCRIPTION
*  LinkIt application call this function to quit and update application itself.
*****************************************************************************/
void vm_exit_and_update_app(void);
/* DOM-NOT_FOR_SDK-END */


/* DOM-NOT_FOR_SDK-BEGIN */

/******************************************************************************
 * FUNCTION
 *	vm_get_customer_name
 * DESCRIPTION
 *	get customer name
 * PARAMETERS
 *	value : [OUT] string to store customer name.
 *	len : [IN] length of value.
 * RETURNS
 *	length of customer name.
 ******************************************************************************/
VMUINT vm_get_customer_name(VMCHAR *value, VMUINT len);

/******************************************************************************
 * FUNCTION
 *	vm_get_origin_release_verno
 * DESCRIPTION
 *	get origin release verno.
 * PARAMETERS
 *	value : [OUT] string to store origin release verno.
 *	len : [IN] length of value.
 * RETURNS
 *	length of origin release verno.
 ******************************************************************************/
VMUINT vm_get_origin_release_verno(VMCHAR *value, VMUINT len);

/* DOM-NOT_FOR_SDK-END */

/*****************************************************************************
* FUNCTION
 *    vm_get_exec_filename
 * DESCRIPTION
 *  get current application file name
 * PARAMETERS
 *  filename: [OUT] output file name string encoding with UCS2 format.
 * RETURNS
 *  if 0, file name will output to the parameter filename, else means there is no application running.
*****************************************************************************/
VMINT vm_get_exec_filename(VMWSTR filename);

/*****************************************************************************
 * FUNCTION
 *  vm_get_sys_property
 * DESCRIPTION
 *  get LinkIt system property. Property is defined as group of key and value. The property is maintained by LinkIt internal and APP can not 
 *  modify it or delete it.
 * PARAMETERS
 *  key : [IN] the key to get the system property
 *  value : [OUT] point to continuous memory,store the gotten system property. if value ==NULL, it shows that no data writing operation.
 *  len : [IN] the max length that value storing data. unit: VMCHAR
 *              e.g. if len =12 and actual written length is 10,  value[10] = 0x00
 *                      if len =12 and actual written length is 12,  value string will not include 0x00
 *                      if len =12 and actual need to be written length is 15, only the first 12 character will be written to value region
 * RETURNS
 *  the actual written length, not including 0x00
 * EXAMPLE
 *	VMCHAR value[20] = {0};
 *    VMUINT valueNum = vm_get_sys_property(MRE_SYS_SUBSCRIBER_ID, value, 20);
 *****************************************************************************/ 
VMUINT vm_get_sys_property(const VMINT key, VMCHAR* value, VMUINT len);

/*****************************************************************************
 * FUNCTION
 *  vm_get_modules
 * DESCRIPTION
 *  get modules information 
 * PARAMETERS
 *  modules : module structure
 *  size : module structure's size
 * RETURNS
 *  if succeed ,return 0, otherwise,return error code
 *****************************************************************************/
VMINT vm_get_modules(vm_module_struct *modules, VMUINT size);

/*****************************************************************************
 * FUNCTION
 *  vm_get_version
 * DESCRIPTION
 *  get version  
 * PARAMETERS
 *  
 * RETURNS:
 * if 1000,will be the version LinkIt1.0.00, if 3000,will be the version LinkIt3.0.00
 *  version
 *****************************************************************************/
VMUINT vm_get_version(void);

/* DOM-NOT_FOR_SDK-BEGIN */
/*****************************************************************************
* FUNCTION
 *    vm_reg_func_callback
 * DESCRIPTION
 *  register get function pointer callback. for download UI
 * PARAMETERS
 *  f : [IN] callback function.
*****************************************************************************/
void vm_reg_func_callback(VMINT (*f)(VMSTR symbol));
/* DOM-NOT_FOR_SDK-END */

/*****************************************************************************
* FUNCTION
 *    vm_pmng_set_bg
 * DESCRIPTION
 *  set the caller process to background state. This function can be invoked only during foreground
 *  state, and all the UI resource should be release before call this function.
 * RETURNS
 *  result of setting background state
 * RETURN VALUES                                      
 *  VM_PMNG_OP_OK : set successfully.
 *  VM_PMNG_NO_OP_IN_STATUS : the caller process is not during foreground state.
 *  
*****************************************************************************/
VMINT vm_pmng_set_bg(void);

/*****************************************************************************
* FUNCTION
 *    vm_pmng_state
 * DESCRIPTION
 *  get the state of specified process ID.
 * PARAMETERS
 *  p_handle : [IN]  process handle to be checked. If want to get current process state,
 *  it should be VM_PMNG_CUR_HANDLE.
 * RETURNS
 *  the state of specified process.
* RETURN VALUES                                      
 *  VM_PMNG_FOREGROUND : foreground state
 *  VM_PMNG_BACKGROUND : background state
 *  VM_PMNG_PAUSED : inactive state
 *  VM_PMNG_UNLOAD : unloaded state
 *  
*****************************************************************************/
VM_PROCESS_STATUS vm_pmng_state(VM_P_HANDLE p_handle);

/*****************************************************************************
* FUNCTION
 *    vm_pmng_get_current_handle
 * DESCRIPTION
 *  get process handle of current process(app or sm/so).
 * RETURNS
 *  the process ID of current running if larger than zero, 0 means no process running 
 *  
*****************************************************************************/
VM_P_HANDLE vm_pmng_get_current_handle(void);


/****************************************************************************
 * for application communication begin
 ****************************************************************************/

/* LinkIt application messge id base, application should define its own message id started from this. */
#define VM_MESSAGE_ID_BASE  1000

/* LINKIT application messge id maximum, application should define its own message id less than this. */
#define VM_MESSAGE_ID_MAX  60000

typedef VMINT (*VM_MESSAGE_PROC) (VM_P_HANDLE sender, VMUINT msg_id, VMINT wparam, VMINT lparam);
/*****************************************************************************
* FUNCTION
 *    vm_pmng_get_handle
 * DESCRIPTION
 *  get process handle of specified file name.
 * PARAMETERS
 *  file_name : [IN]  file name to be checked. 
 * RETURNS
 *  the process ID of specified file if larger than zero, 0 means there is no specified file running 
 *  
*****************************************************************************/
VM_P_HANDLE vm_pmng_get_handle(VMWSTR file_name);

/*****************************************************************************
* FUNCTION
 *    vm_reg_msg_proc
 * DESCRIPTION
 *  register user defined message callback function.
 *  use vm_appcomm_send_msg send msg to app, will invoke this callback
 * PARAMETERS
 *  proc : [IN] callback function.
 *<code>
 *VM_MESSAGE_PROC f;
 *VMINT message_proc(VM_P_HANDLE sender, VMUINT msg_id, VMINT wparam, VMINT lparam)
 *{
 * ...
 *}
 *f = message_proc;
 *vm_reg_msg_proc(f);
 * 
 *</code>
*****************************************************************************/
void vm_reg_msg_proc(VM_MESSAGE_PROC proc);

/*****************************************************************************
* FUNCTION
 *    vm_send_msg
 * DESCRIPTION
 *  send message to LinkIt app or native app, will invoke message procedure directly.
 * PARAMETERS
 *  phandle : [IN] receiver process handle, if receiver is native application, this value should be zero.
 *  msg_id : [IN] user defined message ID, should larger than VM_MESSAGE_ID_BASE.
 *  wparam : [IN] wparam of message.
 *  lparam : [IN] lparam of message.
 * RETURNS
 *  message procedure return value.
*****************************************************************************/
VMINT vm_send_msg(VM_P_HANDLE phandle, VMUINT msg_id, VMINT wparam, VMINT lparam);


/*****************************************************************************
* FUNCTION
 *    vm_post_msg
 * DESCRIPTION
 *  post message to LinkIt app or native app, will put this message to the end of LinkIt message queue. 
 *  when this function call finish, MMI task will dispatch LinkIt message and invoke message procedure. 
 * PARAMETERS
 *  phandle : [IN] receiver process handle, if receiver is native application, this value should be zero.
 *  msg_id : [IN] user defined message ID, should larger than VM_MESSAGE_ID_BASE.
 *  wparam : [IN] wparam of message.
 *  lparam : [IN] lparam of message.
 * RETURNS
 *  1 means add message into message queue successfully, 0 means message queue is full.
*****************************************************************************/
VMINT vm_post_msg(VM_P_HANDLE phandle, VMUINT msg_id, VMINT wparam, VMINT lparam);

/****************************************************************************
 * for application communication end
 ****************************************************************************/
 
/*****************************************************************************
* FUNCTION
 *    vm_pmng_get_app_handle
 * DESCRIPTION
 *  get process handle of current process(app).
 * RETURNS
 *  the process ID of current running app if larger than zero, 0 means no process running 
 *  
*****************************************************************************/
VMINT vm_pmng_get_app_handle(void);

/**
 * notification mode of background running application applying to foreground running.
 */
typedef enum 
{
	VM_NOTIFY_TYPE_DEFAULT = 0,            /* by default mode (follow engine control) */
	VM_NOTIFY_TYPE_SOUND = 1,		/* by sound mode */
	VM_NOTIFY_TYPE_VIBRATILITY = 2	/* by vibration mode */
} VM_FG_NOTIFY_TYPE;

/*****************************************************************************
* FUNCTION
 *  vm_start_app
 * DESCRIPTION
 *  Run another APP
 * PARAMETERS 
 *  filepath :          [IN]  The file path need to startup.
 *  parent_app_handle : [IN]  Parent APP handle, usually should be current APP.
 *  is_parent_exit :    [IN]  Is need exit Parent APP before enter new one.
 * RETURNS
 *  VM_TRUE means successed, VM_FALSE means failed 
 *  
*****************************************************************************/
VMBOOL vm_start_app(const VMWCHAR* filepath, VMINT parent_app_handle, VMINT is_parent_exit);

/*****************************************************************************
* FUNCTION
 *  vm_start_app_with_para
 * DESCRIPTION
 *  Run another APP,the parameter will be send with message VM_MSG_CREATE in param(an address)
 *  handle_sysevt(VMINT message, VMINT param)
 * PARAMETERS 
 *  filepath :          [IN]  The file path need to startup.
 *  parent_app_handle : [IN]  Parent APP handle, usually should be current APP.
 *  is_parent_exit :    [IN]  Is need exit Parent APP before enter new one.
 *  parameter : [IN] parmeter.
 *  parameter_size : [IN] parameter size
 * RETURNS
 *  void
 *  
*****************************************************************************/
void vm_start_app_with_para(const VMWCHAR* filepath, VMINT parent_app_handle, VMINT is_parent_exit,void* parameter,VMINT parameter_size);


/*****************************************************************************
* FUNCTION
 *    vm_pmng_get_process_list
 * DESCRIPTION
 *  get process list. set handle_list NULL to get process number.
 * PARAMETERS
 *  handle_list : [IN] process handle list
 *  num : [IN/OUT] process number.
 * RETURNS
 *  >0 means process number, <0 means fail
*****************************************************************************/
VMINT vm_pmng_get_process_list(VM_P_HANDLE *handle_list, VMUINT *num);

/*****************************************************************************
* FUNCTION
 *    vm_pmng_get_process_property
 * DESCRIPTION
 *  get process property
 * PARAMETERS
 *  handle : [IN] process handle
 *  property : [OUT] process property
 * RETURNS
 *  0 means success, < 0 means fail
*****************************************************************************/
VMINT vm_pmng_get_process_property(VM_P_HANDLE handle, vm_process_property *property);

/*****************************************************************************
 * FUNCTION
 *  vm_pmng_set_fg
 * DESCRIPTION
 *  bring an application from bg to fg
 * PARAMETERS
 *  fileName        [IN]         Application file name encoding with USC2 format.
 * RETURNS
 *  sucess app handle, <0 means fail
 *****************************************************************************/
VM_P_HANDLE vm_pmng_set_fg(VMWSTR fileName);

/*****************************************************************************
 * FUNCTION
 *  vm_get_full_path_by_short_name
 * DESCRIPTION
 *  get full path from short name. it is get the vxp or vpp or vsp file in current running app folder.
 *  e.g.FBv2, maybe get FBv2.vsp in the same folder, or rom which named FBv2
 * PARAMETERS
 *  short_name        [IN]         Short name encoding with USC2 format.
 *  full_path             [OUT]      full path
 * RETURNS
 *  sucess 0;  <0 means fail
 *****************************************************************************/

VMINT vm_get_full_path_by_short_name(VMWSTR short_name, VMWSTR full_path);

/*****************************************************************************
 * FUNCTION
 *  vm_pmng_set_pen_move_not_exit
 * DESCRIPTION
 * when call this api in wearable app, will not exit app when pen move event release.
 * this api should call in when receive VM_MSG_ACTIVE,because only when app forground, this setting work.
 * PARAMETERS
 * none
 * RETURNS
 *  none
 *****************************************************************************/
void vm_pmng_set_pen_move_not_exit();
/*****************************************************************************
 * FUNCTION
 *  vm_pmng_set_pen_move_exit
 * DESCRIPTION
 * when call this api in wearable app, will hide or inactive app when pen move event release.
 * PARAMETERS
 * none
 * RETURNS
 *  none
 *****************************************************************************/
void vm_pmng_set_pen_move_exit();
/* DOM-NOT_FOR_SDK-BEGIN */
#define vm_get_mre_modules vm_get_modules
#define vm_get_mre_version vm_get_version
/* DOM-NOT_FOR_SDK-END */
#ifdef __cplusplus
}
#endif 
#endif /* _VM_PRO_MNG_SDK_ */
