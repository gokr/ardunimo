/*
  Listfiles

 This example shows how print out the files in a
 directory on a SD card

 created   Nov 2010
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe
 modified 2 Feb 2014
 by Scott Fitzgerald

 port to LinkIt ONE
 by Loovee
 2014-10-12


 This example code is in the public domain.

 */
#include <LTask.h>
#include <LFlash.h>
#include <LSD.h>
#include <LStorage.h>

LFile root;

#define Drv LFlash          // use Internal 10M Flash
// #define Drv LSD           // use SD card

void setup()
{
    // Open serial communications and wait for port to open:
    Serial.begin(9600);
    
    while(!Serial.available());         // input any thing to start

    Serial.print("Initializing Storage card...");

    pinMode(10, OUTPUT);

    Drv.begin();
    
    
    Serial.println("initialization done.");

    root = Drv.open("/");

    printDirectory(root, 0);

    Serial.println("done!");
}

void loop()
{
    // nothing happens after setup finishes.
}

void printDirectory(LFile dir, int numTabs) {
    while(true) {

        LFile entry =  dir.openNextFile();
        if (! entry) {
            // no more files
            break;
        }
        for (uint8_t i=0; i<numTabs; i++) {
            Serial.print('\t');
        }
        Serial.print(entry.name());
        if (entry.isDirectory()) {
            Serial.println("/");
            printDirectory(entry, numTabs+1);
        } else {
            // files have sizes, directories do not
            Serial.print("\t\t");
            Serial.println(entry.size(), DEC);
        }
        entry.close();
    }
}



