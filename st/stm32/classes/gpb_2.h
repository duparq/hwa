
/* This file is part of the HWA project.
 * Copyright (c) 2021 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief GPIO port
 */

/**
 * @addtogroup stm32_gpb
 * @section stm32_gpbif Interface
 *
 *  * Power control
 *
 * @code
 * hw|hwa( power, PORT,   on
 *			| off );
 * @endcode
 */

/*******************************************************************************
 *									       *
 *	Context management						       *
 *									       *
 *******************************************************************************/

#define _hwa_setup__gpb(o,a)			\
  _hwa_setup_r( o, mode   );			\
  _hwa_setup_r( o, otype  );			\
  _hwa_setup_r( o, ospeed );			\
  _hwa_setup_r( o, pupd   );			\
  _hwa_setup_r( o, odr    );			\
  _hwa_setup_r( o, bsrr   );			\
  _hwa_setup_r( o, lckr   );			\
  _hwa_setup_r( o, afrl   );			\
  _hwa_setup_r( o, afrh   );			\
  hwa->o.toggles = 0

#define _hwa_init__gpb(o,a)			\
  _hwa_init_r( o, mode   , _hwa_gpbmode_##o  );	\
  _hwa_init_r( o, otype  , 0x00000000        );	\
  _hwa_init_r( o, ospeed , _hwa_gpbspeed_##o );	\
  _hwa_init_r( o, pupd   , _hwa_gpbpupd_##o  );	\
  _hwa_init_r( o, odr    , 0x00000000        );	\
  _hwa_init_r( o, bsrr   , 0x00000000        );	\
  _hwa_init_r( o, lckr   , 0x00000000        );	\
  _hwa_init_r( o, afrl   , 0x00000000        );	\
  _hwa_init_r( o, afrh   , 0x00000000        )

#define _hwa_gpbmode_porta		0xA8000000
#define _hwa_gpbmode_portb		0x00000280
#define _hwa_gpbmode_portc		0x00000000
#define _hwa_gpbmode_portd		0x00000000
#define _hwa_gpbmode_porte		0x00000000
#define _hwa_gpbmode_portf		0x00000000
#define _hwa_gpbmode_portg		0x00000000
#define _hwa_gpbmode_porth		0x00000000

#define _hwa_gpbspeed_porta		0x0C000000
#define _hwa_gpbspeed_portb		0x000000C0
#define _hwa_gpbspeed_portc		0x00000000
#define _hwa_gpbspeed_portd		0x00000000
#define _hwa_gpbspeed_porte		0x00000000
#define _hwa_gpbspeed_portf		0x00000000
#define _hwa_gpbspeed_portg		0x00000000
#define _hwa_gpbspeed_porth		0x00000000

#define _hwa_gpbpupd_porta		0x64000000
#define _hwa_gpbpupd_portb		0x00000100
#define _hwa_gpbpupd_portc		0x00000000
#define _hwa_gpbpupd_portd		0x00000000
#define _hwa_gpbpupd_porte		0x00000000
#define _hwa_gpbpupd_portf		0x00000000
#define _hwa_gpbpupd_portg		0x00000000
#define _hwa_gpbpupd_porth		0x00000000

#define _hwa_commit__gpb(o,a)			\
  _hwa_commit_r( o, otype  );			\
  _hwa_commit_r( o, ospeed );			\
  _hwa_commit_r( o, pupd   );			\
  _hwa_commit_r( o, afrl   );			\
  _hwa_commit_r( o, afrh   );			\
  _hwa_commit_r( o, odr    );			\
  _hwa_commit_r( o, bsrr   );			\
  _hwa_commit_r( o, mode   );			\
  _hwa_commit_toggles( &hwa->o );		\
  _hwa_commit_r( o, lckr   )


/*  Toggle pins
 */
HW_INLINE void _hwa_commit_toggles ( hwa_gpb_t *o )
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
