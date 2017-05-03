
#	-*- Makefile -*-

openocd:
#	openocd -f /usr/share/openocd/scripts/interface/stlink-v2.cfg \
#		-f /usr/share/openocd/scripts/target/stm32f1x.cfg
	openocd -f ../make/openocd-100ask-openjtag.cfg \
		-f /usr/share/openocd/scripts/target/stm32f1x.cfg


$(OUTDIR)/gdb.init: ../make/gdb.init.in
	sed -e 's|PROJECT|$(OUT).elf|' $< >$@


gdb:	$(OUTDIR)/gdb.init
	$(GDB) -x $(OUTDIR)/gdb.init
