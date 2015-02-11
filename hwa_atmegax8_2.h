
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

#include "hwa_atmelavr_2.h"
#include "hwa_atmelavr_core.h"
#include "hwa_atmelavr_ios_2.h"
#include "hwa_atmelavr_wdog.h"
#include "hwa_atmelavr_wdogB.h"


HW_INLINE void _hwa_begin ( hwa_t *hwa )
{
  _hwa_begin_reg( hw_core0, osccal );
  _hwa_begin_reg( hw_core0, prr    );
  _hwa_begin_reg( hw_core0, mcucr  );
  _hwa_begin_reg( hw_core0, mcusr  );
  _hwa_begin_reg( hw_core0, smcr   );
  _hwa_begin_reg( hw_core0, gpior2 );
  _hwa_begin_reg( hw_core0, gpior1 );
  _hwa_begin_reg( hw_core0, gpior0 );
  _hwa_begin_reg( hw_core0, eimsk  );
  _hwa_begin_reg( hw_core0, eifr   );

  _hwa_begin_reg( hw_portb, port );
  _hwa_begin_reg( hw_portb, ddr  );
  _hwa_begin_reg( hw_portc, port );
  _hwa_begin_reg( hw_portc, ddr  );
  _hwa_begin_reg( hw_portd, port );
  _hwa_begin_reg( hw_portd, ddr  );

  hwa->watchdog0.action = 0xFF ;		/* 0xFF == unchanged */
  hwa->watchdog0.timeout = 0xFF ;		/* 0xFF == unchanged */
  _hwa_begin_reg( hw_watchdog0, csr );
}


HW_INLINE void _hwa_init ( hwa_t *hwa )
{
  _hwa_set_r8( &hwa->core0.osccal, 0x00 );
  _hwa_set_r8( &hwa->core0.prr,    0x00 );
  _hwa_set_r8( &hwa->core0.mcucr,  0x00 );
  //  _hwa_set_r8( &hwa->core0.mcusr,  0x00 );
  _hwa_set_r8( &hwa->core0.smcr,   0x00 );
  _hwa_set_r8( &hwa->core0.gpior2, 0x00 );
  _hwa_set_r8( &hwa->core0.gpior1, 0x00 );
  _hwa_set_r8( &hwa->core0.gpior0, 0x00 );
  _hwa_set_r8( &hwa->core0.eimsk,  0x00 );
  _hwa_set_r8( &hwa->core0.eifr,   0x00 );

  _hwa_set_r8( &hwa->portb.port, 0x00 );
  _hwa_set_r8( &hwa->portb.ddr,  0x00 );
  _hwa_set_r8( &hwa->portc.port, 0x00 );
  _hwa_set_r8( &hwa->portc.ddr,  0x00 );
  _hwa_set_r8( &hwa->portd.port, 0x00 );
  _hwa_set_r8( &hwa->portd.ddr,  0x00 );

  _hwa_set_r8( &hwa->watchdog0.csr, 0x00 );
}


HW_INLINE void _hwa_commit ( hwa_t *hwa )
{
  _hwa_commit_reg( hw_core0, osccal, hwa->commit );
  _hwa_commit_reg( hw_core0, prr,    hwa->commit );
  _hwa_commit_reg( hw_core0, mcucr,  hwa->commit );
  _hwa_commit_reg( hw_core0, mcusr,  hwa->commit );
  _hwa_commit_reg( hw_core0, smcr,   hwa->commit );
  _hwa_commit_reg( hw_core0, gpior2, hwa->commit );
  _hwa_commit_reg( hw_core0, gpior1, hwa->commit );
  _hwa_commit_reg( hw_core0, gpior0, hwa->commit );
  _hwa_commit_reg( hw_core0, eimsk,  hwa->commit );
  _hwa_commit_reg( hw_core0, eifr,   hwa->commit );

  _hwa_commit_reg( hw_portb, port, hwa->commit );
  _hwa_commit_reg( hw_portb, ddr,  hwa->commit );
  _hwa_commit_reg( hw_portc, port, hwa->commit );
  _hwa_commit_reg( hw_portc, ddr,  hwa->commit );
  _hwa_commit_reg( hw_portd, port, hwa->commit );
  _hwa_commit_reg( hw_portd, ddr,  hwa->commit );

  _hwa_commit_wdogB( hwa, &hwa->watchdog0 );
}
