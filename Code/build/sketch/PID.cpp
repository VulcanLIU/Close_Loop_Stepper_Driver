#include "PID.h"


double Kp = 1.2, Ki = 0, Kd = 0;

double _X_Setpoint_, _X_Input_, _X_Output_;
double _Y_Setpoint_, _Y_Input_, _Y_Output_;
double _Z_Setpoint_, _Z_Input_, _Z_Output_;

PID StepperX_PID(&_X_Input_, &_X_Output_, &_X_Setpoint_, Kp, Ki, Kd, DIRECT);
PID StepperY_PID(&_Y_Input_, &_Y_Output_, &_Y_Setpoint_, Kp, Ki, Kd, DIRECT);
PID StepperZ_PID(&_Z_Input_, &_Z_Output_, &_Z_Setpoint_, Kp, Ki, Kd, DIRECT);

void PID_begin()
{
    //PID计算器初始化
    StepperX_PID.SetMode(AUTOMATIC);
    StepperY_PID.SetMode(AUTOMATIC);
    StepperZ_PID.SetMode(AUTOMATIC);
}

float PID_X_Compute(float X_Input, float X_Setpoint)
{
    _X_Setpoint_ = X_Setpoint;
    _X_Input_ = X_Input;

    StepperX_PID.Compute();

#ifdef PID_X_COMPUTE_DEBUG
    Serial.print("In:");
    Serial.print(_X_Input_);
    Serial.print("  S:");
    Serial.print(_X_Setpoint_);
    Serial.print("  Out:");
    Serial.print(_X_Output_);
    Serial.println();
#endif

    return (float)_X_Output_;
}

float PID_Y_Compute(float Y_Input, float Y_Setpoint)
{
    _Y_Setpoint_ = Y_Setpoint;
    _Y_Input_ = Y_Input;

    StepperY_PID.Compute();

    return (float)_Y_Output_;
}
float PID_Z_Compute(float Z_Input, float Z_Setpoint)
{
    _Z_Setpoint_ = Z_Setpoint;
    _Z_Input_ = Z_Input;

    StepperZ_PID.Compute();

    return (float)_Z_Output_;
}

void PID_SetTunings(double _kp_, double _ki_, double _kd_)
{
    StepperX_PID.SetTunings(_kp_,_ki_,_kd_);
    StepperY_PID.SetTunings(_kp_,_ki_,_kd_);
    StepperZ_PID.SetTunings(_kp_,_ki_,_kd_);
}
