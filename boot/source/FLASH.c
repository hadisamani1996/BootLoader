#include "FLASH.h"
uint8_t flash_eraseflash()
{
	uint8_t success;
	uint8_t page_number;
	uint32_t flash_erase_address=FLASH_WRITE_ADDRESS;
	if(FILE_SIZE%FLASH_PAGE_SIZE)
	{
		page_number=(FILE_SIZE/FLASH_PAGE_SIZE)+1;
	}
	else
	{
		page_number=(FILE_SIZE/FLASH_PAGE_SIZE);
	}
	FLASH_UnlockBank1();
	while(page_number--)
	{
		success=FLASH_ErasePage(flash_erase_address);
		flash_erase_address+=FLASH_PAGE_SIZE;
	}
	return success;
}
uint8_t flash_write_data(uint32_t address,uint16_t data)
{
	uint8_t success;
	success=FLASH_ProgramHalfWord(address,data);
	return success;
}




