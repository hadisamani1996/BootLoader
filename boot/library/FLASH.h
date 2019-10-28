#ifndef	__FLASH_H
#define __FLASH_H
#include "stm32f10x.h"

#define FILE_SIZE								4000
#define FLASH_PAGE_SIZE 				0x800
#define FLASH_WRITE_ADDRESS			0x8003000
#define FLASH_END_WRITE_ADDRESS	0x8007000
#define OFFSET_ADDRESS					0x3000
uint8_t flash_eraseflash(void);
uint8_t flash_write_data(uint32_t address,uint16_t data);
#endif


