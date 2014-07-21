
#	Source files
#
SOURCES		=	main.c	\
			swuart.sx


#	Target device
#
MCU		=	attiny84
PKG		=	DIL
#DEFINES		+=	-Wno-unknown-pragmas

#	Chip programming
#
PROG_SW		=	diabolo
DIABOLO_OPTS	+=	--read-flash	# programming will be faster
DIABOLO_OPTS	+=	--mcu=$(MCU)

#	HWA
#
HWA		= 	$(abspath $(PWD)/../..)
INCLUDES	+= 	-I$(HWA)
DEFINES		+=	-DHWA_DEVICE=$(MCU)
DEFINES		+=	-DHWA_PKG_$(PKG)

#	SWUART
#
SWUART		= 	$(abspath $(PWD)/../swuart-src)
INCLUDES	+= 	-I$(SWUART)


#	Toolchain path
#
# PATH		:= $(HOME)/dev/gcc-toolchains/4.7.0/bin:$(PATH)

#	Output basename
#
OUT		= out

#	Build directory
#
OBJDIR		= build


#	Default target
#
#all:	deps hex bin lst size
all:	deps bin lst crc


#	Device-specific makefile
#	Common makefile
#
include $(abspath $(PWD)/../make/Makefile.$(MCU)) $(abspath $(PWD)/../make/Makefile.in)
