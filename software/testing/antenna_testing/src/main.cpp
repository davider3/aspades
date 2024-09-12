#include <Arduino.h>
#include <SPI.h>

#define V_REF 4.92
#define SAMPLES 40
#define ADC_RES 1023.0
#define CS 53
#define GAIN_WRITE 0b01000000
#define GAIN_2X 0b00000001
#define GAIN_4X 3
#define GAIN_32X 0b00000111

float max_adc = 0;
int readings[SAMPLES];
int count = 0;
int i;
int sum;

int getMax();
int getMean();
int getMin();

void setup() {
    Serial.begin(9600);
    for(i = 0; i < SAMPLES; ++i)
        readings[i] = 0;

    pinMode(CS, OUTPUT);
    SPI.begin();
    SPI.setBitOrder(MSBFIRST);
    SPI.setDataMode(SPI_MODE0);
    SPI.setClockDivider(SPI_CLOCK_DIV4); // 16MHZ/4 = 4MHZ
    digitalWrite(CS, LOW);
    SPI.transfer(GAIN_WRITE);
    SPI.transfer(GAIN_4X);
    digitalWrite(CS, HIGH);
    SPI.end();
}

void loop() {
    readings[count] = analogRead(A0);
    max_adc = getMax();
    Serial.print("MAX: ");
    Serial.println((max_adc/ADC_RES) * V_REF);
    // Serial.print(" MIN: ");
    // Serial.print((getMin()/ADC_RES) * V_REF);
    // Serial.print(" MEAN: ");
    // Serial.println((getMean()/ADC_RES) * V_REF);

    count = (count + 1) % SAMPLES;

    
    // digitalWrite(CS, LOW);
    // SPI.transfer(GAIN_WRITE);
    // SPI.transfer(GAIN_32X);
    // digitalWrite(CS, HIGH);
}

int getMax(){
    int temp = 0;
    for(i = 0; i < SAMPLES; ++i){
        if(readings[i] > temp)
            temp = readings[i];
    }

    return temp;
}

int getMin(){
    int temp = 1024;
    for(i = 0; i < SAMPLES; ++i){
        if(readings[i] < temp)
            temp = readings[i];
    }

    return temp;
}

int getMean(){
    sum = 0;
    for(i = 0; i < SAMPLES; ++i){
        sum += readings[i];
    }

    return sum / SAMPLES;
}