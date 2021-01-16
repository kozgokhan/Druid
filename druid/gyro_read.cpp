#include "gyro_read.h"
#include <Wire.h>


double get_x_offset(){
  double x_pos = 0;
  double sum = 0;
  int i = 0;
  int avg_num = 100;
  double offset = 0;
  int iter_cnt = 0;

  while (i<avg_num){
    sum = sum + get_x_spd(offset);
    i = i + 1;
    if (i==avg_num){
      offset = offset - sum/avg_num;
      if ((abs(sum/avg_num) < 0.1) || iter_cnt>10){
        return offset;
        }
      sum = 0;
      i = 0;
      iter_cnt = iter_cnt + 1;
      }
    }
  }


double get_x_spd(double offset) {

  int rawX = 0;
  int rawY = 0;
  
  Wire.beginTransmission(0x68);            
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission(true);

  Wire.beginTransmission(0x68);
  Wire.write(0x1B);
  Wire.write(0x10);
  Wire.endTransmission(true);

  Wire.beginTransmission(0x68);
  Wire.write(0x43);
  Wire.endTransmission(false);
  Wire.requestFrom(0x68,4,true);
         
  rawX=Wire.read()<<8|Wire.read();
  rawY=Wire.read()<<8|Wire.read();
  
  return ((double)rawX/32.8 + offset);
  }
