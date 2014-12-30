
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


ifeq (,$(SOURCES))
$(error Please define SOURCES)
endif

#	Retrieve target device informations from source files
#
ifeq (,$(MCU))
  MCU = $(shell								\
  mkdir -p $(OBJDIR)							;\
  for f in $(SOURCES) ; do						\
    DST=$$f.hwa.c							;\
    cat $$f >"$$DST"							;\
    echo 'HW_DEVICE_FLASH_SIZE' >>"$$DST"				;\
    echo 'HW_DEVICE_FUSE_EB' >>"$$DST"					;\
    echo 'HW_DEVICE_FUSE_HB' >>"$$DST"					;\
    echo 'HW_DEVICE_FUSE_LB' >>"$$DST"					;\
    echo 'HW_DEVICE' >>"$$DST"						;\
    $(CC) -I$(HWA) -E $$DST >$(OBJDIR)/$(OUT).hwa 2>/dev/null		;\
    rm "$$DST" >/dev/null 2>&1					;\
    HW_DEVICE=$$(tail -1 $(OBJDIR)/$(OUT).hwa 2>/dev/null)		;\
    if [ "$$HW_DEVICE" != "HW_DEVICE" ] ; then				\
      echo $$HW_DEVICE							;\
      break								;\
    fi									;\
  done)
  comma := ,
  MCU := $(strip $(firstword $(subst $(comma), ,$(MCU))))
endif

ifeq (,$(MCU))
$(error Please define HW_DEVICE in one of the source files)
endif

FLASHSZ = $(shell \
	V=$$(tail -5 $(OBJDIR)/$(OUT).hwa 2>/dev/null | head -1 -)	;\
	if [ "$$V" != "HW_DEVICE_FLASH_SIZE" ] ; then			\
	  echo $$V							;\
	fi								;\
	done)

#	Chip programming
#
ifeq (,$(PROG_SW))
PROG_SW		=	diabolo
#DIABOLO_OPTS	+=	--read-flash	# programming will be faster
DIABOLO_OPTS	+=	--flash-cache=build/flash-cache.bin # even faster
DIABOLO_OPTS	+=	--mcu=$(MCU)
else
PROG_SW		=	avrdude
PROG_HW		=	usbasp
endif



#	Default target
#
all:	deps lst crc

doc:
	(cd $(CWD)../.. && make doc)


#	Common makefile
#
include $(CWD)Makefile.in
