#include "common.h"
#include "video.h"
#include "panic.h"
#include "string.h"
#include "idt.h"
#include "time.h"
#include "keyboard.h"

unsigned int initial_esp;

__attribute__((section(".text.cmain")))
int cmain(unsigned int init_stack)
{
	initial_esp = init_stack;
	clear_screen(0x1e);
	print("Hello, C world!\n");
	print("init stack: ");
	print(itoa(init_stack, 16));
	init_idt();
	init_keyboard();
	//init_timer(50);

	while (true);
}
