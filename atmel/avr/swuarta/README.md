
Software UART for Atmel AVRs 	{#atmelavr_swuarta}
============================

Class @ref atmelavr_swuarta "_swuarta" provides is a software UART for Atmel AVR
devices. It is used in the HWA examples so that the same code can be written,
the device having an UART or not. This is also an example of hardware
virtualization that you can achieve with HWA.

Swuarta is programmed in assembler and you'll find the source code under
`hwa/atmel/avr/swuarta/`.

In the examples, the swuart is configured to use the same I/O pins as Diabolo so
that you will not have to touch any wire between programming and executing the
example.

Class `_swuarta` implements a software UART for 1 or 2-wire communication with
automatic baudrate detection capability. It can use an 8 or 16-bit counter and
any pin that provides a pin-change interrupt.

Tested on ATtinyX4 with internal oscillator (~8 MHz):
-  1200..115200 bps with 16-bit timer not prescaled
-   450.. 50000 bps with 16-bit timer 1/8 prescaled
- 38400..115200 bps with  8-bit timer not prescaled
-         10000 bps with  8-bit timer 1/8 prescaled
