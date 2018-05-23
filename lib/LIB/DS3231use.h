#include <Wire.h> // must be included here so that Arduino library object file references work
#include <RtcDS3231.h>

#define countof(a) (sizeof(a) / sizeof(a[0]))

void printDateTime(const RtcDateTime& dt)
{
    char datestring[20];

    snprintf_P(datestring,
            countof(datestring),
            PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
            dt.Month(),
            dt.Day(),
            dt.Year(),
            dt.Hour(),
            dt.Minute(),
            dt.Second() );
    Serial.print(datestring);
}

void ScanI2C(){
  Serial.print("I2C scanning .......");
  Wire.begin();
  byte count = 0;
  for (byte i = 1; i < 120; i++)
  {
    Wire.beginTransmission (i);
    if (Wire.endTransmission () == 0)
      {
      Serial.print ("Found address: ");
      Serial.print (i, DEC);
      Serial.print (" (0x");
      Serial.print (i, HEX);
      Serial.println (")");
      count++;
      delay (1);  // maybe unneeded?
      } // end of good response
  } // end of for loop
  Serial.println ("Done.");
  Serial.print ("Found ");
  Serial.print (count, DEC);
  Serial.println (" device(s).");
}

bool ScanDS3231(){
  //Serial.print("Scanning for timer DS3231");
  Wire.begin();
  Wire.beginTransmission (104);
  if (Wire.endTransmission () == 0){
      //Serial.println("Found DS3231 address");
      return true;
  } // end of good response
  return false;
}

void RTCSetup(){
  //--------RTC SETUP ------------

  Rtc.Begin();

  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
  printDateTime(compiled);
  Serial.println();

  if (!Rtc.IsDateTimeValid())
  {
      // Common Cuases:
      //    1) first time you ran and the device wasn't running yet
      //    2) the battery on the device is low or even missing

      Serial.println("RTC lost confidence in the DateTime!");

      // following line sets the RTC to the date & time this sketch was compiled
      // it will also reset the valid flag internally unless the Rtc device is
      // having an issue

      //Rtc.SetDateTime(compiled);
  }

  if (!Rtc.GetIsRunning())
  {
      Serial.println("RTC was not actively running, starting now");
      Rtc.SetIsRunning(true);
  }

  //RtcDateTime now = Rtc.GetDateTime();

  // never assume the Rtc was last configured by you, so
  // just clear them to your needed state
  Rtc.Enable32kHzPin(false);
  Rtc.SetSquareWavePin(DS3231SquareWavePin_ModeNone);
}

void DS3231update(long epoch){
  //set ds3231 time
  RtcDateTime timeToSet;
  timeToSet.InitWithEpoch32Time(epoch);
  Rtc.SetDateTime(timeToSet);
  //print updated time
  RtcDateTime now = Rtc.GetDateTime();
  Serial.print("DS3231 updated time is:");
  printDateTime(now);
}
