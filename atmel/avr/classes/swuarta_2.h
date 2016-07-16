
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Software-emulated UART
 */

/**
 * @page atmelavr_swuarta Class _swuarta: software-emulated UART
 *
 * Class `_swuarta` implements a software-emulated UART with the following
 * features:
 *
 * * simplex or half-duplex communication over 1 or 2 wires
 * * frames of 1 start bit, 8 data bits, 1 stop bit (no parity bit)
 * * requirements:
 *   * one 8 or 16-bit counter compare unit
 *   * one pin able to trigger an interrupt when a falling edge or any
 *     change occurs (currently, only pin-change is implemented) for RXD
 * * optionnal automatic baudrate detection
 * * optionnal bus-collision detection
 *
 * @par Performances
 *
 * `_swuarta` has been successfully tested on ATtinyX4 with internal oscillator
 * (~8 MHz):
 *
 *  * 1200..115200 bps with 16-bit timer not prescaled
 *  * 450.. 50000 bps with 16-bit timer 1/8 prescaled
 *  * 38400..115200 bps with 8-bit timer not prescaled
 *  * 10000 bps with 8-bit timer 1/8 prescaled
 *
 *  * ATtiny85 rc_8MHz hw_counter1compare0 clk_div=1 sync=5_1: 45..140 kbps
 *
 * @note It is advised for better synchronization to disable all interrupts
 * (except the UART starter) and the sleep instruction.
 *
 * The make rule `swuart-perfs` defined in
 * `hwa/atmel/avr/examples/make/Makefile.cc` displays the number of CPU cycles
 * spent in different sections of the `_swuarta` code and in critical sections
 * according to the configuration.
 */


/**
 * @page atmelavr_swuarta
 * @section atmelavr_swuarta_hardconf Compile-time configuration
 *
 * For efficiency reasons, a large part of the configuration of class `_swuarta`
 * UARTs must be defined at compile time. The following symbols are used:
 *
 * Symbol | Example | Comment
 * :------|:--------|:-------
 * `hw_swuart0_pin_txd` | `hw_pin_pa0`         | Pin used for TXD (optionnal)
 * `hw_swuart0_pin_rxd` | `hw_pin_5`           | Pin used for RXD (optionnal)
 * `hw_swuart0_starter` | `hw_rel(hw_pin_5,pcic)` | Interrupt provider for the start condition
 * `hw_swuart0_compare` | `hw_oc00`<br>`hw_oc01`<br>...    | Counter compare unit used for bit timing
 * `hw_swuart0_clk_div` | `1`<br>`8`<br>...      | Counter prescaler setting (division of `hw_sysclk`)
 * `hw_swuart0_autosync`| `5_1`<br>`9_1`<br>`10_1` | Synchronization method (optionnal)
 * `hw_swuart0_check_tx`|                    | Define this for bus collision detection (optionnal)
 * `hw_swuart0_pin_dbg` | `hw_pin_6`           | Pin used for debugging (optionnal)
 *
 * @par Pins
 *
 * If both `hw_swuart0_pin_rxd` and `hw_swuart0_pin_txd` are defined and the
 * same, the UART reverts to RX mode after a transmission is
 * completed. Transmissions are delayed until a reception is completed once it
 * has started.<br>
 *
 * The debug pin is usefull only for debugging the implementation of the UART
 * and should be left undefined.
 *
 * @par Start detection
 *
 * By default, the pin-change controller associated to the RXD pin is used as
 * the interrupt provider for detecting the start bit. This implies that the
 * same pin-change controller should not be used by the application.
 *
 * @par Counting unit
 *
 * The counting unit is configured in up-loop mode, counting from 0 to the
 * maximum it can reach. The user application can use the count value and the
 * overflow interrupt, for example to make a RTC counter.
 *
 * @par Automatic baudrate detection
 *
 * If defined, the `hw_swuart0_autosync` gives the UART the capability to
 * automatically detect the baudrate.
 *
 * * The `5_1` method waits for a sequence of 5 low-level bits followed by
 *   1 low-level bit. The ASCII character 'A' will do that.
 *
 * * The `9_1` method waits for a sequence of 9 low-level bits followed by
 *   1 low-level bit. E.g.: 0x00 / 0xFF bytes.
 *
 * * The `10_1` method waits for a sequence of 10 low-level bits followed by 1
 *   low-level bit. This can be done by sending a break byte of 10 low-level
 *   bits or a '0' byte with even parity, followed by a 0xFF byte.
 *
 * @par Bus collision detection
 *
 * If the symbol `hw_swuart0_check_tx` is defined, each time a new bit has to be
 * transfered the status of the bus is first compared to the last bit sent. If
 * there is a mismatch (collision), the UART releases the TXD pin and sets the
 * `stop` status flag to 0. The UART continues virtually to send until the end
 * of the frame when it sets the `txc` bit as usual. That way, the application
 * remains synchronized with the bus and can decide whether to retry the
 * transmission or to listen to what is happening on the bus.
 */


#if defined hw_swuart0_pin_rxd || defined hw_swuart0_pin_txd
#  if !defined hw_swuart0_compare
#    error hw_swuart0_compare is not defined
#  endif
#  if defined hw_swuart0_pin_txd && hw_id(hw_swuart0_pin_txd)==0
#    error invalid definition of hw_swuart0_pin_txd
#  endif
#  if defined hw_swuart0_pin_rxd && hw_id(hw_swuart0_pin_rxd)==0
#    error invalid definition of hw_swuart0_pin_rxd
#  endif
#  if defined hw_swuart0_pin_rxd && !defined hw_swuart0_starter
#    warning hw_swuart0_starter is not defined, using default 'pcic'
#    define hw_swuart0_starter	hw_rel(hw_swuart0_pin_rxd,pcic)
#  endif
#  if !defined hw_swuart0_compare
#    error hw_swuart0_compare is not defined
#  endif
#  if !defined hw_swuart0_clk_div
#    error hw_swuart0_clk_div is not defined
#  endif

/*  Configure the relatives of hw_swuart0
 */
HW_INLINE void _hw_swuart0_config_relatives ( hwa_t *hwa __attribute__((unused)) )
{
  /*  Configure the counter if its clock prescaling is defined
   */
#  if defined hw_swuart0_clk_div
  hwa_config( hw_rel(hw_swuart0_compare,counter),
  	      clock,     prescaler_output(hw_swuart0_clk_div),
  	      countmode, loop_up,
  	      top,       max );
#  endif

  /*  RXD pin
   */
#  if defined hw_swuart0_pin_rxd
  hwa_config( hw_swuart0_pin_rxd, direction, input );
  hwa_clear_irqf( hw_rel(hw_swuart0_pin_rxd,pcic) );
  hwa_turn_irq( hw_rel(hw_swuart0_pin_rxd,pcic), on );
  hwa_turn( hw_rel(hw_swuart0_pin_rxd,pcic), hw_swuart0_pin_rxd, on );
#  endif

  /*  TXD pin
   *
   *	Configure TXD pin as output high unless the pin is also used as RXD.
   */
#  if defined hw_swuart0_pin_txd && hw_id(hw_swuart0_pin_txd) != hw_id(hw_swuart0_pin_rxd)
  hwa_config( hw_swuart0_pin_txd, direction, output );
  hwa_write( hw_swuart0_pin_txd, 1 );
#  endif

  /*	DBG pin
   */
#  if defined hw_swuart0_pin_dbg
  hwa_config( hw_swuart0_pin_dbg, direction, output );
#  endif
}
#endif

#if defined hw_swuart1_pin_rxd || defined hw_swuart1_pin_txd
#  if !defined hw_swuart1_compare
#    error hw_swuart1_compare is not defined
#  endif
#  if defined hw_swuart1_pin_txd && hw_id(hw_swuart1_pin_txd)==0
#    error invalid definition of hw_swuart1_pin_txd
#  endif
#  if defined hw_swuart1_pin_rxd && hw_id(hw_swuart1_pin_rxd)==0
#    error invalid definition of hw_swuart1_pin_rxd
#  endif
#  if defined hw_swuart1_pin_rxd && !defined hw_swuart1_starter
#    warning hw_swuart1_starter is not defined, using default 'pcic'
#    define hw_swuart1_starter	hw_rel(hw_swuart1_pin_rxd,pcic)
#  endif
#  if !defined hw_swuart1_compare
#    error hw_swuart1_compare is not defined
#  endif
#  if !defined hw_swuart1_clk_div
#    error hw_swuart1_clk_div is not defined
#  endif

/*  Configure the relatives of hw_swuart1
 */
HW_INLINE void _hw_swuart1_config_relatives ( hwa_t *hwa __attribute__((unused)) )
{
  /*  Configure the counter if its clock prescaling is defined
   */
#  if defined hw_swuart1_clk_div
  hwa_config( hw_rel(hw_swuart1_compare,counter),
  	      clock,     prescaler_output(hw_swuart1_clk_div),
  	      countmode, loop_up,
  	      top,       max );
#  endif

  /*  RXD pin
   */
#  if defined hw_swuart1_pin_rxd
  hwa_config( hw_swuart1_pin_rxd, direction, input );
  hwa_clear_irqf( hw_rel(hw_swuart1_pin_rxd,pcic) );
  hwa_turn_irq( hw_rel(hw_swuart1_pin_rxd,pcic), on );
  hwa_turn( hw_rel(hw_swuart1_pin_rxd,pcic), hw_swuart1_pin_rxd, on );
#  endif

  /*  TXD pin
   *
   *	Configure TXD pin as output high unless the pin is also used as RXD.
   */
#  if defined hw_swuart1_pin_txd && hw_id(hw_swuart1_pin_txd) != hw_id(hw_swuart1_pin_rxd)
  hwa_config( hw_swuart1_pin_txd, direction, output );
  hwa_write( hw_swuart1_pin_txd, 1 );
#  endif

  /*	DBG pin
   */
#  if defined hw_swuart1_pin_dbg
  hwa_config( hw_swuart1_pin_dbg, direction, output );
#  endif
}
#endif

/**
 * @page atmelavr_swuarta
 * @section atmelavr_swuarta_config Configuration
 *
 * The instructions `hwa_config(UART,...)` and `hw_config(UART,...)` differ
 * slightly in what they do:
 *
 * * The instruction `hwa_config(UART,...)` configures the UART and its
 *   relatives: the counting unit, the start bit IRQ, the RXD and TXD pins, and
 *   the debug pin if declared.
 *
 * * The instruction `hw_config(UART,...)` does not change the configuration of
 *   the counting unit or the pins. It can only be used to change the baudrate
 *   or to enable/disable the receiver by enabling/disabling start bit
 *   interrupts.
 *
 * Optionnal arguments are used for consistency with the class `_uarta`.
 *
 * @code
 * hwa_config( UART,
 *
 *             //  Baudrate in bits per second
 *             //
 *           [ bps,         BPS, ]
 *
 *             //  Baudrate in CPU clock pulses per bit
 *             //
 *           [ cpb,         N, ]
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
 *           [ transmitter, enabled ]
 *
 *           );
 * @endcode
 */
#define _hw_mthd_hw_config__swuarta		, _hw_cfswuarta
#define _hw_mthd_hwa_config__swuarta		, _hwa_cfswuarta

/*  Configuration of the relatives is easier inside a function to handle
 *  undeclared pins.
 */

#define _hwa_cfswuarta(o,i,a,...)					\
  do {									\
    _##o##_config_relatives( hwa );					\
    HW_G2(_hwx_cfswuarta_kbps, HW_IS(bps,__VA_ARGS__))(_hwa,o,__VA_ARGS__,); \
  } while(0)

#define _hw_cfswuarta(o,i,a,...)					\
  do {									\
    HW_G2(_hwx_cfswuarta_kbps, HW_IS(bps,__VA_ARGS__))(_hw,o,__VA_ARGS__,); \
  } while(0)

/*  Process arg `bps`
 */
#define _hwx_cfswuarta_kbps_1(x,o,k,v,...)				\
  _##o##_##set_dt((hw_syshz + (v)/2) / (v)) ;				\
  *(volatile uint8_t*)_hw_ra(o,sr) |= 0x08 ; /* Set SYNC */		\
  HW_G2(_hwx_cfswuarta_kdatabits, HW_IS(databits,__VA_ARGS__))(x,o,__VA_ARGS__)

#define _hwx_cfswuarta_kbps_0(x,o,k,...)				\
  HW_G2(_hwx_cfswuarta_kcpb, HW_IS(cpb,k))(x,o,k,__VA_ARGS__)

#define _hw_is_bps_bps				, 1

/*  Process arg `cpb`
 */
#define _hwx_cfswuarta_kcpb_1(x,o,k,v,...)				\
  _##o##_##set_dt(v) ;							\
  *(volatile uint8_t*)_hw_ra(o,sr) |= 0x08 ; /* Set SYNC */		\
  HW_G2(_hwx_cfswuarta_kdatabits, HW_IS(databits,__VA_ARGS__))(x,o,__VA_ARGS__)

#define _hwx_cfswuarta_kcpb_0(x,o,k,...)					\
  HW_G2(_hwx_cfswuarta_kdatabits, HW_IS(databits,k))(x,o,k,__VA_ARGS__)

#define _hw_is_cpb_cpb				, 1

/*  Process arg `databits`
 */
#define _hwx_cfswuarta_kdatabits_1(x,o,k,v,...)				\
  HW_G2(_hwx_cfswuarta_vdatabits, HW_IS(,_hw_swuarta_csz_##v))(x,o,v,__VA_ARGS__)

#define _hwx_cfswuarta_vdatabits_0(x,o,v,...)		\
  HW_ERR("`databits` must be `8`, not `" #v "`.")

#define _hwx_cfswuarta_vdatabits_1(x,o,v,...)	\
  _hwx_cfswuarta_kdatabits_0(x,o,__VA_ARGS__)

#define _hwx_cfswuarta_kdatabits_0(x,o,k,...)				\
  HW_G2(_hwx_cfswuarta_kparity, HW_IS(parity,k))(x,o,k,__VA_ARGS__)

#define _hw_is_databits_databits		, 1
#define _hw_swuarta_csz_8			, 0

/*  Process arg `parity`
 */
#define _hwx_cfswuarta_kparity_1(x,o,k,v,...)				\
  HW_G2(_hwx_cfswuarta_vparity, HW_IS(,_hw_swuarta_pm_##v))(x,o,v,__VA_ARGS__)

#define _hwx_cfswuarta_vparity_0(x,o,v,...)		\
  HW_ERR("`parity` must be `none`, not `" #v "`.")

#define _hwx_cfswuarta_vparity_1(x,o,v,...)	\
  _hwx_cfswuarta_kparity_0(x,o,__VA_ARGS__)

#define _hwx_cfswuarta_kparity_0(x,o,k,...)				\
  HW_G2(_hwx_cfswuarta_kstopbits, HW_IS(stopbits,k))(x,o,k,__VA_ARGS__)

#define _hw_is_parity_parity			, 1
#define _hw_swuarta_pm_none			, 0

/*  Process arg `stopbits`
 */
#define _hwx_cfswuarta_kstopbits_1(x,o,k,v,...)				\
  HW_G2(_hwx_cfswuarta_vstopbits, HW_IS(,_hw_swuarta_sbs_##v))(x,o,v,__VA_ARGS__)

#define _hwx_cfswuarta_vstopbits_0(x,o,v,...)		\
  HW_ERR("`stopbits` must be `1`, not `" #v "`.")

#define _hwx_cfswuarta_vstopbits_1(x,o,v,...)	\
  _hwx_cfswuarta_kstopbits_0(x,o,__VA_ARGS__)

#define _hwx_cfswuarta_kstopbits_0(x,o,k,...)				\
  HW_G2(_hwx_cfswuarta_kreceiver, HW_IS(receiver,k))(x,o,k,__VA_ARGS__)

#define _hw_is_stopbits_stopbits		, 1
#define _hw_swuarta_sbs_1			, 0

/*  Process arg `receiver`
 */
#define _hwx_cfswuarta_kreceiver_1(x,o,k,v,...)				\
  HW_G2(_hwx_cfswuarta_vreceiver, HW_IS(,_hw_state_##v))(x,o,v,__VA_ARGS__)

#define _hwx_cfswuarta_vreceiver_0(x,o,v,...)				\
  HW_ERR("`receiver` can be `enabled` or `disabled`, but not `" #v "`.")

#define _hwx_cfswuarta_vreceiver_1(x,o,v,...)				\
  x##_turn_irq(o##_pin_rx),change,_hw_state_##v));			\
  _hwx_cfswuarta_kreceiver_0(x,o,__VA_ARGS__)

#define _hwx_cfswuarta_kreceiver_0(x,o,k,...)				\
  HW_G2(_hwx_cfswuarta_ktransmitter, HW_IS(transmitter,k))(x,o,k,__VA_ARGS__)

#define _hw_is_receiver_receiver		, 1

/*  Process arg `transmitter`
 */
#define _hwx_cfswuarta_ktransmitter_1(x,o,k,v,...)			\
    HW_G2(_hwx_cfswuarta_vtransmitter, HW_IS(,_hw_state_##v))(x,o,v,__VA_ARGS__)

#define _hwx_cfswuarta_vtransmitter_0(x,o,v,...)				\
  HW_ERR("`transmitter` must be `enabled`, not `" #v "`.")

#define _hwx_cfswuarta_vtransmitter_1(x,o,v,...)	\
  _hwx_cfswuarta_end(o,__VA_ARGS__)

#define _hwx_cfswuarta_ktransmitter_0(x,o,...)	\
  _hwx_cfswuarta_end(o,__VA_ARGS__)

#define _hw_is_transmitter_transmitter		, 1

#define _hwx_cfswuarta_end(o,...)		\
  HW_TX(,__VA_ARGS__)


/**
 * @page atmelavr_swuarta
 * @section atmelavr_swuarta_read Receiving
 *
 * The `hw_read()` instruction waits for the reception of a byte, clears the
 * `rxc` flag, and returns the byte.
 *
 * @code
 * uint8_t byte = hw_read( UART ); // Clears the 'rxc' status flag
 * @endcode
 */
#define _hw_mthd_hw_read__swuarta	, _hw_swuarta_read
#define _hw_swuarta_read(o,i,a,...)	HW_TX(_##o##_getbyte(),__VA_ARGS__)

#if defined hw_swuart0_pin_rxd
extern uint8_t				_hw_swuart0_getbyte ( ) ;
#else
#  define _hw_swuart0_getbyte()		HW_ERR("hw_swuart0 has no RXD PIN.")
#endif

#if defined hw_swuart1_pin_rxd
extern uint8_t				_hw_swuart1_getbyte ( ) ;
#else
#  define _hw_swuart1_getbyte()		HW_ERR("hw_swuart1 has no RXD PIN.")
#endif


/**
 * @page atmelavr_swuarta
 * @section atmelavr_swuarta_write Transmitting
 *
 * The `hw_write()` instruction waits for the completion of the transmission
 * (and the reception in 1-wire mode) and places the byte to send into the shift
 * register. This instruction returns before the byte is actually
 * transmitted. You need to check the `txc` flag to know when the transmission
 * is complete.
 *
 * @code
 * hw_write( UART, '#' ); // Clears the 'txc' status flag
 * @endcode
 */
#define _hw_mthd_hw_write__swuarta	, _hw_swuarta_write
#define _hw_swuarta_write(o,i,a,v,...)	HW_TX(_##o##_putbyte(v),__VA_ARGS__)

#if defined hw_swuart0_pin_txd
extern void				_hw_swuart0_putbyte ( uint8_t byte ) ;
#else
#  define _hw_swuart0_putbyte(x)	HW_ERR("hw_swuart0 has no TXD PIN.")
#endif

#if defined hw_swuart1_pin_txd
extern void				_hw_swuart1_putbyte ( uint8_t byte ) ;
#else
#  define _hw_swuart1_putbyte(x)	HW_ERR("hw_swuart1 has no TXD PIN.")
#endif


/**
 * @page atmelavr_swuarta
 * @section atmelavr_swuarta_stat Status
 *
 * The UART status is accessible through the `hw_stat()` instruction. It
 * contains the following flags:
 *
 * * `stop`: the state of the received stop bit, 0 if the byte failed to
 *           transmit (collision)
 * * `rxc`: 1 when a reception is completed (stop bit sampled)
 * * `txc`: 1 when the transmission is completed (stop bit sent)
 * * `sync`: 1 when the UART is synchronized
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
  unsigned int	rxc  : 1 ;
  unsigned int	txc  : 1 ;
  unsigned int	stop : 1 ;
  unsigned int	sync : 1 ;
  unsigned int	rxtx : 1 ;
  unsigned int	wbtx : 1 ;
  unsigned int	__6  : 1 ;
  unsigned int  __7  : 1 ;
} _hw_swuarta_stat_t ;


#define _hw_mthd_hw_stat_t__swuarta	, _hw_sttswuarta
#define _hw_sttswuarta(o,i,a,...)	HW_TX( _hw_swuarta_stat_t, __VA_ARGS__)

#define _hw_mthd_hw_stat__swuarta	, _hw_stswuarta
#define _hw_stswuarta(o,i,a,...)					\
  HW_TX( (*(volatile _hw_swuarta_stat_t*)_hw_ra(o,sr)), __VA_ARGS__)


/**
 * @page atmelavr_swuarta
 *
 * The `hw_clear()` instruction clears the `rxc` and `txc` status flags.
 *
 * @code
 * hw_clear( UART );
 * @endcode
 */
#define _hw_mthd_hw_clear__swuarta		, _hw_clear__swuarta
#define _hw_clear__swuarta(o,i,a,...)		HW_TX(_hw_clear_swuarta(o),__VA_ARGS__)
#define _hw_clear_swuarta( o )						\
  do {									\
    *(volatile uint8_t*)_hw_ra(o,sr) &= 0xFE ; /* Clear RXC */	\
    *(volatile uint8_t*)_hw_ra(o,sr) &= 0xFD ; /* Clear TXC */	\
  }while(0)

/**
 * @page atmelavr_swuarta
 * @section atmelavr_swuarta_reset Resetting
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

#if defined hw_swuart0_compare
extern void					_hw_swuart0_reset ( ) ;
extern void					_hw_swuart0_set_dt ( uint16_t ) ;
extern hw_uint_t(hw_bn(hw_swuart0_compare))	__hw_swuart0_dtn ;
extern hw_uint_t(hw_bn(hw_swuart0_compare))	__hw_swuart0_dt0 ;
#endif

#if defined hw_swuart1_compare
extern void					_hw_swuart1_reset ( ) ;
extern void					_hw_swuart1_set_dt ( uint16_t ) ;
extern hw_uint_t(hw_bn(hw_swuart1_compare))	__hw_swuart1_dtn ;
extern hw_uint_t(hw_bn(hw_swuart1_compare))	__hw_swuart1_dt0 ;
#endif


/**
 * @page atmelavr_swuarta
 * @section atmelavr_swuarta_internals Internals
 *
 * Class `_swuarta` objects hold the following registers:
 *
 *  * `dt0`: counter clocks between the start condition and the sampling of data bit 0
 *  * `dtn`: counter clocks between samplings
 *  * `sr`: status byte
 *
 * These registers are accessible through the @ref public_reg_instructions
 * "register access intructions".
 */


/**
 * @page atmelavr_swuarta
 * <br>
 */
