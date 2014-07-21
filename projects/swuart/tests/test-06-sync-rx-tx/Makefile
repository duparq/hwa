
#	Source files
#
SOURCES		=	main.c	\
			swuart.sx

#	Target device
#
MCU		= 	attiny84
PKG		=	DIL


#	Chip programming
#
PROG_SW		=	diabolo
DIABOLO_OPTS	=	--read-flash	# programming will be faster
DIABOLO_OPTS	+=	--mcu=$(MCU)

#	HWA
#
HWA		= 	$(HOME)/dev/hwa-dev
DEFINES		+=	-DHWA_DEVICE=$(MCU)
DEFINES		+=	-DHWA_PKG_$(PKG)

#	SWUART
#
SWUART		= $(HOME)/dev/hwa-dev/projects/swuart/src

#	hwa.c is required for STM32
#
#SOURCES		:= $(HWA)/hwa.c $(SOURCES)

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
OBJDIR		= build

#	Default make target
#
all:	deps bin lst crc

#	Device-specific makefile
#	Common makefile
#
include make/Makefile.$(MCU) make/Makefile.in
#include $(abspath $(PWD)/../../make/Makefile.$(MCU)) make/Makefile.in
# include $(abspath $(PWD)/../../make/Makefile.$(MCU)) \
# 	$(abspath $(PWD)/../../make/Makefile.in)
#include ../../make-0/Makefile.$(MCU) ../../make-0/Makefile.in
