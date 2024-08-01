#include "stm32f4xx.h"

#include "timers.h"

int main(void)
{
	initTim4Ch1();
	setTim4Frequency(160, 10);
	
	startTim4Ch1();
	
	while(1)
	{
		
	}
	
}



