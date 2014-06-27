
#	Makefile for checking that HWA produces valid code.
#
#	'result' and 'valid' files contain test function names and their assembly code.
#
#	Target "all" creates 'result' files and compare them with 'valid' files.
#       It also creates 'valid' files that do not exist yet.
#
#	Target "results" creates 'result' files and exits.
#
#	Use ./mkvalid to validate modifications to test files. This will copy
#	newly-compiled result files onto valid files.


#	Sources containing test functions
#
SOURCES		=	
#SOURCES		+= attiny44-ios.c
#SOURCES		+= attiny44-counter0.c
SOURCES		+= attiny44-counter1.c


#	Target device
#
MCU		= attiny44
DEFINES		+= -DHW_DEVICE=$(MCU)
DEFINES		+= -DFUSE_LB=0xE2
DEFINES		+= -DFUSE_HB=0xDF
DEFINES		+= -DFUSE_EB=0xFE


#	HWA directory
#
HWA		= $(PWD)/../..


#	HWA files path
#
INCLUDES	+= -I$(HWA)


#	Toolchain path
#
# PATH		:= $(HOME)/dev/gcc-toolchains/4.7.0/bin:$(PATH)


#	Build directory
#
BUILDIR		= build


ARCH		= avr-
MMCU		= -mmcu=$(MCU)

CC		= $(ARCH)gcc
AS		= $(ARCH)as
OBJCOPY		= $(ARCH)objcopy
ODUMP		= $(ARCH)objdump
GDB		= $(ARCH)gdb
SIZE		= $(ARCH)size

CFLAGS		+= $(MMCU)
CFLAGS		+= -std=c1x
CFLAGS		+= -Wall
CFLAGS		+= -Wextra
CFLAGS		+= -pedantic
CFLAGS		+= -Os
CFLAGS		+= $(DEFINES)
CFLAGS		+= $(INCLUDES)

LDFLAGS		+= $(MMCU)
LDFLAGS		+= -Wl,--gc-sections


#	Lists of files
#
OBJECTS		= $(patsubst %,$(BUILDIR)/%,$(SOURCES:.c=.o))
RESULTS		= $(OBJECTS:.o=.result)
DIFFS		= $(RESULTS:.result=.diff)


.PHONY: all
all:	$(BUILDIR) $(DIFFS) $(RESULTS) # $(OBJECTS)


.PHONY: results
results: $(BUILDIR) $(RESULTS)


$(BUILDIR):
	mkdir $(BUILDIR)


$(BUILDIR)/%.diff : %.valid $(BUILDIR)/%.result
	@diff $^ >$@ || (echo "Diff:" >&2 ; cat $@ >&2 ; exit 1)


%.valid : $(BUILDIR)/%.result
	@[ -f $@ ] || cp $< $@


$(BUILDIR)/%.result : %.c $(BUILDIR)/%.elf $(BUILDIR)/%.bin
	./mkresult.sh $^ >$@


%.bin : %.elf
	$(OBJCOPY) -R .eeprom -O binary $^ $@


$(BUILDIR)/%.elf : %.o $(BUILDIR)/main-%.o
	$(CC) $(LDFLAGS) -o $@ $^


$(BUILDIR)/%.o : %.c
	$(CC) $(CFLAGS) -c $^ -o $@


$(BUILDIR)/main-%.o : $(BUILDIR)/main-%.c
	$(CC) $(CFLAGS) -c $^ -o $@


$(BUILDIR)/main-%.c: %.c
	./mkmain.sh $^ >$@

$(BUILDIR)/%.cp.c: %.c
	$(CC) -E $(CFLAGS) $^ >$@

.PHONY: cpp
cpp:
	$(CC) -E $(CFLAGS) $^


.PHONY: clean
clean:
	rm -rf $(BUILDIR)
	find . '(' 			\
		-name '*~' 		\
		-o -name '*.cp.*'	\
		-o -name '*.pyc'	\
		')' -exec rm {} ';'
