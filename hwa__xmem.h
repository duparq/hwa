
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


/*	Check and expand arguments for register access
 *
 *	Returns:  0, msg: error explained in msg
 *	          1, ...: access to 1 register
 *	          2, ...: access to 2 registers
 *
 *	Note: one void argument is appended to arguments list (simplifies the
 *	process).
 */
/* #define HW_XMEM(...)			HW_G2(_HW_XMEM_XCTR, HW_IS(ctr,__VA_ARGS__))(__VA_ARGS__,) */

/* #define _HW_XMEM_XCTR_0(...)			\ */
/*   0, "first argument is not a controller." */

/* #define _HW_XMEM_XCTR_1(ctr, cc,cn,ca,rn,...)				\ */
/*   HW_G2(_HW_XMEM, HW_IS(mem,hw_##cc##_##rn))(cc,cn,ca,rn,__VA_ARGS__) */

/* #define _HW_XMEM_0(cc,cn,ca,rn,...)			\ */
/*   0, "controller `" #cn "` of class `" #cc "`has no register `" #rn "`." */

#define HW_XMEM(cc,cn,ci,ca,rn,...)	_HW_XMEM_2(cc,cn,ca,rn,hw_##cc##_##rn,__VA_ARGS__)
#define _HW_XMEM_2(...)			_HW_XMEM_3(__VA_ARGS__)
#define _HW_XMEM_3(cc,cn,ca,rn, mem,x,...)	_HW_XMEM_##x(cc,cn,ca,rn,__VA_ARGS__)

#define _HW_XMEM_reg(cc,cn,ca, rn,rw,ra,rrv,rwm,...)	\
  1, cn,ca, rn,rw,ra,rrv,rwm, rw,0, __VA_ARGS__

#define _HW_XMEM_regb(cc,cn,ca,xn,rn,bn,bp,...)			\
  _HW_XMEM_regb_2(cn,ca,rn,hw_##cc##_##rn,bn,bp,__VA_ARGS__)
#define _HW_XMEM_regb_2(...)		_HW_XMEM_regb_3(__VA_ARGS__)
#define _HW_XMEM_regb_3(cn,ca,rn, mem,reg, ...)	\
  1, cn,ca,rn,__VA_ARGS__

#define _HW_XMEM_regbb(cc,cn,ca,xn, rn1,rbn1,rbp1,vbp1, rn2,rbn2,rbp2,vbp2, ...) \
  _HW_XMEM_regbb_2(cn,ca,						\
		   rn1,hw_##cc##_##rn1,rbn1,rbp1,vbp1,			\
		   rn2,hw_##cc##_##rn2,rbn2,rbp2,vbp2, __VA_ARGS__)
#define _HW_XMEM_regbb_2(...)		_HW_XMEM_regbb_3(__VA_ARGS__)
#define _HW_XMEM_regbb_3(cn,ca,						\
			 rn1,mem1,reg1,rw1,ra1,rrv1,rwm1,rbn1,rbp1,vbp1, \
			 rn2,mem2,reg2,rw2,ra2,rrv2,rwm2,rbn2,rbp2,vbp2, ...) \
  2, cn,ca,								\
    rn1,rw1,ra1,rrv1,rwm1,rbn1,rbp1,vbp1,				\
    rn2,rw2,ra2,rrv2,rwm2,rbn2,rbp2,vbp2, __VA_ARGS__

#define _HW_XMEM_xreg(cc,cn,ca,xn, sctr,scc,scn,sca, srn,...)	\
  _HW_XMEM_xreg_2(scc,scn,sca,srn,hw_##scc##_##srn, __VA_ARGS__)
#define _HW_XMEM_xreg_2(...)		_HW_XMEM_xreg_3(__VA_ARGS__)
#define _HW_XMEM_xreg_3(cc,cn,ca,rn, mem, x,...)	_HW_XMEM_##x(cc,cn,ca,rn,__VA_ARGS__)



/*	Register
 */
#if 0
#define hw_reg(c,rn)		HW_G2(_hw_reg_xctr, HW_IS(ctr,c))(rn,c)
#define _hw_reg_xctr_0(...)	HW_ERR(first argument is not a controller.)
#define _hw_reg_xctr_1(rn,ctr,cc,cn,ca,...)	\
  HW_G2(_hw_reg_xmem,HW_IS(mem, hw_##cc##_##rn))(rn,cc,cn,ca,__VA_ARGS__)
#define _hw_reg_xmem_0(rn,cc,cn,ca,...)	\
  HW_ERR("`" #rn "` is not a register of class `"#cc"` controller `hw_"#cn"`.")
#define _hw_reg_xmem_1(rn,cc,cn,ca,...)	_hw_reg_2(rn,cc,cn,ca,hw_##cc##_##rn,__VA_ARGS__)
#define _hw_reg_2(...)		_hw_reg_3(__VA_ARGS__)
#define _hw_reg_3(rn,cc,cn,ca, mem,x,...)	_hw_reg_##x(rn,cc,cn,ca,__VA_ARGS__)

#define _hw_reg_reg(rn,cc,cn,ca,rw,ra,rrv,rwm,...)	\
  mem,bit,cn,rn,ca+ra,rw,0
#define _hw_reg_regb(rn0,cc,cn,ca,rn,bn,bp,...)		\
  _hw_reg_regb_2(rn,cn,ca,hw_##cc##_##rn,bn,bp,__VA_ARGS__)
#define _hw_reg_regb_2(...)		_hw_reg_regb_3(__VA_ARGS__)
#define _hw_reg_regb_3(rn,cn,ca,mem,reg,rw,ra,rrw,rwm,bn,bp,...)	\
  mem,bit,cn,rn,ca+ra,bn,bp
#define _hw_reg_regbb(rn,cn,...)	HW_ERR(register `rn` is spread over two registers)
#endif




#define hw_hasmem_reg
#define hw_hasmem_regb
#define hw_hasmem_regbb
#define hw_hasmem_xreg

#define _hw_mem_ccrn(cc,rn)			_hw_mem_cm_3(cc,,,rn,hw_##cc##_##rn)

#define _hw_mem_cm(...)				_hw_mem_cm_2(__VA_ARGS__,)
#define _hw_mem_cm_2(cc,cn,ci,ca,rn,...)	_hw_mem_cm_3(cc,cn,ca,rn,hw_##cc##_##rn)
#define _hw_mem_cm_3(...)			_hw_mem_cm_4(__VA_ARGS__)
#define _hw_mem_cm_4(cc,cn,ca,rn,x,...)	HW_G2(_hw_mem_cm, HW_IS(,hw_hasmem_##x))(cc,cn,ca,rn,x,__VA_ARGS__)
#define _hw_mem_cm_0(cc,cn,ca,rn,...)	HW_G2(_hw_mem_0, HW_IS(,rn))(cc,cn,ca,rn)
#define _hw_mem_0_1(cc,cn,ca,rn)	HW_ERR("member of hw_" #cc "is required.")
#define _hw_mem_0_0(cc,cn,ca,rn)	HW_ERR("`" #rn "` is not a member of hw_" #cc)
#define _hw_mem_cm_1(cc,cn,ca,rn, x,...)	_hw_mem_##x(cc,cn,ca,rn,__VA_ARGS__)

#define _hw_mem_reg(cc,cn,ca, rn,rw,ra,rrv,rwm,...)	\
  mem1, cn,ca, rn,rw,ra,rrv,rwm, rw,0

#define _hw_mem_regb(cc,cn,ca,xn,rn,bn,bp)	_hw_mem_regb_2(cn,ca,rn,hw_##cc##_##rn,bn,bp)
#define _hw_mem_regb_2(...)			_hw_mem_regb_3(__VA_ARGS__)
#define _hw_mem_regb_3(cn,ca,rn, reg, ...)	\
  mem1, cn,ca, rn,__VA_ARGS__

#define _hw_mem_regbb(cc,cn,ca,crn, rn1,rbn1,rbp1,vbp1, rn2,rbn2,rbp2,vbp2) \
  _hw_mem_regbb_2(cn,ca,						\
		  rn1,hw_##cc##_##rn1,rbn1,rbp1,vbp1,			\
		  rn2,hw_##cc##_##rn2,rbn2,rbp2,vbp2)
#define _hw_mem_regbb_2(...)		_hw_mem_regbb_3(__VA_ARGS__)
#define _hw_mem_regbb_3(cn,ca,						\
			rn1,reg1,rw1,ra1,rrv1,rwm1,rbn1,rbp1,vbp1,	\
			rn2,reg2,rw2,ra2,rrv2,rwm2,rbn2,rbp2,vbp2)	\
  mem2, cn,ca,								\
    rn1,rw1,ra1,rrv1,rwm1,rbn1,rbp1,vbp1,				\
    rn2,rw2,ra2,rrv2,rwm2,rbn2,rbp2,vbp2


#define _hw_mem_xreg(cc,cn,ca,xn, scc,scn,sci,sca, srn)	\
  _hw_mem_xreg_2(scc,scn,sca,srn,hw_##scc##_##srn)
#define _hw_mem_xreg_2(...)			_hw_mem_xreg_3(__VA_ARGS__)
#define _hw_mem_xreg_3(cc,cn,ca,rn, x,...)	_hw_mem_##x(cc,cn,ca,rn,__VA_ARGS__)
