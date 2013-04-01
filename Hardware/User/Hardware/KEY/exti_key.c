#include "stm32f10x_lib.h"
#include "exti_key.h"
#include "key.h"
#include "led.h"

/*****************外部中断0处理函数*********************/
void EXTI0_IRQHandler(void)
{
	DelayMs(10);
	//读取WK_UP状态
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==1)
	{
		//DS0和DS1均取反
		DS0_Convs();
		DS1_Convs();
	}
	//软件清除中断挂起位
	EXTI_ClearITPendingBit(EXTI_Line0);
}


/*****************外部中断10～15处理函数*********************/
void EXTI15_10_IRQHandler(void)
{
	DelayMs(10);
	//Key0按下 DS0取反
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_13)==0)
		DS0_Convs();
	//Key1按下 DS1取反
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15)==0)
		DS1_Convs();
	
	//软件清除中断挂起位
	EXTI_ClearITPendingBit(EXTI_Line13);
	EXTI_ClearITPendingBit(EXTI_Line15);	
}

/**********************按键外部中断初始化函数**********************/
void EXTIKey_Init(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/********************配置键盘相应的IO口***********************/
	//配置 KEY0 PA13，KEY1 PA15	为上拉输入模式
	//配置WK_UP PA0  为下拉输入模式
	Key_Init();

	/***************************配置外部中断优先级*******************************
	*					按键优先级：KEY0=KEY1>WK_UP
	****************************************************************************/
	//配置中断优先级组2
  	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  
  
  	//设置EXTI0优先级  WK_UP
  	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQChannel; //中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =  2;  //强占优先级
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;//次优先级
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  //通道中断使能
  	NVIC_Init(&NVIC_InitStructure);//初始化中断
	//设置EXTI13 EXTI15优先级	   KEY0  KEY1
  	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQChannel; //中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =  2;  //强占优先级
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;//次优先级
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  //通道中断使能
  	NVIC_Init(&NVIC_InitStructure);//初始化中断

	/*********************配置外部中断****************************
	*  EXTI0	PA0		WK_UP 	上升沿触发
	*  EXTI13 	PA13 	KEY0 	下降沿触发
	*  EXTI13	PA15	KEY1	下降沿触发
	*************************************************************/
	//配置外部中断线 把EXTI0 连接到PA0	WK_UP
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);
	//配置外部中断线 把EXTI13 连接到PA13 KEY0
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource13);
	//配置外部中断线 把EXTI15 连接到PA15 KEY1
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource15);
	
	//配置EXTI0 上升沿触发中断
	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	//配置EXTI13和EXTI15 下降沿触发中断
	EXTI_InitStructure.EXTI_Line=EXTI_Line13|EXTI_Line15;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure);	
}
