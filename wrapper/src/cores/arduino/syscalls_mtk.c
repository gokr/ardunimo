/*
  Copyright (c) 2011 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

  Modified 20 Aug 2014 by MediaTek Inc.
  
*/

/**
  * \file syscalls_mtk.c
  *
  * Implementation of newlib syscall.
  *
  */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/


#include "syscalls.h"

#include <stdio.h>
#include <stdarg.h>
#if defined (  __GNUC__  ) /* GCC CS3 */
  #include <sys/types.h>
  #include <sys/stat.h>
#endif

#include "vmsys.h"
#include "vmlog.h"
#include "vmdatetime.h"

#undef errno
extern int errno ;
extern int  _end ;

unsigned int g_size = 1024*200;
unsigned char * base_address = NULL;

#define RESERVED_MEMORY_SIZE  270*1024

extern void _exit( int status ) ;
extern void _kill( int pid, int sig ) ;
extern int _getpid ( void ) ;

typedef VMINT (*vm_get_sym_entry_t)(char* symbol);
vm_get_sym_entry_t vm_get_sym_entry;

typedef VMUINT (*_vm_get_total_heap_size_t)(void);
_vm_get_total_heap_size_t _vm_get_total_heap_size = NULL;
VMUINT vm_get_total_heap_size(void)
{
    if (NULL == _vm_get_total_heap_size)
        _vm_get_total_heap_size = (_vm_get_total_heap_size_t)vm_get_sym_entry((char*)"vm_get_total_heap_size");

    if (NULL != _vm_get_total_heap_size)
        return _vm_get_total_heap_size();
    return 0;
}

typedef VMINT (*_vm_set_time_t)(vm_time_t* time);
_vm_set_time_t _vm_set_time = NULL;

VMINT vm_set_time(vm_time_t* time)
{
    if (NULL == _vm_set_time)
        _vm_set_time = (_vm_set_time_t)vm_get_sym_entry("vm_set_time");

    if (NULL != _vm_set_time)
        return _vm_set_time(time);

    return (VMINT )-1;
}

extern caddr_t _sbrk ( int incr )
{
    static unsigned char *heap = NULL ;
    static unsigned char *base = NULL ;
    unsigned char *prev_heap ;

    if ( heap == NULL )
    {
       base = (unsigned char *)base_address; 
	if(base == NULL)
	{
		vm_log_fatal("malloc failed");
	}
	else
	{
		heap = base;
		vm_log_info("init memory success");
	}
    }
    
    if (heap + incr > base + g_size) {
        vm_log_fatal("memory not enough");
    }
    
    prev_heap = heap;

    heap += incr ;

    return (caddr_t) prev_heap ;
}


extern int link( char *cOld, char *cNew )
{
    return -1 ;
}

extern int _close( int file )
{
    return -1 ;
}

extern int _fstat( int file, struct stat *st )
{
    st->st_mode = S_IFCHR ;

    return 0 ;
}

extern int _isatty( int file )
{
    return 1 ;
}

extern int _lseek( int file, int ptr, int dir )
{
    return 0 ;
}

extern int _read(int file, char *ptr, int len)
{
    return 0 ;
}

extern int _write( int file, char *ptr, int len )
{
    return len ;
}

extern void _exit( int status )
{
    for ( ; ; ) ;
}

extern void _kill( int pid, int sig )
{
    return ;
}

extern int _getpid ( void )
{
    return -1 ;
}

int __cxa_guard_acquire(int *g) {return !*(char *)(g);};
void __cxa_guard_release (int *g) {*(char *)g = 1;};

typedef void (**__init_array) (void);

void __libc_init_array(void);

void gcc_entry(unsigned int entry, unsigned int init_array_start, unsigned int count) 
{
  __init_array ptr;
  int i;
  VMUINT size = 0;

  vm_get_sym_entry = (vm_get_sym_entry_t)entry;
  
  size = vm_get_total_heap_size();
  
  if(size == 0)
  {
  	base_address = vm_malloc(g_size);
  }
  else
  {
  	if(size > RESERVED_MEMORY_SIZE)
		size -= RESERVED_MEMORY_SIZE;
	
  	base_address = vm_malloc(size);
    	g_size = size;
}

  vm_log_info("init lib arrays");

  __libc_init_array();
  
  ptr = (__init_array)init_array_start;

  for (i = 1; i < count; i++)
  {
  		ptr[i]();
  } 
  vm_main();
}

