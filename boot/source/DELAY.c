#include "DELAY.h"

void delay_ms(uint32_t ms)
{
	volatile uint32_t nCount;
	RCC_ClocksTypeDef RCC_Clocks;
	RCC_GetClocksFreq (&RCC_Clocks);
	nCount=(RCC_Clocks.HCLK_Frequency/10000)*ms;
	for (; nCount!=0; nCount--);
}
