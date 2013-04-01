/* #include "Module_ADXL345.h" */

#ifndef __Module_ADXL345_H
#define __Module_ADXL345_H
/*=====================================================================================================*/
/*=====================================================================================================*/
#define ADXL345_I2C_ADDR          ((u8)0xA6)

#define ADXL345_ID                ((u8)0x00)	// ADXL345_ID	= 0xE5
#define ADXL345_THRESH_TAP        ((u8)0x1D)
#define ADXL345_OFSX              ((u8)0x1E)	// X軸偏移 15.6mg/LSB
#define ADXL345_OFSY              ((u8)0x1F)	// Y軸偏移 15.6mg/LSB
#define ADXL345_OFSZ              ((u8)0x20)	// Z軸偏移 15.6mg/LSB
#define ADXL345_DUR               ((u8)0x21)	// 敲擊持續時間
#define ADXL345_Latent            ((u8)0x22)	// 敲擊延遲
#define ADXL345_WIN               ((u8)0x23)	// 敲擊窗口
#define ADXL345_THRESH_ACT        ((u8)0x24)	// 活動閾值
#define ADXL345_THRESH_INACT      ((u8)0x25)	// 靜止閾值
#define ADXL345_TIME_INACT        ((u8)0x26)	// 靜止時間
#define ADXL345_ACT_INACT_CTL     ((u8)0x27)	// 軸使能控制活動和靜止檢測
#define ADXL345_THRESH_FF         ((u8)0x28)	// 自由落體閾值
#define ADXL345_TIME_FF           ((u8)0x29)	// 自由落體時間
#define ADXL345_TAP_AXES          ((u8)0x2A)	// 單擊/雙擊軸控制
#define ADXL345_ACT_TAP_STATUS    ((u8)0x2B)	// 單擊/雙擊源
#define ADXL345_BW_RATE           ((u8)0x2C)	// 數據速率及功率模式
#define ADXL345_POWER_CTL         ((u8)0x2D)	// 省電特性
#define ADXL345_INT_ENABLE        ((u8)0x2E)	// 中斷使能
#define ADXL345_INT_MAP           ((u8)0x2F)	// 中斷映射
#define ADXL345_INT_SOURCE        ((u8)0x30)	// 中斷源
#define ADXL345_DATA_FORMAT       ((u8)0x31)	// 數據格式
#define ADXL345_DATAX0            ((u8)0x32)	// X軸數據0
#define ADXL345_DATAX1            ((u8)0x33)	// X軸數據1
#define ADXL345_DATAY0            ((u8)0x34)	// Y軸數據0
#define ADXL345_DATAY1            ((u8)0x35)	// Y軸數據1
#define ADXL345_DATAZ0            ((u8)0x36)	// Z軸數據0
#define ADXL345_DATAZ1            ((u8)0x37)	// Z軸數據1
#define ADXL345_FIFO_CTL          ((u8)0x38)	// FIFO控制
#define ADXL345_FIFO_STATUS       ((u8)0x39)	// FIFO狀態

#define ADXL345_MULTIPLE          ((u8)0x32)

#define ADXL345_s2g               (3.9)		// mg/LSB
#define ADXL345_s4g               (7.8)		// mg/LSB
#define ADXL345_s8g      	      (15.6)	// mg/LSB
#define ADXL345_s16g              (31.2)	// mg/LSB
/*=====================================================================================================*/
/*=====================================================================================================*/
extern void ADXL345_Init( void );
extern void ADXL345_Read_Multiple( u8* );
/*=====================================================================================================*/
/*=====================================================================================================*/
// typedef union {
// 	s16 Data;
// 	HL_Struct Byte;
// }	ADXL345_union;
// typedef struct {
// 	ADXL345_union X;
// 	ADXL345_union Y;
// 	ADXL345_union Z;
// }	ADXL345_Struct;
/*=====================================================================================================*/
/*=====================================================================================================*/
#endif
