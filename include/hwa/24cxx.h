
/* This file is part of the HWA project.
 * Copyright (c) 2020 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief 24CXX I²C EEPROM
 * @page _24cxx 24CXX I²C EEPROM
 *
 * As this device is not speed critical, its implementation focuses on code size
 * rather than on speed, so it relies on extern C functions rather than on
 * inlined code.
 *
 * __Declaration__
 *
 * @code
 * #define EEPROM         HW_24CXX ( interface,   twi0,   \
 *                                   address,     0x50,   \
 *                                   addresssize, 2,      \
 *                                   pagesize,    8 )
 * @endcode
 */
/*	_24cxx, name, twi, sla, as, ps
 *
 *	as: address size (larger EEPROM devices (from 24C32) have 16-bit address)
 *	ps: page size
 */
#define hw_class__24cxx

#define _hw_is_interfaceaddressaddresssizepagesize_interfaceaddressaddresssizepagesize	, 1

#define HW_24CXX(...)				_HW_24CXX_01(__VA_ARGS__,,,,,,,,,)
#define _HW_24CXX_01(k1,v1,k2,v2,k3,v3,k4,v4,eol,...)			\
  HW_Y(_HW_24CXX_01_,_hw_is_interfaceaddressaddresssizepagesize_##k1##k2##k3##k4##eol)(k1,v1,k2,v2,k3,v3,k4,v4)
#define _HW_24CXX_01_0(...)						\
  ,HW_24CXX(...),"HW_24CXX(...)" must be defined as "HW_24CXX(interface,...,address,...,addresssize,...,pagesize,...)"
#define _HW_24CXX_01_1(k1,twi,k2,sla,k3,as,k4,ps)	_HW_24CXX_02(HW_A1(HW_X(twi)),sla,as,ps)
#define _HW_24CXX_02(...)		_HW_24CXX_03(__VA_ARGS__)
#define _HW_24CXX_03(otwi,sla,as,ps)	xb(_24cxx,24cxx_##otwi,otwi,sla,as,ps)


/**
 * @page _24cxx
 * __Interface__
 *
 * The following declares the functions that implement the memory. You can use it in
 * your header files:
 *
 * @code
 * HW_DECLARE( EEPROM );
 * @endcode
 */
#define HW_DECLARE__24cxx		, _hw_declare_pcf8574

#define _hw_declare_pcf8574(o,...)					\
  uint8_t _hw_##o##_read_bytes ( uint8_t, uint8_t, uint16_t, int, uint8_t* ); \
  uint8_t _hw_##o##_write_page ( uint8_t, uint8_t, uint8_t, uint16_t, int, const uint8_t* ); \
  uint8_t _hw_##o##_write_bytes ( uint8_t, uint8_t, uint8_t, uint16_t, int, const uint8_t* ); \
  extern void _hwa_fake()


/**
 * @page _24cxx
 * __Implement__
 *
 * The following defines the functions that implement the memory. It must
 * appear in one of your source files:
 *
 * @code
 * HW_DEFINE( EEPROM );
 * @endcode
 *
 * @code
 * HW_DEFINE_WEAK( EEPROM ); // Allows multiple definitions
 * @endcode
 */
#define HW_DEFINE__24cxx		, _hw_im24cxx_
#define HW_DEFINE_WEAK__24cxx	, _hw_im24cxxw

#define _hw_im24cxx_(o,twi,...)		_hw_im24cxx(twi,)
#define _hw_im24cxxw(o,twi,...)		_hw_im24cxx(twi,__attribute__((weak)))

#define _hw_im24cxx(twi,weak)				\
  _hw_im24cxx_read_bytes(twi,weak)			\
    _hw_im24cxx_write_page(twi,weak)			\
    _hw_im24cxx_write_bytes(twi,weak)			\
    extern void _hwa_fake() /* require a semicolon */


/**
 * @page _24cxx
 * __Actions__
 *
 * `write`
 *
 * @code
 * uint8_t r ;
 * r = hw( write,   EEPROM,
 *         address, a,
 *         size,    s,
 *         buffer,  b );
 * if (r < s)
 *   error();
 * @endcode
 */
#define hw_write__24cxx			, _hw_wr24cxx

#define _hw_is_addresssizebuffer_addresssizebuffer	, 1

#define _hw_wr24cxx(...)		_hw_wr24cxx0(__VA_ARGS__,,,,,,)
#define _hw_wr24cxx0(o,twi,sla,as,ps,ka,va,ks,vs,kb,vb,eol,...)	HW_Y(_hw_wr24cxx0,_hw_is_addresssizebuffer_##ka##ks##kb##eol)(o,twi,sla,as,ps,ka,va,ks,vs,kb,vb,eol)
#define _hw_wr24cxx00(o,twi,sla,as,ps,ka,va,ks,vs,kb,vb,eol) HW_E(syntax is hw(write,object,address,..., size,..., buffer,... ))
#define _hw_wr24cxx01(o,twi,sla,as,ps,ka,va,ks,vs,kb,vb,eol) _hw_24cxx_##twi##_write_bytes(sla,as,ps,va,vs,(const uint8_t*)vb)


/**
 * @page _24cxx
 *
 * `read`
 *
 * @code
 * uint8_t r ;
 * r = hw( read,    EEPROM,
 *         address, a,
 *         size,    s,
 *         buffer,  b );
 * if (r < s)
 *   error();
 * @endcode
 */
#define hw_read__24cxx			, _hw_rd24cxx

#define _hw_rd24cxx(...)		_hw_rd24cxx0(__VA_ARGS__,,,,,,)
#define _hw_rd24cxx0(o,twi,sla,as,ps,ka,va,ks,vs,kb,vb,eol,...)	HW_Y(_hw_rd24cxx0,_hw_is_addresssizebuffer_##ka##ks##kb##eol)(o,twi,sla,as,ka,va,ks,vs,kb,vb,eol)
#define _hw_rd24cxx00(o,twi,sla,as,ka,va,ks,vs,kb,vb,eol) HW_E(syntax is hw(read,object,address,..., size,..., buffer,... ))
#define _hw_rd24cxx01(o,twi,sla,as,ka,va,ks,vs,kb,vb,eol) _hw_24cxx_##twi##_read_bytes(sla,as,va,vs,(uint8_t*)vb)



#define _hw_im24cxx_read_bytes(twi,weak)				\
  uint8_t weak _hw_24cxx_##twi##_read_bytes ( uint8_t sla, uint8_t as, uint16_t addr, int len, uint8_t *buf ) \
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
    hw( bus_start, twi );						\
									\
    while( !hw(read, irqflag(twi)) ) {}					\
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
    hw( bus_slaw, twi, _sla>>1 );					\
    while( !hw(read, irqflag(twi)) ) {}					\
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
      hw( bus_write, twi, addr >> 8 );					\
      while( !hw(read, irqflag(twi)) ) {}				\
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
    hw( bus_write, twi, addr & 255 );					\
    while( !hw(read, irqflag(twi)) ) {}					\
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
    hw( bus_start, twi );						\
    while( !hw(read, irqflag(twi)) ) {}					\
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
    hw( bus_slar, twi, sla & 127 );					\
    while( !hw(read, irqflag(twi)) ) {}					\
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
	hw( bus_read, twi, nack );					\
      else								\
	hw( bus_read, twi, ack );					\
									\
      while( !hw(read, irqflag(twi)) ) {}				\
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
    hw( bus_stop, twi );						\
    return rv;								\
  }


#define    _hw_im24cxx_write_page(twi,weak)				\
  uint8_t weak _hw_24cxx_##twi##_write_page ( uint8_t sla, uint8_t as, uint8_t ps, uint16_t addr, int len, const uint8_t *buf ) \
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
    hw( bus_start, twi );						\
    while( !hw(read, irqflag(twi)) ) {}					\
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
    hw( bus_slaw, twi, _sla>>1 );					\
    while( !hw(read, irqflag(twi)) ) {}					\
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
      hw( bus_write, twi, addr>>8 );					\
      while( !hw(read, irqflag(twi)) ) {}				\
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
    hw( bus_write, twi, addr );						\
    while( !hw(read, irqflag(twi)) ) {}					\
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
      hw( bus_write, twi, (*buf++) );					\
									\
      while( !hw(read, irqflag(twi)) ) {}				\
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
    hw( bus_stop, twi );						\
    return rv;								\
  }


#define _hw_im24cxx_write_bytes(twi,weak)				\
  uint8_t weak _hw_24cxx_##twi##_write_bytes ( uint8_t sla, uint8_t as, uint8_t ps, \
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
