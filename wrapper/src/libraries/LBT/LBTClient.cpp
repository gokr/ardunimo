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
#include "vmlog.h"
#include "BTClient.h"
#include "LBTClient.h"
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

vm_thread_mutex_struct client_mutex = {0};
LBTClientClass::LBTClientClass(LBTRingBuffer* pRx_buffer) : m_post_write(0), m_post_read(0)
{
  _rx_buffer = pRx_buffer;
}

boolean LBTClientClass::begin(void)
{
    _LTaskClass::begin();
    
	m_signal_write = vm_signal_init();
	m_signal_read = vm_signal_init();
	
    LBTClientBeginContext c;
    c.ptr = this;
    c.result = false;
	remoteCall(btClientBegin, &c);
	return c.result;
}

void LBTClientClass::end(void)
{
    _LTaskClass::stop();
	vm_signal_clean(m_signal_write);
	vm_signal_deinit(m_signal_write);
	vm_signal_clean(m_signal_read);
	vm_signal_deinit(m_signal_read);
	remoteCall(btClientEnd, (void*)NULL);
}

boolean LBTClientClass::connect(const char *MACAddr, const char* pinCode)
{
    LBTClientConnectContext c;
    c.is_set_pin = false;
    LBTAddress addr = {0};
    c.address = &addr;
    if (0 > addrStr2Mac(MACAddr, *(c.address)))
        return false;
    
    if(pinCode!= NULL)
    {
        int len = strlen(pinCode);
        if(len > LBT_PIN_CODE_BUFFER_SIZE - 1)
        {
            len = LBT_PIN_CODE_BUFFER_SIZE - 1;
        }
        c.is_set_pin = true;
        memset((void*)_pincode_buffer, 0, LBT_PIN_CODE_BUFFER_SIZE);
        memcpy((void*)_pincode_buffer, (void*)pinCode, len+1);
    }  
    
    remoteCall(btClientConnect, (void*)&c);

    return c.result;
}


boolean LBTClientClass::connect(LBTAddress &address, const char* pinCode)
{
    LBTClientConnectContext c;
    c.address = &address;
    c.is_set_pin = false;
    if(pinCode!= NULL)
    {
        int len = strlen(pinCode);
        if(len > LBT_PIN_CODE_BUFFER_SIZE - 1)
        {
            len = LBT_PIN_CODE_BUFFER_SIZE - 1;
        }
        c.is_set_pin = true;
        memset((void*)_pincode_buffer, 0, LBT_PIN_CODE_BUFFER_SIZE);
        memcpy((void*)_pincode_buffer, (void*)pinCode, len+1);
    }
    remoteCall(btClientConnect, (void*)&c);

    return c.result;
}

boolean LBTClientClass::connected(void)
{
	boolean result = true;
    remoteCall(btClientConnected, &result);

    return result;
}

int LBTClientClass::scan(size_t time_out)
{
    LBTClientScanContext c;
    c.time_out= time_out;
    remoteCall(btClientScan, (void*)&c);

    return c.number;
}

boolean LBTClientClass::getDeviceInfo(size_t index, LBTDeviceInfo* device_info)
{
    LBTClientGetDeviceInfoContext c;
    c.index = index;
    c.device_info = device_info;
    remoteCall(btClientGetDeviceInfo, (void*)&c);

    return c.result;
}

size_t LBTClientClass::write(const uint8_t *buf, size_t size)
{
    LBTClientReadWriteContext c;
	c.buf = (void*)buf;
	c.len = size;
	
	if (!m_post_write)
	{
        APP_LOG((char*)"LBTClientClass::write wait");
        vm_signal_wait(m_signal_write); // wait for VM_SRV_SPP_EVENT_READY_TO_WRITE
        APP_LOG((char*)"LBTClientClass::write wait ok");
    }
    m_post_write = 0;
    vm_signal_clean(m_signal_write);

    remoteCall(btClientWrite, (void*)&c);
    m_post_write = 1;

	return c.lenProcessed;
}

void LBTClientClass::post_signal_write()
{
    APP_LOG((char*)"LBTClientClass::post_signal_write");
	vm_signal_post(m_signal_write);
	m_post_write = 1;
}

void LBTClientClass::post_signal_read()
{
    APP_LOG((char*)"LBTClientClass::post_signal_read");
	vm_signal_post(m_signal_read);
	m_post_read = 1;
}

int LBTClientClass::available(void)
{
  return (uint32_t)(LBT_SERIAL_BUFFER_SIZE + _rx_buffer->_iHead - _rx_buffer->_iTail) % LBT_SERIAL_BUFFER_SIZE;
}

int LBTClientClass::peek(void)
{
  if(_rx_buffer->_iHead == _rx_buffer->_iTail)
  	return -1;
  return _rx_buffer->_aucBuffer[_rx_buffer->_iTail];
}

int LBTClientClass::read(void)
{

  if(_rx_buffer->_iHead == _rx_buffer->_iTail)
  	return -1;
	if(client_mutex.guard == 0)
	{
		vm_mutex_create(&client_mutex);
	}
  vm_mutex_lock(&client_mutex);
  uint8_t uc = _rx_buffer->_aucBuffer[_rx_buffer->_iTail];
  _rx_buffer->_iTail = (unsigned int)(_rx_buffer->_iTail + 1) % LBT_SERIAL_BUFFER_SIZE;
  vm_mutex_unlock(&client_mutex);
  return uc;
}

void LBTClientClass::flush(void)
{
  while(read()!=-1);
}

size_t LBTClientClass::write(const uint8_t data)
{
  LBTClientReadWriteContext c;
	c.buf = (void*)&data;
	c.len = 1;
	
	if (!m_post_write)
	{
        APP_LOG((char*)"LBTClientClass::write wait");
        vm_signal_wait(m_signal_write); // wait for VM_SRV_SPP_EVENT_READY_TO_WRITE
        APP_LOG((char*)"LBTClientClass::write wait ok");
    }
    m_post_write = 0;
    vm_signal_clean(m_signal_write);

    remoteCall(btClientWrite, (void*)&c);
    m_post_write = 1;

	return c.lenProcessed;
}

LBTRingBuffer LBTClient_rx_buffer;
LBTClientClass LBTClient(&LBTClient_rx_buffer);


