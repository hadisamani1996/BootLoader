#include "stm32f10x.h"
#include "stdlib.h"
#include "stdio.h"
#include "TIMER.h"
#include "GPIO.h"
#include "USART.h"
#include "FLASH.h"
#include "BOOTLOADER.h"
#include "DELAY.h"

uint8_t receive1[2000]="0";
uint8_t receive2[500]="0";
uint16_t __flash_read[1500];


typedef  void (*pFunction)(void);
pFunction JumpToApplication;
uint32_t JumpAddress;

uint32_t now_pointer;

uint16_t receive1_ptr;
uint16_t receive2_ptr;

uint8_t receive_flag;

//*********flags********\\
uint8_t receive_flag;
uint8_t analyze_flag;

int main()
{
	GPIO_init();
	usart_init();
	//timer_init();
	while(1)
	{
		while(!GPIO_ReadInputDataBit(BOTTON_PORT,BOTTON_PIN))
		{
			
		}
		if(receive_flag)
		{
			FLASH_UnlockBank1();
			flash_eraseflash();
			write_to_flash();
			FLASH_LockBank1();
			receive_flag=0;
		}
		else
		{
			// Determine whether the stack address value is between 0x2000 0000 - 0x 2000 2000
			if (((*(__IO uint32_t*)FLASH_WRITE_ADDRESS) & 0x2FFE0000) == 0x20000000)
			
				JumpAddress = *(__IO uint32_t*)(FLASH_WRITE_ADDRESS+4);
				JumpToApplication = (pFunction) JumpAddress;
				JumpToApplication();
				while(1)
				{
					
			}
		}
	}
}



