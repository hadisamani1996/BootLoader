#ifndef	__BOOTLOADER_H
#define __BOOTLOADER_H

#include "stm32f10x.h"
#include "stdio.h"
#include "FLASH.h"

typedef  void (*pFunction)(void);

void write_to_flash(void);
void read_from_flash(uint16_t* data);
void EnablePrivilegedMode(uint32_t write_register);
void interrupt_disable_all(void);
void interrupt_pending_disable_all(void);
void systick_disable(void);
void fault_handler_disable(void);
void active_MSP(void);
void appjump(void);
#endif



