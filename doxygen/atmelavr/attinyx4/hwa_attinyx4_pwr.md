
Atmel ATtiny24 ATtiny44 ATtiny84 Power Management {#attinyx4_pwr}
=================================================

A few controllers can be turned on/off to manage power consumption of the device by
using the `hw/hwa_turn(...)` instruction:

These controllers are:
* `hw_counter0`
* `hw_counter1`
* `hw_usi0`
* `hw_adc0`

Examples:

@code
hwa_begin();
...
hwa_turn( hw_counter0, on );	// Power-on TIMER/COUNTER0
...
hwa_commit();
@endcode

@code
hw_turn( hw_usi0, off );	// Power-off USI
@endcode
