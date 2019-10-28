#include "SPI.h"

void spi_init_clock()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC|RCC_APB2Periph_SPI1,ENABLE);
}
void spi_init_gpio()
{
	GPIO_InitTypeDef	GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	//GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin=SPI_PIN_NSS;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(SPI_PORT,&GPIO_InitStruct);
	GPIO_SetBits(SPI_PORT,SPI_PIN_NSS);
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin=SPI_PIN_CS;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(SPI_PORT_CS,&GPIO_InitStruct);
	GPIO_SetBits(SPI_PORT_CS,SPI_PIN_CS);
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin=SPI_PIN_SCK;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(SPI_PORT,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin=SPI_PIN_MISI;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(SPI_PORT,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin=SPI_PIN_MISO;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(SPI_PORT,&GPIO_InitStruct);
}
void spi_init_hardware()
{
	SPI_InitTypeDef	SPI_InitStruct;
	SPI_InitStruct.SPI_Direction=SPI_Direction_2Lines_FullDuplex;
	SPI_InitStruct.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_8;
	SPI_InitStruct.SPI_CPOL=SPI_CPOL_High;
	SPI_InitStruct.SPI_CPHA=SPI_CPHA_2Edge;
	SPI_InitStruct.SPI_CRCPolynomial=0;//7
	SPI_InitStruct.SPI_DataSize=SPI_DataSize_8b;
	SPI_InitStruct.SPI_FirstBit=SPI_FirstBit_MSB;
	SPI_InitStruct.SPI_Mode=SPI_Mode_Master;
	SPI_InitStruct.SPI_NSS=SPI_NSS_Soft;
	SPI_Init(SPI1,&SPI_InitStruct);
	//SPI_SSOutputCmd(SPI1, ENABLE);
	SPI_Cmd(SPI1,ENABLE);
}
void spi_deinit()
{
  SPI_I2S_DeInit(SPI1);
  SPI_Cmd(SPI1, DISABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, DISABLE);  
}

void spi_init()
{
	spi_init_clock();
	spi_init_gpio();
	spi_init_hardware();
}


