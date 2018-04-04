// iftttMaker library
//------- Replace the following! ------
//#define KEY "zzzzzzzzzzzzzzzzzzzzzzz"  // Get it from this page https://ifttt.com/services/maker/settings
//#define EVENT_NAME "device_on" // Name of your event name, set when you are creating the applet
#include <IFTTTMaker.h>
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
    WiFiClientSecure *clientIFTTT = new WiFiClientSecure();
    IFTTTMaker ifttt(KEY, clientIFTTT);
    if(ifttt.triggerEvent(EVENT_NAME, ssid)){
      Serial.println("IFTT Successfully sent");
    } else { Serial.println("IFTT Failed!");
    delete clientIFTT;
    clientIFTT = nullptr;
}

  }
  if (debouncer.doubleclick()){config.Mode = 2; debouncer.reset();}
  if (debouncer.longpress()){
    if (config.Mode == 0){
      config.Mode = 3; debouncer.reset();
    }
    else {config.Mode = 0;}
  }
}
