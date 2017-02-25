
/*  This file is part of the HWA project.
 *  Copyright (c) 2012,2015 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief I/O definition
 */

/**
 * @page esp8266_io1a Class _io1a: General Purpose I/O definition
 *
 * A class `_io1a` object is a single or a group of consecutive pins inside the
 * same I/O port.
 */
#define _hw_class__io1a


/**
 * @page esp8266_io1a
 * @par Instructions that do not produce C code:
 *
 * The `hw_bn()` instruction retrieves the number of bits of an I/O definition:
 *
 * @code
 * #if hw_id(pin_pa3) && (hw_bn(pin_pa3) != 1)
 * #  HWA is damaged!
 * #endif
 * @endcode
 */
#define _hw_mthd_hw_bn__io1a                   , _hw_bn_io1a

#define _hw_bn_io1a(o,i, cn,bn,bp,...)         bn


/**
 * @page esp8266_io1a
 *
 * For a group of consecutive pins, the `hw_bp()` instruction gives the position
 * of the least significant bit:
 *
 * @code
 * #if hw_id(pin_pa3) && (hw_bp(pin_pa3) != 3)
 * #  HWA is damaged!
 * #endif
 * @endcode
 */
#define _hw_mthd_hw_bp__io1a                   , _hw_bp_io1a
#define _hw_bp_io1a(o,i, cn,bn,bp,...)         bp


/**
 * @page esp8266_io1a
 *
 * The `hw_rel()` instruction is usefull to retrieve the name of the I/O port
 * associated to the I/O:
 *
 * @code
 * #if hw_id(pin_pa3) && hw_id(rel(hw_pin_pa3,port)) != hw_id(port_a)
 * #  Pin PA3 should be a PORTA pin!
 * #endif
 * @endcode
 */
#define _hw_mthd_hw_rel__io1a		, _hw_rel_io1a

#define _hw_is_port_port

#define _hw_rel_io1a(o,x,...)	\
  HW_GX(_hw_rel_io1a,_hw_is_port_##x)(o,x,__VA_ARGS__)

#define _hw_rel_io1a_1(o,x,i,p,...)	p

#define _hw_rel_io1a_0(o,x,...)		HW_E(`o` has no relative named `x`)
