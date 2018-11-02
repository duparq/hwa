
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
#define _hw_mtd_hwa_configure__wdoga	, _hwa_cfwdoga

/*    Optionnal argument `timeout`
 */
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

#define _hwa_cfwdoga(o,i,a,k,...)					\
  do { HW_Y(_hwa_cfwdoga_ktimeout,_hw_is_timeout_##k)(o,k,__VA_ARGS__,,) }while(0)

#define _hwa_cfwdoga_ktimeout_1(o,k,v,...)				\
  HW_Y(_hwa_cfwdoga_vtimeout,_hw_wdoga_timeout_##v)(o,v,__VA_ARGS__)

#define _hwa_cfwdoga_vtimeout_0(o,v,...)				\
  HW_E_AVL(timeout, v, 16ms | 32ms | 64ms | 125ms | 250ms | 500ms | 1s | 2s | 4s | 8s)

#define _hwa_cfwdoga_vtimeout_1(o,v,k,...)			\
  hwa->o.config.timeout = HW_A1(_hw_wdoga_timeout_##v);		\
  HW_Y(_hwa_cfwdoga_kaction,_hw_is_action_##k)(o,k,__VA_ARGS__)

#define _hwa_cfwdoga_ktimeout_0(...)				\
  HW_Y(_hwa_cfwdoga_kaction,_hw_is_action_##k)(o,k,__VA_ARGS__)

/*    Mandatory argument `action`
 */
#define _hw_wdoga_action_none		, 0
#define _hw_wdoga_action_irq		, 1
#define _hw_wdoga_action_reset		, 2
#define _hw_wdoga_action_irq_or_reset	, 3

#define _hwa_cfwdoga_kaction_0(o,k,...)				\
  HW_E_VL(k,action)

#define _hwa_cfwdoga_kaction_1(o,k,v,...)				\
  HW_Y(_hwa_cfwdoga_vaction,_hw_wdoga_action_##v)(o,v,__VA_ARGS__)

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
 * hw( turn watchdog0,   on
 *                     | off );
 * @endcode
 */
#define _hw_mtd_hw_turn__wdoga		, _hw_turn_wdoga

#define _hw_turn_wdoga(o,i,a, v)			\
  HW_Y(_hw_turn_wdoga,_hw_state_##v)(o,v)

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
 * @page atmelavr_wdoga
 *
 * @code
 * hwa( turn, watchdog0,   on
 *                       | off );
 * @endcode
 */
#define _hw_mtd_hwa_turn__wdoga	, _hwa_turn_wdoga

#define _hwa_turn_wdoga(o,i,a,k,...)	HW_Y(_hwa_turn_wdoga,_hw_state_##k)(o,k,__VA_ARGS__,)

#define _hwa_turn_wdoga_0(o, v, ...)	HW_E_ST(v)

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
 * hw_reset( watchdog0 );
 * @endcode
 */
#define _hw_mtd_hw_reset__wdoga	, _hw_rstwdoga

#define _hw_rstwdoga(o,i,a,...)			hw_asm("wdr"::) HW_EOL(__VA_ARGS__)


/**
 * @page atmelavr_wdoga
 * @section atmelavr_wdoga_stat Status
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
	_hwa_write_reg( o, wde,	 1 );					\
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


/**
 * @page atmelavr_wdoga
 * <br>
 */
