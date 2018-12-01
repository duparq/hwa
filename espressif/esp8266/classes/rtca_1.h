
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief RTC
 */

/**
 * @page espressif_rtca Class _rtca: RTC
 *
 */
#define hw_class__rtca


#if !defined __ASSEMBLER__

typedef struct {
  /* hwa_r32_t	_store0, _store1, _store2, _store3 ; */
  hwa_r32_t	_gpioout ;
  hwa_r32_t	_gpioen ;
  /* hwa_r32_t	_gpioin ; */
  hwa_r32_t	_gpiocf ;
  /* hwa_r32_t	_padxpddcdcconf ; */
  hwa_r32_t	_gpiocr ;
} hwa_rtca_t ;

#endif
