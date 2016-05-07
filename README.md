
HWA
===

Introduction
============

HWA<sup><a href="#hwa">*</a></sup> is a hardware abstraction tool for
programming microcontrollers in C language. A few features of HWA are useful for
programming in assembler too.

HWA is designed to help the developer to write hardware-related code that:

 * is easy to read,
 * is easy to port between different targets,
 * produces the most effecient binary code.

To achieve these goals, HWA provides the developer with:

 * a set of object names that represent the hardware of a microcontroller,

 * a small set of
   [polymorphic](https://en.wikipedia.org/wiki/Ad_hoc_polymorphism) instructions
   that use an object name followed by mandatory or optional self-speaking
   keyword arguments,

 * a transactional processing mechanism, using a _context_, allowing further
   optimization of the binary code.

**HWA is not a library** but a set of preprocessor definitions. Thus, contrary
to a library (such as used by the Arduinos), the use of HWA does not affect the
efficiency of the binary code produced: the compiler's optimizers make the
binary code as efficient as if you wrote smart accesses to hardware registers
yourself. So, there is no penalty in using HWA, either in terms of size,
execution speed or memory used.

**HWA does not require a C++ compiler**. Any C compiler compatible with the
[C11](https://en.wikipedia.org/wiki/C11_%28C_standard_revision%29) standard
should be able to compile your source code.

HWA tries to produce **error messages that help the developer**, often by
reminding him the positional parameters that an instruction expects or the
allowed values for a parameter.

There is an example of how to use a watchdog interrupt to make a LED blink with
an Atmel AVR device:


    //  Load HWA definitions for the target device
    //
    #include <hwa/attiny44a_pu.h>


    //  We can use pin numbers as the device name tells HWA the package
    //
    #define PIN_LED      hw_pin_7


    //  Service watchdog IRQ
    //
    HW_ISR( hw_wdog0 )
    {
      //  Blink the LED
      //
      hw_toggle( PIN_LED );
    }


    int main ( )
    {
      //  Create a HWA context preloaded with RESET values to
      //  collect the hardware configuration
      //
      hwa_begin_from_reset();

      //  Configure the LED pin
      //
      hwa_config( PIN_LED, direction, output );

      //  Configure the watchdog to trigger an IRQ every 250ms
      //
      hwa_config( hw_wdog0,
                  timeout,  250ms,
                  action,   irq
                  );

      //  Configure the core to enter idle mode when asked to sleep
      //
      hwa_config( hw_core0,
                  sleep,      enabled,
                  sleep_mode, idle
                  );

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


Supported devices
=================

HWA supports almost fully Atmel AVR ATtinyX4, ATtinyX5, and ATmegaX8. Support
of ATmega32U4 has been started.

Support of Espressif's ESP8266 has been started.

ST's STM32F103 is the device that initiated the writing of HWA. The code now
needs to be rewritten.


Organization of the source tree
-------------------------------

The base source code of HWA is in the `hwa/` directory.

Device-related source codes are stored in `vendor/architecture/` directories
(`atmel/avr/`, `st/stm32/`, `espressif/`, ...) where you'll find `classes/`,
`devices/`, and `examples/` directories.


Examples
========

The `vendor/architecture/examples/` directories (e.g. `atmel/avr/examples/`)
contain HWA example projects.

Each `examples/` directory contains a `README.md` file that explains how to
compile the examples.


Documentation
=============

You can browse a ready-made documentation from [this web
page](http://duparq.free.fr/hwa/index.html).

To build the documentation in HTML format from sources, you need to have
[Doxygen](http://www.stack.nl/~dimitri/doxygen/) and Gnu Make installed (see
below). You then just need to run `make` in the HWA base directory. You'll start
with the `doxygen/html/index.html` page.


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

HWA is free software. See the "license" page for license information.

<hr>

<a name="hwa"><sup>*</sup></a>: pronounced "Wah!" <i>a statement or exclamation, in
several languages that shows pleasure, appreciation and surprise.</i> --
Wikipedia.

<br>
