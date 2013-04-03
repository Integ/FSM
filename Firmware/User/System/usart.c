#include "stm32f10x_lib.h"
#include "usart.h"

/*******************************************************************************
* 				          USART1和相应IO口配置 
*******************************************************************************/
void USART1_Configuration(void)
{
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/**************相应IO口配置  ***************
	*		TXD~PA9				RXD~PA10
	*******************************************/
   	//配置USART1_Tx(PA9)为复合推挽输出
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  	GPIO_Init(GPIOA, &GPIO_InitStructure);

    //配置 USART1_Rx(PA10)为浮空输入
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

	/***************USART1配置***************/
    //波特率 = 115200
    //数据长度 = 8位
    // 一个停止位
    //无校验
    //非硬件流控制
    //允许接收和发送
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	//配置串口1
	USART_Init(USART1,&USART_InitStructure);

	//启动串口1
	USART_Cmd(USART1, ENABLE);
}

/*******************************************************************************
*            字符串发送函数 
*******************************************************************************/
void USART1_PutString(u8* BUF,u8 LEN)
{
	u8 i;
	for(i=0;i<LEN;i++)
	{
		USART_SendData(USART1,(u8)*BUF++);
		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
	}
}
