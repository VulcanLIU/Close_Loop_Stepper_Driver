#include "MyTimer.h"

//定时器频率变量定义
float TIM1_freq = 50;
float TIM2_freq = 1000; //步进电机X的定时器
float TIM3_freq = 1000; //步进电机Y的定时器
float TIM4_freq = 1000; //步进电机Z的定时器

//定时器对象定义
TIM_TypeDef *Instance1 = TIM1;                        //使用TIM1
HardwareTimer *MyTim1 = new HardwareTimer(Instance1); //定义TIM1硬件定时器对象
TIM_TypeDef *Instance2 = TIM2;                        //使用TIM2
HardwareTimer *MyTim2 = new HardwareTimer(Instance2); //定义TIM2硬件定时器对象
TIM_TypeDef *Instance3 = TIM3;                        //使用TIM3
HardwareTimer *MyTim3 = new HardwareTimer(Instance3); //定义TIM3硬件定时器对象
TIM_TypeDef *Instance4 = TIM4;                        //使用TIM4
HardwareTimer *MyTim4 = new HardwareTimer(Instance4); //定义TIM4硬件定时器对象

void TIM_begin()
{
    //四个定时器初始化
    TIM1_begin();
#ifndef ENCODER_DIRECT2_OUTPUT
    TIM2_begin();
    TIM3_begin();
    TIM4_begin();
#endif

#ifdef TIM_DEBUG
    Serial.println("TIM_begin");
#endif
}

//定时器函数
void TIM1_begin()
{
    //定时器频率100Hz
    MyTim1->setOverflow(TIM1_freq, HERTZ_FORMAT);

    //注册TIM1_Update_IT_callback为定时器1比较匹配中断回调函数
    MyTim1->attachInterrupt(TIM1_Update_IT_callback);

    //定时器1开始运行
    MyTim1->resume();
}

void TIM2_begin()
{
    //定时器频率100Hz
    MyTim2->setOverflow(TIM2_freq, HERTZ_FORMAT);

    //注册TIM1_Update_IT_callback为定时器1比较匹配中断回调函数
    MyTim2->attachInterrupt(TIM2_Update_IT_callback);

    //定时器1开始运行
    MyTim2->resume();
}

void TIM3_begin()
{
    //定时器频率100Hz
    MyTim3->setOverflow(TIM3_freq, HERTZ_FORMAT);

    //注册TIM1_Update_IT_callback为定时器1比较匹配中断回调函数
    MyTim3->attachInterrupt(TIM3_Update_IT_callback);

    //定时器1开始运行
    MyTim3->resume();
}

void TIM4_begin()
{
    //定时器频率100Hz
    MyTim4->setOverflow(TIM4_freq, HERTZ_FORMAT);

    //注册TIM1_Update_IT_callback为定时器1比较匹配中断回调函数
    MyTim4->attachInterrupt(TIM4_Update_IT_callback);

    //定时器1开始运行
    MyTim4->resume();
}

void TIM2_setOverflow(uint32_t _freq_)
{
    TIM2_freq = _freq_;
    MyTim2->setOverflow(TIM2_freq, HERTZ_FORMAT);
#ifdef TIM_DEBUG
    Serial.print("TIM2_set:");
    Serial.println(_freq_);
#endif
}

void TIM3_setOverflow(uint32_t _freq_)
{
    TIM3_freq = _freq_;
    MyTim3->setOverflow(TIM3_freq, HERTZ_FORMAT);
#ifdef TIM_DEBUG
    Serial.print("TIM3_set:");
    Serial.println(_freq_);
#endif
}

void TIM4_setOverflow(uint32_t _freq_)
{
    TIM4_freq = _freq_;
    MyTim4->setOverflow(TIM4_freq, HERTZ_FORMAT);
#ifdef TIM_DEBUG
    Serial.print("TIM4_set:");
    Serial.println(_freq_);
#endif
}
