
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


#error


HW_INLINE void _hwa_begin_cores ( hwa_t *hwa )
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
}


HW_INLINE void _hwa_init_cores ( hwa_t *hwa )
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
}


HW_INLINE void _hwa_commit_cores ( hwa_t *hwa )
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
}


/*	Available sleep modes
 */
#define hw_core_sm_idle			, 0
#define hw_core_sm_adc_noise_reduction	, 1
#define hw_core_sm_power_down		, 2
#define hw_core_sm_standby		, 3


/*	Power management
 */
#define hw_power_counter1	prtim1
#define hw_power_counter0	prtim0
#define hw_power_usi0		prusi
#define hw_power_adc0		pradc

#define hw_def_hw_turn__c8a	, _hw_turn_power
#define hw_def_hw_turn__c16a	, _hw_turn_power
#define hw_def_hw_turn_usia	, _hw_turn_power
#define hw_def_hw_turn_ad10a	, _hw_turn_power

#define _hw_turn_power(c,n,i,a,vstate)\
  HW_G2(_hw_turn_power, HW_IS(,hw_state_##vstate))(c,n,i,a,vstate)
#define _hw_turn_power_0(c,n,i,a, vstate)			\
  HW_ERR("expected `on` or `off`, got `" #vstate "` instead.")
#define _hw_turn_power_1(c,n,i,a, vstate)	\
  _hw_write_reg(hw_core0, hw_power_##n, (HW_A1(hw_state_##vstate)==0))


#define hw_def_hwa_turn__c8a	, _hwa_turn_power
#define hw_def_hwa_turn__c16a	, _hwa_turn_power
#define hw_def_hwa_turn_usia	, _hwa_turn_power
#define hw_def_hwa_turn_ad10a	, _hwa_turn_power

#define _hwa_turn_power(c,n,i,a,vstate)\
  HW_G2(_hwa_turn_power, HW_IS(,hw_state_##vstate))(c,n,i,a,vstate)
#define _hwa_turn_power_0(c,n,i,a, vstate)			\
  HW_ERR("expected `on` or `off`, got `" #vstate "` instead.")
#define _hwa_turn_power_1(c,n,i,a, vstate)	\
  _hwa_write_reg(hw_core0, hw_power_##n, (HW_A1(hw_state_##vstate)==0))
