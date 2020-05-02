#ifndef __DEBUG_CONFG__
#define __DEBUG_CONFG__

#include "Arduino.h"

#define DEBUG_ENABLE

#ifdef DEBUG_ENABLE

//#define ENCODER_DEBUG
//#define ENCODER_IIC_OUTPUT
//#define ENCODER_DIRECT_OUTPUT
//#define ENCODER_DIRECT2_OUTPUT

//#define UI_DEBUG

//#define TIM1_DEBUG
//#define TIM2_DEBUG
// #define TIM3_DEBUG
// #define TIM4_DEBUG

//#define STEPPER_DEBUG
//#define STEPPER_SPEED_DEBUG

#define CMD_READ_DEBUG
//#define CMD_READ2_DEBUG
#define CMD_PROCESS_DEBUG //显示读到的指令类型、指令处理状态
//#define CMD_PROCESS2_DEBUG

//#define PID_X_DEBUG //G1 X9999 A450
//#define PID_X_COMPUTE_DEBUG
#define PID_CORE_DEBUG

#endif

#endif