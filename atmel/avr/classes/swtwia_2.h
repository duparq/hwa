
/* This file is part of the HWA project.
 * Copyright (c) 2018 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/*	DO NOT USE!
 *
 *	This is a temporary file, for experimentation. <hwa/twimaster.h> should be used instead.
 */

#error Do not use this!

/*
 * @file
 * @brief Software-emulated TWI
 */

/*
 * @page atmelavr_swtwia Class _swtwia: software-emulated two-wire interface
 *
 */

#define _hw_class__swtwia

/*	Object swtwi0
 */
#if defined hw_swtwi0_scl || defined hw_swtwi0_sda || defined hw_swtwi0_bps || defined hw_swtwi0_sr
#  define HWA_HAS_SWTWI0
#  if !defined hw_swtwi0_scl
#    error hw_swtwi0_scl is not defined
#  elif HW_ADDRESS(hw_swtwi0_scl) == -1
#    error HWA: hw_swtwi0_scl: invalid definition
#    undef HWA_HAS_SWTWI0
#  endif
#  if !defined hw_swtwi0_sda
#    error hw_swtwi0_sda is not defined
#    undef HWA_HAS_SWTWI0
#  elif HW_ADDRESS(hw_swtwi0_sda) == -1
#    error HWA: hw_swtwi0_sda: invalid definition
#    undef HWA_HAS_SWTWI0
#  endif
#  if !defined hw_swtwi0_bps
#    error hw_swtwi0_bps is not defined
#    undef HWA_HAS_SWTWI0
#  else
#    define hw_swtwi0_dt (HW_SYSHZ / (2*hw_swtwi0_bps))
#  endif
#  if !defined hw_swtwi0_sr
#    error hw_swtwi0_sr is not defined
#    undef HWA_HAS_SWTWI0
#  endif
#endif

#if defined HWA_HAS_SWTWI0
#  define _hw_rel_swtwi0_sda		hw_swtwi0_sda
#  define _hw_rel_swtwi0_scl		hw_swtwi0_scl
#  define _hw_def_swtwi0		_swtwia, 0, 0
#  define _hw_irq_swtwi0_		_irq, swtwi0, 0, null, if
#  define _hw_reg_swtwi0_sr		_r8, (intptr_t)&hw_swtwi0_sr, -1, 0x00
#  define _hw_reg__swtwia_cr		_const, 0xFF, 0, 0
#  define _hw_reg__swtwia_if		_cb1, cr, 1, 7		// IRQ flag

#  define hw_swtwi0_scl_0		_hw( configure, hw_swtwi0_scl, mode, digital_output )
#  define hw_swtwi0_scl_X		_hw( configure, hw_swtwi0_scl, mode, digital_input )
#  define hw_swtwi0_sda_0		_hw( configure, hw_swtwi0_sda, mode, digital_output )
#  define hw_swtwi0_sda_X		_hw( configure, hw_swtwi0_sda, mode, digital_input )

extern uint8_t hw_swtwi0_sr ;


#if HW_IS(max,hw_swtwi0_bps)
#  define hw_swtwi0_delay()
#else
void __attribute__((weak)) hw_swtwi0_delay (  )
{
  // 1 * CALL + 2 * LDI + 1 * JMP + 1 * RET = 4 + 2*1 + 3 + 4 = 13 cycles
  //  __hw_loop_16 ( (HW_SYSHZ / (2*hw_swtwi0_bps) - 13 + 2) / 4 );

  // 1 * CALL + 1 * RET = 4 + 4 = 8 cycles
  hw_waste_cycles( HW_SYSHZ / (2*hw_swtwi0_bps) - 8 );
}
#endif

void __attribute__((weak)) hw_swtwi0_txstart ( )
{
  /*  SDA goes low while SCL is high
   */
  hw_swtwi0_sda_0 ;
  hw_swtwi0_delay();
  hw_swtwi0_scl_0 ;
}

void __attribute__((weak)) hw_swtwi0_txstop ( )
{
  /*  SDA goes high while SCL is high
   */
  hw_swtwi0_scl_X ;
  hw_swtwi0_delay();
  hw_swtwi0_sda_X ;
}

uint8_t __attribute__((weak)) hw_swtwi0_tx ( uint8_t byte )
{
  /*  SDA can change while SCL is low
   */
  for ( uint8_t bit=0x80 ; bit ; bit>>=1 ) {
    if ( (byte & bit) == 0 )
      hw_swtwi0_sda_0 ;
    else
      hw_swtwi0_sda_X ;
    hw_swtwi0_delay();
    hw_swtwi0_scl_X ;
    hw_swtwi0_delay();
    while ( !hw(read, hw_swtwi0_scl) ) {} /* The slave can extend the SCL low period */
    hw_swtwi0_scl_0 ;
  }
  hw_swtwi0_sda_X ;
  hw_swtwi0_delay();
  hw_swtwi0_scl_X ;
  hw_swtwi0_delay();
  while ( !hw(read, hw_swtwi0_scl) ) {} /* The slave can extend the SCL low period */
  byte = hw(read, hw_swtwi0_sda);
  hw_swtwi0_scl_0 ;
  hw_swtwi0_sda_0 ;
  hw_swtwi0_delay();
  return byte ;
}

void __attribute__((weak)) hw_swtwi0_txslaw ( uint8_t sla )
{
  uint8_t ack = hw_swtwi0_tx( sla<<1 );
  if ( ack == 0 )
    hw_swtwi0_sr = 0x18 ; /* HW_TWI_MT_SLA_ACK */
  else
    hw_swtwi0_sr = 0 ;
}


/*
 * @page atmelavr_swtwia
 * @section swtwiacf Configuration
 *
 * `configure`
 *
 * @code
 * hwa( configure,   swtwi0,
 *
 *      bps,         BPS           //  bits per second
 *                 | max );
 * @endcode
 */
#define _hw_mtd_hw_configure__swtwia	, _hw_cfswtwia
#define _hw_mtd_hwa_configure__swtwia	, _hwa_cfswtwia

#define _hw_cfswtwia(o,a,...)		_hwx_cfswtwia(_hw,o,__VA_ARGS__)
#define _hwa_cfswtwia(o,a,...)	_hwx_cfswtwia(_hwa,o,__VA_ARGS__)

#define _hwx_cfswtwia(h,o,k,...)					\
  do{									\
    h( configure, (o,sda), mode, digital_input );			\
    h( configure, (o,scl), mode, digital_input );			\
    h( write, (o,sda), 0 );						\
    h( write, (o,scl), 0 );						\
    HW_Y(_hwx_cfswtwia_kbps,_hw_is_bps_##k)(o,k,__VA_ARGS__,);		\
  }while(0)

/*  Key `bps`
 */
#define _hwx_cfswtwia_kbps_0(o,k,...)		HW_E_NIL(k,(bps))

#define _hwx_cfswtwia_kbps_1(o,k,v,...)				\
  HW_Y(_hwx_cfswtwia_kbps1,_hw_is_max_##v)(o,v,__VA_ARGS__)
#define _hwx_cfswtwia_kbps1_0(o,v,...)					\
  HW_G2(_hwx_cfswtwia_kbps2,HW_IS(max,hw_##o##_bps))(o,v,__VA_ARGS__)
#define _hwx_cfswtwia_kbps2_0(o,v,...)					\
  do{ if ( hw_##o##_bps != v ) HWA_E(`v` does not match `hw_##o##_bps`); }while(0) HW_EOL(__VA_ARGS__)
#define _hwx_cfswtwia_kbps2_1(o,v,...)		\
  HWA_E(`v` does not match `hw_##o##_bps`)
#define _hwx_cfswtwia_kbps1_1(o,v,...)					\
  HW_G2(_hwx_cfswtwia_kbps3,HW_IS(max,hw_##o##_bps))(o,v,__VA_ARGS__)
#define _hwx_cfswtwia_kbps3_0(o,v,...)	HWA_E(`v` does not match `hw_##o##_bps`)
#define _hwx_cfswtwia_kbps3_1(o,v,...)	HW_EOL(__VA_ARGS__)


/*
 * @page atmelavr_swtwia
 * @section swtwiacf Bus operations
 *
 * @code
 * hw( bus_start, swtwi0 );
 * @endcode
 * <br>
 */
#define _hw_mtd_hw_bus_start__swtwia	, _hw_swtwia_txstart
#define _hw_mtd_hw_bus_slaw__swtwia	, _hw_swtwia_txslaw
/* #define _hw_mtd_hw_bus_slar__swtwia	, _hw_swtwia_txslar */
#define _hw_mtd_hw_bus_stop__swtwia	, _hw_swtwia_txstop
#define _hw_mtd_hw_bus_data__swtwia	, _hw_swtwia_txdata
/* #define _hw_mtd_hw_bus_read__swtwia	, _hw_swtwia_txread */
#define _hw_mtd_hw_stat__swtwia		, _hw_swtwia_stat

#define _hw_swtwia_txstart(o,a,...)	hw_##o##_txstart() HW_EOL(__VA_ARGS__)
#define _hw_swtwia_txstop(o,a,...)	hw_##o##_txstop() HW_EOL(__VA_ARGS__)
#define _hw_swtwia_txslaw(o,a,v,...)	hw_##o##_txslaw(v) HW_EOL(__VA_ARGS__)
#define _hw_swtwia_txdata(o,a,v,...)	hw_##o##_tx(v) HW_EOL(__VA_ARGS__)
#define _hw_swtwia_stat(o,a,v,...)	hw_##o##_sr HW_EOL(__VA_ARGS__)

#endif /* defined HWA_HAS_SWTWI0 */
