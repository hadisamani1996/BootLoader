#include "TIMER.h"

void timer_init(void)
{
	timer_init_clock();
	timer_init_nvic();
	timer_init_hardware();
}
void timer_init_clock( void )
{
	RCC_APB1PeriphClockCmd(CLOCK_TIMERx,ENABLE);
}
void timer_init_nvic( void )
{
	NVIC_InitTypeDef	NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel=TIMERx_IRQ_CHANNEL;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=0;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStruct);
}
void timer_init_hardware( void )
{
	// Update Event (Hz) = timer_clock / ((TIM_Prescaler + 1) * (TIM_Period + 1))
	// Update Event (Hz) = 72MHz / ((3599 + 1) * (9999 + 1)) = 2Hz (0.5s)
	TIM_TimeBaseInitTypeDef	TIM_Basic_Init;
	 
	TIM_Basic_Init.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_Basic_Init.TIM_Prescaler=8999;
	TIM_Basic_Init.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_Basic_Init.TIM_Period=7999;
	//TIM_Basic_Init.TIM_RepetitionCounter=0x00;
	TIM_TimeBaseInit(TIMERx,&TIM_Basic_Init);

	
	TIM_ITConfig(TIMERx,TIM_IT_Update,ENABLE);
	TIM_ClearITPendingBit(TIMERx,TIM_IT_Update);
	TIM_Cmd(TIMERx,ENABLE);
}
void TIM4_IRQHandler( void )
{
	int read;
	TIM_Cmd(TIMERx,DISABLE);
	if(TIM_GetFlagStatus(TIMERx,TIM_FLAG_Update))
	{
		read=GPIO_ReadOutputDataBit(LED_PORT,GPIO_Pin_6);
		printf("\nLED state is: %i",read);
		GPIO_WriteBit(LED_PORT,GPIO_Pin_6,!read);
	}
	TIM_ClearFlag(TIMERx,TIM_FLAG_Update);
	TIM_ClearITPendingBit(TIMERx,TIM_IT_Update);
	TIM_Cmd(TIMERx,ENABLE);
}





