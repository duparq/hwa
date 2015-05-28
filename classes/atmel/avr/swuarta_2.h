
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @page atmelavr_swuarta Class _swuarta: software-emulated UART
 *
 * Class `_swuarta` implements a software UART for 1 or 2-wire communication
 * with automatic baudrate detection capability.
 *
 * `_swuarta` can work with an 8 or 16-bit counter. It can use any pin that
 * provides a pin-change interrupt.
 *
 * Tested on ATtinyX4 with internal oscillator (~8 MHz):
 * -  1200..115200 bps with 16-bit timer not prescaled
 * -   450.. 50000 bps with 16-bit timer 1/8 prescaled
 * - 38400..115200 bps with  8-bit timer not prescaled
 * -         10000 bps with  8-bit timer 1/8 prescaled
 */


/**
 * @page atmelavr_swuarta
 * @section atmelavr_swuarta_hardconf Compile-time configuration
 *
 * Note: the naming of these symbols will change in the future to suit HWA
 * object-oriented style better.
 *
 * For efficiency reasons, a large part of the configuration must be defined at
 * compile time. The following symbols must be defined in your project.
 *
 * Symbol | Example | Comment
 * :------|:--------|:-------
 * `hw_swuart0_pin_tx`          | hw_pin_pa0                   | Pin used for TXD
 * `hw_swuart0_pin_rx`          | hw_pin_5                     | Pin used for RXD
 * `hw_swuart0_autosync`        | 5_1<br>10_1                  | Synchronization method
 * `hw_swuart0_counter`         | hw_counter0<br>hw_counter1   | Counter used
 * `hw_swuart0_counter_clk_div` | 1<br>8                       | Counter clock division (of `hw_syshz`)
 * `hw_swuart0_counter_compare` | compare0<br>compare1         | Compare unit used for bit timing
 * `hw_swuart0_pin_dbg`         | hw_pin_6                     | Pin used for debugging
 *
 * If `HW_SWUART0_PIN_TX` and `HW_SWUART0_PIN_TX` are the same, the UART will revert to
 * RX mode after transmission is completed and transmission will be delayed
 * until reception is completed.<br>
 *
 * Pin-change IRQs associated to `HW_SWUART0_PIN_TX` are serviced by the UART. This
 * implies that the same pin-change vector can not be used by the application.
 *
 * `hw_swuart0_pin_dbg` is usefull only for debugging the implementation of the UART
 * and should be left undefined.
 *
 * @par Automatic baudrate detection
 *
 * * The `5_1` method waits for a sequence of 5 low-level bits followed by 1
 *   low-level bit. The ASCII character 'A' will do that.
 *
 * * The `10_1` method waits for a sequence of 10 low-level bits followed by 1
 *   low-level bit. This is done by sending a break byte of 10 low-level bits
 *   followed by a 0xFF byte.
 *
 * Leave `hw_swuart0_autosync` undefined if you do not need this feature.
 */


/**
 * @page atmelavr_swuarta
 * @section atmelavr_swuarta_config Configuring the UART
 *
 * @code
 * hwa_config(  UART,
 *             [baudrate, BAUDRATE ]
 *           );
 * @endcode
 */
#define _hw_mthd_hwa_config__swuarta	, _hwa_swuarta_config
//#define _hwa_swuarta_config(p,i,a,...)	HW_TX(_swuart_configure(hwa),__VA_ARGS__)


#define _hw_cfswuarta_baudrate


#define _hwa_swuarta_config(p,i,a,...)					\
  do {									\
    _##p##_config( hwa );							\
    HW_G2(_hwa_cfswuarta_xbaud, HW_IS(,_hw_cfswuarta_##__VA_ARGS__))(p,__VA_ARGS__) \
  } while(0)

#define _hwa_cfswuarta_xbaud_1(p,kw,v,...)		\
  __##p##_##dtn = hw_syshz / v ;			\
  HW_TX(,__VA_ARGS__)

#define _hwa_cfswuarta_xbaud_0(p,...)	HW_TX(,__VA_ARGS__)


HW_INLINE void _hw_swuart0_config ( hwa_t *hwa __attribute__((unused)) )
{
  /*  Counter
   */
#if defined hw_swuart0_counter
  hwa_config( hw_swuart0_counter,
	      clock,     HW_G2(syshz_div, hw_swuart0_counter_clk_div),
	      countmode, loop_up,
	      top,       max );
#endif

  /*  RX pin
   */
#if defined hw_swuart0_pin_rx
  hwa_config( hw_swuart0_pin_rx, direction, input );
  hwa_clear_irqf( hw_swuart0_pin_rx, change );
  hwa_turn_irq( hw_swuart0_pin_rx, change, on );
  hwa_write_reg( hw_pcic0, hw_swuart0_pin_rx, 1 );
#endif

  /*  TX pin
   *
   *	Configure TX pin as state 1 output unless the pin is also used for RX.
   */
#if defined hw_swuart0_pin_tx && hw_id(hw_swuart0_pin_tx) != hw_id(hw_swuart0_pin_rx)
  hwa_config( hw_swuart0_pin_tx, direction, output );
  hwa_write( hw_swuart0_pin_tx, 1 );
#endif

  /*	DBG pin
   */
#if defined hw_swuart0_pin_dbg
  hwa_config( hw_swuart0_pin_dbg, direction, output );
#endif
}


HW_INLINE void _hw_swuart1_config ( hwa_t *hwa __attribute__((unused)) )
{
  /*  Counter
   */
#if defined hw_swuart1_counter
  hwa_config( hw_swuart1_counter,
	      clock,     HW_G2(syshz_div, hw_swuart1_counter_clk_div),
	      countmode, loop_up,
	      top,       max );
#endif

  /*  RX pin
   */
#if defined hw_swuart1_pin_rx
  hwa_config(hw_swuart1_pin_rx, direction, input);
  hwa_clear_irqf(hw_swuart1_pin_rx, change);
  hwa_turn_irq(hw_swuart1_pin_rx, change, on);
  hwa_write_reg( hw_pcic0, hw_swuart1_pin_rx, 1 );
#endif

  /*  TX pin
   *
   *	Configure TX pin as state 1 output unless the pin is also used for RX.
   */
#if defined hw_swuart1_pin_tx && hw_id(hw_swuart1_pin_tx) != hw_id(hw_swuart1_pin_rx)
  hwa_config(hw_swuart1_pin_tx, direction, output);
  hwa_write(hw_swuart1_pin_tx, 1);
#endif

  /*	DBG pin
   */
#if defined hw_swuart1_pin_dbg
  hwa_config( hw_swuart1_pin_dbg, direction, output );
#endif
}



/**
 * @page atmelavr_swuarta
 * @section atmelavr_swuarta_read Reading one byte from UART
 *
 * @code
 * uint8_t byte = hw_read( UART );
 * @endcode
 */
#define _hw_mthd_hw_read__swuarta	, _hw_swuarta_read
#define _hw_swuarta_read(o,i,a,...)	HW_TX(_##o##_getbyte(),__VA_ARGS__)

extern uint8_t				_hw_swuart0_getbyte ( ) ;
extern uint8_t				_hw_swuart1_getbyte ( ) ;


/**
 * @page atmelavr_swuarta
 * @section atmelavr_swuarta_write Writing one byte into UART
 *
 * @code
 * hw_write( UART, '#' );
 * @endcode
 */
#define _hw_mthd_hw_write__swuarta	, _hw_swuarta_write
#define _hw_swuarta_write(o,i,a,v,...)	HW_TX(_##o##_putbyte(v),__VA_ARGS__)

extern void				_hw_swuart0_putbyte ( uint8_t byte ) ;
extern void				_hw_swuart1_putbyte ( uint8_t byte ) ;


/**
 * @page atmelavr_swuarta
 * @section atmelavr_swuarta_stat Getting the status of the UART
 *
 * The UART status contains the following flags:
 *
 * * stop: the state of the received stop bit
 * * idle: the UART is ready for RX or TX
 * * rxc: receiving complete (stop bit sampled)
 * * txc: transmission complete (stop bit sent)
 * * synced: the UART is synchronized
 *
 * @code
 * uint8_t byte ;
 * hw_stat_t( UART ) st ;       // Structure of UART status
 * st = hw_stat( UART );        // Read the status
 * if ( st.rxc )                // Reception complete?
 *   byte = hw_read( UART );
 * @endcode
 */
typedef struct {
  unsigned int	stop	: 1 ;
  unsigned int	idle    : 1 ;
  unsigned int	rxc     : 1 ;
  unsigned int	txc     : 1 ;
  unsigned int	rxtx    : 1 ;
  unsigned int	wbtx    : 1 ;
  unsigned int	synced  : 1 ;
  unsigned int  __7     : 1 ;
} swuart_status_t ;

#define _hw_mthd_hw_stat_t__swuarta	, _hw_swuarta_stat_t
#define _hw_swuarta_stat_t(p,i,a,...)	HW_TX( swuart_status_t, __VA_ARGS__)

#define _hw_mthd_hw_stat__swuarta	, _hw_swuarta_stat
//#define _hw_swuarta_stat(p,i,a,...)	HW_TX( (*(volatile swuart_status_t*)swuart_st), __VA_ARGS__)
#define _hw_swuarta_stat(p,i,a,...)	HW_TX( (*(volatile swuart_status_t*)_##p##__st), __VA_ARGS__)


/**
 * @page atmelavr_swuarta
 * @section atmelavr_swuarta_reset Resetting the UART
 *
 * Resetting the UART will abort any transmission or reception. If the UART has automatic
 * baudrate detection, the UART will first resynchronize.
 *
 * @code
 * hw_reset( UART );
 * @endcode
 */
#define _hw_mthd_hw_reset__swuarta		, _hw_swuarta_reset
#define _hw_swuarta_reset(p,i,a,...)		HW_TX(_##p##_##reset(),__VA_ARGS__)

extern void					_hw_swuart0_reset ( ) ;
extern void					_hw_swuart1_reset ( ) ;

#if defined hw_swuart0_counter
extern hw_rt(hw_swuart0_counter,count)		__hw_swuart0_dtn ;
extern hw_rt(hw_swuart0_counter,count)		__hw_swuart0_dt0 ;
#endif


#if defined hw_swuart1_counter
extern hw_rt(hw_swuart1_counter,count)		__hw_swuart1_dtn ;
extern hw_rt(hw_swuart1_counter,count)		__hw_swuart1_dt0 ;
#endif

/**
 * @page atmelavr_swuarta
 * <br>
 */
