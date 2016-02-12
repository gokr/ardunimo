#ifndef __VM_DCL_SIO_H__
#define __VM_DCL_SIO_H__

/*****************************************************************************
 * DESCRIPTION
 *   vm_uart_ready_to_write_ind_struct is the  meassge  struct which  inform 
 * user to write data ,user can get port information from this content
 *****************************************************************************/
typedef struct  
{       
	VMUINT8 	ref_count;
	VMUINT16 	msg_len;			/* LOCAL_PARA_HDR */	
	VMUINT16 	port;                           /*uart port*/
}vm_uart_ready_to_write_ind_struct;


/*****************************************************************************
 * DESCRIPTION
 *   vm_uart_ready_to_read_ind_struct is the  meassge  struct which  inform 
 * user to write data ,user can get port information from this content
 *****************************************************************************/
typedef struct  
{       
	VMUINT8 	ref_count;
	VMUINT16 	msg_len;			/* LOCAL_PARA_HDR */	
	VMUINT16 	port;                            /*uart port*/
}vm_uart_ready_to_read_ind_struct;


/*****************************************************************************
 * DESCRIPTION
 *   VM_DCL_SIO_DEV_T is the seriport type ENUM, user can select one of 
 *  the devices to use
 * EXAMPLE		                            
 * <code>
 * DCL_HANDLE uart_handle;
 * VM_DCL_MODULE_TYPE_T usr_id;
 * usr_id = vm_dcl_get_ownerid();
 * uart_handle = vm_dcl_open(vm_uart_port1,usr_id);
 * if(VM_DCL_HANDLE_INVALID==uart_handle) return;
 * //Do something with the handle.
 * </code>
 *****************************************************************************/
typedef enum
{
 	 	vm_uart_port1 = VM_DCL_SIO_GROUP_START,        /*uart port1*/	
		vm_uart_port2,                                 /*uart port2*/	   
		vm_uart_port3,                                 /*uart port3*/
		vm_uart_port_reserved,                         /*uart reserved*/
		vm_usb_port1,                                  /*usb port1*/
		vm_usb_port2                                    /*usb port2*/
} VM_DCL_SIO_DEV_T;


/************************************************************************************************************
 * DESCRIPTION
 *   VM_DCL_SIO_EVENT_T is the event type ENUM, user can select one of 
 *  the event to use, every event is matched with the callback user defined
 * EXAMPLE		                            
 * <code>
 * DCL_HANDLE uart_handle;
 * VM_DCL_MODULE_TYPE_T usr_id;
 * usr_id = vm_dcl_get_ownerid();
 * uart_handle = vm_dcl_open(vm_uart_port1,usr_id);
 * if(VM_DCL_HANDLE_INVALID==uart_handle) return;
 * vm_dcl_registercallback(uart_handle,VM_UART_READY_TO_WRITE ,(VM_DCL_CALLBACK)uart_callback,(void *)NULL);
 * //uart_callback is defined by user 
 * </code>
 **************************************************************************************************************/
typedef enum
{
    VM_UART_READY_TO_READ = VM_SERIPORT_EVENTS_START,    /*uart read event*/	
    VM_UART_READY_TO_WRITE,                                /*uart write event*/	
    VM_UART_CHECK_TX_BUFFER = 0x103,
    VM_USB_CHECK_TX_BUFFER = 0x211
} VM_DCL_SIO_EVENT_T;

typedef struct  
{       
    VMINT return_result;
}vm_dcl_sio_check_tx_buffer_t;


/************************************************************************************************************
 * DESCRIPTION
 *  VM_DCL_SIO_CTRL_CMD is the CMD type ENUM, user can use VM_SIO_CMD_SET_DCB_CONFIG 
 *  command to config uart driver 
 * EXAMPLE		                            
 * <code>
 * DCL_HANDLE uart_handle;
 * VM_DCL_MODULE_TYPE_T usr_id;
 * vm_sio_ctrl_dcb_t config;
 * usr_id = vm_dcl_get_ownerid();
 * uart_handle = vm_dcl_open(vm_uart_port1,usr_id);
 * if(VM_DCL_HANDLE_INVALID==uart_handle) return;
 *  config.u4OwenrId = usr_id;
 *	config.rUARTConfig.fgDSRCheck = 0;
 *	config.rUARTConfig.u1DataBits = VM_LEN_8;
 *	config.rUARTConfig.u1FlowControl = VM_FC_NONE;
 *	config.rUARTConfig.u1Parity = VM_PA_NONE;
 *	config.rUARTConfig.u1StopBits = VM_SB_1;
 *	config.rUARTConfig.u4Baud = VM_UART_BAUD_115200;
 *	config.rUARTConfig.ucXoffChar = 0x13;
 *	config.rUARTConfig.ucXonChar = 0x11;
 *	vm_dcl_control(uart_handle,VM_SIO_CMD_SET_DCB_CONFIG,&config);
 * //uart_callback is defined by user 
 * </code>
 **************************************************************************************************************/
                                           
 typedef enum
 {							    
	VM_SIO_CMD_SET_DCB_CONFIG = 0xd      /*uart setting*/	  
 }VM_DCL_SIO_CTRL_CMD;                                              
                                            
 

/*****************************************************************************
 * DESCRIPTION
 *  VM_UART_BAUDRATE_T is the type of   uart buadrate,which is a member of 
 * vm_sio_config_t
 *****************************************************************************/
typedef VMUINT32 VM_UART_BAUDRATE_T;  

/*****************************************************************************
 * DESCRIPTION
 *  VM_UART_baudrate is the type of VMUINT32,which define the type UART BUADRATE
 *  user set
 *****************************************************************************/
typedef VMUINT32 VM_UART_baudrate;    

/*****************************************************************************
 * DESCRIPTION
 *  VM_UART_PORT is the type of VMUINT16 ,which define the type UART_PORT
 *  user select
 *****************************************************************************/
typedef VMUINT16   VM_UART_PORT;               



/*****************************************************************************
 * DESCRIPTION
 *  VM_UART_BAUD_XXX is the VALUE of VM_UART_BAUDRATE_T type,use can select one
 *  of these vaules to config
 *****************************************************************************/
#define     VM_UART_BAUD_AUTO          0           /*AUTO BUADRATE*/    
#define     VM_UART_BAUD_75            75           /*BUADRATE 75*/     
#define     VM_UART_BAUD_150           150           /*BUADRATE 150*/  
#define     VM_UART_BAUD_300           300           /*BUADRATE 300*/  
#define     VM_UART_BAUD_600           600           /*BUADRATE 600*/    
#define     VM_UART_BAUD_1200          1200           /*BUADRATE 1200*/   
#define     VM_UART_BAUD_2400          2400             /*BUADRATE 2400*/   
#define     VM_UART_BAUD_4800          4800               /*BUADRATE 4800*/  
#define     VM_UART_BAUD_7200          7200              /*BUADRATE 7200*/  
#define     VM_UART_BAUD_9600          9600              /*BUADRATE 9600*/  
#define     VM_UART_BAUD_14400         14400              /*BUADRATE 14400*/   
#define     VM_UART_BAUD_19200         19200               /*BUADRATE 19200*/   
#define     VM_UART_BAUD_28800         28800              /*BUADRATE 28800*/   
#define     VM_UART_BAUD_33900         33900               /*BUADRATE 33900*/    
#define     VM_UART_BAUD_38400         38400               /*BUADRATE 38400*/    
#define     VM_UART_BAUD_57600         57600                /*BUADRATE 57600*/    
#define     VM_UART_BAUD_115200        115200                /*BUADRATE 115200*/    
#define     VM_UART_BAUD_230400        230400                 /*BUADRATE 230400*/  
#define     VM_UART_BAUD_460800        460800                /*BUADRATE 460800*/    
#define     VM_UART_BAUD_921600        921600                 /*BUADRATE 921600*/    
#define     VM_UART_BAUD_1500000       1500000                 /*BUADRATE 1500000*/  


/************************************************************************************************************
 * DESCRIPTION
 *  VM_UART_BITS_PER_CHAR_T is the DATA_LENGTH type ENUM, user can set DATA_LENGTH 
 *  to config uart driver 
 * EXAMPLE		                            
 * <code>
 * DCL_HANDLE uart_handle;
 * VM_DCL_MODULE_TYPE_T usr_id;
 * vm_sio_ctrl_dcb_t config;
 * usr_id = vm_dcl_get_ownerid();
 * uart_handle = vm_dcl_open(vm_uart_port1,usr_id);
 * if(VM_DCL_HANDLE_INVALID==uart_handle) return;
 *  config.u4OwenrId = usr_id;
 *	config.rUARTConfig.fgDSRCheck = 0;
 *	config.rUARTConfig.u1DataBits = VM_LEN_8;
 *	config.rUARTConfig.u1FlowControl = VM_FC_NONE;
 *	config.rUARTConfig.u1Parity = VM_PA_NONE;
 *	config.rUARTConfig.u1StopBits = VM_SB_1;
 *	config.rUARTConfig.u4Baud = VM_UART_BAUD_115200;
 *	config.rUARTConfig.ucXoffChar = 0x13;
 *	config.rUARTConfig.ucXonChar = 0x11;
 *	vm_dcl_control(uart_handle,VM_SIO_CMD_SET_DCB_CONFIG,&config);
 * //uart_callback is defined by user 
 * </code>
 **************************************************************************************************************/
typedef enum {
      VM_LEN_5=5,    /* 5 DATA LENGTH*/       
      VM_LEN_6,      /* 6 DATA LENGTH*/       
      VM_LEN_7,      /* 7 DATA LENGTH*/         
      VM_LEN_8       /* 8 DATA LENGTH*/           
} VM_UART_BITS_PER_CHAR_T;


/************************************************************************************************************
 * DESCRIPTION
 *  VM_UART_STOP_BITS_T is the STOP_BIT type ENUM, user can set STOP_BIT 
 *  to config uart driver 
 * EXAMPLE		                            
 * <code>
 * DCL_HANDLE uart_handle;
 * VM_DCL_MODULE_TYPE_T usr_id;
 * vm_sio_ctrl_dcb_t config;
 * usr_id = vm_dcl_get_ownerid();
 * uart_handle = vm_dcl_open(vm_uart_port1,usr_id);
 * if(VM_DCL_HANDLE_INVALID==uart_handle) return;
 *  config.u4OwenrId = usr_id;
 *	config.rUARTConfig.fgDSRCheck = 0;
 *	config.rUARTConfig.u1DataBits = VM_LEN_8;
 *	config.rUARTConfig.u1FlowControl = VM_FC_NONE;
 *	config.rUARTConfig.u1Parity = VM_PA_NONE;
 *	config.rUARTConfig.u1StopBits = VM_SB_1;
 *	config.rUARTConfig.u4Baud = VM_UART_BAUD_115200;
 *	config.rUARTConfig.ucXoffChar = 0x13;
 *	config.rUARTConfig.ucXonChar = 0x11;
 *	vm_dcl_control(uart_handle,VM_SIO_CMD_SET_DCB_CONFIG,&config);
 * //uart_callback is defined by user 
 * </code>
 **************************************************************************************************************/
typedef enum {
     VM_SB_1=1,   /* 1 STOP BIT*/     
      VM_SB_2,    /* 2 STOP BIT*/         
      VM_SB_1_5   /* 3 STOP BIT*/        
} VM_UART_STOP_BITS_T;


/************************************************************************************************************
 * DESCRIPTION
 *  VM_UART_PARITY_T is the PARITY type ENUM, user can set PARITY 
 *  to config uart driver 
 * EXAMPLE		                            
 * <code>
 * DCL_HANDLE uart_handle;
 * VM_DCL_MODULE_TYPE_T usr_id;
 * vm_sio_ctrl_dcb_t config;
 * usr_id = vm_dcl_get_ownerid();
 * uart_handle = vm_dcl_open(vm_uart_port1,usr_id);
 * if(VM_DCL_HANDLE_INVALID==uart_handle) return;
 *  config.u4OwenrId = usr_id;
 *	config.rUARTConfig.fgDSRCheck = 0;
 *	config.rUARTConfig.u1DataBits = VM_LEN_8;
 *	config.rUARTConfig.u1FlowControl = VM_FC_NONE;
 *	config.rUARTConfig.u1Parity = VM_PA_NONE;
 *	config.rUARTConfig.u1StopBits = VM_SB_1;
 *	config.rUARTConfig.u4Baud = VM_UART_BAUD_115200;
 *	config.rUARTConfig.ucXoffChar = 0x13;
 *	config.rUARTConfig.ucXonChar = 0x11;
 *	vm_dcl_control(uart_handle,VM_SIO_CMD_SET_DCB_CONFIG,&config);
 * //uart_callback is defined by user 
 * </code>
 **************************************************************************************************************/
typedef enum {
     VM_PA_NONE=0, 
      VM_PA_ODD,     
      VM_PA_EVEN,   
      VM_PA_MARK,   
      VM_PA_SPACE    
} VM_UART_PARITY_T;

/************************************************************************************************************
 * DESCRIPTION
 *  VM_UART_FLOW_CTRL_MODE_T is the FLOW CONTROL type ENUM, user can set flow control 
 *  to config uart driver 
 * EXAMPLE		                            
 * <code>
 * DCL_HANDLE uart_handle;
 * VM_DCL_MODULE_TYPE_T usr_id;
 * vm_sio_ctrl_dcb_t config;
 * usr_id = vm_dcl_get_ownerid();
 * uart_handle = vm_dcl_open(vm_uart_port1,usr_id);
 * if(VM_DCL_HANDLE_INVALID==uart_handle) return;
 *  config.u4OwenrId = usr_id;
 *	config.rUARTConfig.fgDSRCheck = 0;
 *	config.rUARTConfig.u1DataBits = VM_LEN_8;
 *	config.rUARTConfig.u1FlowControl = VM_FC_NONE;
 *	config.rUARTConfig.u1Parity = VM_PA_NONE;
 *	config.rUARTConfig.u1StopBits = VM_SB_1;
 *	config.rUARTConfig.u4Baud = VM_UART_BAUD_115200;
 *	config.rUARTConfig.ucXoffChar = 0x13;
 *	config.rUARTConfig.ucXonChar = 0x11;
 *	vm_dcl_control(uart_handle,VM_SIO_CMD_SET_DCB_CONFIG,&config);
 * //uart_callback is defined by user 
 * </code>
 **************************************************************************************************************/
typedef enum {
      VM_FC_NONE=1, /*none flow control*/
      VM_FC_HW,     /*hw flow control*/
      VM_FC_SW      /*sw flow control*/
} VM_UART_FLOW_CTRL_MODE_T;


/************************************************************************************************************
 * DESCRIPTION
 *  vm_sio_config_t is the seriport config  type struct, which is one member of vm_sio_ctrl_dcb_t struct.
 *  user can set the members to config uart driver 
 * EXAMPLE		                            
 * <code>
 * DCL_HANDLE uart_handle;
 * VM_DCL_MODULE_TYPE_T usr_id;
 * vm_sio_ctrl_dcb_t config;
 * usr_id = vm_dcl_get_ownerid();
 * uart_handle = vm_dcl_open(vm_uart_port1,usr_id);
 * if(VM_DCL_HANDLE_INVALID==uart_handle) return;
 *  config.u4OwenrId = usr_id;
 *	config.rUARTConfig.fgDSRCheck = 0;
 *	config.rUARTConfig.u1DataBits = VM_LEN_8;
 *	config.rUARTConfig.u1FlowControl = VM_FC_NONE;
 *	config.rUARTConfig.u1Parity = VM_PA_NONE;
 *	config.rUARTConfig.u1StopBits = VM_SB_1;
 *	config.rUARTConfig.u4Baud = VM_UART_BAUD_115200;
 *	config.rUARTConfig.ucXoffChar = 0x13;
 *	config.rUARTConfig.ucXonChar = 0x11;
 *	vm_dcl_control(uart_handle,VM_SIO_CMD_SET_DCB_CONFIG,&config);
 * //uart_callback is defined by user 
 * </code>
 **************************************************************************************************************/
 typedef struct
{
   VM_UART_BAUDRATE_T      u4Baud;              /*baudrate-->like VM_UART_BAUD_150 or VM_UART_BAUD_1500000*/
   VMUINT8            u1DataBits;              /*data bit--> VM_UART_BITS_PER_CHAR_T*/
   VMUINT8            u1StopBits;              /*stop bit-->VM_UART_STOP_BITS_T*/
   VMUINT8            u1Parity;                /*parity-->VM_UART_PARITY_T*/
   VMUINT8            u1FlowControl;          /*flow control-->VM_UART_FLOW_CTRL_MODE_T*/
   VMUCHAR            ucXonChar;		     /*SW Xon flow control-->if your HW not support SW flowcontrol,please write 0x0*/
   VMUCHAR            ucXoffChar;		    /*SW Xoff flow control-->if your HW not support SW flowcontrol,please write 0x0*/
   VMBOOL             fgDSRCheck;		    /*DSR check-->please write 0x0*/
}vm_sio_config_t;


/************************************************************************************************************
 * DESCRIPTION
 *  vm_sio_config_t is the seriport config  type struct, user can set the members
 *  to config uart driver 
 * EXAMPLE		                            
 * <code>
 * DCL_HANDLE uart_handle;
 * VM_DCL_MODULE_TYPE_T usr_id;
 * vm_sio_ctrl_dcb_t config;
 * usr_id = vm_dcl_get_ownerid();
 * uart_handle = vm_dcl_open(vm_uart_port1,usr_id);
 * if(VM_DCL_HANDLE_INVALID==uart_handle) return;
 *  config.u4OwenrId = usr_id;
 *	config.rUARTConfig.fgDSRCheck = 0;
 *	config.rUARTConfig.u1DataBits = VM_LEN_8;
 *	config.rUARTConfig.u1FlowControl = VM_FC_NONE;
 *	config.rUARTConfig.u1Parity = VM_PA_NONE;
 *	config.rUARTConfig.u1StopBits = VM_SB_1;
 *	config.rUARTConfig.u4Baud = VM_UART_BAUD_115200;
 *	config.rUARTConfig.ucXoffChar = 0x13;
 *	config.rUARTConfig.ucXonChar = 0x11;
 *	vm_dcl_control(uart_handle,VM_SIO_CMD_SET_DCB_CONFIG,&config);
 * //uart_callback is defined by user 
 * </code>
 **************************************************************************************************************/ 
 typedef struct
{
	VMUINT32 u4OwenrId;           /*uart's owner id */
	vm_sio_config_t  rUARTConfig;  /*user config setting */ 
} vm_sio_ctrl_dcb_t;    



/************************************************************************************************************
 * DESCRIPTION
 *  vm_sio_ctrl_open_t is the  UART owner ID
 * EXAMPLE		                            
 * <code>
 * DCL_HANDLE uart_handle;
 * VM_DCL_MODULE_TYPE_T usr_id;
 * vm_sio_ctrl_dcb_t config;
 * usr_id = vm_dcl_get_ownerid();
 * uart_handle = vm_dcl_open(vm_uart_port1,usr_id);
 * if(VM_DCL_HANDLE_INVALID==uart_handle) return;
 **************************************************************************************************************/ 
typedef struct
{
  VMUINT32 u4OwenrId;  /*uart's owner id */
}vm_sio_ctrl_open_t;



/************************************************************************************************************
 * DESCRIPTION
 *  vm_sio_ctrl_put_bytes_t is the struct of putting uart data.
 * EXAMPLE		                            
 * <code>
 * DCL_HANDLE uart_handle;
 * VM_DCL_MODULE_TYPE_T usr_id;
 * vm_sio_ctrl_put_bytes_t data;
 * vm_sio_ctrl_dcb_t config;
 * usr_id = vm_dcl_get_ownerid();
 * uart_handle = vm_dcl_open(vm_uart_port1,usr_id);
 * if(VM_DCL_HANDLE_INVALID==uart_handle) return;
   data.u2Length=2048;
   data.u4OwenrId=usr_id;
   data.puBuffaddr=data_buffer;
 *  vm_dcl_write(uart_handle,(VM_DCL_BUFF*)data_buffer,2048,&writen_len,usr_id);
 **************************************************************************************************************/ 
typedef struct
{
	VMUINT16 u2Length;     /*uart's data length */
	VMUINT32 u4OwenrId;    /*uart's owner id */
	VMUINT16	u2RetSize;   /*uart's sent data size */ 
	VMUINT8* puBuffaddr;    /*uart's buffer address */
}vm_sio_ctrl_put_bytes_t;
  
  
/************************************************************************************************************
 * DESCRIPTION
 *  vm_sio_ctrl_get_bytes_t is the struct of getting uart data.
 * EXAMPLE		                            
 * <code>
 * DCL_HANDLE uart_handle;
 * VM_DCL_MODULE_TYPE_T usr_id;
 * vm_sio_ctrl_put_bytes_t data;
 * vm_sio_ctrl_dcb_t config;
 * usr_id = vm_dcl_get_ownerid();
 * uart_handle = vm_dcl_open(vm_uart_port1,usr_id);
 * if(VM_DCL_HANDLE_INVALID==uart_handle) return;
   data.u2Length=2048;
   data.u4OwenrId=usr_id;
   data.puBuffaddr=data_buffer;
 * vm_dcl_read(uart_handle,(VM_DCL_BUFF*)data_buffer,1024,&returned_len,usr_id);
 **************************************************************************************************************/   
typedef struct
{
	VMUINT16 u2Length;     /*uart's data length */
	VMUINT32 u4OwenrId;    /*uart's owner id */
	VMUINT16	u2RetSize;   /*uart's get data size */ 
	VMUINT8* puBuffaddr;    /*uart's buffer address */
	VMUINT8*  pustatus;    /*uart's  status */  
	
}vm_sio_ctrl_get_bytes_t;   

                                     
#endif                                          
                                                
                                                
                                                
                                                                                                                                              
