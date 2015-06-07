
/*	Atmel AVR pin change interrupt controller model 'a'
 *
 * This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */


/**
 * @page atmelavr_pcicb Class _pcicb: pin change interrupt controller
 *
 * A class `_pcicb` object is a pin change interrupt controller.
 *
 * This class implements a global pin change controller that manages any of the
 * pins that have this feature. This is a single object though it can trigger
 * different IRQs.
 */
#define _hw_class__pcicb


#if !defined __ASSEMBLER__

typedef struct {
  hwa_r8_t 	fr, cr ;
  hwa_r8_t 	msk0, msk1, msk2 ;
} hwa_pcicb_t ;

#endif
