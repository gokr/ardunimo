/*
  SD card file dump

 This example shows how to read a file from the SD card using the
 SD library and send it over the serial port.


 created  22 December 2010
 by Limor Fried
 modified 9 Apr 2012
 by Tom Igoe

  port to LinkIt ONE
 by Loovee
 2014-10-12
 This example code is in the public domain.

 */

#include <LTask.h>
#include <LFlash.h>
#include <LSD.h>
#include <LStorage.h>


#define Drv LFlash          // use Internal 10M Flash
// #define Drv LSD           // use SD card


void setup()
{
    // Open serial communications and wait for port to open:
    Serial.begin(9600);

    while(!Serial.available());         // input any thing to start


    Serial.print("Initializing SD card...");
    // make sure that the default chip select pin is set to
    // output, even if you don't use it:
    pinMode(10, OUTPUT);

    // see if the card is present and can be initialized:
    Drv.begin();
    Serial.println("card initialized.");

    // open the file. note that only one file can be open at a time,
    // so you have to close this one before opening another.
    LFile dataFile = Drv.open("datalog.txt");

    // if the file is available, write to it:
    if (dataFile) {
        while (dataFile.available()) {
            Serial.write(dataFile.read());
        }
        dataFile.close();
    }
    // if the file isn't open, pop up an error:
    else {
        Serial.println("error opening datalog.txt");
    }
}

void loop()
{
    // do nothing here
}

