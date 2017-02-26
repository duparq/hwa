
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief 23-bit timer
 */

/**
 * @page espressif_tm23a Class _tm23a: 23-bit timer
 *
 * A class `_tm23a` object is a 23-bit timer.
 *
 * It is used in:
 *
 *  * @ref esp8266 : `timer1` and `timer2`
 */
#define _hw_class__tm23a


#if !defined __ASSEMBLER__

typedef struct {
  hwa_r32_t     _load, _ctrl ;

  /* struct { */
  /*   uint32_t	baudrate ; */
  /*   uint8_t	databits, parity, stopbits, rxen, txen ; */
  /* } config ; */
  /* struct { */
  /*   uint8_t action ;	// Used at commit time */
  /* } config ; */
} hwa_tm23a_t ;

#endif
