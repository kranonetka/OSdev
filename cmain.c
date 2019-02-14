#include "video.h"
#include "panic.h"
#include "string.h"

int cmain()
{
	clear_screen(0x1e);
	print("cmain");
	PANIC("test panic");
	return 0;
}
