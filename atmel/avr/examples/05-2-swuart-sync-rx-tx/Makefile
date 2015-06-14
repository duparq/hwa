
#	Source files
#
SOURCES		=	main.c	\
			swuart.sx

CONFIG		=	HW_DEVICE			\
			hw_syshz			\
			hw_swuart0_pin_rx		\
			hw_swuart0_pin_tx		\
			hw_swuart0_counter		\
			hw_swuart0_counter_clk_div	\
			hw_swuart0_counter_compare	\
			PIN_LED				\
			UART				\
			OSCCAL


include ../../../../make/Makefile


#	Get the sync method for main.py
#
sync:
	@mkdir -p build
	@echo 'SYNC=hw_swuart0_autosync\n' >build/sync.c
	@$(CPP) $(INCLUDES) -imacros "config.h" build/sync.c | grep '^SYNC='>build/sync
