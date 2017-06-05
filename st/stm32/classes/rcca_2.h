
/* This file is part of the HWA project.
 * Copyright (c) 2017 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Clocks
 */

#include "sclka_2.h"
#include "plla_2.h"
#include "ahba_2.h"
#include "apba_2.h"
#include "a12a_2.h"
#include "usba_2.h"
#include "hsia_2.h"
#include "hsea_2.h"

/**
 * @page stm32_rcca
 *
 * The `_rcca` class is not used directly. It holds hardware registers shared by
 * several objects to access the device's RCC in order to configure the
 * different clocks of the device.
 *
 * The RCC is also used transparently by several other objects to enable/disable
 * their clocking for power management purpose.
 *
 * <br>
 */



/*******************************************************************************
 *									       *
 *	Context management						       *
 *									       *
 *******************************************************************************/

#define _hwa_setup__rcca(o,i,a)			\
  _hwa_setup_reg( o, cr      );			\
  _hwa_setup_reg( o, cfgr    );			\
  _hwa_setup_reg( o, apb2enr )

#define _hwa_init__rcca(o,i,a)			\
  _hwa_init_reg( o, cr,      0x00000083 );	\
  _hwa_init_reg( o, cfgr,    0x00000000 );	\
  _hwa_init_reg( o, apb2enr, 0x00000000 )

#define _hwa_commit__rcca(o,i,a)		\
  _hwa_commit_reg( o, cr      );		\
  _hwa_commit_reg( o, cfgr    );		\
  _hwa_commit_reg( o, apb2enr )
