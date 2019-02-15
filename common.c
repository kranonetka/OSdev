#include "common.h"

void outb(unsigned short int port, unsigned char value)
{
	asm volatile(
		"outb %1, %0"
		:
		: "dN" (port), "a" (value)
	);
}

unsigned char inb(unsigned short int port)
{
	unsigned char retval;
	asm volatile(
		"inb %1, %0"
		: "=a" (retval)
		: "dN" (port)
	);
	return retval;
}

unsigned short int inw(unsigned short int port)
{
	unsigned short int ret;
	asm volatile(
		"inw %1, %0"
		: "=a" (ret)
		: "dN" (port)
	);
	return ret;
} 
