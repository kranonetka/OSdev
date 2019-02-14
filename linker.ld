OUTPUT_FORMAT(binary)
OUTPUT_ARCH(i386)

SECTIONS
{
	. = 0x7e00;

	.text . :
	{
		init_kernel.o(.text)
		*(EXCLUDE_FILE(init_kernel.o) .text)
	}

	.data :
	{
		*(.data)
		*(.rodata)
	}

	.bss :
	{
		*(.bss)
	}
}
