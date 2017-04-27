#ifndef HWA_H
#define HWA_H

#include "types.h"


/*	Begin a HWA session.
 *	Structure hwa_t is defined in device-specific header.
 */
#define hwa_begin(reset)						\
  u8	hwa_nocommit = 0 ; /* Will warn if hwa_commit() is not called */ \
  hwa_begin_device(HWA_BEGIN_##reset)

#define HWA_BEGIN_			0
#define HWA_BEGIN_RESET			1


/*	Commit configuration to hardware.
 */
#define hwa_commit()							\
  do {									\
    if (0) { HWA_WARN("Did you forget to turn compiler optimization on?"); } \
    hwa_nocommit = 0 ;							\
    hwa_commit_device();						\
  } while(0)

#define hwa_nocommit()							\
  do {									\
    if (0) { HWA_WARN("Did you forget to turn compiler optimization on?"); } \
    hwa_nocommit = 1 ;							\
    hwa_commit_device();						\
  } while(0)


#define HWA_STATE_OFF			0
#define HWA_STATE_ON			1

#define HWA_NONE			0xFFFFFFFF

extern void hwa_warn();

#define HWA_WARN(msg)			HWA_WARN_(msg, __LINE__)
#if defined HWA_DEBUG
#  define HWA_WARN_(msg, num)		hwa_warn()
#else
#  define HWA_WARN_(msg, num)			\
  do {						\
    void __attribute__((noinline, warning(msg)))	\
      HWA_G2(hwa_warn, num)(void){hwa_warn();}	\
    HWA_G2(hwa_warn, num)();			\
  } while(0)
#endif

#define HWA_ERROR(msg)			HWA_ERROR_(msg, __LINE__)
#if defined HWA_DEBUG
#  define HWA_ERROR_(msg, num)		hwa_warn()
#else
#define HWA_ERROR_(msg, num)			\
  do {						\
    extern void __attribute__((error(msg)))	\
      HWA_G2(hwa_error, num)(void);		\
    HWA_G2(hwa_error, num)();			\
  } while(0)
#endif

#define HWA_(x, va...)			va##x

#define HWA_G2(a,b)			HWA_G2_(a,b)
#define HWA_G2_(a,b)			a##_##b

#define HWA_G3(a,b,c)			HWA_G3_(a,b,c)
#define HWA_G3_(a,b,c)			a##_##b##_##c

#define HWA_STR(x)			HWA_STR_(x)
#define HWA_STR_(x)			#x

#define HWA_1ST(va...)			HWA_1ST_(va)
#define HWA_1ST_(a, ...)		a

#define HWA_2ND(va...)			HWA_2ND_(va, 0)
#define HWA_2ND_(a, b, ...)		b

#define HWA_3RD(va...)			HWA_3RD_(va, 0)
#define HWA_3RD_(a, b, c, ...)		c

#define HWA_4TH(va...)			HWA_4TH_(va, 0)
#define HWA_4TH_(a, b, c, d, ...)	d

#define HWA_5TH(va...)			HWA_5TH_(va, 0)
#define HWA_5TH_(a, b, c, d, e, ...)	e

#define HWA_P(pname)			HWA_P_(pname)
#define HWA_P_(pname)			pname##_P
/* #define HWA_VPTR(pname)			hwa_##pname */

/*	Mask corresponding to bits definition.
 *
 *	'bdef' must expand to 'mname, rname, bits, shift'
 */
/* #define HWA_MASK(bdef...)			HWA_MASK_(bdef) */
/* #define HWA_MASK_(mname, rname, bits, shift)	((bits)<<(shift)) */

/*	Integer type of hardware register.
 */
#define HWA_VTYPE(mname, rname)		HWA_2ND(mname##_##rname)

/*	Address of hardware register.
 */
#define HWA_VADDR(mname, rname)		HWA_3RD(mname##_##rname)

/*	Reset value of hardware register.
 */
#define HWA_HINIT(mname, rname)		HWA_4TH(mname##_##rname)

/*	Writeable bits mask in hardware register.
 */
#define HWA_HWMASK(mname, rname)	HWA_5TH(mname##_##rname)


/*	Mandatory declarations for virtual peripheral structure
 */
#define HWA_PDCL(pname)				\
  u32	hwaddr ;\
  u8	used


/*	Initialise virtual peripheral structure
 */
#define HWA_PINIT(mname, pname)			\
  mname pname##_ST ;				\
  mname *pname##_P = &pname##_ST ;		\
  pname##_P->hwaddr = pname##_BASE ;		\
  pname##_P->used = 0

/*	Hardware register (lvalue).
 *
 *	'HWA_##mname##_##rname' must expand to 'volatile, type, address, ...'
 */
#define HWA_HREG(mname, pname, rname)		HWA_HREG_(pname, mname##_##rname)
#define HWA_HREG_(va...)			HWA_HREG__(va...)
#define HWA_HREG__(pname, volatile, type, addr, ...)	(*((volatile type *)(pname##_BASE+addr)))

#define HWA_HREGP(mname, p, rname)		HWA_HREGP_(p, mname##_##rname)
#define HWA_HREGP_(va...)			HWA_HREGP__(va...)
#define HWA_HREGP__(p, volatile, type, addr, ...)	\
  (*((volatile type *)(p->hwaddr+(intptr_t)addr)))

/*	Write hardware register bits
 */
#define HWA_HSET(va...)			HWA_HSET_(va)
#define HWA_HSET_(mname, pname, rname, mask, shift, value)		\
  HWA_HREG(mname, pname, rname) =					\
    (HWA_HREG(mname, pname, rname) & ~((mask) << (shift))) | ((value) << (shift)) ;

#define HWA_HGET(va...)			HWA_HGET_(va)
#define HWA_HGET_(mname, pname, rname, mask, shift)			\
  (HWA_HREG(mname, pname, rname) & ((bits)<<(shift)) >> (shift))


/*	Virtual register (lvalue).
 */
/* #define HWA_VREG(pname,rname,vname)	hwa_##pname->rname##_##vname */
#define HWA_VREGP(p,rname,vname)	p->rname##_##vname

/*	Future value of hardware register bits or -1 if unknown (rvalue).
 *
 *	'bdef' must expand to 'mname, rname, bits, shift'
 */
#define HWA_NVALP(p, rname)						\
  (HWA_VREGP(p, rname, mvmask) ? HWA_VREGP(p, rname, mvalue) :		\
   HWA_VREGP(p, rname, ovmask) ? HWA_VREGP(p, rname, ovalue) : HWA_NONE)

/*	Virtual register declaration
 */
#define HWA_VDCL(mname, rname)			\
  HWA_VTYPE(mname, rname) rname##_mvmask, rname##_mvalue, rname##_ovmask, rname##_ovalue


/*	Virtual register initialisation
 */
#define HWA_VINIT(mname, pname, rname, reset)				\
  do {									\
    HWA_P(pname)->rname##_mvmask	= 0 ;				\
    HWA_P(pname)->rname##_mvalue	= 0 ;				\
    HWA_P(pname)->rname##_ovmask = reset ? HWA_HWMASK(mname, rname) : 0 ; \
    HWA_P(pname)->rname##_ovalue = reset ? HWA_HINIT(mname, rname) : 0 ; \
  } while(0)


/*	Virtual 'sub-register' bits value (rvalue).
 *	mname is not used but kept for consistancy with VSETP, VCOMMITP
 */
#define HWA_VBITSP(va...)		HWA_VBITSP_(va)
#define HWA_VBITSP_(mname, ptr, rname, bits, shift, vname)		\
  (((HWA_VREGP(ptr, rname, vname)) & ((bits)<<(shift))) >> (shift))


#define HWA_VSETP(va...)			HWA_VSETP_(va)
#define HWA_VSETP_(mname, ptr, rname, bits, shift, val)			\
  do {									\
    HWA_VTYPE(mname, rname) mmask = (bits) << (shift) ;			\
    HWA_VTYPE(mname, rname) vmask = (val) << (shift) ;			\
    if ( (HWA_HWMASK(mname, rname) & mmask) != mmask )			\
      HWA_ERROR("Try to modify not writeable bits.");			\
    if ( (HWA_VREGP(ptr, rname, mvmask) & mmask) != 0			\
	 && (HWA_VREGP(ptr, rname, mvalue) & mmask) != vmask )		\
      HWA_ERROR("Previous affectation with different value not committed."); \
    if ( ((HWA_VREGP(ptr, rname, ovmask) & mmask) == mmask		\
	  && (HWA_VREGP(ptr, rname, ovalue) & mmask) != vmask)		\
	 || (HWA_VREGP(ptr, rname, ovmask) & mmask) != mmask) {		\
      ptr->used = 1 ;							\
      HWA_VREGP(ptr, rname, mvmask) |= mmask ;				\
      HWA_VREGP(ptr, rname, mvalue) =					\
	(HWA_VREGP(ptr, rname, mvalue) & ~mmask)			\
	| (mmask & vmask) ;						\
    }									\
  } while(0)


/*	Write bits designed by mask from virtual to hardware register.
 *
 *	va must expand to 'mname, rname [, mask]'
 *	-1 is appended so that will be used as 'mask' if none given
 */
#define HWA_COMMITP(va...)		HWA_COMMITP_(va, -1)
#define HWA_COMMITP_(dry, mname, ptr, rname, mask, ...)			\
  do {									\
    HWA_VTYPE(mname, rname) m = HWA_VREGP(ptr, rname, mvmask) & (mask) ; \
    if ( m != 0 ) {							\
      if ( m != HWA_HWMASK(mname, rname)				\
	   && HWA_VREGP(ptr, rname, ovmask) != HWA_HWMASK(mname, rname) ) { \
	if ( dry == 0 && HWA_VADDR(mname, rname) != -1 )		\
	  HWA_VREGP(ptr, rname, ovalue) = HWA_HREGP(mname, ptr, rname) ; \
	HWA_VREGP(ptr, rname, ovmask) = HWA_HWMASK(mname, rname) ;	\
	HWA_VREGP(ptr, rname, mvalue) =					\
	  (HWA_VREGP(ptr, rname, ovalue) & ~HWA_VREGP(ptr, rname, mvmask)) \
	  | (HWA_VREGP(ptr, rname, mvalue) & HWA_VREGP(ptr, rname, mvmask)) ; \
      }									\
      HWA_VREGP(ptr, rname, ovalue) =					\
	(HWA_VREGP(ptr, rname, ovalue) & ~m)				\
	| (HWA_VREGP(ptr, rname, mvalue) & m) ;				\
      if ( dry == 0 && HWA_VADDR(mname, rname) != -1 )			\
	HWA_HREGP(mname, ptr, rname) = HWA_VREGP(ptr, rname, ovalue) ;	\
      HWA_VREGP(ptr, rname, mvmask) &= ~m ;				\
      HWA_VREGP(ptr, rname, ovmask) |= m ;				\
    }									\
  } while(0)


/*	Include device-specific definitions from "hwa_device.h"
 */
#ifndef HWA_DEVICE
#  error "HWA_DEVICE not defined."
#endif

#include HWA_STR(HWA_G2(hwa, HWA_DEVICE).h)


#endif
