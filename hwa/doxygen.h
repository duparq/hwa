
/* This file is part of the HWA project.
 * Copyright (c) 2020 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @ingroup hwa
 * @defgroup hwa_pri HWA internals
 *
 * A few notes about how HWA works internally.
 * 
 * Hierarchy of files
 * ------------------
 * 
 * The base source code of HWA is in the `hwa/` directory.
 * 
 * Device-related sources are stored in `vendor/architecture/` directories
 * (`atmel/avr/`, `st/stm32/`, `espressif/esp8266/`, ...) where are stored
 * `classes/`, `devices/`, and `examples/` directories.
 * 
 * 
 * Macro dependencies
 * ------------------
 * 
 *     HW_X()    _HW_FC
 *      |         (f,c,)
 *      |           |
 *      |           |
 *      |--         |==      _hw_read(o,r)
 *      |--         |==      _hw_atomic_read(o,r)
 *      |--         |==      _hw_write(o,r,v)
 *      |--         |==      _hw_write_m(o,r,m,v)
 *      |--         |==      _hwa_write(o,r,v)
 *      |--         |==      _hwa_write_m(o,r,m,v)
 *      |--         |==      _hwa_mmask(o,r)
 *      |--         |==      _hwa_mvalue(o,r)
 *      |--         |==      _hwa_ovalue(o,r)
 *      |
 *      |--                  _hwa_setup_r(o,r)
 *      |--                  _hwa_init_r(o,r,v)
 *      |--                  _hwa_commit_r(o,r)
 *      |--                  _hwa_nocommit_r(o,r)
 *      |
 *      |--                  _hw(...)
 *      |--                  _hwa(...)
 *      |
 *      |--                  HW_ID(o)
 *      |--                  HW_ISR(oo [,reason] [,naked] ... )
 *      |--                  HW_VOID_ISR(o [,reason])
 *      |
 *      |---------HW_F()
 *      |           |
 *      |           |==      HW_ADDRESS(oo)
 *      |           |==      HW_BIT(oo)
 *      |           |==      HW_POSITION(oo)
 *      |--         |==      hw(...)
 *      |--         |==      hwa(...)
 * 
 *                           _hwa_setup_o(o)
 *                           _hwa_init_o(o)
 *                           _hwa_solve_o(o)
 *                           _hwa_commit_o(o)
 * 
 * 
 * 
 * Macro argument names
 * --------------------
 * 
 * HWA uses the following standardized argument names in its macro definitions:
 * 
 *  * `a`: address of the object
 *  * `bn`: number of bits
 *  * `bp`: position of least significant bit
 *  * `c`: class of the object
 *  * `f`: name of the function
 *  * `h`: "hw" or "hwa" prefix
 *  * `i`: id of the object
 *  * `n`: name of the object, may be a path
 *  * `o`: name of a single object
 *  * `r`: name of a register
 *  * `ra`: relative address of the register 
 *  * `rbn`: number of bits of a logical register
 *  * `rbp`: position of least significant bit of a logical register in the
 *           hardware register
 *  * `rwm`: register writeable bits mask
 *  * `rfm`: register flags mask
 *  * `rx`: definition of a register (expansion)
 *  * `t`: type
 *  * `vbn`: number of bits in the value
 *  * `vbp`: position of least significant bit in the value
 * 
 * 
 */
