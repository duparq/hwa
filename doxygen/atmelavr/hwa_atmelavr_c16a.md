
Atmel AVR  ATtiny24, ATtiny44, ATtiny84Timer/Counter1 {#atmelavr_c16a}
==============

hw_counter1
===========

Supported operations
--------------------

Operation                           | Result
------------------------------------|--------------
hw_bn( hw_counter1 )                | 16
`hw_sub( hw_counter1, output0..1 )` | Definition of an output (OC0A, OC0B)
hw_read( hw_counter1 )              | Value of the `count` register
hw/hwa_write( hw_counter1, value )  | Write `value` into the `count` register
hwa_config( hw_counter1, ... )      | Configure the counter


Configuration
-------------

~~~~~~~~~~~~~~~{.c}
hwa_config( hw_counter1,

            countmode,     loop_up
                         | loop_updown,

          [ bottom,       0, ]

            top,           fixed_0xFF
                         | fixed_0x1FF,
                         | fixed_0x3FF,
                         | fixed_0xFFFF,
                         | register_capture,
                         | register_compare_a,

            clock,         syshz
                         | syshz_div_8
                         | syshz_div_64
                         | syshz_div_256
                         | syshz_div_1024
                         | ext_falling
                         | ext_rising,

          [ overflow,      at_bottom
                         | at_top
                         | at_max, ]


          [ update,        at_bottom
                         | at_top
                         | at_max ]
          );
~~~~~~~~~~~~~~~


Power Management
----------------

`hw_counter1` can be turned off to reduce power consumption of the device:

@code
hw/hwa_turn( hw_counter1, on | off );
@endcode


hw_counter1 output units
========================

hw_counter1 has two compare-output units:

* `hw_counter1_output0` and
* `hw_counter1_output1`

corresponding to OC0A and OC0B in the Atmel terminology.


Supported operations
--------------------

Operation                          | Result
-----------------------------------|--------------
hw_bn( hw_counter1 )               | 8
hw_sub( hw_counter1, output0..1 )  | Definition of output compare A or B
hw_read( hw_counter1 )             | Value of the `count` register
hw/hwa_write( hw_counter1, value ) | Write `value` into the `count` register


Configuration
-------------
