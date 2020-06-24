
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief RTC
 */


/*******************************************************************************
 *									       *
 *	HWA Context							       *
 *									       *
 *******************************************************************************/

#define _hwa_setup__rtca(o,a)			\
  _hwa_setup_r( o, _gpioout );		\
  _hwa_setup_r( o, _gpioen );			\
  _hwa_setup_r( o, _gpiocf );			\
  _hwa_setup_r( o, _gpiocr )
/* _hwa_setup_r( o, _store0 );			\ */
/* _hwa_setup_r( o, _store1 );			\ */
/* _hwa_setup_r( o, _store2 );			\ */
/* _hwa_setup_r( o, _store3 );			\ */
/* _hwa_setup_r( o, _gpioin );			\ */

#define _hwa_init__rtca(o,a)			\
  _hwa_init_r( o, _gpioout, 0 );		\
  _hwa_init_r( o, _gpioen,  0 );		\
  _hwa_init_r( o, _gpiocf, 0 );		\
  _hwa_init_r( o, _gpiocr, 0 )
/* _hwa_init_r( o, _store0,  0 );		\ */
/* _hwa_init_r( o, _store1,  0 );		\ */
/* _hwa_init_r( o, _store2,  0 );		\ */
/* _hwa_init_r( o, _store3,  0 );		\ */
/* _hwa_init_r( o, _gpioin,  0 );		\ */

#define _hwa_commit__rtca(o,a)		\
  _hwa_commit_r( o, _gpioout );		\
  _hwa_commit_r( o, _gpioen );		\
  _hwa_commit_r( o, _gpiocf );		\
  _hwa_commit_r( o, _gpiocr )
/* _hwa_commit_r( o, _store0 );		\ */
/* _hwa_commit_r( o, _store1 );		\ */
/* _hwa_commit_r( o, _store2 );		\ */
/* _hwa_commit_r( o, _store3 );		\ */
/* _hwa_commit_r( o, _gpioin );		\ */
