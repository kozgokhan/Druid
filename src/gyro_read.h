#ifndef GYRO_READ_H
#define GYRO_READ_H

#include <Arduino.h>

int read_gyro(float * raw, float * offset);
int get_gyro_pos(float *pos, float *raw_gyro, float dt_s);
float * get_offset(float * offset);
double get_x_offset();
void init_mpu();

#endif
