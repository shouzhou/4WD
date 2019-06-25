#include <servo.h>
//54321 -----FROM LEFT TO  RIGHT
void ServoLeft(void)
{
	 ServoDegree=4;//4*0.5 =2ms
}
void ServoRight(void)
{
	ServoDegree=2;//2*0.5=1ms
}
void ServoStop(void)
{
	 ServoDegree=0;//1.5ms
}