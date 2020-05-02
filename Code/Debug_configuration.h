#ifndef __DEBUG_CONFG__
#define __DEBUG_CONFG__

#include "Arduino.h"

#define DEBUG_ENABLE

#ifdef DEBUG_ENABLE

//#define ENCODER_DEBUG
//#define ENCODER_IIC_OUTPUT
//#define ENCODER_DIRECT_OUTPUT //
//#define ENCODER_DIRECT2_OUTPUT //在定时器中

//#define UI_DEBUG

//#define TIM1_DEBUG
//#define TIM2_DEBUG
// #define TIM3_DEBUG
// #define TIM4_DEBUG
//#define TIM_BASE_FREQ_DEBUG

//#define STEPPER_DEBUG
//#define STEPPER_SPEED_DEBUG

//#define CMD_READ_DEBUG //显示独到的指令的所有内容
//#define CMD_READ2_DEBUG
//#define CMD_PROCESS_DEBUG //显示读到的指令类型、指令处理状态
//#define CMD_PROCESS2_DEBUG

#define PID_X_DEBUG
#define PID_Y_DEBUG
#define PID_Z_DEBUG

//#define PID_X_COMPUTE_DEBUG

//#define PID_CORE_DEBUG
//#define PID_X_CORE_DEBUG 

//DEBUG指令
//G0 X3000
//G0 Y3000
//G0 Z3000
//G0 X1000 Y2000 Z3000
//G1 X9999 A450
//G1 Y9999 B540
//G1 Z9999 C1000
//G1 X9999 Y9999 Z9999 A450 B540 C1000

//M0 P0.1 I1.3 D0

#endif

#endif