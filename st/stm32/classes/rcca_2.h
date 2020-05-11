
/* This file is part of the HWA project.
 * Copyright (c) 2017 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Clocks
 */

#include "sclka_2.h"
#include "plla_2.h"
#include "ahba_2.h"
#include "apba_2.h"
#include "a12a_2.h"
#include "usba_2.h"
#include "hsia_2.h"
#include "hsea_2.h"

/*
 * @page stm32_rcca
 *
 * The `_rcca` class is not used directly. It holds hardware registers shared by
 * several objects to access the device's RCC in order to configure the
 * different clocks of the device.
 *
 * The RCC is also used transparently by several other objects to enable/disable
 * their clocking for power management purpose.
 *
 * @code
 * hw( turn, (rcc,usart1), on );
 * @endcode
 *
 * @code
 * hwa( turn, (rcc,usart1), on );
 * @endcode
 */

/* #define hw_turn__rccen			, _hw_tnrcc */
/* #define _hw_tnrcc(o,r,v,...)		HW_Y(_hw_tnrcc,_hw_state_##v)(v,r,__VA_ARGS__) */
/* #define _hw_tnrcc1(v,r,...)		_hw_write(rcc,r,HW_A1(_hw_state_##v)) */
/* #define _hw_tnrcc0(v,...)		HW_E_ST(v) */

/* #define hwa_turn__rccen			, _hwa_tnrcc */
/* #define _hwa_tnrcc(o,r,v,...)		HW_Y(_hwa_tnrcc,_hw_state_##v)(v,r,__VA_ARGS__) */
/* #define _hwa_tnrcc1(v,r,...)		_hwa_write(rcc,r,HW_A1(_hw_state_##v)) */
/* #define _hwa_tnrcc0(v,...)		HW_E_ST(v) */


/*
 * @page stm32_rcca
 *
 * @section Examples
 *
 * The following shows typical code used at setup to power-on some
 * controllers. Note the various ways of accessing the RCC:
 *
 * @code
 * // Power-on PORTA, USART1, and TIM2
 * //
 * hwa( begin, reset );
 * hwa( turn, (rcc,(pa0,port)), on );
 * hwa( turn, (rcc,usart1), on );
 * hwa( turn, (counter2,rcc), on );
 * hwa( commit );
 * @endcode
 */


/*******************************************************************************
 *									       *
 *	Context management						       *
 *									       *
 *******************************************************************************/

#define _hwa_setup__rcca(o,a)			\
  _hwa_setup_r( o, cr	   );			\
  _hwa_setup_r( o, cfgr	   );			\
  _hwa_setup_r( o, apb2enr );			\
  _hwa_setup_r( o, apb1enr )

#define _hwa_init__rcca(o,a)			\
  _hwa_init_r( o, cr,	   0x00000083 );	\
  _hwa_init_r( o, cfgr,	   0x00000000 );	\
  _hwa_init_r( o, apb2enr, 0x00000000 );	\
  _hwa_init_r( o, apb1enr, 0x00000000 )

#define _hwa_commit__rcca(o,a)		\
  _hwa_commit_r( o, cr	    );		\
  _hwa_commit_r( o, cfgr    );		\
  _hwa_commit_r( o, apb2enr );		\
  _hwa_commit_r( o, apb1enr )
