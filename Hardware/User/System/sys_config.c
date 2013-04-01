#include "stm32f10x_lib.h"
#include "sys_config.h"

/*******************************************************************************
* 
*            RCC配置
* 
*******************************************************************************/
void RCC_Configuration(void)
{   
	ErrorStatus HSEStartUpStatus;

	//复位RCC外部设备寄存器到默认值
	RCC_DeInit();  
	//打开外部高速晶振
  	RCC_HSEConfig(RCC_HSE_ON); 
	//等待外部高速时钟准备好
  	HSEStartUpStatus = RCC_WaitForHSEStartUp(); 
	//外部高速时钟已经准别好
  	if(HSEStartUpStatus == SUCCESS)  
  	{
    	FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		FLASH_SetLatency(FLASH_Latency_2);
  
   		//配置AHB(HCLK)时钟=SYSCLK
    	RCC_HCLKConfig(RCC_SYSCLK_Div1);
		//配置APB2(PCLK2)钟=AHB时钟
    	RCC_PCLK2Config(RCC_HCLK_Div1); 
		//配置APB1(PCLK1)钟=AHB 1/2时钟
    	RCC_PCLK1Config(RCC_HCLK_Div2);  	
		//配置ADC时钟=PCLK2 1/4
    	RCC_ADCCLKConfig(RCC_PCLK2_Div4); 
		//配置PLL时钟 == 外部高速晶体时钟*9
    	RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9); 
		//配置ADC时钟= PCLK2/4
    	RCC_ADCCLKConfig(RCC_PCLK2_Div4);
		//使能PLL时钟
    	RCC_PLLCmd(ENABLE);  

   		//等待PLL时钟就绪
    	while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
    
		//配置系统时钟 = PLL时钟
    	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK); 
		//检查PLL时钟是否作为系统时钟
    	while(RCC_GetSYSCLKSource() != 0x08);
  	}
}

/*******************************************************************************
* 
*            NVIC配置
* 
*******************************************************************************/
void NVIC_Configuration(void)
{
	#ifdef  VECT_TAB_RAM  
  		/* Set the Vector Table base location at 0x20000000 */ 
  		NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0); 
	#else  /* VECT_TAB_FLASH  */
  		/* Set the Vector Table base location at 0x08000000 */ 
  		NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);   
	#endif
}
