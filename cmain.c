#include "common.h"
#include "video.h"
#include "panic.h"
#include "string.h"
#include "idt.h"

int cmain()
{
	clear_screen(0x1e);
	print("Hello, C world!\n");
	init_idt();
	asm volatile(
		"int 16\n\t"
		"int 14\n\t"
	);
	return 0;
}
