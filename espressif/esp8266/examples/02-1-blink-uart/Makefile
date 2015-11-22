
#	Source files
#
SOURCES		= user.c

#	Target board
#
BOARD		= esp-wroom-02

#	Output directory and files basename
#
OUTDIR		= build/$(BOARD)
OUT		= $(OUTDIR)/out


HERE		:= $(dir $(lastword $(MAKEFILE_LIST)))

#	SDK
#
ESP		:= $(HOME)/dev/esp8266
SDK		?= $(ESP)/esp-open-sdk
IOT_SDK		?= $(ESP)/esp_iot_sdk_v1.4.0

#  Directories searched for include files:
#
INCLUDES	 = -I.
INCLUDES	+= -I$(IOT_SDK)/include
INCLUDES	+= -I$(HERE)../../../../include

#  Messages in english
#
LANG		:= C

#  Toolchain commands
#
PATH		:= $(SDK)/xtensa-lx106-elf/bin:$(PATH)

ARCH		:= xtensa-lx106-elf-
PP		:= $(ARCH)gcc -E
CC		:= $(ARCH)gcc
LD		:= $(ARCH)gcc
AR		:= $(ARCH)ar
AS		:= $(ARCH)as
OC		:= $(ARCH)objcopy
OD		:= $(ARCH)objdump
GDB		:= $(ARCH)gdb
SIZE		:= $(ARCH)size

ESPTOOL		?= python $(SDK)/esptool/esptool.py


#	Default target
#
.PHONY: all
all:	deps size


################################################################################
#									       #
#			Cleaning					       #
#									       #
################################################################################

#  Remove built files under the working directory
#
.PHONY: clean
clean:
	@echo Cleaning...
	@find . -name 'build' -prune -exec rm -rf {} ';'
	@find . '(' 			\
		-name '*~' 		\
		-o -name '*.cp.*'	\
		-o -name '*.hwa.c'	\
		-o -name '*.pyc'	\
		')' -exec rm {} ';'


################################################################################
#									       #
#			Source dependencies				       #
#									       #
################################################################################

.PHONY: deps
deps:	$(DEPS)

#  List of dependency files
#  One dependency file is generated for each .c or .sx source file
#
DEPS		 = $(SOURCES:.c=.d)
DEPS		:= $(DEPS:.sx=.d)
DEPS		:= $(addprefix $(OUTDIR)/,$(DEPS))

#  Include dependencies
#
-include $(DEPS)

#	Dependencies of .c files
#
$(OUTDIR)/%.d: %.c
#	@echo "RULE: $@: $^"
	@mkdir -p $(OUTDIR)
	@set -e ; rm -f $@ ; $(PP) -MM $(INCLUDES) $(DEFINES) $< >$@.tmp	;\
	sed 's,\($*\)\.o[ :]*,$(OUTDIR)/\1.o $@ : ,g' < $@.tmp > $@

#	Dependencies of .sx files
#
$(OUTDIR)/%.d: %.sx
#	@echo "RULE: $@: $^"
	@mkdir -p $(OUTDIR)
	@set -e ; rm -f $@ ; $(PP) -MM $(INCLUDES) $(DEFINES) $< > $@.tmp	;\
	sed 's,\($*\)\.o[ :]*,$(OUTDIR)/\1.o $@ : ,g' < $@.tmp > $@


#  Preprocess only
#
force: ;
%.cp.c: %.c force
	@echo "(PP) $@: $^"
	@$(Q) $(PP) $(INCLUDES) $(DEFINES) $< >$@


################################################################################
#									       #
#			Compiling					       #
#									       #
################################################################################

#  Object files list (from source files list)
#
OBJECTS		 = $(SOURCES:.c=.o)
OBJECTS		:= $(addprefix $(OUTDIR)/,$(OBJECTS))

#  Compiling options
#
# CFLAGS		+= -mmcu=$(DEVICE)
CFLAGS		+= -std=c1x
CFLAGS		+= -Wall
CFLAGS		+= -Wextra

CFLAGS		+= -Wpointer-arith
CFLAGS		+= -Wundef
CFLAGS		+= -Werror
CFLAGS		+= -Wl,-EL
CFLAGS		+= -fno-inline-functions
CFLAGS		+= -nostdlib
CFLAGS		+= -mlongcalls
CFLAGS		+= -mtext-section-literals
CFLAGS		+= -D__ets__
CFLAGS		+= -DICACHE_FLASH

#CFLAGS		+= -pedantic
#CFLAGS		+= -Wpedantic	# GCC 4.8
CFLAGS		+= -fno-diagnostics-show-caret	# GCC 4.8
CFLAGS		+= -ftrack-macro-expansion=0
#CFLAGS		+= -fomit-frame-pointer
CFLAGS		+= -ffunction-sections
#CFLAGS		+= -fno-builtins
CFLAGS		+= -fpack-struct
#CFLAGS		+= -fshort-enums
#CFLAGS		+= -mcall-prologues
#CFLAGS		+= -g
#CFLAGS		+= -pipe
CFLAGS		+= -Os
#CFLAGS		+= -O0
#CFLAGS		+= -O1
CFLAGS		+= -O2
#CFLAGS		+= -O3
CFLAGS		+= $(DEFINES)
CFLAGS		+= $(INCLUDES)
#CFLAGS		+= -save-temps


$(OUTDIR)/%.o: %.c
	@echo "RULE: $@ : $^"
	@mkdir -p $(OUTDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

#  We want .sx files to be preprocessed first
#
$(OUTDIR)/%.o: $(OUTDIR)/%.cp.sx
#	@echo "RULE: $@ : $^"
	@mkdir -p $(OUTDIR)
	@$(CC) $(AFLAGS) -c $< -o $@


################################################################################
#									       #
#			Linking						       #
#									       #
################################################################################

#  Create an archive of all object files
#
$(OUT).a: $(OBJECTS)
	@echo "RULE: $@ : $^"
	@$(AR) cru $@ $^

#	Flags
#
#LDFLAGS		+= -mmcu=$(DEVICE)
#LDFLAGS		+= -s
#LDFLAGS		+= -Wl,-Map,$(OUT).map,--cref
#LDFLAGS		+= -Wl,-u,vfprintf -lprintf_min
#LDFLAGS		+= -nostartfiles
#LDFLAGS		+= -Wl,--gc-sections
#LDFLAGS		+= -nostdlib # Provide clear_bss aso
#LDFLAGS		+= -Wl,--section-start=.protext=0x1E00
#LDFLAGS		+= -Wl,--section-start=.bss.pro=0x800100
#LDFLAGS		+= -L/usr/lib/avr/lib
#LDFLAGS		+= -L$(HOME)/dev/avr/toolchain/current/install/avr/lib
#LDFLAGS		+= -lm
LDFLAGS		+= -nostdlib
LDFLAGS		+= -Wl,--no-check-sections
LDFLAGS		+= -u call_user_start
LDFLAGS		+= -Wl,-static

IOT_SDK_LIBDIR	?= $(IOT_SDK)/lib


#	Libraries used in this project, mainly provided by the IOT_SDK
#
LIBS		 = -lc
LIBS		+= -lgcc
LIBS		+= -lhal
LIBS		+= -lpp
LIBS		+= -lphy
LIBS		+= -lnet80211
LIBS		+= -llwip
LIBS		+= -lwpa
LIBS		+= -lmain

#	Linker script
#
LD_SCRIPT	?= $(IOT_SDK)/ld/eagle.app.v6.ld

#	ELF output
#
$(OUT).elf: $(OUT).a $(LD_SCRIPT)
	@echo "RULE: $@ : $^"
	@$(LD) -L$(IOT_SDK_LIBDIR) -T$(LD_SCRIPT) $(LDFLAGS) \
		-Wl,--start-group $(LIBS) $(OUT).a -Wl,--end-group -o $@


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
lst:	$(OUT).lst

%.lst: %.a
	@echo "RULE: $@ : $^"
	@$(OD) -d $^ >$@

%.elf.lst: %.elf
	@echo "RULE: $@ : $^"
	@$(OD) -d $^ >$@

.PHONY: crc
crc: $(OUT).lst
	@echo "RULE: $@ : $^"
	@crc32 $<

#  Size of the generated binary code
#
.PHONY: size
size:	$(OUT).elf
	@$(SIZE) $^


################################################################################
#									       #
#			Install						       #
#									       #
################################################################################

#  Installable binaries
#
bin: $(OUT).0x00000.bin $(OUT).0x40000.bin

$(OUT).0x00000.bin $(OUT).0x40000.bin: $(OUT).elf
	@echo "RULE: $@ : $^"
	@$(ESPTOOL) elf2image $< -o $(OUT).

install: $(OUT).0x00000.bin $(OUT).0x40000.bin
	@echo "RULE: $@ : $^"
	@ARGS=""	;\
	X=0x00000	;\
	if ! test -f /tmp/$$X.bin || ! diff -q $(OUT).$$X.bin /tmp/$$X.bin >/dev/null ; then \
	  ARGS="$$ARGS $$X $(OUT).$$X.bin"	;\
	fi					;\
	X=0x40000	;\
	if ! test -f /tmp/$$X.bin || ! diff -q $(OUT).$$X.bin /tmp/$$X.bin >/dev/null ; then \
	  ARGS="$$ARGS $$X $(OUT).$$X.bin"	;\
	fi					;\
	if test -n "$$ARGS" ; then				\
	  $(ESPTOOL) --baud 460800 write_flash $$ARGS		\
	  && (cp -a $(OUT).0x00000.bin /tmp/0x00000.bin		;\
	      cp -a $(OUT).0x40000.bin /tmp/0x40000.bin)	;\
	else						\
	  echo Nothing new to be programmed		;\
	fi

#	echo $(ESPTOOL) --baud 460800 write_flash \
#		0x00000 $(OUT).0x00000.bin 0x40000 $(OUT).0x40000.bin

test: $(OUT).0x00000.bin $(OUT).0x40000.bin
	@echo "RULE: $@ : $^"
	ls -l $(OUTDIR)
