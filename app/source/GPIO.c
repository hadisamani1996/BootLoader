#include "GPIO.h"
void GPIO_init()
{
	GPIO_init_clock();
	GPIO_init_gpio();
}
void GPIO_init_gpio()
{
	GPIO_InitTypeDef		GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = LED_PIN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LED_PORT,&GPIO_InitStruct);
	
	GPIO_WriteBit(LED_PORT,GPIO_Pin_6,Bit_SET);
}
void GPIO_init_clock()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF , ENABLE);
}





