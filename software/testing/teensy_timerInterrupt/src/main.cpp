#include <Arduino.h>
IntervalTimer myTimer;

const int ledPin = 13; 
volatile bool ledState = false; 

void toggleLED() {
  ledState = !ledState; 
  digitalWrite(ledPin, ledState); 
}

void setup() {
  pinMode(ledPin, OUTPUT); 
  myTimer.begin(toggleLED, 1000000);
}

void loop() {
  
}