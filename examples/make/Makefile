
#	-*- makefile -*-

#  No need to go beyond without a list of source files
#
ifeq (,$(SOURCES))
  $(error SOURCES not defined)
endif


#  Directory from where make was started
#
CWD := $(dir $(lastword $(MAKEFILE_LIST)))


.SUFFIXES:
.SUFFIXES: .c .o
SHELL		= /bin/sh


#  HWA source path and other related include directories
#
HWA		=  $(abspath $(CWD)../..)
INCLUDES	+= -I$(HWA) -I$(HWA)/swuart-src -I$(HWA)/examples

#	Toolchain path
#
# PATH		:= $(HOME)/dev/gcc-toolchains/4.7.0/bin:$(PATH)

#	Output basename and directory
#
OUT		= out
OBJDIR		= build

#  Dependencies
#
DEPS		 = $(SOURCES:.c=.d)
DEPS		:= $(DEPS:.sx=.d)
DEPS		:= $(addprefix $(OBJDIR)/,$(DEPS))

#  Definitions from sources
#
INC_HWA		= $(OBJDIR)/$(OUT).hwa
INC_HWA_C	= $(INC_HWA).c


#	Default target
#
.PHONY: all
all:	bin lst crc


#  Get DEVICE informations from definitions in source files
#
#	Build a .c file that will retrieve the informations we're looking for.
#
#	Double quotes are required for complex values for make to not show an
#	error message when it reads it.
#
$(INC_HWA_C):
	@echo "RULE: $@"
	@mkdir -p $(OBJDIR)
	@echo 'DEVICE=HW_A0(HW_DEVICE)' >$@
	@echo 'DEVICE_FLASH_SIZE=HW_DEVICE_FLASH_SIZE' >>$@
	@echo 'DEVICE_FUSE_EB=HW_QUOTE(HW_DEVICE_FUSE_EB)' >>$@
	@echo 'DEVICE_FUSE_HB=HW_QUOTE(HW_DEVICE_FUSE_HB)' >>$@
	@echo 'DEVICE_FUSE_LB=HW_QUOTE(HW_DEVICE_FUSE_LB)' >>$@
#
#	Let CC compile this .c file with the symbols defined in each source file
#	in turn until DEVICE is found. Store the informations in a file.
#
$(INC_HWA): $(DEPS) $(INC_HWA_C) $(SOURCES)
	@echo "RULE: $@: $^"
	@set -e ; for f in  $(SOURCES) ; do				\
	  $(CC) $(CFLAGS) -E -imacros "$$f" $(INC_HWA_C) >$@	;\
	  . $@							;\
	  test "$$DEVICE" = HW_DEVICE || break			;\
	done
#
#	Include the definitions about DEVICE
#
-include $(INC_HWA)


ifneq (,$(MAKE_RESTARTS))
  ifeq (HW_DEVICE,$(DEVICE))
    $(error "HW_DEVICE not defined (or preprocessing errors)")
  endif
endif


#  Dependencies
#
#	Build one dependency files for each source file
#
$(OBJDIR)/%.d: %.c
	@echo "RULE: $@: $^"
	@mkdir -p $(OBJDIR)
	@set -e; rm -f $@; \
	$(CC) -M $(INCLUDES) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

$(OBJDIR)/%.d: %.sx
	@echo "RULE: $@: $^"
	@mkdir -p $(OBJDIR)
	@set -e; rm -f $@; \
	$(CC) -M $(INCLUDES) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$
#
#	Load dependencies
#
-include $(DEPS)


#  Chip programmer
#
ifeq (,$(PROG_SW))
  PROG_SW	=	diabolo
else
  PROG_SW	=	avrdude
  PROG_HW	=	usbasp
endif


#  Documentation
#
.PHONY: doc
doc:
	(cd $(CWD)../.. && make doc)


#  Common makefile
#
include $(CWD)Makefile.in

# ifneq ($(DEVICE),HW_DEVICE)
#   include $(CWD)Makefile.in
# endif


#	Clean
#
.PHONY: clean
clean:
	@echo "RULE: $@"
	@rm -rf $(OBJDIR)
	@find . '(' 			\
		-name '*~' 		\
		-o -name '*.cp.*'	\
		-o -name '*.pyc'	\
		-o -name '*.hwa.c'	\
		')' -exec rm {} ';'


#	Archive
#
tarball: clean
	SRC=$$(basename $$PWD)					;\
	DST=$$SRC.tar.bz2					;\
	tar -cvO --exclude=trash --exclude=$$DST		\
		../$$SRC | bzip2 >$$DST


deps:	$(DEPS)
