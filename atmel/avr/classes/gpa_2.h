
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief I/O port
 */


/*******************************************************************************
 *									       *
 *	Context management						       *
 *									       *
 *******************************************************************************/

#define _hwa_setup__gpa(o,a)			\
  _hwa_setup_r( o, port );			\
  _hwa_setup_r( o, ddr	)

#define _hwa_init__gpa(o,a)			\
  _hwa_init_r( o, port, 0x00 );			\
  _hwa_init_r( o, ddr,	0x00 )

#define _hwa_commit__gpa(o,a)			\
  _hwa_commit_r( o, port );			\
  _hwa_commit_r( o, ddr	 )
