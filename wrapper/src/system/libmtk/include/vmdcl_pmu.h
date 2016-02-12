
#ifndef __VM_DCL_PMU_H_STRUCT__
#define __VM_DCL_PMU_H_STRUCT__


/*Define the dev for PMU module. Used in dcl_open*/
typedef enum
{
	VM_DCL_PMU_START = VM_DCL_PMU_GROUP_START,
	VM_DCL_PMU
}VM_DCL_PMU_DEV_T;


/* Enum of VM_LDO/BUCK List */
typedef enum
{
	VM_VA12,				//VM_VA12
	VM_VRTC,				//VM_VRTC
	VM_VMIC,				//VM_VMIC
	VM_VAUDN,				//VM_VAUDN
	VM_VAUDP,				//VM_VAUDP
	VM_VRF28,				//VM_VRF28
	VM_VRF=VM_VRF28,		//VM_VRF
	VM_VTCXO,				//VM_VTCXO
	VM_VA25,				//VM_VA25
	VM_VCAMA,				//VM_VCAMA
	VM_VCAMD,				//VM_VCAMD
	VM_VCAM_IO,				//VM_VCAM_IO
	VM_VCAM_AF,				//VM_VCAM_AF
	VM_VIO28,				//VM_VIO28
	VM_VUSB,				//VM_VUSB
	VM_VBT,					//VM_VBT
	VM_VSIM,				//VM_VSIM
	VM_VSIM1 = VM_VSIM,		//VM_VSIM1
	VM_VSIM2,				//VM_VSIM2
	VM_VIBR,				//VM_VIBR
	VM_VMC,					//VM_VMC
	VM_VMC1,				//VM_VMC1
	VM_VCAMA2,				//VM_VCAMA2
	VM_VCAMD2,				//VM_VCAMD2
	VM_VFM,					//VM_VFM
	VM_VM12,				//VM_VM12
	VM_VM12_1,				//VM_VM12_1
	VM_VM12_2,				//VM_VM12_2
    VM_VM12_INT,			//VM_VM12_INT
	VM_VCORE,				//VM_VCORE
	VM_VCORE2,				//VM_VCORE2
	VM_VIO18,				//VM_VIO18
	VM_VPA_SW,				//VM_VPA_SW
	VM_VPROC,				//VM_VPROC
	VM_VRF18,				//VM_VRF18
	VM_VA,					//VM_VA
	VM_VA28 = VM_VA,		//VM_VA28
	VM_VM,					//VM_VM
	VM_VSF,					//VM_VSF
	VM_VWIFI2V8,			//VM_VWIFI2V8
	VM_VWIFI3V3,			//VM_VWIFI3V3
	VM_V3GTX,				//VM_V3GTX
	VM_V3GRX,				//VM_V3GRX
	VM_VGP,					//VM_VGP
	VM_VGP2,				//VM_VGP2
	VM_VSDIO,				//VM_VSDIO
	VM_VDIG,				//VM_VDIG
	VM_VBUS,				//VM_VBUS
	VM_VA1,					//VM_VA1
	VM_VA2,					//VM_VA2
	VM_VBACKUP,				//VM_VBACKUP
	VM_VM_PMU_LDO_BUCK_MAX	//VM_VM_PMU_LDO_BUCK_MAX
}VM_PMU_LDO_BUCK_LIST_ENUM;


/* Enum of LDO/BUCK List */
typedef enum
{
	VM_VGPIO0,
	VM_VGPIO1,
	VM_VGPIO2,
	VM_VGPIO3,
	VM_VGPIO4,
	VM_VGPIO5,
	VM_VGPIO6,
	VM_VGPIO7,
	VM_VGPIO8,
	VM_VGPIO9,
	VM_VGPIO10,
	VM_VGPIO11,
	VM_VGPIO12,
	VM_VGPIO13,
	VM_VGPIO14,
	VM_VGPIO15,
	VM_VGPIO16,
	VM_VGPIO17,
	VM_VGPIO18,
	VM_VGPIO19,
	VM_VGPIO20,
	VM_VGPIO21,
	VM_VGPIO22,
	VM_VGPIO23,
	VM_VGPIO24,
	VM_VGPIO25,
	VM_VGPIO26,
	VM_VGPIO27,
	VM_VGPIO28,
	VM_VGPIO29,
	VM_VGPIO30,
	VM_VGPIO31,
	VM_VGPIO32,
	VM_VGPIO33,
	VM_VGPIO34,
	VM_VGPIO35,
	VM_VGPIO36,
	VM_VGPIO37,
	VM_VGPIO38,
	VM_VGPIO39,
	VM_VGPIO40,
	VM_VGPIO41,
	VM_VGPIO42,
	VM_VGPIO43,
	VM_VGPIO44,
	VM_VGPIO45,
	VM_VGPIO46,
	VM_VGPIO47,
	VM_VGPIO48,
	VM_VGPIO49,
	VM_VGPIO50,
	VM_VGPIO51,
	VM_VGPIO52,
	VM_VGPIO53,
	VM_VGPIO54,
	VM_VGPIO55,
	VM_VGPIO56,
	VM_VGPIO57,
	VM_VGPIO58,
	VM_VGPIO59,
	VM_VGPIO60,
	VM_VGPIO61,
	VM_VGPIO62,
	VM_VGPIO63,
	VM_VGPIO64,
	VM_VGPIO65,
	VM_VGPIO66,
	VM_VGPIO67,
	VM_VGPIO68,
	VM_VGPIO69,
	VM_VGPIO70,
	VM_VGPIO71,
	VM_VGPIO72,
	VM_VGPIO73,
	VM_VGPIO74,
	VM_VGPIO75,
	VM_VGPIO76,
	VM_VGPIO77,
	VM_VGPIO78,
	VM_VGPIO79,
	VM_VGPIO80,
	VM_VGPIO81,
	VM_VGPIO82,
	VM_VGPIO83,
	VM_VGPIO84,
	VM_VGPIO85,
	VM_VGPIO86,
	VM_VGPIO87,
	VM_VGPIO88,
	VM_VGPIO89,
	VM_VGPIO90,
	VM_VGPIO91,
	VM_VGPIO92,
	VM_VGPIO93,
	VM_VGPIO94,
	VM_VGPIO95,
	VM_VGPIO96,
	VM_VGPIO97,
	VM_VGPIO98,
	VM_VGPIO99,
	VM_VGPIO100,
	PMU_LDO_BUCK_GPIO_POWER_MAX
}VM_PMU_LDO_BUCK_GPIO_POWER_LIST_ENUM;

/* PMU Driver command list */
typedef enum
{
   VM_PMU_CTRL_CMD_LDO_BUCK_SET_EN = 0x2,   /* Command to enable ldo/buck , use structure VM_PMU_CTRL_LDO_BUCK_SET_EN */
   VM_PMI_CTRL_CMD_LDO_BUCK_SET_GPIO_POWER_EN = 0x1006,  /* command open gpio power */
   VM_KPLED_SET_EN = 3000 					/* Command to enable kpled, use structure VM_PMU_CTRL_KPLED_SET_EN */
}VM_DCL_PMU_CTRL_CMD_T;

 
 /*****************************************************************************
 * Description
 *		This struct is for VM_PMU_CTRL_CMD_LDO_BUCK_SET_EN command
 * EXAMPLE		                            
 * <code>
 * //This example explain how to enable the LDO (example VM_VMC)
 *    VM_DCL_HANDLE handle;
 *    VM_PMU_CTRL_LDO_BUCK_SET_EN val;
 *
 *    handle = vm_dcl_open(VM_DCL_PMU, 0);
 *     
 *    val.enable = KAL_TRUE;	// enable ,  KAL_FLASE : disable
 *    val.mod = VM_VMC;		// LDO 
 *     
 *    vm_dcl_control(handle, VM_PMU_CTRL_LDO_BUCK_SET_EN, (void *)&val);
 *    vm_dcl_close(handle);		
 * 
 * </code>
 *****************************************************************************/
typedef struct
{
	VM_PMU_LDO_BUCK_LIST_ENUM		mod;  /* LDO, please reference VM_PMU_LDO_BUCK_LIST_ENUM */
	VMBOOL	enable;						  /* Enalbe or not */
}VM_PMU_CTRL_LDO_BUCK_SET_EN;


 /*****************************************************************************
  * Description
  * 	 This struct is for VM_PMI_CTRL_CMD_LDO_BUCK_SET_GPIO_POWER_EN command
  * EXAMPLE 								 
  * <code>
  * //This example explain how to enable gpio power (example VGPIO40)
  *    VM_DCL_HANDLE handle;
  *    VM_PMI_CTRL_CMD_LDO_BUCK_SET_GPIO_POWER_EN val;
  *
  *    handle = vm_dcl_open(VM_DCL_PMU, 0);
  * 	
  *    val.enable = KAL_TRUE;	 // enable ,  KAL_FLASE : disable
  *    val.mod = VM_VGPIO40;	 // gpio number 
  * 	
  *    vm_dcl_control(handle, VM_PMI_CTRL_CMD_LDO_BUCK_SET_GPIO_POWER_EN, (void *)&val);
  *    vm_dcl_close(handle);	 
  * 
  * </code>
  *****************************************************************************/

 typedef struct
 {
	 VM_PMU_LDO_BUCK_GPIO_POWER_LIST_ENUM		 gpionum;
	 VMBOOL	 enable;
 }PMU_CTRL_LDO_BUCK_SET_GPIO_POWER_EN;


 /*****************************************************************************
  * Description
  *		This struct is for VM_PMU_CTRL_KPLED_SET_EN command.
  * EXAMPLE 								 
  * <code>
  * //This example explain how to enable the LDO (example VM_VMC)
  *    VM_DCL_HANDLE handle;
  *    VM_PMU_CTRL_KPLED_SET_EN val;
  *
  *    handle = vm_dcl_open(VM_DCL_PMU, 0);
  * 	
  *    val.enable = KAL_TRUE;	 // enable ,  KAL_FLASE : disable
  * 	
  *    vm_dcl_control(handle, VM_PMU_CTRL_KPLED_SET_EN, (void *)&val);
  *    vm_dcl_close(handle);	 
  * 
  * </code>
  *****************************************************************************/
 typedef struct
 {
	 VMBOOL	 enable;	/* Enable or not */
 }VM_PMU_CTRL_KPLED_SET_EN;





#endif // #ifndef __VM_DCL_VM_PMU_H_PROTOTYPE__

