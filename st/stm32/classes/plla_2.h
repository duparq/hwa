
/* This file is part of the HWA project.
 * Copyright (c) 2017 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief PLL
 */

#define _hw_actions__plla	, (configure,connect,power,stat,write)
#define _hwa_actions__plla	, (configure,connect,power,stat,write)

/**
 * @addtogroup stm32_plla
 *
 * @section stm32_pllaif Interface
 *
 * * Power control
 *
 * @code
 * hw|hwa( power, pll,   on
 *                     | off );
 * @endcode
 */

/* Implemented in stm32/hwa_2.h */

/**
 * @addtogroup stm32_plla
 *
 * * Configuration
 *
 * @note The PLL can not be configured while it is running.
 *
 * @code
 * hw|hwa( configure, pll,
 *
 *	 [ input,        hsi/2
 *		       | hse
 *		       | hse/2, ]
 *
 *	 [ multiplier,   2..16 );	// Any value in the range [ 2..16 ]
 * @endcode
 */
#define hw_configure__plla		, _hw_cfplla
#define _hw_cfplla(o,a,k,...)		do{ HW_BW(_hwx_cfpllain,input,k)(_hw,o,k,__VA_ARGS__) }while(0)

#define hwa_configure__plla		, _hwa_cfplla
#define _hwa_cfplla(o,a,k,...)		do{ HW_BW(_hwx_cfpllain,input,k)(_hwa,o,k,__VA_ARGS__) }while(0)

/*  Optionnal parameter `input`
 */
#define _hwx_cfpllain1(h,o,k,v,...)	HW_BV(_hwx_cfpllain1,cfpllain_,v,h,o,v) (h,o,__VA_ARGS__)//PUSH
#define _hwx_cfpllain1_			_hwx_cfpllain10
#define _hwx_cfpllain10(v,...)		HW_E(HW_EM_XNIL(v,(hsi/2, hse, hse/2)))
#define _hwx_cfpllain11(i,d,h,o,v)					\
  if	  ( i==0 && d==1.0/2 ) h##_write(o,src,0);			\
  else if ( i==1 && d==1.0   ) h##_write(o,xtpresrc,1); /* xtpre=0, src=1 */ \
  else if ( i==1 && d==1.0/2 ) h##_write(o,xtpresrc,3); /* xtpre=1, src=1 */ \
  else HWA_E(HW_EM_VAL(v,input,(hsi/2, hse, hse/2)));			\
  _hwx_cfpllain0 //POP

#define _hw_cfpllain_hsi		, 0, 1.0	// 0:HSI, 1.0/x
#define _hw_cfpllain_hse		, 1, 1.0	// 1:HSE, 1.0/x

#define _hwx_cfpllain0(h,o,k,...)	HW_BW(_hwx_cfpllamul,multiplier,k)(h,o,k,__VA_ARGS__)

/*  Optionnal parameter `multiplier`
 */
#define _hwx_cfpllamul1(h,o,k,v,...)		\
  if (v-1+1<2 || v-1+1>16)			\
    HWA_E(HW_EM_VL(v,(2..16)));			\
  else h##_write(o,mul,((uint8_t)(v)-2));	\
  HW_EOL(__VA_ARGS__)

#define _hwx_cfpllamul0(h,o,...)	HW_EOL(__VA_ARGS__)


/**
 * @addtogroup stm32_plla
 *
 * * Start & stop
 *
 * @code
 * hw|hwa( start, pll );
 * @endcode
 *
 * @code
 * hw|hwa( stop, pll );
 * @endcode
 */
#define hw_start__plla		, _hw_srplla
#define _hw_srplla(o,a,...)	_hw_write(o,on,1) HW_EOL(__VA_ARGS__)

#define hwa_start__plla		, _hwa_srplla
#define _hwa_srplla(o,a,...)	_hwa_write(o,on,1) HW_EOL(__VA_ARGS__)

#define hw_stop__plla		, _hw_spplla
#define _hw_spplla(o,a,...)	_hw_write(o,on,0) HW_EOL(__VA_ARGS__)

#define hwa_stop__plla		, _hwa_spplla
#define _hwa_spplla(o,a,...)	_hwa_write(o,on,0) HW_EOL(__VA_ARGS__)


/**
 * @addtogroup stm32_plla
 *
 * * Status
 *
 * @code
 * // Wait for the PLL to be locked
 * //
 * hw_stat_t(pll) st = hw(stat,pll) ;
 * while ( ! st.ready ) {}
 * @endcode
 */
typedef struct {
  unsigned int _0_24  : 25 ;
  unsigned int ready  :	 1 ;
  unsigned int _26_31 :	 6 ;
} _hw_stplla_t ;

#define hw_stat_t__plla			, _hw_sttplla
#define _hw_sttplla(o,a,...)		 _hw_stplla_t HW_EOL(__VA_ARGS__)

#define hw_stat__plla			, _hw_stplla
#define _hw_stplla(o,a,g,...)		HW_B(_hw_stplla1_,g)(g)
#define _hw_stplla1_0(g)		HW_E(HW_EM_G(g))
#define _hw_stplla1_1(g)		(*(volatile _hw_stplla_t*)HW_ADDRESS((rcc,cr)))
