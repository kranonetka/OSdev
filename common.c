#include "common.h"
#include "panic.h"

static unsigned int alloc_mem = 0x47e00; //256 kB from 0x7e00
static const unsigned int alloc_limit = 0x7ffff;

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

void memset(char * const dest, const unsigned char val, const unsigned int len)
{
	unsigned int i = 0;
	while (i < len)
	{
		dest[i++] = val;
	}
}

unsigned int malloc(const unsigned int size)
{
	if (alloc_mem + size > alloc_limit)
	{
		PANIC("Out of memory");
	}
	unsigned int ret_mem = alloc_mem;
	alloc_mem += size;
	memset((char*)ret_mem, 0, size);
	return ret_mem;
}

void free(const unsigned int ptr)
{
	return;
}

void gap()
{
	asm volatile(
		"nop\n\t"
		"nop\n\t"
		"nop\n\t"
		"nop\n\t"
		"nop\n\t"
		"nop\n\t"
		"nop\n\t"
		"nop\n\t"
		"nop\n\t"
		"nop\n\t"
		"nop\n\t"
		"nop\n\t"
		"nop\n\t"
		"nop\n\t"
		"nop\n\t"
		"nop\n\t"
	);
}
