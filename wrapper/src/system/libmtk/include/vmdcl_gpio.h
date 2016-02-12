#ifndef __VM_DCL_GPIO_H_STRUCT__
#define __VM_DCL_GPIO_H_STRUCT__

/******************************************************************
* DESCRIPTION
*   This enum defines the device for gpio module,used in vm_dcl_open as a parameter.
*   To control GPIOs, you should use DCL(Driver Common Layer) APIs. 
* EXAMPLE
* <code>
*   #include "vm_dcl.h"
*   VM_DCL_HANDLE gpio_handle;					 // Declare a VM_DCL_HANDLE variable. 
*   gpio_handle = vm_dcl_open(VM_DCL_GPIO,55);      // Call vm_dcl_open to get a handle. 55 means gpio55
* </code>
*******************************************************************/
typedef enum
{
	VM_DCL_GPIO_START = VM_DCL_GPIO_GROUP_START, /*GPIO device start*/
	VM_DCL_GPIO,/*This device is used to control GPIO normal function.*/
	VM_DCL_GPIO_CLK /*This device is used to control GPIO clk function.*/
}VM_DCL_GPIO_DEV_T;


/******************************************************************
* DESCRIPTION
*   This enum is for GPIO_CMD_SET_CLK_OUT command,used in vm_dcl_control as parameter.
*   Please refer the introduction of vm_gpio_ctrl_set_clk_out_t for more details.
*******************************************************************/
typedef enum {
   vm_mode_default = 0,/*The default mode is 0. User should refer to the GPIO datasheet to see the specified value*/
   vm_mode_f32k_ck = 0x82, /*Use this enum value to set the 32K clock out in a faster way*/
   vm_mode_max_num /*This value defines the max  number of mode, do not exceed this value*/
 } vm_gpio_clk_mode;  


/******************************************************************
* DESCRIPTION
*   This enum is for GPIO_CMD_SET_CLK_DIV,used in vm_dcl_control as parameter.
*   Please refer the introduction of vm_gpio_ctrl_set_clk_div_t for more details.
*******************************************************************/
typedef enum {
   vm_div_max_num=16 /*This value defines the max number of div, do not exceed this value*/ 
} vm_gpio_clk_div;	


/******************************************************************
* DESCRIPTION
*   This enum  define the control command for GPIO  module,used in vm_dcl_control as parameter.
*   With different commands, user could control the different function of the GPIOs.
*   To control GPIOs, you should use DCL(Driver Common Layer) APIs. 
* EXAMPLE
* <code>
*   #include "vm_dcl.h"
*   VM_DCL_HANDLE gpio_handle;			 // Declare a VM_DCL_HANDLE variable. 
*   vm_gpio_ctrl_read_t gpio_input_data;		 //Declare a variable for read IO. 
*   vm_gpio_ctrl_set_pupd_r0_r1_t pupd_r0r1_data; //Declare a vm_gpio_ctrl_set_pupd_r0_r1_t variable.
*   gpio_handle = vm_dcl_open(VM_DCL_GPIO,55); // First, we call vm_dcl_open to get a handle. 55 means gpio55
*   vm_dcl_control(gpio_handle,VM_GPIO_CMD_SET_MODE_3,NULL); //  we call vm_dcl_control to set gpio55 as mode3. 
*   vm_dcl_control(gpio_handle,VM_GPIO_CMD_READ,(void *)&gpio_input_data); // We call vm_dcl_control to read gpio55 . 
*   vm_dcl_control(gpio_handle,VM_GPIO_CMD_WRITE_HIGH,0); // we call vm_dcl_control to write gpio55 . 
*   pupd_r0r1_data.fgSetPupd = 1; // More details, please refer to the GPIO datasheet. 
*   pupd_r0r1_data.fgSetR0 = 1; // More details, please refer to the GPIO datasheet. 
*   pupd_r0r1_data.fgSetR1 = 0; // More details, please refer to the GPIO datasheet. 
*   vm_dcl_control(gpio_handle,VM_GPIO_CMD_SET_PUPD_R0_R1,(void *)&pupd_r0r1_data); //we call vm_dcl_control to set pupd of gpio55 . 
*   vm_dcl_close(gpio_handle); // Finally, we call vm_dcl_close 
* </code>
*******************************************************************/
typedef enum
{
   VM_GPIO_CMD_READ = 1, 			 /*Read data from GPIO Pin*/
   VM_GPIO_CMD_WRITE_LOW,   		 /*Write low to GPIO pin,the GPIO pin will output low*/
   VM_GPIO_CMD_WRITE_HIGH,			 /*Write high to GPIO Pin,the GPIO pin will output high*/
   VM_GPIO_CMD_SET_MODE_0, 		     /*Set GPIO mode as mode 0,user should refer to the GPIO datasheet to get the real meaning of MODE0*/
   VM_GPIO_CMD_SET_MODE_1,			 /*Set GPIO mode as mode 1,user should refer to the GPIO datasheet to get the real meaning of MODE1*/
   VM_GPIO_CMD_SET_MODE_2,			 /*Set GPIO mode as mode 2,user should refer to the GPIO datasheet to get the real meaning of MODE2*/
   VM_GPIO_CMD_SET_MODE_3,			 /*Set GPIO mode as mode 3,user should refer to the GPIO datasheet to get the real meaning of MODE3*/
   VM_GPIO_CMD_SET_MODE_4,			 /*Set GPIO mode as mode 4 ,only for chip support 4-bit mode*/
   VM_GPIO_CMD_SET_MODE_5,			 /*Set GPIO mode as mode 5,only for chip support 4-bit mode*/
   VM_GPIO_CMD_SET_MODE_6,			 /*Set GPIO mode as mode 6,only for chip support 4-bit mode*/
   VM_GPIO_CMD_SET_MODE_7,			 /*Set GPIO mode as mode 7,only for chip support 4-bit mode*/
   VM_GPIO_CMD_SET_MODE_8,			 /*Set GPIO mode as mode 8,only for chip support 4-bit mode*/
   VM_GPIO_CMD_SET_DIR_OUT, 		 /*Set GPIO direction as output*/
   VM_GPIO_CMD_SET_DIR_IN,	 		 /*Set GPIO direction as input*/
   VM_GPIO_CMD_RETURN_MODE, 		 /*Get current GPIO mode*/
   VM_GPIO_CMD_RETURN_DIR,  		 /*Get current GPIO direction*/
   VM_GPIO_CMD_RETURN_OUT,  		 /*Get current GPIO output level,0 means low level and 1 means high level*/
   VM_GPIO_CMD_ENABLE_PULL, 		 /*Enable GPIO pull-up/pull-down  */
   VM_GPIO_CMD_DISABLE_PULL,		 /*Disable GPIO pull-up/pull-down */
   VM_GPIO_CMD_SET_PULL_HIGH,        /*Set GPIO as pull-up*/
   VM_GPIO_CMD_SET_PULL_LOW,         /*Set GPIO as pull-down*/
   VM_GPIO_CMD_SET_DINV,  			 /*Enable or disable GPIO data inversion*/
   VM_GPIO_CMD_RESERVED0,  	         /*Reserved commond, don't use this command*/
   VM_GPIO_CMD_SET_CLK_OUT,          /*Select the clock output source of GPIO*/
   VM_GPIO_CMD_SET_CLK_DIV,          /*Set the clock division of the clock source*/
   VM_GPIO_CMD_RESERVED1,	  	     /*Reserved command, don't use this command*/
   VM_GPIO_CMD_RESERVED2,    	     /*Reserved command, don't use this command*/
   VM_GPIO_CMD_RESERVED3,  		     /*Reserved command, don't use this command*/
   VM_GPIO_CMD_RESERVED4,  			 /*Reserved command, don't use this command*/
   VM_GPIO_CMD_RESERVED5, 			 /*Reserved command, don't use this command*/
   VM_GPIO_CMD_RESERVED6,            /*Reserved command, don't use this command*/
   VM_GPIO_CMD_RESERVED7, 			 /*Reserved command, don't use this command*/
   VM_GPIO_CMD_RESERVED8,            /*Reserved command, don't use this command*/
   VM_GPIO_CMD_RESERVED9,            /*Reserved command, don't use this command*/
   VM_GPIO_CMD_RESERVED10,           /*Reserved command, don't use this command*/
   VM_GPIO_CMD_RESERVED11,           /*Reserved command, don't use this command*/
   VM_GPIO_CMD_RESERVED12,           /*Reserved command, don't use this command*/
   VM_GPIO_CMD_RESERVED13, 		     /*Reserved command, don't use this command*/
   VM_GPIO_CMD_RESERVED14,		     /*Reserved command, don't use this command*/
   VM_GPIO_CMD_SET_PUPD_R0_R1,       /*set the special gpio's pull up/down register. User should refer to the GPIO datasheet*/
   VM_GPIO_CMD_SET_MODE_9,			 /*Set GPIO mode as mode 9,only for chip support 4-bit mode*/
   VM_GPIO_CMD_SET_MODE_10,			 /*Set GPIO mode as mode 10,only for chip support 4-bit mode*/
}VM_DCL_GPIO_CTRL_CMD_T;


/******************************************************************
* DESCRIPTION
*   This struct is for GPIO_CMD_READ control command,used in vm_dcl_control as parameter.
*   You can find the sample code in the description of VM_DCL_GPIO_CTRL_CMD_T.
*******************************************************************/
typedef struct
{
	#define VM_GPIO_IO_HIGH    1  
	#define VM_GPIO_IO_LOW     0   
    VMUINT8   u1IOData;           /* The returned value. 0 means the GPIO pin input level is low. 1 means level is high*/
} vm_gpio_ctrl_read_t;

/******************************************************************
* DESCRIPTION
*   This struct is for GPIO_CMD_RETURN_MODE control command,used in vm_dcl_control as parameter.
*   With this command, you can get the current mode of a specified GPIOs.
*   You can find the sample code in the description of VM_DCL_GPIO_CTRL_CMD_T.
*   All commands have similar usage.
*******************************************************************/
typedef struct
{
#define VM_GPIO_MODE_0    0
#define VM_GPIO_MODE_1    1
#define VM_GPIO_MODE_2    2
#define VM_GPIO_MODE_3    3
#define VM_GPIO_MODE_4    4
#define VM_GPIO_MODE_5    5
#define VM_GPIO_MODE_6    6
#define VM_GPIO_MODE_7    7
#define VM_GPIO_MODE_8    8 
   VMUINT8   u1RetMode;          /*The returned mode value:  0, 1, 2, 3,4,5,6,7,8. Please refer to more details about what the mode number represents from GPIO datasheet*/
} vm_gpio_ctrl_return_mode_t;


/******************************************************************
* DESCRIPTION
*   This struct is for GPIO_CMD_RETURN_DIR control command,used in vm_dcl_control as parameter.
*   With this command, you can get the direction of a specified GPIOs.
*   You can find the sample code in the description of VM_DCL_GPIO_CTRL_CMD_T.
*   All commands have similar usage.
*******************************************************************/
typedef struct
{
#define VM_GPIO_DIR_IN  0
#define VM_GPIO_DIR_OUT 1 
   VMUINT8   u1RetDirData;     /*The returned dir value: to return 0 means input, or 1 means output*/
}vm_gpio_ctrl_return_dir_t;

/******************************************************************
* DESCRIPTION
*   This struct is for GPIO_CMD_RETURN_OUT control command,used in vm_dcl_control as parameter.
*   With this command, you can get the output level of a specified GPIOs.
*   You can find the sample code in the description of VM_DCL_GPIO_CTRL_CMD_T.
*   All commands have similar usage.
*******************************************************************/
typedef struct
{
   VMUINT8   u1RetOutData;/*The returned value:   1 means gpio output level is high,0 means gpio output level is low */
}vm_gpio_ctrl_return_out_t;


/******************************************************************
* DESCRIPTION
*   This struct is for FOR GPIO_CMD_SET_DINV control command,used in vm_dcl_control as parameter.
*   With this command, you can set the data inversion funtion of a specified GPIOs.
*   You can find the sample code in the description of VM_DCL_GPIO_CTRL_CMD_T.
*   All commands have similar usage.
*******************************************************************/
typedef struct
{
   VMBOOL    fgSetDinv; /*This function only valid when the direction is input. 1 means enable this function. Get more information from datasheet*/
}vm_gpio_ctrl_set_dinv_t;

/******************************************************************
* DESCRIPTION
*   This struct is for GPIO_CMD_SET_PUPD_R0_R1  control command,used in vm_dcl_control as parameter.
*   With this command, you can set the pupd,r0,r1 funtion of a specified GPIOs.
*   You can find the sample code in the description of VM_DCL_GPIO_CTRL_CMD_T.
*   All commands have similar usage.
*******************************************************************/
typedef struct
{
   VMBOOL    fgSetPupd; /*This function set the pull up/down resisters of some special GPIO pins. Different fgSetPupd,fgSetR0,fgSetR1 means defferent pull up/down resisters.Please get more details in datasheet.*/
   VMBOOL    fgSetR0;  /*This function set the pull up/down resisters of some special GPIO pins. Different fgSetPupd,fgSetR0,fgSetR1 means defferent pull up/down resisters.Please get more details in datasheet.*/
   VMBOOL    fgSetR1; /*This function set the pull up/down resisters of some special GPIO pins. Different fgSetPupd,fgSetR0,fgSetR1 means defferent pull up/down resisters.Please get more details in datasheet.*/
}vm_gpio_ctrl_set_pupd_r0_r1_t;


/******************************************************************
* DESCRIPTION
*   This struct is for GPIO_CMD_SET_CLK_OUT control command,used in vm_dcl_control as parameter.
*   To control GPIOs, you should use DCL(Driver Common Layer) APIs. 
* EXAMPLE
*   <code>
*   #include "vm_dcl.h"
*   VM_DCL_HANDLE gpio_handle; // Declare a VM_DCL_HANDLE variable. 
*   vm_gpio_ctrl_set_clk_out_t clk_data; //Declare a vm_gpio_ctrl_set_clk_out_t variable.
*   gpio_handle = vm_dcl_open(VM_DCL_GPIO_CLK,55);// Step1, we call vm_dcl_open to get a handle. 55 means gpio55. Notice the dev parameter is VM_DCL_GPIO_CLK. 
*   clk_data.u2ClkNum = 2;// More details, please refer to the GPIO datasheet. 
*   clk_data.u2Mode = 4; //More details, please refer to the GPIO datasheet. 
*   vm_dcl_control(gpio_handle,VM_GPIO_CMD_SET_CLK_OUT,(void *)&clk_data); // Step2, we call vm_dcl_control to set pupd of gpio55 .
*   vm_dcl_close(gpio_handle); // Finally, we call vm_dcl_close 
*   </code>
*******************************************************************/
typedef struct
{
   VMUINT16  u2ClkNum; /*The clock register number in datasheet.*/
   vm_gpio_clk_mode u2Mode;/*The clock mode in datasheet.different mode means different source clock selected*/
}vm_gpio_ctrl_set_clk_out_t;


/******************************************************************
* DESCRIPTION
*   This struct is for GPIO_CMD_SET_CLK_DIV control command,used in vm_dcl_control as parameter.
*   To control GPIOs, you should use DCL(Driver Common Layer) APIs. 
*   Note,some platform do not have such functions and others may have. You should refer the datasheet before using GPIOs.
* EXAMPLE
*   <code>
*   #include "vm_dcl.h"
*   VM_DCL_HANDLE gpio_handle; // Declare a VM_DCL_HANDLE variable. 
*   vm_gpio_ctrl_set_clk_div_t clk_data; //Declare a vm_gpio_ctrl_set_clk_out_t variable.
*   gpio_handle = vm_dcl_open(VM_DCL_GPIO_CLK,55);// Step1, we call vm_dcl_open to get a handle. 55 means gpio55. Notice the dev parameter is VM_DCL_GPIO_CLK. 
*   clk_data.u2ClkNum = 3;// More details, please refer to the GPIO datasheet. 
*   clk_data.u2Div = 2; //More details, please refer to the GPIO datasheet. 
*   vm_dcl_control(gpio_handle,GPIO_CMD_SET_CLK_DIV,(void *)&clk_data); // Step2, we call vm_dcl_control to set pupd of gpio55 .
*   vm_dcl_close(gpio_handle); // Finally, we call vm_dcl_close 
*   </code>
*******************************************************************/
typedef struct
{
    VMUINT16  u2ClkNum; /*The clock register number in datasheet.*/
    vm_gpio_clk_div   u2Div; /*The division value in datasheet.Please get more details in datasheet.*/
}vm_gpio_ctrl_set_clk_div_t;


#endif


