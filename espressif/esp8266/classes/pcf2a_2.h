
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief I/O configurator
 */

/**
 * @page espressif_pcf2a
 *
 */


/*******************************************************************************
 *									       *
 *	HWA Context							       *
 *									       *
 *******************************************************************************/

#define _hwa_setup__pcf2a(o,i,a)		\
  _hwa_setup_reg( o, _reg )

#define _hwa_init__pcf2a(o,i,a)			

#define _hwa_commit__pcf2a(o,i,a)		\
  _hwa_commit_reg( o, _reg )
