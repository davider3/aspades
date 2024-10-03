#include <Arduino.h>
#include <FreqMeasure.h>

void setup() {
  Serial.begin(9600);
  FreqMeasure.begin(); // PIN 22 on Teensy 4.0
}

double sum=0;
int count=0;

void loop() {
  if (FreqMeasure.available()) {
    // average several reading together
    sum = sum + FreqMeasure.read();
    count = count + 1;
    if (count > 30) {
      float frequency = FreqMeasure.countToFrequency(sum / count);
      Serial.println(frequency);
      sum = 0;
      count = 0;
    }
  }
}