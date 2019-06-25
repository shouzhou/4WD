#ifndef _FILE_MAIN_H
#define _FILE_MAIN_H

#include <STC89C5X.h>
#include <intrins.h>
#include <delay.h>
#include <ultrasonic.h>
#include <motor.h>
#define uchar unsigned char
#define uint  unsigned int
sbit IRIN = P3^3;         //红外接收器数据线  INT1
sbit DISIN= P3^2;         //避障输入引脚 di电平有效
sbit BEEP = P3^6;         //蜂鸣器驱动线

sbit TX = P2^0;           //ultrasonic send
sbit RX = P2^1;  
sbit Servo_pwm=P2^7;     //舵机pwm引脚//ultrasonic receive

sbit LED1=P1^0;
sbit LED2=P1^1;

sbit LF_moto_pwm =P1^4;	  //左前
sbit LB_moto_pwm =P1^5;
sbit RF_moto_pwm =P1^6;	  //右前	 
sbit RB_moto_pwm =P1^7;


extern uchar IRCOM[7];
extern bit Right_moto_stop;
extern bit Left_moto_stop ;
extern unsigned  int  time;
extern unsigned  int  time_t2;
extern unsigned char ServoDegree; //5 4 3 2 1 从左到右

extern unsigned char pwm_val_left  ;//变量定义
extern unsigned char push_val_left ;// 左电机占空比N/10
extern unsigned char pwm_val_right ;
extern unsigned char push_val_right;// 右电机占空比N/10



#endif