OUTPUT_FORMAT(binary)
OUTPUT_FORMAT(i386)

SECTIONS
{
	. = 0x7e00;

	.text . :
	{
		start.o(.text)
		*(EXCLUDE_FILE(start.o) .text)
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
