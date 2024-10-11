#include <Arduino.h>
#include <Wire.h>
#include "MCP6S2x.h"
#include "LoopAntenna.h"

#define PRINT_DELAY 2e6
#define DEBUG_CH0 true
#define DEBUG_CH1 false
#define DEBUG_CH2 false

MCP6S2x* amp1 = new MCP6S2x(A0, 10, 1);
MCP6S2x* amp2 = new MCP6S2x(A1, 9, 1);
LoopAntenna ant = LoopAntenna(amp1, amp2, CH0, CH0);
LoopAntenna ant2 = LoopAntenna(amp1, amp2, CH1, CH0);
LoopAntenna ant3 = LoopAntenna(amp1, amp2, CH2, CH0);
IntervalTimer timer;

volatile bool print;

void printIt(){
    print = true;
}

void setup() {

    if(DEBUG_CH0 || DEBUG_CH1 || DEBUG_CH2){
        Serial.begin(9600);
        timer.begin(printIt, PRINT_DELAY);
    }

    analogReadAveraging(4);

    print = false;

}

void loop() {

    ant.measureAmplitude();
    // ant2.measureAmplitude();
    // ant3.measureAmplitude();

    if(print){
        if(DEBUG_CH0){
            Serial.print("Channel 1: ");Serial.print(ant.getAmplitude()*ADC_CONVERT);
            Serial.print("\tGain: "); Serial.print(ant.getTotalGain());
            Serial.println();
            Serial.print("\tOriginal Amplitude: "); Serial.print(ant.getOGAmplitude(), 6);
            Serial.println();
        }
        if(DEBUG_CH1){
            Serial.print("Channel 2: ");Serial.print(ant2.getAmplitude()*ADC_CONVERT);
            Serial.print("\tGain: "); Serial.print(ant2.getTotalGain());
            Serial.println();
            Serial.print("\tOriginal Amplitude: "); Serial.print(ant2.getOGAmplitude(), 6);
            Serial.println();
        }
        if(DEBUG_CH2){
            Serial.print("Channel 3: ");Serial.print(ant3.getAmplitude()*ADC_CONVERT);
            Serial.print("\tGain: "); Serial.print(ant3.getTotalGain());
            Serial.println();
            Serial.print("\tOriginal Amplitude: "); Serial.print(ant3.getOGAmplitude(), 6);
            Serial.println();
        }
        Serial.println();
        print = false;
    }
}
