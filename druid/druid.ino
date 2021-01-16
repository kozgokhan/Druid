#include "gyro_read.h"
#include <Wire.h>

float x_pos = 0;
int x_spd;
float x_offset = 3;
int  *spd;

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
}

void loop() {

  float raw[6];
  
  x_spd = get_spd(raw);
  Serial.println( raw[3] );
  
  delay(10);
}
