// Include the libraries we need
#include <OneWire.h>
#include <DallasTemperature.h>



// Data wire is plugged into port 2 on the Arduino+
// original #define ONE_WIRE_BUS 2
#define ONE_WIRE_BUS D2
#define TEMPERATURE_PRECISION 9

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

int numberOfDevices; // Number of temperature devices found

DeviceAddress tempDeviceAddress; // We'll use this variable to store a found device address

//int  resolution = 12;
unsigned long lastTempRequest = 0;
int  delayInMillis = 0;
float temperature = 0.0;
int  idle = 0;
// pomoc BRISI kasnije
long	SensorTemperature[5];
//byte  SensorID[5][8];

// function to print the temperature for a device
void printTemperature(DeviceAddress deviceAddress)
{
  float tempC = sensors.getTempC(deviceAddress);
  Serial.print("Temp C: ");
  Serial.print(tempC);
}

// function to print a device address
void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}
/*
Dallas Temperature IC Control Library Demo
Locating devices...Found 2 devices.
Parasite power is: OFF
Found device 0 with address: 28FFEC96B3160424
Setting resolution to 9
Found device 1 with address: 28FF7388B3160352
Setting resolution to 9
Requesting temperatures...DONE
*/

// test hex conversion
//
//the calling
//byte buf[] = {0,1,10,11};
//char *result;
//String rezultat;
//rezultat = bin_to_strhex(buf, sizeof(buf));
//Serial.println("rezultat test konverzije 0,1,10,11:");
//Serial.println(rezultat);
//free(result);

String bin_to_strhex(byte Idarray[], byte ArrayLen)
{
    Serial.println("bin_to_hex");
    static const char table[] = "0123456789abcdef";
		String tempers;
    for (byte k = 0; k<ArrayLen; k++)
    {
        byte c = Idarray[k];
				tempers = tempers+ table[c >> 4];
				tempers = tempers + table[c & 0x0f];
    }
	return tempers;
}

int GetSensorID(byte SensorID[5][8], DeviceAddress deviceAddress){
  for(int j=0;j<5; j++){
    for(int i=0;i<8; i++){
      if (SensorID[j][i] == deviceAddress[i]){
        if (i == 4) {return j;}
      }
      else {break;}
    }
  }
  return 99;
}

void CopySensorAddress(byte SensorID[5][8], int i, DeviceAddress deviceAddress){
  Serial.println("Copy Sensor Address");
  for(int j=0;j<8; j++){
    SensorID[i][j] = tempDeviceAddress[j];
  }
  //test brisi
  String rezultat;
  rezultat = bin_to_strhex(SensorID[i], sizeof(SensorID[i]));
  Serial.print("rezultat test konverzije ID:");
  Serial.println(i,DEC);
  Serial.println(rezultat);
  Serial.print("GetsensorID:");
  Serial.println(GetSensorID(SensorID, SensorID[i]), DEC);

  //Serial.println("copysensoraddress passed");
}

void I2CDallasSetup(){
  Serial.println("Dallas Temperature IC Control Library Demo");

  // Start up the library
  sensors.begin();

  // Grab a count of devices on the wire
  numberOfDevices = sensors.getDeviceCount();

/* locate devices on the bus
  Serial.print("Locating devices...");

  Serial.print("Found ");
  Serial.print(numberOfDevices, DEC);
  Serial.println(" devices.");
*/
  // report parasite power requirements

  // parasite power
  /*
  Serial.print("Parasite power is: ");
  if (sensors.isParasitePowerMode()) Serial.println("ON");
  else Serial.println("OFF");
*/

  // Loop through each device, print out address
  for(int i=0;i<numberOfDevices; i++)
  {
    // Search the wire for address
    if(sensors.getAddress(tempDeviceAddress, i))
    {
      //SensorID[i];
      /*Serial.print("Found device ");
      Serial.print(i, DEC);
      Serial.print(" with address: ");
      printAddress(tempDeviceAddress);
      Serial.println();*/

      /*Serial.print("Setting resolution to ");
      Serial.println(TEMPERATURE_PRECISION, DEC);*/

      // set the resolution to TEMPERATURE_PRECISION bit (Each Dallas/Maxim device is capable of several different resolutions)
      sensors.setResolution(tempDeviceAddress, TEMPERATURE_PRECISION);

      // Serial.print("Resolution actually set to: ");
      //Serial.print(sensors.getResolution(tempDeviceAddress), DEC);
      //Serial.println();
    }else{
      Serial.print("Found ghost device at ");
      Serial.print(i, DEC);
      Serial.print(" but could not detect address. Check power and cabling");
    }
  }
  sensors.setWaitForConversion(false);
  sensors.requestTemperatures();
  //delayInMillis = 750 / (1 << (12 - TEMPERATURE_PRECISION));
  delayInMillis = 1000;
  Serial.print("Delay in millis:");
  Serial.println(delayInMillis, DEC);
  lastTempRequest = millis();
  pinMode(D4, OUTPUT);
}


void I2CDallasLoop(){
  //test waited long enough
  if (millis() - lastTempRequest >= delayInMillis) // waited long enough??
  {
    Bouncemixutest();
    
    digitalWrite(D4, LOW);

    // Loop through each device, print out temperature data
    for(int i=0;i<numberOfDevices; i++)
    {
      // Search the wire for address
      if(sensors.getAddress(tempDeviceAddress, i))
      {
        // Output the device ID
        Serial.print("Temperature for device: ");
        Serial.println(i,DEC);
        config.LinkID[i] = GetSensorID(config.SensorID, tempDeviceAddress);
        //CopySensorAddress(config.SensorID, i, tempDeviceAddress);
        Serial.print("CopySensorAddress passed");
        // It responds almost immediately. Let's print out the data
        printTemperature(tempDeviceAddress); // Use a simple function to print out the data
      }
    //else ghost device! Check your power requirements and cabling
    yield();
    }

    //Serial.print(" Temperature: ");
    //temperature = sensors.getTempCByIndex(0);
    //Serial.println(temperature, resolution - 8);
    //Serial.print("  Resolution: ");
    //Serial.println(resolution);
    Serial.print("Idle counter: ");
    Serial.println(idle);
    Serial.println();

    idle = 0;

    // immediately after fetching the temperature we request a new sample
    // in the async modus
    // for the demo we let the resolution change to show differences
    //resolution++;
    //if (resolution > 12) resolution = 9;
    //sensors.setResolution(tempDeviceAddress, resolution);
    //
    sensors.requestTemperatures();
    //delayInMillis = 750 / (1 << (12 - resolution));
    lastTempRequest = millis();
  }
  //check idle time, set diode
  digitalWrite(D4, HIGH);
  idle++;
}
