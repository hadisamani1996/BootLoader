#ifndef	__GPIO_H
#define __GPIO_H
#include "stm32f10x.h"

#define 	BUZZER_PORT_CLOCK		RCC_APB2Periph_GPIOB
#define		BUZZER_PIN					GPIO_Pin_10
#define		BUZZER_PORT					GPIOB

#define 	BOTTON_PORT_CLOCK		RCC_APB2Periph_GPIOC
#define		BOTTON_PIN					GPIO_Pin_13
#define		BOTTON_PORT					GPIOC

void GPIO_init(void);
void GPIO_init_clock( void );
void GPIO_init_gpio( void );
#endif



