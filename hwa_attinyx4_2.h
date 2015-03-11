
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
  _hwa_begin( core0 );
  _hwa_begin( porta );
  _hwa_begin( portb );
  _hwa_begin( watchdog0 );
  _hwa_begin( counter0 );
  _hwa_begin( counter1 );
}


HW_INLINE void _hwa_init_all( hwa_t *hwa )
{
  _hwa_init( core0 );
  _hwa_init( porta );
  _hwa_init( portb );
  _hwa_init( watchdog0 );
  _hwa_init( counter0 );
  _hwa_init( counter1 );
}


HW_INLINE void _hwa_commit_all( hwa_t *hwa )
{
  _hwa_solve( counter0 );
  _hwa_solve( counter1 );

  /*  Used compare outputs must be configured as i/o outputs
   */
  if ( hwa->counter0.compare0_output != 0xFF
       && hwa->counter0.compare0_output != HW_A1(hw_ocu_output_disconnected) )
    hwa_config( pin_pb2, direction, output );
  if ( hwa->counter0.compare1_output != 0xFF
       && hwa->counter0.compare1_output != HW_A1(hw_ocu_output_disconnected) )
    hwa_config( pin_pa7, direction, output );
  if ( hwa->counter1.compare0_output != 0xFF
       && hwa->counter1.compare0_output != HW_A1(hw_ocu_output_disconnected) )
    hwa_config( pin_pa6, direction, output );
  if ( hwa->counter1.compare1_output != 0xFF
       && hwa->counter1.compare1_output != HW_A1(hw_ocu_output_disconnected) )
    hwa_config( pin_pa5, direction, output );

  _hwa_commit( core0 );
  _hwa_commit( watchdog0 );
  _hwa_commit( porta );
  _hwa_commit( portb );
  _hwa_commit( counter0 );
  _hwa_commit( counter1 );
}
