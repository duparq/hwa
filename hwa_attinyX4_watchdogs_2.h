
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


HW_INLINE void _hwa_begin_watchdogs ( hwa_t *hwa )
{
  _hwa_begin_reg( hw_watchdog0, csr );
}


HW_INLINE void _hwa_reset_watchdogs ( hwa_t *hwa )
{
  _hwa_reset_r8( &hwa->watchdog0.csr );
}


HW_INLINE void _hwa_commit_watchdogs ( hwa_t *hwa )
{
  _hwa_commit_r8( hwa->commit, &hwa->watchdog0.csr, -1 );
}


#define _hw_turn_wdog(c,n,i,a, vstate)					\
  HW_G2(_hw_turn_wdog, HW_IS(,hw_state_##vstate))(c,n,i,a,vstate)
#define _hw_turn_wdog_0(c,n,i,a, vstate)			\
  HW_ERR("expected `on` or `off`, got `" #vstate "` instead.")
#define _hw_turn_wdog_1(c,n,i,a, vstate)	\
  HW_G2(_hw_turn_wdog, vstate)(c,n,i,a)
#define _hw_turn_wdog_on(c,n,i,a)		\
  _hw_write_reg(c,n,i,a,wde,1)


/*  Disable the watchdog by clearing WDE. That special sequence must be
 *  respected. That also clears WDRF (required) and other reset flags, as well
 *  as WDIE but this should not be a problem. WDP and WDIF are left intact.
 */
#define _hw_turn_wdog_off(c,n,i,a)			\
  __asm__ __volatile__("    ldi  r24, 0"	"\n\t"	\
		       "    out  0x34, r24"	"\n\t"	\
		       "    in   r24, 0x21"	"\n\t"	\
		       "    ori  r24, 0x18"	"\n\t"	\
		       "    out  0x21, r24"	"\n\t"	\
		       "    andi r24, 0x27"	"\n\t"	\
		       "    out  0x21, r24"	"\n\t"	\
		       ::: "r24" );


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


#define _hwa_config_wdog(c,n,i,a, ...)		\
  do {						\
    uint8_t timeout=0xFF, action=0xFF ;		\
    _hwa_config_wdog_timeout(n,__VA_ARGS__,)	\
      }while(0)

/*    Optionnal argument `timeout`
 */
#define _hwa_config_wdog_timeout(n,...)					\
  HW_G2(_hwa_config_wdog_xtimeout,HW_IS(timeout,__VA_ARGS__))(n,__VA_ARGS__)
#define _hwa_config_wdog_xtimeout_0(...)	_hwa_config_wdog_action(__VA_ARGS__)
#define _hwa_config_wdog_xtimeout_1(n,timeout,...)			\
  HW_G2(_hwa_config_wdog_vtimeout,HW_IS(,hw_wdog_timeout_##__VA_ARGS__))(n,__VA_ARGS__)
#define _hwa_config_wdog_vtimeout_0(n,vtimeout,...)			\
  HW_ERR("`timeout` can be `16ms`, `32ms`, `64ms`, `125ms`, `250ms`, `500ms`, `1s`, " \
	 "`2s`, `4s` or `8s` but not `" #vtimeout "`.")
#define _hwa_config_wdog_vtimeout_1(n,vtimeout,...)	\
  timeout = HW_A1(hw_wdog_timeout_##vtimeout);		\
  _hwa_config_wdog_action(n,__VA_ARGS__)

/*    Mandatory argument `action`
 */
#define _hwa_config_wdog_action(n,...)					\
  HW_G2(_hwa_config_wdog_xaction,HW_IS(action,__VA_ARGS__))(n,__VA_ARGS__)
#define _hwa_config_wdog_xaction_0(n,...)				\
  HW_ERR("expected `action` instead of `" HW_QUOTE(__VA_ARGS__) "`.")
#define _hwa_config_wdog_xaction_1(n,action,...)			\
  HW_G2(_hwa_config_wdog_vaction,HW_IS(,hw_wdog_action_##__VA_ARGS__))(n,__VA_ARGS__)
#define _hwa_config_wdog_vaction_0(n,vaction,...)			\
  HW_ERR("`action` can be `none`, `irq`, `reset`, or `irq_or_reset` but not `" #vaction "`.")
#define _hwa_config_wdog_vaction_1(n,vaction,...)	\
  action = HW_A1(hw_wdog_action_##vaction);		\
  _hwa_docfwdog( hwa, timeout, action );		\
  HW_EOP(__VA_ARGS__)					\


/*  Process the configuration of the watchdog
 */
HW_INLINE void _hwa_docfwdog( hwa_t *hwa, uint8_t timeout, uint8_t action )
{
  if ( timeout != 0xFF )
    _hwa_write_reg( hw_watchdog0, wdp, timeout );
  if ( action == 0 ) {
    /*
     *  Turn the watchdog off. This requires a special sequence, so we do it
     *  here instead of using the registers cache.
     *
     *	FIXME: that should be done in _hwa_commit_watchdogs()
     */
    _hw_turn_wdog_off(,,,);
  }
  else if ( action != 0xFF ) {
    _hwa_write_reg( hw_watchdog0, wde,  action&0x02 );
    _hwa_write_reg( hw_watchdog0, wdie, action&0x01 );
  }
}
