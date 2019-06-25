#include <main.h>

 unsigned char pwm_val_left  =0;//变量定义
 unsigned char push_val_left =0;// 左电机占空比N/10
 unsigned char pwm_val_right =0;
 unsigned char push_val_right=0;// 右电机占空比N/10
 extern bit flag_zhangai;
 bit Right_moto_stop=1;
 bit Left_moto_stop =1;
 unsigned  int  time=0;
 unsigned  int  time_t2=0;
 unsigned char ServoDegree=0; //5 4 3 2 1 从左到右
 uchar IRCOM[7];
/************************************************************************/
/*                    PWM调制电机转速                                   */
/************************************************************************/
/*                    左电机调速                                        */
/*调节push_val_left的值改变电机转速,占空比            */
void pwm_out_LF_moto(void)
{  
   if(Left_moto_stop)
   {
    if(pwm_val_left<=push_val_left)
	       LF_moto_pwm=1; 
	else 
	       LF_moto_pwm=0;
	if(pwm_val_left>=10)
    	pwm_val_left=0;
   }
   else  LF_moto_pwm=0;
}


void pwm_out_LB_moto(void)
{  
   if(Left_moto_stop)
   {
    if(pwm_val_left<=push_val_left)
	       LB_moto_pwm=1; 
	else 
	       LB_moto_pwm=0;
	if(pwm_val_left>=10)
	      pwm_val_left=0;
   }
   else  LB_moto_pwm=0;
}
/******************************************************************/
/*                    右前电机调速                                  */  
   void pwm_out_RF_moto(void)
{ 
  if(Right_moto_stop)
   { 
    if(pwm_val_right<=push_val_right)
	       RF_moto_pwm=1; 
	else 
	       RF_moto_pwm=0;
	if(pwm_val_right>=10)
	pwm_val_right=0;
   }
   else    RF_moto_pwm=0;
}

/*                    右后电机调速                                  */  
   void pwm_out_RB_moto(void)
{ 
  if(Right_moto_stop)
   { 
    if(pwm_val_right<=push_val_right)
	       RB_moto_pwm=1; 
	else 
	       RB_moto_pwm=0;
	if(pwm_val_right>=10)
	pwm_val_right=0;
   }
   else    RB_moto_pwm=0;
}
/*******************************************************************/
void  timer2() interrupt 5 using 2//似乎没有中断。。。
{
    TF2=0;//T2 定时器中断需要人工清TF2，否则不行	   注意验证
    time_t2++;
	if(time_t2==10)
	{ 
	   LED1=!LED1;
	   time_t2=0;
	 }
}
  
/***************************************************/
///*TIMER0中断服务子函数产生PWM信号*/
 void timer0()interrupt 1   using 1
{
	 TH0= 0XFe;		 //about 0.5ms 
 	 TL0= 0X33;
  //servo control code
	 if(time< ServoDegree)             //判断0.5ms次数是否小于角度标识
	                                   //servoDegree =3 first
      Servo_pwm=1;                   //确实小于，PWM输出高电平，其中
	                                   //高电平==1ms 右极限位置
							                      //高电平==1.5ms 中间静止
	                                   //高电平==2ms   左边极限
     else
      Servo_pwm=0;                  //大于则输出低电平
      time	=(time+1);              //0.05ms次数加1
    
	  time=time%40;	                  
	 //end servo control
	 //motor control
 	 pwm_val_left++;
	 pwm_val_right++;
	 pwm_out_LF_moto();
	 pwm_out_LB_moto();
	 pwm_out_RF_moto();
	 pwm_out_RB_moto();
	 //end motor control
 }
 
 
 //*************interrupt  INT0****************************/
 /**********************************************************/
void MY_INT0() interrupt 0 using 0
 {
	 EX0=0;
	 flag_zhangai=1;
	 EX0=1;
 }
 //*************interrupt  INT1****************************/
 /**********************************************************/
void IR_IN() interrupt 2 using 0
{
  unsigned char j,k,N=0;
     EX1 = 0;   
	 delay(15);
	 if (IRIN==1) 
     { EX1 =1;
	   return; } 
                           //确认IR信号出现
  while (!IRIN)            //等IR变为高电平，跳过9ms的前导低电平信号。
    {delay(1);}

 for (j=0;j<4;j++)         //收集四组数据
 { 
  for (k=0;k<8;k++)        //每组数据有8位
  {
   while (IRIN)            //等 IR 变为低电平，跳过4.5ms的前导高电平信号。
     {delay(1);}
    while (!IRIN)          //等 IR 变为高电平
     {delay(1);}
     while (IRIN)           //计算IR高电平时长
      {
				delay(1);
				N++;           
				if (N>=30)
				{ EX1=1;	return;}      //0.14ms计数过长自动离开。
      }                        //高电平计数完毕                
     IRCOM[j]=IRCOM[j] >> 1;                  //数据最高位补“0”
     if (N>=8) 
			{IRCOM[j] = IRCOM[j] | 0x80;}  //数据最高位补“1”
     N=0;
  }
 }
   
   if (IRCOM[2]!=~IRCOM[3])
   { EX1=1;
     return; }
     beep();
     EX1 = 1; 
} 