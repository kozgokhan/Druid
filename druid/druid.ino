#include "gyro_read.h"
#include <Wire.h>

double x_pos = 0;
double x_spd = 0;
double x_offset = 3;

void setup() {
  Wire.begin(); 
  Serial.begin(9600);
  x_offset = get_x_offset();
}

void loop() {
  x_spd = get_x_spd(x_offset);
  x_pos = x_pos + x_spd * 0.0101;
  
  Serial.println(x_pos);
  
  delay(10);
}
