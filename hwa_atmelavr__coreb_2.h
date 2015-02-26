
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


#include "hwa_atmelavr__core_2.h"

//#define hw_def_hw_config__coreb		, _hw_config_coreb
#define hw_def_hwa_config__coreb	, _hwa_config_core
#define hw_def_hw_stat__coreb		, _hw_stat_core
#define hw_def_hwa_clear__coreb		, _hwa_clear_core


HW_INLINE void __hwa_begin__coreb ( hwa_coreb_t *p, intptr_t a )
{
  _hwa_begin_pacr( p, a, _coreb, eimsk  );
  _hwa_begin_pacr( p, a, _coreb, eifr   );
  _hwa_begin_pacr( p, a, _coreb, mcucr  );
  _hwa_begin_pacr( p, a, _coreb, mcusr  );
  _hwa_begin_pacr( p, a, _coreb, smcr   );
  _hwa_begin_pacr( p, a, _coreb, osccal );
  _hwa_begin_pacr( p, a, _coreb, gpior2 );
  _hwa_begin_pacr( p, a, _coreb, gpior1 );
  _hwa_begin_pacr( p, a, _coreb, gpior0 );
  _hwa_begin_pacr( p, a, _coreb, prr    );
}


HW_INLINE void __hwa_init__coreb ( hwa_coreb_t *p )
{
  _hwa_set_r8( &p->eimsk,  0x00 );
  _hwa_set_r8( &p->eifr,   0x00 );
  _hwa_set_r8( &p->mcucr,  0x00 );
  //  mcusr is not initialized as its status is not known after RESET
  _hwa_set_r8( &p->smcr,   0x00 );
  _hwa_set_r8( &p->osccal, 0x00 );
  _hwa_set_r8( &p->gpior2, 0x00 );
  _hwa_set_r8( &p->gpior1, 0x00 );
  _hwa_set_r8( &p->gpior0, 0x00 );
  _hwa_set_r8( &p->prr,    0x00 );
}


HW_INLINE void __hwa_commit__coreb ( hwa_t *hwa, hwa_coreb_t *p )
{
  _hwa_commit_pcr( p, _coreb, eimsk  );
  _hwa_commit_pcr( p, _coreb, eifr   );
  _hwa_commit_pcr( p, _coreb, mcucr  );
  _hwa_commit_pcr( p, _coreb, mcusr  );
  _hwa_commit_pcr( p, _coreb, smcr   );
  _hwa_commit_pcr( p, _coreb, osccal );
  _hwa_commit_pcr( p, _coreb, gpior2 );
  _hwa_commit_pcr( p, _coreb, gpior1 );
  _hwa_commit_pcr( p, _coreb, gpior0 );
  _hwa_commit_pcr( p, _coreb, prr    );
}
