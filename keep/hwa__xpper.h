
/*	Expand arguments for instructions waiting a controller argument
 */

#error

/*	Specialize according to the type of the first argument
 */
#define HW_X2RPER(...)		HW_G2(HW_X2RPER, HW_IS(ctr,__VA_ARGS__))(__VA_ARGS__)

#define _HW_X2RPER_0(...)	no( "`" HW_QUOTE(HW_A1(__VA_ARGS__)) "` is not a controller." )

#define _HW_X2RPER_reg(...)	HW_PPERROR( "first argument must be a controller or io." )

#define _HW_X2RPER_io(f,...)	HW_G2(_HW_X2RPER_io, HW_IS(,f##_io_isfn))(f,__VA_ARGS__)
#define _HW_X2RPER_io_0(f,...)	HW_PPERROR( "instruction " #f "() is not applicable to io." )
#define _HW_X2RPER_io_1(f,io,...)	f##_io(__VA_ARGS__)


#define _HW_X2RPER_ctr(f,t,cn,cc,...)					\
  HW_G2(_HW_X2RPER_ctr_CCX, HW_ISFN(HW_G3(f,cc,HW_A1(__VA_ARGS__))))(f,cn,cc,__VA_ARGS__)
#define _HW_X2RPER_ctr_CCX_1(f,cn,cc,...)		\
  HW_G3(f,cc,HW_A1(__VA_ARGS__))(cn,cc,__VA_ARGS__)
#define _HW_X2RPER_ctr_CCX_0(f,cn,cc,...)				\
  HW_G2(_HW_X2RPER_ctr_PTX, HW_ISFN(HW_G3(f,ctr,HW_A1(__VA_ARGS__))))(f,cn,cc,__VA_ARGS__)
#define _HW_X2RPER_ctr_PTX_1(f,cn,cc,...)		\
  HW_G3(f,ctr,HW_A1(__VA_ARGS__))(cn,cc,__VA_ARGS__)
#define _HW_X2RPER_ctr_PTX_0(f,cn,cc,...)				\
  HW_G2(_HW_X2RPER_ctr_CC, HW_ISFN(HW_G2(f,cc)))(f,cn,cc,__VA_ARGS__)
#define _HW_X2RPER_ctr_CC_1(f,cn,cc,...)	\
  HW_G2(f,cc)(cn,cc,__VA_ARGS__)
#define _HW_X2RPER_ctr_CC_0(f,...)				\
  HW_G2(_HW_X2RPER_ctr_PT, HW_ISFN(f##_ctr))(f,__VA_ARGS__)
#define _HW_X2RPER_ctr_PT_1(f,...)		\
  f##_ctr(__VA_ARGS__)
#define _HW_X2RPER_ctr_PT_0(f,...)			\
  HW_G2(_HW_X2RPER_REG, HW_ISFN(f##_reg))(f,__VA_ARGS__)


/*	Memory access
 *
 *	Note: 'hw_end' is appended after the arguments.
 */
#define _HW_X2RPER_REG_0(f,...)		HW_PPERROR( #f "(...) is not applicable." )
#define _HW_X2RPER_REG_1(f,...)		_HW_X2RPER_REG_2(f,HW_GA1A3(__VA_ARGS__,), __VA_ARGS__)
#define _HW_X2RPER_REG_2(...)		_HW_X2RPER_REG_3(__VA_ARGS__,hw_end)  /* appended */
#define _HW_X2RPER_REG_3(f,t,...)	HW_G2(_HW_X2RPER_REG,HW_A2(hw_type_##t))(f,t,__VA_ARGS__)
#define _HW_X2RPER_REG_(f,...)		HW_PPERROR( #f "(...) is not applicable." )
#define _HW_X2RPER_REG_reg(f,t,...)	_HW_X2RPER_reg_##t(f,__VA_ARGS__)

/*	Access one register of the controller
 */
#define _HW_X2RPER_reg_reg(f,r,rw,ra,riv,rwm, p,cc,ca,pm,...)	\
  f##_reg1(p,ca,r,rw,ra,riv,rwm,rw,0,__VA_ARGS__)

/*	Access one group of bits of the controller
 */
#define _HW_X2RPER_reg_regb(f,t,...)	_HW_X2RPER_regb_##t(f,__VA_ARGS__)
#define _HW_X2RPER_regb_reg(f,r,rw,ra,riv,rwm,rbn,rbp, p,cc,ca,pm,...)	\
  f##_reg1(p,ca,r,rw,ra,riv,rwm,rbn,rbp,__VA_ARGS__)

/*	Access one group of bits of another controller
 */
#define _HW_X2RPER_regb_ctr(f,p,cc,ca, r, ...) _HW_X2RPER_regb_ctr_2(f,ca,HW_G3(hw,cc,r),__VA_ARGS__)
#define _HW_X2RPER_regb_ctr_2(...) 	_HW_X2RPER_regb_ctr_3(__VA_ARGS__)
#define _HW_X2RPER_regb_ctr_3(f,ca,_reg_,r,rw,ra,riv,rwm,rbn,rbp, p,cc,ca0,pm,...) \
  f##_reg1(p,ca,r,rw,ra,riv,rwm,rbn,rbp,__VA_ARGS__)

/*	Access two groups of bits of the controller
 */
#define _HW_X2RPER_reg_regbb(f,_reg1_,r1,rw1,ra1,riv1,rwm1,rbn1,rbp1,vbp1, \
		       _reg2_,r2,rw2,ra2,riv2,rwm2,rbn2,rbp2,vbp2, p,cc,ca,pm,...) \
  f##_reg2(p,ca,							\
	   r1,rw1,ra1,riv1,rwm1,rbn1,rbp1,vbp1,				\
	   r2,rw2,ra2,riv2,rwm2,rbn2,rbp2,vbp2,__VA_ARGS__)
