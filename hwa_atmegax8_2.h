
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

#include "hwa_atmelavr_2.h"

#include "hwa_atmegax8_cores_2.h"
/* #include "hwa_atmegax8_pcints_2.h" */
#include "hwa_atmegax8_ios_2.h"
/* #include "hwa_atmegax8_counters_2.h" */
/* //#include "hwa_atmegax8_pscs_2.h" */
/* #include "hwa_atmegax8_usis_2.h" */
/* #include "hwa_atmegax8_acmps_2.h" */
/* #include "hwa_atmegax8_adcs_2.h" */
/* #include "hwa_atmegax8_watchdogs_2.h" */


HW_INLINE void _hwa_begin_all ( hwa_t *hwa )
{
  _hwa_begin_cores(hwa);
  /* _hwa_begin_pcints(hwa); */
  _hwa_begin_ios(hwa);
  /* _hwa_begin_counters(hwa); */
  /* _hwa_begin_usis(hwa); */
  /* _hwa_begin_acmps(hwa); */
  /* _hwa_begin_adcs(hwa); */
  /* _hwa_begin_watchdogs(hwa); */
}


HW_INLINE void _hwa_init_all ( hwa_t *hwa )
{
  _hwa_init_cores(hwa);
  /* _hwa_init_pcints(hwa); */
  _hwa_init_ios(hwa);
  /* _hwa_init_counters(hwa); */
  /* _hwa_init_usis(hwa); */
  /* _hwa_init_acmps(hwa); */
  /* _hwa_init_adcs(hwa); */
  /* _hwa_init_watchdogs(hwa); */
}


HW_INLINE void _hwa_commit_all ( hwa_t *hwa )
{
  /* _hwa_solve_counters(hwa); */

  _hwa_solve_cores(hwa);
  _hwa_commit_cores(hwa);
  /* _hwa_commit_pcints(hwa); */
  _hwa_commit_ios(hwa);
  /* _hwa_commit_counters(hwa); */
  /* _hwa_commit_usis(hwa); */
  /* _hwa_commit_acmps(hwa); */
  /* _hwa_commit_adcs(hwa); */
  /* _hwa_commit_watchdogs(hwa); */
}
