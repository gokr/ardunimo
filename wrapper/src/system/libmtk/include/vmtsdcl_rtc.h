#ifndef __VM_TS_DCL_RTC_H__
#define __VM_TS_DCL_RTC_H__ 


/******************************************************************
* DESCRIPTION
*   This enum defines the device for RTC module,used in vm_ts_dcl_open as a parameter.
*   To control GPIOs, you should use DCL(Driver Common Layer) APIs. 
* EXAMPLE
* <code>
*   #include "vmtsdcl.h"
*   VM_TS_DCL_HANDLE rtc_handle;					 // Declare a VM_TS_DCL_HANDLE variable. 
*   rtc_handle = vm_ts_dcl_open(VM_TS_DCL_RTC,0);      // Call vm_ts_dcl_open to get a handle.
* </code>
*******************************************************************/
typedef enum
{
	VM_TS_RTC_GROUP_START = VM_TS_DCL_RTC_GROUP_START,
	VM_TS_DCL_RTC          /*This is for control normal rtc function. */
}VM_TS_DCL_RTC_DEV;

/******************************************************************
* DESCRIPTION
*   This enum  define the control command for RTC  module,used in vm_ts_dcl_control as parameter.
*   With different commands, user could control the different function of the RTC.
*   To control RTC, you should use DCL(Driver Common Layer) APIs. 
* EXAMPLE
* <code>
*   #include "vmtsdcl.h"
*   VM_TS_DCL_HANDLE rtc_handle;                                    // Declare a VM_TS_DCL_HANDLE variable. 
*   VM_TS_DCL_RTC_CTRL_GET_TIME_T getTime;                              // Declare a VM_TS_DCL_RTC_CTRL_GET_TIME_T variable.
*   VM_TS_DCL_RTC_CTRL_SET_TIME_UPDATE_PERIOD_T setTimeUpdatePeriod;    // Declare a VM_TS_DCL_RTC_CTRL_SET_TIME_UPDATE_PERIOD_T variable.
*   rtc_handle = vm_ts_dcl_open(VM_TS_DCL_RTC,0);			        // First, we call vm_ts_dcl_open to get a handle.
*   vm_ts_dcl_register_callback(rtc_handle,VM_TS_DCL_REGISTER_CALLBACK_LEVEL2,(void)rtc_callback); // register callback function,Note: rtc calback is given by user
*   setTimeUpdatePeriod.time_update_period = VM_TC_EN_ChkS;         // Wish to get time update notify per second.
*   vm_ts_dcl_control(rtc_handle, VM_TS_RTC_CMD_SET_TIME_UPDATE_PERIOD, (void *)&setTimeUpdatePeriod); // Set debounce time 
*   vm_ts_dcl_control(rtc_handle, VM_TS_RTC_CMD_GET_TIME,(void *)&getTime);    // Get current RTC time;
*   vm_ts_dcl_close(rtc_handle); // Finally, if you are sure you will not use rtc, you call vm_dcl_close ,otherwise, not call this api.
* </code>
*******************************************************************/
typedef enum {
    VM_TS_RTC_CMD_GET_TIME, /* To Get Time*/
    VM_TS_RTC_CMD_SET_TIME_UPDATE_PERIOD, /* To Set Time Update Period*/
}VM_TS_DCL_RTC_CTRL_CMD_T;

 /******************************************************************
 * DESCRIPTION
 *	 This enum define the different time update period choices.
 *	 You can find the sample code in the description of VM_TS_DCL_RTC_CTRL_CMD_T.
 *******************************************************************/
typedef enum{
    VM_TC_EN_None,         /* Time Counter Enable None */
    VM_TC_EN_ChkS,         /* Time Counter Enable Check Sec */
    VM_TC_EN_ChkM,         /* Time Counter Enable Check Min & Sec */
    VM_TC_EN_ChkH,         /* Time Counter Enable Check Hour, Min & Sec */
    VM_TC_EN_ChkD,         /* Time Counter Enable Check DOM, Hour, Min & Sec */
    VM_TC_EN_ChkW,         /* Time Counter Enable Check DOW, Hour, Min & Sec */
    VM_TC_EN_ChkMon,       /* Time Counter Enable Check Month, DOM, Hour, Min & Sec */
    VM_TC_EN_ChkY,         /* Time Counter Enable Check Year, Month, DOM, Hour, Min & Sec */
    VM_TC_EN_NoChange,     /* Time Counter Enable No Change */
}VM_TS_DCL_RTC_TIME_UPDATE_PERIOD;
 
 /******************************************************************
 * DESCRIPTION
 *	 This struct is the member VM_TS_DCL_RTC_CTRL_GET_TIME_T.
 *	 You can find the sample code in the description of VM_TS_DCL_RTC_CTRL_CMD_T.
 *******************************************************************/
typedef struct 
{
	VMUINT8     rtc_sec;    /* Seconds after the minute   - [0,59]  */
	VMUINT8     rtc_min;    /* Minutes after the hour     - [0,59]  */
	VMUINT8     rtc_hour;   /* Hours after the midnight   - [0,23]  */
	VMUINT8     rtc_day;    /* Day of the month           - [1,31]  */
	VMUINT8     rtc_mon;    /* Months 		              - [1,12]  */
	VMUINT8     rtc_wday;   /* Days in a week 		      - [1,7]   */
	VMUINT8     rtc_year;   /* Years                      - [0,127] */
}VM_TS_DCL_RTC_TIME_T;
 
 /******************************************************************
 * DESCRIPTION
 *	 This struct is for VM_TS_RTC_CMD_GET_TIME control command,used in vm_ts_dcl_control as parameter.
 *	 You can find the sample code in the description of VM_TS_DCL_RTC_CTRL_CMD_T.
 *******************************************************************/
typedef struct
{
    VM_TS_DCL_RTC_TIME_T time;
}VM_TS_DCL_RTC_CTRL_GET_TIME_T;

 /******************************************************************
 * DESCRIPTION
 *	 This struct is for VM_TS_RTC_CMD_SET_TIME_UPDATE_PERIOD control command,used in vm_ts_dcl_control as parameter.
 *	 You can find the sample code in the description of VM_TS_DCL_RTC_CTRL_CMD_T.
 *******************************************************************/
typedef struct
{
    VM_TS_DCL_RTC_TIME_UPDATE_PERIOD time_update_period;
}VM_TS_DCL_RTC_CTRL_SET_TIME_UPDATE_PERIOD_T;

#endif

