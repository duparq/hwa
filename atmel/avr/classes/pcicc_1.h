
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 */

/**
 * @page atmelavr_pcicc Class _pcicc: pin change interrupt controller
 *
 * A class `_pcicc` object is a pin change interrupt controller.
 *
 * This class implements a pin change controller that manages any of the
 * pins that have this feature.
 *
 * It is used in:
 *
 *  * Atmel ATtiny25/45/85
 */
#define _hw_class__pcicc


#if !defined __ASSEMBLER__

typedef struct {
  hwa_r8_t 	msk ;
} hwa_pcicc_t ;

#endif
