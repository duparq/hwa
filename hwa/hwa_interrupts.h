
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Interrupts
 *
 * This file contains all that is relative to interrupts.
 */

/*  Interrupt requests are objects of class _irqa or _irqb
 */
//#define _hw_class__irq

#define _hw_is__irq__irqa			, 1
#define _hw_is__irq__irqb			, 1
#define _hw_is__irq__nmi			, 1


/**
 * @brief Get an IRQ object
 *
 * Syntax: `hw_irq( object [, irq_name] )`
 * @hideinitializer
 */
#define hw_irq(...)		_hw_irq2(__VA_ARGS__,,)
#define _hw_irq2(p,c,...)	HW_G2(_hw_irq3,				\
				      HW_IS(_irq,_hw_irq_##p##_##c))(p,c,__VA_ARGS__)
#define _hw_irq3_1(p,c,...)	_hw_irq_##p##_##c
#define _hw_irq3_0(p,...)	HW_G2(_hw_irq4, HW_IS(_irq,_hw_irq_##p))(p,__VA_ARGS__)
//#define _hw_irq4_1(p,...)	_hw_irq_##p, __VA_ARGS__
#define _hw_irq4_1(p,...)	_hw_irq_##p
#define _hw_irq4_0(p,...)	HW_G2(_hw_irq5,HW_ISOBJ(p))(p,__VA_ARGS__)
#define _hw_irq5_0(p,...)	HW_ERR("`"#p"` is not a HWA object.")
#define _hw_irq5_1(p,...)	HW_ERR("`"#p"` has no IRQ named `` or `" \
				       HW_QUOTE(__VA_ARGS__)"`.")

/*	Definition of an interrupt, extra arguments allowed and returned
 */
#define hw_irqx(...)		HW_G2(_hw_irqx2,HW_IS(_irq,__VA_ARGS__))(__VA_ARGS__)
#define _hw_irqx2_1(...)	__VA_ARGS__
#define _hw_irqx2_0(p,...)						\
  HW_G2(_hw_irqx3, HW_IS(_irq,_hw_irq_##p##_##__VA_ARGS__))(p,__VA_ARGS__)
#define _hw_irqx3_1(p,...)	_hw_irq_##p##_##__VA_ARGS__
#define _hw_irqx3_0(p,...)					\
  HW_G2(_hw_irqx4, HW_IS(_irq,_hw_irq_##p))(p,__VA_ARGS__)
#define _hw_irqx4_1(p,...)	_hw_irq_##p, __VA_ARGS__
#define _hw_irqx4_0(p,...)	HW_G2(_hw_irqx5,HW_ISOBJ(p))(p,__VA_ARGS__)
#define _hw_irqx5_0(p,...)	HW_ERR("`"#p"` is not a HWA object.")
#define _hw_irqx5_1(p,...)	HW_ERR("`"#p"` has no IRQ named `` or `" \
				       HW_QUOTE(__VA_ARGS__)"`.")

/**
 * @brief Definition of the enable bit of an IRQ
 *
 * Syntax 1: `hw_irqe( object [, irq_name] )`
 *
 * Syntax 2: `hw_irqe( hw_irq(object [, irq_name]) )`
 * @hideinitializer
 */
#define hw_irqe(...)		_hw_irqe_2(hw_irq(__VA_ARGS__))
#define _hw_irqe_2(...)		HW_G2(_hw_irqe,HW_IS(_irq,__VA_ARGS__))(__VA_ARGS__)
#define _hw_irqe_0(...)		__VA_ARGS__
#define _hw_irqe_1(t,v,o,e,f,c)	_hw_reg(o,e)


/**
 * @brief Definition of the flag bit of an IRQ
 *
 * Syntax 1: `hw_irqf( object [, irq_name] )`
 *
 * Syntax 2: `hw_irqf( hw_irq(object [, irq_name]) )`
 * @hideinitializer
 */
//#define hw_irqf(...)		_hw_irqf_2(hw_irqx(__VA_ARGS__))
#define hw_irqf(...)		_hw_irqf_2(hw_irq(__VA_ARGS__))
#define _hw_irqf_2(...)		HW_G2(_hw_irqf,HW_IS(_irq,__VA_ARGS__))(__VA_ARGS__)
#define _hw_irqf_0(...)		__VA_ARGS__
#define _hw_irqf_1(t,v,o,e,f,c)	_hw_reg(o,f)


/**
 * @brief Definition of the clear bit of an IRQ
 *
 * Syntax 1: `hw_irqc( object [, irq_name] )`
 *
 * Syntax 2: `hw_irqc( hw_irq(object [, irq_name]) )`
 * @hideinitializer
 */
#define hw_irqc(...)		_hw_irqc_2(hw_irq(__VA_ARGS__))
#define _hw_irqc_2(...)		HW_G2(_hw_irqc,HW_IS(_irq,__VA_ARGS__))(__VA_ARGS__)
#define _hw_irqc_0(...)		__VA_ARGS__
#define _hw_irqc_1(t,v,o,e,f,c)	_hw_reg(o,c)


#if !defined __ASSEMBLER__

#define _hw_mthd_hw_turn__irq		, _hw_turn_irq
/**
 * @ingroup private
 * @brief  Turn an IRQ on/off
 * @hideinitializer
 */
#define _hw_turn_irqa(v,o,e,f,c, ...)					\
  HW_G2(_hw_turn_irqa, HW_IS(,_hw_state_##__VA_ARGS__))(o,e, __VA_ARGS__,)
#define _hw_turn_irqa_0(o,e, ...)					\
  HW_ERR("expected `on` or `off`, got `" HW_QUOTE(__VA_ARGS__) "` instead.")
/* #define _hw_turn_irq_vstate_1(o,e,v, ...)				\ */
/*   HW_TX(_hw_write_reg( o,e, HW_A1(_hw_state_##v)), __VA_ARGS__) */


#define _hw_mthd_hwa_turn__irq		, _hwa_turn_irq
/**
 * @ingroup private
 * @brief  Turn an IRQ on/off
 * @hideinitializer
 */
#define _hwa_turn_irqa(v,o,e,f,c, ...)					\
  HW_G2(_hwa_turn_irqa, HW_IS(,_hw_state_##__VA_ARGS__))(o,e, __VA_ARGS__,)
#define _hwa_turn_irqa_0(o,e, ...)					\
  HW_ERR("expected `on` or `off`, got `" HW_QUOTE(__VA_ARGS__) "` instead.")
/* #define _hwa_turn_irq_vstate_1(o,e,v, ...)			\ */
/*   HW_TX(_hwa_write_reg(o,e, HW_A1(_hw_state_##v)), __VA_ARGS__) */


/**
 * @ingroup public_irq_instructions
 * @brief  Stat an IRQ enable bit
 *
 * Get the state of the IRQ enable bit.
 *
 * @code
 * hw_stat_irqe( hw_counter0, overflow )
 * @endcode
 * @hideinitializer
 */
#define hw_stat_irqe(...)		_hw_statirqe_2(hw_irq(__VA_ARGS__))
#define _hw_statirqe_2(...)		HW_G2(_hw_statirqe,HW_IS(_irq,__VA_ARGS__))(__VA_ARGS__)
#define _hw_statirqe_0(...)		__VA_ARGS__
#define _hw_statirqe_1(t,v,o,e,...)	_hw_read_reg(o,e)


/**
 * @ingroup public_irq_instructions
 * @brief  Stat an IRQ flag bit
 *
 * Get the state of the IRQ flag bit.
 *
 * @code
 * hw_stat_irqf( hw_counter0, overflow )
 * @endcode
 * @hideinitializer
 */
#define hw_stat_irqf(...)		_hw_statirqf_2(hw_irq(__VA_ARGS__))
#define _hw_statirqf_2(...)		HW_G2(_hw_statirqf,HW_IS(_irq,__VA_ARGS__))(__VA_ARGS__,)
#define _hw_statirqf_0(...)		__VA_ARGS__
#define _hw_statirqf_1(t,v,o,e,f,...)	_hw_read_reg(o,f)


/**
 * @ingroup public_irq_instructions
 * @brief  Turn an IRQ on/off
 * @hideinitializer
 *
 * Enable or disable an IRQ by setting the IRQ enable bit to 0 or 1.
 *
 * @code
 * hw_turn_irq( hw_counter0, overflow, on );
 * @endcode
 */
#define hw_turn_irq(...)		_hw_turnirq_2(hw_irqx(__VA_ARGS__,))
#define _hw_turnirq_2(...)		HW_G2(_hw_turnirq,HW_IS(_irq,__VA_ARGS__))(__VA_ARGS__)
#define _hw_turnirq_0(...)		__VA_ARGS__
#define _hw_turnirq_1(t,...)		_hw_turn##t(__VA_ARGS__)


/**
 * @ingroup public_irq_instructions
 * @brief  Turn an IRQ on/off
 * @hideinitializer
 *
 * Enable or disable an IRQ by setting the IRQ enable bit to 0 or 1.
 *
 * @code
 * hw_turn_irq( hw_counter0, overflow, on );
 * @endcode
 */
#define hwa_turn_irq(...)		_hwa_turnirq_2(hw_irqx(__VA_ARGS__,))
#define _hwa_turnirq_2(...)		HW_G2(_hwa_turnirq,HW_IS(_irq,__VA_ARGS__))(__VA_ARGS__)
#define _hwa_turnirq_0(...)		__VA_ARGS__
#define _hwa_turnirq_1(t,...)		_hwa_turn##t(__VA_ARGS__)


/**
 * @ingroup private
 * @brief  Clear an IRQ flag
 * @hideinitializer
 */
//#define _hw_clear_irq(v,o,e,f,c, ... )	HW_TX(_hw_write_reg(o,c, 1 ), __VA_ARGS__)
#define _hw_mthd_hw_clear__irq		, _hw_clear_irq


/**
 * @ingroup private
 * @brief  Clear irq flag
 * @hideinitializer
 */
//#define _hwa_clear_irq(v,o,e,f,c, ... )	HW_TX(_hwa_write_reg(o,c, 1 ), __VA_ARGS__)
#define _hw_mthd_hwa_clear__irq		, _hwa_clear_irq


/**
 * @ingroup public_irq_instructions
 * @brief Clear an IRQ flag
 * @hideinitializer
 *
 * This is a synonym for hw_clear_irq()
 */
#define hw_clear_irqf(...)		_hw_clearirq_2(hw_irqx(__VA_ARGS__,))


/**
 * @ingroup public_irq_instructions
 * @brief Clear an IRQ flag
 * @hideinitializer
 *
 * @code
 * hw_clear_irq( hw_counter0, overflow );
 * @endcode
 */
#define hw_clear_irq(...)		_hw_clearirq_2(hw_irqx(__VA_ARGS__,))
#define _hw_clearirq_2(...)		HW_G2(_hw_clearirq,HW_IS(_irq,__VA_ARGS__))(__VA_ARGS__)
#define _hw_clearirq_0(...)		__VA_ARGS__
#define _hw_clearirq_1(t,...)		_hw_clear_irq(__VA_ARGS__)


/**
 * @ingroup public_irq_instructions
 * @brief	Clear an IRQ flag
 * @hideinitializer
 *
 * This is a synonym for hwa_clear_irq()
 */
#define hwa_clear_irqf(...)		_hwa_clearirq_2(hw_irqx(__VA_ARGS__,))

/**
 * @ingroup public_irq_instructions
 * @brief Clear an IRQ flag
 * @hideinitializer
 *
 * @code
 * hwa_clear_irq( hw_counter0, overflow );
 * @endcode
 */
#define hwa_clear_irq(...)		_hwa_clearirq_2(hw_irqx(__VA_ARGS__,))
#define _hwa_clearirq_2(...)		HW_G2(_hwa_clearirq,HW_IS(_irq,__VA_ARGS__))(__VA_ARGS__)
#define _hwa_clearirq_0(...)		__VA_ARGS__
#define _hwa_clearirq_1(t,...)		_hwa_clear_irq(__VA_ARGS__)


/**
 * @ingroup private
 * @brief	Stat irq flag
 * @hideinitializer
 */
#define _hw_stat_irq(v,o,e,f, ... )	HW_TX((_hw_read_reg(o,e)==1), __VA_ARGS__)
#define _hw_mthd_hw_stat__irq		, _hw_stat_irq

#endif /* !defined __ASSEMBLER__ */
