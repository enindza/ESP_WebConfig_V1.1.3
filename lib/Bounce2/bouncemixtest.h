//#include <IFTTTwebhooks.h>
//#include <ESP8266WiFi.h>


//#include "local.h"


// iftttMaker library
//------- Replace the following! ------
//#define KEY "zzzzzzzzzzzzzzzzzzzzzzz"  // Get it from this page https://ifttt.com/services/maker/settings
//#define EVENT_NAME "device_on" // Name of your event name, set when you are creating the applet
//#include <IFTTTMaker.h>
//WiFiClientSecure *clientIFTTT = new WiFiClientSecure();
//IFTTTMaker ifttt(KEY, clientIFTT);




void Bouncemixutest(){

  // debounce do dole
  // Update the Bounce instance :


  // debouncer.testprint();

  if (debouncer.rise()){
    if (config.Mode > 0 ) {config.Mode = 0;}
    else {config.Mode = 1;}

    // delete after IFTT test
    IFTTTset(0);


  }
  if (debouncer.doubleclick()){config.Mode = 2; debouncer.reset();}
  if (debouncer.longpress()){
    if (config.Mode == 0){
      config.Mode = 3; debouncer.reset();
    }
    else {config.Mode = 0;}
  }
}
