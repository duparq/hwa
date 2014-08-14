
CWD := $(dir $(lastword $(MAKEFILE_LIST)))

#	Find target device in source files
#
ifeq (,$(MCU))
  comma := ,
  MCU = $(shell (grep -e '^\#define[[:space:]]HW_DEVICE[[:space:]]'	\
                   $(SOURCES) config.h 2>/dev/null)			\
	  | head -1 | awk '{$$1=$$2=""; print $$0}') # print all but two first columns
  MCU := $(strip $(firstword $(subst $(comma), ,$(MCU))))
endif

ifeq (,$(MCU))
$(error Please define HW_DEVICE in one of the source files or in config.h)
endif

#	Chip programming
#
PROG_SW		=	diabolo
DIABOLO_OPTS	+=	--read-flash	# programming will be faster
DIABOLO_OPTS	+=	--mcu=$(MCU)

#	HWA source path
#
HWA		= 	$(abspath $(CWD)../..)
INCLUDES	+= 	-I$(HWA)

#	SWUART source path
#
SWUART		= 	$(abspath $(CWD)../swuart-src)
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
all:	deps bin lst crc


#	Common makefile
#
include $(CWD)Makefile.in
