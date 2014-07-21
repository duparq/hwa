
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

#include "hwa_atmelavr_usia_2.h"


HW_INLINE void _hwa_begin_usis ( hwa_t *hwa )
{
  HWA_INIT(hw_usi0, cr);
  HWA_INIT(hw_usi0, sr);
  HWA_INIT(hw_usi0, dr);
}


HW_INLINE void _hwa_reset_usis ( hwa_t *hwa )
{
  _hwa_reset_r8( &hwa->usi0.cr );
  _hwa_reset_r8( &hwa->usi0.sr );
  _hwa_reset_r8( &hwa->usi0.dr );
}


HW_INLINE void _hwa_commit_usis ( hwa_t *hwa )
{
  _hwa_commit_r8( hwa->commit, &hwa->usi0.cr, -1 );
  _hwa_commit_r8( hwa->commit, &hwa->usi0.sr, -1 );
  _hwa_commit_r8( hwa->commit, &hwa->usi0.dr, -1 );
}
