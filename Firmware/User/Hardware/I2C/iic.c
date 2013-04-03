#include "stm32f10x_lib.h"
#include "iic.h"
/**********************************************************************/
/*IIC配置		         				                              */
/*																	  */
/**********************************************************************/
void I2C_Config()
{
	GPIO_InitTypeDef GPIO_InitStructure;

	 I2C_InitTypeDef I2C_InitStructure;
	 
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
	/* Configure IO connected to IIC*********************/
	 GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_10 | GPIO_Pin_11;
  	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
 	 GPIO_Init(GPIOB, &GPIO_InitStructure);

	 I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
 	 I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
 	 I2C_InitStructure.I2C_OwnAddress1 = I2C2_SLAVE_ADDRESS7;
 	 I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
 	 I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
 	 I2C_InitStructure.I2C_ClockSpeed = 200000;
	 
	 I2C_Cmd(I2C2, ENABLE);   

	 I2C_Init(I2C2, &I2C_InitStructure);
}
/**********************************************************************/
/*IIC写一个字节	         				                              */
/*																	  */
/**********************************************************************/
void I2C_WriteByte(unsigned char id,unsigned char write_address,unsigned char byte)
{
	I2C_GenerateSTART(I2C2,ENABLE);
	//产生起始条件
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT));
	//等待ACK
	I2C_Send7bitAddress(I2C2,id,I2C_Direction_Transmitter);
	//向设备发送设备地址
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	//等待ACK
	I2C_SendData(I2C2, write_address);
	//寄存器地址
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	//等待ACK
	I2C_SendData(I2C2, byte);
	//发送数据
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	//发送完成
	I2C_GenerateSTOP(I2C2, ENABLE);
	//产生结束信号
}
/**********************************************************************/
/*IIC读数据	         				                              	  */
/*																	  */
/**********************************************************************/
unsigned char I2C_ReadByte(unsigned char  id, unsigned char read_address)
{  
	unsigned char temp; 	

	while(I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY));
  	//等待I2C
  	I2C_GenerateSTART(I2C2, ENABLE);
  	//产生起始信号
  	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT));
    //EV5
  	I2C_Send7bitAddress(I2C2, id, I2C_Direction_Transmitter);
	//发送地址
  	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
  	//EV6
  	I2C_Cmd(I2C2, ENABLE);
 	//重新设置可以清楚EV6
  	I2C_SendData(I2C2, read_address);  
	//发送读得地址
  	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
  	//EV8 
  	I2C_GenerateSTART(I2C2, ENABLE);
	//重新发送
  	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT));
  	//EV5
  	I2C_Send7bitAddress(I2C2, id, I2C_Direction_Receiver);
  	//发送读地址
  	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
  	//EV6  
    I2C_AcknowledgeConfig(I2C2, DISABLE);
    I2C_GenerateSTOP(I2C2, ENABLE);
	//关闭应答和停止条件产生
    while(!(I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED)));
	      
    temp = I2C_ReceiveData(I2C2);
   
  	I2C_AcknowledgeConfig(I2C2, ENABLE);

	return temp;
}

