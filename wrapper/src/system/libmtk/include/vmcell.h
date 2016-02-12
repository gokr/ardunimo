/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2005
*
*  BY OPENING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
*  THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
*  RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO BUYER ON
*  AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
*  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
*  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
*  NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
*  SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
*  SUPPLIED WITH THE MEDIATEK SOFTWARE, AND BUYER AGREES TO LOOK ONLY TO SUCH
*  THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO
*  NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S
*  SPECIFICATION OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
*
*  BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE
*  LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
*  AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
*  OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY BUYER TO
*  MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE. 
*
*  THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE
*  WITH THE LAWS OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT OF
*  LAWS PRINCIPLES.  ANY DISPUTES, CONTROVERSIES OR CLAIMS ARISING THEREOF AND
*  RELATED THERETO SHALL BE SETTLED BY ARBITRATION IN SAN FRANCISCO, CA, UNDER
*  THE RULES OF THE INTERNATIONAL CHAMBER OF COMMERCE (ICC).
*
*****************************************************************************/

#ifndef VMCELL_SDK_H_
#define VMCELL_SDK_H_

#include "vmsys.h"

#ifdef __cplusplus
extern "C" {
#endif

/*cell info structure*/
typedef struct{
    VMUINT16 arfcn;           /*ARFCN*/
    VMUINT8 bsic;              /*BSIC*/
    VMUINT8 rxlev;            /*Received signal level*/
    VMUINT16 mcc;            /*MCC*/
    VMUINT16 mnc;            /*MNC*/
    VMUINT16 lac;              /*LAC*/
    VMUINT16 ci;                /*CI*/
}vm_cell_info_struct;

/*CELL register state*/
typedef enum{
	VM_CELL_OPEN_REG_ERROR = -2,		/*CELL Info register error*/
	VM_CELL_OPEN_RES_LESS = -1,		/*lack of reource*/
	VM_CELL_OPEN_SUCCESS = 0,			/*open successfully*/
	VM_CELL_OPEN_ALREADY_OPEN = 1	/*already open*/			
} vm_cell_reg_state_enum;

/*****************************************************************************
* FUNCTION
 *    vm_cell_open
 * DESCRIPTION
 *  open CELL ID reource 
 * RETURNS
 *  result of open operation.
 * RETURN VALUES 
 *  VM_CELL_OPEN_SUCCESS : open successfully.
 *  VM_CELL_OPEN_ALREADY_OPEN : already open.
 *  VM_CELL_OPEN_RES_LESS : lack of reource
 *  VM_CELL_OPEN_REG_ERROR : CELL Info register error
 *
*****************************************************************************/
VMINT vm_cell_open(void);

/*****************************************************************************
* FUNCTION
 *    vm_cell_close
 * DESCRIPTION
 *  close CELL ID reource 
 *
*****************************************************************************/
void vm_cell_close(void);

/*****************************************************************************
* FUNCTION
 *    vm_cell_get_cur_cell_info
 * DESCRIPTION
 *  get current cell information.  vm_cell_open() should be invoked before this API, 
 *  or NULL will be returned.
 * RETURNS
 *  the pointer to current cell information or NULL.
 *
*****************************************************************************/
vm_cell_info_struct* vm_cell_get_cur_cell_info(void);

/*****************************************************************************
* FUNCTION
 *    vm_cell_get_nbr_cell_info
 * DESCRIPTION
 *  get neighbor cell information.  vm_cell_open() should be invoked before this API, 
 *  or NULL will be returned.
 * RETURNS
 *  the pointer to neighbor cell information or NULL.
 *
*****************************************************************************/
vm_cell_info_struct** vm_cell_get_nbr_cell_info(void);

/*****************************************************************************
* FUNCTION
 *    vm_cell_get_nbr_num
 * DESCRIPTION
 *  get the number of neighbor cell information.  vm_cell_open() should be invoked before this API, 
 *  or NULL will be returned.
 * RETURNS
 *  the pointer to the number of neighbor cell information or NULL.
 *
*****************************************************************************/
VMINT* vm_cell_get_nbr_num(void);

#ifdef __cplusplus
}
#endif 
#endif /* VMCELL_SDK_H_ */

