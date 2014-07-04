
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


#include "hwa_atmelavr_counters_2.h"
#include "hwa_atmelavr_c8a_2.h"
#include "hwa_atmelavr_c16a_2.h"


#define hwa_begin_ocu(cn)			\
  hwa->cn.config = 0 ;				\
  hwa->cn.mode = 0


HW_INLINE void _hwa_begin_counters ( hwa_t *hwa )
{
  hwa_begin_c8a( counter0 );
  hwa_begin_ocu( oc0a );
  hwa_begin_ocu( oc0b );
  hwa_begin_c16a( counter1 );
}


HW_INLINE void _hwa_solve_counters ( hwa_t *hwa )
{
  hwa_solve_c8a( &hwa->counter0 );
  hwa_solve_c8aoc1( &hwa->counter0, &hwa->oc0a );
  hwa_solve_c8aoc2( &hwa->counter0, &hwa->oc0b );
  hwa_solve_c16a( &hwa->counter1 );

  /*  Output-compare pins must be configured as outputs when used
   */
  /* if ( hwa->counter0.oca_mode != 0 ) */
  /*   hwa_config( hw_io(hw_oc0a), output ); */
  /* if ( hwa->counter0.ocb_mode != 0 ) */
  /*   hwa_config( hw_io(hw_oc0b), output ); */

  if ( hwa->counter1.ocra_config != 0
       && hwa->counter1.ocra_mode != 0 )
    hwa_config( hw_io(hw_oc1a), output );
  if ( hwa->counter1.ocrb_config != 0
       && hwa->counter1.ocrb_mode != 0 )
    hwa_config( hw_io(hw_oc1b), output );
}


HW_INLINE void _hwa_reset_counters ( hwa_t *hwa )
{
  _hwa_reset_c8a( &hwa->counter0 );
  _hwa_reset_c16a( &hwa->counter1 );
}


HW_INLINE void _hwa_commit_counters ( hwa_t *hwa )
{
  _hwa_commit_c8a( hwa, &hwa->counter0 );
  _hwa_commit_c16a( hwa, &hwa->counter1 );
}
