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

/*******************************************************************************
* Filename:
* ---------
*  
*
* Project:
* --------
*  MAUI
*
* Description:
* ------------
*  
*
* Author:
* -------
*
*
*==============================================================================
*             HISTORY
* Below this line, this part is controlled by PVCS VM. DO NOT MODIFY!! 
*------------------------------------------------------------------------------
* $Log$
*
* 06 20 2014 shuaihui.ren
* [MAUI_03493338] MRE NAT check in
* .
*
* 06 18 2014 shuaihui.ren
* [MAUI_03505838] "apk occure some error please check" happened when try to view video.
* .
*
* 05 20 2014 shuaihui.ren
* [MAUI_03493338] MRE NAT check in
* .
*
* 03 11 2014 feng.lin
* [MAUI_03479763] [IOT]Merge IOT code to 11C
* .
*
* 01 27 2014 xiufeng.zhang
* [MAUI_03484297] [IOT] UPnP check in
* .
*
* 01 27 2014 xiufeng.zhang
* [MAUI_03484297] [IOT] UPnP check in
* .
*
* .
*------------------------------------------------------------------------------
* Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!! 
*==============================================================================
*******************************************************************************/
#ifndef VM_NAT_SDK_H
#define VM_NAT_SDK_H

#define VM_TYPE_MAX_LEN                                  4
#define VM_UPNP_SUCCESS                                  0
#define VM_UPNP_FAIL_CREATE_SOCKET                       -1
#define VM_UPNP_FAIL_NO_ROUTER                           -2
#define VM_UPNP_FAIL_ROUTER_NOT_SUPPORT_UPNP             -3
#define VM_UPNP_FAIL_CREATE_THREAD                       -4
#define VM_UPNP_FAIL_NO_MEMORY                           -5
#define VM_UPNP_FAIL_MAPPING                             -6
#define VM_UPNP_FAIL_OTHER                               -7
#define VM_UPNP_PROTOCAL_UDP                             0
#define VM_UPNP_PROTOCAL_TCP                             1

/* use for mmi_frm_mapping_ports() parameter*/
typedef struct _vm_upnp_request_info
{
    VMUINT8 mapping_protocal;             /* UPNP_PROTOCAL_UDP or UPNP_PROTOCAL_TCP */
    VMUINT16 local_port;                   /* local port of mapping request. */
    VMUINT16 ext_port;                     /* external port of mapping result. If not 0, upnp will try to mapping the ext_port, or it will mapping a random port.*/
} vm_upnp_request_info;

/* use for response port mapping */
typedef struct _vm_upnp_map_info
{
    VMUINT32 count;
    vm_upnp_request_info*  requset_data;
} vm_upnp_map_info;

typedef void(* vm_upnp_result_cb)(VMUINT8  request_id, VMINT ret, void* res_data, void* user_data);

/**/
typedef struct
{
    VMUINT32 protocol_type;
    VMUINT16 port;
    VMUINT32 userNum;
    VMUINT32 seqId;
    VMUINT8 addr[4];
    VMINT8  request_id[64];
}vm_nat_invite_req_struct;

typedef void(* vm_got_tunneling_addr_cb)(vm_nat_invite_req_struct *out_info, void *user_data);

typedef struct
{
    VMUINT16                port;             /* local port */
    VMUINT16                nat_port;         /* port for NAT */
    VMUINT8                 ip_addr[4];       /* local IP address */
    VMUINT8                 nat_ip_addr[4];   /* address for NAT */
}vm_nat_addr_struct;

typedef void (*vm_nat_got_mapped_addr_cb)(vm_nat_addr_struct *addr, void *user_data);

/*****************************************************************************
* FUNCTION
*  vm_upnp_mapping_ports
* DESCRIPTION
*  Async function, use for add mapping ports on router, the mapping result is notifyed by cb function. 
*  only can be used in mmi task, 
* PARAMETERS
* request_id:                   [in]  user define, use for identify the request. 
* cb                                [in]  the call back function.
* request_data:               [in]  the request ports mapping info. 
* user_data:                    [in]  user data. 
* RETURNS
*  None
* Example
* <code>
* kal_int8 mapping_handler (kal_uint8  request_id, kal_int32 ret, void* res_data, void* user_data);
* kal_int32 fun()
* {
*     upnp_request_info req_data[2];
*     upnp_map_res_info req;
*     kal_uint8  request_id = 1234;
*     req_data[0].mapping_protocal = UPNP_PROTOCAL_UDP;
*     req_data[0].local_port = 2002;
*     req_data[0].ext_port = 0;
*     req_data[1].mapping_protocal = UPNP_PROTOCAL_TCP;
*     req_data[1].local_port = 4221;
*     req_data[1].ext_port = 0;
*     req.requset_data = req_data;
*     vm_upnp_mapping_ports(request_id, mapping_handler, req, NULL);
*     return 0;
* }
*
*
* kal_int8 mapping_handler (kal_uint8  request_id, kal_int32 ret, void* res_data, void* user_data);
* {
*      upnp_map_info* res_data;
*      if(ret == UPNP_SUCCESS)
*      {
*          MMI_FRM_MAPPING_RES_INFO* res;
*          res_data = (vm_upnp_request_info*) res_data;
*          // do_sth();
*      }
*      return 0;
* }
* </code>
*****************************************************************************/
VMINT vm_upnp_mapping_ports(VMUINT8  request_id, vm_upnp_result_cb cb, vm_upnp_map_info* request_data, void* user_data);

/*****************************************************************************
* FUNCTION
*  vm_upnp_get_ext_ip
* DESCRIPTION
*  Async function, use for geting external ip of router, the mapping result is notifyed by cb function. 
*  only can be used in mmi task, 
* PARAMETERS
* request_id:                   [in]  user define, use for identify the request. 
* cb                                [in]  the call back function.
* user_data:                    [in]  user data. 
* RETURNS
*  None
*
* Example
* <code>
* kal_int8 ip_handler (kal_uint8  request_id, kal_int32 ret, void* res_data);
* kal_int32 fun()
* {
*     kal_uint8  request_id = 231;
*     vm_upnp_get_ext_ip(request_id, ip_handler);
*     return 0;
* }
*
* kal_int8 ip_handler(kal_uint8  request_id, kal_int32 ret, void* res_data)
* {
*      kal_char* ip;
*      if(ret == UPNP_SUCCESS)
*      {
*          ip = (kal_char*) res_data;
*          // do_sth();
*      }
*      return 0;
* }
* </code>
*****************************************************************************/
VMINT vm_upnp_get_ext_ip(VMUINT8  request_id, vm_upnp_result_cb cb, void *user_data);

VMINT vm_nat_invite_req(vm_nat_invite_req_struct *req, vm_got_tunneling_addr_cb cb, void* user_data);
VMINT vm_nat_set_life_time(VMUINT32 life_time);
VMINT vm_nat_set_stun_server(VMCHAR *server, VMUINT16 port);
VMINT vm_nat_get_mapped_addr_async(vm_nat_got_mapped_addr_cb callback, void *user_data);
VMINT vm_nat_set_type(VMUINT32 type);
#endif /* VM_NAT_SDK_H */
