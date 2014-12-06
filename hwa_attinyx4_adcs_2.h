
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

#include "hwa_atmelavr_ad10a_2.h"


HW_INLINE void _hwa_begin_adcs ( hwa_t *hwa )
{
  _hwa_begin_reg( hw_adc0, admux );
  _hwa_begin_reg( hw_adc0, sra   );
  _hwa_begin_reg( hw_adc0, srb   );
  _hwa_begin_reg( hw_adc0, did   );
}


HW_INLINE void _hwa_init_adcs ( hwa_t *hwa )
{
  _hwa_set_r8( &hwa->adc0.admux, 0x00 );
  _hwa_set_r8( &hwa->adc0.sra,   0x00 );
  _hwa_set_r8( &hwa->adc0.srb,   0x00 );
  _hwa_set_r8( &hwa->adc0.did,   0x00 );
}


HW_INLINE void _hwa_commit_adcs ( hwa_t *hwa )
{
  _hwa_commit_reg( hw_adc0, admux, hwa->commit );
  _hwa_commit_reg( hw_adc0, sra,   hwa->commit );
  _hwa_commit_reg( hw_adc0, srb,   hwa->commit );
  _hwa_commit_reg( hw_adc0, did,   hwa->commit );
}
