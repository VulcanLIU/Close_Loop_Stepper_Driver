#include "Stepper.h"

//定义步进电机结构体变量
STEPPER Stepper_X;
STEPPER Stepper_Y;
STEPPER Stepper_Z;

//定义步进电机结构体指针数组
STEPPER *Stepper_array[3] = {&Stepper_X, &Stepper_Y, &Stepper_Z};

//三个电机30个定时器周期下的转角间隔储存数组以及写入位置变量
const int MAX_INDEX = 20;
float X_30_array[MAX_INDEX] = {};
int X_ary_indw = 0;
float Y_30_array[MAX_INDEX] = {};
int Y_ary_indw = 0;
float Z_30_array[MAX_INDEX] = {};
int Z_ary_indw = 0;

void Stepper_begin()
{
    //将步进电机使用的引脚都配置为输出模式
    pinMode(X_DIR, OUTPUT);
    pinMode(X_STP, OUTPUT);

    pinMode(Y_DIR, OUTPUT);
    pinMode(Y_STP, OUTPUT);

    pinMode(Z_DIR, OUTPUT);
    pinMode(Z_STP, OUTPUT);

    //对步进电机变量的引脚进行注册
    Stepper_X.Name = 'X';
    Stepper_X.S_id = 'A';
    Stepper_X.DIR = X_DIR;
    Stepper_X.STP = X_STP;

    Stepper_Y.Name = 'Y';
    Stepper_Y.S_id = 'B';
    Stepper_Y.DIR = Y_DIR;
    Stepper_Y.STP = Y_STP;

    Stepper_Z.Name = 'Z';
    Stepper_Z.S_id = 'C';
    Stepper_Z.DIR = Z_DIR;
    Stepper_Z.STP = Z_STP;

    //步进电机驱动器使能引脚拉低进行使能
    pinMode(EN, OUTPUT);
    digitalWrite(EN, LOW);

    //编码器初始化
    Encoder_begin();

#ifdef ENCODER_DIRECT_OUTPUT
    while (1)
    {
        digitalToggle((*Stepper_array[0]).STP);
        digitalToggle((*Stepper_array[1]).STP);
        digitalToggle((*Stepper_array[2]).STP);
        Serial.print(analogRead(Encoder_X_pin));
        Serial.print("  ");
        Serial.print(analogRead(Encoder_Y_pin));
        Serial.print("  ");
        Serial.print(analogRead(Encoder_Z_pin));
        Serial.println();
        delay(1);
    }
#endif
}

void Stepper_X_refresh()
{
    if (Stepper_X.Actived)
    {
#ifdef STEPPER_DEBUG
        Serial.print("X:");
#endif
        Stepper_refresh(X);
    }
}

void Stepper_Y_refresh()
{
    if (Stepper_Y.Actived)
    {
        Stepper_refresh(Y);

#ifdef STEPPER_DEBUG
        Serial.print("Y:");
#endif
    }
}

void Stepper_Z_refresh()
{
    if (Stepper_Z.Actived)
    {
        Stepper_refresh(Z);

#ifdef STEPPER_DEBUG
        Serial.print("Z:");
#endif
    }
}

void Stepper_refresh(Stepper_index _i_)
{
    //读取编码器角度
    (*Stepper_array[_i_]).Encoder_Value = Encoder_get_angle(_i_);

    //处理编码器角度
    if (((*Stepper_array[_i_]).Encoder_Value - (*Stepper_array[_i_]).Last_Encoder_Value) < -180.0)
        (*Stepper_array[_i_]).wrap_count += 1; //Check if we've rotated more than a full revolution (have we "wrapped" around from 359 degrees to 0 or ffrom 0 to 359?)
    else if (((*Stepper_array[_i_]).Encoder_Value - (*Stepper_array[_i_]).Last_Encoder_Value) > 180.0)
        (*Stepper_array[_i_]).wrap_count -= 1;

    //对上一次读取到的编码器角度进行存储
    (*Stepper_array[_i_]).Last_Encoder_Value = (*Stepper_array[_i_]).Encoder_Value;

    //计算转动的总角度
    (*Stepper_array[_i_]).Current_angle = ((*Stepper_array[_i_]).Encoder_Value + (360.0 * (*Stepper_array[_i_]).wrap_count));

    //累计现在转动位置与上次位置之间的位置差
    (*Stepper_array[_i_]).angle_interval30 += (*Stepper_array[_i_]).Current_angle - (*Stepper_array[_i_]).Last_angle;

    //将该次转动角度储存为上次角度
    (*Stepper_array[_i_]).Last_angle = (*Stepper_array[_i_]).Current_angle;

    //如果累加了30次 将位置差放入循环数组
    if ((*Stepper_array[_i_]).counter == 29)
    {
        //数字放入
        X_30_array[X_ary_indw] = (*Stepper_array[_i_]).angle_interval30;
        //X队列写入位置++
        X_ary_indw = (X_ary_indw++) % MAX_INDEX;
        //计数器清零
        (*Stepper_array[_i_]).counter = 0;
        //累加变量清零
        (*Stepper_array[_i_]).angle_interval30 = 0;
    }
    else
    {
        (*Stepper_array[_i_]).counter++;
    }

    //计算目前位置与目标位置间的步数差+操作电平
    int _step_ = ((*Stepper_array[_i_]).Target_angle - (*Stepper_array[_i_]).Current_angle) / X_MIN_ANGLE;

    if (_step_ >= 1)
    {
        digitalWrite((*Stepper_array[_i_]).DIR, X_FWD_DIR);
        digitalToggle((*Stepper_array[_i_]).STP);
    }
    else if (_step_ <= -1)
    {
        digitalWrite((*Stepper_array[_i_]).DIR, !X_FWD_DIR);
        digitalToggle((*Stepper_array[_i_]).STP);
    }
    else
    {
        (*Stepper_array[_i_]).Arrived = true;
    }
#ifdef STEPPER_DEBUG
    if ((*Stepper_array[_i_]).Arrived)
    {
        Serial.println('A');
    }
    else
    {
        Serial.println(_step_);
    }
#endif
}

bool Stepper_arrived()
{
    if (StepperX_arrived() && StepperY_arrived() && StepperZ_arrived())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool StepperX_arrived()
{
    if (Stepper_X.Actived)
    {
        if (Stepper_X.Arrived)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return true;
    }
}

bool StepperY_arrived()
{
    if (Stepper_Y.Actived)
    {
        if (Stepper_Y.Arrived)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return true;
    }
}

bool StepperZ_arrived()
{
    if (Stepper_Z.Actived)
    {
        if (Stepper_Z.Arrived)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return true;
    }
}

//编码器角度
float Encoder_get_angle(Stepper_index _i_)
{
    switch (_i_)
    {
    case X:
        return Encoder_X_get_angle();
        break;
    case Y:
        return Encoder_Y_get_angle();
        break;
    case Z:
        return Encoder_Z_get_angle();
        break;
    default:
        return 0;
        break;
    }
}

//步进电机数据访问函数

float get_X_angle()
{
    return Stepper_X.Current_angle;
}

float get_Y_angle()
{
    return Stepper_Y.Current_angle;
}

float get_Z_angle()
{
    return Stepper_Z.Current_angle;
}

float get_X_speed()
{
    float _speed_ = 0;

    //累加转角间隔储存数组中的角度
    for (int _i_ = 0; _i_ < MAX_INDEX; _i_++)
    {
        _speed_ += X_30_array[_i_];
    }

    //取平均值计算一个TIM2周期步进电机转过的角度
    _speed_ = _speed_ / MAX_INDEX;

    //计算一秒钟转过的度数
    _speed_ *= TIM2_freq;

    return _speed_;
}

float get_Y_speed()
{
    float _speed_ = 0;

    //累加转角间隔储存数组中的角度
    for (int _i_ = 0; _i_ < MAX_INDEX; _i_++)
    {
        _speed_ += Y_30_array[_i_];
    }

    //取平均值计算一个TIM2周期步进电机转过的角度
    _speed_ = _speed_ / MAX_INDEX;

    //计算一秒钟转过的度数
    _speed_ *= TIM3_freq;

    return _speed_;
}

float get_Z_speed()
{
    float _speed_ = 0;

    //累加转角间隔储存数组中的角度
    for (int _i_ = 0; _i_ < MAX_INDEX; _i_++)
    {
        _speed_ += Z_30_array[_i_];
    }

    //取平均值计算一个TIM2周期步进电机转过的角度
    _speed_ = _speed_ / MAX_INDEX;

    //计算一秒钟转过的度数
    _speed_ *= TIM4_freq;

    return _speed_;
}

int32_t convert_s2f(Stepper_index _stepper_)
{
    int32_t _freq_ = 0;
    switch (_stepper_)
    {
    case X:
        _freq_ = (*Stepper_array[_stepper_]).Target_speed * 2 / X_MIN_ANGLE;
        break;
    case Y:
        _freq_ = (*Stepper_array[_stepper_]).Target_speed * 2 / Y_MIN_ANGLE;
        break;
    case Z:
        _freq_ = (*Stepper_array[_stepper_]).Target_speed * 2 / Z_MIN_ANGLE;
        break;

    default:
        break;

        return _freq_;
    }
}