#include <Arduino.h>
#include "MCP6S2x.h"

#define ADC_RES 1023.0
#define V_REF 4.88
#define SAMPLES 40

float getMax();

uint8_t i;
uint8_t count = 0;
int readings[SAMPLES];
MCP6S2x amp = MCP6S2x();
MCP6S2x amp2 = MCP6S2x(A1, 49, 1);

void setup() {
  amp.setGain(GAIN_1X);

  amp2.setGain(GAIN_1X);

  for(i=0; i<SAMPLES; ++i)
    readings[i] = 0;

  // SETUP SERIAL MONITOR
  Serial.begin(9600);
}

void loop() {
  readings[count] = amp2.getValue();

  Serial.print("Max: ");
  Serial.print(getMax());
  Serial.println();

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
