
/* This file is part of the HWA project.
 * Copyright (c) 2017 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief General-purpose 16-bit counter-timer
 */

/**
 * @page stm32_c16a
 * __Actions__
 *
 * `configure` as counter
 * @code
 * hw | hwa ( configure,      counter2,
 *
 *          [ mode,           counter, ]                   // Default mode
 *
 *            //  How the counter is clocked
 *            //
 *            clock,          from_apb1_psc                // See note
 *                          | channel1
 *                          | channel2
 *                          | external
 *                          | xor123,
 *
 *            direction,      up
 *                          | down
 *                          | updown,
 *
 *            //  The following is accepted only when direction is 'up_down'
 *            //
 *          [ compare_flag,   counting_up
 *                          | counting_down
 *                          | counting_up_or_down, ]       // Default
 *
 *          [ loop,           yes                          // Default
 *                          | no, ]
 *
 *          [ prescaler,      x, ]                         // Any value in 0..0xFFFF
 *
 *          [ reload,         x, ]                         // Any value in 0..0xFFFF
 *
 *          [ run,            yes
 *                          | no ] );
 * @endcode
 *
 * @note RM0008, p. 126: The timer clock frequencies are automatically fixed by
 *   hardware. There are two cases:
 *     1. if the APB prescaler is 1, the timer clock frequencies are set to the
 *     same frequency as that of the APB domain to which the timers are connected.
 *     2. otherwise, they are set to twice (×2) the frequency of the APB domain to
 *     which the timers are connected.
 */

#define hw_class__c16a

#define hw_configure__c16a		, _hw_cfc16a
#define hwa_configure__c16a		, _hwa_cfc16a

#define _hw_cfc16a(o,a,k,...)		do{ HW_Y(_hwx_cfc16a,k)(_hw,o,k,__VA_ARGS__) }while(0)
#define _hwa_cfc16a(o,a,k,...)		do{ HW_Y(_hwx_cfc16a,k)(_hwa,o,k,__VA_ARGS__) }while(0)

/*  At least one keyword
 */
#define _hwx_cfc16a1(...)		HW_E_ML((clock,reload))
#define _hwx_cfc16a0(h,o,k,...)		HW_Y(_hwx_cfc16a_kmode,_hw_is_mode_##k)(h,o,k,__VA_ARGS__)

/*  Optionnal parameter `mode`
 */
#define _hw_cfc16a_mode_counter		, _hwx_cfc16a
#define _hw_cfc16a_mode_encoder		, HW_E_TBI
#define _hw_cfc16a_mode_slave		, HW_E_TBI

#define _hwx_cfc16a_kmode0(...)		_hwx_cfc16a(__VA_ARGS__)
#define _hwx_cfc16a_kmode1(h,o,k,v,...)	HW_Y(_hwx_cfc16a_vmode,_hw_cfc16a_mode_##v)(h,o,v,__VA_ARGS__)
#define _hwx_cfc16a_vmode1(h,o,v,...)	HW_A1(_hw_cfc16a_mode_##v)(h,o,__VA_ARGS__)
#define _hwx_cfc16a_vmode0(h,o,v,...)	HW_E_NIL(v,(counter,encoder,slave))

/*  Mode 'counter' - Mandatory parameter `clock`
 */
#define _hwx_cfc16a(h,o,k,...)		HW_Y(_hwx_cfc16a_kclock,_hw_is_clock_##k)(h,o,k,__VA_ARGS__)
#define _hwx_cfc16a_kclock0(h,o,k,...)	HW_E_NIL(k,(clock))
#define _hwx_cfc16a_kclock1(h,o,k,v,...)	HW_Y(_hwx_cfc16a_vclock,_hw_cfc16a_clock_##v)(h,o,v,__VA_ARGS__)
#define _hwx_cfc16a_vclock0(h,o,v,...)	HW_E_NIL(v,_hw_cfc16a_clocks)
#define _hwx_cfc16a_vclock1(h,o,v,...)	HW_A1(_hw_cfc16a_clock_##v)(h,o,__VA_ARGS__)


#define _hw_cfc16a_clocks		(from_apb1_psc,ti1,ti2,xor123)
#define _hw_cfc16a_clock_from_apb1_psc	, _hwx_cfc16a_clock_from_apb1_psc
#define _hw_cfc16a_clock_ti1fed		, HW_E_TBI
#define _hw_cfc16a_clock_channel1	, _hwx_cfc16a_clock_ti1fp1
#define _hw_cfc16a_clock_channel2	, _hwx_cfc16a_clock_ti2fp2
#define _hw_cfc16a_clock_xor123		, HW_E_TBI			// ti1s=  (p. 393)

#define _hwx_cfc16a_clock_from_apb1_psc(h,o,k,...)			\
  h##_write(o,sms,0);							\
  HW_Y(_hwx_cfc16a_kdir,_hw_is_direction_##k)(h,o,k,__VA_ARGS__)
#define _hwx_cfc16a_clock_ti1fp1(h,o,k,...)				\
  h##_write(o,sms,7);							\
  h##_write(o,ts,5);							\
  HW_Y(_hwx_cfc16a_kdir,_hw_is_direction_##k)(h,o,k,__VA_ARGS__)
#define _hwx_cfc16a_clock_ti1fp2(h,o,k,...)				\
  h##_write(o,sms,7);							\
  h##_write(o,ts,6);							\
  HW_Y(_hwx_cfc16a_kdir,_hw_is_direction_##k)(h,o,k,__VA_ARGS__)


/*  Mode 'counter' - Mandatory parameter `direction`
 */
#define _hwx_cfc16a_kdir0(h,o,k,...)	HW_E_NIL(k,(direction))
#define _hwx_cfc16a_kdir1(h,o,k,v,...)	HW_Y(_hwx_cfc16a_vdir,_hw_cfc16a_dir_##v)(h,o,v,__VA_ARGS__)

#define _hw_cfc16a_dirs			(up,down,updown)
//					, jump,              v =  cms  dir
#define _hw_cfc16a_dir_up		, _hwx_cfc16a_kocf0, 0 //  00   0
#define _hw_cfc16a_dir_down		, _hwx_cfc16a_kocf0, 1 //  00   1
#define _hw_cfc16a_dir_updown		, _hwx_cfc16a_vdir2, 6 //  11   x

#define _hwx_cfc16a_vdir0(h,o,v,...)	HW_E_NIL(v,_hw_cfc16a_dirs)
#define _hwx_cfc16a_vdir1(h,o,v,k,...)					\
  uint8_t cmsdir = HW_A2(_hw_cfc16a_dir_##v) ;				\
  HW_A1(_hw_cfc16a_dir_##v)(h,o,k,__VA_ARGS__)

#define _hwx_cfc16a_vdir2(h,o,k,...)	HW_Y(_hwx_cfc16a_kocf,_hw_is_compare_flag_##k)(h,o,k,__VA_ARGS__)

/*  Optionnal parameter `compare_flag`, only when counting up-down
 */
#define _hwx_cfc16a_kocf1(h,o,k,v,...)	HW_Y(_hwx_cfc16a_vocf,_hw_cfc16a_compare_flag_##v)(h,o,v,__VA_ARGS__)
#define _hwx_cfc16a_vocf0(h,o,v,...)	HW_E_NIL(v,(counting_up,counting_down,counting_up_or_down))
#define _hwx_cfc16a_vocf1(h,o,v,k,...)					\
  cmsdir += HW_A1(_hw_cfc16a_compare_flag_##v);				\
  h##_write(o,cmsdir,cmsdir);						\
  HW_Y(_hwx_cfc16a_kloop,_hw_is_loop_##k)(h,o,k,__VA_ARGS__)

#define _hwx_cfc16a_kocf0(h,o,k,...)				\
  h##_write(o,cmsdir,cmsdir);					\
  HW_Y(_hwx_cfc16a_kloop,_hw_is_loop_##k)(h,o,k,__VA_ARGS__)

#define _hw_cfc16a_compare_flag_counting_down		, -4
#define _hw_cfc16a_compare_flag_counting_up		, -2
#define _hw_cfc16a_compare_flag_counting_up_or_down	, +0

/*  Optionnal parameter `loop`
 */
#define _hwx_cfc16a_kloop1(h,o,k,v,...)	HW_Y(_hwx_cfc16a_vloop,_hw_state_##v)(h,o,v,__VA_ARGS__)
#define _hwx_cfc16a_vloop0(h,o,v,...)	HW_E_ST(v)
#define _hwx_cfc16a_vloop1(h,o,v,k,...)					\
  h##_write(o,opm,HW_A2(_hw_state_##v));				\
  HW_Y(_hwx_cfc16a_kpsc,_hw_is_prescaler_##k)(h,o,k,__VA_ARGS__)

#define _hwx_cfc16a_kloop0(h,o,k,...)					\
  HW_Y(_hwx_cfc16a_kpsc,_hw_is_prescaler_##k)(h,o,k,__VA_ARGS__)

/*  Optionnal parameter `prescaler`
 */
#define _hwx_cfc16a_kpsc1(h,o,k0,v,k,...)			\
  h##_write(o,psc,(uint16_t)(v));				\
  HW_Y(_hwx_cfc16a_krld,_hw_is_reload_##k)(h,o,k,__VA_ARGS__)
#define _hwx_cfc16a_kpsc0(h,o,k,...)				\
  HW_Y(_hwx_cfc16a_krld,_hw_is_reload_##k)(h,o,k,__VA_ARGS__)

/*  Optionnal parameter `reload`
 */
#define _hwx_cfc16a_krld1(h,o,k0,v,k,...)			\
  h##_write(o,arr,(uint16_t)(v));				\
  HW_Y(_hwx_cfc16a_krun,_hw_is_run_##k)(h,o,k,__VA_ARGS__)
#define _hwx_cfc16a_krld0(h,o,k,...)				\
  HW_Y(_hwx_cfc16a_krun,_hw_is_run_##k)(h,o,k,__VA_ARGS__)

/*  Optionnal parameter `run`
 */
#define _hwx_cfc16a_krun1(h,o,k,v,...)	HW_Y(_hwx_cfc16a_vrun,_hw_state_##v)(h,o,v,__VA_ARGS__)
#define _hwx_cfc16a_vrun0(h,o,v,...)	HW_E_ST(v)
#define _hwx_cfc16a_vrun1(h,o,v,...)	h##_write(o,cen,HW_A1(_hw_state_##v)); HW_EOL(__VA_ARGS__);
#define _hwx_cfc16a_krun0(h,o,k,...)	HW_EOL(__VA_ARGS__)


/**
 * `configure` as encoder
 *
 * @note To be implemented.
 *
 * @code
 * hw | hwa ( configure,   counter2,
 *
 *	      mode	   encoder );
 * @endcode
 */

/**
 * `configure` as slave
 *
 * @note To be implemented.
 *
 * @code
 * hw | hwa ( configure,   counter2,
 *
 *	      mode,	   slave,
 *
 *	      //  How the counter is clocked
 *	      //
 *	      clock,	   from_apb1	   // Internal clock (CK_INT)
 *			 | channel1
 *			 | channel2
 *			 | external
 *			 | encode(channel1,channel2)
 *			 | xor(channel1,channel2,channel3)
 *
 *	      //  How the counter is reset (slave mode)
 *	      //
 *	    [ reset,	   counter1
 *			 | counter2
 *			 | counter3
 *			 | counter4
 *			 | counter5
 *			 | counter8, ] );
 * @endcode
 */


/**
 * @page stm32_c16a
 * <br>
 * `run`:
 * @code
 * hw | hwa ( run, counter2 );
 * @endcode
 */
#define hw_run__c16a			, _hw_rnc16a
#define _hw_rnc16a(o,a,...)		_hw_write(o,cen,1) HW_EOL(__VA_ARGS__)

#define hwa_run__c16a			, _hwa_rnc16a
#define _hwa_rnc16a(o,a,...)		_hwa_write(o,cen,1) HW_EOL(__VA_ARGS__)


/**
 * @page stm32_c16a
 * <br>
 * `stop`:
 * @code
 * hw | hwa ( stop, counter2 );
 * @endcode
 */
#define hw_stop__c16a			, _hw_spc16a
#define _hw_spc16a(o,a,...)		_hw_write(o,cen,0) HW_EOL(__VA_ARGS__)

#define hwa_stop__c16a			, _hwa_spc16a
#define _hwa_spc16a(o,a,...)		_hwa_write(o,cen,0) HW_EOL(__VA_ARGS__)


/**
 * @page stm32_c16a
 *
 * `read:`
 * @code
 * uint16_t v = hw( read, counter2 );
 * @endcode
 */
#define hw_read__c16a			, _hw_rdc16a
#define _hw_rdc16a(o,a,...)		_hw_read(o,cnt)


/**
 * @page stm32_c16a
 *
 * `write:`
 * @code
 * uint16_t v = hw( write, counter2, 500 );
 * @endcode
 */
#define hw_write__c16a			, _hw_wrc16a
#define _hw_wrc16a(o,a,v,...)		_hw_write(o,cnt,(v) & 0xFFFF) HW_EOL(__VA_ARGS__)


/**
 * @page stm32_c16a
 *
 * `stat:` get the status flags and clear them.
 * @code
 * uint16_t v = hw( stat, counter2 );
 * @endcode
 */
#define hw_stat__c16a			, _hw_stc16a
#define _hw_stc16a(o,a,...)		_hw_read(o,sr)


/**
 * @page stm32_c16a
 * <br>
 * __Registers__
 *
 * <br>
 */



/*******************************************************************************
 *									       *
 *	Context management						       *
 *									       *
 *******************************************************************************/

#define _hwa_setup__c16a(o,a)			\
  _hwa_setup_r( o, cr1 );			\
  _hwa_setup_r( o, cr2 );			\
  _hwa_setup_r( o, smcr );			\
  _hwa_setup_r( o, dier );			\
  _hwa_setup_r( o, ccmr2 );			\
  _hwa_setup_r( o, ccer );			\
  _hwa_setup_r( o, psc );			\
  _hwa_setup_r( o, arr );			\
  _hwa_setup_r( o, ccr3 )

#define _hwa_init__c16a(o,a)			\
  _hwa_init_r( o, cr1,	 0x00000000 );		\
  _hwa_init_r( o, cr2,	 0x00000000 );		\
  _hwa_init_r( o, smcr,  0x00000000 );		\
  _hwa_init_r( o, dier,  0x00000000 );		\
  _hwa_init_r( o, ccmr2, 0x00000000 );		\
  _hwa_init_r( o, ccer,  0x00000000 );		\
  _hwa_init_r( o, psc,	 0x00000000 );		\
  _hwa_init_r( o, arr,	 0x00000000 );		\
  _hwa_init_r( o, ccr3,	 0x00000000 )

#define _hwa_commit__c16a(o,a)			\
  _hwa_commit_r( o, cr1 );			\
  _hwa_commit_r( o, cr2 );			\
  _hwa_commit_r( o, smcr );			\
  _hwa_commit_r( o, dier );			\
  _hwa_commit_r( o, ccmr2 );			\
  _hwa_commit_r( o, ccer );			\
  _hwa_commit_r( o, psc );			\
  _hwa_commit_r( o, arr	 );			\
  _hwa_commit_r( o, ccr3 )
