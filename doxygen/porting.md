
Porting HWA {#porting}
===========

Device definition files
=======================

Porting HWA to a new device, name it `mymcu`, requires writing at least three
files:

 * `include/hwa/mymcu.h`: the header file that will be included in the source
   code of projects using this device

 * `devices/mymcu_1.h`: containing the definitions that do not produce C code +
   the definitions that build the HWA context

 * `devices/mymcu_2.h`: containing the definitions that produce C code


Peripheral classes
==================

All peripherals of a device are objects pertaining to a class.

Each class is defined in two files. For example, the class `_myclassa` is
defined in:

 * `classes/vendor/arch/myclassa_1.h`: containing the definitions that do not
   produce C code + definitions that build the HWA context

 * `classes/vendor/arch/myclassa_2.h`: containing the definitions that produce C
   code

where `vendor` is the name of the vendor of the device (atmel, st,
microchip...) and `arch` is the architecture (avr, avr32, stm32...).

Class names are lower cased and prefixed with a `_`.

If you can not find an already defined class that suits your peripheral, you'll
need to declare a new class. The class `_myclassa` is declared with:

    #define _hw_class__myclassa

Once the class `_myclassa` is declared, you can declare objects and methods of
this class.


Peripheral objects
==================

Although it can vary, depending on the class, an object named `hw_myobject0` of
the class `_myclassa` is generally declared with:

    #define _hw_myobject0           _myclassa, id, address

where:

 * `id` is a unique number identifying the object

 * `address` is the base address of the object

__Note__ that the name of the object is prepended with a '_' for its definition
since HWA prepends this '_' to the object name the instructions are given to
verify that the expansion of the resulting name begins with the name of a
declared class, here `_myclassa`.

`address` can be null if the registers are not consistently mapped into the
memory between different objects of the same class. This is often the case for
Atmel AVR devices.


Registers
=========

The word _register_ in HWA refers to two types of objects:

 * a hardware register

 * a group of bits

Registers can be attributes of classes as well as attributes of objects.

Class registers are convenient when there is only one object of that class in
the device or when all objects of that class share the same memory mapping of
their registers.

Object registers are convenient when all objects of that class do not share the
same memory mapping of their registers.

HWA looks for the definition of the registers first in the class, then in the
object.


Hardware registers
------------------

Hardware registers are objects of the HWA classes `_r8`, `_r16`, or `_r32`.


__Class hardware registers__

An 8-bit hardware register `myreg0` of the class `_myclassa` is declared with:

    #define _hw__myclassa_myreg0     _r8, ra, rwm, rfm

The symbol to define is the concatenation of `_hw_`, the object class name, and the
register name, where:

 * `_r8` is the class or the register ; it could also be `_r16`, or `_r32` for
   16-bit and 32-bit wide registers;

 * `ra` is the address of the register relatively to the base address of the object;

 * `rwm` is the mask of bits that are writeable;

 * `rfm` is the mask of bits that are cleared by writing 1 into them (flag bits).


__Object hardware registers__

A 8-bit hardware register `myreg1` of the object `hw_myobject0` is declared with:

    #define _hw_myobject0_myreg1     _r8, ra, rwm, rfm

The symbol to define is the concatenation of `_`, the object name, and the
register name.


Groups of bits
--------------

Groups of bits are sub parts of hardware registers. There are two kinds of
groups:

 * groups of consecutive bits inside one hardware register;

 * group of bits made of two groups of consecutive bits inside one or two
   hardware registers.

Classes for groups of bits are:

 * `_cb1`: one group of consecutive bits inside one class hardware register;

 * `_cb2`: one group of bits made of two groups of consecutive bits inside one
   or two class hardware registers;

 * `_ob1`: one group of consecutive bits inside one object hardware register;

 * `_ob2`: one group of bits made of two groups of consecutive bits inside one
   or two object hardware registers;

 * `_xob1`: a group of bits in another object hardware register.

A group named `_mybit1`, of `bn` consecutive bits with the least significant at
position `bp` inside the hardware register `myreg0` of the class `_myclassa`
is declared with:

    #define _hw__myclassa_mybit1    _cb1, myreg0, bn, bp

A group named `_mybit2`, made of

 * `rbn1` consecutive bits with the least significant at position `rbp1` inside
   the hardware register `myreg0` corresponding to the `vbp1` bit of the
   group register value

 * `rbn2` consecutive bits with the least significant at position `rbp2` inside
   the hardware register `myreg1` corresponding to the `vbp2` bit of the
   group register value

of the class `_myclassa` objects is declared with:

    #define _hw__myclassa_mybit1    _cb2, myreg0, rbn1, rbp1, vbp1, myreg1, rbn2, vbp2

A typical example is the `wgm` register of the class `_c16a`:

    #define _hw__c16a_wgm           _cb2, ccrb, 2, 3, 2, ccra, 2, 0, 0

That means that `wgm` is a group of 4 bits (corresponding to Atmel WGM3..0) in
which:

 * bits 3..2 (WGM3..2) are bits 4..3 of hardware register ccrb
 * bits 1..0 (WGM1..0) are bits 1..0 of hardware register ccra


__External groups__

Atmel AVR devices sometimes have some bits used by one peripheral stored in the
registers of another peripheral.

You can access, from a class or from an object, a group of consecutive bits in
one register of another object through an object of the class `_xob1`.

An example is the `acic` register of the class `_c16a` that is in fact stored in
the bit 2 of the `csr` register of the analog comparator `hw_acmp0` object:

    #define _hw__c16a_acic          _xob1, hw_acmp0, csr, 1, 2


Interrupts
==========

Interrupts are objects of class `_irq`. You declare the interrupt for the `event`
of the `hw_peripheral0` with:

    #define _hw_irq_hw_peripheral0_event    _irq, vector, enable, flag

where:

 * `vector` is the vector number of the IRQ, counting from 0, so this is the
   vector number Atmel gives minus 1

 * `enable` is the register (_cb1) that enables/disables the IRQ

 * `flag` is the register (_cb1) that signals the IRQ (and that is cleared by
   writing 1 into it).

The interrupt for an unnamed event of the `hw_peripheral0` is declared with:

    #define _hw_irq_hw_peripheral0          _irq, vector, enable, flag



Class methods
=============

A method `hw_mymethod` for the class `_myclassa` is declared with:

    #define _hw_mthd_hw_mymethod__myclassa  , _hw_myclassamethod

that is, the concatenation of: `_hw_mthd_`, the name of the method, '`_`', the
name of the class.

The expansion results in two elements:

 * a first void element that is used by HWA to validate the existence of the
   method for the class

 * the name of the implementation of the method


For example, if you want the class `_myclassa` to support the generic
instruction `hw_config(...)`, you define:

    #define _hw_mthd_hw_config__myclassa    , _hw_cfmyclassa

Then, HWA expands the instruction

    hw_config( myobject0, arg1, arg2 )

to

    _hw_cfmyclassa( myobject0, id, address, arg1, arg2, )

The arguments are:

 * the name of the object

 * the definition of the object (without its class name since the method knows it)

 * the list of arguments

 * a last void argument

The last void argument is useful to verify that there is no remaining argument
in the list after the processing of the instruction. This is used at the end of
the processing of many `hw_config()` instructions with the `HW_TX()` macro:

    HW_TX(,__VA_ARGS__)


Generic instructions
====================

HWA provides a set of generic instructions that should cover almost all the
requirements.

It is not yet decided whether adding new generic instructions is wishable or
not. The generic instructions set should be restricted as these instructions are
meant to apply to a large diversity of objects.

If a small set of objects require the creation of new instructions, the generic
instruction `hw/hwa_command()` should be considered first.

You declare the new generic instruction `hw_mygeneric` with:

    #define hw_mygeneric(...)       HW_MTHD(hw_mygeneric, __VA_ARGS__,)

Assuming that the class of `hw_myobject0` is `_myclassa`, the instruction

    hw_mygeneric( hw_myobject0 );

will be expanded to the second element of the expansion of
`_hw_mthd_mw_mygeneric__myclassa`.

<br>
