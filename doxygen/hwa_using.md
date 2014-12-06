
Using HWA {#using}
=========

In order to use the HWA facilities, the symbol `HW_DEVICE` must first be defined
with the target's name and then hwa.h must be included.

@code
#define HW_DEVICE	attiny44
#include <hwa.h>
@endcode

The @ref devices page gives the `HW_DEVICE` definition to use for each
supported device.


Instructions
============

HWA uses two kinds of instructions:

* synchronous instructions, with `hw_` prefix
* asynchronous instructions, with `hwa_` prefix

Synchronous instruction produce an immediate action.

Asynchronous instructions can only be used after an `hwa_begin()` or
`hwa_begin_from_reset()` instruction. Their action is deferred. When an
`hwa_commit()` or `hwa_nocommit()` instruction is met, HWA determines the values
to write into registers from the asynchronous it encountered and thus produces
the best possible machine code.


Object names
------------

Almost all instructions use an object name as first argument. All object names
are lower cased.

Object names always begin with `hw_` and always end with a number: `hw_counter1`,
`hw_uart0`, `hw_pcic2`...

Pin names always begin with `hw_pin_` or `hw_port_`: `hw_pin_pa0`, `hw_pin_pb4`,
`hw_pin_1`, `hw_port_a`...

Pin numbers can be used if `HW_DEVICE` also defines the package of
the device:

@code
#define HW_DEVICE	attiny44, dil
@endcode

Most HWA instructions are generic and accept various class objects as first
parameter. This allows writing less verbose code that is also easier to port
between different controllers or different devices. Several instructions accept
a variable length list of parameters consisting of key/value pairs.


Instructions that act on hardware
--------------------------------

Synchronous           | Asynchronous        | Action
----------------------|---------------------|--------
`hw_config(...)`      | `hwa_config(...)`   | Configure something
`hw_clear(...)`       | `hwa_clear(...)`    | Clear something: a prescaler, an interrupt flag...
`hw_read(...)`        |                     | Read something: a controller, a pin...
`hw_read_reg(...)`    |                     | Short for `hw_read(hw_reg(...))`
`hw_atomic_read(...)` |                     | Disable interrupts while reading something
`hw_status(...)`      |                     | Get the status of a controller
`hw_release(...)`     | `hwa_release(...)`  | Release something: a prescaler...
`hw_toggle(...)`      | `hwa_toggle(...)`   | Toggle something: an output pin...
`hw_trigger(...)`     | `hwa_trigger(...)`  | Trigger something: an ADC conversion, a PWM output...
`hw_turn(...)`        | `hwa_turn(...)`     | Turn something on/off: a controller, an IRQ...
`hw_turn_irq(...)`    | `hwa_turn_irq(...)` | Enable/disable an IRQ
`hw_write(...)`       | `hwa_write(...)`    | Write something: into a controller, a register, an output pin...
`hw_write_reg(...)`   | `hwa_write_reg(...)`| Short for `hwa_write(hw_reg(...), value)`


Instructions that do not act on hardware
---------------------------------------

HWA provides a few instructions that give informations about objects without
accessing the hardware. These instructions can be used in assembler programming.


Instruction      | Result
-----------------|--------
`hw_addr(...)`   | Address of a register, a group of bits...
`hw_ap(...)`     | Address, position of the least significant bit (for assembler programming)
`hw_reg(...)`    | Register of a controller
`hw_bn(...)`     | Number of bits of a register, group of bits, counter...
`hw_bp(...)`     | Position of least significant bit of a group of bits
`hw_id(...)`     | Id of an object
`hw_io(...)`     | I/O associated to something
`hw_name(...)`   | Name of an object
`hw_sub(...)`    | Sub controller of an object
`hw_sup(...)`    | Parent controller of an object


General purpose macros
----------------------

Errors
------

Macro            | Result
-----------------|--------
`HW_ERR(msg)`    | An error message at preprocessing time
`HWA_ERR(msg)`   | An error message after the code generation is finished


List processing
---------------

Macro        | Result
------------ |--------
`HW_A0(...)` | The first argument (after expansion)
`HW_A1(...)` | The second argument (after expansion)
`HW_A2(...)` | The third argument (after expansion)
`HW_G2(...)` | The first two arguments glued with a '_' between (after expansion)
`HW_G3(...)` | The first three arguments glued with a '_' between (after expansion)


Interrupts
==========

Interrupts are HWA objects. The definition of an interrupt is used when you need
to enable/disable an interrupt request or for declaring an interrupt service
routine (ISR).

You obtain the definition of an interrupt with the instruction `hw_irq(
controller [, interrupt_name] )`.

Use the `hw/hwa_turn(...)` or `hw/hwa_turn_irq(...)` instruction to
enable/disable an interrupt request:

@code
foo()
{
  hwa_begin();
  hwa_turn( hw_irq(hw_counter1, overflow), on ); // Enable counter1 overflow irqs
  hwa_turn_irq( hw_counter1, input0, off );      // Disable counter1 input capture irqs
  hwa_commit();
}
@endcode

Interrupt service routines are declared with the `HW_ISR( hw_irq(...) )` statement:

@code
HW_ISR( hw_irq( hw_counter1, overflow ) )
{
  // code to handle the overflow of the counting register
}
@endcode

The `HW_ISR(...)` macro also accepts that you provide the parameters of
`hw_irq(...)` directly:

@code
HW_ISR( hw_counter1, input0 )
{
  // code to handle the input capture event of Counter/Timer1
}
@endcode

@code
HW_ISR( hw_watchdog0 )
{
  // code to handle the overflow of the watchdog timer
}
@endcode

Optionnal parameter `interruptible` can be added to make the ISR interruptible.

Optionnal parameter `naked` can be used to have a naked body for your ISR
e.g. if you are sure that no register will be altered:

@code
HW_ISR( hw_counter0, overflow, naked )
{
  hw_toggle( hw_pin_pa0 ); // will use the `sbi` instruction, no register is altered
  hw_reti();               // produce the `reti` instruction
}
@endcode


See also
========

* @subpage examples
* @subpage devices
