#ifndef __VM_TS_DCL_I2C_H__
#define __VM_TS_DCL_I2C_H__

/******************************************************************
* DESCRIPTION
*   This enum defines the device for I2C module,used in vm_ts_dcl_open as a parameter.
*   To control I2C, you should use DCL(Driver Common Layer) APIs. 
* EXAMPLE
* <code>
*   #include "vmtsdcl.h"
*   VM_TS_DCL_HANDLE i2c_handle;					 // Declare a VM_TS_DCL_HANDLE variable. 
*   i2c_handle = vm_ts_dcl_open(VM_TS_DCL_I2C,0);      // Call vm_ts_dcl_open to get a handle. flag fill 0.
* </code>
*******************************************************************/
typedef enum
{
	VM_TS_I2C_GROUP_START = VM_TS_DCL_I2C_GROUP_START,
	VM_TS_DCL_I2C
}VM_TS_DCL_I2C_DEV;

/******************************************************************
* DESCRIPTION
*   This enum defines the I2C transaction state, it will be given to user by lisr callback
*   For more details , refer the VM_TS_DCL_I2C_CTRL_CMD_T description.
*******************************************************************/
 typedef enum
 {
	 VM_TS_DCL_I2C_TRANS_STA_FINISH = 1, /* transfer finish success */
	 VM_TS_DCL_I2C_TRANS_STA_ACK_ERR,    /* an ack error happened */
	 VM_TS_DCL_I2C_TRANS_STA_NACK_ERR,   /* an n-ack error happened */
	 VM_TS_DCL_I2C_TRANS_STA_FAIL,	    /* unexpected error happend*/
 }VM_TS_DCL_I2C_TRANSACTION_STATE;

 /******************************************************************
 * DESCRIPTION
 *	 This enum defines the I2C transaction mode.
 *	 For more details , refer the VM_TS_DCL_I2C_CTRL_CONFIG_T description.
 *******************************************************************/
typedef enum
{
   VM_TS_DCL_I2C_TRANSACTION_FAST_MODE, /* Fast Mode: < 400kbps */
   VM_TS_DCL_I2C_TRANSACTION_HIGH_SPEED_MODE /* Hign Speed Mode: > 400kbps */
}VM_TS_DCL_I2C_TRANSACTION_MODE;

/******************************************************************
* DESCRIPTION
*   This enum  define the control command for I2C  module,used in vm_ts_dcl_control as parameter.
*   With different commands, user could control the different function of the I2C.
*   To control I2C, you should use DCL(Driver Common Layer) APIs. 
* EXAMPLE
* <code>
*   #include "vmtsdcl.h"
*   VM_TS_DCL_HANDLE i2c_handle;					 // Declare a VM_TS_DCL_HANDLE variable. 
*   VM_TS_DCL_I2C_CTRL_CONFIG_T i2c_config;
*   i2c_handle = vm_ts_dcl_open(VM_TS_DCL_I2C,0);			// First, we call vm_ts_dcl_open to get a handle. 19 means eint19
*   vm_ts_dcl_register_callback(i2c_handle,VM_TS_DCL_REGISTER_CALLBACK_LEVEL2,(void)i2c_lisr_cb); // register callback function,Note:i2c_lisr_cb is given by user
*   vm_ts_dcl_control(i2c_handle,VM_TS_DCL_I2C_CMD_CONFIG,(void *)&i2c_config);	// Usually, before we config eint, we mask it firstly. 
*   vm_ts_dcl_control(i2c_handle,VM_TS_DCL_I2C_CMD_SINGLE_WRITE_ASYNC,NULL);	// Usually, before we config eint, we mask it firstly. 
*   vm_ts_dcl_close(i2c_handle); // Finally, if you are sure you will not use eint, you call vm_dcl_close ,otherwise, not call this api.
* </code>
*******************************************************************/
typedef enum
{
   RESERVE_VM_TS_DCL_I2C_CMD_SINGLE_WRITE_ASYNC, /* not support,Single write of none-blocking mode */
   RESERVE_VM_TS_DCL_I2C_CMD_SINGLE_READ_ASYNC, /* not support,Single read of none-blocking mode */
   RESERVE_VM_TS_DCL_I2C_CMD_CONT_WRITE_ASYNC, /* not support,Continue write of none-blocking mode */
   RESERVE_VM_TS_DCL_I2C_CMD_CONT_READ_ASYNC, /* not support,Continue read of none-blocking mode */
   RESERVE_VM_TS_DCL_I2C_CMD_WRITE_AND_READ_ASYNC, /* not support,Write and read of none-blocking mode */
   VM_TS_DCL_I2C_CMD_SINGLE_WRITE_SYNC, /* Single write of blocking mode */
   VM_TS_DCL_I2C_CMD_SINGLE_READ_SYNC, /* Single read of blocking mode */
   VM_TS_DCL_I2C_CMD_CONT_WRITE_SYNC, /* Continue write of blocking mode */
   VM_TS_DCL_I2C_CMD_CONT_READ_SYNC, /* Continue read of blocking mode */
   VM_TS_DCL_I2C_CMD_WRITE_AND_READ_SYNC, /* Write and read of blocking mode */
   VM_TS_DCL_I2C_CMD_CONFIG
}VM_TS_DCL_I2C_CTRL_CMD_T;

/* For I2C_CMD_SINGLE_WRITE, I2C_CMD_SINGLE_READ command. */
typedef struct
{
   VMUINT8 *pu1Data; /* Pointer to the buffer of data */
   VMUINT32 u4DataLen; /* Data length */
}VM_TS_DCL_I2C_CTRL_SINGLE_WRITE_T, VM_TS_DCL_I2C_CTRL_SINGLE_READ_T;

/* For I2C_CMD_CONT_WRITE, I2C_CMD_CONT_READ command. */
typedef struct
{
   VMUINT8 *pu1Data; /* Pointer to the buffer of data */
   VMUINT32 u4DataLen; /* Data length of each transfer */
   VMUINT32 u4TransferNum; /* Transfer number */
}VM_TS_DCL_I2C_CTRL_CONT_WRITE_T, VM_TS_DCL_I2C_CTRL_CONT_READ_T;

/* For I2C_CMD_WRITE_AND_READ command. */
typedef struct
{
   VMUINT8 *pu1InData; /* Pointer to the read data */
   VMUINT32 u4InDataLen; /* Read data length */
   VMUINT8 *pu1OutData; /* Pointer to the write data */
   VMUINT32 u4OutDataLen; /* Write data length */
}VM_TS_DCL_I2C_CTRL_WRITE_AND_READE_T;

/* DCL I2C configure structure */
typedef struct
{
   VMUINT8 u1SlaveAddress; /* Slave address */
   VMUINT8 u1DelayLen; /* Wait delay between consecutive transfers (the unit is half pulse width) */
   VM_TS_DCL_I2C_TRANSACTION_MODE eTransactionMode; /* Fast mode or high speed mode */
   VMUINT32 u4FastModeSpeed; /* The transfer speed under fast mode. But even under high speed mode, you should alse configure this parameter */
   VMUINT32 u4HSModeSpeed; /* The transfer speed under high speed mode */
} VM_TS_DCL_I2C_CTRL_CONFIG_T;


#endif 




