#include "time.h"
#include "common.h"

#include "idt.h"	// PIC ports define

void init_timer(const unsigned int frequency)
{
	unsigned int divisor = 1193180 / frequency;

	unsigned char
		l = (unsigned char)(divisor & 0xff),
		h = (unsigned char)((divisor >> 8) & 0xff);

	outb(0x43, 0x36);
	outb(0x40, l);
	outb(0x40, h);
	unsigned char a = inb(MASTER_DATA);
	a &= ~1;
	outb(MASTER_DATA, a);	// allow irq0
}
