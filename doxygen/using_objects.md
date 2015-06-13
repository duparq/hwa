
Objects {#using_objects}
=======

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

I/O pin names always begin with `hw_pin_`:
 * `hw_pin_pa0`
 * `hw_pin_pb4`
 * `hw_pin_2`
 * ...

Pins named by their pin number can be used when HWA knows how the device is
packaged. That should be the case if you have included a HWA header with a
device name suffix:

    #include <hwa/atmega328p_au.h>  // Package 32A: 32 pin QFP

@ref using_interrupts "Interrupts" also are HWA objects that provide their
specific methods.

<br>
