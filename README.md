
HWA
===

HWA is a set of C definitions designed to help developers write hardware-related
code that:

 * is pleasant to read and write,
 * produces efficient binary code,
 * is easier to port to a different target.

To achieve these goals, HWA provides:

 * a set of objects that represent the hardware,
 * one single object-oriented generic instruction, `hw(...)`, that can act on
   all hardware objects and accepts various types and various numbers of
   mandatory and optionnal arguments, putting the focus on the expected result
   rather than on the values to be written in registers,
 * a transactional processing mechanism with the `hwa(...)` instruction that
   allows further optimization of the binary code produced,
 * an error-checking mechanism that tries to produce messages that help the
   developer solve the problems.


Performances and compatibility
==============================

Because it is not a library, using HWA does not affect negatively the efficiency
of the binary code produced either in terms of size, execution speed, or memory
used. HWA helps the compiler's optimizers produce a binary that is as efficient
as if the developer had written smart accesses to hardware registers himself.

HWA relies heavily on macro definitions to implement object-oriented generic
instructions. As the C preprocessor can be used to parse assembly language code,
a few features of HWA can be used for assembly programming. The implementation
of a [software UART for Atmel AVR microcontrollers](atmelavr_swuarta.html) (see
`atmel/avr/swuarta/`) and the [Diabolo bootloader](atmelavr_diabolo.html) (see
`atmel/avr/examples/diabolo`) are examples of such a usage.

Any C compiler compatible with the
[C11](https://en.wikipedia.org/wiki/C11_%28C_standard_revision%29) standard
should be able to compile HWA code.


Examples
========

A [set of commented examples](http://duparq.free.fr/hwa/examples.html) is
provided. You'll find example projects in each `vendor/architecture/examples/`
directory (e.g. `atmel/avr/examples/`) where a `README.md` file that explains
how to compile the projects.

As an appetizer, the following code blinks a LED connected to an Atmel AVR ATtiny44 using
watchdog interrupts and sleep mode (machine code size: 94 bytes):

    #include <hwa/attiny44a_pu.h>   // Load HWA definitions for the target MCU

    #define PIN_LED      HW_PIN(7)

    HW_ISR( watchdog0 )             // Service watchdog IRQ
    {
      hw( toggle, PIN_LED );
    }


    int main ( )
    {
      hwa( begin_from_reset );      // Create a HWA context to record the configuration

      hwa( configure, PIN_LED, mode, digital_output );

      hwa( configure, watchdog0,    // Have the watchdog trigger an IRQ every 250 ms
           timeout,   250ms,
           action,    irq );

      hwa( configure,  core0,       // Put the MCU in idle mode when sleeping
           sleep,      enabled,
           sleep_mode, idle );

      hwa( commit );                // Execute the configuration

      hw( enable_interrupts );

      for(;;)
        hw( sleep_until_irq );      // Put the MCU in sleep mode between interrupts

      return 0 ;
    }


Documentation
=============

A ready-made documentation is available
[here](http://duparq.free.fr/hwa/index.html). Start with the [Using
HWA](http://duparq.free.fr/hwa/using.html) page.

Building your own copy of the documentation from the sources requires
[Doxygen](http://www.stack.nl/~dimitri/doxygen/) and Gnu Make. Run `make` in the
HWA directory, then open the `doxygen/html/index.html` page.


Supported devices
=================

 * HWA supports almost fully:
   * Atmel AVR:
     * [ATtinyX4](http://duparq.free.fr/hwa/attinyx4.html): ATtiny24, ATtiny24A, ATtiny44, ATtiny44A, ATtiny84, ATtiny84A
     * [ATtinyX5](http://duparq.free.fr/hwa/attinyx5.html): ATtiny25, ATtiny45, ATtiny85,
     * [ATmegaX8](http://duparq.free.fr/hwa/atmegax8.html): ATmega328P

 * Very partially supported:
   * Atmel AVR:
     * [ATmega32U4](http://duparq.free.fr/hwa/atmegaxu4.html): ATmega32U4 needs probably a few updates
   * ST STM32:
     * [STM32F103](http://duparq.free.fr/hwa/stm32f103.html): STM32F103C8T6, STM32F103RBT6, STM32F103VCT6
   * Espressif
     * [ESP8266](http://duparq.free.fr/hwa/esp8266.html): ESP8266

 * Support for a few "external" devices has been started:
   * [HD44780](http://duparq.free.fr/hwa/hd44780.html) LCD driver
   * [PCF8574](http://duparq.free.fr/hwa/pcf8574.html) I²C expander
   * [TCS3200](http://duparq.free.fr/hwa/tcs3200.html) colour detector


Organization of the code
========================

The base source code of HWA is in the `hwa/` directory.

Device-related sources are stored in `vendor/architecture/` directories
(`atmel/avr/`, `st/stm32/`, `espressif/esp8266/`, ...) where are stored
`classes/`, `devices/`, and `examples/` directories.


Status
======

__WARNING!__ The development of HWA is very chaotic and this project is subject
to heavy changes of the code base.


Hosting, feedback
=================

HWA is hosted on [Github](http://github.com/duparq/hwa).

Feedbacks will be greatly appreciated. For any bug report, question or
suggestion, please open a new issue on [Github](http://github.com/duparq/hwa),
or use my gmail address (duparq) and put HWA in the object.


License
=======

HWA is free software. See the [license](http://duparq.free.fr/hwa/license.html) page for license information.
