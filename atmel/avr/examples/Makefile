
#$(warning INCLUDE)

CWD		+=	$(dir $(lastword $(MAKEFILE_LIST)))
MFD		:=	$(dir $(firstword $(CWD)))

#$(warning MFD=$(MFD))

export SOURCES
export CONFIG
export BOARD


#  Default target
#
.PHONY: default
# ifeq ($(wildcard main.c),)
#   default:	check-all-examples
# else
#   default:	all
# endif
ifeq ($(SOURCES),)
  default:	all-examples
else
  default:	all
endif


#  Remove built files under the working directory
#
.PHONY: clean
clean:
	@find . -name 'build*' -prune -exec rm -rf {} ';'
	@find . '(' 			\
		-name '*~' 		\
		-o -name '*.cp.*'	\
		-o -name '*.hwa.c'	\
		-o -name '*.pyc'	\
		')' -exec rm {} ';'


#  Produce HTML documentation
#
.PHONY: doc
doc:
	@cd $(MFD)../../../doxygen && $(MAKE) --no-print-directory


#  Default target: check that the compilation of all the examples produces the
#  same machine code for the same configuration
#
.PHONY: check-all-examples
check-all-examples:
#	@echo "RULE $@: $^"
	@BOARD=$(BOARD) bash $(MFD)make/check-all-examples.sh


#  Compile all the examples
#
.PHONY: all-examples
all-examples:
#	@echo "RULE $@: $^"
	@BOARDS=$(BOARD)						;\
	[ -n "$${BOARDS}" ] || BOARDS="attiny84 attiny85 nanodccduino"	;\
	fails=0								;\
	for BOARD in $${BOARDS} ; do					\
	  echo ; echo Building all examples for board $${BOARD}		;\
	  for i in ??-*							;\
	    do echo -n "$$i: "						;\
	    cd $$i							;\
	      if $(MAKE) BOARD=$${BOARD} -s all >/dev/null 2>&1 ; then	\
		echo success						;\
	      else							\
		echo failed						;\
		fails=$$((fails+1))					;\
	      fi							;\
	    cd - >/dev/null						;\
	  done								;\
	done ; echo "$$fails fails."


#  Validate all the examples
#
.PHONY: validate-all-examples
validate-all-examples:
	@for i in ??-* ; do echo $$i	;\
	(cd $$i ; $(MAKE) -s validate )	;\
	done


#  Include board-dependent Makefile if any
#
ifneq (,$(BOARD))
include $(MFD)boards/Makefile.$(BOARD)
else


#  Targets that require BOARD and SOURCES to be defined are found in
#  Makefile.build
#
force: ;

%.cp.c %.cp.sx: force
	@$(MAKE) -f $(MFD)make/Makefile.build --no-print-directory $@

.DEFAULT:
#	@echo "DEFAULT: $@"
	@$(MAKE) -f $(MFD)make/Makefile.build --no-print-directory $@

endif
