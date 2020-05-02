#include "CMD.h"

char cmdbuffer[BUFSIZE][MAX_CMD_SIZE]; //命令队列Buffer
char serial_char;                      //单次从串口读出的字符
int serial_count = 0;                  //单条命令长度计数器-大小不可超过MAX_CMD_SIZE
int bufindr = 0;                       //process_command()读取Buffer位置
int bufindw = 0;                       //get_command()写入Buffer位置
int buflen = 0;                        //
char *strchr_pointer;

void get_coordinates(uint8_t _G_code_)
{
    for (int i = 0; i < 3; i++)
    {
        if (code_seen((*Stepper_array[i]).Name))
        {
            //赋值目标位置
            (*Stepper_array[i]).Target_angle = (float)code_value();
            //将被命令提到的电机设为活动状态
            (*Stepper_array[i]).Actived = true;

            //如果是G0将电机运行状态设为位置控制模式
            if (_G_code_ == 0)
            {
                (*Stepper_array[i]).Mode = P_mode;
            }

            //如果是G1将电机运行状态设为位置控制模式
            if (_G_code_ == 1)
            {
                (*Stepper_array[i]).Mode = S_mode;
            }
#ifdef CMD_PROCESS2_DEBUG
            Serial.print("N:");
            Serial.print((*Stepper_array[i]).Name);
            Serial.print("  T_a:");
            Serial.print((*Stepper_array[i]).Target_angle);
            Serial.print("  Ac:");
            Serial.print((*Stepper_array[i]).Actived);
            Serial.print("  Ar:");
            Serial.print((*Stepper_array[i]).Arrived);
            Serial.print("  M:");
            Serial.println((*Stepper_array[i]).Mode);
#endif
        }
        else
        {
            (*Stepper_array[i]).Actived = false;
        }

        if (_G_code_ == 1 && code_seen((*Stepper_array[i]).S_id))
        {
            //赋值目标速度
            (*Stepper_array[i]).Target_speed = (float)code_value();
#ifdef CMD_PROCESS2_DEBUG
            Serial.print("N:");
            Serial.print((*Stepper_array[i]).Name);
            Serial.print("  T_s:");
            Serial.println((*Stepper_array[i]).Target_speed);
#endif
        }
    }
}

/**
 * @brief 从串口获取命令
 * @details 读取串口
 */
void get_command()
{
    while (Serial.available() > 0 && buflen < BUFSIZE)
    {
        serial_char = Serial.read();

        if (serial_char == '\n' || serial_char == '\r' || serial_count >= (MAX_CMD_SIZE - 1)) //如果检测到换行符 或者指令的数字超长了
        {
            for (int i = serial_count; i < MAX_CMD_SIZE; i++)
            {
                cmdbuffer[bufindw][i] = 0; //清空之后位置的字符
            }
            serial_count = 0; //准备接收下一行
            buflen += 1;

#ifdef CMD_READ_DEBUG
            Serial.print("Get one command:");
            for (int j = 0; j < MAX_CMD_SIZE; j++)
            {
                Serial.print(cmdbuffer[bufindw][j]);
            }
            Serial.print("  ");
            Serial.print("buflen:");
            Serial.println(buflen);
#endif

            bufindw = (bufindw + 1) % BUFSIZE; //写入位置指正++
        }
        else //如果不是换行符
        {
            cmdbuffer[bufindw][serial_count++] = serial_char; //直接把读取到的字符储存到cmdbuffer中
#ifdef CMD_READ2_DEBUG
            Serial.print(cmdbuffer[bufindw][serial_count - 1]);
#endif
        }
    }
}

/**
 * @brief 处理获取的命令
 * 
 */
void process_command()
{
#ifdef CMD_PROCESS_DEBUG
    Serial.print("Processing command...");
#endif
    bool command_states = false;

    if (code_seen('G')) //如果命令中有G
    {
        switch ((int)code_value())
        {
        case 0: //G0指令
#ifdef CMD_PROCESS_DEBUG
            Serial.println(" G0 ");
#endif
            get_coordinates(0);
            command_states = Stepper_arrived();
#ifdef CMD_PROCESS_DEBUG
            Serial.print(" command_states: ");
            Serial.println(command_states);
#endif
            break;
        case 1: //G1指令
#ifdef CMD_PROCESS_DEBUG
            Serial.println(" G1 ");
#endif
            get_coordinates(1);
            command_states = Stepper_arrived();
#ifdef CMD_PROCESS_DEBUG
            Serial.print(" command_states: ");
            Serial.println(command_states);
#endif
            break;
        default:
            break;
        }
    }
    else
    {
#ifdef CMD_PROCESS_DEBUG
        Serial.println(" Not A Command! ");
#endif
        //否则不构成命令，直接跳转
        command_states = true;
    }

    if (command_states == true)
    {
        bufindr = (bufindr + 1) % BUFSIZE; //读取位置指针++
        buflen = (buflen - 1);             //待处理任务--
        command_states = false;            //复位命令状态
        for (int i = 0; i < 3; i++)
        {
            ((*Stepper_array[i]).Arrived = false);//步进电机到达状态清零
        }
#ifdef CMD_PROCESS_DEBUG
        Serial.println("Go to Next Command!");
#endif
    }
}

bool code_seen(char code)
{
    strchr_pointer = strchr(cmdbuffer[bufindr], code);
    return (strchr_pointer != NULL); //Return True if a character was found
}

/**
 * @brief 
 * 
 * @return float 
 */
float code_value()
{
    return (strtod(&cmdbuffer[bufindr][strchr_pointer - cmdbuffer[bufindr] + 1], NULL));
}

/**
 * @brief 
 * 
 * @return long 
 */
long code_value_long()
{
    return (strtol(&cmdbuffer[bufindr][strchr_pointer - cmdbuffer[bufindr] + 1], NULL, 10));
}