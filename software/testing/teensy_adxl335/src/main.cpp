#include <Arduino.h>
#include <Wire.h>
#include <ADS1X15.h>

ADS1115 adc(ADS1115_ADDRESS);
float conversionFactor;

void setup() {

  Serial.begin(9600);

  Wire.begin();
  adc.begin();

  adc.setGain(1);

  conversionFactor = adc.toVoltage(1);
  
  analogReadAveraging(1);
}

void loop() {

  Serial.print("ADS1115: "); Serial.print(adc.readADC(0));
  Serial.println();
  // Serial.print("ADC: "); Serial.print(analogRead(A0)*.003207, 6);
  // Serial.println(); Serial.println();

  delay(250);
  
}
