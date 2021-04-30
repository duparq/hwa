
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief HWA definitions that do not produce C code
 */

#include "hwa_errors.h"
#include "hwa_macros.h"
#include "hwa_interrupts.h"
#include "hwa_path.h"


/*	State definitions		, positive, negative
 */
#define _hw_state_1			, 1, 0
#define _hw_state_0			, 0, 1
#define _hw_state_on			, 1, 0
#define _hw_state_off			, 0, 1
#define _hw_state_yes			, 1, 0
#define _hw_state_no			, 0, 1
#define _hw_state_enabled		, 1, 0
#define _hw_state_disabled		, 0, 1


/*  Keywords
 */
#define _hw_is_0_0				, 1
#define _hw_is_16_16				, 1
#define _hw_is_1_1				, 1
#define _hw_is_8_8				, 1
#define _hw_is__				, 1
#define _hw_is__fake__fake			, 1
#define _hw_is__io1a__io1a			, 1
#define _hw_is__irq__irq			, 1
#define _hw_is__m11__m11			, 1
#define _hw_is__pin__pin			, 1
#define _hw_is_ack_ack				, 1
#define _hw_is_action_action			, 1
#define _hw_is_address_address			, 1
#define _hw_is_after_bottom_after_bottom	, 1
#define _hw_is_after_top_after_top		, 1
#define _hw_is_ahb_ahb				, 1
#define _hw_is_alias_alias			, 1
#define _hw_is_align_align			, 1
#define _hw_is_bandgap_bandgap			, 1
#define _hw_is_bottom_bottom			, 1
#define _hw_is_bps_baudrate			, 1
#define _hw_is_bps_bps				, 1
#define _hw_is_class_class			, 1
#define _hw_is_clock_clock			, 1
#define _hw_is_cols_cols			, 1
#define _hw_is_compare_compare			, 1
#define _hw_is_connected_connected		, 1
#define _hw_is_counter_counter			, 1
#define _hw_is_cpb_cpb				, 1
#define _hw_is_data_data			, 1
#define _hw_is_data_order_data_order		, 1
#define _hw_is_databits_databits		, 1
#define _hw_is_delay_h_delay_h			, 1
#define _hw_is_delay_l_delay_l			, 1
#define _hw_is_direction_direction		, 1
#define _hw_is_direction_direction		, 1
#define _hw_is_disabled_disabled		, 1
#define _hw_is_disconnected_disconnected	, 1
#define _hw_is_e_e				, 1
#define _hw_is_edge_edge			, 1
#define _hw_is_enabled_enabled			, 1
#define _hw_is_external_external		, 1
#define _hw_is_fast_fast			, 1
#define _hw_is_filter_filter			, 1
#define _hw_is_frequency_frequency		, 1
#define _hw_is_function_function		, 1
#define _hw_is_gain_gain			, 1
#define _hw_is_general_call_general_call	, 1
#define _hw_is_gpio_gpio			, 1
#define _hw_is_hi8_hi8				, 1
#define _hw_is_idle_state_idle_state		, 1
#define _hw_is_input_input			, 1
#define _hw_is_interface_interface		, 1
#define _hw_is_ioclk_ioclk			, 1
#define _hw_is_irq_irq				, 1
#define _hw_is_irq_type_irq_type		, 1
#define _hw_is_latch_latch			, 1
#define _hw_is_level_level			, 1
#define _hw_is_lines_lines			, 1
#define _hw_is_lo8_lo8				, 1
#define _hw_is_mode_mode			, 1
#define _hw_is_multiplier_multiplier		, 1
#define _hw_is_nack_nack			, 1
#define _hw_is_negative_input_negative_input	, 1
#define _hw_is_no_no				, 1
#define _hw_is_off_off				, 1
#define _hw_is_output_l_output_l		, 1
#define _hw_is_output_output			, 1
#define _hw_is_overflow_overflow		, 1
#define _hw_is_parity_parity			, 1
#define _hw_is_pcic_pcic			, 1
#define _hw_is_polarity_polarity		, 1
#define _hw_is_port_port			, 1
#define _hw_is_positive_input_positive_input	, 1
#define _hw_is_prescaler_prescaler		, 1
#define _hw_is_pulldown_pulldown		, 1
#define _hw_is_pullup_pullup			, 1
#define _hw_is_receiver_receiver		, 1
#define _hw_is_reload_reload			, 1
#define _hw_is_reset_reset			, 1
#define _hw_is_rs_rs				, 1
#define _hw_is_rule_rule			, 1
#define _hw_is_run_run				, 1
#define _hw_is_rw_rw				, 1
#define _hw_is_rxd_rxd				, 1
#define _hw_is_sampling_edge_sampling_edge	, 1
#define _hw_is_scl_scl				, 1
#define _hw_is_sclhz_sclhz			, 1
#define _hw_is_sda_sda				, 1
#define _hw_is_sense_sense			, 1
#define _hw_is_slave_address_mask_slave_address_mask	, 1
#define _hw_is_slave_address_slave_address	, 1
#define _hw_is_sleep_mode_sleep_mode		, 1
#define _hw_is_sleep_sleep			, 1
#define _hw_is_source_source			, 1
#define _hw_is_stopbits_stopbits		, 1
#define _hw_is_sysclk_sysclk			, 1
#define _hw_is_timeout_timeout			, 1
#define _hw_is_top_top				, 1
#define _hw_is_transmitter_transmitter		, 1
#define _hw_is_trigger_trigger			, 1
#define _hw_is_txd_txd				, 1
#define _hw_is_up_loop_up_loop			, 1
#define _hw_is_update_update			, 1
#define _hw_is_var_var				, 1
#define _hw_is_vref_vref			, 1
#define _hw_is_yes_yes				, 1


/*  Define wich classes are hardware bits
 */
#define _hw_isa_reg__r8			, 1
#define _hw_isa_reg__r16		, 1
#define _hw_isa_reg__r32		, 1
#define _hw_isa_reg__cb1		, 1
#define _hw_isa_reg__cb2		, 1
#define _hw_isa_reg__ob1		, 1
#define _hw_isa_reg__ob2		, 1
#define _hw_isa_reg__xb1		, 1
#define _hw_isa_reg__xb2		, 1


/*  3-bit numbers
 */
#define _hw_isa_3bn_0			, 1
#define _hw_isa_3bn_1			, 1
#define _hw_isa_3bn_2			, 1
#define _hw_isa_3bn_3			, 1
#define _hw_isa_3bn_4			, 1
#define _hw_isa_3bn_5			, 1
#define _hw_isa_3bn_6			, 1
#define _hw_isa_3bn_7			, 1


/*  4-bit numbers
 */
#define _hw_isa_4bn_0			, 1
#define _hw_isa_4bn_1			, 1
#define _hw_isa_4bn_2			, 1
#define _hw_isa_4bn_3			, 1
#define _hw_isa_4bn_4			, 1
#define _hw_isa_4bn_5			, 1
#define _hw_isa_4bn_6			, 1
#define _hw_isa_4bn_7			, 1
#define _hw_isa_4bn_8			, 1
#define _hw_isa_4bn_9			, 1
#define _hw_isa_4bn_10			, 1
#define _hw_isa_4bn_11			, 1
#define _hw_isa_4bn_12			, 1
#define _hw_isa_4bn_13			, 1
#define _hw_isa_4bn_14			, 1
#define _hw_isa_4bn_15			, 1


/**
 * @ingroup hwa_dev
 * @hideinitializer
 *
 * Detect an argument surrounded by parentheses.
 */
#define _hw_par(...)			, 1


/**
 * @ingroup hwa_dev
 * @hideinitializer
 *
 * Generic object class.
 */
#define hw_class__obj


/**
 * @ingroup hwa_classes
 * @defgroup hwa_r8 Class _r8: 8-bit hardware register class.
 *
 * @section hwa_r8_rel Relatives
 *
 *  * `(register,p)`: the single bit at position `p` of `register`.
 *  * `(register,n,p)`: n consecutive bits at position `p` of `register`.
 */
#define hw_class__r8


/**
 * @ingroup hwa_dev
 * @defgroup hwa_r16 Class _r16
 * @brief 16-bit hardware register class.
 */
#define hw_class__r16


/**
 * @ingroup hwa_dev
 * @defgroup hwa_r32 Class _r32
 * @brief 32-bit hardware register class.
 */
#define hw_class__r32


/**
 * @ingroup hwa_dev
 * @defgroup hwa_cb1 Class _cb1
 * @brief Class logical register made of one group of consecutive bits.
 */
#define hw_class__cb1


/**
 * @ingroup hwa_dev
 * @defgroup hwa_cb2 Class _cb2
 * @brief Class logical register made of two groups of consecutive bits.
 */
#define hw_class__cb2


/**
 * @ingroup hwa_dev
 * @defgroup hwa_ob1 Class _ob1
 * @brief Object logical register made of one group of consecutive bits.
 */
#define hw_class__ob1


/**
 * @ingroup hwa_dev
 * @defgroup hwa_ob2 Class _ob2
 * @brief Object logical register made of two groups of consecutive bits.
 */
#define hw_class__ob2


/**
 * @ingroup hwa_dev
 * @defgroup hwa_xb1 Class _xb1
 * @brief Logical register made of one group of consecutive bits in another object.
 */
#define hw_class__xb1


/**
 * @ingroup hwa_dev
 * @defgroup hwa_xb2 Class _xb2
 * @brief Logical register made of two groups of consecutive bits in another object.
 */
#define hw_class__xb2


/**
 * @ingroup hwa_dev
 * @defgroup hwa_m11 Class _m11
 * @brief Memory definition for one group of consecutive bits.
 */
#define hw_class__m11

#define _hw_actions__m11	, (read,toggle,write)
#define _hwa_actions__m11	, (toggle,write)


/*
 *  Provide relative notation for accessing one group of bits of a memory location
 *    '(register,bp)' -> one bit at position bp
 *    '(register,bn,bp)' -> bn bits at position bp
 *    '(register,bn,bp,x)' -> FIXME should trigger an error
 *
 *  FIXME: assumes 8 bit register (3bn for position). TODO: consider 16 bit registers.
 *  FIXME: should use classes _m11p and _m11np
 */
#define hw__m11_					, _hw_m11_
#define _hw_m11_(oo,x,...)				_HW_B(_hw_m11r,_hw_isa_3bn_##x)(oo,x,__VA_ARGS__)
#define _hw_m11r0(oo,x,...)				,,HW_EM_XNIL(x,(0..7))
#define _hw_m11r1(oo,x,o,r,rc,ra,rwm,rfm,rbn,rbp)	_HW_B(_hw_m11r1,_hw_is_1_##rbn)(oo,x,o,r,rc,ra,rwm,rfm,rbn,rbp)
#define _hw_m11r10(oo,x,o,r,rc,ra,rwm,rfm,rbn,rbp)	_m11,(o,r,1,x),(o,r,rc,ra,rwm,rfm,1,x)
#define _hw_m11r11(oo,x,o,r,rc,ra,rwm,rfm,rbn,rbp)	_m11,(o,r,rbp,x),(o,r,rc,ra,rwm,rfm,rbp,x)


/**
 * @ingroup hwa_dev
 * @defgroup hwa_m12 Class _m12
 * @brief Memory definition for two groups of consecutive bits at the same address.
 */
#define hw_class__m12


/**
 * @ingroup hwa_dev
 * @defgroup hwa_m22 Class _m22
 * @brief Memory definition for two groups of consecutive bits at two different addresses.
 */
#define hw_class__m22

#define _hw_actions__m22	, (read,toggle,write)
#define _hwa_actions__m22	, (toggle,write)

/**
 * @ingroup hwa_classes
 * @defgroup hwa_reg Register
 *
 * A HWA register object is a set of consecutive bits (1 or more). It can
 * correspond to a hardware register or to one or two subsets of one or two
 * hardware registers.
 *
 * A register object is accessed through the object it pertains to, using the
 * path notation: `(object, register)`.
 *
 * Register objects give access to subsets of their content using the path
 * notation:
 *
 *  * `(object,register,p)`: the single bit at position `p` in the register object;
 *  * `(object,register,n,p)`: `n` bits from position `p` in the register object.
 *
 * `HW_ADDRESS()` gives the address of a register object if it corresponds to a
 * single hardware register:
 *
 * @code
 * addr = HW_ADDRESS( (counter0,cs) )
 * @endcode
 *
 * `HW_POSITION()` gives the position of the least significant bit in the
 * corresponding hardware register:
 *
 * @code
 * addr = HW_POSITION( (counter0,cs) )
 * @endcode
 *
 * `HW_BITS()` gives the number of bits of a register:
 *
 * @code
 * addr = HW_BITS( (counter0,cs) )
 * @endcode
 *
 * @section hwa_regif Interface
 *
 * Operations on registers can use the `hw(...)` instruction to act immediatly,
 * or the transactional machanism with `hwa(...)`.
 *
 *  * Reading a register:
 *
 * @code
 * //  Read register `wgm` of `counter0`:
 * //
 * uint8_t x = hw( read, (counter0,wgm) );
 * @endcode
 *
 * @code
 * //  Store bits 7 & 6 of register `pin` of `porta`
 * //  in bits 1 & 0 of `x`:
 * //
 * uint8_t x = hw( read, (porta,pin,2,6) );
 * @endcode
 *
 *  * Writing a register:
 *
 * @code
 * //  write register `wgm` of `counter0`:
 * //
 * hw( write, (counter0,wgm), 2 );
 * @endcode
 *
 * @code
 * //  Set bits 5 & 4, and reset bits 3 & 2 of
 * //  register `ddr` of `porta`:
 * //
 * hw( write, (porta,ddr,4,2), 0x0C );
 * @endcode
 *
 *  * Toggling a register:
 *
 * @code
 * //  Toggle bit 1 of register `port` of `porta`:
 * //
 * hw( toggle, (porta,port,1) );
 * @endcode
 */


/**
 * @ingroup hwa_dev
 * @defgroup hwa_fake Class _fake
 * @brief The _fake class accepts all kinds of actions and does nothing at all.
 */
#define hw_class__fake


/**
 * @ingroup hwa_dev
 * @brief Fake object: useful for compiling code for a target that does not implement non
 * vital hardware.
 * @hideinitializer
 */
#define hw_fake				_fake, -1

/*	Relatives of fake are fake
 */
#define hw__fake_			, _hw_fake_
#define _hw_fake_(o,x,d)		_fake, fake, (-1)


/**
 * @ingroup hwa_dev
 * @brief The virtual object 'pin' handles the '(pin,...)' notation.
 * @hideinitializer
 *
 * -
 */
#define hw_pin				_pin, -1
#define hw_class__pin


/**
 * @ingroup hwa_pub
 * @brief Returns the address of an @ref using_objects "object" or -1 if the object does not exist.
 * @hideinitializer
 *
 * For I/O objects, the address is computed from their definition.
 *
 * @code
 * #if HW_ADDRESS(counter0) == -1
 * # error counter0 does not exist
 * #endif
 * @endcode
 */
#define HW_ADDRESS(...)			HW_F( HW_ADDRESS, __VA_ARGS__ )
#define HW_ADDRESS_E(...)		-1	// Error


/*  Address correction
 *    C and assembly addresses are offset by 0x20 bytes with avr-gcc (or avrlibc?)
 */
#if !defined HW_AC
#  define HW_AC
#endif

#define HW_ADDRESS__m11			, _hw_address_m11
#define _hw_address_m11(n,o,r,c,a,...)	(a HW_AC)

#define HW_ADDRESS_			, _hw_address_		// By default
#define _hw_address_(o,a,...)		a


/**
 * @ingroup hwa_dev
 * @brief `HW_AP(logical_register)` returns the pair address,position of a logical register.
 *
 * This is useful for assembly programming, for example with the SBI / CBI instructions.
 *
 * @hideinitializer
 */
#define HW_AP(...)			HW_F( HW_AP, __VA_ARGS__ )
#define HW_AP_E(...)			0 // An error occured

#define HW_AP__m11				, _hw_ap_m11
#define _hw_ap_m11(n,o,r,c,a,wm,fm,bn,bp,...)	(a HW_AC), bp


/**
 * @ingroup hwa_pub
 * @hideinitializer
 *
 * Number of bits of an @ref using_objects "object", 0 if the object has no bits
 * or does not exist (no error is emitted).
 *
 * @code
 * #if HW_BITS(counter0) != 16
 * # error You must chose a 16-bit counter
 * #endif
 * @endcode
 */
#define HW_BITS(...)			HW_F( HW_BITS, __VA_ARGS__ )
#define HW_BITS_E(...)			0


/**
 * @ingroup hwa_pub
 * @brief Declares the functions that implement an object.
 * @hideinitializer
 *
 * External objects usually rely on functions to implement their HWA
 * actions. These functions are declared by HW_DECLARE() and implemened by
 * HW_IMPLEMENT().
 *
 * @code
 * #define PCF		HW_PCF8574( interface, twi0, address, 0x27 )
 *
 * HW_DECLARE(PCF);
 * @endcode
 *
 * An optionnal parameter 'weak' can be given so that the definitions can be
 * overriden:
 *
 * @code
 * HW_DECLARE(PCF,weak);
 * @endcode
 */
#define HW_DECLARE(...)			HW_F(HW_DECLARE,__VA_ARGS__)
#define HW_DECLARE_E(e)			HW_E(e) extern uint8_t hw_foo()

#define _hw_declare_			, 
#define _hw_declare_weak		, __attribute__((weak))


/**
 * @ingroup hwa_pub
 * @brief Defines the functions that implement an object.
 * @hideinitializer
 *
 * External objects usually rely on functions to implement their HWA
 * actions. These functions are declared by `HW_DECLARE()` and defined by
 * `HW_IMPLEMENT()`.
 *
 * @code
 * #define PCF		HW_PCF8574( interface, twi0, address, 0x27 )
 *
 * HW_IMPLEMENT(PCF);
 * @endcode
 */
#define HW_IMPLEMENT(...)		HW_F(HW_IMPLEMENT,__VA_ARGS__)
#define HW_IMPLEMENT_E(e)		HW_E(e) extern uint8_t hw_foo()


/**
 * @ingroup hwa_pub
 * @brief Returns the position of the least significant bit of an object.
 * @hideinitializer
 */
#define HW_POSITION(...)		HW_F( HW_POSITION, __VA_ARGS__ )
#define HW_POSITION_E(...)		0 // An error occured
//#define HW_POSITION_E(e)		HW_E(e) /* FIXME: causes problems with swuarta */

#define HW_POSITION__m11				, _hw_position_m11
#define _hw_position_m11(n,o,r,c,a,wm,fm,bn,bp,...)	bp


#if !defined __ASSEMBLER__

/*  Storage class of HWA functions.
 *
 *  HWA function-like macros MUST be injected inside their callers and not leave
 *  any trace elsewhere, i.e. they must be strictly equivalent to macros,
 *  otherwise all kinds of HWA warnings and errors will be triggered.
 *
 *  GCC does the job with only the 'inline' keyword when optimisations are on,
 *  and optimisations must be on when using HWA.
 *
 *  However, it seems that the 'static' keyword prevents the function to be
 *  inlined unless the 'always_inline' attribute is also specified.
 *
 *  `__attribute__((always_inline))` triggers a warning if gcc fails to inline the
 *  function.
 */
#define HW_INLINE		static inline __attribute__((always_inline))


#if defined __cplusplus
# define HW_EXTERN_C		extern "C"
#else
# define HW_EXTERN_C
#endif


/* This structure is used in the HWA context to store one 8-bit hardware
 * register.
 */
typedef struct
{
  intptr_t	a ;		/*!< Address of hardware register.		*/
  uint8_t	mmask ;		/*!< Modified bits mask.			*/
  uint8_t	mvalue ;	/*!< Modified value mask.			*/
  uint8_t	omask ;		/*!< Hardware known bits mask.			*/
  uint8_t	ovalue ;	/*!< Hardware known value mask.			*/
} hwa_r8_t ;

typedef struct
{
  intptr_t	a ;
  uint16_t	mmask ;
  uint16_t	mvalue ;
  uint16_t	omask ;
  uint16_t	ovalue ;
} hwa_r16_t ;

typedef struct
{
  intptr_t	a ;
  uint32_t	mmask ;
  uint32_t	mvalue ;
  uint32_t	omask ;
  uint32_t	ovalue ;
} hwa_r32_t ;


#endif /* !defined __ASSEMBLER__ */
