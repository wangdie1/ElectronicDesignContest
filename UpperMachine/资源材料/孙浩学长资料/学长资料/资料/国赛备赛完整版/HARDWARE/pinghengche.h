#ifndef _PINGHENGCHE_H_
#define _PINGHENGCHE_H_
typedef struct PID
{
	int SetPoint;//�趨Ŀ��ֵ
	long SumError;//����ۼ�
	double Proportion;//��������P
	double Integral;//���ֳ���I
	double Derivative;//΢�ֳ��� D
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
