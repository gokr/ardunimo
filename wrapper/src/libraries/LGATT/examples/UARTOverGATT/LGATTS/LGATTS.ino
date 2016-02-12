#include "LGATTSUart.h"
#include "LGATTSABC.h"
#include <LGATTUUID.h>

#ifdef APP_LOG
#undef APP_LOG
#endif

#define APP_LOG(...) Serial.printf(__VA_ARGS__); \
    Serial.println();

LGATTSUart uart;
LGATTUT abc;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(8000);
  //LGATTServer.begin(g_gatts_uuid, 1, &uart);
  
    if (!LGATTServer.begin(2, &uart, &abc))
    {
        APP_LOG("[FAILED] GATTS begin");
    }
    else
    {
        APP_LOG("GATTS begin");
    }
    
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(5000);
  LGATTServer.handleEvents();
  //LGATTAttributeValue value = {13, "hello, world!"};
  if (uart.isConnected())
  {
    LGATTAttributeValue value = {0};
    const char *str = "[peripheral] hello";
    value.len = strlen(str);
    memcpy(value.value, str, value.len);
    boolean ret = uart.sendIndication(value, uart.getHandleNotify(), false);
    if (!ret)
    {
        APP_LOG("[FAILED] send [%d]", ret);
    }
    APP_LOG("send [%d][%s]", ret, str);
  }
  //uart.send(value, uart.getHandle(0), false); // just a notify

}

