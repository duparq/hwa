
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief UART
 */

/**
 * @addtogroup atmelavr_uarta
 * @section atmelavr_uarta_act Actions
 *
 * <br>
 * `configure`:
 *
 * @code
 * hwa( configure, uart0,
 *
 *	//  Transfer rate in bits per second
 *	//
 *    [ bps,	     BPS, ]
 *
 *	//  Number of data bits in frame. Default is `8`.
 *	//
 *    [ databits,    5 | 6 | 7 | 8 | 9, ]
 *
 *	//  Parity. Default is `none`.
 *	//
 *    [ parity,	     none, even, odd, ]
 *
 *	//  Number of stop bits in frame. Default is `1`.
 *	//
 *    [ stopbits,    1 | 2, ]
 *
 *	//  Whether the UART can receive. Default is `enabled`.
 *	//
 *    [ receiver,    enabled | disabled, ]
 *
 *	//  Whether the UART can transmit. Default is `enabled`.
 *	//
 *    [ transmitter, enabled | disabled, ] );
 * @endcode
 */
#define _hwa_cfuarta(o,a,k,...)					\
  do { HW_B(_hwa_cfuarta_kbps_,_hw_is_bps_##k)(o,k,__VA_ARGS__,,) } while(0)

#define hwa_configure__uarta		, _hwa_cfuarta

/*	Optionnal parameter `bps`
 *	  Choose the U2X value that gives the lowest error
 */
#define _hwa_cfuarta_kbps_1(o,k,v,...)					\
  HW_B(_hwa_cfuarta_vbps_,v)(o,v,__VA_ARGS__)

#define _hwa_cfuarta_vbps_1(o,v,...)	HW_E(HW_EM_VAM(bps))

#define _hwa_cfuarta_vbps_0(o,v,k,...)					\
  uint32_t brr8 = (HW_SYSHZ / 8 + (v/2)) / v ;				\
  uint32_t brr16 = (HW_SYSHZ / 16 + (v/2)) / v ;			\
  float e16 = 1.0 * HW_SYSHZ / (16*brr16) / v ;				\
  float e8 = 1.0 * HW_SYSHZ / (8*brr8) / v ;				\
  if ( e16 < 1.0 ) e16 = 2.0 - e16 ;					\
  if ( e8 < 1.0 ) e8 = 2.0 - e8 ;					\
  if ( e8 < e16 && brr8 > 0 && brr8 < 0x1000 ) {			\
    hwa->o.config.u2x = 1 ;						\
    hwa->o.config.brr = brr8-1 ;					\
  }									\
  else if ( brr16 > 0 && brr16 < 0x1000 ) {				\
    hwa->o.config.u2x = 0 ;						\
    hwa->o.config.brr = brr16-1 ;					\
  }									\
  else									\
    HWA_E(HW_EM_XSO(bps,o));						\
  HW_B(_hwa_cfuarta_kdatabits_,_hw_is_databits_##k)(o,k,__VA_ARGS__)

#define _hwa_cfuarta_kbps_0(o,k,...)					\
  HW_B(_hwa_cfuarta_kdatabits_,_hw_is_databits_##k)(o,k,__VA_ARGS__)

/*	Optionnal parameter `databits`
 */
#define _hwa_cfuarta_kdatabits_1(o,k,v,...)				\
  HW_B(_hwa_cfuarta_vdatabits_,_hw_uarta_csz_##v)(o,v,__VA_ARGS__)

#define _hwa_cfuarta_vdatabits_0(o,v,...)	HW_E(HW_EM_VOAL(v,databits,(5,6,7,8,9)))

#define _hwa_cfuarta_vdatabits_1(o,v,k,...)	\
  hwa->o.config.csz = HW_A1(_hw_uarta_csz_##v);	\
  HW_B(_hwa_cfuarta_kparity_,_hw_is_parity_##k)(o,k,__VA_ARGS__)

#define _hwa_cfuarta_kdatabits_0(o,k,...)				\
  HW_B(_hwa_cfuarta_kparity_,_hw_is_parity_##k)(o,k,__VA_ARGS__)

#define _hw_uarta_csz_5			, 0
#define _hw_uarta_csz_6			, 1
#define _hw_uarta_csz_7			, 2
#define _hw_uarta_csz_8			, 3
#define _hw_uarta_csz_9			, 7

/*	Optionnal parameter `parity`
 */
#define _hwa_cfuarta_kparity_1(o,k,v,...)				\
  HW_B(_hwa_cfuarta_vparity_,_hw_uarta_pm_##v)(o,v,__VA_ARGS__)

#define _hwa_cfuarta_vparity_0(o,v,...)		HW_E(HW_EM_VOAL(v,parity,(none,even,odd)))

#define _hwa_cfuarta_vparity_1(o,v,k,...)	\
  hwa->o.config.pm = HW_A1(_hw_uarta_pm_##v);	\
  HW_B(_hwa_cfuarta_kstopbits_,_hw_is_stopbits_##k)(o,k,__VA_ARGS__)

#define _hwa_cfuarta_kparity_0(o,k,...)					\
  HW_B(_hwa_cfuarta_kstopbits_,_hw_is_stopbits_##k)(o,k,__VA_ARGS__)

#define _hw_uarta_pm_none		, 0
#define _hw_uarta_pm_even		, 2
#define _hw_uarta_pm_odd		, 3

/*	Optionnal parameter `stopbits`
 */
#define _hwa_cfuarta_kstopbits_1(o,k,v,...)				\
  HW_B(_hwa_cfuarta_vstopbits_,_hw_uarta_sbs_##v)(o,v,__VA_ARGS__)

#define _hwa_cfuarta_vstopbits_0(o,v,...)	HW_E(HW_EM_VOAL(v,stopbits,(1,2)))

#define _hwa_cfuarta_vstopbits_1(o,v,k,...)	\
  hwa->o.config.sbs = HW_A1(_hw_uarta_sbs_##v);	\
  HW_B(_hwa_cfuarta_kreceiver_,_hw_is_receiver_##k)(o,k,__VA_ARGS__)

#define _hwa_cfuarta_kstopbits_0(o,k,...)				\
  HW_B(_hwa_cfuarta_kreceiver_,_hw_is_receiver_##k)(o,k,__VA_ARGS__)

#define _hw_uarta_sbs_1			, 0
#define _hw_uarta_sbs_2			, 1

/*	Optionnal parameter `receiver`
 */
#define _hwa_cfuarta_kreceiver_1(o,k,v,...)				\
  HW_B(_hwa_cfuarta_vreceiver_,_hw_state_##v)(o,v,__VA_ARGS__)

#define _hwa_cfuarta_vreceiver_0(o,v,...)	HW_E(HW_EM_VOAST(v,receiver))

#define _hwa_cfuarta_vreceiver_1(o,v,k,...)	\
  hwa->o.config.rxen = HW_A1(_hw_state_##v);				\
  HW_B(_hwa_cfuarta_ktransmitter_,_hw_is_transmitter_##k)(o,k,__VA_ARGS__)

#define _hwa_cfuarta_kreceiver_0(o,k,...)				\
  HW_B(_hwa_cfuarta_ktransmitter_,_hw_is_transmitter_##k)(o,k,__VA_ARGS__)

/*	Optionnal parameter `transmitter`
 */
#define _hwa_cfuarta_ktransmitter_1(o,k,v,...)				\
  HW_B(_hwa_cfuarta_vtransmitter_,_hw_state_##v)(o,v,__VA_ARGS__)

#define _hwa_cfuarta_vtransmitter_0(o,v,...)	HW_E(HW_EM_VOAST(v,transmitter))

#define _hwa_cfuarta_vtransmitter_1(o,v,...)	\
  hwa->o.config.txen = HW_A1(_hw_state_##v);	\
  _hwa_cfuarta_end(o,__VA_ARGS__)

#define _hwa_cfuarta_ktransmitter_0(o,...)	\
  _hwa_cfuarta_end(o,__VA_ARGS__)

#define _hwa_cfuarta_end(o,...)			\
  _hwa_write(o,brr,	 hwa->o.config.brr );	\
  _hwa_write(o,2x,	 hwa->o.config.u2x );	\
  _hwa_write(o,csz,	 hwa->o.config.csz );	\
  _hwa_write(o,pm,	 hwa->o.config.pm  );	\
  _hwa_write(o,sbs,	 hwa->o.config.sbs );	\
  _hwa_write(o,rxen, hwa->o.config.rxen );	\
  _hwa_write(o,txen, hwa->o.config.txen );	\
   HW_EOL(__VA_ARGS__)


/**
 * @addtogroup atmelavr_uarta
 * @section atmelavr_uarta_data Data
 *
 * The `read` returns the content of the data register but it does not
 * verify that the transmit buffer of the UART is not empty before reading
 * it. You may have to verify that a character has been received before reading
 * the data register:
 *
 * @code
 * while ( ! hw( read, (uart0,irq, rxc ) ) ) {}
 * uint8_t byte = hw( read, uart0 );
 * @endcode
 */
#define hw_read__uarta			, _hw_rduarta
#define _hw_rduarta(o,a,...)		_hw_read(o,dr) HW_EOL(__VA_ARGS__)


/**
 * @addtogroup atmelavr_uarta
 *
 * The `hw_write()` instruction writes a character into the data registerbut it
 * does not verify that the transmit buffer of the UART is not full before
 * writing into it. You may have to verify this first:
 *
 * @code
 * while ( ! hw( read, (uart0,irq, txqnf ) ) ) {}
 * hw( write, uart0, '#' );
 * @endcode
 */
#define hw_write__uarta			, _hw_wruarta
#define _hw_wruarta(o,a,v,...)	_hw_write(o,dr,v) HW_EOL(__VA_ARGS__)


/*  Power management
 */
#define hw_power__uarta			, _hw_power
#define hwa_power__uarta		, _hwa_power


/**
 * @addtogroup atmelavr_uarta
 * @section atmelavr_uarta_stat Status
 *
 * The UART status contains the following flags:
 *  * `pe` or `parity_error`
 *  * `dor` or `overrun`
 *  * `fe` or `frame_error`
 *  * `txqnf`: transmit queue not full
 *  * `txc`: transmit complete
 *  * `rxc`: receive complete
 *
 * @code
 * uint8_t byte ;
 * hw_stat_t( uart0 ) st ;	    // Structure of UART status
 * st = hw( stat, uart0 );	    // Read the status
 * if ( st.rxc )		    // Reception complete?
 *   byte = hw( read, uart0 );
 * @endcode
 */
typedef union {
  uint8_t		byte ;
  struct {
    unsigned int __0_1 : 2 ;
    unsigned int pe    : 1 ;
    unsigned int dor   : 1 ;
    unsigned int fe    : 1 ;
    unsigned int txqnf : 1 ;
    unsigned int txc   : 1 ;
    unsigned int rxc   : 1 ;
  };
  struct {
    unsigned int ___0_1	      : 2 ;
    unsigned int parity_error : 1 ;
    unsigned int overrun      : 1 ;
    unsigned int frame_error  : 1 ;
    unsigned int _txqnf	      : 1 ;
    unsigned int _txc	      : 1 ;
    unsigned int _rxc	      : 1 ;
  };
} _hw_uarta_stat_t ;

#define hw_stat_t__uarta		, _hw_sttuarta
#define _hw_sttuarta(o,a,...)		 _hw_uarta_stat_t HW_EOL(__VA_ARGS__)

#define hw_stat__uarta			, _hw_stuarta
#define _hw_stuarta(o,a,...)		_hw___stuarta(_hw_read(o,csra)) HW_EOL(__VA_ARGS__)

HW_INLINE _hw_uarta_stat_t _hw___stuarta ( uint8_t byte )
{
  _hw_uarta_stat_t	st ;
  st.byte = byte ;
  return st ;
}


/*******************************************************************************
 *									       *
 *	Context management						       *
 *									       *
 *******************************************************************************/

#define _hwa_setup__uarta(o,a)			\
  _hwa_setup_r( o, ubrr );				\
  _hwa_setup_r( o, csra );				\
  _hwa_setup_r( o, csrb );				\
  _hwa_setup_r( o, csrc );				\
  hwa->o.config.brr  = 0 ;				\
  hwa->o.config.u2x  = 0 ;				\
  hwa->o.config.csz  = HW_A1(_hw_uarta_csz_8) ;		\
  hwa->o.config.pm   = HW_A1(_hw_uarta_pm_none) ;	\
  hwa->o.config.sbs  = HW_A1(_hw_uarta_sbs_1) ;		\
  hwa->o.config.rxen = 1 ;				\
  hwa->o.config.txen = 1

#define _hwa_init__uarta(o,a)			\
  _hwa_init_r( o, ubrr, 0x00 );		\
  _hwa_init_r( o, csra, 0x20 );		\
  _hwa_init_r( o, csrb, 0x00 );		\
  _hwa_init_r( o, csrc, 0x06 )

#define _hwa_commit__uarta(o,a)		\
  _hwa_commit_r( o, ubrr );			\
  _hwa_commit_r( o, csra );			\
  _hwa_commit_r( o, csrb );			\
  _hwa_commit_r( o, csrc )

/**
 * @addtogroup atmelavr_uarta
 * <br>
 */
