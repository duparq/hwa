
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


/**
 * @page stm32f103_io1a
 * @section stm32f103_io1a_config Configuration
 *
 * @code
 * hw|hwa( configure,   pin_pa0,
 *
 *         mode,        analog,
 *      
 *       [ direction,   input ] );
 * @endcode
 *
 * @code
 * hw|hwa( configure,   pin_pa0,
 *
 *         mode,        digital,
 *      
 *         direction,   input,
 *      
 *       [ pullup,      on
 *                    | *off*, ]
 *      
 *       [ pulldown,    on
 *                    | *off*, ] );
 * @endcode
 *
 * @code
 * hw|hwa( configure,   pin_pa0,
 *
 *         mode,        digital,
 *      
 *         direction, | output
 *                    | output_pushpull
 *                    | output_opendrain,
 *      
 *       [ frequency,   2MHz
 *                    | *10MHz*
 *                    | 50MHz ] );
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

//#define _hw_cfio1a(...)			_hwx_cfio1a(_hw,__VA_ARGS__,,)
#define _hw_cfio1a(o,i,p,bn,bp,k,...)					\
  do {									\
    uint8_t cnf=0, mode=2 /* 2 MHz output */;				\
    struct { uint8_t commit ; hwa_p16a_t p ; } st ;			\
    hwa_t *hwa = (hwa_t*)&st ;						\
    _hwa_setup(p);							\
    HW_X(_hw_cfio1a_kmode,_hw_is_mode_##k)(_hwa,o,p,bn,bp,k,__VA_ARGS__); \
    st.commit = 1 ;							\
    _hwa_commit(p);							\
  }while(0)

#define _hwa_cfio1a(...)		_hwx_cfio1a(_hwa,__VA_ARGS__,,)

#define _hwx_cfio1a(x,o,i,p,bn,bp,k,...)				\
  do{ uint8_t cnf, mode=1 ; HW_X(_hw_cfio1a_kmode,_hw_is_mode_##k)(x,o,p,bn,bp,k,__VA_ARGS__); }while(0)

#define _hw_cfio1a_kmode_0(x,o,p,bn,bp,k,v,...)		HW_E_K(mode,k)
#define _hw_cfio1a_kmode_1(x,o,p,bn,bp,k,v,...)		HW_X(_hw_cfio1a_vmode,_hw_cfio1a_mode_##v)(x,o,p,bn,bp,v,__VA_ARGS__)
#define _hw_cfio1a_vmode_0(x,o,p,bn,bp,v,...)		HW_E_AVL(mode, v, analog | digital)
#define _hw_cfio1a_vmode_1(x,o,p,bn,bp,v,...)		_hw_cfio1a_##v(x,o,p,bn,bp,__VA_ARGS__)

#define _hw_cfio1a_digital(x,o,p,bn,bp,k,...)		HW_X(_hw_cfio1a1_kdir,_hw_is_direction_##k)(x,o,p,bn,bp,k,__VA_ARGS__)
#define _hw_cfio1a1_kdir_0(x,o,p,bn,bp,k,...)		HW_E_K(direction,k)
#define _hw_cfio1a1_kdir_1(x,o,p,bn,bp,k,v,...)		HW_X(_hw_cfio1a1_vdir,_hw_cfio1a_dir_##v)(x,o,p,bn,bp,v,__VA_ARGS__)
#define _hw_cfio1a1_vdir_0(x,o,p,bn,bp,v,...)		HW_E_AVL(direction,v, input|output|output_pushpull|output_opendrain)
#define _hw_cfio1a1_vdir_1(x,o,p,bn,bp,v,...)		_hw_cfio1a1_##v(x,o,p,bn,bp,__VA_ARGS__)

#define _hw_cfio1a1_intput(x,o,p,bn,bp,k,...)		HW_X(_hw_cfio1a2_kpu,_hw_is_pullup_##k)(x,o,p,bn,bp,k,__VA_ARGS__)

#define _hw_cfio1a1_output(x,o,p,bn,bp,k,...)		cnf=0; HW_X(_hw_cfio1a3_kfq,_hw_is_frequency_##k)(x,o,p,bn,bp,k,__VA_ARGS__)
#define _hw_cfio1a1_output_pushpull(x,o,p,bn,bp,k,...)	cnf=0; HW_X(_hw_cfio1a3_kfq,_hw_is_frequency_##k)(x,o,p,bn,bp,k,__VA_ARGS__)
#define _hw_cfio1a1_output_opendrain(x,o,p,bn,bp,k,...)	cnf=1; HW_X(_hw_cfio1a3_kfq,_hw_is_frequency_##k)(x,o,p,bn,bp,k,__VA_ARGS__)
#define _hw_cfio1a3_kfq_0(x,o,p,bn,bp,k,...)		HW_E_K(frequency,k)
#define _hw_cfio1a3_kfq_1(x,o,p,bn,bp,k,v,...)		HW_X(_hw_cfio1a3_vfq,_hw_cfio1a_mode_##v)(x,o,p,bn,bp,v,__VA_ARGS__)
#define _hw_cfio1a3_vfq_1(x,o,p,bn,bp,v,...)		mode=HW_A1(_hw_cfio1a_mode_##v); _hw_cfio1a9(x,o,p,bn,bp,__VA_ARGS__)

#define _hw_cfio1a9(x,o,p,bn,bp,...)			HW_X(_hw_cfio1a9,__VA_ARGS__)(x,o,p,bn,bp,__VA_ARGS__)
#define _hw_cfio1a9_0(x,o,p,bn,bp,g,...)		HW_E_G(g)
#define _hw_cfio1a9_1(x,o,p,bn,bp,g,...)		x##_do_cfio1a( &hwa->p,((1UL<<bn)-1)<<bp, (cnf<<2)|mode )


HW_INLINE void _hwa_do_cfio1a_( hwa_r32_t *r, uint8_t i, uint8_t mode )
{
  i *= 4 ;
  uint32_t msk = 0x0F << i ;
  uint32_t v = mode << i ;
  r->mmask |= msk ;
  r->mvalue = (r->mvalue & ~msk) | (msk & v) ;
}

  
HW_INLINE void _hwa_do_cfio1a( hwa_p16a_t *p, uint16_t mask, uint8_t mode )
{
  if ( mask & 0x0001 ) _hwa_do_cfio1a_(&p->crl,0,mode);
  if ( mask & 0x0002 ) _hwa_do_cfio1a_(&p->crl,1,mode);
  if ( mask & 0x0004 ) _hwa_do_cfio1a_(&p->crl,2,mode);
  if ( mask & 0x0008 ) _hwa_do_cfio1a_(&p->crl,3,mode);
}



#if 0
#define _hw_cfio1a_vmode_analog(o,p,bn,bp,...)				\
  HW_X(_hw_cfio1a_vmode_analog,HW_G2(_hw_isa_reg,_hw_reg_##o##_##did),0)(o,p,bn,bp,__VA_ARGS__)

#define _hw_cfio1a_vmode_analog_0(o,p,bn,bp,...)	HW_E(pin `o` does not support analog mode)

#define _hw_cfio1a_vmode_analog_1(o,p,bn,bp,k,...)			\
  analog = 1 ;								\
  _hw_write(_hw_reg_##o##_##did, 1);						\
  HW_X(_hw_cfio1a_kdirection,_hw_is_direction_##k)(o,p,bn,bp,k,__VA_ARGS__)

#define _hw_cfio1a_vmode_digital(o,p,bn,bp,k,...)			\
  analog = 0 ;								\
  HW_X(_hw_cfio1a_kdirection,_hw_is_direction_##k)(o,p,bn,bp,k,__VA_ARGS__)

#define _hw_cfio1a_kmode_0(o,p,bn,bp,k,...)				\
  HW_X(_hw_cfio1a_kdirection,_hw_is_direction_##k)(o,p,bn,bp,k,__VA_ARGS__)

#define _hw_cfio1a_kdirection_1(o,p,bn,bp,k,v,...)			\
  HW_X(_hw_cfio1a_vdirection,hw_cfio1a_direction_##v)(o,p,bn,bp,v,__VA_ARGS__)

#define _hw_cfio1a_vdirection_1(o,p,bn,bp,v,k,...)			\
  if ( HW_A1(hw_cfio1a_direction_##v)==1 && analog==1 )			\
    HWA_ERR("`" #o "` can not be an anolog output.");			\
  _hw_write_reg_m(p,ddr,((1<<bn)-1)<<bp, HW_A1(hw_cfio1a_direction_##v)?((1U<<bn)-1)<<bp:0); \
  HW_X(_hw_cfio1a_kpullup,_hw_is_pullup_##k)(o,p,bn,bp,k,__VA_ARGS__)

#define _hw_cfio1a_vdirection_0(o,p,bn,bp,v,...)			\
  HW_E_AVL(direction, v, input | output)

#define _hw_cfio1a_kdirection_0(o,p,bn,bp,k,...)			\
  HW_X(_hw_cfio1a_kpullup,_hw_is_pullup_##k)(o,p,bn,bp,k,__VA_ARGS__)

/*  Optionnal parameter `pullup`
 */
#define _hw_is_pullup_pullup		, 1

#define _hw_cfio1a_kpullup_0(o,p,bn,bp,...)\
  HW_EOL(__VA_ARGS__)

#define _hw_cfio1a_kpullup_1(o,p,bn,bp,k,v,...)				\
  HW_X(_hw_cfio1a_vpullup,_hw_state_##v)(o,p,bn,bp,v,__VA_ARGS__)

#define _hw_cfio1a_vpullup_1(o,p,bn,bp,v,...)			\
    _hw_write_reg_m(p,port,((1<<bn)-1)<<bp, HW_A1(hw_state_##v)?((1U<<bn)-1)<<bp:0); \
    HW_EOL(__VA_ARGS__)

#define _hw_cfio1a_vpullup_0(o,p,bn,bp,v,...)			\
  HW_E_AVL(pullup, v, on | off)

/**
 * @page stm32f103_io1a
 *
 * @code
 * hwa( configure, pin_pa0,
 *
 *    [ mode,        analog,
 *                 | digital, ]
 *
 *    [ direction,   input,
 *                 | output, ]
 *
 *    [ pullup,      on,
 *                 | off ] );
 * @endcode
 */
#define _xhwa_cfio1a( o,i, p,bn,bp, ...)					\
  do {									\
    HW_X(_hwa_cfio1a_kmode,_hw_is_mode_##__VA_ARGS__)(o,p,bn,bp,__VA_ARGS__,,); \
  } while(0)

#define _hwa_cfio1a_kmode_1(o,p,bn,bp,k,v,...)				\
  HW_X(_hwa_cfio1a_vmode,hw_cfio1a_mode_##v)(o,p,bn,bp,v,__VA_ARGS__)

#define _hwa_cfio1a_vmode_0(o,p,bn,bp,v,...)				\
  HW_E_AVL(mode, v, analog | digital)

#define _hwa_cfio1a_vmode_1(o,p,bn,bp,v,...)				\
  HW_G2(_hwa_cfio1a_vmode, v)(o,p,bn,bp,__VA_ARGS__)

#define _hwa_cfio1a_vmode_analog(o,p,bn,bp,...)				\
  HW_X(_hwa_cfio1a_vmode_analog,HW_G2(_hw_isa_reg,_hw_reg_##o##_##did),0)(o,p,bn,bp,__VA_ARGS__)

#define _hwa_cfio1a_vmode_analog_0(o,p,bn,bp,...)	HW_E(pin `o` does not support analog mode)

#define _hwa_cfio1a_vmode_analog_1(o,p,bn,bp,...)	\
  _hwa( write, _hw_reg_##o##_##did, 1);			\
  _hwa_cfio1a_kmode_0(o,p,bn,bp,__VA_ARGS__)

#define _hwa_cfio1a_vmode_digital	_hwa_cfio1a_kmode_0

#define _hwa_cfio1a_kmode_0(o,p,bn,bp,k,...)				\
  HW_X(_hwa_cfio1a_kdirection,_hw_is_direction_##k)(o,p,bn,bp,k,__VA_ARGS__) \

#define _hwa_cfio1a_kdirection_1(o,p,bn,bp,k,v,...)			\
  HW_X(_hwa_cfio1a_vdirection,hw_cfio1a_direction_##v)(o,p,bn,bp,v,__VA_ARGS__)

#define _hwa_cfio1a_vdirection_1(o,p,bn,bp,v,k,...)			\
  _hwa_write__r8( &hwa->p.ddr, 0xFF,0, bn,bp, (HW_A1(hw_cfio1a_direction_##v)?(1U<<bn)-1:0)); \
  HW_X(_hwa_cfio1a_kpullup,_hw_is_pullup_##k)(o,p,bn,bp,k,__VA_ARGS__)

#define _hwa_cfio1a_vdirection_0(o,p,bn,bp,v,...)			\
  HW_E_AVL(direction, v, input | output)

#define _hwa_cfio1a_kdirection_0(o,p,bn,bp,k,...)			\
  HW_X(_hwa_cfio1a_kpullup,_hw_is_pullup_##k)(o,p,bn,bp,k,__VA_ARGS__)

#define _hwa_cfio1a_kpullup_0(o,p,bn,bp,...)	\
  HW_EOL(__VA_ARGS__)

#define _hwa_cfio1a_kpullup_1(o,p,bn,bp,k,v,...)			\
  HW_X(_hwa_cfio1a_vpullup,_hw_state_##v)(o,p,bn,bp,v,__VA_ARGS__)

#define _hwa_cfio1a_vpullup_1(o,p,bn,bp,v,...)			\
  _hwa_write__r8( &hwa->p.port, 0xFF,0, bn,bp, (HW_A1(_hw_state_##v)?(1U<<bn)-1:0) );\
  HW_EOL(__VA_ARGS__)

#define _hwa_cfio1a_vpullup_0(o,p,bn,bp,v,...)				\
  HW_E_AVL(pullup, v, on | off)
#endif


/**
 * @page stm32f103_io1a
 * @section stm32f103_io1a_read State
 *
 * Class `_io1a` I/O objects can be read and written with the following instructions:
 *
 * @code
 * uint8_t value = hw( read, pin_pa0 );
 * @endcode
 */
#define _hw_rdio1a(o,i,p,bn,bp,...)	HW_X(_hw_rdio1a,__VA_ARGS__)(p,bn,bp,__VA_ARGS__,)
#define _hw_rdio1a_0(p,bn,bp,g,...)	HW_E_G(g)
#define _hw_rdio1a_1(p,bn,bp,...)	( (_hw_read_reg(p,idr) & ((1UL<<bn)-1)) >> bp )


/**
 * @page stm32f103_io1a
 * @code
 * hw( write, pin_pa0, value );
 * @endcode
 */
#define _hw_wrio1a(o,i,p,bn,bp,v,...)	HW_X(_hw_wrio1a,__VA_ARGS__)(p,bn,bp,v,__VA_ARGS__,)
#define _hw_wrio1a_0(p,bn,bp,v,g,...)	HW_E_G(g)
#define _hw_wrio1a_1(p,bn,bp,v,...)	_hw_write_reg_m(p,odr,((1UL<<bn)-1)<<bp,(v)<<bp)

/**
 * @page stm32f103_io1a
 * @code
 * hwa( write, pin_pa0, value );
 * @endcode
 */
#define _hwa_write_io1a(o,i, p,bn,bp, v, ...)		\
  HW_TX(_hwa_write__r8(&hwa->p.port, 0xFF,0x00, bn,bp, v),__VA_ARGS__)


/**
 * @page stm32f103_io1a
 * @code
 * hw( toggle, pin_pa0 );	//  Toggle one or several consecutive pins at once
 * @endcode
 */
#define _hw_tgio1a(o,i,p,bn,bp,g,...)		HW_X(_hw_tgio1a,g)(p,bn,bp,g)
#define _hw_tgio1a_0(p,bn,bp,g)			HW_E_G(g)
#define _hw_tgio1a_1(p,bn,bp,_)			\
  do {						\
    uint16_t mask = (((1UL<<bn)-1) << bp);	\
    uint16_t odr = _hw_read_reg(p,odr) ;	\
    _hw_write_reg(p,odr,~odr & mask);		\
  }while(0)
    


#define _hw_toggle_io1a(o,i,p,...)		_hw_toggle_io1a_2(_HW_M(p,pin),__VA_ARGS__)
#define _hw_toggle_io1a_2(...)			_hw_toggle_io1a_3(__VA_ARGS__)
#define _hw_toggle_io1a_3(_m1,o,a,r,rc,ra,rwm,rfm,_bn,_bp,bn,bp,...)	\
  HW_TX(_hw_write(_m1,o,a,r,rc,ra,rwm,rfm,bn,bp,(1UL<<bn)-1,),__VA_ARGS__)


/**
 * @page stm32f103_io1a
 * @code
 * // All the pins of the same object are toggled at once by the
 * // following `hwa_commit()`.
 * //
 * hwa( toggle, pin_pa0 );
 * @endcode
 */
#define _hwa_toggle_io1a(o,i, p,...)		_hwa_toggle_io1a_2(_HW_M(p,pin),__VA_ARGS__)
#define _hwa_toggle_io1a_2(...)			_hwa_toggle_io1a_3(__VA_ARGS__)
#define _hwa_toggle_io1a_3(_m1,p,a,r,rw,ra,rwm,rfm,_bn,_bp,bn,bp,...)	\
  HW_TX(_hwa(write,_m1,p,a,r,rw,ra,rwm,rfm,bn,bp,(1UL<<bn)-1),__VA_ARGS__)


/**
 * @page stm32f103_io1a
 * @section stm32f103_io1a_def Creating a I/O definition
 *
 * Creating an I/O definition allows giving a set of consecutive pins a name
 * that tells their role and benefit of the generic read/write instructions.
 *
 * A class `_io1a` object named `mypins` is created with:
 *
 * @code
 *     #define _hw_pin_mypins		_io1a, id, port, bn, bp
 * @endcode
 *
 * where:
 *
 * * `id` is a unique number identifying the object. If you're not going to use
 *   the `HW_ID()` instruction with this object, any value (or even none) is OK.
 *
 * * `port` is the name of the object holding the pin, e.g.: `porta`.
 *
 * * `bn` is the number of consecutive bits the GPIO definition contains.
 *
 * * `bp` is the position of the least significant bit in the port.
 */

/**
 * @page stm32f103_io1a
 * <br>
 */
