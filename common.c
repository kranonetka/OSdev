#include "common.h"

void outb(const unsigned short int port, const unsigned char value)
{
	asm volatile(
		"out %0, %1\n\t"
		:
		: "dN" (port), "a" (value)
	);
}

unsigned char inb(const unsigned short int port)
{
	unsigned char retval;
	asm volatile(
		"in %0, %1\n\t"
		: "=a" (retval)
		: "dN" (port)
	);
	return retval;
}

unsigned short int inw(const unsigned short int port)
{
	unsigned short int retval;
	asm volatile(
		"in %0, %1\n\t"
		: "=a" (retval)
		: "dN" (port)
	);
	return retval;
} 
