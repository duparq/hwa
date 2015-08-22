
#	Source files
#
SOURCES		=	main.c	\
			swuart.sx

CONFIG		=	HW_DEVICE			\
			hw_syshz			\
			hw_swuart0_pin_rxd		\
			hw_swuart0_pin_txd		\
			hw_swuart0_autosync		\
			hw_swuart0_compare		\
			hw_swuart0_clk_div		\
			PIN_LED				\
			UART				\
			OSCCAL

include ../Makefile

#	Get the sync method for main.py
#
# build/sync.c:
# 	@mkdir -p build
# 	@echo 'SYNC=hw_swuart0_autosync\n' >build/sync.c

# build/sync: build/sync.c
# 	@echo BOARD=$(BOARD)
# 	@[ -n "$$BOARD" ] || BOARD=$$(cat ../boards/default) ;\
# 	if [ -z "$$BOARD" ] ; then echo "BOARD is not defined!" ; exit 1 ; fi ;\
# 	$(CPP) -I.. -I../../../../include -DBOARD_H=\<boards/$(BOARD).h\> \
# 	  -imacros "config.h" build/sync.c | grep '^SYNC='>build/sync
