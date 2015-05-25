
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

#include "atmel/avr/2.h"
#include "atmel/avr/corea_2.h"
#include "atmel/avr/io_2.h"
#include "atmel/avr/pcica_2.h"
#include "atmel/avr/wdoga_2.h"
#include "atmel/avr/ocua_2.h"
#include "atmel/avr/c8a_2.h"
#include "atmel/avr/c16a_2.h"
#include "atmel/avr/psca_2.h"
#include "atmel/avr/icua_2.h"
#include "atmel/avr/usia_2.h"
#include "atmel/avr/acmpa_2.h"
#include "atmel/avr/ad10a_2.h"
#include "atmel/avr/eeproma_2.h"
#include "atmel/avr/flasha_2.h"
#include "atmel/avr/swuarta_2.h"


HW_INLINE void _hwa_begin_all( hwa_t *hwa )
{
  _hwa_begin( hw_core0 );
  _hwa_begin( hw_porta );
  _hwa_begin( hw_portb );
  _hwa_begin( hw_pcic0 );
  /* _hwa_begin_r8( &hwa->hw_pcic0.msk, 0x32 ); */
  /* _hwa_begin_r8( &hwa->hw_pcic1.msk, 0x40 ); */

  _hwa_begin( hw_wdog0 );
  _hwa_begin( hw_counter0 );

  //  hwa_r8_t* restrict r = &hwa->hw_counter0.ccrb ;
  //  hwa->hw_counter0.cs.r = r ;

  //  hwa->hw_counter0.cs.r = (hwa_r8_t*)&hwa->hw_counter0.ccrb;
  //  _hwa_begin_m8( hw_counter0, cs );

  _hwa_begin( hw_counter1 );
  _hwa_begin( hw_usi0 );
  _hwa_begin( hw_adc0 );
  _hwa_begin( hw_acmp0 );
}


HW_INLINE void _hwa_init_all( hwa_t *hwa )
{
  _hwa_init( hw_core0 );
  _hwa_init( hw_porta );
  _hwa_init( hw_portb );
  _hwa_init( hw_pcic0 );
  /* _hwa_set_r8( &hwa->hw_pcic0.msk, 0 ); */
  /* _hwa_set_r8( &hwa->hw_pcic1.msk, 0 ); */
  _hwa_init( hw_wdog0 );
  _hwa_init( hw_counter0 );
  _hwa_init( hw_counter1 );
  _hwa_init( hw_usi0 );
  _hwa_init( hw_adc0 );
  _hwa_init( hw_acmp0 );
}


HW_INLINE void _hwa_commit_all( hwa_t *hwa )
{
  /*  Solve the configuration.
   *
   *  The configuration values are written here since the solve function only
   *  has the address of the counter and does not know its name.
   *
   *  _hw_creg(...) could be used as well though it can not access registers of
   *  another object.
   */
  _hwa_solve_c8a( &hwa->hw_counter0 );
  if ( hwa->hw_counter0.solved.cs != 0xFF )
    _hwa_write_reg( hw_counter0, cs, hwa->hw_counter0.solved.cs );
  if ( hwa->hw_counter0.solved.wgm != 0xFF )
    _hwa_write_reg( hw_counter0, wgm, hwa->hw_counter0.solved.wgm );
  if ( hwa->hw_counter0.solved.coma != 0xFF )
    _hwa_write_reg( hw_counter0, compare0_mode, hwa->hw_counter0.solved.coma );
  if ( hwa->hw_counter0.solved.comb != 0xFF )
    _hwa_write_reg( hw_counter0, compare1_mode, hwa->hw_counter0.solved.comb );

  _hwa_solve( hw_counter1 );
  if ( hwa->hw_counter1.solved.cs != 0xFF )
    _hwa_write_reg( hw_counter1, cs, hwa->hw_counter1.solved.cs );
  if ( hwa->hw_counter1.solved.wgm != 0xFF )
    _hwa_write_reg( hw_counter1, wgm, hwa->hw_counter1.solved.wgm );
  if ( hwa->hw_counter1.solved.coma != 0xFF )
    _hwa_write_reg( hw_counter1, compare0_mode, hwa->hw_counter1.solved.coma );
  if ( hwa->hw_counter1.solved.comb != 0xFF )
    _hwa_write_reg( hw_counter1, compare1_mode, hwa->hw_counter1.solved.comb );
  if ( hwa->hw_counter1.solved.acic != 0xFF )
    _hwa_write_reg( hw_counter1, acic, hwa->hw_counter1.solved.acic );
  if ( hwa->hw_counter1.solved.ices != 0xFF )
    _hwa_write_reg( hw_counter1, ices, hwa->hw_counter1.solved.ices );
  if ( hwa->hw_counter1.solved.icnc != 0xFF )
    _hwa_write_reg( hw_counter1, icnc, hwa->hw_counter1.solved.icnc );


  /*  If used, compare outputs must be configured as i/o outputs
   */
  if ( hwa->hw_counter0.config.compare0.output != 0xFF
       && hwa->hw_counter0.config.compare0.output != HW_A1(hw_ocu_output_disconnected) )
    hwa_config( hw_pin_pb2, direction, output );
  if ( hwa->hw_counter0.config.compare1.output != 0xFF
       && hwa->hw_counter0.config.compare1.output != HW_A1(hw_ocu_output_disconnected) )
    hwa_config( hw_pin_pa7, direction, output );
  if ( hwa->hw_counter1.config.compare0.output != 0xFF
       && hwa->hw_counter1.config.compare0.output != HW_A1(hw_ocu_output_disconnected) )
    hwa_config( hw_pin_pa6, direction, output );
  if ( hwa->hw_counter1.config.compare1.output != 0xFF
       && hwa->hw_counter1.config.compare1.output != HW_A1(hw_ocu_output_disconnected) )
    hwa_config( hw_pin_pa5, direction, output );

  _hwa_commit( hw_core0 );
  _hwa_commit( hw_wdog0 );
  _hwa_commit( hw_porta );
  _hwa_commit( hw_portb );

  _hwa_commit( hw_pcic0 );
  /* _hwa_commit_r8( hwa, &hwa->hw_pcic0.msk ); */
  /* _hwa_commit_r8( hwa, &hwa->hw_pcic1.msk ); */
  /* _hwa_commit_reg_p( &hwa->hw_pcic0, _pcica0, msk ); */
  /* _hwa_commit_reg_p( &hwa->hw_pcic1, _pcica1, msk ); */

  _hwa_commit( hw_counter0 );
  _hwa_commit( hw_counter1 );
  _hwa_commit( hw_usi0 );
  _hwa_commit( hw_adc0 );
  _hwa_commit( hw_acmp0 );
}
