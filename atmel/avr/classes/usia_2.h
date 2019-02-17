
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Universal Serial Interface
 */

/**
 * @page atmelavr_usia
 * @section atmelavr_usia_config Configuration
 *
 * @code
 * hwa( configure, USI,
 *
 *      //  How the USI behaves
 *      //
 *      mode,    disconnected          // The USI is disabled
 *             | spi_master            // The USI acts as a SPI master
 *             | spi_slave             // The USI acts as a SPI slave
 *             | twi_master            // The USI acts as a I²C master
 *             | twi_slave,            // The USI acts as a I²C slave
 *
 *      //  How is it clocked
 *      //
 *      clock,   software              // Clocked by software
 *             | compare0              // Clocked by compare unit ? of counter 0
 *             | external_rising       // Clocked by external source rising edge
 *             | external_falling      // Clocked by external source falling edge
 *      );
 * @endcode
 */
#define hwa_configure__usia	, _hwa_cfusia

#define _hw_usia_mode_disconnected	, 1
#define _hw_usia_mode_spi_master	, 2
#define _hw_usia_mode_spi_slave		, 3
#define _hw_usia_mode_twi_master	, 4
#define _hw_usia_mode_twi_slave		, 5

#define _hw_usia_clock_software		, 0
#define _hw_usia_clock_compare0		, 1	/* FIXME: compare or overflow? */
#define _hw_usia_clock_external_rising	, 2
#define _hw_usia_clock_external_falling	, 3

/*	Mandatory argument `mode`
 */
#define _hwa_cfusia(o,i,a,k,...)					\
  do {									\
    uint8_t mode, clock ;						\
    HW_Y(_hwa_cfusia_kmode_,_hw_is_mode_##k)(o,k,__VA_ARGS__,,)		\
      } while(0)
#define _hwa_cfusia_kmode_0(o,k,...)	HW_E_VL(k, mode)
#define _hwa_cfusia_kmode_1(o,k,v,...)	HW_Y(_hwa_cfusia_vmode_,_hw_usia_mode_##v)(o,v,__VA_ARGS__)
#define _hwa_cfusia_vmode_0(o,v,...)	HW_E_AVL(mode, v, spi_master | spi_slave)
#define _hwa_cfusia_vmode_1(o,v,k,...)					\
  mode = HW_A1(_hw_usia_mode_##v);					\
  HW_Y(_hwa_cfusia_kclock_,_hw_is_clock_##k)(o,k,__VA_ARGS__)

#define _hwa_cfusia_kclock_0(o,k,...)	HW_E_VL(k, clock)

/*	Mandatory argument `clock`
 */
#define _hwa_cfusia_kclock_1(o,k,v,...)	HW_Y(_hwa_cfusia_vclock_,_hw_usia_clock_##v)(o,v,__VA_ARGS__)
#define _hwa_cfusia_vclock_0(o,v,...)	HW_E_AVL(clock, v, software | compare0 | external_rising | external_falling)
#define _hwa_cfusia_vclock_1(o,v,...)					\
  clock = HW_A1(_hw_usia_clock_##v);					\
  _hwa_docfusia(o,mode,clock) HW_EOL(__VA_ARGS__);

#define _hwa_docfusia( o, mode, clock )				\
  if ( mode != HW_A1(_hw_usia_mode_spi_master)			\
       && mode != HW_A1(_hw_usia_mode_spi_slave) )		\
    HWA_ERR("sorry, desired mode is not supported yet.");	\
  if ( clock != HW_A1(_hw_usia_clock_software) )		\
    HWA_ERR("sorry, desired clock mode is not supported yet.");	\
  _hwa_write( o, wm, 1 );					\
  _hwa_write( o, cs, 2 );					\
  if ( mode == HW_A1(_hw_usia_mode_spi_master) ) {		\
    _hwa( configure, HW_PIN(usck), mode, digital_output );		\
    _hwa( configure, HW_PIN(do),   mode, digital_output );		\
    _hwa( configure, HW_PIN(di),   mode, digital_input  );		\
    _hwa_write( o, clk, 1 );				\
  }								\
  else								\
    _hwa_write( o, clk, 0 );


/**
 * @page atmelavr_usia
 * @section atmelavr_usia_data Data
 *
 * @code
 * uint8_t byte = hw( read, usi0 );
 * @endcode
 */
#define hw_read__usia		, _hw_rdusia

/*  FIXME: the datasheet advices using br instead of dr but does not tell at
 *  what moment br is valid. Reading br returns weird values...
 */
#define _hw_rdusia(o,i,a,...)		 _hw_read( o, dr ) HW_EOL(__VA_ARGS__)


/**
 * @page atmelavr_usia
 *
 * @code
 * hw( write, usi0, 'A' );
 * @endcode
 */
#define hw_write__usia		, _hw_wrusia

#define _hw_wrusia(o,i,a,v,...)		 _hw_write( o, dr, v ) HW_EOL(__VA_ARGS__)


/**
 * @page atmelavr_usia
 * @section atmelavr_usia_trigger Clocking
 *
 * @code
 * hw( trigger, usi0 );
 * @endcode
 */

 /* FIXME: 2 types of clocking should be handled. Look at the datasheet. */

#define hw_trigger__usia	, _hw_tgusia

#define _hw_tgusia(o,i,a,...)		 _hw_write(o,tc,1) HW_EOL(__VA_ARGS__)



/**
 * @page atmelavr_usia_spimaster_swclk
 * @section atmelavr_usia_spimaster_swclk_config Configuring the SPI
 *
 * @code
 * #define SPI		spimaster0_swclk
 *
 * hw( configure, SPI );
 * @endcode
 */
#define hwa_configure__usia_spimaster_swclk	, _hwa_cfspimswclk

#define _hwa_cfspimswclk(p,i,o,...)		\
   _hwa_docfspimswclk(o) HW_EOL(__VA_ARGS__)

#define _hwa_docfspimswclk( o )			\
  do {							\
    _hwa( configure, _HW_PIN(o,ck), mode, digital_output );		\
    _hwa( configure, _HW_PIN(o,do), mode, digital_output );		\
    _hwa_write( o, wm,  1 );			\
    _hwa_write( o, cs,  2 );			\
    _hwa_write( o, clk, 1 );			\
  } while(0)


/**
 * @page atmelavr_usia_spimaster_swclk
 * @section atmelavr_usia_spimaster_swclk_read Getting the last received byte
 *
 * @code
 * #define SPI		spimaster0_swclk
 *
 * uint8_t byte = hw( read, SPI );
 * @endcode
 */
#define hw_read__usia_spimaster_swclk	, _hw_rdspimswclk

#define _hw_rdspimswclk(o,i,usio,...)		 _hw_read( usio, dr ) HW_EOL(__VA_ARGS__)


/**
 * @page atmelavr_usia_spimaster_swclk
 * @section atmelavr_usia_spimaster_swclk_write Sending one byte
 *
 * @code
 * hw( write, spimaster0_swclk, 'A' );
 * @endcode
 */
#define hw_write__usia_spimaster_swclk	, _hw_wrspimswclk

#define _hw_wrspimswclk(p,i,usin,v,...)		\
  do {						\
    _hw_write(usin, dr, v );		\
    _hw_write(usin, ifov, 1 );		\
    do						\
      _hw_write(usin, tc, 1);		\
    while( _hw_read(usin, ifov) == 0 );	\
  }while(0)					\
    HW_EOL( __VA_ARGS__ )



/*	Configuration of USI as SPI master with counter0_overflow clock
 */
#define hwa_configure_usia_spimaster_c0clk	, _hwa_cfspimc0clk

#define _hwa_docfspimc0clk( hwa, o )			\
  do {							\
    _hwa( configure, HW_PIN(usck), mode, digital_output );	\
    _hwa( configure, HW_PIN(do),   mode, digital_output );	\
    _hwa( configure, HW_PIN(di),   mode, digital_input  );	\
    _hwa_write( o, wm,  1 );			\
    _hwa_write( o, cs,  1 );			\
    _hwa_write( o, clk, 0 );			\
  } while(0)


#define hw_write_usia_spimaster_c0clk	, _hw_write_usia_spimaster_c0clk

#define _hw_write_usia_spimaster_c0clk(c,n,i, usin, v)	\
  _hw_write(##usin, dr, v )


#define hw_read_usia_spimaster_c0clk	, _hw_read_usia


/*******************************************************************************
 *									       *
 *	Context management						       *
 *									       *
 *******************************************************************************/

#define _hwa_setup__usia(o,i,a)		_hwa_setup_r( o, cr )
#define _hwa_init__usia(o,i,a)		_hwa_init_r( o, cr, 0x00 )
#define _hwa_commit__usia(o,i,a)	_hwa_commit_r( o, cr )
