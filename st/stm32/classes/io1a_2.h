
/* This file is part of the HWA project.
 * Copyright (c) 2017 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief I/O
 */

#define hw_read__io1a		, _hw_rdio1a
#define hw_write__io1a		, _hw_wrio1a
#define hwa_write__io1a		, _hwa_wrio1a
#define hw_toggle__io1a		, _hw_tgio1a
#define hwa_toggle__io1a	, _hwa_tgio1a


/**
 * @page stm32_io1a
 * @section stm32_io1a_actions Actions
 *
 * `configure`:
 *
 * @code
 * hw | hwa( configure,   pa0,
 *
 *         [ function,    gpio                                          // Default
 *                      | signal                                        // Alternate function
 *                      | (controller,signal), ]                        // Alternate function
 *
 *           mode,        digital_input | digital_input_floating        // Default
 *                      | digital_input_pullup
 *                      | digital_input_pulldown
 *                      | analog_input
 *                      | digital_output | digital_output_pushpull
 *                      | digital_output_opendrain,
 *
 *           // Only for output modes
 *           //
 *         [ frequency,   2MHz | lowest
 *                      | 10MHz                                         // Default
 *                      | 50MHz | highest ] );
 * @endcode
 */

//  Default/alternate function			, macro selector
//
#define _hw_cfio1a_df_digital_input		, dif
#define _hw_cfio1a_df_digital_input_floating	, dif
#define _hw_cfio1a_df_digital_input_pullup	, dipu
#define _hw_cfio1a_df_digital_input_pulldown	, dipd
#define _hw_cfio1a_df_digital_output		, dopp
#define _hw_cfio1a_df_digital_output_pushpull	, dopp
#define _hw_cfio1a_df_digital_output_opendrain	, dood
#define _hw_cfio1a_df_analog_input		, ai

#define _hw_cfio1a_af_digital_input		, dif
#define _hw_cfio1a_af_digital_input_floating	, dif
#define _hw_cfio1a_af_digital_input_pullup	, dipu
#define _hw_cfio1a_af_digital_input_pulldown	, dipd
#define _hw_cfio1a_af_digital_output		, afdopp
#define _hw_cfio1a_af_digital_output_pushpull	, afdopp
#define _hw_cfio1a_af_digital_output_opendrain	, afdood
#define _hw_cfio1a_af_analog_input		, ai


/*  Check and translate a "(controller,signal)": return "controller_signal" or
 *  ', em' on error.
 */
#define HW_AF(...)		_HW_AF00(__VA_ARGS__,,)
#define _HW_AF00(o,...)		_HW_AF01( (HW_X(o)), __VA_ARGS__ )
#define _HW_AF01(...)		_HW_AF02(__VA_ARGS__)
#define _HW_AF02(o,...)		HW_Y(_HW_AF02, HW_A0 o)(o,__VA_ARGS__)
#define _HW_AF021(o,...)	, HW_A2 o // Error message
#define _HW_AF020(o,...)	_HW_AF03( HW_A1 o, __VA_ARGS__ )
#define _HW_AF03(...)		_HW_AF04(__VA_ARGS__)
#define _HW_AF04(o,r,...)	HW_Y(_HW_AF04,__VA_ARGS__)(o,r,__VA_ARGS__)
#define _HW_AF041(o,r,...)	o##_##r
#define _HW_AF040(o,r,...)	, HW_EM_GA(r)


/*  Synchronous action: create a local minimal context, apply the asynchronous
 *  action on it, and commit.
 */
#define hw_configure__io1a			, _hw_cfio1a
#define _hw_cfio1a(o,i,p,...)						\
  do {									\
    uint8_t cnf, mode, odr=0 ;						\
    struct { uint8_t commit ; hwa_p16a_t p ; hwa_afioa_t afio ; } hwa_st ; \
    hwa_t *hwa = (hwa_t*)&hwa_st ;					\
    _hwa_setup_o(p);							\
    _hwa_cfio1a_(o,i,p,__VA_ARGS__);					\
    hwa_st.commit = 1 ; _hwa_commit_o(p);				\
  }while(0)

#define hwa_configure__io1a			, _hwa_cfio1a
#define _hwa_cfio1a(...)			do{ uint8_t cnf, mode, odr=0 ; _hwa_cfio1a_(__VA_ARGS__); }while(0)

/*  Key 'function'. Select default or alternate function (df/af). Register signal-pin association for 'af'.
 */
#define _hwa_cfio1a_(o,i,p,bn,bp,k,...)		HW_Y(_hwa_cfio1a_kfn,_hw_is_function_##k)(o,p,bn,bp,k,__VA_ARGS__)
#define _hwa_cfio1a_kfn1(o,p,bn,bp,k,v,...)	HW_Y(_hwa_cfio1a_vfb,_hw_isa_leftbkt v)(o,p,bn,bp,v,__VA_ARGS__)
#define _hwa_cfio1a_vfb0(o,p,bn,bp,v,...)	_hwa_cfio1a_vfn4(_hw_fn_##o##_##v,v,v,o,p,bn,bp,__VA_ARGS__)
#define _hwa_cfio1a_vfb1(o,p,bn,bp,v,...)	_hwa_cfio1a_vfb2( HW_AF v,v,o,p,bn,bp,__VA_ARGS__)
#define _hwa_cfio1a_vfb2(...)			_hwa_cfio1a_vfb3(__VA_ARGS__)
#define _hwa_cfio1a_vfb3(x,...)			HW_Y0(_hwa_cfio1a_vfb3,x)(x,__VA_ARGS__)
#define _hwa_cfio1a_vfb31(z,e,...)		HW_E(e)
#define _hwa_cfio1a_vfb30(x,v,o,...)		_hwa_cfio1a_vfn4(_hw_fn_##o##_##x,x,v,o,__VA_ARGS__)
#define _hwa_cfio1a_vfn4(...)			_hwa_cfio1a_vfn5(__VA_ARGS__)
#define _hwa_cfio1a_vfn5(x,...)			HW_Y(_hwa_cfio1a_vfn5,x)(x,__VA_ARGS__)
#define _hwa_cfio1a_vfn50(x,f,v,o,...)		HW_E_NIL(v,_hw_fn_##o)
#define _hwa_cfio1a_vfn51(z,f,...)		_hwa_cfio1a_vfn52_##f(__VA_ARGS__)
#define _hwa_cfio1a_vfn52_df(sig,v,o,...)	_hwa_cfio1a_vfn53(df,__VA_ARGS__)
#define _hwa_cfio1a_vfn52_af(sig,v,o,...)	hwa->afio.map.sig = HW_IDX(o); _hwa_cfio1a_vfn53(af,__VA_ARGS__)
#define _hwa_cfio1a_vfn53(f,p,bn,bp,k,...)	HW_Y(_hwa_cfio1a_kmd,_hw_is_mode_##k)(f,p,bn,bp,k,__VA_ARGS__)
#define _hwa_cfio1a_kfn0(o,p,bn,bp,k,...)	HW_Y(_hwa_cfio1a_kmd,_hw_is_mode_##k)(df,p,bn,bp,k,__VA_ARGS__)

/*  Key 'mode'
 */
#define _hwa_cfio1a_kmd0(f,p,bn,bp,k,v,...)	HW_E_K(mode,k)
#define _hwa_cfio1a_kmd1(f,p,bn,bp,k,v,...)	HW_Y(_hwa_cfio1a_vmd,_hw_cfio1a_##f##_##v)(f,p,bn,bp,v,__VA_ARGS__)
#define _hwa_cfio1a_vmd0(f,p,bn,bp,v,...)	HW_E_NIL(v, (digital_input,digital_input_floating,digital_input_pullup,\
							     digital_input_pulldown,analog_input,digital_output,\
							     digital_output_pushpull, digital_output_opendrain))
#define _hwa_cfio1a_vmd1(f,p,bn,bp,v,...)	HW_G2(_hwa_cfio1a,HW_A1(_hw_cfio1a_##f##_##v))(p,bn,bp,__VA_ARGS__)

#define _hwa_cfio1a_dif(p,bn,bp,...)		cnf=1 ; mode=0 ; _hwa_cfio1a9(p,bn,bp,__VA_ARGS__)
#define _hwa_cfio1a_dipu(p,bn,bp,...)		cnf=2 ; mode=0 ; odr=1 ; _hwa_cfio1a9(p,bn,bp,__VA_ARGS__)
#define _hwa_cfio1a_dipd(p,bn,bp,...)		cnf=2 ; mode=0 ; odr=0 ; _hwa_cfio1a9(p,bn,bp,__VA_ARGS__)
#define _hwa_cfio1a_ai(p,bn,bp,...)		cnf=0 ; mode=0 ; _hwa_cfio1a9(p,bn,bp,__VA_ARGS__)
#define _hwa_cfio1a_dopp(p,bn,bp,k,...)		cnf=0 ; HW_Y(_hwa_cfio1a_kfq_,_hw_is_frequency_##k)(p,bn,bp,k,__VA_ARGS__)
#define _hwa_cfio1a_dood(p,bn,bp,k,...)		cnf=1 ; HW_Y(_hwa_cfio1a_kfq_,_hw_is_frequency_##k)(p,bn,bp,k,__VA_ARGS__)
#define _hwa_cfio1a_afdopp(p,bn,bp,k,...)	cnf=2 ; HW_Y(_hwa_cfio1a_kfq_,_hw_is_frequency_##k)(p,bn,bp,k,__VA_ARGS__)
#define _hwa_cfio1a_afdood(p,bn,bp,k,...)	cnf=3 ; HW_Y(_hwa_cfio1a_kfq_,_hw_is_frequency_##k)(p,bn,bp,k,__VA_ARGS__)

/*  Key 'frequency' (only for output modes)
 */
#define _hw_cfio1a_fq_10MHz			, 1
#define _hw_cfio1a_fq_2MHz			, 2
#define _hw_cfio1a_fq_lowest			, 2
#define _hw_cfio1a_fq_50MHz			, 3
#define _hw_cfio1a_fq_highest			, 3

#define _hwa_cfio1a_kfq_0(p,bn,bp,k,...)	HW_Y(_hwa_cfio1a_kfq0_,k)(p,bn,bp,k,__VA_ARGS__)
#define _hwa_cfio1a_kfq0_1(p,bn,bp,k,...)	mode=2 ; _hwa_do_cfio1a( &hwa->p, bn, bp, cnf, mode, odr )
#define _hwa_cfio1a_kfq0_0(p,bn,bp,k,...)	HW_E_K(frequency,k)

#define _hwa_cfio1a_kfq_1(p,bn,bp,k,v,...)	HW_Y(_hwa_cfio1a_vfq_,_hw_cfio1a_fq_##v)(p,bn,bp,v,__VA_ARGS__)
#define _hwa_cfio1a_vfq_1(p,bn,bp,v,...)	mode=HW_A1(_hw_cfio1a_fq_##v); _hwa_cfio1a9(p,bn,bp,__VA_ARGS__)
#define _hwa_cfio1a_vfq_0(p,bn,bp,v,...)	HW_E_NIL(v,(2MHz,10MHz,50MHz))

#define _hwa_cfio1a9(p,bn,bp,...)		HW_Y(_hwa_cfio1a9_,__VA_ARGS__)(p,bn,bp,__VA_ARGS__)
#define _hwa_cfio1a9_0(p,bn,bp,g,...)		HW_E_G(g)
#define _hwa_cfio1a9_1(p,bn,bp,g,...)		_hwa_do_cfio1a( &hwa->p, bn, bp, cnf, mode, odr )


HW_INLINE void _hwa_do_cfio1a_( uint8_t i, hwa_p16a_t *p, uint8_t cnf, uint8_t mode, uint8_t odr )
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


HW_INLINE void _hwa_do_cfio1a( hwa_p16a_t *p, uint8_t bn, uint8_t bp, uint8_t cnf, uint8_t mode, uint8_t odr )
{
  uint16_t mask = ((1UL<<bn)-1)<<bp ;
  if ( mask & 0x0001 ) _hwa_do_cfio1a_( 0,p,cnf,mode,odr);
  if ( mask & 0x0002 ) _hwa_do_cfio1a_( 1,p,cnf,mode,odr);
  if ( mask & 0x0004 ) _hwa_do_cfio1a_( 2,p,cnf,mode,odr);
  if ( mask & 0x0008 ) _hwa_do_cfio1a_( 3,p,cnf,mode,odr);
  if ( mask & 0x0010 ) _hwa_do_cfio1a_( 4,p,cnf,mode,odr);
  if ( mask & 0x0020 ) _hwa_do_cfio1a_( 5,p,cnf,mode,odr);
  if ( mask & 0x0040 ) _hwa_do_cfio1a_( 6,p,cnf,mode,odr);
  if ( mask & 0x0080 ) _hwa_do_cfio1a_( 7,p,cnf,mode,odr);
  if ( mask & 0x0100 ) _hwa_do_cfio1a_( 8,p,cnf,mode,odr);
  if ( mask & 0x0200 ) _hwa_do_cfio1a_( 9,p,cnf,mode,odr);
  if ( mask & 0x0400 ) _hwa_do_cfio1a_(10,p,cnf,mode,odr);
  if ( mask & 0x0800 ) _hwa_do_cfio1a_(11,p,cnf,mode,odr);
  if ( mask & 0x1000 ) _hwa_do_cfio1a_(12,p,cnf,mode,odr);
  if ( mask & 0x2000 ) _hwa_do_cfio1a_(13,p,cnf,mode,odr);
  if ( mask & 0x4000 ) _hwa_do_cfio1a_(14,p,cnf,mode,odr);
  if ( mask & 0x8000 ) _hwa_do_cfio1a_(15,p,cnf,mode,odr);
}



/**
 * @page stm32_io1a
 * <br>
 * `read`:
 * @code
 * uint8_t value = hw( read, pa0 );
 * @endcode
 */
#define _hw_rdio1a(o,i,p,bn,bp,...)	HW_Y(_hw_rdio1a_,__VA_ARGS__)(p,bn,bp,__VA_ARGS__,)
#define _hw_rdio1a_0(p,bn,bp,g,...)	HW_E_G(g)
#define _hw_rdio1a_1(p,bn,bp,...)	( (_hw_read(p,idr) & ((1UL<<bn)-1)) >> bp )


/**
 * @page stm32_io1a
 * <br>
 * `write`:
 * @code
 * hw | hwa( write, pa0, 0 );
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
 *        LSB16 bits set the ODR bits, it has the priority over MSB16
 */
#define _hw_wrio1a(o,i,p,bn,bp,v,g,...)		HW_Y(_hwx_wrio1a1_,v)(_hw,p,bn,bp,v,g)
#define _hwa_wrio1a(o,i,p,bn,bp,v,g,...)	HW_Y(_hwx_wrio1a1_,v)(_hwa,p,bn,bp,v,g)
#define _hwx_wrio1a1_1(x,p,bn,bp,v,g)		HW_E_V()
#define _hwx_wrio1a1_0(x,p,bn,bp,v,g)		HW_Y(_hwx_wrio1a2_,g)(x,p,bn,bp,v,g)
#define _hwx_wrio1a2_0(x,p,bn,bp,v,g)		HW_E_G(g)
#define _hwx_wrio1a2_1(x,p,bn,bp,v,g)					\
  { uint32_t v32 = (v); /* v could be volatile, boolean expr... */	\
    x##_write_m( p, bsrr, 0xffffffff,					\
		 ((((1UL<<bn)-1)<<bp) & (~v32)<<bp)<<16 |		\
		 ((((1UL<<bn)-1)<<bp) & ( v32)<<bp) ); }


/**
 * @page stm32_io1a
 *
 * `toggle`: toggles one or several consecutive pins at once.
 *
 * @note `toggle` is not atomic: it reads the ODR, then sets/resets the relevant
 * bits through the BSRR. The ODR is not written directly.
 *
 * @code
 * hw( toggle, pa0 );
 * @endcode
 */
/*  Use the BSRR instead of a read-modify-write on the ODR.
 */
#define _hw_tgio1a(o,i,p,bn,bp,g,...)		HW_Y(_hw_tgio1a_,g)(p,bn,bp,g)
#define _hw_tgio1a_0(p,bn,bp,g)			HW_E_G(g)
#define _hw_tgio1a_1(p,bn,bp,g)						\
  do {									\
    uint32_t v = *(volatile uint32_t*)(HW_ADDRESS((p,odr)));		\
    *(volatile uint32_t*)(HW_ADDRESS((p,bsrr))) =			\
      ((((1UL<<bn)-1)<<bp) & v)<<16 | ((((1UL<<bn)-1)<<bp) & ~v);	\
  }while(0)

/**
 * @page stm32_io1a
 *
 * @code
 * hwa( toggle, pa0 );     //  Register pa0 for toggling
 * hwa( toggle, pa4 );     //  Register pa4 for toggling
 * hwa( commit );          //  Toggle all registered pins at once
 * @endcode
 */
#define _hwa_tgio1a(o,i,p,bn,bp,g,...)		HW_Y(_hwa_tgio1a_,g)(p,bn,bp,g)
#define _hwa_tgio1a_0(p,bn,bp,g)		HW_E_G(g)
#define _hwa_tgio1a_1(p,bn,bp,g)		hwa->p.toggles |= (((1UL<<bn)-1) << bp)
