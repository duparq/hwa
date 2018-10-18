
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief UART
 */

/**
 * @page espressif_uarta
 * @section espressif_uarta_config Configuration
 *
 * @code
 * hw | hwa( configure, uart0,
 *
 *           //  Transfer rate in bits per second
 *           //
 *         [   bps
 *           | baudrate,  BPS, ]
 *         
 *           //  Number of data bits in frame. Default is `8`.
 *           //
 *         [ databits,    5 | 6 | 7 | 8, ]
 *         
 *           //  Parity. Default is `none`.
 *           //
 *         [ parity,      none
 *                      | even
 *                      | odd, ]
 *         
 *           //  Number of stop bits in frame. Default is `1`.
 *           //
 *         [ stopbits,    1 | 2, ] );
 * @endcode
 *
 * __Note__ You must connect the I/O pins to the proper UART signals using the
 * `configure` action on the I/O pin.
 */
#define _hw_mtd_hw_configure__uarta	, _hw_cfuarta
#define _hw_mtd_hwa_configure__uarta	, _hwa_cfuarta

#define _hw_cfuarta(o,i,a,k,...)					\
  do{									\
    typedef struct { uint8_t commit ; hwa_uarta_t o ; } hwa_t ;		\
    hwa_t hwa_st ; hwa_t *hwa= &hwa_st ;				\
    _hwa_setup( o );							\
    HW_Y(_hwx_cfuarta_kbps,_hw_is_bps_##k)(o,k,__VA_ARGS__,,);		\
    hwa->commit = 1 ; _hwa_commit( o );					\
  }while(0)

#define _hwa_cfuarta(o,i,a,k,...)					\
  do{ HW_Y(_hwx_cfuarta_kbps,_hw_is_bps_##k)(o,k,__VA_ARGS__,,) }while(0)

/*	Optionnal parameter `bps`
 */
#define _hwx_cfuarta_kbps_1(o,k,v,...)			\
  HW_Y(_hwx_cfuarta_vbps,v)(o,v,__VA_ARGS__)

#define _hwx_cfuarta_vbps_1(o,v,...)		HW_E_VM(bps)

#define _hwx_cfuarta_vbps_0(o,v,k,...)					\
  _hwa_write_reg(o, clkdiv, (int)(0.5 + HW_APBHZ*1.0/(v)) );		\
  HW_Y(_hwx_cfuarta_kdatabits,_hw_is_databits_##k)(o,k,__VA_ARGS__)

#define _hwx_cfuarta_kbps_0(o,k,...)					\
  HW_Y(_hwx_cfuarta_kdatabits,_hw_is_databits_##k)(o,k,__VA_ARGS__)

/*	Optionnal parameter `databits`
 */
#define _hwx_cfuarta_kdatabits_1(o,k,v,...)				\
  HW_Y(_hwx_cfuarta_vdatabits,_hw_uarta_databits_##v)(o,v,__VA_ARGS__)

#define _hwx_cfuarta_vdatabits_0(o,v,...)	HW_E_AVL(databits, v, 5 | 6 | 7 | 8)

#define _hwx_cfuarta_vdatabits_1(o,v,k,...)			\
  _hwa_write_reg(o, cbn, HW_A1(_hw_uarta_databits_##v));	\
  HW_Y(_hwx_cfuarta_kparity,_hw_is_parity_##k)(o,k,__VA_ARGS__)

#define _hwx_cfuarta_kdatabits_0(o,k,...)			\
  HW_Y(_hwx_cfuarta_kparity,_hw_is_parity_##k)(o,k,__VA_ARGS__)

#define _hw_uarta_databits_5		, 0
#define _hw_uarta_databits_6		, 1
#define _hw_uarta_databits_7		, 2
#define _hw_uarta_databits_8		, 3

/*	Optionnal parameter `parity`
 */
#define _hwx_cfuarta_kparity_1(o,k,v,...)				\
  HW_Y(_hwx_cfuarta_vparity,_hw_uarta_parity_##v)(o,v,__VA_ARGS__)

#define _hwx_cfuarta_vparity_0(o,v,...)		HW_E_AVL(parity, v, none | even | odd)

#define _hwx_cfuarta_vparity_1(o,v,k,...)				\
  _hwa_write_reg(o, cpx, HW_A1(_hw_uarta_parity_##v));			\
  HW_Y(_hwx_cfuarta_kstopbits,_hw_is_stopbits_##k)(o,k,__VA_ARGS__)

#define _hwx_cfuarta_kparity_0(o,k,...)					\
    HW_Y(_hwx_cfuarta_kstopbits,_hw_is_stopbits_##k)(o,k,__VA_ARGS__)

#define _hw_uarta_parity_none		, 0
#define _hw_uarta_parity_even		, 2
#define _hw_uarta_parity_odd		, 3

/*	Optionnal parameter `stopbits`
 */
#define _hwx_cfuarta_kstopbits_1(o,k,v,...)				\
    HW_Y(_hwx_cfuarta_vstopbits,_hw_uarta_stopbits_##v)(o,v,__VA_ARGS__)

#define _hwx_cfuarta_vstopbits_0(o,v,...)	HW_E_AVL(stopbits, v, 1 | 1_5 | 2)

#define _hwx_cfuarta_vstopbits_1(o,v,k,...)			\
  _hwa_write_reg(o, csbn, HW_A1(_hw_uarta_stopbits_##v));	\
  HW_EOL(__VA_ARGS__)

#define _hwx_cfuarta_kstopbits_0(o,k,...)	\
  HW_EOL(__VA_ARGS__)

#define _hw_uarta_stopbits_0		, 0
#define _hw_uarta_stopbits_1		, 1
#define _hw_uarta_stopbits_1_5		, 2
#define _hw_uarta_stopbits_2		, 3


/*
 * @page espressif_uarta
 * @section espressif_uarta_data Data
 *
 * The `read` returns the content of the data register but it does not
 * verify that the transmit buffer of the UART is not empty before reading
 * it. You may have to verify that a character has been received before reading
 * the data register:
 *
 * @code
 * while ( ! hw( read, HW_IRQFLAG( uart0, rxc ) ) ) {}
 * uint8_t byte = hw( read, uart0 );
 * @endcode
 */
/* #define _hw_mtd_hw_read__uarta	, _hw_rduarta */
/* #define _hw_rduarta(o,i,a,...)		HW_TX(_hw_read_reg(o,dr),__VA_ARGS__) */


/*
 * @page espressif_uarta
 *
 * The `hw_write()` instruction writes a character into the data registerbut it
 * does not verify that the transmit buffer of the UART is not full before
 * writing into it. You may have to verify this first:
 *
 * @code
 * while ( ! hw( read, HW_IRQFLAG( uart0, txqnf ) ) ) {}
 * hw_write( uart0, '#' );
 * @endcode
 */
/* #define _hw_mtd_hw_write__uarta	, _hw_wruarta */
/* #define _hw_wruarta(o,i,a,v,...)	HW_TX(_hw_write_reg(o,dr,v),__VA_ARGS__) */


/*  Power management
 */
/* #define _hw_mtd_hw_power__uarta	, _hw_power */
/* #define _hw_mtd_hwa_power__uarta	, _hwa_power */


/*
 * @page espressif_uarta
 * @section espressif_uarta_stat Status
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
/* typedef union { */
/*   uint8_t		byte ; */
/*   struct { */
/*     unsigned int __0_1 : 2 ; */
/*     unsigned int pe	  : 1 ; */
/*     unsigned int dor	  : 1 ; */
/*     unsigned int fe	  : 1 ; */
/*     unsigned int txqnf : 1 ; */
/*     unsigned int txc	  : 1 ; */
/*     unsigned int rxc	  : 1 ; */
/*   }; */
/*   struct { */
/*     unsigned int ___0_1	 : 2 ; */
/*     unsigned int parity_error : 1 ; */
/*     unsigned int overrun	 : 1 ; */
/*     unsigned int frame_error	 : 1 ; */
/*     unsigned int _txqnf	 : 1 ; */
/*     unsigned int _txc	 : 1 ; */
/*     unsigned int _rxc	 : 1 ; */
/*   }; */
/* } _hw_uarta_stat_t ; */

/* #define _hw_mtd_hw_stat_t__uarta	, _hw_sttuarta */
/* #define _hw_sttuarta(o,i,a,...)		HW_TX( _hw_uarta_stat_t, __VA_ARGS__) */

/* #define _hw_mtd_hw_stat__uarta	, _hw_stuarta */
/* #define _hw_stuarta(o,i,a,...)		HW_TX(__hw_stuarta(_hw_read_reg(o,csra)), \ */
/*					      __VA_ARGS__) */

/* HW_INLINE _hw_uarta_stat_t __hw_stuarta ( uint8_t byte ) */
/* { */
/*   _hw_uarta_stat_t	st ; */
/*   st.byte = byte ; */
/*   return st ; */
/* } */


/*******************************************************************************
 *									       *
 *	Context management						       *
 *									       *
 *******************************************************************************/

#define _hwa_setup__uarta(o,i,a)		\
  _hwa_setup_reg( o, _ie );			\
  _hwa_setup_reg( o, _ic );			\
  _hwa_setup_reg( o, _clkdiv );			\
  _hwa_setup_reg( o, _conf0 );			\
  _hwa_setup_reg( o, _conf1 )

#define _hwa_init__uarta(o,i,a)					\
  _hwa_init_reg( o, _ie,	 0 );				\
  _hwa_init_reg( o, _ic,	 0 );				\
  _hwa_init_reg( o, _clkdiv,	 0 /* 0x2B6 seems wrong */ );	\
  _hwa_init_reg( o, _conf0,   0x1C );				\
  _hwa_init_reg( o, _conf1, 0x6060 )

#define _hwa_commit__uarta(o,i,a)		\
  _hwa_commit_reg( o, _clkdiv );		\
  _hwa_commit_reg( o, _conf0 );			\
  _hwa_commit_reg( o, _conf1 );			\
  _hwa_commit_reg( o, _ic );			\
  _hwa_commit_reg( o, _ie )

/**
 * @page espressif_uarta
 * <br>
 */
