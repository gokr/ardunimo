/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2006
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
#ifndef VM_BTSPP_SDK_H
#define VM_BTSPP_SDK_H


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "vmsys.h"


/*spp connect type*/
typedef enum{
	VM_SRV_SPP_CONNECT_WITH_SCO = 0x01, /* connect with SOC */
	VM_SRV_SPP_CONNECT_WITHOUT_SCO = 0x02 /* connect without SOC */
}vm_srv_spp_connect_type;

/*spp return error type*/
typedef enum
{
    VM_BT_SPP_ERR_LOGICAL = -5, /* error in logical */
    VM_BT_SPP_ERR_BAD_PARAM, /* error in bad param */
    VM_BT_SPP_ERR_NO_RESOURCE, /* error in resource */
    VM_BT_SPP_ERR_NOT_SUPPORT, /* error in support */
    VM_BT_SPP_ERR_NO_AUTHORIZATION, /* error in authorization */
    VM_BT_SPP_ERR_SUCCESS = 0 /* no error */
}vm_btspp_error_t;

/*spp security level*/
typedef enum{
	VM_SRV_SPP_SEC_NAN = 0x00, /* security NAN */
	VM_SRV_SPP_SEC_AUTHENTICATION = 0x01, /* security level */
	VM_SRV_SPP_SEC_AUTHORIZATION = 0x04, /* security level */
	VM_SRV_SPP_SEC_ENCRYPTION = 0x10, /* security level */
	VM_SRV_SPP_SEC_ALL = 0xff /*  */
}vm_srv_spp_security_level;

/*spp srv for app event enum*/
typedef enum{
	VM_SRV_SPP_EVENT_START = 0x0001, /* spp event start */
	VM_SRV_SPP_EVENT_BIND_FAIL = 0x0002, /* spp event bind fail */
	VM_SRV_SPP_EVENT_AUTHORIZE = 0x0004, /* spp event authorize */
	VM_SRV_SPP_EVENT_CONNECT = 0x0008, /* spp event connect */
	VM_SRV_SPP_EVENT_SCO_CONNECT = 0x0010, /* spp event soc connect */
	VM_SRV_SPP_EVENT_READY_TO_WRITE = 0x0020, /* spp event ready to write */
	VM_SRV_SPP_EVENT_READY_TO_READ = 0x0040, /* spp event ready to read */
	VM_SRV_SPP_EVENT_DISCONNECT = 0x0080, /* spp event disconnect */
	VM_SRV_SPP_EVENT_SCO_DISCONNECT = 0x0100, /* spp event soc disconnect */
	VM_SRV_SPP_EVENT_END
}vm_srv_spp_event_enum;

/*spp srv for app event structure */
typedef struct{
    VMINT res_hd;                 /* res handle*/
    void * user_data;            /* user data */
	VMINT ret;                  /* result (bool) */
	VMINT conn_id;          /* connection id */
}vm_srv_spp_event_cntx;


#ifndef vm_bt_cm_bt_addr
#define vm_bt_cm_bt_addr
typedef struct _vm_srv_bt_cm_bt_addr vm_srv_bt_cm_bt_addr;
#endif

/*****************************************************************************
 * FUNCTION
 *  vm_btspp_get_min_buf_size
 * DESCRIPTION
 *  get spp minmal buf, return the minmal buf for tx and rx
 * PARAMETERS
 * void
 * RETURNS
 *  VMINT : failure if less than 0, else buf size
 *****************************************************************************/
VMINT vm_btspp_get_min_buf_size(void);

/*****************************************************************************
 * FUNCTION
 *  vm_btspp_open
 * DESCRIPTION
 *  open btspp, return the resource handle if success
 * PARAMETERS
 * void
 * RETURNS
 *  VMINT : failure if less than 0, else successful
 *****************************************************************************/
VMINT vm_btspp_open(VMUINT evt_mask, void (*callback)(VMUINT evt, void * param, void * user_data), void * user_data);

/*****************************************************************************
 * FUNCTION
 *  vm_btspp_distory
 * DESCRIPTION
 *  This function is for distorying a spp resource
 * PARAMETERS
 *  res_hd [IN]: res handler 
 * RETURNS
 *  VMINT : failure if less than 0, else successful
 *****************************************************************************/
VMINT vm_btspp_close(VMINT res_hd);

/*****************************************************************************
 * FUNCTION
 *  vm_btspp_disconnect
 * DESCRIPTION
 *  This function is for app disconnect a connect
 * PARAMETERS
 *  conn_id [IN]:          connnect id
 * RETURNS
 *  VMINT : failure if less than 0, else successful
 *****************************************************************************/
VMINT vm_btspp_disconnect(VMINT conn_id);

/*****************************************************************************
 * FUNCTION
 *  vm_btspp_write
 * DESCRIPTION
 *  This function is for app write data
 * PARAMETERS
 *  conn_id [IN]:          connect id 
 *  buf [IN]:           data buf want to transfer
 *  size [IN]:          the size of data want to transfer
 * RETURNS
 *  VMINT : failure if less than 0, see vm_btspp_error_t, 
 * else return the size of data transferred successfully
 *****************************************************************************/
VMINT vm_btspp_write(VMUINT conn_id, void * buf, VMUINT size);

/*****************************************************************************
 * FUNCTION
 *  vm_btspp_read
 * DESCRIPTION
 *  This function is for app read data
 * PARAMETERS
 *  conn_id [IN]:          connect id 
 *  buf [IN]:           data buf want to receive
 *  size [IN]:          the size of data want to receive
 * RETURNS
 *  VMINT : failure if less than 0, see vm_btspp_error_t, 
 * else return the size of data received successfully
 *****************************************************************************/
VMINT vm_btspp_read(VMUINT conn_id, void * buf, VMUINT size);

/*****************************************************************************
 * FUNCTION
 *  vm_btspp_get_dev_addr
 * DESCRIPTION
 *  get the bt addr with the conn_id
 * PARAMETERS
 *  conn_id [IN]: connect id 
 *  bt_addr [IN]: bt_addr.
 * RETURNS
 *  VMINT : failure if less than 0, else successful
 *****************************************************************************/
VMINT vm_btspp_get_dev_addr(VMINT conn_id, vm_srv_bt_cm_bt_addr * bt_addr);

/*****************************************************************************
 * FUNCTION
 *  vm_btspp_set_security_level
 * DESCRIPTION
 *  This function is for set security level by handle
 * PARAMETERS
 *  res_hd [IN]: res handler 
 *  level [IN]: spp instance security level in vm_srv_spp_security_level
 * RETURNS
 *  VMINT : failure if less than 0, else successful
 *****************************************************************************/
VMINT vm_btspp_set_security_level(VMINT res_hd, VMINT level);

/*****************************************************************************
 * FUNCTION
 *  vm_btspp_set_service_name
 * DESCRIPTION
 *  This function is for set a spp resource name
 * PARAMETERS
 *  res_hd [IN]: res handler 
 *  name [IN]: spp resource name UCS2
 * RETURNS
 *  VMINT : failure if less than 0, else successful
 *****************************************************************************/
VMINT vm_btspp_set_service_name(VMINT res_hd, VMWCHAR * name);

/* SPP SERVER USING START*/

/*****************************************************************************
 * FUNCTION
 *  vm_btspp_bind
 * DESCRIPTION
 *  This function is for app create a spp instance
 * PARAMETERS
 *  res_hd [IN]: res handler 
 *  uuid [IN]: profile id
 * RETURNS
 *  VMINT : failure if less than 0, else successful
 *****************************************************************************/
VMINT vm_btspp_bind(VMINT res_hd, VMUINT16 uuid);

/*****************************************************************************
 * FUNCTION
 *  vm_btspp_accept
 * DESCRIPTION
 *  This function is used for server whether do accept when notified by event VM_SRV_SPP_EVENT_AUTHORIZE
 * PARAMETERS
 *  conn_id [IN]: connect id         
 *  buf [IN]: tx rx buffer
 *  tx_size [IN]: tx buffer size
 *  rx_size [IN]: rx buffer size
 * RETURNS
 *  VMINT : failure if less than 0, else successful
 *****************************************************************************/
VMINT vm_btspp_accept(VMINT conn_id,
						void * buf, 
						VMUINT tx_size,
						VMUINT rx_size
						);
						
/*****************************************************************************
 * FUNCTION
 *  vm_btspp_reject
 * DESCRIPTION
 *  This function is used for server whether do accept when notified by event VM_SRV_SPP_EVENT_AUTHORIZE
 * PARAMETERS
 *  conn_id : connect id
 * RETURNS
 *  VMINT : failure if less than 0, else successful
 *****************************************************************************/
VMINT vm_btspp_reject(VMINT conn_id);

/* SPP SERVER USING END */


/* SPP CLIENT USING START */

/*****************************************************************************
 * FUNCTION
 *  vm_srv_spp_connect
 * DESCRIPTION
 *  This function is for app connect server
 * PARAMETERS
 *  res_hd [IN]: res handler 
 *  bt_addr [IN]: server bt address
 *  buf [IN]: for tx rx buffer
 *  tx_size [IN]: tx buffer size
 *  rx_size [IN]: rx buffer size
 *  uuid [IN]: profile id
 * RETURNS
 *  VMINT : failure if less than 0, else successful
 *****************************************************************************/
VMINT vm_btspp_connect(VMINT res_hd,
					const vm_srv_bt_cm_bt_addr * bt_addr,
					void * buf,
					VMUINT tx_size,
					VMUINT rx_size, 
					VMUINT16 uuid);

/*****************************************************************************
 * FUNCTION
 *  vm_srv_spp_connect_ex
 * DESCRIPTION
 *  This function is for app connect server
 * PARAMETERS
 *  res_hd [IN]: res handler 
 *  bt_addr [IN]: bt address.
 *  buf [IN]: for tx rx buffer
 *  tx_size [IN]: tx buffer size
 *  rx_size [IN]: rx_size
 *  connect_type [IN]: with sco or not
 *  uuid [IN]: profile id
 * RETURNS
 *  VMINT : failure if less than 0, else successful
 *****************************************************************************/
VMINT vm_btspp_connect_ex(VMINT res_hd, 
						const vm_srv_bt_cm_bt_addr * bt_addr,
						void * buf,
						VMUINT tx_size,
						VMUINT rx_size,
						vm_srv_spp_connect_type conn_type, 
						VMUINT16 uuid);

/* SPP CLIENT USING END */


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* VM_BTSPP_SDK_H */
