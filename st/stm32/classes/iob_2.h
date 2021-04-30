
/* This file is part of the HWA project.
 * Copyright (c) 2021 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief I/O
 */

#define _hw_actions__iob		, (configure,read,toggle,write)
#define _hwa_actions__iob		, (configure,toggle,write)

/**
 * @ingroup stm32_classes
 * @addtogroup stm32_iob
 *
 * * Configuration
 *
 * @code
 * hw|hwa( configure,   (porta,0),
 *       
 *       [ function,    gpio, ]					// Default
 *       
 *         mode,        digital_input | digital_input_floating	// Default
 *       	      | digital_input_pullup
 *       	      | digital_input_pulldown
 *       	      | analog_input
 *       	      | digital_output | digital_output_pushpull
 *       	      | digital_output_opendrain,
 *       
 *         // Only for output modes
 *         //
 *       [ frequency,   low | lowest
 *       	      | medium
 *       	      | fast
 *       	      | high | highest ] );
 * @endcode
 */
#define hw_configure__iob			, _hw_cfiob
#define _hw_cfiob(o,p,...)						\
  do {									\
    uint8_t __attribute__((unused)) af=0xFF, mode=0xFF, pupd=0xFF, otype=0xFF, ospeed=0xFF ; \
    struct { uint8_t commit ; hwa_gpb_t p ; } hwa_st ;			\
    hwa_t *hwa = (hwa_t*)&hwa_st ;					\
    _hwa_setup_o(p);							\
    _hwa_cfiob_(o,p,__VA_ARGS__);					\
    hwa_st.commit = 1 ; _hwa_commit_o(p);				\
  }while(0)

#define hwa_configure__iob			, _hwa_cfiob
#define _hwa_cfiob(...)							\
  do{									\
    uint8_t __attribute__((unused)) af=0xFF, mode=0xFF, pupd=0xFF, otype=0xFF, ospeed=0xFF ; \
    _hwa_cfiob_(__VA_ARGS__);						\
  }while(0)



#define _hwa_cfiob_(o,p,bn,bp,k,...)		HW_BW(_hwa_cfiobfn,function,k)(o,p,bn,bp,k,__VA_ARGS__)

/*	Function?
 */
#define _hwa_cfiobfn0(o,p,bn,bp,k,...)		HW_BW(_hwa_cfiobmd,mode,k)(df,o,p,bn,bp,k,__VA_ARGS__)
#define _hwa_cfiobfn1(o,p,bn,bp,k,v,...)	HW_BW(_hwa_cfiobfn1,gpio,v)(o,p,bn,bp,v,__VA_ARGS__)
/*
 *		GPIO
 */
#define _hwa_cfiobfn11(o,p,bn,bp,v,k,...)	HW_BW(_hwa_cfiobmd,mode,k)(df,o,p,bn,bp,k,__VA_ARGS__)
/*
 *		Alternate?
 */
#define _hwa_cfiobfn10(o,p,bn,bp,...)		HW_BW(_hwa_cfiobfn2,1,bn)(o,p,bn,bp,__VA_ARGS__)
/*
 *		Can't set alternate function to multiple pins
 */
#define _hwa_cfiobfn20(o,p,bn,bp,...)		HW_E(error)
/*
 *		Single pin, is function '(...)'?
 */
#define _hwa_cfiobfn21(o,p,bn,bp,v,...)		HW_BP(_hwa_cfiobfn3,v)(o,p,bn,bp,v,__VA_ARGS__)
/*
 *		Function is '(...)', insert expanded signal name
 */
#define _hwa_cfiobfn31(o,p,bn,bp,v,...)		_hwa_cfiobfn32(o,p,bn,bp,HW_G2 v,v,__VA_ARGS__)
#define _hwa_cfiobfn32(...)			_hwa_cfiobfn4(__VA_ARGS__)
/*
 *		Function is not '(...)', copy signal name
 */
#define _hwa_cfiobfn30(o,p,bn,bp,v,...)		_hwa_cfiobfn4(o,p,bn,bp,v,v,__VA_ARGS__)
/*
 *		Verify function name for pin
 */
#define _hwa_cfiobfn4(o,p,bn,bp,vx,v,...)	HW_BV(_hwa_cfiobfn4,af_##o##_,vx,v,o)  (o,p,bn,bp,__VA_ARGS__)//PUSH
#define _hwa_cfiobfn40(vx,v,o)			HW_E(HW_EM_XNIL(v,_hw_af_##o)) HW_EAT//POP
#define _hwa_cfiobfn41(r,v,o)			af=r; _hwa_cfiobfn42//POP
#define _hwa_cfiobfn42(o,p,bn,bp,k,...)		HW_BW(_hwa_cfiobmd,mode,k)(af,o,p,bn,bp,k,__VA_ARGS__)

/*
 *	'mode'. Can drop 'o'.
 */
#define _hwa_cfiobmd0(f,o,p,bn,bp,k,v,...)	HW_E(HW_EM_AN(k,mode))

#define _hwa_cfiobmd1(...)			_hwa_cfiobmd2(__VA_ARGS__)
#define _hwa_cfiobmd2(f,o,p,bn,bp,k,v,...)	HW_BV(_hwa_cfiobmd2,cfiob_##f##_,v,)(p,bn,bp,__VA_ARGS__)//PUSH
#define _hwa_cfiobmd20(v,...)						\
  HW_E(HW_EM_VAL(v,mode,(digital_input,digital_input_floating,digital_input_pullup, \
			 digital_input_pulldown,analog_input,digital_output, \
			 digital_output_pushpull, digital_output_opendrain)))		HW_EAT//POP
#define _hwa_cfiobmd21(code,branch,...)		code branch//POP
/*
 *  Default/alternate function
 *
 *	mode		otype		ospeed		pupd
 *
 *	0 input		0 push-pull	0 low		0 none
 *	1 output	1 open-drain	1 medium	1 pull-up
 *	2 alt func			2 fast		2 pull-down
 *	3 analog			3 high
 *
 *						, code             , branch
 */
#define _hw_cfiob_df_digital_input		, mode=0;          , _hwa_cfiob9
#define _hw_cfiob_df_digital_input_floating	, mode=0; pupd=0;  , _hwa_cfiob9
#define _hw_cfiob_df_digital_input_pullup	, mode=0; pupd=1;  , _hwa_cfiob9
#define _hw_cfiob_df_digital_input_pulldown	, mode=0; pupd=2;  , _hwa_cfiob9
#define _hw_cfiob_df_digital_output		, mode=1;          , _hwa_cfiobfq
#define _hw_cfiob_df_digital_output_pushpull	, mode=1; otype=0; , _hwa_cfiobfq
#define _hw_cfiob_df_digital_output_opendrain	, mode=1; otype=1; , _hwa_cfiobfq
#define _hw_cfiob_df_analog_input		, mode=3;          , _hwa_cfiob9

#define _hw_cfiob_af_digital_input		, mode=2;          , _hwa_cfiob9
#define _hw_cfiob_af_digital_input_floating	, mode=2; pupd=0;  , _hwa_cfiob9
#define _hw_cfiob_af_digital_input_pullup	, mode=2; pupd=1;  , _hwa_cfiob9
#define _hw_cfiob_af_digital_input_pulldown	, mode=2; pupd=2;  , _hwa_cfiob9
#define _hw_cfiob_af_digital_output		, mode=2;          , _hwa_cfiobfq
#define _hw_cfiob_af_digital_output_pushpull	, mode=2; otype=0; , _hwa_cfiobfq
#define _hw_cfiob_af_digital_output_opendrain	, mode=2; otype=1; , _hwa_cfiobfq
#define _hw_cfiob_af_analog_input		, mode=2;          , _hwa_cfiob9

/*
 *  Optionnal argument 'frequency' (only for output modes)
 */
#define _hw_cfiob_fq_lowest			, 0
#define _hw_cfiob_fq_low			, 0
#define _hw_cfiob_fq_medium			, 1
#define _hw_cfiob_fq_fast			, 2
#define _hw_cfiob_fq_high			, 3
#define _hw_cfiob_fq_highest			, 3

#define _hwa_cfiobfq(p,bn,bp,k,...)		HW_BW(_hwa_cfiobfq,frequency,k)(p,bn,bp,k,__VA_ARGS__)
#define _hwa_cfiobfq0(p,bn,bp,k,...)		HW_B(_hwa_cfiobfq0,k)(p,bn,bp,k,__VA_ARGS__)
#define _hwa_cfiobfq01(p,bn,bp,k,...)		_hwa_do_cfiob( &hwa->p, bn, bp, af, mode, pupd, otype, ospeed )
#define _hwa_cfiobfq00(p,bn,bp,k,...)		HW_E(HW_EM_AN(k,frequency))

#define _hwa_cfiobfq1(p,bn,bp,k,v,...)		HW_BV(_hwa_cfiobfq1,cfiob_fq_,v,)(p,bn,bp,__VA_ARGS__)
#define _hwa_cfiobfq11(r,...)			ospeed=r; _hwa_cfiob9
#define _hwa_cfiobfq10(v,...)			HW_E(HW_EM_VAL(v,frequency,(lowest,2MHz,10MHz,50MHz,highest))) HW_EAT

#define _hwa_cfiob9(p,bn,bp,...)		HW_B(_hwa_cfiob9,__VA_ARGS__)(p,bn,bp,__VA_ARGS__)
#define _hwa_cfiob90(p,bn,bp,g,...)		HW_E(HW_EM_G(g))
#define _hwa_cfiob91(p,bn,bp,g,...)		_hwa_do_cfiob( &hwa->p, bn, bp, af, mode, pupd, otype, ospeed )


HW_INLINE void _hwa_do_cfiob_( hwa_gpb_t *p, uint8_t i,
			       uint8_t af, uint8_t mode, uint8_t pupd, uint8_t otype, uint8_t ospeed )
{
  uint32_t mask, value ;
  
  if ( af != 0xFF ) {
    value = af ;
    if ( i < 8 ) {
      mask = 0x0F<<(4*i);
      value <<= (4*i);
      p->afrl.mmask |= mask ;
      p->afrl.mvalue = (p->afrl.mvalue & ~mask) | value ;
    }
    else {
      mask = 0x0F<<(4*(i-8));
      value <<= (4*(i-8));
      p->afrh.mmask |= mask ;
      p->afrh.mvalue = (p->afrh.mvalue & ~mask) | value ;
    }
  }
  
  if ( mode != 0xFF ) {
    value = mode ;
    mask = 3UL<<(2*i);
    value <<= (2*i);
    p->mode.mmask |= mask ;
    p->mode.mvalue = (p->mode.mvalue & ~mask) | value ;
  }

  if ( otype != 0xFF ) {
    value = otype ;
    mask = 1UL<<i;
    value <<= i;
    p->otype.mmask |= mask ;
    p->otype.mvalue = (p->otype.mvalue & ~mask) | value ;
  }

  if ( ospeed != 0xFF ) {
    value = ospeed ;
    mask = 3UL<<(2*i);
    value <<= (2*i);
    p->ospeed.mmask |= mask ;
    p->ospeed.mvalue = (p->ospeed.mvalue & ~mask) | value ;
  }

  if ( pupd != 0xFF ) {
    value = pupd ;
    mask = 3UL<<(2*i);
    value <<= (2*i);
    p->pupd.mmask |= mask ;
    p->pupd.mvalue = (p->pupd.mvalue & ~mask) | value ;
  }
}


HW_INLINE void _hwa_do_cfiob( hwa_gpb_t *p, uint8_t bn, uint8_t bp,
			      uint8_t af, uint8_t mode, uint8_t pupd, uint8_t otype, uint8_t ospeed )
{
  uint16_t mask = ((1UL<<bn)-1)<<bp ;
  if ( mask & 0x0001 ) _hwa_do_cfiob_(p, 0,af,mode,pupd,otype,ospeed);
  if ( mask & 0x0002 ) _hwa_do_cfiob_(p, 1,af,mode,pupd,otype,ospeed);
  if ( mask & 0x0004 ) _hwa_do_cfiob_(p, 2,af,mode,pupd,otype,ospeed);
  if ( mask & 0x0008 ) _hwa_do_cfiob_(p, 3,af,mode,pupd,otype,ospeed);
  if ( mask & 0x0010 ) _hwa_do_cfiob_(p, 4,af,mode,pupd,otype,ospeed);
  if ( mask & 0x0020 ) _hwa_do_cfiob_(p, 5,af,mode,pupd,otype,ospeed);
  if ( mask & 0x0040 ) _hwa_do_cfiob_(p, 6,af,mode,pupd,otype,ospeed);
  if ( mask & 0x0080 ) _hwa_do_cfiob_(p, 7,af,mode,pupd,otype,ospeed);
  if ( mask & 0x0100 ) _hwa_do_cfiob_(p, 8,af,mode,pupd,otype,ospeed);
  if ( mask & 0x0200 ) _hwa_do_cfiob_(p, 9,af,mode,pupd,otype,ospeed);
  if ( mask & 0x0400 ) _hwa_do_cfiob_(p,10,af,mode,pupd,otype,ospeed);
  if ( mask & 0x0800 ) _hwa_do_cfiob_(p,11,af,mode,pupd,otype,ospeed);
  if ( mask & 0x1000 ) _hwa_do_cfiob_(p,12,af,mode,pupd,otype,ospeed);
  if ( mask & 0x2000 ) _hwa_do_cfiob_(p,13,af,mode,pupd,otype,ospeed);
  if ( mask & 0x4000 ) _hwa_do_cfiob_(p,14,af,mode,pupd,otype,ospeed);
  if ( mask & 0x8000 ) _hwa_do_cfiob_(p,15,af,mode,pupd,otype,ospeed);
}



/**
 * @addtogroup stm32_iob
 *
 * * Read
 *
 * @code
 * uint8_t value = hw( read, (porta,0) );
 * @endcode
 */
#define hw_read__iob			, _hw_rdiob
#define _hw_rdiob(o,p,bn,bp,...)	HW_B(_hw_rdiob_,__VA_ARGS__)(p,bn,bp,__VA_ARGS__,)
#define _hw_rdiob_0(p,bn,bp,g,...)	HW_E(HW_EM_G(g))
#define _hw_rdiob_1(p,bn,bp,...)	( (_hw_read(p,idr) & ((1UL<<bn)-1)) >> bp )


/**
 * @addtogroup stm32_iob
 *
 * * Toggle
 *
 * Toggles one or several consecutive pins at once.
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
#define hw_toggle__iob			, _hw_tgiob
#define _hw_tgiob(o,p,bn,bp,g,...)		HW_B(_hw_tgiob_,g)(p,bn,bp,g)
#define _hw_tgiob_0(p,bn,bp,g)			HW_E(HW_EM_G(g))
#define _hw_tgiob_1(p,bn,bp,g)						\
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
 * @addtogroup stm32_iob
 *
 * @code
 * hwa( toggle, (porta,0) );	   //  Register PA0 for toggling
 * hwa( toggle, (porta,4) );	   //  Register PA4 for toggling
 * hwa( commit );		   //  Toggle PA0 and PA4 at once
 * @endcode
 */
#define hwa_toggle__iob			, _hwa_tgiob
#define _hwa_tgiob(o,p,bn,bp,g,...)	HW_B(_hwa_tgiob_,g)(p,bn,bp,g)
#define _hwa_tgiob_0(p,bn,bp,g)		HW_E(HW_EM_G(g))
#define _hwa_tgiob_1(p,bn,bp,g)		hwa->p.toggles |= (((1UL<<bn)-1) << bp)


/**
 * @addtogroup stm32_iob
 *
 * * Write
 *
 * @code
 * hw|hwa( write, (porta,0), 0 );
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
#define hw_write__iob				, _hw_wriob
#define _hw_wriob(o,p,bn,bp,v,g,...)		HW_B(_hwx_wriob1_,v)(_hw,p,bn,bp,v,g)

#define hwa_write__iob				, _hwa_wriob
#define _hwa_wriob(o,p,bn,bp,v,g,...)		HW_B(_hwx_wriob1_,v)(_hwa,p,bn,bp,v,g)

#define _hwx_wriob1_1(x,p,bn,bp,v,g)		HW_E(HW_EM_V)
#define _hwx_wriob1_0(x,p,bn,bp,v,g)		HW_B(_hwx_wriob2_,g)(x,p,bn,bp,v,g)
#define _hwx_wriob2_0(x,p,bn,bp,v,g)		HW_E(HW_EM_G(g))
#define _hwx_wriob2_1(x,p,bn,bp,v,g)					\
  { uint32_t v32 = (v); /* v could be volatile, boolean expr... */	\
    x##_write_m( p, bsrr, 0xffffffff,					\
		 ((((1UL<<bn)-1)<<bp) & (~v32)<<bp)<<16 |		\
		 ((((1UL<<bn)-1)<<bp) & ( v32)<<bp) ); }
