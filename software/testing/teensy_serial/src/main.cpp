#include <Arduino.h>

void setup() {
  Serial.begin(9600);
}

void loop() {

  for(int i=1; i<11; ++i){
    Serial.println(i);
    delay(250);
  }
}
