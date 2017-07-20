
#	Source files
#
SOURCES		=	main.c	\
			swuart.sx

CONFIG		=	HW_DEVICE			\
			hw_syshz			\
			UART				\
			BPS				\
			hw_swuart0_pin_txd		\
			hw_swuart0_compare		\
			hw_swuart0_clk_div

include ../make/Makefile

perfs:
	@get() { echo 0x$$(avr-nm build/${BOARD}/out.elf | grep " a $$1\$$" | cut -d' ' -f1); } ;\
	CY_ST=$$(get CY_ST)			;\
	CY_ST_SEI=$$(get CY_ST_SEI)		;\
	CY_RX_SEI=$$(get CY_RX_SEI)		;\
	CY_RX_DB=$$(get CY_RX_DB)		;\
	CY_RX_LDB=$$(get CY_RX_LDB)		;\
	CY_RX_SB=$$(get CY_RX_SB)		;\
	CY_TX_SEI=$$(get CY_TX_SEI)		;\
	CY_TX_DB=$$(get CY_TX_DB)		;\
	CY_TX_LDB=$$(get CY_TX_LDB)		;\
	CY_TX_SB=$$(get CY_TX_SB)		;\
	echo Start condition takes $$(( $$CY_ST )) cycles				;\
	echo Start condition disables interrupts for $$(( $$CY_ST_SEI )) cycles		;\
	echo Reception of bit disables interrupts for $$(( $$CY_RX_SEI )) cycles 	;\
	echo Reception of data bit takes $$(( $$CY_RX_DB )) cycles			;\
	echo Reception of stop bit takes $$(( $$CY_RX_SB )) cycles			;\
	echo Reception of last data bit takes $$(( $$CY_RX_LDB )) cycles		;\
	echo Transmission of bit disables interrupts for $$(( $$CY_TX_SEI )) cycles 	;\
	echo Transmission of data bit takes $$(( $$CY_TX_DB )) cycles			;\
	echo Transmission of last data bit takes $$(( $$CY_TX_LDB )) cycles		;\
	echo Transmission of stop bit takes $$(( $$CY_TX_SB )) cycles
