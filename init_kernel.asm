; vim:ft=nasm
; Промежуточный модуль для перехода в C
[BITS 32]
section .text
extern cmain
call cmain

mov ebx, 80*24
mov ah, 0x0c
mov esi, msg

CDone:
	lodsb
	test al, al
	jz end_CDone
	mov [gs:(ebx*2)], ax
	inc ebx
	jmp CDone
end_CDone:
	jmp $

section .data
msg: db "C Done!", 0
