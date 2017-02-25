
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief 16-bit capture unit
 */

/*
 *	This is the same as the _ic16a except that it can not bo connected to
 *	the analog comparator output.
 */

/**
 * @page atmelavr_ic16b Class _ic16b: 16-bit capture unit
 *
 * A class `_ic16b` object is a 16-bit capture unit. It has the following
 * relative objects:
 *
 *  * one counter, whose name is given by `HW_REL( CAPTURE_NAME, counter )`
 *
 *  * one input pin, whose name is given by `HW_REL( CAPTURE_NAME, pin )`
 *
 * It is used in:
 *
 *  * @ref atmegaxu4 : `hw_ic30`
 */
#define _hw_class__ic16b

/**
 * @page atmelavr_ic16b
 * @par Instructions that do not produce C code
 *
 * The `HW_BITS()` instruction retrieves the number of bits of the capture
 * register:
 *
 * @code
 * #if HW_BITS( CAPTURE_NAME ) != 16
 * #  error A 16-bit capture unit is required!
 * #endif
 * @endcode
 */
#define _hw_mthd_hw_bn__ic16b			, _hw_bn_ic16b
#define _hw_bn_ic16b(o,i,a,...)			16


/**
 * @page atmelavr_ic16b
 * @par Interrupts
 *
 * The capture unit can trigger an @ref using_interrupts "anonymous IRQ" when
 * a capture event occurs.
 *
 * @code
 * HW_ISR( CAPTURE_NAME )
 * {
 *    // Process capture event
 * }
 * @endcode
 */

#define hwa_ic16b_t	hwa_ic16a_t
