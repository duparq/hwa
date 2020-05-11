
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief I/O
 */

#define hw_configure__ioa		, _hw_cfioa
#define hwa_configure__ioa		, _hwa_cfioa
#define hw_read__ioa			, _hw_read_ioa
#define hw_write__ioa			, _hw_write_ioa
#define hwa_write__ioa			, _hwa_write_ioa
#define hw_toggle__ioa			, _hw_toggle_ioa


/**
 * @page atmelavr_ioa
 * @section atmelavr_ioa_act Actions
 *
 * `configure`:
 *
 * @code
 * hw | hwa( configure,	  pa0,
 *
 *	   [ function,	  gpio, ]			// Default
 *
 *	     mode,	  digital_input
 *			| digital_input_floating	// Default
 *			| digital_input_pullup
 *			| digital_output | digital_output_pushpull
 *			| analog_input
 *			| analog_input_floating
 *			| analog_input_pullup );
 * @endcode
 *
 * @note a digital output in high state enables the pull-up when switched to an
 *	 input mode.
 */

#define _hw_cfioa(...)		_hwx_cfioa(_hw,__VA_ARGS__,,)
#define _hwa_cfioa(...)	_hwx_cfioa(_hwa,__VA_ARGS__,,)

/*  Atmel AVR peripheral controllers are responsible of their I/O pins
 *  configuration, so there is no need for a 'function' argument as it is always
 *  'gpio'. 
 */

/*  Key 'function'
 */
#define _hw_cfioa_fn_gpio

#define _hwx_cfioa(x,o,p,bn,bp,k,...)	HW_Y(_hwx_cfioa_kfn_,_hw_is_function_##k)(x,o,p,bn,bp,k,__VA_ARGS__)
#define _hwx_cfioa_kfn_0(x,o,p,bn,bp,k,...)	HW_Y(_hwx_cfioa_kmd_,_hw_is_mode_##k)(x,o,p,bn,bp,k,__VA_ARGS__)
#define _hwx_cfioa_kfn_1(x,o,p,bn,bp,k,v,...)	HW_Y(_hwx_cfioa_vfn_,_hw_cfioa_fn_##v)(x,o,p,bn,bp,v,__VA_ARGS__)
#define _hwx_cfioa_vfn_0(x,o,p,bn,bp,v,...)	HW_E_NIL(v, (gpio) )
#define _hwx_cfioa_vfn_1(x,o,p,bn,bp,v,k,...)	HW_Y(_hwx_cfioa_kmd_,_hw_is_mode_##k)(x,o,p,bn,bp,k,__VA_ARGS__)

/*  Key 'mode'
 */
#define _hw_cfioa_md_digital_input	, di
#define _hw_cfioa_md_digital_input_floating	, dif
#define _hw_cfioa_md_digital_input_pullup	, dipu
#define _hw_cfioa_md_digital_output	, do
#define _hw_cfioa_md_digital_output_pushpull	, do
#define _hw_cfioa_md_analog_input	, ai
#define _hw_cfioa_md_analog_input_floating	, aif
#define _hw_cfioa_md_analog_input_pullup	, aipu

#define _hwx_cfioa_kmd_0(x,o,p,bn,bp,k,...)	HW_E_NIL(k, (mode) )
#define _hwx_cfioa_kmd_1(x,o,p,bn,bp,k,v,...)	HW_Y(_hwx_cfioa_vmd_,_hw_cfioa_md_##v)(x,o,p,bn,bp,v,__VA_ARGS__)
#define _hwx_cfioa_vmd_0(x,o,p,bn,bp,v,...)	HW_E_NIL(v, (digital_input|digital_output|analog_input) )
#define _hwx_cfioa_vmd_1(x,o,p,bn,bp,v,...)	HW_G2(_hwx_cfioa,HW_A1(_hw_cfioa_md_##v))(x,o,p,bn,bp,__VA_ARGS__)

#define _hwx_cfioa_di(x,o,p,bn,bp,k,...)	x##_write_m(p,ddr,((1U<<bn)-1)<<bp, 0); HW_EOL(__VA_ARGS__)

#define _hwx_cfioa_dif(x,o,p,bn,bp,k,...)				\
  do{ x##_write_m(p,ddr,((1U<<bn)-1)<<bp, 0);				\
    x##_write_m(p,port,((1U<<bn)-1)<<bp, 0 ); }while(0) HW_EOL(__VA_ARGS__)

#define _hwx_cfioa_dipu(x,o,p,bn,bp,k,...)				\
  do{ x##_write_m(p,ddr,((1U<<bn)-1)<<bp, 0);				\
    x##_write_m(p,port,((1U<<bn)-1)<<bp, ((1U<<bn)-1)<<bp ); }while(0) HW_EOL(__VA_ARGS__)

#define _hwx_cfioa_do(x,o,p,bn,bp,k,...)				\
  x##_write_m(p,ddr,((1U<<bn)-1)<<bp, ((1U<<bn)-1)<<bp) HW_EOL(__VA_ARGS__)

#define _hwx_cfioa_ai(x,o,p,bn,bp,...)		HW_Y(_hwx_cfioa_ai_,HW_G2(_hw_isa_reg,hw_##o##_##did),0)(x,o,p,bn,bp,__VA_ARGS__)
#define _hwx_cfioa_ai_0(x,o,p,bn,bp,...)	HW_E(pin `o` does not support analog_input)
#define _hwx_cfioa_ai_1(x,o,p,bn,bp,k,...)	x( write, hw_##o##_##did, 1); HW_EOL(__VA_ARGS__)

/* x##_write(o,did,1); DOES NOT WORK: 'o' is not a regular object */

#define _hwx_cfioa_aipu(x,o,p,bn,bp,...)	HW_Y(_hwx_cfioa_aipu_,HW_G2(_hw_isa_reg,hw_##o##_##did),0)(x,o,p,bn,bp,__VA_ARGS__)
#define _hwx_cfioa_aipu_0(x,o,p,bn,bp,...)	HW_E(pin `o` does not support analog_input)
#define _hwx_cfioa_aipu_1(x,o,p,bn,bp,k,...)				\
  do { x( write, (o,did), 1);						\
    x##_write_m(p, port, ((1U<<bn)-1)<<bp, ((1U<<bn)-1)<<bp); }while(0) HW_EOL(__VA_ARGS__)


/**
 * @page atmelavr_ioa
 *
 * `read`:
 *
 * @code
 * uint8_t value = hw( read, pa0 );
 * @endcode
 */
#define _hw_read_ioa(o, p,bn,bp,...)					\
  ((_hw_read(p, pin) & (((1<<bn)-1)<<bp))>>bp) HW_EOL(__VA_ARGS__)


/**
 * @page atmelavr_ioa
 *
 * `write`:
 *
 * @code
 * hw | hwa( write, pa0, value );
 * @endcode
 */
#define _hw_write_ioa(o, p,bn,bp, v,...)				\
  _hw_write_m(p, port, ((1UL<<bn)-1)<<bp, (v)<<bp) HW_EOL(__VA_ARGS__)

#define _hwa_write_ioa(o, p,bn,bp, v, ...)				\
  _hwa_write__r8(&hwa->p.port, 0xFF,0x00, bn,bp, v) HW_EOL(__VA_ARGS__)


/**
 * @page atmelavr_ioa
 *
 * `toggle`
 *
 * @code
 * hw( toggle, pa0 );		// Toggle pin PA0
 * @endcode
 */
#define _hw_toggle_ioa(o,p,bn,bp,...)	_hw_tgioa01(HW_X(p,pin),bn,bp)
#define _hw_tgioa01(...)			_hw_tgioa02(__VA_ARGS__)
#define _hw_tgioa02(t,...)			_hw_tgioa_##t(__VA_ARGS__)
#define _hw_tgioa__m111(n,o,r,c,a,rwm,rfm,rbn,rbp,bn,bp)	_hw_tgioa(a,bn,bp)


HW_INLINE void _hw_tgioa ( intptr_t a, uint8_t bn, uint8_t bp )
{
  volatile uint8_t *pin = (volatile uint8_t*)a ;

  if ( bn == 1 && a < 0x40 )
    *pin |= 1<<bp ; // Use sbi
  else
    *pin = ((1UL<<bn)-1)<<bp ;
}
