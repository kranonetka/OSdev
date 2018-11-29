#define VIDEO_MEM ((char *)0xb8000)

const char hello[] = "Hello, C world!";

int strlen(const char *str_addr)
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
		VIDEO_MEM[i * 2] = ' ';
		VIDEO_MEM[i * 2 + 1] = color;
		++i;
	}	
}

int cmain()
{
	clear_screen(0x1e);
	
	int n = strlen(hello);
	int i = 0;
	while (i < n)
	{
		VIDEO_MEM[i * 2] = hello[i];
		++i;
	}
	return 0;
}
