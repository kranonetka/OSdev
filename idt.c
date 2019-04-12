#include "idt.h"
#include "common.h"

#define	IDT_ENTRIES_C	48

IDTDescr_t idt_entries[IDT_ENTRIES_C] __attribute__((aligned(8)));

static void lidt()
{
	idt_info_t idt_info;

	idt_info.base = (unsigned int)&idt_entries;
	idt_info.limit = sizeof(IDTDescr_t) * IDT_ENTRIES_C - 1;

	asm volatile(
		"lidt [%0]\n\t"
		:
		:"m"(idt_info)
	);
}

static void idt_set_gate(const unsigned int index, const unsigned int offset, const unsigned short int selector, const unsigned char type_attr)
{
	idt_entries[index].offset_lo = offset & 0xFFFF;
	idt_entries[index].offset_hi = (offset >> 16) & 0xFFFF;
	
	idt_entries[index].selector = selector;
	idt_entries[index].zero = 0;
	idt_entries[index].type_attr = type_attr;
}

void init_idt()
{
	idt_set_gate(0, (unsigned int)isr0, 0x08, 0x8E);
	idt_set_gate(1, (unsigned int)isr1, 0x08, 0x8E);
	idt_set_gate(2, (unsigned int)isr2, 0x08, 0x8E);
	idt_set_gate(3, (unsigned int)isr3, 0x08, 0x8E);
	idt_set_gate(4, (unsigned int)isr4, 0x08, 0x8E);
	idt_set_gate(5, (unsigned int)isr5, 0x08, 0x8E);
	idt_set_gate(6, (unsigned int)isr6, 0x08, 0x8E);
	idt_set_gate(7, (unsigned int)isr7, 0x08, 0x8E);
	idt_set_gate(8, (unsigned int)isr8, 0x08, 0x8E);
	idt_set_gate(9, (unsigned int)isr9, 0x08, 0x8E);
	idt_set_gate(10, (unsigned int)isr10, 0x08, 0x8E);
	idt_set_gate(11, (unsigned int)isr11, 0x08, 0x8E);
	idt_set_gate(12, (unsigned int)isr12, 0x08, 0x8E);
	idt_set_gate(13, (unsigned int)isr13, 0x08, 0x8E);
	idt_set_gate(14, (unsigned int)isr14, 0x08, 0x8E);
	idt_set_gate(15, (unsigned int)isr15, 0x08, 0x8E);
	idt_set_gate(16, (unsigned int)isr16, 0x08, 0x8E);
	idt_set_gate(17, (unsigned int)isr17, 0x08, 0x8E);
	idt_set_gate(18, (unsigned int)isr18, 0x08, 0x8E);
	idt_set_gate(19, (unsigned int)isr19, 0x08, 0x8E);
	idt_set_gate(20, (unsigned int)isr20, 0x08, 0x8E);
	idt_set_gate(21, (unsigned int)isr21, 0x08, 0x8E);
	idt_set_gate(22, (unsigned int)isr22, 0x08, 0x8E);
	idt_set_gate(23, (unsigned int)isr23, 0x08, 0x8E);
	idt_set_gate(24, (unsigned int)isr24, 0x08, 0x8E);
	idt_set_gate(25, (unsigned int)isr25, 0x08, 0x8E);
	idt_set_gate(26, (unsigned int)isr26, 0x08, 0x8E);
	idt_set_gate(27, (unsigned int)isr27, 0x08, 0x8E);
	idt_set_gate(28, (unsigned int)isr28, 0x08, 0x8E);
	idt_set_gate(29, (unsigned int)isr29, 0x08, 0x8E);
	idt_set_gate(30, (unsigned int)isr30, 0x08, 0x8E);
	idt_set_gate(31, (unsigned int)isr31, 0x08, 0x8E);

	idt_set_gate(32, (unsigned int)irq0, 0x08, 0x8E);
	idt_set_gate(33, (unsigned int)irq1, 0x08, 0x8E);
	idt_set_gate(34, (unsigned int)irq2, 0x08, 0x8E);
	idt_set_gate(35, (unsigned int)irq3, 0x08, 0x8E);
	idt_set_gate(36, (unsigned int)irq4, 0x08, 0x8E);
	idt_set_gate(37, (unsigned int)irq5, 0x08, 0x8E);
	idt_set_gate(38, (unsigned int)irq6, 0x08, 0x8E);
	idt_set_gate(39, (unsigned int)irq7, 0x08, 0x8E);
	idt_set_gate(40, (unsigned int)irq8, 0x08, 0x8E);
	idt_set_gate(41, (unsigned int)irq9, 0x08, 0x8E);
	idt_set_gate(42, (unsigned int)irq10, 0x08, 0x8E);
	idt_set_gate(43, (unsigned int)irq11, 0x08, 0x8E);
	idt_set_gate(44, (unsigned int)irq12, 0x08, 0x8E);
	idt_set_gate(45, (unsigned int)irq13, 0x08, 0x8E);
	idt_set_gate(46, (unsigned int)irq14, 0x08, 0x8E);
	idt_set_gate(47, (unsigned int)irq15, 0x08, 0x8E);
	
	//PIC remapping
	outb(MASTER_CMD, 0x11);	// start initialization master
	outb(SLAVE_CMD, 0x11);	// start initialization slave
	outb(MASTER_DATA, 32);	// MASTER interrupts [32:39] (irq0-irq7) //ICW2
	outb(SLAVE_DATA, 40);	// SLAVE interrupts [40:47] (irq8-irq15) //ICW2
	outb(MASTER_DATA, 0x4);	// Slave pic at IRQ2 (4 == 0b100) //ICW3
	outb(SLAVE_DATA, 0x2);	// Slave pic's cascade(??) (2 == b10) //ICW3
	outb(MASTER_DATA, 0x1);	// ICW4
	outb(SLAVE_DATA, 0x1);	// ICW4

	outb(MASTER_DATA, 0xff);	// Set IMR for MASTER
	outb(SLAVE_DATA, 0xff);		// Sets IMR for SLAVE

	asm volatile(
		"sti\n\t"
	);

	lidt();
}
