/* #include "Module_L3G4200.h" */

#ifndef __Module_L3G4200_H
#define __Module_L3G4200_H
/*=====================================================================================================*/
/*=====================================================================================================*/
#define L3G4200_I2C_ADDR				((u8)0xD2)

#define L3G4200_WHO_AM_I				((u8)0x0F)	// 0xD3
#define L3G4200_CTRL_REG1				((u8)0x20)	
#define L3G4200_CTRL_REG2				((u8)0x21)	
#define L3G4200_CTRL_REG3				((u8)0x22)	
#define L3G4200_CTRL_REG4				((u8)0x23)	
#define L3G4200_CTRL_REG5				((u8)0x24)	
#define L3G4200_REFERENCE				((u8)0x25)	
#define L3G4200_OUT_TEMP				((u8)0x26)	
#define L3G4200_STATUS_REG			((u8)0x27)
#define L3G4200_OUT_X_L					((u8)0x28)
#define L3G4200_OUT_X_H					((u8)0x29)
#define L3G4200_OUT_Y_L					((u8)0x2A)	
#define L3G4200_OUT_Y_H					((u8)0x2B)	
#define L3G4200_OUT_Z_L					((u8)0x2C)	
#define L3G4200_OUT_Z_H					((u8)0x2D)	
#define L3G4200_FIFO_CTRL_REG		((u8)0x2E)	
#define L3G4200_FIFO_SRC_REG		((u8)0x2F)
#define L3G4200_INT1_CFG				((u8)0x30)	
#define L3G4200_INT1_SRC				((u8)0x31)	
#define L3G4200_INT1_TSH_XH			((u8)0x32)
#define L3G4200_INT1_TSH_XL			((u8)0x33)	
#define L3G4200_INT1_TSH_YH			((u8)0x34)	
#define L3G4200_INT1_TSH_YL			((u8)0x35)	
#define L3G4200_INT1_TSH_ZH			((u8)0x36)	
#define L3G4200_INT1_TSH_ZL			((u8)0x37)	
#define L3G4200_INT1_DURATION		((u8)0x38)
#define L3G4200_MULTIPLE				((u8)0xA8)	// 連續讀取地址

#define L3G4200_s250dps					(0.00875)		// 8.75mdps
#define L3G4200_s500dps					(0.01750)		// 17.5mdps
#define L3G4200_s2000dps				(0.07000)		// 70mdps
/*=====================================================================================================*/
/*=====================================================================================================*/
extern void L3G4200_Init( void );
extern void L3G4200_Read_Multiple( u8* );
/*=====================================================================================================*/
/*=====================================================================================================*/
/* Define Data Struct */
// typedef struct {
// 	u16 X_Axis;
// 	u16 Y_Axis;
// 	u16 Z_Axis;
// } L3G4200_Struct;
/*=====================================================================================================*/
/*=====================================================================================================*/
#endif
