
/* This file is part of the HWA project.
 * Copyright (c) 2018 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief PCF8574: 8-bit I/O expander for I²C bus
 * @page pcf8574 PCF8574: 8-bit I/O expander for I²C bus
 *
 * As this device is not speed critical, its implementation focuses on code size
 * rather than on speed, so it relies on extern C functions rather than on
 * inlined code.
 *
 * Currently, HWA supports only the driving of the HD44780 through the I2C
 * expander PCF8574.
 *
 * __Declaration__
 *
 * @code
 * #define PCF          HW_PCF8574( interface, twi0, address, 0x27 )
 * @endcode
 */
#define hw_class__pcf8574

#define _hw_is_interfaceaddress_interfaceaddress	, 1

#define HW_PCF8574(...)				_HW_PCF8574_01(__VA_ARGS__,,,,,)
#define _HW_PCF8574_01(k1,v1,k2,v2,eol,...)				\
  HW_Y(_HW_PCF8574_01_,_hw_is_interfaceaddress_##k1##k2##eol)(k1,v1,k2,v2)
#define _HW_PCF8574_01_0(...)						\
  ,HW_PCF8574(...),"HW_PCF8574(...)" must be defined as "HW_PCF8574(interface,...,address,...)"
#define _HW_PCF8574_01_1(k1,twi,k2,sla)		_HW_PCF8574_02(HW_A1(HW_X(twi)),sla)
#define _HW_PCF8574_02(...)			_HW_PCF8574_03(__VA_ARGS__)
#define _HW_PCF8574_03(otwi,sla)		xb(_pcf8574,pcf8574_##otwi##_##sla,otwi,sla)


/**
 * @page pcf8574
 * __Interface__
 *
 * The following makes the implementation functions for TWI declared. Use it in
 * your header files:
 *
 * @code
 * HW_DECLARE(PCF);
 * @endcode
 */
#define HW_DECLARE__pcf8574		, _hw_declare_pcf8574

#define _hw_declare_pcf8574(o,twi,sla,...)				\
  									\
  extern uint8_t _hw_##o##_reg ;					\
									\
  HW_INLINE uint8_t _hw_##o##_read ( )					\
  {									\
    return _hw_##twi##_start_read_stop(sla);				\
  }									\
									\
  HW_INLINE uint8_t _hw_##o##_read_np ( uint8_t n, uint8_t p )		\
  {									\
    return (_hw_##twi##_start_read_stop(sla)>>p) & ((1U<<n)-1);		\
  }									\
									\
  HW_INLINE void _hw_##o##_writea_np ( uint8_t n, uint8_t p, uint8_t v ) \
  {									\
    _hw_##o##_reg = (_hw_##o##_reg & ~(((1U<<n)-1)<<p)) | (v<<p) ;	\
  }									\
									\
  HW_INLINE void _hw_##o##_togglea_np ( uint8_t n, uint8_t p )		\
  {									\
    _hw_##o##_reg = _hw_##o##_reg ^ (((1U<<n)-1)<<p) ;			\
  }									\
									\
  HW_INLINE void _hw_##o##_commit ( )					\
  {									\
    _hw_##twi##_start_write_stop(sla,_hw_##o##_reg);			\
  }									\
									\
  HW_INLINE void _hw_##o##_write ( uint8_t v )				\
  {									\
    _hw_##o##_reg = v ;							\
    _hw_##o##_commit();							\
  }									\
									\
  HW_INLINE void _hw_##o##_write_np ( uint8_t n, uint8_t p, uint8_t v ) \
  {									\
    _hw_##o##_writea_np(n,p,v) ;					\
    _hw_##o##_commit();							\
  }									\
									\
  HW_INLINE void _hw_##o##_toggle_np ( uint8_t n, uint8_t p )		\
  {									\
    _hw_##o##_togglea_np(n,p) ;						\
    _hw_##o##_commit();							\
  }									\
									\
  extern void _hwa_fake() /* require a ; */


/**
 * @page pcf8574
 * __Implement__
 *
 * The following makes the implementation functions for TWI defined. It must
 * appear in one of your source files:
 *
 * @code
 * HW_DEFINE(PCF);
 * @endcode
 */
#define HW_DEFINE__pcf8574		, _hw_define_pcf8574_
#define HW_DEFINE_WEAK__pcf8574	, _hw_define_pcf8574w

#define _hw_define_pcf8574_(o,sla,twi,...)	_hw_define_pcf8574(o,sla,twi,,__VA_ARGS__)
#define _hw_define_pcf8574w(o,sla,twi,...)	_hw_define_pcf8574(o,sla,twi,__attribute__((weak)),__VA_ARGS__)
#define _hw_define_pcf8574(o,sla,twi,attr,...)	uint8_t attr _hw_##o##_reg


/**
 * @page pcf8574
 *
 * __Actions__
 *
 * `configure`
 *
 * @code
 * hw( configure, PCF );
 * @endcode
 *
 * @code
 * hwa( configure, PCF );
 * @endcode
 */
#define hw_configure__pcf8574		, _hw_cfpcf8574
#define hwa_configure__pcf8574		, _hwa_cfpcf8574

#define _hw_cfpcf8574(o,sla,twi,...)	_hwx_cfpcf8574(o,sla,twi,__VA_ARGS__)
#define _hwa_cfpcf8574(o,sla,twi,...)	_hwx_cfpcf8574(o,sla,twi,__VA_ARGS__)
#define _hwx_cfpcf8574(o,sla,twi,...)	_hw_##o##_reg = 0xFF HW_EOL(__VA_ARGS__)


/**
 * @page pcf8574
 *
 * `write`
 * @code
 * hw( write, PCF, value );
 * @endcode
 */
#define hw_write__pcf8574			, _hw_wrpcf8574
#define _hw_wrpcf8574(o,sla,twi,v,...)		_hw_##o##_write(v)

#define hw_read__pcf8574			, _hw_rdpcf8574
#define _hw_rdpcf8574(o,sla,twi,...)		_hw_##o##_read()

#define hw_commit__pcf8574			, _hw_commit_pcf8574
#define _hw_commit_pcf8574(o,sla,twi,...)	_hw_##o##_commit()


/*  IO
 */
#define hw_class__pcf8574_io

#define HW_IO__pcf8574				, _hw_io_pcf8574
#define _hw_io_pcf8574(opcf,sla,twil,bn,bp,...)	xb(_pcf8574_io,opcf,bn,bp)

#define HW_BITS__pcf8574_io			, _hw_bits_pcf8574_io
#define _hw_bits_pcf8574_io(opcf,n,p,...)	n

/* #define HW_PORT_pcf8574io			, _hw_port_pcf8574io */
/* #define _hw_port_pcf8574io(opcf,...)		_pcf8574,opcf,null,0 */

#define HW_PORT__pcf8574_io			, _hw_port__pcf8574_io
#define _hw_port__pcf8574_io(opcf,...)		_pcf8574,opcf,null,0

/*  FIXME: this implementation of 'configure' is a fake used for testing the
 *  compilability when a PCF8574 drives another PCF8574
 */
/* #define hw_configure__pcf8574_io		, _hw_cfpcf8574io */
/* #define _hw_cfpcf8574io(opcf,bn,bp,...)		_hw_##opcf##_write_np(bn,bp,1) */

#define hw_write__pcf8574_io			, _hw_pcf8574iowr
#define _hw_pcf8574iowr(opcf,bn,bp,v,...)	_hw_##opcf##_write_np(bn,bp,v)

#define hw_toggle__pcf8574_io			, _hw_pcf8574iotg
#define _hw_pcf8574iotg(opcf,bn,bp,...)		_hw_##opcf##_toggle_np(bn,bp)

#define hw_writea__pcf8574_io			, _hw_pcf8574iowra

#define _hw_pcf8574iowra(opcf,bn,bp,v,...)	_hw_##opcf##_writea_np(bn,bp,v)

#define hw_read__pcf8574_io			, _hw_pcf8574iord
#define _hw_pcf8574iord(opcf,bn,bp,v,...)	_hw_##opcf##_read_np(bn,bp)

#define hwa_write__pcf8574_io			, _hwa_pcf8574iowr
#define _hwa_pcf8574iowr(opcf,bn,bp,v,...)	_hw_##opcf##_writea_np(bn,bp,v)
