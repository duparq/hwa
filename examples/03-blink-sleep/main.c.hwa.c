
/*	Blink a LED at ~2 Hz using watchdog interrupts and sleep mode
 */

//#define HW_DEVICE_WATCHDOG_ALWAYS_ON			yes

#include "config.attiny85.h"
#include <hwa.h>

#define hw_is_sleep_sleep		, 1
#define hw_is_awaker_awaker		, 1

#define hw_awaker_io			, 0
#define hw_awaker_adc			, 1
#define hw_awaker_int0			, 2
#define hw_awaker_pinchange		, 2
#define hw_awaker_usi_start_condition	, 2
#define hw_awaker_watchdog		, 2




#define _hwa_config_core(c,n,i,a,...)					\
  do {									\
    uint8_t sleep = 0xFF ;						\
    uint8_t level ;							\
    uint8_t awaker_level = 2 ;						\
    HW_G2(_hwa_cfcore_xsleep, HW_IS(sleep,__VA_ARGS__))(__VA_ARGS__);	\
  } while(0)

#define _hwa_cfcore_xsleep_0(...)					\
  HW_ERR("expected `sleep`, got `" HW_QUOTE(__VA_ARGS__) "` instead.")

#define _hwa_cfcore_xsleep_1(kw,...)					\
  HW_G2(_hwa_cfcore_vsleep, HW_IS(,hw_state_##__VA_ARGS__))(__VA_ARGS__)

#define _hwa_cfcore_vsleep_0(...)					\
  HW_ERR("expected `enabled` or `disabled`, got `" HW_QUOTE(__VA_ARGS__) "` instead.")

#define _hwa_cfcore_vsleep_1(v,...)					\
  sleep = HW_A1(hw_state_##v);						\
  _hwa_write_reg(hw_core0, se, sleep );					\
  HW_G2(_hwa_cfcore_xawaker1, HW_IS(awaker,__VA_ARGS__))(__VA_ARGS__)

#define _hwa_cfcore_xawaker1_0(...)	_hwa_cfcore_end(__VA_ARGS__)

#define _hwa_cfcore_xawaker1_1(kw,...)					\
  HW_G2(_hwa_cfcore_vawaker1, HW_IS(,hw_awaker_##__VA_ARGS__))(__VA_ARGS__)

#define _hwa_cfcore_vawaker1_0(v,...)				\
  HW_ERR("`awaker` can be `int0`, `pinchange`, `adc`, or "	\
	 "`watchdog`, but not `" HW_QUOTE(v) "`.")

#define _hwa_cfcore_vawaker1_1(v,...)		\
  level = HW_A1(hw_awaker_##v);			\
  if ( level < awaker_level )			\
    awaker_level = level ;			\
  _hwa_cfcore_end(__VA_ARGS__)

#define _hwa_cfcore_end(...)			\
  if ( sleep == 1 )				\
    _hwa_write_reg(hw_core0, sm, awaker_level);	\
  HW_TX(,__VA_ARGS__)




/*  Watchdog timeout interrupt
 *
 *    The IRQ awakes the MCU but the ISR itself does nothing. Then we can spare
 *    a few bytes of program memory declaring the ISR 'naked' and inserting the
 *    'reti' instruction ourselves since otherwise avr-gcc does some register
 *    initializations even though none is used.
 */
    HW_ISR( hw_watchdog0, naked )
    {
      __asm__ __volatile__("reti"	"\n\t" ::: );
    }


int main ( )
{
  static uint8_t	count = 0 ;

  hwa_begin_from_reset();

  /*	Configure LED pin
   */
  hwa_config( PIN_LED, direction, output );
  //  hwa_write( PIN_LED, 1 );
  //  hwa_write( PIN_LED, 0 );

  /*	Have the CPU enter power_down mode when the 'sleep' instruction is
   *	executed and make it wake up as a watchdog interrupt occurs.
   */
  hwa_config( hw_core0,
  	      sleep,		enabled,
  	      awaker,		watchdog );

  /*	Stop the watchdog and enter sleep if the watchdog triggered a reset.
   *	Note: when the device is reset by the watchdog, the watchdog remains enabled!
   */
  if ( hw_stat( hw_core0 ).reset_by_watchdog ) {
    hwa_turn( hw_watchdog0, off );
    hwa_commit();
    hw_sleep();
    for (;;)			/* This should */
      hw_toggle( PIN_LED );	/* not happen  */
  }

  /*	Watchdog timeout and action. The IRQ is used to wake-up the CPU.
   */
  hwa_config( hw_watchdog0,
  	      timeout,      250ms,
  	      action,       irq_or_reset );

  hwa_commit();

  /*	MCU can't awake from sleep without interrupts.
   */
  hw_enable_interrupts();

  for(;;) {
    hw_sleep();
    hw_toggle( PIN_LED );
    count++ ;
    if ( count < 19 ) {
      /*
       *  WDIE is cleared by hardware after a time-out when watchdog action is
       *  set to 'irq_or_reset'. If it is not set, the next time-out will
       *  trigger a reset.
       */
      /* hw_write_reg( hw_watchdog0, wdie, 1 ); */
      hwa_begin();
      hwa_config( hw_watchdog0,
		  timeout,      250ms,
		  action,       irq_or_reset );
      hwa_commit();
    }
  }

  return 0 ;
}
HW_DEVICE_FLASH_SIZE
HW_DEVICE_FUSE_EB
HW_DEVICE_FUSE_HB
HW_DEVICE_FUSE_LB
HW_DEVICE
