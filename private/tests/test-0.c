
#include BOARD_H

#define E	_Pragma("GCC error \"Error\"")

#define ISE(x)		_ISE2(x)
#define _ISE2(x)	HW_X(_ISE,_hw_is_##x)(x)
#define _ISE_0(x)	0
#define _ISE_1(x)	1

#define F(x)		_F(x)
#define _F(x)		HW_X(_F,x)(x)

H1: E;
H2: HW_IS(e,E);
H3: HW_IS(,E);
H4: HW_G2(E,x);

H5: ISE(E);

#if 1 == 1
H6: Yes
#else
H6: No
#endif

#if ISE(E) == 1
H7: Yes
#else
H7: No
#endif

#if ISE(F) == 1
H8: Yes
#else
H8: No
#endif

F(x)
F(E)
