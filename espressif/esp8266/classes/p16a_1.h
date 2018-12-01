
/*  This file is part of the HWA project.
 *  Copyright (c) 2012,2015 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief General purpose I/O port (_p16a)
 */

/**
 * @page espressif_p16a Class _p16a: 16-bit I/O port
 *
 * A class `_p16a` object is a 16-bit I/O port.
 *
 * It is used in:
 *  * @ref esp8266
 */
#define hw_class__p16a


#if !defined __ASSEMBLER__

typedef struct {
  hwa_r32_t	_conf;
  hwa_r32_t	_out ;
  /* hwa_r32_t	_outw1ts ; */
  /* hwa_r32_t	_outw1tc ; */
  hwa_r32_t	_enb ;
  /* hwa_r32_t	_enbw1ts ; */
  /* hwa_r32_t	_enbw1tc ; */
  hwa_r32_t	_in ;
  hwa_r32_t	_ie ;
  /* hwa_r32_t	_iew1ts ; */
  /* hwa_r32_t	_iew1tc ; */
} hwa_p16a_t ;

#endif
