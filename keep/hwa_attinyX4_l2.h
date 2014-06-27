
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

//#include "hwa_atmelavr_l2.h"
#include "hwa_attinyX4_cores_l2.h"
#include "hwa_attinyX4_ios_l2.h"
#include "hwa_attinyX4_counters_l2.h"
#include "hwa_attinyX4_adcs_l2.h"


HW_INLINE void hwa_begin_all ( hwa_t *hwa )
{
  hwa_begin_cores(hwa);
  hwa_begin_ios(hwa);
  hwa_begin_counters(hwa);
  hwa_begin_adcs(hwa);
}


HW_INLINE void hwa_commit_all ( hwa_t *hwa )
{
  hwa_solve_counters(hwa);

  hwa_commit_cores(hwa);
  hwa_commit_ios(hwa);
  hwa_commit_counters(hwa);
  hwa_commit_adcs(hwa);
}
