/*
  Copyright (c) 2014 MediaTek Inc.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License..

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
   See the GNU Lesser General Public License for more details.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "UARTClass.h"
#include "variant.h"
#include "vmlog.h"

static VM_DCL_HANDLE usb_device_handle = -1;
       
typedef struct  
{       
    VMINT 	result;
}vm_uart_ctrl_com_response;

// Constructors ////////////////////////////////////////////////////////////////

UARTClass::UARTClass( int usbNum, RingBuffer* pRx_buffer )
{
    _rx_buffer = pRx_buffer ;
    _usbNum = usbNum;
    uart_handle = -1;
}

void UartIrqHandler(void* parameter, VM_DCL_EVENT event, VM_DCL_HANDLE device_handle)
{
    if(event == VM_UART_READY_TO_READ)
    {
        char data[SERIAL_BUFFER_SIZE];
        int i;
        VM_DCL_STATUS status;
        VM_DCL_BUFF_LEN returned_len;

        status = vm_dcl_read(device_handle,(VM_DCL_BUFF*)data,SERIAL_BUFFER_SIZE,&returned_len,vm_dcl_get_ownerid());
        if(status<VM_DCL_STATUS_OK)
        {
            vm_log_info((char*)"read failed");
        }  
        if(device_handle == g_APinDescription[0].ulHandle)
        {
            for(i=0;i<returned_len;i++)
            {
                Serial1._rx_buffer->store_char(data[i]);
            }
        }
        else
        {
            for(i=0;i<returned_len;i++)
            {
                Serial._rx_buffer->store_char(data[i]);
            }
        }
    }
    else
    {
    }
}

// Public Methods //////////////////////////////////////////////////////////////

void UARTClass::begin( const uint32_t dwBaudRate )
{

    vm_sio_ctrl_dcb_t data;
	
    if(_usbNum == 2)
    {
        if(!changePinType(0, PIO_UART, &uart_handle))
            return;
	
        if(uart_handle == VM_DCL_HANDLE_INVALID)
            uart_handle = vm_dcl_open(vm_uart_port1,vm_dcl_get_ownerid());
    }
    else
    {
        uart_handle = vm_dcl_open(vm_usb_port1,vm_dcl_get_ownerid());
    }

    if(VM_DCL_HANDLE_INVALID==uart_handle) 
    {
        vm_log_info((char*)"UARTClass failed");
        return;
    }

    data.u4OwenrId = vm_dcl_get_ownerid();	
    data.rUARTConfig.u4Baud = dwBaudRate;
    data.rUARTConfig.u1DataBits = 8;
    data.rUARTConfig.u1StopBits = 1;
    data.rUARTConfig.u1Parity = 0;
    data.rUARTConfig.u1FlowControl = 1;
    data.rUARTConfig.ucXonChar = 0x11;
    data.rUARTConfig.ucXoffChar = 0x13;
    data.rUARTConfig.fgDSRCheck = 0;
    vm_dcl_control(uart_handle,VM_SIO_CMD_SET_DCB_CONFIG,(void *)&data);
    vm_dcl_registercallback(uart_handle,VM_UART_READY_TO_READ,(VM_DCL_CALLBACK)UartIrqHandler,(void*)NULL);

    if(_usbNum == 2)
    {
        setPinHandle(0, uart_handle);
    }
    else
    {
        usb_device_handle = uart_handle;
    }
}

void UARTClass::end( void )
{
// clear any received data
    _rx_buffer->_iHead = _rx_buffer->_iTail ;
    vm_dcl_close(uart_handle);
  
    if(_usbNum == 2)
    {
        g_APinDescription[0].ulHandle = VM_DCL_HANDLE_INVALID;
        g_APinDescription[0].ulPinType = PIO_DIGITAL;
    }
    else
    {
        usb_device_handle = -1;
    }
}

int UARTClass::available( void )
{
    return (uint32_t)(SERIAL_BUFFER_SIZE + _rx_buffer->_iHead - _rx_buffer->_iTail) % SERIAL_BUFFER_SIZE ;
}

int UARTClass::peek( void )
{
    if( _rx_buffer->_iHead == _rx_buffer->_iTail )
        return -1 ;

    return _rx_buffer->_aucBuffer[_rx_buffer->_iTail] ;
}

int UARTClass::read( void )
{
// if the head isn't ahead of the tail, we don't have any characters
    if ( _rx_buffer->_iHead == _rx_buffer->_iTail )
        return -1 ;

    uint8_t uc = _rx_buffer->_aucBuffer[_rx_buffer->_iTail] ;
    _rx_buffer->_iTail = (unsigned int)(_rx_buffer->_iTail + 1) % SERIAL_BUFFER_SIZE ;
    return uc ;
}


void UARTClass::flush( void )
{
    vm_dcl_sio_check_tx_buffer_t return_data;
    VM_DCL_STATUS status;
    VMINT command = 0;
    if(uart_handle != -1)
    {
        if(_usbNum == 2)
        {
            command = VM_UART_CHECK_TX_BUFFER;
        }
        else
        {
            command = VM_USB_CHECK_TX_BUFFER;   
        }
        status = vm_dcl_control(uart_handle, command, (vm_dcl_sio_check_tx_buffer_t*)&return_data);
        while(return_data.return_result!=1)
        {
            status = vm_dcl_control(uart_handle, command, (vm_dcl_sio_check_tx_buffer_t*)&return_data);
        }
    }
}

size_t UARTClass::write( const uint8_t uc_data )
{
    vm_dcl_sio_check_tx_buffer_t return_data;
    VM_DCL_STATUS status;
    VMINT command = 0;
    VM_DCL_BUFF_LEN writen_len = 0;
    int count = 0;
    if(uart_handle != -1)
    {
        if(_usbNum == 2)
        {
            command = VM_UART_CHECK_TX_BUFFER;
        }
        else
        {
            command = VM_USB_CHECK_TX_BUFFER; 
        }
        status = vm_dcl_control(uart_handle, command, (vm_dcl_sio_check_tx_buffer_t*)&return_data);
        while(return_data.return_result!=1)
        {
            status = vm_dcl_control(uart_handle, command, (vm_dcl_sio_check_tx_buffer_t*)&return_data);
        }  
        status = vm_dcl_write(uart_handle,(VM_DCL_BUFF*)&uc_data,1,&writen_len,vm_dcl_get_ownerid());
        return writen_len;
    }
    return 0;
  
}

UARTClass::operator bool()
{
    if(_usbNum == 2)
    {
        return true;
    }
	
    if(VM_DCL_HANDLE_INVALID != uart_handle) 
    {
        vm_uart_ctrl_com_response dtr;
        vm_dcl_control(uart_handle, 528, (vm_uart_ctrl_com_response*) &dtr);
        if (dtr.result == TRUE)
        {
            return true;
        }
    }
	
    delay(5);
    return false;

}


