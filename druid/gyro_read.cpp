#include "gyro_read.h"
#include <Wire.h>

float * get_offset(float * offset){
  float raw[6] = {0};
  float sum[6] = {0};
  int sample = 0;
  int max_sample = 100;
  int completed_num = 0;
  int max_iter = 10;
  int iter_cnt = 0;
  float tolerance = 0.1;
  
  while (sample<max_sample) {
    read_gyro(raw, offset);
    for (int i=0; i<6; i++) sum[i] = sum[i] + raw[i];
    sample++;
    if (sample == max_sample) {
      completed_num = 0;
      for (int i=0; i<6; i++) {
      offset[i] = offset[i] - sum[i]/max_sample;
      if (abs(sum[i]/max_sample) < tolerance) completed_num++;
      }
      if (completed_num == 6 || iter_cnt == max_iter) return offset;
      memset(sum, 0, sizeof sum);
      sample = 0;
      iter_cnt++;
    }
  delay(5);
  }
}

int read_gyro(float * raw, float * offset) {
  
  Wire.beginTransmission(0x68);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(0x68,6,true);

  float accAngleX, accAngleY;
  float x_acc, y_acc, z_acc;
         
  x_acc = (float)(Wire.read()<<8|Wire.read()) / 16384.0;
  y_acc = (float)(Wire.read()<<8|Wire.read()) / 16384.0;
  z_acc = (float)(Wire.read()<<8|Wire.read()) / 16384.0;

  raw[0] = (atan(y_acc / sqrt(pow(x_acc, 2) + pow(z_acc, 2))) * 180 / PI) + offset[0];
  raw[1] = (atan(-1 * x_acc / sqrt(pow(y_acc, 2) + pow(z_acc, 2))) * 180 / PI) + offset[1];
  raw[2] = 0.0 + offset[2];

  Wire.beginTransmission(0x68);
  Wire.write(0x43);
  Wire.endTransmission(false);
  Wire.requestFrom(0x68, 6, true);

  raw[3] = (float)(Wire.read()<<8|Wire.read()) / 32.8 + offset[3]; // x_spd
  raw[4] = (float)(Wire.read()<<8|Wire.read()) / 32.8 + offset[4]; // y_spd
  raw[5] = (float)(Wire.read()<<8|Wire.read()) / 32.8 + offset[5]; // z_spd
  
  return 1;
  }

int get_gyro_pos(float *pos, float *raw_gyro, float dt_s){
  for (int i=0; i<3; i++) {
    pos[i] = pos[i] + raw_gyro[i+3]*dt_s;
    pos[i] = pos[i] *0.96 + 0.04*raw_gyro[i];
    }
   return 1;
  
  //gyroAngleX = gyroAngleX + raw_gyro[3]*dt_s;

  return 1;
  }

  
