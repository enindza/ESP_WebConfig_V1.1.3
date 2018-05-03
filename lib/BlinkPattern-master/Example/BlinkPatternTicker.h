BlinkPattern pattern = BlinkPattern();

void Half_Second_Tick()
{
	//Serial.printf("Half_Second_Tick");
	//int state = digitalRead(HEATERINDICATOR);  // get the current state of GPIO1 pin
	//digitalWrite(HEATERINDICATOR, !state);
}

void Debounce_Tick()
{
	debouncer.update();
	// Get the updated value :
  bool value = debouncer.read();
	pattern.Update();

  //serial.print("vrednost debouncer.read je:");
  //serial.println(value);
  // Turn on or off the LED as determined by the state :
	//if (value == true){
  //  digitalWrite(LED_PIN, 1 );
  //}
  //else{
  //  digitalWrite(LED_PIN, 0 );
  //}


	//
	/*
	Tickercounter++;
	if(Tickercounter == 25){
		Half_Second_Tick();
	}
	if (Tickercounter == 50){
		TickCounter = 0;
		Second_Tick();
		Serial.print("Tickertime ***");
		unsigned long time1 = millis();
		Serial.println(time1);
	}
	*/
}
