#include "stm32f10x_lib.h"
#include "iwdg.h"

/*******************************************************************************
* 				          IWDG配置(独立看门狗) 
*	  看门狗的溢出时间：T=（（4×2^Prer）×RLR）/40
*	  看门狗的溢出时间:T=1s，Prer=4(分频)分频因子为64  重载值RLR=625
*******************************************************************************/
void IWDG_Init(void)
{
	//对IWDG_PR和IWDG_RLR寄存器的写访问被使能
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	//设置预分频因子为64
	IWDG_SetPrescaler(IWDG_Prescaler_64);
	//设定重载值为625
	IWDG_SetReload(625);
	//喂狗
	IWDG_ReloadCounter();
	//使能IWDG
	IWDG_Enable();
}

/*******************************************************************************
* 				     喂独立看门狗函数（重载计数值）
*******************************************************************************/
void IWDG_Feed(void)
{
	IWDG_ReloadCounter();
}
