
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


/*	Watchdog class methods declared for derived classes
 *
 *	hw/hwa_turn_wdog
 *	hw/hwa_reset_wdog
 *	hw_stat_wdog
 */


/*	Turn watchdog on/off (synchronous)
 */
#define _hw_turn_wdog(c,n,i,a, vstate)					\
  HW_G2(_hw_turn_wdog, HW_IS(,hw_state_##vstate))(c,n,i,a,vstate)
#define _hw_turn_wdog_0(c,n,i,a, vstate)			\
  HW_ERR("expected `on` or `off`, got `" #vstate "` instead.")
#define _hw_turn_wdog_1(c,n,i,a, vstate)	\
  HW_G2(_hw_turn_wdog, vstate)(c,n,i,a)

#define _hw_turn_wdog_on(c,n,i,a)		\
  _hw_write_reg(c,n,i,a,wde,1)


/*  Disable the watchdog by clearing WDE. That special sequence must be
 *  respected.
 *
 *  FIXME: that also clears WDRF (required) and other reset flags, as well
 *  as WDIE but this should not be a problem. WDP and WDIF are left intact.
 *  May be should only clear WDRF
 *
 *  FIXME: 0x27 is the mask for WDP bits in WDTCR
 */
#define _hw_turn_wdog_off(c,n,i,a)					\
  do {									\
    uint8_t reg ;							\
    _hw_write_reg( hw_core0, mcusr, 0 );				\
    __asm__ __volatile__("  in   %[r], %[wdtcr]"	"\n\t"		\
			 "  ori  %[r], %[wdce]|%[wde]"	"\n\t"		\
			 "  out  %[wdtcr], %[r]"	"\n\t"		\
			 "  andi %[r], %[wdp]"		"\n\t"		\
			 "  out  %[wdtcr], %[r]"	"\n\t"		\
			 : [r] "=&d" (reg)				\
			 : [wdtcr] "I" (_hw_addr(_hw_reg(c,n,i,a, csr))-0x20), \
			   [wdce] "I" (1<<_hw_bp(_hw_reg(c,n,i,a, wdce))), \
			   [wde] "I" (1<<_hw_bp(_hw_reg(c,n,i,a, wde))), \
			   [wdp] "I" (0x27));				\
  } while(0)


/*	Turn watchdog on/off (asynchronous)
 */
#define _hwa_turn_wdog(c,n,i,a, ...)					\
  HW_G2(_hwa_turn_wdog, HW_IS(,hw_state_##__VA_ARGS__))(c,n,i,a,__VA_ARGS__,)
#define _hwa_turn_wdog_0(c,n,i,a, v, ...)			\
  HW_ERR("expected `on` or `off`, got `" #v "` instead.")
#define _hwa_turn_wdog_1(c,n,i,a, v, ...)	\
  HW_G2(_hwa_turn_wdog, v)(c,n,i,a)		\
  HW_TX(,__VA_ARGS__)

#define _hwa_turn_wdog_on(c,n,i,a)		\
  _hwa_write_reg(c,n,i,a,wde,1)

#define _hwa_turn_wdog_off(c,n,i,a)			\
  hwa->watchdog0.action = HW_A1(hw_wdog_action_none)


/*  Clear (reset) watchdog or just the irq flag
 *
 *	hw_clear( hw_watchdog0 ) resets the watchdog timer
 *	hw_clear( hw_watchdog0, irq ) clears the watchdog irq and sets WDIE
 *	hw_clear_irq( hw_watchdog0 ) only clears the watchdog irq flag
 *
 *	WDIE is cleared by hardware after a timeout occurs then it must be set
 *	again to 1 when the interrupt flag is cleared. Otherwise the device will
 *	be RESET at the next timeout.
 */
#define _hw_clwdog(c,n,i,a,...)						\
  HW_G2(_hw_clwdog_xirq,HW_IS(irq,__VA_ARGS__))(c,n,i,a,__VA_ARGS__)

#define _hw_clwdog_xirq_0(c,n,i,a,...)		\
  HW_TX(__asm__( "wdr":: ) ,__VA_ARGS__)

#define _hw_clwdog_xirq_1(c,n,i,a,irq,...)			\
  HW_TX(_hw_write_reg_2(c,n,i,a, wdifie, 3) ,__VA_ARGS__)



/*	Configure watchdog
 */
#define hw_is_timeout_timeout		, 1
#define hw_wdog_timeout_16ms		, 0
#define hw_wdog_timeout_32ms		, 1
#define hw_wdog_timeout_64ms		, 2
#define hw_wdog_timeout_125ms		, 3
#define hw_wdog_timeout_250ms		, 4
#define hw_wdog_timeout_500ms		, 5
#define hw_wdog_timeout_1s		, 6
#define hw_wdog_timeout_2s		, 7
#define hw_wdog_timeout_4s		, 8
#define hw_wdog_timeout_8s		, 9

#define hw_is_action_action		, 1
#define hw_wdog_action_none		, 0
#define hw_wdog_action_irq		, 1
#define hw_wdog_action_reset		, 2
#define hw_wdog_action_irq_or_reset	, 3


#define _hwa_cfwdog(c,n,i,a, ...)	_hwa_cfwdog_timeout(n,__VA_ARGS__)

/*    Optionnal argument `timeout`
 */
#define _hwa_cfwdog_timeout(n,kw,...)					\
    HW_G2(_hwa_cfwdog_xtimeout,HW_IS(timeout,kw))(n,kw,__VA_ARGS__)
#define _hwa_cfwdog_xtimeout_0(...)	_hwa_cfwdog_action(__VA_ARGS__)
#define _hwa_cfwdog_xtimeout_1(n,kw,...)				\
    HW_G2(_hwa_cfwdog_vtimeout,HW_IS(,hw_wdog_timeout_##__VA_ARGS__))(n,__VA_ARGS__)
#define _hwa_cfwdog_vtimeout_0(n,v,...)					\
    HW_ERR("`timeout` can be `16ms`, `32ms`, `64ms`, `125ms`, `250ms`, `500ms`, `1s`, " \
	   "`2s`, `4s` or `8s` but not `" #v "`.")
#define _hwa_cfwdog_vtimeout_1(n,v,...)		\
  hwa->n.timeout = HW_A1(hw_wdog_timeout_##v);	\
  _hwa_cfwdog_action(n,__VA_ARGS__);

/*    Mandatory argument `action`
 */
#define _hwa_cfwdog_action(n,kw,...)				\
  HW_G2(_hwa_cfwdog_xaction,HW_IS(action,kw))(n,kw,__VA_ARGS__)
#define _hwa_cfwdog_xaction_0(n,kw,...)				\
    HW_ERR("expected `action` instead of `" HW_QUOTE(kw) "`.")
#define _hwa_cfwdog_xaction_1(n,kw,v,...)				\
  HW_G2(_hwa_cfwdog_vaction,HW_IS(,hw_wdog_action_##v))(n,v,__VA_ARGS__)
#define _hwa_cfwdog_vaction_0(n,v,...)					\
  HW_ERR("`action` can be `none`, `irq`, `reset`, or `irq_or_reset` but not `" #v "`.")
#define _hwa_cfwdog_vaction_1(n,v,...)		\
    hwa->n.action = HW_A1(hw_wdog_action_##v);	\
    HW_TX(,__VA_ARGS__)


/*  Watchdog status
 *
 *	hw_stat_t(...) declares the structure that holds the status
 *	hw_stat(...) reads and returns the status
 *
 *	The only flag that is available is the irq flag.
 */
typedef union {
  uint8_t         byte ;
  struct {
    unsigned int  __0to6a : 7 ;
    unsigned int  irq     : 1 ;
  };
} _hw_wdog_stat_t ;


#define _hw_statt_wdog(c,n,i,a,...)	HW_TX(_hw_wdog_stat_t, __VA_ARGS__)
#define _hw_stat_wdog(c,n,i,a)		_hw_wdog_stat( _hw_read_reg(c,n,i,a, csr) )


HW_INLINE _hw_wdog_stat_t _hw_wdog_stat( uint8_t byte )
{
  _hw_wdog_stat_t	st ;
  st.byte = byte ;
  return st ;
}
