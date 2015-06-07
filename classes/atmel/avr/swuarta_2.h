
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @page atmelavr_swuarta Class _swuarta: software-emulated UART
 *
 * Class `_swuarta` implements a software UART for 1 or 2-wire communication
 * with automatic transfer rate detection capability.
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
 * `hw_swuart0_autosync`        | sync_5_1<br>sync_10_1        | Synchronization method
 * `hw_swuart0_counter`         | hw_counter0<br>hw_counter1   | Counter used
 * `hw_swuart0_counter_clk_div` | 1<br>8                       | Counter clock division (of `hw_syshz`)
 * `hw_swuart0_counter_compare` | compare0<br>compare1         | Compare unit used for bit timing
 * `hw_swuart0_pin_dbg`         | hw_pin_6                     | Pin used for debugging
 *
 * If `hw_swuart0_pin_tx` and `hw_swuart0_pin_tx` are the same, the UART will revert to
 * RX mode after transmission is completed and transmission will be delayed
 * until reception is completed.<br>
 *
 * Pin-change IRQs associated to `hw_swuart0_pin_tx` are serviced by the UART. This
 * implies that the same pin-change vector can not be used by the application.
 *
 * `hw_swuart0_pin_dbg` is usefull only for debugging the implementation of the UART
 * and should be left undefined.
 *
 * @par Automatic baudrate detection
 *
 * * The `sync_5_1` method waits for a sequence of 5 low-level bits followed by
 *   1 low-level bit. The ASCII character 'A' will do that.
 *
 * * The `sync_10_1` method waits for a sequence of 10 low-level bits followed
 *   by 1 low-level bit. This is done by sending a break byte of 10 low-level
 *   bits followed by a 0xFF byte.
 *
 * Leave `hw_swuart0_autosync` undefined if you do not need this feature.
 */


/*  Configure the hardware for hw_swuart0
 */
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


/*  Configure the hardware for hw_swuart0
 */
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
 * @section atmelavr_swuarta_config Configuring the UART
 *
 * @code
 * hwa_config( hw_swuart0,
 *
 *             //  Transfer rate in bits per second
 *             //
 *           [ bps,         BPS, ]
 *
 *             //  Number of data bits in frame. Must be `8`.
 *             //
 *           [ databits,    8, ]
 *
 *             //  Parity. Must be `none`.
 *             //
 *           [ parity,      none, ]
 *
 *             //  Number of stop bits in frame. Must be `1`.
 *             //
 *           [ stopbits,    1, ]
 *
 *             //  Whether the UART can receive. Default is `enabled`.
 *             //
 *           [ receiver,    enabled | disabled, ]
 *
 *             //  Whether the UART can transmit. Must be `enabled`.
 *             //
 *           [ transmitter, enabled, ]
 *
 *           );
 * @endcode
 */
#define _hw_mthd_hwa_config__swuarta		, _hwa_cfswuarta

#define _hw_is_bps_bps				, 1
#define _hw_is_databits_databits		, 1
#define _hw_is_parity_parity			, 1
#define _hw_is_stopbits_stopbits		, 1
#define _hw_is_receiver_receiver		, 1
#define _hw_is_transmitter_transmitter		, 1

#define _hw_swuarta_csz_8			, 0

#define _hw_swuarta_pm_none			, 0

#define _hw_swuarta_sbs_1			, 0


#define _hwa_cfswuarta(o,i,a,...)					\
  do {									\
    _##o##_config( hwa ); /* configure the counter and i/o */		\
      HW_G2(_hwa_cfswuarta_kbps, HW_IS(bps,__VA_ARGS__))(o,__VA_ARGS__,) \
	} while(0)

/*  Process arg `bps`
 */
#define _hwa_cfswuarta_kbps_1(o,k,v,...)	\
  __##o##_##dtn = (hw_syshz + v/2) / v ;	\
  _hwa_cfswuarta_kbps_0(o,__VA_ARGS__)

#define _hwa_cfswuarta_kbps_0(o,k,...)					\
  HW_G2(_hwa_cfswuarta_kdatabits, HW_IS(databits,k))(o,k,__VA_ARGS__)

/*  Process arg `databits`
 */
#define _hwa_cfswuarta_kdatabits_1(o,k,v,...)				\
  HW_G2(_hwa_cfswuarta_vdatabits, HW_IS(,_hw_swuarta_csz_##v))(o,v,__VA_ARGS__)

#define _hwa_cfswuarta_vdatabits_0(o,v,...)		\
  HW_ERR("`databits` must be `8`, but not `" #v "`.")

#define _hwa_cfswuarta_vdatabits_1(o,v,...)	\
  _hwa_cfswuarta_kdatabits_0(o,__VA_ARGS__)

#define _hwa_cfswuarta_kdatabits_0(o,k,...)				\
  HW_G2(_hwa_cfswuarta_kparity, HW_IS(parity,k))(o,k,__VA_ARGS__)

/*  Process arg `parity`
 */
#define _hwa_cfswuarta_kparity_1(o,k,v,...)				\
  HW_G2(_hwa_cfswuarta_vparity, HW_IS(,_hw_swuarta_pm_##v))(o,v,__VA_ARGS__)

#define _hwa_cfswuarta_vparity_0(o,v,...)		\
  HW_ERR("`parity` must be `none`, but not `" #v "`.")

#define _hwa_cfswuarta_vparity_1(o,v,...)	\
  _hwa_cfswuarta_kparity_0(o,__VA_ARGS__)

#define _hwa_cfswuarta_kparity_0(o,k,...)				\
  HW_G2(_hwa_cfswuarta_kstopbits, HW_IS(stopbits,k))(o,k,__VA_ARGS__)

/*  Process arg `stopbits`
 */
#define _hwa_cfswuarta_kstopbits_1(o,k,v,...)				\
  HW_G2(_hwa_cfswuarta_vstopbits, HW_IS(,_hw_swuarta_sbs_##v))(o,v,__VA_ARGS__)

#define _hwa_cfswuarta_vstopbits_0(o,v,...)		\
  HW_ERR("`stopbits` must be `1`, but not `" #v "`.")

#define _hwa_cfswuarta_vstopbits_1(o,v,...)	\
  _hwa_cfswuarta_kstopbits_0(o,__VA_ARGS__)

#define _hwa_cfswuarta_kstopbits_0(o,k,...)				\
  HW_G2(_hwa_cfswuarta_kreceiver, HW_IS(receiver,k))(o,k,__VA_ARGS__)

/*  Process arg `receiver`
 */
#define _hwa_cfswuarta_kreceiver_1(o,k,v,...)				\
  HW_G2(_hwa_cfswuarta_vreceiver, HW_IS(,hw_state_##v))(o,v,__VA_ARGS__)

#define _hwa_cfswuarta_vreceiver_0(o,v,...)				\
  HW_ERR("`receiver` can be `enabled`, or `disabled`, but not `" #v "`.")

#define _hwa_cfswuarta_vreceiver_1(o,v,...)		\
  _hwa_turn_irq(HW_G2(o,pin_rx),change,hw_state_##v));	\
  _hwa_cfswuarta_kreceiver_0(o,__VA_ARGS__)

#define _hwa_cfswuarta_kreceiver_0(o,k,...)				\
  HW_G2(_hwa_cfswuarta_ktransmitter, HW_IS(transmitter,k))(o,k,__VA_ARGS__)

/*  Process arg `transmitter`
 */
#define _hwa_cfswuarta_ktransmitter_1(o,k,v,...)			\
    HW_G2(_hwa_cfswuarta_vtransmitter, HW_IS(,hw_state_##v))(o,v,__VA_ARGS__)

#define _hwa_cfswuarta_vtransmitter_0(o,v,...)				\
  HW_ERR("`transmitter` can be `enabled`, or `disabled`, but not `" #v "`.")

#define _hwa_cfswuarta_vtransmitter_1(o,v,...)	\
  hwa->o.config.txen = HW_A1(hw_state_##v);	\
  _hwa_cfswuarta_end(o,__VA_ARGS__)

#define _hwa_cfswuarta_ktransmitter_0(o,...)	\
  _hwa_cfswuarta_end(o,__VA_ARGS__)

#define _hwa_cfswuarta_end(o,...)		\
  HW_TX(,__VA_ARGS__)


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
 * hw_stat_t( hw_swuart0 ) st ;   // Structure of UART status
 * st = hw_stat( hw_swuart0 );    // Read the status
 * if ( st.rxc )                  // Reception complete?
 *   byte = hw_read( hw_swuart0 );
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
} _hw_swuarta_stat_t ;

#define _hw_mthd_hw_stat_t__swuarta	, _hw_sttswuarta
#define _hw_sttswuarta(p,i,a,...)	HW_TX( _hw_swuarta_stat_t, __VA_ARGS__)

#define _hw_mthd_hw_stat__swuarta	, _hw_stswuarta
#define _hw_stswuarta(p,i,a,...)					\
  HW_TX( (*(volatile _hw_swuarta_stat_t*)_##p##__st), __VA_ARGS__)


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
