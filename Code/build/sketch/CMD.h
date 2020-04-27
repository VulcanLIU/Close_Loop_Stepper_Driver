#ifndef __CMD_H__
#define __CMD_H__

#include "Arduino.h"
#include "Stepper.h"

#define MAX_CMD_SIZE 96
#define BUFSIZE 4

static char cmdbuffer[BUFSIZE][MAX_CMD_SIZE]; //命令队列Buffer
static char serial_char;                      //单次从串口读出的字符
static int serial_count = 0;                  //单条命令长度计数器-大小不可超过MAX_CMD_SIZE
static int bufindr = 0;                       //process_command()读取Buffer位置
static int bufindw = 0;                       //get_command()写入Buffer位置
static int buflen = 0;                        //
static char *strchr_pointer;

void get_command();
void process_command();
void get_coordinates(uint8_t _G_code_);

bool code_seen(char code);
float code_value();
long code_value_long();


#endif