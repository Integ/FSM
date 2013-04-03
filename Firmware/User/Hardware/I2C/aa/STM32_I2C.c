/*=====================================================================================================*/
/*=====================================================================================================*/
#include "stm32f10x_lib.h"
#include "STM32_I2C.h"
/*=====================================================================================================*/
/*=====================================================================================================*/
#define I2C1_DR_Address		0x40005410
#define I2C2_DR_Address		0x40005810
#define Transmitter				0x00
#define Receiver					0x01

static vu8 MasterDirection = Transmitter;
static u8 I2C_SlaveAddr;
static u8 I2C_RegAddr;
static u8 I2C_NumByte = 0;
static bool check_begin = FALSE;
static bool OffsetDone = FALSE;
u8 I2C_NumByteWritingNow = 0;
u8* I2C_pBuf = 0;
static vu8 PV_flag_1;
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : I2C_Config
**功能 : 
**輸入 : 
**輸出 : 
**使用 : 
**=====================================================================================================*/
/*=====================================================================================================*/
void I2C_Config( void )
{
	NVIC_InitTypeDef NVIC_Struct;
	GPIO_InitTypeDef GPIO_Structure;
	I2C_InitTypeDef I2C_Structure;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_Struct.NVIC_IRQChannel = DMA1_Channel6_IRQChannel;
	NVIC_Struct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Struct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_Struct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_Struct);
	NVIC_Struct.NVIC_IRQChannel = DMA1_Channel7_IRQChannel;
	NVIC_Struct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Struct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_Struct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_Struct);
	NVIC_Struct.NVIC_IRQChannel = I2C1_ER_IRQChannel;
	NVIC_Struct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_Struct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Struct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_Struct);
	NVIC_Struct.NVIC_IRQChannel = I2C1_EV_IRQChannel;
	NVIC_Struct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_Struct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Struct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_Struct);

	/* SCL PB6 */	/* SDA PB7 */
	GPIO_Structure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_Structure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Structure.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_Init(GPIOB, &GPIO_Structure);

	I2C_DeInit(I2C1);
	I2C_Cmd(I2C1, DISABLE);
	I2C_Structure.I2C_Mode = I2C_Mode_I2C;
	I2C_Structure.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_Structure.I2C_OwnAddress1 = 0x3A;
	I2C_Structure.I2C_Ack = I2C_Ack_Enable;
	I2C_Structure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_Structure.I2C_ClockSpeed = 400000;
	I2C_Cmd(I2C1, ENABLE);
	I2C_Init(I2C1, &I2C_Structure);
//	I2C_AcknowledgeConfig(I2C1, ENABLE);
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : I2C_WriteReg
**功能 : 
**輸入 : 
**輸出 : 
**使用 : 
**=====================================================================================================*/
/*=====================================================================================================*/
void I2C_WriteReg( u8 SloveAddr, u8 WriteAddr, u8 WriteData )
{
	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
	I2C_AcknowledgeConfig(I2C1, ENABLE);
	I2C_GenerateSTART(I2C1, ENABLE);

	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
	I2C_Send7bitAddress(I2C1, SloveAddr, I2C_Direction_Transmitter);

	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

	I2C_Cmd(I2C1, ENABLE);
	I2C_SendData(I2C1, WriteAddr);

	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	I2C_SendData(I2C1, WriteData);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	I2C_GenerateSTOP(I2C1, ENABLE);
	I2C_AcknowledgeConfig(I2C1, ENABLE);
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : I2C_ReadReg
**功能 : 
**輸入 : 
**輸出 : 
**使用 : 
**=====================================================================================================*/
/*=====================================================================================================*/
void I2C_ReadReg( u8 SloveAddr, u8 ReadAddr, u8* ReadData )
{
	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
	
	I2C_AcknowledgeConfig(I2C1, ENABLE);
	I2C_GenerateSTART(I2C1, ENABLE);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

	I2C_Send7bitAddress(I2C1, SloveAddr, I2C_Direction_Transmitter);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	
	I2C_SendData(I2C1, ReadAddr);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	I2C_GenerateSTART(I2C1, ENABLE);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

	I2C_Send7bitAddress(I2C1, SloveAddr, I2C_Direction_Receiver);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
	
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED));
	*ReadData = I2C_ReceiveData(I2C1);
	I2C_AcknowledgeConfig(I2C1, DISABLE);
	I2C_GenerateSTOP(I2C1, ENABLE);
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : I2C_ReadMultiple
**功能 : 
**輸入 : 
**輸出 : 
**使用 : 
**=====================================================================================================*/
/*=====================================================================================================*/
void I2C_ReadMultiple( u8 SloveAddr, u8 ReadAddr, u8 ReadNum, u8* ReadData )
{
	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
	I2C_AcknowledgeConfig(I2C1, ENABLE);
	I2C_GenerateSTART(I2C1, ENABLE);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

	I2C_Send7bitAddress(I2C1, SloveAddr, I2C_Direction_Transmitter);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

	I2C_SendData(I2C1, ReadAddr);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	I2C_GenerateSTART(I2C1, ENABLE);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
	I2C_Send7bitAddress(I2C1, SloveAddr, I2C_Direction_Receiver);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
	while(ReadNum) {
		if(ReadNum == 1) {
			I2C_AcknowledgeConfig(I2C1, DISABLE);
			I2C_GenerateSTOP(I2C1, ENABLE);
		}
		if(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED)) {      
			*ReadData = I2C_ReceiveData(I2C1);
			ReadData++;
			ReadNum--;
		} 
	}
	I2C_AcknowledgeConfig(I2C1, DISABLE);
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : I2C_DMA_ReadReg
**功能 : 
**輸入 : 
**輸出 : 
**使用 : 
**=====================================================================================================*/
/*=====================================================================================================*/
void I2C_DMA_ReadReg( u8* ReadBuf, u8 SlaveAddr, u8 ReadAddr, u8 NumByte )
{
	DMA_InitTypeDef DMA_Struct;

	/* PV operation */
	if(PV_flag_1 != 0)
		return;
	PV_flag_1 = 1;

	/* DMA initialization */
	DMA_DeInit(DMA1_Channel7);
	DMA_Struct.DMA_PeripheralBaseAddr = (u32)I2C1_DR_Address;
	DMA_Struct.DMA_MemoryBaseAddr = (u32)ReadBuf;
	DMA_Struct.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_Struct.DMA_BufferSize = NumByte;
	DMA_Struct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_Struct.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_Struct.DMA_PeripheralDataSize = DMA_MemoryDataSize_Byte;
	DMA_Struct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_Struct.DMA_Mode = DMA_Mode_Normal;
	DMA_Struct.DMA_Priority = DMA_Priority_VeryHigh;
	DMA_Struct.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel7, &DMA_Struct);
	DMA_ITConfig(DMA1_Channel7, DMA_IT_TC, ENABLE);

	/* initialize static parameter */
	MasterDirection = Receiver;

	/* initialize static parameter according to input parameter */
	I2C_SlaveAddr = SlaveAddr;
	I2C_RegAddr = ReadAddr;
	OffsetDone = FALSE;

	I2C_AcknowledgeConfig(I2C1, ENABLE);
	I2C_ITConfig(I2C1, I2C_IT_EVT | I2C_IT_ERR , ENABLE);

	/* Send START condition */
	I2C_GenerateSTOP(I2C1, DISABLE);
	I2C_GenerateSTART(I2C1, ENABLE);
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : I2C_DMA_WriteReg
**功能 : 
**輸入 : 
**輸出 : 
**使用 : 
**=====================================================================================================*/
/*=====================================================================================================*/
void I2C_DMA_WriteReg( u8* WriteBuf, u8 SlaveAddr, u8 WriteAddr, u8 NumByte )
{
	DMA_InitTypeDef  DMA_Struct;

	/* PV operation */
	if(PV_flag_1 != 0)
		return;
	PV_flag_1 = 1;

	I2C_pBuf = WriteBuf;
	I2C_NumByte = NumByte;

	/* DMA initialization */
	DMA_DeInit(DMA1_Channel6);
	DMA_Struct.DMA_PeripheralBaseAddr = (u32)I2C1_DR_Address;
	DMA_Struct.DMA_MemoryBaseAddr = (u32)WriteBuf;
	DMA_Struct.DMA_DIR = DMA_DIR_PeripheralDST;
	DMA_Struct.DMA_BufferSize = NumByte;
	DMA_Struct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_Struct.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_Struct.DMA_PeripheralDataSize = DMA_MemoryDataSize_Byte;
	DMA_Struct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_Struct.DMA_Mode = DMA_Mode_Normal;
	DMA_Struct.DMA_Priority = DMA_Priority_VeryHigh;
	DMA_Struct.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel6, &DMA_Struct);
	DMA_ITConfig(DMA1_Channel6, DMA_IT_TC, ENABLE);

	/* initialize static parameter */
	MasterDirection = Transmitter;

	/* initialize static parameter according to input parameter */ 
	I2C_SlaveAddr = SlaveAddr;
	I2C_RegAddr = WriteAddr;
	OffsetDone = FALSE;

	I2C_AcknowledgeConfig(I2C1, ENABLE);
	I2C_ITConfig(I2C1, I2C_IT_EVT | I2C_IT_BUF | I2C_IT_ERR, ENABLE);

	/* Send START condition */
	I2C_GenerateSTOP(I2C1, DISABLE);
	I2C_GenerateSTART(I2C1, ENABLE);

	I2C_NumByteWritingNow = NumByte;
}
/*=====================================================================================================*/
/*=====================================================================================================*/
void I2C1_EV_IRQ( void )
{
	u32 lastevent = I2C_GetLastEvent(I2C1);

	switch(lastevent) {
/************************** Master Invoke **************************************/
		case I2C_EVENT_MASTER_MODE_SELECT:	/* EV5 */
			if(MasterDirection == Receiver) {
				if(!OffsetDone)
					I2C_Send7bitAddress(I2C1, I2C_SlaveAddr, I2C_Direction_Transmitter);
				else {
					/* Send slave Address for read */
					I2C_Send7bitAddress(I2C1, I2C_SlaveAddr, I2C_Direction_Receiver);
					OffsetDone = FALSE;
				}
			}
			else {
				/* Send slave Address for write */
				I2C_Send7bitAddress(I2C1, I2C_SlaveAddr, I2C_Direction_Transmitter);
			}
			I2C_ITConfig(I2C1, I2C_IT_BUF, ENABLE);
			break;
/********************** Master Receiver events ********************************/
		case I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED:	/* EV6 */
			I2C_ITConfig(I2C1, I2C_IT_EVT | I2C_IT_BUF, DISABLE);
			// without it, no NAK signal on bus after last Data
			// I2C data line would be hold low
			I2C_DMALastTransferCmd(I2C1, ENABLE);
			I2C_DMACmd(I2C1, ENABLE);
			DMA_Cmd(DMA1_Channel7, ENABLE);
			break;
		case I2C_EVENT_MASTER_BYTE_RECEIVED:	/* EV7 */
			// MSL BUSY RXNE 0x30040
			break;
/************************* Master Transmitter events **************************/
		case I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED:	/* EV8 just after EV6 */
			// BUSY, MSL, ADDR, TXE and TRA 0x70082
			if(check_begin) {
				check_begin = FALSE;
				I2C_ITConfig(I2C1, I2C_IT_EVT | I2C_IT_BUF |I2C_IT_ERR, DISABLE);
				I2C_GenerateSTOP(I2C1, ENABLE);
				// !! write over
				I2C_pBuf += I2C_NumByteWritingNow;
				I2C_RegAddr += I2C_NumByteWritingNow;
				I2C_NumByte -= I2C_NumByteWritingNow;
				if(I2C_NumByte>0)
					I2C_DMA_WriteReg(I2C_pBuf, I2C_SlaveAddr, I2C_RegAddr, I2C_NumByte);
				else
					PV_flag_1 = 0;
				break;
			}
			I2C_SendData(I2C1, I2C_RegAddr);
			OffsetDone = TRUE;
			break;
		case I2C_EVENT_MASTER_BYTE_TRANSMITTING:		/* EV8 I2C_EVENT_MASTER_BYTE_TRANSMITTING*/
			if(MasterDirection == Receiver) {
				I2C_ITConfig(I2C1, I2C_IT_BUF , DISABLE);
				while ((I2C1->CR1 & 0x200) == 0x200); 
				I2C_GenerateSTART(I2C1, ENABLE);
			}
			else {
				I2C_ITConfig(I2C1, I2C_IT_EVT | I2C_IT_BUF, DISABLE);
				I2C_DMACmd(I2C1, ENABLE);
				DMA_Cmd(DMA1_Channel6, ENABLE);
			}
			break;
		case I2C_EVENT_MASTER_BYTE_TRANSMITTED:		/* EV8-2 */
			// TRA, BUSY, MSL, TXE and BTF 0x70084
			break;
	}
}
/*=====================================================================================================*/
/*=====================================================================================================*/
void I2C1_ER_IRQ( void )
{
	if(I2C_GetFlagStatus(I2C1, I2C_FLAG_AF)) {
		if(check_begin)
			I2C_GenerateSTART(I2C1, ENABLE);
		else if(I2C1->SR2&0x01) {
			// !! receive over
			I2C_GenerateSTOP(I2C1, ENABLE);
			PV_flag_1 = 0;
		}
		I2C_ClearFlag(I2C1, I2C_FLAG_AF);
	}
	if(I2C_GetFlagStatus(I2C1, I2C_FLAG_BERR)) {
		if(I2C1->SR2&0x01) {
			I2C_GenerateSTOP(I2C1, ENABLE);
			PV_flag_1 = 0;
		}
		I2C_ClearFlag(I2C1, I2C_FLAG_BERR);
	}
}
/*=====================================================================================================*/
/*=====================================================================================================*/
void I2C1_Send_DMA_IRQ( void )
{
	if(DMA_GetFlagStatus(DMA1_FLAG_TC6)) {
		if(I2C1->SR2 & 0x01) {		// master send DMA finish, check process later
			// DMA1-6 (I2C1 Tx DMA)transfer complete ISR
			I2C_DMACmd(I2C1, DISABLE);
			DMA_Cmd(DMA1_Channel6, DISABLE);
			// wait until BTF
			while(!(I2C1->SR1 & 0x04));
			I2C_GenerateSTOP(I2C1, ENABLE);
			// wait until BUSY clear
			while(I2C1->SR2 & 0x02);
			I2C_ITConfig(I2C1, I2C_IT_EVT, ENABLE); // use interrupt to handle check process
			check_begin = TRUE;
			if(I2C1->CR1 & 0x200)
				I2C1->CR1 &= 0xFDFF;
			I2C_GenerateSTART(I2C1, ENABLE);
		}
		DMA_ClearFlag(DMA1_FLAG_TC6);
	}
	if(DMA_GetFlagStatus(DMA1_FLAG_GL6))
		DMA_ClearFlag(DMA1_FLAG_GL6);
	if(DMA_GetFlagStatus(DMA1_FLAG_HT6))
		DMA_ClearFlag(DMA1_FLAG_HT6);
}
/*=====================================================================================================*/
/*=====================================================================================================*/
void I2C1_Recv_DMA_IRQ( void )
{
	if(DMA_GetFlagStatus(DMA1_FLAG_TC7)) {
		if(I2C1->SR2 & 0x01) {
			I2C_DMACmd(I2C1, DISABLE);
			I2C_GenerateSTOP(I2C1, ENABLE);
			PV_flag_1 = 0;
		}
		DMA_ClearFlag(DMA1_FLAG_TC7);
	}
	if(DMA_GetFlagStatus(DMA1_FLAG_GL7))
		DMA_ClearFlag(DMA1_FLAG_GL7);
	if(DMA_GetFlagStatus(DMA1_FLAG_HT7))
		DMA_ClearFlag(DMA1_FLAG_HT7);
}
/*=====================================================================================================*/
/*=====================================================================================================*/
