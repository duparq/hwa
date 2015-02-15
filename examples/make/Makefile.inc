
#	-*- makefile -*-

#	This makefile is included after DEVICE has been set
#	There are all the rule to build the binary

#$(warning "INCLUDE: Makefile.inc")

#	Default target
#
.PHONY: all
all:	$(INC_HWA) bin lst size crc

hex:	$(OUTDIR)/$(OUT).hex
bin:	$(OUTDIR)/$(OUT).bin
lst:	$(OUTDIR)/$(OUT).lst


#  Dependencies
#
#	Build one dependency files for each source file
#
DEPS		 = $(SOURCES:.c=.d)
DEPS		:= $(DEPS:.sx=.d)
DEPS		:= $(addprefix $(OUTDIR)/,$(DEPS))

deps:	$(DEPS)

$(OUTDIR)/%.d: %.c
	@echo "RULE: $@: $^"
	@mkdir -p $(OUTDIR)
	@set -e; rm -f $@; \
	$(CC) -M $(INCLUDES) $< > $@.tmp; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.tmp > $@; \
	rm -f $@.tmp

$(OUTDIR)/%.d: %.sx
	@echo "RULE: $@: $^"
	@mkdir -p $(OUTDIR)
	@set -e; rm -f $@; \
	$(CC) -M $(INCLUDES) $< > $@.tmp; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.tmp > $@; \
	rm -f $@.tmp
#
#	Load dependencies
#
-include $(DEPS)


#  Documentation
#
.PHONY: doc
doc:
	(cd $(CWD)../.. && make doc)


#  Device-specific Makefile
#
-include $(CWD)Makefile.$(DEVICE_VENDOR)$(DEVICE_ARCH)


#  Chip programming hardware/software
#
ifeq (,$(PROG_SW))
  PROG_SW	=	diabolo
else
  PROG_SW	=	avrdude
  PROG_HW	=	usbasp
endif

ifneq ($(strip $(PROG_SW)),)
  -include $(CWD)Makefile.$(PROG_SW)
endif

ifneq ($(strip $(PROG_HW)),)
  -include $(CWD)Makefile.$(PROG_HW)
endif


#  Compiling commands, path & options
#
# PATH		:= $(HOME)/dev/gcc-toolchains/4.7.0/bin:$(PATH)
ARCH		= $(DEVICE_ARCH)-
CC		= $(ARCH)gcc
AS		= $(ARCH)as
OBJCOPY		= $(ARCH)objcopy
ODUMP		= $(ARCH)objdump
GDB		= $(ARCH)gdb
SIZE		= $(ARCH)size
STD		= c1x

CFLAGS		+= -mmcu=$(DEVICE)
CFLAGS		+= -std=$(STD)
CFLAGS		+= -Wall
CFLAGS		+= -Wextra
#CFLAGS		+= -pedantic
CFLAGS		+= -Wpedantic	# GCC 4.8
CFLAGS		+= -fno-diagnostics-show-caret	# GCC 4.8
CFLAGS		+= -ftrack-macro-expansion=0
#CFLAGS		+= -fomit-frame-pointer
CFLAGS		+= -ffunction-sections
#CFLAGS		+= -fno-builtins
CFLAGS		+= -fpack-struct
#CFLAGS		+= -fshort-enums
#CFLAGS		+= -mcall-prologues
CFLAGS		+= -g
#CFLAGS		+= -pipe
CFLAGS		+= -Os
#CFLAGS		+= -O0
#CFLAGS		+= -O1
#CFLAGS		+= -O2
#CFLAGS		+= -O3
CFLAGS		+= $(DEFINES)
CFLAGS		+= $(INCLUDES)

AFLAGS		+= -mmcu=$(DEVICE)
AFLAGS		+= -Wall
#AFLAGS		+= -Wextra
AFLAGS		+= $(DEFINES)
AFLAGS		+= $(INCLUDES)


LDFLAGS		+= -mmcu=$(DEVICE)
#LDFLAGS		+= -s
LDFLAGS		+= -Wl,-Map,$(OUTDIR)/$(OUT).map,--cref
#LDFLAGS		+= -Wl,-u,vfprintf -lprintf_min
#LDFLAGS		+= -nostartfiles
LDFLAGS		+= -Wl,--gc-sections
#LDFLAGS		+= -nostdlib # Provide clear_bss aso
#LDFLAGS		+= -Wl,--section-start=.protext=0x1E00
#LDFLAGS		+= -Wl,--section-start=.bss.pro=0x800100
#LDFLAGS		+= -L/usr/lib/avr/lib
#LDFLAGS		+= -L/home/indy/dev/avr/toolchain/current/install/avr/lib
#LDFLAGS		+= -lm


#ODUMPFLAGS	= -S
ODUMPFLAGS	= -h -S
#ODUMPFLAGS	= -D


#  Object files list (from source files list)
#
OBJECTS		 = $(SOURCES:.c=.$(DEVICE).o)
OBJECTS		:= $(OBJECTS:.sx=.$(DEVICE).o)
OBJECTS		:= $(addprefix $(OUTDIR)/,$(OBJECTS))


#	Preprocess
#
%.cp.c: %.c
	$(CPP) $(CFLAGS) $< >$@
#	$(CPP) $(CFLAGS) $< |sed -e 's/;/;\n/g'|bcpp -s -i 2 -bcl | sed -e 's/#/\/\//g' > $@

%.cp.s: %.s
	$(CPP) $(AFLAGS) $< >$@

%.cp.sx: %.sx
	$(CPP) $(AFLAGS) $< >$@
	if grep '\.fail' $@ ; then exit 1 ; fi
	if grep '#error' $@ ; then exit 1 ; fi

%.s : %.c
	$(CC) -mmcu=$(DEVICE) -std=c99 -Wall -Wextra -Os -c -g -S $< -o $@


#	Compile and link
#
$(OBJECTS): | $(OUTDIR) $(INC_HWA)		# Create directory if needed

$(OUTDIR):
	@mkdir $(OUTDIR)


$(OUTDIR)/%.$(DEVICE).o : %.c
	@echo "RULE: $@: $^"
	$(CC) $(CFLAGS) -c $< -o $@

$(OUTDIR)/%.o : %.c
	@echo "RULE: $@: $^"
	$(CC) $(CFLAGS) -c $< -o $@

$(OUTDIR)/%.$(DEVICE).o : %.s
	@echo "RULE: $@: $^"
	$(AS) $(AFLAGS) $< -o $@

$(OUTDIR)/%.o : %.s
	@echo "RULE: $@: $^"
	$(AS) $(AFLAGS) $< -o $@

# $(OUTDIR)/%.$(MCU).o : %.sx Makefile
# 	grep '\.fail' $< && $(CC) $(AFLAGS) -c $< -o $@
# $(OUTDIR)/%.o : %.sx Makefile
# 	$(CC) $(AFLAGS) -c $< -o $@

$(OUTDIR)/%.$(DEVICE).o : %.cp.sx
	@echo "RULE: $@: $^"
	$(CC) $(AFLAGS) -c $< -o $@

# $(OUTDIR)/%.$(MCU).o : %.sx
# 	$(CC) $(AFLAGS) -c $< -o $@

# $(OUTDIR)/%.o : %.cp.sx
# 	if grep '\.fail' $< ; then exit1 ; else exit 0 ; fi
# 	$(AS) $(AFLAGS) -o $@ $<

$(OUTDIR)/$(OUT).elf : $(OBJECTS) $(LDSCRIPT)
	@echo "RULE: $@: $^"
	$(CC) $(LDFLAGS) -o $@ $(OBJECTS) $(LIBS)


#  PADTO is used to fill unused flash memory space with 0xFF bytes
#
ifneq (,$(DEVICE_FLASH_SIZE))
  PADTO = --pad-to $(DEVICE_FLASH_SIZE)
else
  PADTO =
endif


#  Post-linking targets
#
%.bin : %.elf
	$(OBJCOPY) -R .eeprom -O binary --gap-fill=0xFF $(PADTO) $^ $@

%.hex : %.elf
	$(OBJCOPY) --gap-fill=0xFF -R .eeprom -O ihex $^ $@

%.lst : %.elf
	$(ODUMP) $(ODUMPFLAGS) $^ >$@

#  Size of the generated binary
#
.PHONY: size
size:	$(OUTDIR)/$(OUT).elf
	$(SIZE) $^
