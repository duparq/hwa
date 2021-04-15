
/* This file is part of the HWA project.
 * Copyright (c) 2020 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief 24CXX I²C EEPROM
 */

/**
 * @ingroup ext
 * @defgroup ee24cxx 24CXX I²C EEPROM
 *
 * This is a generic class that implements 24CXX I²C EEPROMs.
 *
 * Header file:
 *
 * @code
 * #include <hwa/ext/24cxx.h>
 * @endcode
 *
 * @section ee24cxxctr Interface
 *
 * * define a 24CXX device:<br><br>
 *   <div>
 *   HW_24CXX(...) defines a 24CXX device. You must provide:
 *   * the I²C interface the device is connected to;
 *   * the slave address of the device;
 *   * the address size in bytes (1, 2);
 *   * the pagesize in bytes.
 *
 *   <br>Example:
 *
 *   @code
 *   #define EEPROM	  HW_24CXX( interface,	 twi0,	 \
 *				    address,	 0x50,	 \
 *				    addresssize, 2,	 \
 *				    pagesize,	 8 )
 *   @endcode
 *
 *   <br><br>The implementation of this device focuses on code size rather than
 *   on speed, so it relies on extern C functions. These functions are declared
 *   with HW_DECLARE(...) and defined with HW_IMPLEMENT(...):
 *   
 *   @code
 *   HW_DECLARE( EEPROM );	// Declare the functions that implement the device
 *   @endcode
 *   
 *   @code
 *   HW_IMPLEMENT( EEPROM );	// Define the functions that implement the device
 *   @endcode
 *   </div>
 */

/**
 * @ingroup ee24cxx_dev
 * Constructor for 24CXX EEPROM
 * @hideinitializer
 */

/*	_24cxx, name, twi, sla, as, ps
 *
 *	as: address size (larger EEPROM devices (from 24C32) have 16-bit address)
 *	ps: page size
 */

#define HW_24CXX(...)					_HW_24CXX0(__VA_ARGS__,,,,,,,,,)
#define _HW_24CXX0(k1,v1,k2,v2,k3,v3,k4,v4,eol,...)			\
  HW_B(_HW_24CXX0_,_hw_is_interfaceaddressaddresssizepagesize_##k1##k2##k3##k4##eol)(k1,v1,k2,v2,k3,v3,k4,v4)
#define _HW_24CXX0_0(...)						\
  ,HW_24CXX(...),"HW_24CXX(...)" must be defined as "HW_24CXX(interface,...,address,...,addresssize,...,pagesize,...)"
#define _HW_24CXX0_1(k1,twi,k2,sla,k3,as,k4,ps)		_HW_24CXX1(HW_XO(twi),sla,as,ps)
#define _HW_24CXX1(...)					_HW_24CXX2(__VA_ARGS__)
//#define _HW_24CXX_03(otwi,sla,as,ps)			_24cxx,24cxx_##otwi,(otwi,sla,as,ps)
#define _HW_24CXX2(x,...)				_HW_B(_HW_24CXX3_,x)(x,__VA_ARGS__)
#define _HW_24CXX3_1(z,o,e,...)				,o,e
#define _HW_24CXX3_0(c,o,d,sla,as,ps)			_24cxx,24cxx_##o,(o,sla,as,ps)

#define hw_class__24cxx

#define _hw_is_interfaceaddressaddresssizepagesize_interfaceaddressaddresssizepagesize	, 1


/**
 * @ingroup ee24cxx_dev
 * Declare the functions that implement a 24CXX EEPROM
 * @hideinitializer
 */
#define HW_DECLARE__24cxx		, _hw_dc24cxx

#define _hw_dc24cxx(o,twi,sla,as,ps,...)	HW_BV(_hw_dc24cxx,declare_,HW_A0(__VA_ARGS__),o)
#define _hw_dc24cxx0(v,o)			HW_E(HW_EM_OVL(v,(weak)))
#define _hw_dc24cxx1(weak,o)						\
  uint8_t _hw_##o##_read_bytes ( uint8_t, uint8_t, uint16_t, int, uint8_t* ) weak ; \
  uint8_t _hw_##o##_write_page ( uint8_t, uint8_t, uint8_t, uint16_t, int, const uint8_t* ) weak ; \
  uint8_t _hw_##o##_write_bytes ( uint8_t, uint8_t, uint8_t, uint16_t, int, const uint8_t* ) weak ; \
  extern uint8_t hw_foo()

/**
 * @ingroup ee24cxx_dev
 * Define the functions that implement a 24CXX EEPROM
 * @hideinitializer
 */
#define HW_IMPLEMENT__24cxx		, _hw_im24cxx

#define _hw_im24cxx(o,twi,...)			\
  _hw_im24cxx_read_bytes(twi)			\
    _hw_im24cxx_write_page(twi)			\
    _hw_im24cxx_write_bytes(twi)		\
    extern uint8_t hw_foo()


/**
 * @addtogroup ee24cxx
 *
 * * read multiple bytes from the EEPROM:
 *
 *   @code
 *   uint8_t r ;
 *   r = hw( read,    EEPROM,
 *           address, a,
 *           size,    s,
 *           buffer,  b );
 *   if (r < s)
 *     error();
 *   @endcode
 */
#define hw_read__24cxx			, _hw_rd24cxx

#define _hw_rd24cxx(...)		_hw_rd24cxx0(__VA_ARGS__,,,,,,)

#define _hw_rd24cxx0(o,twi,sla,as,ps,ka,va,ks,vs,kb,vb,eol,...)	\
  HW_B(_hw_rd24cxx0,_hw_is_addresssizebuffer_##ka##ks##kb##eol)(o,twi,sla,as,ka,va,ks,vs,kb,vb,eol)
#define _hw_rd24cxx00(o,twi,sla,as,ka,va,ks,vs,kb,vb,eol)	\
  HW_E(HW_EM_SY("hw(read,object,address,..., size,..., buffer,... )"))
#define _hw_rd24cxx01(o,twi,sla,as,ka,va,ks,vs,kb,vb,eol) 	\
  _hw_24cxx_##twi##_read_bytes(sla,as,va,vs,(uint8_t*)vb)



#define _hw_im24cxx_read_bytes(twi)					\
  uint8_t _hw_24cxx_##twi##_read_bytes ( uint8_t sla, uint8_t as, uint16_t addr, int len, uint8_t *buf ) \
  {									\
    uint8_t	_twst ;							\
    uint8_t	_sla ;							\
    uint8_t	rv = 0 ;						\
									\
    if ( as == 2 )							\
      _sla = sla | ((addr >> 8) & 0x07);				\
    else								\
      _sla = sla ;							\
									\
  begin:								\
    hw( xfr_start, twi );						\
									\
    while( !hw(read,(twi,irq)) ) {}					\
    switch( (_twst=hw(stat,twi)) )					\
      {									\
	case HW_TWI_START:						\
	case HW_TWI_REP_START:						\
	  break;							\
									\
	case HW_TWI_MT_ARB_LOST:					\
	  goto begin;							\
									\
	default:							\
	  goto error ;							\
      }									\
									\
    hw( xfr_slaw, twi, _sla>>1 );					\
    while( !hw(read,(twi,irq)) ) {}					\
    switch( (_twst=hw(stat,twi)) )					\
      {									\
	case HW_TWI_MT_SLA_ACK:						\
	  break;							\
									\
	case HW_TWI_MT_ARB_LOST:					\
	  goto begin;							\
									\
	default:							\
	  goto error;							\
      }									\
									\
    if ( as == 2 ) {							\
      hw( xfr_write, twi, addr >> 8 );					\
      while( !hw(read,(twi,irq)) ) {}					\
      switch( (_twst=hw(stat,twi)) )					\
	{								\
	  case HW_TWI_MT_DATA_ACK:					\
	    break;							\
									\
	  case HW_TWI_MT_DATA_NACK:					\
	    goto quit;							\
									\
	  case HW_TWI_MT_ARB_LOST:					\
	    goto begin;							\
									\
	  default:							\
	    goto error;							\
	}								\
    }									\
									\
    hw( xfr_write, twi, addr & 255 );					\
    while( !hw(read,(twi,irq)) ) {}					\
    switch( (_twst=hw(stat,twi)) )					\
      {									\
	case HW_TWI_MT_DATA_ACK:					\
	  break;							\
									\
	case HW_TWI_MT_DATA_NACK:					\
	  goto quit;							\
									\
	case HW_TWI_MT_ARB_LOST:					\
	  goto begin;							\
									\
	default:							\
	  goto error;							\
      }									\
									\
    hw( xfr_start, twi );						\
    while( !hw(read,(twi,irq)) ) {}					\
    switch( (_twst=hw(stat,twi)) )					\
      {									\
	case HW_TWI_START:						\
	case HW_TWI_REP_START:						\
	  break;							\
									\
	case HW_TWI_MT_ARB_LOST:					\
	  goto begin;							\
									\
	default:							\
	  goto error;							\
      }									\
									\
    hw( xfr_slar, twi, sla & 127 );					\
    while( !hw(read,(twi,irq)) ) {}					\
    switch( (_twst=hw(stat,twi)) )					\
      {									\
	case HW_TWI_MR_SLA_ACK:						\
	  break;							\
									\
	case HW_TWI_MR_SLA_NACK:					\
	  goto quit;							\
									\
	case HW_TWI_MR_ARB_LOST:					\
	  goto begin;							\
									\
	default:							\
	  goto error;							\
      }									\
									\
    for ( ; len>0 ; len-- ) {						\
      if (len == 1)							\
	hw( xfr_read, twi, nack );					\
      else								\
	hw( xfr_read, twi, ack );					\
									\
      while( !hw(read,(twi,irq)) ) {}					\
      switch( (_twst=hw(stat,twi)) )					\
	{								\
	  case HW_TWI_MR_DATA_NACK:					\
	    len = 0;							\
	  case HW_TWI_MR_DATA_ACK:					\
	    *buf++ = hw(read,twi);					\
	    rv++;							\
	    if(_twst == HW_TWI_MR_DATA_NACK)				\
	      goto quit;						\
	    break;							\
									\
	  default:							\
	    goto error;							\
	}								\
    }									\
									\
  error:								\
  quit:									\
    hw( xfr_stop, twi );						\
    return rv;								\
  }


/**
 * @addtogroup ee24cxx
 *
 * * write multiple bytes into the EEPROM:
 *
 *   @code
 *   uint8_t r ;
 *   r = hw( write,   EEPROM,
 *           address, a,
 *           size,    s,
 *           buffer,  b );
 *   if (r < s)
 *     error();
 *   @endcode
 */
#define hw_write__24cxx			, _hw_wr24cxx

#define _hw_is_addresssizebuffer_addresssizebuffer	, 1

#define _hw_wr24cxx(...)		_hw_wr24cxx0(__VA_ARGS__,,,,,,)
#define _hw_wr24cxx0(o,twi,sla,as,ps,ka,va,ks,vs,kb,vb,eol,...)	\
  HW_B(_hw_wr24cxx0,_hw_is_addresssizebuffer_##ka##ks##kb##eol)(o,twi,sla,as,ps,ka,va,ks,vs,kb,vb,eol)
#define _hw_wr24cxx00(o,twi,sla,as,ps,ka,va,ks,vs,kb,vb,eol)	\
  HW_E(HW_EM_SY("hw(write,object,address,..., size,..., buffer,... )"))
#define _hw_wr24cxx01(o,twi,sla,as,ps,ka,va,ks,vs,kb,vb,eol)	\
  _hw_24cxx_##twi##_write_bytes(sla,as,ps,va,vs,(const uint8_t*)vb)


#define	   _hw_im24cxx_write_page(twi)					\
  uint8_t _hw_24cxx_##twi##_write_page ( uint8_t sla, uint8_t as, uint8_t ps, uint16_t addr, int len, const uint8_t *buf ) \
  {									\
    uint8_t _twst ;							\
    uint8_t _sla ;							\
    uint8_t rv = 0;							\
    uint16_t endaddr;							\
									\
    if (addr + len <= (addr | (ps - 1)))				\
      endaddr = addr + len;						\
    else								\
      endaddr = (addr | (ps - 1)) + 1;					\
    len = endaddr - addr;						\
									\
    if ( as == 2 )							\
      _sla = sla | ((addr >> 8) & 0x07);				\
    else								\
      _sla = sla ;							\
									\
  begin:								\
    hw( xfr_start, twi );						\
    while( !hw(read,(twi,irq)) ) {}					\
    switch( (_twst=hw(stat,twi)) )					\
      {									\
	case HW_TWI_REP_START:						\
	case HW_TWI_START:						\
	  break;							\
									\
	case HW_TWI_MT_ARB_LOST:					\
	  goto begin;							\
									\
	default:							\
	  goto error ;							\
      }									\
									\
    hw( xfr_slaw, twi, _sla>>1 );					\
    while( !hw(read,(twi,irq)) ) {}					\
    switch( (_twst=hw(stat,twi)) )					\
      {									\
	case HW_TWI_MT_SLA_ACK:						\
	  break;							\
									\
	case HW_TWI_MT_ARB_LOST:					\
	  goto begin;							\
									\
	default:							\
	  goto error;							\
      }									\
									\
    if ( as == 2 ) {							\
      hw( xfr_write, twi, addr>>8 );					\
      while( !hw(read,(twi,irq)) ) {}					\
      switch( (_twst=hw(stat,twi)) )					\
	{								\
	  case HW_TWI_MT_DATA_ACK:					\
	    break;							\
									\
	  case HW_TWI_MT_DATA_NACK:					\
	    goto quit;							\
									\
	  case HW_TWI_MT_ARB_LOST:					\
	    goto begin;							\
									\
	  default:							\
	    goto error;							\
	}								\
    }									\
									\
    hw( xfr_write, twi, addr );						\
    while( !hw(read,(twi,irq)) ) {}					\
    switch( (_twst=hw(stat,twi)) )					\
      {									\
	case HW_TWI_MT_DATA_ACK:					\
	  break;							\
									\
	case HW_TWI_MT_DATA_NACK:					\
	  goto quit;							\
									\
	case HW_TWI_MT_ARB_LOST:					\
	  goto begin;							\
									\
	default:							\
	  goto error;							\
      }									\
									\
									\
    for ( ; len>0 ; len-- ) {						\
									\
      hw( xfr_write, twi, (*buf++) );					\
									\
      while( !hw(read,(twi,irq)) ) {}					\
      switch( (_twst=hw(stat,twi)) )					\
	{								\
	  case HW_TWI_MT_DATA_NACK:					\
	    goto error;							\
									\
	  case HW_TWI_MT_DATA_ACK:					\
	    rv++;							\
	    break;							\
									\
	  default:							\
	    goto error;							\
	}								\
    }									\
									\
  error:								\
  quit:									\
    hw( xfr_stop, twi );						\
    return rv;								\
  }


#define _hw_im24cxx_write_bytes(twi)					\
  uint8_t _hw_24cxx_##twi##_write_bytes ( uint8_t sla, uint8_t as, uint8_t ps, \
					  uint16_t eeaddr, int len, const uint8_t *buf) \
  {									\
    uint8_t rv, total;							\
									\
    total = 0;								\
    do									\
      {									\
	rv = _hw_24cxx_##twi##_write_page( sla, as, ps, eeaddr, len, buf); \
	if (rv == (uint8_t)-1)						\
	  return -1;							\
									\
	eeaddr += rv;							\
	len -= rv;							\
	buf += rv;							\
	total += rv;							\
      }									\
    while (len > 0);							\
									\
    return total;							\
  }
