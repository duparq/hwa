
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
 * @section atmelavr_dtga_acfg Configuration
 *
 * The same clock prescaler is used for the 4 units. The value `compareX_y` is
 * the delay in prescaled clock units before the assertion of the output `X_y`:
 *
 * @code
 * hw_config( HW_REL( hw_counter0, dtg0 ),
 *
 *          [ clock_div,  1 | 2 | 4 | 8, ]      // default is `1`
 *
 *          [ compare0_h, 0..15, ]              // default is `0`
 *
 *          [ compare0_l, 0..15, ]              // default is `0`
 *
 *          [ compare1_h, 0..15, ]              // default is `0`
 *
 *          [ compare1_l, 0..15  ]              // default is `0`
 *           );
 * @endcode
 */

#define _hw_mthd_hwa_configure__dtga		, _hwa_cfdtga


/*  Optionnal argument `clock_div`
 */
#define _hw_dtga_kclockdiv_clock_div
#define _hw_dtga_vclockdiv_1			, 0
#define _hw_dtga_vclockdiv_2			, 1
#define _hw_dtga_vclockdiv_4			, 2
#define _hw_dtga_vclockdiv_8			, 3

#define _hwa_cfdtga(o,i,a, ...)						\
  do {									\
    /* Add a second void argument to the end of the list so that there are always */ \
    /* at least 2 arguments following the last non-void argument. */	\
    HW_GX(_hwa_cfdtga_kclockdiv,_hw_dtga_kclockdiv_##__VA_ARGS__)(o,__VA_ARGS__,) \
      } while(0)

#define _hwa_cfdtga_kclockdiv_1(o,kw,v,...)				\
  HW_GX(_hwa_cfdtga_vclockdiv,HW_A0(_hw_dtga_vclockdiv_##v))(o,v,__VA_ARGS__) \

#define _hwa_cfdtga_vclockdiv_0(o,v,...)		\
  HW_E_AVL(clockdiv, v, 1 | 2 | 4 | 8)

#define _hwa_cfdtga_vclockdiv_1(o,v,...)		\
  _hwa_write_reg(o,psc,HW_A1(_hw_dtga_vclockdiv_##v));\
  _hwa_cfdtga_kclockdiv_0(o,__VA_ARGS__)

#define _hwa_cfdtga_kclockdiv_0(o,kw,...)				\
  HW_GX(_hwa_cfdtga_kcompare0h,_hw_dtga_kcompare0h_##kw)(o,kw,__VA_ARGS__)


/*  Optionnal argument `compare0_h`
 */
#define _hw_dtga_kcompare0h_compare0_h

#define _hwa_cfdtga_kcompare0h_1(o,kw,v,...)				\
  if ( v>=0 && v<=15 )							\
    _hwa_write_reg(o,compare0_h,v);					\
  else									\
    HWA_ERR("`compare0_h` must be in the 0..15 range, not `" #v "`.");	\
  _hwa_cfdtga_kcompare0h_0(o,__VA_ARGS__)

#define _hwa_cfdtga_kcompare0h_0(o,kw,...)				\
  HW_GX(_hwa_cfdtga_kcompare0l,_hw_dtga_kcompare0l_##kw)(o,kw,__VA_ARGS__)


/*  Optionnal argument `compare0_l`
 */
#define _hw_dtga_kcompare0l_compare0_l

#define _hwa_cfdtga_kcompare0l_1(o,kw,v,...)				\
  if ( v>=0 && v<=15 )							\
    _hwa_write_reg(o,compare0_l,v);					\
  else									\
    HWA_ERR("`compare0_l` must be in the 0..15 range, not `" #v "`.");	\
  _hwa_cfdtga_kcompare0l_0(o,__VA_ARGS__)

#define _hwa_cfdtga_kcompare0l_0(o,kw,...)				\
  HW_GX(_hwa_cfdtga_kcompare1h,_hw_dtga_kcompare1h_##kw)(o,kw,__VA_ARGS__)


/*  Optionnal argument `compare1_h`
 */
#define _hw_dtga_kcompare1h_compare1_h

#define _hwa_cfdtga_kcompare1h_1(o,kw,v,...)				\
  if ( v>=0 && v<=15 )							\
    _hwa_write_reg(o,compare1_h,v);					\
  else									\
    HWA_ERR("`compare1_h` must be in the 0..15 range, not `" #v "`.");	\
  _hwa_cfdtga_kcompare1h_0(o,__VA_ARGS__)

#define _hwa_cfdtga_kcompare1h_0(o,kw,...)				\
  HW_GX(_hwa_cfdtga_kcompare1l,_hw_dtga_kcompare1l_##kw)(o,kw,__VA_ARGS__)


/*  Optionnal argument `compare1_l`
 */
#define _hw_dtga_kcompare1l_compare1_l

#define _hwa_cfdtga_kcompare1l_1(o,kw,v,...)				\
  if ( v>=0 && v<=15 )							\
    _hwa_write_reg(o,compare1_l,v);					\
  else									\
    HWA_ERR("`compare1_l` must be in the 0..15 range, not `" #v "`.");	\
  _hwa_cfdtga_kcompare1l_0(o,__VA_ARGS__)

#define _hwa_cfdtga_kcompare1l_0(o,...)		\
  HW_EOL(__VA_ARGS__)


/*******************************************************************************
 *                                                                             *
 *      Context management						       *
 *                                                                             *
 *******************************************************************************/

#define _hwa_setup__dtga(o,i,a)			\
  _hwa_setup_reg( o, dtps );			\
  _hwa_setup_reg( o, dta );			\
  _hwa_setup_reg( o, dtb );

#define _hwa_init__dtga(o,i,a)			\
  _hwa_init_reg( o, dtps, 0x00 );		\
  _hwa_init_reg( o, dta, 0x00 );		\
  _hwa_init_reg( o, dtb, 0x00 );

#define _hwa_commit__dtga(o,i,a)		\
  _hwa_commit_reg(o,dtps);			\
  _hwa_commit_reg(o,dta);			\
  _hwa_commit_reg(o,dtb);


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
 *
 * These registers are accessible through the @ref public_reg_instructions
 * "register access intructions".
 */


/**
 * @page atmelavr_dtga
 * <br>
 */
