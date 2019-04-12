#include "interrupt.h"
#include "video.h"
#include "string.h"
#include "common.h"

#define IRQ_COUNT 16

#define int_with_errcode (regs.int_no == 8) || ((10 <= regs.int_no) && (regs.int_no <= 14)) || (regs.int_no == 17)



void isr_handler(int_registers_t regs)
{
	static char* int_desc[] = {
	"Divide Error",
	"Debug Exception",
	"NMI Interrupt",
	"Breakpoint",
	"Overflow",
	"BOUND Range Exceeded",
	"Invalid Opcode (Undefined Opcode)",
	"Device Not Available (No Math Coprocessor)",
	"Double Fault",
	"Coprocessor Segment Overrun (reserved)",
	"Invalid TSS",
	"Segment Not Present",
	"Stack-Segment Fault",
	"General Protection",
	"Page Fault",
	"(Intel reserved. Do not use.)",
	"x87 FPU Floating-Point Error (Math Fault)",
	"Alignment Check",
	"Machine Check",
	"SIMD Floating-Point Exception",
	"Virtualization Exception",
	};

	print(">>>INTERRUPT ");
	print(itoa(regs.int_no, 10));
	print(": ");
	if (regs.int_no < 21)
	{
		print(int_desc[regs.int_no]);
	}
	else
	{
		print(int_desc[15]);
	}

	if (int_with_errcode)
	{
		print(" (err code ");
		print(itoa(regs.err_code, 10));
		print(")<<<");
		print(itoa(regs.ss,16));
	}
	else
	{
		print("<<<");
	}
	while (true);
}

void irq_handler(irq_registers_t regs)
{
	print(">>>IRQ ");
	print(itoa(regs.int_no-32, 10));
	print("<<<");

	if (regs.int_no == 32)
	{
		print("\nTick!");
	}

	if (regs.int_no >= 40)
	{
		outb(0xa0, 0x20); // Sends EOI to slave cmd
	}
	outb(0x20, 0x20);	// Sends EOI to master cmd
}
