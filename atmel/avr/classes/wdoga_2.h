
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Watchdog timer
 */

/**
 * @page atmelavr_wdoga
 * @section atmelavr_wdoga_config Configuration
 *
 * When `action` is `irq_or_reset` the watchdog IRQ is enabled. It is disabled
 * by hardware after a first timeout occurs. Then, if you do not re-enable the
 * IRQ, the next timeout resets the device.
 *
 * @code
 * hwa_config( hw_wdog0,
 *
 *           [ timeout,   16ms
 *                      | 32ms
 *                      | 64ms
 *                      | 125ms
 *                      | 250ms
 *                      | 500ms
 *                      | 1s
 *                      | 2s
 *                      | 4s
 *                      | 8s,   ]
 *
 *             action,    none
 *                      | irq
 *                      | reset
 *                      | irq_or_reset,
 *            );
 * @endcode
 */
#define _hw_mthd_hwa_configure__wdoga	, _hwa_cfwdoga

/*    Optionnal argument `timeout`
 */
#define _hw_is_timeout_timeout		, 1
#define _hw_wdoga_timeout_16ms		, 0
#define _hw_wdoga_timeout_32ms		, 1
#define _hw_wdoga_timeout_64ms		, 2
#define _hw_wdoga_timeout_125ms		, 3
#define _hw_wdoga_timeout_250ms		, 4
#define _hw_wdoga_timeout_500ms		, 5
#define _hw_wdoga_timeout_1s		, 6
#define _hw_wdoga_timeout_2s		, 7
#define _hw_wdoga_timeout_4s		, 8
#define _hw_wdoga_timeout_8s		, 9

#define _hwa_cfwdoga(o,i,a, ...)	\
  do { HW_G2(_hwa_cfwdoga_ktimeout,HW_IS(timeout,__VA_ARGS__))(o,__VA_ARGS__,,) }while(0)

#define _hwa_cfwdoga_ktimeout_1(o,k,v,...)				\
  HW_G2(_hwa_cfwdoga_vtimeout,HW_IS(,_hw_wdoga_timeout_##v))(o,v,__VA_ARGS__)

#define _hwa_cfwdoga_vtimeout_0(o,v,...)				\
  HW_E_AVL(timeout, v, 16ms | 32ms | 64ms | 125ms | 250ms | 500ms | 1s | 2s | 4s | 8s)

#define _hwa_cfwdoga_vtimeout_1(o,v,k,...)			\
  hwa->o.config.timeout = HW_A1(_hw_wdoga_timeout_##v);		\
  HW_G2(_hwa_cfwdoga_kaction,HW_IS(action,k))(o,k,__VA_ARGS__)

#define _hwa_cfwdoga_ktimeout_0(...)				\
  HW_G2(_hwa_cfwdoga_kaction,HW_IS(action,k))(o,k,__VA_ARGS__)

/*    Mandatory argument `action`
 */
#define _hw_is_action_action		, 1
#define _hw_wdoga_action_none		, 0
#define _hw_wdoga_action_irq		, 1
#define _hw_wdoga_action_reset		, 2
#define _hw_wdoga_action_irq_or_reset	, 3

#define _hwa_cfwdoga_kaction_0(o,k,...)				\
  HW_E_VL(k,action)

#define _hwa_cfwdoga_kaction_1(o,k,v,...)				\
  HW_G2(_hwa_cfwdoga_vaction,HW_IS(,_hw_wdoga_action_##v))(o,v,__VA_ARGS__)

#define _hwa_cfwdoga_vaction_0(o,v,...)					\
  HW_E_AVL(action, v, none | irq | reset | irq_or_reset)

#define _hwa_cfwdoga_vaction_1(o,v,...)			\
  hwa->o.config.action = HW_A1(_hw_wdoga_action_##v);	\
  HW_EOL(__VA_ARGS__)


/**
 * @page atmelavr_wdoga
 * @section atmelavr_wdoga_turn Turning on/off
 *
 * @code
 * hw_turn( hw_wdog0,   on
 *                    | off );
 * @endcode
 */
#define _hw_mthd_hw_turn__wdoga		, _hw_turn_wdoga

#define _hw_turn_wdoga(o,i,a, v)			\
  HW_G2(_hw_turn_wdoga, HW_IS(,_hw_state_##v))(o,v)

#define _hw_turn_wdoga_0(o, v)						\
  HW_E_ST(v)

#define _hw_turn_wdoga_1(o, v)		HW_G2(_hw_turn_wdoga, v)(o)

#define _hw_turn_wdoga_on(o)		_hw_write_reg(o,wde,1)

/*  Disable the watchdog by clearing WDE. That special sequence must be
 *  respected.
 *
 *  FIXME: that also clears WDRF (required) and other reset flags, as well
 *  as WDIE but this should not be a problem. WDP and WDIF are left intact.
 *  May be should only clear WDRF
 *
 *  FIXME: 0x27 is the mask for WDP bits in WDTCR
 */
#define _hw_turn_wdoga_off(o)						\
  do {									\
    uint8_t reg ;							\
    _hw_write_reg( hw_core0, mcusr, 0 );				\
    __asm__ __volatile__("  in   %[r], %[wdtcr]"	"\n\t"		\
			 "  ori  %[r], %[wdce]|%[wde]"	"\n\t"		\
			 "  out  %[wdtcr], %[r]"	"\n\t"		\
			 "  andi %[r], %[wdp]"		"\n\t"		\
			 "  out  %[wdtcr], %[r]"	"\n\t"		\
			 : [r] "=&d" (reg)				\
			 : [wdtcr] "I" (_hw_addr(_HW_REG(o, csr))-0x20), \
			   [wdce] "I" (1<<_hw_bp(_HW_REG(o, wdce))),	\
			   [wde] "I" (1<<_hw_bp(_HW_REG(o, wde))),	\
			   [wdp] "I" (0x27));				\
  } while(0)


/**
 * @page atmelavr_wdoga
 *
 * @code
 * hwa_turn( hw_wdog0,   on
 *                     | off );
 * @endcode
 */
#define _hw_mthd_hwa_turn__wdoga	, _hwa_turn_wdoga

#define _hwa_turn_wdoga(o,i,a, ...)					\
  HW_G2(_hwa_turn_wdoga, HW_IS(,_hw_state_##__VA_ARGS__))(o,__VA_ARGS__,)

#define _hwa_turn_wdoga_0(o, v, ...)				\
  HW_E_ST(v)

#define _hwa_turn_wdoga_1(o, v, ...)		\
  HW_G2(_hwa_turn_wdoga, v)(o,i,a)		\
  HW_EOL(__VA_ARGS__)

#define _hwa_turn_wdoga_on(o,i,a)		\
  _hwa_write_reg(o,wde,1)

#define _hwa_turn_wdoga_off(o,i,a)			\
  /* Action completed when committing */		\
  hwa->o.config.action = HW_A1(_hw_wdoga_action_none)


/**
 * @page atmelavr_wdoga
 * @section atmelavr_wdoga_reset Reset
 *
 * The `hw_reset()` instruction resets the watchdog timer (issues a `wdr`):
 *
 * @code
 * hw_reset( hw_wdog0 );
 * @endcode
 */
#define _hw_mthd_hw_reset__wdoga		, _hw_rstwdoga

#define _hw_rstwdoga(o,i,a,...)			HW_TX(hw_asm("wdr"::),__VA_ARGS__)


/**
 * @page atmelavr_wdoga
 * @section atmelavr_wdoga_stat Status
 *
 * The overflow flag can be accessed through the interrupt-related instructions:
 *
 * @code
 * if ( hw_stat_irqf( hw_wdog0 ) ) {
 *   hw_clear_irqf( hw_wdog0 );
 *   hw_turn_irq( hw_wdog0, on );
 *   n_wdoverflows++ ;
 * }
 * @endcode
 */


/*******************************************************************************
 *                                                                             *
 *      Context management						       *
 *                                                                             *
 *******************************************************************************/

#define _hwa_setup__wdoga(o,i,a)		\
  _hwa_setup_reg( o, csr );			\
  hwa->o.config.action = 0xFF ;			\
  hwa->o.config.timeout = 0xFF


#define _hwa_init__wdoga(o,i,a)			_hwa_init_reg( o, csr, 0x00 )


/**
 * @brief Commit the configuration of a _wdoga class watchdog
 * @hideinitializer
 *
 * Turning the watchdog off requires:
 *    1. Clearing WDRF
 *    2. Setting WDCE and WDE to 1 in the same operation
 *    3. Setting WDE to 0 within 4 cycles after 2.
 */
#define _hwa_commit__wdoga(o,i,a)					\
  do {									\
    if ( hwa->o.config.action != 0xFF ) {				\
      if ( hwa->o.config.action == HW_A1(_hw_wdoga_action_none) ) {	\
	/* Turn it off */						\
	if ( HW_DEVICE_WDTON == 0 )					\
	  HWA_ERR( "watchdog can not be turned off because HW_DEVICE_WATCHDOG_ALWAYS_ON is `yes`." ); \
	_hwa_write_reg( o, wdrf, 0 );					\
	_hwa_commit_reg( o, wdrf );					\
	_hwa_write_reg( o, wdce, 1 );					\
	_hwa_write_reg( o, wde,  1 );					\
	_hwa_commit_reg( o, csr );					\
	_hwa_write_reg( o, ie, 0 );					\
	_hwa_write_reg( o, wdce, 0 );					\
	_hwa_write_reg( o, wde, 0 );					\
	_hwa_write_reg( o, wdp, 0 );					\
      }									\
      else {								\
	/* Configure it */						\
	_hwa_write_reg( o, eie, hwa->o.config.action );			\
	if ( hwa->o.config.timeout != 0xFF )				\
	  _hwa_write_reg( o, wdp, hwa->o.config.timeout );		\
      }									\
      hwa->o.config.action = 0xFF ;					\
      hwa->o.config.timeout = 0xFF ;					\
    }									\
    _hwa_commit_reg( o, csr );						\
  } while(0)


#if 0
#define _hwa_commit__wdoga(o,i,a)		_hwa_commit_p__wdoga(hwa,&hwa->o)

HW_INLINE void _hwa_commit_p__wdoga ( hwa_t *hwa, hwa_wdoga_t *p )
{
  if ( p->config.action != 0xFF ) {
    if ( p->config.action == HW_A1(_hw_wdoga_action_none) ) {
      /*
       *  Turn the watchdog off:
       *    1. Clear WDRF
       *    2. Set WDCE and WDE to 1 in the same operation
       *    3. Set WDE to 0 within 4 cycles after 2.
       */
#if HW_DEVICE_WDTON == 0
      HW_E(watchdog can not be turned off because HW_DEVICE_FUSE_WDTON is enabled)
#endif
      _hwa_write_reg_p( p, _wdoga, wdrf, 0 );
      _hwa_commit_reg_p( p, _wdoga, wdrf );

      // _hwa_write_reg_p( p, _wdoga, wdif, 1 );
      _hwa_write_reg_p( p, _wdoga, wdce, 1 );
      _hwa_write_reg_p( p, _wdoga, wde,  1 );
      _hwa_commit_reg_p( p, _wdoga, csr );
      _hwa_write_reg_p( p, _wdoga, ie, 0 );
      _hwa_write_reg_p( p, _wdoga, wdce, 0 );
      _hwa_write_reg_p( p, _wdoga, wde, 0 );
      _hwa_write_reg_p( p, _wdoga, wdp, 0 );
    }
    else {
      /*
       *  Configure the watchdog
       */
      _hwa_write_reg_p( p, _wdoga, eie, p->config.action );
      if ( p->config.timeout != 0xFF )
	_hwa_write_reg_p( p, _wdoga, wdp, p->config.timeout );
    }
    p->config.action = 0xFF ;
    p->config.timeout = 0xFF ;
  }
  _hwa_commit_reg_p( p, _wdoga, csr );
}
#endif


/**
 * @page atmelavr_wdoga
 * <br>
 */
