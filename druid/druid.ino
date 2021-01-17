#include "gyro_read.h"
#include <Wire.h>

float raw[6];
float offset[6];
float accAngleX = 0;
float gyroAngleX = 0;
float accAngleXfild = 0;

void setup() {
  Wire.begin(); 
  Serial.begin(9600);

  Wire.beginTransmission(0x68);            
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission(true);

  Wire.beginTransmission(0x68);
  Wire.write(0x1B);
  Wire.write(0x10);
  Wire.endTransmission(true);

  Wire.beginTransmission(0x68);
  Wire.write(0x1B);
  Wire.write(0x10);
  Wire.endTransmission(true);

  get_offset(offset);
  
}

void loop() {
  
  read_gyro(raw, offset);
  //accAngleX = (atan(raw[1] / sqrt(pow(raw[0], 2) + pow(raw[2], 2))) * 180 / PI);
  //gyroAngleX = gyroAngleX + raw[3]*0.01;
  //accAngleXfild = accAngleXfild*0.5 + accAngleX*0.5;

  //Serial.println(accAngleX);
  Serial.println(raw[0]);
  //Serial.println( 0.96 * gyroAngleX + 0.04 * accAngleX );
  
  delay(10);
}
