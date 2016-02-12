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

#ifndef VMSYS_SDK_H_
#define VMSYS_SDK_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef TRUE
#define TRUE 1 /*1*/
#endif

#ifndef FALSE
#define FALSE 0/*0*/
#endif

#ifndef NULL
#define NULL 0/*0*/
#endif


/* start LinkIt environment normally */
#define VM_NORMAL_START_MRE_ENV 1


typedef unsigned char VMUINT8;/*unsigned char*/
typedef unsigned short VMUINT16;/*unsigned short*/
typedef unsigned int VMUINT;/*unsigned int*/
typedef unsigned long VMUINT32;/*unsigned long*/


typedef  unsigned long long VMUINT64 ;/*unsigned long long*/
typedef  long long VMINT64 ;/*long long*/


typedef char VMINT8;/*char*/
typedef short VMINT16;/*short*/
typedef int  VMINT;/*int */
typedef long  VMINT32;/*long */

typedef VMUINT8 VMUCHAR;/*VMUINT8*/
typedef VMUINT16 VMUWCHAR;/*VMUINT16*/
typedef VMUINT8 * VMUSTR;/*VMUINT8 * */
typedef VMUINT16 * VMUWSTR;/*VMUINT16 * */

typedef VMINT8 VMCHAR;/*VMINT8*/
typedef VMINT16 VMWCHAR;/*VMINT16*/
typedef VMINT8 * VMSTR;/* VMINT8 * */
typedef VMINT16 * VMWSTR;/* VMINT16 * */

typedef unsigned char VMBYTE;/*unsigned char*/
typedef unsigned short VMUSHORT;/*unsigned short*/
typedef short VMSHORT;/*short*/

typedef VMINT VMFILE;/*VMINT*/
typedef VMINT VMBOOL;/*VMINT*/

typedef VMUINT32      VMCOLOR32;/*VMUINT32*/

#include "vmdatetime.h"
#include "vmuimisc.h"
#include "vmpwr.h"
#include "vmota.h"
#include "vmappmgr.h"
#include "vmpromng.h"
/*the statistic of memory using status */
typedef struct malloc_stat_t {
	/* the number if the malloc memory API is called, including vm_malloc(),vm_realloc(), * vm_calloc()   */
	VMINT malloc_count;

	/*the number of free memory API is called	 */
	VMINT free_count;

	/*current used memory */
	VMINT current;

	/*peak memory*/
	VMINT peak;

	/*the number of memory malloc fail*/
	VMINT fail_times;

	/* the max size that malloc memory failed */
	VMINT max_fail_size;

	/* current avail heap size  */
	VMINT avail_heap_size;
} malloc_stat_t;


typedef float         VMFLOAT;/*float*/

typedef VMINT32       VMMSEC;/*VMINT32*/

typedef VMINT32       VMRESID;/*VMINT32*/

typedef VMINT32       VMID;/*VMINT32*/

#define VM_TRUE       1/*VM_TRUE*/
#define VM_FALSE      0/*VM_FALSE*/

/* DOM-NOT_FOR_SDK-BEGIN */
/*****************************************************************************
 * FUNCTION
 *  vm_get_malloc_stat
 * DESCRIPTION
 *  get current memory management data after the memory management is available 
 * PARAMETERS
 *  void
 * RETURNS
 *  the memory status structure pointer
 *****************************************************************************/ 
malloc_stat_t* vm_get_malloc_stat(void);
/* DOM-NOT_FOR_SDK-END */

/*****************************************************************************
* FUNCTION
 *    vm_malloc
 * DESCRIPTION
 *  allocate specified size of memory 
 * PARAMETERS
 *  size : [IN]  size of byte to be allocated.
 * RETURNS
 *  memory pointer allocated, NULL means allocation failed.
*****************************************************************************/
void *vm_malloc(int size);

/*****************************************************************************
* FUNCTION
 *    vm_calloc
 * DESCRIPTION
 *  allocate specified size of memory and clean as zero.
 * PARAMETERS
 *  size : [IN]  size of byte to be allocated.
 * RETURNS
 *  memory pointer allocated, NULL means allocation failed.
*****************************************************************************/
void *vm_calloc(int size);

/*****************************************************************************
* FUNCTION
 *    vm_realloc
 * DESCRIPTION
 *  reallocate specified size of memory for the memory already allocated before.
 * PARAMETERS
 *  p : [IN] memory pointer to be realloced.
 *  size : [IN]  size of byte to be allocated.
 * RETURNS
 *  memory pointer allocated; NULL means allocation failed, but the original pointer will not free.
*****************************************************************************/
void *vm_realloc(void* p, int size);

/*****************************************************************************
* FUNCTION
 *    vm_free
 * DESCRIPTION
 *  free memory allocated by vm_malloc(), vm_calloc(), or vm_realloc().
 * PARAMETERS
 *  ptr : [IN]  memory pointer to be free.
*****************************************************************************/
void vm_free(void* ptr);

/* DOM-NOT_FOR_SDK-BEGIN */
/*****************************************************************************
* FUNCTION
 *    vm_global_malloc
 * DESCRIPTION
 *  allocate extra memory excluding the size announced when packing, size must larger than 10KB. 
 * PARAMETERS
 *  size : [IN]  size of byte to be allocated.
 * RETURNS
 *  memory pointer allocated, NULL means allocation failed.
*****************************************************************************/
void *vm_global_malloc(unsigned int size);
/*****************************************************************************
* FUNCTION
 *    vm_free
 * DESCRIPTION
 *  free memory allocated by vm_global_malloc();
 * PARAMETERS
 *  ptr : [IN]  memory pointer to be free.
*****************************************************************************/
void vm_global_free(void* ptr);

/*****************************************************************************
* FUNCTION
 *    vm_global_get_max_alloc_size
 * DESCRIPTION
 *  Get the max possible size of single allocation from app-based ASM. 
 *
 *  Remark: we can use this function to dynamically decide the allocation size 
 *  (for example, use larger image cache when there is more memory)
 *  
 *  However, sometimes we cannot allocate 2 * 10KB blocks if the maximum allocation size 
 *  is 20KB because of the overheads of memory management bookkeeping. 
 *
 *  It is suggested to use "fail-safe" allocation regardless the internal 
 *  implementation of ASM if we want to allocate more memory adaptively according
 *  to the free space
 *  Step 1. Decide the size of free space => e.g. 100KB
 *  Step 2. Allocate 100KB
 *  Step 3. If failed, allocate 95 KB
 *  Step 4. If failed, allocate 90 KB
 *  Step 5. ...
 * PARAMETERS
 *  void
 * RETURNS
 *  memory size
*****************************************************************************/
VMINT vm_global_get_max_alloc_size(void);

/*****************************************************************************
* FUNCTION
 *    vm_malloc
 * DESCRIPTION
 *  allocate non-cacheable  memory 
 * PARAMETERS
 *  size : [IN]  size of byte to be allocated.
 * RETURNS
 *  memory pointer allocated, NULL means allocation failed.
*****************************************************************************/
void *vm_malloc_nc(int size);
/*****************************************************************************
* FUNCTION
 *    vm_malloc_nc_topmost
 * DESCRIPTION
 *  allocate specified size of non-cachable memory from topmost address
 * PARAMETERS
 *  size : [IN]  size of byte to be allocated.
 * RETURNS
 *  memory pointer allocated, NULL means allocation failed.
*****************************************************************************/
void *vm_malloc_nc_topmost(int size);

typedef enum 
{
   VM_SLA_STOP,
   VM_SLA_START,
   VM_SLA_LABEL
} vm_sla_action_type;

/*****************************************************************************
* FUNCTION
 *    vm_sla_custom_logging
 * DESCRIPTION
 *  SWLA custom logging function
 * PARAMETERS
 *  custom_label : [IN] the custom label.
 *  action       : [IN] the logging action
*****************************************************************************/
void vm_sla_custom_logging(VMSTR custom_label, vm_sla_action_type action);

/* DOM-NOT_FOR_SDK-END */

/*****************************************************************************
 * FUNCTION
 *  vm_get_total_mem_size

 * DESCRIPTION
 *  get LinkIt total memory size  
 * PARAMETERS

 *  
 * RETURNS
 *  memory size
 *****************************************************************************/
VMUINT vm_get_total_mem_size(void);

#define vm_get_mre_total_mem_size vm_get_total_mem_size


VMUINT vm_get_total_heap_size(void);

/*****************************************************************************
* FUNCTION
 *    vm_malloc_nc_topmost
 * DESCRIPTION
 *  allocate specified size of  memory from topmost address
 * PARAMETERS
 *  size : [IN]  size of byte to be allocated.
 * RETURNS
 *  memory pointer allocated, NULL means allocation failed.
*****************************************************************************/
void *vm_malloc_topmost(int size);

/*****************************************************************************
* FUNCTION
 *    vm_malloc_nc_topmost
 * DESCRIPTION
 *  re-allocate specified size of  memory from topmost address
 * PARAMETERS
 *  size : [IN]  size of byte to be allocated.
 * RETURNS
 *  memory pointer allocated, NULL means allocation failed.
*****************************************************************************/
void *vm_realloc_topmost(void * p,int size);

#ifdef __cplusplus
}
#endif 

#endif /* VMSYS_SDK_H_ */
