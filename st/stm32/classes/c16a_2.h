
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
 * hw | hwa ( configure,   counter2,
 *
 *          [ mode,        counter ]       // Default mode
 *
 *            //  How the counter is clocked
 *            //
 *            clock,       from_apb1_psc   // See note
 *                       | channel1
 *                       | channel2
 *                       | external
 *                       | xor123
 *
 *            direction,   up_loop
 *                       | up_noloop
 *                       | down_loop
 *                       | down_noloop
 *                       | updown_loop,
 *
 *          [ prescaler,   x, ]            // Any value in 0..0xFFFFFF
 *
 *          [ reload,      x, ]            // Any value in 0..0xFFFFFF
 *
 *          [ run,         yes
 *                       | no ] );
 * @endcode
 *
 * @note The clock frequency is that of the AHB when the APB prescaler is 1 or 2.\n
 *   RM0008, p. 126: The timer clock frequencies are automatically fixed by
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
#define _hwa_cfc16a(o,a,k,...)	do{ HW_Y(_hwx_cfc16a,k)(_hwa,o,k,__VA_ARGS__) }while(0)

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
#define _hwx_cfc16a_vclock0(h,o,v,...)	HW_E_NIL(v,_hw_cfc16a_clock_list)
#define _hwx_cfc16a_vclock1(h,o,v,...)	HW_A1(_hw_cfc16a_clock_##v)(h,o,__VA_ARGS__)


#define _hw_cfc16a_clock_list		(from_apb1_psc,ti1,ti2,xor123)
#define _hw_cfc16a_clock_from_apb1_psc	, _hwx_cfc16a_clock_from_apb1_psc
#define _hw_cfc16a_clock_ti1fed		, HW_E_TBI
#define _hw_cfc16a_clock_channel1	, _hwx_cfc16a_clock_ti1fp1
#define _hw_cfc16a_clock_channel2	, _hwx_cfc16a_clock_ti2fp2
#define _hw_cfc16a_clock_xor123		, HW_E_TBI				// ti1s=		(p. 393)

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

#define _hw_cfc16a_dir_list		(up_loop,up_noloop,down_loop,down_noloop,updown_loop)
//					 dir opm cms
#define _hw_cfc16a_dir_up_loop		,  0,  0,  0
#define _hw_cfc16a_dir_up_noloop	,  0,  1,  0
#define _hw_cfc16a_dir_down_loop	,  1,  0,  0
#define _hw_cfc16a_dir_down_noloop	,  1,  1,  0
#define _hw_cfc16a_dir_updown_loop	,  0,  0,  1

#define _hwx_cfc16a_vdir0(h,o,v,...)	HW_E_NIL(v,_hw_cfc16a_dir_list)
#define _hwx_cfc16a_vdir1(h,o,v,...)	_hwx_cfc16a_vdir2(h,o,_hw_cfc16a_dir_##v,__VA_ARGS__)
#define _hwx_cfc16a_vdir2(...)		_hwx_cfc16a_vdir3(__VA_ARGS__)
#define _hwx_cfc16a_vdir3(h,o,v0,vdir,vopm,vcms,k,...)	\
  h##_write(o,dir,vdir);							\
  h##_write(o,opm,vopm);							\
  h##_write(o,cms,vcms);							\
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

/*  Mandatory parameter `run`
 */
#define _hwx_cfc16a_krun0(h,o,k,...)	HW_E_KX(run,k)
#define _hwx_cfc16a_krun1(h,o,k,v,...)	HW_Y(_hwx_cfc16a_vrn_,_hw_state_##v)(h,o,v,__VA_ARGS__)
#define _hwx_cfc16a_vrn_0(h,o,v,...)	HW_E_ST(v)
#define _hwx_cfc16a_vrn_1(h,o,v,g,...)	h##_write(o,cen,HW_A1(_hw_state_##v)); HW_EOL(g)


/**
 * `configure` as encoder
 * @code
 * hw | hwa ( configure,   counter2,
 *
 *            mode         encoder );
 * @endcode
 */

/**
 * `configure` as slave
 * @code
 * hw | hwa ( configure,   counter2,
 *
 *            mode,        slave,
 *
 *            //  How the counter is clocked
 *            //
 *            clock,       from_apb1       // Internal clock (CK_INT)
 *                       | channel1
 *                       | channel2
 *                       | external
 *                       | encode(channel1,channel2)
 *                       | xor(channel1,channel2,channel3)
 *
 *            //  How the counter is reset (slave mode)
 *            //
 *          [ reset,       counter1
 *                       | counter2
 *                       | counter3
 *                       | counter4
 *                       | counter5
 *                       | counter8
 *
 *            //  Not used for 'encoder' mode
 *            //
 *          [ direction,   up_loop
 *                       | down_loop
 *                       | updown, ]
 *
 *          [ reload,      x, ]            // Any value in 0..0xFFFFFF
 *
 *          [ run,         yes
 *                       | no ] );
 * @endcode
 */


/**
 * @page stm32_c16a
 * <br>
 * `turn`:
 * @code
 * hw | hwa ( turn, counter2, on );
 * @endcode
 */
#define hw_turn__c16a			, _hw_tnc16a
#define _hw_tnc16a(o,a,...)		do{ _hwx_tnc16a(_hw,o,__VA_ARGS__) }while(0)

#define hwa_turn__c16a			, _hwa_tnc16a
#define _hwa_tnc16a(o,a,...)		do{ _hwx_tnc16a(_hwa,o,__VA_ARGS__) }while(0)

#define _hwx_tnc16a(h,o,v,...)		HW_Y(_hwx_tnc16a_,_hw_state_##v)(h,o,v,__VA_ARGS__)
#define _hwx_tnc16a_0(h,o,v,...)	HW_E_ST(v)
#define _hwx_tnc16a_1(h,o,v,g,...)	h##_write(o,cen,HW_A1(_hw_state_##v)); HW_EOL(g)


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
 * <br>
 * __Interrupt__
 * @code
 * hw | hwa ( turn, irq(systick), on | off );
 * @endcode
 */


/**
 * @page stm32_c16a
 * <br>
 * @code
 * if ( hw(read, irqflag(systick)) )    // Reading the flag clears it
 *   hw(toggle,LED);
 * @endcode
 * <br>
 */


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
  _hwa_setup_r( o, psc );			\
  _hwa_setup_r( o, arr )

#define _hwa_init__c16a(o,a)			\
  _hwa_init_r( o, cr1,  0x00000000 );		\
  _hwa_init_r( o, cr2,  0x00000000 );		\
  _hwa_init_r( o, smcr, 0x00000000 );		\
  _hwa_init_r( o, dier, 0x00000000 );		\
  _hwa_init_r( o, psc,  0x00000000 );		\
  _hwa_init_r( o, arr,  0x00000000 )

#define _hwa_commit__c16a(o,a)		\
  _hwa_commit_r( o, cr1 );			\
  _hwa_commit_r( o, cr2 );			\
  _hwa_commit_r( o, smcr );			\
  _hwa_commit_r( o, dier );			\
  _hwa_commit_r( o, psc );			\
  _hwa_commit_r( o, arr  )
