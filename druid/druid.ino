#include "gyro_read.h"
#include <Wire.h>

float raw_gyro[6];
float offset[6];
float pos[3];
float accAngleX = 0;
float gyroAngleX = 0;
float accAngleXfild = 0;
float previousTime, currentTime, dt_ms, dt_s;
float corr;

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

  previousTime = currentTime;
  currentTime = millis();
  dt_ms = (currentTime - previousTime);
  dt_s = dt_ms * 0.001;
  
  read_gyro(raw_gyro, offset);
  get_gyro_pos(pos, raw_gyro, dt_s);
//  //accAngleX = (atan(raw[1] / sqrt(pow(raw[0], 2) + pow(raw[2], 2))) * 180 / PI);
//  gyroAngleX = gyroAngleX + raw_gyro[3]*dt_s;
//  //accAngleXfild = accAngleXfild*0.5 + accAngleX*0.5;
//  gyroAngleX = gyroAngleX *0.96 + 0.04*raw_gyro[0];
//  //Serial.println(accAngleX);
  Serial.print("AccX ");
  Serial.print(raw_gyro[0]);
  Serial.print(" GyrX ");
  Serial.println(pos[0]);
  



  //delay(5);
}
