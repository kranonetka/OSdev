#include "interrupt.h"
#include "video.h"
#include "string.h"

void isr_handler(registers_t regs)
{
	print("recieved interrupt: ");
	print(itoa(regs.int_no, 10));
	print("\n");
}
