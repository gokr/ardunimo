#include <LGSM.h>

String remoteNumber = "";  // the number you will call
char charbuffer[20];

void setup()
{
  // initialize serial communications
  Serial.begin(115200); 
  Serial.println("Make Voice Call");
  Serial.println("Enter phone number to call.");
}

void loop()
{
  // add any incoming characters to the String:
  while (Serial.available() > 0)
  {
    char inChar = Serial.read();
    // if it's a newline, that means you should make the call:
    if (inChar == '\n')
    {
      // make sure the phone number is not too long:
      if (remoteNumber.length() < 20)
      {
        // let the user know you're calling:
        Serial.print("Calling to : ");
        Serial.println(remoteNumber);
        Serial.println();

        // Call the remote number
        remoteNumber.toCharArray(charbuffer, 20);
        
        // Check if the receiving end has picked up the call
        if(LVoiceCall.voiceCall(charbuffer))
        {
          Serial.println("Call Established. Enter line to end");
          // Wait for some input from the line
          while(Serial.read() !='\n');
          // And hang up
          LVoiceCall.hangCall();
        }
        Serial.println("Call Finished");
        remoteNumber="";
        Serial.println("Enter phone number to call.");
      } 
      else
      {
        Serial.println("That's too long for a phone number. I'm forgetting it"); 
        remoteNumber = "";
      }
    } 
    else
    {
      // add the latest character to the message to send:
      if(inChar!='\r')
        remoteNumber += inChar;
    }
  } 
}
