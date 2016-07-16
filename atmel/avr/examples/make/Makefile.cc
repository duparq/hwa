
#	-*- Makefile -*-

#  This Makefile is responsible for building the example projects. It needs a
#  board name to be defined with a corresponding board definition header file
#  that defines the target device.

#$(warning INCLUDE)

#  MFD contains the directory name of this Makefile whatever has been included
#
MFD	:=	$(dir $(lastword $(MAKEFILE_LIST)))

#$(info Loaded $(MFD)Makefile.cc)

#	Choose a default board if none specified
#
ifeq (,$(BOARD))
  BOARD		:=	attiny84
  $(info Selected default board 'attiny84')
endif

#	Load board's Makefile if it exists
#
#$(warning include $(MFD)../boards/Makefile.$(BOARD))
-include $(MFD)../boards/Makefile.$(BOARD)

#	Output directory and files basename
#
OUTDIR		= build/$(BOARD)
OUT		= $(OUTDIR)/out

#  Directory of boards
#
BOARDS		= $(MFD)../boards

#  Diabolo is the preferred bootloader
#
diabolo		= $(MFD)../diabolo/software/diabolo.py

#  BOARD_H indicates the board definition header file the example project source
#  must use
#
DEFINES		+= -DBOARD_H=\<boards/$(BOARD).h\>

#  Directories searched for include files:
#   * ~hwa/include/
#   * ~hwa/atmel/avr/examples/
#
INCLUDES	= -I$(MFD)../../../../include 
INCLUDES	+= -I$(MFD)..

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
$(BOARDS)/build/$(BOARD).c:
#	@echo "RULE: $@"
	@mkdir -p $(BOARDS)/build
	@echo "DEVICE=HW_DEVICE" >$@
	@echo "DEVICE_FLASH_SIZE=HW_DEVICE_FLASH_SIZE" >>$@
	@echo "DEVICE_FUSE_EB=HW_QUOTE(HW_DEVICE_FUSE_EB)" >>$@
	@echo "DEVICE_FUSE_HB=HW_QUOTE(HW_DEVICE_FUSE_HB)" >>$@
	@echo "DEVICE_FUSE_LB=HW_QUOTE(HW_DEVICE_FUSE_LB)" >>$@
	@echo "DEVICE_SYSHZ=hw_syshz" >>$@

#  Load informations about the target device
#
#  Let CPP process board.c using the definitions found in the board's header
#  file. __ASSEMBLER__ is defined so that HWA will not load the definitions that
#  produce C code and that are useless for what we want to do.
#
$(BOARDS)/build/$(BOARD): $(BOARDS)/build/$(BOARD).c $(BOARDS)/$(BOARD).h
#	@echo "RULE: $@ : $^"
	@avr-cpp -I$(MFD)../../../../include					\
		-D__ASSEMBLER__							\
		-imacros $(BOARDS)/$(BOARD).h $(BOARDS)/build/$(BOARD).c | grep '^DEVICE' >$@

#  Include informations about the target device, borrowed from the board header
#  file
#
#$(warning include $(BOARDS)/build/$(BOARD))
-include $(BOARDS)/build/$(BOARD)


################################################################################
#									       #
#			Dependencies					       #
#									       #
################################################################################

.PHONY: all
all:	deps bin lst size stat

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

AFLAGS		+= -mmcu=$(DEVICE)
AFLAGS		+= -Wall
AFLAGS		+= -fno-diagnostics-show-caret	# GCC 4.8
#AFLAGS		+= -Wextra
AFLAGS		+= $(DEFINES)
AFLAGS		+= $(INCLUDES)

#.PHONY: force
force: ;
#	@echo "RULE: $@: $^"

#  It is sometimes useful to just preprocess the source file to determine what
#  went wrong with the HWA macros
#
%.cp.c: %.c
#	@echo "RULE $@: $^"
	@$(CPP) $(CFLAGS) $< >$@
#	$(CPP) $(CFLAGS) $< |sed -e 's/;/;\n/g'|bcpp -s -i 2 -bcl | sed -e 's/#/\/\//g' > $@

#  .sx files must first be preprocessed in order to catch HWA error messages and
#  format them for a correct display
#
$(OUTDIR)/%.cp.sx %.cp.sx: %.sx
#	@echo "RULE $@: $^"
	@$(CPP) $(AFLAGS) $< >$@

foo:
	@awk 'BEGIN { result=0; }{						\
	  x=match($$0,/hw_error\((.*),(.*),(.*)\)/,gr) ;			\
	  if (x != 0) {								\
	    result=1;								\
	    command="cd "gr[1]"; pwd ; basename "gr[1] ;			\
	    command|getline fpath ;						\
	    printf "%s:%s:error: %s\n",fpath,gr[2],gensub(/" *"/,"","g",gr[3])	\
	  }									\
	} END { exit result; }' $@


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

#  Object files list (from source files list)
#
#OBJECTS		 = $(SOURCES:.c=.$(DEVICE).o)
#OBJECTS		:= $(OBJECTS:.sx=.$(DEVICE).o)
OBJECTS		 = $(SOURCES:.c=.o)
OBJECTS		:= $(OBJECTS:.sx=.o)
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

#  PADTO is used to fill unused flash memory space with 0xFF bytes
#
ifneq (,$(DEVICE_FLASH_SIZE))
#  $(info PADTO=$(DEVICE_FLASH_SIZE))
  PADTO = --pad-to $(DEVICE_FLASH_SIZE)
else
  PADTO =
endif

%.bin: %.elf
	@$(OBJCOPY) -O binary $^ $@

# @$(OBJCOPY) --only-section .text --only-section .data	\
# 	-O binary --gap-fill=0xFF $(PADTO) $^ $@

%.hex: %.elf
	@$(OBJCOPY) --only-section .text --only-section .data	\
		-O ihex --gap-fill=0xFF $^ $@

#  Object dump flags:
#
#  -d: disassembly
#  -S: disassembly + source code
#  -h: section headers
#  --no-show-raw-insn: no machine code
#
%.lst: %.elf
#	@$(ODUMP) -S $^ >$@
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
	@if python -V >/dev/null 2>&1 ; then					\
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
#
$(OUT).cfg.c: $(SOURCES)
#	@echo "RULE: $@: $^  CONFIG=$(CONFIG)"
	@set -e						;\
	if [ -z "$(CONFIG)" ] ; then			\
	  echo FAIL: no config				;\
	  exit 1					;\
	fi						;\
	echo "#define HW_Q(...) HW_Q2(__VA_ARGS__)" >$@	;\
	echo "#define HW_Q2(...) #__VA_ARGS__" >>$@	;\
	for c in $(CONFIG)				;\
	  do echo "_$$c=HW_Q($$c)" >>$@			;\
	done

#  Create a file that describes the configuration of the project. Assume the
#  configuration is included in the first source file.
#
$(OUT).cfg: $(OUT).cfg.c
	@$(CPP) $(INCLUDES) $(DEFINES) -imacros $(firstword $(SOURCES)) \
		$< | grep '^_.*' | sed -e 's/_//' >$@


#  Create a file that contains the compiler name and version
#
.PHONY: rem$(OUT).ccversion
rem$(OUT).ccversion:
#	@echo "RULE: $@: $^"
	@$(CC) --version | awk 'NR==1 {x=match($$3,/([0-9]+)\.([0-9]+)\.([0-9]+)/,m);\
				if(x!=0){print "$(CC)-"m[1]m[2]m[3]}}' >$@


#  Validate a project: store the configuration and the disassembly output in a
#  file named .valid+device+CRC32+size+CRC
#
.PHONY: validate
validate: $(OUT).cfg $(OUT).bin #$(OUT).ccversion
#	@echo RULE: $@: $^
	@if python -V >/dev/null 2>&1 ; then						\
	  set -e									;\
	  S_CRC=$$($(diabolo) --crc32 $(OUT).cfg | awk '{print $1}' )			;\
	  O_CRC=$$($(diabolo) -q -m $(DEVICE) --crc $(OUT).bin)				;\
	  O_SIZE=$$($(diabolo) -q -m $(DEVICE) --size $(OUT).bin)			;\
	  CCVERSION=$$($(CC) --version	\
	   | awk 'NR==1 {x=match($$3,/([0-9]+)\.([0-9]+)\.([0-9]+)/,m);	\
	          if(x!=0){print "$(CC)-"m[1]m[2]m[3]}}')				;\
	  rm -f .valid-$${CCVERSION}-$(DEVICE)-$$S_CRC-*				;\
	  cp $(OUT).cfg .valid-$${CCVERSION}-$(DEVICE)-$$S_CRC-$$O_SIZE-$$O_CRC			;\
	  $(ODUMP) -d $(OUT).elf >>.valid-$${CCVERSION}-$(DEVICE)-$$S_CRC-$$O_SIZE-$$O_CRC	;\
	  echo Validation: .valid-$${CCVERSION}-$(DEVICE)-$$S_CRC-$$O_SIZE-$$O_CRC	;\
	else										\
	  echo "Python is required to validate the application."			;\
	fi

#	  CCVERSION=$$(cat $(OUT).ccversion)						;\

.PHONY: ccversion
ccversion:
	@CCVERSION=$$($(CC) --version	\
	 | awk 'NR==1 {x=match($$3,/([0-9]+)\.([0-9]+)\.([0-9]+)/,m);	\
	        if(x!=0){print "$(CC)-"m[1]m[2]m[3]}}')				;\
	echo CCVERSION=$$CCVERSION


#  Check that the CRC is still the same for a given configuration
#
.PHONY: check
check: $(OUT).cfg $(OUT).bin #$(OUT).ccversion
#	@echo "RULE: $@: $^"
	@OUT=$(OUT) bash $(MFD)check.sh


#  Disassemble binary output file
#
.PHONY: disassemble
disassemble:
	@avr-objdump -m avr:5 -b binary -D $(OUT).bin


#  Show device fuse values
#
.PHONY: show-fuses
show-fuses: $(INC_HWA)
#	@echo "RULE: $@: $^"
	@printf "FUSE_EB=0x%02X  FUSE_HB=0x%02X  FUSE_LB=0x%02X\n" \
		$$(($$(echo $(DEVICE_FUSE_EB)))) \
		$$(($$(echo $(DEVICE_FUSE_HB)))) \
		$$(($$(echo $(DEVICE_FUSE_LB))))


################################################################################
#									       #
#			Device programming				       #
#									       #
################################################################################

#  This target automatically takes the name of the target that was not found.
#  Load the Makefile for programming targets.
#
ifeq (,$(PROG_SW))
PROG_SW		= diabolo
endif

# export diabolo

#.DEFAULT:
#	@echo ".DEFAULT: $@"
#	$(MAKE) -f $(MFD)Makefile.$(PROG_SW) --no-print-directory $@

ifneq (,$(filter $(MAKECMDGOALS), install diabolo erase decode-fuses reset))
#  $(info Loading $(MFD)Makefile.$(PROG_SW))
  include $(MFD)Makefile.$(PROG_SW)
endif
