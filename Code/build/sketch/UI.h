#ifndef __MYUI_H__
#define __MYUI_H__

//#include "Debug_configuration.h"
#include "Arduino.h"

//UI界面坐标定义

//行列位置定义
#define LINE_HIGHT 8

#define LINE1 10
#define LINE2 (LINE1 + LINE_HIGHT)
#define LINE3 (LINE2 + LINE_HIGHT)
#define LINE4 (LINE3 + LINE_HIGHT)
#define LINE5 (LINE4 + LINE_HIGHT)
#define LINE6 (LINE5 + LINE_HIGHT)
#define LINE7 (LINE6 + LINE_HIGHT)

#define COLUMN1 0
#define COLUMN2 10
#define COLUMN3 69

//字符串位置定义
#define STR_S_X COLUMN2
#define STR_A_X COLUMN3
#define STR_S_Y LINE1
#define STR_A_Y LINE1

#define STR_M1_X COLUMN1
#define STR_T1_X COLUMN1
#define STR_M2_X COLUMN1
#define STR_T2_X COLUMN1
#define STR_M3_X COLUMN1
#define STR_T3_X COLUMN1

#define STR_M1_Y LINE2
#define STR_T1_Y LINE3
#define STR_M2_Y LINE4
#define STR_T2_Y LINE5
#define STR_M3_Y LINE6
#define STR_T3_Y LINE7

//数字位置定义
#define VAL_M1_S_X COLUMN2
#define VAL_M1_ST_X COLUMN2
#define VAL_M2_S_X COLUMN2
#define VAL_M2_ST_X COLUMN2
#define VAL_M3_S_X COLUMN2
#define VAL_M3_ST_X COLUMN2

#define VAL_M1_S_Y LINE2
#define VAL_M1_ST_Y LINE3
#define VAL_M2_S_Y LINE4
#define VAL_M2_ST_Y LINE5
#define VAL_M3_S_Y LINE6
#define VAL_M3_ST_Y LINE7

#define VAL_M1_A_X COLUMN3
#define VAL_M1_AT_X COLUMN3
#define VAL_M2_A_X COLUMN3
#define VAL_M2_AT_X COLUMN3
#define VAL_M3_A_X COLUMN3
#define VAL_M3_AT_X COLUMN3

#define VAL_M1_A_Y LINE2
#define VAL_M1_AT_Y LINE3
#define VAL_M2_A_Y LINE4
#define VAL_M2_AT_Y LINE5
#define VAL_M3_A_Y LINE6
#define VAL_M3_AT_Y LINE7

//定义表头结构体及数组
typedef struct UI_STR
{
    uint8_t X;
    uint8_t Y;
    String string;
};

//定义数据结构体及数组
typedef struct UI_DATA
{
    uint8_t X;
    uint8_t Y;
    float data;
};

enum UI_DATA_INDEX
{
    X_speed,
    X_target_speed,
    Y_speed,
    Y_target_speed,
    Z_speed,
    Z_target_speed,
    X_angle,
    X_target_angle,
    Y_angle,
    Y_target_angle,
    Z_angle,
    Z_target_angle
};

extern UI_STR UI_str[8];
extern UI_DATA UI_data[12];

void UI_begin();
void UI_update();

#endif