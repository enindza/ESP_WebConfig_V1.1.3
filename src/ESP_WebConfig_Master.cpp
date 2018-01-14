/*
  ESP_WebConfig

  Copyright (c) 2015 John Lassen. All rights reserved.
  This is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.
  This software is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

  Latest version: 1.1.3  - 2015-07-20
  Changed the loading of the Javascript and CCS Files, so that they will successively loaded and that only one request goes to the ESP.

  -----------------------------------------------------------------------------------------------
  History

  Version: 1.1.2  - 2015-07-17
  Added URLDECODE for some input-fields (SSID, PASSWORD...)

  Version  1.1.1 - 2015-07-12
  First initial version to the public




  */
  //
  //debouncing



#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Ticker.h>
#include <EEPROM.h>
#include <WiFiUdp.h>
#include "helpers.h"
#include "Arduino.h"
#include <Bouncemix.h>
//#include "Bouncemix.cpp"
#define BUTTON_PIN D0
#define LED_PIN D1
#define HEATERINDICATOR D3
#define HEATER D1
#define POWERINDICATOR D4
#define MINIMALTEMPERATURE 22
// Instantiate a Bounce object
Bouncemix debouncer = Bouncemix();

#include "global.h"
#include "bouncemixtest.h"

// Instantiate a Bounce object :
/*Bounce debouncer = Bounce();

unsigned long buttonPressTimeStamp;
unsigned long buttonPressTime;
bool button;
#include "BounceHelper2.h"
*/

/*
Include the HTML, STYLE and Script "Pages"
*/
# include <I2CDallas.h>
#include "powerregulation.h"

#include "Page_Root.h"
#include "Page_Admin.h"
#include "Page_Script.js.h"
#include "Page_Style.css.h"
#include "Page_NTPsettings.h"
#include "Page_Information.h"
#include "Page_General.h"
//#include "Page_GeneralBoiler.h"
#include "Page_applSettings.h"
#include "PAGE_NetworkConfiguration.h"
#include "example.h"
#include "Setup_Server.h"

#include "powerregulation.h"

#define ACCESS_POINT_NAME  "ESP"
#define ACCESS_POINT_PASSWORD  "12345678"
#define AdminTimeOut 180  // Defines the Time in Seconds, when the Admin-Mode will be diabled

void setPin(int state) {
  digitalWrite(LED_BUILTIN, state);
}

void setup ( void ) {
	//Velicina eeprom memorije
	EEPROM.begin(512);
	Serial.begin(115200);
	delay(500);
	Serial.println("Starting ES8266");

	// set default CONFIGURATION by changing cfg part for FRESH START
	//EEPROM.write(0,'J');
	// Test for FRESH START configuration settings
	if (!ReadConfig())
	{
		// DEFAULT CONFIG
		config.ssid = "ssid";
		config.password = "lozinka";
		config.dhcp = true;
		config.IP[0] = 192;config.IP[1] = 168;config.IP[2] = 6;config.IP[3] = 95;
		config.Netmask[0] = 255;config.Netmask[1] = 255;config.Netmask[2] = 255;config.Netmask[3] = 0;
		config.Gateway[0] = 192;config.Gateway[1] = 168;config.Gateway[2] = 6;config.Gateway[3] = 1;
		config.ntpServerName = "0.de.pool.ntp.org";
		config.Update_Time_Via_NTP_Every =  0;
		config.timezone = -10;
		config.daylight = true;
		config.DeviceName = "Not Named";
		config.AutoTurnOff = false;
		config.AutoTurnOn = false;
		config.AutoTurnOff2 = false;
		config.AutoTurnOn2 = false;
		config.TurnOffHour = 0;
		config.TurnOffMinute = 0;
		config.TurnOnHour = 0;
		config.TurnOnMinute = 0;
		config.TurnOffHour2 = 0;
		config.TurnOffMinute2 = 0;
		config.TurnOnHour2 = 0;
		config.TurnOnMinute2 = 0;
		config.temp1 = 0;
		config.temp2 = 0;
		config.temp3 = 0;
		config.temp4 = 0;
		config.temp5 = 0;
		config.SensName0 ="Kotao";
		config.SensName1 ="Izlazna voda";
		config.SensName2 ="Povratna voda";
		config.SensName3 ="Soba";
		config.SensName4 ="Spolja";
		WriteConfig();
		Serial.println("Default config applied");
	}

	if (AdminEnabled)
	{ WiFi.mode(WIFI_AP_STA);
		WiFi.softAP( ACCESS_POINT_NAME , ACCESS_POINT_PASSWORD);}
	else
	{WiFi.mode(WIFI_STA);}

	ConfigureWifi();

	SetupServer();

	I2CDallasSetup();
	//Heater indicator
	pinMode(HEATERINDICATOR, OUTPUT);

  // debouncing
  // Setup the button with an internal pull-up :
  pinMode(BUTTON_PIN,INPUT_PULLUP);
  // After setting up the button, setup the Bounce instance :
  debouncer.attach(BUTTON_PIN);
  debouncer.interval(5); // interval in ms
  //Setup the LED :
  pinMode(LED_PIN,OUTPUT);

}


void loop ( void ) {
	//
	//web config
	//Disable Admin mode
	//update NTP time
	//turn Timer ON/OFF
	//
	if (AdminEnabled)
	{
		if (AdminTimeOutCounter > AdminTimeOut)
		{
			 AdminEnabled = false;
			 Serial.println("Admin Mode disabled!");
			 WiFi.mode(WIFI_STA);
		}
	}
	if (config.Update_Time_Via_NTP_Every  > 0 )
	{
		if (cNTP_Update > 5 && firstStart)
		{
			NTPRefresh();
			cNTP_Update =0;
			firstStart = false;
		}
		else if ( cNTP_Update > (config.Update_Time_Via_NTP_Every * 60) )
		{
			NTPRefresh();
			cNTP_Update =0;
		}
	}

	if(DateTime.minute != Minute_Old)
	{
		 Minute_Old = DateTime.minute;
		 if (config.AutoTurnOn)
		 {
			 if (DateTime.hour == config.TurnOnHour && DateTime.minute == config.TurnOnMinute)
			 {
				  Serial.println("SwitchON");
			 }
		 }
		 Minute_Old = DateTime.minute;
		 if (config.AutoTurnOn2)
		 {
			 if (DateTime.hour == config.TurnOnHour2 && DateTime.minute == config.TurnOnMinute2)
			 {
				  Serial.println("SwitchON2");
			 }
		 }

		 Minute_Old = DateTime.minute;
		 if (config.AutoTurnOff)
		 {
			 if (DateTime.hour == config.TurnOffHour && DateTime.minute == config.TurnOffMinute)
			 {
				  Serial.println("SwitchOff");
			 }
		 }
		 Minute_Old = DateTime.minute;
		 if (config.AutoTurnOff2)
		 {
			 if (DateTime.hour == config.TurnOffHour2 && DateTime.minute == config.TurnOffMinute2)
			 {
					Serial.println("SwitchOff2");
			 }
		 }
	}
	server.handleClient();


	/*
	*    Your Code here
	*
	*
	*/
	I2CDallasLoop();
  PowerControl();
	/*
	*    Your Code end here
	*
	*
	*/



	if (Refresh)
	{
		Refresh = false;
		///Serial.println("Refreshing...");
		 //Serial.printf("FreeMem:%d %d:%d:%d %d.%d.%d \n",ESP.getFreeHeap() , DateTime.hour,DateTime.minute, DateTime.second, DateTime.year, DateTime.month, DateTime.day);
	}
}
