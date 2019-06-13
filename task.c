#include "task.h"
#include "video.h"
#include "string.h"
#include "common.h"
#include "time.h"
#include "interrupt.h"

#define PRINT_COUNT 0xffff

unsigned int last_task_id = 0;
task_t* task_queue = 0;
task_t* current_task = 0;

static void task1()
{
	int i = 0;
	while (i++ < PRINT_COUNT)
	{
		print("........\n");
	}
}

static void task2()
{
	int i = 0;
	while (i++ < PRINT_COUNT)
	{
		print("--------\n");
	}
}

static void task3()
{
	int i = 0;
	while (i++ < PRINT_COUNT)
	{
		print("////////\n");
	}
}

static void task4()
{
	int i = 0;
	while (i++ < PRINT_COUNT)
	{
		print("55555555\n");
	}
}

static void task_end()
{
	print("Task ");
	print(itoa(current_task->id, 10));
	print(" done\n");
	current_task->ready = false;
	while (true);
}

static void create_task(const unsigned int fn, const unsigned int task_end_handler)
{
	save_state();
	task_t *curr;
	if (!task_queue)
	{
		task_queue = (task_t*)malloc(sizeof(task_t));
		task_queue->next = task_queue;
		curr = task_queue;
	}
	else
	{
		curr = task_queue;
		while(curr->next != task_queue)
		{
			curr = curr->next;
		}
		curr->next = (task_t*)malloc(sizeof(task_t));
		curr = curr->next;
		curr->next = task_queue;
	}

	curr->id = last_task_id++;
	curr->stack = malloc(8192) + 8188;
	*((unsigned int*)curr->stack) = task_end_handler;
	curr->stack -= sizeof(irq_registers_t);
/* i don't know why this doesn't work
	irq_registers_t *regs = (irq_registers_t*)current_task->stack;
	regs->eflags = 0x202; //ints enabled 
	regs->cs = 0x08;
	regs->eip = fn;
	regs->esp = (unsigned int)&(regs->eip);
*/
	*((unsigned int*)(curr->stack + 12*4)) = 0x202; //ints enabled
	*((unsigned int*)(curr->stack + 11*4)) = 0x08;	//cs
	*((unsigned int*)(curr->stack + 10*4)) = fn;	//eip
	*((unsigned int*)(curr->stack + 0 *4)) = curr->stack+4;	//esp

	curr->ready = true;
//	gap(); //for debug
	restore_state();
}

void init_tasking()
{
	create_task((unsigned int)task1, (unsigned int)task_end);
	create_task((unsigned int)task2, (unsigned int)task_end);
	create_task((unsigned int)task3, (unsigned int)task_end);
	create_task((unsigned int)task4, (unsigned int)task_end);
	init_timer(50);
}
