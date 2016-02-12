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
#ifndef VMSIM_SDK_H_
#define VMSIM_SDK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "vmsys.h"

/* Operator */
typedef enum
{
    NO_SIM_CARD = 0,    /* No SIM card. */
    UNKOWN_OPERATOR,    /* Unknown operator. */
    CMCC,               /* China Mobile. */
    UNICOM,             /* China Unicom. */
    CNC,                /* China Netcom. */
    CNTELCOM,           /* China Telecom. */
    ALL                 /* All the operator. */
} operator_t;

/* The return value of vm_get_sim_card_status(). */
typedef enum
{
    VM_SIM_STATE_ERROR = -1,    /* Get failed. */
    VM_SIM_STATE_VACANT = 0,    /* No SIM card or the SIM card not work. */
    VM_SIM_STATE_WORKING = 1    /* The SIM card is working. */
} vm_sim_state_t;

typedef void (*vm_sim_get_iccid_cb)(VMCHAR* iccid, void* user_data);

#define VM_SIM_NO 0     /* No SIM card */
#define VM_SIM_SIM1 1   /* SIM card 1 */
#define VM_SIM_SIM2 2   /* SIM card 2 */
#define VM_SIM_SIM3 3   /* SIM card 3 */
#define VM_SIM_SIM4 4   /* SIM card 4 */

/*****************************************************************************
 * FUNCTION
 *  vm_get_operator
 * DESCRIPTION
 *  Get the active operator.
 * RETURNS
 *  The operator code.
 * RETURN VALUES
 *  NO_SIM_CARD : No SIM card.
 *  UNKOWN_OPERATOR : Unknown operator.
 *  CMCC : China Mobile.
 *  UNICOM : China Unicom.
 *  CNC : China Netcom.
 *  CNTELCOM : China Telecom.
 *****************************************************************************/
operator_t vm_get_operator(void);

/*****************************************************************************
 * FUNCTION
 *  vm_has_sim_card
 * DESCRIPTION
 *  To query whether the SIM is available or not.
 * RETURNS
 *  TRUE if any SIM is available.
 * RETURN VALUES
 *  TRUE : A SIM available.
 *  FALSE : No SIM available.
 *****************************************************************************/
VMINT vm_has_sim_card(void);

/*****************************************************************************
 * FUNCTION
 *  vm_get_imei
 * DESCRIPTION
 *  Get the IMEI of the phone. If the phone support dual card, it will get the IMEI of the selected SIM card.
 * RETURNS
 *  IMEI string for the phone in ASCII format.
 * RETURN VALUES
 *  NULL : The request of IMEI is in progress, please try again later.
 *****************************************************************************/
VMSTR vm_get_imei(void);

/*****************************************************************************
 * FUNCTION
 *  vm_get_imsi
 * DESCRIPTION
 *  Get the IMSI(have 16 numbers with a redundant 9 at begin) of selected SIM card.
 * RETURNS
 *  IMSI string of the selected SIM card.
 * RETURN VALUES
 *  NULL : The request of IMSI is in progress, please try again later.
 *****************************************************************************/
VMSTR vm_get_imsi(void);

/*****************************************************************************
 * FUNCTION
 *  vm_sim_card_count
 * DESCRIPTION
 *  Get the number of SIM cards.
 * RETURNS
 *  The number of SIM cards.
 * RETURN VALUES
 *  99 : Flight mode.
 *  VM_SIM_NO : No SIM.
 *  1 : One SIM card.
 *  2 : Two SIM card.
 *****************************************************************************/
VMINT vm_sim_card_count(void);

/*****************************************************************************
 * FUNCTION
 *  vm_set_active_sim_card
 * DESCRIPTION
 *  Set active SIM card.
 * PARAMETERS
 *  card_id : [IN] Index of SIM card, 1-SIM1, 2-SIM2.
 * RETURN VALUES
 *  TRUE : If successful.
 *  FALSE : If failed.
 *****************************************************************************/
VMINT vm_set_active_sim_card(VMINT card_id);

/*****************************************************************************
 * FUNCTION
 *  vm_get_sim_card_status
 * DESCRIPTION
 *  Get the status of the given SIM card.
 * PARAMETERS
 *  card_id : [IN] Index of SIM card, 1-SIM1, 2-SIM2.
 * RETURNS
 *  The status of the given SIM card.
 * RETURN VALUES
 *  VM_SIM_STATE_ERROR : Get failed.
 *  VM_SIM_STATE_VACANT : No SIM card or the SIM card not work.
 *  VM_SIM_STATE_WORKING : The given SIM card is working.
 *****************************************************************************/
vm_sim_state_t vm_get_sim_card_status(VMINT card_id);

/* The maximum length of operator code */
#define VM_MAX_OPERATOR_CODE_SIZE         (7)

/*****************************************************************************
 * FUNCTION
 *  vm_query_operator_code
 * DESCRIPTION
 *  Get the operator code.
 * PARAMETERS
 *  buffer : [OUT] Buffer stores operator code.
 *  buffer_size : [IN] Size of the buffer.
 * RETURNS
 *  The error code of the operation.
 * RETURN VALUES
 *  0 : If successful.
 *  Other error code: If unsuccessful.
 *****************************************************************************/
VMINT vm_query_operator_code(VMCHAR *buffer, VMUINT buffer_size);

/*****************************************************************************
 * FUNCTION
 *  vm_sim_get_iccid
 * DESCRIPTION
 *  Get the iccid of sim card.
 * PARAMETERS
 *  sim : [IN] which sim card :1,2,3,4....
 *  callback : [IN] callback function.
 *  iccid : [IN] buff to receive iccid
 *  buff_len : [IN] buff length
 *  user_data : [IN] user data in callback.
 * RETURNS
 *  The error code of the operation.
 * RETURN VALUES
 *  0 : If successful.
 *  Other error code: If unsuccessful.
 *****************************************************************************/
VMINT vm_sim_get_iccid(VMINT sim, vm_sim_get_iccid_cb callback, VMCHAR* iccid, VMINT buff_len, void* user_data);

/*****************************************************************************
 * FUNCTION
 *  vm_sim_get_active_sim_card
 * DESCRIPTION
 *  Get the active sim card.
 * PARAMETERS
 *
 * RETURNS
 *  sim card 1,2,3,4...
 * RETURN VALUES
 *  0 : no active sim card
 *****************************************************************************/
VMINT vm_sim_get_active_sim_card(void);

/*****************************************************************************
 * FUNCTION
 *  vm_sim_max_card_count
 * DESCRIPTION
 *  Get the max card phone support
 * PARAMETERS
 *
 * RETURNS
 *  1,2,3,4...
 * RETURN VALUES
 *  
 *****************************************************************************/
VMINT vm_sim_max_card_count(void);

/*****************************************************************************
 * FUNCTION
 *  vm_sim_get_prefer_sim_card
 * DESCRIPTION
 *  Get the user prefer sim card
 * PARAMETERS
 *
 * RETURNS
 *  1,2,3,4...
 * RETURN VALUES
 *  
 *****************************************************************************/
VMINT vm_sim_get_prefer_sim_card(void);

/*****************************************************************************
 * FUNCTION
 *  vm_get_imei
 * DESCRIPTION
 *  Get the IMEI of the phone. 
 * PARAMETERS
 *  sim : [IN] which sim card :1,2,3,4.... 
 * RETURNS
 *  IMEI string for the phone in ASCII format.
 * RETURN VALUES
 *  NULL : The request of IMEI is in progress, please try again later.
 *****************************************************************************/
VMSTR vm_get_imei_ext(VMINT sim);


/* NEW */
/*****************************************************************************
 * FUNCTION
 *  vm_sim_get_imei
 * DESCRIPTION
 *  Get the IMEI of the phone. If the phone support dual card, it will get the IMEI of the selected SIM card.
 * RETURNS
 *  IMEI string for the phone in ASCII format.
 * RETURN VALUES
 *  NULL : The request of IMEI is in progress, please try again later.
 *****************************************************************************/
VMSTR vm_sim_get_imei(void);
/*****************************************************************************
 * FUNCTION
 *  vm_get_imsi
 * DESCRIPTION
 *  Get the IMSI(have 16 numbers with a redundant 9 at begin) of selected SIM card.
 * RETURNS
 *  IMSI string of the selected SIM card.
 * RETURN VALUES
 *  NULL : The request of IMSI is in progress, please try again later.
 *****************************************************************************/
VMSTR vm_sim_get_imsi(void);

/*****************************************************************************
 * FUNCTION
 *  vm_gsm_sim_get_imsi_ext
 * DESCRIPTION
 *  Get the IMSI(have 15 numbers) of selected SIM card.
 * RETURNS
 *  IMSI string of the selected SIM card.
 * RETURN VALUES
 *  NULL : The request of IMSI is in progress, please try again later.
 *****************************************************************************/
VMSTR vm_gsm_sim_get_imsi_ext(void);

/*****************************************************************************
 * FUNCTION
 *  vm_sim_get_imei_ext
 * DESCRIPTION
 *  Get the IMEI of the phone. 
 * PARAMETERS
 *  sim : [IN] which sim card :1,2,3,4.... 
 * RETURNS
 *  IMEI string for the phone in ASCII format.
 * RETURN VALUES
 *  NULL : The request of IMEI is in progress, please try again later.
 *****************************************************************************/
VMSTR vm_sim_get_imei_ext(VMINT sim);

/*****************************************************************************
 * FUNCTION
 *  vm_sim_get_operator
 * DESCRIPTION
 *  Get the active operator.
 * RETURNS
 *  The operator code.
 * RETURN VALUES
 *  NO_SIM_CARD : No SIM card.
 *  UNKOWN_OPERATOR : Unknown operator.
 *  CMCC : China Mobile.
 *  UNICOM : China Unicom.
 *  CNC : China Netcom.
 *  CNTELCOM : China Telecom.
 *****************************************************************************/
operator_t vm_sim_get_operator(void);

/*****************************************************************************
 * FUNCTION
 *  vm_get_sim_card_status
 * DESCRIPTION
 *  Get the status of the given SIM card.
 * PARAMETERS
 *  card_id : [IN] Index of SIM card, 1-SIM1, 2-SIM2.
 * RETURNS
 *  The status of the given SIM card.
 * RETURN VALUES
 *  VM_SIM_STATE_ERROR : Get failed.
 *  VM_SIM_STATE_VACANT : No SIM card or the SIM card not work.
 *  VM_SIM_STATE_WORKING : The given SIM card is working.
 *****************************************************************************/
vm_sim_state_t vm_sim_get_card_status(VMINT sim);

/*****************************************************************************
 * FUNCTION
 *  vm_has_sim_card
 * DESCRIPTION
 *  To query whether the SIM is available or not.
 * RETURNS
 *  TRUE if any SIM is available.
 * RETURN VALUES
 *  TRUE : A SIM available.
 *  FALSE : No SIM available.
 *****************************************************************************/
VMBOOL vm_sim_has_card(void);
/*****************************************************************************
 * FUNCTION
 *  vm_query_operator_code
 * DESCRIPTION
 *  Get the operator code.
 * PARAMETERS
 *  buffer : [OUT] Buffer stores operator code.
 *  buffer_size : [IN] Size of the buffer.
 * RETURNS
 *  The error code of the operation.
 * RETURN VALUES
 *  0 : If successful.
 *  Other error code: If unsuccessful.
 *****************************************************************************/
VMINT vm_sim_query_operator_code(VMCHAR* buffer, VMUINT buffer_size);
/*****************************************************************************
 * FUNCTION
 *  vm_sim_get_active_sim_card
 * DESCRIPTION
 *  Get the active sim card.
 * PARAMETERS
 *
 * RETURNS
 *  sim card 1,2,3,4...
 * RETURN VALUES
 *  0 : no active sim card
 *****************************************************************************/
VMBOOL vm_sim_set_active_card(VMINT sim);

#define VM_MAX_PLMN_LEN 6
/*****************************************************************************
 * FUNCTION
 *  vm_sim_get_home_plmn
 * DESCRIPTION
 *  Get the SIM PLMN.
 * PARAMETERS
 *  sim : [IN] Index of SIM card, 1-SIM1, 2-SIM2.
 *  buffer : [OUT] Buffer stores operator code. The size shall be
 *                             (VM_MAX_PLMN_LEN + 1) at minimum.
 *  buffer_size : [IN] Size of the buffer. It shall be >=
 *                             (VM_MAX_PLMN_LEN + 1)
 * RETURNS
 *  The error code of the operation.
 * RETURN VALUES
 *  0 : If successful.
 *  Other error code: If unsuccessful.
 *****************************************************************************/
VMINT vm_sim_get_home_plmn(VMINT sim, VMCHAR* buffer, VMUINT buffer_size);


/*****************************************************************************
 * FUNCTION
 *  vm_nw_info_get_nw_plmn
 * DESCRIPTION
 *  Get network PLMN.
 * PARAMETERS
 *  sim                 : [IN] Which protocol layer of SIM
 *  buffer     : [OUT] PLMN buffer to be filled in. The size shall be
 *                             (VM_MAX_PLMN_LEN + 1) at minimum.
 *  buffer_size         : [IN] The size of out_plmn_buffer[]. It shall be >=
 *                             (VM_MAX_PLMN_LEN + 1).
 * RETURN VALUES
 *  0    : If returned PLMN is valid.
 *  else   : If PLMN is not available; for example, no service state.
 *****************************************************************************/
VMINT vm_nw_info_get_nw_plmn(VMINT sim, VMCHAR* buffer, VMUINT buffer_size);
#ifdef __cplusplus
}
#endif 

#endif /* VMSIM_H_ */ 

