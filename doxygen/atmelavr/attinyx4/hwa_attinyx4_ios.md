
Digital I/O {#attinyx4_ios}
===========

I/O Names
=========

I/O name        | Description
----------------|-------------------------
hw_port_a	| Port A
hw_pin_pa0	| Pin PA0
hw_pin_pa1	| Pin PA1
hw_pin_pa2	| Pin PA2
hw_pin_pa3	| Pin PA3
hw_pin_pa4	| Pin PA4
hw_pin_pa5	| Pin PA5
hw_pin_pa6	| Pin PA6
hw_pin_pa7	| Pin PA7
hw_port_b	| Port B
hw_pin_pb0	| Pin PB0
hw_pin_pb1	| Pin PB1
hw_pin_pb2	| Pin PB2
hw_pin_pb3	| Pin PB3

Pin numbers `hw_pin_2` to `hw_pin_13` can also be used if `HW_DEVICE` has 'dil'
as second argument.


Configure
=========

Use the `hw_config(...)` or `hwa_config(...)` instructions to configure an I/O:

@code
hw/hwa_config( io,   input
                   | input_pullup
                   | input_nopullup
                   | pullup           // enable pullup
                   | nopullup         // disable pullup
                   | output
              );
@endcode

Not available yet:
@code
hw/hwa_config( io, 

               direction,   input
                          | output,

               pullup,      on
                          | off,
              );
@endcode


Read
====

@code
foo = hw_read( io );
@endcode


Write
=====

@code
hw/hwa_write( io, value );
@endcode


Port of a pin
=============

@code
hw_sup( hw_pin_pa0 ) // equivalent to hw_port_a
@endcode


Number of bits
==============

@code
hw_bn( hw_port_b ) // 4
@endcode


Position of least significant bit
=================================

@code
hw_bp( hw_pin_pa4 ) // 4
@endcode


I/O definition
==============

@code
hw_io( hw_pin_pb3 ) // equivalent to hw_pin_pb3!
@endcode


Defining a group of bits
========================

@code
/*    New group of pins         class, name, id, controller, bn, bp
 */
#define hw_pin_pa4pa5pa6        io, pin_pa4pa5pa6, 0, hw_porta, 3, 4
@endcode
