	 
#ifndef __VM_TS_DCL_UART_H_STRUCT__
#define __VM_TS_DCL_UART_H_STRUCT__

/*****************************************************************************
 * DESCRIPTION
 *  VM_TS_UART_PORT is the type of VMDCL_UINT16 ,which define the type UART_PORT
 *  user select
 *****************************************************************************/
typedef VMDCL_UINT16  VM_TS_UART_PORT;

/*******************************************************************************
 * DESCRIPTION
 *  VM_TS_UART_T_OWNER_TO_HANDLE(owner) is the   owner and handler mapping MACRO
 *******************************************************************************/
#define VM_TS_UART_T_OWNER_TO_HANDLE(owner)   (owner | VM_TS_DCL_UART_T_DEV_MAGIC_NUM)

/*******************************************************************************
 * DESCRIPTION
 *  VM_TS_DCL_UART_T_DEV_MAGIC_NUM is the magic number 
 *******************************************************************************/
#define VM_TS_DCL_UART_T_DEV_MAGIC_NUM 0xA0000000

/*****************************************************************************
 * DESCRIPTION
 *   VM_TS_DCL_UART_DEV_T is the  uart type ENUM, user can select one of 
 *  the port to use
 * EXAMPLE		                            
 * <code>
 * uart_handle = vm_ts_dcl_open(VM_TS_UART_PORT1,0);
 * if(VM_TS_DCL_HANDLE_INVALID==uart_handle) return;
 * //Do something with the handle.
 * </code>
 *****************************************************************************/
typedef enum
{
	VM_TS_UART_PORT1=VM_TS_DCL_UART_GROUP_START, 
	VM_TS_UART_PORT2, 
	VM_TS_UART_PORT3
} VM_TS_DCL_UART_DEV_T;


/*****************************************************************************
 * DESCRIPTION
 *  VM_TS_DRV_UART_ID_CNT is the  number of uart ports
 *****************************************************************************/
#define VM_TS_DRV_UART_ID_CNT  	6


/*****************************************************************************
 * DESCRIPTION
 *  VM_TS_UART1_HISR_ID is  UART1_HISR ID 
 *****************************************************************************/
#define VM_TS_UART1_HISR_ID  (VM_TS_DRV_UART_ID_START + 1)

/*****************************************************************************
 * DESCRIPTION
 *  VM_TS_UART1_HISR_RX_ID is UART1_HISR_RX ID 
 *****************************************************************************/
#define VM_TS_UART1_HISR_RX_ID  (VM_TS_DRV_UART_ID_START + 1)

/*****************************************************************************
 * DESCRIPTION
 *  VM_TS_UART1_HISR_TX_ID is  UART1_HISR_TX ID
 *****************************************************************************/
#define VM_TS_UART1_HISR_TX_ID  (VM_TS_DRV_UART_ID_START + 2)

/*****************************************************************************
 * DESCRIPTION
 *  VM_TS_UART2_HISR_ID is  UART2_HISR ID 
 *****************************************************************************/
#define VM_TS_UART2_HISR_ID  (VM_TS_DRV_UART_ID_START + 3)

/*****************************************************************************
 * DESCRIPTION
 *  VM_TS_UART2_HISR_RX_ID is UART2_HISR_RX ID 
 *****************************************************************************/
#define VM_TS_UART2_HISR_RX_ID  (VM_TS_DRV_UART_ID_START + 3)

/*****************************************************************************
 * DESCRIPTION
 *  VM_TS_UART2_HISR_TX_ID is  UART2_HISR_TX ID
 *****************************************************************************/
#define VM_TS_UART2_HISR_TX_ID  (VM_TS_DRV_UART_ID_START + 4)

/*****************************************************************************
 * DESCRIPTION
 *  VM_TS_UART3_HISR_ID is  UART3_HISR ID 
 *****************************************************************************/
#define VM_TS_UART3_HISR_ID  (VM_TS_DRV_UART_ID_START + 5)

/*****************************************************************************
 * DESCRIPTION
 *  VM_TS_UART3_HISR_RX_ID is UART3_HISR_RX ID 
 *****************************************************************************/
#define VM_TS_UART3_HISR_RX_ID  (VM_TS_DRV_UART_ID_START + 5)

/*****************************************************************************
 * DESCRIPTION
 *  VM_TS_UART3_HISR_TX_ID is  UART3_HISR_TX ID
 *****************************************************************************/
#define VM_TS_UART3_HISR_TX_ID  (VM_TS_DRV_UART_ID_START + 6)

/************************************************************************************************************
 * DESCRIPTION
 *  VM_TS_UART_CTRL_CMD_T is the CMD type ENUM, user can use VM_TS_UART_CTRL_CMD_T 
 *  command to control UART  
 * EXAMPLE		                            
 * <code>
 * 	VM_TS_DCL_HANDLE user_handler;
 *  VM_TS_UART_CTRL_GET_BYTES_T user_get_Data;
 *  user_get_Data.puBuffaddr = test_uart_Rx_buffer;
 *	user_get_Data.u2Length = ts_uart_total_get_num-ts_uart_have_get_num;
 *	user_handler = VM_TS_DCL_Open(VM_TS_UART_PORT1,0);
 *	VM_TS_DCL_Control(user_handler,VM_TS_UART_CMD_GET_BYTES,(void*)&user_get_Data);
 *  ts_uart_have_get_num += user_get_Data.u2RetSize;
 *	VM_TS_DCL_Close(user_handler);
 * </code>
 **************************************************************************************************************/
typedef enum
{
   VM_TS_UART_CMD_GET_BYTES,  /*interrupt mode */
   VM_TS_UART_CMD_PUT_BYTES,  /*interrupt mode */
   VM_TS_UART_CMD_GET_BYTE,   /*polling mode */
   VM_TS_UART_CMD_PUT_BYTE    /*polling mode */
}VM_TS_UART_CTRL_CMD_T;

/************************************************************************************************************
 * DESCRIPTION
 *  VM_TS_UART_CTRL_GET_BYTES_T is the cmd struct, user can use VM_TS_UART_CMD_GET_BYTES 
 *  command to get data  in interrupt mode 
 * EXAMPLE		                            
 * <code>
 * 	VM_TS_DCL_HANDLE user_handler;
 *  VM_TS_UART_CTRL_GET_BYTES_T user_get_Data;
 *  user_get_Data.puBuffaddr = test_uart_Rx_buffer;
 *	user_get_Data.u2Length = ts_uart_total_get_num-ts_uart_have_get_num;
 *	user_handler = VM_TS_DCL_Open(VM_TS_UART_PORT1,0);
 *	VM_TS_DCL_Control(user_handler,VM_TS_UART_CMD_GET_BYTES,(void*)&user_get_Data);
 *  ts_uart_have_get_num += user_get_Data.u2RetSize;
 *	VM_TS_DCL_Close(user_handler);
 * </code>
 **************************************************************************************************************/
typedef struct
{
	VMDCL_UINT16 u2Length;
	VMDCL_UINT32 u4OwenrId;
	VMDCL_UINT8* puBuffaddr;
	VMDCL_UINT16	u2RetSize;
}VM_TS_UART_CTRL_GET_BYTES_T;

/************************************************************************************************************
 * DESCRIPTION
 *  VM_TS_UART_CTRL_PUT_BYTES_T is the cmd struct, user can use VM_TS_UART_CTRL_PUT_BYTES_T 
 *  command to put data in interrupt mode 
 * EXAMPLE		                            
 * <code>
 * 	VM_TS_DCL_HANDLE user_handler;
 *  VM_TS_UART_CTRL_PUT_BYTES_T user_put_Data;
  *	user_handler = VM_TS_DCL_Open(VM_TS_UART_PORT1,0);
 *  user_put_Data.puBuffaddr = test_uart_Tx_buffer;
 *	user_put_Data.u2Length = ts_uart_total_put_num-ts_uart_have_put_num;
 *	VM_TS_DCL_Control(user_handler,VM_TS_UART_CMD_PUT_BYTES,(void*)&user_put_Data);
 *  ts_uart_have_put_num += user_put_Data.u2RetSize;
 *	VM_TS_DCL_Close(user_handler);
 * </code>
 **************************************************************************************************************/
typedef struct
{
	VMDCL_UINT16 u2Length;
	VMDCL_UINT32 u4OwenrId;
	VMDCL_UINT8* puBuffaddr;
	VMDCL_UINT16	u2RetSize;
}VM_TS_UART_CTRL_PUT_BYTES_T;

/************************************************************************************************************
 * DESCRIPTION
 *  VM_TS_UART_CTRL_GET_BYTE_T is the cmd struct, user can use VM_TS_UART_CMD_GET_BYTE 
 *  command to get data in polling mode 
 * EXAMPLE		                            
 * <code>
 * VM_TS_DCL_HANDLE user_handler;
 * VM_TS_UART_CTRL_GET_BYTE_T user_get_Data;
 * user_get_Data.puBuffaddr = &test_uart_Rx_one_data;
 *	user_handler = VM_TS_DCL_Open(TS_UART_PORT1,0);
 *	VM_TS_DCL_Control(user_handler,VM_TS_UART_CMD_GET_BYTE,(void*)&user_get_Data);
 *	if( user_get_Data.u1IsGetData )
 *	{
 *	 //get byte success
 *	}
 *	else
 *	{
 *	 //there is no data
 *	}
 *	TS_DCL_Close(user_handler);
 * </code>
 **************************************************************************************************************/
typedef struct
{
	VMDCL_UINT32 u4OwenrId;
	VMDCL_UINT8* puBuffaddr;
	VMDCL_UINT8	u1IsGetData;
}VM_TS_UART_CTRL_GET_BYTE_T;


/************************************************************************************************************
 * DESCRIPTION
 *  VM_TS_UART_CTRL_PUT_BYTE_T is the cmd struct, user can use VM_TS_UART_CMD_PUT_BYTE 
 *  command to put data in polling mode 
 * EXAMPLE		                            
 * <code>
 * VM_TS_DCL_HANDLE user_handler;
 * VM_TS_UART_CTRL_PUT_BYTE_T user_put_Data;
 * user_put_Data.puBuffaddr = &test_uart_Tx_one_data;
 *	user_handler = VM_TS_DCL_Open(TS_UART_PORT1,0);
 *	VM_TS_DCL_Control(user_handler,VM_TS_UART_CMD_PUT_BYTE,(void*)&user_get_Data);
 *	TS_DCL_Close(user_handler);
 * </code>
 **************************************************************************************************************/
typedef struct
{
	VMDCL_UINT32 u4OwenrId;
	VMDCL_UINT8* puBuffaddr;
}VM_TS_UART_CTRL_PUT_BYTE_T;


extern VM_TS_DCL_STATUS VM_TS_Dcl_UART_Initialize(void);

/*************************************************************************
* FUNCTION
*  VM_TS_Dcl_UART_Open
*
* DESCRIPTION
*  This function is to open the UART module and get a handle. Note that 
* multiple opens are prohibited.
*
* PARAMETERS
*	eDev - only valid for VM_TS_UART_PORT1, VM_TS_UART_PORT2, VM_TS_UART_PORT3(if exists) and 
*         DCL_UART_XXX.
*	flags - user id (VM_TS_UART1_HISR_ID,VM_TS_UART2_HISR_ID.VM_TS_UART3_HISR_ID)
*
* RETURNS
*  VM_TS_DCL_HANDLE_INVALID - The device is not valid.
*  other value - a valid handle
*
*************************************************************************/
extern VM_TS_DCL_HANDLE VM_TS_Dcl_UART_Open(TS_DCL_DEV dev, TS_DCL_FLAGS flags);

/*************************************************************************
* FUNCTION
*  VM_TS_Dcl_UART_Control
*
* DESCRIPTION
*  This function is support UART module commands.
*
* CALLS  
*	It is called to send command to control the UART module.
*
* PARAMETERS
*	handle - a valid handle return by VM_TS_Dcl_UART_Open()
*   cmd   - please refer to VM_TS_UART_CTRL_CMD_T STRUCT
*   data -  user's setting data 
*	
* RETURNS
*	 VM_TS_STATUS_OK: command is executed successfully.
* VM_TS_STATUS_INVALID_CMD: It's a invalid command.
* VM_TS_STATUS_INVALID_HANDLE: It's a invalid handle.
*
*************************************************************************/
extern VM_TS_DCL_STATUS VM_TS_Dcl_UART_Control(TS_DCL_HANDLE handle, TS_DCL_CTRL_CMD cmd, void *data);

/*************************************************************************
* FUNCTION
*  VM_TS_Dcl_UART_Close
*
* DESCRIPTION
*  This function is to close the UART module.
*
* PARAMETERS
*	handle  - hanlde previous got from VM_TS_Dcl_UART_Open()
*
* RETURNS
*	 VM_TS_STATUS_OK - successfully close the UART module.
*  VM_TS_STATUS_INVALID_HANDLE - invalid handle

*************************************************************************/
extern VM_TS_DCL_STATUS VM_TS_Dcl_UART_Close(TS_DCL_HANDLE handle);


#endif 

