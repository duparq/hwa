
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
 * @defgroup esp8266_ioa Class _ioa: General Purpose I/O definition
 *
 * A class `_ioa` object is a single or a group of consecutive pins inside the
 * same I/O port.
 */
#define hw_class__ioa


/**
 * @addtogroup esp8266_ioa
 * @par Instructions that do not produce C code:
 *
 * The `hw_bn()` instruction returns the number of bits of an I/O definition:
 *
 * @code
 * #if (HW_ADDRESS((porta,3)) != -1) && (HW_BITS((porta,3)) != 1)
 * #  HWA is damaged!
 * #endif
 * @endcode
 */
#define HW_BITS__ioa		, _hw_bn_ioa

#define _hw_bn_ioa(o, cn,bn,bp,...)	       bn


/**
 * @addtogroup esp8266_ioa
 *
 * For a group of consecutive pins, the `hw_bp()` instruction gives the position
 * of the least significant bit:
 *
 * @code
 * #if (HW_ADDRESS((porta,3)) != -1) && (HW_POSITION((porta,3)) != 3)
 * #  HWA is damaged!
 * #endif
 * @endcode
 */
#define HW_POSITION__ioa		, _hw_bp_ioa
#define _hw_bp_ioa(o, cn,bn,bp,...)	       bp
