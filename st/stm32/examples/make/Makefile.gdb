
#	-*- Makefile -*-

openocd:
#	openocd -f /usr/share/openocd/scripts/interface/stlink-v2.cfg \
#		-f /usr/share/openocd/scripts/target/stm32f1x.cfg
	openocd -f ../make/openocd-100ask-openjtag.cfg \
		-f /usr/share/openocd/scripts/target/stm32f1x.cfg


$(OUTDIR)/gdb.init: ../make/gdb.init.in
	sed -e 's|PROJECT|$(OUT).elf|' $< >$@


gdb:	$(OUTDIR)/gdb.init $(OUT).elf
	$(GDB) -x $(OUTDIR)/gdb.init

run:	$(OUT).elf
	@$(GDB)	-ex "target remote localhost:3333" 		\
		-ex "mon reset halt"				\
		-ex "load $(OUT).elf"				\
		-ex "mon mww 0xE000ED08 0x20000000"		\
		-ex 'set $$sp = *(int*)0x20000000'		\
		-ex 'set $$pc = *(int*)0x20000004'		\
		-ex "mon resume"				\
		-ex "detach"					\
		-ex "quit"
