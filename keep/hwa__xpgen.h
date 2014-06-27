
/*	Expand arguments for the generic function (arg0)
 *
 *	The result of the expansion depends on the possibility of the
 *	application of a specialized function, based on the definition or not of
 *	the symbol: hw_<function>_<type>_isfn
 */


/*	Specialize according to the type of the first argument
 */
#define HW_XPGEN(f,...)		HW_G2(HW_XPGEN, hw_typeof(__VA_ARGS__))(f,__VA_ARGS__)

#define _HW_XPGEN_0(...)	\
  HW_PPERROR( "undeclared argument (" HW_QUOTE(HW_A1(__VA_ARGS__)) ")." )

#define _HW_XPGEN_1(...)	\
  HW_PPERROR( "argument (" HW_QUOTE(HW_A2(__VA_ARGS__)) ") is of unknown type." )

#define _HW_XPGEN_reg(...)	HW_PPERROR( "first argument must be a peripheral or io." )

#define _HW_XPGEN_io(f,...)	HW_G2(_HW_XPGEN_io, HW_IS(,f##_io_isfn))(f,__VA_ARGS__)
#define _HW_XPGEN_io_no(f,...)	HW_PPERROR( "instruction " #f "() is not applicable to io." )
#define _HW_XPGEN_io_ok(f,io,...)	f##_io(__VA_ARGS__)


#define _HW_XPGEN_per(f,t,pn,pc,...)					\
  HW_G2(_HW_XPGEN_per_PCX, HW_ISFN(HW_G3(f,pc,HW_A1(__VA_ARGS__))))(f,pn,pc,__VA_ARGS__)
#define _HW_XPGEN_per_PCX_ok(f,pn,pc,...)		\
  HW_G3(f,pc,HW_A1(__VA_ARGS__))(pn,pc,__VA_ARGS__)
#define _HW_XPGEN_per_PCX_no(f,pn,pc,...)				\
  HW_G2(_HW_XPGEN_per_PTX, HW_ISFN(HW_G3(f,per,HW_A1(__VA_ARGS__))))(f,pn,pc,__VA_ARGS__)
#define _HW_XPGEN_per_PTX_ok(f,pn,pc,...)		\
  HW_G3(f,per,HW_A1(__VA_ARGS__))(pn,pc,__VA_ARGS__)
#define _HW_XPGEN_per_PTX_no(f,pn,pc,...)				\
  HW_G2(_HW_XPGEN_per_PC, HW_ISFN(HW_G2(f,pc)))(f,pn,pc,__VA_ARGS__)
#define _HW_XPGEN_per_PC_ok(f,pn,pc,...)	\
  HW_G2(f,pc)(pn,pc,__VA_ARGS__)
#define _HW_XPGEN_per_PC_no(f,...)				\
  HW_G2(_HW_XPGEN_per_PT, HW_ISFN(f##_per))(f,__VA_ARGS__)
#define _HW_XPGEN_per_PT_ok(f,...)		\
  f##_per(__VA_ARGS__)
#define _HW_XPGEN_per_PT_no(f,...)			\
  HW_G2(_HW_XPGEN_REG, HW_ISFN(f##_reg))(f,__VA_ARGS__)


/*	Memory access
 *
 *	Note: 'hw_end' is appended after the arguments.
 */
#define _HW_XPGEN_REG_no(f,...)		HW_PPERROR( #f "(...) is not applicable." )
#define _HW_XPGEN_REG_ok(f,...)		_HW_XPGEN_REG_2(f,HW_GA1A3(__VA_ARGS__,), __VA_ARGS__)
#define _HW_XPGEN_REG_2(...)		_HW_XPGEN_REG_3(__VA_ARGS__,hw_end)  /* appended */
#define _HW_XPGEN_REG_3(f,t,...)	HW_G2(_HW_XPGEN_REG,HW_A2(hw_typeof_##t))(f,t,__VA_ARGS__)
#define _HW_XPGEN_REG_(f,...)		HW_PPERROR( #f "(...) is not applicable." )
#define _HW_XPGEN_REG_reg(f,t,...)	_HW_XPGEN_reg_##t(f,__VA_ARGS__)

/*	Access one register of the peripheral
 */
#define _HW_XPGEN_reg_reg(f,r,rw,ra,riv,rwm, p,pc,pa,pm,...)	\
  f##_reg1(p,pa,r,rw,ra,riv,rwm,rw,0,__VA_ARGS__)

/*	Access one group of bits of the peripheral
 */
#define _HW_XPGEN_reg_regb(f,t,...)	_HW_XPGEN_regb_##t(f,__VA_ARGS__)
#define _HW_XPGEN_regb_reg(f,r,rw,ra,riv,rwm,rbn,rbp, p,pc,pa,pm,...)	\
  f##_reg1(p,pa,r,rw,ra,riv,rwm,rbn,rbp,__VA_ARGS__)

/*	Access one group of bits of another peripheral
 */
#define _HW_XPGEN_regb_per(f,p,pc,pa, r, ...) _HW_XPGEN_regb_per_2(f,pa,HW_G3(hw,pc,r),__VA_ARGS__)
#define _HW_XPGEN_regb_per_2(...) 	_HW_XPGEN_regb_per_3(__VA_ARGS__)
#define _HW_XPGEN_regb_per_3(f,pa,_reg_,r,rw,ra,riv,rwm,rbn,rbp, p,pc,pa0,pm,...) \
  f##_reg1(p,pa,r,rw,ra,riv,rwm,rbn,rbp,__VA_ARGS__)

/*	Access two groups of bits of the peripheral
 */
#define _HW_XPGEN_reg_regbb(f,_reg1_,r1,rw1,ra1,riv1,rwm1,rbn1,rbp1,vbp1, \
		       _reg2_,r2,rw2,ra2,riv2,rwm2,rbn2,rbp2,vbp2, p,pc,pa,pm,...) \
  f##_reg2(p,pa,							\
	   r1,rw1,ra1,riv1,rwm1,rbn1,rbp1,vbp1,				\
	   r2,rw2,ra2,riv2,rwm2,rbn2,rbp2,vbp2,__VA_ARGS__)
