#include <Arduino.h>
#include "MCP6S2x.h"

void set1Gain(int);
void set2Gain(int);

MCP6S2x* amp1 = new MCP6S2x(A0, 10, 1);
MCP6S2x* amp2 = new MCP6S2x(A1, 9, 1);
String temp = "";
bool inputComplete = false;

enum STATES {SETUP, CONTROL1, CONTROL2};
STATES state = SETUP;

void setup() {

  Serial.begin(9600);
  while(!Serial);
  Serial.println("\n\nHow many amplifiers are you using?");

  amp1->setGain(GAIN_1X);
  amp2->setGain(GAIN_1X);

}

void loop() {
  switch(state){

    case SETUP:
      if (inputComplete) {
        temp = temp.trim();
        if (temp == "1") {
          Serial.println("Controlling 1 amp\n");
          state = CONTROL1;
          Serial.println("You may now type the Gain value that you want for your amp");
          Serial.println("Valid Values are 1, 2, 4, 5, 8, 10, 16, 32");

        } else if (temp == "2") {
          Serial.println("Controlling 2 amps\n");
          state = CONTROL2;
          Serial.println("You may now type the total Gain value that you want for both amps");
          Serial.println("Valid Values are 1, 2, 4, 5, 8, 10, 16, 20, 25, 32, 40, 50, 64, 80, 100, 128, 160, 256, 320, 512, 1024");

        } else {
          Serial.println("Invalid syntax");
        }
        inputComplete = false;
        temp = "";
        Serial.println();
      }
      break;

    case CONTROL1:
      if(inputComplete){
        temp = temp.trim();
        set1Gain(temp.toInt());
        temp = "";
        inputComplete = false;
      }

      break;

    case CONTROL2:
      if(inputComplete){
        temp = temp.trim();
        set2Gain(temp.toInt());
        temp = "";
        inputComplete = false;
      }

      break;
  }
}

void set1Gain(int gain){
  switch(gain){
    case 1:
      amp1->setGain(GAIN_1X);
      break;

    case 2:
      amp1->setGain(GAIN_2X);
      break;

    case 4:
      amp1->setGain(GAIN_4X);
      break;

    case 5:
      amp1->setGain(GAIN_5X);
      break;

    case 8:
      amp1->setGain(GAIN_8X);
      break;

    case 10:
      amp1->setGain(GAIN_10X);
      break;

    case 16:
      amp1->setGain(GAIN_16X);
      break;

    case 32:
      amp1->setGain(GAIN_32X);
      break;

    default:
      Serial.println("Invalid syntax");
      break;
  }
}

void set2Gain(int gain){
  switch(gain) {
        case 1:
            amp1->setGain(GAIN_1X);
            amp2->setGain(GAIN_1X);
            break;
        case 2:
            amp1->setGain(GAIN_2X);
            amp2->setGain(GAIN_1X);
            break;
        case 4:
            amp1->setGain(GAIN_2X);
            amp2->setGain(GAIN_2X);
            break;
        case 5:
            amp1->setGain(GAIN_5X);
            amp2->setGain(GAIN_1X);
            break;
        case 8:
            amp1->setGain(GAIN_4X);
            amp2->setGain(GAIN_2X);
            break;
        case 10:
            amp1->setGain(GAIN_5X);
            amp2->setGain(GAIN_2X);
            break;
        case 16:
            amp1->setGain(GAIN_4X);
            amp2->setGain(GAIN_4X);
            break;
        case 20:
            amp1->setGain(GAIN_5X);
            amp2->setGain(GAIN_4X);
            break;
        case 25:
            amp1->setGain(GAIN_5X);
            amp2->setGain(GAIN_5X);
            break;
        case 32:
            amp1->setGain(GAIN_8X);
            amp2->setGain(GAIN_4X);
            break;
        case 40:
            amp1->setGain(GAIN_8X);
            amp2->setGain(GAIN_5X);
            break;
        case 50:
            amp1->setGain(GAIN_10X);
            amp2->setGain(GAIN_5X);
            break;
        case 64:
            amp1->setGain(GAIN_8X);
            amp2->setGain(GAIN_8X);
            break;
        case 80:
            amp1->setGain(GAIN_10X);
            amp2->setGain(GAIN_8X);
            break;
        case 100:
            amp1->setGain(GAIN_10X);
            amp2->setGain(GAIN_10X);
            break;
        case 128:
            amp1->setGain(GAIN_16X);
            amp2->setGain(GAIN_8X);
            break;
        case 160:
            amp1->setGain(GAIN_16X);
            amp2->setGain(GAIN_10X);
            break;
        case 256:
            amp1->setGain(GAIN_16X);
            amp2->setGain(GAIN_16X);
            break;
        case 320:
            amp1->setGain(GAIN_32X);
            amp2->setGain(GAIN_10X);
            break;
        case 512:
            amp1->setGain(GAIN_32X);
            amp2->setGain(GAIN_16X);
            break;
        case 1024:
            amp1->setGain(GAIN_32X);
            amp2->setGain(GAIN_32X);
            break;
        default:
            Serial.println("Invalid gain value");
            break;
    }
}

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    Serial.print(inChar);  // Echo the input back to the serial monitor

    if (inChar == '\n') {
      inputComplete = true;
      return;
    } else {
      temp += inChar;
    }
  }
}