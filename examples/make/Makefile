
#	-*- makefile -*-

#$(warning "RESTART: $(MAKE_RESTARTS) $(DEVICE)")


#  Directory of this Makefile
#
CWD := $(dir $(lastword $(MAKEFILE_LIST)))


#  No need to go beyond without a list of source files
#
ifeq (,$(SOURCES))
  $(error SOURCES not defined)
endif


.SUFFIXES:
.SUFFIXES: .c .o
SHELL		= /bin/sh


#  HWA source path and other related include directories
#
HWA		=  $(abspath $(CWD)../..)
INCLUDES	+= -I$(HWA) -I$(HWA)/swuart-src -I$(HWA)/examples


#	Output basename and directory
#
OUT		= out
OUTDIR		= build


#  Definitions from sources
#
INC_HWA		= $(OUTDIR)/$(OUT).hwa


#  Include the definitions about DEVICE (may rebuild INC_HWA)
#
-include $(INC_HWA)


#  DEVICE could not be determined. Stop here.
#
ifeq (HW_DEVICE,$(DEVICE))
  $(error "HW_DEVICE not defined (or preprocessing errors)")
endif


#  DEVICE is known, include Makefile.2
#
ifneq (,$(DEVICE))
  include $(CWD)Makefile.inc
endif


#  Get DEVICE informations from definitions in source files
#
#	Build a .c file that will retrieve the informations we're looking for.
#
#	Double quotes are required for complex values for make to not show an
#	error message when it reads it.
#
$(INC_HWA).c:
	@echo "RULE: $@"
	@mkdir -p $(OUTDIR)
	@echo 'DEVICE=HW_A0(HW_DEVICE)' >$@
	@echo 'DEVICE_VENDOR=HW_DEVICE_VENDOR' >>$@
	@echo 'DEVICE_ARCH=HW_DEVICE_ARCH' >>$@
	@echo 'DEVICE_FLASH_SIZE=HW_DEVICE_FLASH_SIZE' >>$@
	@echo 'DEVICE_FUSE_EB=HW_QUOTE(HW_DEVICE_FUSE_EB)' >>$@
	@echo 'DEVICE_FUSE_HB=HW_QUOTE(HW_DEVICE_FUSE_HB)' >>$@
	@echo 'DEVICE_FUSE_LB=HW_QUOTE(HW_DEVICE_FUSE_LB)' >>$@
#
#	Let CPP process this .c file with the symbols defined in each source file
#	in turn until DEVICE is found. Store the informations in a file.
#
$(INC_HWA): $(SOURCES) $(INC_HWA).c
	@echo "RULE: $@: $^"
	@set -e ; for f in  $(SOURCES) ; do			\
	  $(CPP) $(INCLUDES) -E -imacros "$$f" $(INC_HWA).c >$@	;\
	  . $@							;\
	  test "$$DEVICE" = HW_DEVICE || break			;\
	done


#  Clean
#
.PHONY: clean
clean:
	@echo "RULE: $@"
	@rm -rf $(OUTDIR)
	@find . '(' 			\
		-name '*~' 		\
		-o -name '*.cp.*'	\
		-o -name '*.pyc'	\
		-o -name '*.hwa.c'	\
		')' -exec rm {} ';'


#  Archive the source directory
#
.PHONY: tarball
tarball: clean
	SRC=$$(basename $$PWD)					;\
	DST=$$SRC.tar.bz2					;\
	tar -cvO --exclude=trash --exclude=$$DST		\
		../$$SRC | bzip2 >$$DST
