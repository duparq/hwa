
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
 * `configure`:
 * @code
 * hw | hwa ( configure,   counter2,
 *
 *            function,    timer
 *                       | encoder
 *                       | slave,
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
 *
 * Counter used as encoder:
 * @code
 * hw | hwa ( configure,   encoder(counter2),
 *          );
 * @endcode
 */
#define _hw_class__c16a

#define _hw_mtd_hw_configure__c16a	, _hw_cfc16a
#define _hw_mtd_hwa_configure__c16a	, _hwa_cfc16a

#define _hw_cfc16a_clk_from_apb1	, 17

#if 0
#define _hw_cfc16a(o,i,a,k,...)		do{ HW_Y(_hwx_cfc16a_k,k)(_hw,o,k,__VA_ARGS__) }while(0)
#define _hwa_cfc16a(o,i,a,k,...)	do{ HW_Y(_hwx_cfc16a_k,k)(_hwa,o,k,__VA_ARGS__) }while(0)
#else
#define _hw_cfc16a(o,i,a,k,...)		HW_E_TBI()
#define _hwa_cfc16a(o,i,a,k,...)	HW_E_TBI()
#endif

/*  At least one keyword
 */
#define _hwx_cfc16a_k_1(h,o,k,...)	HW_E_ML((clock,reload))
#define _hwx_cfc16a_k_0(h,o,k,...)	HW_Y(_hwx_cfc16a_kclk,_hw_is_clock_##k)(h,o,k,__VA_ARGS__)

/*  Optionnal parameter `clock`
 */
#define _hwx_cfc16a_kclk_1(h,o,k,v,...)	HW_Y(_hwx_cfc16a_vclk,_hw_cfc16a_clk_##v)(h,o,v,__VA_ARGS__)
#define _hwx_cfc16a_vclk_0(h,o,v,...)	HW_E_NIL(v,(apb1))
#define _hwx_cfc16a_vclk_1(h,o,v,...)	_hwx_cfc16a_vclk_2(h,o,v,_hw_cfc16a_clk_##v,__VA_ARGS__)
#define _hwx_cfc16a_vclk_2(...)		_hwx_cfc16a_vclk_3(__VA_ARGS__)
#define _hwx_cfc16a_vclk_3(h,o,v,z,xv,k,...)				\
  if      ( 8*xv == 17 ) h##_write_reg(o,clksource,0);			\
  else if (   xv == 17 ) h##_write_reg(o,clksource,1);			\
  else HWA_E_NIL(v,(ahb/8, ahb));					\
  HW_Y(_hwx_cfc16a_krld,_hw_is_reload_##k)(h,o,k,__VA_ARGS__)

#define _hwx_cfc16a_kclk_0(h,o,k,...)	HW_Y(_hwx_cfc16a_krld,_hw_is_reload_##k)(h,o,k,__VA_ARGS__)

/*  Optionnal parameter `reload`
 */
#define _hwx_cfc16a_krld_1(h,o,k0,v,k,...)			\
  h##_write_reg(o,arr,(uint32_t)(v));				\
  HW_Y(_hwx_cfc16a_krn,_hw_is_run_##k)(h,o,k,__VA_ARGS__)

#define _hwx_cfc16a_krld_0(h,o,k,...)	HW_Y(_hwx_cfc16a_krn,_hw_is_run_##k)(h,o,k,__VA_ARGS__)

/*  Optionnal parameter `run`
 */
#define _hwx_cfc16a_krn_0(h,o,k,...)	HW_EOL(k)
#define _hwx_cfc16a_krn_1(h,o,k,v,...)	HW_Y(_hwx_cfc16a_vrn,_hw_state_##v)(h,o,v,__VA_ARGS__)
#define _hwx_cfc16a_vrn_0(h,o,v,...)	HW_E_ST(v)
#define _hwx_cfc16a_vrn_1(h,o,v,g,...)	h##_write_reg(o,cen,HW_A1(_hw_state_##v)); HW_EOL(g)


/**
 * @page stm32_c16a
 * <br>
 * `turn`:
 * @code
 * hw | hwa ( turn, systick, on | off );
 * @endcode
 */
#define _hw_mtd_hw_turn__c16a		, _hw_tnc16a
#define _hw_mtd_hwa_turn__c16a		, _hwa_tnc16a

#define _hw_tnc16a(o,i,a,...)		do{ _hwx_tnc16a(_hw,o,__VA_ARGS__) }while(0)
#define _hwa_tnc16a(o,i,a,...)		do{ _hwx_tnc16a(_hwa,o,__VA_ARGS__) }while(0)

#define _hwx_tnc16a(h,o,v,...)		HW_Y(_hwx_tnc16a,_hw_state_##v)(h,o,v,__VA_ARGS__)
#define _hwx_tnc16a_0(h,o,v,...)	HW_E_ST(v)
#define _hwx_tnc16a_1(h,o,v,g,...)	h##_write_reg(o,cen,HW_A1(_hw_state_##v)); HW_EOL(g)


/**
 * @page stm32_c16a
 * <br>
 * `read:`
 * @code
 * hw( read, systick );
 * @endcode
 */
#define _hw_mtd_hw_read__c16a		, _hw_rdc16a

#define _hw_rdc16a(o,i,a,...)		_hw_read_reg(o,current)


/**
 * @page stm32_c16a
 * <br>
 * __Interrupt__
 * @code
 * hw | hwa ( turn, HW_IRQ(systick), on | off );
 * @endcode
 */


/**
 * @page stm32_c16a
 * <br>
 * @code
 * if ( hw(read, HW_IRQFLAG(systick)) )    // Reading the flag clears it
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

#define _hwa_setup__c16a(o,i,a)			\
  _hwa_setup_reg( o, cr1 );			\
  _hwa_setup_reg( o, cr2 );			\
  _hwa_setup_reg( o, dier );			\
  _hwa_setup_reg( o, psc );			\
  _hwa_setup_reg( o, arr )

#define _hwa_init__c16a(o,i,a)			\
  _hwa_init_reg( o, cr1,  0x00000000 );		\
  _hwa_init_reg( o, cr2,  0x00000000 );		\
  _hwa_init_reg( o, dier, 0x00000000 );		\
  _hwa_init_reg( o, psc,  0x00000000 );		\
  _hwa_init_reg( o, arr,  0x00000000 )

#define _hwa_commit__c16a(o,i,a)		\
  _hwa_commit_reg( o, cr1 );			\
  _hwa_commit_reg( o, cr2 );			\
  _hwa_commit_reg( o, dier );			\
  _hwa_commit_reg( o, psc );			\
  _hwa_commit_reg( o, arr  )
