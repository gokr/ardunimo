#ifndef _VM_DCL_PWM_H_
#define _VM_DCL_PWM_H_


/******************************************************************
* DESCRIPTION
*   This enum defines the device for PWM module,used in vm_dcl_open as a parameter.
*   To control PWM, you should use DCL(Driver Common Layer) APIs. 
* EXAMPLE
* <code>
*   #include "vm_dcl.h"
*   VM_DCL_HANDLE pwm_handle;					 // Declare a VM_DCL_HANDLE variable. 
*   pwm_handle = vm_dcl_open(VM_DCL_KPLED_PWM,0);      // Call vm_dcl_open to get a handle. 
* </code>
*******************************************************************/
typedef enum
{
	VM_DCL_PWM_START = VM_DCL_PWM_GROUP_START, /*PWM device start*/
	VM_DCL_KPLED_PWM,                      /*This device is used to control keypad LED PWM.*/

	
	VM_DCL_HW_PWM_GROUP_START = (VM_DCL_PWM_GROUP_START+0x20),
	VM_DCL_PWM1,  /* control pwm1 */
	VM_DCL_PWM_RESERVED2,  /* Reserved, do not use. */
	VM_DCL_PWM_RESERVED3, /* Reserved, do not use. */
	VM_DCL_PWM4, /* control pwm4 */
}VM_DCL_PWM_DEV_T;

/******************************************************************
* DESCRIPTION
*   This enum  define the control command for PWM  module,used in vm_dcl_control as parameter.
*   With different commands, user could control the different function of the PWM.
*   To control PWM, you should use DCL(Driver Common Layer) APIs. 
* EXAMPLE
* <code>
*   #include "vm_dcl.h"
*   VM_DCL_HANDLE pwm_handle;			 // Declare a VM_DCL_HANDLE variable. 
*   VM_PWM_LEVEL_T pwm_level_var;
*   pwm_handle = vm_dcl_open(VM_DCL_KPLED_PWM,0); // First, we call vm_dcl_open to get a handle. the second parameter always fill 0.
*   pwm_level_var.pwm_level = 2;
*   vm_dcl_control(pwm_handle,VM_PWM_CMD_SET_LEVEL,(void *)(&pwm_level_var)); //  we call vm_dcl_control to set the kpled full brightness. 
*   vm_dcl_close(pwm_handle); // Finally, we call vm_dcl_close 
* </code>
*******************************************************************/

typedef enum
{
	VM_PWM_CMD_START = 0xD06, /*For hw pwm control only*/
	VM_PWM_CMD_STOP = 0xD07,  /*For hw pwm control only*/
	VM_PWM_CMD_SET_LEVEL = 0xD0C,  /* for VM_DCL_KPLED_PWM only,nowadays, The keypad led only support 3 levels:0,1,2.  0 means stop pwm, 1 means 50% of brightness, 2 means 100% of brightness.*/
	VM_PWM_CMD_CONFIG = 0xD14,  /*For hw pwm control only*/
	VM_PWM_CMD_SET_CLK = 0xD1B,  /*For hw pwm control only*/
	VM_PWM_CMD_SET_COUNTER_AND_THRESHOLD = 0xD1C,/*For hw pwm control only*/

}VM_DCL_PWM_CTRL_CMD_T;


/******************************************************************
* DESCRIPTION
*   This struct is for VM_PWM_CMD_SET_LEVEL control command,used in vm_dcl_control as parameter.
*   With this command, you can set the brightness of the keypad led PWM.
*   You can find the sample code in the description of VM_DCL_PWM_CTRL_CMD_T.
*   All commands have similar usage.
*******************************************************************/

typedef struct
{
   VMUINT8  pwm_level; /*nowadays, The keypad led only support 3 levels:0,1,2.  0 means stop pwm, 1 means 50% of brightness, 2 means 100% of brightness.*/
}VM_PWM_LEVEL_T;

typedef struct
{
	VMUINT32 freq; // the PWM channel output frequency.
	VMUINT8 duty;  // the duty cycle of the high level under the periodical output.
}VM_PWM_CONFIG_T;

typedef struct
{
	VMUINT8 source_clk; // 0 means 13Mhz, 1means 32K
	VMUINT8 source_clk_div;  // 0 means 0 div, 1 means 2 div, 2 means 4 div, 3 means 8 div.
}VM_PWM_SET_CLOCK_T;

typedef struct
{
	VMUINT16 counter; // 0 means 13Mhz, 1means 32K
	VMUINT16 threshold;  // 0 means 0 div, 1 means 2 div, 2 means 4 div, 3 means 8 div.
}VM_PWM_SET_COUNTER_THRESHOLD_T;


#endif

