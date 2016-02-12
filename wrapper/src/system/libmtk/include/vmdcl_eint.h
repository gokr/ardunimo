#ifndef _VM_DCL_EINT_H_
#define _VM_DCL_EINT_H_


/******************************************************************
* DESCRIPTION
*   This enum define the device for eint module, used in vm_dcl_open as a parameter.
*   To control EINTs, you should use DCL(Driver Common Layer) APIs. 
* EXAMPLE
* <code>
*   #include "vm_dcl.h"
*   eint_handle = vm_dcl_open(VM_DCL_EINT,19);			//We call vm_dcl_open to get a handle. 19 means eint19
* </code>
*******************************************************************/
typedef enum
{
	VM_DCL_EINT_DEV_GROUP_START = VM_DCL_EINT_GROUP_START,           /* EINT dev group start. */
	VM_DCL_EINT                                     /* DCL EINT device. */
}VM_DCL_EINT_DEV_T;

/******************************************************************
* DESCRIPTION
*   This enum define the event for eint module.
*   When user recieve this event, it means the specified EINT has triggerd an interrupt.
*******************************************************************/
typedef enum
{
	VM_EVENT_EINT_TRIGGER = VM_EINT_EVENTS_START      /* EINT trigger event. */
}VM_DCL_EINT_EVENT_T;



/******************************************************************
* DESCRIPTION
*   This enum define the eint control command, used in vm_dcl_open as a parameter.
*   With different commands, user could control the different function of the EINTs.
*   To control EINTs, you should use DCL(Driver Common Layer) APIs. 
* EXAMPLE
* <code>
*   #include "vm_dcl.h"
*   VM_DCL_HANDLE eint_handle;					 // Declare a VM_DCL_HANDLE variable. 
*   vm_eint_ctrl_config_t eint_config;   //Declare a vm_eint_ctrl_config_t variable.
*   vm_eint_ctrl_set_sensitivity_t sens_data;  //Declare a vm_eint_ctrl_set_sensitivity_t variable.
*   vm_eint_ctrl_set_hw_deounce_t deboun_time; //Declare a vm_eint_ctrl_set_hw_deounce_t variable.
*   eint_handle = vm_dcl_open(VM_DCL_EINT,19);			// First, we call vm_dcl_open to get a handle. 19 means eint19
*   vm_dcl_control(eint_handle,VM_EINT_CMD_MASK,NULL);	// Usually, before we config eint, we mask it firstly. 
*   vm_dcl_registercallback(eint_handle,EVENT_EINT_TRIGGER,(VM_DCL_CALLBACK)eint_callback,(void*)NULL ); // register callback function,Note: the last paramter fill NULL 
*   sens_data.sensitivity = 1;	  // 1 means level sensitive, 0 means edge sensitive. 
*   vm_dcl_control(eint_handle,VM_EINT_CMD_SET_SENSITIVITY,(void *)&sens_data);  // set eint sensitivity 
*   deboun_time.debounce_time = 10;  //Debounce time 10ms 
*   vm_dcl_control(eint_handle,VM_EINT_CMD_SET_HW_DEBOUNCE,(void *)&deboun_time); // Set debounce time 
*   eint_config.act_polarity = 0;	// 1 means positive active, 0 means negative active. 
*   eint_config.debounce_en = 1;	// 1 means enable hw debounce, 0 means disable. 
*   eint_config.auto_unmask = 1;	// 1 means unmask after callback, 0 means not unmask, and user should unmask it themselves. 
*   vm_dcl_control(eint_handle,VM_EINT_CMD_CONFIG,(void *)&eint_config);   // Please call this api finally, because we will unmask eint in this command. 
*   vm_dcl_control(eint_handle,VM_EINT_CMD_UNMASK,NULL);  // call this function to unmask this eint. 
*   vm_dcl_close(eint_handle); // Finally, we call vm_dcl_close 
* </code>
*******************************************************************/
typedef enum
{
	VM_EINT_CMD_GROUP_START = 0x1E00,           /* EINT cmmand group start. */
	VM_EINT_CMD_CONFIG,                         /* EINT config command. */
	VM_EINT_CMD_SET_HW_DEBOUNCE,                /* EINT set hardware debounce command. */
	VM_EINT_CMD_SET_POLARITY,                   /* EINT set polartiy command. */
	VM_EINT_CMD_SET_SENSITIVITY,                /* EINT set sensitivity command. */
	VM_EINT_CMD_MASK,                           /* EINT mask command. */
	VM_EINT_CMD_UNMASK,                         /* EINT unmask command. */	
	VM_EINT_CMD_RESERVED,                       /* Reserved, do not use it */
	VM_EINT_CMD_SET_AUTO_CHANGE_POLARTIY        /* Eint set auto change polarity command*/
}VM_DCL_EINT_CMD_T;

 
/******************************************************************
* DESCRIPTION
*   This struct is for VM_EINT_CMD_CONFIG command,used in vm_dcl_control as parameter.
*   With this command, you can config the attribute of a specified EINT.
*   You can find the sample code in the description of VM_DCL_EINT_CMD_T.
*   All commands have similar usage.
*******************************************************************/
typedef struct
{
	VMUINT8	 debounce_en;                 /* The value is 1 or 0. 1 means enable hw debounce, 0 means disable.  */
	VMUINT8	 act_polarity;                /* The value is 1 0r 0. 1 means positive active, 0 means negative active. */
	VMUINT8	 auto_unmask;                 /* The value is 1 or 0. 1 means unmask after callback, 0 means not unmask. user unmask it themselves. */
} vm_eint_ctrl_config_t;

/******************************************************************
* DESCRIPTION
*   This struct is for VM_EINT_CMD_SET_HW_DEBOUNCE command,used in vm_dcl_control as parameter.
*   With this command, you can set the hw debounce time of a specified EINT.
*   You can find the sample code in the description of VM_DCL_EINT_CMD_T.
*   All commands have similar usage.
*******************************************************************/
typedef struct
{
 	VMUINT32	  debounce_time;          /* HW debounce time. the unit is 1ms. */
}vm_eint_ctrl_set_hw_deounce_t;

/******************************************************************
* DESCRIPTION
*   This struct is for VM_EINT_CMD_SET_POLARITY command,used in vm_dcl_control as parameter.
*   With this command, you can set the polarity of a specified EINT.
*   You can find the sample code in the description of VM_DCL_EINT_CMD_T.
*   All commands have similar usage.
*******************************************************************/
typedef struct
{
 	VMUINT8 ACT_Polarity;                 /* The value is 1 0r 0. 1 means positive active, 0 means negative active. */
}vm_eint_ctrl_set_polarity_t;

/******************************************************************
* DESCRIPTION
*   This struct is for VM_EINT_CMD_SET_SENSITIVITY command,used in vm_dcl_control as parameter.
*   With this command, you can set the sensitivity of a specified EINT.
*   You can find the sample code in the description of VM_DCL_EINT_CMD_T.
*   All commands have similar usage.
*******************************************************************/
typedef struct
{
 	VMUINT8 sensitivity;                  /* The value is 1 or 0. 1 means level  sensitive,0 means edge sensitive. */
}vm_eint_ctrl_set_sensitivity_t;
 
typedef struct
{
	 VMUINT8 autoChangePol; 		/* The value is 1 or 0. 1 means enable auto change polarity, 0 means disable. note that the default value is 0 */
}vm_eint_ctrl_set_auto_change_pol_t;


#endif
