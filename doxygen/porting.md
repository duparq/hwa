
Porting HWA {#porting}
===========

[TOC]

Files {#porting_files}
=====

Porting HWA to a device `%mymcu` of architecture `%arch` (avr, avr32, stm32...)
built by the `vendor` company (atmel, st, microchip...) requires writing at
least two files:

 * `%include/hwa/mymcu.h`: the header file that is included in the source code of
   the projects that use this device;

 * `%vendor/arch/devices/mymcu.h`: the device file, included by the header file,
   that gathers all the definitions that make HWA useable for the device.

The device file defines all the objects that represent the peripheral
controllers the device embeds and includes their classes definitions. The
definitions of the classes are split into two files in the
`vendor/arch/classes/` directory whose names begin with the class name without
the leading underscore `%_`:

 * one file whose name ends with `%_1.h` that contains the definitions that do
   not produce C code and the definition that builds the HWA context;

 * one file whose name ends with `%_2.h` that contains the definitions that
   produce C code.


Structure of a device file {#porting_df}
--------------------------

Let's see how the `atmel/avr/devices/atmegax8.h` file is structured.

The file is split in two parts. The first part is the only one that is included
for assembler programming as it defines all the objects but nothing that
produces C code:

 1. It includes `../hwa_1.h`, that is `atmel/avr/hwa_1.h` that is included by
    all the Atmel AVR device definition files. In addition to including the
    global `hwa/hwa_1.h` header, it defines symbols common to all Atmel AVR
    devices.

 2. The device file then processes and defines symbols related to the fuse
    bytes. These are treated early since they permit to compute the system clock
    frequency `hw_syshz` that is often necessary.

 3. Then comes the list of the peripherals for the documentation and the
    definitions of the interrupts.

 4. A `%shared` object is created to gather hardware registers that are not to be
    attached to a specific object.

 5. The ports and I/O pins are declared, as well as their alternate names.

 6. Then follow all the objects that implement the others peripherals.


The second part of the device file concerns the HWA context and the production
of C code:

 1. The `hwa_t` structure is populated with the elements of context relative to
    each object.

 2. The class definition header files that produce C code `*_2.h` are included.

 3. The context management functions are defined.


Classes {#porting_classes}
=======

All peripheral controllers of a device are objects pertaining to a class.

Class names are lower cased, prefixed with an underscore `_` and end with a
letter that is used to distinguish various classes of the same kind of objects.

For example, classes that implement an 8-bit counter are called `_c8a`, `_c8b`,
or `_c8c`...

A class is declared with a symbol starting with `_hw_class_` and ending with the
class name. The definition of this symbol must be void. For example, the class
`_c8a` is declared with:

@code
#define _hw_class__c8a
@endcode


Objects {#porting_objects}
=======

An object is declared to HWA with a symbol that starts with `_hw_def_` followed
by the object name. The definition of this symbol must begin with a declared
class name.

For example, the object named `counter0` of class `%_c8a` is declared with
something like:

@code
/*	Object				class, id, address
 */
#define _hw_def_counter0		_c8a, 100, 0x0000
@endcode

where:

 * `100` is a unique number identifying the object. This is used by the
   `HW_ID()` instruction.

 * `0x0000` is the base address of the object, that will be added to the
   relative addresses of the registers of the class. The base address can be
   null if the registers are not consistently mapped in the memory between
   different objects of the same class. This is often the case for Atmel AVR
   devices.


Registers {#porting_regs}
=========

The word _register_ in HWA refers to two types of objects:

 * _hardware registers_, that represent the real registers of a device;

 * _logical registers_, that represent sets of bits that altogether hold a
   meaningful value.

Registers can be attributes of classes as well as attributes of objects.

Class registers are convenient for registers that are always mapped the same way
into the memory whatever the object or the device, or when only one object of
that class can exist in one device.

Object registers are convenient for registers that have variable memory
mappings.

When a register is used, HWA looks for its definition first in the class, and
then in the object.


Hardware registers {#porting_hregs}
------------------

Hardware registers are objects of class `%_r8`, `%_r16`, or `%_r32`, respectively
for 8, 16, and 32-bit real registers.


__Class hardware registers__

The `count` register of an 8-bit counter class `_c8a` is declared as a class
register with a definition like:

@code
/*	Class hardware register		class, address, write mask, flags mask
 */
#define _hw_reg__c8a_count		_r8, 0x40, 0xFF, 0x00
@endcode

The symbol defined is the concatenation of `_hw_reg_`, the class name, and the
register name. In this definition:

 * `%_r8` is the class of the register;

 * `0x40` is the address of the register relatively to the base address of the
   object);

 * `0xFF` is the mask of the writeable bits in the register, `0xFF` means that
   all bits of the register can be written;

 * `0x00` is the mask of 'flag' bits, that are cleared by writing 1 into them,
   `0x00` means that there is no flag bit in this register.


__Object hardware registers__

The `ifr` register of an 8-bit counter class `_c8a` is declared as a register of
the `counter0` object with a definition like:

@code
/*	Object hardware register	class, address, write mask, flags mask
 */
#define _hw_reg_counter0_ifr		_r8, 0x35, 0x07, 0x07
@endcode

The symbol defined is the concatenation of an underscore, the object name, an
underscore, and the register name. In this definition:

 * `_r8` is the class of the register;

 * `0x35` is the address of the register;

 * the first `0x07` is the mask of the writeable bits in the register, `0x07`
   means that only the bits b2, b1, and b0 of the register can be written;

 * the second `0x07` is the mask of 'flag' bits, that are cleared by writing 1
   into them, `0x07` means that the bits b2, b1, and b0 are cleared by writing 1
   into them.


Logical registers {#porting_lregs}
-----------------

Logical registers are sub parts of hardware registers that hold one
information. Logical registers can be:

 * one group of consecutive bits inside one hardware register;

 * the association of two groups of consecutive bits inside one or two hardware
   registers.

Logical registers are objects of one of the following classes:

 * `_cb1`: one group of consecutive bits inside one class hardware register;

 * `_cb2`: two groups of consecutive bits inside one or two class hardware
   registers;

 * `_ob1`: one group of consecutive bits inside one object hardware register;

 * `_ob2`: two groups of consecutive bits inside one or two object hardware
   registers;

 * `_xob1`: one group of consecutive bits in one hardware register of another
   object.


The logical `cs` register of an 8-bit counter class `_c8a` is declared as a
class register with a definition like:

@code
/*	Class logical register
 */
#define _hw_reg__c8a_cs			_cb1, ccrb, 3, 0
@endcode

where:

 * `_cb1` is the class of the register;

 * `ccrb` is the name of the hardware register that holds this logical register;

 * `3` is the number of consecutive bits of this register;

 * `0` is the position of the least significant bit of this register in the hardware register.


The logical `wgm` register of an 8-bit counter class `_c8a` is declared as an
object register with a definition like:

@code
/*	Object logical register
 */
#define _hw_reg_counter0_wgm		_ob2, ccra, 2, 0, 0, ccrb, 1, 3, 2
@endcode

where:

 * `_ob2` is the class of the register;

 * `ccra, 2, 0, 0` tells that bits b1,b0 of the hardware register `ccra` hold bits b1,b0
   of this logical register;

 * `ccrb, 1, 3, 2` tells that bit b3 of the hardware register `ccrb` holds bit
   b2 of this logical register;


__External registers__

Atmel AVR devices sometimes have some bits used by one peripheral stored in the
registers of another peripheral.

One logical register in one object hardware register can be accessed
from a class or from an object using a register of class `_xob1`.

An example is the `acic` logical register of the class `_c16a` that is in fact
stored in the bit 2 of the `csr` hardware register of the analog comparator
`acmp0` object:

@code
#define _hw_reg__c16a_acic		_xob1, acmp0, csr, 1, 2
@endcode


Interrupts {#porting_irqs}
==========

Interrupts are objects of the `_irq` class.

For the ATtinyX4, the interrupt for the event `overflow` of the `counter0` is
defined like this (the second definition considers that there is no need for the
event name to be specified):

@code
#define _hw_irq_counter0_overflow       _irq, counter0, 11, ie,  if
#define _hw_irq_counter0_               _irq, counter0, 11, ie,  if
@endcode

where:

 * `counter0` is the IRQ name

 * `11` is the vector number of the IRQ, counting from 0, so this is the vector
   number Atmel gives minus 1. This is used by HWA to build the name of the ISR.

 * `ie` is the name of the logical register (class `_cb1` or `_ob1`) that
   enables/disables the IRQ

 * `if` is the name of the logical register that signals the IRQ (and that is
   cleared by writing 1 into it)

For the STM32, the SysTick timer alarm is defined like this:

@code
#define _hw_irq_systick_alarm           _irq, systick, esr_systick, ie, if
@endcode

where `esr_systick` is the name of the ISR.



Class methods {#porting_cmtd}
=============

A class method is "called" when a generic instruction is applied to an object
whose class has declared that it supports the instruction by the means of a
symbol made of the prefix `_hw_mtd_`, the instruction name, an underscore `_`,
the class name.

For example, to declare that the class `_wdoga` supports the generic instruction
`hw(reset,...)`, the following symbol must be defined:

@code
#define _hw_mtd_hw_reset__wdoga	, _hw_rstwdoga
@endcode

The definition contains two elements:

 * a first void element that is used by HWA to validate that the class supports
   the instruction;

 * the name of the method that implements the instruction.

Then, HWA will expand the instruction

@code
hw( reset, watchdog0 )
@endcode

to

@code
_hw_rstwdoga( watchdog0, 100, 0x0000, )
@endcode

where the arguments are:

 * the name of the object, its id, its base address;

 * the list of arguments passed to the generic instruction terminated by an
   additionnal void argument.

The void argument is a reasonably sufficient way to verify that there is no
remaining argument in the list after the end of their processing, using the
`HW_EOL()` or `HW_TX()` macro:

@code
HW_EOL(__VA_ARGS__)	// Produce an error if first argument in __VA_ARGS__ is not void
@endcode


Parsing arguments lists {#porting_parseargs}
=======================

The processing of variable length lists of arguments, made of key/value pairs,
is a feature of HWA that helps writing source code that is both concise and
clear.

Let's see how the `_c8a` class implements the asychronous `configure` action
(`hwa(configure,counter0,...)`) in the file `atmel/avr/classes/c8a_2.h`.

First, the method has to be declared:

@code
#define _hw_mtd_hwa_configure__c8a	, _hwa_cfc8a
@endcode

The instruction `hwa( configure, counter0, ... )` will then be translated to
`_hwa_cfc8a(o,i,a,...)` where:

 * `o` is the name of the object: "counter0";

 * `i` is the id of the object;

 * `a` is the base address of the object;

 * `...` represents the arguments following the object name.

We want the first argument that follows the object name to be the keyword
"clock" and the next argument to be a value for "clock". There is the definition
of `_hwa_cfc8a(...)`:

@code
#define _hwa_cfc8a(o,i,a, ...)						\
  do { HW_X(_hwa_cfc8a_kclock,_hw_is_clock_##__VA_ARGS__)(o,__VA_ARGS__,,) } while(0)
@endcode

The `do { ... } while(0)` block is there so that the expansion of the
instruction remains a block even though it develops as several statements.

`HW_X()` concatenates `_1` to its first argument, if the result of the expansion
of `_hw_is_clock_##``__VA_ARGS__` begins with a void
element. Otherwise, it concatenates `_0`.

For that to work, the following definition is required:

@code
#define _hw_is_clock_clock              , 1
@endcode

Then, if the first argument of the `__VA_ARGS__` list is "clock",
`HW_X(_hwa_cfc8a_kclock,_hw_is_clock_##``__VA_ARGS__)` expands to
`_hwa_cfc8a_kclock_1`, otherwise it expands to `_hwa_cfc8a_kclock_0`.

After that, `_hwa_cfc8a_kclock_0` or `_hwa_cfc8a_kclock_1` is concatenated with
`(o,__VA_ARGS__,,)`. The `i` and `a` parameters are dropped since the processing
of the `configure` action does not need the id or the address of the
object. Two more void elements are added to the end of the arguments list in
order to ensure that it always has at least 4; this will make further processing
simpler.

If the argument `k` is not "clock", `_hwa_cfc8a_kclock_0(o,__VA_ARGS__,,)`
produces an error explaining that `k` is not the word "clock":

@code
#define _hwa_cfc8a_kclock_0(o,k,...)    HW_E_VL(k,clock)
@endcode

If `k` is "clock", `_hwa_cfc8a_kclock_1(o,__VA_ARGS__,,)` continues the
processing of the arguments to verify that the following argument `v` is an
acceptable value for the "clock" key:

@code
#define _hwa_cfc8a_kclock_1(o,k,v,...)                                  \
  HW_X(_hwa_cfc8a_vclock,_hw_c8a_clock_##v)(o,v,__VA_ARGS__)
@endcode

and

@code
#define _hw_c8a_clock_prescaler_output_0	, 0
#define _hw_c8a_clock_prescaler_output_1	, 1024
#define _hw_c8a_clock_prescaler_output_8	, (1024/8)
#define _hw_c8a_clock_prescaler_output_64	, (1024/64)
#define _hw_c8a_clock_prescaler_output_256	, (1024/256)
#define _hw_c8a_clock_prescaler_output_1024	, (1024/1024)
#define _hw_c8a_clock_prescaler_output(x)	, 1024.0/(x)
@endcode

define the acceptable values. For instance, `prescaler_output_64` is a valid
value as well as `prescaler_output(64)`.

Then, if `v` is valid, the processing continues with
`_hwa_cfc8a_vclock_1(o,v,k,...)` where `v` is the validated symbolic value for
the "clock" key, `k` is the next key, and `...` the remaining arguments in the
list.

The numerical value corresponding to `v` is stored in the 'config' structure in
the HWA context of the object `o` in order to be processed later and the
processing of the following key, that should be "countmode", begins:

@code
#define _hwa_cfc8a_vclock_1(o,v,k,...)                          \
  _hwa_cfc8a_vclock(&hwa->o, HW_A1(_hw_c8a_clock_##v));         \
  HW_X(_hwa_cfc8a_kmode,_hw_is_countmode_##k)(o,k,__VA_ARGS__)

HW_INLINE void _hwa_cfc8a_vclock( hwa_c8a_t *o, float v )
{
  if ( v==0 || v==6 || v==7 )
    o->config.clock = v ;
  else if ( v == 1024 )
    o->config.clock = 1 ;
  else if ( v == 1024/8 )
    o->config.clock = 2 ;
  else if ( v == 1024/64 )
    o->config.clock = 3 ;
  else if ( v == 1024/256 )
    o->config.clock = 4 ;
  else if ( v == 1024/1024 )
    o->config.clock = 5 ;
  else
    HWA_E(value of `clock` must be in (`none`, `prescaler_output(0|1|8|64|256|1024)`, `ext_falling`, `ext_rising`, `ioclk`, `ioclk/8`, `ioclk/64`, `ioclk/256`, `ioclk/1024`));
}
@endcode

`HW_A1(_hw_c8a_clock_##%v)` expands to the element _a1_ of the list '(_a0_, _a1_,
...)'.

`_hwa_cfc8a_vclock()` checks that the provided value, when using
`prescaler_output()`, is valid.


Solving the configuration {#porting_solve}
=========================

Atmel AVR counter classes such as `_c8a` are implemented using separate objects
(the counting unit, the compare units, the prescaler) and the configuration of
the compare units have an incidence on the values to be written in the logical
register `wgm` of the counting unit. Thus, contrary to other simpler objects,
`_hwa_cfc8a()` does not immediately set logical register values according to the
parsed arguments but only stores the configuration in the context as will the
configuration instructions for the compare units. The `hwa_commit()` instruction
will call `_hwa_solve()` to process the values stored in the context, compute
the values of the registers, and verify that the whole configuration is valid
before the `_hwa_commit()` instruction effectively writes the registers into the
hardware.


Macro argument names {#porting_macargs}
====================

HWA uses the following standardized argument names in its macro definitions:

 * `o`: name of the object
 * `c`: class of the object
 * `i`: id of the object
 * `a`: base address of the object
 * `f`: name of the function
 * `t`: type
 * `r`: name of a register
 * `ra`: relative address of the register
 * `rwm`: register writeable bits mask
 * `rfm`: register flags mask
 * `bn`: number of bits
 * `bp`: position of least significant bit
 * `rbn`: number of bits of a logical register
 * `rbp`: position of least significant bit of a logical register in the
   hardware register
 * `vbn`: number of bits in the value
 * `vbp`: position of least significant bit in the value

<br>
