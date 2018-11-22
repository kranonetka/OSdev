
#define VIDEO_MEM ((char *)0xb8000)

const char hello[] = "Hello, C world!";

char a[0x1000];

int strlen(const char *str_addr)
{
	const char *tmp = str_addr;
	while (*tmp)
	{
		++tmp;
	}
	return tmp - str_addr;
}

int cmain()
{
	char *video = VIDEO_MEM;
	int i = 0;
	while (i < 80 * 25)
	{
		video[i * 2] = 0x20;
		video[i * 2 + 1] = 0x7;
		++i;
	}

	int n = strlen(hello);
	for (i = 0; i < n; ++i)
	{
		video[i*2] = hello[i];
	}
}
