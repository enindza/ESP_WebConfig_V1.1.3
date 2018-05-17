//
// Created by a on 24.12.2017..
//

#ifndef PRVI_TEST_BLINKPATTERN_H
#define PRVI_TEST_BLINKPATTERN_H

#include <inttypes.h>
#include <ESP8266WiFi.h>

class BlinkPattern
{
public:
    // Create an instance of the BlinkPattern library
    BlinkPattern();

    // Attach to a pin (and also sets initial state)
    void attach(uint8_t pin);

    // Attach to a pin (and also sets initial state) and sets pin to mode (INPUT/INPUT_PULLUP/OUTPUT)
    void attach(uint8_t pin, uint8_t mode);


    // create 8 bit pattern from 01111111, 00111111, 00011111 to 00000001 based on difference between MaxValue and Current Value
    // the main aim of this code is to visualise difference between  two values
    // like battery status, hot or cold
    // Returns resulted pattern
    // pattern is generated based on difference between MaxValue and CurrentValue
    // check for ValDifPrescaler for working range definition
    uint8_t BlinkPatternCreate(uint8_t MaxValue, uint8_t CurrentValue);

    // Manual set pattern, for error code or similar
    // example 0b01010101 or 0b00110011 or 0b0101000
    void BlinkPatternSet(uint8_t CurrentPattern);

    // true will invert output pin value
    void Invert(bool InvertOutput);

    //ValDifPrescaler value need to be in interval 0 - 7
    //0 - divide by 1, full pattern change occurs withih CurrentValue range of (MaxValue, MaxValue - 6)
    //1 - divide by 2, full pattern change occurs withih CurrentValue range of (MaxValue, MaxValue - 12)
    //2 - divide by 4, full pattern change occurs withih CurrentValue range of (MaxValue, MaxValue - 24)
    //3 - divide by 8, full pattern change occurs withih CurrentValue range of (MaxValue, MaxValue - 42)
    void ValDifPrescaler(uint8_t DivideByShift);

    // Prescaler will set TimeScale value, when Update() frequently, it will rally update only after TimeScale number of calls
    void Prescaler(uint8_t TimeScale);

    // update pattern value on selected output pin
    void Update();


protected:
    bool InvertOutput;
    bool Output;
    uint8_t DivideByShift;
    uint8_t TimeScale;
    uint8_t TimeScaleCounter;
    uint8_t CurrentPattern;
    uint8_t CurrentPatternBit;
    uint8_t state;
    uint8_t pin;
};



#endif //PRVI_TEST_BLINKPATTERN_H
