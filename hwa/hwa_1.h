
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief HWA definitions that do not produce C code
 */

#include "hwa_macros.h"
#include "hwa_interrupts.h"


#if DOXYGEN

/**
 * @ingroup public_def
 * @brief The name of the device as used by the compiler.
 * @hideinitializer
 */
#  define HW_DEVICE

/**
 * @ingroup public_def
 * @brief Defined if the packaging of the device is device_package. See the @ref devices "device-specific documentation" for details.
 * @hideinitializer
 */
#  define HW_DEVICE_PACKAGE_device_package

/**
 * @ingroup public_def
 * @brief The device vendor. See the @ref devices "device-specific documentation" for details.
 * @hideinitializer
 */
#  define HW_DEVICE_VENDOR

/**
 * @ingroup public_def
 * @brief The device architecture. See the @ref devices "device-specific documentation" for details.
 * @hideinitializer
 */
#  define HW_DEVICE_ARCH

/**
 * @ingroup public_def
 * @brief The CPU clock frequency (cpu cycles per second).
 */
#  define HW_SYSHZ

#endif /* defined DOXYGEN */


/*	State definitions		, positive, negative
 */
#define _hw_state_on			, 1, 0
#define _hw_state_off			, 0, 1
#define _hw_state_yes			, 1, 0
#define _hw_state_no			, 0, 1
#define _hw_state_enabled		, 1, 0
#define _hw_state_disabled		, 0, 1


/*  Keywords
 */
#define _hw_is_					, 1
#define _hw_is_0_0				, 1
#define _hw_is_16_16_				, 1
#define _hw_is_8_8_				, 1
#define _hw_is__				, 1
#define _hw_is__fake__fake			, 1
#define _hw_is__irq__irq			, 1
#define _hw_is__io1a__io1a			, 1
#define _hw_is_ack_ack				, 1
#define _hw_is_action_action			, 1
#define _hw_is_ahb_ahb				, 1
#define _hw_is_align_align			, 1
#define _hw_is_at_bottom_at_bottom		, 1
#define _hw_is_at_top_at_top			, 1
#define _hw_is_bandgap_bandgap			, 1
#define _hw_is_bottom_bottom			, 1
#define _hw_is_bps_baudrate			, 1
#define _hw_is_bps_bps				, 1
#define _hw_is_clock_clock			, 1
#define _hw_is_direction_direction		, 1
#define _hw_is_cpb_cpb				, 1
#define _hw_is_data_order_data_order		, 1
#define _hw_is_databits_databits		, 1
#define _hw_is_direction_direction		, 1
#define _hw_is_disabled_disabled		, 1
#define _hw_is_disconnected_disconnected	, 1
#define _hw_is_edge_edge			, 1
#define _hw_is_enabled_enabled			, 1
#define _hw_is_external_external		, 1
#define _hw_is_filter_filter			, 1
#define _hw_is_frequency_frequency		, 1
#define _hw_is_function_function		, 1
#define _hw_is_gain_gain			, 1
#define _hw_is_general_call_general_call	, 1
#define _hw_is_gpio_gpio			, 1
#define _hw_is_hi8_hi8				, 1
#define _hw_is_idle_state_idle_state		, 1
#define _hw_is_input_input			, 1
#define _hw_is_ioclk_ioclk			, 1
#define _hw_is_irq_irq				, 1
#define _hw_is_irq_type_irq_type		, 1
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
#define _hw_is_run_run				, 1
#define _hw_is_sampling_edge_sampling_edge	, 1
#define _hw_is_sclhz_sclhz			, 1
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
#define _hw_is_up_loop_up_loop			, 1
#define _hw_is_update_update			, 1
#define _hw_is_var_var				, 1
#define _hw_is_vref_vref			, 1
#define _hw_is_yes_yes				, 1

#define _hw_isa_leftbkt(...)			, 1


/**
 * @ingroup private_def
 * @brief Generic object class.
 */
#define _hw_class__obj


/**
 * @ingroup private_def
 * @brief 8-bit hardware register class.
 */
#define _hw_class__r8


/**
 * @ingroup private_def
 * @brief 16-bit hardware register class.
 */
#define _hw_class__r16


/**
 * @ingroup private_def
 * @brief 32-bit hardware register class.
 */
#define _hw_class__r32


/**
 * @ingroup private_def
 * @brief Class logical register made of one group of consecutive bits.
 */
#define _hw_class__cb1


/**
 * @ingroup private_def
 * @brief Class logical register made of two groups of consecutive bits.
 */
#define _hw_class__cb2


/**
 * @ingroup private_def
 * @brief Object logical register made of one group of consecutive bits.
 */
#define _hw_class__ob1


/**
 * @ingroup private_def
 * @brief Object logical register made of two groups of consecutive bits.
 */
#define _hw_class__ob2


/**
 * @ingroup private_def
 * @brief Interrupt object class.
 */
#define _hw_class__irq


/**
 * @ingroup private_def
 * @brief Memory definition of one group of consecutive bits.
 */
#define _hw_class__m1


/**
 * @ingroup private_def
 * @brief Memory definition of two groups of consecutive bits.
 */
#define _hw_class__m2


/**
 * @ingroup private_def
 * @brief Object logical register made of one group of consecutive bits.
 */
#define _hw_class__xob1


/**
 * @ingroup private_def
 * @brief Object register class.
 *
 *  An `_oreg` class object is a register of an object that can be accessed with
 *  the generic instructions designed for objects.
 */
#define _hw_class__oreg


#if !defined __ASSEMBLER__

#include <stdint.h>


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
 *  inlined unless the 'always_inline' attribute is specified.
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


/**
 * @brief 8-bit HWA context register.
 *
 * This structure is used in the HWA context to store one 8-bit hardware
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
