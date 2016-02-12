#include <LGATT.h>
#include <LGATTClient.h>
#include <LGATTServer.h>

static LGATTUUID test_uuid("B4B4B4B4-B4B4-B4B4-B4B4-B4B4B4B4B4B5");

LGATTClient c;

void setup() {
    delay(5000);
    Serial.begin(9600); 
    Serial.println("[LGATTC ino]setup.");
    
    // gatt client register

    if (c.begin(test_uuid))
    {
        Serial.println("[LGATTC ino]begin() success to register.");
    }
    else
    {
        Serial.println("[LGATTC ino]begin() failed to register.");
        delay(0xffffffff);
    }
}

void loop() 
{
    // scan device
    Serial.println("[LGATTC ino]loop::start to scan.");
    int num = 0;
    LGATTDeviceInfo info = {0};
    while (1)
    {
        num = c.scan(6);
        int found = 0;
        Serial.printf("scan num [%d] a", num);
        Serial.println();
        for (int i = 0; i < num; i++)
        {
            c.getScanResult(i, info);
            if (!c.connect(info.bd_addr)) // search all services till timeout or searching done.
            {
                Serial.println("[LGATTC ino]begin() failed to connect.");
                delay(0xffffffff);
            }
            else
                Serial.println("[LGATTC ino]begin() success to connect.");
            int32_t rssi = 0;
            while (1)
            {
                if (c.readRemoteRSSI(info.bd_addr, rssi))
                {
                    Serial.printf("[LGATTC ino] readRemoteRSSI address : [%x:%x:%x:%x:%x:%x] rssi [%d]", 
                    info.bd_addr.addr[5], info.bd_addr.addr[4], info.bd_addr.addr[3], info.bd_addr.addr[2], info.bd_addr.addr[1], info.bd_addr.addr[0],
                    rssi);
                    Serial.println();
                    delay(1000);
                }
                else
                {
                    Serial.println("[LGATTC ino] failed to get rssi");
                    break;
                }
            }
            c.disconnect(info.bd_addr);
            
        }
        delay(500);
    }
    
    //delay(0xffffffff);
}
