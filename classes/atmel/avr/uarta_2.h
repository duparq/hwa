
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 */

/**
 * @page atmelavr_uarta
 * @section atmelavr_uarta_config Configuring the UART
 *
 * @code
 * hwa_config( hw_uart0,
 *
 *             //  Transfer rate in bits per second
 *             //
 *           [ bps,         BPS, ]
 *
 *             //  Number of data bits in frame. Default is `8`.
 *             //
 *           [ databits,    5 | 6 | 7 | 8 | 9, ]
 *
 *             //  Parity. Default is `none`.
 *             //
 *           [ parity,      none, even, odd, ]
 *
 *             //  Number of stop bits in frame. Default is `1`.
 *             //
 *           [ stopbits,    1 | 2, ]
 *
 *             //  Whether the UART can receive. Default is `enabled`.
 *             //
 *           [ receiver,    enabled | disabled, ]
 *
 *             //  Whether the UART can transmit. Default is `enabled`.
 *             //
 *           [ transmitter, enabled | disabled, ]
 *
 *           );
 * @endcode
 */
#define _hw_mthd_hwa_config__uarta		, _hwa_cfuarta

#define _hw_is_bps_bps				, 1
#define _hw_is_databits_databits		, 1
#define _hw_is_parity_parity			, 1
#define _hw_is_stopbits_stopbits		, 1
#define _hw_is_receiver_receiver		, 1
#define _hw_is_transmitter_transmitter		, 1

#define _hw_uarta_csz_5				, 0
#define _hw_uarta_csz_6				, 1
#define _hw_uarta_csz_7				, 2
#define _hw_uarta_csz_8				, 3
#define _hw_uarta_csz_9				, 7

#define _hw_uarta_pm_none			, 0
#define _hw_uarta_pm_even			, 2
#define _hw_uarta_pm_odd			, 3

#define _hw_uarta_sbs_1				, 0
#define _hw_uarta_sbs_2				, 1


#define _hwa_cfuarta(o,i,a,...)						\
  do {									\
      HW_G2(_hwa_cfuarta_kbps, HW_IS(bps,__VA_ARGS__))(o,__VA_ARGS__,)	\
      } while(0)

/*  Process arg `bps`
 *    Choose the U2X value that gives the lowest error
 */
#define _hwa_cfuarta_kbps_1(o,k,v,...)					\
  uint32_t brr8 = (hw_syshz / 8 + (v/2)) / v ;				\
  uint32_t brr16 = (hw_syshz / 16 + (v/2)) / v ;			\
  float e16 = 1.0 * hw_syshz / (16*brr16) / v ;				\
  float e8 = 1.0 * hw_syshz / (8*brr8) / v ;				\
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
    HWA_ERR("can not solve the configuration for the required transfer rate."); \
  _hwa_cfuarta_kbps_0(o,__VA_ARGS__)

#define _hwa_cfuarta_kbps_0(o,k,...)					\
  HW_G2(_hwa_cfuarta_kdatabits, HW_IS(databits,k))(o,k,__VA_ARGS__)

/*  Process arg `databits`
 */
#define _hwa_cfuarta_kdatabits_1(o,k,v,...)				\
  HW_G2(_hwa_cfuarta_vdatabits, HW_IS(,_hw_uarta_csz_##v))(o,v,__VA_ARGS__)

#define _hwa_cfuarta_vdatabits_0(o,v,...)				\
  HW_ERR("`databits` can be `5`, `6`, `7`, `8`, or `9`, but not `" #v "`.")

#define _hwa_cfuarta_vdatabits_1(o,v,...)		\
  hwa->o.config.csz = HW_A1(_hw_uarta_csz_##v);	\
  _hwa_cfuarta_kdatabits_0(o,__VA_ARGS__)

#define _hwa_cfuarta_kdatabits_0(o,k,...)				\
  HW_G2(_hwa_cfuarta_kparity, HW_IS(parity,k))(o,k,__VA_ARGS__)

/*  Process arg `parity`
 */
#define _hwa_cfuarta_kparity_1(o,k,v,...)				\
  HW_G2(_hwa_cfuarta_vparity, HW_IS(,_hw_uarta_pm_##v))(o,v,__VA_ARGS__)

#define _hwa_cfuarta_vparity_0(o,v,...)					\
  HW_ERR("`parity` can be `none`, `even`, or `odd`, but not `" #v "`.")

#define _hwa_cfuarta_vparity_1(o,v,...)			\
  hwa->o.config.pm = HW_A1(_hw_uarta_pm_##v);	\
  _hwa_cfuarta_kparity_0(o,__VA_ARGS__)

#define _hwa_cfuarta_kparity_0(o,k,...)					\
  HW_G2(_hwa_cfuarta_kstopbits, HW_IS(stopbits,k))(o,k,__VA_ARGS__)

/*  Process arg `stopbits`
 */
#define _hwa_cfuarta_kstopbits_1(o,k,v,...)				\
  HW_G2(_hwa_cfuarta_vstopbits, HW_IS(,_hw_uarta_sbs_##v))(o,v,__VA_ARGS__)

#define _hwa_cfuarta_vstopbits_0(o,v,...)				\
  HW_ERR("`stopbits` can be `1`, or `2`, but not `" #v "`.")

#define _hwa_cfuarta_vstopbits_1(o,v,...)		\
  hwa->o.config.sbs = HW_A1(_hw_uarta_sbs_##v);	\
  _hwa_cfuarta_kstopbits_0(o,__VA_ARGS__)

#define _hwa_cfuarta_kstopbits_0(o,k,...)				\
  HW_G2(_hwa_cfuarta_kreceiver, HW_IS(receiver,k))(o,k,__VA_ARGS__)

/*  Process arg `receiver`
 */
#define _hwa_cfuarta_kreceiver_1(o,k,v,...)				\
  HW_G2(_hwa_cfuarta_vreceiver, HW_IS(,hw_state_##v))(o,v,__VA_ARGS__)

#define _hwa_cfuarta_vreceiver_0(o,v,...)			\
  HW_ERR("`receiver` can be `enabled`, or `disabled`, but not `" #v "`.")

#define _hwa_cfuarta_vreceiver_1(o,v,...)	\
    hwa->o.config.rxen = HW_A1(hw_state_##v);	\
    _hwa_cfuarta_kreceiver_0(o,__VA_ARGS__)

#define _hwa_cfuarta_kreceiver_0(o,k,...)				\
  HW_G2(_hwa_cfuarta_ktransmitter, HW_IS(transmitter,k))(o,k,__VA_ARGS__)

/*  Process arg `transmitter`
 */
#define _hwa_cfuarta_ktransmitter_1(o,k,v,...)				\
  HW_G2(_hwa_cfuarta_vtransmitter, HW_IS(,hw_state_##v))(o,v,__VA_ARGS__)

#define _hwa_cfuarta_vtransmitter_0(o,v,...)				\
  HW_ERR("`transmitter` can be `enabled`, or `disabled`, but not `" #v "`.")

#define _hwa_cfuarta_vtransmitter_1(o,v,...)	\
  hwa->o.config.txen = HW_A1(hw_state_##v);	\
  _hwa_cfuarta_end(o,__VA_ARGS__)

#define _hwa_cfuarta_ktransmitter_0(o,...)	\
  _hwa_cfuarta_end(o,__VA_ARGS__)

#define _hwa_cfuarta_end(o,...)			\
  _hwa_write_reg(o,brr,  hwa->o.config.brr );	\
  _hwa_write_reg(o,2x,   hwa->o.config.u2x );	\
  _hwa_write_reg(o,csz,  hwa->o.config.csz );	\
  _hwa_write_reg(o,pm,   hwa->o.config.pm  );	\
  _hwa_write_reg(o,sbs,  hwa->o.config.sbs );	\
  _hwa_write_reg(o,rxen, hwa->o.config.rxen );	\
  _hwa_write_reg(o,txen, hwa->o.config.txen );	\
  HW_TX(,__VA_ARGS__)


/**
 * @page atmelavr_uarta
 * @section atmelavr_uarta_read Reading one byte from UART
 *
 * @code
 * uint8_t byte = hw_read( hw_uart0 );
 * @endcode
 */
#define _hw_mthd_hw_read__uarta		, _hw_rduarta
#define _hw_rduarta(o,i,a,...)		HW_TX(_hw_read_reg(o,dr),__VA_ARGS__)


/**
 * @page atmelavr_uarta
 * @section atmelavr_uarta_write Writing one byte into UART
 *
 * @code
 * hw_write( hw_uart0, '#' );
 * @endcode
 */
#define _hw_mthd_hw_write__uarta	, _hw_wruarta
#define _hw_wruarta(o,i,a,v,...)	HW_TX(_hw_write_reg(o,dr,v),__VA_ARGS__)


/**
 * @page atmelavr_uarta
 *
 * @code
 * hwa_write( hw_uart0, '#' );
 * @endcode
 */
#define _hw_mthd_hwa_write__uarta	, _hwa_wruarta
#define _hwa_wruarta(o,i,a,v,...)	HW_TX(_hwa_write_reg(o,dr,v),__VA_ARGS__)


/**
 * @page atmelavr_uarta
 * @section atmelavr_uarta_stat Getting the status of the UART
 *
 * The UART status contains the following flags:
 * * pe | parity_error
 * * dor | overrun
 * * fe | frame_error
 * * txqnf: transmit queue not full
 * * txc: transmit complete
 * * rxc: receive complete
 *
 * @code
 * uint8_t byte ;
 * hw_stat_t( hw_uart0 ) st ;       // Structure of UART status
 * st = hw_stat( hw_uart0 );        // Read the status
 * if ( st.rxc )                    // Reception complete?
 *   byte = hw_read( hw_uart0 );
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
    unsigned int ___0_1       : 2 ;
    unsigned int parity_error : 1 ;
    unsigned int overrun      : 1 ;
    unsigned int frame_error  : 1 ;
    unsigned int _txqnf       : 1 ;
    unsigned int _txc         : 1 ;
    unsigned int _rxc         : 1 ;
  };
} _hw_uarta_stat_t ;

#define _hw_mthd_hw_stat_t__uarta	, _hw_sttuarta
#define _hw_sttuarta(o,i,a,...)		HW_TX( _hw_uarta_stat_t, __VA_ARGS__)

#define _hw_mthd_hw_stat__uarta		, _hw_stuarta
#define _hw_stuarta(o,i,a,...)		HW_TX(__hw_stuarta(_hw_read_reg(o,csra)), \
					      __VA_ARGS__)

HW_INLINE _hw_uarta_stat_t __hw_stuarta ( uint8_t byte )
{
  _hw_uarta_stat_t	st ;
  st.byte = byte ;
  return st ;
}


HW_INLINE void __hwa_begin__uarta ( hwa_uarta_t *p, intptr_t a )
{
  _hwa_begin_reg_p( p, a, _uarta, ubrr );
  _hwa_begin_reg_p( p, a, _uarta, dr   );
  _hwa_begin_reg_p( p, a, _uarta, csra );
  _hwa_begin_reg_p( p, a, _uarta, csrb );
  _hwa_begin_reg_p( p, a, _uarta, csrc );
}

HW_INLINE void __hwa_init__uarta ( hwa_uarta_t *p )
{
  _hwa_set_r16( &p->ubrr, 0x0000 );
  _hwa_set_r8( &p->dr,    0x00   );
  _hwa_set_r8( &p->csra,  0x20   );
  _hwa_set_r8( &p->csrb,  0x00   );
  _hwa_set_r8( &p->csrc,  0x06   );

  p->config.brr  = 0 ;
  p->config.u2x  = 0 ;
  p->config.csz  = HW_A1(_hw_uarta_csz_8) ;
  p->config.pm   = HW_A1(_hw_uarta_pm_none) ;
  p->config.sbs  = HW_A1(_hw_uarta_sbs_1) ;
  p->config.rxen = 1 ;
  p->config.txen = 1 ;
}

HW_INLINE void __hwa_commit__uarta ( hwa_t *hwa, hwa_uarta_t *p )
{
  _hwa_commit_reg_p( p, _uarta, ubrr );
  _hwa_commit_reg_p( p, _uarta, dr   );
  _hwa_commit_reg_p( p, _uarta, csra );
  _hwa_commit_reg_p( p, _uarta, csrb );
  _hwa_commit_reg_p( p, _uarta, csrc );
}
