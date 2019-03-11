#include "common.h"

void outb(unsigned short int port, unsigned char value)
{
	asm volatile(
		"out %0, %1\n\t"
		:
		: "dN" (port), "a" (value)
	);
}

unsigned char inb(unsigned short int port)
{
	unsigned char retval;
	asm volatile(
		"in %0, %1\n\t"
		: "=a" (retval)
		: "dN" (port)
	);
	return retval;
}

unsigned short int inw(unsigned short int port)
{
	unsigned short int retval;
	asm volatile(
		"in %0, %1\n\t"
		: "=a" (retval)
		: "dN" (port)
	);
	return ret;
} 
