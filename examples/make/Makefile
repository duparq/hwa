
#	Find target device
#
ifeq ($(strip $(MCU)),)
  MCU = $(shell (grep -e '^\#define[[:space:]]HWA_DEVICE[[:space:]]'	\
                   $(SOURCES) config.h 2>/dev/null)			\
	  | head -1 | awk '{print $$NF}')
endif

ifeq ($(strip $(MCU)),)
$(error Please define HWA_DEVICE in one source file or in config.h)
endif

#DEFINES		+=	-Wno-unknown-pragmas

#	Chip programming
#
PROG_SW		=	diabolo
DIABOLO_OPTS	+=	--read-flash	# programming will be faster
DIABOLO_OPTS	+=	--mcu=$(MCU)

#	HWA source path
#
HWA		= 	$(abspath $(PWD)/../..)
INCLUDES	+= 	-I$(HWA)

#	SWUART source path
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


#	Common makefile
#
CWD := $(dir $(lastword $(MAKEFILE_LIST)))
include $(CWD)Makefile.in
