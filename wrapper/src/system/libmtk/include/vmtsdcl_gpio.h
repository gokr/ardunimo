#ifndef __VM_TS_DCL_GPIO_H__
#define __VM_TS_DCL_GPIO_H__



/******************************************************************
* DESCRIPTION
*   This enum defines the device for gpio module,used in vm_ts_dcl_open as a 
parameter.
*   To control GPIOs, you should use DCL(Driver Common Layer) APIs. 
* EXAMPLE
* <code>
*   #include "vmtsdcl.h"
*   VM_TS_DCL_HANDLE gpio_handle;					 // Declare a VM_TS_DCL_HANDLE variable. 
*   gpio_handle = vm_ts_dcl_open(VM_TS_DCL_GPIO,55);      // Call vm_ts_dcl_open to get a handle. 55 means gpio55
* </code>
*******************************************************************/

typedef enum
{
	VM_TS_GPIO_GROUP_START = VM_TS_DCL_GPIO_GROUP_START,
	VM_TS_DCL_GPIO,              /*This is for control normal gpio function. */
}VM_TS_DCL_GPIO_DEV;



/******************************************************************
* DESCRIPTION
*   This enum  define the control command for GPIO  module,used in vm_ts_dcl_control as parameter.
*   With different commands, user could control the different function of the GPIOs.
*   To control GPIOs, you should use DCL(Driver Common Layer) APIs. 
* EXAMPLE
* <code>
*   #include "vmtsdcl.h"
*   VM_TS_DCL_HANDLE gpio_handle;			 // Declare a VM_TS_DCL_HANDLE variable. 
*   VM_TS_DCL_GPIO_CTRL_READ_T gpio_input_data;		 //Declare a variable for read IO. 
*   VM_TS_DCL_GPIO_CTRL_SET_PUPD_R0_R1_T pupd_r0r1_data; //Declare a VM_TS_DCL_GPIO_CTRL_SET_PUPD_R0_R1_T variable.
*   gpio_handle = vm_ts_dcl_open(VM_TS_DCL_GPIO,55); // First, we call vm_ts_dcl_open to get a handle. 55 means gpio55
*   vm_ts_dcl_control(gpio_handle,VM_TS_DCL_GPIO_CMD_SET_MODE_3,NULL); //  we call vm_ts_dcl_control to set gpio55 as mode3. 
*   vm_ts_dcl_control(gpio_handle,VM_TS_DCL_GPIO_CMD_READ,(void *)&gpio_input_data); // We call vm_ts_dcl_control to read gpio55 . 
*   vm_ts_dcl_control(gpio_handle,VM_TS_DCL_GPIO_CMD_WRITE_HIGH,0); // we call vm_ts_dcl_control to write gpio55 . 
*   pupd_r0r1_data.fgSetPupd = 1; // More details, please refer to the GPIO datasheet. 
*   pupd_r0r1_data.fgSetR0 = 1; // More details, please refer to the GPIO datasheet. 
*   pupd_r0r1_data.fgSetR1 = 0; // More details, please refer to the GPIO datasheet. 
*   vm_ts_dcl_control(gpio_handle,VM_TS_DCL_GPIO_CMD_SET_PUPD_R0_R1,(void *)&pupd_r0r1_data); //we call vm_ts_dcl_control to set pupd of gpio55 . 
*   vm_ts_dcl_close(gpio_handle); // Finally, we call vm_ts_dcl_close 
* </code>
*******************************************************************/
typedef enum
{
   VM_TS_DCL_GPIO_CMD_READ, 			 	/*read data from GPIO Pin*/
   VM_TS_DCL_GPIO_CMD_WRITE_LOW,   		   /*write low to GPIO pin*/
   VM_TS_DCL_GPIO_CMD_WRITE_HIGH,			/*write high to GPIO Pin*/
   VM_TS_DCL_GPIO_CMD_SET_MODE_0, 		    /*set GPIO mode as mode 0*/
   VM_TS_DCL_GPIO_CMD_SET_MODE_1,			/*set GPIO mode as mode 1*/
   VM_TS_DCL_GPIO_CMD_SET_MODE_2,			/*set GPIO mode as mode 2*/
   VM_TS_DCL_GPIO_CMD_SET_MODE_3,			/*set GPIO mode as mode 3*/
   VM_TS_DCL_GPIO_CMD_SET_MODE_4,			/*set GPIO mode as mode 4 ,only for chip support 4-bit mode*/
   VM_TS_DCL_GPIO_CMD_SET_MODE_5,			/*set GPIO mode as mode 5*,only for chip support 4-bit mode*/
   VM_TS_DCL_GPIO_CMD_SET_MODE_6,			/*set GPIO mode as mode 6*,only for chip support 4-bit mode*/
   VM_TS_DCL_GPIO_CMD_SET_MODE_7,		    /*set GPIO mode as mode 7*,only for chip support 4-bit mode*/
   VM_TS_DCL_GPIO_CMD_SET_MODE_8,		    /*set GPIO mode as mode 8*,only for chip support 4-bit mode*/
   VM_TS_DCL_GPIO_CMD_SET_MODE_9,			/*set GPIO mode as mode 9*,only for chip support 4-bit mode*/
   VM_TS_DCL_GPIO_CMD_SET_MODE_10,			/*set GPIO mode as mode 10*,only for chip support 4-bit mode*/
   VM_TS_DCL_GPIO_CMD_SET_DIR_OUT, 		    /*set GPIO direction as output*/
   VM_TS_DCL_GPIO_CMD_SET_DIR_IN,	 		/*set GPIO direction as input*/
   VM_TS_DCL_GPIO_CMD_ENABLE_PULL, 		    /*enable GPIO pull-up/pull-down seting */
   VM_TS_DCL_GPIO_CMD_DISABLE_PULL,		   /*disable GPIO pull-up/pull-down seting*/
   VM_TS_DCL_GPIO_CMD_SET_PULL_HIGH,       /*set GPIO as pull-up*/
   VM_TS_DCL_GPIO_CMD_SET_PULL_LOW,        /*set GPIO as pull-down*/
}VM_TS_DCL_GPIO_CTRL_CMD_T;

/******************************************************************
* DESCRIPTION
*   This struct is for VM_TS_DCL_GPIO_CMD_READ control command,used in vm_ts_dcl_control as parameter.
*   You can find the sample code in the description of VM_TS_DCL_GPIO_CTRL_CMD_T.
*******************************************************************/
typedef struct
{
   VMUINT8   u1IOData; /* The returned value. 0 means the GPIO pin input level is low. 1 means level is high*/
} VM_TS_DCL_GPIO_CTRL_READ_T;





#endif 


