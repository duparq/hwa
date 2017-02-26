
Software UART for Atmel AVRs
============================

Class '_swuarta' implements a software-emulated UART with the following
features:

* simplex or half-duplex communicapion over 1 or 2 wires
* frames of 1 start bit, 8 data bits, 1 stop bit (no parity bit)
* requirements:
  * one 8 or 16-bit counter compare unit
  * one pin able to trigger an interrupt when a falling edge or any
    change occurs (currently, only pin-change is implemented) for RXD
* optionnal automatic baudrate detection
* optionnal bus-collision detection

See the class documentation for more informations.
