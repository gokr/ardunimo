#include "LGATTClient.h"
#include "GATTClient.h"

/*
int32_t LGATTClient::begin()
{
    
    _LTaskClass::remoteCall(gattBegin, this);
}
*/
#include "Arduino.h"
#include "vmlog.h"
#include "vmthread.h"
#include "LTask.h"

boolean GATTCSetClient(LGATTClient *client);

extern LGATTDeviceInfo GATT_CLIENT_BD_ADDR_LIST[];
extern const char *logGATTUUID(const LGATTUUID& uuid);

LGATTClient::LGATTClient(void)
{
    memset(&cb_data, 0x0, sizeof(lgatt_callback_data_struct));
    
    memset(&_cntx, 0x0, sizeof(_cntx));
    //cb_data.search_result.service_uuid_num = MAX_BLE_SERVICES;

    
}


boolean LGATTClient::begin(const LGATTUUID &uuid)
{
    /* lgatt_register_client_struct &register_client */
    
    LGATTUUID uuidObj = uuid;
    VM_BT_UUID *uuidInt = (VM_BT_UUID *)&uuidObj;
  APP_LOG("[LGATT]LGATTClient::begin - 1, _cntx.state = %d", _cntx.state);
  if(_cntx.state == LGATTC_STATUS_DISABLED)
	{
	    APP_LOG("[LGATT]LGATTClient::begin - 2");
		//_cntx.state = LGATTC_STATUS_ENABLING;
		memset(_cntx.uuid.uu, 0x0, sizeof(_cntx.uuid.uu));
		memcpy(_cntx.uuid.uu, uuidInt->uuid, sizeof(_cntx.uuid.uu));
		//_cntx.state = (lgatt_client_status)register_client.status;
        //cb_data.register_client.status = register_client.status;
        if (!GATTCSetClient(this))
        {
            APP_LOG("[LGATT]LGATTClient::begin - 2");
            return false;
        }
		_LTaskClass::remoteCall(gattBegin, this);
		//delay(1000);
	}
	
	APP_LOG("[LGATT]LGATTClient::begin - 3, _return_value = %d", _return_value);
	
    //memcpy(&register_client, &cb_data.register_client, sizeof(lgatt_register_client_struct));
    
    //APP_LOG("[LGATT]LGATTClient::begin - 4, register_client.status = %d", *register_client.status);
    
	return _return_value;
}

int32_t LGATTClient::scan(uint32_t timeout)
{
    /* LGATTDeviceInfo* scan_result */
    APP_LOG("[LGATT]LGATTClient::scan timeout[%d]", timeout);

    this->_cntx._timeout = timeout;
	_LTaskClass::remoteCall(gattScan, this);
	
    if (!_return_value)
        return 0;
	return _cntx._searched_ble_dev_nums;

}

boolean LGATTClient::getScanResult(int index, // IN, parameter index ranges from 0 to (scan() - 1)
                      LGATTDeviceInfo& info  // OUT, have "rssi", "LGATTAddress"
                      )
{
    if (index < 0 || index >= _cntx._searched_ble_dev_nums)
    {
        return false;
    }
    
    memcpy(&info, &GATT_CLIENT_BD_ADDR_LIST[index], sizeof(LGATTDeviceInfo));

    return true;
}

boolean LGATTClient::connect(const LGATTAddress &deviceAddress)
{
    APP_LOG("[LGATT]LGATTClient::connect - Start");
    /*
    memcpy(&cb_data.connection, &connection, sizeof(lgatt_connection_struct));
    cb_data.connection.connected = connection.connected;
    cb_data.search_result.uuid_num = search_result.uuid_num;
    cb_data.search_result.uuid = search_result.uuid;
    search_uuid_index = 0;
        
    APP_LOG("[LGATT]LGATTClient::connect - connected = %d",*(cb_data.connection.connected));
    */
    memcpy(_cntx._address.addr, deviceAddress.addr, sizeof(_cntx._address.addr));
	_LTaskClass::remoteCall(gattConnect, this);
	//delay(1000);

    //memcpy(&connection, &cb_data.connection, sizeof(lgatt_connection_struct));
    APP_LOG("[LGATT]LGATTClient::connect - End");
    
	return _return_value;
}

boolean LGATTClient::disconnect(const LGATTAddress &deviceAddress)
{
    APP_LOG("[LGATT]LGATTClient::disconnect - Start");
    /*
    memcpy(&cb_data.connection, &connection, sizeof(lgatt_connection_struct));
    cb_data.connection.connected = connection.connected;
    cb_data.search_result.uuid_num = search_result.uuid_num;
    cb_data.search_result.uuid = search_result.uuid;
    search_uuid_index = 0;
        
    APP_LOG("[LGATT]LGATTClient::connect - connected = %d",*(cb_data.connection.connected));
    */
    memcpy(_cntx._address.addr, deviceAddress.addr, sizeof(_cntx._address.addr));
	_LTaskClass::remoteCall(gattDisConnect, this);
	//delay(1000);

    //memcpy(&connection, &cb_data.connection, sizeof(lgatt_connection_struct));
    APP_LOG("[LGATT]LGATTClient::disconnect - End");
    
	return _return_value;
}

boolean LGATTClient::setupNotification(boolean enable, 
                                const LGATTUUID &serviceUUID, 
                                boolean isPrimary, 
                                const LGATTUUID& characteristicUUID)
{
    APP_LOG("[LGATT]LGATTClient::enableNotification - Start");

    this->_cntx._isEnableNotification = enable;
    this->_cntx._currServiceUUID = serviceUUID;
    this->_cntx._isPrimary = isPrimary;
    this->_cntx._currCharUUID= characteristicUUID;
    
	_LTaskClass::remoteCall(gattEnableNotification, this);
    APP_LOG("[LGATT]LGATTClient::enableNotification - End");
    
	return _return_value;
}

boolean LGATTClient::queryNotification(const LGATTUUID &serviceUUID, 
                                boolean isPrimary, 
                                const LGATTUUID& characteristicUUID,
                                LGATTAttributeValue &value)
{
    APP_LOG("[LGATT]LGATTClient::queryNotification - Start");

    
    if (this->_cntx._currServiceUUID == serviceUUID &&
        this->_cntx._isPrimary == isPrimary &&
        this->_cntx._currCharUUID == characteristicUUID)
    {
	    //_LTaskClass::remoteCall(gattQueryNotification, this);
	    
        APP_LOG("[LGATT]LGATTClient::queryNotification - len[%d]", this->_cntx._currNotificationData._attrValue.len);
	    if (this->_cntx._currNotificationData._attrValue.len > 0)
	    {
	        value = this->_cntx._currNotificationData._attrValue;
	        this->_cntx._currNotificationData._attrValue.len = 0;
            _return_value = true;
        }
        else
        {
            _return_value = false;
        }
	}
	else
	{
        _return_value = false;
	}
    APP_LOG("[LGATT]LGATTClient::queryNotification - ret[%d] End", _return_value);
    
	return _return_value;
}
uint32_t LGATTClient::getServiceCount()
{
    return this->cb_data.search_result.service_uuid_num;
}

boolean LGATTClient::getServiceInfo(int index, LGATTUUID& serviceUUID, boolean &isPrimary)
{
    APP_LOG("[LGATT]LGATTClient::getServiceInfo - [%d/%d] Start", index, cb_data.search_result.service_uuid_num);
    if (0 > index || index >= cb_data.search_result.service_uuid_num)
    {
        APP_LOG("[LGATT]LGATTClient::getServiceInfo - [%d/%d] Start1", index, cb_data.search_result.service_uuid_num);
        return false;
    }
    VM_BT_UUID *tmp = (VM_BT_UUID *)&(cb_data.search_result.uuid[index].uuid.uuid);
    serviceUUID = *tmp;
#ifdef __LINKIT_ONE_DEBUG__
    Serial.print("getServiceInfo ");
    Serial.print(serviceUUID);
    Serial.println();
#endif
    APP_LOG("getServiceInfo UUID : [%s]", logGATTUUID(serviceUUID));


    isPrimary = cb_data.search_result.uuid[index].is_primary;
    
    APP_LOG("[LGATT]LGATTClient::getServiceInfo - end");
    return true;
}

boolean LGATTClient::getCharacteristicInfo(const LGATTUUID &serviceUUID, 
                                    boolean isPrimary, 
                                    LGATTUUID& characteristicUUID, 
                                    LGATT_CHAR_PROPERTIES &properties
                                    )
{
    
    APP_LOG("[LGATT]LGATTClient::getCharacteristic - Start");

    this->_cntx._currServiceUUID = serviceUUID;
    this->_cntx._isPrimary = isPrimary;
    this->_cntx._currCharUUID = characteristicUUID;
    
    //memcpy(&cb_data.characteristic, &characteristic, sizeof(lgatt_get_characteristic_struct));
	_LTaskClass::remoteCall(gattGetCharacteristic, this);

    if (_return_value)
    {
        characteristicUUID = *(VM_BT_UUID*)(&(this->cb_data.characteristic.ch.ch_uuid.uuid));
        properties = this->cb_data.characteristic.properties;
        
    }
    APP_LOG("[LGATT]LGATTClient::getCharacteristic - End");
	return _return_value;
}

boolean LGATTClient::getDescriptorInfo(const LGATTUUID &serviceUUID, 
                            boolean isPrimary, 
                            const LGATTUUID& characteristicUUID,
                            LGATTUUID &descriptorUUID // OUT
                          )
{
    APP_LOG("[LGATT]LGATTClient::getDescriptorInfo - START");

    this->_cntx._currServiceUUID = serviceUUID;
    this->_cntx._isPrimary = isPrimary;
    this->_cntx._currCharUUID = characteristicUUID;

    _LTaskClass::remoteCall(gattGetDescriptor, this);
    if (_return_value)
    {
        descriptorUUID = *(VM_BT_UUID*)(&(this->cb_data.descriptor.descr.descr_uuid.uuid));
    }

    APP_LOG("[LGATT]LGATTClient::getDescriptorInfo - ret[%d] End", _return_value);
	return _return_value;
}

boolean LGATTClient::readCharacteristic(const LGATTUUID &serviceUUID,
                                boolean isPrimary, 
                                const LGATTUUID& characteristicUUID,
                                LGATTAttributeValue &attrValue)
{
    APP_LOG("[LGATT]LGATTClient::readCharacteristic - Start");
    

    this->_cntx._currServiceUUID = serviceUUID;
    this->_cntx._isPrimary = isPrimary;
    this->_cntx._currCharUUID = characteristicUUID;
    
	_LTaskClass::remoteCall(gattReadCharacteristic, this);

	if (_return_value)
	{
	    memcpy(&attrValue, &(this->cb_data.read_characteristic.value), sizeof(LGATTAttributeValue));
	}

    APP_LOG("[LGATT]LGATTClient::readCharacteristic - ret[%d] End", _return_value);

    //memcpy(&read_characteristic, &cb_data.read_characteristic, sizeof(lgatt_read_characteristic_struct));
	return _return_value;
}

boolean LGATTClient::writeCharacteristic(const LGATTUUID &serviceUUID,
                                boolean isPrimary, 
                                const LGATTUUID& characteristicUUID,
                                const LGATTAttributeValue &attrValue)
{
    APP_LOG("[LGATT]LGATTClient::writeCharacteristic - Start");
    

    this->_cntx._currServiceUUID = serviceUUID;
    this->_cntx._isPrimary = isPrimary;
    this->_cntx._currCharUUID = characteristicUUID;
    memcpy(&(this->_cntx._currAttrValue), &attrValue, sizeof(LGATTAttributeValue));
    
	_LTaskClass::remoteCall(gattWriteCharacteristic, this);

    APP_LOG("[LGATT]LGATTClient::writeCharacteristic - ret[%d] End", _return_value);

    //memcpy(&read_characteristic, &cb_data.read_characteristic, sizeof(lgatt_read_characteristic_struct));
	return _return_value;

}

boolean LGATTClient::readDescriptor(const LGATTUUID &serviceUUID,
                                boolean isPrimary, 
                                const LGATTUUID& characteristicUUID,
                                const LGATTUUID& descriptorUUID,
                                LGATTAttributeValue &attrValue)
{
    APP_LOG("[LGATT]LGATTClient::readDescriptor - Start");
    

    this->_cntx._currServiceUUID = serviceUUID;
    this->_cntx._isPrimary = isPrimary;
    this->_cntx._currCharUUID = characteristicUUID;
    this->_cntx._currDescUUID = descriptorUUID;
    
	_LTaskClass::remoteCall(gattReadDescriptor, this);

	if (_return_value)
	{
	    memcpy(&attrValue, &(this->cb_data.read_descriptor.value), sizeof(LGATTAttributeValue));
	}

    APP_LOG("[LGATT]LGATTClient::readDescriptor - ret[%d] End", _return_value);

    //memcpy(&read_characteristic, &cb_data.read_characteristic, sizeof(lgatt_read_characteristic_struct));
	return _return_value;
}

boolean LGATTClient::writeDescriptor(const LGATTUUID &serviceUUID,
                                boolean isPrimary, 
                                const LGATTUUID& characteristicUUID,
                                const LGATTUUID& descriptorUUID,
                                const LGATTAttributeValue &attrValue)
{
    APP_LOG("[LGATT]LGATTClient::writeDescriptor - Start");
    

    this->_cntx._currServiceUUID = serviceUUID;
    this->_cntx._isPrimary = isPrimary;
    this->_cntx._currCharUUID = characteristicUUID;
    this->_cntx._currDescUUID = descriptorUUID;
    memcpy(&(this->_cntx._currAttrValue), &attrValue, sizeof(LGATTAttributeValue));
    
	_LTaskClass::remoteCall(gattWriteDescriptor, this);

    APP_LOG("[LGATT]LGATTClient::writeDescriptor - ret[%d] End", _return_value);

	return _return_value;
}

boolean LGATTClient::readRemoteRSSI(const LGATTAddress &address, int32_t &rssi)
{
    APP_LOG("[LGATT]LGATTClient::readRemoteRSSI - Start");

    memcpy(&(this->_cntx._address), &address, sizeof(LGATTAddress)); 
    
	_LTaskClass::remoteCall(gattReadRemoteRSSI, this);

	rssi = this->cb_data.read_remote_rssi.rssi;

    APP_LOG("[LGATT]LGATTClient::readRemoteRSSI - end[%d]", rssi);

	return _return_value;
}

boolean LGATTClient::end()
{

    disconnect(this->_cntx._address);

	_LTaskClass::remoteCall(gattEnd, this);
	_cntx.state = LGATTC_STATUS_DISABLED;

	return _return_value;
}