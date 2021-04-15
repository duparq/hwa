
#	Source files
#
SOURCES		=	main.c

#  	Search include files in ~hwa/include/
#
INCLUDES	:= -I$(MFD)../../../hwa/include 
INCLUDES	:= -I$(MFD)../../../../hwa/include 

#  Output directory and files basename
#
OUTDIR		:= build
OUT		:= $(OUTDIR)/out

#  Messages in english
#
LANG		:= C

#	Default make target
#
.PHONY: default
default: expand

.PHONY: expand
expand: main.cp.c
	@sed -n '/EXPAND/,$$p' $<


.PHONY: all
all:	deps bin lst size stat


################################################################################
#									       #
#		Determine target device					       #
#									       #
################################################################################

#  Create a C source file that collects HWA definitions relative to the
#  configuration of the target device
#
#	Quoting with HW_QUOTE is required for make not to show an error message
#	when it reads complex values.
#
$(OUT).hwa.c: $(SOURCES)
#	@echo "RULE: $@"
	@mkdir -p $(dir $@)
	@cat $< >$@
	@echo "DEVICE=HW_DEVICE" >>$@
	@echo "DEVICE_ARCH=HW_DEVICE_ARCH" >>$@

#  Load informations about the target device
#
#  Let CPP process board.c using the definitions found in the board's header
#  file. __ASSEMBLER__ is defined so that HWA will not load the definitions that
#  produce C code and that are useless for what we want to do.
#
$(OUT).hwa: $(OUT).hwa.c
#	@echo "RULE: $@ : $^"
	@cpp $(INCLUDES) -D__ASSEMBLER__ $< 2>/dev/null | grep '^DEVICE' >$@

include $(OUT).hwa


ifeq (stm32,$(DEVICE_ARCH))
	ARCH = arm-none-eabi-
	MMCU = 
else
  ifeq (avr,$(DEVICE_ARCH))
	ARCH = avr-
	MMCU = -mmcu=$(DEVICE)
  endif
endif


#  Toolchain commands
#
CPP		:= $(ARCH)cpp
CC		:= $(ARCH)gcc
AS		:= $(ARCH)as
OBJCOPY		:= $(ARCH)objcopy
ODUMP		:= $(ARCH)objdump
GDB		:= $(ARCH)gdb
SIZE		:= $(ARCH)size


################################################################################
#									       #
#			Preprocessing					       #
#									       #
################################################################################

#  It is sometimes useful to just preprocess the source file to determine what
#  went wrong with the HWA macros. Use the -B option to force make rebuild the
#  target.
#
%.cp.c: %.c
#	@echo "RULE $@: $^"
#	@echo "$(CPP) $(CFLAGS) $< >$@"
	@$(CPP) $(CFLAGS) $< >$@
#	$(CPP) $(CFLAGS) $< |sed -e 's/;/;\n/g'|bcpp -s -i 2 -bcl | sed -e 's/#/\/\//g' > $@

#  .sx files must first be preprocessed in order to catch HWA error messages and
#  format them for a correct display
#
AFLAGS		+= $(MMCU)
AFLAGS		+= -Wall
AFLAGS		+= -fno-diagnostics-show-caret	# GCC 4.8
#AFLAGS		+= -Wextra
AFLAGS		+= $(DEFINES)
AFLAGS		+= $(INCLUDES)

$(OUTDIR)/%.cp.sx %.cp.sx: %.sx
	@echo "RULE $@: $^"
	$(CPP) $(AFLAGS) $< >$@


################################################################################
#									       #
#			Compiling					       #
#									       #
################################################################################

#  Compiling options
#
CFLAGS		+= $(MMCU)
CFLAGS		+= -std=c1x
CFLAGS		+= -Wall
CFLAGS		+= -Wextra
CFLAGS		+= -Wpedantic	# GCC 4.8
CFLAGS		+= -fno-diagnostics-show-caret	# GCC 4.8
CFLAGS		+= -ftrack-macro-expansion=0 # -Wno-misleading-indentation unrecognized
#CFLAGS		+= -fdata-sections
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
	@$(CC) $(CFLAGS) -c $< -o $@


################################################################################
#									       #
#			Linking						       #
#									       #
################################################################################

#  Object files list (from source files list)
#
OBJECTS		:= $(SOURCES:.c=.o)
OBJECTS		:= $(OBJECTS:.sx=.o)
OBJECTS		:= $(addprefix $(OUTDIR)/,$(OBJECTS))

LDFLAGS		+= $(MMCU)
LDFLAGS		+= -Wl,-Map,$(OUT).map,--cref
LDFLAGS		+= -Wl,--gc-sections

#  Use a special linker script in the source directory, based on the DEVICE used.
#    ATmega328:     avr5.ld
#    ATtinyX4 / X5: avr25.ld
#
# ifneq (,$(LOCALLD))
#   LDFLAGS	+= -Tavr$(shell echo __AVR_ARCH__ | avr-cpp $(MMCU) | tail -1).ld
# endif


$(OUT).elf: $(OBJECTS) $(LDSCRIPT)
#	@echo "RULE: $@ : $^"
	@$(CC) $(LDFLAGS) -o $@ $(OBJECTS) $(LIBS)


################################################################################
#									       #
#			Post-linking					       #
#									       #
################################################################################

bin:	$(OUT).lst $(OUT).bin
lst:	$(OUT).lst

#  Note: must specify the section otherwise gap-fill includes the .data section (-> 8 MB!)
#
%.bin: %.elf
	@$(OBJCOPY) --gap-fill=0xFF --pad-to $(DEVICE_FLASH_SIZE) 		\
		--only-section .text --only-section .bss --only-section .data	\
		-O binary $^ $@

#  Object dump flags:
#
#  -d: disassembly
#  -S: disassembly + source code
#  -h: section headers
#  --no-show-raw-insn: no machine code
#
%.lst: %.elf
	$(ODUMP) -d $^ >$@

#  Size of the generated binary
#
.PHONY: size
size:	$(OUT).elf
	@$(SIZE) $^

#  Diabolo's CRC of the generated binary
#
.PHONY: stat
stat:	$(OUT).bin
	@if [ ! -f "$(diabolo)" ] ; then					\
	  echo "Diabolo is required for make target 'stat'." ;			\
	elif python3 -V >/dev/null 2>&1 ; then					\
	  $(diabolo) --mcu=$(DEVICE) --stat $(OUT).bin -q			;\
	else									\
	  echo "Install Python if you want Diabolo to stat your application."	;\
	fi

################################################################################
#									       #
#			Misc						       #
#									       #
################################################################################


#  Remove built files under the working directory
#
.PHONY: clean
clean:
	@find . -name 'build' -prune -exec rm -rf {} ';'
	@find . '(' 					\
		-name '*~' 				\
		-o -name '*.cp.*'			\
		')' -exec rm {} ';'
