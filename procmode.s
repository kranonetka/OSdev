;Entering protected mode
[BITS 16]
org 0x7e00

cli
lgdt [gdt_info]
mov eax,cr0
or al,1
mov cr0,eax

jmp 0x08:($+5) ;init cs register

[BITS 32]
start:
;init segment regs
	mov ax, 0x10
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov ax, 0x18
	mov gs, ax
	mov esp, 0x10000

	mov ebx, 80 * 1
	mov ah, 0x4a
	mov esi, msg
.put_msg:
	lodsb
	test al, al
	jz .end_msg
	mov [gs:(ebx*2)], ax
	inc ebx
	jmp .put_msg
.end_msg:
	jmp $	

gdt_start:
;null segment:
	dd 0, 0
;code segment:
	dw 0xffff	;limit 0-15
	dw 0	;base 0-15
	db 0	;base 16-23
	db 10011010b	;access byte
			;7: 1 - valid sector
			;6-5: privelege (0 - kernel)
			;4: reserved 1
			;3: 1 - code segment
			;2: 0 - c b executed from kernel
			;1: 1 - readable
			;0: 0 - reserved
	db 11001111b	;flags + limit 16-19
			;granularity -  1
			;1 - 32 bit
	db 0	;base 24-31
		;base 0x0
;data segment:	
	dw 0xffff	;limit 0-15
	dw 0	;base 0-15
	db 0	;base 16-23
	db 10010010b	;access byte
			;7: 1 - valid sector
			;6-5: privelege (0 - kernel)
			;4: reserved 1
			;3: 0 - data segment
			;2: 0 - segment grows up
			;1: 1 - writable
			;0: 0 - reserved
	db 11001111b	;flags + limit 16-19
			;granularity -  1
			;1 - 32 bit protected
	db 0	;base 24-31
		;base 0x0
;video segment:
	dw 0xffff	;limit 0-15
	db 0x0, 0x80, 0x0b	;base 0-23
	db 10010010b	;access byte
	db 10001111b	;flags+ limit 16-19
			;granularity - 1
			;0 - 16 bit
	db 0	;base 24-31
		;base 0x000b8000
		
gdt_info:
	dw gdt_info - gdt_start - 1
	dd gdt_start

msg: db "Protected mode entered!", 0

times 512 - ($ - $$) db 0
