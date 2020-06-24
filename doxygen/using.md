
Using HWA {#using}
=========

[TOC]

This section gives general informations about how to use HWA, whatever the
target device. Look at the "Modules" for device-specific documentation.

Reserved symbols   {#using_symbols}
================

HWA defines a lot of symbols, all beginning with one of these:
 * `hw_...`, `_hw_...`, 
 * `HW_...`, `_HW_...`,
 * `hwa_...`, `_hwa_...`,
 * `HWA_...`, `_HWA_...`

plus: `hw`, `_hw`, `HW`, `hwa`, `_hwa`.


Header file {#using_header}
===========

In order to use the HWA facilities, you must include the header file
that describes your target device to your source:

@code
#include <hwa/attiny44a_pu.h>
@endcode

This assumes that your compiler is configured to look for header files in the
`/include/` directory of HWA.

If your device uses configuration fuses (e.g. Atmel AVR), you should set their
values __before including the header__. If you do not, factory values will be
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

For Atmel AVR devices, HWA uses the fuses' values to define the symbol
`HW_SYSHZ` as the frequency of the CPU clock. These values are also used by the
example projects to drive the compilation and the bootloader. Have a look at the
Makefiles to see how this works.


Instructions {#using_instructions}
============

Many HWA instructions are generic: they apply @ref using_actions "actions" on
various types of @ref using_objects "objects" and accept a variable number of
arguments, mandatory or optionnal, often organized as key/value pairs.

The two mostly used instructions are `hw()` and `hwa()`. Both take an action as
first argument and an object as second argument. Additional arguments may
follow.

`hw( ACTION, OBJECT, ... )` produces an immediate result.

@code
hw( trigger, adc0 );	// Start ADC0 conversion
@endcode

`hwa( ACTION, OBJECT, ... )` records actions in a _context_ that must have been
created previously with `hwa(begin)` or `hwa(begin,reset)`, the latter loading
the context with the state of the hardware as it is after a hard reset.

The execution of the recorded actions is triggered by `hwa(commit)`. Using a
context can lead to a better optimization of the code produced since it allows
HWA to reduce the number of accesses to the hardware registers. You'll get an
error if you record contradictory actions.

@code
hwa( begin, reset );                            // Create a context, load reset state
hwa( configure, (porta,2), mode, output );      // Configure PA2
hwa( configure, (porta,4,4), mode, output );    // Configure PA7,PA6,PA5,PA4
hwa( commit );                                  // Do it now
@endcode

`hwa(nocommit)` does nothing but leave the context in a known state before
recording new actions. That way, HWA produces the code that reflects the changes
to the hardware between `hwa(nocommit)` and `hwa(commit)`. See the example
project `atmel/avr/examples/02-3-blink-watchdog-irq-reset/` for an illustration.

See also: <a href="modules.html">instructions sorted by category</a>.


Actions {#using_actions}
=======

Actions are lower-cased words:
 * `power`
 * `turn`
 * `configure`
 * `write`
 * `read`
 * `read_atomic`
 * `stat`
 * `toggle`
 * `trigger`
 * `clear`
 * `reset`
 * `enable`
 * `disable`
 * ...

Objects {#using_objects}
=======

Object names are based on manufacturers' but using lower case:
 * `porta`, `portb`... ;
 * `counter0`, `counter1`... (timers are named `counter` because they become
   timers only when connected to a clock of known frequency);
 * `uart0`, `uart1`...

Objects can be designated using a _path_, between parentheses:
 * `(counter0,compare0)`: the compare unit #0 attached to counter0;
 * `(counter0,compare0,counter)`: equals `counter0`;
 * `(counter0,count)`: the `count` register of counter0;
 * `(counter0,irq)`: the IRQ object of counter0;
 * `((portb,1,0),port)`: GPIO port of pin PB0, equals `portb`;
 * `(portb,pcic)`: pin-change interrupt controller of portb
 * ...

HWA can drive external controllers, using a constructor:
 * @ref pcf8574 "PCF8574": `HW_PCF8574( interface, twi0, address, 0x27 )`
 * @ref hd44780 "HD44780": `HW_HD44780( lines, 2, cols, 16, e, pc2, rs, pc0, rw, pc1, data, (port2,4,4) )`


I/Os {#using_ios}
====

I/Os such as PA2, PB4... can be designated using a _path_ made of a GPIO port
name, the number of consecutive pins (assumed to be 1 if ommitted), and the
lowest pin number:
 * `(porta,2)` or `(porta,1,2)`: aka PA2;
 * `(portb,4,2)`: pins PB5,PB4,PB4,PB2.

I/Os can also be designated using the `(pin,...)` notation:
 * `(pin,2)`: pin number 2 (pin numbers are defined if the package of the device
   is known);
 * `(pin,adc0)`: pin named ADC0. Note that `adc0` would designate an ADC converter.

External controllers can give access to their I/Os using the same notation as
with GPIO ports. You can then drive their I/Os using the same instructions as
for internal GPIO ports:

@code
#define PCF             HW_PCF8574( interface, twi0, address, 0x27 )
#define PINS            (PCF,4,2)

hw( write, PINS, 5 );   // Sets pins 4 & 2, clears pins 5 & 3 of PCF
@endcode


Configuring GPIOs
-----------------

GPIOs are configured with the `configure` action. GPIOs can support multiple
functions and modes, hence the parameters:
 * `function`: to indicate the function;
 * `mode`: to indicate the electrical behavior.

@code
hw( configure, pin,
    function,  gpio,                    // Optionnal, `gpio` is the default value
    mode,      output_push_pull );
@endcode

The optionnal `function` parameter indicates the function of the pin:
 * `gpio`: the pin acts as a GPIO pin (assumed by default if the `function`
   parameter is ommitted);
 * `(CONTROLLER,SIGNAL)`: the pin is driven by an internal peripheral controller
   signal:
   * `(uart0,txd)`: TXD signal of uart0
   * `(counter0,clock)`: clock input of counter0
   * ...

@code
hwa( begin, reset );
hwa( configure, gpio15, function, (uart0,txd) );        // Remap pins of ESP8266 UART
hwa( configure, gpio13, function, (uart0,rxd) );        //
hwa( commit );
@endcode

The `mode` parameter tells how, electrically, the pin behaves. It may be
mandatory or forbidden depending on the `function` of the pin. Typical values
are:
    *  `analog_input`
    *  `analog_input_floating`
    *  `analog_input_pullup`
    *  `digital_input` | `digital_input_floating`
    *  `digital_input_pullup`
    *  `digital_input_pullup_when_awake`
    *  `digital_input_pulldown`
    *  `digital_output` | `digital_output_pushpull`
    *  `digital_output_when_awake` | `digital_output_pushpull_when_awake`
    *  `digital_output_opendrain`


Read, write, toggle
-------------------

@code
uint8_t code = hw( read, (portb,4,4) );   // Put PB7:PB4 in bits 3:0 of code
@endcode

@code
hwa(begin);
hwa(write, (portb,2,4), 2 );    // Record PB5,PB4 = 1,0
hwa(write, (portb,2,6), 1 );    // Record PB7,PB6 = 0,1
hwa(commit);                    // Do it now
hwa(write, (portb,2,6), 2 );    // Record PB7,PB6 = 1,0
hwa(commit);                    // Do it now
@endcode

@code
hw( toggle, (portb,2,2) );      // Toggle PB3 and PB2
@endcode


Interrupts {#using_interrupts}
==========

IRQs, their flags and masks are objects that can be accessed using the `irq`
element in a path:

 * `(counter0,irq)`: the IRQ triggered by counter0;
 * `(counter0,irq,overflow)`: the IRQ triggered by counter0 when it overflows;
 * `(counter0,compare0,irq)`: the IRQ of the compare unit #0 of counter0;

Available actions for IRQs are:

 * `enable`: allows the IRQ to be triggered;
 * `disable`: prevents the IRQ to be triggered;
 * `read`: returns the status of the IRQ flag;
 * `clear`: clears the IRQ flag.

@code
hw( clear, (counter0,overflow,irq) );   // Clear IRQ flag
hw( enable, (counter0,overflow,irq) );  // Enable IRQ
@endcode

@code
if( hw(read, (counter0,irq,overflow) ) ) {
    hw(clear, (counter0,irq,overflow) );
    hw(toggle, LED);
}
@endcode

Interrupt service routines are declared with the `HW_ISR()` instruction:

@code
HW_ISR( (watchdog0,irq) )
{
  // code to handle the overflow of the watchdog timer
}
@endcode

For a controller that can trigger several different interrupt requests, an event
name is required:

@code
HW_ISR( (usi0,irq,txc) )
{
  // code to handle the transmit-complete IRQ of the USI
}
@endcode


With some target devices and some compilers (only tested with GNU gcc for the
moment), `HW_ISR()` accepts the following optionnal parameters:

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
cycles. If you use this, you must ensure that your ISR does not alter any CPU
register and you must provide the instruction for exiting the ISR yourself:

@code
HW_ISR( (counter0,irq,overflow), naked )
{
  hw( toggle, pa0 );    // Will use the `sbi` instruction, no register is altered
  hw_asm("reti");       // Produce the `reti` instruction
}
@endcode


Interrupts can be globally enabled or disabled:

@code
hw( enable, interrupts );
@endcode

@code
hw( disable, interrupts );
@endcode


Registers {#using_registers}
=========

HWA gives access to the registers of the MCU through a path that start with the
name of the object that holds the register.
 * hardware registers are bytes or words defined by the MCU vendor;
 * logical registers are one or two sets of consecutive bits inside one or two
   hardware registers that have a semantical meaning.
   
Both hardware and logical registers are managed by the same instructions hw(...)
and hwa(...) with actions `read`, `write`, `set`, `clear`.

The following sets the values of the WGM bits of the 8-bit timer/counter0 of an
Atmel ATmega328. These bits are spread over two hardware registers: TCCR0A holds
bits 0 and 1 in position 0 and 1, and TCCR0B holds bit 2 in position:

@code
hw( write, (counter0,wgm), 5 );
@endcode

Note that using hwa() instructions optimizes the resulting binary code since the
accesses to hardware registers will be combined.


Useful macros {#using_macros}
=============

These macros can be used in assembly language.

`HW_ADDRESS(OBJECT_PATH)` returns the address of an object or -1 if the object does not exist. This can be used to compare objects.

`HW_BITS(OBJECT_PATH)` returns the number of bits of an object (I/Os, counter, register...) or 0 if the object does not exist.

`HW_POSITION(OBJECT_PATH)` returns the position of an object (I/Os, register...) or 0 if the object does not exist.


Examples {#using_examples}
========

The <a href="examples.html">Examples</a> page gives links to example projects
that demonstrate the usage of HWA.
