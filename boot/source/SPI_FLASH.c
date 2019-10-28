#include "SPI_FLASH.h"

uint8_t SpiFlash_device_id(uint16_t* read_id)
{
	uint32_t i;
	uint32_t timeout=10000;
	GPIO_WriteBit(SPI_PORT_CS,SPI_PIN_CS,Bit_RESET);
	delay_ms(1);
	SPI_I2S_SendData(SPI1,spi_flash_PowerDown_DeviceID);
	delay_ms(2);
	i=0;
	while(!SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE))
	{
		if(flag_time_overflow(&i,timeout)) return 0;
	}
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE))
	{
		SPI_I2S_ReceiveData(SPI1);
		if(flag_time_overflow(&i,timeout)) return 0;
	}
	if(!SpiFlash_dummy(3)) return 0;
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE))
	{
		SPI_I2S_ReceiveData(SPI1);
		if(flag_time_overflow(&i,timeout)) return 0;
	}
	SPI_I2S_SendData(SPI1,0xFF);
	delay_ms(2);
	i=0;
	while(!SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE))
	{
		if(flag_time_overflow(&i,timeout)) return 0;
	}
	i=0;
	while(!SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE))
	{
		if(flag_time_overflow(&i,timeout)) return 0;
	}
	*read_id|=SPI_I2S_ReceiveData(SPI1);
	GPIO_WriteBit(SPI_PORT_CS,SPI_PIN_CS,Bit_SET);
	printf("\nid=%u",*read_id);
	delay_ms(10);
	return 1;
}
uint8_t SpiFlash_manufature_id(uint16_t* manufature_id,uint16_t* device_id)
{
	uint32_t i;
	uint32_t timeout=10000;
	uint8_t repeat=3;
	GPIO_WriteBit(SPI_PORT_CS,SPI_PIN_CS,Bit_RESET);
	delay_ms(2);
	SPI_I2S_SendData(SPI1,spi_flash_manufature_DeviceID);
	delay_ms(1);
	i=0;
	while(!SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE))
	{
		if(flag_time_overflow(&i,timeout)) return 0;
	}
	while(repeat--)
	{
		SPI_I2S_SendData(SPI1,0x00);
		delay_ms(2);
		i=0;
		while(!SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE))
		{
			if(flag_time_overflow(&i,timeout)) return 0;
		}
		while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE))
		{
			SPI_I2S_ReceiveData(SPI1);
			if(flag_time_overflow(&i,timeout)) return 0;
		}
	}
	SPI_I2S_SendData(SPI1,0xFF);
	delay_ms(2);
	i=0;
	while(!SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE))
	{
		if(flag_time_overflow(&i,timeout)) return 0;
	}
	while(!SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE))
	{
		if(flag_time_overflow(&i,timeout)) return 0;
	}
	*manufature_id=SPI_I2S_ReceiveData(SPI1);
	SPI_I2S_SendData(SPI1,0xFF);
	delay_ms(2);
	i=0;
	while(!SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE))
	{
		if(flag_time_overflow(&i,timeout)) return 0;
	}
	while(!SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE))
	{
		if(flag_time_overflow(&i,timeout)) return 0;
	}
	*device_id=SPI_I2S_ReceiveData(SPI1);
	GPIO_WriteBit(SPI_PORT_CS,SPI_PIN_CS,Bit_SET);
	delay_ms(10);
	printf("\nmanufacture id is=%u\nand device_id=%u",*manufature_id,*device_id);
	return 1;
}
uint8_t SpiFlash_write_enable()
{
	uint32_t i;
	uint32_t timeout=10000;
	GPIO_WriteBit(SPI_PORT_CS,SPI_PIN_CS,Bit_RESET);
	delay_ms(2);
	SPI_I2S_SendData(SPI1,spi_flash_write_enable);
	delay_ms(2);
	i=0;
	while(!SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE))
	{
		if(flag_time_overflow(&i,timeout)) return 0;
	}
	GPIO_WriteBit(SPI_PORT_CS,SPI_PIN_CS,Bit_SET);
	delay_ms(10);
	return 1;
}
uint8_t SpiFlash_write_disable()
{
	uint32_t i;
	uint32_t timeout=10000;
	GPIO_WriteBit(SPI_PORT_CS,SPI_PIN_CS,Bit_RESET);
	delay_ms(2);
	SPI_I2S_SendData(SPI1,spi_flash_write_disable);
	delay_ms(2);
	i=0;
	while(!SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE))
	{
		if(flag_time_overflow(&i,timeout)) return 0;
	}
	GPIO_WriteBit(SPI_PORT_CS,SPI_PIN_CS,Bit_SET);
	delay_ms(10);
	return 1;
}
uint8_t SpiFlash_read_status_register()
{
	uint16_t read_status=0;
	uint32_t i;
	uint32_t timeout=10000;
	GPIO_WriteBit(SPI_PORT_CS,SPI_PIN_CS,Bit_RESET);
	delay_ms(2);
	SPI_I2S_SendData(SPI1,spi_flash_read_status_register);
	delay_ms(2);
	i=0;
	while(!SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE))
	{
		if(flag_time_overflow(&i,timeout)) return 0;
	}
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE))
	{
		SPI_I2S_ReceiveData(SPI1);
		if(flag_time_overflow(&i,timeout)) return 0;
	}
	SPI_I2S_SendData(SPI1,0xFF);
	delay_ms(2);
	i=0;
	while(!SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE))
	{
		if(flag_time_overflow(&i,timeout)) return 0;
	}
	i=0;
	while(!SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE))
	{
		if(flag_time_overflow(&i,timeout)) return 0;
	}
	read_status=SPI_I2S_ReceiveData(SPI1);
	GPIO_WriteBit(SPI_PORT_CS,SPI_PIN_CS,Bit_SET);
	delay_ms(10);
	printf("\nstatus register  is:%u",read_status);
	return read_status;
}
uint8_t SpiFlash_write_status_register(uint8_t write_byte)
{
	uint32_t i;
	uint32_t timeout=10000;
	SpiFlash_write_enable();
	GPIO_WriteBit(SPI_PORT_CS,SPI_PIN_CS,Bit_RESET);
	delay_ms(2);
	SPI_I2S_SendData(SPI1,spi_flash_write_status_register);
	delay_ms(2);
	i=0;
	while(!SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE))
	{
		if(flag_time_overflow(&i,timeout)) return 0;
	}
	SPI_I2S_SendData(SPI1,write_byte);
	delay_ms(2);
	i=0;
	while(!SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE))
	{
		if(flag_time_overflow(&i,timeout)) return 0;
	}
	GPIO_WriteBit(SPI_PORT_CS,SPI_PIN_CS,Bit_SET);
	delay_ms(10);
	return 1;
}
uint8_t SpiFlash_chip_erase()
{
	uint32_t i;
	uint32_t timeout=10000;
	SpiFlash_write_enable();
	GPIO_WriteBit(SPI_PORT_CS,SPI_PIN_CS,Bit_RESET);
	delay_ms(2);
	SPI_I2S_SendData(SPI1,spi_flash_chip_erase);
	delay_ms(2);
	i=0;
	while(!SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE))
	{
		if(flag_time_overflow(&i,timeout)) return 0;
	}
	GPIO_WriteBit(SPI_PORT_CS,SPI_PIN_CS,Bit_SET);
	while((SpiFlash_read_status_register())&spi_flash_BUSY_flag);
	return 1;
}
uint8_t SpiFlash_block_erase(uint32_t address)
{
	uint32_t i;
	uint32_t __address_byte=ADDRESS_BYTE;
	uint32_t timeout=10000;
	SpiFlash_write_status_register(((SpiFlash_read_status_register())&0xBF));
	if((SpiFlash_read_status_register())&spi_flash_BUSY_flag) return 0;
	SpiFlash_write_enable();
	GPIO_WriteBit(SPI_PORT_CS,SPI_PIN_CS,Bit_RESET);
	delay_ms(2);
	SPI_I2S_SendData(SPI1,spi_flash_block_erase);
	delay_ms(2);
	while(__address_byte--)
	{
		SPI_I2S_SendData(SPI1,address>>(8*__address_byte));
		delay_ms(2);
		i=0;
		while(!SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE))
		{
			if(flag_time_overflow(&i,timeout)) return 0;
		}
	}
	GPIO_WriteBit(SPI_PORT_CS,SPI_PIN_CS,Bit_SET);
	while((SpiFlash_read_status_register())&spi_flash_BUSY_flag);
	return 1;
}
uint8_t SpiFlash_sector_erase(uint32_t address)
{
	uint32_t i;
	uint32_t __address_byte=ADDRESS_BYTE;
	uint32_t timeout=10000;
	SpiFlash_write_status_register(((SpiFlash_read_status_register())&0xBF));
	if((SpiFlash_read_status_register())&spi_flash_BUSY_flag) return 0;
	SpiFlash_write_enable();
	GPIO_WriteBit(SPI_PORT_CS,SPI_PIN_CS,Bit_RESET);
	delay_ms(2);
	SPI_I2S_SendData(SPI1,spi_flash_sector_erase);
	delay_ms(2);
	while(__address_byte--)
	{
		SPI_I2S_SendData(SPI1,address>>(8*__address_byte));
		delay_ms(2);
		i=0;
		while(!SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE))
		{
			if(flag_time_overflow(&i,timeout)) return 0;
		}
	}
	GPIO_WriteBit(SPI_PORT_CS,SPI_PIN_CS,Bit_SET);
	while((SpiFlash_read_status_register())&spi_flash_BUSY_flag);
	return 1;
}
uint8_t SpiFlash_write(uint32_t address,uint16_t n_bytes,uint8_t* data)
{
	uint32_t i;
	uint32_t timeout=10000;
	uint8_t __address_byte=ADDRESS_BYTE;
	SpiFlash_write_status_register(0x00);
	if(SpiFlash_read_status_register()) return 0;
	SpiFlash_write_enable();
	GPIO_WriteBit(SPI_PORT_CS,SPI_PIN_CS,Bit_RESET);
	delay_ms(2);
	SPI_I2S_SendData(SPI1,spi_flash_page_program);
	delay_ms(2);
	i=0;
	while(!SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE))
	{
		if(flag_time_overflow(&i,timeout)) return 0;
	}
	while(__address_byte--)
	{
		SPI_I2S_SendData(SPI1,address>>(8*__address_byte));
		delay_ms(2);
		i=0;
		while(!SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE))
		{
			if(flag_time_overflow(&i,timeout)) return 0;
		}
	}
	while(n_bytes--)
	{
		SPI_I2S_SendData(SPI1,*data);
		delay_ms(2);
		i=0;
		while(!SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE))
		{
			if(flag_time_overflow(&i,timeout)) return 0;
		}
		data+=1;
	}
	GPIO_WriteBit(SPI_PORT_CS,SPI_PIN_CS,Bit_SET);
	delay_ms(10);
	while((SpiFlash_read_status_register())&spi_flash_BUSY_flag);
	return 1;
}
uint8_t SpiFlash_read(uint32_t address,uint16_t number_bytes,uint8_t* read_ptr)
{
	uint32_t i;
	uint8_t __address_byte=ADDRESS_BYTE;
	uint32_t timeout=10000;
	SpiFlash_write_status_register(((SpiFlash_read_status_register())&0x03));
	if((SpiFlash_read_status_register())&spi_flash_BUSY_flag) return 0;
	GPIO_WriteBit(SPI_PORT_CS,SPI_PIN_CS,Bit_RESET);
	delay_ms(2);
	SPI_I2S_SendData(SPI1,spi_flash_read_data);
	delay_ms(2);
	i=0;
	while(!SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE))
	{
		if(flag_time_overflow(&i,timeout)) return 0;
	}
	while(__address_byte--)
	{
		SPI_I2S_SendData(SPI1,address>>(8*__address_byte));
		delay_ms(2);
		i=0;
		while(!SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE))
		{
			if(flag_time_overflow(&i,timeout)) return 0;
		}
	}
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE))
	{
		SPI_I2S_ReceiveData(SPI1);
		if(flag_time_overflow(&i,timeout)) return 0;
	}
	while(number_bytes--)
	{
		SPI_I2S_SendData(SPI1,0xFF);
		delay_ms(2);
		i=0;
		while(!SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE))
		{
			if(flag_time_overflow(&i,timeout)) return 0;
		}
		i=0;
		while(!SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE))
		{
			if(flag_time_overflow(&i,timeout)) return 0;
		}
		*read_ptr=SPI_I2S_ReceiveData(SPI1);
		read_ptr++;
	}
	GPIO_WriteBit(SPI_PORT_CS,SPI_PIN_CS,Bit_SET);
	delay_ms(10);
	return 1;
}
uint8_t SpiFlash_fast_read(uint32_t address,uint8_t n_byte,uint8_t *read_ptr)
{
	uint32_t i;
	uint8_t __address_byte=ADDRESS_BYTE;
	uint32_t timeout=10000;
	SpiFlash_write_status_register(((SpiFlash_read_status_register())&0x03));
	if((SpiFlash_read_status_register())&spi_flash_BUSY_flag) return 0;
	GPIO_WriteBit(SPI_PORT_CS,SPI_PIN_CS,Bit_RESET);
	delay_ms(2);
	SPI_I2S_SendData(SPI1,spi_flash_fast_read);
	delay_ms(2);
	i=0;
	while(!SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE))
	{
		if(flag_time_overflow(&i,timeout)) return 0;
	}
	while(__address_byte--)
	{
		SPI_I2S_SendData(SPI1,address>>(8*__address_byte));
		delay_ms(2);
		i=0;
		while(!SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE))
		{
			if(flag_time_overflow(&i,timeout)) return 0;
		}
	}
	SPI_I2S_SendData(SPI1,0xFF);
	delay_ms(2);
	i=0;
	while(!SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE))
	{
		if(flag_time_overflow(&i,timeout)) return 0;
	}
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE))
	{
		SPI_I2S_ReceiveData(SPI1);
		if(flag_time_overflow(&i,timeout)) return 0;
	}
	while(n_byte--)
	{
		SPI_I2S_SendData(SPI1,0xFF);
		i=0;
		while(!SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE))
		{
			if(flag_time_overflow(&i,timeout)) return 0;
		}
		i=0;
		while(!SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE))
		{
			if(flag_time_overflow(&i,timeout)) return 0;
		}
		*read_ptr=SPI_I2S_ReceiveData(SPI1);
		read_ptr++;
	}
	GPIO_WriteBit(SPI_PORT_CS,SPI_PIN_CS,Bit_SET);
	delay_ms(10);
	return 1;
}
uint8_t SpiFlash_fast_read_dual_output(uint32_t address,uint8_t n_byte,uint8_t *read_ptr)
{
	uint32_t i;
	uint8_t __address_byte=ADDRESS_BYTE;
	uint32_t timeout=10000;
	SpiFlash_write_status_register(((SpiFlash_read_status_register())&0x03));
	if((SpiFlash_read_status_register())&spi_flash_BUSY_flag) return 0;
	GPIO_WriteBit(SPI_PORT_CS,SPI_PIN_CS,Bit_RESET);
	delay_ms(2);
	SPI_I2S_SendData(SPI1,spi_flash_fast_read_daul_output);
	delay_ms(2);
	i=0;
	while(!SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE))
	{
		if(flag_time_overflow(&i,timeout)) return 0;
	}
	while(__address_byte--)
	{
		SPI_I2S_SendData(SPI1,address>>(8*__address_byte));
		delay_ms(2);
		i=0;
		while(!SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE))
		{
			if(flag_time_overflow(&i,timeout)) return 0;
		}
	}
	SPI_I2S_SendData(SPI1,0xFF);
	delay_ms(2);
	i=0;
	while(!SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE))
	{
		if(flag_time_overflow(&i,timeout)) return 0;
	}
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE))
	{
		SPI_I2S_ReceiveData(SPI1);
		if(flag_time_overflow(&i,timeout)) return 0;
	}
	while(n_byte--)
	{
		SPI_I2S_SendData(SPI1,0xFF);
		i=0;
		while(!SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE))
		{
			if(flag_time_overflow(&i,timeout)) return 0;
		}
		i=0;
		while(!SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE))
		{
			if(flag_time_overflow(&i,timeout)) return 0;
		}
		*read_ptr=SPI_I2S_ReceiveData(SPI1);
		read_ptr++;
	}
	GPIO_WriteBit(SPI_PORT_CS,SPI_PIN_CS,Bit_SET);
	delay_ms(10);
	return 1;
}
uint8_t SpiFlash_power_down()
{
	uint32_t i;
	uint32_t timeout=10000;
	GPIO_WriteBit(SPI_PORT_CS,SPI_PIN_CS,Bit_RESET);
	delay_ms(2);
	SPI_I2S_SendData(SPI1,spi_flash_power_down);
	delay_ms(2);
	i=0;
	while(!SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE))
	{
		if(flag_time_overflow(&i,timeout)) return 0;
	}
	GPIO_WriteBit(SPI_PORT_CS,SPI_PIN_CS,Bit_SET);
	delay_ms(10);
	return 1;
}
uint8_t SpiFlash_power_up()
{
	uint32_t i;
	uint32_t timeout=10000;
	GPIO_WriteBit(SPI_PORT_CS,SPI_PIN_CS,Bit_RESET);
	delay_ms(2);
	SPI_I2S_SendData(SPI1,spi_flash_PowerDown_DeviceID);
	delay_ms(2);
	i=0;
	while(!SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE))
	{
		if(flag_time_overflow(&i,timeout)) return 0;
	}
	GPIO_WriteBit(SPI_PORT_CS,SPI_PIN_CS,Bit_SET);
	delay_ms(10);
	return 1;
}
uint8_t SpiFlash_dummy(uint8_t repeat)
{
	uint32_t i;
	uint32_t timeout=2000;
	while(repeat--)
	{
		SPI_I2S_SendData(SPI1,0x00);
		delay_ms(2);
		i=0;
		while(!SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE))
		{
			if(flag_time_overflow(&i,timeout)) return 0;
		}
	}
	return 1;
}
uint8_t flag_time_overflow(uint32_t* i,uint32_t timeout)
{
	uint8_t overflow=0;
	*i+=1;
	if(*i>= timeout)
	{
		overflow = 1;
		spi_deinit();
		for(int j=0; j<3000; j++){__asm("nop");}
		spi_init();
		for(int j=0; j<3000; j++){__asm("nop");}
	}
	return overflow;
}
void delay_ms(uint32_t ms)
{
	volatile uint32_t nCount;
	RCC_ClocksTypeDef RCC_Clocks;
	RCC_GetClocksFreq (&RCC_Clocks);
	nCount=(RCC_Clocks.HCLK_Frequency/10000)*ms;
	for (; nCount!=0; nCount--);
}


