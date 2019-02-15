#include "common.h"
#include "video.h"
#include "panic.h"
#include "string.h"

int cmain()
{
	clear_screen(0x1e);
	print("Hello, C world!\n");
	return 0;
}
