
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

#include "hwa_atmelavr_2.h"
#include "hwa_atmelavr_core.h"
#include "hwa_atmelavr_ios_2.h"
#include "hwa_atmelavr_wdog.h"
#include "hwa_atmelavr_wdogA.h"


/*	Available sleep modes
 */
/* #define hw_core_sm_idle			, 0 */
/* #define hw_core_sm_adc_noise_reduction	, 1 */
/* #define hw_core_sm_power_down		, 2 */


HW_INLINE void _hwa_begin( hwa_t *hwa )
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

  _hwa_begin_reg( hw_portb, port );
  _hwa_begin_reg( hw_portb, ddr  );

  hwa->watchdog0.action = 0xFF ;		/* 0xFF == unchanged */
  hwa->watchdog0.timeout = 0xFF ;		/* 0xFF == unchanged */
  _hwa_begin_reg( hw_watchdog0, csr );
}

HW_INLINE void _hwa_init( hwa_t *hwa )
{
  _hwa_set_r8( &hwa->core0.gimsk,  0x00 );
  _hwa_set_r8( &hwa->core0.gifr,   0x00 );
  _hwa_set_r8( &hwa->core0.mcucr,  0x00 );
  //  _hwa_set_r8( &hwa->core0.mcusr,  0x00 );
  _hwa_set_r8( &hwa->core0.osccal, 0x00 );
  _hwa_set_r8( &hwa->core0.gpior2, 0x00 );
  _hwa_set_r8( &hwa->core0.gpior1, 0x00 );
  _hwa_set_r8( &hwa->core0.gpior0, 0x00 );
  _hwa_set_r8( &hwa->core0.prr,    0x00 );

  _hwa_set_r8( &hwa->portb.port, 0x00 );
  _hwa_set_r8( &hwa->portb.ddr,  0x00 );

  _hwa_set_r8( &hwa->watchdog0.csr, 0x00 );
}


HW_INLINE void _hwa_commit( hwa_t *hwa )
{
  _hwa_commit_reg( hw_core0, gimsk,  hwa->commit );
  _hwa_commit_reg( hw_core0, gifr,   hwa->commit );
  _hwa_commit_reg( hw_core0, mcucr,  hwa->commit );
  _hwa_commit_reg( hw_core0, mcusr,  hwa->commit );
  _hwa_commit_reg( hw_core0, osccal, hwa->commit );
  _hwa_commit_reg( hw_core0, gpior2, hwa->commit );
  _hwa_commit_reg( hw_core0, gpior1, hwa->commit );
  _hwa_commit_reg( hw_core0, gpior0, hwa->commit );
  _hwa_commit_reg( hw_core0, prr,    hwa->commit );

  _hwa_commit_reg( hw_portb, port, hwa->commit );
  _hwa_commit_reg( hw_portb, ddr,  hwa->commit );

  _hwa_commit_wdogA( hwa, &hwa->watchdog0 );
}
