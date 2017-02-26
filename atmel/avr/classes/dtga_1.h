
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Dead time generator
 */

/**
 * @page atmelavr_dtga Class _dtga: dead time generator
 *
 * A class `_dtga` object is a dead time generator.
 *
 * It is used in:
 *
 * * @ref attinyx5 : `dtg1`
 */
#define _hw_class__dtga


#if !defined __ASSEMBLER__

typedef struct {

  /*  Hardware registers
   */
  hwa_r8_t	dtps, dta, dtb ;

  /*  Registers used for high-level configuration
   */
  struct {
    uint8_t	clock ;
  } config ;

} hwa_dtga_t ;

#endif
