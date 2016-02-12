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
#include "Arduino.h"
#include "BTServer.h"
#include "LBTServer.h"
#include "vmlog.h"
#include "vmthread.h"
#include "LBT.h"
extern int addrStr2Mac(const char *MACAddr, LBTAddress &address);
extern void app_log_file(char *fmt, ...);
#ifdef LBT_DEBUG
#define APP_LOG(...) app_log_file(__VA_ARGS__); \
    vm_log_info(__VA_ARGS__)
#else
#define APP_LOG(...)
#endif

vm_thread_mutex_struct server_mutex = {0};
LBTServerClass::LBTServerClass(LBTRingBuffer* pRx_buffer) : m_post_write(0), m_post_read(0)
{
  _rx_buffer = pRx_buffer;
}


boolean LBTServerClass::begin(const uint8_t* buf, const uint8_t* pinCode)
{
    APP_LOG((char*)"LBTServerClass::begin");
    _LTaskClass::begin();
    LBTServerBeginContext c;
    c.is_set_pin = false;
    if(pinCode!= NULL)
    {
    	int len = strlen((char*)pinCode);
    	if(len > LBT_PIN_CODE_BUFFER_SIZE - 1)
    	{
    		len = LBT_PIN_CODE_BUFFER_SIZE - 1;
    	}
    	c.is_set_pin = true;
    	memcpy(_pincode_buffer, pinCode, len+1);
    }
    
	m_signal_write = vm_signal_init();
	m_signal_read = vm_signal_init();


    c.name = (void*)buf;
    c.ptr = this;
    remoteCall(btServerBegin, &c);
    APP_LOG((char*)"LBTServerClass::end %d", c.result);
    return c.result;
}

void LBTServerClass::end(void)
{
    _LTaskClass::stop();
    
	vm_signal_clean(m_signal_write);
	vm_signal_deinit(m_signal_write);
	vm_signal_clean(m_signal_read);
	vm_signal_deinit(m_signal_read);
	remoteCall(btServerEnd, (void*)NULL);
}

boolean LBTServerClass::accept(size_t time_out)
{
    LBTServerAcceptContext c;
    c.time_out = time_out;
    c.address = NULL;
    remoteCall(btServerAccept, (void*)&c);

    return c.result;
}


boolean LBTServerClass::accept(size_t time_out, const char *MACAddr)
{
    LBTServerAcceptContext c;
    c.time_out = time_out;
    LBTAddress addr = {0};
    c.address = &addr;
    if (0 > addrStr2Mac(MACAddr, *(c.address)))
        return false;
    remoteCall(btServerAccept, (void*)&c);

    return c.result;
}

boolean LBTServerClass::connected(void)
{
	boolean result = true;
    remoteCall(btServerConnected, &result);

    return result;

}

boolean LBTServerClass::getHostDeviceInfo(LBTDeviceInfo* device_info)
{
    LBTServerGetHostDeviceInfoContext c;
    c.device_info = device_info;
    remoteCall(btServerGetHostDeviceInfo, (void*)&c);

    return c.result;
}

size_t LBTServerClass::write(const uint8_t *buf, size_t size)
{
    LBTServerReadWriteContext c;
	c.buf = (void*)buf;
	c.len = size;

	if (!m_post_write)
	{
        APP_LOG((char*)"LBTServerClass::write wait");
        vm_signal_wait(m_signal_write); // wait for VM_SRV_SPP_EVENT_READY_TO_WRITE
        APP_LOG((char*)"LBTServerClass::write wait ok");
    }
    vm_signal_clean(m_signal_write);
    m_post_write = 0;
    
    remoteCall(btServerWrite, (void*)&c);
    m_post_write = 1;

	return c.lenProcessed;
}

void LBTServerClass::post_signal_write()
{
    APP_LOG((char*)"LBTServerClass::post_signal_write");
	vm_signal_post(m_signal_write);
	m_post_write = 1;
}

void LBTServerClass::post_signal_read()
{
    APP_LOG((char*)"LBTServerClass::post_signal_read");
	vm_signal_post(m_signal_read);
	m_post_read = 1;
}

uint8_t a2x(char ch)
{

	switch(ch)
	{
	case '0':
	    return 0;
	case '1':
		return 1;
	case '2':
		return 2;
	case '3':
		return 3;
	case '4':
		return 4;
	case '5':
		return 5;
	case '6':
		return 6;
	case '7':
		return 7;
	case '8':
		return 8;
	case '9':
		return 9;
	case 'A':
	case 'a':
		return 10;
	case 'B':
	case 'b':
		return 11;
	case 'C':
	case 'c':
		return 12;
	case 'D':
	case 'd':
		return 13;
	case 'E':
	case 'e':
		return 14;
	case 'F':
	case 'f':
		return 15;
	default:
		break;;
	}


	return -1;

}

int addrStr2Mac(const char *MACAddr, LBTAddress &address)
{
    if (17 != strlen(MACAddr))
    {
        return -1;
    }

    if (MACAddr[2] != ':' || MACAddr[5] != ':' ||
        MACAddr[8] != ':' || MACAddr[11] != ':' || MACAddr[14] != ':')
    {
        return -2;
    }

    char tmp[13] = {0};
    strncpy(tmp, MACAddr, 2);
    strncpy(tmp + 2, MACAddr + 3, 2);
    strncpy(tmp + 4, MACAddr + 6, 2);
    strncpy(tmp + 6, MACAddr + 9, 2);
    strncpy(tmp + 8, MACAddr + 12, 2);
    strncpy(tmp + 10, MACAddr + 15, 2);

    for (int i = 0; i < 12; ++i)
    {
        if (0 > a2x(tmp[i]))
            return -3;
    }

    address.nap[1] = a2x(tmp[0])*16 + a2x(tmp[1]);
    address.nap[0] = a2x(tmp[2])*16 + a2x(tmp[3]);
    address.uap = a2x(tmp[4])*16 + a2x(tmp[5]);
    address.lap[2] = a2x(tmp[6])*16 + a2x(tmp[7]);
    address.lap[1] = a2x(tmp[8])*16 + a2x(tmp[9]);
    address.lap[0] = a2x(tmp[10])*16 + a2x(tmp[11]);

    return 0;
}


int LBTServerClass::available(void)
{
  return (uint32_t)(LBT_SERIAL_BUFFER_SIZE + _rx_buffer->_iHead - _rx_buffer->_iTail) % LBT_SERIAL_BUFFER_SIZE;
}

int LBTServerClass::peek(void)
{
  if(_rx_buffer->_iHead == _rx_buffer->_iTail)
  	return -1;
  return _rx_buffer->_aucBuffer[_rx_buffer->_iTail];
}

int LBTServerClass::read(void)
{

  if(_rx_buffer->_iHead == _rx_buffer->_iTail)
  {
  	return -1;
  }
	if(server_mutex.guard == 0)
	{
		vm_mutex_create(&server_mutex);
	}	
 	vm_mutex_lock(&server_mutex); 
  uint8_t uc = _rx_buffer->_aucBuffer[_rx_buffer->_iTail];
  _rx_buffer->_iTail = (unsigned int)(_rx_buffer->_iTail + 1) % LBT_SERIAL_BUFFER_SIZE;
  vm_mutex_unlock(&server_mutex);
  return uc;
  
}

void LBTServerClass::flush(void)
{
  while(read()!=-1);
}

size_t LBTServerClass::write(const uint8_t data)
{
  LBTServerReadWriteContext c;
	c.buf = (void*)&data;
	c.len = 1;

	if (!m_post_write)
	{
        APP_LOG((char*)"LBTServerClass::write wait");
        vm_signal_wait(m_signal_write); // wait for VM_SRV_SPP_EVENT_READY_TO_WRITE
        APP_LOG((char*)"LBTServerClass::write wait ok");
    }
    vm_signal_clean(m_signal_write);
    m_post_write = 0;
    
    remoteCall(btServerWrite, (void*)&c);
    m_post_write = 1;

	return c.lenProcessed;
}


LBTRingBuffer LBTServer_rx_buffer;
LBTServerClass LBTServer(&LBTServer_rx_buffer);

