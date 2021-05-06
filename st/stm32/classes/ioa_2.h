
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


/*  The first argument 'x' is an indicator:
 *    1: hwa(...) is used to configure one single pin and can process signal remaping;
 *    0: hw(...) or multiple pins to configure -> signal remaping impossible.
 */
#define _hwa_cfioa_(x,o,p,bn,bp,k,...)		HW_BW(_hwa_cfioafn,function,k)(x,o,p,bn,bp,k,__VA_ARGS__)
#define _hwa_cfioafn0(x,o,p,bn,bp,k,...)	HW_BW(_hwa_cfioamd,mode,k)(df,o,p,bn,bp,k,__VA_ARGS__)

/*	Function
 */
#define _hwa_cfioafn1(x,o,p,bn,bp,k,v,...)	HW_BW(_hwa_cfioafn1,gpio,v)(x,o,p,bn,bp,v,__VA_ARGS__)
/*
 *		GPIO
 */
#define _hwa_cfioafn11(x,o,p,bn,bp,v,k,...)	HW_BW(_hwa_cfioamd,mode,k)(df,o,p,bn,bp,k,__VA_ARGS__)
/*
 *		Alternate
 */
#define _hwa_cfioafn10(x,o,p,bn,bp,...)		_hwa_cfioafn2##x(o,p,bn,bp,__VA_ARGS__)
/*
 *		x==0, can't set alternate function
 */
#define _hwa_cfioafn20(o,p,bn,bp,...)		HW_E(HW_EM_CANTREMAP)
/*
 *		Is function '(...)'?
 */
#define _hwa_cfioafn21(o,p,bn,bp,v,...)		HW_BP(_hwa_cfioafn3,v)(o,p,bn,bp,v,__VA_ARGS__)
/*
 *		Function is '(...)', insert expanded signal name (assume there's only 2 elements).
 */
#define _hwa_cfioafn31(o,p,bn,bp,v,...)		_hwa_cfioafn32(o,p,bn,bp,HW_G2 v,v,__VA_ARGS__)
#define _hwa_cfioafn32(...)			_hwa_cfioafn4(__VA_ARGS__)
/*
 *		Function is not '(...)', copy signal name
 */
#define _hwa_cfioafn30(o,p,bn,bp,v,...)		_hwa_cfioafn4(o,p,bn,bp,v,v,__VA_ARGS__)
/*
 *		Verify that there is a definition: _hw_af_<port_1_x>_<name>
 */
#define _hwa_cfioafn4(o,p,bn,bp,vx,v,...)	HW_B(_hwa_cfioafn4,_hw_af_##o##_##vx)(o,p,bn,bp,vx,v,__VA_ARGS__)
#define _hwa_cfioafn40(o,p,bn,bp,vx,v,...)	HW_E(HW_EM_VAL(v,function,_hw_af_##o))
/*
 *		Record association of signal to pin. Verification and processing is made at commit time.
 */
#define _hwa_cfioafn41(o,p,bn,bp,vx,v,k,...)			\
  if ( hwa->map.vx == 0 )					\
    hwa->map.vx = HW_ADDRESS((p,bn,bp));			\
  else if ( hwa->map.vx != HW_ADDRESS((p,bn,bp)) )		\
    HWA_E(HW_EM_MAP);						\
  HW_BW(_hwa_cfioamd,mode,k)(af,o,p,bn,bp,k,__VA_ARGS__)

#define _hwa_cfioamd0(f,o,p,bn,bp,k,...)	HW_E(HW_EM_AN(k,mode))

/*	Mode. Can drop 'o'.
 */
#define _hwa_cfioamd1(f,o,p,bn,bp,k,v,...)	HW_BV(_hwa_cfioamd2,cfioa_##f##_,v,)(p,bn,bp,__VA_ARGS__)//PUSH
#define _hwa_cfioamd20(v,...)	\
  HW_E(HW_EM_VAL(v,mode,(digital_input,digital_input_floating,digital_input_pullup, \
			 digital_input_pulldown,analog_input,digital_output, \
			 digital_output_pushpull, digital_output_opendrain))) HW_EAT//POP
#define _hwa_cfioamd21(v,...)			v//POP
/*
 *  Default/alternate function			, code ; branch
 */
#define _hw_cfioa_df_digital_input		, cnf=1 ; mode=0 ;         _hwa_cfioa9
#define _hw_cfioa_df_digital_input_floating	, cnf=1 ; mode=0 ;         _hwa_cfioa9
#define _hw_cfioa_df_digital_input_pullup	, cnf=2 ; mode=0 ; odr=1 ; _hwa_cfioa9
#define _hw_cfioa_df_digital_input_pulldown	, cnf=2 ; mode=0 ; odr=0 ; _hwa_cfioa9
#define _hw_cfioa_df_digital_output		, cnf=0 ; 		   _hwa_cfioafq
#define _hw_cfioa_df_digital_output_pushpull	, cnf=0 ; 		   _hwa_cfioafq
#define _hw_cfioa_df_digital_output_opendrain	, cnf=1 ; 		   _hwa_cfioafq
#define _hw_cfioa_df_analog_input		, cnf=0 ; mode=0 ;         _hwa_cfioa9

#define _hw_cfioa_af_digital_input		, cnf=1 ; mode=0 ;         _hwa_cfioa9
#define _hw_cfioa_af_digital_input_floating	, cnf=1 ; mode=0 ;         _hwa_cfioa9
#define _hw_cfioa_af_digital_input_pullup	, cnf=2 ; mode=0 ; odr=1 ; _hwa_cfioa9
#define _hw_cfioa_af_digital_input_pulldown	, cnf=2 ; mode=0 ; odr=0 ; _hwa_cfioa9
#define _hw_cfioa_af_digital_output		, cnf=2 ; 		   _hwa_cfioafq
#define _hw_cfioa_af_digital_output_pushpull	, cnf=2 ; 		   _hwa_cfioafq
#define _hw_cfioa_af_digital_output_opendrain	, cnf=3 ; 		   _hwa_cfioafq
#define _hw_cfioa_af_analog_input		, cnf=0 ; mode=0 ;         _hwa_cfioa9
/*
 *  Optionnal argument 'frequency' (only for output modes)
 */
#define _hwa_cfioafq(p,bn,bp,k,...)		HW_BW(_hwa_cfioafq,frequency,k)(p,bn,bp,k,__VA_ARGS__)

#define _hw_cfioa_fq_10MHz			, 1
#define _hw_cfioa_fq_2MHz			, 2
#define _hw_cfioa_fq_lowest			, 2
#define _hw_cfioa_fq_50MHz			, 3
#define _hw_cfioa_fq_highest			, 3

#define _hwa_cfioafq0(p,bn,bp,k,...)		HW_B(_hwa_cfioafq0,k)(p,bn,bp,k,__VA_ARGS__)
#define _hwa_cfioafq01(p,bn,bp,k,...)		mode=2 ; _hwa_do_cfioa( &hwa->p, bn, bp, cnf, mode, odr )
#define _hwa_cfioafq00(p,bn,bp,k,...)		HW_E(HW_EM_AN(k,frequency))

#define _hwa_cfioafq1(p,bn,bp,k,v,...)		HW_B(_hwa_cfioafq2,_hw_cfioa_fq_##v)(p,bn,bp,v,__VA_ARGS__)
#define _hwa_cfioafq21(p,bn,bp,v,...)		mode=HW_A1(_hw_cfioa_fq_##v); _hwa_cfioa9(p,bn,bp,__VA_ARGS__)
#define _hwa_cfioafq20(p,bn,bp,v,...)		HW_E(HW_EM_VAL(v,frequency,(lowest,2MHz,10MHz,50MHz,highest)))

#define _hwa_cfioa9(p,bn,bp,...)		HW_B(_hwa_cfioa9,__VA_ARGS__)(p,bn,bp,__VA_ARGS__)
#define _hwa_cfioa90(p,bn,bp,g,...)		HW_E(HW_EM_G(g))
#define _hwa_cfioa91(p,bn,bp,g,...)		_hwa_do_cfioa( &hwa->p, bn, bp, cnf, mode, odr )


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
