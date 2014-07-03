
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


/*
 *	Definition of a memory location
 */

#define hw_hasmem_reg
#define hw_hasmem_regb
#define hw_hasmem_regbb
#define hw_hasmem_xreg

#define _hw_mem_ccrn(cc,rn)		_hw_mem_cm_3(cc,,,rn,hw_##cc##_##rn)

#define _hw_mem_cm(...)			_hw_mem_cm_2(__VA_ARGS__)
#define _hw_mem_cm_2(c,n,i,a,rn)	_hw_mem_cm_3(c,n,a,rn,hw_##c##_##rn)
#define _hw_mem_cm_3(...)		_hw_mem_cm_4(__VA_ARGS__)
#define _hw_mem_cm_4(c,n,a,rn,...)	HW_G2(_hw_mem_cm, \
					      HW_IS(,hw_hasmem_##__VA_ARGS__))(c,n,a,rn,__VA_ARGS__)
#define _hw_mem_cm_0(c,n,a,rn,...)	HW_G2(_hw_mem_0, HW_IS(,rn))(c,n,a,rn)
#define _hw_mem_0_1(c,n,a,rn)		HW_ERR("member of hw_" #c "is required.")
#define _hw_mem_0_0(c,n,a,rn)		HW_ERR("`" #rn "` is not a member of hw_" #c)
#define _hw_mem_cm_1(c,n,a,rn, x,...)	_hw_mem_##x(c,n,a,rn,__VA_ARGS__)

#define _hw_mem_reg(c,n,a, rn,rw,ra,rrv,rwm)	\
  mem1, n,a, rn,rw,ra,rrv,rwm, rw,0

#define _hw_mem_regb(c,n,a,xn,rn,bn,bp)	_hw_mem_regb_2(n,a,rn,hw_##c##_##rn,bn,bp)
#define _hw_mem_regb_2(...)		_hw_mem_regb_3(__VA_ARGS__)
#define _hw_mem_regb_3(n,a,rn, t, ...)		\
  mem1, n,a, rn,__VA_ARGS__

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
