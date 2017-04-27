
#	Nom de base des fichiers "exécutables"
#
PROJECT		=	project

#	Liste des fichiers sources (.c) nécessaires pour
#	produire l'exécutable
#
SOURCES		=	../../hwa.c		\
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

#INCLUDES	+= -I$(PWD)/inc -I$(PWD)/hwa
INCLUDES	+= -I../..

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


all: elf lst

elf: $(BUILDIR)/$(PROJECT).elf
lst: $(BUILDIR)/$(PROJECT).lst

$(BUILDIR)/$(PROJECT).elf: $(OBJECTS) Makefile
	$(CC) $(LDFLAGS) -o $@ $(OBJECTS) $(LIBS)

$(BUILDIR)/%.$(MCU).o : %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

size: $(BUILDIR)/$(PROJECT).elf
	@$(SIZE) $<

%.lst : %.elf
	$(ODUMP) -S -z -j.vectors -j.app_head -j.text -j.rodata -j.bss -j.data $^ >$@

%.cp:	%.c
	$(CPP) $(CFLAGS) $^ |sed -e 's/;/;\n/g'|bcpp -s -i 2 -bcl | sed -e 's/#/\/\//g' > $@

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
		')' -exec rm -rf {} ';'
	@rm -rf $(BUILDIR)
