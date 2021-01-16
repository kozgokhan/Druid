#ifndef GYRO_READ_H
#define GYRO_READ_H

#include <Arduino.h>

int read_gyro(float * raw, float * offset);
float * get_offset(float * offset);
double get_x_offset();

#endif
