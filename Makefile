
# all:
# 	cd .. && make

# %:
# 	cd .. && make $@

test:	build/test



#	Nom de base des fichiers "exécutables"
#
PROJECT		=	test

#	Liste des fichiers sources (.c) nécessaires pour
#	produire l'exécutable
#
SOURCES		=	../hwa/hwa.c		\
			test.c

MCU		=	stm32

#	Répertoire de dépot des fichiers objets
#
BUILDIR		=	build

DEFINES		+= -DHWA_DBG
DEFINES		+= -DHWA_DEVICE=$(MCU)
DEFINES		+= -DNO_DATA_INIT

CFLAGS		+= -std=c99
CFLAGS		+= -Wall
CFLAGS		+= -Wextra
#CFLAGS		+= -pedantic
CFLAGS		+= -g
CFLAGS		+= -pipe
CFLAGS		+= -Os

INCLUDES	+= -I$(PWD)/hwa -I$(PWD)/inc -I$(PWD)/lib

LDFLAGS		= $(CFLAGS)
LDFLAGS		+= -Wl,--gc-sections

DEPS		= $(BUILDIR)/$(PROJECT).$(MCU).deps


#	Calcule les noms des fichiers objets à générer
#	par substitution des extensions
#
SRC		:=	$(SOURCES) $(APP_C)
SRC		:=	$(SRC:.c=.$(MCU).o)
OBJECTS		=	$(patsubst %,$(BUILDIR)/%,$(SRC))

CFLAGS		+= $(DEFINES)
CFLAGS		+= $(INCLUDES)


ODUMP		= $(ARCH)objdump


all: elf lst size

elf: $(BUILDIR)/$(PROJECT)
lst: $(BUILDIR)/$(PROJECT).lst

$(BUILDIR)/$(PROJECT): $(OBJECTS) Makefile
	$(CC) $(LDFLAGS) -o $@ $(OBJECTS) $(LIBS)

$(BUILDIR)/%.$(MCU).o : %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

size: $(BUILDIR)/$(PROJECT)
	@$(SIZE) $<

%.lst : %
	$(ODUMP) -S -z -j.vectors -j.app_head -j.text -j.rodata -j.bss -j.data $^ >$@


#	Nettoie le répertoire
#
clean:
	@find . '(' 			\
		-name '*~' 		\
		-o -name '*.deps' 	\
		-o -name '*.map' 	\
		-o -name '*.a'		\
		-o -name '*.bin'	\
		-o -name '*.cp'		\
		-o -name '*.cpp.*'	\
		-o -name '*.o'		\
		-o -name '*.pyc'	\
		-o -name '*.so'		\
		-o -name '*.out'	\
		-o -name '*.elf'	\
		-o -name '*.hex'	\
		-o -name 'build'	\
		')' -exec rm -rf {} ';'
