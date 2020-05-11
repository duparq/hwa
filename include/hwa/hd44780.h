
/* This file is part of the HWA project.
 * Copyright (c) 2018 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief HD44780: LCD driver
 * @page hd44780 HD44780: LCD driver
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

#define HW_HD44780(...)				_HW_HD44780_(__VA_ARGS__,,,,,,,,,,)
#define _HW_HD44780_(k,...)			HW_KW(_HW_HD44780_1,lines,k)(k,__VA_ARGS__)
#define _HW_HD44780_10(k,...)			_HW_HD44780_E(k,__VA_ARGS__)
#define _HW_HD44780_11(k0,l,k,...)		HW_KW(_HW_HD44780_2,cols,k)(l,k,__VA_ARGS__)
#define _HW_HD44780_20(l,k,...)			_HW_HD44780_E(k,__VA_ARGS__)
#define _HW_HD44780_21(l,k0,c,k,...)		HW_KW(_HW_HD44780_3,e,k)(l,c,k,__VA_ARGS__)
#define _HW_HD44780_30(l,c,k,...)		_HW_HD44780_E(k,__VA_ARGS__)
#define _HW_HD44780_31(l,c,k,...)		_HW_HD44780_32(l,c,HW_AD(__VA_ARGS__))
#define _HW_HD44780_32(...)			_HW_HD44780_33(__VA_ARGS__)
#define _HW_HD44780_33(l,c,e,k,...)		HW_KW(_HW_HD44780_4,rs,k)(l,c,e,k,__VA_ARGS__)
#define _HW_HD44780_40(l,c,e,k,...)		_HW_HD44780_E(k,__VA_ARGS__)
#define _HW_HD44780_41(l,c,e,k,...)		_HW_HD44780_42(l,c,e,HW_AD(__VA_ARGS__))
#define _HW_HD44780_42(...)			_HW_HD44780_43(__VA_ARGS__)
#define _HW_HD44780_43(l,c,e,s,k,...)		HW_KW(_HW_HD44780_5,rw,k)(l,c,e,s,k,__VA_ARGS__)
#define _HW_HD44780_50(l,c,e,s,k,...)		_HW_HD44780_E(k,__VA_ARGS__)
#define _HW_HD44780_51(l,c,e,s,k,...)		_HW_HD44780_52(l,c,e,s,HW_AD(__VA_ARGS__))
#define _HW_HD44780_52(...)			_HW_HD44780_53(__VA_ARGS__)
#define _HW_HD44780_53(l,c,e,s,w,k,...)		HW_KW(_HW_HD44780_6,data,k)(l,c,e,s,w,k,__VA_ARGS__)
#define _HW_HD44780_60(l,c,e,s,w,k,...)		_HW_HD44780_E(k,__VA_ARGS__)
#define _HW_HD44780_61(l,c,e,s,w,k,...)		_HW_HD44780_62(l,c,e,s,w,HW_AD(__VA_ARGS__))
#define _HW_HD44780_62(...)			_HW_HD44780_63(__VA_ARGS__)
#define _HW_HD44780_63(l,c,e,s,w,d,g,...)	HW_Y(_HW_HD44780_7,g)(l,c,e,s,w,d,g,__VA_ARGS__)
#define _HW_HD44780_70(x,...)			HW_E_G(x)
#define _HW_HD44780_71(l,c,e,s,w,d,...)		_HW_HD44780_72(HW_A1 e,l,c,e,s,w,d)
#define _HW_HD44780_72(...)			_HW_HD44780_73(__VA_ARGS__)
#define _HW_HD44780_73(eo,...)			_hd44780,hd44780_##eo,(__VA_ARGS__)

#define _HW_HD44780_E(k,...)	HW_E(HW_EM_S("HW_HD44780(lines,..., cols,..., e,..., rs,..., rw,..., data,...)" (k,__VA_ARGS__)))


/**
 * @page hd44780
 *
 * The following declares the functions that implement the object:
 *
 * @code
 * HW_DECLARE(LCD);
 * @endcode
 */
#define HW_DECLARE__hd44780		, _hw_dchd44780

#define _hw_dchd44780(o,...)					\
  void _hw_##o##__pulse ( );					\
  void _hw_##o##__write ( uint8_t, uint8_t );			\
  uint8_t _hw_##o##__read ( uint8_t );				\
  uint8_t _hw_##o##__wait ( );					\
  void _hw_##o##__command ( uint8_t );				\
  void _hw_##o##__data ( uint8_t );				\
  void _hw_##o##_clear_cgram ( );				\
  void _hw_##o##_cls ( );					\
  void _hw_##o##_init ( );					\
  void _hw_##o##_gotoxy ( uint8_t, uint8_t );			\
  void _hw_##o##_newline( uint8_t );				\
  void _hw_##o##_home ( );					\
  void _hw_##o##_putchar( unsigned char ) /* require a ; */


/**
 * @page hd44780
 *
 * The following defines the functions that implement the object:
 *
 * @code
 * HW_DEFINE(LCD);
 * @endcode
 */
#define HW_DEFINE__hd44780		, _hw_dfhd44780

#define _hw_dfhd44780(o,...)				\
  _hw_dfhd44780__pulse(o,__VA_ARGS__)			\
    _hw_dfhd44780__write(o,__VA_ARGS__)			\
    _hw_dfhd44780__read(o,__VA_ARGS__)			\
    _hw_dfhd44780__wait(o,__VA_ARGS__)			\
    _hw_dfhd44780__command(o,__VA_ARGS__)		\
    _hw_dfhd44780__data(o,__VA_ARGS__)			\
    _hw_dfhd44780_cls(o,__VA_ARGS__)			\
    _hw_dfhd44780_init(o,__VA_ARGS__)			\
    _hw_dfhd44780_gotoxy(o,__VA_ARGS__)			\
    _hw_dfhd44780_newline(o,__VA_ARGS__)		\
    _hw_dfhd44780_home(o,__VA_ARGS__)			\
    _hw_dfhd44780_putchar(o,__VA_ARGS__)		\
    extern void _hwa_() /* require/catch a semicolon */

#define _hw_dfhd44780__pulse(o,lines,cols,e,...)	\
  void _hw_##o##__pulse ( ) {				\
    hw(write, e, 1);				\
    hw(write, e, 0);				\
  }

#define _hw_dfhd44780__write(o,lines,cols,e,rs,rw,d,...)	\
  void _hw_##o##__write ( uint8_t data, uint8_t r )	{	\
    _hw_##o##__wait();						\
    hw( writea, rs, r );					\
    hw( writea, rw, 0 );					\
    hw( writea, d, data>>4 );				\
    hw( commit, HW_PORT e );					\
    _hw_##o##__pulse();						\
    hw( write, d, data&15 );				\
    _hw_##o##__pulse();						\
    hw( write, d, 15 );					\
  }

#define _hw_dfhd44780__read(o,lines,cols,e,rs,rw,d,...)			\
  uint8_t _hw_##o##__read ( uint8_t r ) {				\
    _hw( write, rs, r );						\
    _hw( write, rw, 1 );						\
    _hw( write, e, 1 );						\
    uint8_t hi = _hw( read, d );					\
    _hw( write, e, 0 );						\
    _hw( write, e, 1 );						\
    hw_waste_cycles( 100e-6 * HW_SYSHZ );/*FIXME: can't have it working without this delay?*/ \
    uint8_t lo = _hw( read, d );					\
    _hw( write, e, 0 );						\
    return (hi<<4)|lo ;							\
  }

#define _hw_dfhd44780__wait(o,lines,cols,e,rs,rw,d,...)			\
  uint8_t _hw_##o##__wait ( ) {						\
    uint8_t r0 ;							\
    while( (r0 = _hw_##o##__read(0)) & 0x80 ) /* Bit 7 of register #0: busy  */ \
      hw_waste_cycles( 10e-6 * HW_SYSHZ );				\
    return r0; /* Return counter */					\
  }

#define _hw_dfhd44780__command(o,lines,cols,e,rs,rw,d,...)	\
  void _hw_##o##__command ( uint8_t c ) {			\
    _hw_##o##__write(c,0);					\
  }

#define _hw_dfhd44780__data(o,lines,cols,e,rs,rw,d,...)	\
  void _hw_##o##__data ( uint8_t data ) {		\
    _hw_##o##__write(data,1);				\
  }

#define _hw_dfhd44780_cls(o,lines,cols,e,rs,rw,d,...)	\
  void _hw_##o##_cls ( ) {				\
    _hw_##o##__command(1);				\
  }

#define _hw_dfhd44780_init(o,lines,cols,e,rs,rw,d,...)			\
  void _hw_##o##_init ( ) {						\
    hw( writea, e, 0 );						\
    hw( writea, rs, 0 );						\
    hw( writea, rw, 0 );						\
    hw( writea, d, 0 );						\
    hw_waste_cycles( 0.015 * HW_SYSHZ );				\
    hw( write, d, 3 );	/* initial write 8bit */		\
    _hw_##o##__pulse();							\
    hw_waste_cycles( 0.0041 * HW_SYSHZ );				\
    _hw_##o##__pulse();			/* repeat last command */	\
    hw_waste_cycles( 64e-6 * HW_SYSHZ );				\
    _hw_##o##__pulse();			/* repeat last command */	\
    hw_waste_cycles( 64e-6 * HW_SYSHZ );				\
    hw( write, d, 2 );	/* configure for 4bit */		\
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

#define _hw_dfhd44780_gotoxy(o,lines,cols,e,rs,rw,d,...)	\
  void _hw_##o##_gotoxy ( uint8_t x, uint8_t y ) {		\
    if ( lines==2 && y>0 )					\
      _hw_##o##__command(0x80+64+x);				\
    else							\
      _hw_##o##__command(0x80+0+x);				\
  }

#define _hw_dfhd44780_newline(o,lines,cols,e,rs,rw,d,...)	\
  void _hw_##o##_newline ( uint8_t pos ) {			\
    if ( lines==1 )						\
      _hw_##o##_gotoxy(0,0);					\
    else if ( lines==2 ) {					\
      if ( pos < 64 )						\
	_hw_##o##_gotoxy(0,1);					\
      else							\
	_hw_##o##_gotoxy(0,0);					\
    }								\
  }								\

#define _hw_dfhd44780_home(o,lines,cols,e,rs,rw,d,...)	\
  void _hw_##o##_home ( ) {				\
    _hw_##o##__command(2);				\
  }

/* FIXME: should cache current line and column so that reading the LCD would not be necessary
 */
#define _hw_dfhd44780_putchar(o,lines,cols,e,rs,rw,d,...)		\
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
#define _hw_function_hd44780(o,lines,cols,e,rs,rw,d,f,...)	_hw_##o##_##f


/**
 * @page hd44780
 *
 * __Actions__
 *
 * `init`: the LCD requires an initialization before it can be used.
 * @code
 * hw( init, LCD );
 * @endcode
 */
#define hw_init__hd44780		, _hw_hd44780_init
#define _hw_hd44780_init(o,...)		_hw_##o##_init()


/**
 * @page hd44780
 *
 * `cls`: clear screen.
 * @code
 * hw( cls, LCD );
 * @endcode
 */
#define hw_cls__hd44780			, _hw_hd44780_cls
#define _hw_hd44780_cls(o,...)		_hw_##o##_cls()


/**
 * @page hd44780
 *
 * `gotoxy`: move the cursor to column x, line y.
 * @code
 * hw( gotoxy, LCD, x, y );
 * @endcode
 */
#define hw_gotoxy__hd44780					, _hw_hd44780_gotoxy
#define _hw_hd44780_gotoxy(o,lines,cols,e,rs,rw,d,x,y,...)	_hw_##o##_gotoxy(x,y)


/**
 * @page hd44780
 *
 * `newline`: move the cursor to the start of the line below.
 * @code
 * hw( newline, LCD, pos );
 * @endcode
 */
#define hw_newline__hd44780					, _hw_hd44780_newline
#define _hw_hd44780_newline(o,lines,cols,e,rs,rw,d,pos,...)	_hw_##o##_newline(pos)


/**
 * @page hd44780
 *
 * `home`: move the cursor to the home position.
 * @code
 * hw( home, LCD );
 * @endcode
 */
#define hw_home__hd44780					, _hw_hd44780_home
#define _hw_hd44780_home(o,...)					_hw_##o##_home()


/**
 * @page hd44780
 *
 * `putchar`: write a character at the current position.
 * @code
 * hw( putchar, LCD, c );
 * @endcode
 */
#define hw_putchar__hd44780					, _hw_hd44780_putchar
#define _hw_hd44780_putchar(o,lines,cols,e,rs,rw,d,ch,...)	_hw_##o##_putchar(ch)
