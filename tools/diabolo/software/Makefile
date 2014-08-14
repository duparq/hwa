
SOURCES		=	Makefile		\
			premain.py		\
			utils.py		\
			com.py			\
			crc_ccitt.py		\
			device.py		\
			cscont.py		\
			csmod.py		\
			diabolo.py		\
			wxdiabolo.py		\
			w_options.py		\
			miniterm.py

all:

list:
	echo $(SOURCES)


#	Nettoye le répertoire
#
clean:
	find . '(' 			\
		-name '*~' 		\
		-o -name '*.deps' 	\
		-o -name '*.map' 	\
		-o -name '*.a'		\
		-o -name '*.bin'	\
		-o -name '*.cpp.*'	\
		-o -name '*.o'		\
		-o -name '*.pyc'	\
		-o -name '*.so'		\
		-o -name '*.out'	\
		-o -name '*.elf'	\
		-o -name '*.hex'	\
		')' -exec rm {} ';'
	rm -rf $(BUILDIR)

#	Liste des cibles qui ne sont pas des fichiers
#
.PHONY: all list-files clean
