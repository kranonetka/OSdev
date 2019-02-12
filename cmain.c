#define PANIC(err_msg) PANIC_FUNC(err_msg, __FILE__, __LINE__)
char* const VIDEO_MEM = (char *)0xb8000;
unsigned short pointer = 0;

char buffer[1024] = {0};

void clear_screen(char color)
{
	unsigned short i = 0;
	while (i < 80*25)
	{
		VIDEO_MEM[i << 1] = ' ';
		VIDEO_MEM[(i << 1) + 1] = color;
		++i;
	}
	pointer = 0;
}

unsigned strlen(const char* str_addr)
{
	const char *tmp = str_addr;
	while (*tmp++);
	return tmp - str_addr - 1;
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
	const unsigned string_len = strlen(string);
	unsigned i = 0;
	while (i < string_len)
	{
		if (string[i] == '\n')
		{
			unsigned char est_spaces =
			80 - (pointer % 80)
			?
			80 - (pointer % 80)
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
			unsigned char est_spaces =
			8 - (pointer & 7)
			?
			8 - (pointer & 7)
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
			scroll();
		}
		++i;
	}
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

char* itoa (int value, char* dest, const unsigned base)
{
	unsigned char i = 0;
	unsigned char isNegative = 0;

	if (!value)
	{
		dest[i++] = '0';
		dest[i] = '\0';
		return dest;
	}
	
	if (value < 0 && base == 10)
	{
		isNegative = 1;
		value = -value;
	}

	while (value)
	{
		unsigned char digit = value % base;
		dest[i++] = digit + '0';
		value /= base;
	}

	if (isNegative)
	{
		dest[i++] = '-';
	}
	
	dest[i] = '\0';
	reverse(dest, i);
	return dest;
}

void PANIC_FUNC(const char* err_msg, const char* filename, int line)
{
	itoa(line, buffer, 10);
	print("PANIC: ");
	print(filename);
	print(":");
	print(buffer);
	print(": error: ");
	print(err_msg);
	print("\n");
	while (1);
}

int cmain()
{
	clear_screen(0x1e);
	print("cmain");
	return 0;
}
