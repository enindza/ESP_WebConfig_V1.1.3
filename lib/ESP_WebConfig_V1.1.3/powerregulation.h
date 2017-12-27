
#ifndef powerregulation_h
#define powerregulation_h

uint8_t BlinkProfile(uint8_t Uppertemperature){
  uint8_t curenttemp = sensors.getTempC(config.SensorID[0]);
	uint8_t resulta = ((curenttemp - MINIMALTEMPERATURE) * TICKPOWERCOUNTER) / (Uppertemperature - MINIMALTEMPERATURE);
	Serial.print("profile temperature:");
	Serial.println(resulta,DEC);
	Serial.print("profile temperature byte:");
	uint8_t resultb = resulta;
	Serial.println(resultb,DEC);
	return resultb;
}

void PowerControl(){
  //Serial.print("Power control");
  if (millis() - lastPowerRequest >= 1000){
    //Serial.print("Power control ");
    uint8_t profile = BlinkProfile(config.MidTemperature);
    lastPowerRequest = millis();
  }

}

#endif
