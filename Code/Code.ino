#include "Stepper.h"
#include "UI.h"
#include "MyTimer.h"
#include "CMD.h"
#include "PID.h"
#include "Debug_configuration.h"

/*****   变量定义   *****/
//DEBUG开关宏定义
#define SERIAL_DEBUG

void setup()
{
    //开启串口
    Serial.begin(115200);

    //步进电机初始化
    Stepper_begin();

    //UI初始化
    UI_begin();

    //定时器初始化
    TIM_begin();

    PID_begin();
}

void loop()
{
    //读取串口命令
    get_command();

    //如果待处理的命令大于0
    if (buflen)
    {
        //命令处理
        process_command();
    }

    //更新UI
    UI_data[X_speed].data = Stepper_X.Current_speed;
    UI_data[X_target_speed].data = Stepper_X.Target_speed;
    UI_data[Y_speed].data = Stepper_Y.Current_speed;
    UI_data[Y_target_speed].data = Stepper_Y.Target_speed;
    UI_data[Z_speed].data = Stepper_Z.Current_speed;
    UI_data[Z_target_speed].data = Stepper_Z.Target_speed;
    UI_data[X_angle].data = Stepper_X.Current_angle;
    UI_data[X_target_angle].data = Stepper_X.Target_angle;
    UI_data[Y_angle].data = Stepper_Y.Current_angle;
    UI_data[Y_target_angle].data = Stepper_Y.Target_angle;
    UI_data[Z_angle].data = Stepper_Z.Current_angle;
    UI_data[Z_target_angle].data = Stepper_Z.Target_angle;

    UI_update();
}

/*****************************************          电机控制函数区          ************************************************/

/**
 * @brief 转动舵机
 * 
 * @return true 转到角度
 * @return false 
 */
//定时器1比较匹配中断回调函数
void TIM1_Update_IT_callback(HardwareTimer *)
{
    //步进电机X PID计算
    Stepper_X.Current_speed = get_X_speed();
    switch (Stepper_X.Mode)
    {
    case P_mode:
        /* code */
        TIM2_setOverflow(1000);
        break;
    case S_mode:
        /* 增量PID代码段 */
        StepperX_PID.Compute();
        //更新定时器频率
        TIM2_setOverflow(TIM2_freq);
        break;
    default:
        break;
    }

    //步进电机Y PID计算
    Stepper_Y.Current_speed = get_Y_speed();
    switch (Stepper_Y.Mode)
    {
    case P_mode:
        /* code */
        TIM3_setOverflow(1000);
        break;
    case S_mode:
        /* 增量PID代码段 */
        StepperY_PID.Compute();
        //更新定时器频率
        TIM3_setOverflow(TIM3_freq);
        break;
    default:
        break;
    }

    //步进电机Z PID计算
    Stepper_Z.Current_speed = get_Z_speed();
    switch (Stepper_Z.Mode)
    {
    case P_mode:
        /* code */
        TIM4_setOverflow(1000);
        break;
    case S_mode:
        /* 增量PID代码段 */
        StepperZ_PID.Compute();
        //更新定时器频率
        TIM4_setOverflow(TIM4_freq);
        break;
    default:
        break;
    }

#ifdef TIM1_DEBUG
    Serial.print("T1_cb:");
    Serial.print(millis());
    Serial.print("  T2_f:");
    Serial.print(TIM2_freq);
    Serial.print("  T3_f:");
    Serial.print(TIM3_freq);
    Serial.print("  T4_f:");
    Serial.print(TIM4_freq);
    Serial.println();
#endif
}

//定时器2比较匹配中断回调函数
void TIM2_Update_IT_callback(HardwareTimer *)
{
    Stepper_X_refresh();
#ifdef TIM2_DEBUG
    Serial.print("T2_cb:");
    Serial.println(millis());
#endif
}

//定时器1比较匹配中断回调函数
void TIM3_Update_IT_callback(HardwareTimer *)
{
    Stepper_Y_refresh();
#ifdef TIM3_DEBUG
    Serial.print("TIM3_cb:");
    Serial.println(millis());
#endif
}

//定时器1比较匹配中断回调函数
void TIM4_Update_IT_callback(HardwareTimer *)
{
    Stepper_Z_refresh();
#ifdef TIM4_DEBUG
    Serial.print("TIM4_cb:");
    Serial.println(millis());
#endif
}