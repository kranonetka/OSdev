; vim:ft=nasm
[BITS 32]

extern current_task
global switch_task
;[esp+4] - current context ptr
;[esp+8] - ptr to task to switch
switch_task:
	mov edi, [current_task]
	mov esi, [esp+4]
	mov esi, [esi]
	;edi - points to current_task.context.eax (where to save)
	;esi - poits to irq_registers_t.eax (what to save)
ret
