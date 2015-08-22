
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
			hw_swuart1_pin_rxd		\
			hw_swuart1_pin_txd		\
			hw_swuart1_autosync		\
			hw_swuart1_compare		\
			hw_swuart1_clk_div		\
			PIN_LED

include ../Makefile


#	Get the sync method for main.py
#
build/sync.c:
	@mkdir -p build
	@echo 'SYNC=hw_swuart0_autosync\n' >build/sync.c

build/sync: build/sync.c
	@$(CPP) -I.. -I../../../../include -DBOARD_H=\<boards/$(BOARD).h\> \
	  -imacros "config.h" build/sync.c | grep '^SYNC='>build/sync
