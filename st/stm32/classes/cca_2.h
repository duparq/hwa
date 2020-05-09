
/* This file is part of the HWA project.
 * Copyright (c) 2020 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Counter capture/compare channel
 * @page stm32_cca
 */

/**
 * @page stm32_cca
 * __Actions__
 *
 * `configure` as compare channel
 *
 * @code
 *
 * hwa( configure,       (counter2,channel3),   // Fig. 131, RM0008, p. 389
 *
 *      function,        compare,               // (ccs=0) Default
 *
 *      rule,            frozen                 // (ocm=0) Default
 *                     | set_on_match           // (ocm=1)
 *                     | clear_on_match         // (ocm=2)
 *                     | toggle_on_match        // (ocm=3)
 *                     | low                    // (ocm=4)
 *                     | high                   // (ocm=5)
 *                     | clear_on_match_up_set_on_match_down  // (ocm=6) must count updown?
 *                     | set_on_match_up_clear_on_match_down  // (ocm=7) must count updown?
 *
 *    [ clear_on_etr,    no                     // (occe=0) Default
 *                     | yes, ]                 // (occe=1)
 *
 *    [ latch,           no                     // (ocpe=0) Default
 *                     | yes, ]                 // (ocpe=1)
 *
 *    [ fast,            no                     // (ocfe=0) Default
 *                     | yes, ]                 // (ocfe=1)
 *
 *    [ polarity,        normal                 // (ccp=0) Default
 *                     | reversed, ]            // (ccp=1)
 *
 *      output,          disconnected           // (cce=0) Default
 *                     | connected,             // (cce=1)
 *      );
 *
 * @endcode
 */

#define hw_configure__cca		, _hw_cfcca
#define hwa_configure__cca		, _hwa_cfcca

/*  At least one keyword
 */
#define _hw_cfcca(o,c,n,k,...)		do{ HW_Y(_hwx_cfcca,k)(_hw,c,n,k,__VA_ARGS__) }while(0)
#define _hwa_cfcca(o,c,n,k,...)		do{ HW_Y(_hwx_cfcca,k)(_hwa,c,n,k,__VA_ARGS__) }while(0)

#define _hwx_cfcca1(...)		HW_E_ML((function))

/*  Mandatory argument 'function'
 */
#define _hwx_cfcca0(h,c,n,k,...)	HW_KW(_hwx_cfcca_kfun,function,k)(h,c,n,k,__VA_ARGS__)
#define _hwx_cfcca_kfun0(h,c,n,k,...)	HW_E_NIL(k,(function))
#define _hwx_cfcca_kfun1(h,c,n,k,v,...)	HW_KW(_hwx_cfcca_vmod,compare,v)(h,c,n,v,__VA_ARGS__)
#define _hwx_cfcca_vmod0(h,c,n,v,...)	HW_E_TBIKV(function,v)
#define _hwx_cfcca_vmod1(h,c,n,v,k,...)			\
  h##_write(c,cc##n##s,0);				\
  HW_KW(_hwx_cfcca_krul,rule,k)(h,c,n,k,__VA_ARGS__)

/*  Mandatory argument 'rule'
 */
#define _hwx_cfcca_krul0(h,c,n,k,...)	HW_E_NIL(k,(rule))
#define _hwx_cfcca_krul1(h,c,n,k,v,...)	HW_Y(_hwx_cfcca_vrul,_hw_ccarul_##v)(h,c,n,v,__VA_ARGS__)

#define _hw_ccarul_frozen					, 0
#define _hw_ccarul_set_on_match					, 1
#define _hw_ccarul_clear_on_match				, 2
#define _hw_ccarul_toggle_on_match				, 3
#define _hw_ccarul_low						, 4
#define _hw_ccarul_high						, 5
#define _hw_ccarul_clear_on_match_up_set_on_match_down	, 6
#define _hw_ccarul_set_on_match_up_clear_on_match_down	, 7

#define _hwx_cfcca_vrul0(h,c,n,v,...)	HW_E_NIL(v,(frozen, set_on_match, clear_on_match, \
						    toggle_on_match, low, high, \
						    clear_on_match_up_set_on_match_down, \
						    set_on_match_up_clear_on_match_down))

#define _hwx_cfcca_vrul1(h,c,n,v,k,...)			\
  h##_write(c,oc##n##m,HW_A1(_hw_ccarul_##v));		\
  HW_KW(_hwx_cfcca_kcoe,k,clear_on_etr)(h,c,n,k,__VA_ARGS__)

/*  Optionnal argument 'clear_on_etr'
 */
#define _hw_is_clear_on_etr_clear_on_etr	, 1

#define _hwx_cfcca_kcoe0(h,c,n,k,...)	HW_KW(_hwx_cfcca_klat,k,latch)(h,c,n,k,__VA_ARGS__)
#define _hwx_cfcca_kcoe1(h,c,n,k,v,...)	HW_KS2(_hwx_cfcca_vcoe,v)(h,c,n,v,__VA_ARGS__)
#define _hwx_cfcca_vcoe0(h,c,n,v,...)
#define _hwx_cfcca_vcoe1(r,h,c,n,v,k,...)		\
  h##_write(c,oc##n##ce,r);				\
  HW_KW(_hwx_cfcca_klat,k,latch)(h,c,n,k,__VA_ARGS__)

/*  Optionnal argument 'latch'
 */
#define _hwx_cfcca_klat0(h,c,n,k,...)	HW_KW(_hwx_cfcca_kfst,k,fast)(h,c,n,k,__VA_ARGS__)
#define _hwx_cfcca_klat1(h,c,n,k,v,...)	HW_KS2(_hwx_cfcca_vlat,v)(h,c,n,v,__VA_ARGS__)
#define _hwx_cfcca_vlat0(h,c,n,v,...)
#define _hwx_cfcca_vlat1(r,h,c,n,v,k,...)		\
  h##_write(c,oc##n##pe,r);				\
  HW_KW(_hwx_cfcca_kfst,k,fast)(h,c,n,k,__VA_ARGS__)	

/*  Optionnal argument 'fast'
 */
#define _hwx_cfcca_kfst0(h,c,n,k,...)	HW_KW(_hwx_cfcca_kpol,k,polarity)(h,c,n,k,__VA_ARGS__)
#define _hwx_cfcca_kfst1(h,c,n,k,...)	HW_KS2(_hwx_cfcca_vfst,v)(h,c,n,v,__VA_ARGS__)
#define _hwx_cfcca_vfst0(h,c,n,v,...)
#define _hwx_cfcca_vfst1(r,h,c,n,v,k,...)		\
  h##_write(c,oc##n##fe,r);				\
  HW_KW(_hwx_cfcca_kpol,k,polarity)(h,c,n,k,__VA_ARGS__)

/*  Optionnal argument 'polarity'
 */
#define _hwx_cfcca_kpol0(h,c,n,k,...)	HW_KW(_hwx_cfcca_kout,k,output)(h,c,n,k,__VA_ARGS__)
#define _hwx_cfcca_kpol1(h,c,n,k,...)	HW_Y(_hwx_cfcca_vrul,_hw_ccapol_##v)(h,c,n,v,__VA_ARGS__)

#define _hw_ccapol_normal		, 0
#define _hw_ccapol_reversed		, 1

#define _hwx_cfcca_vpol0(h,c,n,v,...)	HW_E_NIL(v,(normal,reversed))
#define _hwx_cfcca_vpol1(h,c,n,v,k,...)			\
  h##_write(c,cc##n##p,HW_A1(_hw_ccapol_##v));		\
  HW_KW(_hwx_cfcca_kout,k,output)(h,c,n,k,__VA_ARGS__)

/*  Mandatory argument 'output'
 */
#define _hwx_cfcca_kout0(h,c,n,k,...)	HW_E_MA(output)
#define _hwx_cfcca_kout1(h,c,n,k,v,...)	HW_KW(_hwx_cfcca_vout1,connected,v)(h,c,n,v,__VA_ARGS__)
#define _hwx_cfcca_vout11(h,c,n,v,...)	h##_write(c,cc##n##e,1);
#define _hwx_cfcca_vout10(h,c,n,v,...)	HW_KW(_hwx_cfcca_vout2,disconnected,v)(h,c,n,v,__VA_ARGS__)
#define _hwx_cfcca_vout21(h,c,n,v,...)	h##_write(c,cc##n##e,0);
#define _hwx_cfcca_vout20(h,c,n,v,...)	HW_E_NIL(v,(connected,disconnected))
