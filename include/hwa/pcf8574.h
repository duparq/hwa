
/* This file is part of the HWA project.
 * Copyright (c) 2018 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief PCF8574
 */

/**
 * @page hwa_pcf8574 Class _pcf8574
 *
 * Definition:
 *
 * @code
 * #define PCF		HW_PCF8574( interface, twi0, address, 0x27 )
 * @endcode
 */

#define hw_class__pcf8574

#define _hw_is_interfaceaddress_interfaceaddress	, 1

#define HW_PCF8574(...)				_HW_PCF8574_01(__VA_ARGS__,,,,,)
#define _HW_PCF8574_01(k1,v1,k2,v2,eol,...)	HW_Y(_HW_PCF8574_01_,_hw_is_interfaceaddress_##k1##k2##eol)(k1,v1,k2,v2)
#define _HW_PCF8574_01_0(...)						\
  ,HW_PCF8574(...),"HW_PCF8574(...)" must be defined as "HW_PCF8574(interface,...,address,...)"
/* #define _HW_PCF8574_01_1(k1,twi,k2,sla)		pcf8574(HW_G3(pcf8574,HW_A1(HW_X(twi)),sla),twi,sla) */
#define _HW_PCF8574_01_1(k1,twi,k2,sla)		_HW_PCF8574_02(HW_A1(HW_X(twi)),sla)
#define _HW_PCF8574_02(...)			_HW_PCF8574_03(__VA_ARGS__)
/* #define _HW_PCF8574_03(twi,sla)			_HW_PCF8574_04(HW_A1 twi, twi,sla) */
/* #define _HW_PCF8574_04(...)			_HW_PCF8574_05(__VA_ARGS__) */
#define _HW_PCF8574_03(otwi,sla)			pcf8574(pcf8574_##otwi##_##sla,otwi,sla)


#define _HW_X_pcf8574			, _hw_x_pcf8574

#define _hw_x_pcf8574(...)		_pcf8574,__VA_ARGS__


#define HW_INTERFACE__pcf8574		, _hw_interface_pcf8475

#define _hw_interface_pcf8475(o,twi,sla,...)				\
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
  HW_INLINE void _hw_##o##_commit ( )					\
  {									\
    _hw_##twi##_start_write_stop(sla,_hw_##o##_reg);			\
  }									\
									\
  HW_INLINE void _hw_##o##_write ( uint8_t v )				\
  {									\
    _hw_##o##_reg = v ;							\
    _hw_##twi##_start_write_stop(sla,v);				\
  }									\
									\
  HW_INLINE void _hw_##o##_write_m ( uint8_t m, uint8_t v )		\
  {									\
    _hw_##o##_reg = (_hw_##o##_reg & ~m) | v ;				\
    _hw_##twi##_start_write_stop(sla,_hw_##o##_reg);			\
  }									\
									\
  HW_INLINE void _hw_##o##_writea_np ( uint8_t n, uint8_t p, uint8_t v ) \
  {									\
    _hw_##o##_reg = (_hw_##o##_reg & ~(((1U<<n)-1)<<p)) | (v<<p) ;	\
  }									\
									\
  HW_INLINE void _hw_##o##_write_np ( uint8_t n, uint8_t p, uint8_t v ) \
  {									\
    _hw_##o##_writea_np(n,p,v) ;					\
    _hw_##o##_commit();							\
  }


#define HW_IMPLEMENT__pcf8574		, _hw_implement_pcf8574_
#define HW_IMPLEMENT_WEAK__pcf8574	, _hw_implement_pcf8574w

#define _hw_implement_pcf8574_(o,sla,twi,...)	_hw_implement_pcf8574(o,sla,twi,,__VA_ARGS__)
#define _hw_implement_pcf8574w(o,sla,twi,...)	_hw_implement_pcf8574(o,sla,twi,__attribute__((weak)),__VA_ARGS__)

#define _hw_implement_pcf8574(o,sla,twi,attr,...)		\
							\
  uint8_t attr _hw_##o##_reg ;


/**
 * @page hwa_pcf8574
 * @section pcf8574cf Configuration
 *
 * `configure`
 *
 * @code
 * hw | hwa( configure, pcf8574_0 );
 * @endcode
 */
#define hw_configure__pcf8574		, _hw_cfpcf8574
#define hwa_configure__pcf8574		, _hwa_cfpcf8574

#define _hw_cfpcf8574(o,sla,twi,...)	_hwx_cfpcf8574(o,sla,twi,__VA_ARGS__)
#define _hwa_cfpcf8574(o,sla,twi,...)	_hwx_cfpcf8574(o,sla,twi,__VA_ARGS__)
#define _hwx_cfpcf8574(o,sla,twi,...)	_hw_##o##_reg = 0xFF HW_EOL(__VA_ARGS__)


/**
 * @page hwa_pcf8574
 * @section hwa_pcf8574_actions Actions
 *
 * `write`
 * @code
 * hw( write, pcf8574_0, VALUE );
 * @endcode
 */
#define hw_write__pcf8574		, _hw_wrpcf8574
#define _hw_wrpcf8574(o,sla,twi,v,...)	_hw_##o##_write(v)

#define hw_write_m__pcf8574		, _hw_wrmpcf8574
#define _hw_wrmpcf8574(o,sla,twi,m,v,...)	_hw_##o##_write_m(m,v)

#define hw_read__pcf8574		, _hw_rdpcf8574
#define _hw_rdpcf8574(o,sla,twi,...)	_hw_##o##_read()




/*  Context
 */
/* #define hwa_begin__pcf8574	, _hwa_begin_pcf8574 */

/* #define _hwa_begin_pcf8574(o,twi,sla,...)	//uint8_t _hwa_pcf8574_##twi##_##sla##_reg = _hw_pcf8574_##twi##_##sla##_reg */

/* #define hwa_write__pcf8574	, hwa_pcf8574wr */

/* #define hwa_pcf8574wr(o,twi,sla,v,...)	_hw_pcf8574_##twi##_##sla##_reg = v */

/* #define hwa_write_m__pcf8574		, _hwa_pcf8574wrm */
/* #define _hwa_pcf8574wrm(o,twi,sla,m,v,...)				\ */
/*   _hw_pcf8574_##twi##_##sla##_reg = (_hw_pcf8574_##twi##_##sla##_reg & ~(m)) | (v) */

/* #define hwa_commit__pcf8574	, _hwa_commit_pcf8574 */

/* #define _hwa_commit_pcf8574(o,twi,sla,...)	_hw( write, o, _hw_pcf8574_##twi##_##sla##_reg ) */

#define hw_commit__pcf8574	, _hw_commit_pcf8574

/* #define _hw_commit_pcf8574(o,sla,twi,...)	_hw( write, o, _hw_##o##_reg ) */
#define _hw_commit_pcf8574(o,sla,twi,...)	_hw_##o##_commit()

//_hw( write, pcf8574_swtwimaster_pc5_0x27, _hw_pcf8574_swtwimaster_pc5_0x27_reg );


/*  IO
 */
#define hw_class__pcf8574_io

#define HW_IO__pcf8574				, _hw_io_pcf8574
#define _hw_io_pcf8574(opcf,sla,twil,bn,bp,...)	pcf8574io(opcf,bn,bp)

#define _HW_X_pcf8574io				, _hw_x_pcf8574io
#define _hw_x_pcf8574io(...)			_pcf8574_io, __VA_ARGS__

#define HW_BITS__pcf8574_io			, _hw_bits_pcf8574_io
#define _hw_bits_pcf8574_io(opcf,n,p,...)	n

#define HW_PORT_pcf8574io			, _hw_port_pcf8574io
#define _hw_port_pcf8574io(opcf,...)		_pcf8574,opcf,null,0

#define HW_PORT__pcf8574_io			, _hw_port__pcf8574_io
#define _hw_port__pcf8574_io(opcf,...)		_pcf8574,opcf,null,0



#define hw_write__pcf8574_io			, _hw_pcf8574iowr

//#define _hw_pcf8574iowr(o,pcf,bn,bp,v,...)	_hw( write_m, pcf, ((1UL<<bn)-1)<<bp, (v)<<bp )
#define _hw_pcf8574iowr(opcf,bn,bp,v,...)	_hw_##opcf##_write_m(((1UL<<bn)-1)<<bp, (v)<<bp )

#define hw_writea__pcf8574_io			, _hw_pcf8574iowra

#define _hw_pcf8574iowra(opcf,bn,bp,v,...)	_hw_##opcf##_writea_np(bn,bp,v)

#define hw_read__pcf8574_io			, _hw_pcf8574iord

/* #define _hw_pcf8574iord(o,pcf,bn,bp,v,...)	((_hw( read, pcf )>>bp) & ((1UL<<bn)-1)) */
#define _hw_pcf8574iord(opcf,bn,bp,...)	((_hw_##opcf##_read()>>bp) & ((1UL<<bn)-1))

#define hwa_write__pcf8574_io			, _hwa_pcf8574iowr

//#define _hwa_pcf8574iowr(o,pcf,bn,bp,v,...)	_hwa( write_m, pcf, ((1UL<<bn)-1)<<bp, (v)<<bp )

#define _hwa_pcf8574iowr(opcf,bn,bp,v,...)	_hw_##opcf##_writea_np(bn,bp,v)
