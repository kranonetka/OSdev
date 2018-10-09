;Entering protected mode
[BITS 16]

cli
lgdt [gdtr]
mov eax,cr0
or al,1
mov cr0,eax

jmp 0x08:PModeMain

PModeMain:
;init segment regs

gdtr:
	;create struct

times 512 - ($ - $$) db 0

