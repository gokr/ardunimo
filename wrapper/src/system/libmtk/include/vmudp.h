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

#ifndef VMUDP_SDK_H
#define VMUDP_SDK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "vmsys.h"



/* write status */
#define VM_UDP_EVT_WRITE	2

/* read status */
#define VM_UDP_EVT_READ		3

/* broken status */
#define VM_UDP_EVT_PIPE_BROKEN	4

/* udp pipe closed */
#define VM_UDP_EVT_PIPE_CLOSED	6


/*****************************************************************************
 * FUNCTION
 *    vm_udp_create
 * DESCRIPTION
 *  create udp socket.
 * PARAMETERS
 *  port : [IN] port number for binding.
 *  apn : [IN] apn id.
 *  callback : [IN] callback function for udp notification.
 *  loopback : [IN] loopback flag, non-zero: loopback; zero: no loopback.
 * RETURNS
 *  create udp success or not.
 * RETURN VALUES
 *  udp handle, if value >= 0; failue if < 0
 * EXAMPLE
 * <code>
 *  static VMINT g_hdll;
 *  void hl_udp_create(void)
 *  {
 *      VMINT port = 0x1234;
 *      g_hdl1 = vm_udp_create(port, VM_TCP_APN_CMNET, udp_callback, 1);
 *  }
 * </code>
*****************************************************************************/
VMINT vm_udp_create(VMINT port, VMINT apn, void (*callback)(VMINT hdl, VMINT event), VMINT loopback);
/*****************************************************************************
 * FUNCTION
 *    vm_udp_sendto
 * DESCRIPTION
 *  send data to the destination.
 * PARAMETERS
 *  hdl : [IN] udp handle.
 *  buf : [IN] buf.
 *  len : [IN] buf len.
 *  addr : [IN] the address of destination.
 * RETURNS
 *  size of sent data.
 * RETURN VALUES
 *  udp handle, if value >= 0; failue if < 0
 * EXAMPLE
 * <code>
 *  static void udp_callback(VMINT hdl, VMINT evt)
 *  {
 *      vm_sockaddr_struct sendto = {0};
 *      sendto.addr[0] = 192;
 *      sendto.addr[1] = 168;
 *      sendto.addr[2] = 1;
 *      sendto.addr[3] = 33;
 *      sendto.addr_len = 4;
 * 
 *      switch (evt)
 *      {
 *      case VM_UDP_EVT_WRITE:
 *          {
 *              VMINT ret = 0;
 *              sendto.port = 2500;
 *                  sendto.addr[1],
 *                  sendto.addr[2],
 *                  sendto.addr[3],
 *                  sendto.port,
 *                  sendto.addr_len);
 *              ret = vm_udp_sendto(hdl, buf, 1024, &sendto);
 *          }break;
 *      default:
 *          {
 *  
 *          }break;
 *      }
 *  }
 * </code>
*****************************************************************************/
VMINT vm_udp_sendto(VMINT hdl, const void * buf, VMINT32 len, const vm_sockaddr_struct * addr);
/*****************************************************************************
 * FUNCTION
 *    vm_udp_recvfrom
 * DESCRIPTION
 *  receive data from the destination.
 * PARAMETERS
 *  hdl : [IN] udp handle.
 *  buf : [OUT] buf.
 *  len : [IN] buf len.
 *  addr : [OUT] the address of destination.
 * RETURNS
 *  size of received data.
 * RETURN VALUES
 *  udp handle, if value >= 0; failue if < 0
 * EXAMPLE
 * <code>
 *  static void udp_callback(VMINT hdl, VMINT evt)
 *  {
 *      VMCHAR buf[1024] = {0};
 *      switch (evt)
 *      {
 *      case VM_UDP_EVT_READ:
 *          {
 *              VMINT ret = 0;
 *              vm_sockaddr_struct recvfrom = {0};
 *              ret = vm_udp_recvfrom(hdl, buf, 1024, &recvfrom);
 *          }break;
 *      default:
 *          {
 *  
 *          }break;
 *      }
 *  }
 * </code>
*****************************************************************************/
VMINT vm_udp_recvfrom(VMINT hdl, void * buf, VMINT32 len, vm_sockaddr_struct * addr);
/*****************************************************************************
 * FUNCTION
 *    vm_udp_close
 * DESCRIPTION
 *  close udp socket.
 * PARAMETERS
 *  port : [IN] dest host port.
 *  apn : [IN] apn id.
 *  callback : [IN] callback function for udp notification.
 * RETURNS
 *  create udp success or not.
 * RETURN VALUES
 *  udp handle, if value >= 0; failue if < 0
 * EXAMPLE
 * <code>
 *  static VMINT g_hdll;
 *  void hl_udp_create(void)
 *  {
 *      VMINT port = 0x1234;
 *      g_hdl1 = vm_udp_create(port, VM_TCP_APN_CMNET, udp_callback, 1);
 *      vm_udp_close(g_hdll);
 *  }
 * </code>
*****************************************************************************/
VMINT vm_udp_close(VMINT hdl);
#ifdef __cplusplus
}
#endif

#endif /* VMUDP_SDK_H */

