
/*  This file is part of the HWA project.
 *  Copyright (c) 2012,2015 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief I/O
 */

/**
 * @page atmelavr_io1a Class _io1a: General Purpose Input/Output
 *
 * A class `_io1a` object is a single or a group of consecutive pins inside the
 * same I/O port. An `_io1a` object can be configured as analog input if it has
 * a `_did` logical register.
 *
 * `_io1a` objects have the following relative objects:
 *
 *  * one port, of class @ref atmelavr_p8a "_p8a": `HW_REL( IO_NAME, port )`
 *  * one interrupt controller, of class @ref atmelavr_pcica "_pcica": `HW_REL( IO_NAME, pcic )`
 */
#define _hw_class__io1a


/**
 * @page atmelavr_io1a
 * @par Instructions that do not produce C code:
 *
 * The `HW_BITS()` instruction retrieves the number of bits of an I/O definition:
 *
 * @code
 * #if HW_ID(hw_pin_pa3) && (HW_BITS(hw_pin_pa3) != 1)
 * #  HWA is damaged!
 * #endif
 * @endcode
 */
#define _hw_mthd_hw_bn__io1a                   , _hw_bn_io1a

#define _hw_bn_io1a(o,i, cn,bn,bp,...)         bn


/**
 * @page atmelavr_io1a
 *
 * For a group of consecutive pins, the `hw_bp()` instruction gives the position
 * of the least significant bit:
 *
 * @code
 * #if HW_ID(hw_pin_pa3) && (hw_bp(pin_pa3) != 3)
 * #  HWA is damaged!
 * #endif
 * @endcode
 */
#define _hw_mthd_hw_bp__io1a                   , _hw_bp_io1a
#define _hw_bp_io1a(o,i, cn,bn,bp,...)         bp


/**
 * @page atmelavr_io1a
 *
 * The `HW_REL()` instruction is usefull to retrieve the name of the I/O port
 * associated to the I/O:
 *
 * @code
 * #if HW_ID(hw_pin_pa3) && HW_ID(HW_REL(hw_pin_pa3,port)) != HW_ID(hw_port_a)
 * #  Pin PA3 should be a PORTA pin!
 * #endif
 * @endcode
 */
#define _hw_mthd_HW_REL__io1a		, _HW_REL_io1a

#define _hw_is_port_port

#define _HW_REL_io1a(o,x,...)		HW_GX(_HW_REL_io1a,_hw_is_port_##x)(o,x,__VA_ARGS__)

#define _HW_REL_io1a_1(o,x,i,p,...)	p
#define _HW_REL_io1a_0(o,x,...)		HW_E_OO(o,x)
