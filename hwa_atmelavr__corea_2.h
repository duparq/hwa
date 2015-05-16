
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


/** @page atmelavr_corea
 *  @par Configuring the core
 *
 *  @code
 *  hwa_config( CORE,
 *
 *              [sleep,        enabled,
 *                           | disabled,]
 *
 *              [sleep_mode,   idle
 *                           | adc_noise_reduction
 *                           | power_down
 *                           | standby]             );
 *  @endcode
 */

/** @page atmelavr_corea
 *  @par Entering sleep
 *
 *  @code
 *  hw_sleep();
 *  @endcode
 */

#define corex		corea
#define atmelavr_corex	atmelavr_corea

#include "hwa_atmelavr__corex_2.h"

/*	Class methods
 */
#define _hw_mthd_hwa_config__corea	, _hwa_config_core
#define _hw_mthd_hw_stat__corea		, _hw_stat_core
#define _hw_mthd_hwa_clear__corea	, _hwa_clear_core


HW_INLINE void __hwa_begin__corea ( hwa_corea_t *p, intptr_t a )
{
  _hwa_begin_reg_p( p, a, _corea, gimsk  );
  _hwa_begin_reg_p( p, a, _corea, gifr   );
  _hwa_begin_reg_p( p, a, _corea, mcucr  );
  _hwa_begin_reg_p( p, a, _corea, mcusr  );
  _hwa_begin_reg_p( p, a, _corea, osccal );
  _hwa_begin_reg_p( p, a, _corea, gpior2 );
  _hwa_begin_reg_p( p, a, _corea, gpior1 );
  _hwa_begin_reg_p( p, a, _corea, gpior0 );
  _hwa_begin_reg_p( p, a, _corea, prr    );
}



HW_INLINE void __hwa_init__corea ( hwa_corea_t *p )
{
  _hwa_set_r8( &p->gimsk,  0x00 );
  _hwa_set_r8( &p->gifr,   0x00 );
  _hwa_set_r8( &p->mcucr,  0x00 );
  //  mcusr is not initialized as its status is not known after RESET
  _hwa_set_r8( &p->osccal, 0x00 );
  _hwa_set_r8( &p->gpior2, 0x00 );
  _hwa_set_r8( &p->gpior1, 0x00 );
  _hwa_set_r8( &p->gpior0, 0x00 );
  _hwa_set_r8( &p->prr,    0x00 );
}


HW_INLINE void __hwa_commit__corea ( hwa_t *hwa, hwa_corea_t *p )
{
  _hwa_commit_reg_p( p, _corea, gimsk  );
  _hwa_commit_reg_p( p, _corea, gifr   );
  _hwa_commit_reg_p( p, _corea, mcucr  );
  _hwa_commit_reg_p( p, _corea, mcusr  );
  _hwa_commit_reg_p( p, _corea, osccal );
  _hwa_commit_reg_p( p, _corea, gpior2 );
  _hwa_commit_reg_p( p, _corea, gpior1 );
  _hwa_commit_reg_p( p, _corea, gpior0 );
  _hwa_commit_reg_p( p, _corea, prr    );
}
