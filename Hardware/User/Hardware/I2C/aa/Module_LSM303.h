/* #include "Module_LSM303.h" */

#ifndef __Module_LSM303_H
#define __Module_LSM303_H
/*=====================================================================================================*/
/*=====================================================================================================*/
#define LSM303A_I2C_ADDR				((u8)0x31)
#define LSM303M_I2C_ADDR				((u8)0x3C)

#define LSM303A_CTRL_REG1				((u8)0x20)
#define LSM303A_CTRL_REG2				((u8)0x21)
#define LSM303A_CTRL_REG3				((u8)0x22)
#define LSM303A_CTRL_REG4				((u8)0x23)
#define LSM303A_CTRL_REG5				((u8)0x24)
#define LSM303A_HP_FILTER_RESET	((u8)0x25)
#define LSM303A_REFERENCE				((u8)0x26)
#define LSM303A_STATUS_REG			((u8)0x27)
#define LSM303A_OUT_X_L					((u8)0x28)
#define LSM303A_OUT_X_H					((u8)0x29)
#define LSM303A_OUT_Y_L					((u8)0x2A)
#define LSM303A_OUT_Y_H					((u8)0x2B)
#define LSM303A_OUT_Z_L					((u8)0x2C)
#define LSM303A_OUT_Z_H					((u8)0x2D)
#define LSM303A_INT1_CFG				((u8)0x30)
#define LSM303A_INT1_SOURCE			((u8)0x31)
#define LSM303A_INT1_INT1_THS		((u8)0x32)
#define LSM303A_INT1_DURATION		((u8)0x33)
#define LSM303A_INT2_CFG				((u8)0x34)
#define LSM303A_INT2_SOURCE			((u8)0x35)
#define LSM303A_INT2_THS				((u8)0x36)
#define LSM303A_INT2_DURATION		((u8)0x37)
#define LSM303A_MULTIPLE				((u8)0xA8)	// 連續讀取地址

#define LSM303M_CRA_REG					((u8)0x00)
#define LSM303M_CRB_REG					((u8)0x01)
#define LSM303M_MR_REG					((u8)0x02)
#define LSM303M_OUT_X_H					((u8)0x03)
#define LSM303M_OUT_X_L					((u8)0x04)
#define LSM303M_OUT_Y_H					((u8)0x05)
#define LSM303M_OUT_Y_L					((u8)0x06)
#define LSM303M_OUT_Z_H					((u8)0x07)
#define LSM303M_OUT_Z_L					((u8)0x08)
#define LSM303M_SR_REG					((u8)0x09)
#define LSM303M_IRA_REG					((u8)0x0A)
#define LSM303M_IRB_REG					((u8)0x0B)
#define LSM303M_IRC_REG					((u8)0x0C)
#define LSM303M_MULTIPLE				((u8)0x83)	// 連續讀取地址
/*=====================================================================================================*/
/*=====================================================================================================*/
extern void LSM303A_Init( void );
extern void LSM303M_Init( void );
extern void LSM303A_Read_Multiple( u8* );
extern void LSM303M_Read_Multiple( u8* );
/*=====================================================================================================*/
/*=====================================================================================================*/
/* Define Data Struct */
// typedef struct {
// 	u16 X_Axis;
// 	u16 Y_Axis;
// 	u16 Z_Axis;
// } LSM303A_Struct;
// typedef struct {
// 	u16 X_Axis;
// 	u16 Y_Axis;
// 	u16 Z_Axis;
// } LSM303M_Struct;
/*=====================================================================================================*/
/*=====================================================================================================*/
#endif
