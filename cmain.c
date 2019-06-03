#include "common.h"
#include "video.h"
#include "panic.h"
#include "string.h"
#include "idt.h"
#include "time.h"
#include "keyboard.h"


__attribute__((section(".text.cmain")))
int cmain()
{
	clear_screen(0x1e);
	print("Hello, C world!\n");
	init_idt();
	init_keyboard();
	//init_timer(50);

	while (true);
}
