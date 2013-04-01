/* #include "STM32_I2C.h" */

#ifndef __STM32_I2C_H
#define __STM32_I2C_H
/*====================================================================================================*/
/*====================================================================================================*/
void I2C_Config( void );
extern void I2C_WriteReg( u8, u8, u8 );
extern void I2C_ReadReg( u8, u8, u8* ); 
extern void I2C_ReadMultiple( u8, u8, u8, u8* );

extern void I2C_DMA_ReadReg( u8* ReadBuf, u8 SlaveAddr, u8 ReadAddr, u8 NumByte );
extern void I2C_DMA_WriteReg( u8* WriteBuf, u8 SlaveAddr, u8 WriteAddr, u8 NumByte );
void I2C1_EV_IRQ( void );
void I2C1_ER_IRQ( void );
void I2C1_Send_DMA_IRQ( void );
void I2C1_Recv_DMA_IRQ( void );
/*====================================================================================================*/
/*====================================================================================================*/
#endif
