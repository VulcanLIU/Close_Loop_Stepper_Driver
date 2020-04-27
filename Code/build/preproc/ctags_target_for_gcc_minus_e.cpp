# 1 "e:\\5\\Close_Loop_Stepper_Driver\\Code\\Code.ino"
# 2 "e:\\5\\Close_Loop_Stepper_Driver\\Code\\Code.ino" 2
# 3 "e:\\5\\Close_Loop_Stepper_Driver\\Code\\Code.ino" 2

# 5 "e:\\5\\Close_Loop_Stepper_Driver\\Code\\Code.ino" 2
# 6 "e:\\5\\Close_Loop_Stepper_Driver\\Code\\Code.ino" 2


/*****   变量定义   *****/
//DEBUG开关宏定义


//PID定义
double Kp = 2, Ki = 5, Kd = 1;
PID StepperX_PID(&Stepper_X.Current_speed, &TIM2_freq, &Stepper_X.Target_speed, Kp, Ki, Kd, 0);
PID StepperY_PID(&Stepper_Y.Current_speed, &TIM3_freq, &Stepper_Y.Target_speed, Kp, Ki, Kd, 0);
PID StepperZ_PID(&Stepper_Z.Current_speed, &TIM4_freq, &Stepper_Z.Target_speed, Kp, Ki, Kd, 0);

void setup()
{
    //开启串口
    Serial2.begin(115200);

    //步进电机初始化
    Stepper_begin();

    //UI初始化
    UI_begin();

    //定时器初始化
    TIM_begin();

    //PID计算器初始化
    StepperX_PID.SetMode(1);
    StepperY_PID.SetMode(1);
    StepperZ_PID.SetMode(1);
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
# 144 "e:\\5\\Close_Loop_Stepper_Driver\\Code\\Code.ino"
}

//定时器2比较匹配中断回调函数
void TIM2_Update_IT_callback(HardwareTimer *)
{
    Stepper_X_refresh();




}

//定时器1比较匹配中断回调函数
void TIM3_Update_IT_callback(HardwareTimer *)
{
    Stepper_Y_refresh();




}

//定时器1比较匹配中断回调函数
void TIM4_Update_IT_callback(HardwareTimer *)
{
    Stepper_Z_refresh();




}
