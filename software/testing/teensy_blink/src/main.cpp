#include <Arduino.h>

#define LED 13

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(500000);
}

void loop() {
  digitalWrite(LED, HIGH);
  Serial.println("Blink!");
  delay(100);
  digitalWrite(LED, LOW);
  delay(500);
}