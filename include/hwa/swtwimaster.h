
/* This file is part of the HWA project.
 * Copyright (c) 2018 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief SWTWIMASTER: Software-emulated TWI master
 * @page swtwimaster SWTWIMASTER: Software-emulated TWI master
 *
 * This is a software-emulated TWI master. As this kind of interface is not
 * speed critical, the implementation focuses on code size rather than on speed,
 * so it relies on extern C functions rather than on inlined code.
 *
 * __Constructor__
 *
 * Two GPIO lines named `scl` and `sda` and the `bps` rate must be defined:
 *
 * @code
 * #define TWI     HW_SWTWIMASTER( scl, pc5,
 *                                 sda, pc4,
 *                                 bps, 400000 )
 * @endcode
 *
 * @code
 * #define TWI     HW_SWTWIMASTER( scl, HW_IO(port0, 1, 2),
 *                                 sda, HW_IO(port0, 1, 3),
 *                                 bps, 100000 )
 * @endcode
 */
#define hw_class__swtwimaster

#define HW_SWTWIMASTER(...)			_HW_SWTWIM_(__VA_ARGS__,,,,,,,)
#define _HW_SWTWIM_(k,...)			HW_KW(_HW_SWTWIM_1,scl,k)(k,__VA_ARGS__)
#define _HW_SWTWIM_10(k,...)			_HW_SWTWIM_E(k,__VA_ARGS__)
#define _HW_SWTWIM_11(k,...)			_HW_SWTWIM_12(HW_AD(__VA_ARGS__))	/* Get SCL def */
#define _HW_SWTWIM_12(...)			_HW_SWTWIM_13(__VA_ARGS__)
#define _HW_SWTWIM_13(scl,k,...)		HW_KW(_HW_SWTWIM_2,sda,k)(scl,k,__VA_ARGS__)
#define _HW_SWTWIM_20(scl,k,...)		_HW_SWTWIM_E(k,__VA_ARGS__)
#define _HW_SWTWIM_21(scl,k,...)		_HW_SWTWIM_22(scl,HW_AD(__VA_ARGS__))	/* Get SDA def */
#define _HW_SWTWIM_22(...)			_HW_SWTWIM_23(__VA_ARGS__)
#define _HW_SWTWIM_23(scl,sda,k,...)		HW_KW(_HW_SWTWIM_3,bps,k)(HW_A1 scl,scl,sda,k,__VA_ARGS__)
#define _HW_SWTWIM_30(sclo,scl,sda,k,...)		_HW_SWTWIM_E(k,__VA_ARGS__)
#define _HW_SWTWIM_31(sclo,scl,sda,k,bps,g,...)	HW_Y0(_HW_SWTWIM_4,g)(sclo,scl,sda,bps,g,__VA_ARGS__)
#define _HW_SWTWIM_40(sclo,scl,sda,bps,g,...)	HW_E(HW_EM_G(g))
#define _HW_SWTWIM_41(sclo,scl,sda,bps,...)	_swtwimaster,swtwimaster_##sclo,(scl,sda,bps)

#define _HW_SWTWIM_E(k,...)	HW_E(HW_EM_S("HW_SWTWIM(scl,..., sda,..., bps,...)" (k,__VA_ARGS__)))


/**
 * @page swtwimaster
 * __Interface__
 *
 * The following makes the implementation functions for TWI declared. Use it in
 * your header files:
 *
 * @code
 * HW_DECLARE(TWI);
 * @endcode
 */
#define HW_DECLARE__swtwimaster		, _hw_dcswtwimaster

#define _hw_dcswtwimaster(o,...)			\
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
  void _hw_##o##_start_write_stop ( uint8_t, uint8_t )


/**
 * @page swtwimaster
 * __Implement__
 *
 * The following makes the implementation functions for TWI defined. It must
 * appear in one of your source files:
 *
 * @code
 * HW_DEFINE(TWI);
 * @endcode
 */
#define HW_DEFINE__swtwimaster		, _hw_dfswtwimaster

#define _hw_dfswtwimaster(o,scl,sda,bps,...)				\
									\
  extern void _hw_##o##__delay ( ) ;					\
									\
  uint8_t _hw_##o##__sr ;						\
									\
  void _hw_##o##__delay ( ) {						\
    hw_waste_cycles( HW_SYSHZ / (2*bps) - 8 );				\
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
  uint8_t _hw_##o##_read_nack ( ) {					\
    uint8_t data = _hw_##o##__read();					\
    _hw( configure, scl, mode, digital_input );			\
    _hw_##o##__delay();							\
    while ( !hw(read, scl) ) {} /* The slave can extend the SCL low period */ \
    _hw( configure, scl, mode, digital_output ) ;			\
    _hw( configure, sda, mode, digital_output ) ;			\
    _hw_##o##__delay();							\
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
  extern void _hw_() /* for semicolon */


/**
 * @page swtwimaster
 *
 * `configure`
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
#define _hw_cfswtwimaster(o,scl,sda,bps,...)			\
  do{								\
    _hwa_begin_(,);						\
    _hwa( configure, scl, mode, digital_input_floating );	\
    _hwa( configure, sda, mode, digital_input_floating );	\
    _hwa( write, scl, 0 );				\
    _hwa( write, sda, 0 );				\
    _hwa_commit_(,);					\
  }while(0)


#define hwa_configure__swtwimaster	, _hwa_cfswtwimaster

#define _hwa_cfswtwimaster(o,scl,sda,bps,...)			\
  do{								\
    _hwa( configure, scl, mode, digital_input_floating );	\
    _hwa( configure, sda, mode, digital_input_floating );	\
    _hwa( write, scl, 0 );				\
    _hwa( write, sda, 0 );				\
  }while(0)


/**
 * @page swtwimaster
 *
 * `Bus actions`
 *
 * @code
 * hw( bus_start, TWI );        // Send a start condition on the bus
 * @endcode
 *
 * @code
 * hw( bus_slaw, TWI, sla );    // Send slave address + write bit
 * @endcode
 *
 * @code
 * hw( bus_write, TWI, data );  // Send one data byte to the slave
 * @endcode
 *
 * @code
 * hw( bus_stop, TWI );         // Send a stop condition on the bus
 * @endcode
 *
 * @code
 * hw( bus_stat, TWI );         // Get the status
 * @endcode
 */
#define hw_bus_start__swtwimaster	, _hw_swtwimaster_start
#define hw_bus_slaw__swtwimaster	, _hw_swtwimaster_slaw
#define hw_bus_write__swtwimaster	, _hw_swtwimaster_write
#define hw_bus_stop__swtwimaster	, _hw_swtwimaster_stop
#define hw_stat__swtwimaster		, _hw_swtwimaster_stat

#define _hw_swtwimaster_start(o,scl,sda,bps,...)	_hw_##o##_start() HW_EOL(__VA_ARGS__)
#define _hw_swtwimaster_slaw(o,scl,sda,bps,sla,...)	_hw_##o##_slaw(sla) HW_EOL(__VA_ARGS__)
#define _hw_swtwimaster_write(o,scl,sda,bps,data,...)	_hw_##o##_write(data) HW_EOL(__VA_ARGS__)
#define _hw_swtwimaster_stop(o,scl,sda,bps,...)		_hw_##o##_stop() HW_EOL(__VA_ARGS__)
#define _hw_swtwimaster_stat(o,scl,sda,bps,...)		_hw_##o##__sr HW_EOL(__VA_ARGS__)
