
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief General purpose macro definitions usable in C or assembler source code.
 */


/*
 * @ingroup private_mac
 * @brief Element a0 of the list a0,...
 * @hideinitializer
 */
#define HW_A0(...)			_HW_A0_2(__VA_ARGS__,)
#define _HW_A0_2(a0,...)		a0

#define HW_A0_A1(...)			_HW_A0_A1_2(__VA_ARGS__,,)
#define _HW_A0_A1_2(a0,a1,...)		a0,a1

#define HW_T4(...)			_HW_T4(__VA_ARGS__,,,,)
#define _HW_T4(a0,a1,a2,a3,...)		__VA_ARGS__


/*
 * @ingroup private_mac
 * @brief Element a1 of the list a0,a1,...
 * @hideinitializer
 */
#define HW_A1(...)				_HW_A1_2(__VA_ARGS__,,)
#define _HW_A1_2(a0,a1,...)			a1

#define HW_A2(...)				_HW_A2_2(__VA_ARGS__,,,)
#define _HW_A2_2(a0,a1,a2,...)			a2

#define HW_A3(...)				_HW_A3_2(__VA_ARGS__,,,,)
#define _HW_A3_2(a0,a1,a2,a3,...)		a3

#define HW_A4(...)				HW_A0(HW_T4(__VA_ARGS__))
#define HW_A5(...)				HW_A1(HW_T4(__VA_ARGS__))
#define HW_A6(...)				HW_A2(HW_T4(__VA_ARGS__))
#define HW_A7(...)				HW_A3(HW_T4(__VA_ARGS__))

#define HW_A8(...)				HW_A0(HW_T4(HW_T4(__VA_ARGS__)))
#define HW_A9(...)				HW_A1(HW_T4(HW_T4(__VA_ARGS__)))
#define HW_A10(...)				HW_A2(HW_T4(HW_T4(__VA_ARGS__)))
#define HW_A11(...)				HW_A3(HW_T4(HW_T4(__VA_ARGS__)))


/*  Replace the definition of an object by its name in the beginning of a list.
 *
 *    This is used by functions that accept HWA-built objects as arguments, such
 *    as HW_SWTWIMASTER. The functions get the definition instead of the object
 *    name.
 */
#define HW_ANAME(x,...)			HW_Y0(_HW_ANAME1_,_hw_islb x)(x,__VA_ARGS__)
#define _HW_ANAME1_1(...)		HW_E(HW_EM_TBI)
#define _HW_ANAME1_0(x,...)		HW_Y0(_HW_ANAME2_,hw_class_##x)(x,__VA_ARGS__)
#define _HW_ANAME2_1(c,o,d,...)		o,__VA_ARGS__
#define _HW_ANAME2_0(...)		__VA_ARGS__


#define HW_D3(...)			_HW_D3(__VA_ARGS__)
#define _HW_D3(c,o,...)			c,o,(__VA_ARGS__)


/*  Reduce the definition of the object in first position to one single
 *  bracketted element.
 */
#define HW_AD(x,...)			HW_Y0(_HW_AD1,_hw_islb x)(x,__VA_ARGS__)
#define _HW_AD11(...)			HW_E_TBI()
#define _HW_AD10(x,...)			HW_Y0(_HW_AD2,hw_class_##x)(x,__VA_ARGS__)
#define _HW_AD21(c,o,d,...)		(c,o,d),__VA_ARGS__
//#define _HW_AD20(x,...)			(HW_X(x)),__VA_ARGS__
#define _HW_AD20(x,...)			(HW_D3(HW_X(x))),__VA_ARGS__

/**
 * @ingroup public_mac
 * @brief `HW_ADDRESS(object)` returns the address of the @ref using_objects "object".
 * @hideinitializer
 *
 */
/* #define HW_ADDRESS(...)			_HW_ADDRESS2(__VA_ARGS__,,) */
/* #define _HW_ADDRESS2(x,...)		HW_Y(_HW_ADDRESS,__VA_ARGS__)(x,__VA_ARGS__) */
/* #define _HW_ADDRESS0(x,y,...)		HW_E_G(y) */
/* #define _HW_ADDRESS1(x,...)		HW_F( HW_ADDRESS, x ) */

#define HW_ADDRESS(...)			HW_F( HW_ADDRESS, __VA_ARGS__ )

#define HW_ADDRESS_E(...)		-1	// Error

/*  Address correction
 *    C and assembly addresses are offset by 0x20 bytes with avr-gcc (or avrlibc?)
 */
#if !defined HW_AC
#  define HW_AC
#endif

#define HW_ADDRESS__m111		, _hw_address_m111
#define _hw_address_m111(n,o,r,c,a,...)	(a HW_AC)

#define HW_ADDRESS__m1			, _hw_address_m1
#define _hw_address_m1(n,o,r,c,a,...)	(a HW_AC)

#define HW_ADDRESS_			, _hw_address_		// By default
#define _hw_address_(o,a,...)		a


/**
 * @ingroup public_mac
 * @brief `HW_AP(logical_register)` returns the pair address,position of a logical register.
 *
 * This is useful for assembly programming, for example with the SBI / CBI instructions.
 *
 * @hideinitializer
 *
 */
#define HW_AP(...)			HW_F( HW_AP, __VA_ARGS__ )
#define HW_AP_E(...)			0 // An error occured

#define HW_AP__m111				, _hw_ap_m111
#define _hw_ap_m111(n,o,r,c,a,wm,fm,bn,bp,...)	(a HW_AC), bp


/**
 * @ingroup public_mac
 * @brief `HW_BITS(object)` returns the number of bits of the @ref using_objects "object".
 * @hideinitializer
 *
 * The object may be an I/O definition, a register, a counter...
 *
 * @code
 * #if HW_BITS(counter0) != 16
 * # error You must chose a 16-bit counter
 * #endif
 * @endcode
 */
#define HW_BITS(...)			HW_F( HW_BITS, __VA_ARGS__ )
#define HW_BITS_E(...)			0


/* @brief Trigger an error at preprocessing stage
 * @hideinitializer
 *
 * Error handling is based on the C99 _Pragma operator. It produces a
 * preprocessing error as soon as the _Pragma(...) sentence is emitted, be it
 * inside or outside of a C function definition, or in an assembler
 * source.
 *
 * The error message 's' must be a single argument, i.e. it must not contain
 * commas.
 *
 * @note _Pragma(...) can not be processed by macros as the sentence is removed
 * from the preprocessor output and replaced by a void token.
 */
#define HW_E(s)			_HW_E2(GCC error HW_QUOTE(HWA: s.))
#define _HW_E2(s)		_HW_E3(s)
#if !defined HW_XE
#  define _HW_E3(s)		_Pragma(#s)
#else
#  define _HW_E3(s)		_xPragma(#s)
#endif

#define HW_EM_C(c)		HW_Q(c) is not a class
#define HW_EM_CM(c,m)		class HW_Q(c) has no method HW_Q(m)
#define HW_EM_F(f)		`f`: unknown function
#define HW_EM_G(x)		garbage starting at HW_Q(x)
#define HW_EM_GA(x)		garbage after HW_Q(x)
#define HW_EM_IA(a)		HW_Q(a): invalid argument
#define HW_EM_IRQ(n)		HW_Q(n) is not an IRQ
#define HW_EM_KX(k,x)		expected HW_Q(k) instead of HW_Q(x)
#define HW_EM_NKX(n,k,x)	expected HW_Q(k) instead of HW_Q(x) in HW_Q(n)
#define HW_EM_O(x)		HW_Q(x) is not an object
#define HW_EM_OM()		HW_Q(missing object name)
#define HW_EM_ONAP(x)		HW_Q(x) is not a pin name
#define HW_EM_OO(o,x)		HW_Q(o) has no relative named HW_Q(x)
#define HW_EM_S(s)		syntax is s
#define HW_EM_TL(l)		try one of l

#define HW_E_AVL(a,v,l)		HW_E(HW_Q(a) can be HW_Q(l) but not HW_Q(v))
#define HW_E_AVM(a)		HW_E(missing value for HW_Q(a))
#define HW_E_CM(c,m)		HW_E(class HW_Q(c) has no method HW_Q(m))
#define HW_E_G(x)		HW_E(garbage starting at HW_Q(x))
#define HW_E_IMP(f)		HW_E(HW_Q(f): not implemented for this target)
#define HW_E_IOFN(o,a,v,l)	HW_E(HW_Q(o): HW_Q(a) can be HW_Q(l) but not HW_Q(v))
#define HW_E_IRQ(n)		HW_E(HW_Q(n) is not an IRQ)
#define HW_E_K(k,x)		HW_E(expected HW_Q(k) instead of HW_Q(x))
#define HW_E_KVNIY(k,v)		HW_E(HW_Q(k=v) is not implemented yet)
#define HW_E_KW(w)		HW_E(HW_Q(w) is not an argument name)
#define HW_E_KX(k,x)		HW_E(expected HW_Q(k) instead of HW_Q(x))
#define HW_E_M(m)		HW_E(unknown method HW_Q(m))
#define HW_E_MA(w)		HW_E(missing argument HW_Q(w))
#define HW_E_ML(l)		HW_E(expected one argument in HW_Q(l))
#define HW_E_NIL(v,l)		HW_E(HW_Q(v) is not in l)
#define HW_E_O(x)		HW_E(HW_Q(x) is not an object)
#define HW_E_OAVL(a,v,l)	HW_E(optionnal parameter HW_Q(a) can be HW_Q(l) but not HW_Q(v))
#define HW_E_OCM(o,c,m)		HW_Y(_HW_EOCM_,c)(o,c,m)
#define HW_E_OKMV(k,v,l)	HW_E(value of optionnal parameter HW_Q(k) must be HW_Q(l) not HW_Q(v))
#define HW_E_OKVL(k,v,l)	HW_E(value HW_Q(v) for optionnal parameter HW_Q(k) is not in l)
#define HW_E_OM()		HW_E(missing object name)
#define HW_E_OO(o,x)		HW_E(object HW_Q(o) has no relative named HW_Q(x))
#define HW_E_P(x)		HW_E(HW_Q(x) is not a pin)
#define HW_E_ST(x)		HW_E(HW_Q(x) is not in (0,1,on,off,yes,no))
#define HW_E_T(x)		HW_E(unrecognized token HW_Q(x))
#define HW_E_TBI(...)		HW_E(instruction is not implemented yet)
#define HW_E_TBIKV(k,v)		HW_E(k HW_Q(v) is not implemented yet)
#define HW_E_V()		HW_E(missing value)
#define HW_E_VL(v,l)		HW_E(HW_Q(v) is not HW_Q(l))

#define _HW_EOCM_0(o,c,m)	HW_E(object HW_Q(o) of class HW_Q(c) has no method named HW_Q(m))
#define _HW_EOCM_1(...)


/*
 * @ingroup private_mac
 * @brief Trigger an error if the first argument is not void.
 * @hideinitializer
 *
 * This is used to ensure that there is no remaining elements in a list at the
 * end of its parsing.
 */
#define HW_EOL(...)			HW_Y(_HW_EOL_,__VA_ARGS__)(__VA_ARGS__,)
#define _HW_EOL_0(g,...)		HW_E_G(g)
#define _HW_EOL_1(...)


/*  This is used to catch pushed data
 */
#define HW_POP(...)


/*
 * @ingroup public_ins_obj
 * @brief Find a function f for object o and call it.
 *
 * Call f_E(e) with an error message if an error occurs. It's up to f_E to produce an error (or not).
 *
 * The method is searched in this order:
 *  1. f_c
 *  2. f_o
 *  3. f
 *
 * The definition of the object is pushed away with the arguments of the method.
 *
 * @hideinitializer
 */
#define HW_F(...)			_HW_F(__VA_ARGS__,)
#define _HW_F(f,x,...)		        HW_Y0(_HW_F_,_hw_islb x)(f,x,__VA_ARGS__)
/*
 *  x is not (...)
 */
#define _HW_F_0(f,x,...)	        HW_Y0(_HW_F_0_,hw_class_##x)(f,x,__VA_ARGS__)
/*
 *  x is a class name
 */
#define _HW_F_0_1(f,x,o,d,...)	        _HW_F01(f,x,o,HW_XB d,__VA_ARGS__)
/*
 *  x is not a class name
 */
#define _HW_F_0_0(f,x,...)	        HW_Y0(_HW_F00_,x)(f,x,__VA_ARGS__)
/*
 *  x is void (error message or void)
 */
#define _HW_F00_1(...)		  	_HW_F00_2(__VA_ARGS__,,,,)
#define _HW_F00_2(f,z,o,e,...)	  	HW_Y0(_HW_F00_2,o)(f,z,o,__VA_ARGS__)
#define _HW_F00_21(f,z,o,e,...)	  	f##_E(HW_EM_OM())
#define _HW_F00_20(f,z,o,e,...)	  	f##_E(e)
/*
 *  x is not void
 */
#define _HW_F00_0(f,x,...)	  	_HW_F00(f, HW_X(x),__VA_ARGS__)
/*
 *  x is (...)
 */
#define _HW_F_1(f,x,...)		_HW_F00(f, HW_X x,__VA_ARGS__)
#define _HW_F00(...)			_HW_F01(__VA_ARGS__)
/*
 *  Got object definition in c,o,...
 */
#define _HW_F01(f,c,o,...)		HW_Y0(_HW_F01_,c)(f,c,o) /* Arguments pushed --> */ (o,__VA_ARGS__)
#define _HW_F01_1(f,c,o)		f##_E(HW_EM_O(o)) HW_POP  /* <-- Arguments popped */
/* Class method? */
#define _HW_F01_0(f,c,o)		_HW_F02(f,c,o,f##_##c,)
#define _HW_F02(...)			_HW_F03(__VA_ARGS__)
#define _HW_F03(f,c,o,x,...)		HW_Y0(_HW_F03_,x)(f,c,o,x,__VA_ARGS__)
#define _HW_F03_1(f,c,o,z,y,...)	y /* <-- Arguments popped */
/* Object method? */
#define _HW_F03_0(f,c,o,...)		_HW_F04(f,c,o,f##_##o,)
#define _HW_F04(...)			_HW_F05(__VA_ARGS__)
#define _HW_F05(f,c,o,x,...)		HW_Y0(_HW_F05_,x)(f,c,o,x,__VA_ARGS__)
#define _HW_F05_1(f,c,o,z,y,...)	y /* <-- Arguments popped */
/* Global method? */
#define _HW_F05_0(f,c,o,...)		_HW_F06(f,c,o,f##_,)
#define _HW_F06(...)			_HW_F07(__VA_ARGS__)
#define _HW_F07(f,c,o,x,...)		HW_Y0(_HW_F07_,x)(f,c,o,x,__VA_ARGS__)
#define _HW_F07_1(f,c,o,z,y,...)	y /* <-- Arguments popped */
/* Fake object? */
#define _HW_F07_0(f,c,o,...)		HW_Y0(_HW_F08_,_hw_is__fake_##c)(f,c,o)
#define _HW_F08_1(f,c,o)
#define _HW_F08_0(f,c,o)		f##_E(HW_EM(no function f for o)) HW_POP  /* <-- Arguments popped */

/**
 * @ingroup public_mac
 * @brief `HW_FUNCTION(object,function)` returns the name of a function an object provides
 * @hideinitializer
 *
 * @code
 * #define PCF          HW_PCF8574( interface, twi0, address, 0x27 )
 * #define LCD          HW_HD44780( lines, 2,                   \
 *                                  cols,  16,                  \
 *                                  e,     HW_IO(PCF, 1, 2),    \
 *                                  rs,    HW_IO(PCF, 1, 0),    \
 *                                  rw,    HW_IO(PCF, 1, 1),    \
 *                                  data,  HW_IO(PCF, 4, 4) )
 *
 * xprintf( HW_FUNCTION(LCD,putchar), "Seconds=%d", seconds );
 * @endcode
 */
#define HW_FUNCTION(object,function)	HW_F(HW_FUNCTION,object,function)


/*
 * @ingroup private_mac
 * @brief Glue the first two elements of the list with a '_' between them.
 * @hideinitializer
 */
#define HW_G2(...)			_HW_G2_(__VA_ARGS__,,)
#define _HW_G2_(a,b,...)		a##_##b


/*
 * @ingroup private_mac
 * @brief Glue the first three elements of the list with a '_' between them.
 * @hideinitializer
 */
#define HW_G3(...)			_HW_G3_(__VA_ARGS__,,,)
#define _HW_G3_(a,b,c,...)		a##_##b##_##c

#define HW_G4(...)			_HW_G4_(__VA_ARGS__,,,,)
#define _HW_G4_(a,b,c,d,...)		a##_##b##_##c##_##d


/**
 * @ingroup public_mac
 * @brief `HW_DEFINE(object)` defines the functions that implement an object.
 * @hideinitializer
 *
 * External objects usually rely on functions to implement their HWA
 * actions. These functions are declared by `HW_DECLARE()` and implemened by
 * `HW_DEFINE()`.
 *
 * @code
 * #define PCF		HW_PCF8574( interface, twi0, address, 0x27 )
 *
 * HW_DEFINE(PCF);
 * @endcode
 */
#define HW_DEFINE(...)			HW_F(HW_DEFINE,__VA_ARGS__)
#define HW_DEFINE_E(e)			HW_E(e) extern void _hwa_()

/**
 * @ingroup public_mac
 * @brief `HW_DEFINE_WEAK(object)` defines the functions that implement an object.
 * @hideinitializer
 *
 * Using HW_DEFINE_WEAK() instead of HW_DEFINE() allows multiple definitions of
 * the same functions without errors.
 *
 * @code
 * #define PCF		HW_PCF8574( interface, twi0, address, 0x27 )
 *
 * HW_DEFINE_WEAK(PCF);
 * @endcode
 */
#define HW_DEFINE_WEAK(...)		HW_F(HW_DEFINE_WEAK,__VA_ARGS__)
#define HW_DEFINE_WEAK_E(e)		HW_E(e) extern void _hwa_()


/**
 * @ingroup public_mac
 * @brief `HW_DECLARE(object)` declares the functions that implement an object.
 * @hideinitializer
 *
 * External objects usually rely on functions to implement their HWA
 * actions. These functions are declared by `HW_DECLARE()` and implemened by
 * `HW_DEFINE()`.
 *
 * @code
 * #define PCF		HW_PCF8574( interface, twi0, address, 0x27 )
 *
 * HW_DECLARE(PCF);
 * @endcode
 */
#define HW_DECLARE(...)			HW_F(HW_DECLARE,__VA_ARGS__)
#define HW_DECLARE_E(e)			HW_E(e) extern void _hwa_()


/**
 * @ingroup public_mac
 * @brief `HW_IO( port, number, position )` defines a set of I/O lines.
 *
 * * `port` is the name of a port controller (`port0`, `port1`...) **not the name
 *    of the GPIO port** (`porta`, `portb`...);
 * * `number` is the number of consecutive bits;
 * * `position` is the position of the least significant bit.
 *
 * @code
 * #define PINS                    HW_IO(port0,4,3)        // Pins 6,5,4,3 of port0
 *
 * hw( configure, PINS, mode, digital_output );            // Sets pins 6..4 as output
 * hw( write, PINS, 5 );                                   // Sets pins 5 & 3, clears pins 6 & 4.
 * @endcode
 *
 * `HW_IO(...)` can also be used with external controllers:
 * @code
 * #define PCF                     HW_PCF8574( interface, twi0, address, 0x27 )
 * #define LED                     HW_IO( PCF, 1, 3 )
 *
 * hw( write, LED, 1 );
 * @endcode
 *
 * @hideinitializer
 */
#define HW_IO(...)			HW_F(HW_IO,__VA_ARGS__)
#define HW_IO_E(o,e,...)		_fake,o,e HW_E(e)


/*
 * @ingroup private_mac
 * @brief Expands to 1 if the first two elements of the list are defined equal, 0 otherwise.
 *
 * For that to work, `HW_IS()` must be used as `HW_IS(x,y)` and there must be a
 * definition of `_hw_is_x_y` that expands as '`, 1`'
 *
 * @hideinitializer
 */
#define HW_IS(...)			_HW_IS_2(__VA_ARGS__,,)
#define _HW_IS_2(x,y,...)		HW_A1(_hw_is_##x##_##y,0)


/*  Test for a bracketted argument
 *    Expand as f##1 if x is ()
 *              f##0 otherwise
 */
/* #define HW_ISB(f,x)			_HW_ISB01(f,_hw_isa_leftbkt x,0,1,) */
/* #define _HW_ISB01(...)			_HW_ISB2(__VA_ARGS__) */
/* #define _HW_ISB2(f,x,y,...)		f##y */

#define HW_EAT(...)

/*  Test for a bracketted argument
 *    Expand as f if x is ()
 *              void otherwise
 */
#define HW_IFB(x,f)			_HW_IFB01(_hw_isa_leftbkt x,f,HW_EAT,)
#define _HW_IFB01(...)			_HW_IFB2(__VA_ARGS__)
#define _HW_IFB2(z,x,y,...)		y

  
/**
 * @ingroup public_mac
 * @brief `HW_PIN(p)` returns the canonical name of pin `p`.
 * @hideinitializer
 */
#define HW_PIN(p)			_HW_PIN1(p,_hw_pin_##p,)
#define _HW_PIN1(...)			_HW_PIN2(__VA_ARGS__)
#define _HW_PIN2(o,x,...)		HW_Y(_HW_PIN_,x)(o,__VA_ARGS__)
#define _HW_PIN_0(o,...)		HW_E_P(o)
#define _HW_PIN_1(o,p,...)		p


/*
 * @ingroup private_ins
 * @brief Returns the canonical name of pin `p` of object `o`.
 * @hideinitializer
 */
#define _HW_PIN(o,p)			HW_A1(_hw_pin_##o##_##p,)


/**
 * @ingroup public_mac
 * @brief `HW_PORT(pin)` returns the port name of a HW_IO pin.
 * @hideinitializer
 */
#define HW_PORT(...)			_HW_PORT01(HW_X(__VA_ARGS__))
#define _HW_PORT01(...)			_HW_PORT02(__VA_ARGS__)
#define _HW_PORT02(c,...)		HW_Y0(_HW_PORT02_,c)(c,__VA_ARGS__)
#define _HW_PORT02_1(c,o,e)		HW_E(e)
#define _HW_PORT02_0(c,...)		HW_Y0(_HW_PORT_,HW_PORT_##c)(c,__VA_ARGS__)
#define _HW_PORT_0(c,o,...)		HW_E_OCM(o,c,HW_PORT)
#define _HW_PORT_1(c,o,...)		HW_A1(HW_PORT_##c)(o,__VA_ARGS__,)


/**
 * @ingroup public_mac
 * @brief `HW_POSITION(object)` returns the position of the least significant bit of the @ref using_objects "object".
 * @hideinitializer
 */
#define HW_POSITION(...)		HW_F( HW_POSITION, __VA_ARGS__ )
#define HW_POSITION_E(...)		0 // An error occured

#define HW_POSITION__m111			, _hw_position_m111
#define _hw_position_m111(n,o,r,c,a,wm,fm,bn,bp,...)	bp


/**
 * @ingroup public_mac
 * @brief Build a C string from the first element in the list
 * @hideinitializer
 */
#define HW_QUOTE(...)			_HW_QUOTE_2(__VA_ARGS__,)
#define _HW_QUOTE_2(x,...)		#x

#define HW_Q				HW_QUOTE


/*
 * @ingroup private_mac
 * @brief Elements a1,... of the list a0,a1,...
 * @hideinitializer
 */
#define HW_TL(...)			_HW_TL2(__VA_ARGS__,)
#define _HW_TL2(a0,...)			__VA_ARGS__


/*
 * @ingroup private_ins
 * @brief Return a single argument or concat 2 arguments inside brackets
 * @hideinitializer
 */
#define _HW_UBKT(...)			HW_Y(_HW_UBKT_,_hw_isa_leftbkt __VA_ARGS__)(__VA_ARGS__)
#define _HW_UBKT_0(...)			__VA_ARGS__
#define _HW_UBKT_1(...)			_HW_UBKT1 __VA_ARGS__
#define _HW_UBKT1(...)			_HW_UBKT2(__VA_ARGS__,,)
#define _HW_UBKT2(a,x,...)		HW_Y(_HW_UBKT3_,x)(a,x,__VA_ARGS__)
#define _HW_UBKT3_1(a,...)		a
#define _HW_UBKT3_0(a,b,x,...)		HW_Y(_HW_UBKT4_,x)(a,b,x,__VA_ARGS__)
#define _HW_UBKT4_1(a,b,...)		a##b
#define _HW_UBKT4_0(...)		HW_E((__VA_ARGS__):too many arguments)


/*
 * @ingroup private_mac
 * @brief Expand the argument to a function call
 * @hideinitializer
 *
 * The first argument is ignored, the second is the name of the function, the
 * third is the argument of the function.
 */
#define HW_VF(...)			_HW_VF2(__VA_ARGS__)
#define _HW_VF2(x,f,a)			f(a)


/*
 *@brief Remove brackets
 */
#define HW_XB(...)			__VA_ARGS__


/*  Concatenates '1' or '0' to the first argument if the second is void.
 *
 *    HW_Y(f,c) expands to:
 *      f##1 if c is "",
 *      f##0 if c is not "".
 */
#define HW_Y(...)			_HW_Y00(__VA_ARGS__,,)
#define _HW_Y00(f,x,...)		_HW_Y01(f,_hw_isa_leftbkt x,0,x)
#define _HW_Y01(...)			_HW_Y2(__VA_ARGS__)
#define _HW_Y2(f,x,y,...)		_HW_Y2_##y(f,__VA_ARGS__,)
#define _HW_Y2_1(f,...)			f##0
#define _HW_Y2_0(f,x,...)		_HW_Y03(f,_hw_is__##x,0,)
#define _HW_Y03(...)			_HW_Y04(__VA_ARGS__)
#define _HW_Y04(f,x,y,...)		f##y

/*  This version does not handle brackets.
 */
#define HW_Y0(...)			_HW_Y000(__VA_ARGS__,,)
#define _HW_Y000(f,x,...)		_HW_Y001(f,_hw_is__##x,0,)
#define _HW_Y001(...)			_HW_Y002(__VA_ARGS__)
#define _HW_Y002(f,x,y,...)		f##y

  
/*  Branch depending on a word
 *
 *    HW_KW(f,k,w) expands to:
 *      f0 if k is not w
 *      f1 if k is w	(there must a: #define _hw_is_k_k , 1)
 */
#define HW_KW(...)			_HW_KW01(__VA_ARGS__,,,)
#define _HW_KW01(f,k,w,...)		_HW_KW02(f,k,w,_hw_isa_leftbkt w, 0,)
#define _HW_KW02(...)			_HW_KW03(__VA_ARGS__)
#define _HW_KW03(f,k,w,z,x,...)		_HW_KW03##x(f,k,w)
#define _HW_KW031(f,k,w)		f##0
#define _HW_KW030(f,k,w)		_HW_KW04(f,k,w,_hw_is__##w, 0,)
#define _HW_KW04(...)			_HW_KW05(__VA_ARGS__)
#define _HW_KW05(f,k,w,z,x,...)		_HW_KW05##x(f,k,w)
#define _HW_KW051(f,k,w)		f##0
#define _HW_KW050(f,k,w)		_HW_KW06(f,k,w,_hw_is_##k##_##w, 0,)
#define _HW_KW06(...)			_HW_KW07(__VA_ARGS__)
#define _HW_KW07(f,k,w,z,x,...)		f##x


/*  Branch depending on a state: (0,1,on,off,yes,no,(x))
 *    (x) is considered a state as it can be a boolean expression.
 *
 *    HW_KS(f,w,...) expands to:
 *      f0(__VA_ARGS__) if w is not a state, and produce an error
 *      f1(0|1|(), __VA_ARGS__) if w is a state
 */
#define HW_KS(f,w,...)			_HW_KS02(f,w,(__VA_ARGS__),_hw_isa_leftbkt w, 0,)
#define _HW_KS02(...)			_HW_KS03(__VA_ARGS__)
#define _HW_KS03(f,w,va,z,x,...)	_HW_KS03##x(f,w,va)
#define _HW_KS031(f,w,va)		_HW_KS0A( f, HW_A1(_hw_state_##w), HW_XB va) //f##1(w, HW_XB va)
#define _HW_KS030(f,w,va)		_HW_KS04(f,w,va,_hw_is__##w, 0,)
#define _HW_KS04(...)			_HW_KS05(__VA_ARGS__)
#define _HW_KS05(f,w,va,z,x,...)	_HW_KS05##x(f,w,va)
#define _HW_KS051(f,w,va)		HW_E_ST(w) f##0 va
#define _HW_KS050(f,w,va)		_HW_KS06(f,w,va,_hw_state_##w, 0,)
#define _HW_KS06(...)			_HW_KS07(__VA_ARGS__)
#define _HW_KS07(f,w,va,z,...)		_HW_KS08(f,w,va,_hw_is__##z,0,)
#define _HW_KS08(...)			_HW_KS09(__VA_ARGS__)
#define _HW_KS09(f,w,va,n,x,...)	_HW_KS09##x(f,w,va)
#define _HW_KS090(f,w,va)		HW_E_ST(w) f##0 va
#define _HW_KS091(f,w,va)		_HW_KS0A( f, HW_A1(_hw_state_##w), HW_XB va)
#define _HW_KS0A(f,...)			f##1( __VA_ARGS__ )


/**
 * @ingroup public_ins_obj
 * @brief `hw( action, object [,...] )` executes an @ref using_actions "action" immediately on an @ref using_objects "object".
 * @hideinitializer
 *
 * * An explicit error message is produced if the object does not exist or if it
 *   does not support the action.
 * * Additional arguments may follow the name of the object.
 *
 * @code
 * hw( configure, pa0, direction, output );
 * hw( write, counter0, 0 );
 * @endcode
 */
#define hw(...)				hwx(hw_,__VA_ARGS__,,)


/**
 * @ingroup public_ins_obj
 * @brief `hwa( action, object [,...] )` stores an @ref using_actions "action" for the @ref using_objects "object" into a *HWA context*.
 * @hideinitializer
 *
 * * An explicit error message is produced if the object does not exist or if it
 *   does not support the action.
 * * Additional arguments may follow the name of the object.
 * * The context must have been created, only once in the same translation unit,
 *   with `hwa(begin)` or `hwa(begin, reset)`.
 * * `hwa(commit)` triggers the production of the machine code.
 * * `hwa(nocommit)` does not produce code but is useful to put the context in a
 *   known state.
 *
 * @code
 * //  Configure PA0, PA2, PA4, PA5, PA6, PA7 as outputs
 * //  accessing the DDRA register only once.
 * //
 * hwa( begin, reset );
 * hwa( configure, pa0, direction, output );
 * hwa( configure, HW_IO(pa2), direction, output );
 * hwa( configure, HW_IO(port0,4,4), direction, output );
 * hwa( commit );
 * @endcode
 */
#define hwa(...)			hwx(hwa_,__VA_ARGS__,,)


/*
 * @ingroup public_ins_obj
 * @brief Find a method for an object and call it
 * @hideinitializer
 *
 * The method is searched in this order:
 *  1. A class method, h_f_c
 *  2. A global method, h_f
 *  3. A class method h_f_ if 'o' is void (begin,commit...)
 *
 * FIXME: using the object name to distinguish a no-object call and an
 * error-object call. A class _err would be faster?
 */
#define hwx(h,f,x,...)			HW_Y0(_hwx0_,_hw_islb x)(h,f,x,__VA_ARGS__)
/*
 *  x is ()
 */
#define _hwx0_1(h,f,x,...)		_hwx_0(h,f,HW_X x,__VA_ARGS__)
/*
 *  x is not ()
 */
#define _hwx0_0(h,f,x,...)		HW_Y0(_hwx1_,hw_class_##x)(h,f,x,__VA_ARGS__)
/*
 *  x is a class name, expand the definition.
 */
#define _hwx1_1(h,f,x,o,d,...)		_hwx_10(h,f,x,o,HW_XB d,__VA_ARGS__)
/*
 *  x is not a class name
 */
#define _hwx1_0(h,f,x,...)		HW_Y0(_hwx10_,x)(h,f,x,__VA_ARGS__)
/*
 *  x is void
 */
#define _hwx10_1(h,f,z,...)		HW_Y0(_hwx101_,__VA_ARGS__)(h,f,z,__VA_ARGS__)
#define _hwx101_0(h,f,z,o,e,...)	HW_E(e)
#define _hwx101_1(h,f,x,...)		_hwx_0(h,f,HW_X(x),__VA_ARGS__)
/*
 *  x is not void
 */
#define _hwx10_0(h,f,x,...)		_hwx_0(h,f,HW_X(x),__VA_ARGS__)
#define _hwx_0(...)			_hwx_1(__VA_ARGS__)
#define _hwx_1(h,f,c,...)		HW_Y0(_hwx_1,c)(h,f,c,__VA_ARGS__)
/*
 *  o is not an object. Look for h_##f##_##o
 */
#define _hwx_11(h,f,c,o,e,...)		_hwx_12(h,e,f,h##f##_##o,o,__VA_ARGS__)
#define _hwx_12(...)			_hwx_13(__VA_ARGS__)
#define _hwx_13(h,e,f,x,...)		HW_Y0(_hwx_13,x)(h,e,f,x,__VA_ARGS__)
#define _hwx_131(h,e,f,z,y,...)		y(__VA_ARGS__)
/*
 *                            Look for h_##f##_
 */
#define _hwx_130(h,e,f,m,...)		_hwx_14(h,e,f,h##f##_,__VA_ARGS__)
#define _hwx_14(...)			_hwx_15(__VA_ARGS__)
#define _hwx_15(h,e,f,x,...)		HW_Y0(_hwx_15,x)(h,e,f,x,__VA_ARGS__)
#define _hwx_151(h,f,z,y,...)		y(__VA_ARGS__)
//#define _hwx_150(...)			HW_E(internal error [_hwx_150(__VA_ARGS__)] )
#define _hwx_150(h,e,...)		HW_E(e) extern void hwa_require_semicolon()
/*
 *  2nd arg is an object of class c
 */
/* Class method? */
#define _hwx_10(h,f,c,o,...)		_hwx_2(h,f,c,o,h##f##_##c,__VA_ARGS__)
#define _hwx_2(...)			_hwx_3(__VA_ARGS__)
#define _hwx_3(h,f,c,o,x,...)		HW_Y0(_hwx_3,x)(h,f,c,o,x,__VA_ARGS__)
#define _hwx_31(h,f,c,o,z,y,...)	y(o,__VA_ARGS__)
/* Global method? */
#define _hwx_30(h,f,c,o,x,...)		_hwx_6(h,f,c,o,h##f,__VA_ARGS__)
#define _hwx_6(...)			_hwx_7(__VA_ARGS__)
#define _hwx_7(h,f,c,o,x,...)		HW_Y0(_hwx_7,x)(h,f,c,o,x,__VA_ARGS__)
#define _hwx_71(h,f,c,o,z,y,...)	y(c,o,__VA_ARGS__)
/* Fake object? */
#define _hwx_70(h,f,c,o,x,...)		HW_Y0(_hwx_8,_hw_is__fake_##c)(h,f,c,o)
#define _hwx_81(...)			// Nothing to do, fake is always OK.
#define _hwx_80(h,f,c,o)		/* h##f##_ */ HW_E_OCM(o,c,f)


/*  Internal use only version
 */
#define _hw(...)			__hw1(__VA_ARGS__,,)
#define __hw1(f,o,...)			__hw2(f,HW_X(o),__VA_ARGS__)
#define __hw2(...)			__hw3(__VA_ARGS__)
#define __hw3(f,c,...)			HW_Y(__hw4_,c)(f,c,__VA_ARGS__)
#define __hw4_1(c,o,e,...)		HW_E(e)	// Error, stop here.
#define __hw4_0(f,c,...)		HW_Y(__hw41_,hw_##f##_##c)(f,c,__VA_ARGS__)
#define __hw41_1(f,c,...)		HW_A1(hw_##f##_##c)(__VA_ARGS__)
#define __hw41_0(f,c,o,...)		HW_E_OCM(o,c,hw_##f)


/*  Internal use only version
 */
#define _hwa(...)			__hwa1(__VA_ARGS__,)
#define __hwa1(f,o,...)			__hwa2(f,HW_X(o),__VA_ARGS__)
#define __hwa2(...)			__hwa3(__VA_ARGS__)
#define __hwa3(f,c,...)			HW_Y(__hwa4_,c)(f,c,__VA_ARGS__)
#define __hwa4_1(c,o,e,...)		HW_E(e)	// Error, stop here.
#define __hwa4_0(f,c,...)		HW_Y(__hwa41_,hwa_##f##_##c)(f,c,__VA_ARGS__)
#define __hwa41_1(f,c,...)		HW_A1(hwa_##f##_##c)(__VA_ARGS__)
#define __hwa41_0(f,c,o,...)		HW_E_OCM(o,c,hwa_##f)


/**
 * @ingroup public_ins_obj
 * @brief Returns the structure of the status of the @ref using_objects "object".
 * @hideinitializer
 *
 * @code
 * hw_stat_t(spi0) st = hw(stat,spi0);
 * if ( st.collision )
 *   ++n_collisions;
 * @endcode
 */
#define hw_stat_t(object)		hw(stat_t,object)


/**
 * @ingroup public_mac
 * @brief Returns an unsigned integer type of `n` bits.
 * @hideinitializer
 *
 * * `hw_uint_t(8)` expands to `uint8_t`;
 * * `hw_uint_t(16)` expands to `uint16_t`.
 *
 * This is useful, for example,when you need to store a value whose size depends
 * on an object:
 *
 * @code
 * hw_uint_t(HW_BITS(counter0)) count = hw( read, counter0 );
 * @endcode
 */
#define hw_uint_t(n)			_hw_uintt0(n)
#define _hw_uintt0(n)			HW_KW(_hw_uintt0,8,n)(n)
#define _hw_uintt01(n)			uint8_t
#define _hw_uintt00(n)			HW_KW(_hw_uintt1,16,n)(n)
#define _hw_uintt11(n)			uint16_t
#define _hw_uintt10(n)			HW_E_VL(n,8|16) uint8_t


#if defined DOXYGEN
/**
 * @brief Remove Doxygen warnings "explicit link request to 'k' could not be resolved".
 * @hideinitializer
 */
#define k

/**
 * @brief Remove Doxygen warnings "explicit link request to 'v' could not be resolved".
 * @hideinitializer
 */
#define v

#endif
