[BITS 16]
org 0x7c00

	;Инициализация сегментных регистров
	jmp 0x0:($+5)	;Инициализация регистра cs
	xor ax, ax	
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax

start_with_ints:
	mov ax, 0x0003
	int 0x10	;change video mode

	mov ah, 0x0b
	mov bx, 0x0001
	int 0x10	;change background

	mov ax, 0x1301
	mov bx, 0x001e
	mov cx, msg_len
	xor dx, dx
	mov bp, msg
	int 0x10	;print string

;start_without_ints:
;	;video memory at 0xb8000
;	mov ax, 0xb800
;	mov es, ax
;
;	mov cx, 25*80
;	xor bx, bx
;.clear_screen:
;	mov word [bx], 0x1e20
;	times 2 inc bx
;	loop .clear_screen
;
;	mov si, msg
;	mov bx, 160 * 10 + 80 - 14
;	mov ah, 0x1e
;.print_message:
;	lodsb
;	test al, al
;	jz .end_message
;	mov [bx], ax
;	times 2 inc bx
;	jmp .print_message
;.end_message:

 read_sectors:
	mov bx, 0x07e0
	mov es, bx
	mov ax, 0x0204	;read 4 sectors
	mov cx, 0x0002	;cylinder 0, sector 2
	mov dx, 0x0080	;head 0, dl = 80 - disk on ch0
	xor bx, bx	;read to 0x07e00
	int 0x13

;Отключить прерывания (cli)
;Включить A20 line(включена по умолчанию в боксе)
;Рагрузить размер и линейный адрес GDT в GDTR (lgdt [gdtr_struc_adress]
	;первые 2 байта - лимит, следющие 4 - адрес gdt
;Выставить бит PE в CR0
;Инициализировать сегментные регистры


jmp $

data:
	msg: db "Hello, world!", 0
	msg_len: equ $ - msg - 1
times 510 - ($ - $$) db 0
db 0x55, 0xaa
