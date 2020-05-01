#ifndef __ENCODER_H__
#define __ENCODER_H__

#include "Arduino.h"
#include "AS5600_IIC.h"
#include "Debug_configuration.h"

//编码器ADC引脚定义
#define Encoder_X_pin A0
#define Encoder_Y_pin A1
#define Encoder_Z_pin A2

//编码器IIC引脚定义
#define Encoder_X_SDA_pin PB12
#define Encoder_X_SCL_pin PB13
#define Encoder_Y_SDA_pin PB14
#define Encoder_Y_SCL_pin PB15
#define Encoder_Z_SDA_pin PB1
#define Encoder_Z_SCL_pin PB2

//编码器函数定义
void Encoder_begin();
float Encoder_get_angle(int _index_);
float Encoder_X_get_angle();
float Encoder_Y_get_angle();
float Encoder_Z_get_angle();
float fmap(float x, float in_min, float in_max, float out_min, float out_max);
#endif