
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

`hw()` is used for synchronous actions, i.e. actions that produce an immediate
result.

`hwa()` is used for asynchronous actions. Asynchronous actions can only be used
after a _HWA context_ has been created with the `hwa_begin()` or the
`hwa_begin_from_reset()` instruction.

The following asynchronous actions are then memorized into the context until the
the `hwa_commit()` instruction or the `hwa_nocommit()` instruction is met.

The `hwa_commit()` instruction triggers the production of the machine code.

The `hwa_nocommit()` instruction does not produce machine code but is useful to
put the context in a known state usually before following actions modify
it. This allows the production of machine code that avoids writing values that
already are in the registers.

Using a HWA context allows the best optimization of the machine code to
access the hardware, particularly with microcontrollers that have hardware
registers shared by several peripheral controllers.

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

 * `counter0`, `counter1` ;
 * `adc0` ;
 * `uart0` ;
 * `porta`, `portb` ;
 * `pa0`...

Instructions that return objects names (`HW_RELATIVE()`, `HW_PIN()`) or those
that return object definitions (`HW_IRQ()`, `HW_IRQFLAG()`, `HW_REGISTER()`) can
be used as object arguments too.


Interrupts {#using_interrupts}
==========

Interrupts are objects returned by the `HW_IRQ(...)` instruction. The first
argument must be an object name, the optionnal second argument must be an event
name:

 * `HW_IRQ(watchdog0)`;
 * `HW_IRQ(counter0)`;
 * `HW_IRQ(counter0, overflow)`;
 * `HW_IRQ(counter0, compare0)`;
 * `HW_IRQ(pa0, change)`;
 * ...

Interrupts can be enabled and disabled with the `turn` action:

@code
hw( turn, HW_IRQ(counter0, overflow), on );     // Enable counter0 overflow interrupts
@endcode

@code
hw( turn, HW_IRQ(counter0, overflow), off );    // Disable counter0 overflow interrupts
@endcode


The `HW_IRQFLAG(...)` instruction can be used to acces an interrupt flag. The
arguments are the same as for `HW_IRQ(...)`.

IRQ flags can be read and cleared:

@code
if( hw(read, HW_IRQFLAG(counter0,overflow)) )
    hw(toggle, LED);
@endcode

@code
hw(clear, HW_IRQFLAG(counter0,overflow));
@endcode


Interrupt service routines are declared with the `HW_ISR()` instruction,
using the same arguments as for `HW_IRQ()`:

@code
HW_ISR( watchdog0 )
{
  // code to handle the overflow of the watchdog timer
}
@endcode

As the USI can trigger several different interrupt requests, the event name is
required:

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



Examples {#using_examples}
========

See the <a href="examples.html">Examples</a> page for a list of examples
projects that demonstrate the usage of HWA.
