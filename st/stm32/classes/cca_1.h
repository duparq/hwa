
/* This file is part of the HWA project.
 * Copyright (c) 2020 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Counter capture/compare channel
 * @page stm32_cca Class _cca: 16-bit capture-compare channel
 */

/**
 * @page stm32_cca
 *
 * A `_cca` class object is a 16-bit capture-compare channel that is associated
 * with a _cta counter.
 *
 */
#define hw_class__cca


/*  Return the counter associated to a _cca.
 */
#define hw__cca_counter			, _hw_cca_counter
#define _hw_cca_counter(o,c,...)	_ioa,o,(c,__VA_ARGS__),counter, HW_XO(c)


/*  These functions map 'virtual' cca register to their real counter register
 *  Used by HW_OX(). Return o,c,d,x,...reg...
 *
 *  FIXME: return the memory definition instead of the register?
 */
#define hw__cca_occe			, _hw_cca_occe
#define _hw_cca_occe(o,c,n)		_cta,c,(HW_A1(hw_##c)),occe, hw__cta_oc##n##ce

#define hw__cca_ocm			, _hw_cca_ocm
#define _hw_cca_ocm(o,c,n)		_cta,c,(HW_A1(hw_##c)),ocm, hw__cta_oc##n##m

#define hw__cca_icf			, _hw_cca_icf
#define _hw_cca_icf(o,c,n)		_cta,c,(HW_A1(hw_##c)),icf, hw__cta_ic##n##f

#define hw__cca_ocpe			, _hw_cca_ocpe
#define _hw_cca_ocpe(o,c,n)		_cta,c,(HW_A1(hw_##c)),ocpe, hw__cta_oc##n##pe

#define hw__cca_ocfe			, _hw_cca_ocfe
#define _hw_cca_ocfe(o,c,n)		_cta,c,(HW_A1(hw_##c)),ocfe, hw__cta_oc##n##fe

#define hw__cca_icpsc			, _hw_cca_icpsc
#define _hw_cca_icpsc(o,c,n)		_cta,c,(HW_A1(hw_##c)),icpsc, hw__cta_ic##n##psc

#define hw__cca_ccs			, _hw_cca_ccs
#define _hw_cca_ccs(o,c,n)		_cta,c,(HW_A1(hw_##c)),ccs, hw__cta_cc##n##s

#define hw__cca_cce			, _hw_cca_cce
#define _hw_cca_cce(o,c,n)		_cta,c,(HW_A1(hw_##c)),cce, hw__cta_cc##n##e

#define hw__cca_ccp			, _hw_cca_ccp
#define _hw_cca_ccp(o,c,n)		_cta,c,(HW_A1(hw_##c)),ccp, hw__cta_cc##n##p



#define hwa_read__cca			, _hwa_rdcca
#define _hwa_rdcca(o,c,n,...)		HW_EOL(__VA_ARGS__) _hwa_read(c,ccr##n)

#define hw_read__cca			, _hw_rdcca
#define _hw_rdcca(o,c,n,...)		HW_EOL(__VA_ARGS__) _hw_read(c,ccr##n)



#define hwa_write__cca			, _hwa_wrcca
#define _hwa_wrcca(o,c,n,v,...)		HW_EOL(__VA_ARGS__) _hwa_write(c,ccr##n,v)

#define hw_write__cca			, _hw_wrcca
#define _hw_wrcca(o,c,n,v,...)		HW_EOL(__VA_ARGS__) _hw_write(c,ccr##n,v)
