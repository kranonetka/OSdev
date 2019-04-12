#pragma once

struct int_registers_struct
{
	unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;	//pushed from isr_stub
	unsigned int int_no, err_code;	//pushed from ISR
	unsigned int eip, cs, eflags, useresp, ss;	//pushed when called INT n
} __attribute__((packed));
typedef struct int_registers_struct int_registers_t;

struct irq_registers_struct
{
	unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;	//pushed from irq_stub
	unsigned int int_no;	//pushed from IRQ
	unsigned int eip, cs, eflags, useresp, ss;	//pushed by processor
} __attribute__((packed));
typedef struct irq_registers_struct irq_registers_t;

void isr_handler();
void irq_handler();
