#ifndef __IWDG_H
#define __IWDG_H
#include "stm32f10x_lib.h"

//独立看门狗初始化函数
void IWDG_Init(void);
//喂狗函数
void IWDG_Feed(void);

#endif
