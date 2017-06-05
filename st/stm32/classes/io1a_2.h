
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
 * @code
 * hw | hwa( configure,   pin_pa0,
 *
 *           mode,        analog,
 *
 *         [ direction,   input ] );    // Default
 * @endcode
 * <br>
 * @code
 * hw | hwa( configure,   pin_pa0,
 *
 *           mode,        digital,
 *
 *           direction,   input,
 *
 *         [ pullup,      on
 *                      | off, ]        // Default
 *
 *         [ pulldown,    on
 *                      | off, ] );     // Default
 * @endcode
 * <br>
 * @code
 * hw | hwa( configure,   pin_pa0,
 *
 *           mode,        digital,
 *
 *           direction, | output
 *                      | output_pushpull
 *                      | output_opendrain,
 *
 *         [ frequency,   2MHz
 *                      | 10MHz         // Default
 *                      | 50MHz ] );
 * @endcode
 */

#define _hw_is_mode_mode		, 1
#define _hw_is_direction_direction	, 1
#define _hw_is_frequency_frequency	, 1

#define _hw_cfio1a_mode_analog		, 1
#define _hw_cfio1a_mode_digital		, 1

#define _hw_cfio1a_dir_input		, 1
#define _hw_cfio1a_dir_output		, 1
#define _hw_cfio1a_dir_output_pushpull	, 1
#define _hw_cfio1a_dir_output		, 1

#define _hw_cfio1a_mode_10MHz		, 1
#define _hw_cfio1a_mode_2MHz		, 2
#define _hw_cfio1a_mode_50MHz		, 3


/*  Create a local minimal context, apply the asynchronous action on it, and
 *  commit.
 */
#define _hw_cfio1a(o,i,p,...)				\
  do {							\
    struct { uint8_t commit ; hwa_p16a_t p ; } st ;	\
    hwa_t *hwa = (hwa_t*)&st ;				\
    _hwa_setup(p);					\
    _hwa_cfio1a(o,i,p,__VA_ARGS__);			\
    st.commit = 1 ; _hwa_commit(p);			\
  }while(0)

#define _hwa_cfio1a(o,i,p,bn,bp,k,...)					\
  do{ uint8_t cnf=0, mode=2 ; HW_X(_hwa_cfio1a_kmode,_hw_is_mode_##k)(o,p,bn,bp,k,__VA_ARGS__); }while(0)

#define _hwa_cfio1a_kmode_0(o,p,bn,bp,k,v,...)	HW_E_K(mode,k)
#define _hwa_cfio1a_kmode_1(o,p,bn,bp,k,v,...)	HW_X(_hwa_cfio1a_vmode,_hw_cfio1a_mode_##v)(o,p,bn,bp,v,__VA_ARGS__)
#define _hwa_cfio1a_vmode_0(o,p,bn,bp,v,...)	HW_E_AVL(mode, v, analog | digital)
#define _hwa_cfio1a_vmode_1(o,p,bn,bp,v,...)	_hwa_cfio1a_##v(o,p,bn,bp,__VA_ARGS__)

#define _hwa_cfio1a_digital(o,p,bn,bp,k,...)	HW_X(_hwa_cfio1a1_kdir,_hw_is_direction_##k)(o,p,bn,bp,k,__VA_ARGS__)
#define _hwa_cfio1a1_kdir_0(o,p,bn,bp,k,...)	HW_E_K(direction,k)
#define _hwa_cfio1a1_kdir_1(o,p,bn,bp,k,v,...)	HW_X(_hwa_cfio1a1_vdir,_hw_cfio1a_dir_##v)(o,p,bn,bp,v,__VA_ARGS__)
#define _hwa_cfio1a1_vdir_0(o,p,bn,bp,v,...)	HW_E_AVL(direction,v, input|output|output_pushpull|output_opendrain)
#define _hwa_cfio1a1_vdir_1(o,p,bn,bp,v,...)	_hwa_cfio1a1_dir_##v(o,p,bn,bp,__VA_ARGS__)

#define _hwa_cfio1a1_dir_intput(o,p,bn,bp,k,...)	HW_X(_hwa_cfio1a2_kpu,_hw_is_pullup_##k)(o,p,bn,bp,k,__VA_ARGS__)

#define _hwa_cfio1a1_dir_output(o,p,bn,bp,k,...)	cnf=0; HW_X(_hwa_cfio1a3_kfq,_hw_is_frequency_##k)(o,p,bn,bp,k,__VA_ARGS__)
#define _hwa_cfio1a1_dir_output_pushpull(o,p,bn,bp,k,...)	cnf=0; HW_X(_hwa_cfio1a3_kfq,_hw_is_frequency_##k)(o,p,bn,bp,k,__VA_ARGS__)
#define _hwa_cfio1a1_dir_output_opendrain(o,p,bn,bp,k,...)	cnf=1; HW_X(_hwa_cfio1a3_kfq,_hw_is_frequency_##k)(o,p,bn,bp,k,__VA_ARGS__)
#define _hwa_cfio1a3_kfq_0(o,p,bn,bp,k,...)	HW_E_K(frequency,k)
#define _hwa_cfio1a3_kfq_1(o,p,bn,bp,k,v,...)	HW_X(_hwa_cfio1a3_vfq,_hw_cfio1a_mode_##v)(o,p,bn,bp,v,__VA_ARGS__)
#define _hwa_cfio1a3_vfq_1(o,p,bn,bp,v,...)	mode=HW_A1(_hw_cfio1a_mode_##v); _hwa_cfio1a9(o,p,bn,bp,__VA_ARGS__)

#define _hwa_cfio1a9(o,p,bn,bp,...)		HW_X(_hwa_cfio1a9,__VA_ARGS__)(o,p,bn,bp,__VA_ARGS__)
#define _hwa_cfio1a9_0(o,p,bn,bp,g,...)		HW_E_G(g)
#define _hwa_cfio1a9_1(o,p,bn,bp,g,...)		_hwa_do_cfio1a( &hwa->p,((1UL<<bn)-1)<<bp, (cnf<<2)|mode )


HW_INLINE void _hwa_do_cfio1a_( hwa_r32_t *r, uint8_t i, uint8_t mode )
{
  i *= 4 ;
  uint32_t msk = 0x0FUL << i ;
  uint32_t v = ((uint32_t)mode) << i ;
  r->mmask |= msk ;
  r->mvalue = (r->mvalue & ~msk) | (msk & v) ;
}


HW_INLINE void _hwa_do_cfio1a( hwa_p16a_t *p, uint16_t mask, uint8_t mode )
{
  if ( mask & 0x0001 ) _hwa_do_cfio1a_(&p->crl,0,mode);
  if ( mask & 0x0002 ) _hwa_do_cfio1a_(&p->crl,1,mode);
  if ( mask & 0x0004 ) _hwa_do_cfio1a_(&p->crl,2,mode);
  if ( mask & 0x0008 ) _hwa_do_cfio1a_(&p->crl,3,mode);
  if ( mask & 0x0010 ) _hwa_do_cfio1a_(&p->crl,4,mode);
  if ( mask & 0x0020 ) _hwa_do_cfio1a_(&p->crl,5,mode);
  if ( mask & 0x0040 ) _hwa_do_cfio1a_(&p->crl,6,mode);
  if ( mask & 0x0080 ) _hwa_do_cfio1a_(&p->crl,7,mode);

  if ( mask & 0x0100 ) _hwa_do_cfio1a_(&p->crh,0,mode);
  if ( mask & 0x0200 ) _hwa_do_cfio1a_(&p->crh,1,mode);
  if ( mask & 0x0400 ) _hwa_do_cfio1a_(&p->crh,2,mode);
  if ( mask & 0x0800 ) _hwa_do_cfio1a_(&p->crh,3,mode);
  if ( mask & 0x1000 ) _hwa_do_cfio1a_(&p->crh,4,mode);
  if ( mask & 0x2000 ) _hwa_do_cfio1a_(&p->crh,5,mode);
  if ( mask & 0x4000 ) _hwa_do_cfio1a_(&p->crh,6,mode);
  if ( mask & 0x8000 ) _hwa_do_cfio1a_(&p->crh,7,mode);
}



/**
 * @page stm32_io1a
 * <br>
 * `read`:
 * @code
 * uint8_t value = hw( read, pin_pa0 );
 * @endcode
 */
#define _hw_rdio1a(o,i,p,bn,bp,...)	HW_X(_hw_rdio1a,__VA_ARGS__)(p,bn,bp,__VA_ARGS__,)
#define _hw_rdio1a_0(p,bn,bp,g,...)	HW_E_G(g)
#define _hw_rdio1a_1(p,bn,bp,...)	( (_hw_read_reg(p,idr) & ((1UL<<bn)-1)) >> bp )


/**
 * @page stm32_io1a
 * <br>
 * `write`:
 * @code
 * hw | hwa( write, pin_pa0, 0 );
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
#define _hw_wrio1a(o,i,p,bn,bp,v,g,...)		HW_X(_hwx_wrio1a1,v)(_hw,p,bn,bp,v,g)
#define _hwa_wrio1a(o,i,p,bn,bp,v,g,...)	HW_X(_hwx_wrio1a1,v)(_hwa,p,bn,bp,v,g)
#define _hwx_wrio1a1_1(x,p,bn,bp,v,g)		HW_E_V()
#define _hwx_wrio1a1_0(x,p,bn,bp,v,g)		HW_X(_hwx_wrio1a2,g)(x,p,bn,bp,v,g)
#define _hwx_wrio1a2_0(x,p,bn,bp,v,g)		HW_E_G(g)
#define _hwx_wrio1a2_1(x,p,bn,bp,v,g)				\
  x##_write_reg_m( p, bsrr, 0xffffffff,				\
		   ((((1UL<<bn)-1)<<bp) & (~(v))<<bp)<<16 |	\
		   ((((1UL<<bn)-1)<<bp) & ( (v))<<bp) )


/**
 * @page stm32_io1a
 * <br>
 * `toggle`:
 * @code
 * hw( toggle, pin_pa0 );       //  Toggle one or several consecutive pins at once
 * @endcode
 */
/*  Use the BSRR instead of a read-modify-write on the ODR.
 */
#define _hw_tgio1a(o,i,p,bn,bp,g,...)		HW_X(_hw_tgio1a,g)(p,bn,bp,g)
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
 * hwa( toggle, pin_pa0 );      //  Register pin_pa0 for toggling
 * hwa( toggle, pin_pa4 );      //  Register pin_pa4 for toggling
 * hwa_commit();                //  Commit all registered pins at once
 * @endcode
 *
 * @note `toggle` is not atomic: it reads the ODR, then sets/resets the relevant
 * bits through the BSRR. The ODR is not written directly.
 */
#define _hwa_tgio1a(o,i,p,bn,bp,g,...)		HW_X(_hwa_tgio1a,g)(p,bn,bp,g)
#define _hwa_tgio1a_0(p,bn,bp,g)		HW_E_G(g)
#define _hwa_tgio1a_1(p,bn,bp,g)		hwa->p.toggles |= (((1UL<<bn)-1) << bp)


/**
 * @page stm32_io1a
 * @section stm32_io1a_def How to create a I/O definition
 *
 * Creating an I/O definition allows giving a set of consecutive pins a name
 * that tells their role and use the HWA generic instructions.
 *
 * A class `_io1a` object named `mypins` is created with:
 *
 * @code
 * #define _hw_pin_mypins       _io1a, id, port, bn, bp
 * @endcode
 *
 * where:
 *
 * * `id` is a unique number identifying the object. If you're not going to use
 *   the `HW_ID()` instruction with this object, any value (or even none) is OK.
 *
 * * `port` is the name of the object holding the pin, e.g.: `port0`.
 *
 * * `bn` is the number of consecutive bits the GPIO definition contains.
 *
 * * `bp` is the position of the least significant bit in the port.
 *
 * @code
 * #define _hw_pin_outs         _io1a, , port0, 4, 3    // Pins 6,5,4,3 of port0
 *
 * hw( write, pin_outs, 5 );                            // Sets pins 5 & 3, clears pins 6 & 4.
 * @endcode
 * <br>
 */
