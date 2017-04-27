#ifndef HWA_H
#define HWA_H

#include "types.h"

#if defined HWA_DEBUG || defined DEBUG
#  define hwa_debug	1
#else
#  define hwa_debug	0
#endif


/*	Access hardware registers from peripheral name
 *
 *	'mname##_##rname' must expand to 'volatile, type, address, ...'
 */
#define HW_HR(mname, pname, rname)		HW_HR_(pname, HWA_G2(mname,rname))
#define HW_HR_(...)				HW_HR__(__VA_ARGS__)
#define HW_HR__(pname, volatile, type, addr, ...)	\
  (*((volatile type *)(pname##_BASE+addr)))

#define HWA_HA(mname, pname, rname)		HWA_HA_(pname, HWA_G2(mname,rname))
#define HWA_HA_(...)			HWA_HA__(__VA_ARGS__)
#define HWA_HA__(pname, volatile, type, addr, ...)	\
  (pname##_BASE+addr)

#define HW_HTST(...)				HW_HTST_(__VA_ARGS__)
#define HW_HTST_(mname, pname, rname, mask, shift)			\
  (HW_HR(mname, pname, rname) & ((mask) << (shift)))

#define HW_HBGET(...)				HW_HBGET_(__VA_ARGS__)
#define HW_HBGET_(mname, pname, rname, mask, shift)			\
  ((HW_HR(mname, pname, rname) & ((mask) << (shift))) >> (shift))

#define HW_HBSET(...)			HW_HBSET_(__VA_ARGS__)
#define HW_HBSET_(mname, pname, rname, mask, shift, value)		\
  HW_HR(mname, pname, rname) =					\
    (HW_HR(mname, pname, rname) & ~((mask) << (shift))) | ((value) << (shift))



/*	Begin a HWA session.
 */
#define hwa_begin(reset)						\
  u8	hwa_commit = 0 ; /* Will warn if hwa_commit() is not called */	\
  hwa_begin_device(HWA_BEGIN_##reset)

#define HWA_BEGIN_			0
#define HWA_BEGIN_RESET			1


/*	Commit configuration to hardware.
 */
#define hwa_commit()							\
  do {									\
    if (0) { HWA_WARN("Did you forget to turn compiler optimization on?"); } \
    hwa_commit = 1 ;							\
    HWA_CORE0->commit = 1 ;						\
    hwa_commit_device();						\
  } while(0)

#define hwa_nocommit()							\
  do {									\
    HWA_CORE0->commit = 0 ;						\
    hwa_commit_device();						\
  } while(0)


#define HWA_STATE_OFF			0
#define HWA_STATE_ON			1


/*	Warnings and errors
 */
typedef enum {
  HWA_EXIT_ESR			= 63000,
  HWA_EXIT_ISR			= 64000,
  HWA_EXIT_MAIN			= 65000
} HwaExitValue ;

void				hwa_warn();
void __attribute__((noreturn))	hwa_exit ( HwaExitValue xv __attribute__((unused)) ) ;


#define HWA_WARN(...)			HWA_WARN_(__VA_ARGS__, __LINE__)
#if defined HWA_DEBUG
#  define HWA_WARN_(msg, num, ...)	hwa_warn()
#else
#  define HWA_WARN_(msg, num, ...)		\
  do {						\
    void __attribute__((noinline, warning(msg)))	\
      HWA_G2(hwa_warn, num)(void){hwa_warn();}	\
    HWA_G2(hwa_warn, num)();			\
  } while(0)
#endif


#define HWA_ERROR(...)			HWA_ERROR_(__VA_ARGS__, __LINE__)
#if defined HWA_DEBUG
#  define HWA_ERROR_(msg, num, ...)	hwa_warn()
#else
#define HWA_ERROR_(msg, num, ...)		\
  do {						\
    extern void __attribute__((error(msg)))	\
      HWA_G2(hwa_error, num)(void);		\
    HWA_G2(hwa_error, num)();			\
  } while(0)
#endif


/*	Concatenators, stringificator, extractors
 */
#define HWA_G2(a,b)			HWA_G2_(a,b)
#define HWA_G2_(a,b)			a##_##b

#define HWA_G3(a,b,c)			HWA_G3_(a,b,c)
#define HWA_G3_(a,b,c)			a##_##b##_##c

#define HWA_G4(a,b,c,d)			HWA_G4_(a,b,c,d)
#define HWA_G4_(a,b,c,d)		a##_##b##_##c##_##d

#define HWA_STR(x)			HWA_STR_(x)
#define HWA_STR_(x)			#x

#define HWA_1ST(...)			HWA_1ST_(__VA_ARGS__)
#define HWA_1ST_(a, ...)		a

#define HWA_2ND(...)			HWA_2ND_(__VA_ARGS__, 0)
#define HWA_2ND_(a, b, ...)		b

#define HWA_3RD(...)			HWA_3RD_(__VA_ARGS__, 0)
#define HWA_3RD_(a, b, c, ...)		c

#define HWA_4TH(...)			HWA_4TH_(__VA_ARGS__, 0)
#define HWA_4TH_(a, b, c, d, ...)	d

#define HWA_5TH(...)			HWA_5TH_(__VA_ARGS__, 0)
#define HWA_5TH_(a, b, c, d, e, ...)	e


/*	Mask corresponding to bits definition.
 *
 *	'bdef' must expand to 'mname, rname, bits, shift'
 */

#define HWA_BMSK(...)			HWA_BMSK_(__VA_ARGS__)
#define HWA_BMSK_(reg, bits, shift)		((bits)<<(shift))

#define HWA_BREG(...)			HWA_BREG_(__VA_ARGS__)
#define HWA_BREG_(reg, bits, shift)		reg


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


/*	Initialise virtual peripheral structure
 */
#define HWA_PINIT(mname, pname)			\
  mname pname##_ST ;				\
  mname *pname = &pname##_ST ;			\
  pname->hwaddr = pname##_BASE ;		\
  pname->used = 0


/*	Mandatory declarations for virtual peripheral structure
 */
#define HWA_PDCL(pname)				\
  intptr_t	hwaddr ;			\
  u8		used ;


/*	Access hardware registers from HWA pointer
 */
#define HWA_HREG(mname, p, rname)		HWA_HREG_(p, mname##_##rname)
#define HWA_HREG_(...)			HWA_HREG__(__VA_ARGS__)
#define HWA_HREG__(p, volatile, type, addr, ...)	\
  (*((volatile type *)(p->hwaddr+addr)))

#define HWA_HBGET(...)		HWA_HBGET_(__VA_ARGS__)
#define HWA_HBGET_(mname, ptr, rname, bits, shift)		\
  (((HWA_HREG(mname, ptr, rname)) & ((bits)<<(shift))) >> (shift))


#define HWA_HBSET(...)		HWA_HBSET_(__VA_ARGS__)
#define HWA_HBSET_(mname, ptr, rname, bits, shift, value)	\
  HWA_HREG(mname, ptr, rname) =					\
    (HWA_HREG(mname, ptr, rname) & ~((bits) << (shift))) | ((value) << (shift))


/*	Virtual register declaration
 */
#define HWA_VDCL(mname, rname)			\
  HWA_VTYPE(mname, rname) rname##_mvmask, rname##_mvalue, rname##_ovmask, rname##_ovalue


/*	Virtual register (lvalue).
 */
#define HWA_VREG(p,rname,vname)	p->rname##_##vname


/*	Future value of hardware register bits or -1 if unknown (rvalue).
 *
 *	'bdef' must expand to 'mname, rname, bits, shift'
 */
#define HWA_NVAL(p, rname, dfault)					\
  (HWA_VREG(p, rname, mvmask) ? HWA_VREG(p, rname, mvalue) :		\
   HWA_VREG(p, rname, ovmask) ? HWA_VREG(p, rname, ovalue) : dfault)


/*	Virtual register initialisation
 */
#define HWA_VINIT(mname, pname, rname, reset)				\
  do {									\
    pname->rname##_mvmask	= 0 ;					\
    pname->rname##_mvalue	= 0 ;					\
    pname->rname##_ovmask = reset ? HWA_HWMASK(mname, rname) : 0 ;	\
    pname->rname##_ovalue = reset ? HWA_HINIT(mname, rname) : 0 ;	\
  } while(0)


/*	Virtual 'sub-register' bits value (rvalue).
 *	mname is not used but kept for consistancy with VSET, VCOMMIT
 */
#define HWA_VBGET(...)		HWA_VBGET_(__VA_ARGS__)
#define HWA_VBGET_(mname, ptr, rname, bits, shift, vname)		\
  (((HWA_VREG(ptr, rname, vname)) & ((bits)<<(shift))) >> (shift))


#define HWA_VBSET(...)			HWA_VBSET_(__VA_ARGS__)
#define HWA_VBSET_(mname, ptr, rname, bits, shift, val)			\
  do {									\
    HWA_VTYPE(mname, rname) mmask = (bits) << (shift) ;			\
    HWA_VTYPE(mname, rname) vmask = (val) << (shift) ;			\
    if ( (HWA_HWMASK(mname, rname) & mmask) != mmask )			\
      HWA_ERROR("Try to modify not writeable bits.", vset1);		\
    if ( (HWA_VREG(ptr, rname, mvmask) & mmask) != 0			\
	 && (HWA_VREG(ptr, rname, mvalue) & mmask) != vmask )		\
      HWA_ERROR("Previous affectation with different value not committed.", vset2); \
    if ( ((HWA_VREG(ptr, rname, ovmask) & mmask) == mmask		\
	  && (HWA_VREG(ptr, rname, ovalue) & mmask) != vmask)		\
	 || (HWA_VREG(ptr, rname, ovmask) & mmask) != mmask) {		\
      ptr->used = 1 ;							\
      HWA_VREG(ptr, rname, mvmask) |= mmask ;				\
      HWA_VREG(ptr, rname, mvalue) =					\
	(HWA_VREG(ptr, rname, mvalue) & ~mmask)				\
	| (mmask & vmask) ;						\
    }									\
  } while(0)


/*	Write bits designed by mask from virtual to hardware register.
 *
 *	va must expand to 'mname, rname [, mask]'
 *	-1 is appended so that will be used as 'mask' if none given
 */
#define HWA_COMMIT(...)		HWA_COMMIT_(__VA_ARGS__, -1)
#define HWA_COMMIT_(core, mname, ptr, rname, mask, ...)			\
  do {									\
    HWA_VTYPE(mname, rname) m = HWA_VREG(ptr, rname, mvmask) & (mask) ; \
    if ( m != 0 ) {							\
      if ( m != HWA_HWMASK(mname, rname)				\
	   && HWA_VREG(ptr, rname, ovmask) != HWA_HWMASK(mname, rname) ) { \
	if ( core->commit && HWA_VADDR(mname, rname) != -1 )		\
	  HWA_VREG(ptr, rname, ovalue) = HWA_HREG(mname, ptr, rname) ;	\
	HWA_VREG(ptr, rname, ovmask) = HWA_HWMASK(mname, rname) ;	\
	HWA_VREG(ptr, rname, mvalue) =					\
	  (HWA_VREG(ptr, rname, ovalue) & ~HWA_VREG(ptr, rname, mvmask)) \
	  | (HWA_VREG(ptr, rname, mvalue) & HWA_VREG(ptr, rname, mvmask)) ; \
      }									\
      HWA_VREG(ptr, rname, ovalue) =					\
	(HWA_VREG(ptr, rname, ovalue) & ~m)				\
	| (HWA_VREG(ptr, rname, mvalue) & m) ;				\
      if ( core->commit && HWA_VADDR(mname, rname) != -1 )		\
	HWA_HREG(mname, ptr, rname) = HWA_VREG(ptr, rname, ovalue) ;	\
      HWA_VREG(ptr, rname, mvmask) &= ~m ;				\
      HWA_VREG(ptr, rname, ovmask) |= m ;				\
    }									\
  } while(0)



inline s8
hwa_log2_ceil ( u32 n )
{
  s8 l2 = 0 ;
  if ( (1UL<<l2) >= n ) return l2 ; l2++ ;
  if ( (1UL<<l2) >= n ) return l2 ; l2++ ;
  if ( (1UL<<l2) >= n ) return l2 ; l2++ ;
  if ( (1UL<<l2) >= n ) return l2 ; l2++ ;
  if ( (1UL<<l2) >= n ) return l2 ; l2++ ;
  if ( (1UL<<l2) >= n ) return l2 ; l2++ ;
  if ( (1UL<<l2) >= n ) return l2 ; l2++ ;
  if ( (1UL<<l2) >= n ) return l2 ; l2++ ;
  if ( (1UL<<l2) >= n ) return l2 ; l2++ ;
  if ( (1UL<<l2) >= n ) return l2 ; l2++ ;
  if ( (1UL<<l2) >= n ) return l2 ; l2++ ;
  if ( (1UL<<l2) >= n ) return l2 ; l2++ ;
  if ( (1UL<<l2) >= n ) return l2 ; l2++ ;
  if ( (1UL<<l2) >= n ) return l2 ; l2++ ;
  if ( (1UL<<l2) >= n ) return l2 ; l2++ ;
  if ( (1UL<<l2) >= n ) return l2 ; l2++ ;
  return l2 ;
}


/*	Include device-specific definitions from "hwa_<device>.h"
 */
#ifndef HWA_DEVICE
#  error "HWA_DEVICE not defined."
#endif

#include HWA_STR(HWA_G2(hwa, HWA_DEVICE).h)


#endif
