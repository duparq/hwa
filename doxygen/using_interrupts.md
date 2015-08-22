
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


Interrupt Service Routine
=========================

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


Interrupt request flag and mask
===============================

Interrupt request flags can be read and cleared with the `hw_stat_irqf()` and
`hw_clear_irqf()` or `hwa_clear_irqf()` instructions.

Interrupt request masks can be read with the `hw_stat_irqe()` instruction.

Interrupt requests can be enabled and disabled with the `hw_turn_irq()` or
`hwa_turn_irq()` instructions.

<br>
