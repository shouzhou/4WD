#include<motor.h>
void Motor_Reset(void)
{
	   P0=0x00;
	   push_val_right=push_val_left=0;
}
	
	
void Motor_Foward(void)
{
	     if(push_val_left>push_val_right)
			 push_val_right=push_val_left;
		 else
			 push_val_left=push_val_right;
  	
			P0=0XA5;
}

void Motor_Back(void)
{
	 	if(push_val_left>push_val_right)
			 push_val_right=push_val_left;
		 else
			 push_val_left=push_val_right;
			P0=0X5A;
}
void Motor_Left(void)
{
	      P0=0XA5;
		  push_val_right=5;
		  push_val_left=2;
}
	
void Motor_Right(void)
{
	      P0=0XA5;
		  push_val_left=5;
		  push_val_right=2;
}
	
void Motor_CircleL(void)
{
		push_val_left=5;
		push_val_right=5;
		P0=0XAA;
}
	
void Motor_CircleR(void)
{
	  	push_val_left=5;
		push_val_right=5;
		P0=0X55;
}
	
void Motor_Stop(void)
{
	  P0=0X00;
}
	
void Motor_Acc(void)
{
	 
	if(++push_val_left>10)
	push_val_left=10;
	if(++push_val_right>10)
	push_val_right=10;	
	
}
	
void Motor_Dec(void)
{
	  
		  if(--push_val_left<2)
			push_val_left=2;
		  if(--push_val_right<2)
			push_val_right=2;
		 
}
	