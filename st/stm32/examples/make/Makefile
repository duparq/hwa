
ifneq ($(BOARD),)
ifeq ($(SOURCES),)
  $(error SOURCES is not defined)
endif

def_all:
	@$(error No default goal!)


#HWA		=	$(HOME)/dev/hwa
HWA		=	$(abspath ../../../..)
BOARDS		=	$(HWA)/include/hwa/boards

#  Target board must be defined
#
ifeq ($(BOARD),)
  $(error BOARD is not defined)
endif

#  The board's Makefile contains required definitions
#
ifeq ($(wildcard $(BOARDS)/Makefile.$(BOARD)),)
  $(error $(BOARDS)/Makefile.$(BOARD) is not a file)
endif

include $(BOARDS)/Makefile.$(BOARD)

#  Check required definitions
#
ifeq ($(CPU),cortex-m3)
  ARCH	= arm-none-eabi-
  MMCU	= -mcpu=cortex-m3 -mthumb
  PROGSW = openocd
endif

ifeq ($(CPU),cortex-m4)
  ARCH	= arm-none-eabi-
  MMCU	= -mcpu=cortex-m4 -mthumb
  PROGSW = openocd
endif

ifeq ($(ARCH),)
  $(error Could not determine ARCH)
endif

ifneq ($(CRT0),)
  SOURCES	+= $(HWA)/$(CRT0)
endif

ifeq ($(RAMSIZE),)
  $(error RAMSIZE is not defined)
endif

#  Output directory and files basename
#
OUTDIR		:= build/$(BOARD)
OUT		:= $(OUTDIR)/out

DEFINES		+= -DBOARD_H=\<$(BOARD).h\>
DEFINES		+= -DRAMSIZE=$(RAMSIZE)

#  Search include files in ~hwa/include/
#
INCLUDES	+= -I.
INCLUDES	+= -I$(HWA)/include
INCLUDES	+= -I$(BOARDS)

#  Messages in english
#
LANG		:= C

#  Objects
#    Convert sources to absolute paths
#    Put objects and dependencies in directories under OUTDIR
#    Put results under OUTDIR
#
SOURCES		:= $(abspath $(SOURCES))
# CSOURCES	:= $(addprefix $(OUTDIR),$(filter %.c,$(SOURCES)))
# COBJECTS	:= $(CSOURCES:.c=.o)
# SSOURCES	:= $(addprefix $(OUTDIR),$(filter %.s,$(SOURCES)))
# SOBJECTS	:= $(SSOURCES:.s=.o)
# SXSOURCES	:= $(addprefix $(OUTDIR),$(filter %.sx,$(SOURCES)))
# SXOBJECTS	:= $(SXOURCES:.sx=.o)
# OBJECTS		:= $(COBJECTS) $(SOBJECTS) $(SXOBJECTS)
OBJECTS		:= $(addprefix $(OUTDIR),$(SOURCES:.c=.o))
DEPS		:= $(OBJECTS:.o=.d)

# $(info OUTDIR=$(OUTDIR))
# $(info SOURCES=$(SOURCES))
# $(info OBJECTS=$(OBJECTS))
# $(info DEPS=$(DEPS))
# $(info COBJECTS=$(COBJECTS))
# $(info SOBJECTS=$(SOBJECTS))
# $(info SXOBJECTS=$(SXOBJECTS))
# $(info DEFINES=$(DEFINES))
# $(info INCLUDES=$(INCLUDES))

-include $(DEPS)


#  Targets
#
.PHONY: all bin elf lst size crc32 stat

elf:	$(OUT).elf
bin:	$(OUT).bin
lst:	$(OUT).lst

#  Toolchain commands
#
CPP		:= $(ARCH)cpp
CC		:= $(ARCH)gcc
AS		:= $(ARCH)as
OBJCOPY		:= $(ARCH)objcopy
ODUMP		:= $(ARCH)objdump
SIZE		:= $(ARCH)size
GDB		:= gdb-multiarch

#  Flags
#
AFLAGS		+= $(MMCU)
AFLAGS		+= -Wall
AFLAGS		+= -fno-diagnostics-show-caret
AFLAGS		+= -Wextra
AFLAGS		+= $(DEFINES)
AFLAGS		+= $(INCLUDES)

CFLAGS		+= $(MMCU)
CFLAGS		+= $(DEFINES)
CFLAGS		+= $(INCLUDES)
CFLAGS		+= -std=c1x
CFLAGS		+= -Wall
CFLAGS		+= -Wextra
CFLAGS		+= -Wpedantic
CFLAGS		+= -fno-diagnostics-show-caret
CFLAGS		+= -ftrack-macro-expansion=0
CFLAGS		+= -Wno-misleading-indentation
CFLAGS		+= -fdata-sections
CFLAGS		+= -ffunction-sections
CFLAGS		+= -fpack-struct
#CFLAGS		+= -fshort-enums
#CFLAGS		+= -mcall-prologues
CFLAGS		+= -g
#CFLAGS		+= -pipe
CFLAGS		+= -Os		# -Os -O0 -O1 -O2 -O3
#CFLAGS		+= -save-temps
#CFLAGS		+= -ftime-report

LDFLAGS		+= $(MMCU)
LDFLAGS		+= --static
#LDFLAGS		+= -Wl,-Map,$(OUT).map,--cref
LDFLAGS		+= -Wl,--gc-sections
LDFLAGS		+= -nostartfiles
LDFLAGS		+= -nodefaultlibs

ifdef LTO
  ifeq ($(LTO),ON)
    CFLAGS	+= -flto
    LDFLAGS	+= -flto
  else
    ifneq ($(LTO),OFF)
      $(error LTO must be defined "ON" or "OFF")
    endif
  endif
endif

ifeq ($(BOOT),RAM)
DEFINES		+=	-DBOOT_RAM
LDFLAGS		+=	-T../make/ram.ld
endif


################################################################################
#									       #
#	Compile								       #
#									       #
################################################################################

#  Create output directories
#
$(OUT).hwa $(OUT).elf $(OUT).bin $(OUT).lst: |$(OUTDIR)

$(OUTDIR):
#	@echo "Output directories: $(sort $(dir $(OBJECTS)))"
	@mkdir -p $(sort $(OUTDIR) $(dir $(OBJECTS)))

$(DEPS): $(OUTDIR)%.d: %.c |$(OUTDIR)
#	@echo "RULE: $@ : $^"
	@$(CC) $(DEFINES) $(INCLUDES) -MM -c $< -o $@

$(OBJECTS): $(OUTDIR)%.o: %.c |$(OUTDIR)
#	@echo "RULE: $@ : $^"
	@$(CC) $(CFLAGS) -c $< -o $@

# $(COBJECTS): $(OUTDIR)%.o: %.c |$(OUTDIR)
# #	@echo "RULE: $@ : $^"
# 	@$(CC) $(CFLAGS) -MD -c $< -o $@

# $(SOBJECTS): $(OUTDIR)%.o: %.s |$(OUTDIR)
# #	@echo "RULE: $@ : $^"
# 	$(CC) $(CFLAGS) -MD -c $< -o $@

# $(SXOBJECTS): $(OUTDIR)%.o: %.sx |$(OUTDIR)
# #	@echo "RULE: $@ : $^"
# 	@$(CC) $(AFLAGS) -MD -c $< -o $@

#  Link (must append $(LIBS) after other objects)
#
$(OUT).elf: $(OBJECTS) $(LDSCRIPT) |$(OUTDIR)
#	@echo "RULE: $@ : $^"
	@$(CC) $(LDFLAGS) -o $@ $(OBJECTS) $(LIBS)

# $(OUT).elf: $(SOURCES) $(LDSCRIPT)
# #	@echo "RULE: $@ : $^"
# 	@$(CC) $(CFLAGS) $(LDFLAGS) -MD -o $@ $(SOURCES) $(LIBS)

#  Binary output (Atmel AVR)
#    Note: must specify the section otherwise gap-fill includes the .data section (-> 8 MB!)
#
%.bin: %.elf
#	@echo "RULE: $@ : $^"
	@$(OBJCOPY) $(PADTO) 							\
		--only-section .text --only-section .bss --only-section .data	\
		-O binary $^ $@

#  Disassembly
#
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
size:	$(OUT).elf
	@$(SIZE) $^

crc32:	$(OUT).bin
	@echo -n "CRC32: " ; crc32 $^

#  Diabolo's CRC of the generated binary (Atmel AVR)
#
stat:	$(OUT).bin
	@if [ ! -f "$(diabolo)" ] ; then					\
	  echo "Diabolo is required for make target 'stat'." ;			\
	elif python3 -V >/dev/null 2>&1 ; then					\
	  $(diabolo) --mcu=$(target_device) --stat $(OUT).bin -q		;\
	else									\
	  echo "Install Python if you want Diabolo to stat your application."	;\
	fi


################################################################################
#									       #
#	Install for STM32 using openocd					       #
#									       #
################################################################################

ifeq ($(PROGSW),openocd)

  ifeq ($(PROGIF),)
    $(error PROGIF is not defined)
  endif

  ifeq ($(PROGTG),)
    $(error PROGTG_TG is not defined)
  endif

#JTAG	=	stlink-v2
#JTAG	=	ftdi/100ask-openjtag

#  When booting from SRAM:
#    * in the application initialization code, you have to relocate the vector
#      table in SRAM using the NVIC exception table and offset register:
#
#        *(uint32_t*)0xE000ED08 = 0x20000000;
#        mon mww 0xE000ED08 0x20000000
#
#    * the SP is not loaded:
#
#        set $$sp = *(int*)0x20000000
#        set $$pc = *(int*)0x20000004

.PHONY: openocd
openocd:
	@if pidof -q openocd ; then					\
	  echo "openocd is already running." ;				\
	else								\
	  openocd -c 'source [find interface/$(PROGIF).cfg]'		\
	          -c 'source [find target/$(PROGTG).cfg]' ;		\
	fi

#  Use screen for openocd to not be killed by Ctrl-C in gdb
#
.PHONY: gdb
gdb:	$(OUT).elf
	@if ! pidof -q openocd ; then					\
	  screen -d -m -S "OPENOCD" 					\
	    openocd -c 'source [find interface/$(PROGIF).cfg]'		\
	            -c 'source [find target/$(PROGTG).cfg]' &		\
	  sleep 0.1 ; 							\
	fi ;								\
	if pidof openocd ; then						\
	  $(GDB) -ex "set architecture arm"				\
		 -ex "target remote localhost:3333" 			\
		 -ex "mon reset halt"					\
		 -ex "file $(OUT).elf"					\
		 -ex "load $(OUT).elf"					\
		 -ex "mon mww 0xE000ED08 0x20000000"			\
		 -ex 'set $$sp = *(int*)0x20000000'			\
		 -ex 'set $$pc = *(int*)0x20000004'			\
		 -ex 'set output-radix 16' ;				\
	  killall openocd ;						\
	  else echo "Failed to start openocd." >&2; exit 1 ;		\
	fi

.PHONY: install
install: $(OUT).elf $(OUT).lst
	@if ! pidof -q openocd ; then				\
	  exec 1>/dev/null 2>/dev/null				\
	    openocd -c 'source [find interface/$(PROGIF).cfg]'	\
	            -c 'source [find target/$(PROGTG).cfg]' &	\
	  SHUTDOWN="mon shutdown" ;				\
	  sleep 0.1 ; 						\
	fi ;							\
	if pidof -q openocd ; then				\
	$(GDB)	-ex "set architecture arm"			\
		-ex "target remote localhost:3333" 		\
		-ex "mon reset halt"				\
		-ex "mon init"					\
		-ex "load $(OUT).elf"				\
		-ex "mon mww 0xE000ED08 0x20000000"		\
		-ex 'set $$sp = *(int*)0x20000000'		\
		-ex 'set $$pc = *(int*)0x20000004'		\
		-ex "mon resume"				\
		-ex "$$SHUTDOWN"				\
		-ex "detach"					\
		-ex "quit" >/dev/null 2>&1 && echo "Success";	\
	  else echo "Failed to start openocd." >&2 ; exit 1 ;	\
	fi

endif # ifeq ($(PROGSW),openocd)


################################################################################
#									       #
#	Install for Atmel AVR using Diabolo				       #
#									       #
################################################################################


ifeq (avr,$(target_arch))

#  Option: DIABOLO_PORT. This can be:
#    * a tty: /dev/ttyS4
#    * a serial adapter: /dev/ttyUSB0
#    * a RFC2217 adapter: rfc2217://192.168.1.78:23
#
ifneq (,$(DIABOLO_PORT))
  DIABOLO_OPTS	+= -t $(DIABOLO_PORT)
endif

#  Option: DIABOLO_BPS
#
ifneq (,$(DIABOLO_BPS))
   DIABOLO_OPTS	 += --bps=$(DIABOLO_BPS)
endif

#  Compute how long TXD must be held low so that the device has the time to
#  start (assumes 65 ms + 32KCK) and the bootloader has the time to check the
#  CRC of the application (30 cycles/byte).
#
ifeq ($(target_syshz),HW_DEVICE_SYSHZ)
  target_syshz = 8000000
endif

DIABOLO_KEEP_TXD_LOW	?= \
	$(shell \
	SUT=$$(( 65 + (32768+30*$(target_flash))*1000/$(target_syshz) ))	;\
	i=$$(( $$SUT / 1000 ))							;\
	t=$$(( $$SUT - 1000 * $$i ))						;\
	printf "%d.%03d" $$i $$t )

DIABOLO_OPTS	 += --keep-txd-low=$(DIABOLO_KEEP_TXD_LOW)

ifneq (,$(DIABOLO_SYNC))
  DIABOLO_OPTS	 += --sync=$(DIABOLO_SYNC)
endif

DIABOLO_OPTS	 += --mcu=$(target_device)
DIABOLO_OPTS	 += --diag


.PHONY: erase
erase:
	$(diabolo) $(DIABOLO_OPTS)	\
		--erase-flash

.PHONY: install
install: $(OUT).bin
	$(diabolo) $(DIABOLO_OPTS)		\
		--cache=/tmp/diabolo-cache.bin	\
		--burn-flash $<

.PHONY: diabolo
diabolo:
	@$(diabolo) $(DIABOLO_OPTS)

.PHONY: identify
identify:
	@$(diabolo) $(DIABOLO_OPTS)

.PHONY: decode-fuses
decode-fuses:
	@$(diabolo) $(DIABOLO_OPTS) --decode-fuses

.PHONY: reset
reset:
	@$(diabolo) --reset

endif # ifeq (avr,$(target_arch))


#  Preprocessing (for HWA developper)
#
#  It's sometimes useful to preprocess one source to see how the HWA macros
#  expand. 'force' forces make to rebuild the target even if the source is not
#  changed (avoids having to add the -B option).
#  Display everything starting from '--' in the output.
#
%.cp.c: %.c force
#	@echo "RULE $@: $^"
	@$(CPP) $(CFLAGS) $< >$@ && sed -n '/^--/,$$p' $@ |sed -e 's/;/;\n/g'|bcpp -s -i 2 -bcl
#	$(CPP) $(CFLAGS) $< |sed -e 's/;/;\n/g'|bcpp -s -i 2 -bcl | sed -e 's/#/\/\//g' > $@

.PHONY: force
force: ;

endif # ifneq ($(BOARD),)


################################################################################
#									       #
#	Goals available without SOURCES					       #
#									       #
################################################################################


default:
	$(error "clean or tarball?")

#  Cleaning: remove 'build' directories & other useless files
#
.PHONY: clean
clean:
	@find . -name 'build' -prune -exec rm -rf {} ';'
	@find . '(' 					\
		-name '*~' 				\
		-o -name '*.cp.*'			\
		')' -exec rm {} ';'

.PHONY: tarball
tarball:
	tar cJf examples.xz --exclude=examples.xz --exclude=build * && \
	ls -l examples.xz
