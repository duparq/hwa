
/* This file is part of the HWA project.
 * Copyright (c) 2018 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief PCF8574 8-bit I/O expander for I²C bus
 */

/**
 * @ingroup ext
 * @defgroup pcf8574 PCF8574 8-bit I/O expander for I²C bus
 *
 * This class implements a PCF8574 8-bit I/O expander for I²C bus.
 *
 * Header file:
 *
 * @code
 * #include <hwa/ext/pcf8574.h>
 * @endcode
 */

/**
 * @addtogroup pcf8574
 * @section pcf8574rel Relatives
 *
 *   * @ref iopcf8574 "(PCF,p)": the single pin of the PCF at position p (0 to 7);
 *   * @ref iopcf8574 "(PCF,n,p)": n consecutive pins of the PCF starting at position p.
 */

/**
 * @addtogroup pcf8574
 * @section pcf8574_if Interface
 *
 * * define a PCF8574 device
 *
 *   You must provide:
 *
 *   * the name of the TWI interface the object is connected to;
 *   * the slave address of the object.
 *
 *   <br>Example:
 *
 *   @code
 *   #define PCF          HW_PCF8574( interface, twi0, address, 0x27 )
 *   @endcode
 *
 *   The implementation of this device focuses on code size rather than on
 *   speed, so it relies on extern C functions. These functions are declared
 *   with HW_DECLARE(...) and defined with HW_IMPLEMENT(...):
 *
 *   @code
 *   HW_DECLARE( PCF );		// Declare the functions that implement the device
 *   @endcode
 *
 *   @code
 *   HW_IMPLEMENT( PCF );	// Define the functions that implement the device
 *   @endcode
 */
#define hw_class__pcf8574

/**
 * @addtogroup pcf8574
 * @hideinitializer
 *
 * Constructor for PCF8574
 */
#define HW_PCF8574(...)			_HW_PCF8574_(__VA_ARGS__,,,,,)
#define _HW_PCF8574_(k,...)		HW_BW(_HW_PCF8574_1_,interface,k)(k,__VA_ARGS__)
#define _HW_PCF8574_1_0(...)		_HW_PCF8574_E
#define _HW_PCF8574_1_1(k,...)		_HW_PCF8574_1_2(HW_ANAME(__VA_ARGS__))
#define _HW_PCF8574_1_2(...)		_HW_PCF8574_1_3(__VA_ARGS__)
#define _HW_PCF8574_1_3(twi,k,...)	HW_BW(_HW_PCF8574_2_,address,k)(twi,k,__VA_ARGS__)
#define _HW_PCF8574_2_0(...)		_HW_PCF8574_E
#define _HW_PCF8574_2_1(twi,k,sla,...)	_pcf8574,pcf8574_##twi##_##sla,(twi,sla) HW_EOL(__VA_ARGS__)

#define _HW_PCF8574_E			HW_E(HW_EM_SY("HW_PCF8574(interface,..., address,...)"))


#define HW_DECLARE__pcf8574		, _hw_dcpcf8574

#define _hw_dcpcf8574(o,twi,sla,...)	HW_BV(_hw_dcpcf8574,declare_,HW_A0(__VA_ARGS__),o,twi,sla)
#define _hw_dcpcf85740(v,...)		HW_E(HW_EM_OVL(v,(weak)))
#define _hw_dcpcf85741(weak,o,twi,sla)					\
  									\
  extern uint8_t _hw_##o##_reg ;					\
									\
  HW_INLINE weak uint8_t _hw_##o##_read ( )				\
  {									\
    return _hw_##twi##_start_read_stop(sla);				\
  }									\
									\
  HW_INLINE weak uint8_t _hw_##o##_read_np ( uint8_t n, uint8_t p )	\
  {									\
    if ( (p+n)>8 ) HWA_E(HW_EM(o can not access bits outside 0..7));	\
    return (_hw_##twi##_start_read_stop(sla)>>p) & ((1U<<n)-1);		\
  }									\
									\
  HW_INLINE weak void _hw_##o##_writea_np ( uint8_t n, uint8_t p, uint8_t v ) \
  {									\
    if ( (p+n)>8 ) HWA_E(HW_EM(o can not access bits outside 0..7));	\
    _hw_##o##_reg = (_hw_##o##_reg & ~(((1U<<n)-1)<<p)) | (v<<p) ;	\
  }									\
									\
  HW_INLINE weak void _hw_##o##_togglea_np ( uint8_t n, uint8_t p )	\
  {									\
    if ( (p+n)>8 ) HWA_E(HW_EM(o can not access bits outside 0..7));	\
    _hw_##o##_reg = _hw_##o##_reg ^ (((1U<<n)-1)<<p) ;			\
  }									\
									\
  HW_INLINE weak void _hw_##o##_commit ( )				\
  {									\
    _hw_##twi##_start_write_stop(sla,_hw_##o##_reg);			\
  }									\
									\
  HW_INLINE weak void _hw_##o##_write ( uint8_t v )			\
  {									\
    _hw_##o##_reg = v ;							\
    _hw_##o##_commit();							\
  }									\
									\
  HW_INLINE weak void _hw_##o##_write_np ( uint8_t n, uint8_t p, uint8_t v ) \
  {									\
    _hw_##o##_writea_np(n,p,v) ;					\
    _hw_##o##_commit();							\
  }									\
									\
  HW_INLINE weak void _hw_##o##_toggle_np ( uint8_t n, uint8_t p )	\
  {									\
    _hw_##o##_togglea_np(n,p) ;						\
    _hw_##o##_commit();							\
  }									\
									\
  extern void hw_foo()


#define HW_IMPLEMENT__pcf8574		, _hw_define_pcf8574_

#define _hw_define_pcf8574_(o,sla,twi,...)	_hw_define_pcf8574(o,sla,twi,,__VA_ARGS__)
#define _hw_define_pcf8574w(o,sla,twi,...)	_hw_define_pcf8574(o,sla,twi,__attribute__((weak)),__VA_ARGS__)
#define _hw_define_pcf8574(o,sla,twi,attr,...)	uint8_t attr _hw_##o##_reg


/**
 * @ingroup pcf8574
 * @defgroup iopcf8574 PCF8574 I/O
 *
 * @section iopcf8574_if Interface
 *
 * * get the state of one single pin:
 *
 *   @code
 *   hw( read, (PCF,2) );		// Get bit #2
 *   @endcode
 *
 * * set the state of one single pin:
 *
 *   @code
 *   hw( write, (PCF,2), 0 );		// Clear bit #2
 *   @endcode
 *
 * * set the state of multiple pins:
 *
 *   @code
 *   hw( write, (PCF,4,2), 12 );	// Set bits #5 and #4, clear bits #3 and #2
 *   @endcode
 */


/**
 * @addtogroup pcf8574
 *
 * * configure the device:
 *
 *   @code
 *   hw|hwa( configure, PCF );
 *   @endcode
 */
#define hw_configure__pcf8574		, _hw_cfpcf8574
#define hwa_configure__pcf8574		, _hwa_cfpcf8574

#define _hw_cfpcf8574(o,sla,twi,...)	_hwx_cfpcf8574(o,sla,twi,__VA_ARGS__)
#define _hwa_cfpcf8574(o,sla,twi,...)	_hwx_cfpcf8574(o,sla,twi,__VA_ARGS__)
#define _hwx_cfpcf8574(o,sla,twi,...)	_hw_##o##_reg = 0xFF HW_EOL(__VA_ARGS__)


/**
 * @addtogroup pcf8574
 *
 * * get the state of output pins:
 *
 *   @code
 *   hw( read, PCF );
 *   @endcode
 *
 * * set the state of output pins:
 *
 *   @code
 *   hw( write, PCF, value );
 *   @endcode
 */
#define hw_read__pcf8574			, _hw_rdpcf8574
#define _hw_rdpcf8574(o,sla,twi,...)		_hw_##o##_read()

#define hw_write__pcf8574			, _hw_wrpcf8574
#define _hw_wrpcf8574(o,sla,twi,v,...)		_hw_##o##_write(v)

#define hw_commit__pcf8574			, _hw_commit_pcf8574
#define _hw_commit_pcf8574(o,sla,twi,...)	_hw_##o##_commit()


/**
 * @addtogroup pcf8574
 * @defgroup iopcf8574 PCF8574 I/O
 */
#define hw_class__io8574


/*  Accept to append a number to a _pcf8574 definition so that
 *  '(pcf,n)' designates a single pin at position n of pcf, of class _io8574.
 *
 *  Validity of n is verified by functions.
 */
#define hw__pcf8574_			, _hw_pcf8574_
#define _hw_pcf8574_(o,n,twi,sla)	_HW_B(_hw_pcf8574_,_hw_isa_4bn_##n)(o,n)
#define _hw_pcf8574_1(o,n)		_io8574,o,(1,n)
#define _hw_pcf8574_0(o,n)		,o,HW_EM(o has no relative n)


/*  Accept to append a number to a _io8574 definition so that '(pcf,n,p)'
 *  designates a set of n consecutive pins at position p of pcf.
 *
 *  Validity of n and p is verified by functions.
 */
#define hw__io8574_			, _hw_io8574_
#define _hw_io8574_(o,r,bn,bp)		_HW_B(_hw_io8574_,_hw_is_1_##bn)(o,r,bn,bp)
#define _hw_io8574_0(o,r,...)		,o,HW_EM(o has no relative r)
#define _hw_io8574_1(o,r,bn,bp)		_HW_B(_hw_io85741_,_hw_isa_4bn_##r)(o,r,bn,bp)
#define _hw_io85741_1(o,r,bn,bp)	_io8574,o,(bp,r)
#define _hw_io85741_0(o,r,bn,bp)	,o,HW_EM(o has no relative r)


#define HW_BITS__io8574				, _hw_bits_io8574
#define _hw_bits_io8574(o,n,p,...)		n

#define hw__io8574_port				, _hw_io8574_port
#define _hw_io8574_port(o,...)			_pcf8574,o,()

#define hw_read__io8574				, _hw_rdio8574
#define _hw_rdio8574(o,bn,bp,v,...)		_hw_##o##_read_np(bn,bp)

#define hw_write__io8574			, _hw_wrio8574
#define _hw_wrio8574(o,bn,bp,v,...)		_hw_##o##_write_np(bn,bp,v)

#define hw_toggle__io8574			, _hw_tgio8574
#define _hw_tgio8574(o,bn,bp,...)		_hw_##o##_toggle_np(bn,bp)

#define hw_set__io8574				, _hw_w1io8574
#define _hw_w1io8574(o,bn,bp,...)		_hw_##o##_write_np(bn,bp,((1U<<bn)-1))

#define hw_clear__io8574			, _hw_w0io8574
#define _hw_w0io8574(o,bn,bp,...)		_hw_##o##_write_np(bn,bp,0)

#define hw_writea__io8574			, _hw_pcf8574iowra
#define _hw_pcf8574iowra(o,bn,bp,v,...)		_hw_##o##_writea_np(bn,bp,v)

#define hwa_write__io8574			, _hwa_pcf8574iowr
#define _hwa_pcf8574iowr(o,bn,bp,v,...)		_hw_##o##_writea_np(bn,bp,v)

/* #define hwa_write__io8574			, _hwa_wrio8574 */
/* #define _hwa_wrio8574(o,bn,bp,v,...)				\ */
/*   do{ uint8_t msk = ((1U<<bn)-1)<<bp ;				\ */
/*     _hw_##o##_value = (_hw_##o##_value & ~msk) | (v & msk) ;	\ */
/*     _hw_##o##_mask |= msk ;					\ */
/*   }while(0) */
