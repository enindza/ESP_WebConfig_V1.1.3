# ESP_WebConfig_V1.1.3
test Johnn Lassen ESP 8266 Arduino IDE WebConfig

https://www.john-lassen.de/en/projects/esp-8266-arduino-ide-webconfig

Key Features :

    Easy configuration of IP-Address, Netmask, Gateway, SSID and password for your router
    Build-In NTP Client (especially when you want to build a clock), with timezome and daylight saving support
    Realtime clock structure for having a convinient way to access the date/time
    Turn On/Off things at a given time (e.g. for lamps)
    Administration-page will not be accessible after a given time because AP-Mode at the ESP will be disabled
    Simple AJAX Support (microajax)
    HTML pages can be in a differnt (.h-) file and are stored in Progmem.

 
Installation

Compile the source code and put it on your ESP.
After first start use a WiFi device, connect to the ESP Wifi-Access Point (e.g. mobile phone or notebook) and go to address :

http://192.168.4.1/admin.html

Now you see a menu (see on the right side at this page), where you can change the settings to you needs. 

Settings at the INO-File

If the ESP is starting in Admin(Accesspoint)-Mode you have to use/change these settings :

#define ACCESS_POINT_NAME  "MYESP" 
#define ACCESS_POINT_PASSWORD "12345678" 

Define the time, the ESP is in admin-mode after startup and opens up an access point:

#define AdminTimeOut 180 // Defines the time in seconds, when the admin mode will be diabled 

The DateTime structure

In the Main Arduino is a global Struct-Varibale called DateTime. This struct will be updated every second. If you have the NTP Client running, the struct will also be updatet by NTP. 


struct  strDateTime {
   byte hour;
   byte minute;
   byte second;
   int year;
   byte month;
   byte day;
   byte wday;   // Weekday
};

