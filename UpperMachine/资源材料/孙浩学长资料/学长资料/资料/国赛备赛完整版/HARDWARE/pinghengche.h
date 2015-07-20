#ifndef _PINGHENGCHE_H_
#define _PINGHENGCHE_H_
typedef struct PID
{
	int SetPoint;//设定目标值
	long SumError;//误差累计
	double Proportion;//比例常数P
	double Integral;//积分常数I
	double Derivative;//微分常数 D
	int LastError;//Error[-1]
	int PrevError;//Error[-2]
}PID;
void IncPIDInit(void);
float IncPIDCalc(int NextPoint);

void PH_car_init(void);
void PH_motor_init(void);
void PH_gpio_init(void);
void PH_backward100(int  percent);
void PH_forward100(int percent);
void PH_backward90(int  percent);
void PH_forward90(int percent);
void PH_backward80(int  percent);
void PH_forward80(int percent);
void PH_backward70(int  percent);
void PH_forward70(int percent);
void PH_backward60(int  percent);
void PH_forward60(int percent);
void PH_backward50(int  percent);
void PH_forward50(int percent);
void PH_backward40(int  percent);
void PH_forward40(int percent);
void PH_stop(void);
#endif
