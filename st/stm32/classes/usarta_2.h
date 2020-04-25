
/* This file is part of the HWA project.
 * Copyright (c) 2019 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Universal synchronous asynchronous receiver transmitter (USART)
 */

/**
 * @page stm32_usarta
 * @section stm32_usarta_actions Actions
 *
 * `configure`:
 *
 * @code
 * hw | hwa ( configure,   usart1,
 *
 *          [ mode,        asynchronous ]          // Default mode is `asynchronous`.
 *
 *          [ bps,         BPS, ]                  // Transfer rate in bits per second.
 *
 *          [ databits,    8 | 9, ]                // Number of data bits in frame. Default is `8`.
 *
 *          [ parity,      none, even, odd, ]      // Parity. Default is `none`
 *
 *          [ stopbits,    1 | 2, ]                // Number of stop bits in frame. Default is `1`.
 *
 *          [ receiver,    enabled | disabled, ]   // Whether the UART can receive. Default is `enabled`.
 *
 *          [ transmitter, enabled | disabled, ]   // Whether the UART can transmit. Default is `enabled`.
 *          );
 * @endcode
 *
 * Counter used as encoder:
 * @code
 * hw | hwa ( configure,   encoder(counter2),
 *          );
 * @endcode
 */
#define hw_class__usarta

#define hw_configure__usarta		, _hw_cfusarta
#define hwa_configure__usarta		, _hwa_cfusarta

#define _hw_cfusarta_clk_from_apb1	, 17

#if 0
#define _hw_cfusarta(o,a,k,...)		do{ HW_Y(_hwx_cfusarta_k_,k)(_hw,o,k,__VA_ARGS__) }while(0)
#define _hwa_cfusarta(o,a,k,...)	do{ HW_Y(_hwx_cfusarta_k_,k)(_hwa,o,k,__VA_ARGS__) }while(0)
#else
#define _hw_cfusarta(o,a,k,...)		HW_E_TBI()
#define _hwa_cfusarta(o,a,k,...)	HW_E_TBI()
#endif

/*  At least one keyword
 */
#define _hwx_cfusarta_k_1(h,o,k,...)	HW_E_ML((clock,reload))
#define _hwx_cfusarta_k_0(h,o,k,...)	HW_Y(_hwx_cfusarta_kclk_,_hw_is_clock_##k)(h,o,k,__VA_ARGS__)

/*  Optionnal parameter `clock`
 */
#define _hwx_cfusarta_kclk_1(h,o,k,v,...)	HW_Y(_hwx_cfusarta_vclk_,_hw_cfusarta_clk_##v)(h,o,v,__VA_ARGS__)
#define _hwx_cfusarta_vclk_0(h,o,v,...)	HW_E_NIL(v,(apb1))
#define _hwx_cfusarta_vclk_1(h,o,v,...)	_hwx_cfusarta_vclk_2(h,o,v,_hw_cfusarta_clk_##v,__VA_ARGS__)
#define _hwx_cfusarta_vclk_2(...)		_hwx_cfusarta_vclk_3(__VA_ARGS__)
#define _hwx_cfusarta_vclk_3(h,o,v,z,xv,k,...)				\
  if      ( 8*xv == 17 ) h##_write(o,clksource,0);			\
  else if (   xv == 17 ) h##_write(o,clksource,1);			\
  else HWA_E_NIL(v,(ahb/8, ahb));					\
  HW_Y(_hwx_cfusarta_krld_,_hw_is_reload_##k)(h,o,k,__VA_ARGS__)

#define _hwx_cfusarta_kclk_0(h,o,k,...)	HW_Y(_hwx_cfusarta_krld_,_hw_is_reload_##k)(h,o,k,__VA_ARGS__)

/*  Optionnal parameter `reload`
 */
#define _hwx_cfusarta_krld_1(h,o,k0,v,k,...)			\
  h##_write(o,arr,(uint32_t)(v));				\
  HW_Y(_hwx_cfusarta_krn_,_hw_is_run_##k)(h,o,k,__VA_ARGS__)

#define _hwx_cfusarta_krld_0(h,o,k,...)	HW_Y(_hwx_cfusarta_krn_,_hw_is_run_##k)(h,o,k,__VA_ARGS__)

/*  Optionnal parameter `run`
 */
#define _hwx_cfusarta_krn_0(h,o,k,...)	HW_EOL(k)
#define _hwx_cfusarta_krn_1(h,o,k,v,...)	HW_Y(_hwx_cfusarta_vrn_,_hw_state_##v)(h,o,v,__VA_ARGS__)
#define _hwx_cfusarta_vrn_0(h,o,v,...)	HW_E_ST(v)
#define _hwx_cfusarta_vrn_1(h,o,v,g,...)	h##_write(o,cen,HW_A1(_hw_state_##v)); HW_EOL(g)


/**
 * @page stm32_usarta
 *
 * `read:`
 * @code
 * uint16_t v = hw( read, usart1 );
 * @endcode
 */
#define hw_read__usarta			, _hw_rdusarta
#define _hw_rdusarta(o,a,...)		_hw_read(o,cnt)


/**
 * @page stm32_usarta
 * @section Interrupts
 * @code
 * hw | hwa ( turn, irq(systick), on | off );
 * @endcode
 */


/**
 * @page stm32_usarta
 * <br>
 * @code
 * if ( hw(read, irqflag(systick)) )    // Reading the flag clears it
 *   hw(toggle,LED);
 * @endcode
 * <br>
 */


/**
 * @page stm32_usarta
 * @section Registers
 * 
 *   * sr
 *     * cts
 *     * lbd
 *     * txe
 *     * tc
 *     * rxne
 *     * idle
 *     * ore
 *     * ne
 *     * fe
 *     * pe
 *   * dr
 *   * brr
 *     * divmantissa
 *     * divfraction
 *   * cr1
 *     * ue
 *     * m
 *     * wake
 *     * pce
 *     * ps
 *     * peie
 *     * txeie
 *     * tcie
 *     * rxneie
 *     * idleie
 *     * te
 *     * re
 *     * rwu
 *     * sbk
 *   * cr2
 *     * linen
 *     * stop
 *     * clken
 *     * cpol
 *     * cpha
 *     * lbcl
 *     * lbdie
 *     * lbdl
 *     * add
 *   * cr3
 *     * ctsie
 *     * ctse
 *     * rtse
 *     * dmat
 *     * dmar
 *     * scen
 *     * nack
 *     * hdsel
 *     * irlp
 *     * iren
 *     * eie
 *   * gtpr
 *     * gt
 *     * psc
 */


/*******************************************************************************
 *									       *
 *	Context								       *
 *									       *
 *******************************************************************************/

#define _hwa_setup__usarta(o,a)		\
  _hwa_setup_r( o, brr );			\
  _hwa_setup_r( o, cr1 );			\
  _hwa_setup_r( o, cr2 );			\
  _hwa_setup_r( o, cr3 );			\
  _hwa_setup_r( o, gtpr )

#define _hwa_init__usarta(o,a)		\
  _hwa_init_r( o, brr,  0x00000000 );		\
  _hwa_init_r( o, cr1,  0x00000000 );		\
  _hwa_init_r( o, cr2,  0x00000000 );		\
  _hwa_init_r( o, cr3,  0x00000000 );		\
  _hwa_init_r( o, gtpr, 0x00000000 )

#define _hwa_commit__usarta(o,a)		\
  _hwa_commit_r( o, brr );			\
  _hwa_commit_r( o, cr1 );			\
  _hwa_commit_r( o, cr2 );			\
  _hwa_commit_r( o, cr3 );			\
  _hwa_commit_r( o, gtpr )
