
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/*	DO NOT USE!
 *
 *	This is a temporary file, for experimentation. <hwa/twimaster.h> should be used instead.
 */

#error Do not use this!

/*
 * @file
 * @brief I/O configurator
 */

/*
 * @page espressif_pcf2a
 *
 */


/*******************************************************************************
 *									       *
 *	HWA Context							       *
 *									       *
 *******************************************************************************/

#define _hwa_setup__pcf2a(o,a)		\
  _hwa_setup_reg( o, _reg )

#define _hwa_init__pcf2a(o,a)			

#define _hwa_commit__pcf2a(o,a)		\
  _hwa_commit_reg( o, _reg )
