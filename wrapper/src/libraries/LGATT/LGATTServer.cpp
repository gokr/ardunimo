
#include "LGATTServer.h"
#include "GATTServer.h"
#include <stdarg.h>

struct gatts_srv_ctx_t;
extern gatts_srv_ctx_t *gatts_new_ctx();
extern void gatts_delete_ctx(gatts_srv_ctx_t *ctx);

gatts_q_node::gatts_q_node(gatts_evt e, void *s) : evt(e), service(s), data(NULL)
{
    switch (e)
    {
    case GATTS_EVENT_ON_CONNETION:
        {
            data = new LGATTConnection();
        }
        break;
    case GATTS_EVENT_ON_CHAR_ADDED:
    case GATTS_EVENT_ON_DESC_ADDED:
        {
            data = new LGATTAttributeData();
        }
        break;
    case GATTS_EVENT_ON_READ:
        {
            data = new LGATTReadRequest();
        }
        break;
    case GATTS_EVENT_ON_WRITE:
        {
            data = new LGATTWriteRequest();
        }
        break;
    }
}
gatts_q_node::~gatts_q_node()
{
    delete data;
}

LGATTService::LGATTService()
{
    //memset(this, 0, sizeof(LGATTService));
    
    _gatts_srv_ctx = gatts_new_ctx();
}

LGATTService::~LGATTService()
{
    gatts_delete_ctx((gatts_srv_ctx_t *)_gatts_srv_ctx);
}

// characteristic added
boolean LGATTService::onCharacteristicAdded(LGATTAttributeData &data)
{
    
    APP_LOG("LGATTService::onCharacteristicAdded -S");
    const VM_BT_UUID *uuid = &(data.uuid);
    
    APP_LOG("failed[%d], handle[%d], inst[%d], uuid[0x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x] len[%d]", 
        data.failed, data.handle, 0, 
        uuid->uuid[15], 
        uuid->uuid[14], 
        uuid->uuid[13], 
        uuid->uuid[12], 
        uuid->uuid[11], 
        uuid->uuid[10], 
        uuid->uuid[9], 
        uuid->uuid[8], 
        uuid->uuid[7], 
        uuid->uuid[6], 
        uuid->uuid[5], 
        uuid->uuid[4], 
        uuid->uuid[3], 
        uuid->uuid[2], 
        uuid->uuid[1], 
        uuid->uuid[0], 
        uuid->len);
        
    APP_LOG("LGATTService::onCharacteristicAdded -E");
    return true;
}
// descriptor added
boolean LGATTService::onDescriptorAdded(LGATTAttributeData &data)
{
    APP_LOG("LGATTService::onDescriptorAdded -S");
    const VM_BT_UUID *uuid = &(data.uuid);
    APP_LOG("failed[%d], handle[%d], inst[%d], uuid[0x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x] len[%d]", 
        data.failed, data.handle, 0, 
        uuid->uuid[15], 
        uuid->uuid[14], 
        uuid->uuid[13], 
        uuid->uuid[12], 
        uuid->uuid[11], 
        uuid->uuid[10], 
        uuid->uuid[9], 
        uuid->uuid[8], 
        uuid->uuid[7], 
        uuid->uuid[6], 
        uuid->uuid[5], 
        uuid->uuid[4], 
        uuid->uuid[3], 
        uuid->uuid[2], 
        uuid->uuid[1], 
        uuid->uuid[0], 
        uuid->len);
    APP_LOG("LGATTService::onDescriptorAdded -E");
    return true;
}
// connected or disconnected
boolean LGATTService::onConnection(const LGATTAddress &addr, boolean connected)
{
    APP_LOG("LGATTService::onConnection -S");
    APP_LOG("connected[%d], bd_addr[0x%02x%02x%02x%02x%02x%02x]", connected, 
        addr.addr[0],
        addr.addr[1],
        addr.addr[2],
        addr.addr[3],
        addr.addr[4],
        addr.addr[5]
        );
    APP_LOG("LGATTService::onConnection -E");
    return true;
}
// read action comming from master
boolean LGATTService::onRead(LGATTReadRequest &data)
{
    APP_LOG("LGATTService::onRead -S");
    APP_LOG("tid[%d], bd_addr[0x%02x%02x%02x%02x%02x%02x] handle[%d], os[%d]",
        data.trans_id, 
        data.bd.addr[0],
        data.bd.addr[1],
        data.bd.addr[2],
        data.bd.addr[3],
        data.bd.addr[4],
        data.bd.addr[5],
        data.attr_handle,
        data.offset
        );
    APP_LOG("LGATTService::onRead -E");
    return true;
}
// write action comming from master
boolean LGATTService::onWrite(LGATTWriteRequest &data)
{
    APP_LOG("LGATTService::onCharacteristicAdded -S");
    APP_LOG("tid[%d], bd_addr[0x%02x%02x%02x%02x%02x%02x] handle[%d], nr[%d]",
        data.trans_id, 
        data.bd.addr[0],
        data.bd.addr[1],
        data.bd.addr[2],
        data.bd.addr[3],
        data.bd.addr[4],
        data.bd.addr[5],
        data.attr_handle,
        data.offset,
        data.need_rsp
        );
    APP_LOG("value [%s][%d]", data.value.value, data.value.len);
    APP_LOG("LGATTService::onCharacteristicAdded -E");
    return true;
}

boolean LGATTService::begin(const LGATTUUID &uuid, int32_t index, int32_t timeout)
{
    APP_LOG("LGATTService::begin idx[%d] -S", index);
    _gatts_service = onLoadService(index);
    if (NULL == _gatts_service)
    {
        _result = false;
        APP_LOG("LGATTService::begin onLoadService FAILED");
        return false;
    }
    //Serial.print(uuid);
    memcpy(_uuid, &uuid, sizeof(_uuid));
    // do register do profiles creation(add service, add characteristic, add discriptor)
    GATTS_REMOTE_CALL(ACTION_BEGIN, gattServiceRemoteCallHandler, this);

    APP_LOG("LGATTService::begin -E");

    return _result;
}

void LGATTService::end()
{
    APP_LOG("LGATTService::end -S");
    GATTS_REMOTE_CALL(ACTION_END, gattServiceRemoteCallHandler, this);
    APP_LOG("LGATTService::end -E");
}

boolean LGATTService::sendIndication(const LGATTAttributeValue &value, uint16_t attr_handle, boolean needConfirm) // true : indication; false : notify
{
    APP_LOG("LGATTService::send -S");
    _value = (LGATTAttributeValue*)&value;
    _attr_handle = attr_handle;
    _confirm_failed = needConfirm;
    GATTS_REMOTE_CALL(ACTION_SEND, gattServiceRemoteCallHandler, this);
    APP_LOG("LGATTService::send -E");
    return _result;
}

boolean LGATTService::sendResponse(const LGATTAttributeValue &value, uint16_t attr_handle, boolean failed, uint16_t trans_id) // ACK
{
    APP_LOG("LGATTService::send ACK -S");
    _value = (LGATTAttributeValue*)&value;
    _attr_handle = attr_handle;
    _confirm_failed = failed;
    _trans_id = trans_id;
    GATTS_REMOTE_CALL(ACTION_SEND_ACK, gattServiceRemoteCallHandler, this);
    APP_LOG("LGATTService::send ACK -E");
    return _result;
}

LGATTServerClass::LGATTServerClass()
{
    memset(this, 0, sizeof(*this));
}

LGATTServerClass::~LGATTServerClass()
{}

static LGATTUUID g_gatts_uuid("9D6EB1F1-F16D-5B84-5640-E5FF491FA020");

boolean LGATTServerClass::begin(int32_t service_nums, ...)
{
    APP_LOG("LGATTServerClass::begin service_nums[%d] -S", service_nums);
    if (MAX_SERVICES < service_nums || 0 >= service_nums)
    {
        APP_LOG("LGATTServerClass::begin -E1");
        return false;
    }
    LGATTUUID uuidObj = g_gatts_uuid;

    VM_BT_UUID *uuidInt = (VM_BT_UUID *)&uuidObj;
    //memcpy(_uuid.uu, uuid, sizeof(_uuid.uu));
    GATTS_REMOTE_CALL(ACTION_BEGIN, gattServerRemoteCallHandler, this);

    va_list args;
    va_start(args, service_nums);
    for (int i = 0; i < service_nums; i++)
    {
        _gatts_service[i] = va_arg(args, LGATTService *); 
        uuidInt->uuid[0] += i;
        _gatts_service[i]->begin(uuidObj, i);
    }
    va_end(args);

    APP_LOG("LGATTServerClass::begin -E");
    return _result;
}


void LGATTServerClass::end()
{
    APP_LOG("LGATTServerClass::end -S");
    GATTS_REMOTE_CALL(ACTION_END, gattServerRemoteCallHandler, this);
    memset(this, 0, sizeof(*this));
    APP_LOG("LGATTServerClass::end -E");
}

void LGATTServerClass::handleEvents()
{
    APP_LOG("LGATTServer::handleEvents -S");
    gatts_q_node *node = frQ();
    boolean ret = false;

    while (node)
    {
        APP_LOG("LGATTServer::handleEvents event[%d]", node->evt);
        LGATTService *service = (LGATTService*)node->service;
        node->data->_srv = service;
        switch (node->evt)
        {
        case GATTS_EVENT_ON_CONNETION:
            {
                LGATTConnection &connection = *(LGATTConnection*)node->data;
                ret = service->onConnection(connection.addr, connection.connected);
            }break;
        case GATTS_EVENT_ON_CHAR_ADDED:
            {
                ret = service->onCharacteristicAdded(*(LGATTAttributeData*)node->data);
            }break;
        case GATTS_EVENT_ON_DESC_ADDED:
            {
                ret = service->onDescriptorAdded(*(LGATTAttributeData*)node->data);
            }break;
        case GATTS_EVENT_ON_READ:
            {
                ret = service->onRead(*(LGATTReadRequest*)node->data);
            }break;
        case GATTS_EVENT_ON_WRITE:
            {
                ret = service->onWrite(*(LGATTWriteRequest*)node->data);
            }break;
        default:
            break;
        }
        delete node;
        deQ();
        node = frQ();

    }

    APP_LOG("LGATTServer::handleEvents -E");
}

LGATTServerClass *LGATTServerClass::_server = NULL;

LGATTServerClass &LGATTServerClass::getServer()
{
    if (NULL == LGATTServerClass::_server)
    {
        LGATTServerClass::_server = new LGATTServerClass();
        return *(LGATTServerClass::_server);
    }
    return *(LGATTServerClass::_server);
}

boolean LGATTServerClass::enQ(gatts_q_node *node)
{
    mutexLock();

    if (((_ba + 1) % MAX_QUEUE_NODES) == _fr)
    {
        mutexUnlock();
        return false;
    }

    _cq[_ba] = node;
    _ba = (_ba + 1) % MAX_QUEUE_NODES;
    _size++;

    mutexUnlock();
    return true;
}

boolean LGATTServerClass::deQ()
{
    mutexLock();
    if (0 == _size)
    {
        mutexUnlock();
        return false;
    }
    
    _fr = (_fr + 1) % MAX_QUEUE_NODES;
    _size--;

    mutexUnlock();
    return true;
}

gatts_q_node *LGATTServerClass::frQ()
{
    mutexLock();
    if (0 == _size)
    {
        mutexUnlock();
        return NULL;
    }   

    gatts_q_node *tmp = _cq[_fr];
    mutexUnlock();
    return tmp;
}




