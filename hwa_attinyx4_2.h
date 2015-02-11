
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

#include "hwa_atmelavr_2.h"
#include "hwa_atmelavr_core.h"
#include "hwa_atmelavr_ios_2.h"
#include "hwa_atmelavr_wdog.h"
#include "hwa_atmelavr_wdogA.h"

/* #include "hwa_attinyx4_cores_2.h" */
/* #include "hwa_attinyx4_pcints_2.h" */
/* #include "hwa_attinyx4_ios_2.h" */
/* #include "hwa_attinyx4_counters_2.h" */
/* //#include "hwa_attinyx4_pscs_2.h" */
/* #include "hwa_attinyx4_usis_2.h" */
/* #include "hwa_attinyx4_acmps_2.h" */
/* #include "hwa_attinyx4_adcs_2.h" */
/* #include "hwa_attinyx4_watchdogs_2.h" */


HW_INLINE void _hwa_begin ( hwa_t *hwa )
{
  _hwa_begin_reg( hw_core0, gimsk  );
  _hwa_begin_reg( hw_core0, gifr   );
  _hwa_begin_reg( hw_core0, mcucr  );
  _hwa_begin_reg( hw_core0, mcusr  );
  _hwa_begin_reg( hw_core0, osccal );
  _hwa_begin_reg( hw_core0, gpior2 );
  _hwa_begin_reg( hw_core0, gpior1 );
  _hwa_begin_reg( hw_core0, gpior0 );
  _hwa_begin_reg( hw_core0, prr    );

  /* _hwa_begin_reg( hw_pcic0, msk ); */
  /* _hwa_begin_reg( hw_pcic1, msk ); */

  _hwa_begin_reg( hw_porta, port );
  _hwa_begin_reg( hw_porta, ddr  );
  _hwa_begin_reg( hw_portb, port );
  _hwa_begin_reg( hw_portb, ddr  );

  hwa->watchdog0.action = 0xFF ;		/* 0xFF == unchanged */
  hwa->watchdog0.timeout = 0xFF ;		/* 0xFF == unchanged */
  _hwa_begin_reg( hw_watchdog0, csr );
  /* _hwa_begin_counters(hwa); */
  /* _hwa_begin_usis(hwa); */
  /* _hwa_begin_acmps(hwa); */
  /* _hwa_begin_adcs(hwa); */
}


HW_INLINE void _hwa_init ( hwa_t *hwa )
{
  _hwa_set_r8( &hwa->core0.gimsk,  0x00 );
  _hwa_set_r8( &hwa->core0.gifr,   0x00 );
  _hwa_set_r8( &hwa->core0.mcucr,  0x00 );
  _hwa_set_r8( &hwa->core0.mcusr,  0x00 );
  _hwa_set_r8( &hwa->core0.osccal, 0x00 );
  _hwa_set_r8( &hwa->core0.gpior2, 0x00 );
  _hwa_set_r8( &hwa->core0.gpior1, 0x00 );
  _hwa_set_r8( &hwa->core0.gpior0, 0x00 );
  _hwa_set_r8( &hwa->core0.prr,    0x00 );

  _hwa_set_r8( &hwa->porta.port, 0x00 );
  _hwa_set_r8( &hwa->porta.ddr,  0x00 );
  _hwa_set_r8( &hwa->portb.port, 0x00 );
  _hwa_set_r8( &hwa->portb.ddr,  0x00 );

  _hwa_set_r8( &hwa->watchdog0.csr, 0x00 );

  /* _hwa_init_cores(hwa); */
  /* _hwa_init_pcints(hwa); */
  /* _hwa_init_ios(hwa); */
  /* /\* _hwa_init_counters(hwa); *\/ */
  /* /\* _hwa_init_usis(hwa); *\/ */
  /* /\* _hwa_init_acmps(hwa); *\/ */
  /* /\* _hwa_init_adcs(hwa); *\/ */
  /* _hwa_init_watchdogs(hwa); */
}


HW_INLINE void _hwa_commit ( hwa_t *hwa )
{
  /* _hwa_solve_counters(hwa); */
  _hwa_commit_reg( hw_core0, gimsk,  hwa->commit );
  _hwa_commit_reg( hw_core0, gifr,   hwa->commit );
  _hwa_commit_reg( hw_core0, mcucr,  hwa->commit );
  _hwa_commit_reg( hw_core0, mcusr,  hwa->commit );
  _hwa_commit_reg( hw_core0, osccal, hwa->commit );
  _hwa_commit_reg( hw_core0, gpior2, hwa->commit );
  _hwa_commit_reg( hw_core0, gpior1, hwa->commit );
  _hwa_commit_reg( hw_core0, gpior0, hwa->commit );
  _hwa_commit_reg( hw_core0, prr,    hwa->commit );

  _hwa_commit_reg( hw_porta, port, hwa->commit );
  _hwa_commit_reg( hw_porta, ddr,  hwa->commit );
  _hwa_commit_reg( hw_portb, port, hwa->commit );
  _hwa_commit_reg( hw_portb, ddr,  hwa->commit );

  _hwa_commit_wdogA( hwa, &hwa->watchdog0 );

  /* _hwa_commit_cores(hwa); */
  /* _hwa_commit_pcints(hwa); */
  /* _hwa_commit_ios(hwa); */
  /* /\* _hwa_commit_counters(hwa); *\/ */
  /* /\* _hwa_commit_usis(hwa); *\/ */
  /* /\* _hwa_commit_acmps(hwa); *\/ */
  /* /\* _hwa_commit_adcs(hwa); *\/ */
  /* _hwa_commit_watchdogs(hwa); */
}
