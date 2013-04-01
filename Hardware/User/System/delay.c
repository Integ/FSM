#include "stm32f10x_lib.h"
#include "delay.h"

/*******************************************************************************
* 
*           SysTick延迟Ms函数
* 
*******************************************************************************/
void DelayMs(u32 nms)
{
  	u32 CountNum;
	FlagStatus Status;		
	SysTick_CounterCmd(SysTick_Counter_Disable);	//停止计数	
	//关闭SysTick中断
	SysTick_ITConfig(DISABLE);
	//系统默认SysTick是8分频（HCLK/8）当前系统时钟72M的话 72/8 = 9MHZ
  	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
	CountNum=nms*9000;	//时钟为9MHz
	SysTick_SetReload(CountNum);	//装载计数值
	SysTick_CounterCmd(SysTick_Counter_Clear);	//清空计数器
	SysTick_CounterCmd(SysTick_Counter_Enable);	//开始计数
	do
	{
		Status=SysTick_GetFlagStatus(SysTick_FLAG_COUNT);
	}
	while(Status==RESET);	//等待计数完成
	SysTick_CounterCmd(SysTick_Counter_Disable);	//停止计数
	SysTick_CounterCmd(SysTick_Counter_Clear);	//清空计数器
}


