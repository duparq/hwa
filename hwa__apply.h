
/*	Expand to the proper function version according to the arguments
 */
#define HW_APPLY(function,...)	HW_G2(_HW_APPLY, hw_type(__VA_ARGS__))(function,__VA_ARGS__)
#define _HW_APPLY_0(...)						\
  HW_PPERROR( "undeclared argument (" HW_QUOTE(HW_A1(__VA_ARGS__)) ")." )
#define _HW_APPLY_1(...)						\
  HW_PPERROR( "argument (" HW_QUOTE(HW_A2(__VA_ARGS__)) ") is of unknown type." )

#define _HW_APPLY_io(f,...)	HW_G2(_HW_APPLY_io, HW_IS(,f##_io_isfn))(f,__VA_ARGS__)
#define _HW_APPLY_io_0(f,...)	HW_PPERROR( "instruction " #f "() is not applicable to io." )
#define _HW_APPLY_io_1(f,io,...)	f##_io(__VA_ARGS__)
#define _HW_APPLY_reg(...)	HW_PPERROR( "first argument must be a controller or io." )


/*	hw_func_aio_cc(...)	used by hw_pin_ocXy to set duty
 */
#define _HW_APPLY_aio(f,_aio_,aion,ion,_ctr_,cn,cc,...)	\
  HW_G2(_HW_APPLY_aio_xcc, HW_ISFN(f##_##aio##_##cc))(f,aion,cn,cc,__VA_ARGS__)
#define _HW_APPLY_aio_xcc_0(f,aion,...)	\
  HW_PPERROR( "can not apply `" #f "`() to aio `hw_" #aion "`." )
#define _HW_APPLY_aio_xcc_1(f,aion,cn,cc,ca,...)	\
  f##_##aio##_##cc(aion,cn,__VA_ARGS__)


/*	FIXME: should keep _ctr_ and do not assume that it is 'ctr' so that
 *	other types can be used?
 */
#define _HW_APPLY_ctr(f,_ctr_,cn,cc,...)					\
  HW_G2(_HW_APPLY_ctr_xcc, HW_ISFN(HW_G3(f,cc,HW_A1(__VA_ARGS__))))(f,cn,cc,__VA_ARGS__)
#define _HW_APPLY_ctr_xcc_1(f,cn,cc,...)		\
  HW_G3(f,cc,HW_A1(__VA_ARGS__))(cn,cc,__VA_ARGS__)
#define _HW_APPLY_ctr_xcc_0(f,cn,cc,...)				\
  HW_G2(_HW_APPLY_ctr_xct, HW_ISFN(HW_G3(f,ctr,HW_A1(__VA_ARGS__))))(f,cn,cc,__VA_ARGS__)
#define _HW_APPLY_ctr_xct_1(f,cn,cc,...)		\
  HW_G3(f,ctr,HW_A1(__VA_ARGS__))(cn,cc,__VA_ARGS__)
#define _HW_APPLY_ctr_xct_0(f,cn,cc,...)				\
  HW_G2(_HW_APPLY_ctr_cc, HW_ISFN(HW_G2(f,cc)))(f,cn,cc,__VA_ARGS__)
#define _HW_APPLY_ctr_cc_1(f,cn,cc,...)	\
  HW_G2(f,cc)(cn,cc,__VA_ARGS__)
#define _HW_APPLY_ctr_cc_0(f,...)				\
  HW_G2(_HW_APPLY_ctr_ct, HW_ISFN(f##_ctr))(f,__VA_ARGS__)
#define _HW_APPLY_ctr_ct_1(f,...)		\
  f##_ctr(__VA_ARGS__)
#define _HW_APPLY_ctr_ct_0(f,...)			\
  HW_G2(_HW_APPLY_REG, HW_ISFN(f##_reg))(f,__VA_ARGS__)


/*	Memory access
 *
 *	Note: a void argument is appended after the arguments.
 */
#define _HW_APPLY_REG_0(f,...)		HW_PPERROR( #f "(...) is not applicable." )
#define _HW_APPLY_REG_1(f,...)		_HW_APPLY_REG_2(f,HW_GA1A3(__VA_ARGS__,), __VA_ARGS__)
#define _HW_APPLY_REG_2(...)		_HW_APPLY_REG_3(__VA_ARGS__,)  /* void arg appended */
#define _HW_APPLY_REG_3(f,t,...)	HW_G2(_HW_APPLY_REG,HW_A2(hw_type_##t))(f,t,__VA_ARGS__)
#define _HW_APPLY_REG_(f,...)		HW_PPERROR( #f "(...) is not applicable." )
#define _HW_APPLY_REG_reg(f,t,...)	_HW_APPLY_reg_##t(f,__VA_ARGS__)


/*	Access one register of one controller
 */
#define _HW_APPLY_reg_reg(f,r,rw,ra,riv,rwm, cn,cc,ca,pm,...)	\
  f##_reg1(cn,ca,r,rw,ra,riv,rwm,rw,0,__VA_ARGS__)

/*	Access one group of bits of one controller
 */
#define _HW_APPLY_reg_regb(f,t,...)	_HW_APPLY_regb_##t(f,__VA_ARGS__)
#define _HW_APPLY_regb_reg(f,r,rw,ra,riv,rwm,rbn,rbp, cn,cc,ca,pm,...)	\
  f##_reg1(cn,ca,r,rw,ra,riv,rwm,rbn,rbp,__VA_ARGS__)

/*	Access one group of bits of another controller
 */
#define _HW_APPLY_regb_ctr(f,cn,cc,ca, r, ...) _HW_APPLY_regb_ctr_2(f,ca,HW_G3(hw,cc,r),__VA_ARGS__)
#define _HW_APPLY_regb_ctr_2(...) 	_HW_APPLY_regb_ctr_3(__VA_ARGS__)
#define _HW_APPLY_regb_ctr_3(f,ca,_regb_,_reg_,r,rw,ra,riv,rwm,rbn,rbp, cn,cc,ca0,pm,...) \
  f##_reg1(cn,ca,r,rw,ra,riv,rwm,rbn,rbp,__VA_ARGS__)

/*	Access two groups of bits of one ctripheral
 */
#define _HW_APPLY_reg_regbb(f,_reg1_,r1,rw1,ra1,riv1,rwm1,rbn1,rbp1,vbp1, \
			    _reg2_,r2,rw2,ra2,riv2,rwm2,rbn2,rbp2,vbp2, cn,cc,ca,pm,...) \
  f##_reg2(cn,ca,							\
	   r1,rw1,ra1,riv1,rwm1,rbn1,rbp1,vbp1,				\
	   r2,rw2,ra2,riv2,rwm2,rbn2,rbp2,vbp2,__VA_ARGS__)
