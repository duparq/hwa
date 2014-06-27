
/** \brief	Element a1 of the list a0,a1,...
 */
#define HW_A1(...)		_HW_A1_2(__VA_ARGS__,,)
#define _HW_A1_2(a0,a1,...)	a1


/** \brief	Element a2 of the list a0,a1,a2,...
 */
#define HW_A2(...)		_HW_A2_2(__VA_ARGS__,,,)
#define _HW_A2_2(a0,a1,a2,...)	a2


/** \brief	Element a2 of the list a0,a1,a2,...
 */
#define HW_A3(...)			_HW_A3_2(__VA_ARGS__,,,,)
#define _HW_A3_2(a0,a1,a2,a3,...)	a3


#if defined __ASSEMBLER__
#  define HW_PPERROR(msg)	.fail "HWA error: " msg
#endif


/** \brief	Remove first element from list
 */
#define HW_CDR(...)		_HW_CDR(__VA_ARGS__)
#define _HW_CDR(x,...)		__VA_ARGS__


/** \brief	Glue first two arguments
 */
#define HW_G2(...)		_HW_G2_(__VA_ARGS__,,)
#define _HW_G2_(a,b,...)	a##_##b


/** \brief	Glue first three arguments
 */
#define HW_G3(...)		_HW_G3_(__VA_ARGS__,,,)
#define _HW_G3_(a,b,c,...)	a##_##b##_##c


/** \brief	Glue "hw", a1, and a3 of the liste a0,a1,a2,a3...
 *
 *	This is used for determining if a3 is the name of a register of a
 *	peripheral named a1.
 */
#define HW_GA1A3(...)			_HW_GA1A3_2(__VA_ARGS__,,,,)
#define _HW_GA1A3_2(a0,a1,a2,a3,...)	hw##_##a1##_##a3


/*	'ok' if the first two argument are the same, 'no' otherwise
 */
#define HW_IS(...)		_HW_IS_2(__VA_ARGS__,,)
#define _HW_IS_2(x,y,...)	HW_A1(hw_is_##x##_##y,no)
#define hw_is_0_0			, ok
#define hw_is_255_255			, ok
#define hw_is_65535_65535		, ok
#define hw_is__				, ok
#define hw_is_bottom_bottom		, ok
#define hw_is_clk_clk			, ok
#define hw_is_countmode_countmode	, ok
#define hw_is_hw_end_hw_end		, ok
#define hw_is_isr_isr			, ok
#define hw_is_ok_ok			, ok
#define hw_is_per_per			, ok
#define hw_is_reg_reg			, ok
#define hw_is_state_state		, ok
#define hw_is_top_top			, ok
#define hw_is_topreg_topreg		, ok


/** \brief	'ok' if 'hw_isfn_<x>' is defined void, 'no' otherwise.
 */
#define HW_ISFN(...)		_HW_ISFN_2(__VA_ARGS__,)
#define _HW_ISFN_2(x,...)	HW_IS(,x##_isfn)


/** \brief	Quote the first element in the list
 */
#define HW_QUOTE(...)		_HW_QUOTE_2(__VA_ARGS__,)
#define _HW_QUOTE_2(x,...)	#x


/** \brief	Type of the first argument. That is:
 *		\li '0' if its type is not declared
 *		\li '1' if the type of the declared name is not declared
 *		\li 'per', 'io', 'reg' ...
 *
 *	The macro checks that the given name has a declaration whose name
 *	(probably the same as the given name) leads to a declared type.
 */
#define hw_typeof(...)		_hw_typeof_2(__VA_ARGS__,)
#define _hw_typeof_2(t,...)	HW_G2(_hw_typeof_3,HW_A1(hw_typeof_##t))(t,__VA_ARGS__)
#define _hw_typeof_3_(...)	0	/* t is not a declared type */
#define _hw_typeof_3_ok(...)	_hw_typeof_4(__VA_ARGS__)
#define _hw_typeof_4(t,n,...) 	_hw_typeof_5(hw_##n,)
#define _hw_typeof_5(...)	_hw_typeof_6(__VA_ARGS__)
#define _hw_typeof_6(t,...)	HW_G2(_hw_typeof_7,HW_A1(hw_typeof_##t))(t)
#define _hw_typeof_7_(...)	1	/* n has not a declared type */
#define _hw_typeof_7_ok(t)	t


/*	Types
 *
 *	Do not use the 1st argument of the expansion. Use the 2nd so that it is
 *	'ok' or void only whether the type is declared or not.
 */
#define hw_typeof_per		, ok, per
#define hw_typeof_io		, ok, io
#define hw_typeof_reg		, ok, reg
#define hw_typeof_regb		, ok, reg
#define hw_typeof_regbb		, ok, reg
#define hw_typeof_isr		, ok, isr


/** \brief	Address of a peripheral register
 */
#define hw_ra(...)		HW_APPLY(hw_ra, __VA_ARGS__)
#define hw_ra_reg_isfn
#define hw_ra_reg1(p,pa,r,rw,ra,riv,rwm,rbn,rbp,_end_)	(pa+ra+HW_RA_OFFSET)


/** \brief	Pointer to a peripheral register
 */
#define hw_rp(...)		HW_APPLY(hw_rp, __VA_ARGS__)
#define hw_rp_reg_isfn
#define hw_rp_reg1(p,pa,r,rw,ra,riv,rwm,rbn,rbp,_end_)	(uint##rw##_t)(pa+ra+HW_RA_OFFSET)


/** \brief	Number of bits of an io definition
 */
#define hw_bn(...)		HW_APPLY(hw_bn, __VA_ARGS__)
#define hw_bn_io_isfn
#define hw_bn_io(io,_per_,p,pc,pa,bn,bp)	bn


/** \brief	Position of least significant bit of an io definition
 */
#define hw_bp(...)		HW_APPLY(hw_bp, __VA_ARGS__)
#define hw_bp_io_isfn
#define hw_bp_io(io,_per_,p,pc,pa,bn,bp)	bp


/** \brief	Peripheral associated to an io
 */
#define hw_per(...)		HW_APPLY(hw_per, __VA_ARGS__)
#define hw_per_io_isfn
#define hw_per_io(io,_per_,p,pc,pa,bn,bp)	hw_##p


/** \brief	Name of an object
 */
#define hw_name(...)		HW_APPLY(hw_name, __VA_ARGS__)
#define hw_name_io_isfn
#define hw_name_io(io,_per_,p,pc,pa,bn,bp)	io
#define hw_name_per_isfn
#define hw_name_per(p,pc,pa)			p


/** \brief	Equality of two objects
 */
#define _hw_eq(...)		HW_APPLY(hw_eq, __VA_ARGS__)
#define hw_eq_io_isfn
#define _hw_eq_io(io0,_per_0,pn0,pc0,pa0,bn0,bp0,	\
		 _io_,io1,_per_1,pn1,pc1,pa1,bn1,bp1)	\
  (pa0==pa1 && bp0==bp1 && bn0==bn1)

#define hw_eq(a,b)		HW_G3(_hw_eq, hw_typeof(a), hw_typeof(b))(a,b)
//#define _hw_eq_io_0(_io_,io,_per_,pn,pc,pa,bn,bp, bad)	HW_PPERROR(bad " is not defined.")
#define _hw_eq_io_0(...)	0
#define _hw_eq_0_io(...)	0
#define _hw_eq_io_io(_io_0,io0,_per_0,pn0,pc0,pa0,bn0,bp0,	\
		     _io_1,io1,_per_1,pn1,pc1,pa1,bn1,bp1)	\
  (pa0==pa1 && bp0==bp1 && bn0==bn1)


/*	Specialize a function according to the arguments
 *	The __VA_ARGS__ must be of the form: type(args...)
 */
#define HW_SPCLZ(...)		_HW_SPCLZ_2(__VA_ARGS__)
#define _HW_SPCLZ_2(f,...)	f##_##__VA_ARGS__


/*	Interrupts
 */
#define HW_ISR(...)			HW_G2(_hw_isr, HW_IS(per,__VA_ARGS__))(__VA_ARGS__,)
#define _hw_isr_no(x,...)		HW_PPERROR( #x " is undeclared." )
#define _hw_isr_ok(per,pn,pc,pa,...)	HW_G2(_hw_isr_name, HW_IS(isr,HW_G2(hw_isr_##pn,__VA_ARGS__)))(pn,__VA_ARGS__)
#define _hw_isr_name_no(pn,in,...)	HW_PPERROR( #in " is not a valid interrupt name.")
#define _hw_isr_name_ok(pn,in,...)	_hw_isr_2(HW_G3(hw_isr,pn,in),__VA_ARGS__)
#define _hw_isr_2(...)			_hw_isr_3(__VA_ARGS__)
#define _hw_isr_3(_isr_, name, vector, ...)	_hw_isr_4(__VA_ARGS__, name, vector)
#define _hw_isr_4(x,...)		HW_G2(_hw_isr_a1,HW_IS(,x))(x,__VA_ARGS__)
#define _hw_isr_a1_ok(_,...)		_hw_isr_(__VA_ARGS__,)
#define _hw_isr_a1_no(attr,x,...)	HW_G2(_hw_isr_a2,HW_IS(,x))(x,__VA_ARGS__,hw_israttr_##attr)
#define _hw_isr_a2_ok(_,...)		_hw_isr_(__VA_ARGS__)
#define _hw_isr_a2_no(attr,x,...)	HW_G2(_hw_isr_a3,HW_IS(,x))(x,__VA_ARGS__ hw_israttr_##attr)
#define _hw_isr_a3_ok(_,...)		_hw_isr_(__VA_ARGS__)
#define _hw_isr_a3_no(...)		HW_PPERROR( "too many arguments." )
