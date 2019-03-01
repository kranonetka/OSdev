#pragma once

struct registers_struct
{
	unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;	//pushed from isr_stub
	unsigned int int_no, err_code;	//pushed from ISR
	unsigned int eip, cs, eflags, useresp, ss;	//pushed when called INT n
} __attribute__((packed));
typedef struct registers_struct registers_t;

void isr_handler();
