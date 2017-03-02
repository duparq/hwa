
HWA
===

Introduction
============

HWA<sup><a href="#hwa">*</a></sup> is a set of C-preprocessor definitions
designed to help developers write hardware-related code that:

 * is concise and easy to read,
 * is easier to port between different targets,
 * produces efficient binary code.

To achieve these goals, HWA provides:

 * a set of objects that represent the hardware,

 * generic instructions that accept various types and various numbers of
   mandatory and optionnal arguments,

 * an error-checking mechanism that tries to produce messages that help the
   developer to solve the problem,

 * a transactional processing mechanism that allows further optimization of the
   machine code.

Any C compiler compatible with the
[C11](https://en.wikipedia.org/wiki/C11_%28C_standard_revision%29) standard
should be able to compile your source code.

Contrary to a library (such as used by the Arduinos), the use of HWA does not
affect the efficiency of the binary code produced. Using HWA, the compiler's
optimizers make the binary code as efficient as if you wrote smart accesses to
hardware registers yourself. So, there is no penalty in using HWA, either in
terms of size, execution speed or memory used.

As the C-preprocessor can be used to parse assembler source, a few features of
HWA can be used for assembler programming. The implementation of a @ref
atmelavr_swuarta "software UART for Atmel AVR microcontrollers" (see
`atmel/avr/swuarta/`) and a @ref atmelavr_diabolo "bootloader" (see
`atmel/avr/examples/diabolo`) are examples of that usage.


Short example
=============

Here is an example of how to use a watchdog interrupt to make a LED blink with
an Atmel AVR device:


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
      hwa( configure, PIN_LED, direction, output );

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
        hw_sleep();

      return 0 ;
    }


Other examples
==============

The `vendor/architecture/examples/` directories (e.g. `atmel/avr/examples/`)
contain HWA example projects.

Each `examples/` directory contains a `README.md` file that explains how to
compile the examples.


Supported devices
=================

 * HWA supports almost fully Atmel AVR ATtinyX4, ATtinyX5, and ATmegaX8.

 * Support of ATmega32U4 has been started.

 * Support of Espressif's ESP8266 has been started.

 * ST's STM32F103 is the device that initiated the writing of HWA. The code now
needs to be rewritten.


Documentation
=============

You can browse a ready-made documentation from [this web
page](http://duparq.free.fr/hwa/index.html). Start with the @ref using page.

To build the documentation in HTML format from sources, you need to have
[Doxygen](http://www.stack.nl/~dimitri/doxygen/) and Gnu Make installed (see
below). You then just need to run `make` in the HWA base directory. You'll start
with the `doxygen/html/index.html` page.


Organization of the source tree
===============================

The base source code of HWA is in the `hwa/` directory.

Device-related source codes are stored in `vendor/architecture/` directories
(`atmel/avr/`, `st/stm32/`, `espressif/`, ...) where you'll find `classes/`,
`devices/`, and `examples/` directories.


Status
======

__WARNING!__ The development of HWA is very chaotic and this project is subject
to heavy changes of the code-base.


Hosting
=======

HWA is hosted on [Github](http://github.com/duparq/hwa).


Feedback
========

Feedbacks will be greatly appreciated. For any bug report, question or if you
think you have an idea that would enhance HWA, please use my gmail address
(duparq) and put HWA in the object.


License
=======

HWA is free software. See the @ref license "license" page for license information.

<hr>

<a name="hwa"><sup>*</sup></a>: pronounced "Wah!" <i>a statement or exclamation, in
several languages that shows pleasure, appreciation and surprise.</i> --
Wikipedia.

<br>
