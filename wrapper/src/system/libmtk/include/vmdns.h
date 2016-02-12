#ifndef VM_DNS_SDK_H_
#define VM_DNS_SDK_H_

#include "vmsys.h"

/*---------------- DHCP Client APIs -------------------*/

/* DNS status */
typedef enum
{
	VM_STATE_STARTING,
	VM_STATE_RUNNING,
	VM_STATE_STOPPING,
	VM_STATE_STOPED,
	VM_STATE_ERROR	
}vm_dns_state;
 

/*****************************************************************************
 * FUNCTION
 *  vm_dns_start
 * DESCRIPTION
 *  This function is used to start DNS function
 * PARAMETERS
 *  port : dns server listen port
 *	config_path : config file of author dns server
 *	domain_path : records file of customized domian-IP 
 * RETURN VALUES
 *  -1 is failed
 *****************************************************************************/
VMINT vm_dns_start(VMUINT32 port, VMCHAR *config_path, VMCHAR *domain_path);


/*****************************************************************************
 * FUNCTION
 *  vm_dns_stop
 * DESCRIPTION
 *  This function is used to stop DNS functions
 * PARAMETERS
 *          
 * RETURN VALUES
 *  -1 is failed
 *****************************************************************************/
VMINT vm_dns_stop(void);


/*****************************************************************************
 * FUNCTION
 *  vm_dns_get_state
 * DESCRIPTION
 *  This function is used to get DNS status
 * PARAMETERS
 *          
 * RETURN VALUES
 *  vm_dns_state
 *****************************************************************************/
VMINT vm_dns_get_state(void);


#endif /* VM_DNS_SDK_H_ */