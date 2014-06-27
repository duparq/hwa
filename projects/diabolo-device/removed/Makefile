
#	Processor: atmega8, atmega88, atmega16, etc.
#
MCU		= attiny45
PIN_TXD		= INT0
PIN_RXD     	= INT0
# PIN_DBG		=
X_SPD		= 0

DEFINES		+= -DPIN_TXD=$(PIN_TXD) -DPIN_RXD=$(PIN_RXD) -DPIN_DBG=$(PIN_DBG) -DX_SPD=$(X_SPD)

#	Source files
#
SOURCES		=	diabolo-$(MCU).s

#	Output base name
#
OUT		=	out

#	Software used for burning: avrdude, uisp, etc.
#
PROG_SW		=	avrdude

#	Hardware used for burning (dapa, usbasp, stk200...)
#
PROG_HW		= 	usbasp

#	Building directory
#
BUILDIR		=	build

#	Target architecture
#
ARCH		= 	avr-

#	Building toolchain path
#
PATH		:= $(HOME)/dev/gcc-toolchains/4.7.0/bin:$(PATH)


#	Building commands & options
#
CC		= $(ARCH)gcc
AS		= $(ARCH)as
OBJCOPY		= $(ARCH)objcopy
ODUMP		= $(ARCH)objdump
GDB		= $(ARCH)gdb
SIZE		= $(ARCH)size
STD		= c99

MMCU		= -mmcu=$(MCU)

CFLAGS		+= $(MMCU)
CFLAGS		+= -std=$(STD)
CFLAGS		+= -Wall
CFLAGS		+= -Wextra
#CFLAGS		+= -mcall-prologues
#CFLAGS		+= -pedantic
#CFLAGS		+= -fomit-frame-pointer
CFLAGS		+= -ffunction-sections
#CFLAGS		+= -fno-builtins
#CFLAGS		+= -fpack-struct
#CFLAGS		+= -fshort-enums
#CFLAGS		+= -g
#CFLAGS		+= -pipe
CFLAGS		+= -Os
#CFLAGS		+= -O0
#CFLAGS		+= -O1
#CFLAGS		+= -O2
#CFLAGS		+= -O3

#INCLUDES	+= -I$(PWD) -I$(PWD)/inc -I$(PWD)/hwa -I$(PWD)/lib  -I$(PWD)/mod
#INCLUDES	+= -I$(PWD)/inc
INCLUDES	+= -I.

CFLAGS		+= $(DEFINES)
CFLAGS		+= $(INCLUDES)

AFLAGS		+= $(INCLUDES)

LDFLAGS		+= $(MMCU)
#LDFLAGS		+= -s
#LDFLAGS		+= -Wl,-Map,$(BUILDIR)/$(OUT).map,--cref
#LDFLAGS		+= -Wl,-u,vfprintf -lprintf_min
#LDFLAGS		+= -Wl,--section-start=.bootloader=$(BOOTLOADER)
#LDFLAGS		+= -Wl,--defsym=diabolo=$(BOOTLOADER)
#LDFLAGS		+= -Wl,--defsym=program_start=0
LDFLAGS		+= -nostartfiles
#LDFLAGS		+= -Wl,--gc-sections
LDFLAGS		+= -nostdlib
#LDFLAGS		+= -Wl,--section-start=.protext=0x1E00
#LDFLAGS		+= -Wl,--section-start=.bss.pro=0x800100
#LDFLAGS		+= -L/usr/lib/avr/lib
#LDFLAGS	+= -L/home/indy/dev/avr/toolchain/current/install/avr/lib
#LDFLAGS		+= -lm

#LD_LIBRARY_PATH = /home/indy/dev/avr/toolchain/current/install/avr/lib

AFLAGS		+= $(MMCU) $(DEFINES)

#ODUMPFLAGS	= -S
#ODUMPFLAGS	= -D
ODUMPFLAGS	= -d

DEPS		= $(BUILDIR)/$(OUT).$(MCU).deps


#	Calcule les noms des fichiers objets à générer
#	par substitution des extensions
#
S1		=	$(SOURCES:.c=.$(MCU).o)
S2		=	$(S1:.s=.$(MCU).o)
OBJECTS		=	$(patsubst %,$(BUILDIR)/%,$(S2))


#	Cible par défaut : préparer le fichier de programmation
#
all:	clean hex bin lst size

hex:	$(BUILDIR)/$(OUT).hex
bin:	$(BUILDIR)/$(OUT).bin
lst:	$(BUILDIR)/$(OUT).lst
size:	$(BUILDIR)/$(OUT).elf
	$(SIZE) $^

install: burn write_fuses

#	Règle de compilation : comment faire un .hex à partir d'un .elf
#
%.hex : %.elf
#	@echo OS=$(OS)
	$(OBJCOPY) --gap-fill=0xFF -R .eeprom -O ihex $^ $@

%.lst : %.elf
	$(ODUMP) $(ODUMPFLAGS) $^ >$@

#	Règle de compilation : comment faire un .bin à partir d'un .elf
#
%.bin : %.elf
	$(OBJCOPY) -R .eeprom -O binary --gap-fill=0xFF --pad-to $(ROMEND) $^ $@

%.elf:	%.o
	$(CC) $(LDFLAGS) -o $@ $^

#	Règle de compilation : comment faire un .elf à partir d'un .o
#
$(BUILDIR)/$(OUT).elf : $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)

#	Règle de compilation : comment faire un .o à partir d'un .s
#
_$(BUILDIR)/%.$(MCU).o : %.s
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILDIR)/%.$(MCU).o : %.s
	@mkdir -p $(dir $@)
	$(AS) $(AFLAGS) -g $< -o $@


#	gdb initialisation for STM32
#
$(BUILDIR)/gdb.init: tools/gdb.init.in
	sed -e 's|OUT|$(BUILDIR)/$(OUT).elf|' $< >$@

list:
	echo Makefile Makefile.* config.[hs] diabolo-*.s

#	Nettoye le répertoire
#
clean:
	find . '(' 			\
		-name '*~' 		\
		-o -name '*.deps' 	\
		-o -name '*.map' 	\
		-o -name '*.a'		\
		-o -name '*.bin'	\
		-o -name '*.cpp.*'	\
		-o -name '*.o'		\
		-o -name '*.pyc'	\
		-o -name '*.so'		\
		-o -name '*.out'	\
		-o -name '*.elf'	\
		-o -name '*.hex'	\
		')' -exec rm {} ';'
	rm -rf $(BUILDIR)

#	Calcule les dépendances des fichiers sources (.c)
#
deps:	$(DEPS)
$(DEPS): $(SOURCES)
#	@echo Rebuilding deps:
	@mkdir -p $(dir $@)
	@>$@
	@for s in $(SOURCES) ; do \
	  $(CC) -MM $(DEFINES) $(MMCU) \
	    -MT $(BUILDIR)/$(notdir $${s%.*}.$(MCU).o) $(INCLUDES) $$s >>$@ ;\
	done


tarball: clean
	SRC=$$(basename $$PWD)					;\
	DST=$$SRC.tar.bz2					;\
	tar -cvO --exclude=trash --exclude=$$DST		\
		../$$SRC | bzip2 >$$DST


#	Liste des cibles qui ne sont pas des fichiers
#
.PHONY: flash load upload download erase read_fuses select_xtal_osc \
	select_intern_osc_1 select_intern_osc_8 reset clean deps size

-include Makefile.$(MCU)
-include Makefile.$(PROG_SW)

#	Inclut les dépendances (si elles existent déjà).
#
-include $(DEPS)
