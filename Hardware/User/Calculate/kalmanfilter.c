#include "stm32f10x_lib.h"
#include "kalmanfilter.h"

double KalmanFilter(KFParam *param,double U,double Z)
{
	double temp2X2[2][2] = {0};
	double temp = 0;

	// X = A * X + B * U ;
	param->X_pre[0] = param->X[0];
	param->X_pre[1] = param->X[1];
	param->X[0] = param->A[0][0] * param->X_pre[0] + param->A[0][1] * param->X_pre[1] + param->B[0] * U;
	param->X[1] = param->A[1][0] * param->X_pre[0] + param->A[1][1] * param->X_pre[1] + param->B[1] * U;
	
	// P = A * P * A' + Q ;
		// temp2X2 = A * P ;
	param->P_pre[0][0] = param->P[0][0];
	param->P_pre[0][1] = param->P[0][1];
	param->P_pre[1][0] = param->P[1][0];
	param->P_pre[1][1] = param->P[1][1];
	temp2X2[0][0] = param->A[0][0] * param->P_pre[0][0] + param->A[0][1] * param->P_pre[1][0];
	temp2X2[0][1] = param->A[0][0] * param->P_pre[0][1] + param->A[0][1] * param->P_pre[1][1];
	temp2X2[1][0] = param->A[1][0] * param->P_pre[0][0] + param->A[1][1] * param->P_pre[1][0];
	temp2X2[1][1] = param->A[1][0] * param->P_pre[0][1] + param->A[1][1] * param->P_pre[1][1];
	param->P[0][0] = temp2X2[0][0] * param->A[0][0] + temp2X2[0][1] * param->A[1][0] + param->Q[0][0];
	param->P[0][1] = temp2X2[0][0] * param->A[0][1] + temp2X2[0][1] * param->A[1][1] + param->Q[0][1];
	param->P[1][0] = temp2X2[1][0] * param->A[0][0] + temp2X2[1][1] * param->A[1][0] + param->Q[1][0];
	param->P[1][1] = temp2X2[1][0] * param->A[0][1] + temp2X2[1][1] * param->A[1][1] + param->Q[1][1];
	
	// K = P * H / ( H' * P * H + R ) ;
		// temp = H' * P * H + R ;
	temp = ( param->H[0] * param->P[0][0] + param->H[1] * param->P[1][0] ) * param->H[0] + 
		( param->H[0] * param->P[0][1] + param->H[1] * param->P[1][1] ) * param->H[1] + param->R;
	param->K[0] = ( param->P[0][0] * param->H[0] + param->P[0][1] * param->H[1] ) / temp;
	param->K[1] = ( param->P[1][0] * param->H[0] + param->P[1][1] * param->H[1] ) / temp;
	
	// X = X + K * ( Z - H' * X );
		//temp = Z - H' * X ;
	param->X_pre[0] = param->X[0];
	param->X_pre[1] = param->X[1];
	temp = Z - param->H[0] * param->X_pre[0] - param->H[1] * param->X_pre[1];
	param->X[0] = param->X_pre[0] + param->K[0] * temp;
	param->X[1] = param->X_pre[1] + param->K[1] * temp;
	
	// P = ( I - K * H' ) * P ;
		// temp2X2 = I - K * H' ;
	param->P_pre[0][0] = param->P[0][0];
	param->P_pre[0][1] = param->P[0][1];
	param->P_pre[1][0] = param->P[1][0];
	param->P_pre[1][1] = param->P[1][1];
	temp2X2[0][0] = 1 - param->K[0] * param->H[0];
	temp2X2[0][1] = - param->K[0] * param->H[1];
	temp2X2[1][0] = - param->K[1] * param->H[0];
	temp2X2[1][1] = 1 - param->K[1] * param->H[1];
	param->P[0][0] = temp2X2[0][0] * param->P_pre[0][0] + temp2X2[0][1] * param->P_pre[1][0];
	param->P[0][1] = temp2X2[0][0] * param->P_pre[0][1] + temp2X2[0][1] * param->P_pre[1][1];
	param->P[1][0] = temp2X2[1][0] * param->P_pre[0][0] + temp2X2[1][1] * param->P_pre[1][0];
	param->P[1][1] = temp2X2[1][0] * param->P_pre[0][1] + temp2X2[1][1] * param->P_pre[1][1];

	return param->X[0];
}
