
#  Build all the examples
#
.PHONY: all
all:
	@bash make/make-all.sh


#  Check all the examples
#
.PHONY: check
check:
	@bash make/check-all.sh


#  Remove all built files
#
.PHONY: clean
clean:
	@find . -name 'build' -prune -exec rm -rf {} ';'
	@find boards -name 'build' -prune -exec rm -rf {} ';'
	@find . '(' 					\
		-name '*~' 				\
		-o -name '*.cp.*'			\
		-o -name '*.hwa.c'			\
		-o -name '*.pyc'			\
		')' -exec rm {} ';'


#  Produce HTML documentation
#
.PHONY: doc
doc:
	@cd ../../../doxygen && $(MAKE) --no-print-directory
