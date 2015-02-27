
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


/* #include "hwa_attinyx4_cores_2.h" */
/* #include "hwa_attinyx4_pcints_2.h" */
/* #include "hwa_attinyx4_ios_2.h" */
/* //#include "hwa_attinyx4_pscs_2.h" */
/* #include "hwa_attinyx4_usis_2.h" */
/* #include "hwa_attinyx4_acmps_2.h" */
/* #include "hwa_attinyx4_adcs_2.h" */


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

  _hwa_commit( hw_core0 );
  _hwa_commit( hw_watchdog0 );
  _hwa_commit( hw_porta );
  _hwa_commit( hw_portb );
  _hwa_commit( hw_counter0 );
  _hwa_commit( hw_counter1 );
}
