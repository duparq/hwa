
/* This file is part of the HWA project.
 * Copyright (c) 2020 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief STM32 16-bit capture-compare channel
 */

/**
 * @ingroup stm32_classes
 * @defgroup stm32_cca Class _cca: 16-bit capture-compare channel
 *
 * This class is used by:
 *
 * * @ref stm32f103 "STM32F103": `(COUNTER,CHANNEL)`
 *
 * @section stm32_ccarel Relatives
 *
 * * @ref stm32_cta "(CHANNEL,counter)": the counter associated to the channel
 *
 */
#define hw_class__cca


/*  Return the counter associated to a _cca.
 */
#define hw__cca_counter			, _hw_cca_counter
#define _hw_cca_counter(o,c,...)	_ioa,o,(c,__VA_ARGS__),counter, HW_XO(c)


/*  Route logical registers to hardware counter's.
 *    Build the memory definition here as we know the definitions
 *    of the registers and HW_OXR would probably be slower.
 */
#define hw__cca_occe			, _hw_ccarg, oc, ce
#define hw__cca_ocm			, _hw_ccarg, oc, m
#define hw__cca_icf			, _hw_ccarg, ic, f
#define hw__cca_ocpe			, _hw_ccarg, oc, pe
#define hw__cca_ocfe			, _hw_ccarg, oc, fe
#define hw__cca_icpsc			, _hw_ccarg, ic, psc
#define hw__cca_ccs			, _hw_ccarg, cc, s
#define hw__cca_cce			, _hw_ccarg, cc, e
#define hw__cca_ccp			, _hw_ccarg, cc, p

#define hw__cca_ccie			, _hw_ccarg, cc, ie

/* #define _hw_ccarg(p1,p2,o,c,n)		_hw_ccarg1(hw__cta_##p1##n##p2,c,hw_##c) */
/* #define _hw_ccarg1(...)			_hw_ccarg2(__VA_ARGS__) */
/* #define _hw_ccarg2(rc,r,rbn,rbp,o,c,a)	HW_OXR(rc,,r,rbn,rbp,c,o,a) */

#define _hw_ccarg(p1,p2,o,c,n)		_hw_ccarg1((c,channel##n,p1##p2),hw__cta_##p1##n##p2,c,hw_##c,hw__cta_dier)
#define _hw_ccarg1(...)			_hw_ccarg2(__VA_ARGS__)
#define _hw_ccarg2(s,cb1,r,rbn,rbp,o,c,a,rc,ra,rwm,rfm)	_m11,s,(o,r,rc,a+ra,rwm,rfm,rbn,rbp)


#define hwa_read__cca			, _hwa_rdcca
#define _hwa_rdcca(o,c,n,...)		_hwa_read(c,ccr##n) HW_EOL(__VA_ARGS__)

#define hw_read__cca			, _hw_rdcca
#define _hw_rdcca(o,c,n,...)		_hw_read(c,ccr##n) HW_EOL(__VA_ARGS__)



#define hwa_write__cca			, _hwa_wrcca
#define _hwa_wrcca(o,c,n,v,...)		_hwa_write(c,ccr##n,v) HW_EOL(__VA_ARGS__)

#define hw_write__cca			, _hw_wrcca
#define _hw_wrcca(o,c,n,v,...)		_hw_write(c,ccr##n,v) HW_EOL(__VA_ARGS__)
