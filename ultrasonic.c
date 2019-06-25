#include <ultrasonic.h>


float count(void)
{
	 unsigned int time_ultrasonic;
	 float dis;
	 time_ultrasonic=TH2*256+TL2;
	 TH2=0;
	 TL2=0;
	 dis=(time_ultrasonic*1.87)/100;
	 return dis;
}
void StartModule(void)
{
	 TX=1;			                 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_();
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_();
	  TX=0;
}

void Measure(void)
{
	    unsigned int a=0;
	    StartModule();
	    TH2=0;
	    TL2=0;
	    while(!RX)
			{
				a++;
				if(a>2000)
				{a=0;break;}
      }				
	    TR2=1;			    
	    while(RX);			
	    TR2=0;				   
      delayms(1);
}