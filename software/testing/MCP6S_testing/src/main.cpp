#include <Arduino.h>
#include "MCP6S2x.h"

#define ADC_RES 1023.0
#define V_REF 3.295
#define SAMPLES 40
#define PRINT_DELAY 2e6

float getMax();

uint8_t i;
uint8_t count = 0;
int readings[SAMPLES];
MCP6S2x amp = MCP6S2x(A0, 10, 1);
MCP6S2x amp2 = MCP6S2x(A1, 9, 1);
IntervalTimer timer;
volatile bool print;

void printIt(){
    print = true;
}

void setup() {
  amp.setGain(GAIN_8X);

  amp2.setGain(GAIN_8X);

  timer.begin(printIt, PRINT_DELAY);
  print = true;

  for(i=0; i<SAMPLES; ++i)
    readings[i] = 0;

  // SETUP SERIAL MONITOR
  Serial.begin(9600);
}

void loop() {
  readings[count] = amp2.getValue();

  if(print){
    Serial.print("Max: ");
    Serial.print(getMax());
    Serial.println();
    print = false;
  }


  count = (count + 1) % SAMPLES;
}

float getMax(){
    int temp = 0;
    for(i = 0; i < SAMPLES; ++i){
        if(readings[i] > temp)
            temp = readings[i];
    }

    return (temp/ADC_RES) * V_REF;
}
