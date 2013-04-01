#ifndef _GPIO_H
#define _GPIO_H

#include "stm32f10x_lib.h"

#define GPIO_LED GPIOB
#define LED GPIO_Pin_3

void GPIO_Config(void);

#endif
