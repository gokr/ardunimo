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

#ifndef VMSTDLIB_SDK_H_
#define VMSTDLIB_SDK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdarg.h>
#include "vmsys.h"

#define VM_CACHE_SIZE 4096


#if defined(__COMPILER_RVCT__) || defined(__COMPILER_GCC__)
#undef vsprintf
#undef sprintf
#undef sscanf

int vm_vsprintf(char *buf, const char *fmt, va_list args);
int vm_sprintf( char * buf, const char * fmt, ... );
int vm_sscanf(const char *str, const char *format, ...);

#define vsprintf vm_vsprintf
#define sprintf vm_sprintf
#define sscanf vm_sscanf
#endif


/**
* cache structure to transfer block io mode to stream io mode
*/
struct vm_cache_t {
	VMINT eof;					/* end of stream */
	VMINT avail;				/* data still available from stream */
	VMINT count;				/* number of byte of remaining data from stream */
	VMUINT8 buf[VM_CACHE_SIZE];	/* data buffer */
};
typedef struct vm_cache_t vm_cache_t;

/*****************************************************************************
 * FUNCTION
 *  strtoi
 * DESCRIPTION
 *  transfer a number format from string to integer. 
 * PARAMETERS
 *  s : [IN]  string to be transfered.
 * RETURNS
 *  result of transition. -1 means failed.
 *****************************************************************************/
int strtoi(char* s);

/*****************************************************************************
 * FUNCTION
 *    vm_get_filename
 * DESCRIPTION
 *  get file name from full path. 
 * PARAMETERS
 *  path: [IN] full path string encoding with UCS2.
 *  filename : [OUT] output file name encoding with UCS2.
 *****************************************************************************/
void vm_get_filename(VMWSTR path, VMWSTR filename);

/*****************************************************************************
 * FUNCTION
 *    vm_get_path
 * DESCRIPTION
 *  get file path from full path. 
 * PARAMETERS
 *  fullpath: [IN] full path string encoding with UCS2.
 *  path : [OUT] output file path encoding with UCS2.
 * RETURNS
 *  0 means successfully
 *****************************************************************************/
VMINT vm_get_path(VMWSTR fullpath, VMWSTR path);

/* DOM-NOT_FOR_SDK-BEGIN */
/*****************************************************************************
 * FUNCTION
 *    get_today_from_2000
 * DESCRIPTION
 *  get the number of day from 2000/01/01 to now. 
 * RETURNS
 *  number of day, -1 means failed.
 *****************************************************************************/
VMINT get_today_from_2000(void);
/* DOM-NOT_FOR_SDK-END */

/*****************************************************************************
 * FUNCTION
 *    vm_upper_case
 * DESCRIPTION
 *  convert the lower case character to upper case character 
 * PARAMETERS
 *  dst : [OUT] output the upper case of string
 *  src : [IN] string to be converted.
 *****************************************************************************/
void vm_upper_case(char* dst, char* src);

/*****************************************************************************
 * FUNCTION
 *    vm_upper_case
 * DESCRIPTION
 *  convert the upper case character to lower case character 
 * PARAMETERS
 *  dst: [OUT] output the lower case of string
 *  src : [IN] string to be converted.
 *****************************************************************************/
void vm_lower_case(char* dst, char* src);

/*****************************************************************************
 * FUNCTION
 *    vm_string_equals_ignore_case
 * DESCRIPTION
 *  compare string without case sensitive
 * PARAMETERS
 *  s1: [IN] the first string.
 *  s2 : [IN] the second string.
 * RETURNS
 *  0 means the two string are same, -1 means they are different.
 *****************************************************************************/
VMINT vm_string_equals_ignore_case(const char *s1, const char *s2);

/*****************************************************************************
 * FUNCTION
 *    vm_write_cache
 * DESCRIPTION
 *  write data to cache by stream mode.
 * PARAMETERS
 *  cache: [IN] cache pointer.
 *  buf : [IN] buffer address.
 *  buf_len : [IN] buffer length.
 * RETURNS
 *  number of bytes written
 *****************************************************************************/
VMINT vm_write_cache(vm_cache_t *cache, void *buf, VMINT buf_len);

 /*****************************************************************************
 * FUNCTION
 *    vm_read_cache
 * DESCRIPTION
 *  read data from cache by stream mode.
 * PARAMETERS
 *  cache: [IN] cache pointer.
 *  buf : [OUT] buffer address.
 *  buf_size : [IN] buffer size
 *  len : [IN] number of bytes to read.
 * RETURNS
 *  number of bytes read
 *****************************************************************************/
VMINT vm_read_cache(vm_cache_t *cache, void *buf, VMINT buf_size, VMINT len);

 /*****************************************************************************
 * FUNCTION
 *    vm_cache_read_char
 * DESCRIPTION
 *  read a character from cache by stream mode.
 * PARAMETERS
 *  cache: [IN] cache pointer.
 *  ch : [OUT] character.
 * RETURNS
 *  0 means succeed, else return error code.
 *****************************************************************************/
VMINT vm_cache_read_char(vm_cache_t *cache, char *ch);

 /*****************************************************************************
 * FUNCTION
 *    vm_get_cache_free_space
 * DESCRIPTION
 *  get free space of cache.
 * PARAMETERS
 *  cache: [IN] cache pointer.
 * RETURNS
 *  number of byte of free space
 *****************************************************************************/
VMINT vm_get_cache_free_space(vm_cache_t *cache);

 /*****************************************************************************
 * FUNCTION
 *    vm_read_line
 * DESCRIPTION
 *  read a line of string from cache.
 * PARAMETERS
 *  line: [OUT] string pointer to read
 *  size : [IN] line buffer size
 *  cache : [IN] cache pointer.
 * RETURNS
 *  0 means succeed, else return error code.
 *****************************************************************************/
VMINT vm_read_line(char* line, VMINT size, vm_cache_t* cache);

/* DOM-NOT_FOR_SDK-BEGIN */
/*****************************************************************************
* FUNCTION
*    vm_memcpy
* DESCRIPTION
*  memory copy.
* PARAMETERS
*  dst: [OUT] destination data buffer.
*  src : [IN] source data buffer.
*  count : [IN] number of byte to be copied.
*****************************************************************************/
void vm_memcpy(void* dst, void* src, VMINT count);
/* DOM-NOT_FOR_SDK-END */

/**
* dynamic array
*/
typedef struct _vm_dyn_array_t {
/**
* size of block.
    */
    VMINT block_size;
    
    /**
    * initial size.
    */
    VMINT init_size;
    
    /**
    * increased size.
    */
    VMINT inc_size;
    
    /**
    * count of saved block
    */
    VMINT count;
    
    /**
    * capacity of the array
    */
    VMINT capacity;
    
    /**
    *pointer of array
    */
    void  *ptr;
} vm_dyn_array_t;

/*****************************************************************************
 * FUNCTION
 *    vm_create_dyn_array
 * DESCRIPTION
 *  create dynamic array.
 * PARAMETERS
 *  init_size: [IN] initial size of dynamic array.
 *  inc_size : [IN] increased size each time
 *  block_size : [IN] structure size of data stored in the array
 * RETURNS
 *  0 means succeed, else return error code.
 *****************************************************************************/
vm_dyn_array_t* vm_create_dyn_array(VMINT init_size, VMINT inc_size, VMINT block_size);

/*****************************************************************************
 * FUNCTION
 *    vm_dyn_array_add
 * DESCRIPTION
 *  add new data to the end of dynamic array .
 * PARAMETERS
 *  array: [IN] array pointer.
 *  data : [IN] data to be added.
 * RETURNS
 *  0 means succeed, else return error code.
 *****************************************************************************/
VMINT vm_dyn_array_add(vm_dyn_array_t *array, void* data);

/*****************************************************************************
 * FUNCTION
 *    vm_dyn_array_del
 * DESCRIPTION
 *  delete the data item of specified index of the array .
 * PARAMETERS
 *  array: [IN] array pointer.
 *  idx : [IN] index to be deleted.
 * RETURNS
 *  0 means succeed, else return error code.
 *****************************************************************************/
VMINT vm_dyn_array_del(vm_dyn_array_t *array, VMINT idx);

/*****************************************************************************
 * FUNCTION
 *    vm_dyn_array_del_all
 * DESCRIPTION
 *  delete all the data from the specified array .
 * PARAMETERS
 *  array: [IN] array pointer.
 * RETURNS
 *  0 means succeed, else return error code.
 *****************************************************************************/
VMINT vm_dyn_array_del_all(vm_dyn_array_t *array);

/*****************************************************************************
 * FUNCTION
 *    vm_free_dyn_array
 * DESCRIPTION
 *  free the memory of the dynamic array .
 * PARAMETERS
 *  array: [IN] array pointer.
 *****************************************************************************/
void vm_free_dyn_array(vm_dyn_array_t *array);

/**
 * stack operation succeed
 */
#define STACK_OPERATE_SUCCESS				(0)

/**
 * stack operation fail
 */
#define STACK_PARAM_ERROR					(-1)

/**
 * stack operation fail for lack of resource
 */
#define STACK_LEAK_RESOUCE					(-2)

/**
 * stack push fail for overflow
 */
#define STACK_PUSH_OVERFLOW					(-3)

/**
* stack pop fail for empty stack
*/
#define STACK_OPERATE_EMPTY_STACK			(-4)

/**
 * stack operation fail for handler error
 */
#define STACK_HANDLE_ERROR					(-5)

/*****************************************************************************
 * FUNCTION
 *    vm_create_array_stack
 * DESCRIPTION
 *  create an array stack, when not use this, please use vm_destory_stack to destroy it.
 * PARAMETERS
 *  capability : [IN] stack's capability.
 *  handle : [OUT] the handle of stack.
 * RETURNS
 *  create an array stack success or not.
 * RETURN VALUES
 *	STACK_OPERATE_SUCCESS : create stack success.
 *  STACK_PARAM_ERROR : parameter is wrong.
 *  STACK_LEAK_RESOUCE : resource error.
 *****************************************************************************/
VMINT vm_create_array_stack(VMINT capability, VMINT* handle);


/*****************************************************************************
 * FUNCTION
 *    vm_create_linked_stack
 * DESCRIPTION
 *  create an linked stack, memory will dynamicly allocate,when not use this, please use vm_destory_stack to destroy it.
 * PARAMETERS
 *  capability : [IN] stack's capability.
 *  handle : [OUT] the handle of stack.
 * RETURNS
 *  create an linked stack success or not.
 * RETURN VALUES
 *	STACK_OPERATE_SUCCESS : create stack success.
 *  STACK_PARAM_ERROR : parameter is wrong.
 *  STACK_LEAK_RESOUCE : resource error.
 *****************************************************************************/
VMINT vm_create_linked_stack(VMINT capability, VMINT* handle);


/*****************************************************************************
 * FUNCTION
 *    vm_is_empty_stack
 * DESCRIPTION
 *  check stack empty or not.
 * PARAMETERS
 *  stackHandle : [IN] stack's handle when created by vm_create_linked_stack.
 * RETURNS
 *  stack empty or not.
 * RETURN VALUES
 *	FALSE : stack is not empty.
 *  TRUE : stack is empty.
 *****************************************************************************/
VMINT vm_is_empty_stack(VMINT stackHandle);


/*****************************************************************************
 * FUNCTION
 *    vm_push_stack
 * DESCRIPTION
 *  push data to stack.
 * PARAMETERS
 *  stackHandle : [IN] stack's handle.
 *  ptr : [IN] data for pushing.
 * RETURNS
 *  push data to stack success or not.
 * RETURN VALUES
 *	STACK_OPERATE_SUCCESS : push data success.
 *  STACK_PUSH_OVERFLOW : stack is full.
 *  STACK_LEAK_RESOUCE : memory is not enough.
 *  STACK_HANDLE_ERROR : stackHandle is wrong.
 *****************************************************************************/
VMINT vm_push_stack(VMINT stackHandle, void* ptr);


/*****************************************************************************
 * FUNCTION
 *    vm_popup_stack
 * DESCRIPTION
 *  popup data from stack.
 * PARAMETERS
 *  stackHandle : [IN] stack's handle.
 *  ptr : [OUT] data get from stack.
 * RETURNS
 *  popup data success or not.
 * RETURN VALUES
 *	STACK_OPERATE_SUCCESS : popup data success.
 *  STACK_OPERATE_EMPTY_STACK : stack is empty.
 *  STACK_HANDLE_ERROR : stackHandle is wrong.
 *****************************************************************************/
VMINT vm_popup_stack(VMINT stackHandle, void** ptr);


/*****************************************************************************
 * FUNCTION
 *    vm_peek_stack
 * DESCRIPTION
 *  get next data from stack but not popup.
 * PARAMETERS
 *  stackHandle : [IN] stack's handle.
 *  ptr : [OUT] data get from stack.
 * RETURNS
 *  get next data from stack success or not.
 * RETURN VALUES
 *	STACK_OPERATE_SUCCESS : popup data success.
 *  STACK_OPERATE_EMPTY_STACK : stack is empty.
 *  STACK_HANDLE_ERROR : stackHandle is wrong.
 *****************************************************************************/
VMINT vm_peek_stack(VMINT stackHandle, void** ptr);


/*****************************************************************************
 * FUNCTION
 *    vm_reset_stack
 * DESCRIPTION
 *  clear all stack's data.
 * PARAMETERS
 *  stackHandle : [IN] stack's handle.
 * RETURNS
 *  clear all stack's data success or not.
 * RETURN VALUES
 *	STACK_OPERATE_SUCCESS : clear data success.
 *  STACK_HANDLE_ERROR : stackHandle is wrong.
 *****************************************************************************/
VMINT vm_reset_stack(VMINT stackHandle);


/*****************************************************************************
 * FUNCTION
 *    vm_is_exist_stack
 * DESCRIPTION
 *  check data in or not in stack.
 * PARAMETERS
 *  stackHandle : [IN] stack's handle.
 *  ptr : [IN] data.
 * RETURNS
 *  return data in or not in stack.
 * RETURN VALUES
 *	TRUE : in stack.
 *  FALSE : not in stack.
 *****************************************************************************/
VMINT vm_is_exist_stack(VMINT stackHandle, void* ptr);


/*****************************************************************************
 * FUNCTION
 *    vm_destroy_stack
 * DESCRIPTION
 *  check data in or not in stack.
 * PARAMETERS
 *  stackHandle : [IN] stack's handle.
 * RETURNS
 *  destroy stack success or not.
 * RETURN VALUES
 *	STACK_OPERATE_SUCCESS : destroy stack success.
 *  STACK_HANDLE_ERROR : stackHandle is wrong.
 *****************************************************************************/
VMINT vm_destroy_stack(VMINT stackHandle);

/*****************************************************************************
 * FUNCTION
 *    vm_ends_with
 * DESCRIPTION
 *  check specified string is end with specified string
 * PARAMETERS
 *  s1 : [IN]  string to check
 *  s2 : [IN]  ending string
 * RETURNS
 *  0 if s1 ended with s2, else return others.
 *****************************************************************************/
VMINT vm_ends_with(const char *s1, const char *s2);

/*****************************************************************************
 * FUNCTION
 *    vm_ends_with
 * DESCRIPTION
 *  check specified string is end with specified string, and both of the two strings are encoding with UCS2
 * PARAMETERS
 *  s1 : [IN]  string to check
 *  s2 : [IN]  ending string
 * RETURNS
 *  0 if s1 ended with s2, else return others.
 *****************************************************************************/
VMINT vm_wends_with(const VMWSTR s1, const VMWSTR s2);

/* DOM-NOT_FOR_SDK-BEGIN */
/*****************************************************************************
 * FUNCTION
 *    vm_tmp_filename
 * DESCRIPTION
 *  generate a temp file name which will be unique.
 * PARAMETERS
 *  prefix : [IN]  prefix to temp file name, normally is path.
 *  filename : [OUT]  temp file name length is 128 including '\0'. 
 *****************************************************************************/
void vm_tmp_filename(char* prefix, char* filename);
/* DOM-NOT_FOR_SDK-END */

/*****************************************************************************
 * FUNCTION
 *    vm_safe_wstrcpy
 * DESCRIPTION
 *  safe wstrcpy. When destination buffer is not enough, the extra part will be cut.
 * PARAMETERS
 *  dest : [OUT]  destination string.
 *  size : [IN]  length of string.
 *  src : [IN] source string.
 * RETURNS
 *  length of string copied actually.
 *****************************************************************************/
VMINT vm_safe_wstrcpy(VMWSTR dest, VMINT size, VMWSTR src);

#define wstrlen			vm_wstrlen
/*****************************************************************************
 * FUNCTION
 *    vm_wstrcpy
 * DESCRIPTION
 *  get the length of UCS2 string.
 * PARAMETERS
 *  s : [IN]  string to be checked teminated with '\0'.
 * RETURNS
 *  length of string.
 *****************************************************************************/
VMINT vm_wstrlen(VMWSTR s);

#define wstrcpy			vm_wstrcpy
/*****************************************************************************
 * FUNCTION
 *    vm_wstrcpy
 * DESCRIPTION
 *  UCS2 string copy
 * PARAMETERS
 *  dest : [OUT]  destination string.
 *  src : [IN] source string.
 * RETURNS
 *  length of string copied actually.
 *****************************************************************************/
VMINT vm_wstrcpy(VMWSTR dst, const VMWSTR src);

#define wstrcat			vm_wstrcat
/*****************************************************************************
 * FUNCTION
 *    vm_wstrcat
 * DESCRIPTION
 *  UCS2 string append.
 * PARAMETERS
 *  dest : [OUT]  destination string.
 *  src : [IN] source string.
 *****************************************************************************/
VMINT vm_wstrcat(VMWSTR dst, const VMWSTR src);

#define wstrncpy		vm_wstrncpy
/*****************************************************************************
 * FUNCTION
 *    vm_wstrncpy
 * DESCRIPTION
 *  UCS2 string N copy
 * PARAMETERS
 *  dest : [OUT]  destination string.
 *  src : [IN] source string.
 *  length : [IN] lenth of string to be copied.
 * RETURNS
 *  length of string copied actually.
 *****************************************************************************/
VMINT vm_wstrncpy(VMWSTR dst, const VMWSTR src, VMINT length);

#define wstrcmp			vm_wstrcmp

/*****************************************************************************
 * FUNCTION
 *    vm_wstrcmp
 * DESCRIPTION
 *  UCS2 string compare
 * PARAMETERS
 *  str_1 : [IN]  string 1
 *  str_2 : [IN] string 2
 * RETURNS
 *  0 means the two string are same, non-zero means they are different.
 *****************************************************************************/
VMINT vm_wstrcmp(VMWSTR str_1, VMWSTR str_2);

/* DOM-NOT_FOR_SDK-BEGIN */
/*****************************************************************************
 * FUNCTION
 *    vm_wstrcmp_ignore_case
 * DESCRIPTION
 *  UCS2 string compare without case sensitive
 * PARAMETERS
 *  str_1 : [IN]  string 1
 *  str_2 : [IN] string 2
 * RETURNS
 *  0 means the two string are same, non-zero means they are different.
 *****************************************************************************/
VMINT vm_wstrcmp_ignore_case(VMWSTR str_1, VMWSTR str_2);
/* DOM-NOT_FOR_SDK-END */

/*****************************************************************************
 * FUNCTION
 *    vm_wstarts_with
 * DESCRIPTION
 *  check specified string is started with specified string, and both of the two strings are encoding with UCS2
 * PARAMETERS
 *  s1 : [IN]  string to check
 *  s2 : [IN]  starting string
 * RETURNS
 *  0 if s1 start with s2, else return others.
 *****************************************************************************/
VMINT vm_wstarts_with(VMWSTR a, VMWSTR b);

VMINT vm_vwsprintf(VMWSTR outstr, VMINT size, const VMWSTR fmt, va_list args);
VMINT vm_wsprintf(VMWSTR outstr, VMINT size, const VMWSTR fmt, ...);


#ifdef __cplusplus
}
#endif

#endif /* VMSTDLIB_SDK_H_ */
