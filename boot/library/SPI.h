#ifndef		__SPI__H
#define		__SPI__H
#include "stm32f10x.h"
#include "stm32f10x_spi.h"

#define SPI_PORT					GPIOA
#define SPI_PORT_CS				GPIOC
#define SPI_PIN_NSS				GPIO_Pin_4
#define SPI_PIN_SCK				GPIO_Pin_5
#define SPI_PIN_MISO			GPIO_Pin_6
#define SPI_PIN_MISI			GPIO_Pin_7
#define SPI_PIN_CS				GPIO_Pin_4

void spi_init(void);
void spi_deinit(void);
void spi_init_gpio(void);
void spi_init_clock(void);
void spi_init_hardware(void);
#endif





