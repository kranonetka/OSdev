#include "task.h"
#include "video.h"
#include "string.h"
#include "common.h"
#include "time.h"

#define MAX_TASKS 10

unsigned int last_task_id = 0;
task_t* task_queue;
task_t* current_task;

static void task1()
{
	int i = 0;
	while (i++ < 5)
	{
		print("Hello from task1\n");
	}
}

static void task2()
{
	int i = 0;
	while (i++ < 5)
	{
		print("Ohayo from task2 2 u\n");
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

static void create_task(unsigned int fn)
{
	if (!current_task)
	{
		current_task = task_queue = (task_t*)malloc(sizeof(task_t));
	}
	else
	{
		current_task->next = (task_t*)malloc(sizeof(task_t));
		current_task = current_task->next;
	}
	current_task->next = task_queue;
	
	current_task->context.ss = 0x10;
	current_task->context.useresp = malloc(4096) + 4092;
	*((unsigned int*)current_task->context.useresp) = (unsigned int)&task_end;
	current_task->id = last_task_id++;
	current_task->context.eflags = 0x202; //ints enabled 
	current_task->context.cs = 0x08;
	current_task->context.eip = fn;
	
	current_task->ready = true;
}

void init_tasking()
{
	create_task((unsigned int)&task1);
	create_task((unsigned int)&task2);
	init_timer(50);
}
