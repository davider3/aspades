#include <Arduino.h>
#include <Wire.h>

#define QMC5883L_Address 0x0D  // I2C address of the QMC5883L

// Registers
#define Control_Reg_1 0x09
#define Set_Reset_Period_Reg 0x0B
#define Data_Reg_Begin 0x00

void setup() {
  Wire.begin(); // Initialize I2C
  Serial.begin(9600); // Start serial communication at 9600 baud

  // Initialize QMC5883L
  Wire.beginTransmission(QMC5883L_Address);
  Wire.write(Control_Reg_1);
  Wire.write(0x1D); // Set mode to Continuous measurement and ODR to 200Hz
  Wire.endTransmission();

  Wire.beginTransmission(QMC5883L_Address);
  Wire.write(Set_Reset_Period_Reg);
  Wire.write(0x01); // Set the set/reset period
  Wire.endTransmission();
}

void loop() {
  int x, y, z; //triple axis data

  // Tell the QMC5883L where to begin reading data
  Wire.beginTransmission(QMC5883L_Address);
  Wire.write(Data_Reg_Begin);
  Wire.endTransmission();

  // Read data from each axis, 2 registers per axis
  Wire.requestFrom(QMC5883L_Address, 6);
  if (6 <= Wire.available()) {
    x = Wire.read() | Wire.read() << 8;
    y = Wire.read() | Wire.read() << 8;
    z = Wire.read() | Wire.read() << 8;
  }

  // Print results
  Serial.print("X: ");
  Serial.print(x);
  Serial.print(" Y: ");
  Serial.print(y);
  Serial.print(" Z: ");
  Serial.println(z);

  delay(100);
}