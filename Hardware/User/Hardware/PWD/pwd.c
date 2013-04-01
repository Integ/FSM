#include "stm32f10x_lib.h"
#include "pwd.h"



void PWD_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;//定时器初始化结构
	TIM_ICInitTypeDef TIM_ICInitStructure;         //通道输入初始化结构
	GPIO_InitTypeDef GPIO_InitStructure;

	//浮动输入方式
	GPIO_InitStructure.GPIO_Pin = /* GPIO_Pin_0 | */GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6; 
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	//输出初始化
  	TIM_TimeBaseStructure.TIM_Period = 65535;     //周期
  	TIM_TimeBaseStructure.TIM_Prescaler = 720;       //时钟分频
  	TIM_TimeBaseStructure.TIM_ClockDivision = 0;   //时钟分割
  	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//模式
  	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);//基本初始化
  	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

	//捕捉初始化  
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling;//下降沿
 	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;//管脚与寄存器对应关系
  	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;//分频器
  	TIM_ICInitStructure.TIM_ICFilter = 0x4;        //滤波设置，经历几个周期跳变认定波形稳定0x0～0xF
 	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;//通道选择	
//  TIM_ICInit(TIM2, &TIM_ICInitStructure);        //初始化	
  	TIM_ICInit(TIM4, &TIM_ICInitStructure);        //初始化				 
 	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;//通道选择
  	TIM_ICInit(TIM2, &TIM_ICInitStructure);        //初始化
 	TIM_ICInitStructure.TIM_Channel = TIM_Channel_3;//通道选择
  	TIM_ICInit(TIM2, &TIM_ICInitStructure);        //初始化
 	TIM_ICInitStructure.TIM_Channel = TIM_Channel_4;//通道选择
  	TIM_ICInit(TIM2, &TIM_ICInitStructure);        //初始化
  
  	TIM_SelectInputTrigger(TIM2, TIM_TS_TI1FP1);   //选择时钟触发源				   
  	TIM_SelectSlaveMode(TIM2, TIM_SlaveMode_Reset);//触发方式					  
  	TIM_SelectMasterSlaveMode(TIM2, TIM_MasterSlaveMode_Enable); //启动定时器的被动触发
  	TIM_ITConfig(TIM2, /*TIM_IT_CC1|*/TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4, ENABLE);        //打开中断
 
	TIM_SelectInputTrigger(TIM4, TIM_TS_TI1F_ED);   //选择时钟触发源				   
  	TIM_SelectSlaveMode(TIM4, TIM_SlaveMode_Reset);//触发方式					  
  	TIM_SelectMasterSlaveMode(TIM4, TIM_MasterSlaveMode_Enable); //启动定时器的被动触发
  	TIM_ITConfig(TIM4, TIM_IT_CC1, ENABLE);        //打开中断

  	TIM_Cmd(TIM2, ENABLE);		  //启动TIM2
	TIM_Cmd(TIM4, ENABLE);
}

