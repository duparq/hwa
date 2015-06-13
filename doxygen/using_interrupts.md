
Interrupts {#using_interrupts}
==========

Interrupts are HWA objects that have the following specific methods:

 * HW_ISR()
 * hw_turn_irq(), hwa_turn_irq()
 * hw_clear_irq(), hwa_clear_irq()
 * hw_stat_irqe()
 * hw_stat_irqf()

An interrupt object is identified with an object name that may be followed by an
event name. For example:

 * hw_pin_pa0, change
 * hw_couner0, overflow
 * hw_couner0, compare0
 * hw_wdog0
 * hw_acmp0

@par Declaring an Interrupt Service Routine

Interrupt service routines are declared with the HW_ISR() statement:

@code
HW_ISR( hw_counter1, overflow )
{
  // code to handle the overflow of the counting register
}
@endcode

@code
HW_ISR( hw_watchdog0 )
{
  // code to handle the overflow of the watchdog timer
}
@endcode

HW_ISR() accepts two optionnal parameters:

 * `isr_interruptible` makes the ISR interruptible (the interrupts are
   re-enabled as soon as the ISR is executed);

 * `isr_naked` makes the ISR have a naked body. In that case you'll have to end
   you ISR code with the hw_reti() instruction.

For example, if you are sure that your ISR will not alter any register:

@code
HW_ISR( hw_counter0, overflow, isr_naked )
{
  hw_toggle( hw_pin_pa0 ); // will use the `sbi` instruction, no register is altered
  hw_reti();               // produce the `reti` instruction
}
@endcode


@code
  hw_turn_irq( hw_counter1, input0, on );      // Disable counter1 input capture irqs
@endcode
