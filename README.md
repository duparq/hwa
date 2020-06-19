
HardWare Advanced
=================

HWA stands for HardWare Advanced. HWA is a set of C definitions designed for
bare metal programming with a pleasant style.

To give you an idea, the following code blinks a LED connected to an
STM32F103RBT6 using Systick interrupts and sleeping mode:

    #include <hwa/stm32f103rbt6.h>
    
    #define AHBHZ   HW_DEVICE_HSIHZ         // The HSI frequency (8 MHz)
    #define LED     (porta,2)               // PA2
    #define PERIOD  0.5                     // Blinking period in seconds
    
    HW_ISR( (systick,irq) ) {}              // The IRQ is used only to wake the core up.
    
    int main ( )
    {
      hwa( begin, reset );                  // Record the configuration in a context
    
      hwa( power, (LED,port), on );         // Power the LED port
      hwa( commit );                        // Write the context in the hardware
    
      hwa( configure, LED,                  // Configure the LED pin
           function,  gpio,                 //   Optional argument
           mode,      digital_output,       //   Mandatory argument
           frequency, lowest );             //   Optional argument
    
      hwa( configure, systick,              // Configure the system tick timer
           clock,     ahb/8,                //   Clock it at 1/8th the AHB frequency
           reload,    PERIOD/2*AHBHZ/8-1,
           run,       yes );
    
      hwa( enable, (systick,irq) );         // Enable Systick IRQs (to wake the core up)
    
      hwa( commit );                        // Write all that into the hardware
    
      for(;;) {
        hw( wait, irq );                    // wait event is OK too.
        hw( toggle, LED );                  // Toggle the LED at wake-up
      }
    }

The resulting binary is 402 bytes long: 94 bytes of code + 308 bytes of vectors.


HWA in short
============

HWA provides:

 * a set of objects that represent the hardware,
 * the generic instruction, `hw(...)`, that acts on these objects using
   various types and numbers of mandatory and optionnal symbolic arguments,
 * the generic instruction, `hwa(...)`, that provides a transactional processing
   mechanism that allows further optimization of the binary code produced,
 * an error-checking mechanism that produces meaningful messages to help the
   developer quickly solve the problems.


Performances and compatibility
==============================

Any C compiler compatible with the
[C11](https://en.wikipedia.org/wiki/C11_%28C_standard_revision%29) standard
should be able to compile HWA code.

Because it is not a library, using HWA does not affect negatively the efficiency
of the binary code produced either in terms of size, execution speed, or memory
used. HWA helps the compiler's optimizers produce a binary that is as efficient
as if the developer had written smart accesses to hardware registers himself.

HWA relies heavily on macro definitions to implement object-oriented generic
instructions. As the C preprocessor can be used to parse assembly language code,
a few features of HWA can be used for assembly programming. The implementation
of a [software UART for Atmel AVR microcontrollers](atmelavr_swuarta.html) (see
`atmel/avr/classes/swuarta/`) and the [Diabolo bootloader](atmelavr_diabolo.html) (see
`atmel/avr/examples/diabolo/`) are examples of such a usage.



Examples
========

A [set of commented examples](http://duparq.free.fr/hwa/examples.html) is
provided. Example projects are store in the `vendor/architecture/examples/`
directories (e.g. `atmel/avr/examples/`) where a `README.md` file explains how
to compile them.


Documentation
=============

A ready-made documentation is available
[here](http://duparq.free.fr/hwa/index.html). You can start with the [Using
HWA](http://duparq.free.fr/hwa/using.html) page or browse the examples.

Building your own copy of the documentation from the sources requires
[Doxygen](http://www.stack.nl/~dimitri/doxygen/) and Gnu Make. Run `make doc` in
the HWA directory, then open the `doxygen/html/index.html` page.


Supported hardware
==================

 * Atmel AVR:
   * [ATtinyX4](http://duparq.free.fr/hwa/attinyx4.html): ATtiny24, ATtiny24A, ATtiny44, ATtiny44A, ATtiny84, ATtiny84A
   * [ATtinyX5](http://duparq.free.fr/hwa/attinyx5.html): ATtiny25, ATtiny45, ATtiny85,
   * [ATmegaX8](http://duparq.free.fr/hwa/atmegax8.html): ATmega328P
   * Software-emulated devices:
     * [HW_SWUART](http://duparq.free.fr/hwa/atmelavr_swuarta.html) Software UART
     * [HW_SWTWIMASTER](http://duparq.free.fr/hwa/atmelavr_swtwimaster.html) Software TWI master
   * Very partial support (old, must be rewritten):
     * [ATmega32U4](http://duparq.free.fr/hwa/atmegaxu4.html): ATmega32U4

 * ST STM32:
   * [STM32F103](http://duparq.free.fr/hwa/stm32f103.html): STM32F103C8T6, STM32F103RBT6, STM32F103VCT6
 * Espressif
   * [ESP8266](http://duparq.free.fr/hwa/esp8266.html): ESP8266

 * External devices:
   * [24CXX](http://duparq.free.fr/hwa/ext_24cxx.html) I²C EEPROM
   * [HD44780](http://duparq.free.fr/hwa/hd44780.html) LCD driver
   * [PCF8574](http://duparq.free.fr/hwa/pcf8574.html) I²C expander
   * [TCS3200](http://duparq.free.fr/hwa/tcs3200.html) colour detector


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
