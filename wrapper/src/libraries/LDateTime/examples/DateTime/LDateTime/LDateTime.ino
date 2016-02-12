#include <LDateTime.h>

datetimeInfo t;
unsigned int rtc;

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
  LDateTime.getTime(&t);
  LDateTime.getRtc(&rtc);
  delay(1000);
}
