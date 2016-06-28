
Software UART for Atmel AVRs 	{#atmelavr_swuarta}
============================

Class @ref atmelavr_swuarta "_swuarta" implements a software UART for 1 or
2-wire communication with automatic baudrate detection capability. It can use an
8 or 16-bit counter and any pin that provides a pin-change interrupt.

It is used in the HWA examples so that the same code can be written, the device
having an UART or not. This is also an example of how software-emulated hardware
can be achieved with HWA.

Swuarta is programmed in assembler, the source code is in
`hwa/atmel/avr/swuarta/`.

In the examples, the SWUART is configured to use the same I/O pins as Diabolo so
that there is no need to change anything on the hardware between programming and
executing an example.

Tested on ATtinyX4 with internal oscillator (~8 MHz):
-  1200..115200 bps with 16-bit timer not prescaled
-   450.. 50000 bps with 16-bit timer 1/8 prescaled
- 57600..115200 bps with  8-bit timer not prescaled
-         10000 bps with  8-bit timer 1/8 prescaled


Computed performances
---------------------

The following make rule displays some computed performances that help to
determine the safe working area of the SWUART and informs on how long the
interrupts are disabled:

'''
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
'''
