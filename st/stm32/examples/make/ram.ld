
MEMORY
{
	rom (rx) : ORIGIN = 0x08000000,  LENGTH = 128K
	ram (rwx) : ORIGIN = 0x20000000, LENGTH = 20K
}

EXTERN (hw_vectors)

SECTIONS
{
	.text : {
		. = ALIGN(4);
		_stext = . ;
		*(.vectors)
		*(.text)
		*(.text.*)
		*(.rodata)
		*(.rodata.*)
		. = ALIGN(4);
		_etext = . ;
		_sidata = . ;
	} >ram

	.data : {
		. = ALIGN(4);
		_sdata = . ;
		*(.data)
		. = ALIGN(4);
		_edata = . ;
	} >ram

	.bss : {
		. = ALIGN(4);
		_sbss = . ;
		*(.bss)
		. = ALIGN(4);
		_ebss = . ;
	} >ram
}
