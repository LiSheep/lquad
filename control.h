#ifndef CONTROL_H
#define CONTROL_H
#include <Arduino.h> 

#include "define.h"
//写入油门
extern void control_writeServo(Control *ctrl);

//将值从125~250转到1000~2000
extern void control_data2Servo(uint8_t speed, Control *ctrl);

#endif
