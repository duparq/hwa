
CWD		:=	$(dir $(lastword $(MAKEFILE_LIST)))

#  Produce HTML documentation
#
.PHONY: doc
doc:
	@cd $(CWD)doxygen && $(MAKE) --no-print-directory

.PHONY:clean
clean:
	@find . '(' 			\
		-name '*~' 		\
		-o -name '*.cp.*'	\
		-o -name '*.pyc'	\
		-o -name '*.bak'	\
		')' -exec rm -rf {} ';'
	@find . -name 'build' -prune -exec rm -rf {} ';'
	@rm -rf doxygen/html


#  Remove all produced files + examples validation data
#
.PHONY: realclean
realclean: clean
	@find . -name '.valid-*' -exec rm -rf {} ';'


#  Compile all the examples
#
.PHONY: all-examples
all-examples:
	@cd $(CWD)atmel/avr/examples && $(MAKE) --no-print-directory all-examples


#  Check that all the examples machine codes have the same CRC for the same
#  configuration
#
.PHONY: check-all-examples
check-all-examples:
	@cd $(CWD)atmel/avr/examples && $(MAKE) --no-print-directory check-all-examples
