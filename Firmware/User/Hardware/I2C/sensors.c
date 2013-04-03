#include "stm32f10x_lib.h"
#include "iic.h"
#include "sensors.h"


void ADXL345_Init(void)
{
	I2C_WriteByte(ADXL345_Addr,ADXL345_BW_RATE,0x0A);   //速率设定3200hz 参考pdf13页
	I2C_WriteByte(ADXL345_Addr,ADXL345_POWER_CTL,0x08);   //电源工作方式设置 参考pdf24页
	I2C_WriteByte(ADXL345_Addr,ADXL345_DATA_FORMAT,0x0B);	// +/-16g，13bit
	I2C_WriteByte(ADXL345_Addr,ADXL345_INT_ENABLE,0x80);   //使能 DATA_READY 中断
//	I2C_WriteByte(ADXL345_Addr,ADXL345_OFSX,0x00);   //X 偏移量 根据测试传感器的状态写入 参考pdf29页
//	I2C_WriteByte(ADXL345_Addr,ADXL345_OFSY,0x00);   //Y 偏移量 根据测试传感器的状态写入 参考pdf29页
//	I2C_WriteByte(ADXL345_Addr,ADXL345_OFSZ,0x05);   //Z 偏移量 根据测试传感器的状态写入 参考pdf29页	
}

void L3G4200D_Init(void)
{
	I2C_WriteByte(L3G4200_Addr,L3G4200D_CTRL_REG1, 0xff);	//800Hz
	I2C_WriteByte(L3G4200_Addr,L3G4200D_CTRL_REG2, 0x03);	//HPF截止频率8Hz
	I2C_WriteByte(L3G4200_Addr,L3G4200D_CTRL_REG3, 0x08);
	I2C_WriteByte(L3G4200_Addr,L3G4200D_CTRL_REG4, 0x30);	//+-2000dps
	I2C_WriteByte(L3G4200_Addr,L3G4200D_CTRL_REG5, 0x00);	//不过HPF不过LPF2
}

void Read_ADXL345(u8 *Data)
{
	Data[0] = I2C_ReadByte(ADXL345_Addr,ADXL345_DATAX0);//OUT_X_L_A
	Data[1] = I2C_ReadByte(ADXL345_Addr,ADXL345_DATAX1);//OUT_X_H_A

	Data[2] = I2C_ReadByte(ADXL345_Addr,ADXL345_DATAY0);//OUT_Y_L_A
	Data[3] = I2C_ReadByte(ADXL345_Addr,ADXL345_DATAY1);//OUT_Y_H_A

	Data[4] = I2C_ReadByte(ADXL345_Addr,ADXL345_DATAZ0);//OUT_Z_L_A
	Data[5] = I2C_ReadByte(ADXL345_Addr,ADXL345_DATAZ1);//OUT_Z_H_A
}


void Read_L3G4200D(u8 *Data)
{
	Data[0] = I2C_ReadByte(L3G4200_Addr,L3G4200D_OUT_X_L);
	Data[1] = I2C_ReadByte(L3G4200_Addr,L3G4200D_OUT_X_H);

	Data[2] = I2C_ReadByte(L3G4200_Addr,L3G4200D_OUT_Y_L);
	Data[3] = I2C_ReadByte(L3G4200_Addr,L3G4200D_OUT_Y_H);

	Data[4] = I2C_ReadByte(L3G4200_Addr,L3G4200D_OUT_Z_L);
	Data[5] = I2C_ReadByte(L3G4200_Addr,L3G4200D_OUT_Z_H);
}

