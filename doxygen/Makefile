
#  Produce HTML documentation
#
.PHONY: doc
doc:
	@doxygen 			;\
	rm -f html/*.tmp		;\
	find ../atmel/avr/examples -name '*.jpeg' -exec cp -a {} html ';'
	@cd html						;\
	for i in * ; do						\
		perl -pi -e 's|/home/.*/dev/||g' $$i		;\
		perl -pi -e 's|_2home_2.*_2dev_2||g' $$i	;\
	done							;\
	for i in _2home* ; do					\
		mv $$i $${i#_2home_2$${USER}_2dev_2}		;\
	done
