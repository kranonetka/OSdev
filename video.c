#include "video.h"
#include "common.h"

static char* const VIDEO_MEM = (char *)0xb8000;
static unsigned short pointer = 0;


static void update_cursor()
{
	outb(0x3d4, 14);
	outb(0x3d5, pointer >> 8);
	outb(0x3d4, 15);
	outb(0x3d5, pointer);	
}

static void scroll()
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

void clear_screen(const char color)
{
	pointer = 0;
	while (pointer < 80*25*2)
	{
		VIDEO_MEM[pointer++] = ' ';
		VIDEO_MEM[pointer++] = color;
	}
	pointer = 0;
	update_cursor();
}

void print(const char* string)
{
	gap();
	lock();
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
			case '\b':
				if (pointer > 0)
				{
					--pointer;
					VIDEO_MEM[pointer << 1] = ' ';
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
		update_cursor();
		++current_char;
	}
	gap();
	unlock();
}

void color_print(const char* string, const unsigned char color)
{
	lock();
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
			case '\b':
				if (pointer > 0)
				{
					--pointer;
					VIDEO_MEM[pointer << 1] = ' ';
				}
				break;
			default:
				VIDEO_MEM[pointer << 1] = (*current_char);
				VIDEO_MEM[(pointer << 1) + 1] = color;
				++pointer;
		}

		if (pointer == 80*25)
		{
			scroll();
		}
		update_cursor();
		++current_char;
	}
	unlock();
}
