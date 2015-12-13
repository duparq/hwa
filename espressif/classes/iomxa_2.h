
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief I/O multiplexer _iomxa
 */

/**
 * @page espressif_iomxa
 *
 */


/*******************************************************************************
 *									       *
 *	HWA Context							       *
 *									       *
 *******************************************************************************/

#define _hwa_setup__iomxa(o,i,a)		\
  _hwa_setup_reg( o, _conf );			\
  _hwa_setup_reg( o, hw_pin_gpio0 );		\
  _hwa_setup_reg( o, hw_pin_gpio1 );		\
  _hwa_setup_reg( o, hw_pin_gpio2 );		\
  _hwa_setup_reg( o, hw_pin_gpio3 );		\
  _hwa_setup_reg( o, hw_pin_gpio4 );		\
  _hwa_setup_reg( o, hw_pin_gpio5 );		\
  _hwa_setup_reg( o, hw_pin_gpio6 );		\
  _hwa_setup_reg( o, hw_pin_gpio7 );		\
  _hwa_setup_reg( o, hw_pin_gpio8 );		\
  _hwa_setup_reg( o, hw_pin_gpio9 );		\
  _hwa_setup_reg( o, hw_pin_gpio10 );		\
  _hwa_setup_reg( o, hw_pin_gpio11 );		\
  _hwa_setup_reg( o, hw_pin_gpio12 );		\
  _hwa_setup_reg( o, hw_pin_gpio13 );		\
  _hwa_setup_reg( o, hw_pin_gpio14 );		\
  _hwa_setup_reg( o, hw_pin_gpio15 )

#define _hwa_init__iomxa(o,i,a)			
  /* _hwa_init_reg( o, _conf, 0 );			\ */
  /* _hwa_init_reg( o, hw_pin_gpio0, 0 );		\ */
  /* _hwa_init_reg( o, hw_pin_gpio1, 0 );		\ */
  /* _hwa_init_reg( o, hw_pin_gpio2, 0 );		\ */
  /* _hwa_init_reg( o, hw_pin_gpio3, 0 );		\ */
  /* _hwa_init_reg( o, hw_pin_gpio4, 0 );		\ */
  /* _hwa_init_reg( o, hw_pin_gpio5, 0 );		\ */
  /* _hwa_init_reg( o, hw_pin_gpio6, 0 );		\ */
  /* _hwa_init_reg( o, hw_pin_gpio7, 0 );		\ */
  /* _hwa_init_reg( o, hw_pin_gpio8, 0 );		\ */
  /* _hwa_init_reg( o, hw_pin_gpio9, 0 );		\ */
  /* _hwa_init_reg( o, hw_pin_gpio10, 0 );		\ */
  /* _hwa_init_reg( o, hw_pin_gpio11, 0 );		\ */
  /* _hwa_init_reg( o, hw_pin_gpio12, 0 );		\ */
  /* _hwa_init_reg( o, hw_pin_gpio13, 0 );		\ */
  /* _hwa_init_reg( o, hw_pin_gpio14, 0 );		\ */
  /* _hwa_init_reg( o, hw_pin_gpio15, 0 ) */

#define _hwa_commit__iomxa(o,i,a)		\
  _hwa_commit_reg( o, _conf );			\
  _hwa_commit_reg( o, hw_pin_gpio0 );		\
  _hwa_commit_reg( o, hw_pin_gpio1 );		\
  _hwa_commit_reg( o, hw_pin_gpio2 );		\
  _hwa_commit_reg( o, hw_pin_gpio3 );		\
  _hwa_commit_reg( o, hw_pin_gpio4 );		\
  _hwa_commit_reg( o, hw_pin_gpio5 );		\
  _hwa_commit_reg( o, hw_pin_gpio6 );		\
  _hwa_commit_reg( o, hw_pin_gpio7 );		\
  _hwa_commit_reg( o, hw_pin_gpio8 );		\
  _hwa_commit_reg( o, hw_pin_gpio9 );		\
  _hwa_commit_reg( o, hw_pin_gpio10 );		\
  _hwa_commit_reg( o, hw_pin_gpio11 );		\
  _hwa_commit_reg( o, hw_pin_gpio12 );		\
  _hwa_commit_reg( o, hw_pin_gpio13 );		\
  _hwa_commit_reg( o, hw_pin_gpio14 );		\
  _hwa_commit_reg( o, hw_pin_gpio15 )


/**
 * @page espressif_iomxa
 * <br>
 */
