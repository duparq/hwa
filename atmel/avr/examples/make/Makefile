
#  This Makefile is responsible for building the example projects. It needs a
#  board name to be defined and a corresponding board definition header file
#  that defines the target device.


#  MFD contains the directory name of this Makefile whatever has been included
#
MFD		:=	$(dir $(lastword $(MAKEFILE_LIST)))

#  Default target
#
.PHONY: all
all:	deps bin lst size stat


#  Produce HTML documentation
#
.PHONY: doc
doc:
	@cd $(MFD)../../../../doxygen && $(MAKE) --no-print-directory


#  Directory of boards
#
BOARDS		:= $(MFD)../../../../include/hwa/boards
BOARDSBUILD	:= $(MFD)../build

#  Choose a default board if none specified
#
ifeq (,$(BOARD))
  BOARD		:=	attiny84
  $(info Selected default board '$(BOARD)')
endif

#  Load board's Makefile if it exists
#
-include $(BOARDS)/Makefile.$(BOARD)

#  Output directory and files basename
#
OUTDIR		:= build/$(BOARD)
OUT		:= $(OUTDIR)/out

#  Diabolo is the preferred bootloader
#
diabolo		:= $(MFD)../diabolo/software/diabolo.py

#  BOARD_H indicates the board definition header file the example project source
#  must use
#
DEFINES		+= -DBOARD_H=\<hwa/boards/$(BOARD).h\>

#  Search include files in ~hwa/include/
#
INCLUDES	:= -I$(MFD)../../../../include 

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


#  Basic flags (evaluation of DEVICE must be delayed)
#
MMCU		+= -mmcu=$(DEVICE)

#  Variables used by external scripts
#
export LANG
export BOARD
export DEVICE
export OUTDIR
export OUT


################################################################################
#									       #
#			Board configuration				       #
#									       #
################################################################################

#  Create a C source file that collects HWA definitions relative to the
#  configuration of the target device
#
#	Quoting with HW_QUOTE is required for make not to show an error message
#	when it reads complex values.
#
$(BOARDSBUILD)/$(BOARD).c:
#	@echo "RULE: $@"
	@mkdir -p $(BOARDSBUILD)
	@echo "DEVICE=HW_DEVICE" >$@
	@echo "DEVICE_FLASH_SIZE=HW_DEVICE_FLASH_SIZE" >>$@
	@echo "DEVICE_FUSE_EB=HW_QUOTE(HW_DEVICE_FUSE_EB)" >>$@
	@echo "DEVICE_FUSE_HB=HW_QUOTE(HW_DEVICE_FUSE_HB)" >>$@
	@echo "DEVICE_FUSE_LB=HW_QUOTE(HW_DEVICE_FUSE_LB)" >>$@
	@echo "DEVICE_SYSHZ=HW_SYSHZ" >>$@

#  Load informations about the target device
#
#  Let CPP process board.c using the definitions found in the board's header
#  file. __ASSEMBLER__ is defined so that HWA will not load the definitions that
#  produce C code and that are useless for what we want to do.
#
$(BOARDSBUILD)/$(BOARD): $(BOARDSBUILD)/$(BOARD).c $(BOARDS)/$(BOARD).h
#	@echo "RULE: $@ : $^"
	@avr-cpp -I$(MFD)../../../../include					\
		-D__ASSEMBLER__							\
		-imacros $(BOARDS)/$(BOARD).h $(BOARDSBUILD)/$(BOARD).c | grep '^DEVICE' >$@

#  Include informations about the target device, borrowed from the board header
#  file
#
#$(warning include $(BOARDSBUILD)/$(BOARD))
-include $(BOARDSBUILD)/$(BOARD)


################################################################################
#									       #
#			Dependencies					       #
#									       #
################################################################################

.PHONY: deps
deps:	$(DEPS)

#  List of dependency files
#  One dependency file is generated for each .c or .sx source file
#
DEPS	:= $(SOURCES:.c=.d)
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
	@set -e ; rm -f $@ ; $(CPP) -MM $(MMCU) $(INCLUDES) $(DEFINES) $< >$@.tmp	;\
	sed 's,\($*\)\.o[ :]*,$(OUTDIR)/\1.o $@ : ,g' < $@.tmp > $@

#	Dependencies of .sx files
#
$(OUTDIR)/%.d: %.sx
#	@echo "RULE: $@: $^"
	@mkdir -p $(OUTDIR)
	@set -e ; rm -f $@ ; $(CC) -MM $(INCLUDES) $(DEFINES) $< > $@.tmp	;\
	sed 's,\($*\)\.o[ :]*,$(OUTDIR)/\1.o $@ : ,g' < $@.tmp > $@


################################################################################
#									       #
#			Preprocessing					       #
#									       #
################################################################################

AFLAGS		+= $(MMCU)
AFLAGS		+= -Wall
AFLAGS		+= -fno-diagnostics-show-caret	# GCC 4.8
#AFLAGS		+= -Wextra
AFLAGS		+= $(DEFINES)
AFLAGS		+= $(INCLUDES)

#  It is sometimes useful to just preprocess the source file to determine what
#  went wrong with the HWA macros. Use the -B option to force make rebuild the
#  target.
#
%.cp.c: %.c
#	@echo "RULE $@: $^"
	@echo "$(CPP) $(CFLAGS) $< >$@"
	@$(CPP) $(CFLAGS) $< >$@
#	$(CPP) $(CFLAGS) $< |sed -e 's/;/;\n/g'|bcpp -s -i 2 -bcl | sed -e 's/#/\/\//g' > $@

#  .sx files must first be preprocessed in order to catch HWA error messages and
#  format them for a correct display
#
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
#CFLAGS		+= -pedantic
CFLAGS		+= -Wpedantic	# GCC 4.8
CFLAGS		+= -fno-diagnostics-show-caret	# GCC 4.8
CFLAGS		+= -ftrack-macro-expansion=0 # -Wno-misleading-indentation unrecognized
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

#  We want .sx files to be preprocessed first
#
$(OUTDIR)/%.o: $(OUTDIR)/%.cp.sx
#	@echo "RULE: $@ : $^"
	@mkdir -p $(OUTDIR)
	$(CC) $(AFLAGS) -c $< -o $@


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
#LDFLAGS		+= -Wl,--section-start=.flash=.etext

#  Use a special linker script in the source directory, based on the DEVICE used.
#    ATmega328:     avr5.ld
#    ATtinyX4 / X5: avr25.ld
#
ifneq (,$(LOCALLD))
  LDFLAGS	+= -Tavr$(shell echo __AVR_ARCH__ | avr-cpp $(MMCU) | tail -1).ld
endif


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
	@$(ODUMP) -d $^ >$@

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

#  Display _swuarta performances
#
swuart-perfs: $(OUT).elf
	@get() { echo 0x$$(avr-nm $< | grep " a $$1\$$" | cut -d' ' -f1); } ;\
	CY_ST=$$(get CY_ST)								;\
	CY_ST_SEI=$$(get CY_ST_SEI)							;\
	CY_RX_SEI=$$(get CY_RX_SEI)							;\
	CY_RX_DB=$$(get CY_RX_DB)							;\
	CY_RX_LDB=$$(get CY_RX_LDB)							;\
	CY_RX_SB=$$(get CY_RX_SB)							;\
	CY_TX_SEI=$$(get CY_TX_SEI)							;\
	CY_TX_DB=$$(get CY_TX_DB)							;\
	CY_TX_LDB=$$(get CY_TX_LDB)							;\
	CY_TX_SB=$$(get CY_TX_SB)							;\
	CY_SYNC0=$$(get CY_SYNC0)							;\
	CY_SYNC2=$$(get CY_SYNC2)							;\
	echo "Start condition: $$(( $$CY_ST )) cycles (interrupts disabled for $$(( $$CY_ST_SEI )) cycles)"			;\
	echo "Reception of data bit: $$(( $$CY_RX_DB )) cycles (interrupts disabled for $$(( $$CY_RX_SEI )) cycles)"				;\
	echo "Reception of last data bit: $$(( $$CY_RX_LDB )) cycles"			;\
	echo "Reception of stop bit: $$(( $$CY_RX_SB )) cycles"				;\
	echo "Transmission of data bit: $$(( $$CY_TX_DB )) cycles (interrupts disabled for $$(( $$CY_TX_SEI )) cycles)"			;\
	echo "Transmission of last data bit: $$(( $$CY_TX_LDB )) cycles"		;\
	echo "Transmission of stop bit: $$(( $$CY_TX_SB )) cycles"			;\
	echo "Synchronization falling edge to counting loop: $$(( $$CY_SYNC0 )) cycles"	;\
	echo "Synchronization limit exceeded: $$(( $$CY_SYNC2 )) cycles"


################################################################################
#									       #
#			Project validation				       #
#									       #
################################################################################

#  Store application parameters that will be used later to verify that the CRC
#  remains the same for a given configuration. This helps detecting variations
#  in code production after the HWA core has been modified.

#  Create a C source file that holds the configuration of a project.
#  Prefix symbols with a '_' that will be removed after compiling.
#  The CONFIG variable is exported by the project's Makefile.
#
$(OUT).cfg.c: $(SOURCES)
#	@echo "RULE: $@: $^  CONFIG=$(CONFIG)"
	@set -e						;\
	if [ -z "$(CONFIG)" ] ; then			\
	  echo FAIL: no config				;\
	  exit 1					;\
	fi						;\
	for c in $(CONFIG)				;\
	  do echo "_$$c=HW_Q($$c)" >>$@			;\
	done


#  Create a file that describes the configuration of the project. Assume the
#  configuration is included in the first source file.
#
$(OUT).cfg: $(OUT).cfg.c
	@$(CPP) $(INCLUDES) $(DEFINES) -imacros $(firstword $(SOURCES)) \
		$< | grep '^_.*' | sed -e 's/_//' >$@


#  Validate a project: store the configuration and the disassembly output in a
#  file named .valid+device+CRC32+size+CRC
#
.PHONY: validate
validate: $(OUT).cfg $(OUT).bin #$(OUT).ccversion
#	@echo RULE: $@: $^
	@if python3 -V >/dev/null 2>&1 ; then						\
	  set -e									;\
	  S_CRC=$$($(diabolo) --crc32 $(OUT).cfg | awk '{print $1}' )			;\
	  O_CRC=$$($(diabolo) -q -m $(DEVICE) --crc $(OUT).bin)				;\
	  O_SIZE=$$($(diabolo) -q -m $(DEVICE) --size $(OUT).bin)			;\
	  CCVERSION=$(CC)-$$($(CC) -dumpversion | sed -e 's/\.//g')			;\
	  rm -f .valid-$${CCVERSION}-$(DEVICE)-$${S_CRC}-*				;\
	  VALID=.valid-$${CCVERSION}-$(DEVICE)-$${S_CRC}-$${O_SIZE}-$${O_CRC}		;\
	  cp $(OUT).cfg $${VALID}							;\
	  $(ODUMP) -d $(OUT).elf | tail +6 >> $${VALID}					;\
	  echo Validation: $${VALID}							;\
	else										\
	  echo "Python is required to validate the application."			;\
	fi


#  Check that the CRC is still the same for a given configuration
#
.PHONY: check
check: $(OUT).cfg $(OUT).bin
#	@echo "RULE: $@: $^"
	@OUT=$(OUT) bash $(MFD)check.sh


################################################################################
#									       #
#			Device programming				       #
#									       #
################################################################################


#  Show device fuse values
#
.PHONY: print-fuses
print-fuses: $(INC_HWA)
#	@echo "RULE: $@: $^"
	@printf "FUSE_EB=0x%02X  FUSE_HB=0x%02X  FUSE_LB=0x%02X\n" \
		$$(($$(echo $(DEVICE_FUSE_EB)))) \
		$$(($$(echo $(DEVICE_FUSE_HB)))) \
		$$(($$(echo $(DEVICE_FUSE_LB))))


ifneq (,$(filter $(MAKECMDGOALS), install diabolo erase decode-fuses reset read-fuses read-flash))
  ifeq (,$(PROG_SW))
    PROG_SW = diabolo
  endif
  include $(MFD)Makefile.$(PROG_SW)
endif


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
		-o -name '*.hwa.c'			\
		-o -name '*.pyc'			\
		')' -exec rm {} ';'
