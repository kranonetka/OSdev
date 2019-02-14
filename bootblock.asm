; vim:ft=nasm
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

read_sectors:
	mov bx, 0x07e0
	mov es, bx
	xor bx, bx
	mov ah, 0x02	;read sectors
	mov al, 64	;16 sectors
	mov cx, 0x0002	;cylinder 0, sector 2
	mov dx, 0x0080	;head 0, dl = 80 - disk on ch0
	int 0x13	;read to 0x07e00

protected_mode:
	cli
	lgdt [gdt_info]
	mov eax, cr0
	or al, 1
	mov cr0, eax

jmp 0x08:($+5) ;Инициализация регистра cs
[BITS 32]
;Инициализация остальных сегментных регистров
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov ax, 0x18
	mov gs, ax
	mov ax, 0x20
	mov ss, ax
	mov esp, 0xfffffff0

jmp 0x7e00	;Переход на ядро

gdt_start:
;null descriptor:
	dd 0, 0
;code segment descriptor:
	db 0xff, 0xff	;limit 0-15
	db 0x00, 0x00, 0x00	;base 0-23
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
;data segment descriptor:
	db 0xff, 0xff	;limit 0-15
	db 0x00, 0x00, 0x00	;base 0-23
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
;video segment descriptor:
	db 0xa0, 0x0f	;limit 0-15
	db 0x00, 0x80, 0x0b	;base 0-23
	db 10010010b	;access byte
	db 00000000b	;flags+ limit 16-19
			;granularity - 0
			;0 - 16 bit
	db 0	;base 24-31
		;base 0x000b8000
		;limit 0xfa0 (80*25*2)
;stack segment descriptor:
	db 0xe1, 0xff	;limit 0-15
	db 0x00, 0xf0, 0x09	;base 0-23
	db 10010110b	;access byte (2: 1 - segment grows down)
	db 01001111b	;granularity - 0
	db 0x00	;base 24-31
		;base 0x0009f000
		;limit 0xffffe1

gdt_info:
	dw gdt_info - gdt_start - 1
	dd gdt_start

times 510 - ($ - $$) db 0
db 0x55, 0xaa
