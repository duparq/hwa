
/* This file is part of the HWA project.
 * Copyright (c) 2021 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief PLL
 */

#define _hw_actions__pllb	, (configure,start,stop)
#define _hwa_actions__pllb	, (configure,start,stop)

/**
 * @addtogroup stm32_pllb
 *
 * @section stm32_pllbif Interface
 *
 * * Configuration
 *
 * @note The PLL can not be configured once it is running.
 *
 * @code
 * hw|hwa( configure,    pll,
 *
 *	   input,        hse [ / 2..63 ]
 *		       | hsi [ / 2..63 ]
 *
 *	   multiplier,   50..432,
 *
 *         sysclkdiv,    2 | 4 | 6 | 8,
 *
 *	 [ 48MHzdiv,     2..15 ]
 * }
 * @endcode
 */
#define hw_configure__pllb		, _hw_cfpllb
#define _hw_cfpllb(...)							\
  do{									\
    struct { uint8_t commit ; hwa_rccb_t rcc ; } hwa_st ;		\
    hwa_t *hwa = (hwa_t*)&hwa_st ;					\
    _hwa_setup_o(rcc);							\
    _hwa_cfpllb(__VA_ARGS__);						\
    hwa_st.commit = 1 ; _hwa_commit_o(rcc);				\
  }while(0)


#define hwa_configure__pllb		, _hwa_cfpllb
#define _hwa_cfpllb(o,a,k,...)		do{ HW_BW(_hwa_cfpllbin,input,k)(o,k,__VA_ARGS__) }while(0)

/*  Argument `input`
 */
#define _hwa_cfpllbin0(o,k,...)		HW_E(HW_EM_XNIL(k,(input)))
#define _hwa_cfpllbin1(o,k,v,...)	HW_BV(_hwa_cfpllbin1,cfpllbin_,v,o,v) (o,__VA_ARGS__)// PUSH

#define _hw_cfpllbin_hsi		, 0, 1.0	// 0:HSI, 1.0/x
#define _hw_cfpllbin_hse		, 1, 1.0	// 1:HSE, 1.0/x

#define _hwa_cfpllbin10(v,...)		HW_E(HW_EM_XNIL(v,(hse[/2..63],hsi[/2..63])))
#define _hwa_cfpllbin11(r,d,o,v)					\
  _hwa_write(o,src,r);							\
  _hwa_write(o,m,1.0/(d));						\
  if ( 1.0/(d)<2 || 1.0/(d)>63 ) { HWA_E(HW_EM_VAL(v,input,(hse[/2..63],hsi[/2..63]))); }	\
  _hwa_cfpllbn // POP

/*  Argument `multiplier`
 */
#define _hwa_cfpllbn(o,k,...)		HW_BW(_hwa_cfpllbn,k,multiplier)(o,k,__VA_ARGS__)
#define _hwa_cfpllbn0(o,k,...)		HW_E(HW_EM_XNIL(k,(multiplier)))
#define _hwa_cfpllbn1(o,ok,v,k,...)					\
  _hwa_write(o,n,v);							\
  if ( v<50 || v>432 ) { HWA_E(HW_EM_VAL(v,multiplier,(50..432))); }	\
  HW_BW(_hwa_cfpllbp,k,sysclkdiv)(o,k,__VA_ARGS__)

#define _hwa_cfpllbp0(o,k,...)		HW_E(HW_EM_XNIL(k,(sysclkdiv)))
#define _hwa_cfpllbp1(o,ok,v,k,...)			\
  if      ( v==2 ) { _hwa_write(o,p,0);	}		\
  else if ( v==4 ) { _hwa_write(o,p,1); }		\
  else if ( v==6 ) { _hwa_write(o,p,2);	}		\
  else if ( v==8 ) { _hwa_write(o,p,3);	}		\
  else { HWA_E(HW_EM_VAL(v,sysclkdiv,(2,4,6,8))); }	\
  HW_BW(_hwa_cfpllbq,k,48MHzdiv)(o,k,__VA_ARGS__)

/*  Optionnal argument `48MHzdiv`
 */
#define _hwa_cfpllbq0(o,k,...)		HW_B(_hwa_cfpllbq0,k)(o,k,__VA_ARGS__)
#define _hwa_cfpllbq00(o,k,...)		HW_E(HW_EM_XNIL(k,(48MHzdiv)))
#define _hwa_cfpllbq01(...)
#define _hwa_cfpllbq1(o,ok,v,...)				\
  _hwa_write(o,q,v&0x0F);					\
  if ( v<2 || v>15 ) { HWA_E(HW_EM_VAL(v,48MHzdiv,(2..15))); }	\
  HW_EOL(__VA_ARGS__)

/**
 * @addtogroup stm32_pllb
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
#define hw_start__pllb		, _hw_srpllb
#define _hw_srpllb(o,a,...)	_hw_write(o,on,1) HW_EOL(__VA_ARGS__)

#define hwa_start__pllb		, _hwa_srpllb
#define _hwa_srpllb(o,a,...)	_hwa_write(o,on,1) HW_EOL(__VA_ARGS__)

#define hw_stop__pllb		, _hw_sppllb
#define _hw_sppllb(o,a,...)	_hw_write(o,on,0) HW_EOL(__VA_ARGS__)

#define hwa_stop__pllb		, _hwa_sppllb
#define _hwa_sppllb(o,a,...)	_hwa_write(o,on,0) HW_EOL(__VA_ARGS__)


/**
 * @addtogroup stm32_pllb
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
} _hw_stpllb_t ;

#define hw_stat_t__pllb			, _hw_sttpllb
#define _hw_sttpllb(o,a,...)		 _hw_stpllb_t HW_EOL(__VA_ARGS__)

#define hw_stat__pllb			, _hw_stpllb
#define _hw_stpllb(o,a,g,...)		HW_B(_hw_stpllb1_,g)(g)
#define _hw_stpllb1_0(g)		HW_E(HW_EM_G(g))
#define _hw_stpllb1_1(g)		(*(volatile _hw_stpllb_t*)HW_ADDRESS((rcc,cr)))
