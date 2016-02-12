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

#include "LGSM.h"

#include <vmsim.h>
#include <vmsms.h>
#include <vmchset.h>
#include <vmstdlib.h>

/*****************************************************************************
* 
* structure data between Arduino / MMI thread
* 
*****************************************************************************/

struct linkit_sms_send_struct
{
    const char *number;
    const char *content;
    int result;
};

struct linkit_sms_unread_msg_struct
{
    int id;
    char *number;
    char *content;
};


boolean linkit_sms_ready_handler(void* userdata);
boolean linkit_sms_send_handler(void* userdata);

boolean linkit_sms_get_unread_handler(void* userdata);
boolean linkit_sms_delete_handler(void* userdata);

/*****************************************************************************
* 
* LSMSClass class
* 
*****************************************************************************/

LSMSClass::LSMSClass():
    _msgId(-1),
    _msgPos(0)
{

}

LSMSClass::~LSMSClass()
{

}

int LSMSClass::ready()
{
    int result;
    LTask.remoteCall(linkit_sms_ready_handler, &result);
    return result;
}

int LSMSClass::beginSMS(const char* to)
{
    _toNumber = to;
    _toContent = "";
    return 1;
}

size_t LSMSClass::write(uint8_t c)
{
    _toContent += (char)c;
}

int LSMSClass::endSMS()
{
    linkit_sms_send_struct data;

    data.content = _toContent.c_str();
    data.number = _toNumber.c_str();

    LTask.remoteCall(linkit_sms_send_handler, &data);

    LGSMLOG("[LOG]endSMS():");
    LGSMLOG(data.result);

    if(data.result == 1)
        return 1;
    else
        return 0;
}

int LSMSClass::available()
{
    linkit_sms_unread_msg_struct data;
    
    LTask.remoteCall(linkit_sms_get_unread_handler, &data);

    if (data.id < 0)
        return false;

    _msgId = data.id;
    _msgNumber = data.number;
    _msgContent = data.content;
    _msgPos = 0;

    return true;
}

int LSMSClass::remoteNumber(char* number, int nlength)
{
    int len;

    if (_msgId < 0)
        return 0;

    len = strlen(_msgNumber);

    if (len+1 > nlength)
        return len+1;
        
    strcpy(number, _msgNumber);
    return len;
}

int LSMSClass::read()
{
    int result;
    
    if(_msgId < 0)
        return -1;

    result = _msgContent[_msgPos];
    if (result)
        _msgPos++;
    else
        result = -1;
        
    return result;
}

int LSMSClass::peek()
{
    if(_msgId < 0)
        return -1;

    return _msgContent[_msgPos];
}

void LSMSClass::flush()
{
    if(_msgId < 0)
        return;

    LTask.remoteCall(linkit_sms_delete_handler, (void*)_msgId);
    _msgId = -1;
}

/*****************************************************************************
* 
* LSMS MMI part (running on MMI thread)
* 
*****************************************************************************/

boolean linkit_sms_ready_handler(void* userdata)
{
    int result;

    LGSMLOG("[LOG]vm_sim_card_count:");
    LGSMLOG(vm_sim_card_count());
    LGSMLOG("[LOG]vm_sms_is_sms_ready:");
    LGSMLOG(vm_sms_is_sms_ready());

    result = false;
    if(vm_sim_card_count() > 0 && vm_sms_is_sms_ready())
        result = true;

    *((int*)userdata) = result;
    return true;    
}

linkit_sms_send_struct *g_linkit_sms_send_data;

char *g_linkit_sms_number_buf = 0;
char *g_linkit_sms_content_buf = 0;

void linkit_sms_send_callback(VMINT result)
{
    LGSMLOG("[LOG]linkit_sms_send_callback");
    g_linkit_sms_send_data->result = result;
    LTask.post_signal();
}

boolean linkit_sms_send_handler(void* userdata)
{
    linkit_sms_send_struct *data = (linkit_sms_send_struct*)userdata;
    VMWCHAR *number;
    VMWCHAR *content;
    VMINT  size;

    LGSMLOG("[LOG]linkit_sms_send_handler");
    LGSMLOG("[LOG]Number:");
    LGSMLOG(data->number);
    LGSMLOG("[LOG]Content:");
    LGSMLOG(data->content);

    // ascii to ucs2
    size = (strlen(data->number)+1)*sizeof(VMWCHAR);
    number = (VMWCHAR *)vm_malloc(size);
    vm_ascii_to_ucs2(number, size, (VMCHAR*)data->number);

    size = (strlen(data->content)+1)*sizeof(VMWCHAR);
    content = (VMWCHAR *)vm_malloc(size);
    vm_ascii_to_ucs2(content, size, (VMCHAR*)data->content);

    // send and wait for result
    g_linkit_sms_send_data = data;
    size = vm_send_sms(number, content, linkit_sms_send_callback);
    LGSMLOG("[LOG]vm_send_sms:");
    LGSMLOG(size);

    // TODO: can we free them now, or need to wait for callback?
    vm_free(number);
    vm_free(content);
    
    if(!size)   // send fail
    {
        data->result = false;
        return true;
    }
    
    return false;
}

void linkit_sms_read_callback(vm_sms_callback_t* callback_data)
{
    linkit_sms_unread_msg_struct *dest = (linkit_sms_unread_msg_struct*)callback_data->user_data;
    vm_sms_read_msg_cb_t *msg = (vm_sms_read_msg_cb_t*)callback_data->action_data;

    LGSMLOG("[LOG]linkit_sms_read_callback");
    LGSMLOG(callback_data->result);

    if (callback_data->result)
    {
        if(g_linkit_sms_number_buf)
        {
            vm_free(g_linkit_sms_number_buf);
            g_linkit_sms_number_buf = 0;
        }
        if(g_linkit_sms_content_buf)
        {
            vm_free(g_linkit_sms_content_buf);
            g_linkit_sms_content_buf = 0;
        }

        int size = vm_wstrlen((VMWCHAR*)msg->msg_data->number);
        g_linkit_sms_number_buf = (char*)vm_malloc(size+1);
        vm_ucs2_to_ascii(g_linkit_sms_number_buf, size+1, (VMWCHAR*)msg->msg_data->number);

        // assume dcs = UCS2
        g_linkit_sms_content_buf = (char*)vm_malloc(msg->msg_data->content_buff_size/2+1);
        vm_ucs2_to_ascii(g_linkit_sms_content_buf, msg->msg_data->content_buff_size/2+1, (VMWCHAR*)msg->msg_data->content_buff);

        dest->number = g_linkit_sms_number_buf;
        dest->content = g_linkit_sms_content_buf;
        
        LGSMLOG("[LOG]Number:");
        LGSMLOG(g_linkit_sms_number_buf);
        LGSMLOG("[LOG]Content:");
        LGSMLOG(g_linkit_sms_content_buf);
    }
    else
    {
        dest->id = -1;
    }
    
    vm_free(msg->msg_data->content_buff);
    vm_free(msg->msg_data);

    LTask.post_signal();
}

void linkit_sms_get_unread_callback(vm_sms_callback_t* callback_data)
{
    linkit_sms_unread_msg_struct *dest = (linkit_sms_unread_msg_struct*)callback_data->user_data;
    vm_sms_query_msg_cb_t *list = (vm_sms_query_msg_cb_t*)callback_data->action_data;
    int result;

    LGSMLOG("[LOG]linkit_sms_get_unread_callback");
    if (callback_data->result)
    {
        if (list->msg_num > 0)
        {
            // continue to read this message
            vm_sms_msg_data_t *buf = (vm_sms_msg_data_t*)vm_malloc(sizeof(vm_sms_msg_data_t));
            
            buf->content_buff = (VMINT8*)vm_malloc((LGSM_MAX_SMS_LEN+1)*sizeof(VMWCHAR));
            buf->content_buff_size = LGSM_MAX_SMS_LEN*sizeof(VMWCHAR);
            
            dest->id = list->msg_id_list[0];
            result = vm_sms_read_msg(dest->id, 0, buf, linkit_sms_read_callback, dest);
            if(result >= 0)
            {
                return; // continue wait
            }
            else
            {
                LGSMLOG("[LOG]vm_sms_read_msg() fail!!:");
                LGSMLOG(dest->id);
                LGSMLOG(result);
            }
        }
    }
    
    LTask.post_signal();
}

boolean linkit_sms_get_unread_handler(void* userdata)
{
    linkit_sms_unread_msg_struct *dest = (linkit_sms_unread_msg_struct*)userdata;
    vm_sms_query_t param;
    int result;

    dest->id = -1;

    param.sort_flag = VM_SMS_SORT_SIM_ID;
    param.order_flag = VM_SMS_ORDER_ASC;
    param.status = (vm_sms_status_enum)(VM_SMS_STATUS_UNREAD | VM_SMS_STATUS_READ);

    LGSMLOG("[LOG]linkit_sms_get_unread_handler");
    result = vm_sms_get_msg_id_list(&param, linkit_sms_get_unread_callback, userdata);
    if(result < 0)
    {
        LGSMLOG(result);
        return true;
    }
    return false;
}


void linkit_sms_delete_callback(vm_sms_callback_t* callback_data)
{
    LTask.post_signal();
}

boolean linkit_sms_delete_handler(void* userdata)
{
    VMUINT16 msg_id = (VMUINT16)((VMUINT32)userdata);

    vm_sms_delete_msg(msg_id, linkit_sms_delete_callback, userdata);

    return false;
}

LSMSClass LSMS;