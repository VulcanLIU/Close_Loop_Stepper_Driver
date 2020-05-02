#ifndef __PID_H__
#define __PID_H__

#include "PID_v1.h"
#include "Debug_configuration.h"
#include "Arduino.h"

//PID算法初始化
void PID_begin();

//PID计算函数
float PID_X_Compute(float X_Input,float X_Setpoint);
float PID_Y_Compute(float Y_Input,float Y_Setpoint);
float PID_Z_Compute(float Z_Input,float Z_Setpoint);

#endif