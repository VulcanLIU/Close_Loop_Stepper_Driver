#include "PID.h"

double Kp = 2, Ki = 5, Kd = 1;

double _X_Setpoint_, _X_Input_, _X_Output_;
double _Y_Setpoint_, _Y_Input_, _Y_Output_;
double _Z_Setpoint_, _Z_Input_, _Z_Output_;

PID StepperX_PID(&_X_Input_, &_X_Output_, &_X_Setpoint_, Kp, Ki, Kd, DIRECT);
PID StepperX_PID(&_Y_Input_, &_Y_Output_, &_Y_Setpoint_, Kp, Ki, Kd, DIRECT);
PID StepperX_PID(&_Z_Input_, &_Z_Output_, &_Z_Setpoint_, Kp, Ki, Kd, DIRECT);

void PID_begin()
{
    //PID计算器初始化
    StepperX_PID.SetMode(AUTOMATIC);
    StepperY_PID.SetMode(AUTOMATIC);
    StepperZ_PID.SetMode(AUTOMATIC);
}