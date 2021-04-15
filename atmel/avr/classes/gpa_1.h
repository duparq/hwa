
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief I/O port
 */

/**
 * @ingroup atmelavr_classes
 * @defgroup atmelavr_gpa Class _gpa: 8-bit I/O port
 *
 * This class is used in all Atmel AVR devices.
 *
 * @section atmelavr_gparel Relatives
 *
 *  * `(portx,p)`: the single gpio pin at position `p` of `portx`.
 *  * `(portx,n,p)`: the `n` consecutive gpio pins at position `p` of `portx`.
 *  * @ref hwa_r8 "(portx,ddr)": the `DDR` register of `portx`.
 *  * @ref hwa_r8 "(portx,pin)": the `PIN` register of `portx`.
 *  * @ref hwa_r8 "(portx,port)": the `PORT` register of `portx`.
 */
#define hw_class__gpa

/*	Class registers			class, address, rwm, rfm
 */
#define hw__gpa_port			_r8, 0x02, 0xFF, 0x00
#define hw__gpa_ddr			_r8, 0x01, 0xFF, 0x00
#define hw__gpa_pin			_r8, 0x00, 0xFF, 0x00

/*  (portx,p) notation
 */
#define hw__gpa_			, _hw_gpa_
#define _hw_gpa_(o,p,a)			HW_BX(_hw_gpa,_hw_isa_3bn_,p)(o,p)
#define _hw_gpa1(o,p)			_ioa,o##_1_##p,(o,1,p)
#define _hw_gpa0(o,p)			,(o,p),HW_EM_OO(o,p)


#if !defined __ASSEMBLER__

typedef struct {
  hwa_r8_t port ;
  hwa_r8_t ddr ;
} hwa_gpa_t ;

#endif
