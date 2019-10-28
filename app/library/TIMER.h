#ifndef		__TIMER_H
#define 	__TIMER_H
#include "stdio.h"
#include "stm32f10x.h"
#include "GPIO.h"

#define CLOCK_TIMERx						RCC_APB1Periph_TIM4
#define TIMERx_IRQ_CHANNEL			TIM4_IRQn
#define TIMERx									TIM4
#define TIMERx_IRQ							TIM4_IRQn 


void timer_init(void);
void timer_init_clock(void);
void timer_init_nvic(void);
void timer_init_hardware(void);
#endif



