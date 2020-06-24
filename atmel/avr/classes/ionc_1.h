
/*  This file is part of the HWA project.
 *  Copyright (c) 2012,2015 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief I/O (not connected).
 */

/**
 * @ingroup atmelavr_classes
 * @defgroup atmelavr_ionc Class _ionc: General Purpose Input/Output
 *
 * A class `_ionc` object is a not connected pin.
 */
#define hw_class__ionc


#define HW_BITS__ionc			, _hw_bn_ionc
#define _hw_bn_ionc(o, cn,bn,bp,...)	0
