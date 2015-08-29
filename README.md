
HWA
===

Introduction
============

HWA<sup><a href="#hwa">*</a></sup> is a hardware abstraction tool for
programming microcontrollers in C language. A few features of HWA are useful for
programming in assembler too.

HWA provides the programmer with an object-oriented interface to the hardware
that consists of a small set of generic instructions designed to be applied on
various types of objects that represent the peripheral controllers embedded in a
microcontroller.

Using these instructions makes the source code easier to read and to port
between different targets since they describe clearly and concisely their
effect, instead of manipulating numerical values and registers.

HWA is not a library neither is it a programming language. HWA implements a
mechanism of [ad hoc
polymorphism](https://en.wikipedia.org/wiki/Ad_hoc_polymorphism) only using
standard C language
([C11](https://en.wikipedia.org/wiki/C11_%28C_standard_revision%29)) macro
definitions and function-like macros, all processed by the standard
preprocessor, not a C++ compiler such as used for example by
[Arduinos](http://www.arduino.cc). Inline functions and a cache mechanism (the
_HWA context_) combined to the compiler's optimizers make the binary code
produced free of any penalty, either in terms of size, execution speed or memory
used.

Last, but not least, the error messages HWA produces try to guide the developper
quickly to the solution.

![](doxygen/hwa_principle.jpeg)


Documentation
=============

You can browse a ready-made documentation from [this web
page](http://duparq.free.fr/hwa/index.html).

To build the documentation in HTML format from sources, you need to have
[Doxygen](http://www.stack.nl/~dimitri/doxygen/) and Gnu Make installed (see
below). You then just need to run `make` in the HWA base directory. You'll start
with the `doxygen/html/index.html` page.


Examples
========

The `atmel/avr/examples/` directory contains example projects aimed at
illustrating various features of HWA for the Atmel ATtiny44/84, ATmega328P and
ATtiny45/85 devices.

The `main.c` file of each example project gives informations about what it does
and how you can test it. A Python application, usually named `main.py`, is
provided in the directory of the examples that need to communicate with the
host.

A build system is also provided, that uses GNU Make and a few other GNU
utilities.


Toolchain
---------

To be able to compile the example projects, you need a properly configured
avr-gcc toolchain and GNU Make. Python2.7 + pySerial are required if you want to
check the CRC of the binary code produced, use the Diabolo bootloader or for
testing the examples that communicate.

__GNU/Linux__ users usually only have to install the required packages their
distribution provides.

For __Windows__ users, the compilation of the HWA example projects has been
tested using:

 * [Atmel AVR8 GNU Toolchain](http://www.atmel.com/tools/ATMELAVRTOOLCHAINFORWINDOWS.aspx)<br>
   Extracted into `C:\`. That creates the `C:\avr8-gnu-toolchain\` directory.

 * [Git for Windows](https://msysgit.github.io) (for its `bash` shell)<br>
   Extracted into `C:\avr8-gnu-toolchain`

 * [Gow 0.8.0](https://github.com/bmatzelle/gow/releases/download/v0.8.0/Gow-0.8.0.exe)
   (for its `make` command)<br>
   Extracted into `C:\avr8-gnu-toolchain\Gow\`

 * [GNU Awk 4](https://code.google.com/p/gnu-on-windows/downloads/detail?name=gawk-4.0.2-bin.zip)<br>
   Extracted into `C:\avr8-gnu-toolchain\bin\`

 * [Python2.7](https://www.python.org/ftp/python/2.7.10/python-2.7.10.msi)<br>
   Installed into `C:\Python27\` (check at least "Register Extension" and "PIP")

 * [Console2](http://sourceforge.net/projects/console) (for cosmetics!)<br>
   Changed the settings in Edit / Settings / Shell:
   `C:\avr8-gnu-toolchain\bin\bash.exe --login`. Restart.

 * Pyserial: installed from the bash command line: `/c/Python27/Scripts/pip install pyserial`

 * Optionnally: [wxPython](http://www.wxpython.org/download.php) for companion
   applications that have graphical capablities.


Once all this is downloaded and installed, update your PATH, e.g.:

    PATH=/c/avr8-gnu-toolchain/bin:/c/Python27:$PATH

You can put this line in `/etc/profile` to have `bash` set it when it starts.

__Note__: until now, I have only tried such a setup with a VirtualBoxed Windows
XP and it is _very_ slow.


Compiling an example
--------------------

As a first compiling test, you can run `make` in the `examples/01-1-blink-soft/`
directory. If your toolchain is operationnal, that will produce, among others,
the binary file to burn into the default ATtiny84 device. You can choose a
specific target to compile for with the `BOARD` variable. HWA provides a few
target board definition files in the `examples/boards/` directory. These files
contain the configuration of the microcontroller and its environment: fuses, LED
pins, configuration of the Diabolo bootloader... The first example should
compile for any board:

    make BOARD="attiny84"
    make BOARD="attiny85"
    make BOARD="nanodccduino"


Running an example
------------------

If you want to run one of the examples on a microcontroller on which you
previously installed the Diabolo bootloader, you just have to connect your
USB-UART adapter and run e.g. `make BOARD="attiny84" install` from the example's
directory. The settings for Diabolo are computed from the source code of the
example.

If you prefer another programming method, the file `build/$BOARD/out.bin` in
the example project directory contains the binary code to be programmed. You
can define `PROG_SW` and `PROG_HW` in the Makefile of the example project with
the names of your programming tools to override the default Diabolo (and you can
add a 'hex' target to `examples/make/Makefile.build` if you prefer to use .hex
format). For example:

    PROG_SW = avrdude
    PROG_HW = usbasp

You have to provide a specific makefile if you use neither Diabolo nor
avrdude. Look at the `examples/make/` directory.


Compiling all the examples at once
----------------------------------

You can run `make all-examples` in the `examples/` directory to verify that most
examples compile without error for different targets. Here again, the `BOARD`
variable lets you specify a single target board for which you want the examples
be compiled: `make BOARD=attiny84 all-examples`, `make BOARD=nanodccduino
all-examples`, etc.

All the examples should compile without error for the `attiny84` board. A few
examples can be inadequate for other boards and fail to compile. This is not a
bug!


Checking the validity of the produced code without programming a device
-----------------------------------------------------------------------

If you installed Python, you can run `make check-all-examples` in the
`examples/` directory or `make check` in one of the examples directories to
verify that the generated code is valid. Here again, you can use the `BOARD`
variable to restrict the verifications to a specific target board. The
validation is done by verifying that the CRC16 of the binary code produced for a
given compiler and a given configuration is preserved. Each example project
contains validation files, named `.valid-*`. The name of a validation file
contains the compiler version, the target device name, the CRC32 of the
configuration, and the size and the CRC16 of the binary code. The validation
file contains the configuration variables and the machine code produced. A
difference of CRC16 between two binaries produced by two different compilers
does not necessarily mean that one code is better that the other as it is
possible that the compilers just have made different register choices. However,
for a given compiler, and a given configuration, a difference in the CRC16 means
that there is a significant difference in the produced codes. The machine code
included in the validation file is then usefull to see if the variations in the
produced code result of modifications in the HWA core.


Status
======

__WARNING!__ The development of HWA is very chaotic and this project is subject
to heavy changes of the code-base.


Feedback
========

Feedbacks will be greatly appreciated. For any bug report, question or if you
think you have an idea that would enhance HWA, please use my gmail address
(duparq) and put HWA in the object.


License
=======

HWA is free software. See the "license" page for license information.

<hr>

<a name="hwa"><sup>*</sup></a>: <i>"Wah! a statement or exclamation, in
several languages that shows pleasure, appreciation and surprise."</i> --
Wikipedia.

<br>
