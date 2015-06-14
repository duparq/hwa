
Peripherals {#using_peripherals}
===========

All the peripheral features of a device are held by HWA objects that provide
methods to act on them.

All object names are lower cased, begin with `hw_` and end with a number:
 * `hw_counter0`
 * `hw_counter1`
 * `hw_adc0`
 * `hw_uart0`
 * ...

except i/o ports that end with a letter:
 * `hw_porta`
 * `hw_portb`
 * ...

I/O names (singles or groups of I/O pins) always begin with `hw_pin_`:
 * `hw_pin_pa0`
 * `hw_pin_pb4`
 * `hw_pin_2`
 * ...

Pins names based on pin numbers can be used when HWA knows how the device is
packaged. That should be the case if you have included a HWA header with a
full device name:

@code
#include <atmel/avr/atmega328p_au.h>  // ATmega328p in 32 pin QFP
@endcode
