
HWA
===

HWA <sup>(*)</sup> is a hardware abstraction tool for programming
microcontrollers in C language. A few features of HWA are useful for programming
in assembler too.

HWA provides a set of object-oriented generic instructions that allow the
programmer to focus on the result rather than the values that must be written
into registers with the hope that it leads to source code easier to read, easier
to maintain, and easier to port between different targets.

HWA is not a library. It is implemented at the preprocessing and compilation
levels and a cache mechanism (the _HWA context_) combined to the compiler's
optimizers help HWA produce a machine code free of any penalty, either in terms
of size, execution speed or memory used.

![](doxygen/hwa_principle.jpeg)


Documentation
=============

Run `make doc` in the HWA base directory to build the documentation in HTML
format. You'll start with the `doxygen/html/index.html` page.

Alternately you can browse the documentation from [this
website](http://duparq.free.fr/hwa/index.html).

Currently the documentation gives primarily informations about using HWA, not
much on how HWA works internally.


Examples
========

The `atmel/avr/examples/` directory contains a few examples aimed at
illustrating various features of HWA, currently only for Atmel ATtiny44/84 and
ATmega328P devices (ATtinyx5 should be available soon as it was supported before
HWA was last rewritten).

As a first check, you can run `make` in the HWA base directory to verify that
all examples compile without error and that the generated code is correct (there
are validation files that make this verification automatically). You'll need a
properly configured avr-gcc toolchain for that (avr-libc is not required). By
default, the target device is an ATtiny84. If you want to verify that the
examples compile for the ATmega328p device as used on some Arduino boards, you
can run `make clean` then `make BOARD=nanodccduino`.

The `main.c` file of each example gives informations about what it does and how
you can test it. A Python application is provided with the examples that need to
communicate with the host.

Files stored in the `examples/boards/` directory contain the definitions of
various boards used to verify the correctness of the code produced by HWA:
configuration of the microcontroller (fuses...), configuration of the Diabolo
bootloader, LED pins used on Arduino boards...

If you want to run one of these examples on a microcontroller in which you
previously installed the Diabolo bootloader, you just have to connect your
USB-UART adapter and run `make install`.

If you prefer to use another programming method, you'll find the machine code to
be programmed in the `build/out.bin` file. In the Makefile, you can define
`PROG_SW` and `PROG_HW` with the names of your programming tools to override the
default Diabolo. For example:

    PROG_SW = avrdude
    PROG_HW = usbasp

You'll have to provide a specific makefile if you use neither Diabolo nor
avrdude. Look at the `examples/make/` directory.


Status
======

WARNING: this project is subject to heavy changes of the code-base!

Because I do this as a hobby in my spare time, sometimes not touching it for
several weeks, the development pace of HWA is as much irregular as the road I
follow. Besides, I have many things to learn about Doxygen, git or just about
project management.

So, though I started to write it in 2010, HWA is still not stabilized. It was
first designed to be used with STM32 devices, but making it also work with Atmel
AVRs took me a lot of time because of the arrangement of the registers in these
devices. That led me to rewrite HWA several times, as I discovered mistakes in
the conception, new possibilities with the preprocessor or simply that I could
make things better (e.g. object-oriented instructions accepting variable-length
lists of key-value arguments).


License
=======

HWA is free software. See the @ref license "license" page for license
information.

<hr>

<sup>(*)</sup>: <i>"Wah! a statement or exclamation, in several languages that
shows pleasure, appreciation and surprise."</i> -- Wikipedia.
