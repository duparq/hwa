
#  Produce HTML documentation
#
.PHONY: doc
doc:
	@doxygen 			;\
	rm -f html/*.tmp		;\
	find ../atmel/avr/examples -name '*.jpeg' -exec cp -a {} html ';'
