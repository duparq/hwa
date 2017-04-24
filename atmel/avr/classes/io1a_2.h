
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief I/O
 */

#define _hw_mthd_hw_configure__io1a	, _hw_cfio1a
#define _hw_mthd_hwa_configure__io1a	, _hwa_cfio1a
#define _hw_mthd_hw_read__io1a		, _hw_read_io1a
#define _hw_mthd_hw_write__io1a		, _hw_write_io1a
#define _hw_mthd_hwa_write__io1a	, _hwa_write_io1a
#define _hw_mthd_hw_toggle__io1a	, _hw_toggle_io1a


/**
 * @page atmelavr_io1a
 * @section atmelavr_io1a_config Configuration
 *
 * @code
 * hw( configure, pin_pa0,
 *
 *   [ mode,        analog,
 *                | digital, ]
 *
 *   [ direction,   input,
 *                | output, ]
 *
 *   [ pullup,      on,
 *                | off ] );
 * @endcode
 */

/*  Optionnal parameter `mode`
 */
#define _hw_is_mode_mode		, 1
#define hw_cfio1a_mode_digital		, 0
#define hw_cfio1a_mode_analog		, 1

#define _hw_cfio1a( o,i, p,bn,bp, ...)					\
  do{									\
     uint8_t analog = 0xFF ;						\
     HW_X(_hw_cfio1a_kmode,_hw_is_mode_##__VA_ARGS__)(o,p,bn,bp,__VA_ARGS__,,); \
  }while(0)

#define _hw_cfio1a_kmode_1(o,p,bn,bp,k,v,...)				\
  HW_X(_hw_cfio1a_vmode,hw_cfio1a_mode_##v)(o,p,bn,bp,v,__VA_ARGS__)

#define _hw_cfio1a_vmode_0(o,p,bn,bp,v,...)				\
  HW_E_AVL(mode, v, analog | digital)

#define _hw_cfio1a_vmode_1(o,p,bn,bp,v,...)				\
  HW_G2(_hw_cfio1a_vmode,v)(o,p,bn,bp,__VA_ARGS__)

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

/*  Optionnal parameter `direction`
 */
#define _hw_is_direction_direction	, 1
#define hw_cfio1a_direction_input	, 0	/* , ddr */
#define hw_cfio1a_direction_output	, 1

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
 * @page atmelavr_io1a
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
#define _hwa_cfio1a( o,i, p,bn,bp, ...)					\
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


/**
 * @page atmelavr_io1a
 * @section atmelavr_io1a_read State
 *
 * Class `_io1a` I/O objects can be read and written with the following instructions:
 *
 * @code
 * uint8_t value = hw( read, pin_pa0 );
 * @endcode
 */
#define _hw_read_io1a(o,i, p,bn,bp,...)				\
  HW_TX( ((_hw_read_reg(p, pin) & (((1<<bn)-1)<<bp))>>bp),	\
	 __VA_ARGS__)


/**
 * @page atmelavr_io1a
 * @code
 * hw( write, pin_pa0, value );
 * @endcode
 */
#define _hw_write_io1a(o,i, p,bn,bp, v,...)	\
  HW_TX( _hw_write_reg_m(p, port, ((1UL<<bn)-1)<<bp, (v)<<bp), __VA_ARGS__ )

/**
 * @page atmelavr_io1a
 * @code
 * hwa( write, pin_pa0, value );
 * @endcode
 */
#define _hwa_write_io1a(o,i, p,bn,bp, v, ...)		\
  HW_TX(_hwa_write__r8(&hwa->p.port, 0xFF,0x00, bn,bp, v),__VA_ARGS__)


/**
 * @page atmelavr_io1a
 * @code
 * hw( toggle, pin_pa0 );	//  Toggle one or several consecutive pins at once
 * @endcode
 */
#define _hw_toggle_io1a(o,i,p,...)		_hw_toggle_io1a_2(_HW_M(p,pin),__VA_ARGS__)
#define _hw_toggle_io1a_2(...)			_hw_toggle_io1a_3(__VA_ARGS__)
#define _hw_toggle_io1a_3(_m1,o,a,r,rc,ra,rwm,rfm,_bn,_bp,bn,bp,...)	\
  HW_TX(_hw_write(_m1,o,a,r,rc,ra,rwm,rfm,bn,bp,(1UL<<bn)-1,),__VA_ARGS__)


/**
 * @page atmelavr_io1a
 * @code
 * // All the pins of the same I/O port are toggled at once by the
 * // following `hwa_commit()` instruction.
 * //
 * hwa( toggle, pin_pa0 );
 * @endcode
 */
#define _hwa_toggle_io1a(o,i, p,...)		_hwa_toggle_io1a_2(_HW_M(p,pin),__VA_ARGS__)
#define _hwa_toggle_io1a_2(...)			_hwa_toggle_io1a_3(__VA_ARGS__)
#define _hwa_toggle_io1a_3(_m1,p,a,r,rw,ra,rwm,rfm,_bn,_bp,bn,bp,...)	\
  HW_TX(_hwa(write,_m1,p,a,r,rw,ra,rwm,rfm,bn,bp,(1UL<<bn)-1),__VA_ARGS__)


/**
 * @page atmelavr_io1a
 * @section atmelavr_io1a_def Creating a I/O definition
 *
 * Creating an I/O definition allows giving a set of consecutive pins a name
 * that tells their role and benefit of the generic read/write instructions.
 *
 * A class `_io1a` I/O definition named `mypins` is created with:
 *
 *     #define _hw_pin_mypins		_io1a, id, port, bn, bp
 *
 * where:
 *
 * * `id` is a unique number identifying the object. If you're not going to use
 *	  the `HW_ID()` instruction, any value (or even none) is OK.
 *
 * * `port` is the name of the object holding the pin, e.g.: `porta`.
 *
 * * `bn` is the number of consecutive bits the GPIO definition contains.
 *
 * * `bp` is the position of the least significant bit in the port.
 */

/**
 * @page atmelavr_io1a
 * <br>
 */
