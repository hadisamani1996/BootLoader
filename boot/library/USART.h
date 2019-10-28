#ifndef    __USART_H
#define		 __USART_H
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_rcc.h"

void usart_init(void);
void usart_init_clock( void );
void usart_init_gpio( void );
void usart_init_nvic( void );
void usart_init_hardware( void );

#endif
