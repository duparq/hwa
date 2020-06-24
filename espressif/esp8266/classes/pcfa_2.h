
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief I/O configurator
 */

/*******************************************************************************
 *									       *
 *	HWA Context							       *
 *									       *
 *******************************************************************************/

#define _hwa_setup__pcfa(o,a)		\
  _hwa_setup_r( o, _reg )

#define _hwa_init__pcfa(o,a)			

#define _hwa_commit__pcfa(o,a)		\
  _hwa_commit_r( o, _reg )
