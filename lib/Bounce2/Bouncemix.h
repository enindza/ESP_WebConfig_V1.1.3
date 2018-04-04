/*
  The MIT License (MIT)

  Copyright (c) 2013 thomasfredericks

  Permission is hereby granted, free of charge, to any person obtaining a copy of
  this software and associated documentation files (the "Software"), to deal in
  the Software without restriction, including without limitation the rights to
  use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
  the Software, and to permit persons to whom the Software is furnished to do so,
  subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
  FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
  COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
  IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
  CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/* * * * * * * * * * * * * * * * * * * * * * * * * * * *
  Main code by Thomas O Fredericks (tof@t-o-f.info)
  Previous contributions by Eric Lowry, Jim Schimpf and Tom Harkaway
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
  #ifndef Bouncemix_h
  #define Bouncemix_h

#include <inttypes.h>
//#define DOUBLECLICKTIME 40
//#define LONGCLICKTIME 100


class Bouncemix
{
 public:
    // Create an instance of the bounce library
    Bouncemix();

    // Attach to a pin (and also sets initial state)
    void attach(int pin);

    // Attach to a pin (and also sets initial state) and sets pin to mode (INPUT/INPUT_PULLUP/OUTPUT)
    void attach(int pin, int mode);

    // Sets the debounce interval ONLY FOR REFFERENCE DELETE
    void interval(uint16_t interval_millis);

    //  reset clear indicators
    void reset();

    // Updates the pin
    // Returns 1 if the state changed
    // Returns 0 if the state did not change
    bool update();

    // Returns the updated pin state
    bool read();

    // Returns the falling pin state
    bool fell();

    // Returns the rising pin state
    bool rise();

    void testprint();

    bool longpress();

    bool doubleclick();

 protected:
    unsigned long previous_millis;
    uint16_t interval_millis;
    uint8_t state;
    uint8_t pin;
    bool T0; //today
    bool T1; // yesterday
    bool T2; // day before yesterday
    bool SON; //switch on
    uint8_t TONC; //timer for switch on state
    uint8_t TOFFC; // timer for switch off state
    bool SRise; // rising edge indicator
    bool SFell; // falling edge indicator
    bool SDouble; //double switch indicator
    bool SLong; //long press indicator
    uint8_t DOUBLECLICKTIME;
    uint8_t LONGCLICKTIME;
};
#endif
