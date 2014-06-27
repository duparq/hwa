
#	Source files
#
SOURCES		=	test.c	\
			swuart.sx

#	Target device
#
MCU		= atmega48

#	HWA directory
#
HWA		= $(HOME)/dev/hwa

#	hwa.c is required for STM32
#
SOURCES		:= $(HWA)/hwa.c $(SOURCES)

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

#	Default make target
#
all:	deps hex bin lst size

#	Device-specific makefile
#	Common makefile
#
include make/Makefile.$(MCU) make/Makefile.in
