#ifndef __PWM_H
#define __PWM_H

#include "stm32f10x_lib.h"

//通过改变CCR的值改变CH输出PWM的占空比

#define TIM3_CCR1_VAL TIM3->CCR1
#define TIM3_CCR2_VAL TIM3->CCR2
#define TIM3_CCR3_VAL TIM3->CCR3
#define TIM3_CCR4_VAL TIM3->CCR4



//PWM配置
void PWM_Config(void);

#endif
