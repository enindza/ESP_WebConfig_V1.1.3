// Please read Bounce2.h for information about the liscence and authors

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "Bouncemix.h"

Bouncemix::Bouncemix()
    : previous_millis(0)
    , interval_millis(10)
    , state(0)
    , pin(0)
    , T0(false)  //today
    , T1(false)  // yesterday
    , T2(false)  // day before yesterday
    , SON(false) // switch on debounced
    , TONC(0)  //timer for switch on state
    , TOFFC(0) // timer for switch off state
    , SRise(false) // rising edge indicator
    , SFell(false) // falling edge indicator
    , SDouble(false) //double switch indicator
    , SLong(false) //long press indicator
    , DOUBLECLICKTIME(40)
    , LONGCLICKTIME(100)
{}

void Bouncemix::attach(int pin) {
    this->pin = pin;
}

void Bouncemix::attach(int pin, int mode){
    pinMode(pin, mode);
    this->attach(pin);
}

void Bouncemix::interval(uint16_t interval_millis)
{
    this->interval_millis = interval_millis;
}

bool Bouncemix::update()
{
    // Read the state of the switch in a temporary variable.
    bool T0 = !digitalRead(pin);
    //Serial.print("switch read as: "); Serial.println(T0, DEC);

    if (T0 == T1){ // if there was the change wait next call
    //Serial.println("last two of the same kind");
      if (T0 == true){
          //Serial.println("kind ON");
          SON = true;
          TONC++;
          if (T2 == false){ //check if the change is fresh
            // SRise remains true until check or level change
            SRise = true;
            if((TOFFC < DOUBLECLICKTIME + 20) and (TONC < DOUBLECLICKTIME)){SDouble = true;}
            TONC = 0;
            //Serial.print("set rising edge "); Serial.println(SRise,DEC); Serial.print(" TONC is "); Serial.println(TONC);
          }
          if(TONC > LONGCLICKTIME){SLong = true;}
          if (TONC == 255){TONC = 254;}
      }
      else{ // Today and yesterday are false, swith is open
        //Serial.println("kind OFF");
        SON = false;
        TOFFC++;
        if (T2 == true){ // check if change is  fresh and set SFall
          SFell = true;
          TOFFC = 0;
          //Serial.print("set falling edge "); Serial.println(SFell,DEC); Serial.print(" TOFFC is "); Serial.println(TOFFC);
        }
        if(TOFFC == 255){TOFFC = 254;}
      }
    }
    //
    T2 = T1;
    T1 = T0;

    if (T2 == T1){
      //Serial.print ("return TRUE ********* ");
      //Serial.println(SON,DEC);
      return true;
    }
    else {
      //Serial.print ("return FALSE ********* ");
      //Serial.println(SON,DEC);
      return false;
    }
}

bool Bouncemix::read()
{
    return SON;
}

bool Bouncemix::rise()
{
  boolean ret;
  ret = SRise;
  SRise = false;
  return ret;
}

bool Bouncemix::fell()
{
  boolean ret;
  ret = SFell;
  SFell = false;
  return ret;
}

bool Bouncemix::longpress()
{
    return SLong;
}

bool Bouncemix::doubleclick()
{
    return SDouble;
}

void Bouncemix::reset(){
  TONC = 0;  //timer for switch on state
  TOFFC = 0; // timer for switch off state
  SRise = false; // rising edge indicator
  SFell = false; // falling edge indicator
  SDouble = false; //double switch indicator
  SLong = false; //long press indicator
}

void Bouncemix::testprint()
{
  Serial.print("T0: ");
  Serial.println(T0,DEC);
  Serial.print("T1: ");
  Serial.println(T1,DEC);
  Serial.print("T2: ");
  Serial.println(T2,DEC);
  Serial.print("SON: ");
  Serial.println(SON,DEC);
  Serial.print("TONC: ");
  Serial.println(TONC,DEC);
  Serial.print("TOFFC: ");
  Serial.println(TOFFC,DEC);
  Serial.print("SRise: ");
  Serial.println(SRise,DEC);
  Serial.print("SFell: ");
  Serial.println(SFell,DEC);
  Serial.print("SDouble: ");
  Serial.println(SDouble,DEC);
  Serial.print("SLong: ");
  Serial.println(SLong,DEC);
}
