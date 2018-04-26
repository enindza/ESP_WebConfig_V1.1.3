
#pragma once


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
	float	Temperatura[5]; //ocitane temperature senzora prema
	boolean SensorConnected[5];
	String SensName0;
	String SensName1;
	String SensName2;
	String SensName3;
	String SensName4;
	byte LinkID[5];
	//	Boiler termperature
	long MaxTemperature;
	long MidTemperature;
	byte Mode; // 0 - normal operation, 1 - single mid temperature, 2 - single max temperature
	bool PowerOutput;
	bool TimerOn;
	bool Test;
	bool NTPUpdateStatus; //ntp update indicator for google sheet, set after update and reset after httpsredirect
	//long HoldMidTemperature; //minutes to hold mid temperature
}   config;

struct strConfig2{
float	Temperatura[5];
	byte tesstt;
} config2;

struct strIFTTT{
  uint8_t	RetryCounter; //number of current retry
	long RetryDelayExpire; //Time for next IFTTT send
  uint8_t Success; // counts number of successful retry
  uint8_t Code; // 0- reboot, 1 - temperature reached, 2 Sensor Error, 3 Hardware error
} IFTTTconfig;
