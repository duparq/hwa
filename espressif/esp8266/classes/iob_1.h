
/*  This file is part of the HWA project.
 *  Copyright (c) 2012,2015 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief I/O definition
 */

/**
 * @ingroup esp8266_classes
 * @defgroup esp8266_iob Class _iob: General Purpose I/O definition
 *
 * A class `_iob` object is a single or a group of consecutive pins inside the
 * same I/O port.
 */
#define hw_class__iob


/**
 * @addtogroup esp8266_iob
 * @par Instructions that do not produce C code:
 *
 * The `HW_BN()` instruction returns the number of bits of an I/O definition:
 *
 * @code
 * #if (HW_ADDRESS((porta,3)) != -1) && (HW_BN((porta,3)) != 1)
 * #  HWA is damaged!
 * #endif
 * @endcode
 */
#define HW_BITS__iob		, _hw_bn_iob

#define _hw_bn_iob(o, cn,bn,bp,...)	bn


/**
 * @addtogroup esp8266_iob
 *
 * For a group of consecutive pins, the `hw_bp()` instruction gives the position
 * of the least significant bit:
 *
 * @code
 * #if hw_id((porta,3)) && (hw_bp((porta,3)) != 3)
 * #  HWA is damaged!
 * #endif
 * @endcode
 */
#define HW_POSITION__iob	, _hw_bp_iob
#define _hw_bp_iob(o, cn,bn,bp,...)	bp
