#ifndef _HWA_TCS3200_H_
#define _HWA_TCS3200_H_

/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Colour detector TCS3200.
 *
 * @page tcs3200 Class _tcs3200: colour detector
 *
 * A class `_tcs3200` object is colour light-to-frequency converter, also
 * called 'colour detector'.
 *
 * The following declarations create a device called `sensor0`.
 *
 * * `_hw_rel_sensor0_s1` and `_hw_rel_sensor0_s0` must be declared if you want
 * the `configure` action to be able to change the frequency range of the
 * signal.
 *
 * * `_hw_rel_sensor0_s3` and `_hw_rel_sensor0_s2` must be declared if you want
 * the `configure` action to be able to change the filter.
 *
 * * `_hw_rel_sensor0_oe` must be declared if you want the `configure` action to
 * be able to control the signal output.
 *
 * The measurement of the output signal frequency is left to the user.
 *
 * @code
 * #define _hw_def_sensor0              _tcs3200, 0, 0
 * #define _hw_rel_sensor0_s0           pin_pa0
 * #define _hw_rel_sensor0_s1           pin_pa1
 * #define _hw_rel_sensor0_s2           pin_pa2
 * #define _hw_rel_sensor0_s3           pin_pa3
 * #define _hw_rel_sensor0_oe           pin_pa4
 * @endcode
 *
 * @section tcs3200_cf Configuration
 *
 * The user is responsible of the configuration of the I/O pins. The `configure`
 * action, allows the selection of the maximum frequency of the output signal,
 * the filter, and the enabling of the output signal.
 *
 * @code
 * hw[a]( configure, sensor0,
 *
 *      [ frequency,   0                // Requires both _hw_rel_sensor0_s1
 *                   | 12kHz            // and _hw_rel_sensor0_s0 to be defined
 *                   | 120kHz           // as real I/O pins.
 *                   | 600kHz, ]        // 
 *     
 *      [ filter,      red              // Requires both _hw_rel_sensor_s3
 *                   | green            // and _hw_rel_sensor0_s2 to be defined
 *                   | blue             // as real I/O pins.
 *                   | clear ]          //
 *     
 *      [ output,      on               // Requires _hw_rel_sensor_oe
 *                   | off              // to be defined as real I/O pin.
 *      );
 * @endcode
 */
#define _hw_class__tcs3200

#define _hw_mtd_hw_configure__tcs3200	, _hw_cft3k2
#define _hw_mtd_hwa_configure__tcs3200	, _hwa_cft3k2


#define _hw_t3k2_fq_0			, 0, 0	/* S1, S0 */
#define _hw_t3k2_fq_12kHz		, 1, 0	/* S1, S0 */
#define _hw_t3k2_fq_120kHz		, 0, 1	/* S1, S0 */
#define _hw_t3k2_fq_600kHz		, 1, 1	/* S1, S0 */

#define _hw_t3k2_fl_red			, 0, 0	/* S3, S2 */
#define _hw_t3k2_fl_clear		, 0, 1	/* S3, S2 */
#define _hw_t3k2_fl_blue		, 1, 0	/* S3, S2 */
#define _hw_t3k2_fl_green		, 1, 1	/* S3, S2 */

#define _hw_is_frequency_frequency	, 1
#define _hw_is_filter_filter		, 1
#define _hw_is_output_output		, 1

#define _hw_cft3k2(...)			do { _hwx_cft3k2(_hw,__VA_ARGS__) }while(0)
#define _hwa_cft3k2(...)		do { _hwx_cft3k2(_hwa,__VA_ARGS__) }while(0)

/*  Optionnal keyword 'frequency'
 */
#define _hwx_cft3k2(p,o,i,a,k,...)	HW_X(_hwx_cft3k2_kfq,_hw_is_frequency_##k)(p,o,k,__VA_ARGS__)
#define _hwx_cft3k2_kfq_1(p,o,k,v,...)	HW_X(_hwx_cft3k2_vfq,_hw_t3k2_fq_##v)(p,o,v,__VA_ARGS__)
#define _hwx_cft3k2_vfq_0(p,o,v,...)	HW_E_OKVL(frequency,v,`0|12kHz|120kHz|600kHz`)
#define _hwx_cft3k2_vfq_1(p,o,v,k,...)				\
  p(write,_hw_rel_##o##_s1, HW_A1(_hw_t3k2_fq_##v));		\
  p(write,_hw_rel_##o##_s0, HW_A2(_hw_t3k2_fq_##v));		\
  HW_X(_hwx_cft3k2_kfl,_hw_is_filter_##k)(p,o,k,__VA_ARGS__)

/*  Optionnal keyword 'filter'
 */
#define _hwx_cft3k2_kfq_0(p,o,k,...)	HW_X(_hwx_cft3k2_kfl,_hw_is_filter_##k)(p,o,k,__VA_ARGS__)
#define _hwx_cft3k2_kfl_1(p,o,k,v,...)	HW_X(_hwx_cft3k2_vfl,_hw_t3k2_fl_##v)(p,o,v,__VA_ARGS__)
#define _hwx_cft3k2_vfl_0(p,o,v,...)	HW_E_OKVL(filter,v,`10_12kHz|100_120kHz|500_600kHz`)
#define _hwx_cft3k2_vfl_1(p,o,v,k,...)				\
  p(write,_hw_rel_##o##_s3, HW_A1(_hw_t3k2_fl_##v));		\
  p(write,_hw_rel_##o##_s2, HW_A2(_hw_t3k2_fl_##v));		\
  HW_X(_hwx_cft3k2_kou,_hw_is_output_##k)(p,o,k,__VA_ARGS__)

/*  Optionnal keyword 'output'
 */
#define _hwx_cft3k2_kfl_0(p,o,k,...)	HW_X(_hwx_cft3k2_kou,_hw_is_output_##k)(p,o,k,__VA_ARGS__)
#define _hwx_cft3k2_kou_1(p,o,k,v,...)	HW_X(_hwx_cft3k2_vou,_hw_state_##v)(p,o,v,__VA_ARGS__)
#define _hwx_cft3k2_vou_0(p,o,v,...)	HW_E_ST(v)
#define _hwx_cft3k2_vou_1(p,o,v,...)			\
  p(write,_hw_rel_##o##_oe, HW_A1(_hw_state_##v));	\
  HW_EOL(__VA_ARGS__)
#define _hwx_cft3k2_kou_0(p,o,...)	HW_EOL(__VA_ARGS__)

#endif
