
Porting HWA {#porting}
===========

Files
=====

Porting HWA to a new device, name it `mymcu`, requires writing at least those
files:

 * `include/hwa/mymcu.h`: header file that will be used in projects using this
   device

 * `devices/mymcu_1.h`: definitions that do not produce C code + definitions
   that build the HWA context

 * `devices/mymcu_2.h`: definitions that produce C code

You may have to write new HWA classes for the peripherals your device
embeds. Class names are lower cased, prefixed with a `_` and end with a
letter. For example, class `_myclassa` will be defined by the files:

 * `classes/vendor/arch/classa_1.h`: definitions that do not produce C code +
   definitions that build the HWA context

 * `classes/vendor/arch/classa_2.h`: definitions that produce C code

where `vendor` is the name of the vendor of the device (`atmel`, `st`,
`microchip`...) and `arch` is the architecture (`avr`, `avr32`, `stm32`...).


The HWA context
===============

The context is created by the expansion of the `HWA_DCL` macro. This is
triggered by a `hwa_begin()` or hwa_begin_from_reset()` instruction.


Creating an interrupt
=====================

Interrupts are objects of class `_irq`. You create the interrupt for the `event`
of the `hw_peripheral0` with:

    #define _hw_irq_hw_peripheral0_event        _irq, vector, enable, flag

where:

 * `vector` is the vector number of the IRQ, counting from 0, so this is the
   vector number Atmel gives minus 1

 * `enable` is the register (_cb1) that enables/disables the IRQ

 * `flag` is the register (_cb1) that signals the IRQ (and that is cleared by
   writing 1 into it).

The interrupt for an unnamed event of the `hw_peripheral0` is created with:

    #define _hw_irq_hw_peripheral0              _irq, vector, enable, flag


Creating an object
==================

Although the definition of an object depends on its class, an object named
`hw_myobject0` of class `_myclassa` is generally created with:

    #define _hw_myobject0       _myclassa, id, address

where:

 * `id` is a unique number identifying the object

 * `address` is the base address of the object

Note that the name of the object is prepended with a '_' for its definition
since HWA prepends this '_' to the object name provided to instructions to
verify that the expansion of the resulting name begins with the name of a
declared class, here `_myclassa`.

`address` can be null if the registers are not consistently mapped into the
memory between different objects of the same class. This is often the case for
Atmel AVR devices.


Creating a class
================

A class `_myclassa` is created with:

    #define _hw_class__myclassa

Once a class is created, objects of this class and methods can also be declared.


Creating a register
===================

The word 'register' in HWA designs two types of objects:

 * a hardware 8, 16 or 32 bits register

 * a group of bits that are parts of one or two registers and hold one information

Registers can be members of classes as well as members of objects.


Hardware registers
------------------

Objects of class `_crg` design hardware registers.

A register `myreg0` of the class `_myclassa` objects is created with:

    #define _hw__myclassa_myreg0     _crg, rw, ra, rwm, rfm

that is, the concatenation of `_hw_`, the class name, the register name, where:

 * `rw` is the width in bits of the register (8, 16, 32)

 * `ra` is the address of the register relatively to the base address of the object

 * `rwm` is the mask of writeable bits

 * `rfm` is the mask of flag bits (bits that are cleared by writing 1 into them)

A register `myreg1` of the object `hw_myobject0` is created with:

    #define _hw_myobject0_myreg1     _crg, rw, ra, rwm, rfm


Groups of bits
--------------

There are two kinds of groups of bits:

 * `_cb1` designs one group of consecutive bits inside one hardware register

 * `_cb2` designs two groups of consecutive bits spread among two hardware registers

A one-group register named `_mybit1`, of `bn` consecutive bits with the least
significant at position `bp` inside the hardware register `myreg0`, for the
class `_myclassa` objects is created with:

    #define _hw__myclassa_mybit1    _cb1, myreg0, bn, bp

A two-groups register named `_mybit2`, made of

 * `rbn1` consecutive bits with the least significant at position `rbp1` inside
   the hardware register `myreg0` corresponding to the `vbp1` bit of the
   group register value

 * `rbn2` consecutive bits with the least significant at position `rbp2` inside
   the hardware register `myreg1` corresponding to the `vbp2` bit of the
   group register value

for the class `_myclassa` objects is created with:

    #define _hw__myclassa_mybit1    _cb2, myreg0, rbn1, rbp1, vbp1, myreg1, rbn2, vbp2

An example used by HWA is the `wgm` register of the class `_c16a`:

    #define _hw__c16a_wgm           _cb2, ccrb, 2, 3, 2, ccra, 2, 0, 0

That means that `wgm` is a 4 bit register (corresponding to Atmel WGM3..0) made
of two groups:

 * bits 3..2 (WGM3..2) are bits 4..3 of hardware register ccrb
 * bits 1..0 (WGM1..0) are bits 1..0 of hardware register ccra


Creating a method
=================

A method `hw_mymethod` for the class `_myclassa` is created with:

    #define _hw_mthd_hw_mymethod__myclassa       , _hw_myclassamethod

that is, the concatenation of: `_hw_mthd_`, the name of the method, '`_`', the
name of the class.

The expansion results in two elements:

 * a first void element that is used by HWA to validate the existence of the
   method for the class

 * the name of the implementation of the method


For example, if you want the class `_myclassa` to support the generic
instruction `hw_config(...)`, you define:

    #define _hw_mthd_hw_config__myclassa        , _hw_cfmyclassa

Then, HWA expands the instruction

    hw_config( myobject0, arg1, arg2 )

to

    _hw_cfmyclassa( myobject0, id, address, arg1, arg2, )

The arguments are:

 * the name of the object

 * the definition of the object (without its class name since it is known)

 * the list of arguments

 * a last void argument


Creating a generic instruction
==============================

HWA provides a set of generic instructions that should cover almost all the
requirements.

It is not decided wether adding new generic instructions is wishable or not. The
generic instructions set should be restricted as these instructions are meant to
apply to a large diversity of objects.

If a small set of objects require the creation of new instructions, the generic
instruction `hw/hwa_command()` should be considered first.

You create the new generic instruction `hw_mygeneric` with:

    #define hw_mygeneric(...)           HW_MTHD(hw_mygeneric, __VA_ARGS__,)

Assuming that the class of `hw_myobject0` is `_myclassa`, the instruction

    hw_mygeneric( hw_myobject0 );

will be expanded to the method defined by the expansion of
`_hw_mthd_mw_mygeneric__myclassa`.

<br>
