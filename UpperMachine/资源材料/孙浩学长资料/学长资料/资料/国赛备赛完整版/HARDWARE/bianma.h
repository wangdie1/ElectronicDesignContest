#ifndef _BIANMA_H_
#define _BIANMA_H_
//����SPI����Ƭѡ�ź�CS���͵�ƽ��Ч
// ʱ�������ź�CLK,��������Ч 
//�����ź�DIO,˫��
//�����ж������źţ��͵�ƽ��Ч
#define CS(X) X ? GPIO_SetBits(GPIOA,GPIO_Pin_0) :GPIO_ResetBits(GPIOA,GPIO_Pin_0)
#define CLK(X) X ? GPIO_SetBits(GPIOA,GPIO_Pin_1) : GPIO_ResetBits(GPIOA,GPIO_Pin_1)
#define DIO(X) X ? GPIO_SetBits(GPIOA,GPIO_Pin_2) : GPIO_ResetBits(GPIOA,GPIO_Pin_2)
#define INT(X) X ? GPIO_SetBits(GPIOA,GPIO_Pin_3) : GPIO_ResetBits(GPIOA,GPIO_Pin_3)
//��ָ��
#define reset 0xA4
#define test  0xBF
#define SHL   0xA0
#define SHR   0xA1
#define ROL   0xA2
#define ROR   0xA3 
 
void DIO_IN(void);
void DIO_OUT(void);
void SPI_init(void);
void send_com(unsigned int com);
void send_datacom(unsigned int data,unsigned int com);
unsigned int receive(unsigned int com);
unsigned int  getkeycode(unsigned int dat);

#endif

