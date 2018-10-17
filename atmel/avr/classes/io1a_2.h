
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief I/O
 */

#define _hw_mtd_hw_configure__io1a	, _hw_cfio1a
#define _hw_mtd_hwa_configure__io1a	, _hwa_cfio1a
#define _hw_mtd_hw_read__io1a		, _hw_read_io1a
#define _hw_mtd_hw_write__io1a		, _hw_write_io1a
#define _hw_mtd_hwa_write__io1a		, _hwa_write_io1a
#define _hw_mtd_hw_toggle__io1a		, _hw_toggle_io1a


/**
 * @page atmelavr_io1a
 *
 * __Actions__
 *
 * `configure`:
 *
 * @code
 * hw | hwa( configure,   pa0,
 *
 *         [ function,    gpio, ]                       // Default
 *
 *           mode,        digital_input
 *                      | digital_input_floating        // Default
 *                      | digital_input_pullup
 *                      | digital_output | digital_output_pushpull
 *                      | analog_input
 *                      | analog_input_floating
 *                      | analog_input_pullup );
 * @endcode
 *
 * @note a digital output in high state enables the pull-up when switched to an
 *       input mode.
 */

#define _hw_cfio1a(...)		_hwx_cfio1a(_hw,__VA_ARGS__,,)
#define _hwa_cfio1a(...)	_hwx_cfio1a(_hwa,__VA_ARGS__,,)

/*  Atmel AVR peripheral controllers are responsible of their I/O pins
 *  configuration, so there is no need for a 'function' argument as it is always
 *  'gpio'. 
 */

/*  Key 'function'
 */
#define _hw_cfio1a_fn_gpio

#define _hwx_cfio1a(x,o,i,p,bn,bp,k,...)	HW_Y(_hwx_cfio1a_kfn,_hw_is_function_##k)(x,o,p,bn,bp,k,__VA_ARGS__)
#define _hwx_cfio1a_kfn_0(x,o,p,bn,bp,k,...)	HW_Y(_hwx_cfio1a_kmd,_hw_is_mode_##k)(x,o,p,bn,bp,k,__VA_ARGS__)
#define _hwx_cfio1a_kfn_1(x,o,p,bn,bp,k,v,...)	HW_Y(_hwx_cfio1a_vfn,_hw_cfio1a_fn_##v)(x,o,p,bn,bp,v,__VA_ARGS__)
#define _hwx_cfio1a_vfn_0(x,o,p,bn,bp,v,...)	HW_E_NIL(v, (gpio) )
#define _hwx_cfio1a_vfn_1(x,o,p,bn,bp,v,k,...)	HW_Y(_hwx_cfio1a_kmd,_hw_is_mode_##k)(x,o,p,bn,bp,k,__VA_ARGS__)

/*  Key 'mode'
 */
#define _hw_cfio1a_md_digital_input		, di
#define _hw_cfio1a_md_digital_input_floating	, dif
#define _hw_cfio1a_md_digital_input_pullup	, dipu
#define _hw_cfio1a_md_digital_output		, do
#define _hw_cfio1a_md_digital_output_pushpull	, do
#define _hw_cfio1a_md_analog_input		, ai
#define _hw_cfio1a_md_analog_input_floating	, aif
#define _hw_cfio1a_md_analog_input_pullup	, aipu

#define _hwx_cfio1a_kmd_0(x,o,p,bn,bp,k,...)	HW_E_NIL(k, (mode) )
#define _hwx_cfio1a_kmd_1(x,o,p,bn,bp,k,v,...)	HW_Y(_hwx_cfio1a_vmd,_hw_cfio1a_md_##v)(x,o,p,bn,bp,v,__VA_ARGS__)
#define _hwx_cfio1a_vmd_0(x,o,p,bn,bp,v,...)	HW_E_NIL(v, (digital_input|digital_output|analog_input) )
#define _hwx_cfio1a_vmd_1(x,o,p,bn,bp,v,...)	HW_G2(_hwx_cfio1a,HW_A1(_hw_cfio1a_md_##v))(x,o,p,bn,bp,__VA_ARGS__)

#define _hwx_cfio1a_di(x,o,p,bn,bp,k,...)	x##_write_reg_m(p,ddr,((1U<<bn)-1)<<bp, 0); HW_EOL(__VA_ARGS__)

#define _hwx_cfio1a_dif(x,o,p,bn,bp,k,...)				\
  x##_write_reg_m(p,ddr,((1U<<bn)-1)<<bp, 0);				\
  x##_write_reg_m(p,port,((1U<<bn)-1)<<bp, 0 ); HW_EOL(__VA_ARGS__)

#define _hwx_cfio1a_dipu(x,o,p,bn,bp,k,...)				\
  x##_write_reg_m(p,ddr,((1U<<bn)-1)<<bp, 0);				\
  x##_write_reg_m(p,port,((1U<<bn)-1)<<bp, ((1U<<bn)-1)<<bp ); HW_EOL(__VA_ARGS__)

#define _hwx_cfio1a_do(x,o,p,bn,bp,k,...)	x##_write_reg_m(p,ddr,((1U<<bn)-1)<<bp, ((1U<<bn)-1)<<bp); HW_EOL(__VA_ARGS__)

#define _hwx_cfio1a_ai(x,o,p,bn,bp,...)		HW_Y(_hwx_cfio1a_ai,HW_G2(_hw_isa_reg,_hw_reg_##o##_##did),0)(x,o,p,bn,bp,__VA_ARGS__)
#define _hwx_cfio1a_ai_0(x,o,p,bn,bp,...)	HW_E(pin `o` does not support analog_input)
#define _hwx_cfio1a_ai_1(x,o,p,bn,bp,k,...)	x( write, _hw_reg_##o##_##did, 1); HW_EOL(__VA_ARGS__)
/* x##_write_reg(o,did,1); DOES NOT WORK: 'o' is not a regular object */

#define _hwx_cfio1a_aipu(x,o,p,bn,bp,...)	HW_Y(_hwx_cfio1a_aipu,HW_G2(_hw_isa_reg,_hw_reg_##o##_##did),0)(x,o,p,bn,bp,__VA_ARGS__)
#define _hwx_cfio1a_aipu_0(x,o,p,bn,bp,...)	HW_E(pin `o` does not support analog_input)
#define _hwx_cfio1a_aipu_1(x,o,p,bn,bp,k,...)				\
  x( write, _hw_reg_##o##_##did, 1);					\
  x##_write_reg_m(p, port, ((1U<<bn)-1)<<bp, ((1U<<bn)-1)<<bp); HW_EOL(__VA_ARGS__)


/**
 * @page atmelavr_io1a
 *
 * `read`:
 *
 * @code
 * uint8_t value = hw( read, pa0 );
 * @endcode
 */
#define _hw_read_io1a(o,i, p,bn,bp,...)				\
  HW_TX( ((_hw_read_reg(p, pin) & (((1<<bn)-1)<<bp))>>bp),	\
	 __VA_ARGS__)


/**
 * @page atmelavr_io1a
 *
 * `write`:
 *
 * @code
 * hw | hwa( write, pa0, value );
 * @endcode
 */
#define _hw_write_io1a(o,i, p,bn,bp, v,...)	\
  HW_TX( _hw_write_reg_m(p, port, ((1UL<<bn)-1)<<bp, (v)<<bp), __VA_ARGS__ )

#define _hwa_write_io1a(o,i, p,bn,bp, v, ...)		\
  HW_TX(_hwa_write__r8(&hwa->p.port, 0xFF,0x00, bn,bp, v),__VA_ARGS__)


/**
 * @page atmelavr_io1a
 *
 * `toggle`
 *
 * @code
 * hw | hwa( toggle, pa0 );	//  Toggle one or several consecutive pins at once
 * @endcode
 */
#define _hw_toggle_io1a(o,i,p,...)		_hw_toggle_io1a_2(_HW_M(p,pin),__VA_ARGS__)
#define _hw_toggle_io1a_2(...)			_hw_toggle_io1a_3(__VA_ARGS__)
#define _hw_toggle_io1a_3(_m1,o,a,r,rc,ra,rwm,rfm,_bn,_bp,bn,bp,...)	\
  HW_TX(_hw_write(_m1,o,a,r,rc,ra,rwm,rfm,bn,bp,(1UL<<bn)-1,),__VA_ARGS__)


#define _hwa_toggle_io1a(o,i, p,...)		_hwa_toggle_io1a_2(_HW_M(p,pin),__VA_ARGS__)
#define _hwa_toggle_io1a_2(...)			_hwa_toggle_io1a_3(__VA_ARGS__)
#define _hwa_toggle_io1a_3(_m1,p,a,r,rw,ra,rwm,rfm,_bn,_bp,bn,bp,...)	\
  HW_TX(_hwa(write,_m1,p,a,r,rw,ra,rwm,rfm,bn,bp,(1UL<<bn)-1),__VA_ARGS__)


/**
 * @page atmelavr_io1a
 * <br>
 */
