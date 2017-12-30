
#  This Makefile is responsible for building the example projects. It needs a
#  board name to be defined and a corresponding board definition header file
#  that defines the target device.


#  MFD contains the directory name of this Makefile whatever has been included
#
MFD		:=	$(dir $(lastword $(MAKEFILE_LIST)))

#  Default target
#
.PHONY: all
#all:	deps bin lst size crc32
all:	deps lst size

#  Directory of boards
#
BOARDS		:= $(MFD)../boards

#  Choose a default board if none specified
#
ifeq (,$(BOARD))
  BOARD		:=	$(shell cat $(BOARDS)/default)
  $(info Selected default board '$(BOARD)')
endif

#  Load board's Makefile if it exists
#
-include $(BOARDS)/Makefile.$(BOARD)

#  Paths
#
SDK		?= $(HOME)/dev/esp8266/esp-open-sdk
SDKBIN		:= $(SDK)/xtensa-lx106-elf/bin
IOT_SDK		?= $(SDK)/sdk
IOT_SDK_LIBDIR	?= $(IOT_SDK)/lib
PATH		:= $(SDKBIN):$(PATH)

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
DEFINES		+= -DBOARD_H=\"../boards/$(BOARD).h\"

#  Search include files in ~hwa/include/
#
INCLUDES	:= -I$(MFD)../../../../include 

#  Directories searched for include files:
#
INCLUDES	+= -I.				# for SDK to find user_config.h
INCLUDES	+= -I$(IOT_SDK)/include

#  Messages in english
#
LANG		:= C

#  Toolchain commands
#
ARCH		:= xtensa-lx106-elf-
CPP		:= $(ARCH)cpp
CC		:= $(ARCH)gcc
AR		:= $(ARCH)ar
AS		:= $(ARCH)as
OC		:= $(ARCH)objcopy
OD		:= $(ARCH)objdump
GDB		:= $(ARCH)gdb
SIZE		:= $(ARCH)size

PP		:= $(ARCH)gcc -E
LD		:= $(ARCH)gcc
AR		:= $(ARCH)ar
AS		:= $(ARCH)as
OC		:= $(ARCH)objcopy
OD		:= $(ARCH)objdump

#  Basic flags (evaluation of DEVICE must be delayed)
#
FLAGS		= -mcpu=cortex-m3 -mthumb 

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

#  Load informations about the target device
#
#  Let CPP process board.c using the definitions found in the board's header
#  file. __ASSEMBLER__ is defined so that HWA will not load the definitions that
#  produce C code and that are useless for what we want to do.
#
$(BOARDS)/build/$(BOARD): $(BOARDS)/build/$(BOARD).c $(BOARDS)/$(BOARD).h
#	@echo "RULE: $@ : $^"
#	@avr-cpp -I$(MFD)../../../../include					
	@avr-cpp $(INCLUDES)					\
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

AFLAGS		+= $(FLAGS)
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
#	@echo "RULE $@: $^"
	@$(CPP) $(AFLAGS) $< >$@


################################################################################
#									       #
#			Compiling					       #
#									       #
################################################################################

#  Compiling options
#
CFLAGS		+= -std=c1x
CFLAGS		+= -Wall
CFLAGS		+= -Wextra
CFLAGS		+= -Wpointer-arith
CFLAGS		+= -Werror
CFLAGS		+= -Wl,-EL
CFLAGS		+= -fno-inline-functions
CFLAGS		+= -nostdlib
CFLAGS		+= -mlongcalls
CFLAGS		+= -mtext-section-literals
CFLAGS		+= -D__ets__
CFLAGS		+= -DICACHE_FLASH
CFLAGS		+= -fno-diagnostics-show-caret	# GCC 4.8
CFLAGS		+= -ftrack-macro-expansion=0
CFLAGS		+= -ffunction-sections
CFLAGS		+= -fpack-struct
#CFLAGS		+= -g
CFLAGS		+= -Os
CFLAGS		+= -O2
CFLAGS		+= $(DEFINES)
CFLAGS		+= $(INCLUDES)


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
OBJECTS		:= $(SOURCES:.c=.o)
OBJECTS		:= $(OBJECTS:.sx=.o)
OBJECTS		:= $(addprefix $(OUTDIR)/,$(OBJECTS))

LDFLAGS		+= -nostdlib
#LDFLAGS		+= -Wl,--no-check-sections
#LDFLAGS		+= -u call_user_start
#LDFLAGS		+= -Wl,-static

#	Libraries used in this project, mainly provided by the IOT_SDK
#
LIBS		+= -Wl,--start-group
LIBS		+= -lc
# LIBS		+= -lhal
LIBS		+= -lpp
LIBS		+= -lphy
LIBS		+= -lnet80211
LIBS		+= -llwip
LIBS		+= -lwpa
LIBS		+= -lmain
LIBS		+= -Wl,--end-group
LIBS		+= -lgcc

#	Linker script
#
LD_SCRIPT	?= eagle.app.v6.ld

$(OUT).elf: $(OBJECTS)
#	@echo "RULE: $@ : $^"
	$(LD) -T$(LD_SCRIPT) $(LDFLAGS) $(LIBS) -o $@ $<


################################################################################
#									       #
#			Post-linking					       #
#									       #
################################################################################

bin:	$(OUT).0x00000.bin $(OUT).0x10000.bin
lst:	$(OUT).lst

$(OUT).0x00000.bin $(OUT).0x10000.bin: $(OUT).elf
#	@echo "RULE: $@ : $^"
	@esptool.py elf2image $< -o $(OUT).

#  Object dump flags:
#
#  -d: disassembly
#  -S: disassembly + source code
#  -h: section headers
#  --no-show-raw-insn: no machine code
#
%.lst: %.elf
	@$(OD) -d $^ >$@

#  Size of the generated binary
#
.PHONY: size
size:	$(OUT).elf
	@$(SIZE) $^

.PHONY: crc32
crc32:	$(OUT).bin
	@echo -n "CRC32: " ; crc32 $^


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
	  $(OD) -d $(OUT).elf >>.valid-$${CCVERSION}-$(DEVICE)-$$S_CRC-$$O_SIZE-$$O_CRC	;\
	  echo Validation: .valid-$${CCVERSION}-$(DEVICE)-$$S_CRC-$$O_SIZE-$$O_CRC	;\
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

.PHONY: flashinit
flashinit:
	cd $(IOT_SDK) ; $(SDKBIN)/esptool.py		\
		write_flash				\
		-ff 40m					\
		-fm dout				\
		-fs 32m					\
		0x3e000 bin/blank.bin			\
		0x3fc000 bin/esp_init_data_default.bin	\
		0x3fe000 bin/blank.bin

install: $(OUT).0x00000.bin $(OUT).0x10000.bin
#	@echo "RULE: $@ : $^"
	@ARGS=""	;\
	X=0x00000	;\
	if ! test -f /tmp/$$X.bin || ! diff -q $(OUT).$$X.bin /tmp/$$X.bin >/dev/null ; then \
	  ARGS="$$ARGS $$X $(OUT).$$X.bin"	;\
	fi					;\
	X=0x10000	;\
	if ! test -f /tmp/$$X.bin || ! diff -q $(OUT).$$X.bin /tmp/$$X.bin >/dev/null ; then \
	  ARGS="$$ARGS $$X $(OUT).$$X.bin"	;\
	fi					;\
	if test -n "$$ARGS" ; then				\
	  esptool.py --baud 460800 write_flash			\
		--flash_freq 40m				\
		--flash_mode dout				\
		--flash_size 32m				\
		$$ARGS		\
	  && (cp -a $(OUT).0x00000.bin /tmp/0x00000.bin		;\
	      cp -a $(OUT).0x10000.bin /tmp/0x10000.bin)	;\
	else							\
	  echo Nothing new to be programmed			;\
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
		-o -name '*.hwa.c'			\
		-o -name '*.pyc'			\
		')' -exec rm {} ';'
