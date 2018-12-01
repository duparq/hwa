
/*  This file is part of the HWA project.
 *  Copyright (c) 2012,2015 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief General purpose I/O port (_p16a)
 */

/*******************************************************************************
 *									       *
 *	HWA Context							       *
 *									       *
 *******************************************************************************/

#define _hwa_setup__p16a(o,i,a)		\
  _hwa_setup_r( o, _out );			\
  _hwa_setup_r( o, _enb );			\
  _hwa_setup_r( o, _in );			\
  _hwa_setup_r( o, _ie )

#define _hwa_init__p16a(o,i,a)

#define _hwa_commit__p16a(o,i,a)		\
  _hwa_commit_r( o, _out );			\
  _hwa_commit_r( o, _enb );			\
  _hwa_commit_r( o, _in );			\
  _hwa_commit_r( o, _ie )


/**
 * @page espressif_p16a
 * <br>
 */
