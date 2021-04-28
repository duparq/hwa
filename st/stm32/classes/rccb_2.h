
/* This file is part of the HWA project.
 * Copyright (c) 2021 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Clocks
 */

#include "hsia_2.h"
#include "hsea_2.h"
#include "pllb_2.h"
#include "sclka_2.h"
#include "ahba_2.h"
#include "apba_2.h"
#include "usba_2.h"


/*******************************************************************************
 *									       *
 *	HWA context							       *
 *									       *
 *******************************************************************************/

#define _hwa_setup__rccb(o,a)			\
  _hwa_setup_r( o, cr	   );			\
  _hwa_setup_r( o, pllcfgr );			\
  _hwa_setup_r( o, cfgr	   );			\
  _hwa_setup_r( o, cir     );			\
  _hwa_setup_r( o, ahb1enr );			\
  _hwa_setup_r( o, apb1enr )

#define _hwa_init__rccb(o,a)			\
  _hwa_init_r( o, cr,	   0x00000081 );	\
  _hwa_init_r( o, pllcfgr, 0x24003010 );	\
  _hwa_init_r( o, cfgr,	   0x00000000 );	\
  _hwa_init_r( o, cir,     0x00000000 );	\
  _hwa_init_r( o, ahb1enr, 0x00000000 );	\
  _hwa_init_r( o, apb1enr, 0x00000000 )

#define _hwa_commit__rccb(o,a)		\
  _hwa_commit_r( o, cr	    );		\
  _hwa_commit_r( o, pllcfgr );		\
  _hwa_commit_r( o, cfgr    );		\
  _hwa_commit_r( o, cir     );		\
  _hwa_commit_r( o, ahb1enr );		\
  _hwa_commit_r( o, apb1enr )
