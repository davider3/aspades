#include <Arduino.h>
#include <Wire.h>
#include <ADS1X15.h>
#include "MCP6S2x.h"
#include "LoopAntenna.h"

#define PRINT_DELAY 5e5 // 500ms

MCP6S2x* amp1 = new MCP6S2x(A0, 10, 1);
MCP6S2x* amp2 = new MCP6S2x(A1, 9, 1);
ADS1115* adc= new ADS1115(ADS1115_ADDRESS);
LoopAntenna ant = LoopAntenna(amp1, amp2, CH0, CH0);
LoopAntenna ant2 = LoopAntenna(amp1, amp2, CH1, CH0);
IntervalTimer timer;

float conversionFactor;
volatile bool print;

void printIt(){
    print = true;
}

void setup() {

    Serial.begin(9600);
    analogReadAveraging(1);

    print = true;

    timer.begin(printIt, 500000);
}

void loop() {

    ant.measureAmplitude();
    ant2.measureAmplitude();

    if(print){
        Serial.print("Channel 1: ");Serial.print(ant.getAmplitude()*.003207);
        Serial.print("\tGain: "); Serial.print(ant.getTotalGain());
        Serial.println();
        Serial.print("\tOriginal Amplitude: "); Serial.print(ant.getOGAmplitude(), 6);
        Serial.println();
        Serial.print("Channel 2: ");Serial.print(ant2.getAmplitude()*.003207);
        Serial.print("\tGain: "); Serial.print(ant2.getTotalGain());
        Serial.println();
        Serial.print("\tOriginal Amplitude: "); Serial.print(ant2.getOGAmplitude(), 6);
        Serial.println();
        print = false;
    }
}
