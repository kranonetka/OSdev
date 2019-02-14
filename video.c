#include "video.h"
#include "panic.h"
char* const VIDEO_MEM = (char *)0xb8000;
unsigned short pointer = 0;

void clear_screen(const char color)
{
	pointer = 0;
	while (pointer < 80*25*2)
	{
		VIDEO_MEM[pointer++] = ' ';
		VIDEO_MEM[pointer++] = color;
	}
	pointer = 0;
}

void scroll()
{

	unsigned short tmp_ptr = 0;
	while (tmp_ptr < 80*24)
	{
		VIDEO_MEM[tmp_ptr << 1] = VIDEO_MEM[(tmp_ptr << 1) + 80*2];
		++tmp_ptr;
	}
	while (tmp_ptr < 80*25)
	{
		VIDEO_MEM[tmp_ptr << 1] = ' ';
		++tmp_ptr;
	}
	pointer = 80 * 24;
}

void print(const char* string)
{
	char* current_char = (char *)string;
	while (*current_char)
	{
		switch (*current_char)
		{
			case '\n':
				pointer = pointer - (pointer % 80) + 80;
				break;
			case '\t':
				pointer = (pointer + 8) & ~(8-1);
				break;
			case '\r':
				if (pointer > 0)
				{
					--pointer;
				}
				break;
			default:
				VIDEO_MEM[pointer << 1] = (*current_char);
				++pointer;
		}

		if (pointer == 80*25)
		{
			scroll();
		}

		++current_char;
	}
}
