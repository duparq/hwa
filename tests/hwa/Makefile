
#	Fichier de test
#	
SOURCES		= device.c

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

#	Output basename
#
OUT		= out

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


COMPILER	= $(CC)-$(shell $(CC) -dumpversion)

# MAINS		= $(patsubst %,$(BUILDIR)/main-%,$(SOURCES))
# #OBJECTS		= $(SOURCES:.c=.$(MCU).o)
# #OBJECTS		= $(SOURCES:.c=-$(COMPILER).o)
# ELFS		= $(OBJECTS:.o=.elf)
# VALIDS		= $(OBJECTS:.o=.valid)


OBJECTS		= $(patsubst %,$(BUILDIR)/%,$(SOURCES:.c=.o))
RESULTS		= $(OBJECTS:.o=.result)
DIFFS		= $(RESULTS:.result=.diff)


.PHONY:
all:	$(BUILDIR) $(DIFFS) $(RESULTS)

.PHONY: results
results: $(BUILDIR) $(RESULTS)

.PHONY: validate
validate: $(BUILDIR) $(RESULTS)
	cp $(RESULTS) .
	bash -c "for i in *.result ; do mv -i $$i $${i/result/valid} ; done"


$(BUILDIR):
	mkdir $(BUILDIR)


$(BUILDIR)/%.diff : %.valid $(BUILDIR)/%.result
	diff $^ >$@


%.valid : $(BUILDIR)/%.result
	[ -f $@ ] && cp $< $@


$(BUILDIR)/%.result : %.c $(BUILDIR)/%.elf $(BUILDIR)/%.bin
	make/mkresult.sh $^ >$@


%.bin : %.elf
	$(OBJCOPY) -R .eeprom -O binary $^ $@


$(BUILDIR)/%.elf : %.o $(BUILDIR)/main-%.o
	$(CC) $(LDFLAGS) -o $@ $^


$(BUILDIR)/%.o : %.c
	$(CC) $(CFLAGS) -c $^ -o $@


$(BUILDIR)/main-%.o : $(BUILDIR)/main-%.c
	$(CC) $(CFLAGS) -c $^ -o $@


$(BUILDIR)/main-%.c: %.c
	make/mkmain.sh $^ >$@

%.cp.c: %.c
	$(CPP) $(CFLAGS) $< >$@
#	$(CPP) $(CFLAGS) $< |sed -e 's/;/;\n/g'|bcpp -s -i 2 -bcl | sed -e 's/#/\/\//g' > $@

#	Make the result file the reference file
#
# .PHONY: validate
# validate: $(BUILDIR)/$(OUT).result
# 	cp -a $(BUILDIR)/$(OUT).result $(VALID)


.PHONY: clean
clean:
	rm -rf $(BUILDIR)
	find . '(' 			\
		-name '*~' 		\
		-o -name '*.cp.*'	\
		-o -name '*.pyc'	\
		')' -exec rm {} ';'
