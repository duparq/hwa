
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


HW_INLINE void hwa_begin_adcs ( hwa_t *hwa )
{
  HWA_INIT(hw_adc0, admux);
  HWA_INIT(hw_adc0, sra);
  HWA_INIT(hw_adc0, srb);
  HWA_INIT(hw_adc0, did);
}


HW_INLINE void hwa_commit_adcs ( hwa_t *hwa )
{
  hwa_commit_8( hwa->commit, &hwa->adc0.admux, -1 );
  hwa_commit_8( hwa->commit, &hwa->adc0.sra, -1 );
  hwa_commit_8( hwa->commit, &hwa->adc0.srb, -1 );
  hwa_commit_8( hwa->commit, &hwa->adc0.did, -1 );
}
