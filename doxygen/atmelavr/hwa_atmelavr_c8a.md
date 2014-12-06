
Atmel AVR 8-bit Timer/Counter with 2 PWM outputs: class c8a  {#atmelavr_c8a}
===========================================================

Class c8a implements an 8-bit counter/timer with two comparison units with
outputs. It is used in the following devices:

* @ref attinyx4 "ATtiny24, ATtiny44, ATtiny84": `hw_counter0`

The comparison units are named `output0` and `output1` and correspond with
output pins named OCxA and OCxB in the Atmel terminology.

In the text below, the counter is referenced as `COUNTER`, each comparison unit
as `OUTPUT`.

Non-hardware operations          | Result
---------------------------------|--------------
`hw_bn( COUNTER )`               | 8
`hw_sub( COUNTER, output0/1 )`   | Definition of the output0/1 comparison unit
`hw_sup( OUTPUT )`               | Definition of the parent counter
`hw_io( OUTPUT )`                | Definition of the I/O pin


Configuring the counting unit
=============================

@code
hwa_config( COUNTER,

            countmode,     loop_up
                         | loop_updown,

          [ bottom,        0, ]

            top,           fixed_0xFF
                         | reg_output0,         // Top value is stored in the output0 register

            clock,         syshz                // Internal clocking
                         | syshz_div_1
                         | syshz_div_8
                         | syshz_div_64
                         | syshz_div_256
                         | syshz_div_1024
                         | ext_falling          // External clocking
                         | ext_rising,

          [ overflow,      at_bottom
                         | at_top
                         | at_max, ]

          [ update,        immediately
                         | at_bottom
                         | at_top ]
          );
@endcode

Optionnal parameters `overflow` and `update` are determined or checked by
HWA according to the configuration of the comparison units.


Reading/Writing the `COUNT` register
====================================

Class c8a supports read/write instructions:

@code
hw_read( COUNTER );
@endcode

@code
hw/hwa_write( COUNTER, value );
@endcode

Alternatively, you can also use read/write instructions for registers:

@code
hw_read( hw_reg(COUNTER, count) );
@endcode

@code
hw_read_reg( COUNTER, count );
@endcode


Configuring the comparison units
================================

@code
hw/hwa_config( OUTPUT,   disconnected
                       | toggle_on_match
                       | clear_on_match
                       | set_on_match
                       | set_at_bottom_clear_on_match
                       | clear_at_bottom_set_on_match
                       | clear_on_match_up_set_on_match_down
                       | set_on_match_up_clear_on_match_down
             );
@endcode


Reading/Writing the comparison register
=======================================

@code
hw_read( OUTPUT );
@endcode

@code
hw/hwa_write( OUTPUT, value );
@endcode


Forcing a compare-match
=======================

@code
hw_trigger( OUTPUT );
@endcode


Interrupts
==========

Class c8a can trigger the following interrupt requests:

* overflow
* output0
* output1
