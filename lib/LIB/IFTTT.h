#define IFTTTRETRY 3 //Single IFTTT message will be retried IFTTTRETRY times
#define IFTTTCode0 "Bojler power up"  //After power up of reset
#define IFTTTCode1 "Bojler set temperature reached"
#define IFTTTCode2 "Sensor error"
#define IFTTTCode3 "Hardware error"

#include "IFTTTwebhooks.h"
#include "config.h"

IFTTTwebhooks* client1 = nullptr;

// code in config.h
/*
struct strIFTT{
  uint8_t	RetryCounter; //number of current retry
	long RetryDelayExpire; //Time for next IFTTT send
  uint8_t Success; // counts number of successful retry
  uint8_t Code; // 0- reboot, 1 - temperature reached, 2 Sensor Error, 3 Hardware error
} IFTTTconfig;
*/

//initialize on setup routine
void IFTTTinit(){
  IFTTTconfig.RetryCounter = IFTTTRETRY;
  IFTTTconfig.Success = 0;
}

// Set IFTTT message with code for sending
// new message will rewrite old one, check this for next application
// call from the main code
void IFTTTset(uint8_t Code){

  IFTTTconfig.Code = Code;
  IFTTTconfig.RetryCounter = 0;
  IFTTTconfig.RetryDelayExpire = millis(); //Sent first retry as soon as possible
  IFTTTconfig.Success = 0;
  Serial.printf("*-* IFTTTset Code:"); Serial.println(IFTTTconfig.Code, DEC);
}

boolean IFTTTSend(String eventName, String value1 = "", String value2 = "", String value3= ""){
  //if (IFTTTfail < IFTTTRetryMax)
  client1 = new IFTTTwebhooks(KEY);
  boolean result;
  //triggerEvent takes an Event Name and then you can optional pass in up to 3 extra Strings
  //Serial.printf("EVENT_NAME: "); Serial.println(EVENT_NAME);
  Serial.printf("EVENT_NAME: "); Serial.println(eventName);

  if(client1->triggerEvent(eventName, value1, value2, value3)){
    Serial.println("IFTTT Successfully sent");
    result = true;
  } else
  {
    Serial.println("IFTTT Failed!");
    result = false;
  }
  Serial.printf("Free heap1: %u\n", ESP.getFreeHeap());

  // delete IFTTTwebhooks object
  //
  delete client1;
  client1 = nullptr;
  Serial.printf("Free heap2: %u\n", ESP.getFreeHeap());
  return result;
}

//update IFTTT status, and execute code if unnecessary
//should be positioned in main loop, and checked as often as possible
void IFTTTUpdate(){
  boolean  result;
  //String tekst = "";
  //tekst = " " + config.Temperatura[0] + " ";
  if ((HTTPSready) and (WiFi.status() == WL_CONNECTED)){
    Serial.printf("*-* IFTTT switch Code"); Serial.println(IFTTTconfig.Code, DEC);
    switch (IFTTTconfig.Code) {
      case 0: //Boiler power up
        Serial.println("*-* IFTTT enter Case 0");
        result = IFTTTSend(EVENT_NAME, String(config.Temperatura[0], DEC), "0"); // statements
        IFTTTconfig.RetryCounter++;
        break;
      case 1: //Temperature reached
        // statements
        break;
      case 2: //Error
        // statements
        break;
      default:
        // statements
        break;
    }
    if (result){IFTTTconfig.Success++;}
  }
}
