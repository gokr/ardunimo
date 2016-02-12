
#ifndef __VM_DCL_SPI_H__
#define __VM_DCL_SPI_H__


/********************USER SHOULD KEEP THIS RULE*************************************************
* 1) Please use port : vm_spi_port1 ( default start from vm_spi_port1 ,and if NEW SPI HW addes,
*     vm_spi_port2 will be added )
* 2) AP SPI works at DMA mode ,so Please SET USER read/write/readwrite BUFFER as NON-Cachable
*     (ex: VM_READ_BUFFER* spi_read_data;
*          VM_WRITE_BUFFER* spi_write_data;	
*          spi_write_data = (VM_WRITE_BUFFER*)vm_malloc_nc(sizeof(VM_WRITE_BUFFER));
*	          spi_read_data = (VM_READ_BUFFER*)vm_malloc_nc(sizeof(VM_READ_BUFFER));)
***************************************************************************************************/
/*****************************************************************************
 * DESCRIPTION
 *  VM_SPI_MAX_PORT_NUM  indecates that this is the max port number which
 *  spi driver support 
 *****************************************************************************/
#define VM_SPI_MAX_PORT_NUM 2


/*****************************************************************************
 * DESCRIPTION
 *   VM_DCL_SPI_DEV_T is the spi type ENUM, user can select one of 
 *  the devices to use
 * EXAMPLE		                            
 * <code>
 *	VM_DCL_HANDLE spi_handle;
 * spi_handle = vm_dcl_open(vm_spi_port1,0);
 * if(VM_DCL_HANDLE_INVALID==spi_handle) return;
 * //Do something with the handle.
 * </code>
 *****************************************************************************/
typedef enum
{
 	vm_spi_port0 = VM_DCL_SPI_GROUP_START,  /* only for start spi 1,USER NOT USED!!!*/ 
    vm_spi_port1                         /*user use from spi 1*/        
 
} VM_DCL_SPI_DEV_T;

/*************************************************************************************************************************************
 *  DESCRIPTION
 * SPI IOCTL code definition.
 * EXAMPLE
 * <code>
 *	VM_DCL_HANDLE spi_handle;
 *  vm_spi_config_para_t conf_data;
 * spi_handle = vm_dcl_open(vm_spi_port1,0);
 * if(VM_DCL_HANDLE_INVALID==spi_handle) return;
 *	conf_data.clk_high_time = 5;
 *	conf_data.clk_low_time = 5;
 *	conf_data.cs_hold_time = 15;
 *	conf_data.cs_idle_time = 15;
 *	conf_data.cs_setup_time= 15;
 *	conf_data.clk_polarity = VM_SPI_CPOL_B0;
 *	conf_data.clk_fmt = VM_SPI_CPHA_B0;
 *  conf_data.rx_endian = VM_SPI_ENDIAN_LITTLE;
 *	conf_data.tx_endian = VM_SPI_ENDIAN_LITTLE;
 *	conf_data.rx_msbf = VM_SPI_MSBF_MSB;
 *	conf_data.tx_msbf = VM_SPI_MSBF_MSB;
 *	vm_dcl_control(spi_handle,VM_SPI_IOCTL_SET_CONFIG_PARA,(void *)&conf_data);
 * //Do something with the handle.
 * </code>
  *************************************************************************************************************************************/
typedef enum
{

    
    VM_SPI_IOCTL_GET_PARAM=0,             /* Get the current SPI configuration parameters.*/
  
    VM_SPI_IOCTL_QUERY_CAPABILITY=1,       /* Get the capability of current SPI hardware.*/

    VM_SPI_IOCTL_QUERY_MODE_SUPPORT=2,       /* Query supported SPI modes.*/

    VM_SPI_IOCTL_QUERY_CLOCK=3,            /* Query SPI base clock.*/

    VM_SPI_IOCTL_SET_MODE=4,              /* Set and configure SPI mode.*/

    VM_SPI_IOCTL_GET_MODE=5,              /* Get SPI mode settings.*/

    VM_SPI_IOCTL_SET_CONFIG_PARA=8,         /* Set SPI driving current.*/
    
    VM_SPI_IOCTL_WRITE_AND_READ=9           /* Set SPI write and read .*/

} VM_SPI_IOCTL_CODE;


/*************************************************************************************************************************************
  *  DESCRIPTION
  * VM_SPI_HAL_MODE indicates that which mode and functions SPI HW supports, user often use DEASSERT or PAUSE mode
  * ULTRA_HIGH  and SLOW_DOWN is little used beacause of these are used to ajust  the spi ratio of EMI bandwith.GET_TICK is to adjust
  * clock timing in order ro device can sample spi master's clock correctly when speed is very high 
  *************************************************************************************************************************************/

typedef enum
{
    /* Deassert mode. SPI CS pin will be pulled low and high for each byte during transmission. */
    VM_SPI_MODE_DEASSERT,
    /* Pause mode. SPI CS pin is pulled low and keeps until specific amount of transfers have been finished. */
    VM_SPI_MODE_PAUSE,
    /* Ultra high mode. Raise DMA priority during DMA transmission. */
    VM_SPI_MODE_ULTRA_HIGH,
    /* Slow down mode. Slow down SPI DMA speed during DMA transmission. */
    VM_SPI_MODE_SLOW_DOWN,
    /* Get tick delay mode. This mode is used to tuning SPI timing. */
    VM_SPI_MODE_GET_TICK
} VM_SPI_HAL_MODE;

/*************************************************************************************************************************************
 *  DESCRIPTION
 * VM_SPI_GET_TICK_E is the ENUM that set GET_TICK_DELAY1 or GET_TICK_DELAY2
 * EXAMPLE
 * <code>
 *	VM_DCL_HANDLE spi_handle;
 *  vm_spi_mode_t spi_data;
 * spi_handle = vm_dcl_open(vm_spi_port1,0);
 * if(VM_DCL_HANDLE_INVALID==spi_handle) return;
 * spi_data.mode=VM_SPI_MODE_GET_TICK;
 * spi_data.bEnable=KAL_TRUE;
 * spi_data.param=VM_SPI_GET_TICK_DELAY1;
 *	vm_dcl_control(spi_handle,VM_SPI_IOCTL_SET_MODE,(void *)&spi_data);
 * //Do something with the handle.
 * </code>
*************************************************************************************************************************************/
typedef enum
{
    /* Delay SCK for one clock. */
    VM_SPI_GET_TICK_DELAY1 = 1,
    /* Delay SCK for two clocks. */
    VM_SPI_GET_TICK_DELAY2 = 2
} VM_SPI_GET_TICK_E;

/*************************************************************************************************************************************
  *  DESCRIPTION
  * VM_SPI_MSBF_E  indecates that SPI transimssion bit order definition
 * EXAMPLE
 * <code>
 *	VM_DCL_HANDLE spi_handle;
 *  vm_spi_config_para_t conf_data;
 * spi_handle = vm_dcl_open(vm_spi_port1,0);
 * if(VM_DCL_HANDLE_INVALID==spi_handle) return;
 *	conf_data.clk_high_time = 5;
 *	conf_data.clk_low_time = 5;
 *	conf_data.cs_hold_time = 15;
 *	conf_data.cs_idle_time = 15;
 *	conf_data.cs_setup_time= 15;
 *	conf_data.clk_polarity = VM_SPI_CPOL_B0;
 *	conf_data.clk_fmt = VM_SPI_CPHA_B0;
 *  conf_data.rx_endian = VM_SPI_ENDIAN_LITTLE;
 *	conf_data.tx_endian = VM_SPI_ENDIAN_LITTLE;
 *	conf_data.rx_msbf = VM_SPI_MSBF_MSB;
 *	conf_data.tx_msbf = VM_SPI_MSBF_MSB;
 *	vm_dcl_control(spi_handle,VM_SPI_IOCTL_SET_CONFIG_PARA,(void *)&conf_data);
 * //Do something with the handle.
 * </code>
  *************************************************************************************************************************************/
typedef enum
{
    /* Transfer LSB first. */
    VM_SPI_MSBF_LSB = 0,
    /* Transfer MSB first. */
    VM_SPI_MSBF_MSB = 1
} VM_SPI_MSBF_E;

/*************************************************************************************************************************************
  *  DESCRIPTION
  * VM_SPI_CPOL_E  indecates that SPI clock polarity definition.
 * EXAMPLE
 * <code>
 *	VM_DCL_HANDLE spi_handle;
 *  vm_spi_config_para_t conf_data;
 * spi_handle = vm_dcl_open(vm_spi_port1,0);
 * if(VM_DCL_HANDLE_INVALID==spi_handle) return;
 *	conf_data.clk_high_time = 5;
 *	conf_data.clk_low_time = 5;
 *	conf_data.cs_hold_time = 15;
 *	conf_data.cs_idle_time = 15;
 *	conf_data.cs_setup_time= 15;
 *	conf_data.clk_polarity = VM_SPI_CPOL_B0;
 *	conf_data.clk_fmt = VM_SPI_CPHA_B0;
 *  conf_data.rx_endian = VM_SPI_ENDIAN_LITTLE;
 *	conf_data.tx_endian = VM_SPI_ENDIAN_LITTLE;
 *	conf_data.rx_msbf = VM_SPI_MSBF_MSB;
 *	conf_data.tx_msbf = VM_SPI_MSBF_MSB;
 *	vm_dcl_control(spi_handle,VM_SPI_IOCTL_SET_CONFIG_PARA,(void *)&conf_data);
 * //Do something with the handle.
 * </code>
  *************************************************************************************************************************************/
typedef enum
{
    /* CPOL = 0. */
    VM_SPI_CPOL_B0 = 0,
    /* CPOL = 1. */
    VM_SPI_CPOL_B1 = 1
}  VM_SPI_CPOL_E;


/*************************************************************************************************************************************
 *  DESCRIPTION
 * VM_SPI_CPHA_E  indecates that SPI clock format definition.
 * EXAMPLE
 * <code>
 *	VM_DCL_HANDLE spi_handle;
 *  vm_spi_config_para_t conf_data;
 * spi_handle = vm_dcl_open(vm_spi_port1,0);
 * if(VM_DCL_HANDLE_INVALID==spi_handle) return;
 *	conf_data.clk_high_time = 5;
 *	conf_data.clk_low_time = 5;
 *	conf_data.cs_hold_time = 15;
 *	conf_data.cs_idle_time = 15;
 *	conf_data.cs_setup_time= 15;
 *	conf_data.clk_polarity = VM_SPI_CPOL_B0;
 *	conf_data.clk_fmt = VM_SPI_CPHA_B0;
 *  conf_data.rx_endian = VM_SPI_ENDIAN_LITTLE;
 *	conf_data.tx_endian = VM_SPI_ENDIAN_LITTLE;
 *	conf_data.rx_msbf = VM_SPI_MSBF_MSB;
 *	conf_data.tx_msbf = VM_SPI_MSBF_MSB;
 *	vm_dcl_control(spi_handle,VM_SPI_IOCTL_SET_CONFIG_PARA,(void *)&conf_data);
 * //Do something with the handle.
 * </code>
  *************************************************************************************************************************************/
typedef enum
{
    /* CPHA = 0. */
     VM_SPI_CPHA_B0 = 0,
    /* CPHA = 1. */
    VM_SPI_CPHA_B1 = 1
} VM_SPI_CPHA_E;


/*************************************************************************************************************************************
 *  DESCRIPTION
 * VM_SPI_ENDIAN_E  indecates that SPI data transfer byte order definition.
 * EXAMPLE
 * <code>
 *	VM_DCL_HANDLE spi_handle;
 *  vm_spi_config_para_t conf_data;
 * spi_handle = vm_dcl_open(vm_spi_port1,0);
 * if(VM_DCL_HANDLE_INVALID==spi_handle) return;
 *	conf_data.clk_high_time = 5;
 *	conf_data.clk_low_time = 5;
 *	conf_data.cs_hold_time = 15;
 *	conf_data.cs_idle_time = 15;
 *	conf_data.cs_setup_time= 15;
 *	conf_data.clk_polarity = VM_SPI_CPOL_B0;
 *	conf_data.clk_fmt = VM_SPI_CPHA_B0;
 *  conf_data.rx_endian = VM_SPI_ENDIAN_LITTLE;
 *	conf_data.tx_endian = VM_SPI_ENDIAN_LITTLE;
 *	conf_data.rx_msbf = VM_SPI_MSBF_MSB;
 *	conf_data.tx_msbf = VM_SPI_MSBF_MSB;
 *	vm_dcl_control(spi_handle,VM_SPI_IOCTL_SET_CONFIG_PARA,(void *)&conf_data);
 * //Do something with the handle.
 * </code>
  *************************************************************************************************************************************/

typedef enum
{
    /* Use little endian. */
     VM_SPI_ENDIAN_LITTLE = 0,
    /* Use big endian. */
     VM_SPI_ENDIAN_BIG = 1
} VM_SPI_ENDIAN_E;



/*************************************************************************************************************************************
 *  DESCRIPTION
 * vm_spi_config_para_t indecates that SPI configuration parameters.
 * EXAMPLE
 * <code>
 *	VM_DCL_HANDLE spi_handle;
 *  vm_spi_config_para_t conf_data;
 * spi_handle = vm_dcl_open(vm_spi_port1,0);
 * if(VM_DCL_HANDLE_INVALID==spi_handle) return;
 *	conf_data.clk_high_time = 5;
 *	conf_data.clk_low_time = 5;
 *	conf_data.cs_hold_time = 15;
 *	conf_data.cs_idle_time = 15;
 *	conf_data.cs_setup_time= 15;
 *	conf_data.clk_polarity = VM_SPI_CPOL_B0;
 *	conf_data.clk_fmt = VM_SPI_CPHA_B0;
 *  conf_data.rx_endian = VM_SPI_ENDIAN_LITTLE;
 *	conf_data.tx_endian = VM_SPI_ENDIAN_LITTLE;
 *	conf_data.rx_msbf = VM_SPI_MSBF_MSB;
 *	conf_data.tx_msbf = VM_SPI_MSBF_MSB;
 *	vm_dcl_control(spi_handle,VM_SPI_IOCTL_SET_CONFIG_PARA,(void *)&conf_data);
 * //Do something with the handle.
 * </code>
  *************************************************************************************************************************************/
typedef struct
{
    /* CS setup time. Unit in count of SPI base clock. Range(0-255).
       The chip select setup time = (cs_setup_time+1)*CLK_PERIOD, where CLK_PERIOD is the cycle time of the clock the SPI engine adopts. */
    VMUINT32 cs_setup_time;
    /* CS hold time. Unit in count of SPI base clock. Range(0-255).
       The chip select hold time = (cs_hold_time+1)*CLK_PERIOD. */
    VMUINT32 cs_hold_time;
    /* CS idle time. Unit in count of SPI base clock. Range(0-255).
       The chip select idle time between consecutive transaction = (cs_idle_time+1)*CLK_PERIOD. */
    VMUINT32 cs_idle_time;
    /* SCK clock low time. Unit in count of SPI base clock. Range(0-255).
       The SCK clock low time = (clk_low_time+1)*CLK_PERIOD. */
    VMUINT32 clk_low_time;
    /* SCK clock high time. Unit in count of SPI base clock. Range(0-255).
       The SCK clock high time = (clk_high_time+1)*CLK_PERIOD. */
    VMUINT32 clk_high_time;
    /* Bit order setting for SPI output. */
    VM_SPI_MSBF_E tx_msbf;
    /* Bit order setting for SPI input. */
    VM_SPI_MSBF_E rx_msbf;
    /* Byte order setting for SPI output. */
    VM_SPI_ENDIAN_E tx_endian;
    /* Byte order setting for SPI input. */
    VM_SPI_ENDIAN_E rx_endian;
    /* SPI clock polarity. */
    VM_SPI_CPOL_E clk_polarity;
    /* SPI clock format. */
    VM_SPI_CPHA_E clk_fmt;
} vm_spi_config_para_t;

/*************************************************************************************************************************************
 *  DESCRIPTION
 * VM_SPI_CTRL_WRITE_AND_READE_T indecates that SPI  write and read operation.
 * EXAMPLE
 * <code>
 *	VM_DCL_HANDLE spi_handle;
 *  vm_spi_config_para_t conf_data;
 * spi_handle = vm_dcl_open(vm_spi_port0,0);
 * if(VM_DCL_HANDLE_INVALID==spi_handle) return;
 *	conf_data.clk_high_time = 5;
 *	conf_data.clk_low_time = 5;
 *	conf_data.cs_hold_time = 15;
 *	conf_data.cs_idle_time = 15;
 *	conf_data.cs_setup_time= 15;
 *	conf_data.clk_polarity = VM_SPI_CPOL_B0;
 *	conf_data.clk_fmt = VM_SPI_CPHA_B0;
 *  conf_data.rx_endian = VM_SPI_ENDIAN_LITTLE;
 *	conf_data.tx_endian = VM_SPI_ENDIAN_LITTLE;
 *	conf_data.rx_msbf = VM_SPI_MSBF_MSB;
 *	conf_data.tx_msbf = VM_SPI_MSBF_MSB;
 *  VM_SPI_CTRL_WRITE_AND_READE_T  write_and_read;
 *  write_and_read.pu1InData=in_buff;
 *  write_and_read.u4DataLen=10;
 *  write_and_read.pu1OutData=out_buff;
 *  write_and_read.uCount=1; 
 *	vm_dcl_control(spi_handle,VM_SPI_IOCTL_SET_CONFIG_PARA,(void *)&conf_data);
 *	vm_dcl_control(spi_handle,VM_SPI_IOCTL_WRITE_AND_READ,(void *)&write_and_read);
 * //Do something with the handle.
 * </code>
  *************************************************************************************************************************************/
typedef struct
{
   VMUINT8 *pu1InData; /* Pointer to the read data */
   VMUINT32 u4DataLen; /* Read data length */
   VMUINT8 *pu1OutData; /* Pointer to the write data */
   VMUINT32 uCount; /* Read data length */
}VM_SPI_CTRL_WRITE_AND_READE_T;

/*************************************************************************************************************************************
 *  DESCRIPTION
 * vm_spi_capabilty_t indecates that SPI 's Capabilty which user can query,This structure is 
 * used as the parameter of VM_SPI_IOCTL_QUERY_CAPABILITY.
 * EXAMPLE
 * <code>
 *	VM_DCL_HANDLE spi_handle;
 *  vm_spi_capabilty_t spi_data;
 * spi_handle = vm_dcl_open(vm_spi_port1,0);
 * if(VM_DCL_HANDLE_INVALID==spi_handle) return;
 *	vm_dcl_control(spi_handle,VM_SPI_IOCTL_QUERY_CAPABILITY,(void *)&spi_data);
 * //Do something with the handle.
 * </code>
  *************************************************************************************************************************************/
typedef struct
{
    /* Minimum value for cs setup time. */
     VMUINT32 cs_setup_time_min;
    /* Maximum value for cs setup time. */
     VMUINT32 cs_setup_time_max;
    /* Minimum value for cs hold time. */
     VMUINT32 cs_hold_time_min;
    /* Maximum value for cs hold time. */
     VMUINT32 cs_hold_time_max;
    /* Minimum value for cs idle time. */
     VMUINT32 cs_idle_time_min;
    /* Maximum value for cs idle time. */
     VMUINT32 cs_idle_time_max;
    /* Minimum value for clock low time. */
     VMUINT32  clk_low_time_min;
    /* Maximum value for clock low time. */
     VMUINT32  clk_low_time_max;
    /* Minimum value for clock high time. */
     VMUINT32  clk_high_time_min;
    /* Maximum value for clock high time. */
     VMUINT32  clk_high_time_max;
    /* Minimum value for transfer length. */
     VMUINT32  transfer_length_min;
    /* Maximum value for transfer length. */
     VMUINT32  transfer_length_max;
    /* Minimum value for transfer count. */
     VMUINT32  transfer_count_min;
    /* Maximum value for transfer count. */
     VMUINT32  transfer_count_max;
    /* Minimum value for slow down threshold. */
     VMUINT32  slow_down_thresh_min;
    /* Maximum value for slow down threshold. */
     VMUINT32  slow_down_thresh_max;
    /* Minimum value for ultra high threshold. */
     VMUINT32  ultra_high_thresh_min;
    /* Maximum value for ultra high threshold. */
     VMUINT32  ultra_high_thresh_max;
    /* Minimum value for driving current. */
     VMUINT32  driving_current_min;
    /* Maximum value for driving current. */
     VMUINT32  driving_current_max;
} vm_spi_capabilty_t;


/*************************************************************************************************************************************
 *  DESCRIPTION
 * vm_spi_query_mode_t indecates that user can check which mode can SPI  support, This structure is used as the parameter 
 * of VM_SPI_IOCTL_QUERY_MODE_SUPPORT.
 * EXAMPLE
 * <code>
 *	VM_DCL_HANDLE spi_handle;
 *  vm_spi_query_mode_t spi_data;
 * spi_handle = vm_dcl_open(vm_spi_port1,0);
 * if(VM_DCL_HANDLE_INVALID==spi_handle) return;
 * spi_data.mode=VM_SPI_MODE_PAUSE;
 *	vm_dcl_control(spi_handle,VM_SPI_IOCTL_QUERY_MODE_SUPPORT,(void *)&spi_data);
 * //Do something with the handle.
 * </code>
  *************************************************************************************************************************************/
typedef struct
{
    /* [IN] Specify a SPI mode. */
    VM_SPI_HAL_MODE mode;
    /* [OUT] Return whether the specific mode is supported. */
    VMBOOL bSupport;
} vm_spi_query_mode_t;


/*************************************************************************************************************************************
 *  DESCRIPTION
 * vm_spi_query_mode_t indecates that user can check  SPI 's clock, This structure is used as the parameter of VM_SPI_IOCTL_QUERY_CLOCK.
 *  It contains the clock frequency which is used to calculate SPI timing parameters.
 * EXAMPLE
 * <code>
 *	VM_DCL_HANDLE spi_handle;
 *  vm_spi_query_clock_t spi_data;
 * spi_handle = vm_dcl_open(vm_spi_port1,0);
 * if(VM_DCL_HANDLE_INVALID==spi_handle) return;
 *	vm_dcl_control(spi_handle,VM_SPI_IOCTL_QUERY_CLOCK,(void *)&spi_data);
 * //Do something with the handle.
 * </code>
  *************************************************************************************************************************************/
typedef struct
{
    /* [OUT] SPI base clock. Unit in MHz. */
    VMUINT32 clock;
} vm_spi_query_clock_t;



/*************************************************************************************************************************************
 *  DESCRIPTION
 * vm_spi_mode_t indecates that user can set/get  SPI 's mode , This structure is used as the parameter of
 * VM_SPI_IOCTL_SET_MODE and VM_SPI_IOCTL_GET_MODE.
 * EXAMPLE
 * <code>
 *	VM_DCL_HANDLE spi_handle;
 *  vm_spi_mode_t spi_data;
 * spi_handle = vm_dcl_open(vm_spi_port1,0);
 * if(VM_DCL_HANDLE_INVALID==spi_handle) return;
 	spi_data.mode = SPI_MODE_DEASSERT;
	spi_data.bEnable = KAL_TRUE;
 *	vm_dcl_control(spi_handle,SPI_IOCTL_SET_MODE,(void *)&spi_data);
 * //Do something with the handle.
 * </code>
  *************************************************************************************************************************************/

typedef struct
{
    /* [IN] Specify a SPI mode. */
    VM_SPI_HAL_MODE mode;
    /* [IN/OUT] Specify whether the mode is enabled.
       For SPI_IOCTL_SET_MODE, it is an input parameter.
       For SPI_IOCTL_GET_MODE, it is an output parameter.
    */
    VMBOOL bEnable;
    /* [IN/OUT] The parameter for the specific mode.
       The meaning of this parameter depends on the mode to be set/get.
    */
    VMUINT32 Param;
} vm_spi_mode_t;


/*************************************************************************************************************************************
 *  DESCRIPTION
 *  spi read function and spi write function 
 * EXAMPLE
 *<code>
 *	VM_DCL_HANDLE spi_handle;
 *  vm_spi_config_para_t conf_data;
 *  vm_spi_mode_t  spi_data;
 *	VMUINT8 write_buff[3] = {0};
 *	VMUINT32 wrten_len;
 *	VMUINT8 read_buff[3] = {0};
 *	VMUINT32 read_len;
 * spi_handle = vm_dcl_open(vm_spi_port1,0);
 * if(VM_DCL_HANDLE_INVALID==spi_handle) return;
 *	conf_data.clk_high_time = 5;
 *	conf_data.clk_low_time = 5;
 *	conf_data.cs_hold_time = 15;
 *	conf_data.cs_idle_time = 15;
 *	conf_data.cs_setup_time= 15;
 *	conf_data.clk_polarity = VM_SPI_CPOL_B0;
 *	conf_data.clk_fmt = VM_SPI_CPHA_B0;
 *  conf_data.rx_endian = VM_SPI_ENDIAN_LITTLE;
 *	conf_data.tx_endian = VM_SPI_ENDIAN_LITTLE;
 *	conf_data.rx_msbf = VM_SPI_MSBF_MSB;
 *	conf_data.tx_msbf = VM_SPI_MSBF_MSB;
 *	vm_dcl_control(spi_handle,VM_SPI_IOCTL_SET_CONFIG_PARA,(void *)&conf_data);
 *	spi_data.mode = SPI_MODE_DEASSERT;
 *	spi_data.bEnable = KAL_FALSE;
 *	vm_dcl_control(spi_handle,SPI_IOCTL_SET_MODE,(void *)&spi_data);
 *  vm_dcl_write(spi_handle,write_buff,3,&wrten_len,(VMUINT32)0);
 *  vm_dcl_read(spi_handle,read_buffer,3,&returned_len,(VMUINT32)0);
 * //Do something with the handle.
 * </code>
  *************************************************************************************************************************************/
#endif
