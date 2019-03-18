#include "common.h"
#include "video.h"
#include "panic.h"
#include "string.h"
#include "idt.h"

__attribute__((section(".text.cmain")))
int cmain()
{
	clear_screen(0x1e);
	print("Hello, C world!\n");
	init_idt();

	asm volatile(
		"int 2\n\t"
	);

	while (true);
}
