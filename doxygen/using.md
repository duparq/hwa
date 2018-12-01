
Using HWA {#using}
=========

[TOC]

This section gives general informations about how to use HWA, whatever the
target device. Look at the @ref devices "Supported devices" page for
device-specific documentation.


Device header {#using_header}
=============

In order to use the HWA facilities, you must first include a header file
to your source:

@code
#include <hwa/attiny44a_pu.h>
@endcode

Your development tool should be configured to search the header file in the
`/include/` directory of HWA.

If your device uses configuration fuses (e.g. Atmel AVR), you __must__ set their
values __before including the device header__ otherwise factory values will be
assumed:

@code
#define HW_DEVICE_CLK_SRC		rc_8MHz
#define HW_DEVICE_CLK_PSC		1
#define HW_DEVICE_EXTERNAL_RESET	enabled
#define HW_DEVICE_SELF_PROGRAMMING	enabled
#define HW_DEVICE_DEBUG_WIRE		disabled
#define HW_DEVICE_WATCHDOG_ALWAYS_ON	no
#define HW_DEVICE_CLOCK_OUTPUT		disabled
#define HW_DEVICE_BROWNOUT_DETECTION	2500_2900mV

#include <atmel/avr/attiny44a_pu.h>
@endcode


Instructions {#using_instructions}
============

Many HWA instructions are generic: they apply on various types of objects and
accept a variable number of arguments usually consisting of key/value pairs.

The two most important instructions are `hw()` and `hwa()`. Both take an @ref
using_actions "action" as first argument and an @ref using_objects "object" as
second argument. Additional arguments may follow.


@code
hw( <ACTION>, <OBJECT> [,...] );
@endcode

`hw()` is used for synchronous actions, i.e. actions that produce an immediate
result.

`hwa()` is used for asynchronous actions. Asynchronous actions can only be used
after a _HWA context_ has been created with the `hwa_begin()` or the
`hwa_begin_from_reset()` instruction.

Once the context is created, the asynchronous actions are memorized until the
the `hwa_commit_o()` instruction or the `hwa_nocommit()` instruction is met.

The `hwa_commit()` instruction triggers the production of the machine code.

The `hwa_nocommit()` instruction does not produce machine code but is useful to
put the context in a known state usually before new actions modify it. This
allows the production of machine code that avoids writing values that already
are in the registers.

@code
hwa_begin_from_reset()
hwa( <ACTION1>, <OBJECT1> [,...] );
hwa( <ACTION2>, <OBJECT2> [,...] );
...
hwa( <ACTIONN>, <OBJECTN> [,...] );
hwa_commit();
@endcode

Using a HWA context allows the best optimization of the machine code to access
the hardware, particularly with microcontrollers that have hardware registers
shared by several peripheral controllers or logical registers spread accross two
hardware registers.

See also: <a href="modules.html">instructions sorted by category</a>.


Actions {#using_actions}
=======

Action arguments are lower-cased words.

Action	    | Comments
:-----------|:-----------
`power`	    | Power the object ON/OFF.
`configure` | Configure the object.
`write`	    | Write a value in the object.
`clear`	    | Clear the object (usually an IRQ flag).
`reset`	    | Reset the object.
`read`	    | Read the object.
`stat`	    | Read the status of the object.
`toggle`    | Toggle the state of the object (usually an I/O pin).
`trigger`   | Trigger the object (start a ADC convertion...).
`turn`	    | Turn the object ON/OFF.


Objects {#using_objects}
=======

Object arguments can be peripheral controller names or canonical I/O pin names
(i.e. the name used for the basic I/O function). They are lower cased:

 * `counter0`, `counter1`... ;
 * `uart0`, `uart1`... ;
 * `porta`, `portb`... ;
 * `pa0`...

Object arguments can also be a list of objects that provide a path to a target
object (the only way to access logical or hard registers) :

 * `(counter0,compare0)`: the compare unit #0 of the counter0;
 * `(counter0,compare0,counter)`: counter0;
 * `(counter0,count)`: the `count` register of counter0...



Interrupts {#using_interrupts}
==========

IRQs, their flags and masks are objects that can be accessed using a particular
notation:

 * `irq(counter0)` or `irq(counter0,overflow)`: the overflow IRQ of counter0;
 * `irq(counter0,compare0)`: the compare0 IRQ of counter0;
 * `irq((counter0,compare0))`: the IRQ of the compare unit #0 of counter0;
 * `irqflag(counter0)`: the flag of the counter0 overflow IRQ;
 * `irqmask(counter0)`: the mask of the counter0 overflow IRQ;

IRQs can be turned on and off.
IRQ flags can be read and cleared.

Examples:

@code
hw( clear, irqflag(counter0, overflow) );
hw( turn, irq(counter0, overflow), on );
@endcode

@code
if( hw(read, irqflag(counter0,overflow)) ) {
    hw(clear, irqflag(counter0,overflow));
    hw(toggle, LED);
}
@endcode

Interrupt service routines are declared with the `HW_ISR()` instruction:

@code
HW_ISR( watchdog0 )
{
  // code to handle the overflow of the watchdog timer
}
@endcode

As the USI `usi0` can trigger several different interrupt requests, the event
name is required:

@code
HW_ISR( usi0, txc )
{
  // code to handle the transmit-complete IRQ of the USI
}
@endcode


With some devices, `HW_ISR()` accepts the following optionnal parameters:

 * `naked`
 * `interruptible`
 * `noninterruptible`

`interruptible` and `noninterruptible` tell the compiler to make the ISR
interruptible or not. Depending on the target device, these parameters may or
may not produce code. For example, `noninterruptible` will not produce code
for the Atmel AVR devices since these targets automatically disable the
interrupts when an ISR is entered.

`naked` makes the ISR have a naked body: the compiler will not generate any
entry or exit code. That permits sparing a few program memory bytes and CPU
cycles. You then must ensure that your ISR does not alter any CPU register and
you have to provide the instruction for exiting the ISR yourself:

@code
HW_ISR( counter0, overflow, naked )
{
  hw( toggle, pa0 );    // will use the `sbi` instruction, no register is altered
  hw_asm("reti");       // produce the `reti` instruction
}
@endcode


Defining an I/O object {#using_defio}
======================

`HW_IO()` allows using hw() or hwa() to act on a set of consecutive pins of
one I/O port.

`HW_IO()` requires 3 arguments: `HW_IO( port, number, position )` where

 * `port` is the name of the port controller (`port0`, `port1`...). Notice that
   it is not the port name (`porta`, `portb`...);
 * `number` is the number of consecutive bits;
 * `position` is the position of the least significant bit.

@code
#define pins                    HW_IO(port0,4,3)        // Pins 6,5,4,3 of port0

hw( configure, pins, mode, digital_output );            // Sets pins 6..4 as outputs
hw( write, pins, 5 );                                   // Sets pins 5 & 3, clears pins 6 & 4.
@endcode


Pin configuration {#using_cfpin}
=================

HWA tries to provide a syntax that is as independent as possible from the target
device and consistent accross various peripheral controllers.

For the configuration of the device's pins, we'll try to apply the following.

`function` can be:
 * gpio
 * (CONTROLLER,SIGNAL)

`function` tells the function of the pin (or the signal that drives the
pin). This can be a digital I/O, one signal of a peripheral controller, such as
(uart0,tx), (counter0,clock)... If `function` is not specified, `gpio` is
assumed.


`mode` tells how the pin behaves, electrically:

 * AVR
    *  digital_input | digital_input_floating
    *  digital_input_pullup
    *  digital_output | digital_output_pushpull
    *  analog_input
    *  analog_input_floating
    *  analog_input_pullup

 * STM32
    *  digital_input | digital_input_floating
    *  digital_input_pullup
    *  digital_input_pulldown
    *  digital_output | digital_output_pushpull
    *  digital_output_opendrain
    *  analog_input

 * ESP8266:
    *  digital_input | digital_input_floating
    *  digital_input_pullup
    *  digital_input_pullup_when_awake
    *  digital_output | digital_output_pushpull
    *  digital_output_when_awake | digital_output_pushpull_when_awake
    *  analog_input
 

@code
hw( configure, pin,
    function,  gpio,
    mode,      output_push_pull );
@endcode


@code
hw( configure, pin,
    function,  (uart0,rxd) );
@endcode



Examples {#using_examples}
========

See the <a href="examples.html">Examples</a> page for a list of examples
projects that demonstrate the usage of HWA.

<br>
