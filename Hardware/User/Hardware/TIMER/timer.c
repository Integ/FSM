#include "stm32f10x_lib.h"
#include "timer.h"

//定时器3的中断服务程序
void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET)
	{
		//DS1状态反转
		DS0_Convs();
	}
	//清除TIM3 的更新标志位
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);	
}

/************************定时器3配置函数**********************************
*						1s溢出时间计算公式：
*	(1+TIM_Prescaler )/72M)*(1+TIM_Period )=((1+7199)/72M)*(1+9999)=1秒 
*				定时器3默认为外部时钟 APB1×2=72MHz
*							向上计数模式
*************************************************************************/
void Timer_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	
	//打开TIM3时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
		
	/*******************配置TIM3的中断优先级**********************/
	//2位抢占优先级  2位子优先级
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	// Enable the TIM3 gloabal Interrupt
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	/*******************配置TIM3**********************/
	TIM_TimeBaseStructure.TIM_Period = 9999; 
	TIM_TimeBaseStructure.TIM_Prescaler = 7199;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	////清中断，以免一启用中断后立即产生中断
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);
	//使能ARR寄存器 加载
	TIM_ARRPreloadConfig(TIM3, ENABLE); 
	//使能更新时间中断
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);   
	//使能TIM3定时器
	TIM_Cmd(TIM3, ENABLE);

}




