
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

#include "hwa_atmelavr_2.h"
#include "hwa_atmelavr__corea_2.h"
#include "hwa_atmelavr__io_2.h"
#include "hwa_atmelavr__wdoga_2.h"
#include "hwa_atmelavr__c8a_2.h"
#include "hwa_atmelavr__c16a_2.h"


HW_INLINE void _hwa_begin_all( hwa_t *hwa )
{
  _hwa_begin( hw_core0 );
  _hwa_begin( hw_porta );
  _hwa_begin( hw_portb );
  _hwa_begin( hw_watchdog0 );
  _hwa_begin( hw_counter0 );
  _hwa_begin( hw_counter1 );
}


HW_INLINE void _hwa_init_all( hwa_t *hwa )
{
  _hwa_init( hw_core0 );
  _hwa_init( hw_porta );
  _hwa_init( hw_portb );
  _hwa_init( hw_watchdog0 );
  _hwa_init( hw_counter0 );
  _hwa_init( hw_counter1 );
}


HW_INLINE void _hwa_commit_all( hwa_t *hwa )
{
  _hwa_solve( hw_counter0 );
  _hwa_solve( hw_counter1 );

  /*  Used compare outputs must be configured as i/o outputs
   */
  if ( hwa->hw_counter0.compare0_output != 0xFF
       && hwa->hw_counter0.compare0_output != HW_A1(hw_ocu_output_disconnected) )
    hwa_config( hw_pin_pb2, direction, output );
  if ( hwa->hw_counter0.compare1_output != 0xFF
       && hwa->hw_counter0.compare1_output != HW_A1(hw_ocu_output_disconnected) )
    hwa_config( hw_pin_pa7, direction, output );
  if ( hwa->hw_counter1.compare0_output != 0xFF
       && hwa->hw_counter1.compare0_output != HW_A1(hw_ocu_output_disconnected) )
    hwa_config( hw_pin_pa6, direction, output );
  if ( hwa->hw_counter1.compare1_output != 0xFF
       && hwa->hw_counter1.compare1_output != HW_A1(hw_ocu_output_disconnected) )
    hwa_config( hw_pin_pa5, direction, output );

  _hwa_commit( hw_core0 );
  _hwa_commit( hw_watchdog0 );
  _hwa_commit( hw_porta );
  _hwa_commit( hw_portb );
  _hwa_commit( hw_counter0 );
  _hwa_commit( hw_counter1 );
}
