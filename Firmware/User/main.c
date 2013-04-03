#include "stm32f10x_lib.h"
#include "sys_config.h"
#include "delay.h" 
#include "GPIO.h"
#include "pwm.h"
#include "pwd.h"
#include "iic.h"
#include "sensors.h"
#include "math.h"
#include "kalmanfilter.h"
#include "PID.h"

#define T_sample 0.02   //采样周期，单位s

/****************变量声明*****************/

int PWM_Duty[5] = {0,1000,1000,1000,1000}; 
int Duty_Balance[5] = {0,1500,1500,1500,1500};
int Power_Duty = 0;
u16 PWD_Duty[5] = {0};

u8 Data_ADXL345[6] = {0};
double A_X=0,A_Y=0,A_Z=0;
double x_angle_A=0,y_angle_A=0;

u8 Data_L3G4200D[6] = {0};
double L_X=0,L_Y=0,L_Z=0;
double x_angle_L=0,y_angle_L=0,z_angle_L=0;

KFParam x_KFparam = KFPARAM_DEFAULT;
KFParam y_KFparam = KFPARAM_DEFAULT;

double angle_x_current=0,angle_y_current=0;
double angle_x_aim=0,angle_y_aim=0;
double angle_x_error=0,angle_y_error=0;

PIDParam x_PIDparam = X_PIDPARAM_DEFAULT;
PIDParam y_PIDparam = Y_PIDPARAM_DEFAULT;
double x_PIDout=0,y_PIDout=0;

/***************子函数声明***************/
void System_Init(void);
void PWM_set(void);
void PWD_get(void);
void PreProcess(void);



/*******************************************************************************
* 
*            主函数
* 
*******************************************************************************/
int main(void)
{
	int i=0;
	int ledcount=0;	

	System_Init();


//电调行程设置
/*
	while(GPIO_ReadInputDataBit(GPIO_LED,LED));

	PWM_set();

	while(1);
*/


	GPIO_ResetBits(GPIO_LED,LED);

	do
	{
		PWD_get();
	}
	while( PWD_Duty[1]>155 || PWD_Duty[1]<145 || PWD_Duty[2]>155 || PWD_Duty[2]<145 ||
		PWD_Duty[3]>107 || PWD_Duty[3]<103 || PWD_Duty[4]>155 || PWD_Duty[4]<145 );

	DelayMs(5000);       //延时5s，等待电机

	while( PWD_Duty[1]>155 || PWD_Duty[1]<145 || PWD_Duty[2]>155 || PWD_Duty[2]<145 ||
		PWD_Duty[3]>107 || PWD_Duty[3]<103 || PWD_Duty[4]>155 || PWD_Duty[4]<145 );

	
	GPIO_SetBits(GPIO_LED,LED);
	
	for(i=1;i<5;i++)
	{
		Duty_Balance[i] += (PWD_Duty[3]-150)*10;
		PWM_Duty[i] = Duty_Balance[i];	
	}
	Power_Duty = PWD_Duty[3];
	PWM_set();

  	while (1)
  	{
		ledcount++;
		if(ledcount==5)GPIO_ResetBits(GPIO_LED,LED);
		if(ledcount==10)
		{
			GPIO_SetBits(GPIO_LED,LED);
			ledcount = 0;
		}

		Read_ADXL345(Data_ADXL345);
		Read_L3G4200D(Data_L3G4200D);

		PreProcess();
		angle_x_current = KalmanFilter(&x_KFparam,L_X,x_angle_A);
		angle_y_current = KalmanFilter(&y_KFparam,L_Y,y_angle_A); 

		PWD_get();
		for(i=1;i<5;i++)
		{
			if(PWD_Duty[i]>205||PWD_Duty[i]<95)
			{
				if(i!=3)PWD_Duty[i]=150;
				else PWD_Duty[i]=105;
			}
		}
		for(i=1;i<5;i++)
		{
			Duty_Balance[i] += (PWD_Duty[3]-Power_Duty)*10;
		}
		Power_Duty = PWD_Duty[3];
										
		angle_x_aim = -1.0*45/50*(PWD_Duty[2]-150);
		angle_y_aim = -1.0*45/50*(PWD_Duty[4]-150);
		angle_x_error = angle_x_aim - angle_x_current;
		angle_y_error = angle_y_aim - angle_y_current;

		x_PIDout = PIDCalc(&x_PIDparam,angle_x_error);
		y_PIDout = PIDCalc(&y_PIDparam,angle_y_error);

		if(angle_x_current>-1&&angle_x_current<1&&x_PIDout>-0.2&&x_PIDout<0.2&&angle_y_current>-1&&angle_y_current<1&&y_PIDout>-0.2&&y_PIDout<0.2)
		{
			Duty_Balance[1] = PWM_Duty[1];
			Duty_Balance[3] = PWM_Duty[3];
			Duty_Balance[2] = PWM_Duty[2];
			Duty_Balance[4] = PWM_Duty[4];
		}

		PWM_Duty[1] = Duty_Balance[1] +	x_PIDout ;
		PWM_Duty[3] = Duty_Balance[3] -	x_PIDout ;
		PWM_Duty[2] = Duty_Balance[2] +	y_PIDout ;
		PWM_Duty[4] = Duty_Balance[4] -	y_PIDout ;

		if(PWD_Duty[3]<=107)
					PWM_Duty[1] = PWM_Duty[2] = PWM_Duty[3] = PWM_Duty[4] = 1000;  

		PWM_set();
		DelayMs(18);
	}


}

/******************************** 子函数定义 *********************************/
void System_Init(void)
{
	RCC_Configuration();
	NVIC_Configuration();
	//打开外设时钟								 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE); 	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2|RCC_APB1Periph_TIM3|RCC_APB1Periph_TIM4,ENABLE);	

	GPIO_Config();
	PWD_Config();	
	PWM_Config();

	I2C_Config();
	ADXL345_Init();
	L3G4200D_Init(); 	

}


void PWM_set(void)
{	
	char i=0;
	for(i=1;i<5;i++)
	{
		if(PWM_Duty[i]>2000)PWM_Duty[i]=2000;
		if(PWM_Duty[i]<1000)PWM_Duty[i]=1000;
	}
	TIM3_CCR1_VAL = PWM_Duty[1];
	TIM3_CCR2_VAL = PWM_Duty[2];
	TIM3_CCR3_VAL = PWM_Duty[3];
	TIM3_CCR4_VAL = PWM_Duty[4];
}


void PWD_get(void)
{
	PWD_Duty[1] = TIM_GetCapture1(TIM4)+1;							//chanel 1  顺时针逆时针旋转
	PWD_Duty[2] = TIM_GetCapture2(TIM2)+1;							//chanel 2  前后平移
	PWD_Duty[3] = TIM_GetCapture3(TIM2)-PWD_Duty[2]+1;				//chanel 3  油门大小，升降控制
	PWD_Duty[4] = TIM_GetCapture4(TIM2)-PWD_Duty[3]-PWD_Duty[2]+1;	//chanel 4  左右平移
}



void PreProcess(void)
{
	double a_x,a_y;
	
	A_X = (double)((short)((Data_ADXL345[1]<<8)+Data_ADXL345[0]));   
	A_Y = (double)((short)((Data_ADXL345[3]<<8)+Data_ADXL345[2]));  
	A_Z = (double)((short)((Data_ADXL345[5]<<8)+Data_ADXL345[4]));  
	
	L_X = (double)((short)((Data_L3G4200D[1]<<8)+Data_L3G4200D[0]));
	L_Y = (double)((short)((Data_L3G4200D[3]<<8)+Data_L3G4200D[2]));
	L_Z = (double)((short)((Data_L3G4200D[5]<<8)+Data_L3G4200D[4]));

	A_X = -A_X * 3.9;  //unit:mg,13bit=+/-16g
	A_Y = A_Y * 3.9;
	A_Z = A_Z * 3.9;
        
	A_X = A_X + 61.5710;  //校准
	A_Y = A_Y + 13.7979;
	A_Z = A_Z + 100.9602;

	L_X = L_X * 70 / 1000;  //unit:dps
	L_Y = L_Y * 70 / 1000;
	L_Z = L_Z * 70 / 1000;
        
//	L_X = L_X - 0.2177;  //校准
//	L_Y = L_Y + 0.1137;
//	L_Z = L_Z - 0.0513;
	
	y_angle_A = atan2(A_X,sqrt((A_Z*A_Z+A_Y*A_Y)))* (180 / 3.1415926) ; 
	x_angle_A = atan2(A_Y,sqrt((A_Z*A_Z+A_X*A_X)))* (180 / 3.1415926) ; 
	a_x=fabs(x_angle_A);
	a_y=fabs(y_angle_A);
	if(A_Z<0)
	{
		if(y_angle_A<0)
			y_angle_A = -y_angle_A-(180-a_x*2);
		else 
			y_angle_A = (180-a_x*2)-y_angle_A;
		if(x_angle_A<0)
			x_angle_A = -x_angle_A-(180-a_y*2);
		else x_angle_A = (180-a_y*2)-x_angle_A;
	}

	x_angle_L += L_X*T_sample;
	y_angle_L += L_Y*T_sample;
}



#ifdef  DEBUG
/*******************************************************************************
* Function Name  : assert_failed
* Description    : Reports the name of the source file and the source line number
*                  where the assert_param error has occurred.
* Input          : - file: pointer to the source file name
*                  - line: assert_param error line source number
* Output         : None
* Return         : None
*******************************************************************************/
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
