
/*  Declare a software UART object
 *
 *  HW_SWUART(   txd,       ...,
 *             [ rxd,       ..., ]
 *               counter,   ...,
 *               compare,   ...,
 *               clkdiv,    ...,
 *             [ autosync,  ..., ]
 *             [ fastreg,   ...  ]   );
 */
#define hw_class__swuarta

#define HW_SWUART(...)					_HW_SWUART0(__VA_ARGS__,,,,,)
#define _HW_SWUART0(k,...)				HW_KW(_HW_SWUART0_,txd,k)(k,__VA_ARGS__)
#define _HW_SWUART0_0(k,...)				,,HW_EM_KX(txd,k)
#define _HW_SWUART0_1(k,v,...)				HW_KW(_HW_SWUART1_,_ioa,hw_##v)(v,__VA_ARGS__)
#define _HW_SWUART1_0(v,...)				,,HW_EM_ONAP(v)
#define _HW_SWUART1_1(t,k,...)				HW_KW(_HW_SWUART2_,rxd,k)(t,k,__VA_ARGS__)
#define _HW_SWUART2_0(t,k,...)				HW_KW(_HW_SWUART4_,counter,k)(t,,k,__VA_ARGS__)
#define _HW_SWUART2_1(t,k,v,...)			HW_KW(_HW_SWUART3_,_ioa,hw_##v)(t,v,__VA_ARGS__)
#define _HW_SWUART3_0(t,v,...)				,,HW_EM_ONAP(v)
#define _HW_SWUART3_1(t,r,k,...)			HW_KW(_HW_SWUART4_,counter,k)(t,r,k,__VA_ARGS__)
#define _HW_SWUART4_0(...)				_HW_SWUART_E
#define _HW_SWUART4_1(t,r,k1,ct,k,...)			HW_KW(_HW_SWUART5_,compare,k)(t,r,ct,k,__VA_ARGS__)
#define _HW_SWUART5_0(...)				_HW_SWUART_E
#define _HW_SWUART5_1(t,r,ct,k1,cp,k,...)		HW_KW(_HW_SWUART6_,clkdiv,k)(t,r,ct,HW_BITS(ct),cp,k,__VA_ARGS__)
#define _HW_SWUART6_0(t,r,ct,cw,cp,k,...)			_HW_SWUART_E
#define _HW_SWUART6_1(t,r,ct,cw,cp,k1,ps,k,...)		HW_KW(_HW_SWUART7_,autosync,k)(t,r,ct,cw,cp,ps,k,__VA_ARGS__)
#define _HW_SWUART7_0(t,r,ct,cw,cp,ps,k,...)		HW_KW(_HW_SWUART8_,fastreg,k)(t,r,ct,cw,cp,ps,0,k,__VA_ARGS__)
#define _HW_SWUART7_1(t,r,ct,cw,cp,ps,k1,as,k,...)	HW_KW(_HW_SWUART8_,fastreg,k)(t,r,ct,cw,cp,ps,as,k,__VA_ARGS__)
#define _HW_SWUART8_0(t,r,ct,cw,cp,ps,as,k,...)		HW_Y0(_HW_SWUART9_,k)(t,r,ct,cw,cp,ps,as,-1,k,__VA_ARGS__)
#define _HW_SWUART8_1(t,r,ct,cw,cp,ps,as,k1,fr,k,...)	HW_Y0(_HW_SWUART9_,k)(t,r,ct,cw,cp,ps,as,HW_ADDRESS(fr),k,__VA_ARGS__)
#define _HW_SWUART9_0(t,r,ct,cw,cp,ps,as,fr,g,...)		,,HW_EM_G(g)
#define _HW_SWUART9_1(t,r,ct,cw,cp,ps,as,fr,...)		_swuarta, swuart##t##r, (t,r,ct,cw,cp,ps,as,fr)

#define _HW_SWUART_E	,, HW_E(HW_EM_S(HW_SWUARTX( txd,..., [rxd,...,] counter,..., compare,..., clkdiv,..., fastreg,... )))

#define _hw_is_autosync_autosync		, 1
#define _hw_is_clkdiv_clkdiv			, 1
#define _hw_is_fastreg_fastreg			, 1


/*  Return the address of the compare register as address of the swuart
 */
#define HW_ADDRESS__swuarta			, _hw_adswuarta
#define _hw_adswuarta(oo,t,r,ct,cw,cp,...)	_hw_adswuarta1( HW_X((ct,cp,reg)) )
#define _hw_adswuarta1(...)			_hw_adswuarta2(__VA_ARGS__)
#define _hw_adswuarta2(m111,oo,o,r,rc,ra,...)	ra


#if !defined __ASSEMBLER__


/**
 * @page atmelavr_swuarta
 * __Interface and implementation__
 *
 * `HW_DECLARE()` returns the prototypes of the functions used by HWA to perform
 * various actions.
 *
 * @code
 * HW_DECLARE( UART );
 * @endcode
 */
#define HW_DECLARE__swuarta		, _hw_dcswuarta

#define _hw_dcswuarta(o,txd,rxd,ct,cw,cp,ps,as,fr,...)			\
  extern uint8_t      __hw_##o##_stat ;					\
  extern uint##cw##_t __hw_##o##_dtn ;					\
  extern uint##cw##_t __hw_##o##_dt0 ;					\
  extern uint8_t _hw_##o##_getbyte();					\
  extern void _hw_##o##_putbyte(uint8_t);				\
  extern void _hw_##o##_set_dt(uint##cw##_t);				\
  extern void _hw_##o##_reset();					\
  extern void _hw_##o##_sample(uint8_t);				\
  extern void _hw_##o##_wait_idle_bits(uint8_t);			\
  extern void _hw_##o##_brk(uint8_t)


/*  Give access to memory registers created by _swuarta
 */
#define hw__swuarta_dtn					, _hw_swuartadtn
#define _hw_swuartadtn(o,txd,rxd,ct,cw,cp,ps,as,fr)	_mem##cw,(o,dtn),((volatile uint##cw##_t*)__hw_##o##_dtn)

#define hw__swuarta_dt0					, _hw_swuartadt0
#define _hw_swuartadt0(o,txd,rxd,ct,cw,cp,ps,as,fr)	_mem##cw,(o,dt0),((volatile uint##cw##_t*)__hw_##o##_dt0)

#define hw__swuarta_stat				, _hw_swuartast
#define _hw_swuartast(o,txd,rxd,ct,cw,cp,ps,as,fr)	_m111,(o,stat),(o,stat,_r8,(intptr_t)&__hw_##o##_stat,0xFF,0x00,8,0)

#define hw__swuarta_sync				, _hw_swuartasyn
#define _hw_swuartasyn(o,txd,rxd,ct,cw,cp,ps,as,fr)	_m111,(o,sync),(o,sync,_r8,(intptr_t)& __hw_##o##_stat,0xFF,0x00,1,3)


/**
 * @page atmelavr_swuarta
 * @section atmelavr_swuarta_act Actions
 *
 * <br>
 * `configure`
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
 *
 * @endcode
 */
#define hw_configure__swuarta		, _hw_cfswuarta
#define hwa_configure__swuarta		, _hwa_cfswuarta

#define _hwa_cfswuarta_rxd(rxd)		HW_Y0(_hwa_cfswuarta_rxd,rxd)(rxd)
#define _hwa_cfswuarta_rxd1(...)
#define _hwa_cfswuarta_rxd0(rxd)			\
    _hwa( configure, rxd, mode, digital_input );	\
    _hwa( clear, (rxd,pcic,irq) );			\
    _hwa( enable, (rxd,pcic,irq) );			\
    _hwa( turn, (rxd,pcic), rxd, on );


#define _hwa_cfswuarta(o,txd,rxd,ct,cw,cp,ps,as,fr,k,...)			\
  do {									\
    									\
    /*  Configure the counter						\
     */									\
    _hwa( configure, ct,						\
	  clock,     ioclk / ps,					\
	  direction, up_loop,						\
	  top,	     max );						\
    									\
    /*  RXD pin								\
     */									\
    _hwa_cfswuarta_rxd(rxd);						\
    									\
    /*  TXD pin								\
     *									\
     *	Configure TXD pin as output high unless the pin is also		\
     *  used as RXD.							\
     */									\
    if ( HW_ADDRESS(rxd) != HW_ADDRESS(txd) ) {				\
      _hwa( configure, txd, mode, digital_output );			\
      _hwa( write, txd, 1 );						\
    }									\
    									\
    HW_KW(_hwx_cfswuarta_kbps_,bps,k)(_hwa,o,fr,k,__VA_ARGS__,);	\
  } while(0)

#define _hw_cfswuarta(o,t,r,ct,cw,cp,ps,as,fr,k,...)			\
  do {									\
    HW_KW(_hwx_cfswuarta_kbps_,bps,k)(_hw,o,fr,k,__VA_ARGS__,);	\
  } while(0)

/*  Process arg `bps`
 */
#define _hwx_cfswuarta_kbps_1(h,o,fr,k0,v,k,...)			\
  _hw_##o##_##set_dt((HW_SYSHZ + (v)/2) / (v)) ;			\
  *(volatile uint8_t*)fr |= 0x08 ; /* Set SYNC */			\
  HW_KW(_hwx_cfswuarta_kdatabits_,databits,k)(h,o,k,__VA_ARGS__)

#define _hwx_cfswuarta_kbps_0(h,o,fr,k,...)			\
  HW_KW(_hwx_cfswuarta_kcpb_,cpb,k)(h,o,fr,k,__VA_ARGS__)

/*  Process arg `cpb`
 */
#define _hwx_cfswuarta_kcpb_1(h,o,fr,k0,v,k,...)			\
  _hw_##o##_##set_dt(v) ;						\
  *(volatile uint8_t*)fr |= 0x08 ; /* Set SYNC */			\
  HW_KW(_hwx_cfswuarta_kdatabits_,databits,k)(h,o,k,__VA_ARGS__)

#define _hwx_cfswuarta_kcpb_0(h,o,fr,k,...)				\
  HW_KW(_hwx_cfswuarta_kdatabits_,databits,k)(h,o,k,__VA_ARGS__)

/*  Process arg `databits`
 */
#define _hwx_cfswuarta_kdatabits_1(h,o,k,v,...)				\
  HW_Y(_hwx_cfswuarta_vdatabits_,_hw_swuarta_csz_##v)(h,o,v,__VA_ARGS__)

#define _hwx_cfswuarta_vdatabits_0(h,o,v,...)	\
  HW_E_AVL(`databits`, v, `8`)

#define _hwx_cfswuarta_vdatabits_1(h,o,v,...)	\
  _hwx_cfswuarta_kdatabits_0(h,o,__VA_ARGS__)

#define _hwx_cfswuarta_kdatabits_0(h,o,k,...)				\
  HW_KW(_hwx_cfswuarta_kparity_,parity,k)(h,o,k,__VA_ARGS__)

#define _hw_swuarta_csz_8		, 0

/*  Process arg `parity`
 */
#define _hwx_cfswuarta_kparity_1(h,o,k,v,...)				\
  HW_Y(_hwx_cfswuarta_vparity_,_hw_swuarta_pm_##v)(h,o,v,__VA_ARGS__)

#define _hwx_cfswuarta_vparity_0(h,o,v,...)	\
  HW_E_AVL(`parity`, v, `none`)

#define _hwx_cfswuarta_vparity_1(h,o,v,...)	\
  _hwx_cfswuarta_kparity_0(h,o,__VA_ARGS__)

#define _hwx_cfswuarta_kparity_0(h,o,k,...)				\
  HW_KW(_hwx_cfswuarta_kstopbits_,stopbits,k)(h,o,k,__VA_ARGS__)

#define _hw_swuarta_pm_none		, 0

/*  Process arg `stopbits`
 */
#define _hwx_cfswuarta_kstopbits_1(h,o,k,v,...)				\
  HW_Y(_hwx_cfswuarta_vstopbits_,_hw_swuarta_sbs_##v)(h,o,v,__VA_ARGS__)

#define _hwx_cfswuarta_vstopbits_0(h,o,v,...)	\
  HW_E_AVL(`stopbits`, v, `1`)

#define _hwx_cfswuarta_vstopbits_1(h,o,v,...)	\
  _hwx_cfswuarta_kstopbits_0(h,o,__VA_ARGS__)

#define _hwx_cfswuarta_kstopbits_0(h,o,k,...)				\
  HW_KW(_hwx_cfswuarta_kreceiver_,receiver,k)(h,o,k,__VA_ARGS__)

#define _hw_swuarta_sbs_1		, 0

/*  Process arg `receiver`
 */
#define _hwx_cfswuarta_kreceiver_1(h,o,k,v,...)				\
  HW_Y(_hwx_cfswuarta_vreceiver_,_hw_state_##v)(h,o,v,__VA_ARGS__)

#define _hwx_cfswuarta_vreceiver_0(h,o,v,...)	\
  HW_E_AVL(receiver, v, enabled | disabled)

#define _hwx_cfswuarta_vreceiver_1(h,o,v,...)				\
  h( turn, (rxd,pcic,irq), _hw_state_##v);				\
  _hwx_cfswuarta_kreceiver_0(h,o,__VA_ARGS__)

#define _hwx_cfswuarta_kreceiver_0(h,o,k,...)				\
  HW_KW(_hwx_cfswuarta_ktransmitter_,transmitter,k)(h,o,k,__VA_ARGS__)

/*  Process arg `transmitter`
 */
#define _hwx_cfswuarta_ktransmitter_1(h,o,k,v,...)			\
  HW_Y(_hwx_cfswuarta_vtransmitter_,_hw_state_##v)(h,o,v,__VA_ARGS__)

#define _hwx_cfswuarta_vtransmitter_0(h,o,v,...)	\
  HW_E_AVL(`transmitter`, v, `enabled`)

#define _hwx_cfswuarta_vtransmitter_1(h,o,v,...)	\
  _hwx_cfswuarta_end(o,__VA_ARGS__)

#define _hwx_cfswuarta_ktransmitter_0(h,o,...)	\
  _hwx_cfswuarta_end(o,__VA_ARGS__)

#define _hwx_cfswuarta_end(o,...)		\
   HW_EOL(__VA_ARGS__)



/**
 * @page atmelavr_swuarta
 *
 * <br>
 * `read`: waits for the reception of a byte, clears the `rxc` flag, and returns
 * the byte.
 *
 * FIXME: _swuarta should not wait and let the application check the status.
 *
 * @code
 * while ( hw(stat,UART).rxc == 0 );
 * uint8_t byte = hw( read, UART );	// Clears the 'rxc' status flag
 * @endcode
 */
#define hw_read__swuarta				, _hw_rdswuarta
#define _hw_rdswuarta(o,txd,rxd,ct,cw,cp,ps,as,fr,...)	_hw_##o##_getbyte() HW_EOL(__VA_ARGS__)


/**
 * @page atmelavr_swuarta
 *
 * <br>
 * `write`: waits for the completion of the transmission (and the reception in
 * 1-wire mode) and places the byte to send into the shift register. This
 * instruction returns before the byte is actually transmitted. You need to
 * check the `txc` flag to know when the transmission is complete.
 *
 * FIXME: _swuarta should not wait and let the application check the status.
 *
 * @code
 * while ( hw(stat,UART).txc == 0 );
 * hw( write, UART, '#' );		// Clears the 'txc' status flag
 * @endcode
 */
#define hw_write__swuarta				, _hw_wrswuarta
#define _hw_wrswuarta(o,t,r,ct,cw,cp,ps,as,fr,v,...)	_hw_##o##_putbyte(v) HW_EOL(__VA_ARGS__)


/**
 * @page atmelavr_swuarta
 *
 * <br>
 * `stat`: returns the status, containing the following flags:
 *
 * * `stop`: the state of the received stop bit, 0 if the byte failed to
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
} _hw_swuarta_stat_t ;


#define hw_stat_t__swuarta				, _hw_sttswuarta
#define _hw_sttswuarta(o,txd,rxd,ct,cw,cp,ps,as,fr,...)	_hw_swuarta_stat_t HW_EOL(__VA_ARGS__)

#define hw_stat__swuarta		, _hw_stswuarta
#define _hw_stswuarta(o,txd,rxd,ct,cw,cp,ps,as,fr,...)	(*(volatile _hw_swuarta_stat_t*)fr) HW_EOL(__VA_ARGS__)


/**
 * @page atmelavr_swuarta
 *
 * `clear`: clears the `rxc` and `txc` status flags.
 *
 * @code
 * hw( clear, UART );
 * @endcode
 */
#define hw_clear__swuarta				, _hw_clswuarta
#define _hw_clswuarta(o,txd,rxd,ct,cw,cp,ps,as,fr,...)		\
  do {								\
    if ( fr == -1 )						\
      break ;							\
    if ( fr < 0x40 ) {						\
      *(volatile uint8_t*)a &= 0xFE ; /* Clear RXC with cbi */	\
      *(volatile uint8_t*)a &= 0xFD ; /* Clear TXC with cbi */	\
    }else							\
      *(volatile uint8_t*)a &= 0xFC ; /* Clear RXC & TXC */	\
  }while(0)


/**
 * @page atmelavr_swuarta
 *
 * `reset`: aborts any transmission or reception. If the UART has automatic
 * baudrate detection, the UART will first resynchronize.
 *
 * @code
 * hw( reset, UART );
 * @endcode
 */
#define hw_reset__swuarta				, _hw_swuarta_reset
#define _hw_swuarta_reset(o,txd,rxd,ct,cw,cp,ps,as,fr,...)	_hw_##o##_##reset() HW_EOL(__VA_ARGS__)


/**
 * @page atmelavr_swuarta
 * @section atmelavr_swuarta_regs Registers
 *
 * Class `_swuarta` objects hold the following registers:
 *
 *  * `dt0`: number of counter clocks between the start condition and the sampling of data bit 0
 *  * `dtn`: number of counter clocks between samplings
 *  * `sr`: status byte
 */

#else /* !defined __ASSEMBLER__ */

#define HW_DECLARE__swuarta		, _hw_dcswuarta
#define _hw_dcswuarta(...)

#endif /* !defined __ASSEMBLER__ */
