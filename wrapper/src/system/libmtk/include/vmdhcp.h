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

#ifndef VM_DHCP_SDK_H_
#define VM_DHCP_SDK_H_

#include "vmsys.h"

/*---------------- DHCP Client APIs -------------------*/

/* DHCP Client Mode */
typedef enum
{
    VM_DHCP_CLIENT_ON, // The feature that using DHCP to get an IP is available.
    VM_DHCP_CLIENT_OFF, // The feature that using DHCP to get an IP is unavailable.
    
    VM_DHCP_CLIENT_END
}vm_dhcp_client_mode_enum;

/*****************************************************************************
 * FUNCTION
 *  vm_dhcp_client_set_mode
 * DESCRIPTION
 *  This function is used to set the client mode. 
 * PARAMETERS
 *  mode      : [IN]    vm_dhcp_client_mode_enum         
 * RETURN VALUES
 *  TRUE   Setting succeeds.
 *  FALSE  Setting fails.
 *****************************************************************************/
VMINT vm_dhcp_client_set_mode(VMUINT32 mode);


/*****************************************************************************
 * FUNCTION
 *  vm_dhcp_client_get_mode
 * DESCRIPTION
 *  This function is used to get the client mode. 
 * PARAMETERS
 *          
 * RETURN VALUES
 *  >=0    Current client mode in dhcp_client_mode_enum.
 *  <0      Getting fails.
 *****************************************************************************/
VMINT vm_dhcp_client_get_mode(void);



/*---------------- DHCP Server APIs -------------------*/

#define VM_DHCPD_DOT_IP_MAX_LEN 15

/****************************************************************************/
/* Enum                                                              */
/****************************************************************************/
typedef enum
{
    VM_DHCP_SERVER_ON, // Response to clients' requests.
    VM_DHCP_SERVER_OFF, // Won't resonse to any client's request.
    
    VM_DHCP_SERVER_END
}vm_dhcp_server_mode_enum;

/****************************************************************************/
/* Struct                                                              */
/****************************************************************************/
typedef struct
{    
    VMUINT8 start_ip_addr[VM_DHCPD_DOT_IP_MAX_LEN + 1]; // start ip address
    VMUINT8 end_ip_addr[VM_DHCPD_DOT_IP_MAX_LEN + 1]; // end ip address
    VMUINT8 gateway_ip_addr[VM_DHCPD_DOT_IP_MAX_LEN + 1]; // gateway ip address
    VMUINT8 subnet_mask[VM_DHCPD_DOT_IP_MAX_LEN + 1]; // subnet mask
    VMUINT32 default_lease_tm; // default lease time. 
} vm_dhcp_server_config_struct;

/****************************************************************************/
/* API                                                              */
/****************************************************************************/
/*****************************************************************************
 * FUNCTION
 *  vm_dhcp_server_set_mode
 * DESCRIPTION
 *  This function is used to set the server mode. 
 * PARAMETERS
 *  mode      : [IN]    vm_dhcp_server_mode_enum         
 * RETURN VALUES
 *  TRUE    Setting succeeds.
 *  FALSE   Setting fails.
 *****************************************************************************/
VMINT vm_dhcp_server_set_mode(VMUINT32 mode);


/*****************************************************************************
 * FUNCTION
 *  vm_dhcp_server_get_mode
 * DESCRIPTION
 *  This function is used to get the server mode. 
 * PARAMETERS
 *          
 * RETURN VALUES
 *  >=0    Current server mode in dhcp_server_mode_enum.
 *  <0      Getting fails.
 *****************************************************************************/
VMINT vm_dhcp_server_get_mode(void);


/*****************************************************************************
 * FUNCTION
 *  vm_dhcp_server_set_param
 * DESCRIPTION
 *  This function is used to set the parameters for DHCP server, when the phone is in AP mode.
 *  The configurable parameters are start ip, end ip, gateway ip and the default lease time. 
 *  DNS and default domain name are gotten from 3G, which can't be configed by customer. 
 *
 *  There are some restrictions for the input parameter, when server_on is set to be true.
 *  Firstly, start_ip_addr, end_ip_addr, and gateway_ip_addr should be in the same subnet. 
 *  Secondly, gateway_ip_addr should be out of the range defined by start_ip_addr and end_ip_addr.
 *  If any restriction mentioned above is broken, default values will be used.
 *  
 *  The format for the IP address is dot format, such as "xxx.xxx.xxx.xxx". The unit for default_lease_tm is
 *  second. Default lease time will be used, if DHCP client doesn't request certain lease time, .
 *  If the members in dhcp_server_config_struct are not set or are set improperly, default values will be used. 
 *  
 *  Default values for the members in dhcp_server_config_struct.
 *  start_ip_addr    192.168.1.10
 *  end_ip_addr    192.168.1.250
 *  gateway_ip_addr    192.168.1.1
 *  subnet_mask    255.255.255.0
 *  default_lease_tm    3600
 *
 * PARAMETERS
 *  param      : [IN]         
 * RETURN VALUES
 *  TRUE    Setting succeeds.
 *  FALSE   Setting fails.
 *****************************************************************************/
VMINT vm_dhcp_server_set_param(vm_dhcp_server_config_struct *param);


/*****************************************************************************
 * FUNCTION
 *  dhcp_server_get_param
 * DESCRIPTION
 *  This function is used to get DHCP server parameters, when phone is in AP mode and parameters have been set.
 * PARAMETERS
 *  param      : [OUT]         
 * RETURN VALUES
 *  TRUE    Getting succeeds.
 *  FALSE   Getting fails.
 *****************************************************************************/
VMINT vm_dhcp_server_get_param(vm_dhcp_server_config_struct *param);

#endif /* VM_DHCP_SDK_H_ */