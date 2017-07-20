
MEMORY
{
	rom (rx) : ORIGIN = 0x08000000, LENGTH = 128K
	ram (rwx) : ORIGIN = 0x20000000, LENGTH = 20K
}

EXTERN (hw_vectors)

SECTIONS
{
	.text : {
		*(.vectors)
		*(.text)
		*(.text.*)
		*(.rodata)
		*(.rodata.*)
	} >ram

	.data : {
		*(.data)
	} >ram

	.bss : {
		*(.bss)
	} >ram
}
