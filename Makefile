
.PHONY: default
default:
	@echo "make doc | examples | check | clean"

#  Produce HTML documentation
#
.PHONY: doc
doc:
	@cd doxygen && $(MAKE) --no-print-directory


#  Remove all built files
#
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


#  Compile all the examples
#
.PHONY: examples
examples:
	@fails=0								;\
	(cd atmel/avr/examples         && bash make/make-all.sh)		;\
	fails=$$(($$fails+$$?))							;\
	(cd st/stm32/examples          && bash make/make-all.sh)		;\
	fails=$$(($$fails+$$?))							;\
	(cd espressif/esp8266/examples && bash make/make-all.sh)		;\
	fails=$$(($$fails+$$?))							;\
	echo "All examples: $$fails fails."


#  Verify the examples CRCs
#
.PHONY: check
check:
	@cd atmel/avr/examples         && $(MAKE) --no-print-directory check-all-examples
	@cd st/stm32/examples          && $(MAKE) --no-print-directory check-all-examples
	@cd espressif/esp8266/examples && $(MAKE) --no-print-directory check-all-examples
