

/**
 * @page atmelavr_psca
 * @section atmelavr_psca_reset Resetting the prescaler
 * You can use `clear` or `reset` to reset a prescaler.
 * @code
 * hw_clear( PRESCALER );
 * @endcode
 * @code
 * hw_reset( PRESCALER );
 * @endcode
 */
#define _hw_mthd_hw_clear__psca		, _hw_psca_clear
#define _hw_psca_clear(o,i,a,...)	HW_TX(_hw_clrpsca(o),__VA_ARGS__)
#define _hw_clrpsca(o)			_hw_write_reg(o,psr,1)

#define _hw_mthd_hw_reset__psca		, _hw_psca_clear


/**
 * @page atmelavr_psca
 * @section atmelavr_psca_freeze Freezing the prescaler
 *
 * You can halt the prescaler (and the counters connected to it) by turning it
 * off. The prescaler will start counting again after it has been turned on.
 *
 * @code
 * hw_turn( PRESCALER, on | off );
 * @endcode
 */
#define _hw_mthd_hw_turn__psca		, _hw_psca_turn
#define _hw_psca_turn(o,i,a,v,...)	HW_TX(HW_G2(_hw_turnpsca,HW_IS(,hw_state_##v))(o,v), \
					      __VA_ARGS__)

#define _hw_turnpsca_0(o,v)		HW_ERR("expected `on` or `off` but not `"#v"`.")
#define _hw_turnpsca_1(o,v)		HW_G2(_hw_turnpsca_1,HW_A1(hw_state_##v))(o)
//#define _hw_turnpsca_1_0(o)		_hw_write_reg(o,tsmpsr,3)
#define _hw_turnpsca_1_0(o)		_hw_write_reg(o,cr,0x81)
#define _hw_turnpsca_1_1(o)		_hw_write_reg(o,tsm,0)
