
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Dead time generator
 */

/**
 * @page atmelavr_dtga
 * @section atmelavr_dtga_act Actions
 *
 * <br>
 * `configure`:
 *
 * The same clock prescaler is used for the 4 units. `delay_h` and `delay_l` are
 * the number of prescaled clock units before the assertion of the corresponding
 * output:
 *
 * @code
 * hw|hwa( configure, (counter0,compare0,dtg),
 *
 *	 [ prescaler,  1 | 2 | 4 | 8, ]	 // default is `1`
 *
 *	 [ delay_h, 0..15, ]		 // default is `0`
 *
 *	 [ delay_l, 0..15, ] );		 // default is `0`
 * @endcode
 *
 * @code
 * hw|hwa( write, (counter0,compare0,dtg,prescaler), 4 );
 * @endcode
 *
 * @code
 * hw( configure, (counter0,dtg0),
 *
 *   [ prescaler,  1 | 2 | 4 | 8, ]	 // default is `1`
 *
 *   [ compare0_h, 0..15, ]		 // default is `0`
 *
 *   [ compare0_l, 0..15, ]		 // default is `0`
 *
 *   [ compare1_h, 0..15, ]		 // default is `0`
 *
 *   [ compare1_l, 0..15  ] );		 // default is `0`
 * @endcode
 */

/* FIXME
 *
 * Perhaps it would be better to create one DTG attached to each compare unit
 * and one shared DTG prescaler?
 *
 *  * counter1compare0dtg
 *  * counter1compare1dtg
 *  * counter1dtgprescaler
 *
 * hw( configure, counter1compare0dtg,
 *     low,	  2,
 *     high,	  2 );
 *
 * hw( write, counter1dtgprescaler, 4 );
 */

#define hwa_configure__dtga		, _hwa_cfdtga


#define _hwa_cfdtga(o,ct,oc,k,...)	do { HW_YW(_hwx_cfdtga_kpsc_,prescaler,k)(_hwa,ct,oc,k,__VA_ARGS__) } while(0)
#define _hw_cfdtga(o,ct,oc,k,...)	do { HW_YW(_hwx_cfdtga_kpsc_,prescaler,k)(_hw,ct,oc,k,__VA_ARGS__) } while(0)
/*
 *  Optionnal argument 'prescaler'
 */
#define _hwx_cfdtga_kpsc_1(h,ct,oc,k,v,...)	HW_Y0(_hwx_cfdtga_vpsc_,HW_A0(_hw_dtga_vpsc_##v))(h,ct,oc,v,__VA_ARGS__)
#define _hwx_cfdtga_vpsc_0(h,ct,oc,v,...)	HW_E_AVL(psc, v, 1 | 2 | 4 | 8)
#define _hwx_cfdtga_vpsc_1(h,ct,oc,v,k,...)		\
  _hwa_write(ct,dtgps,HW_A1(_hw_dtga_vpsc_##v));	\
  HW_YW(_hwx_cfdtga_kdlh_,delay_h,k)(h,ct,oc,k,__VA_ARGS__)
#define _hwx_cfdtga_kpsc_0(h,ct,oc,k,...)	HW_YW(_hwx_cfdtga_kdlh_,delay_h,k)(h,ct,oc,k,__VA_ARGS__)

#define _hw_dtga_kpsc_prescaler
#define _hw_dtga_vpsc_1			, 0
#define _hw_dtga_vpsc_2			, 1
#define _hw_dtga_vpsc_4			, 2
#define _hw_dtga_vpsc_8			, 3
/*
 *  Optionnal argument 'delay_h'
 */
#define _hwx_cfdtga_kdlh_1(x,ct,oc,k0,v,k,...)				\
  if ( v>=0 && v<=15 )							\
    x##_write(ct,dtg##oc##h,v);						\
  else									\
    HWA_ERR("`delay_h` must be in the 0..15 range, not `" #v "`.");	\
  HW_YW(_hwx_cfdtga_kdll_,delay_l,k)(x,ct,oc,k,__VA_ARGS__)

#define _hwx_cfdtga_kdlh_0(h,ct,oc,k,...)			\
  HW_YW(_hwx_cfdtga_kdll_,delay_l,k)(h,ct,oc,k,__VA_ARGS__)
/*
 *  Optionnal argument 'delay_l'
 */
#define _hwx_cfdtga_kdll_1(h,ct,oc,k0,v,k,...)				\
  if ( v>=0 && v<=15 )							\
    h##_write(ct,dtg##oc##l,v);						\
  else									\
    HWA_ERR("`delay_l` must be in the 0..15 range, not `" #v "`.");	\
  HW_EOL(__VA_ARGS__)

#define _hwx_cfdtga_kdll_0(h,ct,oc,k,...)				\
  HW_EOL(__VA_ARGS__)


/*******************************************************************************
 *									       *
 *	Context management						       *
 *									       *
 *******************************************************************************/

#define _hwa_setup__dtga(o,a)			\
  _hwa_setup_r( o, dtps );			\
  _hwa_setup_r( o, dta );			\
  _hwa_setup_r( o, dtb );

#define _hwa_init__dtga(o,a)			\
  _hwa_init_r( o, dtps, 0x00 );		\
  _hwa_init_r( o, dta, 0x00 );		\
  _hwa_init_r( o, dtb, 0x00 );

#define _hwa_commit__dtga(o,a)		\
  _hwa_commit_r(o,dtps);			\
  _hwa_commit_r(o,dta);			\
  _hwa_commit_r(o,dtb);


/**
 * @page atmelavr_dtga
 * @section atmelavr_dtga_internals Internals
 *
 * Class `_dtga` objects hold the following hardware registers:
 *
 *  * `dtps` : clock prescaler
 *  * `dta` : dead time register a
 *  * `dtb` : dead time register b
 *
 * that hold the following logical registers:
 *
 *  * `psc` : clock prescaler
 *  * `compare0_h` : delay for output pin of compare unit 0
 *  * `compare0_l` : delay for complementary output pin of compare unit 0
 *  * `compare1_h` : delay for output pin of compare unit 1
 *  * `compare1_l` : delay for complementary output pin of compare unit 1
 */
