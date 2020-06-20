
/*  This file is part of the HWA project.
 *  Copyright (c) 2012,2015 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Pin change interrupt controller
 */


/**
 * @page atmelavr_pxa
 * @section atmelavr_pxa_act Actions
 * <br>
 *
 * `enable`, `disable`, `turn` select which pins are monitored (one or several
 * at once):
 *
 * @code
 * hw|hwa( enable, pcic0, (porta,0) );
 * @endcode
 *
 * @code
 * hw|hwa( disable, pcic0, (porta,0) );
 * @endcode
 *
 * @code
 * hw|hwa( turn, pcic0, (porta,0), on | off );
 * @endcode
 */
#define hw_turn__pxa			, _hw_tnpxa
#define _hw_tnpxa(o,a,p,...)		_hwx_tnpxa1(_hw,o,HW_X(p),__VA_ARGS__)

#define hwa_turn__pxa			, _hwa_tnpxa
#define _hwa_tnpxa(o,a,p,...)		_hwx_tnpxa1(_hwa,o,HW_X(p),__VA_ARGS__)

#define hw_enable__pxa			, _hw_enpxa
#define _hw_enpxa(o,a,p,...)		_hwx_tnpxa1(_hw,o,HW_X(p),1,__VA_ARGS__)

#define hwa_enable__pxa			, _hwa_enpxa
#define _hwa_enpxa(o,a,p,...)		_hwx_tnpxa1(_hwa,o,HW_X(p),1,__VA_ARGS__)

#define hw_disable__pxa			, _hw_dspxa
#define _hw_dspxa(o,a,p,...)		_hwx_tnpxa1(_hw,o,HW_X(p),0,__VA_ARGS__)

#define hwa_disable__pxa		, _hwa_dspxa
#define _hwa_dspxa(o,a,p,...)		_hwx_tnpxa1(_hwa,o,HW_X(p),0,__VA_ARGS__)

#define _hwx_tnpxa1(...)		_hwx_tnpxa2(__VA_ARGS__)
#define _hwx_tnpxa2(h,o,c,...)		HW_Y0(_hwx_tnpxa2,c)(h,o,c,__VA_ARGS__)
#define _hwx_tnpxa21(h,o,z,...)		do{}while(0) // p is not an object, error sent by HW_X()
#define _hwx_tnpxa20(h,o,c,...)		HW_YW(_hwx_tnpxa3,_ioa,c)(h,o,c,__VA_ARGS__)
#define _hwx_tnpxa30(h,o,c,p,...)		HW_E(`p` is not an I/O pin)
#define _hwx_tnpxa31(h,o,c,p,po,bn,bp,v,...)	HW_YS(_hwx_tnpxa4,v,h,o,bn,bp,__VA_ARGS__)
#define _hwx_tnpxa40(...)
#define _hwx_tnpxa41(s,h,o,bn,bp,...)					\
  h##_write_m(o,msk,((1U<<bn)-1)<<bp,(((1U<<bn)-1)*s<<bp))		\
    HW_EOL(__VA_ARGS__)


/**
 * @page atmelavr_pxa
 * @section atmelavr_pxa_stat Status
 *
 * The pin change IRQ flag and the enable bit can be accessed through
 * interrupt-related instructions:
 *
 * @code
 * if ( hw( read, (pcic0,irq) ) ) {	// Read pin change flag
 *   hw( clear, (pcic0,irq) );		// Clear pin change flag
 *   hw( disable, (pcic0,irq) );	// Disable pin change IRQ
 * }
 * @endcode
 */


/**
 * @page atmelavr_pxa
 * @section atmelavr_pxa_internals Internals
 *
 * Class `_pxa` objects hold the following hardware registers:
 *
 *  * `msk`: mask of monitored pins
 *
 * and the following logical registers:
 *
 *  * `ie`: pin change IRQ mask
 *  * `if`: pin change IRQ flag
 *
 * These registers are accessible through the @ref public_ins
 * "register access intructions".
 */


/*******************************************************************************
 *									       *
 *	Context management						       *
 *									       *
 *******************************************************************************/

#define _hwa_setup__pxa(o,a)		_hwa_setup_r( o, msk )

#define _hwa_init__pxa(o,a)		_hwa_init_r( o, msk, 0x00 )

#define _hwa_commit__pxa(o,a)		_hwa_commit_r( o, msk )
