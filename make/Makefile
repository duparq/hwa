
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


#  Define a symbol BOARD that can be used to override the default
#  target device in the examples
#
ifneq (,$(BOARD))
  DEFINES += -DBOARD_H=\<boards/$(BOARD).h\>
endif


.SUFFIXES:
.SUFFIXES: .c .o
SHELL		= /bin/sh


#  HWA source path and other related include directories
#
HWA		=  $(abspath $(CWD)..)
INCLUDES	+= -I$(HWA)/include -I$(HWA)/atmel/avr/examples


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


#  Stop here if DEVICE could not be determined
#
ifeq (HW_DEVICE,$(DEVICE))
  $(error "HW_DEVICE not defined (or preprocessing errors)")
endif


#  Once the DEVICE is known, we can include Makefile.inc
#
ifneq (,$(DEVICE))
  include $(CWD)Makefile.inc
endif


#  Get DEVICE informations from definitions in source files
#
#	Build a .c file that will retrieve the informations we're looking for.
#
#	Quoting with HW_QUOTE is required for make to not show an error message
#	when it reads complex values.
#
$(INC_HWA).c:
#	@echo "RULE: $@"
	@mkdir -p $(OUTDIR)
	@echo \
	'DEVICE=HW_DEVICE\n'\
	'DEVICE_VENDOR=HW_DEVICE_VENDOR\n'\
	'DEVICE_ARCH=HW_DEVICE_ARCH\n'\
	'DEVICE_FLASH_SIZE=HW_DEVICE_FLASH_SIZE\n'\
	'DEVICE_FUSE_EB=HW_QUOTE(HW_DEVICE_FUSE_EB)\n'\
	'DEVICE_FUSE_HB=HW_QUOTE(HW_DEVICE_FUSE_HB)\n'\
	'DEVICE_FUSE_LB=HW_QUOTE(HW_DEVICE_FUSE_LB)\n' >$@
#
#	Let CPP process this .c file with the symbols defined in each source file
#	in turn until DEVICE is found. Store the informations in a file.
#
$(INC_HWA): $(SOURCES) $(INC_HWA).c
#	@echo "RULE: $@: $^"
	@set -e ; for f in  $(SOURCES) ; do			\
	  $(CPP) $(INCLUDES) $(DEFINES) -imacros "$$f" $(INC_HWA).c | grep '^DEVICE' >$@ ;\
	  . $@							;\
	  test "$$DEVICE" = HW_DEVICE || break			;\
	done


#	Put the configuration parameters that affect the application code into
#	a file that will be used later to check CRC correspondance. This helps
#	detecting application code modification after the HWA core is modified.
#
CFG	= $(OUTDIR)/$(OUT).config


#  Create a C source file holding the configuration of a project
#  Prefix symbols with '_' that will be removed after compiling.
#
$(CFG).c: $(SOURCES)
#	@echo "RULE: $@: $^  CONFIG=$(CONFIG)"
	@set -e					;\
	if [ -z "$(CONFIG)" ] ; then		\
	  echo FAIL: no config			;\
	  exit 1				;\
	fi					;\
	>$@					;\
	for c in $(CONFIG)			;\
	  do echo _$$c=$$c >>$@			;\
	done


#  List of files from which we want to extract the definitions
#
IMACROS = $(foreach S, $(SOURCES),-imacros $S)


#  Process configuration source
#
$(CFG): $(CFG).c
#	@echo "RULE: $@: $^  IMACROS=$(IMACROS)"
	@$(CPP) $(INCLUDES) $(DEFINES) $(IMACROS) $< | grep '^_.*' | sed -e 's/_//' >$@


#  Validate a project: store configuration, size and CRC
#
.PHONY: validate
validate: $(CFG) $(OUTDIR)/$(OUT).bin $(OUTDIR)/$(OUT).lst
#	@echo RULE: $@: $^
	@set -e										;\
	S_CRC=$$( crc32 $(CFG) | awk '{print $1}' )					;\
	O_CRC=$$(diabolo.py -q -m $(DEVICE) --crc $(OUTDIR)/$(OUT).bin)			;\
	O_SIZE=$$(diabolo.py -q -m $(DEVICE) --size $(OUTDIR)/$(OUT).bin)		;\
	rm -f .valid-$(DEVICE)-$$S_CRC-*						;\
	cp $(CFG) .valid-$(DEVICE)-$$S_CRC-$$O_SIZE-$$O_CRC				;\
	echo >>.valid-$(DEVICE)-$$S_CRC-$$O_SIZE-$$O_CRC				;\
	cat $(OUTDIR)/$(OUT).lst >>.valid-$(DEVICE)-$$S_CRC-$$O_SIZE-$$O_CRC		;\
	echo Validation: .valid-$(DEVICE)-$$S_CRC-$$O_SIZE-$$O_CRC


#  Check that the CRC is still the same for a given configuration
#
.PHONY: check
check: $(CFG)
	@S_CRC=$$( crc32 $(CFG) | awk '{print $1}' )					;\
	if [ "$$S_CRC" = "00000000" ] ; then						\
	  echo "CRC generation failed"							;\
	  exit 1									;\
	fi										;\
	if test -f .valid-$(DEVICE)-$$S_CRC-* ; then					\
	  if make $(OUTDIR)/$(OUT).bin >/dev/null 2>&1 ; then				\
	    O_CRC=$$(diabolo.py -q -m $(DEVICE) --crc $(OUTDIR)/$(OUT).bin)		;\
	    O_SIZE=$$(diabolo.py -q -m $(DEVICE) --size $(OUTDIR)/$(OUT).bin)		;\
	    if test -f .valid-$(DEVICE)-$$S_CRC-$$O_SIZE-$$O_CRC ; then			\
	      echo success								;\
	    else									\
	      echo FAIL: .valid-$(DEVICE)-$$S_CRC-* / $$O_SIZE-$$O_CRC			;\
	      exit 1									;\
	    fi										;\
	  else										\
	    echo "make FAILED"								;\
	    exit1									;\
	  fi										;\
	else										\
	  echo "no validation data"							;\
	fi


#  Clean
#
.PHONY: clean
clean:
#	@echo "RULE: $@"
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

#  Produce HTML documentation
#
.PHONY: doc
doc:
	@cd $(CWD).. && mkdir -p doxygen/html && doxygen doxygen/Doxyfile
