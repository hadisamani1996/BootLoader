#include "BOOTLOADER.h"

uint32_t flash_writ_address;

extern uint8_t analyze_flag;
extern uint16_t __flash_read[3000];
extern uint8_t receive1[2000];
extern uint8_t receive2[500];
extern uint16_t receive1_ptr;
extern uint16_t receive2_ptr;
extern uint32_t now_pointer;
void write_to_flash()
{
	uint16_t send_data;
	uint8_t counter;
	uint16_t data_byte_ptr;
	uint8_t success;
	flash_writ_address=FLASH_WRITE_ADDRESS;
	analyze_flag=1;
	data_byte_ptr=0;
	while(receive1_ptr)
	{
		send_data=0;
		counter=0;
		while(counter<2)
		{
			send_data|=(receive1[data_byte_ptr]<<counter*8);//changed with me
			counter++;
			receive1_ptr--;
			data_byte_ptr++;
		}
		success=flash_write_data(flash_writ_address,send_data);
		flash_writ_address+=2;//changed with me
	}
	data_byte_ptr=0;
	while(receive2_ptr)
	{
		send_data=0;
		counter=0;
		while(counter<2)
		{
			send_data|=(receive2[data_byte_ptr]<<counter*8);//changed with me
			counter++;
			receive2_ptr--;
			data_byte_ptr++;
		}
		success=flash_write_data(flash_writ_address,send_data);
		flash_writ_address+=2;//changed with me
	}
}
void read_from_flash(uint16_t* __read)
{
	uint16_t counter=0;
	uint32_t Address;
	Address=FLASH_WRITE_ADDRESS;
	while(Address<FLASH_END_WRITE_ADDRESS)
	{
		*__read = (*( __IO uint32_t*) Address );
		__read+=1;
		counter++;
		Address +=2;//changed with me
	}
}
void appjump()
{
}










