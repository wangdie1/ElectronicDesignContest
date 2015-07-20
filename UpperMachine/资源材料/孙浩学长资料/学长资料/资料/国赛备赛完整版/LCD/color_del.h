#ifndef __COLOR_DEL_H
#define __COLOR_DEL_H
#include<stm32f10x.h>


#define IMG_X 0	 
#define IMG_Y 0	  
#define IMG_W 320 
#define IMG_H 240 

#define min3v(v1, v2, v3)   ((v1)>(v2)? ((v2)>(v3)?(v3):(v2)):((v1)>(v3)?(v3):(v1)))
#define max3v(v1, v2, v3)   ((v1)<(v2)? ((v2)<(v3)?(v3):(v2)):((v1)<(v3)?(v3):(v1)))

#define ALLOW_FAIL_PER 3 
#define ITERATE_NUM    8

typedef struct{
    unsigned short  H_MIN;   //Ŀ����Сɫ��
    unsigned short  H_MAX;   //Ŀ�����ɫ��
    
	  unsigned char  S_MIN;   //Ŀ����С���Ͷ� 
    unsigned char  S_MAX;   //Ŀ����󱥺Ͷ�
	
	  unsigned char  V_MIN;   //Ŀ����С����
    unsigned char  V_MAX;   //Ŀ���������
	
	  unsigned int  WIDTH_MIN; //Ŀ����С���
	  unsigned int  HIGHT_MIN; //Ŀ����С�߶�

	  unsigned int  WIDTH_MAX; //Ŀ�������
	  unsigned int  HIGHT_MAX; //Ŀ�����߶�

}TARGET_CONDI;   //Ŀ����ɫ



typedef struct{
	unsigned int x;
	unsigned int y;
	unsigned int w;
	unsigned int h;
}RESULT;



typedef struct{
    int  red;             // [0,255]
    int  green;           // [0,255]
    int  blue;            // [0,255]
}COLOR_RGB;//RGB��ɫֵ



typedef struct{
    int hue;              // [0,360]
    int saturation;       // [0,100]
    int value;        // [0,100]
}COLOR_HSV; //HSL��ɫֵ



typedef struct{
    unsigned int X_Start;              
    unsigned int X_End;
	unsigned int Y_Start;              
    unsigned int Y_End;
}SEARCH_AREA;

void con_565to888(unsigned short color,COLOR_RGB *Rgb);
int SearchCentre(unsigned int *x,unsigned int *y, TARGET_CONDI *Condition, SEARCH_AREA *Area);
void RGBtoHSL( u32 color, COLOR_HSV *Hsv);
void HSLtoRGB( COLOR_HSV *Hsv,COLOR_RGB *Rgb );
int ColorMatch( COLOR_HSV *Hsv, TARGET_CONDI *Condition);
int Corrode(unsigned int oldx,unsigned int oldy, TARGET_CONDI *Condition,RESULT *Resu);
int Trace( TARGET_CONDI *Condition,RESULT *Resu);
#endif

