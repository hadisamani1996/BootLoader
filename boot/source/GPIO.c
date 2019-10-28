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
	GPIO_InitStruct.GPIO_Pin = BUZZER_PIN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(BUZZER_PORT,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin = BOTTON_PIN;
	GPIO_Init(BOTTON_PORT,&GPIO_InitStruct);
	
}
void GPIO_init_clock()
{
	RCC_APB2PeriphClockCmd(BUZZER_PORT_CLOCK|BOTTON_PORT_CLOCK, ENABLE);
}





