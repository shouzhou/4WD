#ifndef _FILE_MAIN_H
#define _FILE_MAIN_H

#include <STC89C5X.h>
#include <intrins.h>
#include <delay.h>
#include <ultrasonic.h>
#include <motor.h>
#define uchar unsigned char
#define uint  unsigned int
sbit IRIN = P3^3;         //���������������  INT1
sbit DISIN= P3^2;         //������������ di��ƽ��Ч
sbit BEEP = P3^6;         //������������

sbit TX = P2^0;           //ultrasonic send
sbit RX = P2^1;  
sbit Servo_pwm=P2^7;     //���pwm����//ultrasonic receive

sbit LED1=P1^0;
sbit LED2=P1^1;

sbit LF_moto_pwm =P1^4;	  //��ǰ
sbit LB_moto_pwm =P1^5;
sbit RF_moto_pwm =P1^6;	  //��ǰ	 
sbit RB_moto_pwm =P1^7;


extern uchar IRCOM[7];
extern bit Right_moto_stop;
extern bit Left_moto_stop ;
extern unsigned  int  time;
extern unsigned  int  time_t2;
extern unsigned char ServoDegree; //5 4 3 2 1 ������

extern unsigned char pwm_val_left  ;//��������
extern unsigned char push_val_left ;// ����ռ�ձ�N/10
extern unsigned char pwm_val_right ;
extern unsigned char push_val_right;// �ҵ��ռ�ձ�N/10



#endif