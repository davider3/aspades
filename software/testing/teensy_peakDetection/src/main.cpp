#include <Arduino.h>

#define PRINT_DELAY 5e5
#define PIN A2

IntervalTimer timer;
volatile bool print;

void printIt(){
    print = true;
}

void setup() {
  analogReadAveraging(4);

  Serial.begin(9600);

  timer.begin(printIt, PRINT_DELAY);
  
}

void loop() {
  if(print){
    Serial.println((3.277/1023.0) * analogRead(PIN),4);
    print = false;
  }
}