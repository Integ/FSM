#include "stm32f10x_lib.h"
#include "GPIO.h"

void GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = LED;  // 选择所有脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  //配置成推挽式输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //输出模式下 I/O输出速度 50M HZ
	GPIO_Init(GPIO_LED, &GPIO_InitStructure);  //初始化IO口
	
	//关闭JTAG功能
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);			
}
