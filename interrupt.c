#include "interrupt.h"
#include "video.h"
#include "string.h"
#include "common.h"
#include "task.h"


#define IRQ_COUNT 16


#define int_with_errcode (regs.int_no == 8) || ((10 <= regs.int_no) && (regs.int_no <= 14)) || (regs.int_no == 17)


void isr_handler(int_registers_t regs)
{
	static const char* const int_desc[] = {
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
	}
	else
	{
		print("<<<");
	}
	while (true);
}

extern task_t* task_queue;
extern task_t* current_task;
static void switch_task(irq_registers_t* context_ptr)
{
	if (current_task == 0)
	{
		context_ptr->esp = task_queue->stack+4;
		current_task = task_queue;
	}
	else
	{
		task_t *task_to_switch = current_task->next;
		while (!task_to_switch->ready)
		{
			if (task_to_switch == current_task)
			{
				print("All tasks done\n");
				task_queue = 0;
				return;
			}
			task_to_switch = task_to_switch->next;
		}
		current_task->stack = (unsigned int)&context_ptr->esp;
		context_ptr->esp = task_to_switch->stack+4;
		current_task = task_to_switch;
	}
}

static void PIT_handler(irq_registers_t* context_ptr)
{
	static unsigned int tick_counter = 0;
	++tick_counter;
	if (task_queue)
	{
		if (tick_counter == 1)
		{
			switch_task(context_ptr);
			tick_counter = 0;
		}
	}
/*
	else
	{
		print("Tick ");
		print(itoa(tick_counter++, 10));
		print("!\n");
	}
*/
}

static char scancode_to_ascii(unsigned char scancode)
{
	static char const* const rows[4] = {
		"1234567890-=\b",
		"qwertyuiop[]\n",
		"asdfghjkl;'",
		"zxcvbnm,./"
	};

	if (0x02 <= scancode && scancode <= 0x0e)
	{
		scancode -= 0x02;
		return rows[0][scancode];
	}
	if (0x10 <= scancode && scancode <= 0x1c)
	{
		scancode -= 0x10;
		return rows[1][scancode];
	}
	if (0x1e <= scancode && scancode <= 0x28)
	{
		scancode -= 0x1e;
		return rows[2][scancode];
	}
	if (0x2c <= scancode && scancode <= 0x35)
	{
		scancode -= 0x2c;
		return rows[3][scancode];
	}
	if (scancode == 0x39)
	{
		return ' ';
	}
	return 0;
}

static void keyboard_handler()
{
	unsigned char status = inb(0x64);
	if ((status & 0x1) && !(status & 0x20))
	{
		static char chars_to_print[2] = {0, 0};
		unsigned char scancode = inb(0x60);
		chars_to_print[0] = scancode_to_ascii(scancode);
		print(chars_to_print);
	}
}

void irq_handler(irq_registers_t regs)
{
/*
	print(">>>IRQ ");
	print(itoa(regs.int_no-32, 10));
	print("<<<");
*/
	if (regs.int_no == 32)
	{
		PIT_handler(&regs);
	}
	if (regs.int_no == 33)
	{
		keyboard_handler();
	}

	if (regs.int_no >= 40)
	{
		outb(0xa0, 0x20); // Sends EOI to slave cmd
	}
	outb(0x20, 0x20);	// Sends EOI to master cmd
}
