
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

#include "hwa_attinyX4_cores_2.h"
#include "hwa_attinyX4_pcints_2.h"
#include "hwa_attinyX4_ios_2.h"
#include "hwa_attinyX4_counters_2.h"
//#include "hwa_attinyX4_pscs_2.h"
//#include "hwa_attinyX4_usis_2.h"
#include "hwa_attinyX4_acmps_2.h"
#include "hwa_attinyX4_adcs_2.h"


HW_INLINE void _hwa_begin_all ( hwa_t *hwa )
{
  _hwa_begin_cores(hwa);
  _hwa_begin_pcints(hwa);
  _hwa_begin_ios(hwa);
  _hwa_begin_counters(hwa);
  _hwa_begin_acmps(hwa);
  _hwa_begin_adcs(hwa);
}


HW_INLINE void _hwa_reset_all ( hwa_t *hwa )
{
  _hwa_reset_cores(hwa);
  _hwa_reset_pcints(hwa);
  _hwa_reset_ios(hwa);
  _hwa_reset_counters(hwa);
  _hwa_reset_acmps(hwa);
  _hwa_reset_adcs(hwa);
}


HW_INLINE void _hwa_commit_all ( hwa_t *hwa )
{
  _hwa_solve_counters(hwa);

  _hwa_commit_cores(hwa);
  _hwa_commit_pcints(hwa);
  _hwa_commit_ios(hwa);
  _hwa_commit_counters(hwa);
  _hwa_commit_acmps(hwa);
  _hwa_commit_adcs(hwa);
}
