#pragma once

struct IDTDescr_struct
{
	unsigned short int offset_lo;
	unsigned short int selector;
	unsigned char zero;
	unsigned char type_attr;
	unsigned short int offset_hi;
} __attribute__((packed));
typedef struct IDTDescr_struct IDTDescr_t;

struct idt_info_struct
{
	unsigned short int limit;
	unsigned int base;
} __attribute__((packed));
typedef struct idt_info_struct idt_info_t;

void init_idt();

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();
