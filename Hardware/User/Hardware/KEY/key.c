#include "stm32f10x_lib.h"
#include "key.h"

/******************************** 变量定义 *********************************/
u8 Key0,Key1,WK_UP;	//定义键盘检测变量

//配置所有键盘相连的IO口	KEY0=PA13，KEY1=PA15，WK_UP=PA0
void Key_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	//配置 KEY0 PA13，KEY1 PA15	为上拉输入模式
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	//上拉输入模式 0为输入值
  	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//配置WK_UP PA0  为下拉输入模式
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	//下拉输入模式 1为输入值
  	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//关闭JTAG功能
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);			
}

u8 Key_Scan(void)
{
	Key0=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_13);	//读取KEY0状态
	Key1=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15);	//读取KEY1状态
	WK_UP=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0);	//读取WK_UP状态	
	if(Key0==0||Key1==0||WK_UP==1)	//有按键按下时
	{
		DelayMs(10);//去抖动
		
		//读取KEY0状态
		Key0=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_13);
		if(Key0==0)
		{
			while(!GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_13));//等待按键松开
			return 1;
		}	
		//读取KEY1状态
		Key1=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15);
		if(Key1==0)
		{
			while(!GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15));//等待按键松开
			return 2;
		}
		//读取WK_UP状态
		WK_UP=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0);
		if(WK_UP==1)
		{
			while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0));//等待按键松开
			return 3;
		}
	} 
	return 0;//无按键按下
}
