
#	Source files
#
SOURCES		=	main.c	\
			swuart.sx

CONFIG		=	HW_DEVICE			\
			hw_syshz			\
			HW_SWUART0_PIN_RX		\
			HW_SWUART0_PIN_TX		\
			HW_SWUART0_COUNTER		\
			HW_SWUART0_COUNTER_CLK_DIV	\
			HW_SWUART0_COUNTER_COMP		\
			PIN_LED				\
			UART				\
			OSCCAL


include ../make/Makefile


#	Get the sync method for main.py
#
sync:
	@mkdir -p build
	@echo 'SYNC=HW_SWUART0_AUTOSYNC\n' >build/sync.c
	@$(CPP) $(INCLUDES) -imacros "config.h" build/sync.c | grep '^SYNC='>build/sync
