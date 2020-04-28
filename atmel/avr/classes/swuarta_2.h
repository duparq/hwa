
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
 * __Note__ The make rule `swuart-perfs` defined in
 * `hwa/atmel/avr/examples/make/Makefile.cc` displays the number of CPU cycles
 * spent in different sections of the `_swuarta` code and in critical sections
 * according to the configuration. These figures determine the performances that
 * can be achieved.
 */


/**
 * @page atmelavr_swuarta
 * @section atmelavr_swuarta_hardconf Compile-time configuration
 *
 * For efficiency reasons, a large part of the configuration of `_swuarta`
 * UARTs must be defined at compile time:
 *
 * Symbol | Example | Comment
 * :------|:--------|:-------
 * `hw_swuart0_pin_txd` | `pa0`	 | Pin used for TXD (optionnal)
 * `hw_swuart0_pin_rxd` | `HW_PIN(5)`		 | Pin used for RXD (optionnal)
 * `hw_swuart0_starter` | `(HW_PIN(5),pcic)` | Interrupt provider for the start condition
 * `hw_swuart0_compare` | `counter0compare0`<br>`counter0compare1`<br>...    | Counter compare unit used for bit timing
 * `hw_swuart0_clk_div` | `1`<br>`8`<br>...	 | Counter prescaler setting (division of `ioclk`)
 * `hw_swuart0_autosync`| `5_1`<br>`9_1`<br>`10_1` | Synchronization method (optionnal)
 * `hw_swuart0_check_tx`|			  | Bus collision detection (optionnal)
 * `hw_swuart0_pin_dbg` | `pa3`		 | Pin used for debugging (optionnal)
 *
 * @par Pins
 *
 * If `hw_swuart0_pin_rxd` and `hw_swuart0_pin_txd` are both defined as the
 * same, the UART automatically reverts to RX mode after a transmission is
 * completed and transmissions are delayed (i.e. `hw(write,swuart0,data)`
 * blocks) until a reception is completed once it has started.<br>
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
 * If defined, `hw_swuart0_autosync` gives the UART the capability to
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
 * __Note__ It is advised to disable the sleep instruction and all interrupts
 * except the UART starter for a better accuracy of the baudrate detection. Once
 * the UART is synchronized, interrupts can be re-enabled.
 *
 * __Note__ Do not forget that the software UART is interrupt-driven and that
 * too long delays before the UART IRQs are serviced will lead to loss of data.
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


#if defined hw_swuart0_compare

extern void					_hw_swuart0_reset ( ) ;
extern void					_hw_swuart0_set_dt ( uint16_t ) ;
extern hw_uint_t(HW_BITS(hw_swuart0_compare))	__hw_swuart0_dtn ;
extern hw_uint_t(HW_BITS(hw_swuart0_compare))	__hw_swuart0_dt0 ;

/*  Configure the relatives of hw_swuart0
 */
HW_INLINE void _hw_swuart0_config_relatives ( hwa_t *hwa __attribute__((unused)) )
{
  /*  Configure the counter if its clock prescaling is defined
   */
#  if defined hw_swuart0_clk_div
  _hwa( configure, (hw_swuart0_compare,counter),
	clock,	   ioclk / hw_swuart0_clk_div,
	direction, up_loop,
	top,	   max );
#  endif

  /*  RXD pin
   */
#  if defined hw_swuart0_pin_rxd
  _hwa( configure, hw_swuart0_pin_rxd, mode, digital_input );
  hwa( clear, irqflag((hw_swuart0_pin_rxd,pcic)) );
  hwa( turn, irq((hw_swuart0_pin_rxd,pcic)), on );
  _hwa( turn, (hw_swuart0_pin_rxd,pcic), hw_swuart0_pin_rxd, on );
#  endif

  /*  TXD pin
   *
   *	Configure TXD pin as output high unless the pin is also used as RXD.
   */
#  if defined hw_swuart0_pin_txd && HW_ADDRESS(hw_swuart0_pin_txd) != HW_ADDRESS(hw_swuart0_pin_rxd)
  _hwa( configure, hw_swuart0_pin_txd, mode, digital_output );
  _hwa( write, hw_swuart0_pin_txd, 1 );
#  endif

  /*	DBG pin
   */
#  if defined hw_swuart0_pin_dbg
  _hwa( configure, hw_swuart0_pin_dbg, mode, digital_output );
#  endif
}
#endif


#if defined hw_swuart1_compare

extern void					_hw_swuart1_reset ( ) ;
extern void					_hw_swuart1_set_dt ( uint16_t ) ;
extern hw_uint_t(HW_BITS(hw_swuart1_compare))	__hw_swuart1_dtn ;
extern hw_uint_t(HW_BITS(hw_swuart1_compare))	__hw_swuart1_dt0 ;

/*  Configure the relatives of hw_swuart1
 */
HW_INLINE void _hw_swuart1_config_relatives ( hwa_t *hwa __attribute__((unused)) )
{
  /*  Configure the counter if its clock prescaling is defined
   */
#  if defined hw_swuart1_clk_div
  _hwa( configure, (hw_swuart1_compare,counter),
	clock,	   ioclk / hw_swuart1_clk_div,
	direction, up_loop,
	top,	   max );
#  endif

  /*  RXD pin
   */
#  if defined hw_swuart1_pin_rxd
  _hwa( configure, hw_swuart1_pin_rxd, mode, digital_input );
  hwa( clear, irqflag((hw_swuart1_pin_rxd,pcic)) );
  hwa( turn, irq((hw_swuart1_pin_rxd,pcic)), on );
  _hwa( turn, (hw_swuart1_pin_rxd,pcic), hw_swuart1_pin_rxd, on );
#  endif

  /*  TXD pin
   *
   *	Configure TXD pin as output high unless the pin is also used as RXD.
   */
#  if defined hw_swuart1_pin_txd && HW_ADDRESS(hw_swuart1_pin_txd) != HW_ADDRESS(hw_swuart1_pin_rxd)
  _hwa( configure, hw_swuart1_pin_txd, mode, digital_output );
  _hwa( write, hw_swuart1_pin_txd, 1 );
#  endif

  /*	DBG pin
   */
#  if defined hw_swuart1_pin_dbg
  _hwa( configure, hw_swuart1_pin_dbg, mode, digital_output );
#  endif
}
#endif

#if defined hw_swuart0_compare || defined hw_swuart1_compare

/**
 * @page atmelavr_swuarta
 * @section atmelavr_swuarta_config Configuration
 *
 * The instructions `hwa(configure,UART,...)` and `hw(configure,UART,...)` differ
 * slightly in what they do:
 *
 * * The instruction `hwa(configure,UART,...)` configures the UART and its
 *   relatives: the counting unit, the start bit IRQ, the RXD and TXD pins, and
 *   the debug pin if declared.
 *
 * * The instruction `hw(configure,UART,...)` does not change the configuration of
 *   the counting unit or the pins. It can only be used to change the baudrate
 *   or to enable/disable the receiver by enabling/disabling start bit
 *   interrupts.
 *
 * Optionnal arguments are used for consistency with the class `_uarta`.
 *
 * @code
 * hwa( configure, UART,
 *
 *	       //  Baudrate in bits per second
 *	       //
 *	     [ bps,	    BPS, ]
 *
 *	       //  Baudrate in CPU clock pulses per bit
 *	       //
 *	     [ cpb,	    N, ]
 *
 *	       //  Number of data bits in frame. Must be `8`.
 *	       //
 *	     [ databits,    8, ]
 *
 *	       //  Parity. Must be `none`.
 *	       //
 *	     [ parity,	    none, ]
 *
 *	       //  Number of stop bits in frame. Must be `1`.
 *	       //
 *	     [ stopbits,    1, ]
 *
 *	       //  Whether the UART can receive. Default is `enabled`.
 *	       //
 *	     [ receiver,    enabled | disabled, ]
 *
 *	       //  Whether the UART can transmit. Must be `enabled`.
 *	       //
 *	     [ transmitter, enabled ]
 *
 *	     );
 * @endcode
 */
#define hw_configure__swuarta		, _hw_cfswuarta
#define hwa_configure__swuarta		, _hwa_cfswuarta

/*  Configuration of the relatives is easier inside a function to handle
 *  undeclared pins.
 */

#define _hwa_cfswuarta(o,a,k,...)					\
  do {									\
    _hw_##o##_config_relatives( hwa );					\
    HW_Y(_hwx_cfswuarta_kbps_,_hw_is_bps_##k)(_hwa,o,k,__VA_ARGS__,);	\
  } while(0)

#define _hw_cfswuarta(o,a,k,...)					\
  do {									\
    HW_Y(_hwx_cfswuarta_kbps_,_hw_is_bps_##k)(_hw,o,k,__VA_ARGS__,);	\
  } while(0)

/*  Process arg `bps`
 */
#define _hwx_cfswuarta_kbps_1(x,o,k,v,kk,...)				\
  _hw_##o##_##set_dt((HW_SYSHZ + (v)/2) / (v)) ;			\
  *(volatile uint8_t*)HW_ADDRESS((o,sr)) |= 0x08 ; /* Set SYNC */	\
  HW_Y(_hwx_cfswuarta_kdatabits_,_hw_is_databits_##kk)(x,o,kk,__VA_ARGS__)

#define _hwx_cfswuarta_kbps_0(x,o,k,...)			\
  HW_Y(_hwx_cfswuarta_kcpb_,_hw_is_cpb_##k)(x,o,k,__VA_ARGS__)

/*  Process arg `cpb`
 */
#define _hwx_cfswuarta_kcpb_1(x,o,k,v,kk,...)				\
  _hw_##o##_##set_dt(v) ;						\
  *(volatile uint8_t*)HW_ADDRESS((o,sr)) |= 0x08 ; /* Set SYNC */		\
  HW_Y(_hwx_cfswuarta_kdatabits_,_hw_is_databits_##kk)(x,o,kk,__VA_ARGS__)

#define _hwx_cfswuarta_kcpb_0(x,o,k,...)				\
  HW_Y(_hwx_cfswuarta_kdatabits_,_hw_is_databits_##k)(x,o,k,__VA_ARGS__)

/*  Process arg `databits`
 */
#define _hwx_cfswuarta_kdatabits_1(x,o,k,v,...)				\
  HW_Y(_hwx_cfswuarta_vdatabits_,_hw_swuarta_csz_##v)(x,o,v,__VA_ARGS__)

#define _hwx_cfswuarta_vdatabits_0(x,o,v,...)	\
  HW_E_AVL(`databits`, v, `8`)

#define _hwx_cfswuarta_vdatabits_1(x,o,v,...)	\
  _hwx_cfswuarta_kdatabits_0(x,o,__VA_ARGS__)

#define _hwx_cfswuarta_kdatabits_0(x,o,k,...)				\
  HW_Y(_hwx_cfswuarta_kparity_,_hw_is_parity_##k)(x,o,k,__VA_ARGS__)

#define _hw_swuarta_csz_8		, 0

/*  Process arg `parity`
 */
#define _hwx_cfswuarta_kparity_1(x,o,k,v,...)				\
  HW_Y(_hwx_cfswuarta_vparity_,_hw_swuarta_pm_##v)(x,o,v,__VA_ARGS__)

#define _hwx_cfswuarta_vparity_0(x,o,v,...)	\
  HW_E_AVL(`parity`, v, `none`)

#define _hwx_cfswuarta_vparity_1(x,o,v,...)	\
  _hwx_cfswuarta_kparity_0(x,o,__VA_ARGS__)

#define _hwx_cfswuarta_kparity_0(x,o,k,...)				\
  HW_Y(_hwx_cfswuarta_kstopbits_,_hw_is_stopbits_##k)(x,o,k,__VA_ARGS__)

#define _hw_swuarta_pm_none		, 0

/*  Process arg `stopbits`
 */
#define _hwx_cfswuarta_kstopbits_1(x,o,k,v,...)				\
  HW_Y(_hwx_cfswuarta_vstopbits_,_hw_swuarta_sbs_##v)(x,o,v,__VA_ARGS__)

#define _hwx_cfswuarta_vstopbits_0(x,o,v,...)	\
  HW_E_AVL(`stopbits`, v, `1`)

#define _hwx_cfswuarta_vstopbits_1(x,o,v,...)	\
  _hwx_cfswuarta_kstopbits_0(x,o,__VA_ARGS__)

#define _hwx_cfswuarta_kstopbits_0(x,o,k,...)				\
  HW_Y(_hwx_cfswuarta_kreceiver_,_hw_is_receiver_##k)(x,o,k,__VA_ARGS__)

#define _hw_swuarta_sbs_1		, 0

/*  Process arg `receiver`
 */
#define _hwx_cfswuarta_kreceiver_1(x,o,k,v,...)				\
  HW_Y(_hwx_cfswuarta_vreceiver_,_hw_state_##v)(x,o,v,__VA_ARGS__)

#define _hwx_cfswuarta_vreceiver_0(x,o,v,...)	\
  HW_E_AVL(receiver, v, enabled | disabled)

#define _hwx_cfswuarta_vreceiver_1(x,o,v,...)				\
  x##_turn_irq(o##_pin_rx,change,_hw_state_##v);			\
  _hwx_cfswuarta_kreceiver_0(x,o,__VA_ARGS__)

#define _hwx_cfswuarta_kreceiver_0(x,o,k,...)				\
  HW_Y(_hwx_cfswuarta_ktransmitter_,_hw_is_transmitter_##k)(x,o,k,__VA_ARGS__)

/*  Process arg `transmitter`
 */
#define _hwx_cfswuarta_ktransmitter_1(x,o,k,v,...)			\
  HW_Y(_hwx_cfswuarta_vtransmitter_,_hw_state_##v)(x,o,v,__VA_ARGS__)

#define _hwx_cfswuarta_vtransmitter_0(x,o,v,...)	\
  HW_E_AVL(`transmitter`, v, `enabled`)

#define _hwx_cfswuarta_vtransmitter_1(x,o,v,...)	\
  _hwx_cfswuarta_end(o,__VA_ARGS__)

#define _hwx_cfswuarta_ktransmitter_0(x,o,...)	\
  _hwx_cfswuarta_end(o,__VA_ARGS__)

#define _hwx_cfswuarta_end(o,...)		\
   HW_EOL(__VA_ARGS__)


/**
 * @page atmelavr_swuarta
 * @section atmelavr_swuarta_read Receiving
 *
 * The `read` instruction waits for the reception of a byte, clears the
 * `rxc` flag, and returns the byte.
 *
 * @code
 * uint8_t byte = hw( read, UART ); // Clears the 'rxc' status flag
 * @endcode
 */
#define hw_read__swuarta		, _hw_swuarta_read
#define _hw_swuarta_read(o,a,...)	_hw_##o##_getbyte() HW_EOL(__VA_ARGS__)

#if defined hw_swuart0_pin_rxd
extern uint8_t			_hw_swuart0_getbyte ( ) ;
#else
#  define _hw_swuart0_getbyte()		HW_E(`swuart0` has no RXD pin)
#endif

#if defined hw_swuart1_pin_rxd
extern uint8_t				_hw_swuart1_getbyte ( ) ;
#else
#  define _hw_swuart1_getbyte()		HW_E(`swuart1` has no RXD pin)
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
#define hw_write__swuarta		, _hw_swuarta_write
#define _hw_swuarta_write(o,a,v,...)	_hw_##o##_putbyte(v) HW_EOL(__VA_ARGS__)

#if defined hw_swuart0_pin_txd
extern void				_hw_swuart0_putbyte ( uint8_t byte ) ;
#else
#  define _hw_swuart0_putbyte(x)	HW_E(`swuart0` has no TXD pin)
#endif

#if defined hw_swuart1_pin_txd
extern void				_hw_swuart1_putbyte ( uint8_t byte ) ;
#else
#  define _hw_swuart1_putbyte(x)	HW_E(`swuart1` has no TXD pin)
#endif


/**
 * @page atmelavr_swuarta
 * @section atmelavr_swuarta_stat Status
 *
 * The UART status is accessible through the `hw(stat,)` instruction. It
 * contains the following flags:
 *
 * * `stop`: the state of the received stop bit, 0 if the byte failed to
 *	     transmit (collision)
 * * `rxc`: 1 when a reception is completed (stop bit sampled)
 * * `txc`: 1 when the transmission is completed (stop bit sent)
 * * `sync`: 1 when the UART is synchronized
 *
 * @code
 * uint8_t byte ;
 * hw_stat_t( swuart0 ) st ;   // Structure of UART status
 * st = hw( stat, swuart0 );	// Read the status
 * if ( st.rxc )		  // Reception complete?
 *   byte = hw( read, swuart0 );
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
  unsigned int	__7  : 1 ;
} _hw_swuarta_stat_t ;


#define hw_stat_t__swuarta		, _hw_sttswuarta
#define _hw_sttswuarta(o,a,...)	_hw_swuarta_stat_t HW_EOL(__VA_ARGS__)

#define hw_stat__swuarta		, _hw_stswuarta
#define _hw_stswuarta(o,a,...)					\
  (*(volatile _hw_swuarta_stat_t*)HW_ADDRESS((o,sr))) HW_EOL(__VA_ARGS__)


/**
 * @page atmelavr_swuarta
 *
 * The ``clear`` instruction clears the `rxc` and `txc` status flags.
 *
 * @code
 *`hw( clear, UART )`;
 * @endcode
 */
#define hw_clear__swuarta		, _hw_clear__swuarta
#define _hw_clear__swuarta(o,a,...)	_hw_clear_swuarta(o) HW_EOL(__VA_ARGS__)
#define _hw_clear_swuarta( o )					\
  do {								\
    *(volatile uint8_t*)HW_ADDRESS((o,sr)) &= 0xFE ; /* Clear RXC */	\
    *(volatile uint8_t*)HW_ADDRESS((o,sr)) &= 0xFD ; /* Clear TXC */	\
  }while(0)

/**
 * @page atmelavr_swuarta
 * @section atmelavr_swuarta_reset Resetting
 *
 * Resetting the UART will abort any transmission or reception. If the UART has automatic
 * baudrate detection, the UART will first resynchronize.
 *
 * @code
 * hw( reset, UART );
 * @endcode
 */
#define hw_reset__swuarta		, _hw_swuarta_reset
#define _hw_swuarta_reset(o,a,...)	_hw_##o##_##reset() HW_EOL(__VA_ARGS__)


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
 * These registers are accessible through the @ref public_ins
 * "register access intructions".
 */


#endif /* defined hw_swuart0_compare || defined hw_swuart1_compare */

/**
 * @page atmelavr_swuarta
 * <br>
 */
