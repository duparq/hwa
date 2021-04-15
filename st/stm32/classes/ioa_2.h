
/* This file is part of the HWA project.
 * Copyright (c) 2017 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief I/O
 */

#define hw_read__ioa			, _hw_rdioa
#define hw_write__ioa			, _hw_wrioa
#define hwa_write__ioa			, _hwa_wrioa
#define hw_toggle__ioa			, _hw_tgioa
#define hwa_toggle__ioa			, _hwa_tgioa

#define hw_actions__ioa			, (configure,read,toggle,write)
#define hwa_actions__ioa		, (configure,toggle,write)

/**
 * @ingroup stm32_classes
 * @addtogroup stm32_ioa
 * @section stm32_ioaact Actions
 *
 * <br><br>hw( configure, ... ) configures one set of consecutive pins in the
 * same port assuming the `gpio` function:
 *
 * @code
 * hw( configure,   (porta,0),
 *
 *   [ function,    gpio, ]					// Default
 *
 *     mode,	    digital_input | digital_input_floating	// Default
 *		  | digital_input_pullup
 *		  | digital_input_pulldown
 *		  | analog_input
 *		  | digital_output | digital_output_pushpull
 *		  | digital_output_opendrain,
 *
 *     // Only for output modes
 *     //
 *   [ frequency,   2MHz | lowest
 *		  | 10MHz					// Default
 *		  | 50MHz | highest ]
 * );
 * @endcode
 *
 * <br><br>hwa( configure, ... ) configures one set of consecutive pins in the
 * same port, can set alternate function (remapping):
 *
 * @code
 * hwa( configure,   (porta,0),
 *
 *    [ function,    gpio					// Default
 *		   | (controller,...), ]			// Alternate function
 *
 *	mode,	     digital_input | digital_input_floating	// Default
 *		   | digital_input_pullup
 *		   | digital_input_pulldown
 *		   | analog_input
 *		   | digital_output | digital_output_pushpull
 *		   | digital_output_opendrain,
 *
 *	// Only for output modes
 *	//
 *    [ frequency,   2MHz | lowest
 *		   | 10MHz					// Default
 *		   | 50MHz | highest ]
 * );
 * @endcode
 *
 * @note You can not map one signal to multiple pins.
 */


/*  Immediate action: create a local minimal context, apply the actions for each
 *  pin on it, and commit. Do not handle signal remapping.
 */
#define hw_configure__ioa			, _hw_cfioa
#define _hw_cfioa(o,p,...)						\
  do {									\
    uint8_t __attribute__((unused)) cnf, mode, odr=0 ;			\
    struct { uint8_t commit ; hwa_gpa_t p ; hwa_afioa_t afio ; } hwa_st ; \
    hwa_t *hwa = (hwa_t*)&hwa_st ;					\
    _hwa_setup_o(p);							\
    _hwa_cfioa_(0,o,p,__VA_ARGS__,);					\
    hwa_st.commit = 1 ; _hwa_commit_o(p);				\
  }while(0)

/*  Transaction. Handle signals remapping.
 *    TODO: verify how errors are triggered at different levels of parsing
 */
#define hwa_configure__ioa			, _hwa_cfioa
#define _hwa_cfioa(o,p,bn,...)			_HW_B(_hwa_cfioa,_hw_is_1_##bn)(o,p,bn,__VA_ARGS__,)
#define _hwa_cfioa0(...)			do{ uint8_t cnf, mode, odr=0 ; _hwa_cfioa_(0,__VA_ARGS__); }while(0)
#define _hwa_cfioa1(o,p,bn,bp,...)			\
  do{							\
    uint8_t __attribute__((unused)) cnf, mode, odr=0 ;	\
    _hwa_cfioa_(1,o,p,bn,bp,__VA_ARGS__);		\
    if ( hwa->map.error )				\
      HWA_E(HW_EM_PMAP((o,bp)));			\
  }while(0)


/*  The first argument 'x' is an indicator that can be 0 or 1, telling that
 *  hwa() is used to configure one single pin and can process signal remaping.
 */
#define _hwa_cfioa_(x,o,p,bn,bp,k,...)		HW_BW(_hwa_cfioa_kfn,function,k)(x,(o,p,bn,bp),k,__VA_ARGS__)

/*  Optionnal argument 'function'. Select default or alternate function (df/af). Register signal-pin association for 'af'.
 */
#define _hwa_cfioa_kfn1(x,va,k,v,...)		HW_B(_hwa_cfioa_vfn,_hw_par v)(x,va,v,__VA_ARGS__)
/*
 *    Value is not a (). Must be 'gpio'. Can drop the indicator 'x'. Indicate default function with 'df'
 */
#define _hwa_cfioa_vfn0(x,va,v,...)		HW_BW(_hwa_cfioa_vfn0,gpio,v)(va,v,__VA_ARGS__)
#define _hwa_cfioa_vfn00(va,v,...)		HW_E(HW_EM_VAL(v,function,(gpio,(controller,signal))))
#define _hwa_cfioa_vfn01(va,v,k,...)		HW_BW(_hwa_cfioa_kmd,mode,k)(df,HW_RP va,k,__VA_ARGS__)
/*
 *    Value is a (). Verify that indicator 'x' is 1 before trying to process signal mapping.
 */
#define _hwa_cfioa_vfn1(x,va,...)		_hwa_cfioa_vfn1##x(va,__VA_ARGS__)
#define _hwa_cfioa_vfn10(...)			HW_E(HW_EM_1)
/*
 *	OK, get the signal name.
 */
#define _hwa_cfioa_vfn11(va,v,...)		_hwa_cfioa_vfn2(va,(__VA_ARGS__),v,HW_X(v))
#define _hwa_cfioa_vfn2(...)			_hwa_cfioa_vfn3(__VA_ARGS__)
#define _hwa_cfioa_vfn3(va1,va2,v,c,...)	_HW_B(_hwa_cfioa_vfn3,c)(va1,va2,v,c,__VA_ARGS__)
#define _hwa_cfioa_vfn31(va1,va2,v,...)		HW_E(HW_Q(v) is not a signal)
/*
 *	Record association of signal to pin. Verification and processing is made by commit.
 */
#define _hwa_cfioa_vfn30(va1,va2,v,c,n,...)	_hwa_cfioa_vfn32(HW_RP va1,v,n,HW_RP va2)
#define _hwa_cfioa_vfn32(...)			_hwa_cfioa_vfn33(__VA_ARGS__)
#define _hwa_cfioa_vfn33(o,p,bn,bp,v,n,k,...)	HW_B(_hwa_cfioa_vfn33,_hw_af_##o##_##n)(o,p,bn,bp,v,n,k,__VA_ARGS__)
#define _hwa_cfioa_vfn330(o,p,bn,bp,v,n,k,...)	HW_E(HW_EM_VAL(v,function,_hw_af_##o))
  
#define _hwa_cfioa_vfn331(o,p,bn,bp,v,n,k,...)			\
  if ( hwa->map.n == 0 )					\
    hwa->map.n = HW_ADDRESS((p,bn,bp));				\
  else if ( hwa->map.n != HW_ADDRESS((p,bn,bp)) )		\
    HWA_E(HW_EM_PMAP((p,bp)));					\
  HW_BW(_hwa_cfioa_kmd,mode,k)(af,o,p,bn,bp,k,__VA_ARGS__)

#define _hwa_cfioa_kfn0(x,va,...)		_hwa_cfioa_kfn2(HW_RP va,__VA_ARGS__)
#define _hwa_cfioa_kfn2(...)			_hwa_cfioa_kfn3(__VA_ARGS__)
#define _hwa_cfioa_kfn3(o,p,bn,bp,k,...)	HW_BW(_hwa_cfioa_kmd,mode,k)(df,o,p,bn,bp,k,__VA_ARGS__)
/*
 *  Mandatory argument 'mode'. Can drop 'o'.
 */
#define _hwa_cfioa_kmd0(f,o,p,bn,bp,k,v,...)	HW_E(HW_EM_AN(k,mode))

#define _hwa_cfioa_kmd1(...)			_hwa_cfioa_kmd2(__VA_ARGS__)
#define _hwa_cfioa_kmd2(f,o,p,bn,bp,k,v,...)	_HW_B(_hwa_cfioa_vmd,_hw_cfioa_##f##_##v)(f,p,bn,bp,v,__VA_ARGS__)
#define _hwa_cfioa_vmd0(f,p,bn,bp,v,...)	\
  HW_E(HW_EM_VAL(v,mode,(digital_input,digital_input_floating,digital_input_pullup, \
			 digital_input_pulldown,analog_input,digital_output, \
			 digital_output_pushpull, digital_output_opendrain)))
#define _hwa_cfioa_vmd1(f,p,bn,bp,v,...)	HW_G2(_hwa_cfioa,HW_A1(_hw_cfioa_##f##_##v))(p,bn,bp,__VA_ARGS__)
/*
 *  Default/alternate function			, branch
 */
#define _hw_cfioa_df_digital_input		, dif
#define _hw_cfioa_df_digital_input_floating	, dif
#define _hw_cfioa_df_digital_input_pullup	, dipu
#define _hw_cfioa_df_digital_input_pulldown	, dipd
#define _hw_cfioa_df_digital_output		, dopp
#define _hw_cfioa_df_digital_output_pushpull	, dopp
#define _hw_cfioa_df_digital_output_opendrain	, dood
#define _hw_cfioa_df_analog_input		, ai

#define _hw_cfioa_af_digital_input		, dif
#define _hw_cfioa_af_digital_input_floating	, dif
#define _hw_cfioa_af_digital_input_pullup	, dipu
#define _hw_cfioa_af_digital_input_pulldown	, dipd
#define _hw_cfioa_af_digital_output		, afdopp
#define _hw_cfioa_af_digital_output_pushpull	, afdopp
#define _hw_cfioa_af_digital_output_opendrain	, afdood
#define _hw_cfioa_af_analog_input		, ai

#define _hwa_cfioa_dif(p,bn,bp,...)		cnf=1 ; mode=0 ; _hwa_cfioa9(p,bn,bp,__VA_ARGS__)
#define _hwa_cfioa_dipu(p,bn,bp,...)		cnf=2 ; mode=0 ; odr=1 ; _hwa_cfioa9(p,bn,bp,__VA_ARGS__)
#define _hwa_cfioa_dipd(p,bn,bp,...)		cnf=2 ; mode=0 ; odr=0 ; _hwa_cfioa9(p,bn,bp,__VA_ARGS__)
#define _hwa_cfioa_ai(p,bn,bp,...)		cnf=0 ; mode=0 ; _hwa_cfioa9(p,bn,bp,__VA_ARGS__)
#define _hwa_cfioa_dopp(p,bn,bp,k,...)		cnf=0 ; HW_BW(_hwa_cfioa_kfq_,frequency,k)(p,bn,bp,k,__VA_ARGS__)
#define _hwa_cfioa_dood(p,bn,bp,k,...)		cnf=1 ; HW_BW(_hwa_cfioa_kfq_,frequency,k)(p,bn,bp,k,__VA_ARGS__)
#define _hwa_cfioa_afdopp(p,bn,bp,k,...)	cnf=2 ; HW_BW(_hwa_cfioa_kfq_,frequency,k)(p,bn,bp,k,__VA_ARGS__)
#define _hwa_cfioa_afdood(p,bn,bp,k,...)	cnf=3 ; HW_BW(_hwa_cfioa_kfq_,frequency,k)(p,bn,bp,k,__VA_ARGS__)
/*
 *  Optionnal argument 'frequency' (only for output modes)
 */
#define _hw_cfioa_fq_10MHz			, 1
#define _hw_cfioa_fq_2MHz			, 2
#define _hw_cfioa_fq_lowest			, 2
#define _hw_cfioa_fq_50MHz			, 3
#define _hw_cfioa_fq_highest			, 3

#define _hwa_cfioa_kfq_0(p,bn,bp,k,...)		HW_B(_hwa_cfioa_kfq0_,k)(p,bn,bp,k,__VA_ARGS__)
#define _hwa_cfioa_kfq0_1(p,bn,bp,k,...)	mode=2 ; _hwa_do_cfioa( &hwa->p, bn, bp, cnf, mode, odr )
#define _hwa_cfioa_kfq0_0(p,bn,bp,k,...)	HW_E(HW_EM_AN(k,frequency))

#define _hwa_cfioa_kfq_1(p,bn,bp,k,v,...)	HW_B(_hwa_cfioa_vfq_,_hw_cfioa_fq_##v)(p,bn,bp,v,__VA_ARGS__)
#define _hwa_cfioa_vfq_1(p,bn,bp,v,...)		mode=HW_A1(_hw_cfioa_fq_##v); _hwa_cfioa9(p,bn,bp,__VA_ARGS__)
#define _hwa_cfioa_vfq_0(p,bn,bp,v,...)		HW_E(HW_EM_VAL(v,frequency,(lowest,2MHz,10MHz,50MHz,highest)))

#define _hwa_cfioa9(p,bn,bp,...)		HW_B(_hwa_cfioa9_,__VA_ARGS__)(p,bn,bp,__VA_ARGS__)
#define _hwa_cfioa9_0(p,bn,bp,g,...)		HW_E(HW_EM_G(g))
#define _hwa_cfioa9_1(p,bn,bp,g,...)		_hwa_do_cfioa( &hwa->p, bn, bp, cnf, mode, odr )


HW_INLINE void _hwa_do_cfioa_( uint8_t i, hwa_gpa_t *p, uint8_t cnf, uint8_t mode, uint8_t odr )
{
  uint32_t m, v ;

  /*  Pull-up & pull-down are driven by the ODR
   */
  if ( cnf==2 && mode==0 ) {
    if ( odr == 0 )
      m = 1UL<<(i+16) ;
    else
      m = 1UL<<i ;
    p->bsrr.mmask |= m ;
    p->bsrr.mvalue |= m ;
  }

  v = (cnf<<2)|mode ;

  if ( i < 8 ) {
    i *= 4 ;
    m = 0x0FUL << i ;
    v = v << i ;
    p->crl.mmask |= m ;
    p->crl.mvalue = (p->crl.mvalue & ~m) | (m & v) ;
  }
  else {
    i -= 8 ;
    i *= 4 ;
    m = 0x0FUL << i ;
    v = v << i ;
    p->crh.mmask |= m ;
    p->crh.mvalue = (p->crh.mvalue & ~m) | (m & v) ;
  }
}


HW_INLINE void _hwa_do_cfioa( hwa_gpa_t *p, uint8_t bn, uint8_t bp, uint8_t cnf, uint8_t mode, uint8_t odr )
{
  uint16_t mask = ((1UL<<bn)-1)<<bp ;
  if ( mask & 0x0001 ) _hwa_do_cfioa_( 0,p,cnf,mode,odr);
  if ( mask & 0x0002 ) _hwa_do_cfioa_( 1,p,cnf,mode,odr);
  if ( mask & 0x0004 ) _hwa_do_cfioa_( 2,p,cnf,mode,odr);
  if ( mask & 0x0008 ) _hwa_do_cfioa_( 3,p,cnf,mode,odr);
  if ( mask & 0x0010 ) _hwa_do_cfioa_( 4,p,cnf,mode,odr);
  if ( mask & 0x0020 ) _hwa_do_cfioa_( 5,p,cnf,mode,odr);
  if ( mask & 0x0040 ) _hwa_do_cfioa_( 6,p,cnf,mode,odr);
  if ( mask & 0x0080 ) _hwa_do_cfioa_( 7,p,cnf,mode,odr);
  if ( mask & 0x0100 ) _hwa_do_cfioa_( 8,p,cnf,mode,odr);
  if ( mask & 0x0200 ) _hwa_do_cfioa_( 9,p,cnf,mode,odr);
  if ( mask & 0x0400 ) _hwa_do_cfioa_(10,p,cnf,mode,odr);
  if ( mask & 0x0800 ) _hwa_do_cfioa_(11,p,cnf,mode,odr);
  if ( mask & 0x1000 ) _hwa_do_cfioa_(12,p,cnf,mode,odr);
  if ( mask & 0x2000 ) _hwa_do_cfioa_(13,p,cnf,mode,odr);
  if ( mask & 0x4000 ) _hwa_do_cfioa_(14,p,cnf,mode,odr);
  if ( mask & 0x8000 ) _hwa_do_cfioa_(15,p,cnf,mode,odr);
}



/**
 * @addtogroup stm32_ioa
 * <br>
 * `read`:
 * @code
 * uint8_t value = hw( read, (porta,0) );
 * @endcode
 */
#define _hw_rdioa(o,p,bn,bp,...)	HW_B(_hw_rdioa_,__VA_ARGS__)(p,bn,bp,__VA_ARGS__,)
#define _hw_rdioa_0(p,bn,bp,g,...)	HW_E(HW_EM_G(g))
#define _hw_rdioa_1(p,bn,bp,...)	( (_hw_read(p,idr) & ((1UL<<bn)-1)) >> bp )


/**
 * @addtogroup stm32_ioa
 * <br>
 * `write`:
 * @code
 * hw | hwa( write, (porta,0), 0 );
 * @endcode
 *
 * @note HWA does not write the ODR of the port. It writes the BSRR so that
 * atomicity is guaranted and concurrent tasks can write different pins of the
 * port without conflict.
 */
/*  Writing pins can be done two ways:
 *   * writing the ODR
 *   * writing the BSRR (or BRR)
 *
 *  Writing the BSRR allows atomic writing of the ODR's bits without leading to
 *  a heavier binary code. So, let's use that!
 *
 *  BSRR: MSB16 bits reset the ODR bits
 *	  LSB16 bits set the ODR bits, it has the priority over MSB16
 */
#define _hw_wrioa(o,p,bn,bp,v,g,...)		HW_B(_hwx_wrioa1_,v)(_hw,p,bn,bp,v,g)
#define _hwa_wrioa(o,p,bn,bp,v,g,...)		HW_B(_hwx_wrioa1_,v)(_hwa,p,bn,bp,v,g)
#define _hwx_wrioa1_1(x,p,bn,bp,v,g)		HW_E(HW_EM_V)
#define _hwx_wrioa1_0(x,p,bn,bp,v,g)		HW_B(_hwx_wrioa2_,g)(x,p,bn,bp,v,g)
#define _hwx_wrioa2_0(x,p,bn,bp,v,g)		HW_E(HW_EM_G(g))
#define _hwx_wrioa2_1(x,p,bn,bp,v,g)					\
  { uint32_t v32 = (v); /* v could be volatile, boolean expr... */	\
    x##_write_m( p, bsrr, 0xffffffff,					\
		 ((((1UL<<bn)-1)<<bp) & (~v32)<<bp)<<16 |		\
		 ((((1UL<<bn)-1)<<bp) & ( v32)<<bp) ); }


/**
 * @addtogroup stm32_ioa
 *
 * `toggle`: toggles one or several consecutive pins at once.
 *
 * @note `toggle` is not atomic: it reads the ODR, then sets/resets the relevant
 * bits through the BSRR. The ODR is not written directly.
 *
 * @code
 * hw( toggle, (porta,0) );
 * @endcode
 */
/*  Use the BSRR instead of a read-modify-write on the ODR.
 */
#define _hw_tgioa(o,p,bn,bp,g,...)		HW_B(_hw_tgioa_,g)(p,bn,bp,g)
#define _hw_tgioa_0(p,bn,bp,g)			HW_E(HW_EM_G(g))
#define _hw_tgioa_1(p,bn,bp,g)						\
    do {								\
    uint32_t v = _hw_read(p,odr);					\
    if ( bn==1 ) {							\
      _hw_write( p, bsrr, v<<16 | ~v );					\
    }									\
    else {								\
      uint32_t mask = ((1UL<<bn)-1)<<bp ;				\
      _hw_write( p, bsrr, (v&mask)<<16 | (~v&mask) );			\
    }									\
  }while(0)


/**
 * @addtogroup stm32_ioa
 *
 * @code
 * hwa( toggle, (porta,0) );	   //  Register PA0 for toggling
 * hwa( toggle, (porta,4) );	   //  Register PA4 for toggling
 * hwa( commit );		   //  Toggle PA0 and PA4 at once
 * @endcode
 */
#define _hwa_tgioa(o,p,bn,bp,g,...)	HW_B(_hwa_tgioa_,g)(p,bn,bp,g)
#define _hwa_tgioa_0(p,bn,bp,g)		HW_E(HW_EM_G(g))
#define _hwa_tgioa_1(p,bn,bp,g)		hwa->p.toggles |= (((1UL<<bn)-1) << bp)
