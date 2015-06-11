
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Atmel AVR watchdog model 'b'
 */

#include "wdog_2.h"


/*  Class methods
 */
#define _hw_mthd_hw_turn__wdogb		, _hw_turn_wdog
#define _hw_mthd_hwa_turn__wdogb	, _hwa_turn_wdog
#define _hw_mthd_hw_reset__wdogb	, _hw_wdreset
#define _hw_mthd_hwa_config__wdogb	, _hwa_cfwdog
#define _hw_mthd_hw_stat__wdogb		, _hw_stat_wdog
#define _hw_mthd_hw_stat_t__wdogb	, _hw_statt_wdog


HW_INLINE void _hwa_begin_p__wdogb ( hwa_wdogb_t *p, intptr_t address )
{
  p->action = 0xFF ;
  p->timeout = 0xFF ;
  _hwa_begin_reg_p( p, address, _wdogb, csr );
}


HW_INLINE void _hwa_init_p__wdogb ( hwa_wdogb_t *p )
{
  _hwa_set__r8( &p->csr, 0x00 );
}


HW_INLINE void _hwa_commit_p__wdogb ( hwa_t *hwa, hwa_wdogb_t *p )
{
  if ( p->action != 0xFF ) {
    if ( p->action == HW_A1(hw_wdog_action_none) ) {
      /*
       *  Turn the watchdog off:
       *    1. Clear WDRF
       *    2. Set WDCE and WDE to 1 in the same operation
       *    3. Set WDE to 0 within 4 cycles after 2.
       */
#if HW_DEVICE_WDTON == 0
      HW_ERR( "watchdog can not be turned off because FUSE bit WDTON is " \
	      "programmed." );
#endif
      _hwa_write_reg_p( p, _wdogb, wdrf, 0 );
      _hwa_commit_reg_p( p, _wdogb, wdrf );

      _hwa_write_reg_p( p, _wdogb, if, 1 );
      _hwa_write_reg_p( p, _wdogb, wdce, 1 );
      _hwa_write_reg_p( p, _wdogb, wde,  1 );
      _hwa_commit_reg_p( p, _wdogb, csr );
      _hwa_write_reg_p( p, _wdogb, ie, 0 );
      _hwa_write_reg_p( p, _wdogb, wdce, 0 );
      _hwa_write_reg_p( p, _wdogb, wde, 0 );
      _hwa_write_reg_p( p, _wdogb, wdp, 0 );
    }
    else {
      /*
       *  Configure the watchdog
       */
      //      _hwa_write_reg_p( p, _wdogb, wdif, 1 );
      _hwa_write_reg_p( p, _wdogb, wdce, 1 );
      _hwa_write_reg_p( p, _wdogb, wde,  1 );
      _hwa_commit_reg_p( p, _wdogb, csr );
      _hwa_write_reg_p( p, _wdogb, wdce, 0 );
      _hwa_write_reg_p( p, _wdogb, wdeie, p->action );
      if ( p->timeout != 0xFF )
      	_hwa_write_reg_p( p, _wdogb, wdp, p->timeout );
    }
    /* p->action = 0xFF ; */
    /* p->timeout = 0xFF ; */
  }
  _hwa_commit_reg_p( p, _wdogb, csr );
}
