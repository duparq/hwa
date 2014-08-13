
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


/*	Configuration
 */
#define hw_def_hwa_config_usia		, _hwa_cfusia

#define hw_usia_mode_disconnected	, 1
#define hw_usia_mode_spi_master		, 2
#define hw_usia_mode_spi_slave		, 3
#define hw_usia_mode_2wire_master	, 4
#define hw_usia_mode_2wire_slave	, 5

#define hw_usia_clock_software		, 0
#define hw_usia_clock_counter0_compare	, 1	/* FIXME: compare or overflow? */
#define hw_usia_clock_external_rising	, 2
#define hw_usia_clock_external_falling	, 3

#define hw_is_mode_mode			, 1

#define _hwa_cfusia(c,n,i,a,...)					\
  do {									\
    uint8_t mode, clock ;						\
    HW_G2(_hwa_cfusia_xmode, HW_IS(mode,__VA_ARGS__))(n,__VA_ARGS__,)	\
      } while(0)
#define _hwa_cfusia_xmode_0(n,...)					\
  HW_ERR("expected `mode` instead of `" HW_QUOTE(__VA_ARGS__) "`.")
#define _hwa_cfusia_xmode_1(n,mode,...)					\
  HW_G2(_hwa_cfusia_vmode, HW_IS(,hw_usia_mode_##__VA_ARGS__))(n,__VA_ARGS__)
#define _hwa_cfusia_vmode_0(n,vmode,...)			\
  HW_ERR("`"#vmode"` is not a valid value for `mode`."		\
	 " Valid values are `spi_master`, `spi_slave`.")
#define _hwa_cfusia_vmode_1(n,vmode,...)				\
  mode = HW_A1(hw_usia_mode_##vmode);					\
  HW_G2(_hwa_cfusia_xclock, HW_IS(clock,__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_cfusia_xclock_0(n,...)					\
  HW_ERR("expected `clock` instead of `" HW_QUOTE(__VA_ARGS__) "`.")
#define _hwa_cfusia_xclock_1(n,clock,...)				\
  HW_G2(_hwa_cfusia_vclock, HW_IS(,hw_usia_clock_##__VA_ARGS__))(n,__VA_ARGS__)
#define _hwa_cfusia_vclock_0(n,x,...)			\
  HW_ERR("`"#x"` is not a valid value for `clock`.")
#define _hwa_cfusia_vclock_1(n,vclock,...)				\
  clock = HW_A1(hw_usia_clock_##vclock);				\
  HW_TX(_hwa_docfusia(hwa, &hwa->n, mode, clock),__VA_ARGS__);


HW_INLINE void _hwa_docfusia( hwa_t *hwa, hwa_usia_t *p, uint8_t mode, uint8_t clock )
{
  if ( mode != HW_A1(hw_usia_mode_spi_master)
       && mode != HW_A1(hw_usia_mode_spi_slave) ) {
    HWA_ERR("sorry, desired mode is not supported yet.");
    return ;
  }
  
  if ( clock != HW_A1(hw_usia_clock_software) ) {
    HWA_ERR("sorry, desired clock mode is not supported yet.");
    return ;
  }

  if ( mode == HW_A1(hw_usia_mode_spi_master) ) {
#if defined HWA_DEVICE_ATTINYX4
    hwa_config(hw_pin_pa4, output);	/* USCK */
    hwa_config(hw_pin_pa5, output);	/* DO   */
    hwa_config(hw_pin_pa6, input);	/* DI   */
#else
    HWA_ERR("sorry, this configuration is not handled yet.");
#endif
    _hwa_write_p(p, _hw_creg(usia, wm), 1 );
    _hwa_write_p(p, _hw_creg(usia, cs), 2 );
    _hwa_write_p(p, _hw_creg(usia, clk), 1 );
  }
  else {
    _hwa_write_p(p, _hw_creg(usia, wm), 1 );
    _hwa_write_p(p, _hw_creg(usia, cs), 2 );
    _hwa_write_p(p, _hw_creg(usia, clk), 0 );
  }
}


#define _hw_read_usia(c,n,i, usin)	\
  hw_read_reg( hw_##usin, dr );


/*	Configuration of USI as SPI master with software clock
 */
#define hw_def_hwa_config_usia_spimaster_swclk		, _hwa_cfspimswclk

#define _hwa_cfspimswclk(c,n,i, usin)		\
  _hwa_docfspimswclk(hwa, &hwa->usin)

HW_INLINE void _hwa_docfspimswclk( hwa_t *hwa, hwa_usia_t *p )
{
#if defined HWA_DEVICE_ATTINYX4
  hwa_config(hw_pin_pa4, output);	/* USCK */
  hwa_config(hw_pin_pa5, output);	/* DO   */
#else
  HWA_ERR("sorry, this configuration is not handled yet.");
#endif
  _hwa_write_p(p, _hw_creg(usia, wm), 1 );
  _hwa_write_p(p, _hw_creg(usia, cs), 2 );
  _hwa_write_p(p, _hw_creg(usia, clk), 1 );
}


#define hw_def_hw_write_usia_spimaster_swclk	, _hw_write_usia_spimaster_swclk

#define _hw_write_usia_spimaster_swclk(c,n,i, usin, v)	\
  do {							\
    _hw_write_reg(hw_##usin, dr, v );			\
    _hw_write_reg(hw_##usin, oif, 1 );			\
    while( _hw_read_reg(hw_##usin, oif) == 0 ) {	\
      _hw_write_reg(hw_##usin, tc, 1);			\
      /* hw_nop_loop(17); 1 bit every 5us @8MHz */					\
    }							\
  }while(0)


#define hw_def_hw_read_usia_spimaster_swclk	, _hw_read_usia


/*	Configuration of USI as SPI master with counter0_overflow clock
 */
#define hw_def_hwa_config_usia_spimaster_c0clk		, _hwa_cfspimc0clk

#define _hwa_cfspimc0clk(c,n,i, usin)		\
  _hwa_docfspimswclk(hwa, &hwa->usin)


HW_INLINE void _hwa_docfspimc0clk( hwa_t *hwa, hwa_usia_t *p )
{
#if defined HWA_DEVICE_ATTINYX4
  hwa_config(hw_pin_pa4, output);	/* USCK */
  hwa_config(hw_pin_pa5, output);	/* DO   */
  hwa_config(hw_pin_pa6, input);	/* DI   */
#else
  HWA_ERR("sorry, this configuration is not handled yet.");
#endif
  _hwa_write_p(p, _hw_creg(usia, wm), 1 );
  _hwa_write_p(p, _hw_creg(usia, cs), 1 );
  _hwa_write_p(p, _hw_creg(usia, clk), 0 );
}


#define hw_def_hw_write_usia_spimaster_c0clk	, _hw_write_usia_spimaster_c0clk

#define _hw_write_usia_spimaster_c0clk(c,n,i, usin, v)	\
  _hw_write_reg(hw_##usin, dr, v )


#define hw_def_hw_read_usia_spimaster_c0clk	, _hw_read_usia
