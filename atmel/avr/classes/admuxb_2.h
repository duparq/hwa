
/*
 * This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 */

/**
 * @page atmelavr_admuxb
 * @section atmelavr_admuxb_config Configuring the analog multiplexer
 *
 * @code
 * hwa_config( ADMUX,
 * 
 *             input,   temperature
 *                    | ground
 *                    | bandgap
 *                    | hw_pin_adc0 (or synonym)
 *                    | hw_pin_adc1 (or synonym)
 *                    | hw_pin_adc2 (or synonym)
 *                    | hw_pin_adc3 (or synonym)
 *                    | hw_pin_adc4 (or synonym)
 *                    | hw_pin_adc5 (or synonym)
 *                    | hw_pin_adc6 (or synonym)
 *                    | hw_pin_adc7 (or synonym)
 *           );
 * @endcode
 */
#define _hw_mthd_hwa_config__admuxb		, _hwa_cfadmuxb

#define _hw_is_input_input			, 1
#define _hw_admuxb_input_hw_pin_adc0		, 0
#define _hw_admuxb_input_hw_pin_adc1		, 1
#define _hw_admuxb_input_hw_pin_adc2		, 2
#define _hw_admuxb_input_hw_pin_adc3		, 3
#define _hw_admuxb_input_hw_pin_adc4		, 4
#define _hw_admuxb_input_hw_pin_adc5		, 5
#define _hw_admuxb_input_hw_pin_adc6		, 6
#define _hw_admuxb_input_hw_pin_adc7		, 7
#define _hw_admuxb_input_temperature		, 8
#define _hw_admuxb_input_bandgap		, 14
#define _hw_admuxb_input_ground			, 15


#define _hwa_cfadmuxb(o,i,a,...)					\
  do {									\
    HW_G2(_hwa_cfadmuxb_kinput, HW_IS(input,__VA_ARGS__))(o,__VA_ARGS__,); \
  } while(0)

#define _hwa_cfadmuxb_kinput_0(o,k,...)		\
  HW_ERR("expected `input` instead of `"#k"`.")

#define _hwa_cfadmuxb_kinput_1(o,k,v,...)				\
  if ( HW_IS(,HW_A0(_hw_admuxb_input_##v)) )				\
    _hwa_write_reg(o,admux, HW_A1(_hw_admuxb_input_##v,0));		\
  else if ( hw_id(v) == hw_id( hw_pin_adc0 ) )				\
    _hwa_write_reg(o,admux, 0);						\
  else if ( hw_id(v) == hw_id( hw_pin_adc1 ) )				\
    _hwa_write_reg(o,admux, 1);						\
  else if ( hw_id(v) == hw_id( hw_pin_adc2 ) )				\
    _hwa_write_reg(o,admux, 2);						\
  else if ( hw_id(v) == hw_id( hw_pin_adc3 ) )				\
    _hwa_write_reg(o,admux, 3);						\
  else if ( hw_id(v) == hw_id( hw_pin_adc4 ) )				\
    _hwa_write_reg(o,admux, 4);						\
  else if ( hw_id(v) == hw_id( hw_pin_adc5 ) )				\
    _hwa_write_reg(o,admux, 5);						\
  else if ( hw_id(v) == hw_id( hw_pin_adc6 ) )				\
    _hwa_write_reg(o,admux, 6);						\
  else if ( hw_id(v) == hw_id( hw_pin_adc7 ) )				\
    _hwa_write_reg(o,admux, 7);						\
  else									\
    HWA_ERR("`input` can be `temperature`, `bandgap`, `ground`, "	\
	    "or `hw_pin_adc0..7` (or synonyms), but not `"#v"`.");	\
  HW_TX(__VA_ARGS__)

/**
 * @page atmelavr_admuxb
 * <br>
 */
