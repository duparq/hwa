
/* This file is part of the HWA project.
 * Copyright (c) 2018 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief SWTWIMASTER
 */

/**
 * @page hwa_swtwimaster Class _swtwimaster
 *
 * Definition:
 *
 * @code
 * #define TWI     HW_SWTWIMASTER( scl, HW_IO(port0, 1, 2),
 *                                 sda, HW_IO(port0, 1, 3),
 *                                 bps, 100000 )
 * @endcode
 */

#define hw_class__swtwimaster


#define HW_SWTWIMASTER(...)				_HW_SWTWIMASTER_01(__VA_ARGS__,,,,,,,)
#define _HW_SWTWIMASTER_01(kscl,vscl,ksda,vsda,kbps,vbps,eol,...)	\
  HW_Y(_HW_SWTWIMASTER_01_,_hw_is_sclsdabps_##kscl##ksda##kbps##eol)(kscl,vscl,ksda,vsda,kbps,vbps)
#define _HW_SWTWIMASTER_01_0(...)					\
  ,HW_SWTWIMASTER(...),"HW_SWTWIMASTER(...)" must be defined as "HW_SWTWIMASTER(scl,HW_IO(...),sda,HW_IO(...),bps,..."
#define _HW_SWTWIMASTER_01_1(kscl,vscl,ksda,vsda,kbps,vbps)	_HW_SWTWIMASTER_02((HW_X(vscl)),(HW_X(vsda)),vbps)
#define _HW_SWTWIMASTER_02(...)					_HW_SWTWIMASTER_03(__VA_ARGS__)
#define _HW_SWTWIMASTER_03(scl,sda,bps)				_HW_SWTWIMASTER_04(HW_A1 scl, scl,sda,bps)
#define _HW_SWTWIMASTER_04(...)					_HW_SWTWIMASTER_05(__VA_ARGS__)
#define _HW_SWTWIMASTER_05(p,...)		swtwimaster(swtwimaster_##p,__VA_ARGS__)


#define _HW_X_swtwimaster		, _hw_swtwimaster
#define _hw_swtwimaster(o,scl,sda,bps)	_swtwimaster,o,bps,scl,sda // Put bps in 3rd so that scl is not unbracketed by HW_X()

#define _hw_is_sclsdabps_sclsdabps	, 1
#define _hw_isa_gpio__p8a_io		, 1

/* #define _hw_swtwimaster(...)					\ */
/*   _hw_swtwimaster_01(HW_SWTWIMASTER(__VA_ARGS__),__VA_ARGS__,,,,,,,) */
/* #define _hw_swtwimaster_01(o,kscl,vscl,ksda,vsda,kbps,vbps,eol,...)	\ */
/*   HW_Y0(_hw_swtwimaster_01_,_hw_is_sclsdabps_##kscl##ksda##kbps##eol)	\ */
/*   (o,kscl,vscl,ksda,vsda,kbps,vbps) */
/* #define _hw_swtwimaster_01_0(o,...)		,o,HW_EM(HW_Q(o) must be defined as "HW_SWTWIMASTER(scl,HW_IO(...),sda,HW_IO(...),bps,...") */
/* /\* #define _hw_swtwimaster_01_1(o,kscl,vscl,ksda,vsda,kbps,vbps)	_swtwimaster,o,vscl,vsda,vbps *\/ */
/* #define _hw_swtwimaster_01_1(o,kscl,vscl,ksda,vsda,kbps,vbps)	_swtwimaster,HW_G2(swtwimaster,HW_A1(HW_X(vscl))),vscl,vsda,vbps */


/**
 * @page atmelavr_swtwimaster
 * @section swtwimastercf Configuration
 *
 * `configure`
 *
 * @code
 * hw( configure, swtwi );
 * @endcode
 *
 * @code
 * hwa( configure, swtwi );
 * @endcode
 */
#define hw_configure__swtwimaster	, _hw_cfswtwimaster

/*  SCL and SDA are set to 0 and then configured as digital_input_floating /
 *  digital_output. External pullup resistors are required.
 */
#define _hw_cfswtwimaster(o,bps,scl,sda,...)			\
  do{								\
    hwa_begin();						\
    _hwa( configure, HW_XB scl, mode, digital_input_floating );	\
    _hwa( configure, HW_XB sda, mode, digital_input_floating );	\
    _hwa( write, HW_XB scl, 0 );				\
    _hwa( write, HW_XB sda, 0 );				\
    hwa_commit();						\
  }while(0)


#define hwa_configure__swtwimaster	, _hwa_cfswtwimaster

#define _hwa_cfswtwimaster(o,bps,scl,sda,...)			\
  do{								\
    _hwa( configure, HW_XB scl, mode, digital_input_floating );	\
    _hwa( configure, HW_XB sda, mode, digital_input_floating );	\
    _hwa( write, HW_XB scl, 0 );				\
    _hwa( write, HW_XB sda, 0 );				\
  }while(0)


/*  Create a unique prefix for the required functions based on the pin used as
 *  scl.
 */
/* #define HW_THIS__swtwimaster			, _hw_swtwimaster_this */

/* #define _hw_swtwimaster_this(o,scl,...)		_hw_swtwimaster_this01(HW_X(scl)) */
/* #define _hw_swtwimaster_this01(...)		_hw_swtwimaster_this02(__VA_ARGS__) */
/* #define _hw_swtwimaster_this02(c,o,i,p,bn,bp)	swtwimaster_##p##_pin##bp */


#define HW_INTERFACE__swtwimaster		, _hw_interface_swtwimaster

#define _hw_interface_swtwimaster(o,bps,scl,sda,...)	\
							\
  extern uint8_t _hw_##o##__sr ;			\
							\
  void _hw_##o##__delay ( );				\
  void _hw_##o##_start ( );				\
  void _hw_##o##_slar ( uint8_t );			\
  void _hw_##o##_slaw ( uint8_t );			\
  uint8_t _hw_##o##_write ( uint8_t );			\
  uint8_t _hw_##o##_write ( uint8_t );			\
  void _hw_##o##_stop ( );				\
  uint8_t _hw_##o##_start_read_stop ( uint8_t );	\
  void _hw_##o##_start_write_stop ( uint8_t, uint8_t );


#define HW_IMPLEMENT__swtwimaster		, _hw_implement_swtwimaster

#define _hw_implement_swtwimaster(o,bps,scl,sda,...)			\
									\
  uint8_t _hw_##o##__sr ;						\
									\
  void _hw_##o##__delay ( ) {						\
    hw_waste_cycles( HW_SYSHZ / (2*bps) - 8 );				\
  }									\
									\
  void _hw_##o##_start ( ) {						\
    /* SDA goes low while SCL is high */				\
    _hw( configure, HW_XB sda, mode, digital_output );			\
    _hw_##o##__delay();							\
    _hw( configure, HW_XB scl, mode, digital_output );			\
  }									\
									\
  void _hw_##o##_slar ( uint8_t sla ) {					\
    uint8_t ack = _hw_##o##_write( (sla<<1) + 1 );			\
    if ( ack == 0 )							\
      _hw_##o##__sr = 0x40 ; /* HW_TWI_MR_SLA_ACK */			\
    else								\
      _hw_##o##__sr = 0x48 ; /* HW_TWI_MR_SLA_NACK */			\
  }									\
									\
  void _hw_##o##_slaw ( uint8_t sla ) {					\
    uint8_t ack = _hw_##o##_write( sla<<1 );				\
    if ( ack == 0 )							\
      _hw_##o##__sr = 0x18 ; /* HW_TWI_MT_SLA_ACK */			\
    else								\
      _hw_##o##__sr = 0x20 ; /* HW_TWI_MT_SLA_NACK */			\
  }									\
									\
  uint8_t _hw_##o##__read ( ) {						\
    /* SDA can change while SCL is low */				\
    uint8_t data = 0 ;							\
    _hw( configure, HW_XB sda, mode, digital_input_floating );		\
    for ( uint8_t bit=0x80 ; bit ; bit>>=1 ) {				\
      _hw( configure, HW_XB scl, mode, digital_input_floating );	\
      _hw_##o##__delay();						\
      while ( !hw(read, HW_XB scl) ) {} /* The slave can extend the SCL low period */ \
      if ( hw(read, HW_XB sda) == 0 )					\
	data |= bit ;							\
      _hw( configure, HW_XB scl, mode, digital_output ) ;		\
      _hw_##o##__delay();						\
    }									\
    return data ;							\
  }									\
									\
  uint8_t _hw_##o##_read_nack ( ) {					\
    uint8_t data = _hw_##o##__read();					\
    _hw( configure, HW_XB scl, mode, digital_input_floating );		\
    _hw_##o##__delay();							\
    while ( !hw(read, HW_XB scl) ) {} /* The slave can extend the SCL low period */ \
    _hw( configure, HW_XB scl, mode, digital_output ) ;			\
    _hw( configure, HW_XB sda, mode, digital_output ) ;			\
    _hw_##o##__delay();							\
    return data ;							\
  }									\
									\
  uint8_t _hw_##o##_read_ack ( ) {					\
    uint8_t data = _hw_##o##__read();					\
    _hw( configure, HW_XB sda, mode, digital_output ) ;			\
    _hw( configure, HW_XB scl, mode, digital_input_floating );		\
    _hw_##o##__delay();							\
    while ( !hw(read, HW_XB scl) ) {} /* The slave can extend the SCL low period */ \
    _hw( configure, HW_XB scl, mode, digital_output ) ;			\
    _hw_##o##__delay();							\
    return data ;							\
  }									\
									\
  uint8_t _hw_##o##_write ( uint8_t byte ) {				\
    /* SDA can change while SCL is low */				\
    for ( uint8_t bit=0x80 ; bit ; bit>>=1 ) {				\
      if ( (byte & bit) == 0 )						\
	_hw( configure, HW_XB sda, mode, digital_output );		\
      else								\
	_hw( configure, HW_XB sda, mode, digital_input_floating );	\
      _hw_##o##__delay();						\
      _hw( configure, HW_XB scl, mode, digital_input_floating );	\
      _hw_##o##__delay();						\
      while ( !hw(read, HW_XB scl) ) {} /* The slave can extend the SCL low period */ \
      _hw( configure, HW_XB scl, mode, digital_output ) ;		\
    }									\
    _hw( configure, HW_XB sda, mode, digital_input_floating );		\
    _hw_##o##__delay();							\
    _hw( configure, HW_XB scl, mode, digital_input_floating );		\
    _hw_##o##__delay();							\
    while ( !hw(read, HW_XB scl) ) {} /* The slave can extend the SCL low period */ \
    byte = hw(read, HW_XB sda);						\
    _hw( configure, HW_XB scl, mode, digital_output ) ;			\
    _hw( configure, HW_XB sda, mode, digital_output ) ;			\
    _hw_##o##__delay();							\
    return byte ;							\
  }									\
									\
  void _hw_##o##_stop ( ) {						\
    /* SDA goes high while SCL is high */				\
    _hw( configure, HW_XB scl, mode, digital_input_floating );		\
    _hw_##o##__delay();							\
    _hw( configure, HW_XB sda, mode, digital_input_floating );		\
  }									\
									\
  void _hw_##o##_start_write_stop ( uint8_t sla, uint8_t v )		\
  {									\
    _hw_##o##_start();							\
    _hw_##o##_slaw(sla);						\
    _hw_##o##_write(v);							\
    _hw_##o##_stop();							\
  }									\
									\
  uint8_t _hw_##o##_start_read_stop ( uint8_t sla )			\
  {									\
    _hw_##o##_start();							\
    _hw_##o##_slar(sla);						\
    uint8_t v = _hw_##o##_read_nack();					\
    _hw_##o##_stop();							\
    return v;								\
  }



/**
 * @page atmelavr_swtwimaster
 * @section swtwimastercf Bus operations
 *
 * @code
 * hw( bus_start, swtwi0 );
 * @endcode
 * <br>
 */
#define hw_bus_start__swtwimaster	, _hw_swtwimaster_start
#define hw_bus_slaw__swtwimaster	, _hw_swtwimaster_slaw
#define hw_bus_write__swtwimaster	, _hw_swtwimaster_write
#define hw_bus_stop__swtwimaster	, _hw_swtwimaster_stop
#define hw_stat__swtwimaster		, _hw_swtwimaster_stat

#define _hw_swtwimaster_start(o,bps,scl,sda,...)	_hw_##o##_start() HW_EOL(__VA_ARGS__)
#define _hw_swtwimaster_slaw(o,bps,scl,sda,sla,...)	_hw_##o##_slaw(sla) HW_EOL(__VA_ARGS__)
#define _hw_swtwimaster_write(o,bps,scl,sda,data,...)	_hw_##o##_write(data) HW_EOL(__VA_ARGS__)
#define _hw_swtwimaster_stop(o,bps,scl,sda,...)		_hw_##o##_stop() HW_EOL(__VA_ARGS__)
#define _hw_swtwimaster_stat(o,bps,scl,sda,...)		_hw_##o##__sr HW_EOL(__VA_ARGS__)
