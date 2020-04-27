#ifndef __CIRCULAR_ARRAY__
#define __CIRCULAR_ARRAY__

class CircularArray_float
{
public:
    //环形数组
    float Buffer[10];
    //控制环形数组使用的变量
    int bufindr = 0; //process_command()读取Buffer位置
    int bufindw = 0; //get_command()写入Buffer位置
    int buflen = 0;  //Buffer中的命令总数-大小不可超过BUFSIZE
    char *strchr_pointer;

private:
    //数组长度
};

#endif