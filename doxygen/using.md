
Using HWA {#using}
=========

First of all, in order to use HWA, the symbol `HW_DEVICE` must be
defined with the name of the target device before `hwa.h` is included:

@code
#define HW_DEVICE	attiny44
#include <hwa.h>
@endcode

See the device-specific documentation for the `HW_DEVICE` definition to use with
each supported device.


Instructions
------------

HWA uses two kinds of instructions:

* synchronous instructions, with `hw_` prefix
* asynchronous instructions, with `hwa_` prefix

Synchronous instructions produce an immediate action.

Asynchronous instructions can only be used after an `hwa_begin()` or
`hwa_begin_from_reset()` instruction. Their action is memorized into the HWA
cache.  When the `hwa_commit()` instruction is met, HWA determines from the
content of the cache the machine code to produce.

The `hwa_nocommit()` instruction can be used to put the cache in a known state
without producing machine code. This can be used to make HWA produce code that
modifies a known configuration.

@code
#define HW_DEVICE               attiny44
#define HW_DEVICE_PACKAGE       14pdip
#include <hwa.h>

#define PIN_LED         hw_pin_7

/*  Service watchdog IRQ
 */
HW_ISR( hw_wdog0 )
{
  /*  Blink the LED
   */
  hw_toggle( PIN_LED );
}


int main ( )
{
  /*  Create a HWA context preloaded with RESET values to
   *  collect the hardware configuration
   */
  hwa_begin_from_reset();

  /*  Configure the LED pin as digital output
   */
  hwa_config( PIN_LED, direction, output );

  /*  Configure the watchdog to trigger an IRQ every 125ms
   */
  hwa_config( hw_wdog0,
              timeout,          125ms,
              action,           irq
              );

  /*  Configure the core to enter idle mode when asked to sleep
   */
  hwa_config( hw_core0,
              sleep,      enabled,
              sleep_mode, idle
              );

  /*  Write this configuration into the hardware
   */
  hwa_commit();

  /*  Enable interrupts
   */
  hw_enable_interrupts();

  /*  Sleep between interrupts
   */
  for(;;)
    hw_sleep();
    
  return 0 ;
}
@endcode



Object names
------------

Almost all instructions use an object name as first argument. All object names
are lower cased.

Object names always begin with `hw_` and always end with a number: `hw_counter1`,
`hw_uart0`, `hw_pcic2`...

Pin names always begin with `hw_pin_`: `hw_pin_pa0`, `hw_pin_pb4`...

Pin numbers (`hw_pin_1`...) can be used if `HW_DEVICE_PACKAGE` is defined:

@code
#define HW_DEVICE          attiny44
#define HW_DEVICE_PACKAGE  14pdip
@endcode

Most HWA instructions are generic and accept objects of various classes as first
parameter. This allows writing less verbose code and makes it easier to replace
an object by another, or port the code to a different target device. Several
instructions accept a variable length list of parameters consisting of key/value
pairs.


Instructions that act on hardware
--------------------------------

Synchronous           | Asynchronous        | Action
----------------------|---------------------|--------
`hw_config(...)`      | `hwa_config(...)`   | Configure an object.
`hw_clear(...)`       | `hwa_clear(...)`    | Clear an object.
`hw_read(...)`        |                     | Read an object.
`hw_read_reg(...)`    |                     | Short for `hw_read(hw_reg(...))`
`hw_atomic_read(...)` |                     | Disable interrupts while reading an object.
`hw_stat(...)`        |                     | Get the status of an object.
`hw_toggle(...)`      | `hwa_toggle(...)`   | Toggle an object (probably an output pin).
`hw_trigger(...)`     | `hwa_trigger(...)`  | Trigger an object (A/D converter, compare unit...)
`hw_turn(...)`        | `hwa_turn(...)`     | Turn on object on/off.
`hw_turn_irq(...)`    | `hwa_turn_irq(...)` | Enable/disable an IRQ.
`hw_stat_irq(...)`    |                     | Get the status of an IRQ flag.
`hw_write(...)`       | `hwa_write(...)`    | Write something into an object.
`hw_write_reg(...)`   | `hwa_write_reg(...)`| Short for `hwa_write(hw_reg(...), value)`


Instructions that do not act on hardware
---------------------------------------

HWA provides a few instructions that give informations about objects without
accessing the hardware. Most of these instructions can be used in assembler
programming.


Instruction      | Result
-----------------|--------
`hw_reg(...)`    | Definition of a register (a set of bits) of an object.
`hw_rt(...)`     | Type of one object's register (uint8_t, uint16_t...)
`hw_addr(...)`   | Address (of a register, group of bits...).
`hw_bn(...)`     | Number of bits (of a register, group of bits, counter...)
`hw_bp(...)`     | Position of least significant bit of a group of bits.
`hw_ap(...)`     | Address, position of the least significant bit (for assembler programming)
`hw_id(...)`     | Id of an object
`hw_io(...)`     | I/O name associated to an object
`hw_sub(...)`    | Sub (relative) object of an object
`hw_sup(...)`    | Parent object of an object


General purpose macros
======================

Errors
------

Macro            | Result
-----------------|--------
`HW_ERR(msg)`    | Produce an error message at preprocessing time
`HWA_ERR(msg)`   | Produce an error message after the code generation is finished


List processing
---------------

Macro                 | Result
----------------------|--------
`HW_A0(a0,...)`       | Expansion of a0
`HW_A1(a0,a1,...)`    | Expansion of a1
`HW_A2(a0,a1,a2,...)` | Expansion of a2
`HW_G2(a0,a1,...)`    | Expansions of a0 and a1 glued with a '_' between
`HW_G3(a0,a1,a2,...)` | Expansions of a0, a1, and a2 glued with a '_' between


Interrupts
==========

Interrupts are HWA objects. The definition of an interrupt is used when you need
to enable, disable or clear an interrupt request or for declaring an interrupt
service routine (ISR).

You obtain the definition of an interrupt with the instruction `hw_irq(
object [, interrupt_name] )`.

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
HW_ISR( hw_counter1, capture0 )
{
  // code to handle the capture event of Counter/Timer1
}
@endcode

@code
HW_ISR( hw_watchdog0 )
{
  // code to handle the overflow of the watchdog timer
}
@endcode

Optionnal parameter `isr_interruptible` can be added to make the ISR interruptible.

Optionnal parameter `isr_naked` can be used to have a naked body for your ISR
e.g. if you are sure that no register will be altered:

@code
HW_ISR( hw_counter0, overflow, isr_naked )
{
  hw_toggle( hw_pin_pa0 ); // will use the `sbi` instruction, no register is altered
  hw_reti();               // produce the `reti` instruction
}
@endcode

<br>
