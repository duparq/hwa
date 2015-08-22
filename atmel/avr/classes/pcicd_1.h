
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 */

/**
 * @page atmelavr_pcicd Class _pcicd: pin change interrupt controller
 *
 * A class `_pcicd` object is a pin change interrupt controller.
 *
 * This class implements a global pin change controller that manages any of the
 * pins that have this feature.
 *
 * It is used in:
 *
 * * @ref attinyx5
 */
#define _hw_class__pcicd


#if !defined __ASSEMBLER__

typedef struct {
  hwa_r8_t 	msk0 ;
} hwa_pcicd_t ;

#endif
