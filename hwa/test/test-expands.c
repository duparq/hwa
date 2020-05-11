
//#include <hwa/stm32f103rbt6.h>


#define HW_E_KW(x)			HW_E(expected a keyword instead of HW_Q(x))

  
/*  Branch depending on a key
 *
 *    HW_K(f,k,x) expands to:
 *      f0 if k is not v.
 *      f1 if k is v	(there must a: #define _hw_is_k_k , 1)
 *      f2 if x is not a word (void or bracket)
 */
#define HW_K(...)			_HW_K01(__VA_ARGS__,,,)
#define _HW_K01(f,k,v,...)		_HW_K02(f,k,v,_hw_isa_leftbkt v, 0,)
#define _HW_K02(...)			_HW_K03(__VA_ARGS__)
#define _HW_K03(f,k,v,z,x,...)		_HW_K03##x(f,k,v)
#define _HW_K031(f,k,v)			HW_E_KW(v) f##2
#define _HW_K030(f,k,v)			_HW_K04(f,k,v,_hw_is__##v, 0,)
#define _HW_K04(...)			_HW_K05(__VA_ARGS__)
#define _HW_K05(f,k,v,z,x,...)		_HW_K05##x(f,k,v)
#define _HW_K051(f,k,v)			HW_E_KW(v) f##2
#define _HW_K050(f,k,v)			_HW_K06(f,k,v,_hw_is_##k##_##v, 0,)
#define _HW_K06(...)			_HW_K07(__VA_ARGS__)
#define _HW_K07(f,k,v,z,x,...)		f##x


#define hw_config__io1a			, _hw_cfgio1a

#define _hw_cfgio1a(o,p,bn,bp,k,...)	HW_K(_hw_cfgio1a_kf,function,k)(o,(p,bn,bp),k,__VA_ARGS__)
#define _hw_cfgio1a_kf2(...)
#define _hw_cfgio1a_kf0(o,d,k,...)	HW_E_NIL(k,(function))
#define _hw_cfgio1a_kf1(o,d,k,...)	

//#define _hw_cfgio1a_kf1(o,d,k,v,...)	v

/* hw( config, pa2, (c) ); */
/* hw( config, pa2, ); */
/* hw( config, pa2, key ); */
/* hw( config, pa2, function ); */
/* hw( config, pa2, function, gpio ); */
/* hw( config, pa2, function, (counter2,channel3) ); */


#define HW_V(...)			_HW_V01(__VA_ARGS__,,,)
#define _HW_V01(v,...)			_HW_V02(v,_hw_isa_leftbkt v, 0,)
#define _HW_V02(...)			_HW_V03(__VA_ARGS__)
#define _HW_V03(v,z,x,...)		_HW_V03##x(v)
#define _HW_V031(v)			Expand v /**/
#define _HW_V030(v)			_HW_V04(v,_hw_is__##v, 0,)
#define _HW_V04(...)			_HW_V05(__VA_ARGS__)
#define _HW_V05(v,z,x,...)		_HW_V05##x(v)
#define _HW_V051(v)			HW_E_KW(v) f##2
#define _HW_V050(v)			_HW_V06(v,_hw_is_##k##_##v, 0,)
#define _HW_V06(...)			_HW_V07(__VA_ARGS__)
#define _HW_V07(v,z,x,...)		f##x


/* HW_V(f,); */
/* HW_V(val); */
/* HW_V((v1,v2)); */

/* HW_X(counter3); //_c16a,counter3,0x40000400; */
/* HW_X((counter3,channel1)) */
/* HW_X((counter2,channel3)) */


#define hw_class__p16a

#define hw_port0			_p16a, 0x40010800

#define hw_class__io1a

#define hw_pa2				_io1a, port0,  1,  2

#define hw__io1a_port			, _hw_io1a_port

#define _hw_io1a_port(o,p,...)		_io1a,o,(p,__VA_ARGS__),port, HW_XO(p)


#define hw_class__c16a

#define hw__c16a_creg			_r16, 0x00, 0x03FF, 0

#define hw__c16a_oc2m			_cb1, creg, 3, 12

#define hw_counter2			_c16a, 0x40000000

#define hw_counter2_oreg		_r16, 0x7F, 0x03, 0x00


#define hw_class__cca

//#define hw_counter2_channel1		counter2channel1
//#define hw_counter2channel1		_cca, counter2, 1, 1, 0

#define hw_counter2_channel1		_cca, counter2, 1
#define hw_counter2_channel2		_cca, counter2, 2
#define hw_counter2_channel3		_cca, counter2, 3
#define hw_counter2_channel4		_cca, counter2, 4


#define hw__cca_ocm			, _hw_cca_ocm

#define _hw_cca_ocm(o,c,n)		_c16a,c,(HW_A1(hw_##c)),ocm, hw__c16a_oc##n##m


#include "../../hwa/hwa_1.h"


HW_OX(pa2,port); // _p16a,port0,(0x40010800);

HW_OX(counter2,oreg); // _m111,(counter2,oreg),(counter2,oreg,_r16,0x40000000 +0x7F,0x03,0x00,16,0);

HW_OX(counter2,creg); // _m111,(counter2,creg),(counter2,creg,_r16,0x40000000 +0x00,0x03FF,0,16,0);

HW_OX(counter2,channel1); // _cca,counter2channel1,(counter2, 1);

HW_OX(counter2,channel2); // _cca,counter2,(counter2, 2);

HW_OX(counter2_channel2,ocm);


HW_X((pa2,port)); // _p16a,port0,(0x40010800);

HW_X((counter2,oreg)); // _m111,(counter2,oreg),(counter2,oreg,_r16,0x40000000 +0x7F,0x03,0x00,16,0);

HW_X((counter2,creg)); // _m111,(counter2,creg),(counter2,creg,_r16,0x40000000 +0x00,0x03FF,0,16,0);

HW_X((counter2,channel1)); // _cca,counter2channel1,(counter2, 1);

HW_X((counter2,channel2)); // _cca,counter2,(counter2, 2);

HW_X((counter2,channel2,ocm)); // _m111,(counter2,creg),counter2,creg,_r16,0x40000000 +0x00,0x03FF, 0,7,13;

HW_X(counter2,channel2,ocm); // _m111,(counter2,creg),counter2,creg,_r16,0x40000000 +0x00,0x03FF, 0,7,13;

#define hw_write__m111			, _hw_wrm111

hw( write, (counter2,channel2,ocm), 1); // _m111,(counter2,creg),counter2,creg,_r16,0x40000000 +0x00,0x03FF, 0,7,13;
