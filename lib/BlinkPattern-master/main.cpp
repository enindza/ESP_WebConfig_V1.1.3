#include <iostream>
using namespace std;
#include <bitset>
#include "lib/BlinkPattern.h"
//#include "BlinkPattern.h"

#define MaxTemperature 72
#define LED_PIN 13


BlinkPattern pattern = BlinkPattern();


void TestPatternCreation(){
    for( int a = 80; a > 1 ; a = a - 1 ) {
        uint8_t temp;
        temp = pattern.BlinkPatternCreate(MaxTemperature, a);
        cout << a << " " << std::bitset<8>(temp) << ".\n";
    }
}
void TestPatternDisplay(){
    for( int a = 0; a < 80 ; a = a + 1 ) {
        uint8_t temp;
        pattern.Invert(false);
        pattern.ValDifPrescaler(3);
        //pattern.attach(D0,OUTPUT);
        pattern.BlinkPatternSet(0b00110001);
        pattern.Prescaler(1);
        pattern.Update();
        //cout << a << " " << std::bitset<8>(temp) << ".\n";
    }

}

int main() {
    TestPatternCreation();
    TestPatternDisplay();
    return 0;
}


