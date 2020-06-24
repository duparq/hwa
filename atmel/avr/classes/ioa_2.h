
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief I/O
 */


/**
 * @addtogroup atmelavr_ioa
 * @section atmelavr_ioa_act Actions
 *
 * <br><br>hw( configure, IO, ... ) and hwa( configure, IO, ... ) configure an IO:
 *
 * @code
 * hw | hwa( configure,	  (porta,0),
 *
 *	   [ function,	  gpio, ]			// Default, no other choice
 *
 *	     mode,	  digital_input
 *			| digital_input_floating	// Reset value
 *			| digital_input_pullup
 *			| digital_output | digital_output_pushpull
 *			| analog_input
 *			| analog_input_floating
 *			| analog_input_pullup
 * );
 * @endcode
 *
 * @note Atmel AVR peripheral controllers take care of their I/O configuration,
 *       so there is no need for a 'function' parameter for IOs as it is always
 *       'gpio'.
 *
 * @note A digital output in high state enables its pull-up when switched to an input.
 */

/**
 * @ingroup hwa_pri
 *
 * @todo Using _hw() and _hwa() prevents external objects such as HW_SWUARTA()
 * from using them to configure their IOs. Should revert to _hw_write_m(), _hwa_write_m()...?
 */
#define hw_configure__ioa		, _hw_cfioa
#define _hw_cfioa(...)			do{ _hw_cfioa1(_hw,__VA_ARGS__,,) }while(0)

#define hwa_configure__ioa		, _hwa_cfioa
#define _hwa_cfioa(...)			do{ _hw_cfioa1(_hwa,__VA_ARGS__,,) }while(0)

/*  Handle not-connected pins
 */
#define _hw_cfioa1(h,o,p,bn,bp,...)	HW_BV(_hw_cfioa1,p,_ncmsk,bn,bp) (h,o,p,bn,bp,__VA_ARGS__) // PUSH
#define _hw_cfioa10(...)		_hw_cfioafn // POP
#define _hw_cfioa11(v,bn,bp)		if ( (v) & (((1<<bn)-1)<<bp) ) HWA_E(HW_EM_IONC); _hw_cfioafn // POP

/*  Optionnal key 'function'
 */
#define _hw_cfioafn(h,o,p,bn,bp,k,...)		HW_BW(_hw_cfioafn,function,k)(h,o,p,bn,bp,k,__VA_ARGS__)
#define _hw_cfioafn0				_hw_cfioamd
#define _hw_cfioafn1(h,o,p,bn,bp,k,v,...)	HW_BV(_hw_cfioafn1,_hw_ioafn_,v,)(h,o,p,bn,bp,__VA_ARGS__) // PUSH
#define _hw_cfioafn10(...)			HW_E(HW_EM_VAL(v,function,(gpio)) HW_EAT // POP
#define _hw_cfioafn11(...)			_hw_cfioamd

#define _hw_ioafn_gpio			, 1

/*  Key 'mode'
 */
#define _hw_cfioamd(h,o,p,bn,bp,k,...)		HW_BW(_hw_cfioamd,mode,k)(h,o,p,bn,bp,k,__VA_ARGS__)
#define _hw_cfioamd0(h,o,p,bn,bp,k,...)		HW_E(HW_EM_AN(k,mode))
#define _hw_cfioamd1(h,o,p,bn,bp,k,v,...)	HW_BV(_hw_cfioamd1,ioamd_,v,)(h,o,p,bn,bp,__VA_ARGS__) // PUSH
#define _hw_cfioamd10(v,...)			HW_E(HW_EM_VAL(v,mode,(digital_input, digital_input_floating, \
								       digital_input_pullup, digital_output, \
								       digital_output_pushpull, analog_input, \
								       analog_input_floating, analog_input_pullup ))) \
    HW_EAT // POP
#define _hw_cfioamd11(v,...)			v // POP

#define _hw_ioamd_digital_input			, _hw_cfioamd_di
#define _hw_ioamd_digital_input_floating	, _hw_cfioamd_dif
#define _hw_ioamd_digital_input_pullup		, _hw_cfioamd_dipu
#define _hw_ioamd_digital_output		, _hw_cfioamd_do
#define _hw_ioamd_digital_output_pushpull	, _hw_cfioamd_do
#define _hw_ioamd_analog_input			, _hw_cfioamd_ai
#define _hw_ioamd_analog_input_floating		, _hw_cfioamd_aif
#define _hw_ioamd_analog_input_pullup		, _hw_cfioamd_aipu

#define _hw_cfioamd_di(h,o,p,bn,bp,...)		h##_write_m(p,ddr,((1U<<bn)-1)<<bp, 0); HW_EOL(__VA_ARGS__)
#define _hw_cfioamd_dif(h,o,p,bn,bp,...)			\
  h##_write_m(p,ddr,((1U<<bn)-1)<<bp, 0);			\
  h##_write_m(p,port,((1U<<bn)-1)<<bp, 0 ); HW_EOL(__VA_ARGS__)

#define _hw_cfioamd_dipu(h,o,p,bn,bp,...)				\
  h##_write_m(p,ddr,((1U<<bn)-1)<<bp, 0);				\
  h##_write_m(p,port,((1U<<bn)-1)<<bp, ((1U<<bn)-1)<<bp ); HW_EOL(__VA_ARGS__)

#define _hw_cfioamd_do(h,o,p,bn,bp,...)				\
  h##_write_m(p,ddr,((1U<<bn)-1)<<bp, ((1U<<bn)-1)<<bp ); HW_EOL(__VA_ARGS__)

#define _hw_cfioamd_ai(h,o,p,bn,bp,...)		_hw_cfioamd_ai1(h,o,HW_X(o,did))
#define _hw_cfioamd_ai1(...)			_hw_cfioamd_ai2(__VA_ARGS__)
#define _hw_cfioamd_ai2(h,o,x,...)		HW_BW(_hw_cfioamd_ai2_,_m11,x)(h,o,x,__VA_ARGS__)
#define _hw_cfioamd_ai2_0(h,o,...)		HW_E(HW_EM_OAVI(o,mode,analog_input))
#define _hw_cfioamd_ai2_1(h,o,c,...)		h##_write__m11( __VA_ARGS__, 1, );

#define _hw_cfioamd_aipu(h,o,p,bn,bp,...)	_hw_cfioamd_aipu1(h,o,p,bn,bp,HW_X(o,did))
#define _hw_cfioamd_aipu1(...)			_hw_cfioamd_aipu2(__VA_ARGS__)
#define _hw_cfioamd_aipu2(h,o,p,bn,bp,x,...)	HW_BW(_hw_cfioamd_aipu2_,_m11,x)(h,o,p,bn,bp,x,__VA_ARGS__)
#define _hw_cfioamd_aipu2_0(h,o,...)		HW_E(HW_EM_OAVI(o,mode,analog_input_pullup))
#define _hw_cfioamd_aipu2_1(h,o,p,bn,bp,c,...)			\
  h##_write__m11( __VA_ARGS__, 1, );				\
  h##_write_m( p, port, ((1U<<bn)-1)<<bp, ((1U<<bn)-1)<<bp );


/**
 * @addtogroup atmelavr_ioa
 *
 * <br><br>hw( read, IO, ... ) returns the state of the IO:
 *
 * @code
 * uint8_t value = hw( read, (porta,0) );
 * @endcode
 */
#define hw_read__ioa			, _hw_rdioa

/*  Handle not-connected pins
 */
#define _hw_rdioa(o,p,bn,bp,...)	HW_BV(_hw_rdioa,p,_ncmsk,bn,bp) (o,p,bn,bp,__VA_ARGS__) // PUSH
#define _hw_rdioa0(...)			_hw_rdioa2 // POP
#define _hw_rdioa1(v,bn,bp)		if ( (v) & (((1<<bn)-1)<<bp) ) HWA_E(HW_EM_IONC); _hw_rdioa2 // POP
#define _hw_rdioa2(o,p,bn,bp,...)	_hw(readnp,(p,pin),bn,bp) HW_EOL(__VA_ARGS__)


/**
 * @addtogroup atmelavr_ioa
 *
 * <br><br>hw( write, IO, value ) and hwa( write, IO, value ) set the state of an IO:
 *
 * @code
 * hw | hwa( write, (porta,0), 1 );	// PA0 = 1
 * hw | hwa( write, (portb,2,4), 2 );	// PB5,PB4 = 1,0
 * @endcode
 */
#define hw_write__ioa			, _hw_wrioa
#define _hw_wrioa(o,p,bn,bp,...)	HW_BV(_hw_wrioa,p,_ncmsk,bn,bp) (_hw,o,p,bn,bp,__VA_ARGS__) // PUSH

#define hwa_write__ioa			, _hwa_wrioa
#define _hwa_wrioa(o,p,bn,bp,...)	HW_BV(_hw_wrioa,p,_ncmsk,bn,bp) (_hwa,o,p,bn,bp,__VA_ARGS__) // PUSH

#define _hw_wrioa0(...)			_hw_wrioa2 // POP
#define _hw_wrioa1(m,bn,bp)		if ( (m) & (((1UL<<bn)-1)<<bp) ) HWA_E(HW_EM_IONC); _hw_wrioa2 // POP
#define _hw_wrioa2(h,o,p,bn,bp,v,...)	h(writenp,(p,port),bn,bp,v) HW_EOL(__VA_ARGS__)


/**
 * @addtogroup atmelavr_ioa
 *
 * <br><br>hw( set, IO ) and hwa( set, IO ) set all the bits of the IO to 1:
 *
 * @code
 * hw | hwa( set, (porta,0) );		// PA0 = 1
 * hw | hwa( set, (portb,2,4) );	// PB5,PB4 = 1,1
 * @endcode
 */
/* #define hw_set__ioa			, _hw_set_ioa */
/* #define _hw_set_ioa(o,p,bn,bp,...)	_hw_write_m(p, port, ((1UL<<bn)-1)<<bp, ((1UL<<bn)-1)<<bp) HW_EOL(__VA_ARGS__) */

/* #define hwa_set__ioa			, _hwa_set_ioa */
/* #define _hwa_set_ioa(o,p,bn,bp,...)	_hwa_write__r8(&hwa->p.port,0xFF,0x00,bn,bp,((1UL<<bn)-1)) HW_EOL(__VA_ARGS__) */

#define hw_set__ioa			, _hw_set_ioa
#define _hw_set_ioa(o,p,bn,bp,...)	HW_BV(_hw_wrioa,p,_ncmsk,bn,bp) (_hw,o,p,bn,bp,(1UL<<bn)-1,__VA_ARGS__)

#define hwa_set__ioa			, _hwa_set_ioa
#define _hwa_set_ioa(o,p,bn,bp,...)	HW_BV(_hw_wrioa,p,_ncmsk,bn,bp) (_hwa,o,p,bn,bp,(1UL<<bn)-1,__VA_ARGS__)


/**
 * @addtogroup atmelavr_ioa
 *
 * <br><br>hw( clear, IO ) and hwa( clear, IO ) clear all the bits of the IO:
 *
 * @code
 * hw | hwa( clear, (porta,0) );	// PA0 = 0
 * hw | hwa( clear, (portb,2,4) );	// PB5,PB4 = 0,0
 * @endcode
 */
/* #define hw_clear__ioa			, _hw_clear_ioa */
/* #define _hw_clear_ioa(o,p,bn,bp,...)	_hw_write_m(p, port, ((1UL<<bn)-1)<<bp, 0) HW_EOL(__VA_ARGS__) */

/* #define hwa_clear__ioa			, _hwa_clear_ioa */
/* #define _hwa_clear_ioa(o,p,bn,bp,...)	_hwa_write__r8(&hwa->p.port,0xFF,0x00,bn,bp,0) HW_EOL(__VA_ARGS__) */

#define hw_clear__ioa			, _hw_clrioa
#define _hw_clrioa(o,p,bn,bp,...)	HW_BV(_hw_wrioa,p,_ncmsk,bn,bp) (_hw,o,p,bn,bp,0,__VA_ARGS__)

#define hwa_clear__ioa			, _hwa_clrioa
#define _hwa_clrioa(o,p,bn,bp,...)	HW_BV(_hw_wrioa,p,_ncmsk,bn,bp) (_hwa,o,p,bn,bp,0,__VA_ARGS__)


/**
 * @addtogroup atmelavr_ioa
 *
 * <br><br>hw( toggle, IO ) and hwa( toggle, IO ) toggle all the bits of the IO:
 *
 * @code
 * hw( toggle, (porta,0) );		// Toggle pin PA0
 * @endcode
 *
 * @code
 * hwa( toggle, (porta,0) );		//  Register PA0 for toggling
 * hwa( toggle, (porta,2,3) );		//  Register PA4 and PA3 for toggling
 * hwa( commit );	   		//  Toggle PA0, PA4 and PA3 at once
 * @endcode
 */
/* #define hw_toggle__ioa						, _hw_toggle_ioa */
/* #define _hw_toggle_ioa(o,p,bn,bp,...)				_hw_tgioa01(HW_X(p,pin),bn,bp) */
/* #define _hw_tgioa01(...)					_hw_tgioa02(__VA_ARGS__) */
/* #define _hw_tgioa02(t,...)					_hw_tgioa_##t(__VA_ARGS__) */
/* #define _hw_tgioa__m11(n,o,r,c,a,rwm,rfm,rbn,rbp,bn,bp)		_hw_tgioa(a,bn,bp) */

#define hw_toggle__ioa			, _hw_tgioa
#define _hw_tgioa(o,p,bn,bp,...)	HW_BV(_hw_tgioa,p,_ncmsk,bn,bp) (_hw,o,p,bn,bp,__VA_ARGS__) // PUSH

#define hwa_toggle__ioa			, _hwa_tgioa
#define _hwa_tgioa(o,p,bn,bp,...)	HW_BV(_hw_tgioa,p,_ncmsk,bn,bp) (_hwa,o,p,bn,bp,__VA_ARGS__) // PUSH

#define _hw_tgioa0(...)			_hw_tgioa2 // POP
#define _hw_tgioa1(m,bn,bp)		if ( (m) & (((1UL<<bn)-1)<<bp) ) HWA_E(HW_EM_IONC); _hw_tgioa2 // POP
#define _hw_tgioa2(h,o,p,bn,bp,v,...)	h(writenp,(p,pin),bn,bp,(1UL<<bn)-1) HW_EOL(__VA_ARGS__)



/* HW_INLINE void _hw_tgioa ( intptr_t a, uint8_t bn, uint8_t bp ) */
/* { */
/*   volatile uint8_t *pin = (volatile uint8_t*)a ; */

/*   if ( bn == 1 && a < 0x40 ) */
/*     *pin |= 1<<bp ; // Use sbi */
/*   else */
/*     *pin = ((1UL<<bn)-1)<<bp ; */
/* } */

/* #define _hwa_tgioa(o,p,bn,bp,g,...)	HW_B(_hwa_tgioa_,g)(p,bn,bp,g) */
/* #define _hwa_tgioa_0(p,bn,bp,g)		HW_E(HW_EM_G(g)) */
/* #define _hwa_tgioa_1(p,bn,bp,g)		hwa->p.toggles |= (((1UL<<bn)-1) << bp) */
