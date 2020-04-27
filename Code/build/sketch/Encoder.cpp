#include "Encoder.h"

void Encoder_begin()
{
    //通过软串口将编码器配置为模拟输出模式
    AS5600_IIC_Init(Encoder_X_SDA_pin, Encoder_X_SCL_pin);
    AS5600_IIC_Write_OneByte((0x36 << 1), 0x08, 0XC0);
    //初始化ADC引脚设置ADC分辨率
    analogReadResolution(12);
    pinMode(Encoder_X_pin, INPUT_ANALOG);
    pinMode(Encoder_Y_pin, INPUT_ANALOG);
    pinMode(Encoder_Z_pin, INPUT_ANALOG);

#ifdef ENCODER_DIRECT_OUTPUT
    while (1)
    {
        Serial.print(analogRead(Encoder_X_pin));
        Serial.print("  ");
        Serial.print(analogRead(Encoder_Y_pin));
        Serial.print("  ");
        Serial.print(analogRead(Encoder_Z_pin));
        Serial.println();
    }
#endif
}

float Encoder_X_get_angle()
{
    int _ADC_Value_ = analogRead(Encoder_X_pin);
    float _angle_ = fmap(_ADC_Value_, 0.0, 4096.0, 0.0, 360.0);

#ifdef ENCODER_DEBUG
    Serial.print(_angle_);
    Serial.println();
#endif
}

float Encoder_Y_get_angle()
{
    int _ADC_Value_ = analogRead(Encoder_Y_pin);
    float _angle_ = fmap(_ADC_Value_, 0.0, 4096.0, 0.0, 360.0);
#ifdef ENCODER_DEBUG
    Serial.print(_angle_);
    Serial.println();
#endif
}

float Encoder_Z_get_angle()
{
    int _ADC_Value_ = analogRead(Encoder_Z_pin);
    float _angle_ = fmap(_ADC_Value_, 0.0, 4096.0, 0.0, 360.0);
#ifdef ENCODER_DEBUG
    Serial.print(_angle_);
    Serial.println();
#endif
}

float fmap(float x, float in_min, float in_max, float out_min, float out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}