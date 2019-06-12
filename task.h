#pragma once
#include "interrupt.h"
#include "common.h"

struct task_struct
{
	//irq_registers_t context;
	unsigned int stack;
	unsigned int id;
	bool ready;
	struct task_struct *next;
} __attribute__((packed));
typedef struct task_struct task_t;

void init_tasking();
