
/*	Atmel AVR pin change interrupt controller model 'a'
 *
 * This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


/**
 * @page atmelavr_pcica Class _pcica: pin change interrupt controller
 *
 * A class `_pcica` object is an pin change interrupt controller.
 */
#define _hw_class__pcica


#if !defined __ASSEMBLER__

typedef struct {
  hwa_r8_t 	msk0 ;
  hwa_r8_t 	msk1 ;
} hwa_pcica_t ;

#endif
