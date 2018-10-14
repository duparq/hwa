
/* This file is part of the HWA project.
 * Copyright (c) 2017 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief I/O
 */

#define _hw_mtd_hw_configure__io1a	, _hw_cfio1a
#define _hw_mtd_hwa_configure__io1a	, _hwa_cfio1a
#define _hw_mtd_hw_read__io1a		, _hw_rdio1a
#define _hw_mtd_hw_write__io1a		, _hw_wrio1a
#define _hw_mtd_hwa_write__io1a		, _hwa_wrio1a
#define _hw_mtd_hw_toggle__io1a		, _hw_tgio1a
#define _hw_mtd_hwa_toggle__io1a	, _hwa_tgio1a


/**
 * @page stm32_io1a
 * @section Actions
 *
 * `configure`:
 *
 * @code
 * hw | hwa( configure,   pa0,
 *
 *         [ function,    gpio, ]                                       // Default
 *
 *           mode,        digital_input | digital_input_floating
 *                      | digital_input_pullup
 *                      | digital_input_pulldown
 *                      | digital_output | digital_output_pushpull
 *                      | digital_output_opendrain
 *                      | analog_input,
 *
 *         [ frequency,   2MHz | lowest
 *                      | 10MHz                                         // Default
 *                      | 50MHz | highest ] );
 * @endcode
 * <br>
 * @code
 * //  THIS IS NOT IMPLEMENTED YET
 *
 * //  ALTERNATE_FUNCTION is a signal name, such as `int0` or `(uart0,tx)`.
 * //
 * hw | hwa( configure,   pa0,
 *
 *           function,    ALTERNATE_FUNCTION );
 * @endcode
 * <br>
 */

/*  See also esp8266.h for pin functions
 */

#define _hw_cfio1a_md_digital_input		, dif
#define _hw_cfio1a_md_digital_input_floating	, dif
#define _hw_cfio1a_md_digital_input_pullup	, dipu
#define _hw_cfio1a_md_digital_input_pulldown	, dipd
#define _hw_cfio1a_md_digital_output		, dopp
#define _hw_cfio1a_md_digital_output_pushpull	, dopp
#define _hw_cfio1a_md_digital_output_opendrain	, dood
#define _hw_cfio1a_md_analog_input		, ai


/*  Create a local minimal context, apply the asynchronous action on it, and
 *  commit.
 */
#define _hw_cfio1a(o,i,p,...)				\
  do {							\
    uint8_t cnf, mode, odr=0 ;				\
    struct { uint8_t commit ; hwa_p16a_t p ; } st ;	\
    hwa_t *hwa = (hwa_t*)&st ;				\
    _hwa_setup(p);					\
    _hwa_cfio1a_(o,i,p,__VA_ARGS__);			\
    st.commit = 1 ; _hwa_commit(p);			\
  }while(0)

#define _hwa_cfio1a(...)			do{ uint8_t cnf, mode, odr=0 ; _hwa_cfio1a_(__VA_ARGS__); }while(0);

/*  Key 'function'
 */
#define _hwa_cfio1a_(o,i,p,bn,bp,k,...)		HW_Y(_hwa_cfio1a_kfn,_hw_is_function_##k)(o,p,bn,bp,k,__VA_ARGS__)

#define _hwa_cfio1a_kfn_1(o,p,bn,bp,k,v,...)	HW_Y(_hwa_cfio1a_vfn,_hw_is_gpio_##v)(o,p,bn,bp,v,__VA_ARGS__)
#define _hwa_cfio1a_vfn_0(o,p,bn,bp,v,...)	HW_E_KVNIY(function,v)
#define _hwa_cfio1a_vfn_1(o,p,bn,bp,v,k,...)	HW_Y(_hwa_cfio1a_kmd,_hw_is_mode_##k)(o,p,bn,bp,k,__VA_ARGS__)
#define _hwa_cfio1a_kfn_0(o,p,bn,bp,k,...)	HW_Y(_hwa_cfio1a_kmd,_hw_is_mode_##k)(o,p,bn,bp,k,__VA_ARGS__)

/*  Key 'mode'
 */
#define _hwa_cfio1a_kmd_0(o,p,bn,bp,k,v,...)	HW_E_K(mode,k)
#define _hwa_cfio1a_kmd_1(o,p,bn,bp,k,v,...)	HW_Y(_hwa_cfio1a_vmd,_hw_cfio1a_md_##v)(o,p,bn,bp,v,__VA_ARGS__)
#define _hwa_cfio1a_vmd_0(o,p,bn,bp,v,...)	HW_E_NIL(v, (digital_input,digital_input_floating,digital_input_pullup,\
							     digital_input_pulldown,digital_output,digital_output_pushpull,\
							     digital_output_opendrain,analog_input))
#define _hwa_cfio1a_vmd_1(o,p,bn,bp,v,...)	HW_G2(_hwa_cfio1a,HW_A1(_hw_cfio1a_md_##v))(o,p,bn,bp,__VA_ARGS__)

#define _hwa_cfio1a_dif(o,p,bn,bp,k,...)	cnf=1 ; mode=0 ; _hwa_cfio1a9(o,p,bn,bp,__VA_ARGS__)
#define _hwa_cfio1a_dipu(o,p,bn,bp,k,...)	cnf=2 ; mode=0 ; odr=1 ; _hwa_cfio1a9(o,p,bn,bp,__VA_ARGS__)
#define _hwa_cfio1a_dipd(o,p,bn,bp,k,...)	cnf=2 ; mode=0 ; odr=0 ; _hwa_cfio1a9(o,p,bn,bp,__VA_ARGS__)
#define _hwa_cfio1a_dopp(o,p,bn,bp,k,...)	cnf=0 ; HW_Y(_hwa_cfio1a_kfq,_hw_is_frequency_##k)(o,p,bn,bp,k,__VA_ARGS__)
#define _hwa_cfio1a_dood(o,p,bn,bp,k,...)	cnf=1 ; HW_Y(_hwa_cfio1a_kfq,_hw_is_frequency_##k)(o,p,bn,bp,k,__VA_ARGS__)
#define _hwa_cfio1a_ai(o,p,bn,bp,k,...)		cnf=0 ; mode=0 ; _hwa_cfio1a9(o,p,bn,bp,__VA_ARGS__)

/*  Key 'frequency'
 */
#define _hw_cfio1a_fq_10MHz			, 1
#define _hw_cfio1a_fq_2MHz			, 2
#define _hw_cfio1a_fq_lowest			, 2
#define _hw_cfio1a_fq_50MHz			, 3
#define _hw_cfio1a_fq_highest			, 3

#define _hwa_cfio1a_kfq_0(o,p,bn,bp,k,...)	HW_Y(_hwa_cfio1a_kfq0,k)(o,p,bn,bp,k,__VA_ARGS__)
#define _hwa_cfio1a_kfq0_1(o,p,bn,bp,k,...)	mode=2 ; _hwa_do_cfio1a( &hwa->p, bn, bp, cnf, mode, odr )
#define _hwa_cfio1a_kfq0_0(o,p,bn,bp,k,...)	HW_E_K(frequency,k)

#define _hwa_cfio1a_kfq_1(o,p,bn,bp,k,v,...)	HW_Y(_hwa_cfio1a_vfq,_hw_cfio1a_fq_##v)(o,p,bn,bp,v,__VA_ARGS__)
#define _hwa_cfio1a_vfq_1(o,p,bn,bp,v,...)	mode=HW_A1(_hw_cfio1a_fq_##v); _hwa_cfio1a9(o,p,bn,bp,__VA_ARGS__)
#define _hwa_cfio1a_vfq_0(o,p,bn,bp,v,...)	HW_E_NIL(v,(2MHz,10MHz,50MHz))

#define _hwa_cfio1a9(o,p,bn,bp,...)		HW_Y(_hwa_cfio1a9,__VA_ARGS__)(o,p,bn,bp,__VA_ARGS__)
#define _hwa_cfio1a9_0(o,p,bn,bp,g,...)		HW_E_G(g)
#define _hwa_cfio1a9_1(o,p,bn,bp,g,...)		_hwa_do_cfio1a( &hwa->p, bn, bp, cnf, mode, odr )


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
#define _hw_rdio1a(o,i,p,bn,bp,...)	HW_Y(_hw_rdio1a,__VA_ARGS__)(p,bn,bp,__VA_ARGS__,)
#define _hw_rdio1a_0(p,bn,bp,g,...)	HW_E_G(g)
#define _hw_rdio1a_1(p,bn,bp,...)	( (_hw_read_reg(p,idr) & ((1UL<<bn)-1)) >> bp )


/**
 * @page stm32_io1a
 * <br>
 * `write`:
 * @code
 * hw | hwa( write, pa0, 0 );
 * @endcode
 *
 * @note HWA does not write the ODR of the port. It writes the BSRR so that
 * atomicity is guaranted and concurrent tasks can write the port without
 * conflict.
 */
/*  Writing pins can be done two ways:
 *   * writing the ODR
 *   * writing the BSRR (or BRR)
 *
 *  Writing the BSRR allows atomic writing of the ODR's bits without leading to
 *  a heavier binary code. So, let's use that.
 *
 *  BSRR: MSB16 bits reset the ODR bits
 *        LSB16 bits set the ODR bits, it has the priority over MSB16
 */
#define _hw_wrio1a(o,i,p,bn,bp,v,g,...)		HW_Y(_hwx_wrio1a1,v)(_hw,p,bn,bp,v,g)
#define _hwa_wrio1a(o,i,p,bn,bp,v,g,...)	HW_Y(_hwx_wrio1a1,v)(_hwa,p,bn,bp,v,g)
#define _hwx_wrio1a1_1(x,p,bn,bp,v,g)		HW_E_V()
#define _hwx_wrio1a1_0(x,p,bn,bp,v,g)		HW_Y(_hwx_wrio1a2,g)(x,p,bn,bp,v,g)
#define _hwx_wrio1a2_0(x,p,bn,bp,v,g)		HW_E_G(g)
#define _hwx_wrio1a2_1(x,p,bn,bp,v,g)		x##_write_reg_m( p, bsrr, 0xffffffff, \
								 ((((1UL<<bn)-1)<<bp) & (~(v##UL))<<bp)<<16 | \
								 ((((1UL<<bn)-1)<<bp) & ( (v))<<bp) )


/**
 * @page stm32_io1a
 * <br>
 * `toggle`:
 * @code
 * hw( toggle, pa0 );       //  Toggle one or several consecutive pins at once
 * @endcode
 */
/*  Use the BSRR instead of a read-modify-write on the ODR.
 */
#define _hw_tgio1a(o,i,p,bn,bp,g,...)		HW_Y(_hw_tgio1a,g)(p,bn,bp,g)
#define _hw_tgio1a_0(p,bn,bp,g)			HW_E_G(g)
#define _hw_tgio1a_1(p,bn,bp,g)						\
  do {									\
    uint32_t v = *(volatile uint32_t*)(_HW_A(_HW_R(p,odr)));		\
    *(volatile uint32_t*)(_HW_A(_HW_R(p,bsrr))) =			\
      ((((1UL<<bn)-1)<<bp) & v)<<16 | ((((1UL<<bn)-1)<<bp) & ~v);	\
  }while(0)

/**
 * @page stm32_io1a
 * <br>
 * @code
 * hwa( toggle, pa0 );      //  Register pa0 for toggling
 * hwa( toggle, pa4 );      //  Register pa4 for toggling
 * hwa_commit();                //  Commit all registered pins at once
 * @endcode
 *
 * @note `toggle` is not atomic: it reads the ODR, then sets/resets the relevant
 * bits through the BSRR. The ODR is not written directly.
 */
#define _hwa_tgio1a(o,i,p,bn,bp,g,...)		HW_Y(_hwa_tgio1a,g)(p,bn,bp,g)
#define _hwa_tgio1a_0(p,bn,bp,g)		HW_E_G(g)
#define _hwa_tgio1a_1(p,bn,bp,g)		hwa->p.toggles |= (((1UL<<bn)-1) << bp)


/**
 * @page stm32_io1a
 * <br>
 */
