
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

/*	Expand arguments to a flat register or bit definition
 */
#define HW_X2R(...)		HW_G2(_HW_X2R, hw_loosetype(__VA_ARGS__))(__VA_ARGS__)
#define _HW_X2R_(x,...)				\
  0, "`" #x "` is not declared."
#define _HW_X2R_io(...)			io, __VA_ARGS__
#define _HW_X2R_irqe(_irqe_,...)	_HW_X2R_ctr(__VA_ARGS__)
#define _HW_X2R_irqf(_irqf_,...)	_HW_X2R_ctr(__VA_ARGS__)
#define _HW_X2R_ctr(_ctr_,cn,cc,ca, n)	_HW_X2R_2(cn,cc,ca,n,hw_##cc##_##n)
#define _HW_X2R_regb(...)		__VA_ARGS__

#define _HW_X2R_2(...)			_HW_X2R_3(__VA_ARGS__)
#define _HW_X2R_3(cn,cc,ca,n,...)					\
  HW_G2(_HW_X2R_3, hw_loosetype(__VA_ARGS__))(cn,cc,ca,n,__VA_ARGS__)
#define _HW_X2R_3_0(cn,cc,ca,n,...)			\
  0, "`hw_" #cn "` has no member named `" #n "`."
#define _HW_X2R_3_reg(cn,cc,ca,n,_reg_,rn,rw,ra,riv,rwm)	\
  reg, cn,cc,ca,rn,rw,ra,riv,rwm
/* #define _HW_X2R_3_regb(cn,cc,ca,n,_regb_,_reg_,rn,rw,ra,riv,rwm,bn,bp)	\ */
/*   regb, cn,cc,ca,rn,rw,ra,riv,rwm,bn,bp */
#define _HW_X2R_3_regb(cn,cc,ca,n,_regb_, x, ...)	\
  _HW_X2R_3_regb_##x(cn,cc,ca,n,_regb_,x,__VA_ARGS__)
#define _HW_X2R_3_regb_reg(cn,cc,ca,n,_regb_,_reg_,rn,rw,ra,riv,rwm,bn,bp) \
  regb, cn,cc,ca,rn,rw,ra,riv,rwm,bn,bp
#define _HW_X2R_3_regb_ctr(cn0,cc0,ca0,n0,_regb_,_ctr_,cn,cc,ca, b)	\
  _HW_X2R_3_regb_ctr_2(cn,cc,ca,hw_##cc##_##b)
#define _HW_X2R_3_regb_ctr_2(...)		_HW_X2R_3_regb_ctr_3(__VA_ARGS__)
#define _HW_X2R_3_regb_ctr_3(cn,cc,ca,_regb_,_reg_,rn,rw,ra,rrv,rwm,bn,bp) \
  regb, cn,cc,ca,rn,rw,ra,riv,rwm,bn,bp
