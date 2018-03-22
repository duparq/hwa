
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Serial Peripheral Interface
 */

/**
 * @page atmelavr_spia
 * @section atmelavr_spia_cf Configuration
 *
 * __Note 1__ When configured in master or slave mode, the SPI automatically
 * configures its related I/O pins as inputs or outputs according to the mode.
 *
 * __Note 2__ In master mode, if the SS pin is configured as an input, it must
 *  be held high.  Otherwise the SPI will be automatically turned into slave
 *  mode by hardware as soon as the SS pin goes low.

 * @code
 * hwa( configure,       spi0,
 *
 *      function,        master
 *                     | slave
 *                     | off,
 *
 *      //  Clock frequency
 *      //
 *      clock,           ioclk / (    2
 *                                |   4
 *                                |   8
 *                                |  16
 *                                |  32
 *                                |  64
 *                                | 128 ),
 *
 *    [ mode,            0 | 1 | 2 | 3, ]
 *
 *      //  State of SCK when idle
 *      //
 * |  [ idle_state,      low
 *                     | high,
 *
 *      //  Sampling clock edge
 *      //
 *      sampling_edge,   falling
 *                     | rising, ]
 *
 *    [ data_order,      lsb_first
 *                     | msb_first ] );
 * @endcode
 */
#define _hw_mtd_hwa_configure__spia	, _hwa_cfspia

#define _hwa_cfspia(o,i,a,k,...)					\
  do {									\
    const float ioclk = 1.0 ;						\
    HW_Y(_hwa_cfspia_kfunction,_hw_is_function_##k)(o,k,__VA_ARGS__,,);	\
  } while(0)

/*	Mandatory parameter `function`
 */
#define _hwa_cfspia_kfunction_0(o,k,...)	HW_E_VL(k,function)
#define _hwa_cfspia_kfunction_1(o,k,v,...)	HW_Y(_hwa_cfspia_vfunction,_hw_spia_function_##v)(o,v,__VA_ARGS__)
#define _hwa_cfspia_vfunction_0(o,v,...)	HW_E_AVL(function, v, master | slave | off)
#define _hwa_cfspia_vfunction_1(o,v,k,...)				\
  _hwa_write_reg(o,en, HW_A1(_hw_spia_function_##v));			\
  _hwa_write_reg(o,mstr, HW_A2(_hw_spia_function_##v));			\
  if ( HW_A1(_hw_spia_function_##v) == 1 ) {				\
    if ( HW_A2(_hw_spia_function_##v) == 0 ) {				\
      _hwa( configure, _HW_REL(o,pin_miso), function, digital_output );	\
    } else {								\
      _hwa( configure, _HW_REL(o,pin_mosi), function, digital_output );	\
      _hwa( configure, _HW_REL(o,pin_sck), function, digital_output );	\
    }									\
  }									\
  HW_Y(_hwa_cfspia_kclock,_hw_is_clock_##k)(o,k,__VA_ARGS__)

#define _hw_spia_function_master	, 1, 1	/* , en , mstr */
#define _hw_spia_function_slave		, 1, 0
#define _hw_spia_function_off		, 0, 0

/*	Mandatory parameter `clock`
 */
#define _hwa_cfspia_kclock_0(o,k,...)	HW_E_VL(k,clock)
#define _hwa_cfspia_kclock_1(o,k,v,...)	HW_Y(_hwa_cfspia_vclock,_hw_is_ioclk_##v)(o,v,__VA_ARGS__)
#define _hwa_cfspia_vclock_0(o,v,...)	HW_E_AVL(clock, v, ioclk / (2|4|8|16|32|64|128 ))
#define _hwa_cfspia_vclock_1(o,v,k,...)					\
  _hwa_write_reg(o,xpr, _hwa_cpspia_clk(v));				\
  HW_G2(_hwa_cfspia_kmode,HW_IS(mode,k))(o,k,__VA_ARGS__)

HW_INLINE uint8_t _hwa_cpspia_clk ( float v )
{
  if ( v == 1.0 / 2 )
    return 4 ;
  else if ( v == 1.0 / 4 )
    return 0 ;
  else if ( v == 1.0 / 8 )
    return 5 ;
  else if ( v == 1.0 / 16 )
    return 1 ;
  else if ( v == 1.0 / 32 )
    return 6 ;
  else if ( v == 1.0 / 64 )
    return 2 ;
  else if ( v == 1.0 / 128 )
    return 3 ;
  else
    HWA_E_NIL(clock, ioclk / (2|4|8|16|32|64|128 ));
  return 0 ;
}

/*	Optionnal parameter `mode`
 */
#define _hwa_cfspia_kmode_0(o,k,...)	HW_G2(_hwa_cfspia_kidle,HW_IS(idle_state,k))(o,k,__VA_ARGS__)
#define _hwa_cfspia_kmode_1(o,k,v,...)	HW_Y(_hwa_cfspia_vmode,_hw_spia_mode_##v)(o,v,__VA_ARGS__)
#define _hwa_cfspia_vmode_0(o,v,...)	HW_E_AVL(mode, v, (0|1|2|3))
#define _hwa_cfspia_vmode_1(o,v,k,...)					\
  _hwa_write_reg(o,mode,HW_A1(_hw_spia_mode_##v));			\
  HW_G2(_hwa_cfspia_korder,HW_IS(data_order,k))(o,k,__VA_ARGS__)

#define _hw_spia_mode_0			, 0	/* , mode */
#define _hw_spia_mode_1			, 1
#define _hw_spia_mode_2			, 2
#define _hw_spia_mode_3			, 3

/*	Optionnal parameter `idle_state`
 */
#define _hw_spia_idle_low		, 0	/* , cpol */
#define _hw_spia_idle_high		, 1

#define _hwa_cfspia_kidle_0(o,k,...)	HW_G2(_hwa_cfspia_korder,HW_IS(data_order,k))(o,k,__VA_ARGS__)
#define _hwa_cfspia_kidle_1(o,k,v,...)	HW_Y(_hwa_cfspia_vidle,_hw_spia_idle_##v)(o,v,__VA_ARGS__)
#define _hwa_cfspia_vidle_0(o,v,...)	HW_E_AVL(idle_state, v, low | high)
#define _hwa_cfspia_vidle_1(o,v,k,...)				\
  _hwa_write_reg(o,cpol, HW_A1(_hw_spia_idle_##v));		\
  HW_G2(_hwa_cfspia_ksampling,HW_IS(sampling_edge,k))(o,v,k,__VA_ARGS__)

/*	Mandatory parameter `sampling_edge` following `idle_state`
 */
#define _hw_spia_idle_low_sampling_rising	, 0	/* , cpol */
#define _hw_spia_idle_low_sampling_falling	, 1
#define _hw_spia_idle_high_sampling_rising	, 1
#define _hw_spia_idle_high_sampling_falling	, 0

#define _hwa_cfspia_ksampling_0(o,v,k,...)	HW_E_VL(k,sampling_edge)
#define _hwa_cfspia_ksampling_1(o,i,k,v,...)	HW_G2(_hwa_cfspia_vsampling,HW_IS(,_hw_spia_idle_##i##_sampling_##v))(o,i,v,__VA_ARGS__)
#define _hwa_cfspia_vsampling_0(o,i,v,...)	HW_E_AVL(sampling_edge, v, rising|falling)
#define _hwa_cfspia_vsampling_1(o,i,v,k,...)				\
  _hwa_write_reg(o,cpha, HW_A1(_hw_spia_idle_##i##_sampling_##v));	\
  HW_G2(_hwa_cfspia_korder,HW_IS(data_order,k))(o,k,__VA_ARGS__)  

/*	Optionnal parameter `data_order`
 */
#define _hwa_cfspia_korder_0(o,...)	HW_EOL(__VA_ARGS__)
#define _hwa_cfspia_korder_1(o,k,v,...)	HW_Y(_hwa_cfspia_vorder,_hw_spia_order_##v)(o,v,__VA_ARGS__)
#define _hwa_cfspia_vorder_0(o,v,...)	HW_E_AVL(order, v, (lsb_first|msb_first))
#define _hwa_cfspia_vorder_1(o,v,k,...)			\
  _hwa_write_reg(o,dord,HW_A1(_hw_spia_order_##v));	\
  HW_EOL(__VA_ARGS__)

#define _hw_spia_order_msb_first		, 0	/* , order */
#define _hw_spia_order_lsb_first		, 1


/**
 * @page atmelavr_spia
 * @section atmelavr_spia_data Data
 */

/**
 * @page atmelavr_spia
 * @code
 * hw( read, spi0 );
 * @endcode
 */
#define _hw_mtd_hw_read__spia		, _hw_read_spia
#define _hw_read_spia(o,i,a,...)	HW_TX(_hw_read_reg(o,dr),__VA_ARGS__)


/**
 * @page atmelavr_spia
 * @code
 * hw(_write, spi0, value );
 * @endcode
 */
#define _hw_mtd_hw_write__spia		, _hw_wrspia
#define _hw_wrspia(o,i,a,v,...)		HW_TX(_hw_write_reg(o,dr,v),__VA_ARGS__)

/* #define _hw_wrspia(o,i,a,v,...)						\ */
/*   HW_TX( __hw_wrspia( _hw_rap(o,if), _HW_A(_HW_M(o,dr)), v ), __VA_ARGS__) */

/* HW_INLINE uint8_t __hw_wrspia( intptr_t flag_addr, uint8_t flag_bp, intptr_t dr, uint8_t v ) */
/* { */
/*   uint8_t flag = 1U<<flag_bp ; */
/*   *(volatile uint8_t*)dr = v ; */
/*   while (1) { */
/*     uint8_t sr = *(volatile uint8_t*)flag_addr ; */
/*     if ( sr & flag ) */
/*	 return *(volatile uint8_t*)dr ; */
/*   } */
/* } */

/* /\** */
/*  * @page atmelavr_spia */
/*  * @code */
/*  * hwa_write( spi0, value ); */
/*  * @endcode */
/*  *\/ */
/* #define _hw_mtd_hwa_write__spia	, _hwa_write_spia */
/* #define _hwa_write_spia(o,i,a,v)	_hwa_write_reg(o,dr,v) */


/**
 * @page atmelavr_spia
 * @section atmelavr_spia_turn Turning on/off
 *
 * When the SPI is turned on, it takes control of the MOSI and MISO pins.
 *
 * @code
 * hw( turn, spi0, on | off );
 * @endcode
 */
#define _hw_mtd_hw_turn__spia		, _hw_turn_spia

#define _hw_turn_spia(o,i,a,k,...)				\
  HW_Y(_hw_turn_spia,_hw_state_##k)(o,k,__VA_ARGS__)
#define _hw_turn_spia_0(o,v, ...)			\
  HW_E_ST(v)
#define _hw_turn_spia_1(o,v, ...)				\
  HW_TX(_hw_write_reg(o, en, HW_A1(_hw_state_##v)),__VA_ARGS__)

/**
 * @page atmelavr_spia
 * @code
 * hwa( turn, spi0, on | off );
 * @endcode
 */
#define _hw_mtd_hwa_turn__spia		, _hwa_turn_spia

#define _hwa_turn_spia(o,i,a,k,...)				\
  HW_Y(_hwa_turn_spia,_hw_state_##k)(o,k,__VA_ARGS__)
#define _hwa_turn_spia_0(o,v, ...)			\
  HW_E_ST(v)
#define _hwa_turn_spia_1(o,v, ...)				\
  HW_TX(_hwa_write_reg(o, en, HW_A1(_hw_state_##v)),__VA_ARGS__)


/**
 * @page atmelavr_spia
 * @section atmelavr_spia_st Status
 *
 * Reading the "transfer complete" flag:
 *
 * @code
 * if ( hw( read, HW_IRQFLAG( spi0 ) ) )  // Read "transfer complete" IRQ flag
 *   hw( turn, HW_IRQ( spi0, off ) );     // Disable transfer complete IRQs
 * @endcode
 *
 * The "transfer complete" flag is cleared by hardware when the corresponding
 * ISR is executed. It is also cleared when the SPI is read or written after the
 * flag has been read:
 *
 * @code
 * if ( hw( read, HW_IRQFLAG( spi0 ) ) )  // Read transfer complete IRQ flag
 *   data = hw( read, spi0 );             // Read data and clear transfer complete IRQ flag
 * @endcode
 *
 * The `hw(stat,)` instruction lets you read the `collision` flag:
 *
 * @code
 * //  Create a structure to receive the counter status
 * //
 * hw_stat_t( spi0 ) st ;
 *
 * //  Copy the SPI status into the structure
 * //
 * st = hw( stat, spi0 );
 *
 * //  Process the collision flag
 * //
 * if ( st.collision )
 *   n_collisions++ ;
 * @endcode
 */
#define _hw_mtd_hw_stat__spia		, _hw_stat_spia
#define _hw_mtd_hw_stat_t__spia	, _hw_statt_spia

#define _hw_statt_spia(o,i,a,...)	HW_TX(_hw_spia_stat_t, __VA_ARGS__)

typedef union {
  uint8_t	  byte ;
  struct {
    unsigned int  _0_5	    : 6 ;
    unsigned int  collision : 1 ;
    unsigned int  _7	    : 1 ;
  };
} _hw_spia_stat_t ;

#define _hw_stat_spia(o,i,a,...)	HW_TX(_hw_spia_stat(_hw_read_reg(o, sr)), __VA_ARGS__)

HW_INLINE _hw_spia_stat_t _hw_spia_stat( uint8_t byte )
{
  _hw_spia_stat_t	st ;
  st.byte = byte ;
  return st ;
}


/*******************************************************************************
 *									       *
 *	Context management						       *
 *									       *
 *******************************************************************************/

#define _hwa_setup__spia(o,i,a)		\
  _hwa_setup_reg( o, cr );			\
  _hwa_setup_reg( o, sr )

#define _hwa_init__spia(o,i,a)			\
  _hwa_init_reg( o, cr, 0x00 );			\
  _hwa_init_reg( o, sr, 0x00 )

#define _hwa_commit__spia(o,i,a)		\
  _hwa_commit_reg( o, cr );			\
  _hwa_commit_reg( o, sr )



/**
 * @page atmelavr_spia
 * @section atmelavr_spia_internals Internals
 *
 * Class `_spia` objects hold the following hardware registers:
 *
 *  * `cr`: control register
 *  * `sr`: status register
 *  * `dr`: data register
 *
 * that hold the following logical registers:
 *
 *  * `en`: spi enable
 *  * `dord`: data order
 *  * `mstr`: master/slave
 *  * `cpol`: clock polarity
 *  * `cpha`: clock phase
 *  * `xpr`: clock prescaler
 *  * `wcol`: write collision
 *  * `sp2x`: double clock speed
 *  * `ie`: overflow interrupt mask
 *  * `if`: overflow interrupt flag
 *
 * These registers are accessible through the @ref public_ins
 * "register access intructions".
 */


/**
 * @page atmelavr_spia
 * <br>
 */
