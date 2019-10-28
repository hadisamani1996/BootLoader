#ifndef		__SPI_FLASH__H
#define		__SPI_FLASH__H
#include "stm32f10x.h"
#include "stdio.h"
#include "SPI.h"

#define MIN_ADDRESS   							0
#define MAX_ADDRESS									8388607
#define ADDRESS_BYTE								3
enum SpiFlash_commmand_TypeDef
{
	spi_flash_write_enable=0x06,
	spi_flash_write_disable=0x04,
	spi_flash_read_status_register=0x05,
	spi_flash_write_status_register=0x01,
	spi_flash_read_data=0x03,
	spi_flash_fast_read=0x0B,
	spi_flash_fast_read_daul_output=0x3B,
	spi_flash_page_program=0x02,
	spi_flash_sector_erase=0x20,
	spi_flash_block_erase=0xD8,
	spi_flash_chip_erase=0xC7,
	spi_flash_power_down=0xB9,
	spi_flash_PowerDown_DeviceID=0xAB,
	spi_flash_manufature_DeviceID=0x90,
	spi_flash_JEDEC_ID=0x9F
};
enum SpiFlash_status_flag_TypeDef
{
	spi_flash_WEL_flag=0x02,
	spi_flash_BUSY_flag=0x01,
};

static enum SpiFlash_commmand_TypeDef	SpiFlash_commmand_enum;
static enum SpiFlash_status_flag_TypeDef	SpiFlash_status_flag;
uint8_t SpiFlash_device_id(uint16_t* device_id);
uint8_t SpiFlash_manufature_id(uint16_t* manufature_id,uint16_t* device_id);
uint8_t SpiFlash_write_enable(void);
uint8_t SpiFlash_write_disable(void);
uint8_t SpiFlash_write_status_register(uint8_t write_byte);
uint8_t SpiFlash_read_status_register(void);
uint8_t SpiFlash_write(uint32_t address,uint16_t number_bytes,uint8_t* data);
uint8_t SpiFlash_read(uint32_t address,uint16_t number_bytes,uint8_t* read_data);
uint8_t SpiFlash_fast_read(uint32_t address,uint8_t n_byte,uint8_t *read_ptr);
uint8_t SpiFlash_fast_read_dual_output(uint32_t address,uint8_t n_byte,uint8_t *read_ptr);//درست کار نميکند
uint8_t SpiFlash_chip_erase(void);
uint8_t SpiFlash_block_erase(uint32_t address);
uint8_t SpiFlash_sector_erase(uint32_t address);
uint8_t SpiFlash_power_down(void);
uint8_t SpiFlash_power_up(void);
uint8_t SpiFlash_dummy(uint8_t repeat);
uint8_t flag_time_overflow(uint32_t* i,uint32_t timeout);
void delay_ms(uint32_t ms);
#endif
