
/*  This file is part of the HWA project.
 *  Copyright (c) 2012,2015 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief I/O definition
 */

/**
 * @page espressif_iob Class _iob: General Purpose I/O definition
 *
 * A class `_iob` object is a single or a group of consecutive pins inside the
 * same I/O port.
 */
#define hw_class__iob


/**
 * @page espressif_iob
 * @par Instructions that do not produce C code:
 *
 * The `HW_BN()` instruction returns the number of bits of an I/O definition:
 *
 * @code
 * #if (HW_ADDRESS(pa3) != -1) && (HW_BN(pa3) != 1)
 * #  HWA is damaged!
 * #endif
 * @endcode
 */
#define HW_BITS__iob		, _hw_bn_iob

#define _hw_bn_iob(o, cn,bn,bp,...)	bn


/**
 * @page espressif_iob
 *
 * For a group of consecutive pins, the `hw_bp()` instruction gives the position
 * of the least significant bit:
 *
 * @code
 * #if hw_id(pa3) && (hw_bp(pa3) != 3)
 * #  HWA is damaged!
 * #endif
 * @endcode
 */
#define HW_POSITION__iob	, _hw_bp_iob
#define _hw_bp_iob(o, cn,bn,bp,...)	bp


/**
 * @page espressif_iob
 *
 * The `hw_rel()` instruction is usefull to retrieve the name of the I/O port
 * associated to the I/O:
 *
 * @code
 * #if hw_id(pa3) && hw_id(rel(hw_pa3,port)) != hw_id(port_a)
 * #  Pin PA3 should be a PORTA pin!
 * #endif
 * @endcode
 */
#define hw_rel__iob			, _hw_rel_iob

#define _hw_rel_iob(o,x,...)		HW_Y(_hw_rel_iob_,_hw_is_port_##x)(o,x,__VA_ARGS__)
#define _hw_rel_iob_1(o,x,p,...)	p
#define _hw_rel_iob_0(o,x,...)		HW_E(`o` has no relative named `x`)
