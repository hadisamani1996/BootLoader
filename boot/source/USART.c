#include "USART.h"

extern uint8_t receive1[2000];
extern uint8_t receive2[500];
extern uint16_t receive1_ptr;
extern uint16_t receive2_ptr;
extern uint8_t receive_flag;
void usart_init_clock( void ) 
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
}
void usart_init_gpio( void ) {
	
	GPIO_InitTypeDef	GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init( GPIOA , &GPIO_InitStruct );
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init( GPIOA , &GPIO_InitStruct );
}
void usart_init_nvic( void ) 
{
	NVIC_InitTypeDef	NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 16;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init( &NVIC_InitStruct );
	
}
void usart_init_hardware( void )
{
	USART_InitTypeDef	USART_InitStruct;
	USART_InitStruct.USART_BaudRate = 9600;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b; 
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init( USART1 , &USART_InitStruct );
	USART_ITConfig( USART1 , USART_IT_RXNE , ENABLE );
	USART_Cmd( USART1 , ENABLE );
}
void usart_init()
{
	usart_init_clock();
	usart_init_gpio();
	usart_init_nvic();
	usart_init_hardware();
}

void USART1_IRQHandler( void ) 
{
	if( USART_GetFlagStatus( USART1 , USART_FLAG_RXNE ) != RESET )
	{
		if(receive1_ptr<2000)
		{
			receive1[receive1_ptr]=USART_ReceiveData( USART1 );
			receive1_ptr++;
		}
		else 
		{
			receive2[receive2_ptr]=USART_ReceiveData( USART1 );
			receive2_ptr++;
		}
	}
	if(receive1_ptr!=0)
	{
		receive_flag=1;
	}
}



