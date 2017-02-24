
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
 * hwa_config( USI,
 *
 *             //  How the USI behaves
 *             //
 *             mode,    disconnected          // The USI is disabled
 *                    | spi_master            // The USI acts as a SPI master
 *                    | spi_slave             // The USI acts as a SPI slave
 *                    | twi_master            // The USI acts as a I²C master
 *                    | twi_slave,            // The USI acts as a I²C slave
 *
 *             //  How is it clocked
 *             //
 *             clock,   software              // Clocked by software
 *                    | hw_oc0                // Clocked by compare unit ? of counter 0
 *                    | external_rising       // Clocked by external source rising edge
 *                    | external_falling      // Clocked by external source falling edge
 *            );
 * @endcode
 */
#define _hw_mthd_hwa_configure__usia	, _hwa_cfusia

#define _hw_usia_mode_disconnected	, 1
#define _hw_usia_mode_spi_master	, 2
#define _hw_usia_mode_spi_slave		, 3
#define _hw_usia_mode_twi_master	, 4
#define _hw_usia_mode_twi_slave		, 5

#define _hw_usia_clock_software		, 0
#define _hw_usia_clock_oc0		, 1	/* FIXME: compare or overflow? */
#define _hw_usia_clock_external_rising	, 2
#define _hw_usia_clock_external_falling	, 3

#define _hw_is_mode_mode		, 1

/* 	Mandatory argument `mode`
 */
#define _hwa_cfusia( o,i,a,... )					\
  do {									\
    uint8_t mode, clock ;						\
    HW_G2(_hwa_cfusia_kmode, HW_IS(mode,__VA_ARGS__))(o,__VA_ARGS__,,)	\
      } while(0)
#define _hwa_cfusia_kmode_0(o,k,...)	HW_E_VL(k, mode)
#define _hwa_cfusia_kmode_1(o,kw,...)	HW_G2(_hwa_cfusia_vmode, HW_IS(,_hw_usia_mode_##__VA_ARGS__))(o,__VA_ARGS__)
#define _hwa_cfusia_vmode_0(o,v,...)	HW_E_AVL(mode, v, spi_master | spi_slave)
#define _hwa_cfusia_vmode_1(o,v,...)					\
  mode = HW_A1(_hw_usia_mode_##v);					\
  HW_G2(_hwa_cfusia_kclock, HW_IS(clock,__VA_ARGS__))(o,__VA_ARGS__)

#define _hwa_cfusia_kclock_0(o,k,...)	HW_E_VL(k, clock)
#define _hwa_cfusia_kclock_1(o,kw,...)	HW_G2(_hwa_cfusia_vclock, HW_IS(,_hw_usia_clock_##__VA_ARGS__))(o,__VA_ARGS__)
#define _hwa_cfusia_vclock_0(o,v,...)	HW_E_AVL(clock, v, software | oc0 | external_rising | external_falling)
#define _hwa_cfusia_vclock_1(o,v,...)					\
  clock = HW_A1(_hw_usia_clock_##v);					\
  HW_TX(_hwa_docfusia(o,mode,clock),__VA_ARGS__);

#define _hwa_docfusia( o, mode, clock )				\
  if ( mode != HW_A1(_hw_usia_mode_spi_master)			\
       && mode != HW_A1(_hw_usia_mode_spi_slave) )		\
    HWA_ERR("sorry, desired mode is not supported yet.");	\
  if ( clock != HW_A1(_hw_usia_clock_software) )		\
    HWA_ERR("sorry, desired clock mode is not supported yet.");	\
  _hwa_write_reg( o, wm, 1 );					\
  _hwa_write_reg( o, cs, 2 );					\
  if ( mode == HW_A1(_hw_usia_mode_spi_master) ) {		\
    _hwa( configure, HW_PIN(usck), direction, output );		\
    _hwa( configure, HW_PIN(do),   direction, output );		\
    _hwa( configure, HW_PIN(di),   direction, input  );		\
    _hwa_write_reg( o, clk, 1 );				\
  }								\
  else								\
    _hwa_write_reg( o, clk, 0 );


/**
 * @page atmelavr_usia
 * @section atmelavr_usia_data Data
 *
 * @code
 * uint8_t byte = hw_read( usi0 );
 * @endcode
 */
#define _hw_mthd_hw_read__usia		, _hw_rdusia

/*  FIXME: the datasheet advices using br instead of dr but does not tell at
 *  what moment br is valid. Reading br returns weird values...
 */
#define _hw_rdusia(o,i,a,...)		HW_TX( _hw_read_reg( o, dr ), __VA_ARGS__ )


/**
 * @page atmelavr_usia
 *
 * @code
 * hw_write( usi0, 'A' );
 * @endcode
 */
#define _hw_mthd_hw_write__usia		, _hw_wrusia

#define _hw_wrusia(o,i,a,v,...)		HW_TX( _hw_write_reg( o, dr, v ), __VA_ARGS__ )


/**
 * @page atmelavr_usia
 * @section atmelavr_usia_trigger Clocking
 *
 * @code
 * hw_trigger( usi0 );
 * @endcode
 */

 /* FIXME: 2 types of clocking should be handled. Look at the datasheet. */

#define _hw_mthd_hw_trigger__usia	, _hw_tgusia

#define _hw_tgusia(o,i,a,...)		HW_TX( _hw_write_reg(o,tc,1),__VA_ARGS__ )



/**
 * @page atmelavr_usia_spimaster_swclk
 * @section atmelavr_usia_spimaster_swclk_config Configuring the SPI
 *
 * @code
 * #define SPI		spimaster0_swclk
 *
 * hw_config( SPI );
 * @endcode
 */
#define _hw_mthd_hwa_configure__usia_spimaster_swclk		, _hwa_cfspimswclk

#define _hwa_cfspimswclk(p,i,o,...)		\
  HW_TX( _hwa_docfspimswclk(o), __VA_ARGS__ )

#define _hwa_docfspimswclk( o )			\
  do {							\
    _hwa( configure, HW_PIN(usck), direction, output );	\
    _hwa( configure, HW_PIN(do),   direction, output );	\
    _hwa_write_reg( o, wm,  1 );			\
    _hwa_write_reg( o, cs,  2 );			\
    _hwa_write_reg( o, clk, 1 );			\
  } while(0)


/**
 * @page atmelavr_usia_spimaster_swclk
 * @section atmelavr_usia_spimaster_swclk_read Getting the last received byte
 *
 * @code
 * #define SPI		spimaster0_swclk
 *
 * uint8_t byte = hw_read( SPI );
 * @endcode
 */
#define _hw_mthd_hw_read__usia_spimaster_swclk			, _hw_rdspimswclk

#define _hw_rdspimswclk(o,i,usio,...)		HW_TX( _hw_read_reg( usio, dr ), __VA_ARGS__ )


/**
 * @page atmelavr_usia_spimaster_swclk
 * @section atmelavr_usia_spimaster_swclk_write Sending one byte
 *
 * @code
 * hw_write( spimaster0_swclk, 'A' );
 * @endcode
 */
#define _hw_mthd_hw_write__usia_spimaster_swclk		, _hw_wrspimswclk

#define _hw_wrspimswclk(p,i,usin,v,...)			\
  HW_TX(						\
	do {						\
	  _hw_write_reg(usin, dr, v );			\
	  _hw_write_reg(usin, ifov, 1 );			\
	  do						\
	    _hw_write_reg(usin, tc, 1);			\
	  while( _hw_read_reg(usin, ifov) == 0 );	\
	}while(0), __VA_ARGS__ )



/*	Configuration of USI as SPI master with counter0_overflow clock
 */
#define _hw_mthd_hwa_configure_usia_spimaster_c0clk		, _hwa_cfspimc0clk

#define _hwa_docfspimc0clk( hwa, o )			\
  do {							\
    _hwa( configure, HW_PIN(usck), direction, output );	\
    _hwa( configure, HW_PIN(do),   direction, output );	\
    _hwa( configure, HW_PIN(di),   direction, input  );	\
    _hwa_write_reg( o, wm,  1 );			\
    _hwa_write_reg( o, cs,  1 );			\
    _hwa_write_reg( o, clk, 0 );			\
  } while(0)


#define _hw_mthd_hw_write_usia_spimaster_c0clk	, _hw_write_usia_spimaster_c0clk

#define _hw_write_usia_spimaster_c0clk(c,n,i, usin, v)	\
  _hw_write_reg(##usin, dr, v )


#define _hw_mthd_hw_read_usia_spimaster_c0clk	, _hw_read_usia


/*******************************************************************************
 *									       *
 *	Context management						       *
 *									       *
 *******************************************************************************/

#define _hwa_setup__usia(o,i,a)		_hwa_setup_reg( o, cr )
#define _hwa_init__usia(o,i,a)		_hwa_init_reg( o, cr, 0x00 )
#define _hwa_commit__usia(o,i,a)	_hwa_commit_reg( o, cr )

/**
 * @page atmelavr_usia
 * <br>
 */
