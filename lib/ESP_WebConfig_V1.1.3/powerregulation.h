
#ifndef powerregulation_h
#define powerregulation_h

/*
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
*/


//
// calculate initial on/off state based on timer data.
// program searches for closest lower timer on/off value to variable Current
//
boolean CalculateTimerState(boolean Timer1Enable, boolean Timer2Enable, uint16_t On1, uint16_t On2, uint16_t Off1, uint16_t Off2, uint16_t Current){
    boolean state = false;
    uint16_t ClosestLow;
    ClosestLow = 0;
    if (Timer1Enable) {
        if (Current > On1 and On1 > ClosestLow) { ClosestLow = On1; state = true;}
        if (Current > Off1 and Off1 > ClosestLow) { ClosestLow = Off1; state = false;}
    }
    if(Timer2Enable) {
        if (Current > Off2 and Off2 > ClosestLow) { ClosestLow = Off2; state = false;}
        if (Current > On2 and On2 > ClosestLow) { ClosestLow = On2; state = true;}
    }
    if (ClosestLow == 0){
        if (Timer1Enable and (On1 > Off1)){ state = true;}
        if (Timer1Enable and (On1 > Off1)){ state = true;}
        if(Timer1Enable and Timer2Enable) {
            if (max(On1, On2) > max(Off1, Off2)) { state = true; } else {state = false;}
        }
    }
    return state;
}



//  moguca stanja
//  0. automatski rad (on)(vreme nije azurirano - brzo blinkanje)
//  1.
//  2. stanje tajmera, ukljucen ili iskljucen
//  3. grejanje do config.MidTemperature
//  4. grejanje do config.MaxTemperature

/*
  if(TimerState == true){   //tajmer ukazuje na to da treba da bude upaljen
    if(NeedTimerUpdate){SetPatternErrorCode;}
  }

//
//
*/


void PowerControl(){
  long TempLimit;
  //Serial.print("Power control");
  if (millis() - lastPowerRequest >= 1000){

    //Serial.print("Power control ");
    //pattern.BlinkPatternCreate(config.MidTemperature, config.Temperatura[0]);
    //uint8_t profile = BlinkProfile(config.MidTemperature);
    lastPowerRequest = millis();

    // 0 - normal operation, 1 - single mid temperature, 2 - single max temperature 3 of mode
    if (config.Mode > 0){
      // Single heat Mode
      if(config.Mode == 3){config.PowerOutput = FALSE; pattern.BlinkPatternSet(0b00000000);}
      else{
        if (config.Mode == 1) {pattern.BlinkPatternCreate(config.MidTemperature, config.Temperatura[0]); TempLimit = config.MidTemperature;}
        else{pattern.BlinkPatternCreate(config.MaxTemperature, config.Temperatura[0]); TempLimit = config.MaxTemperature;}
        Serial.print("Mode: "); Serial.print(config.Mode, DEC); Serial.print("     TempLimit: "); Serial.println(TempLimit, DEC);
        if(config.Temperatura[0] > TempLimit){
          // single heat limit reached
          config.Mode = 0;
          config.PowerOutput = FALSE;
        } else {config.PowerOutput = TRUE;}
      }
    }
    else{
      // normal timer operated Mode
      if (firstStart){pattern.BlinkPatternSet(0b10101010); config.PowerOutput = TRUE;}
      else{
        pattern.BlinkPatternSet(0b11111111);
        if (config.TimerOn){
          if(config.Temperatura[0] < config.MaxTemperature){config.PowerOutput = TRUE;}
          else {config.PowerOutput = FALSE;}
        }
        else{
          config.PowerOutput = FALSE;
        }
      }
    }
    digitalWrite(HEATERINDICATOR, config.PowerOutput);
    //Serial.print("PowerOutput: "); Serial.println(config.PowerOutput, DEC);
    //Serial.print("TimerON: "); Serial.println(config.TimerOn, DEC);
    Serial.print("TIME "); Serial.print(DateTime.hour, DEC); Serial.print (":");
    Serial.print(DateTime.minute,DEC); Serial.print ( ":");
    Serial.println(DateTime.second,DEC);
    //Serial.print("firstStart: "); Serial.println(firstStart,DEC);
    //Serial.print("firstStartRefresh: "); Serial.println(firstStartRefresh,DEC);
    //Serial.print("TimeNeverUpdated:"); Serial.println(TimeNeverUpdated, DEC);
    HTTPSredirectFirstRun();
    HTTPSredirectloop();
  }
}



#endif
