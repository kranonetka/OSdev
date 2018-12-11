char * const VIDEO_MEM = (char *)0xb8000;

unsigned int strlen(const char *str_addr)
{
	const char *tmp = str_addr;
	while (*tmp)
	{
		++tmp;
	}
	return tmp - str_addr;
}

void clear_screen(char color)
{
	int i = 0;
	while (i < 80*25)
	{
		VIDEO_MEM[i << 1] = ' ';
		VIDEO_MEM[(i << 1) + 1] = color;
		++i;
	}	
}

void print(const char* string)
{
	static unsigned short pointer = 0;
	const unsigned int string_len = strlen(string);
	int i = 0;
	while (i < string_len)
	{
		if (string[i] == '\n')
		{
			unsigned short est_spaces =
			80 - (pointer % 80)
			?
			(80 - (pointer % 80))
			:
			80;
			while (est_spaces)
			{
				VIDEO_MEM[pointer << 1] = ' ';
				++pointer;
				--est_spaces;
			}
		}
		else if (string[i] == '\t')
		{
			unsigned short est_spaces =
			8 - (pointer & 7)
			?
			(8 - (pointer & 7))
			:
			8;
			while (est_spaces)
			{
				VIDEO_MEM[pointer << 1] = ' ';
				++pointer;
				--est_spaces;
			}
		}
		else
		{
			VIDEO_MEM[pointer << 1] = string[i];
			++pointer;
		}
		if (pointer == 80*25)
		{
			unsigned short tmp_ptr = 0;
			while (tmp_ptr < 80*24)
			{
				VIDEO_MEM[tmp_ptr << 1] = VIDEO_MEM[(tmp_ptr << 1) + 80 * 2];
				++tmp_ptr;
			}
			pointer = 80 * 24;
		}
		++i;
	}
}
int cmain()
{
	clear_screen(0x1e);
	int i = 0;
	print("\ttest");
	while (i < 20)
	{
		print("\n");
		++i;
	}
	print("\n\tmov eax,5\n\tinc eax\n\t");
	print("bbb");	
	return 0;
}
