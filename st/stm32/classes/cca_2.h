
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
 *      result,          frozen                 // (ocm=0) Default
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
#define _hw_cfcca(o,c,n,k,...)		do{ HW_B(_hwx_cfcca,k)(_hw,c,n,k,__VA_ARGS__) }while(0)
#define _hwa_cfcca(o,c,n,k,...)		do{ HW_B(_hwx_cfcca,k)(_hwa,c,n,k,__VA_ARGS__) }while(0)

#define _hwx_cfcca1(...)		HW_E_ML((function))

/*  Mandatory argument 'function'
 */
#define _hwx_cfcca0(h,c,n,k,...)	HW_BW(_hwx_cfcca_fun,function,k)(h,c,n,k,__VA_ARGS__)
#define _hwx_cfcca_fun0(h,c,n,k,...)	HW_E_NIL(k,(function))
#define _hwx_cfcca_fun1(h,c,n,k,v,...)	HW_BW(_hwx_cfcca_fun1,compare,v)(h,c,n,v,__VA_ARGS__)
#define _hwx_cfcca_fun10(h,c,n,v,...)	HW_E_TBIKV(function,v)
#define _hwx_cfcca_fun11(h,c,n,v,k,...)	h##_write(c,cc##n##s,0); HW_BW(_hwx_cfcca_res,result,k)(h,c,n,k,__VA_ARGS__)

/*  Mandatory argument 'result'
 */
#define _hwx_cfcca_res0(h,c,n,k,...)	HW_E_NIL(k,(result))
#define _hwx_cfcca_res1(h,c,n,k,v,...)	HW_BV(_hwx_cfcca_res1,_hw_ccares_,v)(h,c,n,__VA_ARGS__) )
#define _hwx_cfcca_res10(v)		HW_E_NIL(v,(frozen, set_on_match, clear_on_match, \
						    toggle_on_match, low, high, \
						    clear_on_match_up_set_on_match_down, \
						    set_on_match_up_clear_on_match_down)) HW_EAT(
#define _hwx_cfcca_res11(v)		_hwx_cfcca_res12(v, HW_RP /* <- ... ) */
#define _hwx_cfcca_res12(...)		_hwx_cfcca_res13(__VA_ARGS__)
#define _hwx_cfcca_res13(v,h,c,n,k,...)	h##_write(c,oc##n##m,v); HW_BW(_hwx_cfcca_coe,clear_on_etr,k)(h,c,n,k,__VA_ARGS__)

#define _hw_ccares_frozen				, 0
#define _hw_ccares_set_on_match				, 1
#define _hw_ccares_clear_on_match			, 2
#define _hw_ccares_toggle_on_match			, 3
#define _hw_ccares_low					, 4
#define _hw_ccares_high					, 5
#define _hw_ccares_clear_on_match_up_set_on_match_down	, 6
#define _hw_ccares_set_on_match_up_clear_on_match_down	, 7

/*  Optionnal argument 'clear_on_etr'
 */
#define _hw_is_clear_on_etr_clear_on_etr	, 1

#define _hwx_cfcca_coe0(h,c,n,k,...)	HW_BW(_hwx_cfcca_lat,latch,k)(h,c,n,k,__VA_ARGS__)
#define _hwx_cfcca_coe1(h,c,n,k,v,...)	HW_BV(_hwx_cfcca_coe1,_hw_state_,v)(h,c,n,__VA_ARGS__)	/* -> */ )
#define _hwx_cfcca_coe10(v)		HW_E_ST(v) HW_EAT( /* <- ... ) */
#define _hwx_cfcca_coe11(v)		_hwx_cfcca_coe12(v, HW_RP /* <- ... ) */
#define _hwx_cfcca_coe12(...)		_hwx_cfcca_coe13(__VA_ARGS__)
#define _hwx_cfcca_coe13(v,h,c,n,k,...)	h##_write(c,oc##n##ce,v); HW_BW(_hwx_cfcca_lat,k,latch)(h,c,n,k,__VA_ARGS__)

/*  Optionnal argument 'latch'
 */
#define _hwx_cfcca_lat0(h,c,n,k,...)	HW_BW(_hwx_cfcca_fst,k,fast)(h,c,n,k,__VA_ARGS__)
#define _hwx_cfcca_lat1(h,c,n,k,v,...)	HW_BV(_hwx_cfcca_lat1,_hw_state_,v)(h,c,n,__VA_ARGS__)	/* -> */ )
#define _hwx_cfcca_lat10(v)		HW_E_ST(v) HW_EAT( /* <- ... ) */
#define _hwx_cfcca_lat11(v)		_hwx_cfcca_lat12(v, HW_RP /* <- ... ) */
#define _hwx_cfcca_lat12(...)		_hwx_cfcca_lat13(__VA_ARGS__)
#define _hwx_cfcca_lat13(v,h,c,n,k,...)	h##_write(c,oc##n##pe,v);  HW_BW(_hwx_cfcca_fst,fast,k)(h,c,n,k,__VA_ARGS__)

/*  Optionnal argument 'fast'
 */
#define _hwx_cfcca_fst0(h,c,n,k,...)	HW_BW(_hwx_cfcca_pol,k,polarity)(h,c,n,k,__VA_ARGS__)
#define _hwx_cfcca_fst1(h,c,n,k,v,...)	HW_BV(_hwx_cfcca_fst1,_hw_state_,v)(h,c,n,__VA_ARGS__) )
#define _hwx_cfcca_fst10(v)		HW_E_ST(v) HW_EAT( /* <- ... ) */
#define _hwx_cfcca_fst11(v)		_hwx_cfcca_fst12(v, HW_RP /* <- ... ) */
#define _hwx_cfcca_fst12(...)		_hwx_cfcca_fst13(__VA_ARGS__)
#define _hwx_cfcca_fst13(v,h,c,n,k,...)	h##_write(c,oc##n##fe,r); HW_BW(_hwx_cfcca_pol,k,polarity)(h,c,n,k,__VA_ARGS__)

/*  Optionnal argument 'polarity'
 */
#define _hwx_cfcca_pol0(h,c,n,k,...)	HW_BW(_hwx_cfcca_out,k,output)(h,c,n,k,__VA_ARGS__)
#define _hwx_cfcca_pol1(h,c,n,k,v,...)	HW_BV(_hwx_cfcca_pol1,_hw_ccapol_,v)(h,c,n,__VA_ARGS__) )
#define _hwx_cfcca_pol10(v)		HW_E(HW_EM_XNIL(v,(normal,reversed))) HW_EAT( /* <- ... ) */
#define _hwx_cfcca_pol11(v)		_hwx_cfcca_pol12(v, HW_RP /* <- ... ) */
#define _hwx_cfcca_pol12(...)		_hwx_cfcca_pol13(__VA_ARGS__)
#define _hwx_cfcca_pol13(v,h,c,n,k,...)	h##_write(c,cc##n##p,v); HW_BW(_hwx_cfcca_out,k,output)(h,c,n,k,__VA_ARGS__)

#define _hw_ccapol_normal		, 0
#define _hw_ccapol_reversed		, 1

/*  Mandatory argument 'output'
 */
#define _hwx_cfcca_out0(h,c,n,k,...)	HW_E_MA(output)
#define _hwx_cfcca_out1(h,c,n,k,v,...)	HW_BW(_hwx_cfcca_out1,connected,v)(h,c,n,v,__VA_ARGS__)
#define _hwx_cfcca_out11(h,c,n,v,...)	h##_write(c,cc##n##e,1);
#define _hwx_cfcca_out10(h,c,n,v,...)	HW_BW(_hwx_cfcca_out2,disconnected,v)(h,c,n,v,__VA_ARGS__)
#define _hwx_cfcca_out21(h,c,n,v,...)	h##_write(c,cc##n##e,0);
#define _hwx_cfcca_out20(h,c,n,v,...)	HW_E_NIL(v,(connected,disconnected))
