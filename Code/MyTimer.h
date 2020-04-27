#ifndef __MYTIMER_H__
#define __MYTIMER_H__

#include "Arduino.h"
#include "HardwareSerial.h"

//定时器参数定义
extern float TIM1_freq = 50;
extern float TIM2_freq = 1000;//步进电机X的定时器
extern float TIM3_freq = 1000;//步进电机Y的定时器
extern float TIM4_freq = 1000;//步进电机Z的定时器

//定义使用的定时器
extern TIM_TypeDef *Instance1;                        //使用TIM1
extern  HardwareTimer *MyTim1; //定义TIM1硬件定时器对象
extern TIM_TypeDef *Instance2;                        //使用TIM1
extern HardwareTimer *MyTim2; //定义TIM1硬件定时器对象
extern TIM_TypeDef *Instance3;                        //使用TIM1
extern HardwareTimer *MyTim3; //定义TIM1硬件定时器对象
extern TIM_TypeDef *Instance4;                        //使用TIM1
extern HardwareTimer *MyTim4; //定义TIM1硬件定时器对象

extern void TIM1_Update_IT_callback(HardwareTimer *);
extern void TIM2_Update_IT_callback(HardwareTimer *);
extern void TIM3_Update_IT_callback(HardwareTimer *);
extern void TIM4_Update_IT_callback(HardwareTimer *);
//定时器初始化函数
void TIM_begin();

//定时器设置频率函数
void TIM2_setOverflow(uint32_t _freq_);
void TIM3_setOverflow(uint32_t _freq_);
void TIM4_setOverflow(uint32_t _freq_);

#endif