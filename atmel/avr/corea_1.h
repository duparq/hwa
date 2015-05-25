
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Definitions for Atmel AVR core model 'a' that do not produce C code
 *
 *	Used in: ATtinyX4
 *		 ATtinyX5
 *
 */

/**
 * @page atmelavr_corea Class _corea: core of the device
 * A class `_corea` object is a core of the device.
 */
#define _hw_class__corea


/*  Register definitions
 */
#define _hw__corea_bods		_cb1, mcucr, 1, 7
#define _hw__corea_pud		_cb1, mcucr, 1, 6
#define _hw__corea_se		_cb1, mcucr, 1, 5
#define _hw__corea_sm		_cb1, mcucr, 2, 3
#define _hw__corea_bodse	_cb1, mcucr, 1, 2
#define _hw__corea_isc0		_cb1, mcucr, 2, 0

#define _hw__corea_wdrf		_cb1, mcusr, 1, 3
#define _hw__corea_borf		_cb1, mcusr, 1, 2
#define _hw__corea_extrf	_cb1, mcusr, 1, 1
#define _hw__corea_porf		_cb1, mcusr, 1, 0
#define _hw__corea_allrf	_cb1, mcusr, 4, 0	/* convenient */

#define _hw__corea_int0		_cb1, gimsk, 1, 6
#define _hw__corea_pcie1	_cb1, gimsk, 1, 5
#define _hw__corea_pcie0	_cb1, gimsk, 1, 4

#define _hw__corea_intf0	_cb1, gifr, 1, 6
#define _hw__corea_pcif1	_cb1, gifr, 1, 5
#define _hw__corea_pcif0	_cb1, gifr, 1, 4

#define _hw__corea_prtim1	_cb1, prr, 1, 3
#define _hw__corea_prtim0	_cb1, prr, 1, 2
#define _hw__corea_prusi	_cb1, prr, 1, 1
#define _hw__corea_pradc	_cb1, prr, 1, 0


#if !defined __ASSEMBLER__

typedef struct {
  hwa_r8_t sreg ;
  hwa_r8_t gimsk ;
  hwa_r8_t gifr ;
  hwa_r8_t mcucr ;
  hwa_r8_t mcusr ;
  hwa_r8_t osccal ;
  hwa_r8_t gpior2 ;
  hwa_r8_t gpior1 ;
  hwa_r8_t gpior0 ;
  hwa_r8_t prr ;
} hwa_corea_t ;

#endif
