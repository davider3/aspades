#include <Arduino.h>
#include "MCP6S2x.h"

#define ADC_RES 1023.0
#define V_REF 3.33
#define SAMPLES 255
#define GREEN 1
#define BLUE 2

uint8_t count = 0;
MCP6S2x amp = MCP6S2x(A0, 10, 1);
MCP6S2x amp2 = MCP6S2x(A1, 9, 1);
enum States {INITIAL_CHECK, WAITING, GET_AMPLITUDE};
States state = INITIAL_CHECK;
bool exitLoop;


void setup() {
  analogReadAveraging(1);

  amp.setGain(GAIN_2X);
  amp2.setGain(GAIN_1X);

  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  digitalWrite(GREEN, HIGH);
  digitalWrite(BLUE, HIGH);
  delay(500);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);

  // SETUP SERIAL MONITOR
  Serial.begin(9600);
}

void loop() {
  // readings[count] = amp2.getValue();
  int temp = amp2.getValue();
  int amplitude = temp;
  exitLoop = false;
  count = 0;
  while(1){
    switch(state) {

      case INITIAL_CHECK:
        temp = amp2.getValue();
        if(temp > amplitude + 5){
          state = GET_AMPLITUDE;
        } else{
          state = WAITING;
        }
        break;

      case WAITING:
        if(temp <= amplitude){
          count = 0;
          temp = amp2.getValue();
        } else if(count > 10){
          state = GET_AMPLITUDE;
          count = 0;
          break;
        } else{
          count += 1;
          temp = amp2.getValue();
        }
        break;

      case GET_AMPLITUDE:
        if(temp >= amplitude){
          count = 0;
          amplitude = temp;
          temp = amp2.getValue();
        } else if(count > 10){
          state = INITIAL_CHECK;
          delay(1);
          exitLoop = true;
          break;
        } else{
          count += 1;
          temp = amp2.getValue();
        }
        break;

    }

    if(exitLoop) break;
  }

  Serial.print("Max: ");
  Serial.print(amplitude*.003152);
  Serial.println();

}