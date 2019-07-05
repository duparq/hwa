
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
#define HW_A0(...)		_HW_A0_2(__VA_ARGS__,)
#define _HW_A0_2(a0,...)	a0

#define HW_A0_A1(...)		_HW_A0_A1_2(__VA_ARGS__,,)
#define _HW_A0_A1_2(a0,a1,...)	a0,a1


/*
 * @ingroup private_mac
 * @brief Element a1 of the list a0,a1,...
 * @hideinitializer
 */
#define HW_A1(...)		_HW_A1_2(__VA_ARGS__,,)
#define _HW_A1_2(a0,a1,...)	a1


/*
 * @ingroup private_mac
 * @brief Element a2 of the list a0,a1,a2,...
 * @hideinitializer
 */
#define HW_A2(...)		_HW_A2_2(__VA_ARGS__,,,)
#define _HW_A2_2(a0,a1,a2,...)	a2

#define HW_A3(...)			_HW_A3_2(__VA_ARGS__,,,,)
#define _HW_A3_2(a0,a1,a2,a3,...)	a3

/* #define HW_A4(...)			_HW_A4_2(__VA_ARGS__,,,,,) */
/* #define _HW_A4_2(a0,a1,a2,a3,a4,...)	a4 */

/* #define HW_A5(...)			_HW_A5_2(__VA_ARGS__,,,,,,) */
/* #define _HW_A5_2(a0,a1,a2,a3,a4,a5,...)	a5 */


/**
 * @ingroup public_mac
 * @brief `HW_ADDRESS(object)` returns the address of the @ref using_objects "object".
 * @hideinitializer
 *
 * The object should be a peripheral controller or a register.
 */
#define HW_ADDRESS(...)			HW_F( HW_ADDRESS, __VA_ARGS__ )
#define HW_ADDRESS_(...)		0

#define _HW_A				HW_ADDRESS


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
#define HW_BITS_(...)			0


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

#define HW_E_O(x)		HW_E(HW_Q(x) is not an object)
#define HW_EM_O(x)		HW_Q(x) is not an object
#define HW_E_P(x)		HW_E(HW_Q(x) is not a pin)
#define HW_E_OM()		HW_E(missing object name)
#define HW_EM_OM()		HW_Q(missing object name)
#define HW_E_T(x)		HW_E(unrecognized token HW_Q(x))
#define HW_E_V()		HW_E(missing value)
#define HW_E_G(x)		HW_E(garbage starting at HW_Q(x))
#define HW_EM_G(x)		garbage starting at HW_Q(x)
#define HW_EM_GA(x)		garbage after HW_Q(x)
#define HW_E_K(k,x)		HW_E(expected HW_Q(k) instead of HW_Q(x))

#define HW_E_KX(k,x)		HW_E(expected HW_Q(k) instead of HW_Q(x))
#define HW_EM_KX(k,x)		expected HW_Q(k) instead of HW_Q(x)
#define HW_EM_NKX(n,k,x)	expected HW_Q(k) instead of HW_Q(x) in HW_Q(n)

#define HW_EM_C(c)		HW_Q(c) is not a class

#define HW_E_OCM(o,c,m)		HW_Y(_HW_EOCM_,c)(o,c,m)
#define _HW_EOCM_0(o,c,m)	HW_E(object HW_Q(o) of class HW_Q(c) has no method named HW_Q(m))
#define _HW_EOCM_1(...)

#define HW_E_CM(c,m)		HW_E(class HW_Q(c) has no method HW_Q(m))
#define HW_EM_CM(c,m)		class HW_Q(c) has no method HW_Q(m)

#define HW_E_M(m)		HW_E(unknown method HW_Q(m))

#define HW_E_ST(x)		HW_E(HW_Q(x) is not in (on, off))
#define HW_E_VL(v,l)		HW_E(HW_Q(v) is not HW_Q(l))
#define HW_E_AVM(a)		HW_E(missing value for HW_Q(a))
#define HW_E_AVL(a,v,l)		HW_E(HW_Q(a) can be HW_Q(l) but not HW_Q(v))
#define HW_E_OAVL(a,v,l)	HW_E(optionnal parameter HW_Q(a) can be HW_Q(l) but not HW_Q(v))
#define HW_E_OKVL(k,v,l)	HW_E(value HW_Q(v) for optionnal parameter HW_Q(k) is not in l)
#define HW_E_OKMV(k,v,l)	HW_E(value of optionnal parameter HW_Q(k) must be HW_Q(l) not HW_Q(v))
#define HW_E_OO(o,x)		HW_E(object HW_Q(o) has no relative named HW_Q(x))
#define HW_EM_OO(o,x)		HW_Q(o) has no relative named HW_Q(x)
#define HW_E_IOFN(o,a,v,l)	HW_E(HW_Q(o): HW_Q(a) can be HW_Q(l) but not HW_Q(v))
#define HW_E_IMP(f)		HW_E(HW_Q(f): not implemented for this target)
#define HW_E_TBI(f)		HW_E(instruction is not implemented yet)
#define HW_E_KVNIY(k,v)		HW_E(HW_Q(k=v) is not implemented yet)

#define HW_E_ML(l)		HW_E(expected one argument in HW_Q(l))
#define HW_E_NIL(v,l)		HW_E(HW_Q(v) is not in l)

#define HW_E_IRQ(n)		HW_E(HW_Q(n) is not an IRQ)
#define HW_EM_IRQ(n)		HW_Q(n) is not an IRQ

#define HW_ERROR		HW_E


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


/*
 * @ingroup public_ins_obj
 * @brief Find a method for an object and call it
 * @hideinitializer
 *
 * The method is searched in this order:
 *  1. f_c
 *  2. f_o
 *  3. f
 *
 * The definition of the object is pushed away so that it becomes the argument
 * of the method.
 */
#define HW_F(...)			_HW_F0(__VA_ARGS__,)
#define _HW_F0(f,o,...)			_HW_F00(f, HW_X(o),__VA_ARGS__)
#define _HW_F00(...)			_HW_F01(__VA_ARGS__)
#define _HW_F01(f,c,o,...)		HW_Y0(_HW_F01_,c)(f,c,o)   (o,__VA_ARGS__)
#define _HW_F01_1(f,c,o)		f##_	// An error occured
/* Class method? */
#define _HW_F01_0(f,c,o)		_HW_F02(f,c,o,f##_##c,)
#define _HW_F02(...)			_HW_F03(__VA_ARGS__)
#define _HW_F03(f,c,o,x,...)		HW_Y0(_HW_F03_,x)(f,c,o,x,__VA_ARGS__)
#define _HW_F03_1(f,c,o,z,y,...)	y
/* Object method? */
#define _HW_F03_0(f,c,o,...)		_HW_F04(f,c,o,f##_##o,)
#define _HW_F04(...)			_HW_F05(__VA_ARGS__)
#define _HW_F05(f,c,o,x,...)		HW_Y0(_HW_F05_,x)(f,c,o,x,__VA_ARGS__)
#define _HW_F05_1(f,c,o,z,y,...)	y
/* Global method? */
#define _HW_F05_0(f,c,o,...)		_HW_F06(f,c,o,f,)
#define _HW_F06(...)			_HW_F07(__VA_ARGS__)
#define _HW_F07(f,c,o,x,...)		HW_Y0(_HW_F07_,x)(f,c,o,x,__VA_ARGS__)
#define _HW_F07_1(f,c,o,z,y,...)	y
/* Fake object? */
#define _HW_F07_0(f,c,o,...)		HW_Y0(_HW_F08_,_hw_is__fake_##c)(f,c,o)
#define _HW_F08_1(f,c,o)
#define _HW_F08_0(f,c,o)		HW_E_OCM(o,c,f)


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
#define HW_FUNCTION(oject,function)	HW_F(HW_FUNCTION,oject,function)


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
 * @brief Returns the ID of the @ref using_objects "object" or 0 if the object does not exist.
 * @hideinitializer
 */
#define HW_ID(o)			_HW_ID01( HW_X(o) )
#define _HW_ID01(...)			_HW_ID02(__VA_ARGS__)
#define _HW_ID02(c,...)			HW_Y0(_HW_ID02_,c)(c,__VA_ARGS__,)
#define _HW_ID02_1(...)			0 // Do not produce an error
#define _HW_ID02_0(c,o,i,...)		i


/**
 * @ingroup public_mac
 * @brief Returns a computed ID of the @ref using_objects "object" or -1 if the object does not exist.
 * @hideinitializer
 */
#define HW_IDX(...)			HW_F(HW_IDX,__VA_ARGS__) HW_EOL(HW_TL(__VA_ARGS__))
#define HW_IDX_(o,e,...)		-1


/**
 * @ingroup public_mac
 * @brief `HW_IMPLEMENT(object)` implements the interface functions for the object.
 * @hideinitializer
 *
 * External objects may provide functions that are not inlined to implement HWA
 * actions. These functions are declared by `HW_INTERFACE()` and implemened by
 * `HW_IMPLEMENT()`.
 *
 * @code
 * #define PCF		HW_PCF8574( interface, twi0, address, 0x27 )
 *
 * HW_IMPLEMENT(PCF);
 * @endcode
 */
#define HW_IMPLEMENT(...)		HW_F(HW_IMPLEMENT,__VA_ARGS__) HW_EOL(HW_TL(__VA_ARGS__))
#define HW_IMPLEMENT_(o,e,...)		HW_E(e)
#define HW_IMPLEMENT_WEAK(...)		HW_F(HW_IMPLEMENT_WEAK,__VA_ARGS__) HW_EOL(HW_TL(__VA_ARGS__)
#define HW_IMPLEMENT_WEAK_(o,e,...)	HW_E(e)


/**
 * @ingroup public_mac
 * @brief `HW_INTERFACE(object)` declares the interface functions for the object.
 * @hideinitializer
 *
 * External objects may provide functions that are not inlined to implement HWA
 * actions. These functions are declared by `HW_INTERFACE()` and implemened by
 * `HW_IMPLEMENT()`.
 *
 * @code
 * #define PCF		HW_PCF8574( interface, twi0, address, 0x27 )
 *
 * HW_INTERFACE(PCF);
 * @endcode
 */
#define HW_INTERFACE(...)		HW_F(HW_INTERFACE,__VA_ARGS__) HW_EOL(HW_TL(__VA_ARGS__))
#define HW_INTERFACE_(o,e,...)		HW_E(e)


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
#define HW_IO_(o,e,...)			xo(_fake,o,e) HW_E(e)


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

/* #define HW_YIS(...)		_HW_YIS01(__VA_ARGS__,) */
/* #define _HW_YIS01(f,x,y,...)	_HW_YIS02(f,x,y,_hw_isa_leftbkt y) */
/* #define _HW_YIS02(...)		_HW_YIS03(__VA_ARGS__) */
/* #define _HW_YIS03(f,x,y,z)	HW_Y0(_HW_YIS03_,z)(f,x,y) */
/* #define _HW_YIS03_1(...)	0 */
/* #define _HW_YIS03_0(f,x,y)	HW_Y0(f,_hw_is_##x##_##y) */


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
#define HW_POSITION_(...)		0 // An error occured

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


/*
 * @ingroup private_mac
 * @brief Concatenates '_1' or '_0' to the first argument according to the second.
 * @hideinitializer
 *
 * `HW_Y(f_,c)` expands to:
 *  * `f_1` if `c` is "",
 *  * `f_0` if `c` is not "".
 */
#define HW_Y(...)			_HW_Y00(__VA_ARGS__,,)
#define _HW_Y00(f,x,...)		_HW_Y01(f,_hw_isa_leftbkt x,0,x)
#define _HW_Y01(...)			_HW_Y2(__VA_ARGS__)
#define _HW_Y2(f,x,y,...)		_HW_Y2_##y(f,__VA_ARGS__,)
#define _HW_Y2_1(f,...)			f##0
#define _HW_Y2_0(f,x,...)		_HW_Y03(f,_hw_is__##x,0,)
#define _HW_Y03(...)			_HW_Y04(__VA_ARGS__)
#define _HW_Y04(f,x,y,...)		f##y

#define HW_Y0(...)			_HW_Y000(__VA_ARGS__,,)
#define _HW_Y000(f,x,...)		_HW_Y001(f,_hw_is__##x,0,)
#define _HW_Y001(...)			_HW_Y002(__VA_ARGS__)
#define _HW_Y002(f,x,y,...)		f##y


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
 *   with `hwa(begin)` or `hwa(begin_from_reset)`.
 * * `hwa(commit)` triggers the production of the machine code.
 * * `hwa(nocommit)` does not produce code but is useful to put the context in a
 *   known state.
 *
 * @code
 * //  Configure PA0, PA2, PA4, PA5, PA6, PA7 as outputs
 * //  accessing the DDRA register only once.
 * //
 * hwa( begin_from_reset );
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
 *  3. A class method h_f__mcu if 'o' is void (begin,commit...)
 */
#define hwx(h,f,o,...)			_hwx_0(h,f,HW_X(o),__VA_ARGS__)
#define _hwx_0(...)			_hwx_1(__VA_ARGS__)
#define _hwx_1(h,f,c,o,...)		HW_Y0(_hwx_1,c)(h,f,c,o,__VA_ARGS__)
#define _hwx_11(h,f,c,o,e,...)		HW_Y(_hwx_11,o)(h,f,c,o,e,__VA_ARGS__)
#define _hwx_110(h,f,c,o,e,...)		h##f##_	HW_E(e) // An error occured with o
#define _hwx_111(h,f,c,o,e,...)		_hwx_12(h,f,h##f##__mcu,__VA_ARGS__)
#define _hwx_12(...)			_hwx_13(__VA_ARGS__)
#define _hwx_13(h,f,x,...)		HW_Y0(_hwx_13,x)(h,f,x,__VA_ARGS__)
#define _hwx_130(h,f,...)		HW_E_M(f)
#define _hwx_131(h,f,z,y,...)		y(__VA_ARGS__)
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
#define _hwx_80(h,f,c,o,...)		h##f##_ HW_E_OCM(o,c,f)

#define hw_class__mcu
#define hw_mcu				_mcu,,


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
#define _hw_uintt0(n)			HW_G2(_hw_uintt1,HW_IS(8,n##_))(n)
#define _hw_uintt1_1(n)			uint8_t
#define _hw_uintt1_0(n)			HW_G2(_hw_uintt2,HW_IS(16,n##_))(n)
#define _hw_uintt2_1(n)			uint16_t
#define _hw_uintt2_0(n)			HW_E_VL(n,8|16) uint8_t


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
