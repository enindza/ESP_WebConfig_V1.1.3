#ifndef GLOBAL_H
#define GLOBAL_H

ESP8266WebServer server(80);									// The Webserver
boolean firstStart = true;										// On firststart = true, NTP will try to get a valid time
int AdminTimeOutCounter = 0;									// Counter for Disabling the AdminMode
strDateTime DateTime;											// Global DateTime structure, will be refreshed every Second
WiFiUDP UDPNTPClient;											// NTP Client
unsigned long UnixTimestamp = 0;								// GLOBALTIME  ( Will be set by NTP)
boolean Refresh = false; // For Main Loop, to refresh things like GPIO / WS2812
int cNTP_Update = 0;											// Counter for Updating the time via NTP
Ticker tkSecond;												// Second - Timer for Updating Datetime Structure
//Ticker Half_Second_Tick;
boolean AdminEnabled = true;		// Enable Admin Mode for a given Time
byte Minute_Old = 100;				// Helpvariable for checking, when a new Minute comes up (for Auto Turn On / Off)


struct strConfig {
	String ssid;
	String password;
	byte  IP[4];
	byte  Netmask[4];
	byte  Gateway[4];
	boolean dhcp;
	String ntpServerName;
	long Update_Time_Via_NTP_Every;
	long timezone;
	boolean daylight;
	String DeviceName;
	boolean AutoTurnOff;
	boolean AutoTurnOn;
	byte TurnOffHour;
	byte TurnOffMinute;
	byte TurnOnHour;
	byte TurnOnMinute;
	boolean AutoTurnOff2;
	boolean AutoTurnOn2;
	byte TurnOffHour2;
	byte TurnOffMinute2;
	byte TurnOnHour2;
	byte TurnOnMinute2;
	byte LED_R;
	byte LED_G;
	byte LED_B;
	long temp1;
	long temp2;
	long temp3;
	long temp4;
	long temp5;
	/*byte  SensorID1[8];
	byte  SensorID2[8];
	byte  SensorID3[8];
	byte  SensorID4[8];
	byte  SensorID5[8];*/
	long	SensorTemperature[5];
	byte	SensorID[5][8];
	long	temperatura[5];
	String SensName0;
	String SensName1;
	String SensName2;
	String SensName3;
	String SensName4;
	byte LinkID[5];
	//	Boiler termperature
	long MaxTemperature;
	long MidTemperature;
	//long HoldMidTemperature; //minutes to hold mid temperature
}   config;


/*
**
** CONFIGURATION HANDLING
**
*/
void ConfigureWifi()
{
	Serial.println("Configuring Wifi");
	WiFi.begin (config.ssid.c_str(), config.password.c_str());
	if (!config.dhcp)
	{
		WiFi.config(IPAddress(config.IP[0],config.IP[1],config.IP[2],config.IP[3] ),  IPAddress(config.Gateway[0],config.Gateway[1],config.Gateway[2],config.Gateway[3] ) , IPAddress(config.Netmask[0],config.Netmask[1],config.Netmask[2],config.Netmask[3] ));
	}
}



void WriteConfig()
{

	Serial.println("Writing Config");
	Serial.println("EEwrite temp2: " + config.temp2);
	EEPROM.write(0,'C');
	EEPROM.write(1,'F');
	EEPROM.write(2,'G');

	EEPROM.write(16,config.dhcp);
	EEPROM.write(17,config.daylight);

	EEPROMWritelong(18,config.Update_Time_Via_NTP_Every); // 4 Byte

	EEPROMWritelong(22,config.timezone);  // 4 Byte

	EEPROM.write(26,config.LED_R);
	EEPROM.write(27,config.LED_G);
	EEPROM.write(28,config.LED_B);

	EEPROMwritearray(config.IP,32,4);
	//EEPROM.write(32,config.IP[0]);
	//EEPROM.write(33,config.IP[1]);
	//EEPROM.write(34,config.IP[2]);
	//EEPROM.write(35,config.IP[3]);

	EEPROMwritearray(config.Netmask, 36, 4);
	//EEPROM.write(36,config.Netmask[0]);
	//EEPROM.write(37,config.Netmask[1]);
	//EEPROM.write(38,config.Netmask[2]);
	//EEPROM.write(39,config.Netmask[3]);

	EEPROMwritearray(config.Gateway, 40, 4);
	//EEPROM.write(40,config.Gateway[0]);
	//EEPROM.write(41,config.Gateway[1]);
	//EEPROM.write(42,config.Gateway[2]);
	//EEPROM.write(43,config.Gateway[3]);

	WriteStringToEEPROM(64,config.ssid);
	WriteStringToEEPROM(96,config.password);
	WriteStringToEEPROM(128,config.ntpServerName);

	EEPROM.write(300,config.AutoTurnOn);
	EEPROM.write(301,config.AutoTurnOff);
	EEPROM.write(302,config.TurnOnHour);
	EEPROM.write(303,config.TurnOnMinute);
	EEPROM.write(304,config.TurnOffHour);
	EEPROM.write(305,config.TurnOffMinute);
	Serial.println("writing t1");
	EEPROMWritelong(306,config.temp1);  // 4 Byte
	Serial.println("writing t1");
	EEPROMWritelong(310,config.temp2);  // 4 Byte
	Serial.println("writing t1");
	EEPROMWritelong(314,config.temp3);  // 4 Byte
	EEPROMWritelong(318,config.temp4);  // 4 Byte
	EEPROMWritelong(322,config.temp5);  // 4 Byte
	WriteStringToEEPROM(326,config.DeviceName); //20 byte
	EEPROM.write(346,config.AutoTurnOn2);
	EEPROM.write(347,config.AutoTurnOff2);
	EEPROM.write(348,config.TurnOnHour2);
	EEPROM.write(349,config.TurnOnMinute2);
	EEPROM.write(350,config.TurnOffHour2);
	EEPROM.write(351,config.TurnOffMinute2);
	//byte  SensorID1[8];
	EEPROMwritearray(config.SensorID[0], 352, 8);
	EEPROMwritearray(config.SensorID[1], 360, 8);
	EEPROMwritearray(config.SensorID[2], 368, 8);
	EEPROMwritearray(config.SensorID[3], 376, 8);
	EEPROMwritearray(config.SensorID[4], 384, 8);
	WriteStringToEEPROM(392, config.SensName0);
	WriteStringToEEPROM(412, config.SensName1);
	WriteStringToEEPROM(432, config.SensName2);
	WriteStringToEEPROM(452, config.SensName3);
	WriteStringToEEPROM(472, config.SensName4);
	EEPROMWritelong(492,config.MaxTemperature);
	EEPROMWritelong(496,config.MidTemperature);
	EEPROM.commit();
}
boolean ReadConfig()
{

	Serial.println("Reading Configuration");
	Serial.println("EEread temp2: " + config.temp2);
	if (EEPROM.read(0) == 'C' && EEPROM.read(1) == 'F'  && EEPROM.read(2) == 'G' )
	{
		Serial.println("Configurarion Found!");
		config.dhcp = 	EEPROM.read(16);

		config.daylight = EEPROM.read(17);

		config.Update_Time_Via_NTP_Every = EEPROMReadlong(18); // 4 Byte

		config.timezone = EEPROMReadlong(22); // 4 Byte

		config.LED_R = EEPROM.read(26);
		config.LED_G = EEPROM.read(27);
		config.LED_B = EEPROM.read(28);
		EEPROMreadarray(config.IP, 32, 4);
		//config.IP[0] = EEPROM.read(32);
		//config.IP[1] = EEPROM.read(33);
		//config.IP[2] = EEPROM.read(34);
		//config.IP[3] = EEPROM.read(35);

		EEPROMreadarray(config.Netmask, 36, 4);
		//config.Netmask[0] = EEPROM.read(36);
		//config.Netmask[1] = EEPROM.read(37);
		//config.Netmask[2] = EEPROM.read(38);
		//config.Netmask[3] = EEPROM.read(39);

		EEPROMreadarray(config.Gateway, 40, 4);
		//config.Gateway[0] = EEPROM.read(40);
		//config.Gateway[1] = EEPROM.read(41);
		//config.Gateway[2] = EEPROM.read(42);
		//config.Gateway[3] = EEPROM.read(43);

		config.ssid = ReadStringFromEEPROM(64);
		config.password = ReadStringFromEEPROM(96);
		config.ntpServerName = ReadStringFromEEPROM(128);

		config.AutoTurnOn = EEPROM.read(300);
		config.AutoTurnOff = EEPROM.read(301);
		config.TurnOnHour = EEPROM.read(302);
		config.TurnOnMinute = EEPROM.read(303);
		config.TurnOffHour = EEPROM.read(304);
		config.TurnOffMinute = EEPROM.read(305);
		Serial.println("reading t1");
		config.temp1 = EEPROMReadlong(306);
		Serial.println("reading t2");
		config.temp2 = EEPROMReadlong(310);
		Serial.println("reading t3");
		config.temp3 = EEPROMReadlong(314);
		config.temp4 = EEPROMReadlong(318);
		config.temp5 = EEPROMReadlong(322);
		config.DeviceName= ReadStringFromEEPROM(326);
		config.AutoTurnOn2= EEPROM.read(346);
		config.AutoTurnOff2= EEPROM.read(347);
		config.TurnOnHour2= EEPROM.read(348);
		config.TurnOnMinute2= EEPROM.read(349);
		config.TurnOffHour2= EEPROM.read(350);
		config.TurnOffMinute2= EEPROM.read(351);
		//EEPROMwritearray(config.SensorID1, 352, 8);
		EEPROMreadarray(config.SensorID[0], 352, 8);
		EEPROMreadarray(config.SensorID[1], 360, 8);
		EEPROMreadarray(config.SensorID[2], 368, 8);
		EEPROMreadarray(config.SensorID[3], 376, 8);
		EEPROMreadarray(config.SensorID[4], 384, 8);
		config.SensName0 = ReadStringFromEEPROM(392);
		config.SensName1 = ReadStringFromEEPROM(412);
		config.SensName2 = ReadStringFromEEPROM(432);
		config.SensName3 = ReadStringFromEEPROM(452);
		config.SensName4 = ReadStringFromEEPROM(472);
		config.MaxTemperature = EEPROMReadlong(492);
		config.MidTemperature = EEPROMReadlong(496);
		return true;
	}
	else
	{
		Serial.println("Configurarion NOT FOUND!!!!");
		return false;
	}
}

/*
**
**  NTP
**
*/

const int NTP_PACKET_SIZE = 48;
byte packetBuffer[ NTP_PACKET_SIZE];
void NTPRefresh()
{




	if (WiFi.status() == WL_CONNECTED)
	{
		IPAddress timeServerIP;
		WiFi.hostByName(config.ntpServerName.c_str(), timeServerIP);
		//sendNTPpacket(timeServerIP); // send an NTP packet to a time server


		Serial.println("sending NTP packet...");
		memset(packetBuffer, 0, NTP_PACKET_SIZE);
		packetBuffer[0] = 0b11100011;   // LI, Version, Mode
		packetBuffer[1] = 0;     // Stratum, or type of clock
		packetBuffer[2] = 6;     // Polling Interval
		packetBuffer[3] = 0xEC;  // Peer Clock Precision
		packetBuffer[12]  = 49;
		packetBuffer[13]  = 0x4E;
		packetBuffer[14]  = 49;
		packetBuffer[15]  = 52;
		UDPNTPClient.beginPacket(timeServerIP, 123);
		UDPNTPClient.write(packetBuffer, NTP_PACKET_SIZE);
		UDPNTPClient.endPacket();


		delay(1000);

		int cb = UDPNTPClient.parsePacket();
		if (!cb) {
			Serial.println("NTP no packet yet");
		}
		else
		{
			Serial.print("NTP packet received, length=");
			Serial.println(cb);
			UDPNTPClient.read(packetBuffer, NTP_PACKET_SIZE); // read the packet into the buffer
			unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
			unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
			unsigned long secsSince1900 = highWord << 16 | lowWord;
			const unsigned long seventyYears = 2208988800UL;
			unsigned long epoch = secsSince1900 - seventyYears;
			UnixTimestamp = epoch;
		}
	}
}

void Second_Tick()
{
	strDateTime tempDateTime;
	AdminTimeOutCounter++;
	cNTP_Update++;
	UnixTimestamp++;
	ConvertUnixTimeStamp(UnixTimestamp +  (config.timezone *  360) , &tempDateTime);
	if (config.daylight) // Sommerzeit beachten
		if (summertime(tempDateTime.year,tempDateTime.month,tempDateTime.day,tempDateTime.hour,0))
		{
			ConvertUnixTimeStamp(UnixTimestamp +  (config.timezone *  360) + 3600, &DateTime);
		}
		else
		{
			DateTime = tempDateTime;
		}
	else
	{
			DateTime = tempDateTime;
	}
	Refresh = true;
}

void Half_Second_Tick()
{
	int state = digitalRead(D3);  // get the current state of GPIO1 pin
	digitalWrite(D3, !state);
}

#endif
