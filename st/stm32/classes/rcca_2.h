
/* This file is part of the HWA project.
 * Copyright (c) 2017 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Clocks
 */


/*******************************************************************************
 *									       *
 *	Context management						       *
 *									       *
 *******************************************************************************/

#define _hwa_setup__rcca(o,i,a)			\
  _hwa_setup_reg( o, apb2enr )

#define _hwa_init__rcca(o,i,a)			\
  _hwa_init_reg( o, apb2enr,  0x00000000 )

#define _hwa_commit__rcca(o,i,a)		\
  _hwa_commit_reg( o, apb2enr  )

#define _hwa__rcca(f,o)				\
  _hwa_##f##_reg( o, apb2enr,  0x00000000 )


/**
 * @page atmelavr_rcca Class _rcca: 8-bit I/O port
 * <br>
 */
