
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief 16-bit capture unit
 */

/*
 *	This is the same as the _ica except that it can not bo connected to
 *	the analog comparator output.
 */

/**
 * @ingroup atmelavr_classes
 * @defgroup atmelavr_icb Class _icb: 16-bit capture unit
 *
 * A class `_icb` object is a 16-bit capture unit. It has the following
 * relative objects:
 *
 *  * one counter, whose name is given by `( capture0, counter )`
 *
 *  * one input pin, whose name is given by `( capture0, pin )`
 *
 * It is used in:
 *
 *  * @ref atmegaxu4 : `counter3capture0`
 */
#define hw_class__icb

/**
 * @addtogroup atmelavr_icb
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
#define HW_BITS__icb		, _hw_bn_icb
#define _hw_bn_icb(o,a,...)			16


/**
 * @addtogroup atmelavr_icb
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

#define hwa_icb_t			hwa_ica_t
