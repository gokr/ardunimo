#ifndef __VM_DCL_I2C_H__
#define __VM_DCL_I2C_H__

/*****************************************************************************
 * DESCRIPTION
 *  VM_DCL_I2C_OWNER  indecates that this is the DEFAULT user when no users use
 *  i2c driver  
 *****************************************************************************/
typedef enum
{
	VM_DUMMY_I2C_OWNER = 0xD
}VM_DCL_I2C_OWNER;


/*****************************************************************************
 * DESCRIPTION
 *  VM_DCL_I2C_DEV_T  indecates the deivce which use i2c module,*This enum 
 * define the dev for i2c module. Used in vm_dcl_open
  * EXAMPLE		                            
 * <code>
 *	VM_DCL_HANDLE i2c_handle;
 * i2c_handle = vm_dcl_open(VM_DCL_I2C,0);
 * if(VM_DCL_HANDLE_INVALID==i2c_handle) return;
 * //Do something with the handle.
 * </code> 
 *****************************************************************************/
typedef enum
{
	VM_DCL_I2C_START = VM_DCL_I2C_GROUP_START,       /*I2C device start*/
	VM_DCL_I2C                                      /*This device is for vm_dcl_open as a parameter.*/
}VM_DCL_I2C_DEV_T;


/*****************************************************************************
 * DESCRIPTION
 *  VM_DCL_I2C_TRANSACTION_MODE  indecates the i2c Transaction Mode, user
 *  can select FAST or HIGH speed if need
  * EXAMPLE		                            
 * <code>
 *	VM_DCL_HANDLE i2c_handle;
 *	vm_i2c_ctrl_config_t conf_data;
 * i2c_handle = vm_dcl_open(VM_DCL_I2C,0);
 * if(VM_DCL_HANDLE_INVALID==i2c_handle) return;
 *conf_data.Reserved0 = 0;
 *conf_data.eTransactionMode = VM_DCL_I2C_TRANSACTION_FAST_MODE;
 *conf_data.fgGetHandleWait = 0;
 *conf_data.Reserved1 = 0;
 *conf_data.u1DelayLen = 0;
 *conf_data.u1SlaveAddress = 0x98;
 *conf_data.u4FastModeSpeed = 400;
 *conf_data.u4HSModeSpeed = 0;
 *vm_dcl_control(i2c_handle,VM_I2C_CMD_CONFIG,(void *)&conf_data);
 * //Do something with the handle.
 * </code> 
 *****************************************************************************/
typedef enum
{
   VM_DCL_I2C_TRANSACTION_FAST_MODE, /* Fast Mode: < 400kbps */
   VM_DCL_I2C_TRANSACTION_HIGH_SPEED_MODE /* Hign Speed Mode: > 400kbps */
}VM_DCL_I2C_TRANSACTION_MODE;


/*****************************************************************************
 * DESCRIPTION
 *  VM_DCL_I2C_CTRL_CMD_T  indecates tthe I2C control commands, user
 *  can  select CMDS to control driver
  * EXAMPLE		                            
 * <code>
 *	VM_DCL_HANDLE i2c_handle;
 *	vm_i2c_ctrl_config_t conf_data;
 *	vm_i2c_ctrl_single_write_t write_data;
 *  VM_DCL_BUFF_LEN len;
 *	VMUINT8 i2c_write_data[2] = {0x56,0x78};
 * i2c_handle = vm_dcl_open(VM_DCL_I2C,0);
 * if(VM_DCL_HANDLE_INVALID==i2c_handle) return;
 * conf_data.Reserved0 = 0;
 * conf_data.eTransactionMode = VM_DCL_I2C_TRANSACTION_FAST_MODE;
 * conf_data.fgGetHandleWait = 0;
 * conf_data.Reserved1 = 0;
 * conf_data.u1DelayLen = 0;
 * conf_data.u1SlaveAddress = 0x98;
 * conf_data.u4FastModeSpeed = 400;
 * conf_data.u4HSModeSpeed = 0;
 * vm_dcl_control(i2c_handle,VM_I2C_CMD_CONFIG,(void *)&conf_data);
 * write_data.pu1Data = i2c_write_data;
 * write_data.u4DataLen = 2;
 * vm_dcl_write(i2c_handle,(VM_DCL_BUFF*)i2c_write_data,2,&len,0);
 *  //Do something with the handle.
 *  </code> 
 *****************************************************************************/
typedef enum
{
   VM_I2C_CMD_GET_TRANSACTION_MODE = 0x901, /* Get transaction mode */
   VM_I2C_CMD_SET_TRANSACTION_SPEED, /* Set transaction speed */
   VM_I2C_CMD_SINGLE_WRITE, /* Single write of blocking mode */
   VM_I2C_CMD_SINGLE_READ, /* Single read of blocking mode */
   VM_I2C_CMD_CONT_WRITE, /* Continue write of blocking mode */
   VM_I2C_CMD_CONT_READ, /* Continue read of blocking mode */
   VM_I2C_CMD_WRITE_AND_READ, /* Write and read of blocking mode */
   VM_I2C_CMD_RESERVED0, /* Reserved command. Do not use it */
   VM_I2C_CMD_RESERVED1, /* Reserved command. Do not use it */
   VM_I2C_CMD_RESERVED2, /* Reserved command. Do not use it */
   VM_I2C_CMD_RESERVED3, /* Reserved command. Do not use it */
   VM_I2C_CMD_SET_SLAVE_ADDRESS, /* Set the slave address of sensor */
   VM_I2C_CMD_CONFIG /* Configure the i2c for read or writer */
}VM_DCL_I2C_CTRL_CMD_T;

/*****************************************************************************
 * DESCRIPTION
 *  vm_i2c_ctrl_get_transaction_mode_t  indecates I2C_CMD_GET_TRANSACTION_MODE command
  * EXAMPLE		                            
 * <code>
 *	VM_DCL_HANDLE i2c_handle;
 *	vm_i2c_ctrl_config_t conf_data;
 * vm_i2c_ctrl_get_transaction_mode_t mode;
 * i2c_handle = vm_dcl_open(VM_DCL_I2C,0);
 * if(VM_DCL_HANDLE_INVALID==i2c_handle) return;
 * conf_data.Reserved0 = 0;
 * conf_data.eTransactionMode = VM_DCL_I2C_TRANSACTION_FAST_MODE;
 * conf_data.fgGetHandleWait = 0;
 * conf_data.Reserved1 = 0;
 * conf_data.u1DelayLen = 0;
 * conf_data.u1SlaveAddress = 0x98;
 * conf_data.u4FastModeSpeed = 400;
 * conf_data.u4HSModeSpeed = 0;
 * vm_dcl_control(i2c_handle,VM_I2C_CMD_CONFIG,(void *)&conf_data);
 * vm_dcl_control(i2c_handle,I2C_CMD_GET_TRANSACTION_MODE,(void *)&mode);
 *  //Do something with the handle.
 *  </code> 
 *****************************************************************************/
typedef struct
{
   VM_DCL_I2C_TRANSACTION_MODE eTransactionMode; /* Transaction mode */
}vm_i2c_ctrl_get_transaction_mode_t;



/*****************************************************************************
 * DESCRIPTION
 *  vm_i2c_ctrl_set_transaction_speed_t  indecates I2C_CMD_SET_TRANSACTION_SPEED command
  * EXAMPLE		                            
 * <code>
 *	VM_DCL_HANDLE i2c_handle;
 *	vm_i2c_ctrl_config_t conf_data;
 * vm_i2c_ctrl_set_transaction_speed_t speed;
 * i2c_handle = vm_dcl_open(VM_DCL_I2C,0);
 * if(VM_DCL_HANDLE_INVALID==i2c_handle) return;
 * conf_data.Reserved0 = 0;
 * conf_data.eTransactionMode = VM_DCL_I2C_TRANSACTION_FAST_MODE;
 * conf_data.fgGetHandleWait = 0;
 * conf_data.Reserved1 = 0;
 * conf_data.u1DelayLen = 0;
 * conf_data.u1SlaveAddress = 0x98;
 * conf_data.u4FastModeSpeed = 400;
 * conf_data.u4HSModeSpeed = 0;
 * vm_dcl_control(i2c_handle,VM_I2C_CMD_CONFIG,(void *)&conf_data);
 * speed.eTransactionMode = VM_DCL_I2C_TRANSACTION_HIGH_SPEED_MODE;
 * speed.u4FastModeSpeed = 800;
 * speed.u4HSModeSpeed = 1;
 * vm_dcl_control(i2c_handle,I2C_CMD_SET_TRANSACTION_SPEED,(void *)&speed);
 *  //Do something with the handle.
 *  </code> 
 *****************************************************************************/
typedef struct
{
   VM_DCL_I2C_TRANSACTION_MODE eTransactionMode; /* Transaction mode */
   VMUINT32 u4FastModeSpeed; /* Fast mode speed */
   VMUINT32 u4HSModeSpeed; /* High speed mode speed */
}vm_i2c_ctrl_set_transaction_speed_t;

/*****************************************************************************
 * DESCRIPTION
 *  vm_i2c_ctrl_single_write_t,vm_i2c_ctrl_single_read_t  indecates 
 *  I2C_CMD_SINGLE_WRITE, I2C_CMD_SINGLE_READ command.
  * EXAMPLE		                            
 * <code>
 *	VM_DCL_HANDLE i2c_handle;
 *	vm_i2c_ctrl_config_t conf_data;
 *	vm_i2c_ctrl_single_write_t write_data;
 *  vm_i2c_ctrl_single_read_t  read_data;
 *  VM_DCL_BUFF_LEN len;
 *	VMUINT8 i2c_write_data[2] = {0x56,0x78};
  *  VMUINT8 i2c_read_data[2] = {0x0,0x0};
 * i2c_handle = vm_dcl_open(VM_DCL_I2C,0);
 * if(VM_DCL_HANDLE_INVALID==i2c_handle) return;
 * conf_data.Reserved0 = 0;
 * conf_data.eTransactionMode = VM_DCL_I2C_TRANSACTION_FAST_MODE;
 * conf_data.fgGetHandleWait = 0;
 * conf_data.Reserved1 = 0;
 * conf_data.u1DelayLen = 0;
 * conf_data.u1SlaveAddress = 0x98;
 * conf_data.u4FastModeSpeed = 400;
 * conf_data.u4HSModeSpeed = 0;
 * vm_dcl_control(i2c_handle,VM_I2C_CMD_CONFIG,(void *)&conf_data);
 * write_data.pu1Data = i2c_write_data;
 * write_data.u4DataLen = 2;
 * vm_dcl_control(i2c_handle,I2C_CMD_SINGLE_WRITE,(void *)&write_data);
 * read_data.pu1Data=i2c_read_data;
 * read_data.u4DataLen = 2;
 * vm_dcl_control(i2c_handle,I2C_CMD_SINGLE_READ,(void *)&read_data);
 *  //Do something with the handle.
 *  </code> 
 *****************************************************************************/
typedef struct
{
   VMUINT8 *pu1Data; /* Pointer to the buffer of data */
   VMUINT32 u4DataLen; /* Data length ,Note that this len should not exceed 8*/
}vm_i2c_ctrl_single_write_t,vm_i2c_ctrl_single_read_t;

/*****************************************************************************
 * DESCRIPTION
 *  vm_i2c_ctrl_single_write_t,vm_i2c_ctrl_single_read_t  indecates 
 *   I2C_CMD_CONT_WRITE, I2C_CMD_CONT_READ command
  * EXAMPLE		                            
 * <code>
 *	VM_DCL_HANDLE i2c_handle;
 *	vm_i2c_ctrl_config_t conf_data;
 *	vm_i2c_ctrl_cont_write_t write_data;
 *  vm_i2c_ctrl_cont_read_t  read_data;
 *  VM_DCL_BUFF_LEN len;
 *	VMUINT8 i2c_write_data[20] = {0x56,0x78,0x00};
 *  VMUINT8 i2c_read_data[20] = {0x0};
 * i2c_handle = vm_dcl_open(VM_DCL_I2C,0);
 * if(VM_DCL_HANDLE_INVALID==i2c_handle) return;
 * conf_data.Reserved0 = 0;
 * conf_data.eTransactionMode = VM_DCL_I2C_TRANSACTION_FAST_MODE;
 * conf_data.fgGetHandleWait = 0;
 * conf_data.Reserved1 = 0;
 * conf_data.u1DelayLen = 0;
 * conf_data.u1SlaveAddress = 0x98;
 * conf_data.u4FastModeSpeed = 400;
 * conf_data.u4HSModeSpeed = 0;
 * vm_dcl_control(i2c_handle,VM_I2C_CMD_CONFIG,(void *)&conf_data);
 * write_data.pu1Data = i2c_write_data;
 * write_data.u4DataLen = 20;
 * write_data.u4TransferNum = 1;
 * vm_dcl_control(i2c_handle,I2C_CMD_SINGLE_WRITE,(void *)&write_data);
 *  read_data.pu1Data=i2c_read_data;
 * read_data.u4DataLen = 20;
  * read_data.u4TransferNum = 1;
 * vm_dcl_control(i2c_handle,I2C_CMD_SINGLE_READ,(void *)&read_data);
 *  //Do something with the handle.
 *  </code> 
 *****************************************************************************/
typedef struct
{
   VMUINT8 *pu1Data; /* Pointer to the buffer of data */
   VMUINT32 u4DataLen; /* Data length of each transfer ,Note that this len should not exceed 8*/
   VMUINT32 u4TransferNum; /* Transfer number */
}vm_i2c_ctrl_cont_write_t,vm_i2c_ctrl_cont_read_t;


/*****************************************************************************
 * DESCRIPTION
 *  vm_i2c_ctrl_write_and_read_tindecates I2C_CMD_WRITE_AND_READ command command
  * EXAMPLE		                            
 * <code>
 *	VM_DCL_HANDLE i2c_handle;
 *	vm_i2c_ctrl_config_t conf_data;
 *	vm_i2c_ctrl_write_and_read_t write_and_read_data;
 *  vm_i2c_ctrl_cont_read_t  read_data;
 *  VM_DCL_BUFF_LEN len;
 *	VMUINT8 i2c_write_data[20] = {0x56,0x78,0x00};
 *  VMUINT8 i2c_read_data[20] = {0x0};
 * i2c_handle = vm_dcl_open(VM_DCL_I2C,0);
 * if(VM_DCL_HANDLE_INVALID==i2c_handle) return;
 * conf_data.Reserved0 = 0;
 * conf_data.eTransactionMode = VM_DCL_I2C_TRANSACTION_FAST_MODE;
 * conf_data.fgGetHandleWait = 0;
 * conf_data.Reserved1 = 0;
 * conf_data.u1DelayLen = 0;
 * conf_data.u1SlaveAddress = 0x98;
 * conf_data.u4FastModeSpeed = 400;
 * conf_data.u4HSModeSpeed = 0;
 * vm_dcl_control(i2c_handle,VM_I2C_CMD_CONFIG,(void *)&conf_data);
 * write_and_read_data.pu1OutData = i2c_write_data;
 *  write_and_read_data.u4OutDataLen = 20;
 * write_and_read_data.pu1InData = i2c_read_data;
 *  write_and_read_data.u4InDataLen = 20;
 * vm_dcl_control(i2c_handle,I2C_CMD_WRITE_AND_READ,(void *)&write_and_read_data);
 *  //Do something with the handle.
 *  </code> 
 *****************************************************************************/

typedef struct
{
   VMUINT8 *pu1InData; /* Pointer to the read data */
   VMUINT32 u4InDataLen; /* Read data length ,Note that this len should not exceed 8*/
   VMUINT8 *pu1OutData; /* Pointer to the write data */
   VMUINT32 u4OutDataLen; /* Write data length ,Note that this len should not exceed 8*/
}vm_i2c_ctrl_write_and_read_t;


/*****************************************************************************
 * DESCRIPTION
 *  vm_i2c_ctrl_set_slave_address_t  indecates I2C_CMD_SET_SLAVE_ADDRESS command
  * EXAMPLE		                            
 * <code>
 *	VM_DCL_HANDLE i2c_handle;
 *	vm_i2c_ctrl_config_t conf_data;
 * vm_i2c_ctrl_set_slave_address_t address_setting;
 * i2c_handle = vm_dcl_open(VM_DCL_I2C,0);
 * if(VM_DCL_HANDLE_INVALID==i2c_handle) return;
 * conf_data.Reserved0 = 0;
 * conf_data.eTransactionMode = VM_DCL_I2C_TRANSACTION_FAST_MODE;
 * conf_data.fgGetHandleWait = 0;
 * conf_data.Reserved1 = 0;
 * conf_data.u1DelayLen = 0;
 * conf_data.u1SlaveAddress = 0x98;
 * conf_data.u4FastModeSpeed = 400;
 * conf_data.u4HSModeSpeed = 0;
 * vm_dcl_control(i2c_handle,VM_I2C_CMD_CONFIG,(void *)&conf_data);
 * address_setting.u1SlaveAddress=0x98;
 * vm_dcl_control(i2c_handle,I2C_CMD_GET_TRANSACTION_MODE,(void *)&address_setting);
 *  //Do something with the handle.
 *  </code> 
 *****************************************************************************/
typedef struct
{
   VMUINT8 u1SlaveAddress; /* Slave address */
}vm_i2c_ctrl_set_slave_address_t;


/*****************************************************************************
 * DESCRIPTION
 *  vm_i2c_ctrl_config_t  indecates I2C_CMD_CONFIG command
 * EXAMPLE		                            
 * <code>
 *	VM_DCL_HANDLE i2c_handle;
 *	vm_i2c_ctrl_config_t conf_data;
 * i2c_handle = vm_dcl_open(VM_DCL_I2C,0);
 * if(VM_DCL_HANDLE_INVALID==i2c_handle) return;
 *conf_data.Reserved0 = 0;
 *conf_data.eTransactionMode = VM_DCL_I2C_TRANSACTION_FAST_MODE;
 *conf_data.fgGetHandleWait = 0;
 *conf_data.Reserved1 = 0;
 *conf_data.u1DelayLen = 0;
 *conf_data.u1SlaveAddress = 0x98;
 *conf_data.u4FastModeSpeed = 400;
 *conf_data.u4HSModeSpeed = 0;
 *vm_dcl_control(i2c_handle,VM_I2C_CMD_CONFIG,(void *)&conf_data);
 * //Do something with the handle.
 * </code> 
 *****************************************************************************/
typedef struct
{
   VM_DCL_I2C_OWNER Reserved0; /* Reserved, please use 0 */
   VMBOOL fgGetHandleWait; /* KAL_TRUE: wait until I2C is idle; KAL_FALSE: do not wait */
   VMUINT8 u1SlaveAddress; /* Slave address */
   VMUINT8 u1DelayLen; /* Wait delay between consecutive transfers (the unit is half pulse width) */
   VM_DCL_I2C_TRANSACTION_MODE eTransactionMode; /* Fast mode or high speed mode */
   VMUINT32 u4FastModeSpeed; /* The transfer speed under fast mode. But even under high speed mode, you should alse configure this parameter */
   VMUINT32 u4HSModeSpeed; /* The transfer speed under high speed mode */
   VMBOOL Reserved1; /* Reserved,please always use 0 to fill this member. */
} vm_i2c_ctrl_config_t;

#endif


