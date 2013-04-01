#ifndef __SENSORS_H
#define __SENSORS_H

#include "stm32f10x_lib.h"

//定义器件在IIC总线中的从地址
#define	HMC5883L_Addr   0x3C	//磁场传感器器件地址
#define	ADXL345_Addr    0xA6	//加速度传感器器件地址
#define	BMP085_Addr     0xee	//气压传感器器件地址
#define	L3G4200_Addr    0xD2	//陀螺仪传感器器件地址

//ADXL345 寄存器
#define ADXL345_DEVID  0x00 
#define ADXL345_THRESH_TAP 0x1D 
#define ADXL345_OFSX  0x1E 
#define ADXL345_OFSY 0x1F 
#define ADXL345_OFSZ 0x20 
#define ADXL345_DUR 0x21 
#define ADXL345_Latent 0x22 
#define ADXL345_Window 0x23 
#define ADXL345_THRESH_ACT 0x24 
#define ADXL345_THRESH_INACT 0x25 
#define ADXL345_TIME_INACT 0x26 
#define ADXL345_ACT_INACT_CTL 0x27 
#define ADXL345_THRESH_FF 0x28 
#define ADXL345_TIME_FF 0x29  
#define ADXL345_TAP_AXES 0x2A 
#define ADXL345_ACT_TAP_STATUS 0x2B 
#define ADXL345_BW_RATE 0x2C 
#define ADXL345_POWER_CTL 0x2D 
#define ADXL345_INT_ENABLE 0x2E 
#define ADXL345_INT_MAP 0x2F 
#define ADXL345_INT_SOURCE 0x30 
#define ADXL345_DATA_FORMAT 0x31 
#define ADXL345_DATAX0 0x32 
#define ADXL345_DATAX1 0x33 
#define ADXL345_DATAY0 0x34 
#define ADXL345_DATAY1 0x35 
#define ADXL345_DATAZ0 0x36 
#define ADXL345_DATAZ1 0x37 
#define ADXL345_FIFO_CTL 0x38 
#define ADXL345_FIFO_STATUS 0x39 

//L3G4200D 寄存器
#define L3G4200D_CTRL_REG1 0x20
#define L3G4200D_CTRL_REG2 0x21
#define L3G4200D_CTRL_REG3 0x22
#define L3G4200D_CTRL_REG4 0x23
#define L3G4200D_CTRL_REG5 0x24
#define L3G4200D_OUT_X_L 0x28
#define L3G4200D_OUT_X_H 0x29
#define L3G4200D_OUT_Y_L 0x2A
#define L3G4200D_OUT_Y_H 0x2B
#define L3G4200D_OUT_Z_L 0x2C
#define L3G4200D_OUT_Z_H 0x2D


void ADXL345_Init(void);
void L3G4200D_Init(void);
void Read_ADXL345(u8 *Data);
void Read_L3G4200D(u8 *Data);

#endif
