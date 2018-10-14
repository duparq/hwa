
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

Because it is not a library, using HWA does not affect negatively the efficiency
of the binary code produced either in terms of size, execution speed, or memory
used. HWA helps the compiler's optimizers produce a binary that is at least as
efficient as if the developer had written smart accesses to hardware registers
himself.

HWA relies heavily on macro definitions to implement object-oriented generic
instructions. As the C preprocessor can be used to parse assembly language code,
a few features of HWA can be used for assembly programming. The implementation
of a [software UART for Atmel AVR microcontrollers](atmelavr_swuarta.html) (see
`atmel/avr/swuarta/`) and the [Diabolo bootloader](atmelavr_diabolo.html) (see
`atmel/avr/examples/diabolo`) are examples of such a usage.

Any C compiler compatible with the
[C11](https://en.wikipedia.org/wiki/C11_%28C_standard_revision%29) standard
should be able to compile the source code.


Examples
========

Several example projects are provided in the `vendor/architecture/examples/`
directories (e.g. `atmel/avr/examples/`).

Each `examples/` directory contains a `README.md` file that explains how to
compile the examples.

Here is an example of how to use a watchdog interrupt to make a LED blink with
an Atmel AVR ATtiny44A-PU:


    //  Load HWA definitions for the target device
    //
    #include <hwa/attiny44a_pu.h>


    //  We can use pin numbers as the device name tells HWA the package
    //
    #define PIN_LED      HW_PIN(7)


    //  Service watchdog IRQ
    //
    HW_ISR( watchdog0 )
    {
      //  Blink the LED
      //
      hw( toggle, PIN_LED );
    }


    int main ( )
    {
      //  Create a HWA context preloaded with RESET values to
      //  collect the hardware configuration
      //
      hwa_begin_from_reset();

      //  Configure the LED pin
      //
      hwa( configure, PIN_LED, mode, digital_output );

      //  Configure the watchdog to trigger an IRQ every 250ms
      //
      hwa( configure, watchdog0,
           timeout,   250ms,
           action,    irq );

      //  Configure the core to enter idle mode when asked to sleep
      //
      hwa( configure,  core0,
           sleep,      enabled,
           sleep_mode, idle );

      //  Write this configuration into the hardware
      //
      hwa_commit();

      //  Enable interrupts
      //
      hw_enable_interrupts();

      //  Sleep between interrupts
      //
      for(;;)
        hw_sleep_until_irq();

      return 0 ;
    }


Documentation
=============

A ready-made documentation is available
[here](http://duparq.free.fr/hwa/index.html). Start with the [Using
HWA](http://duparq.free.fr/hwa/using.html) page.

Building the documentation from sources requires
[Doxygen](http://www.stack.nl/~dimitri/doxygen/) and Gnu Make. Run `make` in the
HWA base directory and open the `doxygen/html/index.html` page.


Status
======

__WARNING!__ The development of HWA is very chaotic and this project is subject
to heavy changes of the code base.


Supported devices
=================

 * HWA supports almost fully Atmel AVR ATtinyX4, ATtinyX5, and ATmegaX8:
   * ATtiny24, ATtiny24A, ATtiny44, ATtiny44A, ATtiny84, ATtiny84A
   * ATtiny25, ATtiny45, ATtiny85,
   * ATmega328P
   * ATmega32U4 needs probably some updates

 * Very partial support of ST's STM32F103:
   * STM32F103C8T6, STM32F103RBT6, STM32F103VCT6

 * Very partial support of Espressif's ESP8266


Organization of the code
========================

The base source code of HWA is in the `hwa/` directory.

Device-related sources are stored in `vendor/architecture/` directories
(`atmel/avr/`, `st/stm32/`, `espressif/esp8266/`, ...) where are stored
`classes/`, `devices/`, and `examples/` directories.


Hosting
=======

HWA is hosted on [Github](http://github.com/duparq/hwa).


Feedback
========

Feedbacks will be greatly appreciated. For any bug report, question or
suggestion, please open a new issue on [Github](http://github.com/duparq/hwa),
or use my gmail address (duparq) and put HWA in the object.


License
=======

HWA is free software. See the @ref license "license" page for license information.

<br>
