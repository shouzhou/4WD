 
#include <main.h>
#include<LCD1602.h>
#include<servo.h>
#include<motor.h>
float S1=0.0;
float S2=0.0;
bit flag_zhangai;
void Timer0_Init(void)
{
    TMOD=0X01;
		TH0= 0XFF;		  
		TL0= 0X33;
		TR0= 1;
		ET0= 1;
}
	void Timer2_Init(void)		//50ms@11.0592MHz
{
		T2MOD = 0;		//模式控制器
		T2CON = 0;		//控制寄存器
		TL2 = 0x00;		//定时初值
		TH2 = 0x00;		//
		RCAP2L = 0x00;		//重载初值
		RCAP2H = 0x00;		//
		ET2=1;//开启中断使能
}

void Int_Init(void)
{
	  IT0=1;
	    IT1=1;
	  EX0=1;
		EX1=1;
}
	
void sys_init()
{
    IRIN=1;                 
  	Int_Init();	 
  	Timer0_Init();
	  Timer2_Init();
  	push_val_left  =3;  //PWM 调节参数1-10   1为最慢，10是最快  改这个值可以改变其速度
 	  push_val_right =3;
    IRCOM[2]=0XFF;
    ServoDegree=3;
	  delayms(10);
	  ServoDegree=0;
	  EA=1;
}
main()
{
   sys_init();
   while(1)	
   {
		switch (IRCOM[2]) //Judge ir code 
	 {
	 	case 0x0E:	   //up
		Motor_Foward();
			break;
		case 0X1A:	  //down
		Motor_Back();

			break;
		case 0x0A:	   //left
		Motor_Left();	
		    				
			break;
		case 0x1E: //right
		Motor_Right();
			
			break;
		case 0x0D: //btn 1
		Motor_Acc();				
			break;
		case 0x19: //btn 2
		Motor_Dec();	
			
			break;
		case 0x1B: //CIRCLE LEFT  btn3
		Motor_CircleL();
				
			break;
		case 0x01: //CIRCLE RIGHT  btn4
	  Motor_CircleR();			 
			
			break;
		case 0x15:
	  		
			break;
		case 0x17: //btn 7
		 ServoDegree=1;
    		
			break;
		case 0x06://button 8
		ServoDegree=5;
			
    		
			break;
		case 0x12://button 9
		ServoDegree=3;
			
    			
			break;
		case 0x16://button0
		
			;
    			
			break;
		case 0x05:	//stop
		Motor_Stop();
		ServoDegree=3;
		
			break;
		default:
			break;
	}//end switch
	
//   if(flag_zhangai)//前方有障碍
// 	{
// 		 Motor_Stop();
// 		 push_val_left=10;
// 		 push_val_right=10;
// 		 P0=0XAA;
// 		 delayms(120);
// 		 Motor_Stop();
// 		 flag_zhangai=0;
// 		 LED1=0;
// 		 delayms(1000);
//   }
	   	
		  
   }//end while

} //end main
