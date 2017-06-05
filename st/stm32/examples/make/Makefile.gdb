
#	-*- Makefile -*-

.PHONY: openocd
openocd:
	@openocd -c 'source [find interface/stlink-v2.cfg]'	\
		 -c 'source [find target/stm32f1x.cfg]' &	\

.PHONY: gdb
gdb:	openocd $(OUT).elf
	$(GDB)	-ex "target remote localhost:3333" 		\
		-ex "mon reset halt"				\
		-ex "load $(OUT).elf"				\
		-ex "mon mww 0xE000ED08 0x20000000"		\
		-ex 'set $$sp = *(int*)0x20000000'		\
		-ex 'set $$pc = *(int*)0x20000004'

.PHONY: run
run:	openocd $(OUT).elf
	$(GDB)	-ex "target remote localhost:3333" 		\
		-ex "mon reset halt"				\
		-ex "mon init"					\
		-ex "load $(OUT).elf"				\
		-ex "mon mww 0xE000ED08 0x20000000"		\
		-ex 'set $$sp = *(int*)0x20000000'		\
		-ex 'set $$pc = *(int*)0x20000004'		\
		-ex "mon resume"				\
		-ex "mon shutdown"				\
		-ex "detach"					\
		-ex "quit"
