#ifndef __STEPPER_H__
#define __STEPPER_H__

#include "Arduino.h"
#include "Encoder.h"
#include "MyTimer.h"

//步进电机引脚定义
#define EN 8    //步进电机使能端，低电平有效
#define X_DIR 5 //X轴 步进电机方向控制
#define Y_DIR 6 //y轴 步进电机方向控制
#define Z_DIR 7 //z轴 步进电机方向控制
#define X_STP 2 //x轴 步进控制
#define Y_STP 3 //y轴 步进控制
#define Z_STP 4 //z轴 步进控制

//定义步进电机的最小移动角度
#define X_MIN_ANGLE 1.8
#define Y_MIN_ANGLE 1.8
#define Z_MIN_ANGLE 1.8

//定义步进电机转动的正方向
#define X_FWD_DIR HIGH
#define Y_FWD_DIR HIGH
#define Z_FWD_DIR HIGH

//定义步进电机编号枚举量
enum Stepper_index
{
    X,
    Y,
    Z
};
//电机运行模式
enum Stepper_mode
{
    S_mode, //速度控制
    P_mode  //位置控制
};

//步进电机结构体定义以及结构体变量
typedef struct STEPPER
{
    //电机名称
    char Name;

    //速度标识符
    char S_id;

    //绑定的引脚信息
    uint8_t DIR;
    uint8_t STP;
    //角度信息
    float Last_Encoder_Value;
    float Encoder_Value;
    float Last_angle;
    float Current_angle;
    float Target_angle;
    float Current_speed;
    float Target_speed;

    int wrap_count;
    float angle_interval30;
    uint8_t counter;

    //电机运行状态
    bool Actived;
    //电机到达状态
    bool Arrived;
    
    //电机运行模式
    Stepper_mode Mode;
};

extern STEPPER Stepper_X;
extern STEPPER Stepper_Y;
extern STEPPER Stepper_Z;
extern STEPPER *Stepper_array[3];

//电机控制函数
void Stepper_begin();
void Stepper_X_refresh();
void Stepper_Y_refresh();
void Stepper_Z_refresh();
void Stepper_refresh(Stepper_index);

bool Stepper_arrived();
bool StepperX_arrived();
bool StepperY_arrived();
bool StepperZ_arrived();

//步进电机数据访问函数
float get_X_angle();
float get_Y_angle();
float get_Z_angle();
float get_X_speed();
float get_Y_speed();
float get_Z_speed();

//将步进电机目标转速转换为定时器频率的函数
int32_t convert_s2f(Stepper_index);

#endif