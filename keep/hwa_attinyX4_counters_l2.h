
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


/* #include "hwa_l2_atmelavr_counters.h" */
#include "hwa_atmelavr_c8a_l2.h"
#include "hwa_atmelavr_c16a_l2.h"

HW_INLINE void hwa_begin_counters ( hwa_t *hwa )
{
  hwa_begin_c8a( counter0 );
  hwa_begin_c8aoc( oc0a );
  hwa_begin_c8aoc( oc0b );
  hwa_begin_c16a( hw_counter1 );
}


HW_INLINE void hwa_solve_counters ( hwa_t *hwa )
{
  hwa_solve_counter0( hwa );
  hwa_solve_oc0a( hwa );
  hwa_solve_oc0b( hwa );
  //  hwa_solve_c16a( hwa, &hwa->counter1 );
}


HW_INLINE void hwa_commit_counters ( hwa_t *hwa )
{
  hwa_commit_c8a( hwa, &hwa->counter0 );
  hwa_commit_c16a( hwa, &hwa->counter1 );
}
