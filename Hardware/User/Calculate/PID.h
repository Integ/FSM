#ifndef _PID_H
#define _PID_H

#include "stm32f10x_lib.h"

#define X_PID_KP 1.5
#define X_PID_KD 0.00002
#define Y_PID_KP 1.5
#define Y_PID_KD 0.00002

typedef struct
{
	double kp;
	double kd;
	double dt;				// delta time(sample time)
	double last_error;
	double derivative;
	double result;

}PIDParam;

#define X_PIDPARAM_DEFAULT \
	{\
		X_PID_KP,\
		X_PID_KD,\
		T_sample,\
		0,\
		0,\
		0\
	}

#define Y_PIDPARAM_DEFAULT \
	{\
		Y_PID_KP,\
		Y_PID_KD,\
		T_sample,\
		0,\
		0,\
		0\
	}

double PIDCalc(PIDParam *param, double error);

#endif
