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
#include "LTcpServer.h"
#include "LTcpClient.h"
#include "LTask.h"
#include "vmconn.h"
#include "vmtcp.h"
#include "vmlog.h"
#include "vmsock.h"
#include "vmnwsetting.h"

LTcpServer::LTcpServer(uint16_t port):
	m_port(port),
	m_handle(-1)
{
}

void LTcpServer::serverCallback(VMINT handle, VMINT event, VMINT param, void *user_data)
{
	LTcpServer *pThis = (LTcpServer*)user_data;
	vm_log_info("serverCallback handle=%d, evt=%d, param=%d", handle, event, param);
	switch(event)
	{
	case VM_SOC_SVR_EVT_ACTIVED:
		// server ready
		pThis->m_handle = handle;
		LTask.post_signal();
		break;
    case VM_SOC_SVR_EVT_DEACTIVATED:
		pThis->m_handle = -1;
		LTask.post_signal();
		break;
	case VM_SOC_SVR_EVT_ACCEPT:
		vm_log_info("new client handle=%d", param);
		pThis->m_clients.push_back(param);
		break;
    case VM_SOC_SVR_EVT_READ:
		break;
    case VM_SOC_SVR_EVT_WRITE:
		break;
    case VM_SOC_SVR_EVT_CLOSED:
		break;
    case VM_SOC_SVR_EVT_FAILED:
		vm_log_info("open server on port=%d failed param=%d", pThis->m_port, param);
		pThis->m_handle = -1;
		LTask.post_signal();
		break;
	}

}

boolean LTcpServer::initServer(void *userData)
{
	LTcpServer* pThis = (LTcpServer*)userData;
	pThis->m_handle = vm_soc_svr_init(pThis->getAPN(), pThis->m_port, pThis, &serverCallback);
	vm_log_info("initServer on port=%d ret=%d", pThis->m_port, pThis->m_handle);
	if (pThis->m_handle < 0 && pThis->m_handle != -8)
	{
		pThis->m_handle = -1;
		return true;
	}
	return false;
}

void LTcpServer::begin()
{
	LTask.remoteCall(initServer, this);
	return;
}

boolean LTcpServer::deinitServer(void *userData)
{
	LTcpServer* pThis = (LTcpServer*)userData;
	if(pThis->m_handle > 0)
	{
		VMINT ret = vm_soc_svr_deinit(pThis->m_handle);
		vm_log_info("vm_soc_svr_deinit on handle=%d ret=%d", pThis->m_handle, ret);
	}
	return false;
}

void LTcpServer::end()
{
	LTask.remoteCall(deinitServer, this);
	return;
}

struct LTcpAcceptConnectionContext
{
	LTcpServer *pInst;
	VMINT hClient;
	VMINT status;
};

boolean LTcpServer::acceptConnection(void *userData)
{
	LTcpAcceptConnectionContext *pCntx = (LTcpAcceptConnectionContext*)userData;
	vm_log_info("acceptConnection() client count=%d", pCntx->pInst->m_clients.size());	
	if (pCntx->pInst->m_clients.size() > 0)
	{		
		const VMINT hClient = pCntx->pInst->m_clients.back();
		pCntx->pInst->m_clients.pop_back();
		pCntx->hClient = hClient;
	}
	else
	{
		pCntx->hClient = -1;
	}
	return true;
}

void LTcpServer::availableImpl(VMINT& hClient, VMINT& hServer)
{
	vm_log_info((char*)__FUNCTION__);
	// use async to open server port
	LTcpAcceptConnectionContext cntx;
	cntx.pInst = this;
	cntx.hClient = -1;
	LTask.remoteCall(&acceptConnection, &cntx);

	hClient = cntx.hClient;
	hServer = m_handle;
	
	return;
}

size_t LTcpServer::write(uint8_t data)
{
	return write(&data, 1);
}

struct LTcpServerWriteContext
{
	LTcpServer *pInst;
	VMINT totalWritten;
	const uint8_t *buf;
	size_t size;
};

boolean LTcpServer::wifiServerWrite(void *userData)
{
	LTcpServerWriteContext *pCntx = (LTcpServerWriteContext*)userData;
	LTcpServer *pThis = pCntx->pInst;
	pCntx->totalWritten = 0;
	for(int i = 0; i < pThis->m_clients.size(); ++i)
	{
		VMINT written = vm_tcp_write_sync(pThis->m_clients[i], (void*)pCntx->buf, (VMINT)pCntx->size);
		if(written > 0)
		{
			pCntx->totalWritten += written;
		}
	}
}

size_t LTcpServer::write(const uint8_t *buf, size_t size)
{
	LTcpServerWriteContext cntx;
	cntx.pInst = this;
	cntx.totalWritten = 0;
	cntx.buf = buf;
	cntx.size = size;
	LTask.remoteCall(&wifiServerWrite, &cntx);
	return cntx.totalWritten;
}

struct LTcpServerIPContext
{
	VMINT handle;
	IPAddress result;
};

boolean wifiServerIP(void *userData)
{
	LTcpServerIPContext *pCntx = (LTcpServerIPContext*)userData;
	VMUINT8 ip[VM_WLAN_PROF_MAX_IP_ADDR_LEN] = {0};
	// note that vm_soc_get_account_localip()
	// does not take "server handle" as input
	// but take "socket ID" as input instead.
	const VMINT sockID = vm_soc_svr_get_soc_id(pCntx->handle);
	VMINT ret = vm_soc_get_account_localip(sockID, ip);
	vm_log_info("get socket IP ret=%d", ret);
	pCntx->result = IPAddress(ip);
	return true;
}

IPAddress LTcpServer::serverIP()
{
	if (-1 == m_handle)
	{
		return IPAddress();
	}

	LTcpServerIPContext cntx;
	
	cntx.handle = m_handle;
	LTask.remoteCall(&wifiServerIP, &cntx);
	return cntx.result;
}

VMINT LTcpServer::getAPN() const
{
	vm_log_error("LTcpServer::getAPN called. return -1");
	return -1;
}