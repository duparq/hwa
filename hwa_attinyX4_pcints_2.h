
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

HW_INLINE void _hwa_begin_pcints ( hwa_t *hwa )
{
  _hwa_begin_reg( hw_pcic0, msk );
  _hwa_begin_reg( hw_pcic1, msk );
}


HW_INLINE void _hwa_reset_pcints ( hwa_t *hwa )
{
  _hwa_reset_r8( &hwa->pcic0.msk );
  _hwa_reset_r8( &hwa->pcic1.msk );
}


HW_INLINE void _hwa_commit_pcints ( hwa_t *hwa )
{
  _hwa_commit_r8( hwa->commit, &hwa->pcic0.msk, -1 );
  _hwa_commit_r8( hwa->commit, &hwa->pcic1.msk, -1 );
}
