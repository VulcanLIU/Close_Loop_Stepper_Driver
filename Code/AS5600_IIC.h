#ifndef _AS5600_IIC_H
#define _AS5600_IIC_H

#include "Arduino.h"

void AS5600_IIC_Init(void);
void AS5600_IIC_Init(u8 SDA_pin,u8 SCL_pin);

void AS5600_IIC_Write_OneByte(u8 deviceaddr,u8 writeaddr,u8 writedata);

u8 AS5600_IIC_Read_OneByte(u8 deviceaddr,u8 readaddr);

#endif // _Y_IIC_H
