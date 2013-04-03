#include "stm32f10x_lib.h"
#include "led.h"

//DS0和DS1初始化 DS0～PA8	DS1～PD2
void LED_Init(void)
{
  	GPIO_InitTypeDef GPIO_InitStructure;
	//打开外设时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Pin = DS0 ;
	//为了配合PWM波，因此管脚采用浮动输入的方式
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
 
  	GPIO_InitStructure.GPIO_Pin = DS1 ;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  	GPIO_Init(GPIO_DS1, &GPIO_InitStructure);

	//关闭DS0 DS1
	DS0_OFF();
	DS1_OFF();
}

/**************************************************************
*					将特定端口输出取反
*  输入参数：GPIOX（GPIOA～D），GPIO_PIN（GPIO_Pin_0~15）
**************************************************************/
void GPIO_OutputBitToggle(GPIO_TypeDef* GPIOX,u16 GPIO_PIN)
{
	u8 ReadValu;
	ReadValu=GPIO_ReadOutputDataBit(GPIOX,GPIO_PIN);
	if(ReadValu==0x01)
		GPIO_ResetBits(GPIOX,GPIO_PIN);
	else if(ReadValu==0x00)
		GPIO_SetBits(GPIOX,GPIO_PIN);	
}

/**********************DS0操作函数****************************/
//DS0打开
void DS0_ON(void)
{
	GPIO_ResetBits(GPIO_DS0,DS0);
}

//DS0关闭
void DS0_OFF(void)
{
	GPIO_SetBits(GPIO_DS0,DS0);
}

//DS0取反
void DS0_Convs(void)
{
	GPIO_OutputBitToggle(GPIO_DS0,DS0);	
}

/**********************DS1操作函数****************************/
//DS1打开
void DS1_ON(void)
{
	GPIO_ResetBits(GPIO_DS1,DS1);
} 

//DS1关闭
void DS1_OFF(void)
{
	GPIO_SetBits(GPIO_DS1,DS1);
}

//DS1取反
void DS1_Convs(void)
{
	GPIO_OutputBitToggle(GPIO_DS1,DS1);	
}
