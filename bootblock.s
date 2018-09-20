[BITS 16]
org 0x7c00



	;Инициализация сегментных регистров
	jmp 0x0:($+5)	;Инициализация регистра cs
	xor ax,ax	
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax

start:
	;video memory at 0xb800
	mov ax, 0xb800
	mov gs, ax

	mov cx, 25*80
	xor bx, bx
.clear_screen:
	mov byte [gs:bx], ' '
	mov byte [gs:bx+1], 0x1e	;color
	times 2 inc bx
	loop .clear_screen

	mov si, msg
	mov bx, 160 * 10 + 80 -14
.print_message:
	lodsb
	test al, al
	jz .end_message
	mov [gs:bx], al
	mov byte [gs:bx+1], 0x1e
	times 2 inc bx
	jmp .print_message
.end_message:

jmp $

data:
	msg: db "Hello, world!", 0

times 510 - ($ - $$) db 0
db 0x55, 0xaa
