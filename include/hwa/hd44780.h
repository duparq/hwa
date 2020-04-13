
/* This file is part of the HWA project.
 * Copyright (c) 2018 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief HD44780 LCD driver
 * @page hd44780 HD44780 LCD driver
 *
 * As this device is not speed critical, its implementation focuses on code size
 * rather than on speed, so it relies on extern C functions rather than on
 * inlined code.
 *
 * Currently, HWA supports only the driving of the HD44780 through the I²C bus
 * expander @ref pcf8574 "PCF8574".
 *
 * __Declaration__
 *
 * @code
 * #define PCF          HW_PCF8574( interface, twi0, address, 0x27 )
 *
 * #define LCD          HW_HD44780( lines, 2,                  \
 *                                  cols,  16,                 \
 *                                  e,     HW_IO(PCF, 1, 2),   \
 *                                  rs,    HW_IO(PCF, 1, 0),   \
 *                                  rw,    HW_IO(PCF, 1, 1),   \
 *                                  data,  HW_IO(PCF, 4, 4) )
 * @endcode
 */
#define hw_class__hd44780

#define _hw_is_linescolsersrwdata_linescolsersrwdata	, 1
#define _hw_isa_iotwi__pcf8574_io			, 1
#define _hw_hd44780_for__pcf8574_io			, twi


#define HW_HD44780(...)			_HW_HD44780_01(__VA_ARGS__,,,,,,,,,,)
#define _HW_HD44780_01(kl,vl,kc,vc,ke,ve,krs,vrs,krw,vrw,kd,vd,eol,...) \
  HW_Y0(_HW_HD44780_01_,_hw_is_linescolsersrwdata_##kl##kc##ke##krs##krw##kd##eol) \
  (kl,vl,kc,vc,ke,ve,krs,vrs,krw,vrw,kd,vd)
#define _HW_HD44780_01_0(...)		, \
    HW_HD44780(...),"HW_HD44780(...)" must be defined as \
    "HW_HD44780(lines,...,e,...,rs,...,rw,...,d,..."
#define _HW_HD44780_01_1(kl,vl,kc,vc,ke,ve,krs,vrs,krw,vrw,kd,vd)	\
  _HW_HD44780_02((HW_X(ve)),(HW_X(vd)),(HW_X(vrs)),(HW_X(vrw)),vl,vc)

#define _HW_HD44780_02(...)		_HW_HD44780_03(__VA_ARGS__)
#define _HW_HD44780_03(el,dl,rsl,rwl,l,c)	_HW_HD44780_04( HW_A0_A1 el, HW_BITS dl, l,c,el,rsl,rwl,dl)
#define _HW_HD44780_04(...)		_HW_HD44780_05(__VA_ARGS__)
#define _HW_HD44780_05(c,...)		_HW_HD44780_06(_hw_hd44780_for_##c,c,__VA_ARGS__)
#define _HW_HD44780_06(...)		_HW_HD44780_07(__VA_ARGS__)
#define _HW_HD44780_07(x,...)		HW_Y0(_HW_HD44780_07_,x)(__VA_ARGS__)
#define _HW_HD44780_07_1(c,c0,p,n,...)	xb(_hd44780,hd44780_##p,c##n,__VA_ARGS__)


/**
 * @page hd44780 HD44780 LCD driver
 * __Interface__
 *
 * The following makes the implementation functions for TWI declared. Use it in
 * your header files:
 *
 * @code
 * HW_DECLARE(LCD);
 * @endcode
 */
#define HW_DECLARE__hd44780		, _hw_hd44780_interface

#define _hw_hd44780_interface(o,...)		\
  void _hw_##o##__pulse ( );			\
  void _hw_##o##__write ( uint8_t, uint8_t );	\
  uint8_t _hw_##o##__read ( uint8_t );		\
  uint8_t _hw_##o##__wait ( );			\
  void _hw_##o##__command ( uint8_t );		\
  void _hw_##o##__data ( uint8_t );		\
  void _hw_##o##_clear_cgram ( );		\
  void _hw_##o##_cls ( );			\
  void _hw_##o##_init ( );			\
  void _hw_##o##_gotoxy ( uint8_t, uint8_t );	\
  void _hw_##o##_newline( uint8_t );		\
  void _hw_##o##_home ( );			\
  void _hw_##o##_putchar( unsigned char ) /* require a ; */


/**
 * @page hd44780 HD44780 LCD driver
 * __Implement__
 *
 * The following makes the implementation functions for TWI defined. It must
 * appear in one of your source files:
 *
 * @code
 * HW_DEFINE(LCD);
 * @endcode
 */
#define HW_DEFINE__hd44780		, _hw_hd44780_implement

#define _hw_hd44780_implement(o,v,...)			\
  _hw_define_hd44780##v##__pulse(o,v,__VA_ARGS__)	\
  _hw_define_hd44780##v##__write(o,v,__VA_ARGS__)	\
  _hw_define_hd44780##v##__read(o,v,__VA_ARGS__)	\
  _hw_define_hd44780##v##__wait(o,v,__VA_ARGS__)	\
  _hw_define_hd44780##v##__command(o,v,__VA_ARGS__)	\
  _hw_define_hd44780##v##__data(o,v,__VA_ARGS__)	\
  _hw_define_hd44780##v##_cls(o,v,__VA_ARGS__)	\
  _hw_define_hd44780##v##_init(o,v,__VA_ARGS__)	\
  _hw_define_hd44780##v##_gotoxy(o,v,__VA_ARGS__)	\
  _hw_define_hd44780##v##_newline(o,v,__VA_ARGS__)	\
  _hw_define_hd44780##v##_home(o,v,__VA_ARGS__)	\
  _hw_define_hd44780##v##_putchar(o,v,__VA_ARGS__)	\
  extern void _hwa_fake() /* require a ; */

#define _hw_define_hd44780twi4__pulse(o,v,lines,cols,e,...)	\
  void _hw_##o##__pulse ( )	{				\
    hw(write, HW_XB e, 1);					\
    hw(write, HW_XB e, 0);					\
  }

#define _hw_define_hd44780twi4__write(o,v,lines,cols,e,rs,rw,d,...)	\
  void _hw_##o##__write ( uint8_t data, uint8_t r )	{		\
    _hw_##o##__wait();							\
    hw( writea, HW_XB rs, r );						\
    hw( writea, HW_XB rw, 0 );						\
    hw( writea, HW_XB d, data>>4 );					\
    hw( commit, HW_PORT e );						\
    _hw_##o##__pulse();							\
    hw( write, HW_XB d, data&15 );					\
    _hw_##o##__pulse();							\
    hw( write, HW_XB d, 15 );						\
  }

#define _hw_define_hd44780twi4__read(o,v,lines,cols,e,rs,rw,d,...)	\
  uint8_t _hw_##o##__read ( uint8_t r ) {				\
    _hw( write, HW_XB rs, r );						\
    _hw( write, HW_XB rw, 1 );						\
    _hw( write, HW_XB e, 1 );						\
    uint8_t hi = _hw( read, HW_XB d );					\
    _hw( write, HW_XB e, 0 );						\
    _hw( write, HW_XB e, 1 );						\
    hw_waste_cycles( 100e-6 * HW_SYSHZ );/*FIXME: can't have it working without this delay?*/ \
    uint8_t lo = _hw( read, HW_XB d );					\
    _hw( write, HW_XB e, 0 );						\
    return (hi<<4)|lo ;							\
  }

#define _hw_define_hd44780twi4__wait(o,v,lines,cols,e,rs,rw,d,...)	\
  uint8_t _hw_##o##__wait ( ) {						\
    uint8_t r0 ;							\
    while( (r0 = _hw_##o##__read(0)) & 0x80 ) /* Bit 7 of register #0: busy  */ \
      hw_waste_cycles( 10e-6 * HW_SYSHZ );				\
    return r0; /* Return counter */					\
  }

#define _hw_define_hd44780twi4__command(o,v,lines,cols,e,rs,rw,d,...) \
  void _hw_##o##__command ( uint8_t c ) {				\
    _hw_##o##__write(c,0);						\
  }

#define _hw_define_hd44780twi4__data(o,v,lines,cols,e,rs,rw,d,...)	\
  void _hw_##o##__data ( uint8_t data ) {				\
    _hw_##o##__write(data,1);						\
  }

#define _hw_define_hd44780twi4_cls(o,v,lines,cols,e,rs,rw,d,...)	\
  void _hw_##o##_cls ( ) {						\
    _hw_##o##__command(1);						\
  }

#define _hw_define_hd44780twi4_init(o,v,lines,cols,e,rs,rw,d,...)	\
  void _hw_##o##_init ( ) {						\
    hw( writea, HW_XB e, 0 );						\
    hw( writea, HW_XB rs, 0 );						\
    hw( writea, HW_XB rw, 0 );						\
    hw( writea, HW_XB d, 0 );						\
    hw_waste_cycles( 0.015 * HW_SYSHZ );				\
    hw( write, HW_XB d, 3 );	/* initial write 8bit */		\
    _hw_##o##__pulse();							\
    hw_waste_cycles( 0.0041 * HW_SYSHZ );				\
    _hw_##o##__pulse();			/* repeat last command */	\
    hw_waste_cycles( 64e-6 * HW_SYSHZ );				\
    _hw_##o##__pulse();			/* repeat last command */	\
    hw_waste_cycles( 64e-6 * HW_SYSHZ );				\
    hw( write, HW_XB d, 2 );	/* configure for 4bit */		\
    _hw_##o##__pulse();							\
    hw_waste_cycles( 64e-6 * HW_SYSHZ );				\
    uint8_t rv = 0x20 ;	/* 4-bit, 1 line, 5x8 font */			\
    if ( lines == 2 )							\
      rv |= 0x08 ;							\
    _hw_##o##__command( rv ); /* 4-bit, 2 lines, 5x8 font */		\
    _hw_##o##__command( 0x08 ); /* Display off, no cursor, no blink */	\
    _hw_##o##_cls( );							\
    _hw_##o##__command( 0x06 ); /* Entry mode: inc, no shift */		\
    _hw_##o##__command( 0x0C ); /* Display on, no cursor, no blink */	\
  }

#define _hw_define_hd44780twi4_gotoxy(o,v,lines,cols,e,rs,rw,d,...)	\
  void _hw_##o##_gotoxy ( uint8_t x, uint8_t y ) {			\
    if ( lines==2 && y>0 )						\
      _hw_##o##__command(0x80+64+x);					\
    else								\
      _hw_##o##__command(0x80+0+x);					\
  }

#define _hw_define_hd44780twi4_newline(o,v,lines,cols,e,rs,rw,d,...) \
  void _hw_##o##_newline ( uint8_t pos ) {				\
    if ( lines==1 )							\
      _hw_##o##_gotoxy(0,0);						\
    else if ( lines==2 ) {						\
      if ( pos < 64 )							\
	_hw_##o##_gotoxy(0,1);						\
      else								\
	_hw_##o##_gotoxy(0,0);						\
    }									\
  }									\

#define _hw_define_hd44780twi4_home(o,v,lines,cols,e,rs,rw,d,...)	\
  void _hw_##o##_home ( ) {						\
    _hw_##o##__command(2);						\
  }

/* FIXME: should cache current line and column so that reading the LCD would not be necessary
 */
#define _hw_define_hd44780twi4_putchar(o,v,lines,cols,e,rs,rw,d,...) \
  void _hw_##o##_putchar ( unsigned char c ) {				\
    uint8_t pos;							\
									\
    pos = _hw_##o##__wait();   /* wait busy-flag and get address counter */ \
    if (c=='\n')							\
      _hw_##o##_newline(pos);						\
    else {								\
      if ( lines==1 ) {							\
	if ( pos == cols )						\
	  _hw_##o##_gotoxy(0,0);					\
      }									\
      else if ( lines==2 ) {						\
	if ( pos == 0+cols )						\
	  _hw_##o##_gotoxy(0,1);					\
	else if ( pos == 64+cols )					\
	  _hw_##o##_gotoxy(0,0);					\
      }									\
      _hw_##o##__data(c);						\
    }									\
  }


#define HW_FUNCTION__hd44780		, _hw_function_hd44780
#define _hw_function_hd44780(o,v,lines,cols,e,rs,rw,d,f,...)	_hw_##o##_##f


#define hw_init__hd44780		, _hw_hd44780_init
#define _hw_hd44780_init(o,...)		_hw_##o##_init()

#define hw_cls__hd44780			, _hw_hd44780_cls
#define _hw_hd44780_cls(o,...)		_hw_##o##_cls()

#define hw_gotoxy__hd44780		, _hw_hd44780_gotoxy
#define _hw_hd44780_gotoxy(o,v,lines,cols,e,rs,rw,d,x,y,...)	_hw_##o##_gotoxy(x,y)

#define hw_newline__hd44780		, _hw_hd44780_newline
#define _hw_hd44780_newline(o,v,lines,cols,e,rs,rw,d,pos,...)	_hw_##o##_newline(pos)

#define hw_home__hd44780		, _hw_hd44780_home
#define _hw_hd44780_home(o,...)		_hw_##o##_home()

#define hw_putchar__hd44780		, _hw_hd44780_putchar
#define _hw_hd44780_putchar(o,v,lines,cols,e,rs,rw,d,ch,...)	o##_putchar(ch)
