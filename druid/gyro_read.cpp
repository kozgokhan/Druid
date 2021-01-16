#include "gyro_read.h"
#include <Wire.h>

float * get_offset(float * offset){
  float raw[6] = {0};
  float sum[6] = {0};
  int sample = 0;
  int max_sample = 10;
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
  }
}

int read_gyro(float * raw, float * offset) {
  
  Wire.beginTransmission(0x68);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(0x68,6,true);

  float accAngleX, accAngleY;
         
  raw[0] = (float)(Wire.read()<<8|Wire.read()) / 16384.0  + offset[0]; // x_acc
  raw[1] = (float)(Wire.read()<<8|Wire.read()) / 16384.0 + offset[1]; // y_acc
  raw[2] = (float)(Wire.read()<<8|Wire.read()) / 16384.0 + offset[2]; // z_acc

  accAngleX = (atan(raw[1] / sqrt(pow(raw[0], 2) + pow(raw[2], 2))) * 180 / PI); // AccErrorX ~(0.58) See the calculate_IMU_error()custom function for more details
  accAngleY = (atan(-1 * raw[0] / sqrt(pow(raw[1], 2) + pow(raw[2], 2))) * 180 / PI); // AccErrorY ~(-1.58)

  Wire.beginTransmission(0x68);
  Wire.write(0x43); // Gyro data first register address 0x43
  Wire.endTransmission(false);
  Wire.requestFrom(0x68, 6, true);

  raw[3] = (float)(Wire.read()<<8|Wire.read()) / 32.8 + offset[3]; // x_spd
  raw[4] = (float)(Wire.read()<<8|Wire.read()) / 32.8 + offset[4]; // y_spd
  raw[5] = (float)(Wire.read()<<8|Wire.read()) / 32.8 + offset[5]; // z_spd
  
  return 1;
  }

  
