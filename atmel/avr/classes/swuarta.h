
/* This file is part of the HWA project.
 * Copyright (c) 2020 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Atmel AVR software-emulated UART
 */

/**
 * @ingroup swec
 * @defgroup atmelavr_swuarta Class _swuarta: software-emulated UART
 *
 * This class implements a software-emulated UART with the following features:
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
 * @note Currently, this is only supported by @ref atmelavr_devices.
 *
 * @par Performances
 *
 * Tested on @ref attinyx4 with internal oscillator (rc_8MHz):
 *
 *  * 1200..115200 bps with 16-bit counter, clk_div=1
 *  * 450.. 50000 bps with 16-bit counter, clk_div=8
 *  * 38400..115200 bps with 8-bit counter, clk_div=1
 *  * 10000 bps with 8-bit counter, clk_div=8
 *
 *  * 45..140 kbps with @ref attiny85, rc_8MHz, counter1, compare0,
 *    clk_div=1 sync=51
 *
 * @note The make rule `swuarta-perfs` defined in
 * `hwa/atmel/avr/examples/make/Makefile.cc` displays the number of CPU cycles
 * spent in different sections of the `_swuarta` code and in critical sections
 * according to the configuration. These figures determine the performances that
 * can be achieved.
 *
 * @par Pins
 *
 * If the same pin is used for `rxd` and `txd` signals, the UART automatically
 * reverts to RX mode after a transmission is completed and transmissions are
 * delayed one a reception is started, i.e. `hw(write,UART,data)` blocks until a
 * reception is completed once it has started.
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
 * If defined, `autosync` a method to automatically detect the baudrate:
 *
 * * `51`: waits for a sequence of 5 low-level bits followed by 1 low-level
 *   bit. The ASCII characters 'A' or 'p' will do that.
 *
 * * `91`: waits for a sequence of 9 low-level bits followed by 1 low-level
 *   bit. E.g.: 0x00 / 0xFF bytes.
 *
 * * `101`: waits for a sequence of 10 low-level bits followed by 1 low-level
 *   bit. This can be done by sending a break byte of 10 low-level bits or a '0'
 *   byte with even parity, followed by a 0xFF byte.
 *
 * @note It is advised to disable the sleep instruction and all interrupts
 * except the UART starter for a better accuracy of the baudrate detection. Once
 * the UART is synchronized, interrupts can be re-enabled.
 *
 * @note Do not forget that the software UART is interrupt-driven and that
 * too long delays before the UART IRQs are serviced will lead to loss of data.
 *
 * @note Currently, baudrate detection is started when the UART receives a
 * character and it is not synced. The processing is blocking. Non blocking
 * alternatives are provided but not yet useable.
 *
 * @par Bus collision detection
 *
 * If `check_tx` is defined, the status of the bus is compared with the last bit
 * sent before sending a new one. If there is a mismatch (collision), the UART
 * releases the TXD pin and sets the `stop` status flag to 0. The UART continues
 * virtually to send until the end of the frame when it sets the `txc` bit as
 * usual. That way, the application remains synchronized with the bus and can
 * decide whether to retry the transmission or to listen to what is happening on
 * the bus.
 *
 * @note Currently, `check_tx` can not be set by the constructor.
 *
 * @section atmelavr_swuartaimp Implementation
 *
 * Header file:
 *
 * @code
 * #include <hwa/ext/swuarta.h>
 * @endcode
 *
 * <br><br>HW_SWUARTA(...) declares an object. You must provide:
 *  * an I/O for the TXD signal;
 *  * an I/O for the RXD signal;
 *  * an IRQ for start bit detection;
 *  * a counter;
 *  * a compare unit of the counter;
 *  * a prescaler value for the counter's clock;
 *  * a synchronization method;
 *  * the address of a fast access register.
 *
 * @code
 * HW_SWUARTA(  txd,       ...,		// Pin TXD
 *            [ rxd,       ...,		// Pin RXD
 *              startirq,  ..., ]	// IRQ used for RX start bit
 *              counter,   ...,		// Counter unit used
 *              compare,   ...,		// Compare unit used
 *              clkdiv,    ...,		// Counter prescaler value
 *            [ autosync,  ..., ]	// Autosync method (51,91,101)
 *            [ fastreg,   ...  ] );	// Address of a fast access register for status
 * @endcode
 *
 * @code
 *
 * #include <hwa/ext/swuarta.h>
 *
 * #define UART		HW_SWUARTA( txd,      (portb,0),
 *                                  rxd,      (portb,1),
 *                                  startirq, ((portb,1),port,pcic,irq),
 *                                  counter,  counter0,
 *                                  compare,  compare0,
 *                                  clkdiv,   2,
 *                                  autosync, 51,
 *                                  fastreg,  (shared,gpior0) );
 * @endcode
 */
#define hw_class__swuarta

/**
 * @ingroup atmelavr_swuarta
 * @brief Constructor for @ref atmelavr_swuarta "SWUARTA"
 * @hideinitializer
 */
#define HW_SWUARTA(...)					_HW_SWUARTA10(__VA_ARGS__,,,,,)
#define _HW_SWUARTA10(k,...)				HW_BW(_HW_SWUARTA10,txd,k)(k,__VA_ARGS__)

#define _HW_SWUARTA100(k,...)				HW_BW(_HW_SWUARTA20,rxd,k)((),k,__VA_ARGS__)
#define _HW_SWUARTA101(k,...)				_HW_SWUARTA11(HW_AD(__VA_ARGS__))
#define _HW_SWUARTA11(...)				_HW_SWUARTA12(__VA_ARGS__)
#define _HW_SWUARTA12(v,...)				HW_BW(_HW_SWUARTA12,_ioa,HW_A0 v)(v,__VA_ARGS__)
#define _HW_SWUARTA120(v,...)				,HW_SWUARTA(...),HW_EM_OT(v, pin name)
#define _HW_SWUARTA121(t,k,...)				HW_BW(_HW_SWUARTA20,rxd,k)(t,k,__VA_ARGS__)

#define _HW_SWUARTA200(t,k,...)				HW_BW(_HW_SWUARTA40,counter,k)(t,(),,k,__VA_ARGS__)
#define _HW_SWUARTA201(t,k,...)				_HW_SWUARTA21(t,HW_AD(__VA_ARGS__))
#define _HW_SWUARTA21(...)				_HW_SWUARTA22(__VA_ARGS__)
#define _HW_SWUARTA22(t,v,...)				HW_BW(_HW_SWUARTA22,_ioa,HW_A0 v)(t,v,__VA_ARGS__)
#define _HW_SWUARTA220(t,v,...)				,HW_SWUARTA(...),HW_EM_OT(v, pin name)
#define _HW_SWUARTA221(t,r,k,...)			HW_BW(_HW_SWUARTA30,startirq,k)(t,r,k,__VA_ARGS__)

#define _HW_SWUARTA300(t,r,k,...)			,HW_SWUARTA(...),HW_EM_CAN(HW_SWUARTA(...),k,startirq)
#define _HW_SWUARTA301(t,r,k,...)			_HW_SWUARTA31(t,r,HW_AD(__VA_ARGS__))
#define _HW_SWUARTA31(...)				_HW_SWUARTA32(__VA_ARGS__)
#define _HW_SWUARTA32(t,r,v,...)			HW_BW(_HW_SWUARTA32,_irq,HW_A0 v)(t,r,v,__VA_ARGS__)
#define _HW_SWUARTA320(t,r,v,...)			,HW_SWUARTA(...),HW_EM_OT(v,irq)
#define _HW_SWUARTA321(t,r,i,k,...)			HW_BW(_HW_SWUARTA40,counter,k)(t,r,i,k,__VA_ARGS__)

#define _HW_SWUARTA400(t,r,i,k,...)			,HW_SWUARTA(...),HW_EM_KX(counter,k)
#define _HW_SWUARTA401(t,r,i,k1,ct,k,...)		HW_BW(_HW_SWUARTA5_,compare,k)(t,r,i,ct,k,__VA_ARGS__)
#define _HW_SWUARTA5_0(t,r,i,ct,k,...)			,HW_SWUARTA(...),HW_EM_KX(compare,k)
#define _HW_SWUARTA5_1(t,r,i,ct,k1,cp,k,...)		HW_BW(_HW_SWUARTA6_,clkdiv,k)(t,r,i,ct,HW_BITS(ct),cp,k,__VA_ARGS__)
#define _HW_SWUARTA6_0(t,r,i,ct,cp,k,...)		,HW_SWUARTA(...),HW_EM_KX(clkdiv,k)
#define _HW_SWUARTA6_1(t,r,i,ct,cw,cp,k1,ps,k,...)	HW_BW(_HW_SWUARTA7_,autosync,k)(t,r,i,ct,cw,cp,ps,k,__VA_ARGS__)
#define _HW_SWUARTA7_0(t,r,i,ct,cw,cp,ps,k,...)		HW_BW(_HW_SWUARTA8_,fastreg,k)(t,r,i,ct,cw,cp,ps,0,k,__VA_ARGS__)
#define _HW_SWUARTA7_1(t,r,i,ct,cw,cp,ps,k1,as,k,...)	HW_BW(_HW_SWUARTA8_,fastreg,k)(t,r,i,ct,cw,cp,ps,as,k,__VA_ARGS__)
#define _HW_SWUARTA8_0(t,r,i,ct,cw,cp,ps,as,k,...)	_HW_B(_HW_SWUARTA9_,k)(t,r,i,ct,cw,cp,ps,as,-1,k,__VA_ARGS__)
#define _HW_SWUARTA8_1(t,r,i,ct,cw,cp,ps,as,k1,fr,k,...)	_HW_B(_HW_SWUARTA9_,k)(t,r,i,ct,cw,cp,ps,as,HW_ADDRESS(fr),k,__VA_ARGS__)
#define _HW_SWUARTA9_0(t,r,i,ct,cw,cp,ps,as,fr,g,...)	,HW_SWUARTA(...),HW_EM_G(g)
#define _HW_SWUARTA9_1(t,r,i,ct,cw,cp,ps,as,fr,...)	_swuarta, HW_G3(swuarta,HW_A1 t,HW_A1 r), (t,r,i,ct,cw,cp,ps,as,fr)

#define _HW_SWUARTA_E	,HW_SWUARTA(...), HW_E(HW_EM_SY(HW_SWUARTA( txd,..., [rxd,..., startirq,...,] counter,..., compare,..., clkdiv,..., autosync,..., fastreg,... )))


#define _hw_is_startirq_startirq		, 1
#define _hw_is_autosync_autosync		, 1
#define _hw_is_clkdiv_clkdiv			, 1
#define _hw_is_fastreg_fastreg			, 1


/*  Return the address of the compare register as address of the swuarta
 */
#define HW_ADDRESS__swuarta			, _hw_adswuarta
#define _hw_adswuarta(oo,t,r,i,ct,cw,cp,...)	_hw_adswuarta1( HW_X((ct,cp,reg)) )
#define _hw_adswuarta1(...)			_hw_adswuarta2(__VA_ARGS__)
#define _hw_adswuarta2(m11,oo,o,r,rc,ra,...)	ra


#if !defined __ASSEMBLER__


/**
 * @addtogroup atmelavr_swuarta
 *
 * <br><br>HW_DECLARE( UART ) declares the functions that implement the device. You
 * can put it in your header files:
 *
 * @code
 * HW_DECLARE( UART );
 * @endcode
 *
 * Currently, class _swuarta does not support HW_IMPLEMENT(). You must include
 * the assembly file `hwa/ext/swuarta.sx` in one of your source files after having
 * defined a `UART` symbol, once per object:
 *
 * @code
 * 	;; -*- asm -*-
 *
 * #undef UART
 * #define UART	UART0
 * #include <hwa/ext/swuarta.sx>	// Implement UART0
 *
 * #undef UART
 * #define UART	UART1
 * #include <hwa/ext/swuarta.sx>	// Implement UART1
 * @endcode
 */
#define HW_DECLARE__swuarta		, _hw_dcswuarta

#define _hw_dcswuarta(o,t,r,i,ct,cw,cp,ps,as,fr,...)	\
  extern volatile uint8_t hw_##o##_stat ;		\
  extern volatile uint##cw##_t hw_##o##_dtn ;		\
  extern volatile uint##cw##_t hw_##o##_dt0 ;		\
  extern uint8_t hw_##o##_getbyte();			\
  extern void hw_##o##_putbyte(uint8_t);		\
  extern void hw_##o##_set_dt(uint##cw##_t);		\
  extern void hw_##o##_reset();				\
  extern void hw_##o##_sample(uint8_t);			\
  extern void hw_##o##_wait_idle_bits(uint8_t);		\
  extern void hw_##o##_brk(uint8_t)


/*  Give access to memory registers created by _swuarta
 */
#define hw__swuarta_dtn					, _hw_swuartadtn
#define _hw_swuartadtn(o,t,r,i,ct,cw,cp,ps,as,fr)	_mem##cw,(o,dtn),(&hw_##o##_dtn)

#define hw__swuarta_dt0					, _hw_swuartadt0
#define _hw_swuartadt0(o,t,r,i,ct,cw,cp,ps,as,fr)	_mem##cw,(o,dt0),(&hw_##o##_dt0)

#define hw__swuarta_stat				, _hw_swuartast
#define _hw_swuartast(o,t,r,i,ct,cw,cp,ps,as,fr)	_m11,(o,stat),(o,stat,_r8,(intptr_t)&hw_##o##_stat,0xFF,0x00,8,0)

#define hw__swuarta_sync				, _hw_swuartasyn
#define _hw_swuartasyn(o,t,r,i,ct,cw,cp,ps,as,fr)	_m11,(o,sync),(o,sync,_r8,(intptr_t)&hw_##o##_stat,0xFF,0x00,1,3)


/**
 * @addtogroup atmelavr_swuarta
 * @section atmelavr_swuarta_act Actions
 *
 * <br><br>Both hw( configure, UART, ... ) and hwa( configure, UART, ... )
 * configure the object but they differ slightly in what they do:
 *
 * * hwa(configure,UART,...) configures the UART, its pins TXD, RXD, and its
 *   counting unit;
 *
 * * hw(configure,UART,...) can only be used to change the baudrate or to
 *   enable/disable the receiver by enabling/disabling start bit interrupts.
 *
 * Optionnal arguments are used for consistency with the class @ref
 * atmelavr_uarta "_uarta".
 *
 * @code
 * hwa( configure,     UART,
 *
 *    [ bps,	       BPS, ]		//  Baudrate in bits per second
 *
 *    [ cpb,	       N, ]		//  Baudrate in CPU clock pulses per bit
 *
 *    [ databits,      8, ]		//  Number of data bits in frame. Must be `8`.
 *
 *    [ parity,	       none, ]		//  Parity. Must be `none`.
 *
 *    [ stopbits,      1, ]		//  Number of stop bits in frame. Must be `1`.
 *
 *    [ receiver,      enabled		//  Whether the UART can receive. Default is `enabled`.
 *		     | disabled, ]
 *
 *    [ transmitter,   enabled ] );	//  Whether the UART can transmit. Must be `enabled`.
 * @endcode
 *
 * @code
 * hw( configure, UART,
 *     bps,	  100000 );	//  Baudrate in bits per second
 * @endcode
 */
#define hw_configure__swuarta		, _hw_cfswuarta
#define hwa_configure__swuarta		, _hwa_cfswuarta

/**
 * @ingroup hwa_dev
 *
 * @todo HW_SWUARTA() now uses _hw_a() instead of _hwa() now used by IOs.
 */

#define _hwa_cfswuarta(o,t,r,i,ct,cw,cp,ps,as,fr,k,...)			\
  do {									\
    _hwa_cfswuarta_t(r,t);						\
    _hwa_cfswuarta_ri(r,i);						\
    _hwa_cfswuarta_c(ct,ps);						\
    HW_BW(_hwx_cfswuarta_kbps_,bps,k)(_hwa,o,r,fr,k,__VA_ARGS__,);	\
  } while(0)

/*  Configure TXD pin as output high unless the pin is also
 *  used as RXD.
 */
#define _hwa_cfswuarta_t(r,t)		HW_B(_hwa_cfswuarta_t,HW_A1 t)(r,t)
#define _hwa_cfswuarta_t1(r,t)
#define _hwa_cfswuarta_t0(r,t)						\
  if ( HW_ADDRESS(t) != -1 && HW_ADDRESS(r) != HW_ADDRESS(t) ) {	\
    _hw_a( write, t, 1 );						\
    _hw_a( configure, t, mode, digital_output );			\
  }									\

/*  RXD pin & interrupts (for reception / sync)
 */
#define _hwa_cfswuarta_ri(r,i)		HW_B(_hwa_cfswuarta_ri,HW_A1 r)(r,i)
#define _hwa_cfswuarta_ri1(r,i)
#define _hwa_cfswuarta_ri0(r,i)			\
  if ( HW_ADDRESS(r) != -1 ) {			\
    _hw_a( configure, r, mode, digital_input );	\
    _hw_a( turn, (r,port,pcic), r, on );		\
    _hw_a( enable, (r,port,pcic,irq) );		\
  }

/*  Counter
 */
#define _hwa_cfswuarta_c(ct,ps)			\
  _hw_a( configure, ct,				\
	 clock,     ioclk / ps,			\
	 direction, up_loop,			\
	 top,	   max )

#define _hw_cfswuarta(o,t,r,i,ct,cw,cp,ps,as,fr,k,...)			\
  do {									\
    HW_BW(_hwx_cfswuarta_kbps_,bps,k)(_hw,o,r,fr,k,__VA_ARGS__,);	\
  } while(0)

/*  Process arg `bps`
 */
#define _hwx_cfswuarta_kbps_1(h,o,r,fr,k0,v,k,...)			\
  hw_##o##_##set_dt((HW_SYSHZ + (v)/2) / (v)) ;				\
  *(volatile uint8_t*)fr |= 0x0A ; /* Set SYNC, TXC */			\
  HW_BW(_hwx_cfswuarta_kdatabits_,databits,k)(h,o,r,k,__VA_ARGS__)

#define _hwx_cfswuarta_kbps_0(h,o,r,fr,k,...)			\
  HW_BW(_hwx_cfswuarta_kcpb_,cpb,k)(h,o,r,fr,k,__VA_ARGS__)

/*  Process arg `cpb`
 */
#define _hwx_cfswuarta_kcpb_1(h,o,r,fr,k0,v,k,...)			\
  hw_##o##_##set_dt(v) ;						\
  *(volatile uint8_t*)fr |= 0x0A ; /* Set SYNC, TXC */			\
  HW_BW(_hwx_cfswuarta_kdatabits_,databits,k)(h,o,r,k,__VA_ARGS__)

#define _hwx_cfswuarta_kcpb_0(h,o,r,fr,k,...)				\
  HW_BW(_hwx_cfswuarta_kdatabits_,databits,k)(h,o,r,k,__VA_ARGS__)

/*  Process arg `databits`
 */
#define _hwx_cfswuarta_kdatabits_1(h,o,r,k,v,...)			\
  HW_B(_hwx_cfswuarta_vdatabits_,_hw_swuarta_csz_##v)(h,o,r,v,__VA_ARGS__)

#define _hwx_cfswuarta_vdatabits_0(h,o,r,v,...)	\
  HW_E(HW_EM_VAL(v,databits,(8)))

#define _hwx_cfswuarta_vdatabits_1(h,o,r,v,...)	\
  _hwx_cfswuarta_kdatabits_0(h,o,r,__VA_ARGS__)

#define _hwx_cfswuarta_kdatabits_0(h,o,r,k,...)			\
  HW_BW(_hwx_cfswuarta_kparity_,parity,k)(h,o,r,k,__VA_ARGS__)

#define _hw_swuarta_csz_8		, 0

/*  Process arg `parity`
 */
#define _hwx_cfswuarta_kparity_1(h,o,r,k,v,...)				\
  HW_B(_hwx_cfswuarta_vparity_,_hw_swuarta_pm_##v)(h,o,r,v,__VA_ARGS__)

#define _hwx_cfswuarta_vparity_0(h,o,r,v,...)	\
  HW_E(HW_EM_VAL(v,parity,(none)))

#define _hwx_cfswuarta_vparity_1(h,o,r,v,...)	\
  _hwx_cfswuarta_kparity_0(h,o,r,__VA_ARGS__)

#define _hwx_cfswuarta_kparity_0(h,o,r,k,...)				\
  HW_BW(_hwx_cfswuarta_kstopbits_,stopbits,k)(h,o,r,k,__VA_ARGS__)

#define _hw_swuarta_pm_none		, 0

/*  Process arg `stopbits`
 */
#define _hwx_cfswuarta_kstopbits_1(h,o,r,k,v,...)			\
  HW_B(_hwx_cfswuarta_vstopbits_,_hw_swuarta_sbs_##v)(h,o,r,v,__VA_ARGS__)

#define _hwx_cfswuarta_vstopbits_0(h,o,r,v,...)	\
  HW_E(HW_EM_VAL(v,stopbits,(1)))

#define _hwx_cfswuarta_vstopbits_1(h,o,r,v,...)	\
  _hwx_cfswuarta_kstopbits_0(h,o,r,__VA_ARGS__)

#define _hwx_cfswuarta_kstopbits_0(h,o,r,k,...)				\
  HW_BW(_hwx_cfswuarta_kreceiver_,receiver,k)(h,o,r,k,__VA_ARGS__)

#define _hw_swuarta_sbs_1		, 0

/*  Process arg `receiver`
 */
#define _hwx_cfswuarta_kreceiver_1(h,o,r,k,v,...)			\
  HW_B(_hwx_cfswuarta_vreceiver_,_hw_state_##v)(h,o,r,v,__VA_ARGS__)

#define _hwx_cfswuarta_vreceiver_0(h,o,r,v,...)	\
  HW_E(HW_EM_VAL(v,receiver,(enabled)))

#define _hwx_cfswuarta_vreceiver_1(h,o,r,v,...)	\
  h( turn, (r,pcic,irq), _hw_state_##v);	\
  _hwx_cfswuarta_kreceiver_0(h,o,r,__VA_ARGS__)

#define _hwx_cfswuarta_kreceiver_0(h,o,r,k,...)				\
  HW_BW(_hwx_cfswuarta_ktransmitter_,transmitter,k)(h,o,r,k,__VA_ARGS__)

/*  Process arg `transmitter`
 */
#define _hwx_cfswuarta_ktransmitter_1(h,o,r,k,v,...)			\
  HW_B(_hwx_cfswuarta_vtransmitter_,_hw_state_##v)(h,o,r,v,__VA_ARGS__)

#define _hwx_cfswuarta_vtransmitter_0(h,o,r,v,...)	\
  HW_E(HW_EM_VAL(v,transmitter,(enabled)))

#define _hwx_cfswuarta_vtransmitter_1(h,o,r,v,...)	\
  _hwx_cfswuarta_end(o,__VA_ARGS__)

#define _hwx_cfswuarta_ktransmitter_0(h,o,r,...)	\
  _hwx_cfswuarta_end(o,__VA_ARGS__)

#define _hwx_cfswuarta_end(o,...)		\
  HW_EOL(__VA_ARGS__)



/**
 * @addtogroup atmelavr_swuarta
 *
 * <br><br>hw( read, UART ) clears the `rxc` flag, and returns the last byte received.
 *
 * @code
 * while ( hw(stat,UART).rxc == 0 );
 * uint8_t byte = hw( read, UART );
 * @endcode
 */
#define hw_read__swuarta				, _hw_rdswuarta
#define _hw_rdswuarta(o,t,r,i,ct,cw,cp,ps,as,fr,...)	hw_##o##_getbyte() HW_EOL(__VA_ARGS__)


/**
 * @addtogroup atmelavr_swuarta
 *
 * <br><br>hw( write, UART, byte ) places a byte into the shift register, clears
 * the `txc` flag and starts the transmission.
 *
 * This instruction returns before the byte is actually transmitted. You need to
 * check the `txc` flag to know when the transmission is complete.
 *
 * @code
 * while ( hw(stat,UART).txc == 0 );
 * hw( write, UART, '#' );
 * @endcode
 */
#define hw_write__swuarta				, _hw_wrswuarta
#define _hw_wrswuarta(o,t,r,i,ct,cw,cp,ps,as,fr,v,...)	hw_##o##_putbyte(v) HW_EOL(__VA_ARGS__)


/**
 * @addtogroup atmelavr_swuarta
 *
 * <br><br>hw( stat, UART ) returns the status with the following flags:
 *
 * * `stop`: the state of the last stop bit received, 0 if the byte failed to
 *	     transmit (collision)
 * * `rxc`: 1 when a reception is completed (stop bit sampled)
 * * `txc`: 1 when the transmission is completed (stop bit sent)
 * * `sync`: 1 when the UART is synchronized
 *
 * @code
 * uint8_t byte ;
 * hw_stat_t(UART) st ;			// Structure of UART status
 * st = hw( stat, UART );		// Read the status
 * if ( st.rxc==1 && st.stop==1 )	// Reception complete with valid stop bit
 *   byte = hw( read, UART );
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
    } hw_swuarta_stat_t ;


#define hw_stat_t__swuarta				, _hw_sttswuarta
#define _hw_sttswuarta(o,t,r,i,ct,cw,cp,ps,as,fr,...)	_hw_swuarta_stat_t HW_EOL(__VA_ARGS__)

#define hw_stat__swuarta				, _hw_stswuarta
#define _hw_stswuarta(o,t,r,i,ct,cw,cp,ps,as,fr,...)	(*(volatile hw_swuarta_stat_t*)fr) HW_EOL(__VA_ARGS__)


/**
 * @addtogroup atmelavr_swuarta
 *
 * <br><br>hw( clear, UART ) clears the `rxc` and `txc` status flags.
 *
 * @code
 * hw( clear, UART );
 * @endcode
 */
#define hw_clear__swuarta				, _hw_clswuarta
#define _hw_clswuarta(o,t,r,i,ct,cw,cp,ps,as,fr,...)			\
  do {									\
    if ( fr == -1 || fr >= 0x40 )					\
      *(volatile uint8_t*)hw_##o##_stat &= 0xFC ; /* Clear RXC and TXC */ \
    else {								\
      *(volatile uint8_t*)fr &= 0xFE ; /* Clear RXC with cbi */		\
      *(volatile uint8_t*)fr &= 0xFD ; /* Clear TXC with cbi */		\
    }									\
  }while(0)


/**
 * @addtogroup atmelavr_swuarta
 *
 * <br><br>hw( reset, UART ) aborts any transmission or reception. If the UART
 * has automatic baudrate detection, the UART will first resynchronize.
 *
 * @code
 * hw( reset, UART );
 * @endcode
 */
#define hw_reset__swuarta					, _hw_swuarta_reset
#define _hw_swuarta_reset(o,t,r,i,ct,cw,cp,ps,as,fr,...)	hw_##o##_##reset() HW_EOL(__VA_ARGS__)


/**
 * @addtogroup atmelavr_swuarta
 *
 * <br><br>hw( wait_idle, UART, n ) wait n idle bits:
 *
 * @code
 * hw( wait_idle, UART, 25 );
 * @endcode
 */
#define hw_wait_idle_bits__swuarta				, _hw_wiswuarta
#define _hw_wiswuarta(o,t,r,i,ct,cw,cp,ps,as,fr,v,...)		hw_##o##_##wait_idle_bits(v) HW_EOL(__VA_ARGS__)


/**
 * @addtogroup atmelavr_swuarta
 * @section atmelavr_swuarta_regs Registers
 *
 * * `dt0`: number of counter clocks between the start condition and the
 *          sampling of data bit #0
 * * `dtn`: number of counter clocks between samplings
 * * `sr`: status byte
 */

#else /* !defined __ASSEMBLER__ */

#define HW_DECLARE__swuarta		, _hw_dcswuarta
#define _hw_dcswuarta(...)

#endif /* !defined __ASSEMBLER__ */
