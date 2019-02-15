#include "string.h"
#include "common.h"

unsigned strlen(const char* string)
{
	const char *tmp = string;
	while (*tmp++);
	return tmp - string - 1;
}

void reverse(char* str, int length)
{
	unsigned start = 0;
	unsigned end = length - 1;
	while (start < end)
	{
		char tmp = str[start];
		str[start++] = str[end];
		str[end--] = tmp;
	}
}

char* itoa (int value, const unsigned base)
{
	static char buffer[1024] = { 0 };
	unsigned char i = 0;
	bool isNegative = false;

	if (!value)
	{
		buffer[i++] = '0';
		buffer[i] = '\0';
		return buffer;
	}
	
	if (value < 0 && base == 10)
	{
		isNegative = 1;
		value = -value;
	}

	while (value)
	{
		unsigned char digit = value % base;
		buffer[i++] = digit + '0';
		value /= base;
	}

	if (isNegative)
	{
		buffer[i++] = '-';
	}
	
	buffer[i] = '\0';
	reverse(buffer, i);
	return buffer;
}
