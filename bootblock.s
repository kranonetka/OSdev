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
	mov ax, 0x02ff	;read 256 sectors
	mov cx, 0x0002	;cylinder 0, sector 2
	mov dx, 0x0080	;head 0, dl = 80 - disk on ch0
	int 0x13	;read to 0x07e00

jmp 0x7e00	;Переход на ядро

times 510 - ($ - $$) db 0
db 0x55, 0xaa
