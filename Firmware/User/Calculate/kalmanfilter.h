#ifndef __KALMANFILTER_H
#define __KALMANFILTER_H

#include "stm32f10x_lib.h"

typedef struct
{
	double X[2];  //滤波结果向量
	double X_pre[2];
	double A[2][2];
	double B[2];
	double H[2];
	double Q[2][2];
	double R;
	double P[2][2];
	double P_pre[2][2];
	double K[2];
}
KFParam;

#define KFPARAM_DEFAULT \
	{\
		{0},\
		{0},\
		{{1,-T_sample},{0,1}},\
		{T_sample,0},\
		{1,0},\
		{{0.003,0},{0,0.003}},\
		0.056,\
		{{0.0082,-0.0155},{-0.0155,0.2207}},\
		{{0.0082,-0.0155},{-0.0155,0.2207}},\
		{0}\
	}

double KalmanFilter(KFParam *param,double U,double Z);

#endif
