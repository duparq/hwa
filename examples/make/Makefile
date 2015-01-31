
CWD := $(dir $(lastword $(MAKEFILE_LIST)))


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


#	Check that we have the list of source files
#
ifeq (,$(SOURCES))
  $(error Please define SOURCES)
endif


#	Retrieve the name of the target device from source files
#
# ifeq (,$(MCU))
#   MCU = $(shell							\
#   mkdir -p $(OBJDIR)						;\
#   for f in $(SOURCES) ; do					\
#     SRC=".hwa.c"						;\
#     DST=".hwa.1"						;\
#     ERR=".hwa.2"						;\
#     cat "$$f" >"$$SRC"						;\
#     echo 'HW_DEVICE' >>"$$SRC"					;\
#     $(CC) -I$(HWA) -E "$$SRC" >"$$DST" || exit 1		;\
#     HW_DEVICE=$$(tail -1 "$$DST" 2>/dev/null)			;\
#     rm -f "$$SRC" "$$DST" "$$ERR"				;\
#     if [ "$$HW_DEVICE" != "HW_DEVICE" ] ; then			\
#       echo $$HW_DEVICE						;\
#       exit 0							;\
#     fi								;\
#   done)
#   ifeq (,$(wildcard .hwa.2))
#     comma := ,
#     MCU := $(strip $(firstword $(subst $(comma), ,$(MCU))))
#   endif
# endif

ifeq (,$(MCU))
  SRC=".hwa.c"
  DST=".hwa.d"
  ERR=".hwa.e"
  MCU = $(shell								\
  echo 'HW_DEVICE' >"$(SRC)"						;\
  mkdir -p $(OBJDIR)							;\
  for f in $(SOURCES) ; do						\
    $(CC) -I$(HWA) -E -imacros "$$f" "$(SRC)" >"$(DST)" 2>"$(ERR)" || exit 1	;\
    HW_DEVICE=$$(tail -1 "$(DST)" 2>/dev/null)				;\
    if [ "$$HW_DEVICE" != "HW_DEVICE" ] ; then				\
      echo $$HW_DEVICE							;\
      exit 0								;\
    fi									;\
  done)
  ifeq (,$(wildcard .hwa.2))
    comma := ,
    MCU := $(strip $(firstword $(subst $(comma), ,$(MCU))))
  endif
endif

ifeq (,$(MCU))
  $(error HW_DEVICE not defined or preprocessing errors)
endif

#	Chip programming
#
ifeq (,$(PROG_SW))
PROG_SW		=	diabolo
#DIABOLO_OPTS	+=	--read-flash	# programming will be faster
#DIABOLO_OPTS	+=	--flash-cache=build/flash-cache.bin # even faster
#DIABOLO_OPTS	+=	--mcu=$(MCU)
else
PROG_SW		=	avrdude
PROG_HW		=	usbasp
endif



#	Default target
#
all:	deps hwa lst crc

hwa: $(OBJDIR)/$(OUT).hwa

doc:
	(cd $(CWD)../.. && make doc)


#	Common makefile
#
include $(CWD)Makefile.in
