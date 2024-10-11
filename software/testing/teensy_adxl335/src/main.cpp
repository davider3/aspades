#include <Arduino.h>
#include <Wire.h>
#include <ADS1X15.h>

#define SAMPLES 100

ADS1115 adc(ADS1115_ADDRESS);
float conversionFactor;
int readings[SAMPLES];
int i;
float f; 

int getMax();

void setup() {

  Serial.begin(9600);

  Wire.begin();
  adc.begin();

  adc.setGain(0);

  conversionFactor = adc.toVoltage(1);
  f = adc.toVoltage(1); 
  
  analogReadAveraging(1);

}

void loop() {

  for(i=0; i<SAMPLES; ++i){
    readings[i] = adc.readADC(0);
  }

  Serial.print("ADS1115: "); Serial.print(f, 6);
  Serial.println();
  // Serial.print("ADC: "); Serial.print(analogRead(A0)*.003207, 6);
  // Serial.println(); Serial.println();

  delay(250);
  
}


int getMax(){
  int temp = 0;
  for(i=0; i<SAMPLES; ++i){
    if(readings[i] > temp){
      temp = readings[i];
    }
  }
  return temp;
}
