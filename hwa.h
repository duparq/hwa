#ifndef HWA_H
#define HWA_H

#include "types.h"

#if defined HWA_DBG
extern int hwa_dbg_gethr( const char *file, uint line,
			  const char *mname, const char *rname,
			  intptr_t addr ) ;
extern void hwa_dbg_sethr( const char *file, uint line,
			   const char *mname, const char *rname,
			   u8 size, intptr_t addr, uint omask, uint mask, uint val ) ;
#  define hwa_dbg_loadsr_(ptr, rname, mmask)	\
  hwa_dbg_loadsr(__FILE__, __LINE__, ptr, rname, mmask);			\
  HWA_SR(ptr, rname, mvalue) =						\
    (HWA_SR(ptr, rname, ovalue) & ~HWA_SR(ptr, rname, mmask))		\
    | (HWA_SR(ptr, rname, mvalue) & HWA_SR(ptr, rname, mmask)) ;
#else
#  define hwa_dbg_loadsr(ptr, rname, mmask)
#endif


/*	Hardware register Address
 */
#define HW_HA(mname, pname, rname)		HW_HA_(pname, HWA_G2(mname,rname))
#define HW_HA_(...)				HW_HA__(__VA_ARGS__)
#define HW_HA__(pname, volatile, type, addr, ...)	\
  (pname##_BASE+addr)

/*	Hardware Register
 *
 *	'mname##_##rname' must expand to 'volatile, type, address, ...'
 */
#define HW_HR(mname, pname, rname)		HW_HR_(pname, HWA_G2(mname,rname))
#define HW_HR_(...)				HW_HR__(__VA_ARGS__)
#define HW_HR__(pname, volatile, type, addr, ...)	\
  (*((volatile type *)(pname##_BASE+addr)))

#define HW_GETHR(mname, pname, rname)		HW_GETHR_(pname, HWA_G2(mname,rname))
#define HW_GETHR_(...)				HW_GETHR__(__VA_ARGS__)
#if !defined HWA_DBG
#  define HW_GETHR__(pname, volatile, type, addr, ...)	\
  (*((volatile type *)(pname##_BASE+addr)))
#else
//#  define HW_GETHR__(pname, volatile, type, addr, ...)	hwa_dbg_gethr(#pname, addr)
#endif


/*	SET Hardware Register
*/
#define HW_SETHR(...)				HW_SETHR_(__VA_ARGS__)
#if defined HWA_DBG
#  define HW_SETHR_(mname, pname, rname, val)	\
  hwa_dbg("HW_HR(%s, %s, %s)=%d",  #mname, #pname, #rname, val)
#else
#  define HW_SETHR_(mname, pname, rname, val)	\
  HW_HR(mname, pname, rname) = val
#endif

/*	Peripheral TYPE
 *	This is the definition of the symbol {pname}##_TYPE
 */
#define HW_PTYPE(pname)			HW_PTYPE_(pname)
#define HW_PTYPE_(pname)		HWA_G2(pname, TYPE)

/*	Returns a register bit mask for the peripheral flag
 */
#define HW_MSK(pname, flag)		HW_MSK_(HW_PTYPE(pname), flag)
#define HW_MSK_(ptype, flag)		HWA_BMSK(HWA_G3(ptype, FLAG, flag))

/*	Test Hardware register Bits
 */
#define HW_TSTHB(...)				HW_TSTHB_(__VA_ARGS__)
#define HW_TSTHB_(mname, pname, rname, mask, shift)	\
  (HW_HR(mname, pname, rname) & ((mask) << (shift)))

/*	GET Hardware register Bits
 */
#define HW_GETHB(...)				HW_GETHB_(__VA_ARGS__)
#define HW_GETHB_(mname, pname, rname, mask, shift)			\
  ((HW_HR(mname, pname, rname) & ((mask) << (shift))) >> (shift))

/*	SET Hardware register Bits
 */
#define HW_SETHB(...)				HW_SETHB_(__VA_ARGS__)
#define HW_SETHB_(mname, pname, rname, mask, shift, value)		\
    HW_HR(mname, pname, rname) =					\
      (HW_HR(mname, pname, rname) & ~((mask) << (shift))) | ((value) << (shift))

#define HW_ATOMIC_SETHB(...)			HW_ATOMIC_SETHB_(__VA_ARGS__)
#define HW_ATOMIC_SETHB_(mname, pname, rname, mask, shift, value)		\
  do {									\
    if ( HW_HA(mname, pname, rname) > 0x1F )				\
      hw_disable_interrupts();						\
    HW_HR(mname, pname, rname) =					\
      (HW_HR(mname, pname, rname) & ~((mask) << (shift))) | ((value) << (shift)) ; \
    if ( HW_HA(mname, pname, rname) > 0x1F )				\
      hw_enable_interrupts();						\
  } while(0)



/*	Begin a HWA session.
 */
#define hwa_begin(begin_state)						\
  u8	hwa_commit = 0 ; /* Will warn if hwa_commit() is not called */	\
  hwa_begin_device(HWA_BEGIN_##begin_state)

#define HWA_BEGIN_			0
#define HWA_BEGIN_RESET			1


/*	Commit configuration to hardware.
 */
#define hwa_commit()							\
  do {									\
    if (0) { HWA_WARN("Did you forget to turn optimizations on?"); }	\
    u8 foo __attribute__((unused)) = hwa_commit ;			\
    /* hwa_commit = 1 ; */						\
    HWA_CORE0->commit = 1 ;						\
    hwa_commit_device();						\
  } while(0)

#define hwa_nocommit()							\
  do {									\
    if (0) { HWA_WARN("Did you forget to turn optimizations on?"); }	\
    HWA_CORE0->commit = 0 ;						\
    hwa_commit_device();						\
  } while(0)


#define HWA_STATE_0			0
#define HWA_STATE_OFF			0
#define HWA_STATE_1			1
#define HWA_STATE_ON			1

#define HWA_STATE(x)			HWA_STATE_ ## x


/*	Warnings and errors
 */
void				hwa_warn();

#define HWA_WARN(...)			HWA_WARN_(__VA_ARGS__, __COUNTER__)
#if defined HWA_DEBUG
#  define HWA_WARN_(msg, num, ...)	hwa_warn()
#else
#  define HWA_WARN_(msg, num, ...)			\
  do {							\
    void __attribute__((noinline, warning(msg)))	\
      HWA_G2(hwa_warn, num)(void){hwa_warn();}		\
    HWA_G2(hwa_warn, num)();				\
  } while(0)
#endif

#define HWA_ERROR(...)			HWA_ERROR_(__VA_ARGS__, __COUNTER__)
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

#define HWA_BREG(...)			HWA_BREG_(__VA_ARGS__)
#define HWA_BREG_(reg, bits, shift)	reg

#define HWA_BMSK(...)			HWA_BMSK_(__VA_ARGS__)
#define HWA_BMSK_(reg, bits, shift)	(bits<<shift)
/* #define HWA_BMSK_(reg, bits, shift)	(bits)<<(shift) */

#define HWA_BSHFT(...)			HWA_BSHFT_(__VA_ARGS__)
#define HWA_BSHFT_(reg, bits, shift)	shift


/*	Hardware register Type
 */
#define HWA_HT(mname, rname)		HWA_2ND(mname##_##rname)

/*	Hardware register Address
 */
#define HWA_HA(mname, rname)		HWA_3RD(mname##_##rname)

/*	Hardware register Reset Value
 */
#define HWA_HRV(mname, rname)		HWA_4TH(mname##_##rname)

/*	Hardware register Writeable Bits
 */
#define HWA_HWB(mname, rname)		HWA_5TH(mname##_##rname)


/*	Initialise virtual peripheral structure
 */
#define HWA_PINIT(mname, pname)			\
  mname pname##_ST ;				\
  mname *pname = &pname##_ST ;			\
  pname->hwaddr = pname##_BASE ;		\
  pname->used = 0 ;


/*	Mandatory declarations for virtual peripheral structure
 */
#define HWA_PDCL(pname)				\
  intptr_t	hwaddr ;			\
  u8		used ;


/*	Access hardware registers from HWA pointer
 */
/* #define HWA_HR(mname, p, rname)		HWA_HR_(p, mname##_##rname) */
/* #define HWA_HR_(...)				HWA_HR__(__VA_ARGS__) */
/* #define HWA_HR__(p, volatile, type, addr, ...)	\ */
/*   (*((volatile type *)(p->hwaddr+addr))) */

#if !defined HWA_DBG
#  define HWA_GETHR(mname, p, rname)			HWA_GETHR_(p, mname##_##rname)
#  define HWA_GETHR_(...)				HWA_GETHR__(__VA_ARGS__)
#  define HWA_GETHR__(p, volatile, type, addr, ...)	\
  (*((volatile type *)(p->hwaddr+addr)))
#else
#  define HWA_GETHR(mname, p, rname)		HWA_GETHR_(mname, p, rname, mname##_##rname)
#  define HWA_GETHR_(mname, p, rname, ...)	HWA_GETHR__(mname, p, rname, __VA_ARGS__)
#  define HWA_GETHR__(mname, p, rname, volatile, type, addr, ...)	\
  hwa_dbg_gethr(__FILE__, __LINE__, #mname, #rname, p->hwaddr+addr)
#endif

/*	GET Hard register Bits
 */
#define HWA_GETHB(...)			HWA_GETHB_(__VA_ARGS__)
#define HWA_GETHB_(mname, ptr, rname, bits, shift)			\
  (((HWA_GETHR(mname, ptr, rname)) & ((bits)<<(shift))) >> (shift))

/*	SET Hard Register
 */
#if !defined HWA_DBG
#  define HWA_SETHR(mname, p, rname, val)	HWA_SETHR_(p, val, mname##_##rname)
#  define HWA_SETHR_(p, val, ...)		HWA_SETHR__(p, val, __VA_ARGS__)
#  define HWA_SETHR__(p, val, volatile, type, addr, ...)	\
  *((volatile type *)(p->hwaddr+addr)) = val
#else
#  define HWA_SETHR(mname, p, rname, val)	\
  HWA_SETHR_(mname, p, rname, HWA_SR(p, rname, omask), m, val, mname##_##rname)
#  define HWA_SETHR_(mname, p, rname, om, m, val, ...)	\
  HWA_SETHR__(mname, p, rname, om, m, val, __VA_ARGS__)
#  define HWA_SETHR__(mname, p, rname, om, m, val, volatile, type, addr, ...) \
  hwa_dbg_sethr(__FILE__, __LINE__, #mname, #rname, sizeof(type), p->hwaddr+addr, om, m, val)
#endif

/*	SET Hard register Bits
 */
#define HWA_SETHB(...)			HWA_SETHB_(__VA_ARGS__)
#define HWA_SETHB_(mname, ptr, rname, bits, shift, value)		\
  HWA_SETHR(mname, ptr, rname,						\
	    (HWA_GETHR(mname, ptr, rname) & ~((bits) << (shift))) | ((value) << (shift)))

/*	Virtual register declaration
 */
#define HWA_VDCL(mname, rname)						\
  HWA_HT(mname, rname) rname##_mmask, rname##_mvalue, rname##_omask, rname##_ovalue ;


/*	Virtual Sub-register (lvalue).
 */
#define HWA_SR(p,rname,vname)	p->rname##_##vname


/*	Virtual Sub-register MaSK
 */
#define HWA_SMSK(...)		HWA_SMSK_(__VA_ARGS__)
#define HWA_SMSK_(mname, ptr, vname, rname, bits, shift)	\
  ((HWA_SR(ptr, rname, vname)) & ((bits)<<(shift)))


/*	True if bits are to be changed
 */
#define rem_todo_HWA_HBCHG(p, rname, bdef)			\
  (HWA_SR(p, rname, mmask) ? HWA_SR(p, rname, mvalue) :		\
   HWA_SR(p, rname, omask) ? HWA_SR(p, rname, ovalue) : dflt)


/*	True if bits are/were set (known state)
 */
//#define HWA_GETFMB(...)		HWA_GETFMB_(__VA_ARGS__)
#define HWA_TSTFMB(mname, p, bdef)					\
  (HWA_SMSK(mname, p, omask, bdef) != 0 || HWA_SMSK(mname, p, mmask, bdef) != 0)


/*	Virtual register initialisation
 */
#define HWA_VINIT(mname, pname, rname, reset)			\
  do {								\
    pname->rname##_mmask  = 0 ;					\
    /* pname->rname##_mvalue = 0 ; */				\
    pname->rname##_omask  = reset ? HWA_HWB(mname, rname) : 0 ;	\
    pname->rname##_ovalue = reset ? HWA_HRV(mname, rname) : 0 ;	\
    pname->rname##_mvalue = pname->rname##_ovalue ;		\
  } while(0)


#define HWA_RESET(mname, pname, rname)			\
  do {							\
    pname->rname##_mmask  = 0 ;				\
    /* pname->rname##_mvalue = 0 ; */			\
    pname->rname##_omask  = HWA_HWB(mname, rname) ;	\
    pname->rname##_ovalue = HWA_HRV(mname, rname) ;	\
    pname->rname##_mvalue = pname->rname##_ovalue ;	\
  } while(0)


/*	GET virtual Sub-register Bits
 *	mname is not used but kept for consistancy with VSET, VCOMMIT
 */
#define HWA_GETSB(...)		HWA_GETSB_(__VA_ARGS__)
#define HWA_GETSB_(mname, ptr, vname, rname, bits, shift)		\
  (((HWA_SR(ptr, rname, vname)) & ((bits)<<(shift))) >> (shift))


/*	GET Virtual register Bits
 *	Returns the value that will be committed to hardware register
 *	or dflt if never set and left unchanged
 */
#define HWA_GETVB(...)		HWA_GETVB_(__VA_ARGS__)
#define HWA_GETVB_(p, rname, bits, shift, dflt)				\
  (((HWA_SR(p, rname, mmask)|HWA_SR(p, rname, omask)) & ((bits)<<(shift))) ? \
   (HWA_SR(p, rname, mvalue) & ((bits)<<(shift))) >> (shift) :		\
   dflt)
/* #define HWA_GETVB_(p, rname, bits, shift, dflt)	\ */
/*   ((HWA_SR(p, rname, mmask) & ((bits)<<(shift))) ?			\ */
/*    (HWA_SR(p, rname, mvalue) & ((bits)<<(shift))) >> (shift) :		\ */
/*    ((HWA_SR(p, rname, omask)  & ((bits)<<(shift))) ?			\ */
/*     (HWA_SR(p, rname, ovalue) & ((bits)<<(shift))) >> (shift) :		\ */
/*     dflt)) */


/*	GET Virtual register
 *	Returns the value that will be committed to hardware register
 *	or dflt if never set and left unchanged
 */
#define HWA_GETVR(p, rname, dflt)			\
  ((HWA_SR(p, rname, mmask)|HWA_SR(p, rname, omask)) ?	\
   HWA_SR(p, rname, mvalue) : dflt)


/*	SET Virtual register Bits
 *	mmask is changed only if value is changed
 */
#define HWA_SETVB(...)			HWA_SETVB_(__VA_ARGS__)
#define HWA_SETVB_(mname, ptr, rname, bits, shift, val)			\
  do {									\
    HWA_HT(mname, rname) mmask = (bits) << (shift) ;		\
    HWA_HT(mname, rname) vmask = (val) << (shift) ;			\
    if ( (HWA_HWB(mname, rname) & mmask) != mmask )			\
      HWA_ERROR(#rname ": try to modify not writeable bits.", __COUNTER__); \
    if ( (HWA_SR(ptr, rname, mmask) & mmask) != 0			\
	 && (HWA_SR(ptr, rname, mvalue) & mmask) != vmask )		\
      HWA_ERROR(#rname ": previous affectation with different value not committed.", __COUNTER__); \
    if ( ((HWA_SR(ptr, rname, omask) & mmask) == mmask			\
	  && (HWA_SR(ptr, rname, ovalue) & mmask) != vmask)		\
	 || (HWA_SR(ptr, rname, omask) & mmask) != mmask) {		\
      ptr->used = 1 ;							\
      HWA_SR(ptr, rname, mmask) |= mmask ;				\
      HWA_SR(ptr, rname, mvalue) =					\
	(HWA_SR(ptr, rname, mvalue) & ~mmask)				\
	| (mmask & vmask) ;						\
    }									\
  } while(0)

#define HWA_SETVR(...)			HWA_SETVR_(__VA_ARGS__)
#define HWA_SETVR_(mname, ptr, rname, val)	\
  HWA_SETVB_(mname, ptr, rname, -1, 0, val)


/*	Write bits designed by mask from virtual to hardware register.
 *
 *	va must expand to 'mname, rname [, mask]'
 *	-1 is appended to be used as 'mask' if none is given
 */
#define HWA_COMMIT(...)		HWA_COMMIT_(__VA_ARGS__, -1)
#define HWA_COMMIT_(core, mname, ptr, rname, mask, ...)			\
  do {									\
    HWA_HT(mname, rname) m = HWA_SR(ptr, rname, mmask) & (mask) ;	\
    if ( m != 0 ) {							\
      if ( m != HWA_HWB(mname, rname)					\
	   && HWA_SR(ptr, rname, omask) != HWA_HWB(mname, rname) ) {	\
	if ( core->commit && HWA_HA(mname, rname) != -1 ) {		\
	  HWA_SR(ptr, rname, ovalue) = HWA_GETHR(mname, ptr, rname) ;	\
	  HWA_SR(ptr, rname, omask) = HWA_HWB(mname, rname) ;		\
	}								\
	HWA_SR(ptr, rname, mvalue) =					\
	  (HWA_SR(ptr, rname, ovalue) & ~HWA_SR(ptr, rname, mmask))	\
	  | (HWA_SR(ptr, rname, mvalue) & HWA_SR(ptr, rname, mmask)) ;	\
      }									\
      HWA_SR(ptr, rname, ovalue) =					\
	(HWA_SR(ptr, rname, ovalue) & ~m)				\
	| (HWA_SR(ptr, rname, mvalue) & m) ;				\
      if ( core->commit && HWA_HA(mname, rname) != -1 )			\
	HWA_SETHR(mname, ptr, rname, HWA_SR(ptr, rname, ovalue));	\
      HWA_SR(ptr, rname, mmask) &= ~m ;					\
      HWA_SR(ptr, rname, omask) |= m ;					\
    }									\
  } while(0)


#include "types.h"

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


#define HWA_IP(device)			HWA_IP_(device)
#define HWA_IP_(device)			device/hwa##_##device


/*	Include device-specific definitions from "hwa_<device>.h"
 */
#ifndef HWA_DEVICE
#  error "HWA_DEVICE not defined."
#endif

//#include HWA_STR(HWA_G2(hwa, HWA_DEVICE).h)
#include HWA_STR(HWA_IP(HWA_DEVICE).h)


#endif
