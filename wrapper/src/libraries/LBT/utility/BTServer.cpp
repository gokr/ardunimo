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

#include "LBT.h"
#include "vmbtcm.h"
#include "vmtimer.h"
#include "vmbtspp.h"
#include "vmlog.h"
#include "BTServer.h"
#include "LBTServer.h"
#include "vmthread.h"
#include "vmstdlib.h"
#include "vmio.h"
#include "vmchset.h"

#define BT_NAME "SPP"
#define LOG_BUF_SIZE 96
#define FILE_PATH_SIZE 16
#define SPP_DATA "Hello SPP!"
#ifdef LBT_DEBUG
#define APP_LOG(...) app_log_file(__VA_ARGS__); \
    vm_log_info(__VA_ARGS__)
#else
#define APP_LOG(...)
#endif
static VMINT flag_delete_log;
static VMINT g_flag_visibility_event = 0;
extern vm_thread_mutex_struct server_mutex;

extern void app_log_file(char *fmt, ...);



#define SPP_UUID 0x1101

typedef enum
{
    BT_SERVER_IDLE = 0,
    BT_SERVER_BEGINING = 1, // not even power on, need to power on first
    BT_SERVER_POWERING_ON = 2, // waiting for power on to process
    BT_SERVER_READY = 3, // power on and init done
    BT_SERVER_ENDING = 4, // not event powr off, need to power off first
    BT_SERVER_POWERING_OFF = 5 // waiting for power off to process
}bt_server_status;

struct btServerContext
{
    LBTServerClass *ptr;
    VMINT btcm_hdl;
    VMINT btspp_hdl;
    VMINT btspp_buf_size;
    void* btspp_buf;
    VMINT accept_tid;

    bt_server_status server_status;
    VMINT conn_id;
    boolean waiting_for_accept;
    boolean* waiting_result_p;
    void* device_name_p;
    LBTAddress address;
    boolean mac_only;

    btServerContext():
        btcm_hdl(-1),
        btspp_hdl(-1),
        btspp_buf_size(0),
        btspp_buf(NULL),
        accept_tid(-1),
        server_status(BT_SERVER_IDLE),
        conn_id(-1),
        waiting_for_accept(false),
        waiting_result_p(NULL),
        device_name_p(NULL)
    {
        APP_LOG("[BTC]btServerContext, server_status[%d]", server_status);
    }

};

btServerContext g_serverContext;

static VMINT bt_server_init_spp(uint8_t* name);
static boolean bt_server_end_spp();

static void bt_server_btcm_cb(VMUINT evt, void * param, void * user_data)
{

    APP_LOG("[BTC]bt_server_btcm_cb, evt = %d, client_status = %d", evt, g_serverContext.server_status);

    switch (evt)
    {
        case VM_SRV_BT_CM_EVENT_ACTIVATE:
        {
            // waiting for power on to process
            if (g_serverContext.server_status == BT_SERVER_POWERING_ON)
            {
                VMINT ret = bt_server_init_spp((uint8_t*)g_serverContext.device_name_p);
                APP_LOG("[BTC]bt_server_init_spp[%d]", ret);

                if(ret<0)
                {
                    *(g_serverContext.waiting_result_p) = false;                
                    g_serverContext.waiting_result_p = NULL;

                    if(bt_server_end_spp())
                    {
                        g_serverContext.ptr->post_signal();
                    }
                }
                /*
                else if (ret == 0)
                {
                    *(g_serverContext.waiting_result_p) = true;
                    g_serverContext.waiting_result_p = NULL;
                    g_serverContext.ptr->post_signal();
                }*/

            }
            else if (g_serverContext.server_status == BT_SERVER_ENDING)
            {
                VMINT ret = vm_btcm_switch_off();

                if(VM_SRV_BT_CM_RESULT_SUCCESS == ret)
                {
                    //wait for callback to process
                    g_serverContext.server_status = BT_SERVER_POWERING_OFF;
                }
                else
                {
                    if(g_serverContext.btcm_hdl >= 0)
                    {
                        vm_btcm_exit(g_serverContext.btcm_hdl);
                        g_serverContext.btcm_hdl = -1;
                    }
                    
                    g_serverContext.server_status = BT_SERVER_IDLE;
                    g_serverContext.ptr->post_signal();
                }
            }
                
            break;
        }

        case VM_SRV_BT_CM_EVENT_DEACTIVATE:
        {
            if (g_serverContext.server_status == BT_SERVER_BEGINING)
            {
                VMINT ret = vm_btcm_switch_on();
                
                if(VM_SRV_BT_CM_RESULT_SUCCESS == ret)
                {
                    //wait for callback to process
                    g_serverContext.server_status = BT_SERVER_POWERING_ON;
                }
                else
                {
                    *(g_serverContext.waiting_result_p) = false;
                    g_serverContext.waiting_result_p = NULL;

                    if(bt_server_end_spp())
                    {
                        g_serverContext.ptr->post_signal();
                    }
                }
            }
            else if(g_serverContext.server_status == BT_SERVER_POWERING_OFF)
            {
                if(g_serverContext.btcm_hdl >= 0)
                {
                    vm_btcm_exit(g_serverContext.btcm_hdl);
                    g_serverContext.btcm_hdl = -1;
                }
                
                g_serverContext.server_status = BT_SERVER_IDLE;
                g_serverContext.ptr->post_signal();
            }
                
            break;
        }

        case VM_SRV_BT_CM_EVENT_SET_VISIBILITY:
        {
            APP_LOG("[BTC] VM_SRV_BT_CM_EVENT_SET_VISIBILITY [%d]", g_flag_visibility_event);
            if(g_flag_visibility_event == 1)
            {
                *(g_serverContext.waiting_result_p) = true;
                g_serverContext.waiting_result_p = NULL;
                g_serverContext.ptr->post_signal();
                g_flag_visibility_event = 0;
            }
            break;
        }
        
        case VM_SRV_BT_CM_EVENT_SET_NAME:
        {
            break;
        }

        case VM_SRV_BT_CM_EVENT_PAIR_IND:
        {
        	  vm_srv_bt_cm_pair_ind_struct *event = (vm_srv_bt_cm_pair_ind_struct *)param;
        	  vm_bt_cm_send_passkey(&event->dev_addr, (VMUINT8*)LBTServer._pincode_buffer, VM_TRUE);
            break;
        }
        default:
        {
            break;
        }
    }


}

static void bt_server_accept_timeout_cb(VMINT tid)
{
    APP_LOG("bt_server_accept_timeout_cb tid[%d][%d]", tid, g_serverContext.accept_tid);
    if (tid == g_serverContext.accept_tid && g_serverContext.waiting_for_accept)
    {
        g_serverContext.waiting_for_accept = false;
        vm_delete_timer(g_serverContext.accept_tid);
        g_serverContext.accept_tid = -1;

        *(g_serverContext.waiting_result_p) = false;
        g_serverContext.waiting_result_p = NULL;

        g_serverContext.ptr->post_signal();
    }
}

static int bt_server_spp_read(void* data)
{
	
	  VMINT ret = 0;
	  VMINT i = 0;
    if(g_serverContext.conn_id < 0)
    {
        //not connected yet

        APP_LOG((char*)"[BTC]bt_server_spp_read : not connected yet");

        return true;
    }
    char *readdata = new char[LBT_SERIAL_BUFFER_SIZE];
    if(readdata == NULL)
  	{
  		APP_LOG((char*)"[BTC]bt_server_spp_read : allocate memory fail");
  		return false;
  	}
    ret = vm_btspp_read(g_serverContext.conn_id, (void*)readdata, LBT_SERIAL_BUFFER_SIZE);

    APP_LOG("[BTC]bt_server_spp_read, ret: %d", ret);

    if (ret < 0)
    {
       APP_LOG((char*)"[BTC]bt_server_spp_read : read data fail");

    }
    else 
    {

    	  if(server_mutex.guard == 0)
    	  {
    	      vm_mutex_create(&server_mutex);
    	  }
    	  vm_mutex_lock(&server_mutex);
        for(i=0;i<ret;i++)
        {
        	LBTServer._rx_buffer->store_char(readdata[i]);
        }
        vm_mutex_unlock(&server_mutex);

        APP_LOG((char*)"[BTC]btServerRead : read data success");
    }
    delete[] readdata;
	return ret;
}

static void bt_server_spp_cb(VMUINT evt, void * param, void * user_data)
{
    vm_srv_spp_event_cntx* cntx = (vm_srv_spp_event_cntx*)param;
    
    APP_LOG((char*)"[BTS]bt_server_spp_cb %d", evt);

    switch(evt)
    {        
        case VM_SRV_SPP_EVENT_CONNECT:
        {
            if (cntx->ret)
            {
                //connect successfully
                if(g_serverContext.waiting_result_p != NULL)
                {
                    *(g_serverContext.waiting_result_p) = true;
                }
                g_serverContext.conn_id = cntx->conn_id;
            }
            else
            {
                //connnet fail
                if(g_serverContext.waiting_result_p != NULL)
                {
                    *(g_serverContext.waiting_result_p) = false;
                }
            }

            if(g_serverContext.waiting_result_p != NULL)
            {
                g_serverContext.waiting_result_p = NULL;
                g_serverContext.ptr->post_signal();
                bt_server_accept_timeout_cb(g_serverContext.accept_tid);
            }
            else
            {
                // reconnection
            }

            break;
        }

        case VM_SRV_SPP_EVENT_DISCONNECT:
        {
            g_serverContext.conn_id = -1;
            APP_LOG((char*)"[BTS]VM_SRV_SPP_EVENT_DISCONNECT");
            break;
        }

        case VM_SRV_SPP_EVENT_AUTHORIZE:
        {
            if (g_serverContext.mac_only)
            {
                vm_srv_bt_cm_bt_addr curr_addr = {0};
                vm_srv_bt_cm_bt_addr tmp = {0};
                vm_btspp_get_dev_addr(cntx->conn_id, &curr_addr);
                tmp.nap = (VMUINT16)((g_serverContext.address.nap[1] << 8) | g_serverContext.address.nap[0]);
                tmp.uap = (VMUINT8)g_serverContext.address.uap;
                tmp.lap = (VMUINT)((g_serverContext.address.lap[2] << 16) | (g_serverContext.address.lap[1] << 8) | g_serverContext.address.lap[0]);
                APP_LOG("[BTS AUTH] tmp addr: nap:%x, uap:%x, lap:%x",
                            tmp.nap,
                            tmp.uap,
                            tmp.lap);
                APP_LOG("[BTS AUTH] curr_addr: nap:%x, uap:%x, lap:%x",
                            curr_addr.nap,
                            curr_addr.uap,
                            curr_addr.lap);
                if ((tmp.nap != curr_addr.nap) || 
                    (tmp.uap != curr_addr.uap) || 
                    (tmp.lap != curr_addr.lap))
                {
                    vm_btspp_reject(cntx->conn_id);
                    break;
                }
            }

            if(g_serverContext.waiting_for_accept)
            {
                VMINT ret = vm_btspp_accept(cntx->conn_id, g_serverContext.btspp_buf, g_serverContext.btspp_buf_size, g_serverContext.btspp_buf_size);
                g_serverContext.waiting_for_accept = false;
                vm_delete_timer(g_serverContext.accept_tid);
                g_serverContext.accept_tid = -1;
            }
            else
            {
                vm_btspp_reject(cntx->conn_id);
            }


            
            break;
        }

        case VM_SRV_SPP_EVENT_BIND_FAIL:
        {
            break;
        }

        case VM_SRV_SPP_EVENT_READY_TO_WRITE:
        {
            g_serverContext.ptr->post_signal_write();
            break;
        }

        case VM_SRV_SPP_EVENT_READY_TO_READ:
        {
        	  bt_server_spp_read(NULL);
        	#if(0)
            g_serverContext.ptr->post_signal_read();
            #endif
            break;
        }


    }

}

static VMINT bt_server_init_spp(uint8_t* name)
{

    VMUINT evt_mask = VM_SRV_SPP_EVENT_BIND_FAIL |
                      VM_SRV_SPP_EVENT_AUTHORIZE |
                      VM_SRV_SPP_EVENT_CONNECT |
                      VM_SRV_SPP_EVENT_READY_TO_WRITE |
                      VM_SRV_SPP_EVENT_READY_TO_READ |
                      VM_SRV_SPP_EVENT_DISCONNECT;

    
    g_serverContext.btspp_hdl = vm_btspp_open(evt_mask,bt_server_spp_cb,NULL);
    
    if(g_serverContext.btspp_hdl < 0)
    {
        APP_LOG((char*)"[BTC]bt_server_init_spp hdl[%d]", g_serverContext.btspp_hdl);
        return g_serverContext.btspp_hdl;
    }
    vm_btspp_set_security_level(g_serverContext.btspp_hdl,VM_SRV_SPP_SEC_NAN);

    VMINT min_buf_size = vm_btspp_get_min_buf_size();
    g_serverContext.btspp_buf = vm_calloc(min_buf_size);
    g_serverContext.btspp_buf_size = min_buf_size / 2;

    if(g_serverContext.btspp_buf == NULL)
    {
        APP_LOG((char*)"[BTC]bt_server_init_spp fail : alloc buffer");
        return -1;
    }

    VMINT ret = vm_btspp_bind(g_serverContext.btspp_hdl, SPP_UUID);

    if(ret < 0)
    {
        APP_LOG((char*)"[BTC]bt_server_init_spp fail : btspp_bind");
        return -1;
    }

    if(name != NULL)
    {
        ret = vm_btcm_set_host_name((VMUINT8*)name);
    }

    if(ret < 0)
    {
        APP_LOG((char*)"[BTC]bt_server_init_spp fail : btcm_set_host_name");
        return -1;
    }

    if (VM_SRV_BT_CM_VISIBILITY_ON == vm_btcm_srv_get_visibility())
    {
        APP_LOG((char*)"[BTC]bt_server_init_spp get visibility on");
        *(g_serverContext.waiting_result_p) = true;
        g_serverContext.waiting_result_p = NULL;
        g_serverContext.ptr->post_signal();
        ret = 0;
    }
    else
    {
        g_flag_visibility_event = 1;       
        ret = vm_btcm_srv_set_visibility(VM_SRV_BT_CM_VISIBILITY_ON);
        APP_LOG((char*)"[BTC]bt_server_init_spp fail set visibility %d", ret);
        if (VM_SRV_BT_CM_RESULT_SUCCESS == ret)
        {
            ret = 1;
        }
    }
    APP_LOG("[BTC]bt_server_init_spp ret[%d], btspp_hdl=%d", ret, g_serverContext.btspp_hdl);
    return ret;

}

static boolean bt_server_end_spp()
{
    if(g_serverContext.btspp_hdl >= 0)
    {
        vm_btspp_close(g_serverContext.btspp_hdl);
        g_serverContext.btspp_hdl = -1;
    }

    if(g_serverContext.btspp_buf != NULL)
    {
        vm_free(g_serverContext.btspp_buf);
        g_serverContext.btspp_buf = NULL;
    }

    if(g_serverContext.conn_id >= 0)
    {
        g_serverContext.conn_id = -1;
    }

    VMINT ret = vm_btcm_get_power_status();

    if (VM_SRV_BT_CM_POWER_ON == ret)
    {
        VMINT ret = vm_btcm_switch_off();

        if(VM_SRV_BT_CM_RESULT_SUCCESS == ret)
        {
            //wait for callback to process
            g_serverContext.server_status = BT_SERVER_POWERING_OFF;
            return false;
        }
    }
    else if (VM_SRV_BT_CM_POWER_SWITCHING_ON == ret)
    {
        g_serverContext.server_status = BT_SERVER_ENDING;
        return false;
    }
    else if (VM_SRV_BT_CM_POWER_SWITCHING_OFF == ret)
    {
        g_serverContext.server_status = BT_SERVER_POWERING_OFF;
        return false;
    }

    // VM_SRV_BT_CM_POWER_OFF
    if(g_serverContext.btcm_hdl >= 0)
    {
        vm_btcm_exit(g_serverContext.btcm_hdl);
        g_serverContext.btcm_hdl = -1;
    }

    g_serverContext.server_status = BT_SERVER_IDLE;

    return true;

}

boolean btServerBegin(void *userData)
{
    LBTServerBeginContext* pContext = (LBTServerBeginContext*)userData ;

    boolean* result = (boolean*) userData;
    APP_LOG("btServerBegin 1");

    g_serverContext.ptr = (LBTServerClass*)pContext->ptr;
    if(pContext->is_set_pin == true)
    {
        vm_custom_set_bt_pairing_method(VM_PIN_AND_SSP);
    }
    if(g_serverContext.btcm_hdl >= 0)
    {
        //already inited
        pContext->result = false;
        APP_LOG("btServerBegin 2");
        return true;        
    }

    g_serverContext.btcm_hdl = vm_btcm_init(
        bt_server_btcm_cb,     
        VM_SRV_BT_CM_EVENT_ACTIVATE |
        VM_SRV_BT_CM_EVENT_DEACTIVATE |
        VM_SRV_BT_CM_EVENT_SET_VISIBILITY |
        VM_SRV_BT_CM_EVENT_PAIR_IND |
        VM_SRV_BT_CM_EVENT_SECURITY_USER_CONFIRM |
        VM_SRV_BT_CM_EVENT_SET_NAME,
        NULL);

    if(g_serverContext.btcm_hdl < 0)
    {
        //init btcm fail
        pContext->result = false;
        APP_LOG("btServerBegin 3 hdl[%d]", g_serverContext.btcm_hdl);
        return true;
    }

    VMINT ret = vm_btcm_get_power_status();
    g_serverContext.waiting_result_p = &(pContext->result);

    if (VM_SRV_BT_CM_POWER_OFF == ret)
    {
        ret = vm_btcm_switch_on();

        if(VM_SRV_BT_CM_RESULT_SUCCESS == ret)
        {
            //wait for callback to process
            g_serverContext.server_status = BT_SERVER_POWERING_ON;
            g_serverContext.waiting_result_p = &(pContext->result);
            g_serverContext.device_name_p = pContext->name;
            APP_LOG("btServerBegin 4");
            return false;
        }
    }
    else if (VM_SRV_BT_CM_POWER_SWITCHING_OFF == ret)
    {
        g_serverContext.server_status = BT_SERVER_BEGINING;
        g_serverContext.waiting_result_p = &(pContext->result);
        g_serverContext.device_name_p = pContext->name;
        APP_LOG("btServerBegin 5");
        return false;
    }
    else if (VM_SRV_BT_CM_POWER_SWITCHING_ON == ret)
    {
        g_serverContext.server_status = BT_SERVER_POWERING_ON;
        g_serverContext.waiting_result_p = &(pContext->result);
        g_serverContext.device_name_p = pContext->name;
        APP_LOG("btServerBegin 6");
        return false;
    }
    else if (VM_SRV_BT_CM_POWER_ON == ret)
    {
        ret = bt_server_init_spp((uint8_t*)pContext->name);
        if (ret > 0)
        {
            return false;
        }
    }

    if(ret<0)
    {
        pContext->result = false;
        APP_LOG("btServerBegin 7 ret[%d]", ret);
        return bt_server_end_spp();
    }

    //success
    g_serverContext.server_status = BT_SERVER_READY;
    pContext->result = true;

    APP_LOG("btServerBegin 8");
	return true;
}


boolean btServerEnd(void *userData)
{
	return bt_server_end_spp();
}

boolean btServerAccept(void *userData)
{
    LBTServerAcceptContext* pContext = (LBTServerAcceptContext*)userData ;

    if(g_serverContext.conn_id != -1)
    {
        //someone connected
        pContext->result = false;
        return true;        
    }
    
    g_serverContext.mac_only = false;
    
    if (pContext->address)
    {
        g_serverContext.mac_only = true;
        memcpy(&(g_serverContext.address), pContext->address, sizeof(LBTAddress));
        APP_LOG("pContext->address [%02x:%02x:%02x:%02x:%02x:%02x]", 
          g_serverContext.address.nap[1], g_serverContext.address.nap[0],
          g_serverContext.address.uap, 
          g_serverContext.address.lap[2], g_serverContext.address.lap[1], g_serverContext.address.lap[0]);
    }

    g_serverContext.waiting_for_accept = true;
    g_serverContext.waiting_result_p = &(pContext->result);

    g_serverContext.accept_tid = vm_create_timer(pContext->time_out*1000, bt_server_accept_timeout_cb);
    APP_LOG("vm_create_timer [%d] timeout[%d]", g_serverContext.accept_tid, pContext->time_out*1000);

	return false;
}

boolean btServerConnected(void *userData)
{
    boolean* result = (boolean*) userData;

    if(g_serverContext.conn_id != -1)
    {
        //connected
        *result = true;
    }
    else
    {
        //not connected yet
        *result = false;
    }

    return true;
}

boolean btServerGetHostDeviceInfo(void *userData)
{

    LBTServerGetHostDeviceInfoContext* pContext = (LBTServerGetHostDeviceInfoContext*)userData;

    vm_srv_bt_cm_dev_struct dev_info ;

    if( VM_BT_CM_ERR_SUCCESS == vm_btcm_get_host_dev_info(&dev_info) )
    {
        pContext->device_info->address.nap[0] = (dev_info.bd_addr.nap & 0x00ff);
        pContext->device_info->address.nap[1] = (dev_info.bd_addr.nap & 0xff00) >> 8;
        pContext->device_info->address.uap = dev_info.bd_addr.uap;
        pContext->device_info->address.lap[0] = (dev_info.bd_addr.lap & 0x0000ff);
        pContext->device_info->address.lap[1] = (dev_info.bd_addr.lap & 0x00ff00) >> 8;
        pContext->device_info->address.lap[2] = (dev_info.bd_addr.lap & 0xff0000) >> 16;

        strcpy(pContext->device_info->name, (const char*)dev_info.name);

        pContext->result = true;
    }
    else
    {
        // fail to get the device info
        pContext->result = false;
    }

    return true;

}

boolean btServerRead(void *userData)
{

    LBTServerReadWriteContext* pContext = (LBTServerReadWriteContext*)userData;

    if(g_serverContext.conn_id < 0)
    {
        //not connected yet
        pContext->lenProcessed = 0;
        return true;
    }

    VMINT ret = vm_btspp_read(g_serverContext.conn_id, pContext->buf, pContext->len);

    if (ret < 0)
    {
        //read fail
        pContext->lenProcessed = 0;
    }
    else 
    {
        pContext->lenProcessed = ret;
    }

	return true;
}

boolean btServerWrite(void *userData)
{
    LBTServerReadWriteContext* pContext = (LBTServerReadWriteContext*)userData;

    if(g_serverContext.conn_id < 0)
    {
        //not connected yet
        pContext->lenProcessed = 0;
        return true;
    }

    VMINT ret = vm_btspp_write(g_serverContext.conn_id, pContext->buf, pContext->len);
    APP_LOG("vm_btspp_write ret[%d] [%s]", ret, pContext->buf);

    if (ret < 0)
    {
        //read fail
        pContext->lenProcessed = 0;
    }
    else 
    {
        pContext->lenProcessed = ret;
    }

	return true;
}

