
/* This file is part of the HWA project.
 * Copyright (c) 2018 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

#if !defined DOXYGEN && !defined HW_DEVICE_ARCH_AVR
#  warning Class _swtwimaster may not be supported by your hardware
#endif

/**
 * @file
 * @brief Software-emulated TWI master
 */

/**
 * @ingroup swec
 * @defgroup swtwimaster Class _swtwimaster: software-emulated TWI (master only)
 *
 * This class implements a software-emulated TWI master.
 *
 * @note This may not be supported by all the devices.
 *
 * @section Implementation
 *
 * Header file:
 *
 * @code
 * #include <hwa/ext/swtwimaster.h>
 * @endcode
 *
 * <br><br>HW_SWTWIMASTER(...) declares a SWTWIMASTER object. You must provide:
 *  * an I/O for the SCL signal;
 *  * an I/O for the SDA signal;
 *  * the SCL frequency.
 *
 * @code
 * #define TWI     HW_SWTWIMASTER( scl, (portc,5),
 *                                 sda, (portc,4),
 *                                 bps, 400000 )
 * @endcode
 *
 * <br><br>HW_DECLARE( TWI ) declares the functions that implement the device. You
 * can put it in your header files:
 *
 * @code
 * HW_DECLARE( TWI );
 * @endcode
 *
 * <br><br>The implementation of this device focuses on code size rather than on
 * speed, so it relies on extern C functions that must be defined with
 * HW_IMPLEMENT(). This must appear in one of your source files:
 *
 * @code
 * HW_IMPLEMENT( TWI );
 * @endcode
 */
#define hw_class__swtwimaster

/**
 * @ingroup swtwimaster
 * @brief Constructor for SWTWIMASTER
 * @hideinitializer
 */
#define HW_SWTWIMASTER(...)			_HW_SWTWIM_(__VA_ARGS__,,,,,,,)
#define _HW_SWTWIM_(k,...)			HW_BW(_HW_SWTWIM_1,scl,k)(k,__VA_ARGS__)
#define _HW_SWTWIM_10(k,...)			_HW_SWTWIM_E(k,__VA_ARGS__)
#define _HW_SWTWIM_11(k,...)			_HW_SWTWIM_12(HW_AD(__VA_ARGS__))	/* Get SCL def */
#define _HW_SWTWIM_12(...)			_HW_SWTWIM_13(__VA_ARGS__)
#define _HW_SWTWIM_13(scl,...)			HW_B(_HW_SWTWIM_13,HW_A0 scl)(scl,__VA_ARGS__)
#define _HW_SWTWIM_131(scl,...)			,HW_SWTWIMASTER,HW_SWTWIMASTER(...): HW_A2 scl
#define _HW_SWTWIM_130(scl,k,...)		HW_BW(_HW_SWTWIM_2,sda,k)(scl,k,__VA_ARGS__)

#define _HW_SWTWIM_20(scl,k,...)		_HW_SWTWIM_E(k,__VA_ARGS__)
#define _HW_SWTWIM_21(scl,k,...)		_HW_SWTWIM_22(scl,HW_AD(__VA_ARGS__))	/* Get SDA def */
#define _HW_SWTWIM_22(...)			_HW_SWTWIM_23(__VA_ARGS__)
#define _HW_SWTWIM_23(scl,sda,...)		HW_B(_HW_SWTWIM_23,HW_A0 sda)(scl,sda,__VA_ARGS__)
#define _HW_SWTWIM_231(scl,sda,...)		,HW_SWTWIMASTER,HW_SWTWIMASTER(...): HW_A2 sda
#define _HW_SWTWIM_230(scl,sda,k,...)		HW_BW(_HW_SWTWIM_3,bps,k)(HW_A1 scl,scl,sda,k,__VA_ARGS__)

#define _HW_SWTWIM_30(sclo,scl,sda,k,...)	_HW_SWTWIM_E(k,__VA_ARGS__)
#define _HW_SWTWIM_31(sclo,scl,sda,k,bps,g,...)	HW_B(_HW_SWTWIM_4,g)(sclo,scl,sda,bps,g,__VA_ARGS__)
#define _HW_SWTWIM_40(sclo,scl,sda,bps,...)	_HW_SWTWIM_E(k,__VA_ARGS__)
#define _HW_SWTWIM_41(sclo,scl,sda,bps,...)	_swtwimaster,swtwimaster_##sclo,(-1,scl,sda,bps)

//#define _HW_SWTWIM_E(k,...)	HW_E(HW_EM_SY("HW_SWTWIM(scl,..., sda,..., bps,...)" (k,__VA_ARGS__)))
#define _HW_SWTWIM_E(...)	,HW_SWTWIMASTER(),HW_EM_SY("HW_SWTWIMASTER(scl,..., sda,..., bps,...)")


/**
 * @ingroup swtwimaster
 * @brief Declare the functions that implement the class.
 * @hideinitializer
 */
#define HW_DECLARE__swtwimaster		, _hw_dcswtwimaster

#define _hw_dcswtwimaster(o,a,...)	HW_BV(_hw_dcswtwimaster,declare_,HW_A0(__VA_ARGS__),o)
#define _hw_dcswtwimaster0(v,...)	HW_E(HW_EM_OVL(v,(weak)))
#define _hw_dcswtwimaster1(weak,o)				\
								\
  extern uint8_t _hw_##o##__sr ;				\
								\
  void  weak _hw_##o##__delay ( );				\
  void  weak _hw_##o##_start ( );				\
  void  weak _hw_##o##_slar ( uint8_t );			\
  void  weak _hw_##o##_slaw ( uint8_t );			\
  uint8_t  weak _hw_##o##_write ( uint8_t );			\
  uint8_t  weak _hw_##o##_write ( uint8_t );			\
  void  weak _hw_##o##_stop ( );				\
  uint8_t  weak _hw_##o##_start_read_stop ( uint8_t );		\
  void  weak _hw_##o##_start_write_stop ( uint8_t, uint8_t )


/**
 * @ingroup swtwimaster
 * @brief Define the functions that implement the class.
 * @hideinitializer
 */
#define HW_IMPLEMENT__swtwimaster		, _hw_dfswtwimaster

#define _hw_dfswtwimaster(o,a,scl,sda,bps,...)				\
									\
  extern void _hw_##o##__delay ( ) ;					\
									\
  uint8_t _hw_##o##__sr ;						\
									\
  void _hw_##o##__delay ( ) {						\
    hw_waste_cycles( HW_SYSHZ / (2*bps) - 8 /* CALL+RET */);		\
  }									\
									\
  void _hw_##o##_start ( ) {						\
    /* SDA goes low while SCL is high */				\
    _hw( configure, sda, mode, digital_output );			\
    _hw_##o##__delay();							\
    _hw( configure, scl, mode, digital_output );			\
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
    uint8_t ack = _hw_##o##_write( (sla<<1) + 0 );			\
    if ( ack == 0 )							\
      _hw_##o##__sr = 0x18 ; /* HW_TWI_MT_SLA_ACK */			\
    else								\
      _hw_##o##__sr = 0x20 ; /* HW_TWI_MT_SLA_NACK */			\
  }									\
									\
  uint8_t _hw_##o##_write ( uint8_t byte ) {				\
    /* SDA can change while SCL is low */				\
    for ( uint8_t bit=0x80 ; bit ; bit>>=1 ) {				\
      if ( (byte & bit) == 0 )						\
	_hw( configure, sda, mode, digital_output );		\
      else {								\
	_hw( configure, sda, mode, digital_input );		\
	while ( !hw(read, sda) ) {}				\
      }									\
      _hw( configure, scl, mode, digital_input );			\
      while ( !hw(read, scl) ) {} /* The slave can extend the SCL low period */ \
      _hw_##o##__delay();						\
      _hw( configure, scl, mode, digital_output ) ;		\
    }									\
    _hw( configure, sda, mode, digital_input );			\
    _hw( configure, scl, mode, digital_input );			\
    while ( !hw(read, scl) ) {} /* The slave can extend the SCL low period */ \
    _hw_##o##__delay();							\
    byte = hw(read, sda);						\
    _hw( configure, scl, mode, digital_output ) ;			\
    return byte ;							\
  }									\
  									\
  uint8_t _hw_##o##__read ( ) {						\
    /* SDA can change while SCL is low */				\
    uint8_t data = 0 ;							\
    for ( uint8_t bit=0x80 ; bit ; bit>>=1 ) {				\
      _hw( configure, scl, mode, digital_input );			\
      while ( !hw(read, scl) ) {} /* The slave can extend the SCL low period */ \
      _hw_##o##__delay();						\
      if ( hw(read, sda) != 0 )					\
	data |= bit ;							\
      _hw( configure, scl, mode, digital_output ) ;		\
      _hw_##o##__delay();						\
    }									\
    return data ;							\
  }									\
									\
  uint8_t _hw_##o##_read_ack ( ) {					\
    uint8_t data = _hw_##o##__read();					\
    _hw( configure, sda, mode, digital_output ) ;			\
    _hw( configure, scl, mode, digital_input );			\
    _hw_##o##__delay();							\
    while ( !hw(read, scl) ) {} /* The slave can extend the SCL low period */ \
    _hw( configure, scl, mode, digital_output ) ;			\
    _hw_##o##__delay();							\
    return data ;							\
  }									\
									\
  uint8_t _hw_##o##_read_nack ( ) {					\
    uint8_t data = _hw_##o##__read();					\
    _hw( configure, scl, mode, digital_input );				\
    _hw_##o##__delay();							\
    while ( !hw(read, scl) ) {} /* The slave can extend the SCL low period */ \
    _hw( configure, scl, mode, digital_output ) ;			\
    _hw( configure, sda, mode, digital_output ) ;			\
    _hw_##o##__delay();							\
    return data ;							\
  }									\
									\
  void _hw_##o##_stop ( ) {						\
    /* SDA goes high while SCL is high */				\
    if ( hw(read, sda) )						\
      _hw( configure, sda, mode, digital_output ) ;		\
    _hw( configure, scl, mode, digital_input );			\
    _hw_##o##__delay();							\
    _hw( configure, sda, mode, digital_input );			\
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
  }									\
									\
  extern void hw_foo()


/**
 * @addtogroup swtwimaster
 * @section swtwimasteract Actions
 *
 * <br><br>hw( configure, TWI ) and hwa( configure, TWI ) configure the object:
 *
 * @code
 * hw( configure, TWI );
 * @endcode
 *
 * @code
 * hwa( configure, TWI );
 * @endcode
 */
#define hw_configure__swtwimaster	, _hw_cfswtwimaster

/*  SCL and SDA are set to 0 and then configured as digital_input /
 *  digital_output. External pullup resistors are required.
 */
#define _hw_cfswtwimaster(o,a,scl,sda,bps,...)			\
  do{								\
    _hwa_begin_(,);						\
    _hwa( configure, scl, mode, digital_input_floating );	\
    _hwa( configure, sda, mode, digital_input_floating );	\
    _hwa( write, scl, 0 );				\
    _hwa( write, sda, 0 );				\
    _hwa_commit_(,);					\
  }while(0)


#define hwa_configure__swtwimaster	, _hwa_cfswtwimaster

#define _hwa_cfswtwimaster(o,a,scl,sda,bps,...)			\
  do{								\
    _hwa( configure, scl, mode, digital_input_floating );	\
    _hwa( configure, sda, mode, digital_input_floating );	\
    _hwa( write, scl, 0 );				\
    _hwa( write, sda, 0 );				\
  }while(0)


/**
 * @addtogroup swtwimaster
 *
 * <br><br>hw( xfr_start, TWI ) sends a start condition on the TWI bus:
 *
 * @code
 * hw( xfr_start, TWI );
 * @endcode
 *
 * <br><br>hw( xfr_slar, TWI, slave_address ) sends slave address + read bit:
 *
 * @code
 * hw( xfr_slar, TWI, slave_address );
 * @endcode
 *
 * <br><br>hw( xfr_slaw, TWI, slave_address ) sends slave address + write bit:
 *
 * @code
 * hw( xfr_slaw, TWI, slave_address );
 * @endcode
 *
 * <br><br>hw( xfr_read, TWI, data, ack|nack ) receive one data byte:
 *
 * @code
 * uint8_t r = hw( xfr_read, TWI, ack );
 * @endcode
 *
 * <br><br>hw( xfr_write, TWI, data ) transmit one data byte:
 *
 * @code
 * uint8_t r = hw( xfr_write, TWI, data ); // r = ack|nack
 * @endcode
 *
 * <br><br>hw( xfr_stop, TWI ) sends a start condition on the TWI bus:
 *
 * @code
 * hw( xfr_stop, TWI );
 * @endcode
 *
 * <br><br>hw( stat, TWI ) get the status byte of the object:
 *
 * @code
 * uint8_t st = hw( stat, TWI );
 * @endcode
 */
/**
 * @todo Implement hw_stat_t() and (_swtwimaster,state). Flags:
 *  * mr_sla_ack
 *  * mr_sla_nack
 *  * ...
 */
#define hw_xfr_start__swtwimaster			, _hw_swtwimaster_start
#define _hw_swtwimaster_start(o,a,scl,sda,bps,...)	_hw_##o##_start() HW_EOL(__VA_ARGS__)

#define hw_xfr_slar__swtwimaster			, _hw_swtwimaster_slar
#define _hw_swtwimaster_slar(o,a,scl,sda,bps,sla,...)	_hw_##o##_slar(sla) HW_EOL(__VA_ARGS__)

#define hw_xfr_slaw__swtwimaster			, _hw_swtwimaster_slaw
#define _hw_swtwimaster_slaw(o,a,scl,sda,bps,sla,...)	_hw_##o##_slaw(sla) HW_EOL(__VA_ARGS__)

#define hw_xfr_read__swtwimaster			, _hw_swtwimasterrd
#define _hw_swtwimasterrd(o,a,k,...)			HW_BW(_hw_swtwimasterrdack,ack,k)(o,k,__VA_ARGS__,,)
#define _hw_swtwimasterrdack1(o,k,...)			_hw_##o##_read_ack() HW_EOL(__VA_ARGS__)
#define _hw_swtwimasterrdack0(o,k,...)			HW_BW(_hw_swtwimasterrdnack,nack,k)(o,k,__VA_ARGS__)
#define _hw_swtwimasterrdnack1(o,ok,k,...)		_hw_##o##_read_nack() HW_EOL(__VA_ARGS__)
#define _hw_swtwimasterrdnack0(o,k,...)			HW_E(HW_EM_XNIL(k,(ack,nack)))

#define hw_xfr_write__swtwimaster			, _hw_swtwimaster_write
#define _hw_swtwimaster_write(o,a,scl,sda,bps,data,...)	_hw_##o##_write(data) HW_EOL(__VA_ARGS__)

#define hw_xfr_stop__swtwimaster			, _hw_swtwimaster_stop
#define _hw_swtwimaster_stop(o,a,scl,sda,bps,...)		_hw_##o##_stop() HW_EOL(__VA_ARGS__)

#define hw_stat__swtwimaster				, _hw_swtwimaster_stat
#define _hw_swtwimaster_stat(o,a,scl,sda,bps,...)	_hw_##o##__sr HW_EOL(__VA_ARGS__)

