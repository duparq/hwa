
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 */

/**
 * @page atmelavr_pcica Class _pcica: pin change interrupt controller
 *
 * A class `_pcica` object is a pin change interrupt controller.
 *
 * This class implements a global pin change controller that manages any of the
 * pins that have this feature. This is a single object though it can trigger
 * different IRQs.
 */
#define _hw_class__pcica


#if !defined __ASSEMBLER__

typedef struct {
  hwa_r8_t 	msk0 ;
  hwa_r8_t 	msk1 ;
} hwa_pcica_t ;

#endif