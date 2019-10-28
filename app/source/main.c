#include "stm32f10x.h"
#include "TIMER.h"
#include "GPIO.h"

#define FLASH_WRITE_ADDRESS			0x8003000

int main()
{
	//SCB->VTOR=(FLASH_WRITE_ADDRESS);
	GPIO_init();
	timer_init();
	while(1)
	{
		
	}
}







