
/* This file is part of the HWA project.
 * Copyright (c) 2019 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief AFIO
 */

/**
 * @page stm32_afioa
 */
#define hw_class__afioa


/*******************************************************************************
 *									       *
 *	Context								       *
 *									       *
 *******************************************************************************/

#define _hwa_setup__afioa(o,i,a)		\
  _hwa_setup_r( o, mapr )

#define _hwa_init__afioa(o,i,a)			\
  _hwa_init_r( o, mapr,  0x00000000 )

#define _hwa_commit__afioa(o,i,a)		\
  _hwa_commit_r( o, mapr )
