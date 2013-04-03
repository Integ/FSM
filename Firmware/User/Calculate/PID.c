#include "stm32f10x_lib.h"
#include "PID.h"

double PIDCalc(PIDParam *param, double error)
{
	param->result = error * param->kp;

	param->derivative = (error - param->last_error) / param->dt;

	param->last_error  = error;

	param->result += param->kd * param->derivative;
/*
	if(param->result < -param->result_max)
		param->result = -param->result_max;
	else if(param->result > param->result_max)
		param->result = param->result_max;
*/
	return param->result;
}
