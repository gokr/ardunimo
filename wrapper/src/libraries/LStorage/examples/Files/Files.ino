/*
  Drv card basic file example

 created   Nov 2010
 by David A. Mellis
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

LFile myFile;

void setup()
{
    // Open serial communications and wait for port to open:
    Serial.begin(9600);

    while(!Serial.available());         // input any thing to start


    Serial.print("Initializing Drv card...");
    // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
    // Note that even if it's not used as the CS pin, the hardware SS pin
    // (10 on most Arduino boards, 53 on the Mega) must be left as an output
    // or the Drv library functions will not work.
    pinMode(10, OUTPUT);

    Drv.begin();
    Serial.println("initialization done.");

    if (Drv.exists("example.txt")) {
        Serial.println("example.txt exists.");
    }
    else {
        Serial.println("example.txt doesn't exist.");
    }

    // open a new file and immediately close it:
    Serial.println("Creating example.txt...");
    myFile = Drv.open("example.txt", FILE_WRITE);
    myFile.close();

    // Check to see if the file exists:
    if (Drv.exists("example.txt")) {
        Serial.println("example.txt exists.");
    }
    else {
        Serial.println("example.txt doesn't exist.");
    }

    // delete the file:
    Serial.println("Removing example.txt...");
    Drv.remove("example.txt");

    if (Drv.exists("example.txt")) {
        Serial.println("example.txt exists.");
    }
    else {
        Serial.println("example.txt doesn't exist.");
    }
}

void loop()
{
    // nothing happens after setup finishes.
}



