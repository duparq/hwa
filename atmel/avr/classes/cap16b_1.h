
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief 16-bit capture unit
 */

/*
 *	This is the same as the _cap16a except that it can not bo connected to
 *	the analog comparator output.
 */

/**
 * @page atmelavr_cap16b Class _cap16b: 16-bit capture unit
 *
 * A class `_cap16b` object is a 16-bit capture unit. It has the following
 * relative objects:
 *
 *  * one counter, whose name is given by `HW_RELATIVE( capture0, counter )`
 *
 *  * one input pin, whose name is given by `HW_RELATIVE( capture0, pin )`
 *
 * It is used in:
 *
 *  * @ref atmegaxu4 : `counter3capture0`
 */
#define _hw_class__cap16b

/**
 * @page atmelavr_cap16b
 * @par Instructions that do not produce C code
 *
 * The `HW_BITS()` instruction returns the number of bits of the capture
 * register:
 *
 * @code
 * #if HW_BITS( capture0 ) != 16
 * #  error A 16-bit capture unit is required!
 * #endif
 * @endcode
 */
#define _hw_mthd_HW_BITS__cap16b		, _hw_bn_cap16b
#define _hw_bn_cap16b(o,i,a,...)			16


/**
 * @page atmelavr_cap16b
 * @par Interrupts
 *
 * The capture unit can trigger an @ref using_interrupts "anonymous IRQ" when
 * a capture event occurs.
 *
 * @code
 * HW_ISR( capture0 )
 * {
 *    // Process capture event
 * }
 * @endcode
 */

#define hwa_cap16b_t	hwa_cap16a_t
