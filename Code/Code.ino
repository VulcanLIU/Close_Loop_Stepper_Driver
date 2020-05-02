#include "Stepper.h"
#include "UI.h"
#include "MyTimer.h"
#include "CMD.h"
#include "PID.h"
#include "Debug_configuration.h"

/*****   变量定义   *****/
void setup()
{
    //开启串口
    Serial.begin(250000);

    //步进电机初始化
    Stepper_begin();

    //UI初始化
    UI_begin();

    PID_begin();

    //定时器初始化
    TIM_begin();
}

void loop()
{
    //读取串口命令
    get_command();

    //如果待处理的命令大于0
    if (buflen > 0)
    {
        //命令处理
        process_command();
    }

    if (millis() % 100 == 0)
    {
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

#ifdef ENCODER_DIRECT2_OUTPUT
    digitalToggle((*Stepper_array[0]).STP);
    digitalToggle((*Stepper_array[1]).STP);
    digitalToggle((*Stepper_array[2]).STP);
    Serial.print(analogRead(Encoder_X_pin));
    Serial.print("  ");
    Serial.print(analogRead(Encoder_Y_pin));
    Serial.print("  ");
    Serial.print(analogRead(Encoder_Z_pin));
    Serial.println();
#endif

    if (Stepper_X.Actived)
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
            TIM2_freq = get_TIM_base_freq(Stepper_X.Target_speed, X_MIN_ANGLE);
            TIM2_freq += PID_X_Compute(Stepper_X.Current_speed, Stepper_X.Target_speed);
            // //更新定时器频率
            TIM2_setOverflow(TIM2_freq);
            break;
        default:
            break;
        }
    }
    else
    {
        TIM2_freq = 20;
        TIM2_setOverflow(TIM2_freq);
    }

    if (Stepper_Y.Actived)
    {
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
            TIM3_freq = get_TIM_base_freq(Stepper_Y.Target_speed, Y_MIN_ANGLE);
            TIM3_freq += PID_Y_Compute(Stepper_Y.Current_speed, Stepper_Y.Target_speed);
            //更新定时器频率
            TIM3_setOverflow(TIM3_freq);
            break;
        default:
            break;
        }
    }
    else
    {
        TIM3_freq = 20;
        TIM3_setOverflow(TIM3_freq);
    }

    if (Stepper_Z.Actived)
    {
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
            TIM4_freq = get_TIM_base_freq(Stepper_Z.Target_speed, Z_MIN_ANGLE);
            TIM4_freq += PID_Y_Compute(Stepper_Z.Current_speed, Stepper_Z.Target_speed);
            //更新定时器频率
            TIM4_setOverflow(TIM4_freq);
            break;
        default:
            break;
        }
    }
    else
    {
        TIM4_freq = 20;
        TIM4_setOverflow(TIM4_freq);
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

#ifdef PID_X_DEBUG
    Serial.print("  CX:");
    Serial.print(Stepper_X.Current_speed);
    Serial.print("  TX:");
    Serial.print(Stepper_X.Target_speed);
#endif
#ifdef PID_Y_DEBUG
    Serial.print("  CY:");
    Serial.print(Stepper_Y.Current_speed);
    Serial.print("  TY:");
    Serial.print(Stepper_Y.Target_speed);
#endif
#ifdef PID_Z_DEBUG
    Serial.print("  CZ:");
    Serial.print(Stepper_Z.Current_speed);
    Serial.print("  TZ:");
    Serial.print(Stepper_Z.Target_speed);
#endif
#if defined(PID_X_DEBUG) || defined(PID_X_DEBUG) || defined(PID_X_DEBUG)
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