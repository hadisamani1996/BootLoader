#ifndef	__GPIO_H
#define __GPIO_H
#include "stm32f10x.h"

#define		LED_PIN						GPIO_Pin_6
#define		LED_PORT						GPIOF

void GPIO_init(void);
void GPIO_init_clock( void );
void GPIO_init_gpio( void );
#endif



