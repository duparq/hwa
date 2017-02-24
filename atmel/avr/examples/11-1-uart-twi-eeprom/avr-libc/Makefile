
#	Source files
#
SOURCES		=	twitest.c

DEVICE		=	atmega328p

#	Output basename and directory
#
OUTDIR		= build
OUT		= $(OUTDIR)/out

#  Messages in english
#
LANG		:= C

#  Toolchain commands
#
ARCH		:= avr-
CPP		:= $(ARCH)cpp
CC		:= $(ARCH)gcc
AS		:= $(ARCH)as
OBJCOPY		:= $(ARCH)objcopy
ODUMP		:= $(ARCH)objdump
GDB		:= $(ARCH)gdb
SIZE		:= $(ARCH)size


.PHONY: all
all:	deps elf lst size


.PHONY: elf
elf:	$(OUT).elf


#  Remove built files under the working directory
#
.PHONY: clean
clean:
	@find . -name 'build*' -prune -exec rm -rf {} ';'
	@find . '(' 			\
		-name '*~' 		\
		-o -name '*.cp.*'	\
		-o -name '*.hwa.c'	\
		-o -name '*.pyc'	\
		')' -exec rm {} ';'


################################################################################
#									       #
#			Dependencies					       #
#									       #
################################################################################

hex:	$(OUT).hex
bin:	$(OUT).bin
lst:	$(OUT).lst

.PHONY: deps
deps:	$(DEPS)

#  List of dependency files
#  One dependency file is generated for each .c or .sx source file
#
DEPS	 = $(SOURCES:.c=.d)
DEPS	:= $(DEPS:.sx=.d)
DEPS	:= $(addprefix $(OUTDIR)/,$(DEPS))

#  Include dependencies
#
-include $(DEPS)

#	Dependencies of .c files
#
$(OUTDIR)/%.d: %.c
#	@echo "RULE: $@: $^"
	@mkdir -p $(OUTDIR)
	@set -e ; rm -f $@ ; $(CPP) -MM $(INCLUDES) $(DEFINES) $< >$@.tmp	;\
	sed 's,\($*\)\.o[ :]*,$(OUTDIR)/\1.o $@ : ,g' < $@.tmp > $@


################################################################################
#									       #
#			Compiling					       #
#									       #
################################################################################

#  Compiling options
#
CFLAGS		+= -mmcu=$(DEVICE)
CFLAGS		+= -std=c1x
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
#CFLAGS		+= -save-temps

$(OUTDIR)/%.o: %.c
#	@echo "RULE: $@ : $^"
	@mkdir -p $(OUTDIR)
	$(CC) $(CFLAGS) -c $< -o $@


################################################################################
#									       #
#			Linking						       #
#									       #
################################################################################

#  Object files list (from source files list)
#
OBJECTS		 = $(SOURCES:.c=.o)
OBJECTS		:= $(addprefix $(OUTDIR)/,$(OBJECTS))

LDFLAGS		+= -mmcu=$(DEVICE)
#LDFLAGS		+= -s
LDFLAGS		+= -Wl,-Map,$(OUT).map,--cref
#LDFLAGS		+= -Wl,-u,vfprintf -lprintf_min
#LDFLAGS		+= -nostartfiles
LDFLAGS		+= -Wl,--gc-sections
#LDFLAGS		+= -nostdlib # Provide clear_bss aso
#LDFLAGS		+= -Wl,--section-start=.protext=0x1E00
#LDFLAGS		+= -Wl,--section-start=.bss.pro=0x800100
#LDFLAGS		+= -L/usr/lib/avr/lib
#LDFLAGS		+= -L/home/indy/dev/avr/toolchain/current/install/avr/lib
#LDFLAGS		+= -lm

$(OUT).elf: $(OBJECTS) $(LDSCRIPT)
#	@echo "RULE: $@ : $^"
	@$(CC) $(LDFLAGS) -o $@ $(OBJECTS) $(LIBS)


################################################################################
#									       #
#			Post-linking					       #
#									       #
################################################################################


#  Object dump flags:
#
#  -d: disassembly
#  -S: disassembly + source code
#  -h: section headers
#
%.lst: %.elf
#	@$(ODUMP) -S $^ >$@
	@$(ODUMP) -d $^ >$@

#  Size of the generated binary
#
.PHONY: size
size:	$(OUT).elf
	@$(SIZE) $^
