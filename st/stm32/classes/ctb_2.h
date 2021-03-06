
/* This file is part of the HWA project.
 * Copyright (c) 2021 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief General-purpose 32-bit counter-timer
 */

/*  The channels rely on their counter's registers, so we can use the cca
 *  interface definitions with ctb counters.
 */
#include "cca_2.h"

/**
 * @addtogroup stm32_ctb
 *
 * @section stm32_ctbif Interface
 *
 * By default, hw( configure, COUNTER, ... ) and hwa( configure, COUNTER, ... )
 * configure the COUNTER as a counter:
 *
 * @code
 * hw | hwa( configure,	     counter2,
 *
 *	   [ mode,	     counter, ]			// Default mode
 *
 *	     //	 How the counter is clocked
 *	     //
 *	     clock,	     from_apb1_psc		// See note
 *			   | channel1
 *			   | channel2
 *			   | external
 *			   | xor123,
 *
 *	     direction,	     up
 *			   | down
 *			   | updown,
 *
 *	     //	 The following is accepted only when direction is 'up_down'
 *	     //
 *	   [ compare_flag,   counting_up
 *			   | counting_down
 *			   | counting_up_or_down, ]	// Default
 *
 *	   [ prescaler,	     x, ]			// Any value in 0..0xFFFF
 *
 *	   [ reload,	     x, ]			// Any value in 0..0xFFFF
 *
 *	   [ run,	     yes
 *			   | no ]
 * );
 * @endcode
 *
 * @note RM0008, p. 126: The timer clock frequencies are automatically fixed by
 *   hardware. There are two cases:
 *     1. if the APB prescaler is 1, the timer clock frequencies are set to the
 *     same frequency as that of the APB domain to which the timers are connected.
 *     2. otherwise, they are set to twice (×2) the frequency of the APB domain to
 *     which the timers are connected.
 */
#define hw_class__ctb

#define hw_configure__ctb		, _hw_cfctb
#define hwa_configure__ctb		, _hwa_cfctb

#define _hw_cfctb(o,a,k,...)		do{ HW_B(_hwx_cfctb,k)(_hw,o,k,__VA_ARGS__) }while(0)
#define _hwa_cfctb(o,a,k,...)		do{ HW_B(_hwx_cfctb,k)(_hwa,o,k,__VA_ARGS__) }while(0)

/*  At least one keyword
 */
#define _hwx_cfctb1(...)		HW_E(HW_EM_AML((clock,direction)))
#define _hwx_cfctb0(h,o,k,...)		HW_B(_hwx_cfctb_kmode,_hw_is_mode_##k)(h,o,k,__VA_ARGS__)

/*  Optionnal parameter `mode`
 */
#define _hw_cfctb_mode_counter		, _hwx_cfctb
#define _hw_cfctb_mode_encoder		, HW_E_TBI
#define _hw_cfctb_mode_slave		, HW_E_TBI

#define _hwx_cfctb_kmode0(...)		_hwx_cfctb(__VA_ARGS__)
#define _hwx_cfctb_kmode1(h,o,k,v,...)	HW_B(_hwx_cfctb_vmode,_hw_cfctb_mode_##v)(h,o,v,__VA_ARGS__)
#define _hwx_cfctb_vmode1(h,o,v,...)	HW_A1(_hw_cfctb_mode_##v)(h,o,__VA_ARGS__)
#define _hwx_cfctb_vmode0(h,o,v,...)	HW_E(HW_EM_VAL(v,mode,(counter,encoder,slave)))

/*  Mode 'counter' - Mandatory parameter `clock`
 */
#define _hwx_cfctb(h,o,k,...)		HW_B(_hwx_cfctb_kclock,_hw_is_clock_##k)(h,o,k,__VA_ARGS__)
#define _hwx_cfctb_kclock0(h,o,k,...)	HW_E(HW_EM_AN(k,clock))
#define _hwx_cfctb_kclock1(h,o,k,v,...)	HW_B(_hwx_cfctb_vclock,_hw_cfctb_clock_##v)(h,o,v,__VA_ARGS__)
#define _hwx_cfctb_vclock0(h,o,v,...)	HW_E(HW_EM_VAL(v,clock,_hw_cfctb_clocks))
#define _hwx_cfctb_vclock1(h,o,v,...)	HW_A1(_hw_cfctb_clock_##v)(h,o,__VA_ARGS__)


#define _hw_cfctb_clocks		(from_apb1_psc,ti1,ti2,xor123)
#define _hw_cfctb_clock_from_apb1_psc	, _hwx_cfctb_clock_from_apb1_psc
#define _hw_cfctb_clock_ti1fed		, HW_E_TBI
#define _hw_cfctb_clock_channel1	, _hwx_cfctb_clock_ti1fp1
#define _hw_cfctb_clock_channel2	, _hwx_cfctb_clock_ti2fp2
#define _hw_cfctb_clock_xor123		, HW_E_TBI			// ti1s=  (p. 393)

#define _hwx_cfctb_clock_from_apb1_psc(h,o,k,...)			\
  h##_write(o,sms,0);							\
  HW_B(_hwx_cfctb_kdir,_hw_is_direction_##k)(h,o,k,__VA_ARGS__)
#define _hwx_cfctb_clock_ti1fp1(h,o,k,...)				\
  h##_write(o,sms,7);							\
  h##_write(o,ts,5);							\
  HW_B(_hwx_cfctb_kdir,_hw_is_direction_##k)(h,o,k,__VA_ARGS__)
#define _hwx_cfctb_clock_ti1fp2(h,o,k,...)				\
  h##_write(o,sms,7);							\
  h##_write(o,ts,6);							\
  HW_B(_hwx_cfctb_kdir,_hw_is_direction_##k)(h,o,k,__VA_ARGS__)


/*  Mode 'counter' - Mandatory parameter `direction`
 */
#define _hwx_cfctb_kdir0(h,o,k,...)	HW_E(HW_EM_AN(k,direction))
#define _hwx_cfctb_kdir1(h,o,k,v,...)	HW_B(_hwx_cfctb_vdir,_hw_cfctb_dir_##v)(h,o,v,__VA_ARGS__)

#define _hw_cfctb_dirs			(up_loop,up_noloop,down_loop,down_noloop,updown_loop,updown_noloop)
//					, jump,		     v =  cms  dir  opm
#define _hw_cfctb_dir_up_loop		, _hwx_cfctb_kocf0,  0 //  00	0    0
#define _hw_cfctb_dir_up_noloop		, _hwx_cfctb_kocf0,  1 //  00	0    1
#define _hw_cfctb_dir_down_loop		, _hwx_cfctb_kocf0,  2 //  00	1    0
#define _hw_cfctb_dir_down_noloop	, _hwx_cfctb_kocf0,  3 //  00	1    1
#define _hw_cfctb_dir_updown_loop	, _hwx_cfctb_vdir2, 12 //  11	x    0
#define _hw_cfctb_dir_updown_noloop	, _hwx_cfctb_vdir2, 13 //  11	x    1

#define _hwx_cfctb_vdir0(h,o,v,...)	HW_E(HW_EM_VAL(v,direction,_hw_cfctb_dirs))
#define _hwx_cfctb_vdir1(h,o,v,k,...)					\
  uint8_t cmsdiropm = HW_A2(_hw_cfctb_dir_##v) ;			\
  HW_A1(_hw_cfctb_dir_##v)(h,o,k,__VA_ARGS__)

#define _hwx_cfctb_vdir2(h,o,k,...)	HW_B(_hwx_cfctb_kocf,_hw_is_compare_flag_##k)(h,o,k,__VA_ARGS__)

/*  Optionnal parameter `compare_flag`, only when counting up-down
 */
#define _hwx_cfctb_kocf1(h,o,k,v,...)	HW_B(_hwx_cfctb_vocf,_hw_cfctb_compare_flag_##v)(h,o,v,__VA_ARGS__)
#define _hwx_cfctb_vocf0(h,o,v,...)	HW_E(HW_EM_VOAL(v,compare_flag,(counting_up,counting_down,counting_up_or_down)))
#define _hwx_cfctb_vocf1(h,o,v,k,...)					\
  cmsdiropm += HW_A1(_hw_cfctb_compare_flag_##v);			\
  h##_write(o,cmsdiropm,cmsdiropm);					\
  HW_B(_hwx_cfctb_kpsc,_hw_is_prescaler_##k)(h,o,k,__VA_ARGS__)
  /* HW_B(_hwx_cfctb_kloop,_hw_is_loop_##k)(h,o,k,__VA_ARGS__) */

#define _hwx_cfctb_kocf0(h,o,k,...)				\
  h##_write(o,cmsdiropm,cmsdiropm);				\
  HW_B(_hwx_cfctb_kpsc,_hw_is_prescaler_##k)(h,o,k,__VA_ARGS__)
  /* HW_B(_hwx_cfctb_kloop,_hw_is_loop_##k)(h,o,k,__VA_ARGS__) */

#define _hw_cfctb_compare_flag_counting_down		, -8
#define _hw_cfctb_compare_flag_counting_up		, -4
#define _hw_cfctb_compare_flag_counting_up_or_down	, +0

/*  Optionnal parameter `loop`
 */
/* #define _hwx_cfctb_kloop1(h,o,k,v,...)	HW_B(_hwx_cfctb_vloop,_hw_state_##v)(h,o,v,__VA_ARGS__) */
/* #define _hwx_cfctb_vloop0(h,o,v,...)	HW_E(HW_EM_ST(v)) */
/* #define _hwx_cfctb_vloop1(h,o,v,k,...)					\ */
/*   h##_write(o,opm,HW_A2(_hw_state_##v));				\ */
/*   HW_B(_hwx_cfctb_kpsc,_hw_is_prescaler_##k)(h,o,k,__VA_ARGS__) */

/* #define _hwx_cfctb_kloop0(h,o,k,...)					\ */
/*   HW_B(_hwx_cfctb_kpsc,_hw_is_prescaler_##k)(h,o,k,__VA_ARGS__) */

/*  Optionnal parameter `prescaler`
 */
#define _hwx_cfctb_kpsc1(h,o,k0,v,k,...)			\
  h##_write(o,psc,(uint16_t)(v));				\
  HW_B(_hwx_cfctb_krld,_hw_is_reload_##k)(h,o,k,__VA_ARGS__)
#define _hwx_cfctb_kpsc0(h,o,k,...)				\
  HW_B(_hwx_cfctb_krld,_hw_is_reload_##k)(h,o,k,__VA_ARGS__)

/*  Optionnal parameter `reload`
 */
#define _hwx_cfctb_krld1(h,o,k0,v,k,...)			\
  h##_write(o,arr,(uint16_t)(v));				\
  HW_B(_hwx_cfctb_krun,_hw_is_run_##k)(h,o,k,__VA_ARGS__)
#define _hwx_cfctb_krld0(h,o,k,...)				\
  HW_B(_hwx_cfctb_krun,_hw_is_run_##k)(h,o,k,__VA_ARGS__)

/*  Optionnal parameter `run`
 */
#define _hwx_cfctb_krun1(h,o,k,v,...)	HW_B(_hwx_cfctb_vrun,_hw_state_##v)(h,o,v,__VA_ARGS__)
#define _hwx_cfctb_vrun0(h,o,v,...)	HW_E(HW_EM_ST(v))
#define _hwx_cfctb_vrun1(h,o,v,...)	h##_write(o,cen,HW_A1(_hw_state_##v)); HW_EOL(__VA_ARGS__);
#define _hwx_cfctb_krun0(h,o,k,...)	HW_EOL(__VA_ARGS__)


/**
 * <br><br>
 * @note To be implemented. Configure the counter as an encoder:
 *
 * @code
 * hw | hwa( configure, counter2,
 *
 *	     mode,	encoder,
 *
 *           ...
 * );
 * @endcode
 */


/**
 * <br><br>
 * @note To be implemented. Configure the counter as a slave:
 *
 * @code
 * hw | hwa( configure,	  counter2,
 *
 *	     mode,	  slave,
 *
 *	     //	 How the counter is clocked
 *	     //
 *	     clock,	  from_apb1		// Internal clock (CK_INT)
 *			| channel1
 *			| channel2
 *			| external
 *			| encode(channel1,channel2)
 *			| xor(channel1,channel2,channel3)
 *
 *	     //	 How the counter is reset (slave mode)
 *	     //
 *	   [ reset,	  counter1
 *			| counter2
 *			| counter3
 *			| counter4
 *			| counter5
 *			| counter8, ]
 * );
 * @endcode
 */


/**
 * @addtogroup stm32_ctb
 *
 * <br><br>hw( run, COUNTER ) and hwa( run, COUNTER ) run the counter:
 *
 * @code
 * hw | hwa ( run, counter2 );
 * @endcode
 */
#define hw_run__ctb			, _hw_rnctb
#define _hw_rnctb(o,a,...)		_hw_write(o,cen,1) HW_EOL(__VA_ARGS__)

#define hwa_run__ctb			, _hwa_rnctb
#define _hwa_rnctb(o,a,...)		_hwa_write(o,cen,1) HW_EOL(__VA_ARGS__)


/**
 * @addtogroup stm32_ctb
 *
 * <br><br>hw( stop, COUNTER ) and hwa( stop, COUNTER ) stop the counter:
 *
 * @code
 * hw | hwa ( stop, counter2 );
 * @endcode
 */
#define hw_stop__ctb			, _hw_spctb
#define _hw_spctb(o,a,...)		_hw_write(o,cen,0) HW_EOL(__VA_ARGS__)

#define hwa_stop__ctb			, _hwa_spctb
#define _hwa_spctb(o,a,...)		_hwa_write(o,cen,0) HW_EOL(__VA_ARGS__)


/**
 * @addtogroup stm32_ctb
 *
 * <br><br>hw( read, COUNTER ) returns the value of the counting register:
 *
 * @code
 * uint16_t v = hw( read, counter2 );
 * @endcode
 */
#define hw_read__ctb			, _hw_rdctb
#define _hw_rdctb(o,a,...)		_hw_read(o,cnt)


/**
 * @addtogroup stm32_ctb
 *
 * <br><br>hw( write, COUNTER, value ) sets the value of the counting register:
 *
 * @code
 * uint16_t v = hw( write, counter2, 500 );
 * @endcode
 */
#define hw_write__ctb			, _hw_wrctb
#define _hw_wrctb(o,a,v,...)		_hw_write(o,cnt,(v) & 0xFFFF) HW_EOL(__VA_ARGS__)


/**
 * @addtogroup stm32_ctb
 *
 * <br><br>hw( stat, COUNTER ) gets the status flags and clears them:
 *
 * @code
 * uint16_t v = hw( stat, counter2 );
 * @endcode
 */
#define hw_stat__ctb			, _hw_stctb
#define _hw_stctb(o,a,...)		_hw_read(o,sr)


/*******************************************************************************
 *									       *
 *	Context management						       *
 *									       *
 *******************************************************************************/

#define _hwa_setup__ctb(o,a)			\
  _hwa_setup_r( o, cr1 );			\
  _hwa_setup_r( o, cr2 );			\
  _hwa_setup_r( o, smcr );			\
  _hwa_setup_r( o, dier );			\
  _hwa_setup_r( o, psc );			\
  _hwa_setup_r( o, arr )
  /* _hwa_setup_r( o, ccr3 ) */

/* _hwa_setup_r( o, ccmr2 );			\ */
  /* _hwa_setup_r( o, ccer );			\ */

#define _hwa_init__ctb(o,a)			\
  _hwa_init_r( o, cr1,	 0x00000000 );		\
  _hwa_init_r( o, cr2,	 0x00000000 );		\
  _hwa_init_r( o, smcr,	 0x00000000 );		\
  _hwa_init_r( o, dier,	 0x00000000 );		\
  _hwa_init_r( o, psc,	 0x00000000 );		\
  _hwa_init_r( o, arr,	 0x00000000 )
  /* _hwa_init_r( o, ccr3,	 0x00000000 ) */

/* _hwa_init_r( o, ccmr2, 0x00000000 );		\ */
  /* _hwa_init_r( o, ccer,	 0x00000000 );		\ */

#define _hwa_commit__ctb(o,a)			\
  _hwa_commit_r( o, cr1 );			\
  _hwa_commit_r( o, cr2 );			\
  _hwa_commit_r( o, smcr );			\
  _hwa_commit_r( o, dier );			\
  _hwa_commit_r( o, psc );			\
  _hwa_commit_r( o, arr	 );			\
  /* _hwa_commit_r( o, ccr3 ) */

/* _hwa_commit_r( o, ccmr2 );			\ */
  /* _hwa_commit_r( o, ccer );			\ */
