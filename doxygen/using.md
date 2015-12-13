
General informations {#using}
====================

[TOC]

This section gives general informations about how to use HWA, whatever the
target device.


Device header file {#using_header}
==================

In order to use the HWA facilities, you must first include the header file
corresponding to your device:

@code
#include <hwa/attiny44a_pu.h>
@endcode

The header file is searched in the `include/` directory of HWA.

@par Configuration fuses

If your device has configuration fuses (e.g. Atmel AVR), you can set their
values through the definition of symbols prefixed with `HW_DEVICE_` __before
including the device header__. HWA sets undefined fuses with factory default
values:

@code
#define HW_DEVICE_CLK_SRC               rc_8MHz
#define HW_DEVICE_CLK_PSC               1
#define HW_DEVICE_EXTERNAL_RESET        enabled
#define HW_DEVICE_SELF_PROGRAMMING      enabled
#define HW_DEVICE_DEBUG_WIRE            disabled
#define HW_DEVICE_WATCHDOG_ALWAYS_ON    no
#define HW_DEVICE_CLOCK_OUTPUT          disabled
#define HW_DEVICE_BROWNOUT_DETECTION    2500_2900mV

#include <atmel/avr/attiny44a_pu.h>
@endcode


Instructions {#using_instructions}
============

Many HWA instructions are generic and accept an object name as first
parameter. Several instructions accept a variable length list of parameters
consisting of key/value pairs.

There are two kinds of instructions:

 * the synchronous instructions, prefixed with `hw_`;

 * the asynchronous instructions, prefixed with `hwa_`.

__Synchronous instructions__ produce an immediate result.

__Asynchronous instructions__ can only be used after a _HWA context_ has been
created with the `hwa_begin()` or `hwa_begin_from_reset()` instruction. The
action of asynchronous instructions is memorized into the context and when the
`hwa_commit()` instruction is met, HWA determines from the context the machine
code to produce.

The `hwa_nocommit()` instruction puts the context in a known state but does not
produce machine code. This is useful to make HWA produce efficient code for
modifying a configuration without rewriting all the hardware registers.

See also:

 * <a href="modules.html">Instructions sorted by category</a>

 * <a href="examples.html">The examples provided with HWA</a>


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


Relatives {#using_relatives}
---------

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


Interrupts {#using_interrupts}
==========

Interrupts are a special kind of HWA objects that are used through the following
specific methods:

 * `HW_ISR()`
 * `hw_turn_irq()`, `hwa_turn_irq()`
 * `hw_clear_irq()`, `hwa_clear_irq()`
 * `hw_stat_irqe()`
 * `hw_stat_irqf()`

An interrupt object is identified with an object name that may be followed by an
event name. For example:

 * `hw_counter0`
 * `hw_counter0, overflow`
 * `hw_counter0, compare0`
 * `hw_pin_pa0, change`
 * `hw_wdog0`
 * `hw_acmp0`


Interrupt Service Routine {#using_isr}
-------------------------

Interrupt service routines are declared with the `HW_ISR()` instruction.

For example, the USI can trigger several different interrupts, the event name is
required:

@code
HW_ISR( hw_usi0, txc )
{
  // code to handle the transmit-complete IRQ of the USI
}
@endcode

The watchdog can only trigger one "anonymous" IRQ:

@code
HW_ISR( hw_wdog0 )
{
  // code to handle the overflow of the watchdog timer
}
@endcode


`HW_ISR()` accepts a few optionnal parameters:

 * `isr_naked`
 * `isr_interruptible`
 * `isr_noninterruptible`

`isr_interruptible` and `isr_noninterruptible` tell the compiler to make the ISR
interruptible or not. Depending on the target device, these parameters may or
may not produce code. For example, `isr_noninterruptible` will not produce code
for the Atmel AVR devices since these targets automatically disable the
interrupts when an ISR is entered.

`isr_naked` makes the ISR have a naked body: the compiler will not generate any
entry or exit code (you have to provide the instruction for exiting your ISR
yourself).

For example, if you are sure that your ISR does not alter any CPU register, you
can spare a few program memory bytes and CPU cycles:

@code
HW_ISR( hw_counter0, overflow, isr_naked )
{
  hw_toggle( hw_pin_pa0 ); // will use the `sbi` instruction, no register is altered
  hw_reti();               // produce the `reti` instruction
}
@endcode


Interrupt request flag and mask {#using_isr_flags}
-------------------------------

Interrupt request flags can be read and cleared with the `hw_stat_irqf()` and
`hw_clear_irqf()` or `hwa_clear_irqf()` instructions.

Interrupt request masks can be read with the `hw_stat_irqe()` instruction.

Interrupt requests can be enabled and disabled with the `hw_turn_irq()` or
`hwa_turn_irq()` instructions.



Examples {#using_examples}
========

The <a href="examples.html">examples provided with HWA</a> page gives a list of
examples projects demonstrating the usage of HWA.
