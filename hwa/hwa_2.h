
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief HWA definitions that produce C code
 */

/**
 * @ingroup public_context_instructions
 * @brief Create a context to memorize what the `hwa_...(...)` instructions do.
 *
 * Nothing is written into the hardware until `hwa_commit()` is called.
 * @hideinitializer
 */
/*
 * Expands _hwa_begin_all() that must be defined in hwa_<device>_2.h.
 */
#define hwa_begin()							\
  _hwa_check_optimizations(0);						\
  hwa_t hwa_st ; hwa_t *hwa = &hwa_st ;					\
  _hwa_setup_context(hwa) ;						\
  uint8_t hwa_xcommit = 0 /* Will warn if hwa_commit() is not called */


/**
 * @ingroup public_context_instructions
 * @brief Create a context to memorize what the `hwa_...(...)` instructions do.
 *
 * The context is initialized with the values the registers have after a
 * system reset.
 *
 * Nothing is written into the hardware until `hwa_commit()` is called.
 * @hideinitializer
 */
#define hwa_begin_from_reset()			\
  _hwa_check_optimizations(0);			\
  hwa_t hwa_st ; hwa_t *hwa = &hwa_st ;		\
  _hwa_setup_context(hwa) ;			\
  _hwa_init_context(hwa) ;			\
  hwa_nocommit() ;				\
  uint8_t hwa_xcommit = 0


/**
 * @ingroup public_context_instructions
 * @brief  Commit configuration to hardware.
 *
 * Solve the configuration stored into the HWA context, then do the required
 * hardware register writes.
 *
 * @hideinitializer
 */
/* _hwa_commit_all() must be defined somewhere in the device-specific files.
 */
#define hwa_commit()					\
  do {							\
    uint8_t foo __attribute__((unused)) = hwa_xcommit ;	\
    hwa->commit = 1 ;					\
    _hwa_commit_context(hwa);				\
  } while(0)


/**
 * @ingroup public_context_instructions
 * @brief  Same as hwa_commit() but do not write into hardware.
 *
 * This is used to put the HWA context in a known state before modifying it.
 *
 * @hideinitializer
 */
#define hwa_nocommit()				\
  do {						\
    hwa->commit = 0 ;				\
    _hwa_commit_context(hwa);			\
  } while(0)


/**
 * @ingroup public_obj_instructions
 * @brief Read from an object (method)
 * @hideinitializer
 *
 * Syntax: `hw_read( object [,...] );`
 */
/*  Variable arguments list is required. E.g. `hw_read( hw_flash0, address )`
 */
#define hw_read(...)			HW_MTHD(hw_read, __VA_ARGS__,)

/**
 * @ingroup public_obj_instructions
 * @brief Read multiple bytes from an object (method)
 *
 * Syntax: `hw_read_bytes( object [,...] );`
 * @hideinitializer
 */
#define hw_read_bytes(...)		HW_MTHD(hw_read_bytes, __VA_ARGS__,)

/**
 * @ingroup public_reg_instructions
 * @brief Read one register of an object (method)
 *
 * Syntax: `hw_read_reg( object, register );`
 * @hideinitializer
 */
#define hw_read_reg(...)		HW_MTHD(hw_read, hw_reg(__VA_ARGS__))

/**
 * @ingroup public_obj_instructions
 * @brief Read from an object with interrupts disabled (method)
 *
 * Syntax: `hw_atomic_read( object [,...] );`
 * @hideinitializer
 */
#define hw_atomic_read(...)		HW_MTHD(hw_atomic_read, __VA_ARGS__)

/**
 * @ingroup public_obj_instructions
 * @brief Write in an object with interrupts disabled (method)
 *
 * Syntax: `hw_atomic_write( object [,...] );`
 * @hideinitializer
 */
#define hw_atomic_write(...)		HW_MTHD(hw_atomic_write, __VA_ARGS__)


/**
 * @ingroup private
 * @brief Read one register of an object
 *
 * Syntax: `_hw_read( object, register );`
 * @hideinitializer
 */
#define _hw_read_reg(o,r)		_HW_SPEC(_hw_read, _hw_reg(o,r))


/**
 * @ingroup private
 * @brief Read one register of an object with interrupts disabled
 *
 * Syntax: `_hw_atomic_read( object, register );`
 * @hideinitializer
 */
#define _hw_atomic_read_reg(o,r)		_HW_SPEC(_hw_atomic_read, _hw_reg(o,r))


/**
 * @ingroup public_obj_instructions
 * @brief Write into an object (method)
 *
 * Syntax: `hw_write( object [,...], value );`
 * @hideinitializer
 */
/*  Variable arguments list is required. E.g. `hw/hwa_write( hw_flash0, address, value )`
 */
#define hw_write(...)			HW_MTHD(hw_write, __VA_ARGS__,)

/**
 * @ingroup public_obj_instructions
 * @brief Write into an object (method)
 *
 * Syntax: `hwa_write( object [,...], value );`
 * @hideinitializer
 */
#define hwa_write(...)			HW_MTHD(hwa_write, __VA_ARGS__,)

/**
 * @ingroup public_obj_instructions
 * @brief Write multiple bytes into an object (method)
 *
 * Syntax: `hw_write_bytes( object, ... );`
 * @hideinitializer
 */
#define hw_write_bytes(...)		HW_MTHD(hw_write_bytes, __VA_ARGS__,)

/**
 * @ingroup public_reg_instructions
 * @brief Write into one register of an object (method)
 *
 * Syntax: `hw_write_reg( object, register, value );`
 * @hideinitializer
 */
#define hw_write_reg(o,r,v)		HW_MTHD(hw_write, hw_reg(o,r),v)

/**
 * @ingroup public_reg_instructions
 * @brief Write into one register of an object (method)
 *
 * Syntax: `hwa_write( object, register, value );`
 * @hideinitializer
 */
#define hwa_write_reg(o,r,v)		HW_MTHD(hwa_write, hw_reg(o,r),v)

/**
 * @ingroup private
 * @brief Write one register of an object
 *
 * Syntax: `_hw_write_reg( object, register, value );`
 * @hideinitializer
 */
#define _hw_write_reg(o,r,v)		_HW_SPEC(_hw_write, hw_reg(o,r), v)

/**
 * @ingroup private
 * @brief Write one register of an object
 *
 * Syntax: `_hwa_write_reg( object, register, value );`
 * @hideinitializer
 */
#define _hwa_write_reg(o,r,v)		_HW_SPEC(_hwa_write, _hw_reg(o,r), v)


/**
 * @ingroup public_obj_instructions
 * @brief Make an object execute one of its special commands (method)
 *
 * Syntax: `hw_command( object, command [,...] );`
 * @hideinitializer
 */
#define hw_command(...)			HW_MTHD(hw_command, __VA_ARGS__,)


/**
 * @ingroup public_obj_instructions
 * @brief Configure an object (method)
 *
 * Syntax: `hw_config( object, ... );`
 * @hideinitializer
 */
#define hw_config(...)			HW_MTHD(hw_config, __VA_ARGS__,)

#define _hw_config(...)			_HW_MTHD(hw_config, __VA_ARGS__,)

/**
 * @ingroup public_obj_instructions
 * @brief Configure an object (method)
 *
 * Syntax: `hwa_config( object, ... );`
 * @hideinitializer
 */
#define hwa_config(...)			HW_MTHD(hwa_config, __VA_ARGS__,)

#define _hwa_config(...)		_HW_MTHD(hwa_config, __VA_ARGS__,)

/**
 * @ingroup public_obj_instructions
 * @brief Clear an object (method)
 *
 * Syntax: `hw_clear( object [,...] );`
 * @hideinitializer
 */
#define hw_clear(...)			HW_MTHD(hw_clear, __VA_ARGS__,)

/**
 * @ingroup public_obj_instructions
 * @brief Clear an object (method)
 *
 * Syntax: `hwa_clear( object [,...] );`
 * @hideinitializer
 */
#define hwa_clear(...)			HW_MTHD(hwa_clear, __VA_ARGS__,)


/**
 * @ingroup public_obj_instructions
 * @brief Reset an object (method)
 *
 * Syntax: `hw_reset( object [,...] );`
 * @hideinitializer
 */
#define hw_reset(...)			HW_MTHD(hw_reset, __VA_ARGS__,)

/**
 * @ingroup public_obj_instructions
 * @brief Reset an object (method)
 *
 * Syntax: `hwa_reset( object [,...] );`
 * @hideinitializer
 */
#define hwa_reset(...)			HW_MTHD(hwa_reset, __VA_ARGS__,)


/**
 * @ingroup public_obj_instructions
 * @brief Power an object on/off (method)
 *
 * Syntax: `hw_power( object, on | off );`
 * @hideinitializer
 */
#define hw_power(...)			HW_MTHD(hw_power, __VA_ARGS__,)

/**
 * @ingroup public_obj_instructions
 * @brief Power an object on/off (method)
 *
 * Syntax: `hwa_power( object, on | off );`
 * @hideinitializer
 */
#define hwa_power(...)			HW_MTHD(hwa_power, __VA_ARGS__,)


/**
 * @ingroup public_obj_instructions
 * @brief Type of the status of an object (method)
 *
 * Syntax: `hw_stat_t( object );`
 * @hideinitializer
 */
#define hw_stat_t(...)			HW_MTHD(hw_stat_t, __VA_ARGS__,)


/**
 * @ingroup public_obj_instructions
 * @brief Read the status of an object (method)
 *
 * Syntax: `hw_stat( object [,...] );`
 * @hideinitializer
 */
#define hw_stat(...)			HW_MTHD(hw_stat, __VA_ARGS__,)


/**
 * @ingroup public_obj_instructions
 * @brief Toggle an object, probably an i/o pin (method)
 *
 * Syntax: `hw_toggle( object [,...] );`
 * @hideinitializer
 */
#define hw_toggle(...)			HW_MTHD(hw_toggle, __VA_ARGS__,)

/**
 * @ingroup public_obj_instructions
 * @brief Toggle an object, probably an i/o pin (method)
 *
 * Syntax: `hwa_toggle( object [,...] );`
 * @hideinitializer
 */
#define hwa_toggle(...)			HW_MTHD(hwa_toggle, __VA_ARGS__,)


/**
 * @ingroup public_obj_instructions
 * @brief Turn an object on/off (method)
 *
 * Syntax: `hw_turn( object [,...], on | off );`
 * @hideinitializer
 */
#define hw_turn(...)			HW_MTHD(hw_turn, __VA_ARGS__,)

/**
 * @ingroup public_obj_instructions
 * @brief Turn an object on/off (method)
 *
 * Syntax: `hwa_turn( object [,...], on | off );`
 * @hideinitializer
 */
#define hwa_turn(...)			HW_MTHD(hwa_turn, __VA_ARGS__,)


/**
 * @ingroup public_obj_instructions
 * @brief Trigger object `o`.
 *
 * @hideinitializer
 */
#define hw_trigger(o)			HW_MTHD(hw_trigger, o,)

/**
 * @ingroup public_obj_instructions
 * @brief Trigger object `o`.
 *
 * @hideinitializer
 */
#define hwa_trigger(o)			HW_MTHD(hwa_trigger, o,)


#define _hw_mthd_hw_read__m1		, _hw_read__m1
#define _hw_mthd_hw_read__m2		, _hw_read__m2
#define _hw_mthd_hw_write__m1		, _hw_write__m1
#define _hw_mthd_hw_write__m2		, _hw_write__m2
#define _hw_mthd_hwa_write__m1		, _hwa_write__m1
#define _hw_mthd_hwa_write__m2		, _hwa_write__m2


/**
 * @ingroup private
 * @brief Read one group of consecutive bits from one hardware register
 * @hideinitializer
 */
#define _hw_read__m1(o,a, r,rc,ra,rwm,rfm, rbn,rbp)	\
  _hw_read_##rc(a+ra,rbn,rbp)


/**
 * @ingroup private
 * @brief Read one group of consecutive bits from one hardware register with interrupts disabled
 * @hideinitializer
 */
#define _hw_atomic_read__m1(o,a, r,rc,ra,rwm,rfm, rbn,rbp)	\
  _hw_atomic_read_##rc(a+ra,rbn,rbp)


/**
 * @ingroup private
 * @brief Read two groups of consecutive bits from two hardware registers
 * @hideinitializer
 */
#define _hw_read__m2(o,a,					\
		     r1,rc1,ra1,rwm1,rfm1,rbn1,rbp1,vbp1,	\
		     r2,rc2,ra2,rwm2,rfm2,rbn2,rbp2,vbp2)	\
  ((_hw_read_##rc1(a+ra1,rbn1,rbp1)<<vbp1) |			\
   (_hw_read_##rc2(a+ra2,rbn2,rbp2)<<vbp2))


/**
 * @ingroup private
 * @brief Write something
 *
 * Syntax: `_hw_write( ..., value );`
 * @hideinitializer
 */
#define _hw_write(...)			_hw_write_2(__VA_ARGS__) /* Internal use */
#define _hw_write_2(x,...)		_hw_write_##x(__VA_ARGS__)

/**
 * @ingroup private
 * @brief Write one group of consecutive bits into one hardware register
 * @hideinitializer
 */
#define _hw_write__m1(o,a, r,rc,ra,rwm,rfm, rbn,rbp, v)	\
  _hw_write_##rc(a+ra,rwm,rfm,rbn,rbp,v)

/**
 * @ingroup private
 * @brief Write one group of consecutive bits into one hardware register with interrupts disabled
 * @hideinitializer
 */
#define _hw_atomic_write__m1(o,a, r,rc,ra,rwm,rfm, rbn,rbp, v)	\
  _hw_atomic_write_##rc(a+ra,rwm,rfm,rbn,rbp,v)

/**
 * @ingroup private
 * @brief Write two groups of consecutive bits into two hardware registers
 * @hideinitializer
 */
#define _hw_write__m2(o,a,						\
		      rn1,rc1,ra1,rwm1,rfm1,rbn1,rbp1,vbp1,		\
		      rn2,rc2,ra2,rwm2,rfm2,rbn2,rbp2,vbp2, v)		\
  do {									\
    if ( ra1==ra2 ) {							\
      /* HWA_ERR("That should not happen"); */				\
      _hw_write_##rc1##_m( a+ra1, rwm1, rfm1,				\
			   (((1U<<rbn1)-1)<<rbp1) | (((1U<<rbn2)-1)<<rbp2), \
			   (((v>>vbp1)&((1<<rbn1)-1))<<rbp1) | (((v>>vbp2)&((1<<rbn2)-1))<<rbp2)); \
    }									\
    else {								\
      _hw_write_##rc1(a+ra1,rwm1,rfm1,rbn1,rbp1, (v>>vbp1)&((1<<rbn1)-1)); \
	_hw_write_##rc2(a+ra2,rwm2,rfm2,rbn2,rbp2, (v>>vbp2)&((1<<rbn2)-1)); \
    }									\
  } while(0)

#define _hw_writep__m1(_0,_1,r,rc,ra,rwm,rfm, bn,bp, o,v)	\
  _hw_write_##rc( o->r.a, rwm,rfm, bn,bp,v)


#define _hw_write__xob1(o,r,bn,bp,v)	_hw_write__xob1_2(_##o##_##r,o,r,bn,bp,v)
#define _hw_write__xob1_2(...)		_hw_write__xob1_3(__VA_ARGS__)
#define _hw_write__xob1_3(rc,ra,rwm,rfm,o,r,bn,bp,v)	\
  _hw_write_##rc( ra, rwm,rfm, bn,bp, v )


/* #define _hwa_write(...)			_hwa_write_2(__VA_ARGS__) /\* Internal use *\/ */
/* #define _hwa_write_2(x,...)		_hwa_write_##x(x,__VA_ARGS__) */

#define _hwa_write(...)			_HW_MTHD(hwa_write, __VA_ARGS__,)


#define _hwa_write__m1(o,a, r,rc,ra,rwm,rfm, bn,bp, v)	\
  _hwa_write_##rc( &hwa->o.r, rwm,rfm, bn,bp, v )

#define _hwa_write__m2(o,a,						\
		       r1,rc1,ra1,rwm1,rfm1,rbn1,rbp1,vbp1,		\
		       r2,rc2,ra2,rwm2,rfm2,rbn2,rbp2,vbp2, v)		\
  do {									\
    _hwa_write_##rc1(&hwa->o.r1, rwm1,rfm1, rbn1,rbp1, ((v)>>(vbp1))&((1U<<rbn1)-1)); \
      _hwa_write_##rc2(&hwa->o.r2, rwm2,rfm2, rbn2,rbp2, ((v)>>(vbp2))&((1U<<rbn2)-1)); \
  } while(0)


/**
 * @ingroup private_classes
 * @brief Object register class.
 *
 *  An `_oreg` class object is a register of an object that can be accessed with
 *  the generic instructions designed for objects.
 */
#define _hw_class__oreg


/**
 * @brief  Write the register of an object
 */
#define _hw_mthd_hwa_write__oreg	, _hwa_write_oreg
#define _hwa_write_oreg(_,o,r,v,...)	_hwa_write_reg(o,r,v) HW_EOL(__VA_ARGS__)


//#define _hw_xob1__r8(ra,rwm,rfm,bn,bp,o,r) 	_m1, o,0, r,_r8,ra,rwm,rfm, bn,bp
//_hwa_write__xob1(_xob1,hw_adc0, did, 1, 5, 1);
#define _hwa_write__xob1(t,o,r,bn,bp,v)	_hwa_write__xob1_2(_##o##_##r,o,r,bn,bp,v)
#define _hwa_write__xob1_2(...)		_hwa_write__xob1_3(__VA_ARGS__)
#define _hwa_write__xob1_3(rc,ra,rwm,rfm,o,r,bn,bp,v)	\
  _hwa_write_##rc( &hwa->o.r, rwm,rfm, bn,bp, v )

/*  Added for io1a_2.h:   _hwa_write(_##o##_##did, 1);
 */
#define _hw_mthd_hwa_write___xob1	, _hwa__write__xob1
#define _hwa__write__xob1(t,o,r,bn,bp,v,_)	_hwa_write__xob1(t,o,r,bn,bp,v)

/**
 * @ingroup private
 * @brief Write some bits of a hardware register
 * @hideinitializer
 *
 *	_hw_write_reg_m( o, r, m, v );
 */
#define _hw_write_reg_m(o,r,m,v)	_hw_wrrm1(_hw_reg(o,r),m,v)
#define _hw_wrrm1(...)			_hw_wrrm2(__VA_ARGS__)
#define _hw_wrrm2(t,...)		_hw_wrrm_##t(__VA_ARGS__)
#define _hw_wrrm__m1(o,a,r,rc,ra,rwm,rfm,rbn,rbp, m, v)	\
    _hw_write_##rc##_m(a+ra,rwm,rfm,m,v)

/**
 * @ingroup private
 * @brief Write some bits of a hardware register
 * @hideinitializer
 *
 *	_hwa_write_reg_m( o, r, m, v );
 */
#define _hwa_write_reg_m(o,r,m,v)	_hwa_wrrm1(_hw_reg(o,r),m,v)
#define _hwa_wrrm1(...)			_hwa_wrrm2(__VA_ARGS__)
#define _hwa_wrrm2(t,...)		_hwa_wrrm_##t(__VA_ARGS__)
#define _hwa_wrrm__m1(o,a,r,rc,ra,rwm,rfm,rbn,rbp, m, v)	\
    _hwa_write_##rc##_m(&hwa->o.r,rwm,rfm,m,v)


/**
 * @brief Initialize the HWA context registers addresses of an object
 */
//#define _hwa_setup(o)			_HW_SPEC(_hwa_setup,_##o,o)
#define _hwa_setup(o)			_hwa_setup_2(_##o,o)
#define _hwa_setup_2(...)		_hwa_setup_3(__VA_ARGS__)
#define _hwa_setup_3(c,i,a,o)		_hwa_setup_##c(o,i,a)


/**
 * @brief Initialize the HWA context registers of an object with their reset value
 */
//#define _hwa_init(o)			_HW_SPEC(_hwa_init,_##o,o)
#define _hwa_init(o)			_hwa_init_2(_##o,o)
#define _hwa_init_2(...)		_hwa_init_3(__VA_ARGS__)
#define _hwa_init_3(c,i,a,o)		_hwa_init_##c(o,i,a)


/**
 * @brief Solve the configuration of an object
 */
#define _hwa_solve(o)			_hwa_solve_2(o,_##o)
#define _hwa_solve_2(...)		_hwa_solve_3(__VA_ARGS__)
#define _hwa_solve_3(o,c,...)		_hwa_solve_##c(o,__VA_ARGS__)


/**
 * @brief Commit the registers of an object
 */
/* #define _hwa_commit(o)			_HW_SPEC(_hwa_commit,_##o,o) */
#define _hwa_commit(o)			_hwa_commit_2(_##o,o)
#define _hwa_commit_2(...)		_hwa_commit_3(__VA_ARGS__)
#define _hwa_commit_3(c,i,a,o)		_hwa_commit_##c(o,i,a)


/**
 * @ingroup private
 * @brief Create a HWA register
 * @hideinitializer
 */
/* #define _hwa_begin_reg(o,a,r)			_hwa_begin_reg_2(o,a,r,_##o##_##r) */
/* #define _hwa_begin_reg_2(...)			_hwa_begin_reg_3(__VA_ARGS__) */
/* #define _hwa_begin_reg_3(o,a,r, rc,ra, ... )	_hwa_begin_##rc( &hwa->o.r, a+ra ) */

#define _hwa_setup_reg(o,r)			_hwa_setup_reg_2(_hw_hreg(o,r))
#define _hwa_setup_reg_2(...)			_hwa_setup_reg_3(__VA_ARGS__)
#define _hwa_setup_reg_3(rt,ra,rwm,rfm,o,c,a,r)	_hwa_setup_##rt(&hwa->o.r, a+ra)


/**
 * @ingroup private
 * @brief Initialize an HWA register of an object with its reset value
 * @hideinitializer
 */
/* #define _hwa_init_reg(o,r,v)			_hwa_init_reg_2(o,r,_##o##_##r,v) */
/* #define _hwa_init_reg_2(...)			_hwa_init_reg_3(__VA_ARGS__) */
/* #define _hwa_init_reg_3(o,r, rc,ra,rwm,rfm, v)	_hwa_set_##rc( &hwa->o.r, v ) */

#define _hwa_init_reg(o,r,v)			_hwa_init_reg_2(_hw_hreg(o,r),v)
#define _hwa_init_reg_2(...)			_hwa_init_reg_3(__VA_ARGS__)
#define _hwa_init_reg_3(rt,ra,rwm,rfm,o,c,a,r,v)	_hwa_set_##rt( &hwa->o.r, v )


/**
 * @ingroup private
 * @brief Commit one object hardware register
 * @hideinitializer
 */
/* #define _hwa_commit_reg(o,r)			_hwa_commit_reg_2(&hwa->o.r,_##o##_##r) */
/* #define _hwa_commit_reg_2(...)			_hwa_commit_reg_3(__VA_ARGS__) */
/* #define _hwa_commit_reg_3(p,rc,ra,rwm,rfm)	_hwa_commit_##rc(p,rwm,rfm,hwa->commit) */

/* #define _hwa_commit_hreg(o,r)			_hwa_commit_hreg_2(_hw_hreg(o,r)) */
/* #define _hwa_commit_hreg_2(...)			_hwa_commit_hreg_3(__VA_ARGS__) */
/* #define _hwa_commit_hreg_3(rt,ra,rwm,rfm,o,c,a,r)	\ */
/*   _hwa_commit_##rt(&hwa->o.r,rwm,rfm,hwa->commit) */

#define _hwa_commit_reg(o,r)			_hwa_commit_reg_2(_hw_reg(o,r))
#define _hwa_commit_reg_2(...)			_hwa_commit_reg_3(__VA_ARGS__)
#define _hwa_commit_reg_3(rt,...)		_hwa_commit_reg_##rt(__VA_ARGS__)

#define _hwa_commit_reg__m1(o,a,r,rt,ra,rwm,rfm,bn,bp)	\
  _hwa_commit_##rt(&hwa->o.r,rwm,rfm,hwa->commit)


/**
 * @ingroup private
 * @brief Get the mmask of the logical register `r` of object `o`.
 *
 * The mmask is set each time a hwa_write() is performed. It is reset after the
 * value has been committed.
 *
 * @hideinitializer
 */
#define _hwa_mmask(o,r)					_HW_SPEC(_hwa_mmask,_hw_reg(o,r))
#define _hwa_mmask__m1(o,a,r,rc,ra,rwm,rfm,bn,bp)	(((hwa->o.r.mmask)>>bp)&((1U<<bn)-1))


/**
 * @ingroup private
 * @brief Get the value to be committed for the logical register `r` of object `o`.
 * @hideinitializer
 */
#define _hwa_mvalue(o,r)				_HW_SPEC(_hwa_mvalue,_hw_reg(o,r))
#define _hwa_mvalue__m1(o,a,r,rc,ra,rwm,rfm,bn,bp)	(((hwa->o.r.mvalue)>>bp)&((1U<<bn)-1))


/**
 * @ingroup private
 * @brief Get the last committed value for the logical register `r` of object `o`.
 * @hideinitializer
 */
#define _hwa_ovalue(o,r)				_HW_SPEC(_hwa_ovalue,_hw_reg(o,r))
#define _hwa_ovalue__m1(o,a,r,rc,ra,rwm,rfm,bn,bp)	(((hwa->o.r.ovalue)>>bp)&((1U<<bn)-1))


/**
 * @ingroup private
 * @brief Set the value of the logical register `r` of the object `o` in the context to `v` without setting the modification mask (mmask).
 * @hideinitializer
 */
#define _hwa_set_reg(o,r,v)				_HW_SPEC(_hwa_set_reg,_hw_reg(o,r),v)
#define _hwa_set_reg__m1(o,a,r,rc,ra,rwm,rfm,bn,bp,v)			\
    hwa->o.r.mvalue = (((hwa->o.r.mvalue)>>bp) & ~((1U<<bn)-1)) | (v<<bp)



HW_INLINE void _hwa_setup__r8 ( hwa_r8_t *r, intptr_t a )
{
  r->a		= a ;
  r->mmask	= 0 ;
  r->mvalue	= 0 ;
  r->omask	= 0 ;
  r->ovalue	= 0 ;
}

HW_INLINE void _hwa_setup__r16 ( hwa_r16_t *r, intptr_t a )
{
  r->a		= a ;
  r->mmask	= 0 ;
  r->mvalue	= 0 ;
  r->omask	= 0 ;
  r->ovalue	= 0 ;
}

HW_INLINE void _hwa_setup__r32 ( hwa_r32_t *r, intptr_t a )
{
  r->a		= a ;
  r->mmask	= 0 ;
  r->mvalue	= 0 ;
  r->omask	= 0 ;
  r->ovalue	= 0 ;
}


/** 
 * @ingroup private
 * @brief  Initialize a HWA register to a specific value (usually the reset value).
 * @hideinitializer
 */
HW_INLINE void _hwa_set__r8 ( hwa_r8_t *r, uint8_t v )
{
  if ( r->mmask )
    HWA_ERR("commit required before resetting.");

  r->mmask = 0xFF ;
  r->mvalue = v ;
}

HW_INLINE void _hwa_set__r16 ( hwa_r16_t *r, uint16_t v )
{
  if ( r->mmask )
    HWA_ERR("commit required before resetting.");

  r->mmask = 0xFFFF ;
  r->mvalue = v ;
}

HW_INLINE void _hwa_set__r32 ( hwa_r32_t *r, uint32_t v )
{
  if ( r->mmask )
    HWA_ERR("commit required before resetting.");

  r->mmask = 0xFFFFFFFF ;
  r->mvalue = v ;
}


/**
 * @ingroup private
 * @brief  Write into one 8-bit context register.
 *
 * Write value `v` into `bn` consecutive bits starting at least significant
 * position `bp` of the context register pointed by `r`. Trying to write `1`s
 * into non-writeable bits triggers an error.
 *
 * The mask of modified values `mmask` is set according to `bn` and `bp` even if
 * the value is not modified. `_hwa_commit__r8()` will check if the register has
 * effectively been modified.
 *
 * @param r	register pointer.
 * @param rwm	writeable bits mask of the register.
 * @param rfm	flag bits mask of the register.
 * @param bn	number of consecutive bits concerned.
 * @param bp	position of the least significant bit in the register.
 * @param v	value to write.
 */
HW_INLINE void _hwa_write__r8 ( hwa_r8_t *r, 
				uint8_t rwm, uint8_t rfm,
				uint8_t bn, uint8_t bp, uint8_t v )
{
  if (bn == 0)
    HWA_ERR("no bit to be changed?");

  if (v > (1U<<bn)-1)
    HWA_ERR("value too high for number of bits.");

  uint8_t sm = ((1U<<bn)-1) << bp ;	/* shifted mask  */

  //  *((volatile uint8_t*)0) = sm ;

  uint8_t sv = v << bp ;		/* shifted value */

  //  *((volatile uint8_t*)0) = sv ;

  if ((rwm & sm) != sm)
    HWA_ERR("bits not writeable.");

  if ((r->mmask & sm) != 0 && (r->mvalue & sm) != sv)
    HWA_ERR("committing is required before setting a new value.");

  if ( sm & rfm )
    if ( v == 0 )
      HWA_ERR("flag bit can only be cleared by writing 1 into it.");

  r->mmask |= sm ;
  r->mvalue = (r->mvalue & ~sm) | (sm & sv) ;
}


/**
 * @ingroup private
 * @brief  Write into one 8-bit context register.
 *
 * Write value `v` into `msk` bits of the context register pointed by
 * `r`. Trying to write `1`s into non-writeable bits triggers an error.
 *
 * The mask of modified values `mmask` is set according to `msk` even if
 * the value is not modified. `_hwa_commit__r8()` will check if the register has
 * effectively been modified.
 *
 * @param r	register pointer.
 * @param rwm	writeable bits mask of the register.
 * @param rfm	flag bits mask of the register.
 * @param msk	mask of bits concerned.
 * @param v	value to write.
 */
HW_INLINE void _hwa_write__r8_m ( hwa_r8_t *r, 
				  uint8_t rwm, uint8_t rfm,
				  uint8_t msk, uint8_t v )
{
  if (v & ~msk)
    HWA_ERR("value overflows the mask.");

  if ((rwm & msk) != msk)
    HWA_ERR("trying to modify bits that are not writeable.");

  if ((r->mmask & msk) != 0 && (r->mvalue & msk) != v)
    HWA_ERR("committing is required before setting a new value.");

  if ( msk & rfm )
    if ( v == 0 )
      HWA_ERR("flag bit can only be cleared by writing 1 into it.");

  r->mmask |= msk ;
  r->mvalue = (r->mvalue & ~msk) | (msk & v) ;
}


HW_INLINE void _hwa_write__r16 ( hwa_r16_t *r,
				 uint16_t rwm, uint16_t rfm,
				 uint8_t bn, uint8_t bp, uint16_t v )
{
  if (bn == 0)
    HWA_ERR("no bit to be changed?");

  if (v > (1U<<bn)-1)
    HWA_ERR("value too high for bits number.");

  uint16_t sm = ((1U<<bn)-1) << bp ;	/* shifted mask  */
  uint16_t sv = v << bp ;		/* shifted value */

  if ((rwm & sm) != sm)
    HWA_ERR("bits not writeable.");

  if ((r->mmask & sm) != 0 && (r->mvalue & sm) != sv)
    HWA_ERR("commit required before setting a new value.");

  if ( sm & rfm )
    if ( v == 0 )
      HWA_ERR("flag bit can only be cleared by writing 1 into it.");

  r->mmask |= sm ;
  r->mvalue = (r->mvalue & ~sm) | (sm & sv) ;
}


HW_INLINE void _hwa_write__r32_m ( hwa_r32_t *r, 
				   uint32_t rwm, uint32_t rfm,
				   uint32_t msk, uint32_t v )
{
  if ( (v & msk) != v )
    HWA_ERR("value overflows the mask.");

  if ((rwm & msk) != msk)
    HWA_ERR("trying to modify bits that are not writeable.");

  if ((r->mmask & msk) != 0 && (r->mvalue & msk) != v)
    HWA_ERR("committing is required before setting a new value.");

  if ( msk & rfm )
    if ( v == 0 )
      HWA_ERR("flag bit can only be cleared by writing 1 into it.");

  r->mmask |= msk ;
  r->mvalue = (r->mvalue & ~msk) | (msk & v) ;
}

HW_INLINE void _hwa_write__r32 ( hwa_r32_t *r, 
				 uint32_t rwm, uint32_t rfm,
				 uint8_t bn, uint8_t bp, uint32_t v )
{
  _hwa_write__r32_m( r, rwm, rfm, ((1ULL<<bn)-1)<<bp, v<<bp );
}


/**
 * @ingroup private
 * @brief Trigger an error if optimizers failed to remove this code
 * @hideinitializer
 */
HW_INLINE void _hwa_check_optimizations ( uint8_t x )
{
  if (x) { HWA_ERR("you may have forgotten to turn optimizations on."); }
}



#if 0
/**
 * @ingroup private
 * @brief Read one register of an object, knowing only the class and having a
 * pointer on the object in the context.
 *
 * Syntax: `_hw_read_reg_p( pointer, class, register );`
 * @hideinitializer
 */
#define _hw_read_reg_p(o,c,r)		_HW_SPEC(_hw_readp, _hw_reg_p(o,c,r))
/**
 * @ingroup private
 * @brief Write one register of an object, knowing only the class and having a
 * pointer on the object in the context.
 *
 * Syntax: `_hw_write_reg_p( pointer, class, register, value );`
 * @hideinitializer
 */
#define _hw_write_reg_p(o,c,r,v)	_HW_SPEC(_hw_write, _hw_reg_p(o,c,r), v)

/**
 * @ingroup private
 * @brief Write one register of an object, knowing only the class and having a
 * pointer on the object in the context.
 *
 * Syntax: `_hwa_write_reg_p( pointer, class, register, value );`
 * @hideinitializer
 */
#define _hwa_write_reg_p(o,c,r,v)	_HW_SPEC(_hwa_write, _hw_reg_p(o,c,r), v)

#define _hwa_write__m1_p( o,rc,rwm,rfm, bn,bp, v )	\
  _hwa_write_##rc( o, rwm,rfm, bn,bp,v )

#define _hwa_write__m2_p( p1,rc1,rwm1,rfm1,rbn1,rbp1,vbp1,		\
			  p2,rc2,rwm2,rfm2,rbn2,rbp2,vbp2, v )		\
  do { _hwa_write_##rc1(p1, rwm1,rfm1, rbn1,rbp1, ((v)>>(vbp1))&((1U<<rbn1)-1)); \
      _hwa_write_##rc2(p2, rwm2,rfm2, rbn2,rbp2, ((v)>>(vbp2))&((1U<<rbn2)-1)); } while(0)

/**
 * @brief Initialize the HWA context registers addresses of an object (using a pointer in the HWA context)
 */
#define _hwa_setup_p(o)		_hwa_setup_p_2(o, _##o)
#define _hwa_setup_p_2(...)		_hwa_setup_p_3(__VA_ARGS__)
#define _hwa_setup_p_3(o,c,i,a)	_hwa_setup_p_##c(&hwa->o,a)

/**
 * @brief Initialize the HWA context registers of an object with their reset value (using a pointer in the HWA context)
 */
#define _hwa_init_p(o)			_hwa_init_p_2(o, _##o)
#define _hwa_init_p_2(...)		_hwa_init_p_3(__VA_ARGS__)
#define _hwa_init_p_3(o,c,i,a)		_hwa_init_p_##c(&hwa->o)

/**
 * @ingroup private
 * @brief Solve the configuration of an object using a pointer
 * @hideinitializer
 */
#define _hwa_solve_p(o)			_hwa_solve_p_2(o, _##o)
#define _hwa_solve_p_2(...)		_hwa_solve_p_3(__VA_ARGS__)
#define _hwa_solve_p_3(o,c,i,a)		_hwa_solve_p_##c(hwa, &hwa->o)

/**
 * @ingroup private
 * @brief Commit the registers of an object using a pointer
 * @hideinitializer
 */
#define _hwa_commit_p(o)		_hwa_commit_p_2(o, _##o)
#define _hwa_commit_p_2(...)		_hwa_commit_p_3(__VA_ARGS__)
#define _hwa_commit_p_3(o,c,i,a)	_hwa_commit_p_##c(hwa,&hwa->o)

/**
 * @ingroup private
 * @brief Create a HWA register for an object pointed by p
 * @hideinitializer
 */
#define _hwa_setup_reg_p(o,a,c,r)		_hwa_berp_2(o,a,c,r,_hw_##c##_##r)
#define _hwa_berp_2(...)			_hwa_berp_3(__VA_ARGS__)
#define _hwa_berp_3(o,a,c,r, rc,ra,rwm,rfm)	_hwa_setup_##rc(&((o)->r),a+ra)

/**
 * @ingroup private
 * @brief Commit hardware register r of class c pointed by p
 *
 * @hideinitializer
 */
#define _hwa_commit_reg_p(o,c,r)	_hwa_commitregp_2(_hw_reg_p(o,c,r))
#define _hwa_commitregp_2(...)		_hwa_commitregp_3(__VA_ARGS__)
#define _hwa_commitregp_3(t,...)	_hwa_commitregp_##t(__VA_ARGS__)

#define _hwa_commitregp__m1_p(o,rc,rwm,rfm, bn,bp)	_hwa_commit_##rc(o,rwm,rfm,hwa->commit)
#endif
