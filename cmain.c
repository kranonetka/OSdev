#include "common.h"
#include "video.h"
#include "panic.h"
#include "string.h"
#include "idt.h"
#include "time.h"
#include "keyboard.h"
#include "task.h"

__attribute__((section(".text.cmain")))
int cmain()
{
	clear_screen(0x1e);
	print("Hello, C world!\n");
	init_idt();
	init_keyboard();
	init_tasking();
	init_timer(100500);
	while (true);
}
