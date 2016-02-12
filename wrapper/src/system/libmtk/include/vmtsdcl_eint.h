#ifndef __VM_TS_DCL_EINT_H__
#define __VM_TS_DCL_EINT_H__ 


/******************************************************************
* DESCRIPTION
*   This enum defines the device for EINT module,used in vm_ts_dcl_open as a parameter.
*   To control GPIOs, you should use DCL(Driver Common Layer) APIs. 
* EXAMPLE
* <code>
*   #include "vmtsdcl.h"
*   VM_TS_DCL_HANDLE eint_handle;					 // Declare a VM_TS_DCL_HANDLE variable. 
*   eint_handle = vm_ts_dcl_open(VM_TS_DCL_EINT,12);      // Call vm_ts_dcl_open to get a handle. 12 means eint's number is 12.
* </code>
*******************************************************************/
typedef enum
{
	VM_TS_EINT_GROUP_START = VM_TS_DCL_EINT_GROUP_START,
	VM_TS_DCL_EINT          /*This is for control normal eint function. */
}VM_TS_DCL_EINT_DEV;

/******************************************************************
* DESCRIPTION
*   This enum  define the control command for EINT  module,used in vm_ts_dcl_control as parameter.
*   With different commands, user could control the different function of the EINT.
*   To control EINT, you should use DCL(Driver Common Layer) APIs. 
* EXAMPLE
* <code>
*   #include "vmtsdcl.h"
*   VM_TS_DCL_HANDLE eint_handle;					 // Declare a VM_TS_DCL_HANDLE variable. 
*   VM_TS_DCL_EINT_CTRL_CONFIG_T eint_config;   //Declare a VM_TS_DCL_EINT_CTRL_CONFIG_T variable.
*   RESERVE_VM_TS_DCL_EINT_CMD_SET_HW_DEBOUNCE deboun_time; //not support,Declare a VM_TS_DCL_EINT_CTRL_SET_HW_DEBOUNCE_T variable.
*   eint_handle = vm_ts_dcl_open(VM_TS_DCL_EINT,19);			// First, we call vm_ts_dcl_open to get a handle. 19 means eint19
*   vm_ts_dcl_control(eint_handle,VM_TS_EINT_CMD_MASK,NULL);	// Usually, before we config eint, we mask it firstly. 
*   vm_ts_dcl_register_callback(eint_handle,VM_TS_DCL_REGISTER_CALLBACK_LEVEL2,(void)eint_callback); // register callback function,Note: eint calback is given by user
*   deboun_time.debounce_time = 10;  //Debounce time 10ms 
*   vm_ts_dcl_control(eint_handle,VM_TS_EINT_CMD_SET_HW_DEBOUNCE,(void *)&deboun_time); // Set debounce time 
*   eint_config.act_polarity = 0;	// 1 means positive active, 0 means negative active. 
*   eint_config.debounce_en = 1;	// 1 means enable hw debounce, 0 means disable. 
*   eint_config.act_sens = 1;	// 1 means level, 0 means edge.
*   vm_ts_dcl_control(eint_handle,VM_TS_EINT_CMD_CONFIG,(void *)&eint_config);   // Please call this api finally, because we will unmask eint in this command. 
*   vm_ts_dcl_control(eint_handle,VM_TS_EINT_CMD_UNMASK,NULL);  // call this function to unmask this eint. 
*   vm_ts_dcl_close(eint_handle); // Finally, if you are sure you will not use eint, you call vm_dcl_close ,otherwise, not call this api.
* </code>
*******************************************************************/
typedef enum{
	VM_TS_DCL_EINT_CMD_CONFIG,          /* EINT config command. */
	RESERVE_VM_TS_DCL_EINT_CMD_SET_HW_DEBOUNCE, /* not support,EINT set hardware debounce command. */
	VM_TS_DCL_EINT_CMD_MASK,            /* EINT mask command. */
	VM_TS_DCL_EINT_CMD_UNMASK,          /* EINT unmask command. */	
	VM_TS_DCL_EINT_CMD_ACK,             /* EINT ack command, after callback, user should act the eint*/
}VM_TS_DCL_EINT_CTRL_CMD;


 /******************************************************************
 * DESCRIPTION
 *	 This struct is for VM_TS_DCL_EINT_CMD_CONFIG control command,used in vm_ts_dcl_control as parameter.
 *	 You can find the sample code in the description of VM_TS_DCL_EINT_CTRL_CMD.
 *******************************************************************/
typedef struct
{
	VMUINT8	 debounce_en; /* The value is 1 or 0. 1 means enable hw debounce, 0 means disable */
	VMUINT8	 act_sens;   /* The value is 1 0r 0. 1 means level trigger, 0 means edge trigger.*/
	VMUINT8	 act_polarity; /* The value is 1 0r 0. 1 means positive active, 0 means negative active.*/
}VM_TS_DCL_EINT_CTRL_CONFIG_T;
 

#endif

