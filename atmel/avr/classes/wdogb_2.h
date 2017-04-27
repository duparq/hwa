
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Watchdog timer
 */

/**
 * @page atmelavr_wdogb
 * @section atmelavr_wdogb_config Configuration
 *
 * When `action` is `irq_or_reset` the watchdog IRQ is enabled. It is disabled
 * by hardware after a first timeout occurs. Then, if you do not re-enable the
 * IRQ, the next timeout resets the device.
 *
 * @code
 * hwa( configure, watchdog0,
 *
 *	     [ timeout,	  16ms
 *			| 32ms
 *			| 64ms
 *			| 125ms
 *			| 250ms
 *			| 500ms
 *			| 1s
 *			| 2s
 *			| 4s
 *			| 8s,	]
 *
 *	       action,	  none
 *			| irq
 *			| reset
 *			| irq_or_reset,
 *	      );
 * @endcode
 */
#define _hw_mtd_hwa_configure__wdogb	, _hwa_cfwdogb

/*    Optionnal argument `timeout`
 */
#define _hw_is_timeout_timeout		, 1
#define _hw_wdogb_timeout_16ms		, 0
#define _hw_wdogb_timeout_32ms		, 1
#define _hw_wdogb_timeout_64ms		, 2
#define _hw_wdogb_timeout_125ms		, 3
#define _hw_wdogb_timeout_250ms		, 4
#define _hw_wdogb_timeout_500ms		, 5
#define _hw_wdogb_timeout_1s		, 6
#define _hw_wdogb_timeout_2s		, 7
#define _hw_wdogb_timeout_4s		, 8
#define _hw_wdogb_timeout_8s		, 9

#define _hwa_cfwdogb(o,i,a, ...)	\
  do { HW_X(_hwa_cfwdogb_ktimeout,_hw_is_timeout_##__VA_ARGS__)(o,__VA_ARGS__,,) }while(0)

#define _hwa_cfwdogb_ktimeout_1(o,k,v,...)				\
  HW_X(_hwa_cfwdogb_vtimeout,_hw_wdogb_timeout_##v)(o,v,__VA_ARGS__)

#define _hwa_cfwdogb_vtimeout_0(o,v,...)				\
  HW_E_AVL(timeout, v, 16ms | 32ms | 64ms | 125ms | 250ms | 500ms | 1s | 2s | 4s | 8s)

#define _hwa_cfwdogb_vtimeout_1(o,v,k,...)			\
  hwa->o.config.timeout = HW_A1(_hw_wdogb_timeout_##v);		\
  HW_X(_hwa_cfwdogb_kaction,_hw_is_action_##k)(o,k,__VA_ARGS__)

#define _hwa_cfwdogb_ktimeout_0(...)				\
  HW_X(_hwa_cfwdogb_kaction,_hw_is_action_##k)(o,k,__VA_ARGS__)

/*    Mandatory argument `action`
 */
#define _hw_is_action_action		, 1
#define _hw_wdogb_action_none		, 0
#define _hw_wdogb_action_irq		, 1
#define _hw_wdogb_action_reset		, 2
#define _hw_wdogb_action_irq_or_reset	, 3

#define _hwa_cfwdogb_kaction_0(o,k,...)				\
  HW_E_VL(k,action)

#define _hwa_cfwdogb_kaction_1(o,k,v,...)				\
  HW_X(_hwa_cfwdogb_vaction,_hw_wdogb_action_##v)(o,v,__VA_ARGS__)

#define _hwa_cfwdogb_vaction_0(o,v,...)					\
  HW_E_AVL(action, v, none | irq | reset | irq_or_reset)

#define _hwa_cfwdogb_vaction_1(o,v,...)			\
  hwa->o.config.action = HW_A1(_hw_wdogb_action_##v);	\
  HW_EOL(__VA_ARGS__)


/**
 * @page atmelavr_wdogb
 * @section atmelavr_wdogb_turn Turning on/off
 *
 * @code
 * hw( turn, watchdog0,  on
 *                     | off );
 * @endcode
 */
#define _hw_mtd_hw_turn__wdogb		, _hw_turn_wdogb

#define _hw_turn_wdogb(o,i,a, v)			\
  HW_X(_hw_turn_wdogb,_hw_state_##v)(o,v)

#define _hw_turn_wdogb_0(o, v)						\
  HW_E_ST(v)

#define _hw_turn_wdogb_1(o, v)		HW_G2(_hw_turn_wdogb, v)(o)

#define _hw_turn_wdogb_on(o)		_hw_write_reg(o,wde,1)

/*  Disable the watchdog by clearing WDE. That special sequence must be
 *  respected.
 *
 *  FIXME: that also clears WDRF (required) and other reset flags, as well
 *  as WDIE but this should not be a problem. WDP and WDIF are left intact.
 *  May be should only clear WDRF
 *
 *  FIXME: 0x27 is the mask for WDP bits in WDTCR
 */
#define _hw_turn_wdogb_off(o)						\
  do {									\
    uint8_t reg ;							\
    _hw_write_reg( core0, mcusr, 0 );				\
    __asm__ __volatile__("  in	 %[r], %[wdtcr]"	"\n\t"		\
			 "  ori	 %[r], %[wdce]|%[wde]"	"\n\t"		\
			 "  out	 %[wdtcr], %[r]"	"\n\t"		\
			 "  andi %[r], %[wdp]"		"\n\t"		\
			 "  out	 %[wdtcr], %[r]"	"\n\t"		\
			 : [r] "=&d" (reg)				\
			 : [wdtcr] "I" (_HW_A(_HW_M(o, csr))-0x20), \
			   [wdce] "I" (1<<_hw_bp(_HW_M(o, wdce))),	\
			   [wde] "I" (1<<_hw_bp(_HW_M(o, wde))),	\
			   [wdp] "I" (0x27));				\
  } while(0)


/**
 * @page atmelavr_wdogb
 *
 * @code
 * hwa( turn, watchdog0,   on
 *                       | off );
 * @endcode
 */
#define _hw_mtd_hwa_turn__wdogb	, _hwa_turn_wdogb

#define _hwa_turn_wdogb(o,i,a, ...)					\
  HW_X(_hwa_turn_wdogb,_hw_state_##__VA_ARGS__)(o,__VA_ARGS__,)

#define _hwa_turn_wdogb_0(o, v, ...)				\
  HW_E_ST(v)

#define _hwa_turn_wdogb_1(o, v, ...)		\
  HW_G2(_hwa_turn_wdogb, v)(o,i,a)		\
  HW_EOL(__VA_ARGS__)

#define _hwa_turn_wdogb_on(o,i,a)		\
  _hwa_write_reg(o,wde,1)

#define _hwa_turn_wdogb_off(o,i,a)			\
  /* Action completed when committing */		\
  hwa->o.config.action = HW_A1(_hw_wdogb_action_none)


/**
 * @page atmelavr_wdogb
 * @section atmelavr_wdogb_reset Reset
 *
 * The `hw_reset()` instruction resets the watchdog timer (issues a `wdr`):
 *
 * @code
 * hw_reset( watchdog0 );
 * @endcode
 */
#define _hw_mtd_hw_reset__wdogb	, _hw_rstwdogb

#define _hw_rstwdogb(o,i,a,...)			HW_TX(hw_asm("wdr"::),__VA_ARGS__)


/**
 * @page atmelavr_wdogb
 * @section atmelavr_wdogb_stat Status
 *
 * The overflow flag can be accessed through the interrupt-related instructions:
 *
 * @code
 * if ( hw( read, HW_IRQFLAG( watchdog0 ) ) ) {
 *   hw( clear, HW_IRQFLAG( watchdog0 ) );
 *   hw( turn, HW_IRQ( watchdog0, on ) );
 *   n_wdoverflows++ ;
 * }
 * @endcode
 */




/*******************************************************************************
 *									       *
 *	Context management						       *
 *									       *
 *******************************************************************************/

#define _hwa_setup__wdogb(o,i,a)		\
  _hwa_setup_reg( o, csr );			\
  hwa->o.config.action = 0xFF ;			\
  hwa->o.config.timeout = 0xFF

#define _hwa_init__wdogb(o,i,a)			_hwa_init_reg( o, csr, 0x00 )

/**
 * @brief Commit the configuration of a _wdogb class watchdog
 * @hideinitializer
 *
 * Turning the watchdog off requires to:
 *    1. Clear WDRF
 *    2. Clear WDIF
 *    3. Set WDCE and WDE to 1 in the same operation
 *    4. Set WDE to 0 within 4 cycles after step 3.
 */
#define _hwa_commit__wdogb(o,i,a)					\
  do {									\
    if ( hwa->o.config.action != 0xFF ) {				\
      if ( hwa->o.config.action == HW_A1(_hw_wdogb_action_none) ) {	\
	/* Turn it off */						\
	if ( HW_DEVICE_FUSE_WDTON == 0 )				\
	  HWA_ERR( "watchdog can not be turned off because "		\
		   "HW_DEVICE_WATCHDOG_ALWAYS_ON is `enabled`." );	\
	_hwa_write_reg( o, wdrf, 0 );					\
	_hwa_commit_reg( o, wdrf );					\
	_hwa_write_reg( o, if, 1 );	/* was not in _wodga */		\
	_hwa_write_reg( o, wdce, 1 );					\
	_hwa_write_reg( o, wde,	 1 );					\
	_hwa_commit_reg( o, csr );					\
	_hwa_write_reg( o, ie, 0 );					\
	_hwa_write_reg( o, wdce, 0 );					\
	_hwa_write_reg( o, wde, 0 );					\
	_hwa_write_reg( o, wdp, 0 );					\
      }									\
      else {								\
	/* Configure it */						\
	_hwa_write_reg( o, wdce, 1 );	/* was not in _wodga */		\
	_hwa_write_reg( o, wde,	 1 );	/* was not in _wodga */		\
	_hwa_commit_reg( o, csr );	/* was not in _wodga */		\
	_hwa_write_reg( o, wdce, 0 );	/* was not in _wodga */		\
	_hwa_write_reg( o, eie, hwa->o.config.action );			\
	if ( hwa->o.config.timeout != 0xFF )				\
	  _hwa_write_reg( o, wdp, hwa->o.config.timeout );		\
      }									\
      /* hwa->o.config.action = 0xFF ; */				\
      /* hwa->o.config.timeout = 0xFF ; */				\
    }									\
    _hwa_commit_reg( o, csr );						\
  } while(0)


/**
 * @page atmelavr_wdogb
 * <br>
 */
