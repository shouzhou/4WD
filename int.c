#include <main.h>

 unsigned char pwm_val_left  =0;//��������
 unsigned char push_val_left =0;// ����ռ�ձ�N/10
 unsigned char pwm_val_right =0;
 unsigned char push_val_right=0;// �ҵ��ռ�ձ�N/10
 extern bit flag_zhangai;
 bit Right_moto_stop=1;
 bit Left_moto_stop =1;
 unsigned  int  time=0;
 unsigned  int  time_t2=0;
 unsigned char ServoDegree=0; //5 4 3 2 1 ������
 uchar IRCOM[7];
/************************************************************************/
/*                    PWM���Ƶ��ת��                                   */
/************************************************************************/
/*                    ��������                                        */
/*����push_val_left��ֵ�ı���ת��,ռ�ձ�            */
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
/*                    ��ǰ�������                                  */  
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

/*                    �Һ�������                                  */  
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
void  timer2() interrupt 5 using 2//�ƺ�û���жϡ�����
{
    TF2=0;//T2 ��ʱ���ж���Ҫ�˹���TF2��������	   ע����֤
    time_t2++;
	if(time_t2==10)
	{ 
	   LED1=!LED1;
	   time_t2=0;
	 }
}
  
/***************************************************/
///*TIMER0�жϷ����Ӻ�������PWM�ź�*/
 void timer0()interrupt 1   using 1
{
	 TH0= 0XFe;		 //about 0.5ms 
 	 TL0= 0X33;
  //servo control code
	 if(time< ServoDegree)             //�ж�0.5ms�����Ƿ�С�ڽǶȱ�ʶ
	                                   //servoDegree =3 first
      Servo_pwm=1;                   //ȷʵС�ڣ�PWM����ߵ�ƽ������
	                                   //�ߵ�ƽ==1ms �Ҽ���λ��
							                      //�ߵ�ƽ==1.5ms �м侲ֹ
	                                   //�ߵ�ƽ==2ms   ��߼���
     else
      Servo_pwm=0;                  //����������͵�ƽ
      time	=(time+1);              //0.05ms������1
    
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
                           //ȷ��IR�źų���
  while (!IRIN)            //��IR��Ϊ�ߵ�ƽ������9ms��ǰ���͵�ƽ�źš�
    {delay(1);}

 for (j=0;j<4;j++)         //�ռ���������
 { 
  for (k=0;k<8;k++)        //ÿ��������8λ
  {
   while (IRIN)            //�� IR ��Ϊ�͵�ƽ������4.5ms��ǰ���ߵ�ƽ�źš�
     {delay(1);}
    while (!IRIN)          //�� IR ��Ϊ�ߵ�ƽ
     {delay(1);}
     while (IRIN)           //����IR�ߵ�ƽʱ��
      {
				delay(1);
				N++;           
				if (N>=30)
				{ EX1=1;	return;}      //0.14ms���������Զ��뿪��
      }                        //�ߵ�ƽ�������                
     IRCOM[j]=IRCOM[j] >> 1;                  //�������λ����0��
     if (N>=8) 
			{IRCOM[j] = IRCOM[j] | 0x80;}  //�������λ����1��
     N=0;
  }
 }
   
   if (IRCOM[2]!=~IRCOM[3])
   { EX1=1;
     return; }
     beep();
     EX1 = 1; 
} 