
#  Produce HTML documentation
#
.PHONY: doc
doc:
	@cd ../../../../doxygen && $(MAKE) --no-print-directory


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

