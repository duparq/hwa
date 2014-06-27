
#	Source files
#
SOURCES		=	test.c	\
			swuart.sx

#	Target device
#
MCU		= attiny84


#	Chip programming
#
PROG_SW		=	diabolo
DIABOLO_OPTS	=	--read-flash	# programming will be faster
DIABOLO_OPTS	+=	--mcu=$(MCU)


#	HWA directory
#
HWA		= $(HOME)/dev/hwa-dev
SWUART		= $(HOME)/dev/hwa-dev/projects/swuart/src

#	hwa.c is required for STM32
#
SOURCES		:= $(HWA)/hwa.c $(SOURCES)

#	HWA files path
#
INCLUDES	+= -I$(HWA)
INCLUDES	+= -I$(SWUART)

#	Toolchain path
#
# PATH		:= $(HOME)/dev/gcc-toolchains/4.7.0/bin:$(PATH)

#	Output basename
#
OUT		= out

#	Build directory
#
BUILDIR		= build

#	Default make target
#
all:	deps hex bin lst size

#	Device-specific makefile
#	Common makefile
#
include make/Makefile.$(MCU) make/Makefile.in
