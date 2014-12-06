
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

#include "hwa_atmelavr_usia_2.h"


HW_INLINE void _hwa_begin_usis ( hwa_t *hwa )
{
  _hwa_begin_reg( hw_usi0, cr );
  _hwa_begin_reg( hw_usi0, sr );
  _hwa_begin_reg( hw_usi0, dr );
}


HW_INLINE void _hwa_init_usis ( hwa_t *hwa )
{
  _hwa_set_r8( &hwa->usi0.cr, 0x00 );
  _hwa_set_r8( &hwa->usi0.sr, 0x00 );
  _hwa_set_r8( &hwa->usi0.dr, 0x00 );
}


HW_INLINE void _hwa_commit_usis ( hwa_t *hwa )
{
  _hwa_commit_reg( hw_usi0, cr, hwa->commit );
  _hwa_commit_reg( hw_usi0, sr, hwa->commit );
  _hwa_commit_reg( hw_usi0, dr, hwa->commit );
}
