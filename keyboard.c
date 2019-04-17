#include "keyboard.h"
#include "idt.h"	//PIC ports define
#include "common.h"

void init_keyboard()
{
	unsigned char mask = inb(MASTER_DATA);
	mask &= ~2;
	outb(MASTER_DATA, mask);
}
