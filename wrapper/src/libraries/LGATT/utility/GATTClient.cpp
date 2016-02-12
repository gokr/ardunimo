#include "vmbtcm.h"
#include "vmbtgatt.h"
#include "GATTClient.h"
#include "LGATTClient.h"
#include "LTask.h"
#include "vmlog.h"
#include "vmtimer.h"

//#ifdef APP_LOG
//#undef APP_LOG
//#define APP_LOG Serial.printf
//#endif

typedef enum {
	GATT_CLIENT_STATUS_DISABLED = 0,
	GATT_CLIENT_STATUS_ENABLING,
	GATT_CLIENT_STATUS_ENABLED,
	GATT_CLIENT_STATUS_DISABLING,
}GATT_CLIENT_STATUS;

static vm_gattc_callback_struct gatt_client_cb;

typedef enum {
	GATT_CLIENT_STATUS_DISCONNECTED = 0,
	GATT_CLIENT_STATUS_CONNECTING,
	GATT_CLIENT_STATUS_CONNECTED,
	GATT_CLIENT_STATUS_DISCONNECTING,
}GATT_CLIENT_CONNECTION_STATUS;

typedef struct {
	void                 *conn_ctx;
	GATT_CLIENT_CONNECTION_STATUS                   conn_status;
	VMCHAR                  bdaddr[VM_BD_ADDR_SIZE];
}GattClientConnCntx;

LGATTDeviceInfo GATT_CLIENT_BD_ADDR_LIST[MAX_BLE_SERCHED_DEV];

GattClientConnCntx *gatt_conn_cntx = NULL;

VMUINT8 gatt_srv_uuid[] = {
	0xFB, 0x34, 0x9B, 0x5F, 0x80, 0x00, 0x00, 0X80,
	0x00, 0x10, 0x00, 0x00, 0x08, 0x18, 0x00, 0x10
};

VMUINT8 gatt_client_uuid[] = {
	0xFA, 0x34, 0x9B, 0x5F, 0x80, 0x00, 0x00, 0X80,
	0x00, 0x10, 0x00, 0x00, 0x08, 0x18, 0x00, 0x10
};

VMUINT8 gatt_char_uuid[] = {
    0xFC, 0x34, 0x9B, 0x5F, 0x80, 0x00, 0x00, 0X80,
    0x00, 0x10, 0x00, 0x00, 0x09, 0x2A, 0x00, 0x10
};

VM_ATT_VALUE		 gatt_char_value;
VM_ATT_VALUE		 gatt_desc_value;


LGATTClient* gatt_client[MAX_GATT_CLIENT] = {0};

/*
LGATTClient* GATTCGetClientByUUID(vm_bt_uuid_struct *app_uuid)
{
    
    for (int i = 0; (i < MAX_GATT_CLIENT && gatt_client[i]); i++)
    {
        if (0 == memcmp(MAX_GATT_CLIENT[i]->bt_uuid.uu, 
            app_uuid->uu, 
            sizeof(SRV_CTX(LGATTServer._gatts_service[i])->bt_uuid.uu)))
        {
            return LGATTServer._gatts_service[i];
        }
    }
    
	return NULL;
}
*/



boolean GATTCSetClient(LGATTClient *client)
{
    int i = 0;
    APP_LOG("[LGATT]GATTCSetClient s");
    if (!client)
    {
        APP_LOG("[LGATT]GATTCSetClient e1");
        return false;
    }
    
    for (i = 0; (i < MAX_GATT_CLIENT && gatt_client[i]); i++)
    {
        APP_LOG("[LGATT]GATTCSetClient index[%d]", i);
    }

    if (i < MAX_GATT_CLIENT)
    {
        gatt_client[i] = client;
        APP_LOG("[LGATT]GATTCSetClient [0x%x] e", client);
        return true;
    }

    APP_LOG("[LGATT]GATTCSetClient e2");
    return false;
}

LGATTClient* GATTCGetClient(void *reg_ctx)
{
    for (int i = 0; (i < MAX_GATT_CLIENT && gatt_client[i]); i++)
    {
        if (reg_ctx == gatt_client[i]->_cntx.reg_ctx)
        {
            return gatt_client[i];
        }
    }

	return NULL;
}

LGATTClient* GATTCGetClientByTID(int32_t tid)
{
    for (int i = 0; (i < MAX_GATT_CLIENT && gatt_client[i]); i++)
    {
        if (tid == gatt_client[i]->_cntx._tid)
        {
            return gatt_client[i];
        }
    }
    
    return NULL;
}

LGATTClient* GATTCGetClientByUUID(vm_bt_uuid_struct *app_uuid)
{
    for (int i = 0; (i < MAX_GATT_CLIENT && gatt_client[i]); i++)
    {
        if (0 == memcmp(gatt_client[i]->_cntx.uuid.uu, 
            app_uuid->uu,
            sizeof(gatt_client[i]->_cntx.uuid.uu)))
        {
            return gatt_client[i];
        }
    }
    
    return NULL;
}


void GATTCDelClient(LGATTClient *client)
{
    for (int i = 0; (i < MAX_GATT_CLIENT && gatt_client[i]); i++)
    {
        if (client == gatt_client[i])
        {
            gatt_client[i] = NULL;
        }
    }
}

char dtoc(unsigned char harfByte)
{
    static char ref[] = "0123456789ABCDEF";
    unsigned char len = (unsigned char)strlen(ref);
    for (unsigned char i = 0; i < len; i++)
    {
        if (harfByte == i)
        {
            return ref[i];
        }
    }
    return 0;
}

const char *logGATTUUID(const LGATTUUID& uuid)
{
    const VM_BT_UUID *intUUID = &uuid;
    int len = intUUID->len;
    size_t n = 0;
    static char szBuf[40] = {0};
    memset(szBuf, 0, sizeof(szBuf));
    int j = 0;
    for (int i = len-1; i >= 0; i--)
    {
        if (intUUID->uuid[i] <= 0xf)
        {
            szBuf[j++] = '0';
            szBuf[j++] = dtoc(intUUID->uuid[i] & 0x0f);
        }
        else
        {
            szBuf[j++] = dtoc((intUUID->uuid[i] >> 4) & 0x0f);
            szBuf[j++] = dtoc(intUUID->uuid[i] & 0x0f);
        }
        if (12 == i || 
            10 == i || 
            8 == i ||
            6 == i)
            szBuf[j++] = '-';
    }
    return szBuf;
}

void gatt_client_register_client_callback(void *reg_ctx, VM_OS_STATUS status, vm_bt_uuid_struct *app_uuid)
{
    APP_LOG("[LGATT]gatt_client_register_client_callback - reg_ctx[0x%x] Start", reg_ctx); 

    LGATTClient *client = GATTCGetClientByUUID(app_uuid);
    if (!client)
    {
        APP_LOG("[LGATT] FATAL 3");
        return;
    }
    client->_cntx.reg_ctx = reg_ctx;
    client->cb_data.conn.reg_ctx = reg_ctx;
    client->_return_value = true;
    
	if(memcmp(app_uuid, &client->_cntx.uuid, sizeof(vm_bt_uuid_struct)) == 0)
	{
	    APP_LOG("[LGATT]gatt_client_register_client_callback - Check uuid pass"); 
		if(client->_cntx.state == (lgatt_client_status)GATT_CLIENT_STATUS_ENABLING)
		{	
		    APP_LOG("[LGATT]gatt_client_register_client_callback - 3"); 
			if(status == VM_OS_STATUS_SUCCESS)
			{
			    APP_LOG("[LGATT]gatt_client_register_client_callback - 4"); 
				client->_cntx.reg_ctx = reg_ctx;
                client->cb_data.conn.reg_ctx = reg_ctx;
				client->_cntx.state = (lgatt_client_status)GATT_CLIENT_STATUS_ENABLED;
				//vm_gattc_listen(reg_ctx, VM_TRUE);
				client->_return_value = true;
			}
			else
			{
			    APP_LOG("[LGATT]gatt_client_register_client_callback - 5"); 
			    client->_cntx.reg_ctx = NULL;
                client->cb_data.conn.reg_ctx = NULL;
				client->_cntx.state = (lgatt_client_status)GATT_CLIENT_STATUS_DISABLED;
				client->_return_value = false;
			}
		}
		else if(client->_cntx.state == (lgatt_client_status)GATT_CLIENT_STATUS_DISABLING)
		{	
		    APP_LOG("[LGATT]gatt_client_register_client_callback - 6"); 
			if(status == VM_OS_STATUS_SUCCESS)
			{
			    APP_LOG("[LGATT]gatt_client_register_client_callback - 7"); 
				client->_cntx.reg_ctx = NULL;
                client->cb_data.conn.reg_ctx = NULL;
				client->_cntx.state = (lgatt_client_status)GATT_CLIENT_STATUS_DISABLED;
				client->_return_value = true;
				GATTCDelClient(client);
			}
			else
			{
			    APP_LOG("[LGATT]gatt_client_register_client_callback - 8"); 
				client->_cntx.state = (lgatt_client_status)GATT_CLIENT_STATUS_ENABLED;
				client->_return_value = false;
			}
		}
	}
	APP_LOG("[LGATT]gatt_client_register_client_callback - 9"); 
    
	//*(gatt_client->cb_data.register_client.status) = (lgatt_os_status)status;
	//memcpy(&gatt_client->cb_data.register_client.app_uuid, &app_uuid, sizeof(vm_bt_uuid_struct));
	
	APP_LOG("[LGATT]gatt_client_register_client_callback - MAX_BLE_SERCHED_DEV, gatt_client->_return_value = %d", client->_return_value); 
	client->post_signal();
}

static VMUINT32 gatt_client_get_free_index(void)
{
    VMUINT32 idx;

    for (idx = 0; idx < MAX_BLE_SERCHED_DEV; idx++)
    {
        if (GATT_CLIENT_BD_ADDR_LIST[idx].bd_addr.addr[0] == 0
         && GATT_CLIENT_BD_ADDR_LIST[idx].bd_addr.addr[1] == 0
         && GATT_CLIENT_BD_ADDR_LIST[idx].bd_addr.addr[2] == 0
         && GATT_CLIENT_BD_ADDR_LIST[idx].bd_addr.addr[3] == 0
         && GATT_CLIENT_BD_ADDR_LIST[idx].bd_addr.addr[4] == 0
         && GATT_CLIENT_BD_ADDR_LIST[idx].bd_addr.addr[5] == 0)
        {
            return idx;
        }
    }
    return MAX_BLE_SERCHED_DEV;
}


void gatt_client_vmt_scan_result_callback(void *reg_ctx, VM_BD_ADDR *bd_addr, VMINT32 rssi, 
                                                        VMUINT8 eir_len, VMUINT8 *eir)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    VMUINT32 idx;
	VMUINT32 i;
	VMUINT8 server_addr[VM_BD_ADDR_SIZE] = {0xC9,0x92,0x65,0x46,0x5B,0x7E};
    
    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
	APP_LOG("[LGATT] gatt_client_vmt_scan_result_callback - Start,  bd_addr %x:%x:%x:%x:%x:%x!\n", 
	    bd_addr->addr[0],bd_addr->addr[1],bd_addr->addr[2],
	    bd_addr->addr[3],bd_addr->addr[4],bd_addr->addr[5]);
	    
    LGATTClient *client = GATTCGetClient(reg_ctx);
    if (!client)
    {
        APP_LOG("[LGATT] FATAL 3");
        return;
    }    
	if(client->_cntx.reg_ctx == reg_ctx)
	{
	    
	    idx = gatt_client_get_free_index();

        if (idx >= MAX_BLE_SERCHED_DEV)
        {
            idx = MAX_BLE_SERCHED_DEV;
        }

	    for (i = 0; i < idx; i++)
        {
            if (GATT_CLIENT_BD_ADDR_LIST[i].bd_addr.addr[0] == bd_addr->addr[0]
                 && GATT_CLIENT_BD_ADDR_LIST[i].bd_addr.addr[1] == bd_addr->addr[1]
                 && GATT_CLIENT_BD_ADDR_LIST[i].bd_addr.addr[2] == bd_addr->addr[2]
                 && GATT_CLIENT_BD_ADDR_LIST[i].bd_addr.addr[3] == bd_addr->addr[3]
                 && GATT_CLIENT_BD_ADDR_LIST[i].bd_addr.addr[4] == bd_addr->addr[4]
                 && GATT_CLIENT_BD_ADDR_LIST[i].bd_addr.addr[5] == bd_addr->addr[5])
            {
                APP_LOG("[LGATT] gatt_client_vmt_scan_result_callback - address already saved, idx = %d.", i);
                GATT_CLIENT_BD_ADDR_LIST[i].rssi = rssi;
                //GATT_CLIENT_BD_ADDR_LIST[i].eir = eir;
                memcpy(GATT_CLIENT_BD_ADDR_LIST[i].eir, eir, eir_len);
                GATT_CLIENT_BD_ADDR_LIST[i].eir_len = eir_len;
                //gatt_client->post_signal();
                return;
            }
        }
        
	    if (idx < MAX_BLE_SERCHED_DEV)
	    {
                client->_cntx._searched_ble_dev_nums++;
	        memcpy(&(GATT_CLIENT_BD_ADDR_LIST[idx].bd_addr), bd_addr, sizeof(VM_BD_ADDR));
            GATT_CLIENT_BD_ADDR_LIST[idx].rssi = rssi;
            //GATT_CLIENT_BD_ADDR_LIST[idx].eir = eir;
            memcpy(GATT_CLIENT_BD_ADDR_LIST[idx].eir, eir, eir_len);
            GATT_CLIENT_BD_ADDR_LIST[idx].eir_len = eir_len;
		
			
			APP_LOG("[LGATT] gatt_client_vmt_scan_result_callback, copy to scan_result[%d] = %x:%x:%x:%x:%x:%x\n",
                idx,
			    GATT_CLIENT_BD_ADDR_LIST[idx].bd_addr.addr[0],
			    GATT_CLIENT_BD_ADDR_LIST[idx].bd_addr.addr[1],
	            GATT_CLIENT_BD_ADDR_LIST[idx].bd_addr.addr[2],
	            GATT_CLIENT_BD_ADDR_LIST[idx].bd_addr.addr[3],
	            GATT_CLIENT_BD_ADDR_LIST[idx].bd_addr.addr[4],
	            GATT_CLIENT_BD_ADDR_LIST[idx].bd_addr.addr[5]);
	    }
	}
	//gatt_client->post_signal();
}


void gatt_client_clean();
void gatt_client_connection_callback(vm_gatt_conn_struct *conn, VMBOOL connected, VM_BD_ADDR *bd_addr)
{
	APP_LOG("[LGATT] gatt_client_connection_callback - Start, connected = %d, reg_ctx[0x%x] conn_ctx[0x%x]", 
	    connected, conn->reg_ctx, conn->conn_ctx);

    LGATTClient *client;
    if (!conn || !bd_addr)
    {
        APP_LOG("[LGATT] XXX - check conn->, reg_ctx = %x, conn_ctx = %x ", conn->reg_ctx, conn->conn_ctx);
        return;
    }

    client = GATTCGetClient(conn->reg_ctx);
    if (!client)
    {
        APP_LOG("[LGATT] FATAL 3");
    }
    //APP_LOG("[LGATT] XXX - check conn->, reg_ctx = %x, conn_ctx = %x ", conn->reg_ctx, conn->conn_ctx);


    APP_LOG("[LGATT] gatt_client_connection_callback - check bt_addr, bd_addr = [%02x:%02x:%02x:%02x:%02x:%02x]\n", 
        bd_addr->addr[5],bd_addr->addr[4],
        bd_addr->addr[3],bd_addr->addr[2],bd_addr->addr[1],bd_addr->addr[0]);




    APP_LOG("[LGATT] gatt_client_connection_callback - connected result = %d", connected);
	if(connected)
	{
		//do next step Discovery all services
		APP_LOG("[LGATT] gatt_client_connection_callback - success to connect, start to search service..");
		vm_gattc_search_service(conn, NULL);
		
        memcpy(&client->cb_data.connection.bd_addr, bd_addr, VM_BD_ADDR_SIZE);
        //memcpy(&client->cb_data.conn, conn, sizeof(vm_gatt_conn_struct));
        client->_return_value = true;
	}
	else
	{
		APP_LOG("[LGATT] gatt_client_connection_callback - Disconnect.");
		client->_return_value = false;
        //gatt_client_clean();
        client->post_signal();		
	}
    
    
    client->_cntx.conn_ctx = conn->conn_ctx;
    client->cb_data.conn.conn_ctx = conn->conn_ctx;
    client->cb_data.connection.connected = connected;

    
    APP_LOG("[LGATT] gatt_client_connection_callback - End");
    return;
		
}


void gatt_client_listen_callback(void *reg_ctx, VM_OS_STATUS status)
{/*
	APP_LOG("[LGATT] app_client_listen_callback status %d\n", status);
	if ((gatt_client->_cntx.reg_ctx == reg_ctx) && (NULL != reg_ctx))
	{
		if(status == VM_OS_STATUS_SUCCESS)
		{
			APP_LOG("[LGATT] app_client_listen_callback statusok %d!\n", status);
			vm_gattc_scan(reg_ctx, VM_TRUE);
		}
	}
*/}


void gatt_client_set_adv_data_callback(void *reg_ctx, VM_OS_STATUS status)
{
}


void gatt_client_search_complete_callback(vm_gatt_conn_struct *reg_ctx, VM_OS_STATUS status)
{
    APP_LOG("[LGATT] gatt_client_search_complete_callback [0x%x] status[%d]", reg_ctx, status);
    vm_gatt_conn_struct *conn = (vm_gatt_conn_struct*)reg_ctx;
    LGATTClient *client = GATTCGetClient(conn->reg_ctx);
    if (!client)
    {
        APP_LOG("[LGATT] FATAL 3");
        return;
    }
    client->cb_data.search_complete.status = (lgatt_os_status)status;
	if(client->_cntx.reg_ctx == reg_ctx)
	{
		if(status == VM_OS_STATUS_SUCCESS)
		{
            client->_return_value = true;
		}
		else
		{
		    client->_return_value = false;
		}
	}
    client->post_signal();
	
    APP_LOG("[LGATT] gatt_client_search_complete_callback reg_ctx[0x%x] conn_ctx[0x%x] END", conn->reg_ctx, conn->conn_ctx);
}


void gatt_client_search_result_callback(vm_gatt_conn_struct *conn, VM_GATT_SVC_UUID *uuid)
{
	APP_LOG("[LGATT] gatt_client_search_result_callback - Start conn[0x%x] reg_ctx[0x%x] conn_ctx[0x%x] uuid[0x%x]", 
	    conn, conn->reg_ctx, conn->conn_ctx, uuid);
	LGATTClient *client = GATTCGetClient(conn->reg_ctx);
    if (!client)
    {
        APP_LOG("[LGATT] FATAL 3");
        return;
    }

/*
    if(gatt_conn_cntx->conn_ctx != conn->conn_ctx)
    {
        APP_LOG("[LGATT] gatt_client_search_result_callback [ERROR], conn_ctx = %x , %x ", gatt_conn_cntx->conn_ctx, conn->conn_ctx);
    }
*/
    if (uuid && (client->cb_data.search_result.service_uuid_num < MAX_BLE_SERVICES))
    {

        APP_LOG("[LGATT]gatt_client_search_result_callback - svc_uuid = [0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x]",
            uuid->uuid.uuid.uuid[15],
            uuid->uuid.uuid.uuid[14],
            uuid->uuid.uuid.uuid[13],
            uuid->uuid.uuid.uuid[12],
            uuid->uuid.uuid.uuid[11],
            uuid->uuid.uuid.uuid[10],
            uuid->uuid.uuid.uuid[9],
            uuid->uuid.uuid.uuid[8],
            uuid->uuid.uuid.uuid[7],
            uuid->uuid.uuid.uuid[6],
            uuid->uuid.uuid.uuid[5],
            uuid->uuid.uuid.uuid[4],
            uuid->uuid.uuid.uuid[3],
            uuid->uuid.uuid.uuid[2],
            uuid->uuid.uuid.uuid[1],
            uuid->uuid.uuid.uuid[0]); 
        
	    memcpy(&client->cb_data.search_result.uuid[client->cb_data.search_result.service_uuid_num++], 
	        (void*)uuid, sizeof(VM_GATT_SVC_UUID));

        
        
    }
/*
    //TODO: 
    if (gatt_client->search_uuid_index == 1)
    {
        *(gatt_client->cb_data.connection.connected) = true;
        gatt_client->post_signal();
    }
    */
    APP_LOG("[LGATT] gatt_client_search_result_callback - End ");
	return;
}


void gatt_client_get_characteristic_callback(vm_gatt_conn_struct *conn, VM_OS_STATUS status, vm_gattc_char_struct *ch, VM_GATT_CHAR_PROPERTIES properties)
{
	APP_LOG("[LGATT] gatt_client_get_characteristic_callback - status = %d ch uuid[0x%x]", status, ch->ch_uuid);
    LGATTClient *client = GATTCGetClient(conn->reg_ctx);
    if (!client)
    {
        APP_LOG("[LGATT] FATAL 3");
        return;
    }
    
    if (status == VM_OS_STATUS_SUCCESS)
	{
	    client->_return_value = true;
	    memcpy(&(client->cb_data.characteristic.start_char_uuid), ch->ch_uuid, sizeof(lgatt_att_uuid));
	    memcpy(&(client->cb_data.characteristic.ch.svc_uuid), ch->svc_uuid, sizeof(lgatt_svc_uuid));
	    memcpy(&(client->cb_data.characteristic.ch.ch_uuid), ch->ch_uuid, sizeof(lgatt_att_uuid));
        client->cb_data.characteristic.properties = properties;

        LGATTUUID svcUUID = *((VM_BT_UUID*)&(client->cb_data.characteristic.ch.svc_uuid.uuid));
        LGATTUUID startCharUUID = *((VM_BT_UUID*)&(client->cb_data.characteristic.start_char_uuid.uuid));
        LGATTUUID charUUID = *((VM_BT_UUID*)&(client->cb_data.characteristic.ch.ch_uuid.uuid));

        APP_LOG("Service UUID : [%s]", logGATTUUID(svcUUID));
        APP_LOG("START Char UUID : [%s]", logGATTUUID(startCharUUID));
        APP_LOG("Char UUID : [%s]", logGATTUUID(charUUID));
        APP_LOG("properties [0x%x]", client->cb_data.characteristic.properties);
        APP_LOG("reg_ctx[0x%x], conn_ctx[0x%x]", conn->reg_ctx, conn->conn_ctx);
	}
	else
	{
        memset(&(client->cb_data.characteristic), 0, sizeof(client->cb_data.characteristic));
	    client->_return_value = false;
	}
/*
    APP_LOG("[LGATT] gatt_client_get_characteristic_callback - ch = %x", ch);
    APP_LOG("[LGATT] XXX - ch->svc_uuid = %x", ch->svc_uuid);
    APP_LOG("[LGATT] XXX - ch->ch_uuid = %x", ch->ch_uuid);
    
    APP_LOG("[LGATT] svc [0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x]",
        ch->svc_uuid->uuid.uuid.uuid[15],
        ch->svc_uuid->uuid.uuid.uuid[14],
        ch->svc_uuid->uuid.uuid.uuid[13],
        ch->svc_uuid->uuid.uuid.uuid[12],
        ch->svc_uuid->uuid.uuid.uuid[11],
        ch->svc_uuid->uuid.uuid.uuid[10],
        ch->svc_uuid->uuid.uuid.uuid[9],
        ch->svc_uuid->uuid.uuid.uuid[8],
        ch->svc_uuid->uuid.uuid.uuid[7],
        ch->svc_uuid->uuid.uuid.uuid[6],
        ch->svc_uuid->uuid.uuid.uuid[5],
        ch->svc_uuid->uuid.uuid.uuid[4],
        ch->svc_uuid->uuid.uuid.uuid[3],
        ch->svc_uuid->uuid.uuid.uuid[2],
        ch->svc_uuid->uuid.uuid.uuid[1],
        ch->svc_uuid->uuid.uuid.uuid[0]); 
    
    APP_LOG("[LGATT]char [0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x]",
        ch->ch_uuid->uuid.uuid[15],
        ch->ch_uuid->uuid.uuid[14],
        ch->ch_uuid->uuid.uuid[13],
        ch->ch_uuid->uuid.uuid[12],
        ch->ch_uuid->uuid.uuid[11],
        ch->ch_uuid->uuid.uuid[10],
        ch->ch_uuid->uuid.uuid[9],
        ch->ch_uuid->uuid.uuid[8],
        ch->ch_uuid->uuid.uuid[7],
        ch->ch_uuid->uuid.uuid[6],
        ch->ch_uuid->uuid.uuid[5],
        ch->ch_uuid->uuid.uuid[4],
        ch->ch_uuid->uuid.uuid[3],
        ch->ch_uuid->uuid.uuid[2],
        ch->ch_uuid->uuid.uuid[1],
        ch->ch_uuid->uuid.uuid[0]); 
        */
	client->cb_data.characteristic.status = (lgatt_os_status)status;
    //memcpy(&(client->cb_data.characteristic.ch.svc_uuid), ch->svc_uuid, sizeof(lgatt_svc_uuid));
	//memcpy(&(client->cb_data.characteristic.ch.ch_uuid), ch->ch_uuid, sizeof(lgatt_att_uuid));
	//client->cb_data.characteristic.ch = (lgatt_char_struct*)ch;

    
	client->post_signal();
    APP_LOG("[LGATT] gatt_client_get_characteristic_callback - End");
	return ;
}


void gatt_client_get_descriptor_callback(vm_gatt_conn_struct *conn, VM_OS_STATUS status, vm_gattc_descr_struct *descr)
{
	APP_LOG("[LGATT] gatt_client_get_descriptor_callback - status = %d descr uuid[0x%x]", status, descr->ch_uuid);
    LGATTClient *client = GATTCGetClient(conn->reg_ctx);
    if (!client)
    {
        APP_LOG("[LGATT] FATAL 3");
        return;
    }


    client->cb_data.descriptor.status = (lgatt_os_status)status;
    
    if (status == VM_OS_STATUS_SUCCESS)
	{
	    client->_return_value = true;
	    memcpy(&(client->cb_data.descriptor.start_descr_uuid), descr->descr_uuid, sizeof(lgatt_att_uuid));
	    memcpy(&(client->cb_data.descriptor.descr.svc_uuid), descr->svc_uuid, sizeof(lgatt_svc_uuid));
	    memcpy(&(client->cb_data.descriptor.descr.ch_uuid), descr->ch_uuid, sizeof(lgatt_att_uuid));
	    memcpy(&(client->cb_data.descriptor.descr.descr_uuid), descr->descr_uuid, sizeof(lgatt_att_uuid));
	    APP_LOG("[LGATT] gatt_client_get_descriptor_callback - descr = %x", descr);
        APP_LOG("[LGATT] XXX - descr->svc_uuid = %x", descr->svc_uuid);
        APP_LOG("[LGATT] XXX - descr->ch_uuid = %x", descr->ch_uuid);
        
        APP_LOG("[LGATT] svc [0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x]",
            descr->svc_uuid->uuid.uuid.uuid[15],
            descr->svc_uuid->uuid.uuid.uuid[14],
            descr->svc_uuid->uuid.uuid.uuid[13],
            descr->svc_uuid->uuid.uuid.uuid[12],
            descr->svc_uuid->uuid.uuid.uuid[11],
            descr->svc_uuid->uuid.uuid.uuid[10],
            descr->svc_uuid->uuid.uuid.uuid[9],
            descr->svc_uuid->uuid.uuid.uuid[8],
            descr->svc_uuid->uuid.uuid.uuid[7],
            descr->svc_uuid->uuid.uuid.uuid[6],
            descr->svc_uuid->uuid.uuid.uuid[5],
            descr->svc_uuid->uuid.uuid.uuid[4],
            descr->svc_uuid->uuid.uuid.uuid[3],
            descr->svc_uuid->uuid.uuid.uuid[2],
            descr->svc_uuid->uuid.uuid.uuid[1],
            descr->svc_uuid->uuid.uuid.uuid[0]); 
        
        APP_LOG("[LGATT]char [0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x]",
            descr->ch_uuid->uuid.uuid[15],
            descr->ch_uuid->uuid.uuid[14],
            descr->ch_uuid->uuid.uuid[13],
            descr->ch_uuid->uuid.uuid[12],
            descr->ch_uuid->uuid.uuid[11],
            descr->ch_uuid->uuid.uuid[10],
            descr->ch_uuid->uuid.uuid[9],
            descr->ch_uuid->uuid.uuid[8],
            descr->ch_uuid->uuid.uuid[7],
            descr->ch_uuid->uuid.uuid[6],
            descr->ch_uuid->uuid.uuid[5],
            descr->ch_uuid->uuid.uuid[4],
            descr->ch_uuid->uuid.uuid[3],
            descr->ch_uuid->uuid.uuid[2],
            descr->ch_uuid->uuid.uuid[1],
            descr->ch_uuid->uuid.uuid[0]); 
            
        APP_LOG("[LGATT]descr [0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x]",
            descr->descr_uuid->uuid.uuid[15],
            descr->descr_uuid->uuid.uuid[14],
            descr->descr_uuid->uuid.uuid[13],
            descr->descr_uuid->uuid.uuid[12],
            descr->descr_uuid->uuid.uuid[11],
            descr->descr_uuid->uuid.uuid[10],
            descr->descr_uuid->uuid.uuid[9],
            descr->descr_uuid->uuid.uuid[8],
            descr->descr_uuid->uuid.uuid[7],
            descr->descr_uuid->uuid.uuid[6],
            descr->descr_uuid->uuid.uuid[5],
            descr->descr_uuid->uuid.uuid[4],
            descr->descr_uuid->uuid.uuid[3],
            descr->descr_uuid->uuid.uuid[2],
            descr->descr_uuid->uuid.uuid[1],
            descr->descr_uuid->uuid.uuid[0]); 
    }
	else
	{
        memset(&(client->cb_data.descriptor), 0, sizeof(client->cb_data.descriptor));
	    client->_return_value = false;
	}


            
	//client->cb_data.characteristic.status) = (lgatt_os_status)status;
    //memcpy(&(client->cb_data.characteristic.ch.svc_uuid), ch->svc_uuid, sizeof(lgatt_svc_uuid));
	//memcpy(&(client->cb_data.characteristic.ch.ch_uuid), ch->ch_uuid, sizeof(lgatt_att_uuid));
	//client->cb_data.characteristic.ch = (lgatt_char_struct*)ch;
	//client->cb_data.characteristic.properties= properties;


    
	client->post_signal();
    APP_LOG("[LGATT] gatt_client_get_descriptor_callback - End");
}



void gatt_client_get_included_service_callback(vm_gatt_conn_struct *conn, VM_OS_STATUS status, VM_GATT_SVC_UUID *svc_uuid, VM_GATT_SVC_UUID *incl_svc_uuid)
{
}


void gatt_client_register_for_notification_callback(void *reg_ctx, VM_OS_STATUS status, VM_BD_ADDR *bd_addr, vm_gattc_char_struct *ch)
{
    LGATTClient *client = GATTCGetClient(reg_ctx);
    
    APP_LOG("[LGATT] gatt_client_register_for_notification_callback start status[%d] reg_ctx[0x%x]", status, reg_ctx);
    if (!client)
    {
        APP_LOG("[LGATT] FATAL 3");
        return;
    }

    if (status == VM_OS_STATUS_SUCCESS)
    {
    /*
        if (client->_cntx._isEnableNotification)
        {
            client->_cntx._isEnableNotification = true;
        }
        else
        {
            client->_cntx._isEnableNotification = false;
        }
        */
        client->_return_value = true;
    }
    else
    {
        if (client->_cntx._isEnableNotification)
        {
            client->_cntx._isEnableNotification = false;
        }
        else
        {
            client->_cntx._isEnableNotification = true;
        }
        client->_return_value = false;
    }
    
    APP_LOG("[LGATT] gatt_client_register_for_notification_callback end");

    client->post_signal();
}


void gatt_client_notify_callback(vm_gatt_conn_struct *conn, VM_BD_ADDR *bd_addr, vm_gattc_char_struct *ch, VM_ATT_VALUE *value, VMBOOL is_notify)
{
    LGATTClient *client = GATTCGetClient(conn->reg_ctx);
    
    APP_LOG("[LGATT] gatt_client_notify_callback is_notify[%d]", is_notify, conn->reg_ctx, conn->conn_ctx);
    if (!client)
    {
        APP_LOG("[LGATT] FATAL 3");
        return;
    }

    if (!ch)
    {
        APP_LOG("gatt_client_notify_callback ch NULL!!!");
        return;
    }


    client->_cntx._currNotificationData._serviceUUID = ch->svc_uuid->uuid.uuid;
    client->_cntx._currNotificationData._isPrimary = ch->svc_uuid->is_primary;
    client->_cntx._currNotificationData._charUUID = ch->ch_uuid->uuid;
    memcpy(&(client->_cntx._currNotificationData._attrValue), value, sizeof(LGATTAttributeValue));

    APP_LOG("[LGATT] value[%s][%d]", client->_cntx._currNotificationData._attrValue.value, client->_cntx._currNotificationData._attrValue.len);
    APP_LOG("[LGATT] gatt_client_notify_callback - end bd_addr = [%02x:%02x:%02x:%02x:%02x:%02x]", 
        bd_addr->addr[5],bd_addr->addr[4],
        bd_addr->addr[3],bd_addr->addr[2],bd_addr->addr[1],bd_addr->addr[0]);


}


void gatt_client_read_characteristic_callback(vm_gatt_conn_struct *conn, VM_OS_STATUS status, vm_gattc_char_struct *ch, VM_ATT_VALUE *value)
{
    
    LGATTClient *client = GATTCGetClient(conn->reg_ctx);
    
    APP_LOG("[LGATT] gatt_client_read_characteristic_callback start status[%d] reg_ctx[0x%x] conn_ctx[0x%x]", status, conn->reg_ctx, conn->conn_ctx);
    if (!client)
    {
        APP_LOG("[LGATT] FATAL 3");
        return;
    }

    APP_LOG("svc_uuid[0x%x] ch_uuid[0x%x]", ch->svc_uuid, ch->ch_uuid);

    APP_LOG("len[%d] [%s]", value->len, value->value);
/*
    VMUINT16 len = value->len;
    while (len--)
    {
        APP_LOG("[%02x]", value->value[value->len - len]);
    }
    */

    client->cb_data.read_characteristic.status = (lgatt_os_status)status;

    if (status == VM_OS_STATUS_SUCCESS)
    {
        memcpy(&(client->cb_data.read_characteristic.ch.svc_uuid), ch->svc_uuid, sizeof(client->cb_data.read_characteristic.ch.svc_uuid));
        memcpy(&(client->cb_data.read_characteristic.ch.ch_uuid), ch->ch_uuid, sizeof(client->cb_data.read_characteristic.ch.ch_uuid));
        memcpy(&(client->cb_data.read_characteristic.value), value, sizeof(client->cb_data.read_characteristic.value));
        client->_return_value = true;
        
        LGATTUUID svcUUID = *((VM_BT_UUID*)&(client->cb_data.read_characteristic.ch.svc_uuid.uuid));
        LGATTUUID charUUID = *((VM_BT_UUID*)&(client->cb_data.read_characteristic.ch.ch_uuid.uuid));
        APP_LOG("Service UUID : [%s]", logGATTUUID(svcUUID));
        APP_LOG("Char UUID : [%s]", logGATTUUID(charUUID));
        APP_LOG("value[%s] len[%d]", value->value, value->len);
    }
    else
    {
        memset(&(client->cb_data.read_characteristic), 0, sizeof(client->cb_data.read_characteristic));
        client->_return_value = false;
    }

    client->post_signal();
    
    APP_LOG("[LGATT] gatt_client_read_characteristic_callback ret[%d] end", client->_return_value);
	return;
}


void gatt_client_write_characteristic_callback(vm_gatt_conn_struct *conn, VM_OS_STATUS status, vm_gattc_char_struct *ch)
{
    LGATTClient *client = GATTCGetClient(conn->reg_ctx);
	APP_LOG("[LGATT] gatt_client_write_characteristic_callback - status = %d", status);
    if (!client)
    {
        APP_LOG("[LGATT] FATAL 3");
        return;
    }

    
    LGATTUUID svcUUID = ch->svc_uuid->uuid.uuid;
    LGATTUUID charUUID = ch->ch_uuid->uuid;
    APP_LOG("Service UUID : [%s]", logGATTUUID(svcUUID));
    APP_LOG("Char UUID : [%s]", logGATTUUID(charUUID));
    APP_LOG("Service isPrimary[%d], inst[%d]", ch->svc_uuid->is_primary, ch->svc_uuid->uuid.inst);
    APP_LOG("cb_data.conn.reg_ctx[0x%x], cb_data.conn.conn_ctx[0x%x]", client->cb_data.conn.reg_ctx, client->cb_data.conn.conn_ctx);

    
    if (status == VM_OS_STATUS_SUCCESS)
	{
	    client->_return_value = true;
	}
	else
	{
	    client->_return_value = false;
	}
    
    client->post_signal();
    
	APP_LOG("[LGATT] gatt_client_write_characteristic_callback - status = %d", status);
	return;
	
}


void gatt_client_read_descriptor_callback(vm_gatt_conn_struct *conn, VM_OS_STATUS status, vm_gattc_descr_struct *descr, VM_ATT_VALUE *value)
{
    LGATTClient *client = GATTCGetClient(conn->reg_ctx);
	APP_LOG("[LGATT] gatt_client_write_characteristic_callback - status = %d", status);
    if (!client)
    {
        APP_LOG("[LGATT] FATAL 3");
        return;
    }

    
    if (status == VM_OS_STATUS_SUCCESS)
	{
        memcpy(&(client->cb_data.read_descriptor.value), value, sizeof(LGATTAttributeValue));
	    client->_return_value = true;
	}
	else
	{
	    client->_return_value = false;
	}
    
    client->post_signal();
    
	APP_LOG("[LGATT] gatt_client_write_characteristic_callback - status = %d", status);
	return;
	
}   


void gatt_client_write_descriptor_callback(vm_gatt_conn_struct *conn, VM_OS_STATUS status, vm_gattc_descr_struct *descr)
{   
    LGATTClient *client = GATTCGetClient(conn->reg_ctx);
	APP_LOG("[LGATT] gatt_client_write_descriptor_callback - status = %d", status);
    if (!client)
    {
        APP_LOG("[LGATT] FATAL 3");
        return;
    }

    
    if (status == VM_OS_STATUS_SUCCESS)
	{
	    client->_return_value = true;
	}
	else
	{
	    client->_return_value = false;
	}
    
    client->post_signal();
    
	APP_LOG("[LGATT] gatt_client_write_descriptor_callback - status = %d", status);
	return;
	
} 


void gatt_client_execute_write_callback(vm_gatt_conn_struct *conn, VM_OS_STATUS status)
{
/*
	APP_LOG("[LGATT] gatt_client_execute_write_callback - Start");

	if(gatt_conn_cntx->conn_ctx == conn->conn_ctx)
	{
		if(status == VM_OS_STATUS_SUCCESS)
		{
			APP_LOG("[LGATT] service execute write success.");
		}
	}
	return;
	*/
}


void gatt_client_read_remote_rssi_callback(void *reg_ctx, VM_OS_STATUS status, VM_BD_ADDR *bd_addr, VMINT32 rssi)
{

    LGATTClient *client = GATTCGetClient(reg_ctx);
    APP_LOG("[LGATT] gatt_client_read_remote_rssi_callback - Start, rssi = %d, status = %d", rssi, status);
    if (!client)
    {
        APP_LOG("[LGATT] FATAL 3");
        return;
    }

    client->cb_data.read_remote_rssi.rssi = rssi;
	
	memcpy(&(client->cb_data.read_remote_rssi.bd_addr), bd_addr, sizeof(VM_BD_ADDR));
	
    if (status == VM_OS_STATUS_SUCCESS)
	{
	    client->_return_value = true;
	}
	else
	{
	    client->_return_value = false;
	}
	
	client->post_signal();

    APP_LOG("[LGATT] gatt_client_read_remote_rssi_callback - End, rssi = %d, status = %d", rssi, status);
    
	return;
	
}


void gatt_client_get_device_type_callback(void *reg_ctx, VM_OS_STATUS status, VM_BD_ADDR *bd_addr, VM_GATTC_DEV_TYPE dev_type)
{
}




void gatt_client_callback_init(vm_gattc_callback_struct *gattc_cb)
{
    gattc_cb->register_client_cb = gatt_client_register_client_callback;
    gattc_cb->scan_result_cb = gatt_client_vmt_scan_result_callback ;
    gattc_cb->connection_cb = gatt_client_connection_callback;
    gattc_cb->listen_cb = gatt_client_listen_callback;
    gattc_cb->set_adv_data_cb = gatt_client_set_adv_data_callback;
    gattc_cb->search_complete_cb = gatt_client_search_complete_callback;
    gattc_cb->search_result_cb = gatt_client_search_result_callback;
    gattc_cb->get_characteristic_cb = gatt_client_get_characteristic_callback;
    gattc_cb->get_descriptor_cb = gatt_client_get_descriptor_callback;
    gattc_cb->get_included_service_cb = gatt_client_get_included_service_callback;
    gattc_cb->register_for_notification_cb = gatt_client_register_for_notification_callback;
    gattc_cb->notify_cb = gatt_client_notify_callback;
    gattc_cb->read_characteristic_cb = gatt_client_read_characteristic_callback;
    gattc_cb->write_characteristic_cb = gatt_client_write_characteristic_callback;
    gattc_cb->read_descriptor_cb = gatt_client_read_descriptor_callback;
    gattc_cb->write_descriptor_cb = gatt_client_write_descriptor_callback;
    gattc_cb->execute_write_cb = gatt_client_execute_write_callback;
    gattc_cb->read_remote_rssi_cb = gatt_client_read_remote_rssi_callback;
    gattc_cb->get_device_type_cb = gatt_client_get_device_type_callback;
	return;
}


void gatt_client_init(void *user_data)
{
    APP_LOG("[LGATT]gatt_client_init - Start"); 
    LGATTClient *client = (LGATTClient *)user_data;
    if (!client)
    {
        APP_LOG("[LGATT] FATAL 3");
        return;
    }
    if (!GATTCSetClient(client))
        return;
	if(client->_cntx.state == (lgatt_client_status)GATT_CLIENT_STATUS_DISABLED)
	{
	    APP_LOG("[LGATT]gatt_client_init - register gattc.."); 
		client->_cntx.state = (lgatt_client_status)GATT_CLIENT_STATUS_ENABLING;
		gatt_client_callback_init(&gatt_client_cb);

        //memcpy(&gatt_client->_cntx.uuid, gatt_client->cb_data.register_client.app_uuid, sizeof(lgatt_uuid_struct));

        APP_LOG("[LGATT]gatt_client_init - app_uuid = %x,%x,%x,%x,%x,%x...", 
            client->_cntx.uuid.uu[0], client->_cntx.uuid.uu[1], client->_cntx.uuid.uu[2],
            client->_cntx.uuid.uu[3], client->_cntx.uuid.uu[4], client->_cntx.uuid.uu[5]); 
        
		vm_gattc_register((vm_bt_uuid_struct *)&client->_cntx.uuid, (vm_gattc_callback_struct*)&gatt_client_cb);
	}

	APP_LOG("[LGATT]gatt_client_init - End"); 
	return;
}

void gatt_client_clean()
{
    APP_LOG("[LGATT] gatt_client_clean.");
    memset(&gatt_client, 0, sizeof(gatt_client));
}

boolean gatt_client_deinit(void *userData)
{
    APP_LOG("[LGATT]gatt_client_deinit - Start"); 
    LGATTClient *client = (LGATTClient *)userData;
    if (!client)
    {
        APP_LOG("[LGATT] FATAL 3");
        return false;
    }

    
    APP_LOG("[LGATT]gatt_client_deinit - reg_ctx[0x%x]", client->_cntx.reg_ctx); 
    client->_cntx.state = (lgatt_client_status)GATT_CLIENT_STATUS_DISABLING;
    if (0 > vm_gattc_deregister(client->_cntx.reg_ctx))
    {
        return false;
    }
    // TODO:
    else
    {
        client->_cntx.reg_ctx = NULL;
        client->cb_data.conn.reg_ctx = NULL;
        client->_cntx.state = (lgatt_client_status)GATT_CLIENT_STATUS_DISABLED;
        client->_return_value = true;
        GATTCDelClient(client);
        client->post_signal();
    }
    //vm_btcm_switch_off();

    APP_LOG("[LGATT]gatt_client_deinit - End"); 
    return true;
}

void gatt_client_bt_init_cb(VMUINT evt,void * param,void * user_data)
{
    APP_LOG("[LGATT]gatt_client_bt_init_cb - Start"); 
    if (VM_SRV_BT_CM_EVENT_ACTIVATE == evt )
    {
        APP_LOG("[LGATT]gatt_client_bt_init_cb - Success to power on BT."); 
		gatt_client_init(user_data);
	}

    if (evt == 0x00080000)
    {
        APP_LOG("[LGATT]gatt_client_bt_init_cb - 0x00080000."); 
    }
	APP_LOG("[LGATT]gatt_client_bt_init_cb - End"); 
}

static VMINT g_scan_tid = -1;
static void gatt_client_timeout_cb(VMINT tid)
{
    LGATTClient * client = GATTCGetClientByTID(tid);
    if (!client)
    {
        APP_LOG("[LGATT] FATAL 3");
        return;
    }
    APP_LOG("[LGATT]gatt_client_timeout_cb - stop scan"); 
	vm_gattc_scan(client->_cntx.reg_ctx,VM_FALSE);
	vm_delete_timer(tid);
	client->_cntx._tid = -1;
    client->post_signal();

}

boolean gattBegin(void *userData)
{
    //gatt_client = (LGATTClient*)userData;

    APP_LOG("[LGATT]gattBegin - Start"); 

    // open BT
	vm_btcm_init(gatt_client_bt_init_cb,VM_SRV_BT_CM_EVENT_ACTIVATE | 0x00080000,userData);
	if (VM_SRV_BT_CM_POWER_ON == vm_btcm_get_power_status())
	{
	    APP_LOG("[LGATT]gattBegin - BT already power on."); 
		gatt_client_init(userData);
	}
	else
	{
	    APP_LOG("[LGATT]gattBegin - Power on BT.."); 
		vm_btcm_switch_on();
	}
	
	APP_LOG("[LGATT]gattBegin - End"); 
    return false;
}


boolean gattScan(void *userData)
{
	LGATTClient *client = (LGATTClient*)userData;
    
    APP_LOG("[LGATT]gattScan - Start"); 

    if (!client)
    {
        APP_LOG("[LGATT] FATAL 3");
        return true;
    }
    if (0 < client->_cntx._tid)
    {
        client->_return_value = false;
        return true;
    }

    client->_cntx._tid = vm_create_timer(client->_cntx._timeout*1000, gatt_client_timeout_cb);
    if (0 > client->_cntx._tid)
    {
        client->_return_value = false;
        return true;
    }
    
	client->scan_ret = vm_gattc_scan(client->_cntx.reg_ctx,VM_TRUE);
	if (client->scan_ret >= 0)
    {	    
        client->_cntx._searched_ble_dev_nums = 0;        
        memset(&GATT_CLIENT_BD_ADDR_LIST, 0x0, sizeof(GATT_CLIENT_BD_ADDR_LIST));
	    APP_LOG("[LGATT]gattScan - End, scan_ret = %d", client->scan_ret); 
        return false;
	}
	else
	{
	    vm_delete_timer(client->_cntx._tid);
	    client->_cntx._tid = -1;
	}
	APP_LOG("[LGATT]gattScan - End1, scan_ret = %d", client->scan_ret); 
	client->_return_value = false;
    return true;
}


boolean gattConnect(void *userData)
{
	LGATTClient *client = (LGATTClient*)userData;
    
	APP_LOG("[LGATT]gattConnect - reg_ctx[0x%x] Start", client->_cntx.reg_ctx); 

    if (!client)
    {
        APP_LOG("[LGATT] FATAL 3");
        return true;
    }
	vm_gattc_connect(client->_cntx.reg_ctx, (VM_BD_ADDR*)&(client->_cntx._address), VM_TRUE);
 
    APP_LOG("[LGATT]gattConnect - bd_addr = [0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x]", 
            client->_cntx._address.addr[5], 
            client->_cntx._address.addr[4], 
            client->_cntx._address.addr[3], 
            client->_cntx._address.addr[2], 
            client->_cntx._address.addr[1], 
            client->_cntx._address.addr[0]);
    APP_LOG("[LGATT]gattConnect - End, connected = %d", (client->cb_data.connection.connected)); 
    
    return false;
}

boolean gattDisConnect(void *userData)
{
	LGATTClient *client = (LGATTClient*)userData;
    
	APP_LOG("[LGATT]gattDisConnect - reg_ctx[0x%x] Start", client->_cntx.reg_ctx); 

    if (!client)
    {
        APP_LOG("[LGATT] FATAL 3");
        return true;
    }
	vm_gattc_disconnect((vm_gatt_conn_struct*)&(client->cb_data.conn), (VM_BD_ADDR*)&(client->_cntx._address));
 
    APP_LOG("[LGATT]gattDisConnect - bd_addr = [0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x]", 
            client->_cntx._address.addr[5], 
            client->_cntx._address.addr[4], 
            client->_cntx._address.addr[3], 
            client->_cntx._address.addr[2], 
            client->_cntx._address.addr[1], 
            client->_cntx._address.addr[0]);
    APP_LOG("[LGATT]gattDisConnect - End, connected = %d", (client->cb_data.connection.connected)); 
    return false;
}

boolean gattEnableNotification(void *userData)
{
	LGATTClient *client = (LGATTClient*)userData;
    
	APP_LOG("[LGATT]enableNotification - register notification Start"); 

    if (!client)
    {
        APP_LOG("[LGATT] FATAL 3");
        return true;
    }

    vm_gattc_char_struct ch;
    VM_GATT_SVC_UUID svc_uuid = {0};
    VM_ATT_UUID ch_uuid = {0};

    svc_uuid.is_primary = client->_cntx._isPrimary;
    svc_uuid.uuid.inst = 0;
    memcpy(&(svc_uuid.uuid.uuid), &(client->_cntx._currServiceUUID), sizeof(VM_BT_UUID));

    ch_uuid.inst = 0;
    memcpy(&(ch_uuid.uuid), &(client->_cntx._currCharUUID), sizeof(VM_BT_UUID));

    ch.ch_uuid = &ch_uuid;
    ch.svc_uuid = &svc_uuid;

    LGATTUUID svcUUID = ch.svc_uuid->uuid.uuid;
    LGATTUUID charUUID = ch.ch_uuid->uuid;
    APP_LOG("Service UUID : [%s]", logGATTUUID(svcUUID));
    APP_LOG("Service isPrimary[%d], inst[%d]", ch.svc_uuid->is_primary, ch.svc_uuid->uuid.inst);
    APP_LOG("Char UUID : [%s]", logGATTUUID(charUUID));

    if (client->_cntx._isEnableNotification)
    {
    
        vm_gattc_register_for_notification(client->_cntx.reg_ctx, 
                        (VM_BD_ADDR*)&(client->_cntx._address), 
                        &ch);
    }
    else
    {
        vm_gattc_deregister_for_notification(client->_cntx.reg_ctx, 
                        (VM_BD_ADDR*)&(client->_cntx._address), 
                        &ch);
    }
	APP_LOG("[LGATT]enableNotification - register notification End"); 
}

boolean gattQueryNotification(void *userData)
{
	LGATTClient *client = (LGATTClient*)userData;
    
	APP_LOG("[LGATT]enableNotification - register notification Start"); 

    if (!client)
    {
        APP_LOG("[LGATT] FATAL 3");
        return true;
    }

    if (client->_cntx._currNotificationData._attrValue.len > 0)
    {
        client->_return_value = true;
    }
    else
    {
        client->_return_value = false;
    }

	APP_LOG("[LGATT]enableNotification - register notification ret[%d] End", client->_return_value); 

    return true;
    
}
boolean gattGetCharacteristic(void *userData)
{
    APP_LOG("[LGATT]gattGetCharacteristic - Start"); 
    LGATTClient *client = (LGATTClient*)userData;
    if (!client)
    {
        //client->_return_value = false;
        APP_LOG("[LGATT] FATAL 3");
        return true;
    }
    //LGATTClient *client = (LGATTClient *)userData;
/*
    APP_LOG("[LGATT]gattGetCharacteristic - conn = %x", 
        &gatt_client->cb_data.conn); 

    APP_LOG("[LGATT]XXX ->reg_ctx = %x, ->conn_ctx = %x", 
        gatt_client->cb_data.conn.reg_ctx, gatt_client->cb_data.conn.conn_ctx); 

    APP_LOG("[LGATT]gattGetCharacteristic - svc_uuid = %x,%x,%x,%x,%x,%x,%x,%x,%x,%x,%x,%x,%x,%x,%x,%x",
        gatt_client->cb_data.characteristic.ch->svc_uuid->uuid.uuid.uuid[0],
        gatt_client->cb_data.characteristic.ch->svc_uuid->uuid.uuid.uuid[1],
        gatt_client->cb_data.characteristic.ch->svc_uuid->uuid.uuid.uuid[2],
        gatt_client->cb_data.characteristic.ch->svc_uuid->uuid.uuid.uuid[3],
        gatt_client->cb_data.characteristic.ch->svc_uuid->uuid.uuid.uuid[4],
        gatt_client->cb_data.characteristic.ch->svc_uuid->uuid.uuid.uuid[5],
        gatt_client->cb_data.characteristic.ch->svc_uuid->uuid.uuid.uuid[6],
        gatt_client->cb_data.characteristic.ch->svc_uuid->uuid.uuid.uuid[7],
        gatt_client->cb_data.characteristic.ch->svc_uuid->uuid.uuid.uuid[8],
        gatt_client->cb_data.characteristic.ch->svc_uuid->uuid.uuid.uuid[9],
        gatt_client->cb_data.characteristic.ch->svc_uuid->uuid.uuid.uuid[10],
        gatt_client->cb_data.characteristic.ch->svc_uuid->uuid.uuid.uuid[11],
        gatt_client->cb_data.characteristic.ch->svc_uuid->uuid.uuid.uuid[12],
        gatt_client->cb_data.characteristic.ch->svc_uuid->uuid.uuid.uuid[13],
        gatt_client->cb_data.characteristic.ch->svc_uuid->uuid.uuid.uuid[14],
        gatt_client->cb_data.characteristic.ch->svc_uuid->uuid.uuid.uuid[15]); 
     */

    //memcpy(&(gatt_client->cb_data.characteristic.ch.svc_uuid.uuid.uuid), uuidInt, sizeof(lgatt_bt_uuid));
    VM_GATT_SVC_UUID svc_uuid;
    svc_uuid.is_primary = client->_cntx._isPrimary;
    svc_uuid.uuid.inst = 0;
    memcpy(&(svc_uuid.uuid.uuid), &(client->_cntx._currServiceUUID), sizeof(VM_BT_UUID));

    vm_gattc_get_characteristic(
        (vm_gatt_conn_struct*)&(client->cb_data.conn), 
        (VM_GATT_SVC_UUID*)&svc_uuid, 
        (VM_ATT_UUID*)(client->cb_data.characteristic.start_char_uuid.uuid.len ? &(client->cb_data.characteristic.start_char_uuid) : NULL));
    APP_LOG("[LGATT]gattGetCharacteristic - start char[0x%x] len[%d] End", &(client->cb_data.characteristic.start_char_uuid), 
        client->cb_data.characteristic.start_char_uuid.uuid.len); 
    return false;
}


boolean gattGetDescriptor(void *userData)
{
    
    LGATTClient *client = (LGATTClient*)userData;
	client = (LGATTClient*)userData;

    if (!client)
    {
        APP_LOG("[LGATT] FATAL 3");
        return true;
    }	
    vm_gattc_char_struct ch;
    VM_GATT_SVC_UUID svc_uuid;
    VM_ATT_UUID ch_uuid;

    svc_uuid.is_primary = client->_cntx._isPrimary;
    svc_uuid.uuid.inst = 0;
    memcpy(&(svc_uuid.uuid.uuid), &(client->_cntx._currServiceUUID), sizeof(VM_BT_UUID));

    ch_uuid.inst = 0;
    memcpy(&(ch_uuid.uuid), &(client->_cntx._currCharUUID), sizeof(VM_BT_UUID));

    ch.ch_uuid = &ch_uuid;
    ch.svc_uuid = &svc_uuid;

    vm_gattc_get_descriptor(
        (vm_gatt_conn_struct*)&(client->cb_data.conn), 
        (vm_gattc_char_struct*)&ch, 
        (VM_ATT_UUID*)(client->cb_data.descriptor.start_descr_uuid.uuid.len ? &(client->cb_data.descriptor.start_descr_uuid) : NULL));

    return false;

}


boolean gattReadCharacteristic(void *userData)
{

    VMINT ret = 0;
    APP_LOG("[LGATT]gattReadCharacteristic - Start"); 
    
    LGATTClient *client = (LGATTClient*)userData;
    if (!client)
    {
        APP_LOG("[LGATT] FATAL 3");
        return true;
    }

    vm_gattc_char_struct ch;
    VM_GATT_SVC_UUID svc_uuid;
    VM_ATT_UUID ch_uuid;

    svc_uuid.is_primary = client->_cntx._isPrimary;
    svc_uuid.uuid.inst = 0;
    memcpy(&(svc_uuid.uuid.uuid), &(client->_cntx._currServiceUUID), sizeof(VM_BT_UUID));

    ch_uuid.inst = 0;
    memcpy(&(ch_uuid.uuid), &(client->_cntx._currCharUUID), sizeof(VM_BT_UUID));

    ch.ch_uuid = &ch_uuid;
    ch.svc_uuid = &svc_uuid;

    LGATTUUID svcUUID = ch.svc_uuid->uuid.uuid;
    LGATTUUID charUUID = ch.ch_uuid->uuid;
    APP_LOG("Service UUID : [%s]", logGATTUUID(svcUUID));
    APP_LOG("Service isPrimary[%d], inst[%d]", ch.svc_uuid->is_primary, ch.svc_uuid->uuid.inst);
    APP_LOG("Char UUID : [%s]", logGATTUUID(charUUID));


    APP_LOG("[LGATTC] reg[0x%x], conn[0x%x]", client->cb_data.conn.reg_ctx, client->cb_data.conn.conn_ctx);
    
    ret = vm_gattc_read_characteristic((vm_gatt_conn_struct*)&(client->cb_data.conn), 
            (vm_gattc_char_struct*)&ch,
            VM_GATTC_AUTH_REQ_NONE);

    APP_LOG("[LGATT]gattReadCharacteristic - End, ret = %d", ret); 

    if (0 > ret)
    {
        client->_return_value = false;
        return true;
    }
    else
    {
        client->_return_value = true;
    }
    return false;
}


boolean gattWriteCharacteristic(void *userData)
{

    VMINT ret = 0;

    APP_LOG("[LGATT]gattWriteCharacteristic - Start"); 
    
    LGATTClient *client = (LGATTClient*)userData;
    if (!client)
    {
        APP_LOG("[LGATT] FATAL 3");
        return true;
    }

    vm_gattc_char_struct ch;
    VM_GATT_SVC_UUID svc_uuid;
    VM_ATT_UUID ch_uuid;
    VM_ATT_VALUE att_value;

    svc_uuid.is_primary = client->_cntx._isPrimary;
    svc_uuid.uuid.inst = 0;
    memcpy(&(svc_uuid.uuid.uuid), &(client->_cntx._currServiceUUID), sizeof(VM_BT_UUID));

    ch_uuid.inst = 0;
    memcpy(&(ch_uuid.uuid), &(client->_cntx._currCharUUID), sizeof(VM_BT_UUID));

    ch.ch_uuid = &ch_uuid;
    ch.svc_uuid = &svc_uuid;

    memcpy(&att_value, &(client->_cntx._currAttrValue), sizeof(LGATTAttributeValue));    

    LGATTUUID svcUUID = ch.svc_uuid->uuid.uuid;
    LGATTUUID charUUID = ch.ch_uuid->uuid;
    APP_LOG("Service UUID : [%s]", logGATTUUID(svcUUID));
    APP_LOG("Service isPrimary[%d], inst[%d]", ch.svc_uuid->is_primary, ch.svc_uuid->uuid.inst);
    APP_LOG("Char UUID : [%s]", logGATTUUID(charUUID));
    APP_LOG("cb_data.conn.reg_ctx[0x%x], cb_data.conn.conn_ctx[0x%x]", client->cb_data.conn.reg_ctx, client->cb_data.conn.conn_ctx);
    APP_LOG("value [%s] len[%d]", att_value.value, att_value.len);

	ret = vm_gattc_write_characteristic(
    		(vm_gatt_conn_struct*)&(client->cb_data.conn), 
    		(vm_gattc_char_struct*)&ch, 
    		(VM_ATT_VALUE *)&att_value,
    		VM_GATTC_WRITE_TYPE_REQUEST,
    		VM_GATTC_AUTH_REQ_NONE);

    APP_LOG("[LGATT]gattWriteCharacteristic - End,  ret = %d", ret); 
    
    return false;
    
}


boolean gattReadDescriptor(void *userData)
{
    APP_LOG("[LGATT]gattReadDescriptor - Start"); 
    
    LGATTClient *client = (LGATTClient*)userData;
    if (!client)
    {
        APP_LOG("[LGATT] FATAL 3");
        return true;
    }

    vm_gattc_descr_struct descr;
    VM_GATT_SVC_UUID svc_uuid;
    VM_ATT_UUID ch_uuid;
    VM_ATT_UUID descr_uuid;
    
    svc_uuid.is_primary = client->_cntx._isPrimary;
    svc_uuid.uuid.inst = 0;
    memcpy(&(svc_uuid.uuid.uuid), &(client->_cntx._currServiceUUID), sizeof(VM_BT_UUID));

    ch_uuid.inst = 0;
    memcpy(&(ch_uuid.uuid), &(client->_cntx._currCharUUID), sizeof(VM_BT_UUID));

    descr_uuid.inst = 0;
    memcpy(&(descr_uuid.uuid), &(client->_cntx._currDescUUID), sizeof(VM_BT_UUID));

    descr.svc_uuid = &svc_uuid;
    descr.ch_uuid = &ch_uuid;
    descr.descr_uuid = &descr_uuid;

	vm_gattc_read_descriptor(
        (vm_gatt_conn_struct*)&(client->cb_data.conn), 
        (vm_gattc_descr_struct *)&descr, 
        VM_GATTC_AUTH_REQ_NONE);
    APP_LOG("[LGATT]gattReadDescriptor - End"); 

    return false;
}


boolean gattWriteDescriptor(void *userData)
{

    APP_LOG("[LGATT]gattWriteDescriptor - Start"); 
    
    LGATTClient *client = (LGATTClient*)userData;
    if (!client)
    {
        APP_LOG("[LGATT] FATAL 3");
        return true;
    }

    vm_gattc_descr_struct descr;
    VM_GATT_SVC_UUID svc_uuid;
    VM_ATT_UUID ch_uuid;
    VM_ATT_UUID descr_uuid;
    VM_ATT_VALUE att_value;
    
    svc_uuid.is_primary = client->_cntx._isPrimary;
    svc_uuid.uuid.inst = 0;
    memcpy(&(svc_uuid.uuid.uuid), &(client->_cntx._currServiceUUID), sizeof(VM_BT_UUID));

    ch_uuid.inst = 0;
    memcpy(&(ch_uuid.uuid), &(client->_cntx._currCharUUID), sizeof(VM_BT_UUID));

    descr_uuid.inst = 0;
    memcpy(&(descr_uuid.uuid), &(client->_cntx._currDescUUID), sizeof(VM_BT_UUID));

    descr.svc_uuid = &svc_uuid;
    descr.ch_uuid = &ch_uuid;
    descr.descr_uuid = &descr_uuid;

    memcpy(&att_value, &(client->_cntx._currAttrValue), sizeof(LGATTAttributeValue));

	vm_gattc_write_descriptor(
		(vm_gatt_conn_struct*)&(client->cb_data.conn), 
		(vm_gattc_descr_struct *)&descr,
        (VM_ATT_VALUE*)&att_value,
        VM_GATTC_WRITE_TYPE_REQUEST, 
        VM_GATTC_AUTH_REQ_NONE);

    APP_LOG("[LGATT]gattWriteDescriptor - End"); 
    

    return false;
}


boolean gattReadRemoteRSSI(void *userData)
{
    VMINT ret;
    APP_LOG("[LGATT]gattReadRemoteRSSI - Start"); 
    LGATTClient *client = (LGATTClient*)userData;
    if (!client)
    {
        APP_LOG("[LGATT] FATAL 3");
        return true;
    }
    
    VM_BD_ADDR bd_addr;
    memcpy(&bd_addr, &(client->_cntx._address), sizeof(bd_addr));
    
	ret = vm_gattc_read_remote_rssi(client->_cntx.reg_ctx, &bd_addr);

    APP_LOG("[LGATT]gattReadRemoteRSSI - End, ret = %d", ret); 

    return false;
}


boolean gattEnd(void *userData)
{
    VMINT ret;
    APP_LOG("[LGATT]gattEnd - Start"); 
    LGATTClient *client = (LGATTClient*)userData;
    if (!client)
    {
        APP_LOG("[LGATT] FATAL 3");
        return true;
    }
    
    if (!gatt_client_deinit(userData))
    {
        client->_return_value = false;
        return true;
    }
    
    gatt_client_clean();

    APP_LOG("[LGATT]gattEnd - End"); 
	return false;
}


