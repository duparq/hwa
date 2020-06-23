
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
 * __Constructor__
 *
 * Currently, HWA supports only the driving of the HD44780 in 4-bit mode through
 * a single dedicated I²C bus expander @ref pcf8574 "PCF8574".
 *
 * @code
 * #define PCF		HW_PCF8574( interface, twi0, address, 0x27 )
 *
 * #define LCD		HW_HD44780( lines, 2,		\
 *				    cols,  16,		\
 *				    e,	   (PCF, 1, 2),	\
 *				    rs,	   (PCF, 1, 0),	\
 *				    rw,	   (PCF, 1, 1),	\
 *				    data,  (PCF, 4, 4) )
 * @endcode
 */
#define hw_class__hd44780

#define HW_HD44780(...)				_HW_HD44780_(__VA_ARGS__,,,,,,,,,,)
#define _HW_HD44780_(k,...)			HW_BW(_HW_HD44780_1,lines,k)(k,__VA_ARGS__)
#define _HW_HD44780_10(k,...)			_HW_HD44780_E(k,__VA_ARGS__)
#define _HW_HD44780_11(k0,l,k,...)		HW_BW(_HW_HD44780_2,cols,k)(l,k,__VA_ARGS__)
#define _HW_HD44780_20(l,k,...)			_HW_HD44780_E(k,__VA_ARGS__)
#define _HW_HD44780_21(l,k0,c,k,...)		HW_BW(_HW_HD44780_3,e,k)(l,c,k,__VA_ARGS__)
#define _HW_HD44780_30(l,c,k,...)		_HW_HD44780_E(k,__VA_ARGS__)
#define _HW_HD44780_31(l,c,k,...)		_HW_HD44780_32(l,c,HW_AD(__VA_ARGS__))
#define _HW_HD44780_32(...)			_HW_HD44780_33(__VA_ARGS__)
#define _HW_HD44780_33(l,c,e,...)		_HW_B(_HW_HD44780_33,HW_A0 e)(l,c,e,__VA_ARGS__)
#define _HW_HD44780_331(l,c,e,...)		,HW_HD44780(...),(HW_HD44780(...): HW_A2 e)
#define _HW_HD44780_330(l,c,e,k,...)		HW_BW(_HW_HD44780_4,rs,k)(l,c,e,k,__VA_ARGS__)
#define _HW_HD44780_40(l,c,e,k,...)		_HW_HD44780_E(k,__VA_ARGS__)
#define _HW_HD44780_41(l,c,e,k,...)		_HW_HD44780_42(l,c,e,HW_AD(__VA_ARGS__))
#define _HW_HD44780_42(...)			_HW_HD44780_43(__VA_ARGS__)
#define _HW_HD44780_43(l,c,e,s,...)		_HW_B(_HW_HD44780_43,HW_A0 s)(l,c,e,s,__VA_ARGS__)
#define _HW_HD44780_431(l,c,e,s,...)		,HW_HD44780(...),(HW_HD44780(...): HW_A2 s)
#define _HW_HD44780_430(l,c,e,s,k,...)		HW_BW(_HW_HD44780_5,rw,k)(l,c,e,s,k,__VA_ARGS__)
#define _HW_HD44780_50(l,c,e,s,k,...)		_HW_HD44780_E(k,__VA_ARGS__)
#define _HW_HD44780_51(l,c,e,s,k,...)		_HW_HD44780_52(l,c,e,s,HW_AD(__VA_ARGS__))
#define _HW_HD44780_52(...)			_HW_HD44780_53(__VA_ARGS__)
#define _HW_HD44780_53(l,c,e,s,w,...)		_HW_B(_HW_HD44780_53,HW_A0 w)(l,c,e,s,w,__VA_ARGS__)
#define _HW_HD44780_531(l,c,e,s,w,...)		,HW_HD44780(...),(HW_HD44780(...): HW_A2 w)
#define _HW_HD44780_530(l,c,e,s,w,k,...)	HW_BW(_HW_HD44780_6,data,k)(l,c,e,s,w,k,__VA_ARGS__)
#define _HW_HD44780_60(l,c,e,s,w,k,...)		_HW_HD44780_E(k,__VA_ARGS__)
#define _HW_HD44780_61(l,c,e,s,w,k,...)		_HW_HD44780_62(l,c,e,s,w,HW_AD(__VA_ARGS__))
#define _HW_HD44780_62(...)			_HW_HD44780_63(__VA_ARGS__)
#define _HW_HD44780_63(l,c,e,s,w,d,...)		_HW_B(_HW_HD44780_63,HW_A0 d)(l,c,e,s,w,d,__VA_ARGS__)
#define _HW_HD44780_631(l,c,e,s,w,d,...)	,HW_HD44780(...),(HW_HD44780(...): HW_A2 d)
#define _HW_HD44780_630(l,c,e,s,w,d,g,...)	HW_B(_HW_HD44780_7,g)(l,c,e,s,w,d,g,__VA_ARGS__)
#define _HW_HD44780_70(x,...)			HW_E_G(x)

/*  Verify that e is of class _io8574
 */
#define _HW_HD44780_71(l,c,e,s,w,d,...)		_HW_HD44780_72(HW_A0_A1 e, HW_A2 d, l,c,e,s,w,d)
#define _HW_HD44780_72(...)			_HW_HD44780_73(__VA_ARGS__)
#define _HW_HD44780_73(ec,eo,df,...)		HW_BW(_HW_HD44780_73,_io8574,ec)(ec,eo,HW_A0 df,__VA_ARGS__)
#define _HW_HD44780_730(ec,...)			,HW_HD44780(...),HW_HD44780(...): class ec for "e" is not supported
#define _HW_HD44780_731(ec,eo,...)		_hd44780,hd44780_##eo,(ec,__VA_ARGS__)

#define _HW_HD44780_E(k,...)						\
  ,HW_HD44780(...),(HW_EM_S("HW_HD44780(lines,..., cols,..., e,..., rs,..., rw,..., data,...)"))

#define _hw_is__io8574__io8574			, 1


/**
 * @page hd44780
 *
 * `HW_DCLARE()` declares the functions that implement the object:
 *
 * @code
 * HW_DECLARE(LCD);
 * @endcode
 */
#define HW_DECLARE__hd44780		, _hw_dchd44780

#define _hw_dchd44780(o,ec,dw,...)				\
  void _hw_##o##ec##_##dw##__pulse ( );				\
  void _hw_##o##ec##_##dw##__write ( uint8_t, uint8_t );	\
  uint8_t _hw_##o##ec##_##dw##__read ( uint8_t );		\
  uint8_t _hw_##o##__wait ( );					\
  void _hw_##o##__command ( uint8_t );				\
  void _hw_##o##__data ( uint8_t );				\
  void _hw_##o##_clear_cgram ( );				\
  void _hw_##o##_cls ( );					\
  void _hw_##o##ec##_##dw##_init ( );				\
  void _hw_##o##_gotoxy ( uint8_t, uint8_t );			\
  void _hw_##o##_newline( uint8_t );				\
  void _hw_##o##_home ( );					\
  void _hw_##o##_putchar( unsigned char ) /* require a ; */


/**
 * @page hd44780
 *
 * `HW_IMPLEMENT()` defines the functions that implement the object:
 *
 * @code
 * HW_IMPLEMENT(LCD);
 * @endcode
 */
#define HW_IMPLEMENT__hd44780		, _hw_dfhd44780

#define _hw_dfhd44780(o,ec,dw,...)			\
  _hw_dfhd44780_io8574_4__pulse(o,__VA_ARGS__)		\
    _hw_dfhd44780_io8574_4__write(o,__VA_ARGS__)	\
    _hw_dfhd44780_io8574_4__read(o,__VA_ARGS__)		\
    _hw_dfhd44780__wait(o,__VA_ARGS__)			\
    _hw_dfhd44780__command(o,__VA_ARGS__)		\
    _hw_dfhd44780__data(o,__VA_ARGS__)			\
    _hw_dfhd44780_cls(o,__VA_ARGS__)			\
    _hw_dfhd44780_io8574_4_init(o,__VA_ARGS__)		\
    _hw_dfhd44780_gotoxy(o,__VA_ARGS__)			\
    _hw_dfhd44780_newline(o,__VA_ARGS__)		\
    _hw_dfhd44780_home(o,__VA_ARGS__)			\
    _hw_dfhd44780_putchar(o,__VA_ARGS__)		\
    HW_FOO() /* for semicolon */

/*  FIXME: 'hw(pulse,e)' could spare a few bytes by not updating the data cache
 *  of PCF.
 */
#define _hw_dfhd44780_io8574_4__pulse(o,lines,cols,e,...)	\
  void _hw_##o##__pulse ( ) {					\
    hw(write, e, 1);						\
    hw(write, e, 0);						\
  }

/* #define _hwa_dfhd44780_io8574_4__pulse(o,lines,cols,e,...)	\ */
/*   void _hwa_##o##__pulse ( ) {				\ */
/*     hwa(write, e, 1);					\ */
/*     _hwa( commit, (e,port) );				\ */
/*     hwa(write, e, 0);					\ */
/*     _hwa( commit, (e,port) );				\ */
/*   } */

/*  Access for writing:
 *   * RS and RW must be stable >40 ns before rising of E
 *   * E must be stable high for >230 ns
 *   * D must be stable >80 ns before falling of E and >10 ns after falling of E
 *   * period of E must be >500 ns
 */
#define _hw_dfhd44780_io8574_4__write(o,lines,cols,e,rs,rw,d,...)	\
  void _hw_##o##__write ( uint8_t data, uint8_t r ) {		\
    _hw_##o##__wait();						\
    hw( writea, rs, r );					\
    hw( writea, rw, 0 );					\
    hw( writea, d, data>>4 );					\
    hw( commit, (e,port) );					\
    _hw_##o##__pulse();						\
    hw( write, d, data&15 );					\
    _hw_##o##__pulse();						\
  }

/* #define _hw_dfhd44780_io8574_4__write(o,lines,cols,e,rs,rw,d,...)	\ */
/*   void _hw_##o##__write ( uint8_t data, uint8_t r )	{	\ */
/*     _hw_##o##__wait();						\ */
/*     _hwa( begin, (rs,port) );					\ */
/*     _hwa( begin, (rw,port) );					\ */
/*     _hwa( begin, (d,port) );					\ */
/*     _hwa( begin, (e,port) );					\ */
/*     _hwa( write, rs, r );					\ */
/*     _hwa( write, rw, 0 );					\ */
/*     _hwa( commit, (rs,port) );					\ */
/*     _hwa( commit, (rw,port) );					\ */
/*     _hwa( write, e, 1 );					\ */
/*     _hwa( commit, (e,port) );					\ */
/*     _hwa( write, d, data>>4 );					\ */
/*     _hwa( commit, (d,port) );					\ */
/*     _hwa( write, e, 0 );					\ */
/*     _hwa( commit, (e,port) );					\ */
/*     _hwa( write, e, 1 );					\ */
/*     _hwa( commit, (e,port) );					\ */
/*     _hwa( write, d, data&0x0F );				\ */
/*     _hwa( commit, (d,port) );					\ */
/*     _hwa( write, e, 0 );					\ */
/*     _hwa( commit, (e,port) );					\ */
/*     _hwa( write, d, 15 );					\ */
/*     _hwa( commit, (d,port) );					\ */
/*   } */

#define _hw_dfhd44780_io8574_4__read(o,lines,cols,e,rs,rw,d,...)			\
  uint8_t _hw_##o##__read ( uint8_t r ) {				\
    hw( writea, rs, r );						\
    hw( writea, rw, 1 );						\
    hw( writea, d, 0x0F );						\
    hw( commit, (e,port) );						\
    _hw( write, e, 1 );							\
    uint8_t hi = _hw( read, d );					\
    _hw( write, e, 0 );							\
    _hw( write, e, 1 );							\
    hw_waste_cycles( 100e-6 * HW_SYSHZ );/*FIXME: can't have it working without this delay?*/ \
    uint8_t lo = _hw( read, d );					\
    _hw( write, e, 0 );							\
    return (hi<<4)|lo ;							\
  }

/* #define _hw_dfhd44780_io8574_4__read(o,lines,cols,e,rs,rw,d,...)			\ */
/*   uint8_t _hw_##o##__read ( uint8_t r ) {				\ */
/*   _hwa( begin, (rs,port) );						\ */
/*   _hwa( begin, (rw,port) );						\ */
/*   _hwa( begin, (d,port) );						\ */
/*   _hwa( begin, (e,port) );						\ */
/*   _hwa( write, rs, 1 );							\ */
/*   _hwa( write, rw, 1 );							\ */
/*   _hwa( commit, (rs,port) );						\ */
/*   _hwa( commit, (rw,port) );						\ */
/*   _hwa( write, e, 1 );							\ */
/*   _hwa( commit, (e,port) );						\ */
/*   uint8_t hi = _hw( read, d );						\ */
/*   _hwa( write, e, 0 );							\ */
/*   _hwa( commit, (e,port) );						\ */
/*   _hwa( write, e, 1 );							\ */
/*   _hwa( commit, (e,port) );						\ */
/*   hw_waste_cycles( 100e-6 * HW_SYSHZ );/\*FIXME: can't have it working without this delay?*\/ \ */
/*   uint8_t lo = _hw( read, d );						\ */
/*   _hwa( write, e, 0 );							\ */
/*   _hwa( commit, (e,port) );						\ */
/*   return (hi<<4)|lo ;							\ */
/*   } */


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

#define _hw_dfhd44780_io8574_4_init(o,lines,cols,e,rs,rw,d,...)		HW_EOL(__VA_ARGS__) \
  void _hw_##o##_init ( ) {						\
    if ( lines < 1 || lines > 2 ) {					\
      HWA_E(HW_EM(parameter "lines" must be 1 or 2));			\
      return ;								\
    }									\
    uint8_t bits = 4 ;							\
    uint16_t font = 58 ;						\
    hw( writea, e, 0 );							\
    hw( writea, rs, 0 );						\
    hw( writea, rw, 0 );						\
    hw( writea, d, 0 );							\
    hw_waste_cycles( 0.015 * HW_SYSHZ );				\
    hw( write, d, 3 );			/* initial write 8bit */	\
    _hw_##o##__pulse();							\
    hw_waste_cycles( 0.0041 * HW_SYSHZ );				\
    _hw_##o##__pulse();			/* repeat last command */	\
    hw_waste_cycles( 100e-6 * HW_SYSHZ );				\
    _hw_##o##__pulse();			/* repeat last command */	\
    if ( bits == 4 )							\
      hw( write, d, 2 );						\
    _hw_##o##__pulse();							\
    uint8_t val = (bits==4)*0x20 + (lines==2)*0x08 + (font==58)*0x04;	\
    _hw_##o##__command( val );						\
    _hw_##o##__command( 0x0C ); /* Display on, no cursor, no blink */	\
    _hw_##o##_cls( );							\
  }

    /* _hw_##o##__command( 0x08 ); /\* Display off, no cursor, no blink *\/	\ */
    /* _hw_##o##__command( 0x06 ); /\* Entry mode: inc, no shift *\/		\ */
    /* _hw_##o##__command( 0x0C ); /\* Display on, no cursor, no blink *\/	\ */

/* #define _hw_dfhd44780_io8574_4_init(o,lines,cols,e,rs,rw,d,...)			\ */
/*   void _hw_##o##_init ( ) {						\ */
/*     _hwa( begin, (rs,port) );						\ */
/*     _hwa( begin, (rw,port) );						\ */
/*     _hwa( begin, (d,port) );						\ */
/*     _hwa( begin, (e,port) );						\ */
/*     _hwa( write, rs, r );						\ */
/*     _hwa( write, rw, 0 );						\ */
/*     _hwa( write, d, 0 );						\ */
/*     _hwa( write, e, 0 );						\ */
/*     _hwa( commit, (rs,port) );						\ */
/*     _hwa( commit, (rw,port) );						\ */
/*     _hwa( commit, (d,port) );						\ */
/*     _hwa( commit, (e,port) );						\ */
/*     hw_waste_cycles( 0.015 * HW_SYSHZ );				\ */
/*     _hwa( write, d, 3 );	/\* initial write 8bit *\/		\ */
/*     _hwa( commit, (d,port) );						\ */
/*     _hwa_##o##__pulse();						\ */
/*     hw_waste_cycles( 0.0041 * HW_SYSHZ );				\ */
/*     _hw_##o##__pulse();			/\* repeat last command *\/	\ */
/*     hw_waste_cycles( 64e-6 * HW_SYSHZ );				\ */
/*     _hw_##o##__pulse();			/\* repeat last command *\/	\ */
/*     hw_waste_cycles( 64e-6 * HW_SYSHZ );				\ */
/*     hw( write, d, 2 );	/\* configure for 4bit *\/			\ */
/*     _hw_##o##__pulse();							\ */
/*     hw_waste_cycles( 64e-6 * HW_SYSHZ );				\ */
/*     uint8_t rv = 0x20 ;	/\* 4-bit, 1 line, 5x8 font *\/			\ */
/*     if ( lines == 2 )							\ */
/*       rv |= 0x08 ;							\ */
/*     _hw_##o##__command( rv ); /\* 4-bit, 2 lines, 5x8 font *\/		\ */
/*     _hw_##o##__command( 0x08 ); /\* Display off, no cursor, no blink *\/	\ */
/*     _hw_##o##_cls( );							\ */
/*     _hw_##o##__command( 0x06 ); /\* Entry mode: inc, no shift *\/		\ */
/*     _hw_##o##__command( 0x0C ); /\* Display on, no cursor, no blink *\/	\ */
/*   } */


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


/**
 * @page hd44780
 * __Relatives__
 *
 * The relative `putchar` gives the name of the putchar function associated to the LCD.
 *
 * @code
 * HW(LCD,putchar)('x');	//  Write 'x' on the LCD using its putchar function
 * @endcode
 *
 * @code
 * myprintf( HW(LCD,putchar), "ADC=%03d\n", hw(read,adc0));
 * @endcode
 */
#define hw__hd44780_putchar		, _hw_hd44780putchar
#define _hw_hd44780putchar(o,...)	_hw_##o##_##putchar


/**
 * @page hd44780
 * __Actions__
 *
 * `configure`
 *
 * @code
 * hw(   configure, LCD,
 *
 *     [ init,      yes | no, ]		// Initialize (no)
 *
 *     [ display,   on | off,		// Text visibility (on)
 *       cursor,    on | off,		// '_' visibility (off)
 *       blink,     on | off, ]		// Blinking block (off)
 *
 *     [ shift,     cursor | display,	//
 *       direction, left | right ]	//
 *    );
 * @endcode
 */
#define hw_configure__hd44780		, _hw_cfhd44780

#define _hw_cfhd44780(o,ec,dw,lines,cols,e,rs,rw,d,...)		\
  do{								\
    uint8_t init=0 ;						\
    uint8_t display=0xFF ;					\
    uint8_t cursor=0xFF ;					\
    uint8_t blink=0xFF ;					\
    uint8_t shift=0xFF ;					\
    uint8_t direction=0xFF ;					\
    _hw_cfhd44780_(__VA_ARGS__,);				\
    uint8_t val ;						\
    								\
    if ( init == 1 )						\
      _hw_##o##_init();						\
    								\
    if ( display != 0xFF ) {					\
      val = 8 + (display==1)*4 + (cursor==1)*2 + (blink==1)*1;	\
      _hw_##o##__command( val );				\
    }								\
    								\
    if ( shift != 0xFF ) {					\
      val = 16 + (shift==1)*8 + (direction==1)*4;		\
      _hw_##o##__command( val );				\
    }								\
  }while(0)

#define _hw_is_init_init		, 1
#define _hw_is_display_display		, 1
#define _hw_is_cursor_cursor		, 1
#define _hw_is_blink_blink		, 1
#define _hw_is_shift_shift		, 1
#define _hw_hd44780_shift_cursor	, 0
#define _hw_hd44780_shift_display	, 1
#define _hw_hd44780_direction_left	, 0
#define _hw_hd44780_direction_right	, 1

#define _hw_cfhd44780_(k,...)		HW_BW(_hw_cfhd44780_ini,init,k)(k,__VA_ARGS__)
#define _hw_cfhd44780_ini0(k,...)	HW_BW(_hw_cfhd44780_dis1,display,k)(k,__VA_ARGS__)
#define _hw_cfhd44780_ini1(k,v,...)	HW_BV(_hw_cfhd44780_ini2,_hw_state_,v)(__VA_ARGS__)
#define _hw_cfhd44780_ini20(v)		HW_E(HW_EM_ST(v)) HW_EAT
#define _hw_cfhd44780_ini21(v)		init=v; _hw_cfhd44780_dis

#define _hw_cfhd44780_dis(k,...)	HW_BW(_hw_cfhd44780_dis1,display,k)(k,__VA_ARGS__)
#define _hw_cfhd44780_dis10(k,...)	HW_BW(_hw_cfhd44780_shf1,shift,k)(k,__VA_ARGS__)
#define _hw_cfhd44780_dis11(k,v,...)	HW_BV(_hw_cfhd44780_dis2,_hw_state_,v)(__VA_ARGS__)
#define _hw_cfhd44780_dis20(v)		HW_E(HW_EM_ST(v)) HW_EAT
#define _hw_cfhd44780_dis21(v)		display=v; _hw_cfhd44780_cur

#define _hw_cfhd44780_cur(k,...)	HW_BW(_hw_cfhd44780_cur1,cursor,k)(k,__VA_ARGS__)
#define _hw_cfhd44780_cur10(k,...)	HW_E(HW_EM_KX(cursor,k))
#define _hw_cfhd44780_cur11(k,v,...)	HW_BV(_hw_cfhd44780_cur2,_hw_state_,v)(__VA_ARGS__)
#define _hw_cfhd44780_cur20(v)		HW_E(HW_EM_ST(v)) HW_EAT
#define _hw_cfhd44780_cur21(v)		cursor=v; _hw_cfhd44780_blk

#define _hw_cfhd44780_blk(k,...)	HW_BW(_hw_cfhd44780_blk1,blink,k)(k,__VA_ARGS__)
#define _hw_cfhd44780_blk10(k,...)	HW_E(HW_EM_KX(blink,k))
#define _hw_cfhd44780_blk11(k,v,...)	HW_BV(_hw_cfhd44780_blk2,_hw_state_,v)(__VA_ARGS__)
#define _hw_cfhd44780_blk20(v)		HW_E(HW_EM_ST(v)) HW_EAT
#define _hw_cfhd44780_blk21(v)		blink=v; _hw_cfhd44780_shf

#define _hw_cfhd44780_shf(k,...)	HW_BW(_hw_cfhd44780_shf1,shift,k)(k,__VA_ARGS__)
#define _hw_cfhd44780_shf10(k,...)	HW_B(_hw_cfhd44780_shf2,k)(k,__VA_ARGS__)
#define _hw_cfhd44780_shf21(...)	HW_EOL(__VA_ARGS__)
#define _hw_cfhd44780_shf20(k,...)	HW_E(HW_EM_XNIL(k,(init,display,shift)))
#define _hw_cfhd44780_shf11(k,v,...)	HW_BV(_hw_cfhd44780_shf3,_hw_hd44780_shift_,v)(__VA_ARGS__)
#define _hw_cfhd44780_shf30(v)		HW_E(HW_EM_XNIL(v,(cursor,display))) HW_EAT
#define _hw_cfhd44780_shf31(v)		shift=v; _hw_cfhd44780_drn

#define _hw_cfhd44780_drn(k,...)	HW_BW(_hw_cfhd44780_drn1,direction,k)(k,__VA_ARGS__)
#define _hw_cfhd44780_drn10(k,...)	HW_E_KX(direction,k)
#define _hw_cfhd44780_drn11(k,v,...)	HW_BV(_hw_cfhd44780_drn2,_hw_hd44780_direction_,v)(__VA_ARGS__)
#define _hw_cfhd44780_drn20(v)		HW_E(HW_EM_XNIL(v,(left,right))) HW_EAT
#define _hw_cfhd44780_drn21(v)		direction=v; HW_EOL /*__VA_ARGS__*/


/**
 * @page hd44780
 *
 * `cls`: clear screen.
 * @code
 * hw( cls, LCD );
 * @endcode
 */
#define hw_cls__hd44780			, _hw_hd44780_cls
#define _hw_hd44780_cls(o,ec,dw,...)	_hw_##o##_cls()


/**
 * @page hd44780
 *
 * `gotoxy`: move the cursor to column x, line y.
 * @code
 * hw( gotoxy, LCD, x, y );
 * @endcode
 */
#define hw_gotoxy__hd44780						, _hw_hd44780_gotoxy
#define _hw_hd44780_gotoxy(o,ec,dw,lines,cols,e,rs,rw,d,x,y,...)	_hw_##o##_gotoxy(x,y)


/**
 * @page hd44780
 *
 * `newline`: move the cursor to the start of the next line.
 * @code
 * hw( newline, LCD, pos );
 * @endcode
 */
#define hw_newline__hd44780						, _hw_hd44780_newline
#define _hw_hd44780_newline(o,ec,dw,lines,cols,e,rs,rw,d,pos,...)	_hw_##o##_newline(pos)


/**
 * @page hd44780
 *
 * `home`: move the cursor to the home position.
 * @code
 * hw( home, LCD );
 * @endcode
 */
#define hw_home__hd44780						, _hw_hd44780_home
#define _hw_hd44780_home(o,...)						_hw_##o##_home()


/**
 * @page hd44780
 *
 * `putchar`: write a character at the current position.
 * @code
 * hw( putchar, LCD, c );
 * @endcode
 */
#define hw_putchar__hd44780						, _hw_hd44780_putchar
#define _hw_hd44780_putchar(o,ec,dw,lines,cols,e,rs,rw,d,ch,...)	_hw_##o##_putchar(ch)
