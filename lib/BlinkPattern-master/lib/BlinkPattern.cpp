//
// Created by a on 24.12.2017..
//

// Please read BlinkPattern.h for information about the license and authors

//#include "BlinkPattern.h"
#include "BlinkPattern.h"
//#include <iostream>
//using namespace std;
//#include <bitset>

#ifndef bitRead
#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#endif

#ifndef invertOutput
#define invertOutput(val1,val2)((val2 == 1)?(!val1):(val1))
#endif


BlinkPattern::BlinkPattern()
        : InvertOutput(false)
        , Output(false)
        , DivideByShift(3)
        , TimeScale(2)
        , TimeScaleCounter(0)
        , CurrentPattern(31)
        , CurrentPatternBit(0)
        , state(0)
        , pin(0)
{}

void BlinkPattern::attach(uint8_t pin) {
    this->pin = pin;
}

void BlinkPattern::attach(uint8_t pin, uint8_t mode){
    this->pin = pin;
    pinMode(pin, mode);
}

uint8_t BlinkPattern::BlinkPatternCreate(uint8_t MaxValue, uint8_t CurrentValue){
    uint8_t result;
    uint8_t result2;
    if (CurrentValue < MaxValue){
        result = MaxValue - CurrentValue;
        result2 = result >> DivideByShift;
    }
    else{
        result2 = 0;
    }
    result = (255 >> result2) >> 1;
    if (result == 0){ result = 1;}
    //if (InvertOutput){result = result ^ 255;}
    this->CurrentPattern = result;
    return  result;
}

void BlinkPattern::BlinkPatternSet(uint8_t CurrentPattern)
{
    this->CurrentPattern = CurrentPattern;
}


void BlinkPattern::Invert(bool InvertOutput)
{
    this->InvertOutput = InvertOutput;
}

void BlinkPattern::ValDifPrescaler(uint8_t DivideByShift)
{
    if (DivideByShift > 7){DivideByShift = 7;}
    this->DivideByShift = DivideByShift;
}

void BlinkPattern::Prescaler(uint8_t TimeScale)
{
    this->TimeScale = TimeScale;
}

void BlinkPattern::Update()
{
    TimeScaleCounter++;
    //cout << "check ";
    if (TimeScaleCounter >= TimeScale){
        TimeScaleCounter = 0;
        CurrentPatternBit++;
        //cout << "pass" << ".\n";
        if (CurrentPatternBit > 7){
            CurrentPatternBit = 0;
            //cout << "***New cycle***" << std::bitset<8>(CurrentPattern) << ".\n";
        }
        if (Output != bitRead(CurrentPattern, CurrentPatternBit)){
            Output = !Output;
            //cout << "write to port";
            digitalWrite(pin, invertOutput(Output, InvertOutput));
        }
        //cout << (int) CurrentPatternBit << " " << invertOutput(Output, InvertOutput) << ".\n";
    }
    this->TimeScaleCounter = TimeScaleCounter;
}
