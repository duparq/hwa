
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief I/O configurator
 */

/**
 * @page espressif_pcfb
 *
 */


/*******************************************************************************
 *									       *
 *	HWA Context							       *
 *									       *
 *******************************************************************************/

#define _hwa_setup__pcfb(o,i,a)		\
  _hwa_setup_or( o, _reg )

#define _hwa_init__pcfb(o,i,a)			

#define _hwa_commit__pcfb(o,i,a)		\
  _hwa_commit_or( o, _reg )


/**
 * @page espressif_pcfb
 * <br>
 */
