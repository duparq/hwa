#ifndef hw_class__cca

/* This file is part of the HWA project.
 * Copyright (c) 2020 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief STM32 capture-compare channel
 */

/**
 * @ingroup stm32_classes
 * @defgroup stm32_cca Class _cca: capture-compare channel
 *
 * This class is used by:
 *
 * * @ref stm32f103 "STM32F103": `(COUNTER,CHANNEL)`
 * * @ref stm32f411 "STM32F411": `(COUNTER,CHANNEL)`
 *
 * @section stm32_ccarel Relatives
 *
 * * `(CHANNEL,counter)`: @ref stm32_cta "16-bit" or @ref stm32_ctb "32-bit"
 *   counter associated to the channel
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
#define hw__cca_ccif			, _hw_ccarg, cc, if

#define _hw_ccarg(a,b,o,n)		_hw_ccarg1(HW_RP o, a##n##b)
#define _hw_ccarg1(...)			_hw_ccarg2(__VA_ARGS__)
#define _hw_ccarg2(ct,cn,x)		HW_BED(_hw_ccarg2,hw__cta_##x,ct,cn,x)
#define _hw_ccarg20(ct,cn,x,...)	HW_E(HW_EM_OO(o,x))
#define _hw_ccarg21(ct,cn,x,rc,r,bn,bp)	_hw_ccarg3(ct,hw_##ct,hw__cta_##r,r,bn,bp)
#define _hw_ccarg3(...)			_hw_ccarg4(__VA_ARGS__)
#define _hw_ccarg4(ct,ctc,cta,rc,ra,rwm,rfm,r,rbn,rbp)	_m11,(ct,r),(ct,r,rc,cta+ra,rwm,rfm,rbn,rbp)

/*  Generate IRQ objects
 *
 *  _hw_ccairq is called by HW_X():
 *	`o`: channel name "(counterX,channelY)"
 *      `n`: channel definition (Y).
 *  The IRQ object references the counter's registers.
 */
#define hw__cca_irq			, _hw_ccairq

#define _hw_ccairq(o,n)			_hw_ccairq1(HW_RP o, n)
#define _hw_ccairq1(...)		_hw_ccairq2(__VA_ARGS__)
#define _hw_ccairq2(ct,cn,n)		_irq, (ct,irq), (cc##n##ie, cc##n##if, 0)


#define hwa_read__cca			, _hwa_rdcca
#define _hwa_rdcca(o,n,...)		_hwa_read(HW_A0 o,ccr##n) HW_EOL(__VA_ARGS__)

#define hw_read__cca			, _hw_rdcca
#define _hw_rdcca(o,n,...)		_hw_read(HW_A0 o,ccr##n) HW_EOL(__VA_ARGS__)

#define hwa_write__cca			, _hwa_wrcca
#define _hwa_wrcca(o,n,v,...)		_hwa_write(HW_A0 o,ccr##n,v) HW_EOL(__VA_ARGS__)

#define hw_write__cca			, _hw_wrcca
#define _hw_wrcca(o,n,v,...)		_hw_write(HW_A0 o,ccr##n,v) HW_EOL(__VA_ARGS__)


#endif /* ifndef hw_class__cca */
