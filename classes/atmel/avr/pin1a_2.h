
/*  This file is part of the HWA project.
 *  Copyright (c) 2012,2015 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 *
 * Analog input pin
 */

#define _hw_cfaip_mode_analog
#define _hw_cfaip_direction_input

/**
 * @page atmelavr_pin1a
 * @section atmelavr_pin1a_config Configuring the pin
 *
 * A class _pin1a analog input pin does not need any configuration. However, for
 * compatibility with other kinds of pins, the `hw_config(...)` and
 * `hwa_config(...)` instructions are provided.
 *
 * @code
 * #define PIN		hw_pin_adc6
 *
 * hw_config( PIN,
 *
 *            [mode,        analog,]
 *
 *            [direction,   input,]
 *          );
 * @endcode
 */
#define _hw_mthd_hw_config__pin1a	, _hw_cfaipx

#define _hw_cfaip( o,i, pn,bn,bp, ...)				\
  do {									\
    HW_G2(_hw_cfdio_xdirection, HW_IS(direction,__VA_ARGS__))(pn,bn,bp,__VA_ARGS__) \
      } while(0)


/**
 * @page atmelavr_pin1a
 * @code
 * #define PIN		hw_pin_adc6
 *
 * hwa_config( PIN,
 *
 *            [mode,        analog,]
 *
 *            [direction,   input,]
 *
 *            [pullup,      off]
 *           );
 * @endcode
 */
#define _hw_mthd_hwa_config__pin1a	, _hwa_cfaip

#define _hwa_cfaip( o,i, ...)						\
  do {									\
    HW_G2(_hwa_cfaip_kmode, HW_IS(mode,__VA_ARGS__))(o,__VA_ARGS__);	\
  } while(0)

#define _hwa_cfaip_kmode_1(o,k,...)				\
  HW_G2(_hwa_cfaip_vmode, HW_IS(,_hw_cfaip_mode_##__VA_ARGS__))(o,__VA_ARGS__)

#define _hwa_cfaip_vmode_0(o,...)				\
  HW_ERR("`mode` must be `analog`, not `" HW_QUOTE(__VA_ARGS__) "`.")

#define _hwa_cfaip_vmode_1(o,v,...)				\
  _hwa_cfaip_kmode_0(o,__VA_ARGS__)

#define _hwa_cfaip_kmode_0(o,...)				\
  HW_G2(_hwa_cfaip_kdirection, HW_IS(direction,__VA_ARGS__))(o,__VA_ARGS__) \

#define _hwa_cfaip_kdirection_1(o,k,...)				\
  HW_G2(_hwa_cfaip_vdirection, HW_IS(,_hw_cfaip_direction_##__VA_ARGS__))(o,__VA_ARGS__)

#define _hwa_cfaip_vdirection_0(o,...)			\
  HW_ERR("`direction` must be `input`, not `" HW_QUOTE(__VA_ARGS__) "`.")

#define _hwa_cfaip_vdirection_1(o,v,...)			\
  _hwa_cfaip_kdirection_0(o,__VA_ARGS__)

#define _hwa_cfaip_kdirection_0(o,...)			\
  HW_G2(_hwa_cfaip_kpullup, HW_IS(pullup,__VA_ARGS__))(o,__VA_ARGS__)

#define _hwa_cfaip_kpullup_1(o,k,...)			\
  HW_G2(_hwa_cfaip_vpullup, HW_IS(,hw_state_##__VA_ARGS__))(o,__VA_ARGS__)

#define _hwa_cfaip_vpullup_1(o,...)			\
  HW_ERR("`pullup` must be `off`, not `" HW_QUOTE(__VA_ARGS__) "`.")

#define _hwa_cfaip_vpullup_0(o,v,...)				\
  HW_TX(,__VA_ARGS__)

#define _hwa_cfaip_kpullup_0(o,...)	\
  HW_TX(,__VA_ARGS__)
