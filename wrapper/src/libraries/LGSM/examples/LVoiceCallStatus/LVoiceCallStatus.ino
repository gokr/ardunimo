#include <LGSM.h>

// PIN Number
#define PINNUMBER ""

char numtel[20];           // buffer for the incoming call

void setup()
{
  // initialize serial communications
  Serial.begin(115200);
  Serial.println("Receive Voice Call");

  // connection state
  boolean notConnected = true;

  // This makes sure the modem notifies correctly incoming events
  LVoiceCall.hangCall();

  Serial.println("Waiting Call");
}

void loop()
{
  // Check the status of the voice call
  switch (LVoiceCall.getVoiceCallStatus()) 
  {
    case IDLE_CALL: // Nothing is happening

      break;

    case CALLING: // This should never happen, as we are not placing a call

      Serial.println("CALLING");
      break;

    case RECEIVINGCALL: // Yes! Someone is calling us

      Serial.println("RECEIVING CALL");

      // Retrieve the calling number
      LVoiceCall.retrieveCallingNumber(numtel, 20);

      // Print the calling number
      Serial.print("Number:");
      Serial.println(numtel);

      // Answer the call, establish the call
      LVoiceCall.answerCall();         
      break;

    case TALKING:  // In this case the call would be established

      Serial.println("TALKING. Enter line to interrupt.");
      while(Serial.read()!='\n')
        delay(100);
      LVoiceCall.hangCall();
      Serial.println("HANG. Waiting Call.");      
      break;
  }
  delay(1000);
}

