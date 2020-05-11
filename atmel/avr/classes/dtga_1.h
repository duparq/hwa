
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
 * `_dtga` objects are dead time generators.
 *
 * They are used in:
 *
 * * @ref attinyx5 : `dtg1`
 */
#define hw_class__dtga


#if !defined __ASSEMBLER__

typedef struct {

  /*  Registers used for high-level configuration
   */
  struct {
    uint8_t	clock ;
  } config ;

} hwa_dtga_t ;

#endif
