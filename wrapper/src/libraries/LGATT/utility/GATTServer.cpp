#include "GATTServer.h"
#include "LGATTServer.h"
#include "vmbtcm.h"
#include "vmbtgatt.h"
#include "vmwdt.h"

static GATTService g_gatts;

typedef struct 
{
    VMINT16 trans_id;
    VM_ATT_HANDLE char_handle; // ok
    VM_ATT_VALUE value; // ok
}attr_data_t;


struct gatts_srv_ctx_t
{
    vm_bt_uuid_struct bt_uuid; // check only for register cb
    void *reg_ctx;
    void *conn_ctx;
    //gatts_notify app_cb;
    void *user_data;

    // profile info
    VM_GATT_SVC_UUID srv_uuid;
    VM_ATT_HANDLE srv_handle;

    VM_BD_ADDR addr; // client connection identify
    VMINT status; // client status

    //attr_data_t attr_data[MAX_ATTRS];

    gatts_srv_ctx_t(){memset(this, 0, sizeof(gatts_srv_ctx_t));}
};

gatts_srv_ctx_t *gatts_new_ctx()
{
    return new gatts_srv_ctx_t();
}

void gatts_delete_ctx(gatts_srv_ctx_t *ctx)
{
    delete ctx;
}


boolean gattServiceRemoteCallHandler(void *userdata)
{
    LGATTService *service = (LGATTService *)userdata;
    if (NULL == service)
    {
        service->_result = false;
        return true;
    }

    switch (service->_action)
    {
    case LGATTService::ACTION_BEGIN: 
        return GATTService::rBegin(service);
        break;
    case LGATTService::ACTION_SEND: 
    case LGATTService::ACTION_SEND_ACK: 
        return GATTService::rSend(service);
        break;
    case LGATTService::ACTION_END:
        return GATTService::rEnd(service);
        break;
    default:
        break;
    }
    return false;
}


vm_gatts_callback_struct GATTService::_gatts_service_cb = {0};

boolean GATTService::init(LGATTService &s)
{
    return true;
}

void GATTService::deinit(LGATTService &s)
{

}




#define UUID_STR_LEN_128    (32)
#define UUID_STR_LEN_16     (8)
#define UUID_STR_LEN_2      (4)
static VMUINT32 int_gatt_squeeze(VMINT8* str, VMINT8 ch)
{
    VMUINT32 i,j;
    for (i = 0, j = 0; str[i] != '\0'; i++)
    {
        if (str[i] != ch)
        {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';

    return j;
}

VMUINT8 int_gatt_chr_to_u8(char chr)
{
	VMUINT8 ret = 0;
	if(chr >= '0' && chr <= '9')
	{
		ret = chr - '0';
	}
	else if(chr >= 'a' && chr <= 'f')
	{
		ret = chr - 'a' + 10;
	}
	else if(chr >= 'A' && chr <= 'F')
	{
		ret = chr - 'A' + 10;
	}
	return ret;
}

static void int_gatt_str_to_uuid(const VMUINT8* str, VM_BT_UUID* uuid)
{
#if 0
    uuid->len = 16;
    memcpy(uuid->uuid, str, 16);
#else
    VMUINT32 len = 0;
    VMUINT8* uuid_str = NULL;
    VMUINT32 uuid_len = 0;
    int i,j;
	VMUINT8 H4 = 0;
	VMUINT8 L4 = 0;

    len = strlen((const char *)str); //mmi_chset_utf8_strlen(str);
    APP_LOG("int_gatt_str_to_uuid [%s] len[%d]", str, len);
    uuid_str = (VMUINT8*)vm_calloc(len + 1);
    if (uuid_str != NULL)
    {
        memset(uuid_str, 0x0, len+1);
        memcpy(uuid_str, str, len);
        uuid_str[len] = '\0';                
        
        uuid_len = int_gatt_squeeze((VMINT8*)uuid_str, '-');
        
        switch (uuid_len)
        {
        case UUID_STR_LEN_128:
        case UUID_STR_LEN_16:
        case UUID_STR_LEN_2:
            {
                for (i = 0, j = uuid_len - 2; j >= 0; j -= 2)
                {
                	H4 = int_gatt_chr_to_u8(uuid_str[j]);
					L4 = int_gatt_chr_to_u8(uuid_str[j+1]);
                	uuid->uuid[i] = H4*16 + L4;
                    i++;
                }
                uuid->len = i;
            }
            break;
        default:
            APP_LOG("int_gatt_str_to_uuid len error");
            break;
        }

        vm_free(uuid_str);
        uuid_str = NULL;
    }
    else
    {
        APP_LOG("int_gatt_str_to_uuid no memory");
    }
#endif
}



boolean GATTService::rBegin(void *userdata)
{
    LGATTService *s = (LGATTService*)userdata;
    APP_LOG("GATTService::rBegin 0x%x -s", s);

    if (NULL == s)
    {
        s->_result = false;
        return true;
    }

    // init callbacks
    initCB(s);

    // has got service data
    if (0 > toRegist(s))
    {
        s->_result = false;
        return true;
    }
    
    //VM_BT_UUID bt_uuid = {0};
    //int_gatt_str_to_uuid(s->_gatts_service.uuid, &bt_uuid);
    //memcpy(s->_gatts_srv_ctx.bt_uuid, &bt_uuid, sizeof(VM_BT_UUID));
    
    APP_LOG("GATTService::rBegin -e");



    

    
    //switch (s->getAction())
    //{
    //case GATTS_ACTION_BEGIN:
    //    {
    //        s->_gatts_srv_ctx = new gatts_srv_ctx_t;
    //        if (NULL == s->_gatts_srv_ctx)
    //        {
    //            s->_result = false;
    //            return true;
    //        }

    //        //s->_gatts_service;
    //        //s->_result = true;
    //        // TODO:

    //        return false;
    //    }
    //    break;
    //case GATTS_ACTION_GET_STATUS:
    //    {
    //        LGATTService *s = (LGATTService*)userdata;
    //        //s->post_signal();
    //        return false;
    //    }
    //    break;
    //case GATTS_ACTION_END:
    //    {
    //        delete s->_gatts_srv_ctx;

    //        //s->_result = true;
    //        //return true;

    //        return false;
    //    }
    //    break;
    //default:
    //    s->_result = false;
    //    break;
    //}

    return false;
}

boolean GATTService::rSend(void *userdata)
{
    LGATTService *s = (LGATTService*)userdata;
    APP_LOG("GATTService::rSend 0x%x -s", s);
    if (s)
    {
        if (LGATTService::ACTION_SEND == s->_action)
        {
            vm_gatt_conn_struct conn;
            conn.conn_ctx = SRV_CTX(s)->conn_ctx;
            conn.reg_ctx= SRV_CTX(s)->reg_ctx;
            
            APP_LOG("vm_gatts_send_indication hdl[%d] cfm[%d] v[0x%x] len[%d]", 
                s->_attr_handle, s->_confirm_failed, s->_value, s->_value->len);
            if (0 > vm_gatts_send_indication(&conn, s->_attr_handle, s->_confirm_failed, (VM_ATT_VALUE*)s->_value))
            {
                s->_result = false;
            }
            s->_result = true;         
        }
        else if (LGATTService::ACTION_SEND_ACK == s->_action)
        {
            vm_gatt_conn_struct conn;
            conn.conn_ctx = SRV_CTX(s)->conn_ctx;
            conn.reg_ctx= SRV_CTX(s)->reg_ctx;
            
            APP_LOG("vm_gatts_send_response hdl[%d] failed[%d] v[0x%x] len[%d] tid[%d]", 
                s->_attr_handle, s->_confirm_failed, s->_value, s->_value->len, s->_trans_id);
            if (0 > vm_gatts_send_response(&conn, s->_trans_id, (VM_OS_STATUS)s->_confirm_failed, s->_attr_handle, (VM_ATT_VALUE*)s->_value))
            {
                s->_result = false;
            }
            s->_result = true;         
        }
        
        APP_LOG("GATTService::rSend result[%d]", s->_result);
    }
    APP_LOG("GATTService::rSend 0x%x -e", s);

    return true;
}

boolean GATTService::rEnd(void *userdata)
{
    return false;
}
VMINT GATTService::addDeclaration(LGATTService *service, VM_ATT_HANDLE srvc_handle, ard_decl_type_enum type)
{
    VMINT ret = TYPE_END;
    VMUINT16 handle_num = 0;
    VM_BT_UUID bt_uuid = {0};
    int i, find = 0;
    LGATTServiceInfo * item = NULL;

    APP_LOG("int_gatt_add_declaration type[%d] -s", type);

    
    for (i = 0; TYPE_END != service->_gatts_service[i].type; i++)
    {
        if ((service->_gatts_service[i].type == TYPE_SERVICE) || (service->_gatts_service[i].type == TYPE_DESCRIPTOR))
        {
            handle_num += 1;
        }
        else if (service->_gatts_service[i].type == TYPE_CHARACTERISTIC)
        {
            handle_num += 2;
        }
    }
    
    for (i = 0; TYPE_END != service->_gatts_service[i].type; i++)
    {  
        if (!service->_gatts_service[i].trigged)
        {
            if (type == service->_gatts_service[i].type)
            {
                item = &service->_gatts_service[i];
                find = 1;
                item->trigged = 1;
                //ret = 1;
            }
            else
            {
                ret = service->_gatts_service[i].type;
            }
            break;
        }
    }

    if (item != NULL && find)
    {
        switch (type)
        {
        case TYPE_SERVICE:
            {
                VM_GATT_SVC_UUID srv_uuid = {0};
                srv_uuid.is_primary = 1;
                int_gatt_str_to_uuid(item->uuid, &bt_uuid);
                memcpy(&srv_uuid.uuid.uuid, &bt_uuid, sizeof(VM_BT_UUID));
                APP_LOG("vm_gatts_add_service -s");
                vm_gatts_add_service(SRV_CTX(service)->reg_ctx, &srv_uuid, handle_num);
                APP_LOG("uuid[0x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x][%d]",
                    bt_uuid.uuid[0], bt_uuid.uuid[1], bt_uuid.uuid[2], bt_uuid.uuid[3],
                    bt_uuid.uuid[4], bt_uuid.uuid[5], bt_uuid.uuid[6], bt_uuid.uuid[7],
                    bt_uuid.uuid[8], bt_uuid.uuid[9], bt_uuid.uuid[10], bt_uuid.uuid[11],
                    bt_uuid.uuid[12], bt_uuid.uuid[13], bt_uuid.uuid[14], bt_uuid.uuid[15],
                    bt_uuid.len
                    );
                APP_LOG("vm_gatts_add_service -e");
                ret = TYPE_SERVICE;
            }
            break;
        case TYPE_CHARACTERISTIC:
            {
                VM_ATT_UUID att_uuid = {0};
                int_gatt_str_to_uuid(item->uuid, &bt_uuid);
                memcpy(&att_uuid.uuid, &bt_uuid, sizeof(VM_BT_UUID));
                APP_LOG("vm_gatts_add_characteristic -s");
                vm_gatts_add_characteristic(SRV_CTX(service)->reg_ctx, srvc_handle, &att_uuid, item->prop, item->permission);
                APP_LOG("uuid[0x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x][%d]", 
                    bt_uuid.uuid[0], bt_uuid.uuid[1], bt_uuid.uuid[2], bt_uuid.uuid[3],
                    bt_uuid.uuid[4], bt_uuid.uuid[5], bt_uuid.uuid[6], bt_uuid.uuid[7],
                    bt_uuid.uuid[8], bt_uuid.uuid[9], bt_uuid.uuid[10], bt_uuid.uuid[11],
                    bt_uuid.uuid[12], bt_uuid.uuid[13], bt_uuid.uuid[14], bt_uuid.uuid[15],
                    bt_uuid.len
                    );
                APP_LOG("vm_gatts_add_characteristic -e");
                ret = TYPE_CHARACTERISTIC;
            }
            break;
        case TYPE_DESCRIPTOR:
            {
                VM_ATT_UUID att_uuid = {0};
                int_gatt_str_to_uuid(item->uuid, &bt_uuid);
                memcpy(&att_uuid.uuid, &bt_uuid, sizeof(VM_BT_UUID));
                APP_LOG("vm_gatts_add_descriptor -s");
                vm_gatts_add_descriptor(SRV_CTX(service)->reg_ctx, srvc_handle, &att_uuid, item->permission);
                APP_LOG("uuid[0x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x][%d]",
                    bt_uuid.uuid[0], bt_uuid.uuid[1], bt_uuid.uuid[2], bt_uuid.uuid[3],
                    bt_uuid.uuid[4], bt_uuid.uuid[5], bt_uuid.uuid[6], bt_uuid.uuid[7],
                    bt_uuid.uuid[8], bt_uuid.uuid[9], bt_uuid.uuid[10], bt_uuid.uuid[11],
                    bt_uuid.uuid[12], bt_uuid.uuid[13], bt_uuid.uuid[14], bt_uuid.uuid[15],
                    bt_uuid.len
                    );
                APP_LOG("vm_gatts_add_descriptor -e");
                ret = TYPE_DESCRIPTOR;
            }
            break;
        case TYPE_END:
            ret = TYPE_END;
            APP_LOG("addDeclaration TYPE_END");
            break;
        default:
            VM_ASSERT((type == TYPE_SERVICE) || (type == TYPE_CHARACTERISTIC) || (type == TYPE_DESCRIPTOR));
            break;
        }
    }

    APP_LOG("int_gatt_add_declaration ret[%d] -e", ret);

    return ret;


}

void GATTService::initCB(LGATTService *service)
{
    if (!GATTService::_gatts_service_cb.register_server_cb)
    {
        GATTService::_gatts_service_cb.register_server_cb = register_server_callback;
        GATTService::_gatts_service_cb.connection_cb = connection_callback;
        GATTService::_gatts_service_cb.listen_cb = listen_callback;
        GATTService::_gatts_service_cb.service_added_cb = service_added_callback;
        //service->_gatts_service_cb.included_service_added_cb = included_service_added_callback;
        GATTService::_gatts_service_cb.characteristic_added_cb = characteristic_added_callback;
        GATTService::_gatts_service_cb.descriptor_added_cb = descriptor_added_callback;
        GATTService::_gatts_service_cb.service_started_cb = service_started_callback;
        //service->_gatts_service_cb.service_stopped_cb = service_stopped_callback;
        //service->_gatts_service_cb.service_deleted_cb = service_deleted_callback;
        GATTService::_gatts_service_cb.request_read_cb = request_read_callback;
        GATTService::_gatts_service_cb.request_write_cb = request_write_callback;
        //service->_gatts_service_cb.request_exec_write_cb = request_exec_write_callback;
        //service->_gatts_service_cb.response_confirmation_cb = response_confirmation_callback;
        //s._gatts_service_cb.read_tx_power_cb = read_tx_power_callback;
    }

}


VMINT GATTService::toRegist(LGATTService *service)
{
    vm_bt_uuid_struct uuid;
    memcpy(uuid.uu, service->_uuid, sizeof(uuid.uu));
    
    // add uuid to service.
    memcpy(SRV_CTX(service)->bt_uuid.uu, uuid.uu, sizeof(SRV_CTX(service)->bt_uuid.uu));
    
    return vm_gatts_register(&uuid, &(GATTService::_gatts_service_cb));
}

void GATTService::register_server_callback(void *reg_ctx, VM_OS_STATUS status, vm_bt_uuid_struct *app_uuid)
{
    LGATTService *service = GATTServer::getCtxByUUID(app_uuid);
    APP_LOG("register_server_callback srv[0x%x] st[%d] -s", service, status);

    if (service)
    {
        APP_LOG("uuid[0x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x] -s",  
            app_uuid->uu[0], app_uuid->uu[1], app_uuid->uu[2], app_uuid->uu[3],
            app_uuid->uu[4], app_uuid->uu[5], app_uuid->uu[6], app_uuid->uu[7],
            app_uuid->uu[8], app_uuid->uu[9], app_uuid->uu[10], app_uuid->uu[11],
            app_uuid->uu[12], app_uuid->uu[13], app_uuid->uu[14], app_uuid->uu[15]
            );
            
        // add the reg_ctx to service
        SRV_CTX(service)->reg_ctx = reg_ctx;
        
        if (VM_OS_STATUS_SUCCESS == status)
        {
            APP_LOG("will add SERVICE");
            GATTService::addDeclaration(service, 0, TYPE_SERVICE);
        }
        else
        {
            REMOTE_RETURN(service, false);
            /*
            gatt_handle hdl = {0};
            dulife_state_init_t init = {0};
            //init.state = VM_DULIFE_STATE_INIT; //int_gatt_map_state(GATT_STATE_INIT, status);
            init.error_code = (DULIFE_ERR_E)status;
            init.user_data = ctx->user_data;
            init.srv_handle = 0;
            hdl.conn_ctx = NULL;
            hdl.reg_ctx = reg_ctx;
            if (ctx->app_cb)
                ctx->app_cb(&hdl, VM_DULIFE_STATE_INIT, &init);
                */
        }
    }
    
}
void GATTService::service_added_callback(VM_OS_STATUS status, void *reg_ctx,
                VM_GATT_SVC_UUID *srvc_id, VM_ATT_HANDLE srvc_handle)
{
    LGATTService *service;
    APP_LOG("service_added_callback reg_ctx[0x%x] srv_id[0x%x] -s", reg_ctx, srvc_id);
    service = GATTServer::getCtxByCTX(reg_ctx);
    if (service)
    {
        APP_LOG("ctx has");
        if (srvc_id)
        {
            
            APP_LOG("[0x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x] %d[%d][%d]", 
                srvc_id->uuid.uuid.uuid[0], srvc_id->uuid.uuid.uuid[1], srvc_id->uuid.uuid.uuid[2], srvc_id->uuid.uuid.uuid[3],
                srvc_id->uuid.uuid.uuid[4], srvc_id->uuid.uuid.uuid[5], srvc_id->uuid.uuid.uuid[6], srvc_id->uuid.uuid.uuid[7],
                srvc_id->uuid.uuid.uuid[8], srvc_id->uuid.uuid.uuid[9], srvc_id->uuid.uuid.uuid[10], srvc_id->uuid.uuid.uuid[11],
                srvc_id->uuid.uuid.uuid[12], srvc_id->uuid.uuid.uuid[13], srvc_id->uuid.uuid.uuid[14], srvc_id->uuid.uuid.uuid[15],
                srvc_id->is_primary, srvc_id->uuid.inst, srvc_id->uuid.uuid.len
                );
                
            APP_LOG("srvc_id has");
        }
        else
        {
            APP_LOG("srvc_id NULL");
        }
        if (VM_OS_STATUS_SUCCESS == status)
        {            
            // add the srvc_handle to service
            SRV_CTX(service)->srv_handle = srvc_handle;
            APP_LOG("1");
            GATTService::addDeclaration(service, srvc_handle, TYPE_CHARACTERISTIC);
            APP_LOG("2");
            VMCHAR uuid[2] = {0};
            uuid[0] = srvc_id->uuid.uuid.uuid[1];
            uuid[1] = srvc_id->uuid.uuid.uuid[0];
            vm_gattc_set_adv_data(SRV_CTX(service)->reg_ctx, 
                                0, 
                                1, 
                                1, 
                                0,
                                0,
                                0, 
                                0, 
                                0, 
                                0, 
                                0,
                                2,
                                uuid);
            
        }
        else
        {
        /*
            dulife_state_init_t init = {0};
            gatt_handle hdl = {0};
            //init.state = VM_DULIFE_STATE_INIT;//int_gatt_map_state(GATT_STATE_INIT, status);
            APP_LOG("3", 0);
            init.error_code = (DULIFE_ERR_E)status;
            init.user_data = ctx->user_data;
            init.srv_handle = 0;
            hdl.reg_ctx = reg_ctx;
            if (ctx->app_cb)
                ctx->app_cb(&hdl, VM_DULIFE_STATE_INIT, &init);
            */
            REMOTE_RETURN(service, false);
        }
    }
    APP_LOG("service_added_callback status -e");
}


void GATTService::characteristic_added_callback(VM_OS_STATUS status, void *reg_ctx,
                VM_ATT_UUID *uuid, VM_ATT_HANDLE srvc_handle, VM_ATT_HANDLE char_handle)
{
    
    LGATTService *service = GATTServer::getCtxByHandle(reg_ctx, srvc_handle);
    APP_LOG("characteristic_added_callback status[%d] srv_handle[%d]char_handle[%d] -s", status, srvc_handle, char_handle);
    if (service)
    {
        if (VM_OS_STATUS_SUCCESS == status)
        {
            VMINT ret = 0, type;

            if (uuid)
            {
            APP_LOG("uuid[0x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x] [%d][%d]", 
                uuid->uuid.uuid[0], uuid->uuid.uuid[1], uuid->uuid.uuid[2], uuid->uuid.uuid[3],
                uuid->uuid.uuid[4], uuid->uuid.uuid[5], uuid->uuid.uuid[6], uuid->uuid.uuid[7],
                uuid->uuid.uuid[8], uuid->uuid.uuid[9], uuid->uuid.uuid[10], uuid->uuid.uuid[11],
                uuid->uuid.uuid[12], uuid->uuid.uuid[13], uuid->uuid.uuid[14], uuid->uuid.uuid[15],
                uuid->inst, uuid->uuid.len
                );
            }
            //ret = int_gatt_set_characteristic(ctx, char_handle, uuid);
            gatts_q_node *node = new gatts_q_node(GATTS_EVENT_ON_CHAR_ADDED, service);
            ((LGATTAttributeData *)node->data)->handle = char_handle;
            ((LGATTAttributeData *)node->data)->failed = status;
            //((LGATTAttributeData *)node->data)->uuid.inst = uuid->inst;
            //((LGATTAttributeData *)node->data)->uuid.uuid.len = uuid->uuid.len;
            //memcpy(((LGATTAttributeData *)node->data)->uuid.uuid.uuid, uuid->uuid.uuid, uuid->uuid.len);
            ((LGATTAttributeData *)node->data)->uuid = uuid->uuid;
            GATTServer::rEnQ(*node);
            //service->onCharacteristicAdded(data);
            
            VM_ASSERT(ret != 0);
            type = GATTService::addDeclaration(service, srvc_handle, TYPE_CHARACTERISTIC);
            if (TYPE_DESCRIPTOR == type)
            {
            //#define GATT_TRANSPORT_LE                0x00
            //#define GATT_TRANSPORT_BR_EDR            0x01
            //#define GATT_TRANSPORT_LE_BR_EDR         0x02    
                //APP_LOG("vm_gatts_start_service", 0);
                //vm_gatts_start_service(ctx->reg_ctx, srvc_handle, 0x00); // TODO: what are those value mean?
                APP_LOG("add TYPE_DESCRIPTOR");
                //vm_gatts_add_descriptor(ctx->reg_ctx,ctx->srv_handle, VM_ATT_UUID * uuid,VM_GATT_PERMISSION permission)
                GATTService::addDeclaration(service, srvc_handle, TYPE_DESCRIPTOR);
                
            }
            else if (TYPE_END == type) // touch the end of profile
            {
                APP_LOG("vm_gatts_start_service service[0x%x] reg_ctx[0x%x]", service, SRV_CTX(service)->reg_ctx);
                vm_gatts_start_service(SRV_CTX(service)->reg_ctx, srvc_handle, 0x00);
            }
        }
        else
        {
            /*
            dulife_state_init_t init = {0};
            gatt_handle hdl = {0};
            //init.state = VM_DULIFE_STATE_INIT; //int_gatt_map_state(GATT_STATE_INIT, status);
            init.error_code = (DULIFE_ERR_E)status;
            init.user_data = ctx->user_data;
            init.srv_handle = srvc_handle;
            hdl.reg_ctx = reg_ctx;
            if (ctx->app_cb)
                ctx->app_cb(&hdl, VM_DULIFE_STATE_INIT, &init);
            */
        }
    }
    APP_LOG("characteristic_added_callback -e");
}

void GATTService::descriptor_added_callback(VM_OS_STATUS status, void *reg_ctx,
                VM_ATT_UUID *uuid, VM_ATT_HANDLE srvc_handle, VM_ATT_HANDLE descr_handle)
{
    LGATTService *service = GATTServer::getCtxByHandle(reg_ctx, srvc_handle);
    APP_LOG("descriptor_added_callback status[%d] srv_handle[%d]descr_handle[%d] -s", status, srvc_handle, descr_handle);
    if (service)
    {
        if (VM_OS_STATUS_SUCCESS == status)
        {
        	VMINT ret;
			//ctx->data_des.char_handle = descr_handle;
			//ctx->data_des.trans_id = 0;
			//ctx->data_des.value;
            gatts_q_node *node = new gatts_q_node(GATTS_EVENT_ON_DESC_ADDED, service);
            ((LGATTAttributeData *)node->data)->handle = descr_handle;
            ((LGATTAttributeData *)node->data)->failed = status;
            //((LGATTAttributeData *)node->data)->uuid.inst = uuid->inst;
            //((LGATTAttributeData *)node->data)->uuid.uuid.len = uuid->uuid.len;
            //memcpy(((LGATTAttributeData *)node->data)->uuid.uuid.uuid, uuid->uuid.uuid, uuid->uuid.len);
            ((LGATTAttributeData *)node->data)->uuid = uuid->uuid;
            GATTServer::rEnQ(*node);
            //service->onDescriptorAdded(data);
			
            //VM_ASSERT(ret != 0);
            ret = GATTService::addDeclaration(service, srvc_handle, TYPE_CHARACTERISTIC);
            if (TYPE_DESCRIPTOR == ret)
            {
                APP_LOG("add TYPE_DESCRIPTOR");
                GATTService::addDeclaration(service, srvc_handle, TYPE_DESCRIPTOR);
            }
            else if (TYPE_CHARACTERISTIC == ret)
            {
                APP_LOG("add TYPE_CHARACTERISTIC");
            }
            else if (TYPE_END == ret) // touch the end of profile
            {
                APP_LOG("vm_gatts_start_service");
                vm_gatts_start_service(SRV_CTX(service)->reg_ctx, srvc_handle, 0x00);
            }
        }
    }
    APP_LOG("descriptor_added_callback status -e");
}

void GATTService::service_started_callback(VM_OS_STATUS status, void *reg_ctx,
                                         VM_ATT_HANDLE srvc_handle)
{
    LGATTService *service = GATTServer::getCtxByHandle(reg_ctx, srvc_handle);
    APP_LOG("service_started_callback srv_handle[%d] status[%d] -s", srvc_handle, status);
    if (service)
    {
        
        APP_LOG("service_started_callback service[0x%x] reg_ctx[0x%x]", service, SRV_CTX(service)->reg_ctx);
        if (VM_OS_STATUS_SUCCESS == status)
        {
            APP_LOG("vm_gatts_listen");
            vm_gattc_set_adv_data(SRV_CTX(service)->reg_ctx, 
                FALSE, TRUE, FALSE,
                 0, 3000,
                 1,
                 0, 0,
                 0, 0,
                 16, (VMCHAR*)SRV_CTX(service)->bt_uuid.uu);
            vm_gatts_listen(SRV_CTX(service)->reg_ctx, 1);
        }
        else
        {
            /*
            dulife_state_init_t init = {0};
            gatt_handle hdl = {0};
            //init.state = VM_DULIFE_STATE_INIT; //int_gatt_map_state(GATT_STATE_INIT, status);
            init.error_code = (DULIFE_ERR_E)status;
            init.user_data = ctx->user_data;
            init.srv_handle = srvc_handle;
            hdl.reg_ctx = reg_ctx;
            if (ctx->app_cb)
                ctx->app_cb(&hdl, VM_DULIFE_STATE_INIT, &init);
                */
        }
    }
    APP_LOG("service_started_callback -e");
}

/** Callback triggered in response to listen */
void GATTService::listen_callback(void *reg_ctx, VM_OS_STATUS status)
{
    
    LGATTService *service = GATTServer::getCtxByCTX(reg_ctx);
    APP_LOG("listen_callback status[%d] -s", status);
    if (service)
    {
        REMOTE_RETURN(service, !status);
    }
    APP_LOG("listen_callback -e");
}

void GATTService::connection_callback(vm_gatt_conn_struct *conn, VMBOOL connected, VM_BD_ADDR *bd_addr)
{
    LGATTService *service = GATTServer::getCtxByCTX(conn->reg_ctx);
    APP_LOG("connection_callback connected [%d] srv[0x%x] [0x%x, 0x%x] -s", connected, service, conn->reg_ctx, conn->conn_ctx);
    if (service)
    {
        gatts_q_node *node = new gatts_q_node(GATTS_EVENT_ON_CONNETION, service);
        ((LGATTConnection *)(node->data))->connected = connected;
        memcpy(((LGATTConnection *)node->data)->addr.addr, bd_addr->addr, LGATT_BD_ADDR_SIZE);
        GATTServer::rEnQ(*node);
    }
}

void GATTService::request_read_callback(vm_gatt_conn_struct *conn, VMUINT16 trans_id, VM_BD_ADDR *bd_addr,
                                      VM_ATT_HANDLE attr_handle, VMUINT16 offset, VMBOOL is_long)
{
    LGATTService *service = GATTServer::getCtxByCTX(conn->reg_ctx);
    APP_LOG("request_read_callback is_long[%d] att[%d] bd_addr[0x%x] -s", is_long, attr_handle, bd_addr);
    if (service)
    {
        gatts_q_node *node = new gatts_q_node(GATTS_EVENT_ON_READ, service);
        LGATTReadRequest *read = (LGATTReadRequest *)(node->data);
        read->trans_id = trans_id;
        read->attr_handle = attr_handle;
        read->offset = offset;
        //read->is_long = is_long;
        memcpy(read->bd.addr, bd_addr->addr, LGATT_BD_ADDR_SIZE);
        GATTServer::rEnQ(*node);
        APP_LOG("request_read_callback trans_id[%d] OK", trans_id);
    }
    APP_LOG("request_read_callback -e");
}
void GATTService::request_write_callback(vm_gatt_conn_struct *conn, VMUINT16 trans_id, VM_BD_ADDR *bd_addr,
                                       VM_ATT_HANDLE attr_handle, VM_ATT_VALUE *value, VMUINT16 offset,
                                       VMBOOL need_rsp, VMBOOL is_prep)
{
    LGATTService *service = GATTServer::getCtxByCTX(conn->reg_ctx);
    APP_LOG("request_write_callback need_rsp[%d] att[%d] value[0x%x] bd_addr[0x%x] -s", need_rsp, attr_handle, value, bd_addr);
    if (service)
    {
        gatts_q_node *node = new gatts_q_node(GATTS_EVENT_ON_WRITE, service);
        LGATTWriteRequest *written = (LGATTWriteRequest *)(node->data);
        written->trans_id = trans_id;
        written->attr_handle = attr_handle;
        written->offset = offset;
        written->need_rsp = need_rsp;
        //written->is_prep = is_prep;
        memcpy(written->bd.addr, bd_addr->addr, LGATT_BD_ADDR_SIZE);
        written->value.len = value->len;
        memcpy(written->value.value, value->value, LGATT_ATT_MAX_VALUE_LEN);
        GATTServer::rEnQ(*node);
        APP_LOG("request_write_callback trans_id[%d] OK", trans_id);
    }
    APP_LOG("request_write_callback -e", need_rsp, attr_handle, value, bd_addr);
}

boolean gattServerRemoteCallHandler(void *userdata)
{
    LGATTServerClass *server = (LGATTServerClass *)userdata;
    if (NULL == server)
    {
        server->_result = false;
        return true;
    }

    switch (server->_action)
    {
    case LGATTServerClass::ACTION_BEGIN: 
        return GATTServer::rBegin(server);
        break;
    case LGATTServerClass::ACTION_END:
        return GATTServer::rEnd(server);
        break;
    case LGATTServerClass::ACTION_HANDLE_EVENTS:
        break;
    default:
        break;
    }
    return true;
}

VMINT GATTServer::_hdl_btcm = 0;
LGATTServerClass *GATTServer::_server = NULL;

void GATTServer::btcm_cb(VMUINT evt, void* param, void* user_data)
{
    APP_LOG("[btcm_cb] btcm_cb(), evt:%d", evt);
    LGATTServerClass *server = (LGATTServerClass *)user_data;
    switch (evt)
    {
        case VM_SRV_BT_CM_EVENT_ACTIVATE:
        {
            // BT is turned on
            server->_result = true;
            server->post_signal();
            break;
        }
        case VM_SRV_BT_CM_EVENT_DEACTIVATE:
        {
            GATTServer::deinit(server);

            // BT is turned off
            if (server->_action == LGATTServerClass::ACTION_END)
            {
                server->_result = true;
                server->post_signal();
            }
            break;
        }
        default:
            break;
    }
}

boolean GATTServer::init(LGATTServerClass *server)
{
    if (0 == GATTServer::_hdl_btcm)
    {
        GATTServer::_hdl_btcm = vm_btcm_init(GATTServer::btcm_cb, 
            VM_SRV_BT_CM_EVENT_ACTIVATE | VM_SRV_BT_CM_EVENT_DEACTIVATE, 
            (void *)server);           
        if (GATTServer::_hdl_btcm < 0)
        {
            server->_result = false;
            GATTServer::_hdl_btcm = 0;
            return false;
        }
    }

    return true;
}

boolean GATTServer::deinit(LGATTServerClass *server)
{
    if (0 < GATTServer::_hdl_btcm)
    {
        vm_btcm_exit(GATTServer::_hdl_btcm);
        GATTServer::_hdl_btcm = 0;
    }

    return true;
}


LGATTService *GATTServer::getCtxByUUID(vm_bt_uuid_struct *app_uuid)
{
    
    for (int i = 0; (i < MAX_SERVICES && LGATTServer._gatts_service[i]); i++)
    {
        if (0 == memcmp(SRV_CTX(LGATTServer._gatts_service[i])->bt_uuid.uu, 
            app_uuid->uu, 
            sizeof(SRV_CTX(LGATTServer._gatts_service[i])->bt_uuid.uu)))
        {
            return LGATTServer._gatts_service[i];
        }
    }
    
	return NULL;
}

LGATTService *GATTServer::getCtxByCTX(void *reg_ctx)
{
    for (int i = 0; (i < MAX_SERVICES && LGATTServer._gatts_service[i]); i++)
    {
        if (reg_ctx == SRV_CTX(LGATTServer._gatts_service[i])->reg_ctx)
        {
            return LGATTServer._gatts_service[i];
        }
    }

	return NULL;
}

LGATTService *GATTServer::getCtxByHandle(void *reg_ctx, VM_ATT_HANDLE srvc_handle)
{
    for (int i = 0; (i < MAX_SERVICES && LGATTServer._gatts_service[i]); i++)
    {
        if (reg_ctx == SRV_CTX(LGATTServer._gatts_service[i])->reg_ctx && 
            srvc_handle == SRV_CTX(LGATTServer._gatts_service[i])->srv_handle)
        {
            return LGATTServer._gatts_service[i];
        }
    }
    return NULL;
}

boolean GATTServer::rBegin(LGATTServerClass *server)
{
    APP_LOG("GATTServer::rBegin -S");
    _server = server;
    
    GATTServer::init(server);
    
    VMINT status = vm_btcm_get_power_status();
    APP_LOG("GATTServer::rBegin vm_btcm_get_power_status [%d]", status);
    if (VM_SRV_BT_CM_POWER_ON == status)
    {
        server->_result = true;
        APP_LOG("GATTServer::rBegin VM_SRV_BT_CM_POWER_ON -E1");
        return true;
    }
    else if (VM_SRV_BT_CM_POWER_OFF == status)
    {

        vm_btcm_switch_on();
        APP_LOG("GATTServer::rBegin vm_btcm_switch_on -E2");
    }
    APP_LOG("GATTServer::rBegin -E");
    return false;
}

boolean GATTServer::rEnd(LGATTServerClass *server)
{
    if (VM_SRV_BT_CM_POWER_OFF == vm_btcm_get_power_status())
    {
        server->_result = true;
        return true;
    }
    else if (VM_SRV_BT_CM_POWER_ON == vm_btcm_get_power_status())
    {
        vm_btcm_switch_off();
    }

    return false;
}

boolean GATTServer::rEnQ(const gatts_q_node &node)
{
    LGATTServer.enQ((gatts_q_node *)&node);
};


//static gatts_srv_ctx_t g_gatts_ctx;
//
//static gatts_srv_ctx_t *int_gatt_du_new_ctx(){return &g_gatts_ctx;}
//static gatts_srv_ctx_t *int_gatt_du_get_ctx_by_reg(void *reg_ctx)
//{
//    if (reg_ctx == g_gatts_ctx.reg_ctx)
//    {
//        return &g_gatts_ctx;
//    }
//    else
//    {
//        return NULL;
//    }
//};
//static gatts_srv_ctx_t *int_gatt_du_get_ctx_by_uuid(vm_bt_uuid_struct *app_uuid)
//{
//	if(0 == memcmp(app_uuid, &g_gatts_ctx.bt_uuid, sizeof(vm_bt_uuid_struct)))
//	{
//	
//        return &g_gatts_ctx;
//    }
//    else
//        return NULL;
//};
//static void int_gatt_du_delete_ctx(gatts_srv_ctx_t *ctx){};
//
///** Callback invoked in response to register */
//void register_server_callback(void *reg_ctx, VM_OS_STATUS status, vm_bt_uuid_struct *app_uuid)
//{
//    
//    static VM_GATT_SVC_UUID srv_uuid;
//    gatts_srv_ctx_t *ctx = int_gatt_du_get_ctx_by_uuid(app_uuid);
//    APP_LOG("register_server_callback status[%d] -s", status, status);
//    if (ctx)
//    {
//        
//        APP_LOG("uuid[0x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x] -s", status, 
//            app_uuid->uu[0], app_uuid->uu[1], app_uuid->uu[2], app_uuid->uu[3],
//            app_uuid->uu[4], app_uuid->uu[5], app_uuid->uu[6], app_uuid->uu[7],
//            app_uuid->uu[8], app_uuid->uu[9], app_uuid->uu[10], app_uuid->uu[11],
//            app_uuid->uu[12], app_uuid->uu[13], app_uuid->uu[14], app_uuid->uu[15]
//            );
//        
//        ctx->reg_ctx = reg_ctx;
//    
//        if (VM_OS_STATUS_SUCCESS == status)
//        {
//            
//
//            //srv_uuid = (VM_GATT_SVC_UUID*)vm_calloc(sizeof(VM_GATT_SVC_UUID));
//            
//            APP_LOG("srv_uuid [0x%x] 11 ", 0, &srv_uuid);
//            /*
//			srv_uuid.uuid.uuid.len = 16;
//            srv_uuid.is_primary = 1;
//			memcpy(srv_uuid.uuid.uuid.uuid, &g_svc_uid, sizeof(VM_BT_UUID));
//			vm_gatts_add_service(reg_ctx, &srv_uuid, 1);
//			*/
//            int_gatt_add_declaration(ctx->reg_ctx, 0, TYPE_SERVICE);
//        }
//        else
//        {
//            gatt_handle hdl = {0};
//            dulife_state_init_t init = {0};
//            //init.state = VM_DULIFE_STATE_INIT; //int_gatt_map_state(GATT_STATE_INIT, status);
//            init.error_code = (DULIFE_ERR_E)status;
//            init.user_data = ctx->user_data;
//            init.srv_handle = 0;
//            hdl.conn_ctx = NULL;
//            hdl.reg_ctx = reg_ctx;
//            if (ctx->app_cb)
//                ctx->app_cb(&hdl, VM_DULIFE_STATE_INIT, &init);
//        }
//    }
//    APP_LOG("register_server_callback -e", 0);
//
//}
//
///** Callback indicating that a remote device has connected or been disconnected */
//void connection_callback(vm_gatt_conn_struct *conn, VMBOOL connected, VM_BD_ADDR *bd_addr)
//{
//    gatts_srv_ctx_t *ctx;
//    VM_ASSERT(conn);
//    APP_LOG("connection_callback connected [%d] [0x%x, 0x%x] -s", connected, connected, conn->reg_ctx, conn->conn_ctx);
//    ctx = int_gatt_du_get_ctx_by_reg(conn->reg_ctx);
//    if (ctx)
//    {
//        dulife_state_connection_t connection = {0};
//        gatt_handle hdl = {0};
//
//        if (connected)
//        {
//            vm_gatts_listen(conn->reg_ctx, VM_FALSE);
//            APP_LOG("vm_gatts_listen stop", 0);
//            memcpy(ctx->addr.addr, bd_addr->addr, LGATT_BD_ADDR_SIZE);
//            ctx->status = 1;
//        }
//        else 
//        {
//            if(memcmp(bd_addr->addr, ctx->addr.addr, LGATT_BD_ADDR_SIZE) == 0)
//            {
//                APP_LOG("vm_gatts_listen again", 0);
//                vm_gatts_listen(conn->reg_ctx, TRUE);
//                ctx->status = 0;
//            }
//        }
//        //connection.state = VM_DULIFE_STATE_CONNECTION; //int_gatt_map_state(GATT_STATE_CONNECTION, connected ? VM_OS_STATUS_SUCCESS : VM_OS_STATUS_FAILED);
//        connection.error_code = connected ? VM_DULIFE_ERR_SUCCESS : VM_DULIFE_ERR_FAILED;
//        connection.user_data = ctx->user_data;
//        connection.addr = bd_addr;
//        connection.connected = connected;
//        hdl.conn_ctx = conn->conn_ctx;
//        hdl.reg_ctx = conn->reg_ctx;
//        if (bd_addr)
//        {
//            APP_LOG("connection_callback bd_addr [0x%x:%x:%x:%x:%x:%x]", 0, bd_addr->addr[0], bd_addr->addr[1], bd_addr->addr[2], 
//                bd_addr->addr[3], bd_addr->addr[4], bd_addr->addr[5]);
//        }
//        if (ctx->app_cb)
//            ctx->app_cb(&hdl, VM_DULIFE_STATE_CONNECTION, &connection);
//    }
//    APP_LOG("connection_callback connected -E", 0);
//}
////
/////** Callback triggered in response to listen */
////void listen_callback(void *reg_ctx, VM_OS_STATUS status)
////{
////    
////    gatts_srv_ctx_t *ctx = int_gatt_du_get_ctx_by_reg(reg_ctx);
////    APP_LOG("listen_callback status[%d] -s", status, status);
////    if (ctx)
////    {
////                    
////        dulife_state_init_t init = {0};
////        gatt_handle hdl = {0};
////        //init.state = VM_DULIFE_STATE_INIT; //int_gatt_map_state(GATT_STATE_INIT, status);
////        init.error_code = (DULIFE_ERR_E)status;
////        init.user_data = ctx->user_data;
////        init.srv_handle = ctx->srv_handle;
////
////        init.char_rx_handle = ctx->data_rx.char_handle;
////        init.char_tx_handle = ctx->data_tx.char_handle;
////
////        hdl.reg_ctx = reg_ctx;
////        
////        APP_LOG("listen_callback srv_handle[%d] conn_status[%d]", status, init.srv_handle, ctx->status);
////
////        if (0 == ctx->status)
////        {
////            if (ctx->app_cb)
////                ctx->app_cb(&hdl, VM_DULIFE_STATE_INIT, &init);
////        }
////    }
////    APP_LOG("listen_callback -e", 0);
////}
///** Callback invoked in response to create_service */
//void service_added_callback(VM_OS_STATUS status, void *reg_ctx,
//                VM_GATT_SVC_UUID *srvc_id, VM_ATT_HANDLE srvc_handle)
//{
//    gatts_srv_ctx_t *ctx;
//    APP_LOG("service_added_callback reg_ctx[0x%x] srv_id[0x%x] -s", status, reg_ctx, srvc_id);
//    ctx = int_gatt_du_get_ctx_by_reg(reg_ctx);
//    if (ctx)
//    {
//        APP_LOG("ctx has", 0);
//        if (srvc_id)
//        {
//            
//            APP_LOG("[0x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x] %d[%d][%d]", status, 
//                srvc_id->uuid.uuid.uuid[0], srvc_id->uuid.uuid.uuid[1], srvc_id->uuid.uuid.uuid[2], srvc_id->uuid.uuid.uuid[3],
//                srvc_id->uuid.uuid.uuid[4], srvc_id->uuid.uuid.uuid[5], srvc_id->uuid.uuid.uuid[6], srvc_id->uuid.uuid.uuid[7],
//                srvc_id->uuid.uuid.uuid[8], srvc_id->uuid.uuid.uuid[9], srvc_id->uuid.uuid.uuid[10], srvc_id->uuid.uuid.uuid[11],
//                srvc_id->uuid.uuid.uuid[12], srvc_id->uuid.uuid.uuid[13], srvc_id->uuid.uuid.uuid[14], srvc_id->uuid.uuid.uuid[15],
//                srvc_id->is_primary, srvc_id->uuid.inst, srvc_id->uuid.uuid.len
//                );
//                
//            APP_LOG("srvc_id has", 0);
//        }
//        else
//        {
//            APP_LOG("srvc_id NULL", 0);
//        }
//        if (VM_OS_STATUS_SUCCESS == status)
//        {
//            ctx->srv_handle = srvc_handle;
//            APP_LOG("1", 0);
//            int_gatt_add_declaration(ctx->reg_ctx, srvc_handle, TYPE_CHARACTERISTIC);
//            APP_LOG("2", 0);
//        }
//        else
//        {
//            dulife_state_init_t init = {0};
//            gatt_handle hdl = {0};
//            //init.state = VM_DULIFE_STATE_INIT;//int_gatt_map_state(GATT_STATE_INIT, status);
//            APP_LOG("3", 0);
//            init.error_code = (DULIFE_ERR_E)status;
//            init.user_data = ctx->user_data;
//            init.srv_handle = 0;
//            hdl.reg_ctx = reg_ctx;
//            if (ctx->app_cb)
//                ctx->app_cb(&hdl, VM_DULIFE_STATE_INIT, &init);
//        }
//    }
//    APP_LOG("service_added_callback status -e", 0);
//}
///** Callback indicating that an included service has been added to a service */
//void included_service_added_callback(VM_OS_STATUS status, void *reg_ctx,
//                VM_ATT_HANDLE srvc_handle, VM_ATT_HANDLE incl_srvc_handle)
//{
//
//}
///** Callback invoked when a characteristic has been added to a service */
//void characteristic_added_callback(VM_OS_STATUS status, void *reg_ctx,
//                VM_ATT_UUID *uuid, VM_ATT_HANDLE srvc_handle, VM_ATT_HANDLE char_handle)
//{
//    
//    gatts_srv_ctx_t *ctx = int_gatt_du_get_ctx_by_reg(reg_ctx);
//    APP_LOG("characteristic_added_callback status[%d] srv_handle[%d]char_handle[%d] -s", status, status, srvc_handle, char_handle);
//    if (ctx)
//    {
//        if (VM_OS_STATUS_SUCCESS == status)
//        {
//            VMINT ret = 0, type;
//
//            if (uuid)
//            {
//            APP_LOG("uuid[0x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x] [%d][%d]", status, 
//                uuid->uuid.uuid[0], uuid->uuid.uuid[1], uuid->uuid.uuid[2], uuid->uuid.uuid[3],
//                uuid->uuid.uuid[4], uuid->uuid.uuid[5], uuid->uuid.uuid[6], uuid->uuid.uuid[7],
//                uuid->uuid.uuid[8], uuid->uuid.uuid[9], uuid->uuid.uuid[10], uuid->uuid.uuid[11],
//                uuid->uuid.uuid[12], uuid->uuid.uuid[13], uuid->uuid.uuid[14], uuid->uuid.uuid[15],
//                uuid->inst, uuid->uuid.len
//                );
//            }
//            ret = int_gatt_set_characteristic(ctx, char_handle, uuid);
//            VM_ASSERT(ret != 0);
//            type = int_gatt_add_declaration(ctx->reg_ctx, srvc_handle, TYPE_CHARACTERISTIC);
//            if (TYPE_DESCRIPTOR == type)
//            {
//            //#define GATT_TRANSPORT_LE                0x00
//            //#define GATT_TRANSPORT_BR_EDR            0x01
//            //#define GATT_TRANSPORT_LE_BR_EDR         0x02    
//                //APP_LOG("vm_gatts_start_service", 0);
//                //vm_gatts_start_service(ctx->reg_ctx, srvc_handle, 0x00); // TODO: what are those value mean?
//                APP_LOG("add TYPE_DESCRIPTOR", 0);
//                //vm_gatts_add_descriptor(ctx->reg_ctx,ctx->srv_handle, VM_ATT_UUID * uuid,VM_GATT_PERMISSION permission)
//                int_gatt_add_declaration(ctx->reg_ctx, srvc_handle, TYPE_DESCRIPTOR);
//                
//            }
//            else if (TYPE_UNKNOW == type)
//            {
//                APP_LOG("vm_gatts_start_service", 0);
//                vm_gatts_start_service(ctx->reg_ctx, srvc_handle, 0x00);
//            }
//        }
//        else
//        {
//            dulife_state_init_t init = {0};
//            gatt_handle hdl = {0};
//            //init.state = VM_DULIFE_STATE_INIT; //int_gatt_map_state(GATT_STATE_INIT, status);
//            init.error_code = (DULIFE_ERR_E)status;
//            init.user_data = ctx->user_data;
//            init.srv_handle = srvc_handle;
//            hdl.reg_ctx = reg_ctx;
//            if (ctx->app_cb)
//                ctx->app_cb(&hdl, VM_DULIFE_STATE_INIT, &init);
//        }
//    }
//    APP_LOG("characteristic_added_callback -e", 0);
//}
/////** Callback invoked when a descriptor has been added to a characteristic */
////void descriptor_added_callback(VM_OS_STATUS status, void *reg_ctx,
////                VM_ATT_UUID *uuid, VM_ATT_HANDLE srvc_handle, VM_ATT_HANDLE descr_handle)
////{
////    gatts_srv_ctx_t *ctx = int_gatt_du_get_ctx_by_reg(reg_ctx);
////    APP_LOG("descriptor_added_callback status[%d] srv_handle[%d]descr_handle[%d] -s", status, status, srvc_handle, descr_handle);
////    if (ctx)
////    {
////        if (VM_OS_STATUS_SUCCESS == status)
////        {
////        	VMINT ret;
////            //ret = int_gatt_set_characteristic(ctx, descr_handle, uuid);
////			ctx->data_des.char_handle = descr_handle;
////			ctx->data_des.trans_id = 0;
////			ctx->data_des.value;
////            //VM_ASSERT(ret != 0);
////            ret = int_gatt_add_declaration(ctx->reg_ctx, srvc_handle, TYPE_CHARACTERISTIC);
////            if (TYPE_DESCRIPTOR == ret)
////            {
////                APP_LOG("add TYPE_DESCRIPTOR", 0);
////                int_gatt_add_declaration(ctx->reg_ctx, srvc_handle, TYPE_DESCRIPTOR);
////            }
////            else if (TYPE_CHARACTERISTIC == ret)
////            {
////                APP_LOG("add TYPE_CHARACTERISTIC", 0);
////                //int_gatt_add_declaration(ctx->reg_ctx, srvc_handle, TYPE_DESCRIPTOR);
////            }
////            else if (TYPE_UNKNOW == ret) // touch the end of profile
////            {
////                APP_LOG("vm_gatts_start_service", 0);
////                vm_gatts_start_service(ctx->reg_ctx, srvc_handle, 0x00);
////            }
////        }
////    }
////    APP_LOG("descriptor_added_callback status -e", 0);
////}
///** Callback invoked in response to start_service */
//void service_started_callback(VM_OS_STATUS status, void *reg_ctx,
//                                         VM_ATT_HANDLE srvc_handle)
//{
//    gatts_srv_ctx_t *ctx = int_gatt_du_get_ctx_by_reg(reg_ctx);
//    APP_LOG("service_started_callback srv_handle[%d] -s", 0, srvc_handle);
//    if (ctx)
//    {
//        if (VM_OS_STATUS_SUCCESS == status)
//        {
//            APP_LOG("vm_gatts_listen", 0);
//            vm_gatts_listen(ctx->reg_ctx, 1);
//        }
//        else
//        {
//        
//            dulife_state_init_t init = {0};
//            gatt_handle hdl = {0};
//            //init.state = VM_DULIFE_STATE_INIT; //int_gatt_map_state(GATT_STATE_INIT, status);
//            init.error_code = (DULIFE_ERR_E)status;
//            init.user_data = ctx->user_data;
//            init.srv_handle = srvc_handle;
//            hdl.reg_ctx = reg_ctx;
//            if (ctx->app_cb)
//                ctx->app_cb(&hdl, VM_DULIFE_STATE_INIT, &init);
//
//        }
//    }
//    APP_LOG("service_started_callback -e", 0);
//}
///** Callback invoked in response to stop_service */
//void service_stopped_callback(VM_OS_STATUS status, void *reg_ctx,
//                                         VM_ATT_HANDLE srvc_handle)
//{
//    gatts_srv_ctx_t *ctx = int_gatt_du_get_ctx_by_reg(reg_ctx);
//    int_gatt_trans_data_delete_all(ctx);
//}
///** Callback triggered when a service has been deleted */
//void service_deleted_callback(VM_OS_STATUS status, void *reg_ctx,
//                                         VM_ATT_HANDLE srvc_handle)
//{
//    gatts_srv_ctx_t *ctx = int_gatt_du_get_ctx_by_reg(reg_ctx);
//    int_gatt_trans_data_delete_all(ctx);
//}




//
//
//
//
//typedef struct _vm_node_t vm_node_t;
//struct _vm_node_t
//{
//    VMUINT idx;
//    void *user_data;
//    vm_node_t *next;
//};
//
//static vm_node_t *vm_list_int_alloc(gatts_srv_ctx_t *ctx_p)
//{
//    vm_node_t *client;
//    vm_node_t *tmp;
//    if (NULL == ctx_p)
//        return NULL;
//
//	client = vm_calloc(sizeof(vm_node_t));
//	if (NULL == client)
//	    return NULL;
//
//    client->idx = 0;//(VMUINT)client;
//    
//    tmp = ctx_p->head;
//    if (NULL == tmp)
//    {
//        ctx_p->head = client;
//        return client;
//    }
//    
//    while (tmp->next)
//    {
//        tmp = tmp->next;
//        
//    }
//
//    tmp->next = client;
//    
//     
//    return client;
//}
//
//static void vm_list_int_free(vm_btgatt_context_t *ctx_p, VMUINT idx)
//{
//    vm_node_t *p, *q;
//    if (NULL == ctx_p || 0 >= idx)
//        return;
//
//    p = ctx_p->head;
//    if (NULL == p)
//    {
//        return;    
//    }
//    else
//    {
//        if (p->idx == idx)
//        {
//            ctx_p->head = p->next;
//            vm_free(p);
//            return;
//        }
//    }
//
//    q = p->next;
//    while (q)
//    {
//        if (idx == q->idx)
//        {
//            p->next = q->next;
//            vm_free(q);
//            return;   
//        }
//        p = q;
//        q = q->next;
//    }
//    
//}
//
//static void vm_list_int_release_all(vm_btgatt_context_t *ctx_p)
//{
//    vm_node_t *tmp;
//    if (NULL == ctx_p)
//    {
//        return;
//    }
//
//    tmp = ctx_p->head;
//    if (NULL == tmp)
//        return;
//    
//    while (tmp)
//    {
//        ctx_p->head = tmp->next;
//        vm_free(tmp);
//        tmp = ctx_p->head;
//    }
//
//
//    
//}
//
//static vm_node_t * vm_list_int_get(vm_btgatt_context_t *ctx_p, VMUINT idx)
//{
//    vm_node_t *tmp;
//    if (NULL == ctx_p || 0 >= idx)
//        return NULL;
//
//    tmp = ctx_p->head;
//    while (tmp)
//    {
//        if (tmp->idx == idx)
//            return tmp;
//        tmp = tmp->next;
//    }
//    return NULL;
//}
