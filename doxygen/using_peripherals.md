
Peripherals {#using_peripherals}
===========

All the peripheral features of a device are held by HWA objects.

All object names are lower cased, begin with `hw_` and usually end with a
number:

 * `hw_counter0`
 * `hw_counter1`
 * `hw_adc0`
 * `hw_uart0`
 * ...

except I/O ports that end with a letter:

 * `hw_porta`
 * `hw_portb`
 * ...

I/O names (singles or groups of I/O pins) always begin with `hw_pin_`:

 * `hw_pin_pa0`
 * `hw_pin_pb4`
 * `hw_pin_2`
 * ...

Pin names based on pin numbers can be used when HWA knows how the device is
packaged. That should be the case if you have included a header with a full
device name:

@code
#include <hwa/atmega328p_au.h>  // ATmega328p in 32 pin QFP
@endcode


Relatives {#relatives}
=========

Sometimes, one peripheral is implemented by a set of objects that have a
relationship. Typically, the Atmel AVR timer/counters are implemented through:

 * one counting unit
 * two compare units
 * one optionnal capture unit

The compare units and their output pins are also defined as relative objects.

The `hw_rel()` instruction gives the name of any relative object of an
object.

For example, the Atmel AVR ATmega328P has a compare output pin named OC0A that
is the output of the compare unit A of the TIM0 timer/counter. With HWA, TIM0 is
called `hw_counter0` and its first compare unit (A) is called `hw_oc00`.

 * The instruction `hw_rel( hw_counter0, compare0 )` expands to `hw_oc00`.

 * The instruction `hw_rel( hw_oc00, counter )` expands to `hw_counter0`.

 * The instruction `hw_rel( hw_oc00, pin )` expands to `hw_pin_oc0a`.

The `hw_rel()` instruction is useful to make the source code less dependant of
the affectation of the peripherals. For example, you define the symbol PWM to
hold the name of the compare unit whose output pin will produced a PWM
signal. You can configure its related objects, namely the counting unit and the
ouput pin, this way:

@code
#define PWM	hw_oc00

...

hwa_config( PWM, set_at_bottom_clear_on_match );
hwa_config( hw_rel(PWM, counter), countmode, loop_up );
hwa_write( PWM, (1U<<hw_bn(PWM))/2 ); // 50% duty cycle
@endcode

If in the future you must use `hw_oc21` instead of `hw_oc00`, you just need to
change the definition of the PWM symbol accordingly and the rest of the code
will remain unchanged.

<br>
