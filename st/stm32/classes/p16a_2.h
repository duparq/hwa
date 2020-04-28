
/* This file is part of the HWA project.
 * Copyright (c) 2017 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief GPIO port
 */

/**
 * @page stm32_p16a
 *
 * `power`:
 * @code
 * hw | hwa( power, port0,   on
 *			   | off );
 * @endcode
 * <br>
 * @code
 * hw | hwa( power, (pa0,port),	  on
 *					   | off );
 * @endcode
 */

/*******************************************************************************
 *									       *
 *	Context management						       *
 *									       *
 *******************************************************************************/

#define _hwa_setup__p16a(o,a)			\
  _hwa_setup_r( o, crl	);			\
  _hwa_setup_r( o, crh	);			\
  _hwa_setup_r( o, odr	);			\
  _hwa_setup_r( o, bsrr );			\
  _hwa_setup_r( o, brr	);			\
  _hwa_setup_r( o, lckr );			\
  hwa->o.toggles = 0

#define _hwa_init__p16a(o,a)			\
  _hwa_init_r( o, crl,	0x44444444 );		\
  _hwa_init_r( o, crh,	0x44444444 );		\
  _hwa_init_r( o, odr,	0x00000000 );		\
  _hwa_init_r( o, bsrr, 0x00000000 );		\
  _hwa_init_r( o, brr,	0x00000000 );		\
  _hwa_init_r( o, lckr, 0x00000000 )

#define _hwa_commit__p16a(o,a)					\
  _hwa_commit_r( o, crl	 );						\
  _hwa_commit_r( o, crh	 );						\
  _hwa_commit_r( o, odr	 );						\
  _hwa_commit_r( o, bsrr );						\
  _hwa_commit_r( o, brr	 );						\
  _hwa_commit_r( o, lckr );						\
  _hwa_commit_toggles( &hwa->o )


/*  Toggle pins
 */
HW_INLINE void _hwa_commit_toggles ( hwa_p16a_t *o )
{
  if ( o->toggles ) {
    volatile uint32_t *odr = (volatile uint32_t*)o->odr.a;

    if ( (o->odr.omask & 0xffff) != 0xffff ) {
      o->odr.ovalue = *odr ;
      o->odr.omask = 0xffff ;
    }
    o->odr.ovalue ^= o->toggles ;

    /* *odr = o->odr.ovalue ; DO NOT WRITE THE ODR! */
    volatile uint32_t *bsrr = (volatile uint32_t*)o->bsrr.a;
    *bsrr = (o->toggles & ~o->odr.ovalue)<<16 | (o->toggles & o->odr.ovalue);

    /*	Reset the BSRR to 0
     */
    o->bsrr.ovalue = 0;
    o->bsrr.omask = 0xffffffff ;
    o->bsrr.mmask = 0 ;

    o->toggles = 0 ;
  }
}


/**
 * @page stm32_p16a
 * <br>
 */
