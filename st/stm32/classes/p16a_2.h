
/* This file is part of the HWA project.
 * Copyright (c) 2017 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief GPIO port
 */


/*******************************************************************************
 *									       *
 *	Context management						       *
 *									       *
 *******************************************************************************/

#define _hwa_setup__p16a(o,i,a)			\
  _hwa_setup_reg( o, crl  );			\
  _hwa_setup_reg( o, crh  );			\
  _hwa_setup_reg( o, odr  );			\
  _hwa_setup_reg( o, bsrr );			\
  _hwa_setup_reg( o, brr  );			\
  _hwa_setup_reg( o, lckr )

#define _hwa_init__p16a(o,i,a)			\
  _hwa_init_reg( o, crl,  0x44444444 );		\
  _hwa_init_reg( o, crh,  0x44444444 );		\
  _hwa_init_reg( o, odr,  0x00000000 );		\
  _hwa_init_reg( o, bsrr, 0x00000000 );		\
  _hwa_init_reg( o, brr,  0x00000000 );		\
  _hwa_init_reg( o, lckr, 0x00000000 )

#define _hwa_commit__p16a(o,i,a)		\
  _hwa_commit_reg( o, crl  );			\
  _hwa_commit_reg( o, crh  );			\
  _hwa_commit_reg( o, odr  );			\
  _hwa_commit_reg( o, bsrr );			\
  _hwa_commit_reg( o, brr  );			\
  _hwa_commit_reg( o, lckr )

#define _hwa__p16a(f,o)				\
  _hwa_##f##_reg( o, crl,  0x44444444 );	\
  _hwa_##f##_reg( o, crh,  0x44444444 );	\
  _hwa_##f##_reg( o, odr,  0x00000000 );	\
  _hwa_##f##_reg( o, bsrr, 0x00000000 );	\
  _hwa_##f##_reg( o, brr,  0x00000000 );	\
  _hwa_##f##_reg( o, lckr, 0x00000000 )


/**
 * @page atmelavr_p16a Class _p16a: 8-bit I/O port
 * <br>
 */
