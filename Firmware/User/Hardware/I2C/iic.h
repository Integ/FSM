#ifndef __IIC_H
#define __IIC_H

#include "stm32f10x_lib.h"

#define I2C2_SLAVE_ADDRESS7    0xA6


void I2C_Config(void);	//IIC初始化

void I2C_WriteByte(unsigned char id,unsigned char write_address,unsigned char byte);	//I2C写数据

unsigned char I2C_ReadByte(unsigned char  id, unsigned char read_address);	//I2C读数据


#endif
