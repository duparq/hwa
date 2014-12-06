
Atmel AVR ATtiny24, ATtiny44, ATtiny84 Core {#attinyx4_core}
============================================================


hw_core0
========


Sleeping Mode configuration
---------------------------

@code
hwa_config( hw_core0,

            sleepmode,   idle
                       | adc_noise_reduction
                       | power_down
                       | standby );
@endcode


Entering sleep
--------------

@code
hw_sleep_until_irq();
@endcode


Interrupts
----------

hw_core0 can trigger the following interrupt requests:

* int0
