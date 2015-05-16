# 1 "main.c"
# 1 "/home/indy/dev/hwa-dev/examples/05-2-swuart-sync-rx-tx//"
# 1 "<command-line>"
# 1 "main.c"
# 12 "main.c"
# 1 "config.h" 1



# 1 "/home/indy/dev/hwa-dev/examples/targets/attiny84.h" 1
# 5 "config.h" 2
# 13 "main.c" 2
# 1 "/home/indy/dev/hwa-dev/hwa.h" 1
# 40 "/home/indy/dev/hwa-dev/hwa.h"
# 1 "/home/indy/dev/hwa-dev/hwa__macros.h" 1
# 45 "/home/indy/dev/hwa-dev/hwa__macros.h"
extern char hw_error ;
# 41 "/home/indy/dev/hwa-dev/hwa.h" 2
# 1 "/home/indy/dev/hwa-dev/hwa__interrupts.h" 1
# 42 "/home/indy/dev/hwa-dev/hwa.h" 2




# 1 "/usr/lib/gcc/avr/4.8.2/include/stdint.h" 1 3 4
# 9 "/usr/lib/gcc/avr/4.8.2/include/stdint.h" 3 4
# 1 "/usr/lib/avr/include/stdint.h" 1 3 4
# 121 "/usr/lib/avr/include/stdint.h" 3 4
typedef signed int int8_t __attribute__((__mode__(__QI__)));
typedef unsigned int uint8_t __attribute__((__mode__(__QI__)));
typedef signed int int16_t __attribute__ ((__mode__ (__HI__)));
typedef unsigned int uint16_t __attribute__ ((__mode__ (__HI__)));
typedef signed int int32_t __attribute__ ((__mode__ (__SI__)));
typedef unsigned int uint32_t __attribute__ ((__mode__ (__SI__)));

typedef signed int int64_t __attribute__((__mode__(__DI__)));
typedef unsigned int uint64_t __attribute__((__mode__(__DI__)));
# 142 "/usr/lib/avr/include/stdint.h" 3 4
typedef int16_t intptr_t;




typedef uint16_t uintptr_t;
# 159 "/usr/lib/avr/include/stdint.h" 3 4
typedef int8_t int_least8_t;




typedef uint8_t uint_least8_t;




typedef int16_t int_least16_t;




typedef uint16_t uint_least16_t;




typedef int32_t int_least32_t;




typedef uint32_t uint_least32_t;







typedef int64_t int_least64_t;






typedef uint64_t uint_least64_t;
# 213 "/usr/lib/avr/include/stdint.h" 3 4
typedef int8_t int_fast8_t;




typedef uint8_t uint_fast8_t;




typedef int16_t int_fast16_t;




typedef uint16_t uint_fast16_t;




typedef int32_t int_fast32_t;




typedef uint32_t uint_fast32_t;







typedef int64_t int_fast64_t;






typedef uint64_t uint_fast64_t;
# 273 "/usr/lib/avr/include/stdint.h" 3 4
typedef int64_t intmax_t;




typedef uint64_t uintmax_t;
# 10 "/usr/lib/gcc/avr/4.8.2/include/stdint.h" 2 3 4
# 47 "/home/indy/dev/hwa-dev/hwa.h" 2
# 93 "/home/indy/dev/hwa-dev/hwa.h"
typedef struct hwa_r8_t
{
  intptr_t a ;
  uint8_t mmask ;
  uint8_t mvalue ;
  uint8_t omask ;
  uint8_t ovalue ;
} hwa_r8_t ;

typedef struct hwa_r16_t
{
  intptr_t a ;
  uint16_t mmask ;
  uint16_t mvalue ;
  uint16_t omask ;
  uint16_t ovalue ;
} hwa_r16_t ;

typedef struct rem_hwa_r32_t
{
  intptr_t a ;
  uint32_t mmask ;
  uint32_t mvalue ;
  uint32_t omask ;
  uint32_t ovalue ;
} hwa_r32_t ;
# 129 "/home/indy/dev/hwa-dev/hwa.h"
# 1 "/home/indy/dev/hwa-dev/hwa_attiny84_1.h" 1
# 17 "/home/indy/dev/hwa-dev/hwa_attiny84_1.h"
# 1 "/home/indy/dev/hwa-dev/hwa_attinyx4_1.h" 1
# 15 "/home/indy/dev/hwa-dev/hwa_attinyx4_1.h"
# 1 "/home/indy/dev/hwa-dev/hwa_atmelavr_1.h" 1
# 16 "/home/indy/dev/hwa-dev/hwa_attinyx4_1.h" 2

# 1 "/home/indy/dev/hwa-dev/hwa_atmelavr__corea_1.h" 1
# 54 "/home/indy/dev/hwa-dev/hwa_atmelavr__corea_1.h"
typedef struct {
  hwa_r8_t sreg ;
  hwa_r8_t gimsk ;
  hwa_r8_t gifr ;
  hwa_r8_t mcucr ;
  hwa_r8_t mcusr ;
  hwa_r8_t osccal ;
  hwa_r8_t gpior2 ;
  hwa_r8_t gpior1 ;
  hwa_r8_t gpior0 ;
  hwa_r8_t prr ;
} hwa_corea_t ;
# 18 "/home/indy/dev/hwa-dev/hwa_attinyx4_1.h" 2
# 1 "/home/indy/dev/hwa-dev/hwa_atmelavr__io_1.h" 1
# 23 "/home/indy/dev/hwa-dev/hwa_atmelavr__io_1.h"
typedef struct {
  hwa_r8_t port ;
  hwa_r8_t ddr ;
} hwa_io8a_t ;
# 19 "/home/indy/dev/hwa-dev/hwa_attinyx4_1.h" 2
# 1 "/home/indy/dev/hwa-dev/hwa_atmelavr__pcica_1.h" 1
# 19 "/home/indy/dev/hwa-dev/hwa_atmelavr__pcica_1.h"
typedef struct {
  hwa_r8_t msk0 ;
  hwa_r8_t msk1 ;

} hwa_pcica_t ;
# 20 "/home/indy/dev/hwa-dev/hwa_attinyx4_1.h" 2
# 1 "/home/indy/dev/hwa-dev/hwa_atmelavr__wdoga_1.h" 1
# 9 "/home/indy/dev/hwa-dev/hwa_atmelavr__wdoga_1.h"
# 1 "/home/indy/dev/hwa-dev/hwa_atmelavr__wdog_1.h" 1
# 10 "/home/indy/dev/hwa-dev/hwa_atmelavr__wdog_1.h"
typedef struct {
  intptr_t address ;
  uint8_t action, timeout ;
  hwa_r8_t csr ;
} hwa_wdog_t ;
# 10 "/home/indy/dev/hwa-dev/hwa_atmelavr__wdoga_1.h" 2
# 21 "/home/indy/dev/hwa-dev/hwa_attinyx4_1.h" 2
# 1 "/home/indy/dev/hwa-dev/hwa_atmelavr__c8a_1.h" 1
# 32 "/home/indy/dev/hwa-dev/hwa_atmelavr__c8a_1.h"
typedef struct {



  hwa_r8_t ccra ;
  hwa_r8_t ccrb ;
  hwa_r8_t count ;
  union {
    hwa_r8_t ocra ;
    hwa_r8_t compare0 ;
  };
  union {
    hwa_r8_t ocrb ;
    hwa_r8_t compare1 ;
  };

  hwa_r8_t imsk ;
  hwa_r8_t ifr ;




  uint8_t clock, countmode, top, overflow ;
  uint8_t compare0_update, compare0_output ;
  uint8_t compare1_update, compare1_output ;
# 65 "/home/indy/dev/hwa-dev/hwa_atmelavr__c8a_1.h"
} hwa_c8a_t ;
# 22 "/home/indy/dev/hwa-dev/hwa_attinyx4_1.h" 2
# 1 "/home/indy/dev/hwa-dev/hwa_atmelavr__c16a_1.h" 1
# 52 "/home/indy/dev/hwa-dev/hwa_atmelavr__c16a_1.h"
typedef struct {



  hwa_r8_t ccra ;
  hwa_r8_t ccrb ;
  hwa_r8_t ccrc ;
  hwa_r16_t count ;
  union {
    hwa_r16_t ocra ;
    hwa_r16_t compare0 ;
  };
  union {
    hwa_r16_t ocrb ;
    hwa_r16_t compare1 ;
  };
  union {
    hwa_r16_t icr ;
    hwa_r16_t capture0 ;
  };
  hwa_r8_t imsk ;
  hwa_r8_t ifr ;



  uint8_t clock, countmode, top, overflow ;
  uint8_t compare0_update ;
  uint8_t compare0_output ;
  uint8_t compare1_update ;
  uint8_t compare1_output ;
  uint8_t icr_input, icr_edge, icr_filter ;

} hwa_c16a_t ;
# 23 "/home/indy/dev/hwa-dev/hwa_attinyx4_1.h" 2
# 1 "/home/indy/dev/hwa-dev/hwa_atmelavr__ocua_1.h" 1
# 19 "/home/indy/dev/hwa-dev/hwa_atmelavr__ocua_1.h"
typedef struct {
  uint8_t update, output ;
} hwa_ocua_t ;
# 24 "/home/indy/dev/hwa-dev/hwa_attinyx4_1.h" 2
# 1 "/home/indy/dev/hwa-dev/hwa_atmelavr__icua_1.h" 1
# 25 "/home/indy/dev/hwa-dev/hwa_attinyx4_1.h" 2
# 1 "/home/indy/dev/hwa-dev/hwa_atmelavr__acmpa_1.h" 1
# 29 "/home/indy/dev/hwa-dev/hwa_atmelavr__acmpa_1.h"
typedef struct { hwa_r8_t csr ; } hwa_acmpa_t ;
# 26 "/home/indy/dev/hwa-dev/hwa_attinyx4_1.h" 2
# 1 "/home/indy/dev/hwa-dev/hwa_atmelavr__ad10a_1.h" 1
# 26 "/home/indy/dev/hwa-dev/hwa_atmelavr__ad10a_1.h"
typedef struct {
  hwa_r8_t admux ;
  hwa_r8_t sra ;
  hwa_r8_t srb ;
  hwa_r8_t did ;
} hwa_ad10a_t ;
# 27 "/home/indy/dev/hwa-dev/hwa_attinyx4_1.h" 2
# 17 "/home/indy/dev/hwa-dev/hwa_attiny84_1.h" 2
# 130 "/home/indy/dev/hwa-dev/hwa.h" 2
# 144 "/home/indy/dev/hwa-dev/hwa.h"
typedef struct {
  uint8_t commit ;
  hwa_corea_t hw_core0 ; hwa_io8a_t hw_porta ; hwa_io8a_t hw_portb ; hwa_pcica_t hw_pcic0 ; hwa_wdog_t hw_watchdog0 ; hwa_c8a_t hw_counter0 ; hwa_c16a_t hw_counter1 ; hwa_acmpa_t hw_acmp0 ; hwa_ad10a_t hw_adc0 ;
} hwa_t ;

struct hwa_t ;
# 1 "/home/indy/dev/hwa-dev/hwa__2.h" 1
# 298 "/home/indy/dev/hwa-dev/hwa__2.h"
static inline __attribute__((always_inline)) void _hwa_begin_r8 ( hwa_r8_t *r, intptr_t a )
{
  r->a = a ;
  r->mmask = 0 ;
  r->mvalue = 0 ;
  r->omask = 0 ;
  r->ovalue = 0 ;
}

static inline __attribute__((always_inline)) void _hwa_begin_r16 ( hwa_r16_t *r, intptr_t a )
{
  r->a = a ;
  r->mmask = 0 ;
  r->mvalue = 0 ;
  r->omask = 0 ;
  r->ovalue = 0 ;
}




static inline __attribute__((always_inline)) void _hwa_set_r8 ( hwa_r8_t *r, uint8_t v )
{
  if ( r->mmask )
    do { extern void __attribute__((error("commit required before resetting."))) hwa_error_0(void); hwa_error_0(); } while(0);

  r->mmask = 0xFF ;
  r->mvalue = v ;
}

static inline __attribute__((always_inline)) void _hwa_set_r16 ( hwa_r16_t *r, uint16_t v )
{
  if ( r->mmask )
    do { extern void __attribute__((error("commit required before resetting."))) hwa_error_1(void); hwa_error_1(); } while(0);

  r->mmask = 0xFFFF ;
  r->mvalue = v ;
}
# 344 "/home/indy/dev/hwa-dev/hwa__2.h"
static inline __attribute__((always_inline)) void _hwa_write_r8 ( hwa_r8_t *r,
          uint8_t rwm, uint8_t rfm,
          uint8_t bn, uint8_t bp, uint8_t v )
{
  if (bn == 0)
    do { extern void __attribute__((error("no bit to be changed?"))) hwa_error_2(void); hwa_error_2(); } while(0);

  if (v > (1U<<bn)-1)
    do { extern void __attribute__((error("value too high for number of bits."))) hwa_error_3(void); hwa_error_3(); } while(0);

  uint8_t sm = ((1U<<bn)-1) << bp ;



  uint8_t sv = v << bp ;



  if ((rwm & sm) != sm)
    do { extern void __attribute__((error("bits not writeable."))) hwa_error_4(void); hwa_error_4(); } while(0);

  if ((r->mmask & sm) != 0 && (r->mvalue & sm) != sv)
    do { extern void __attribute__((error("committing is required before setting a new value."))) hwa_error_5(void); hwa_error_5(); } while(0);

  if ( sm & rfm )
    if ( v == 0 )
      do { extern void __attribute__((error("flag bit can only be cleared by writing 1 into it."))) hwa_error_6(void); hwa_error_6(); } while(0);

  r->mmask |= sm ;
  r->mvalue = (r->mvalue & ~sm) | (sm & sv) ;
}

static inline __attribute__((always_inline)) void _hwa_write_r16 ( hwa_r16_t *r,
    uint16_t rwm, uint16_t rfm,
    uint8_t bn, uint8_t bp, uint16_t v )
{
  if (bn == 0)
    do { extern void __attribute__((error("no bit to be changed?"))) hwa_error_7(void); hwa_error_7(); } while(0);

  if (v > (1U<<bn)-1)
    do { extern void __attribute__((error("value too high for bits number."))) hwa_error_8(void); hwa_error_8(); } while(0);

  uint16_t sm = ((1U<<bn)-1) << bp ;
  uint16_t sv = v << bp ;

  if ((rwm & sm) != sm)
    do { extern void __attribute__((error("bits not writeable."))) hwa_error_9(void); hwa_error_9(); } while(0);

  if ((r->mmask & sm) != 0 && (r->mvalue & sm) != sv)
    do { extern void __attribute__((error("commit required before setting a new value."))) hwa_error_10(void); hwa_error_10(); } while(0);

  if ( sm & rfm )
    if ( v == 0 )
      do { extern void __attribute__((error("flag bit can only be cleared by writing 1 into it."))) hwa_error_11(void); hwa_error_11(); } while(0);

  r->mmask |= sm ;
  r->mvalue = (r->mvalue & ~sm) | (sm & sv) ;
}
# 420 "/home/indy/dev/hwa-dev/hwa__2.h"
static inline __attribute__((always_inline)) void hwa_check_optimizations ( uint8_t x )
{
  if (x) { do { extern void __attribute__((error("you may have forgotten to turn optimizations on."))) hwa_error_12(void); hwa_error_12(); } while(0); }
}
# 493 "/home/indy/dev/hwa-dev/hwa__2.h"
# 1 "/home/indy/dev/hwa-dev/hwa_attiny84_2.h" 1






# 1 "/home/indy/dev/hwa-dev/hwa_attinyx4_2.h" 1






# 1 "/home/indy/dev/hwa-dev/hwa_atmelavr_2.h" 1
# 48 "/home/indy/dev/hwa-dev/hwa_atmelavr_2.h"
static inline __attribute__((always_inline)) void _hw_write_r8 ( intptr_t ra, uint8_t rwm, uint8_t rfm,
         uint8_t bn, uint8_t bp, uint8_t v )
{

  if ( ra == ~0 )
    do { extern void __attribute__((error("invalid access"))) hwa_error_13(void); hwa_error_13(); } while(0);



  if ( bn == 0 )
    do { extern void __attribute__((error("no bit to be changed?"))) hwa_error_14(void); hwa_error_14(); } while(0);




  uint8_t wm = (1U<<bn)-1 ;


  if (v > wm)
    do { extern void __attribute__((error("value too high for bits number"))) hwa_error_15(void); hwa_error_15(); } while(0);


  wm <<= bp ;
  v <<= bp ;



  if ( (v & wm & rwm) != (v & wm) )
    do { extern void __attribute__((error("bits not writeable."))) hwa_error_16(void); hwa_error_16(); } while(0);

  volatile uint8_t *p = (volatile uint8_t *)ra ;

  if ( ra < 0x40 &&
       (wm==0x01 || wm==0x02 || wm==0x04 || wm==0x08 ||
 wm==0x10 || wm==0x20 || wm==0x40 || wm==0x80) ) {




    if ( v )
      *p |= wm ;
    else {
      if ( wm & rfm )
 do { extern void __attribute__((error("flag bit can only be cleared by writing 1 into it."))) hwa_error_17(void); hwa_error_17(); } while(0);
      *p &= ~wm ;
    }
  }
  else {




    uint8_t rm = rwm & ~wm & ~rfm ;

    if ( rm == 0 )



      *p = v ;
    else {



      *p = (*p & rm) | (v & wm) ;
    }
  }
}





static inline __attribute__((always_inline)) void _hw_write_r16 ( intptr_t ra, uint16_t rwm, uint16_t rfm,
         uint8_t bn, uint8_t bp, uint16_t v )
{
  if ( ra == ~0 )
    do { extern void __attribute__((error("invalid access"))) hwa_error_18(void); hwa_error_18(); } while(0);

  if ( bn == 0 )
    do { extern void __attribute__((error("no bit to be changed?"))) hwa_error_19(void); hwa_error_19(); } while(0);



  uint16_t wm = (1U<<bn)-1 ;

  if (v > wm)
    do { extern void __attribute__((error("value too high for bits number"))) hwa_error_20(void); hwa_error_20(); } while(0);

  wm <<= bp ;
  v <<= bp ;



  if ( (v & wm & rwm) != (v & wm) )
    do { extern void __attribute__((error("bits not writeable."))) hwa_error_21(void); hwa_error_21(); } while(0);

  volatile uint16_t *p = (volatile uint16_t *)ra ;

  if ( ra < 0x40 &&
       (wm==0x0001 || wm==0x0002 || wm==0x0004 || wm==0x0008 ||
 wm==0x0010 || wm==0x0020 || wm==0x0040 || wm==0x0080 ||
 wm==0x0100 || wm==0x0200 || wm==0x0400 || wm==0x0800 ||
 wm==0x1000 || wm==0x2000 || wm==0x4000 || wm==0x8000) ) {




    if ( v )
      *p |= wm ;
    else {
      if ( wm & rfm )
 do { extern void __attribute__((error("flag bit can only be cleared by writing 1 into it."))) hwa_error_22(void); hwa_error_22(); } while(0);
      *p &= ~wm ;
    }
  }
  else {




    uint16_t rm = rwm & ~wm & ~rfm ;

    if ( rm == 0 )



      *p = v ;
    else {



      *p = (*p & rm) | (v & wm) ;
    }
  }
}
# 207 "/home/indy/dev/hwa-dev/hwa_atmelavr_2.h"
static inline __attribute__((always_inline)) void _hwa_commit_r8 ( hwa_r8_t *r, uint8_t rwm, uint8_t rfm, _Bool commit )
{
  if ( !commit ) {
    r->ovalue = (r->ovalue & r->omask & ~r->mmask) | (r->mvalue & r->mmask) ;
    r->omask |= r->mmask ;
    r->mmask = 0 ;
    return ;
  }

  volatile uint8_t *p = (volatile uint8_t *)r->a ;






  uint8_t wm = rwm & r->mmask & ((r->ovalue ^ r->mvalue) | ~r->omask);

  if ( wm ) {
    if ( (uintptr_t)p < 0x40 &&
  (wm==0x01 || wm==0x02 || wm==0x04 || wm==0x08 ||
   wm==0x10 || wm==0x20 || wm==0x40 || wm==0x80 ) ) {




      if ( wm & r->mvalue )
 *p |= wm ;
      else
 *p &= ~wm ;
      r->ovalue = (r->ovalue & ~wm) | (r->mvalue & wm) ;
      r->omask |= wm ;
      r->mmask = 0 ;
      return ;
    }







    uint8_t rm = ~r->mmask & ~rfm & ~r->omask & rwm ;



    if ( rm )
      r->ovalue = *p ;



    r->ovalue = ((r->ovalue & ~wm) | (r->mvalue & wm)) & ~rfm ;



    *p = r->ovalue | (rfm & r->mmask & r->mvalue) ;
  }

  r->omask |= r->mmask ;
  r->mmask = 0 ;
}


static inline __attribute__((always_inline)) void _hwa_commit_r16 ( hwa_r16_t *r, uint16_t rwm, uint16_t rfm, _Bool commit )
{
  if ( !commit ) {
    r->ovalue = (r->ovalue & r->omask & ~r->mmask) | (r->mvalue & r->mmask) ;
    r->omask |= r->mmask ;
    r->mmask = 0 ;
    return ;
  }

  volatile uint16_t *p = (volatile uint16_t *)r->a ;

  uint16_t wm = rwm & r->mmask & ((r->ovalue ^ r->mvalue) | ~r->omask);

  if ( wm ) {





    uint16_t rm = ~r->mmask & ~rfm & ~r->omask & rwm ;

    if ( rm )
      r->ovalue = *p ;

    r->ovalue = ((r->ovalue & ~wm) | (r->mvalue & wm)) & ~rfm ;

    *p = r->ovalue | (rfm & r->mmask & r->mvalue) ;
  }

  r->omask |= r->mmask ;
  r->mmask = 0 ;
}
# 312 "/home/indy/dev/hwa-dev/hwa_atmelavr_2.h"
static inline __attribute__((always_inline)) uint8_t _hw_read_r8 ( intptr_t ra, uint8_t rbn, uint8_t rbp )
{
  uint8_t m = (1U<<rbn)-1 ;
  volatile uint8_t *p = (volatile uint8_t *)ra ;
  return ((*p)>>rbp) & m ;
}

static inline __attribute__((always_inline)) uint16_t _hw_read_r16 ( intptr_t ra, uint8_t rbn, uint8_t rbp )
{
  uint16_t m = (1UL<<rbn)-1 ;
  volatile uint16_t *p = (volatile uint16_t *)ra ;
  return ((*p)>>rbp) & m ;
}
# 335 "/home/indy/dev/hwa-dev/hwa_atmelavr_2.h"
static inline __attribute__((always_inline)) uint16_t _hw_atomic_read_r16 ( intptr_t ra, uint8_t rbn, uint8_t rbp )
{
  volatile uint8_t *pl = (volatile uint8_t *)ra+0 ;
  volatile uint8_t *ph = (volatile uint8_t *)ra+1 ;
  uint16_t v ;
  uint16_t m = (1UL<<rbn)-1 ;

  if ( (m & 0xFF) && (m >> 8) ) {
    uint8_t s = _hw_read_r8(0 +0x5F,8,0);
    __asm__ __volatile__("cli");
    uint8_t lb = *pl ;
    _hw_write_r8(0 +0x5F,0xFF,0x00,8,0,s);
    uint8_t hb = *ph ;
    v = (hb << 8) | lb ;
  }
  else if ( m & 0xFF )
    v = *pl ;
  else
    v = (*ph)<<8 ;
  return (v>>rbp) & m ;
}
# 8 "/home/indy/dev/hwa-dev/hwa_attinyx4_2.h" 2
# 1 "/home/indy/dev/hwa-dev/hwa_atmelavr__corea_2.h" 1
# 29 "/home/indy/dev/hwa-dev/hwa_atmelavr__corea_2.h"
# 1 "/home/indy/dev/hwa-dev/hwa_atmelavr__core_2.h" 1
# 102 "/home/indy/dev/hwa-dev/hwa_atmelavr__core_2.h"
typedef union {
  uint8_t byte ;
  struct {
    unsigned int porf : 1 ;
    unsigned int extrf : 1 ;
    unsigned int borf : 1 ;
    unsigned int wdrf : 1 ;
    unsigned int __4to7 : 4 ;
  };
  struct {
    unsigned int reset_by_power_on : 1 ;
    unsigned int reset_by_reset_pin : 1 ;
    unsigned int reset_by_brown_out : 1 ;
    unsigned int reset_by_watchdog : 1 ;
    unsigned int __4to7_2 : 4 ;
  };
} _hw_core_stat_t ;
# 128 "/home/indy/dev/hwa-dev/hwa_atmelavr__core_2.h"
static inline __attribute__((always_inline)) _hw_core_stat_t _hw_core_stat( uint8_t byte )
{
  _hw_core_stat_t st ;
  st.byte = byte ;
  return st ;
}
# 30 "/home/indy/dev/hwa-dev/hwa_atmelavr__corea_2.h" 2
# 40 "/home/indy/dev/hwa-dev/hwa_atmelavr__corea_2.h"
static inline __attribute__((always_inline)) void __hwa_begin__corea ( hwa_corea_t *p, intptr_t a )
{
  _hwa_begin_r8(&((p)->gimsk),a+0x5B);
  _hwa_begin_r8(&((p)->gifr),a+0x5A);
  _hwa_begin_r8(&((p)->mcucr),a+0x55);
  _hwa_begin_r8(&((p)->mcusr),a+0x54);
  _hwa_begin_r8(&((p)->osccal),a+0x51);
  _hwa_begin_r8(&((p)->gpior2),a+0x35);
  _hwa_begin_r8(&((p)->gpior1),a+0x34);
  _hwa_begin_r8(&((p)->gpior0),a+0x33);
  _hwa_begin_r8(&((p)->prr),a+0x20);
}



static inline __attribute__((always_inline)) void __hwa_init__corea ( hwa_corea_t *p )
{
  _hwa_set_r8( &p->gimsk, 0x00 );
  _hwa_set_r8( &p->gifr, 0x00 );
  _hwa_set_r8( &p->mcucr, 0x00 );

  _hwa_set_r8( &p->osccal, 0x00 );
  _hwa_set_r8( &p->gpior2, 0x00 );
  _hwa_set_r8( &p->gpior1, 0x00 );
  _hwa_set_r8( &p->gpior0, 0x00 );
  _hwa_set_r8( &p->prr, 0x00 );
}


static inline __attribute__((always_inline)) void __hwa_commit__corea ( hwa_t *hwa, hwa_corea_t *p )
{
  _hwa_commit_r8(&((p)->gimsk),0x70,0x00,hwa->commit);
  _hwa_commit_r8(&((p)->gifr),0x70,0x70,hwa->commit);
  _hwa_commit_r8(&((p)->mcucr),0xFF,0x00,hwa->commit);
  _hwa_commit_r8(&((p)->mcusr),0x0F,0x00,hwa->commit);
  _hwa_commit_r8(&((p)->osccal),0xFF,0x00,hwa->commit);
  _hwa_commit_r8(&((p)->gpior2),0xFF,0x00,hwa->commit);
  _hwa_commit_r8(&((p)->gpior1),0xFF,0x00,hwa->commit);
  _hwa_commit_r8(&((p)->gpior0),0xFF,0x00,hwa->commit);
  _hwa_commit_r8(&((p)->prr),0x0F,0x00,hwa->commit);
}
# 9 "/home/indy/dev/hwa-dev/hwa_attinyx4_2.h" 2
# 1 "/home/indy/dev/hwa-dev/hwa_atmelavr__io_2.h" 1







static inline __attribute__((always_inline)) void __hwa_begin__io8a ( hwa_io8a_t *p, intptr_t a )
{
  _hwa_begin_r8(&((p)->port),a+0x02);
  _hwa_begin_r8(&((p)->ddr),a+0x01);
}


static inline __attribute__((always_inline)) void __hwa_init__io8a ( hwa_io8a_t *p )
{
  _hwa_set_r8( &p->port, 0x00 );
  _hwa_set_r8( &p->ddr, 0x00 );
}


static inline __attribute__((always_inline)) void __hwa_commit__io8a ( hwa_t *hwa, hwa_io8a_t *p )
{
  _hwa_commit_r8(&((p)->port),0xFF,0x00,hwa->commit);
  _hwa_commit_r8(&((p)->ddr),0xFF,0x00,hwa->commit);
}
# 10 "/home/indy/dev/hwa-dev/hwa_attinyx4_2.h" 2
# 1 "/home/indy/dev/hwa-dev/hwa_atmelavr__pcica_2.h" 1
# 12 "/home/indy/dev/hwa-dev/hwa_atmelavr__pcica_2.h"
static inline __attribute__((always_inline)) void __hwa_begin__pcica ( hwa_pcica_t *p, intptr_t address )
{
  _hwa_begin_r8(&((p)->msk0),address+0x00);
  _hwa_begin_r8(&((p)->msk1),address+0x00);

}


static inline __attribute__((always_inline)) void __hwa_init__pcica ( hwa_pcica_t *p )
{
  _hwa_set_r8( &p->msk0, 0x00 );
  _hwa_set_r8( &p->msk1, 0x00 );

}


static inline __attribute__((always_inline)) void __hwa_commit__pcica ( hwa_t *hwa, hwa_pcica_t *p )
{
  _hwa_commit_r8(&((p)->msk0),0xFF,0x00,hwa->commit);
  _hwa_commit_r8(&((p)->msk1),0x0F,0x00,hwa->commit);

}
# 11 "/home/indy/dev/hwa-dev/hwa_attinyx4_2.h" 2
# 1 "/home/indy/dev/hwa-dev/hwa_atmelavr__wdoga_2.h" 1
# 12 "/home/indy/dev/hwa-dev/hwa_atmelavr__wdoga_2.h"
# 1 "/home/indy/dev/hwa-dev/hwa_atmelavr__wdog_2.h" 1
# 154 "/home/indy/dev/hwa-dev/hwa_atmelavr__wdog_2.h"
typedef union {
  uint8_t byte ;
  struct {
    unsigned int __0to6a : 7 ;
    unsigned int irq : 1 ;
  };
} _hw_wdog_stat_t ;






static inline __attribute__((always_inline)) _hw_wdog_stat_t _hw_wdog_stat( uint8_t byte )
{
  _hw_wdog_stat_t st ;
  st.byte = byte ;
  return st ;
}
# 13 "/home/indy/dev/hwa-dev/hwa_atmelavr__wdoga_2.h" 2
# 27 "/home/indy/dev/hwa-dev/hwa_atmelavr__wdoga_2.h"
static inline __attribute__((always_inline)) void __hwa_begin__wdoga ( hwa_wdog_t *p, intptr_t address )
{
  p->action = 0xFF ;
  p->timeout = 0xFF ;
  _hwa_begin_r8(&((p)->csr),address+0x41);
}


static inline __attribute__((always_inline)) void __hwa_init__wdoga ( hwa_wdog_t *p )
{
  _hwa_set_r8( &p->csr, 0x00 );
}


static inline __attribute__((always_inline)) void __hwa_commit__wdoga ( hwa_t *hwa, hwa_wdog_t *p )
{
  if ( p->action != 0xFF ) {
    if ( p->action == 0 ) {
# 55 "/home/indy/dev/hwa-dev/hwa_atmelavr__wdoga_2.h"
      _hwa_write_r8( &hwa->hw_core0.mcusr, 0x0F,0x00, 1,3,0);
      _hwa_commit_r8(&hwa->hw_core0.mcusr,0x0F,0x00,hwa->commit);


      _hwa_write_r8( &((p)->csr), 0xFF,0x80, 1,4,1);
      _hwa_write_r8( &((p)->csr), 0xFF,0x80, 1,3,1);
      _hwa_commit_r8(&((p)->csr),0xFF,0x80,hwa->commit);
      _hwa_write_r8( &((p)->csr), 0xFF,0x80, 1,6,0);
      _hwa_write_r8( &((p)->csr), 0xFF,0x80, 1,4,0);
      _hwa_write_r8( &((p)->csr), 0xFF,0x80, 1,3,0);
      do { _hwa_write_r8(&((p)->csr), 0xFF,0x80, 1,5, ((0)>>(3))&((1U<<1)-1)); _hwa_write_r8(&((p)->csr), 0xFF,0x80, 3,0, ((0)>>(0))&((1U<<3)-1)); } while(0);
    }
    else {



      do { _hwa_write_r8(&((p)->csr), 0xFF,0x80, 1,3, ((p->action)>>(1))&((1U<<1)-1)); _hwa_write_r8(&((p)->csr), 0xFF,0x80, 1,6, ((p->action)>>(0))&((1U<<1)-1)); } while(0);
      if ( p->timeout != 0xFF )
 do { _hwa_write_r8(&((p)->csr), 0xFF,0x80, 1,5, ((p->timeout)>>(3))&((1U<<1)-1)); _hwa_write_r8(&((p)->csr), 0xFF,0x80, 3,0, ((p->timeout)>>(0))&((1U<<3)-1)); } while(0);
    }
    p->action = 0xFF ;
    p->timeout = 0xFF ;
  }
  _hwa_commit_r8(&((p)->csr),0xFF,0x80,hwa->commit);
}
# 12 "/home/indy/dev/hwa-dev/hwa_attinyx4_2.h" 2
# 1 "/home/indy/dev/hwa-dev/hwa_atmelavr__c8a_2.h" 1
# 11 "/home/indy/dev/hwa-dev/hwa_atmelavr__c8a_2.h"
# 1 "/home/indy/dev/hwa-dev/hwa_atmelavr__counters.h" 1
# 12 "/home/indy/dev/hwa-dev/hwa_atmelavr__c8a_2.h" 2
# 1 "/home/indy/dev/hwa-dev/hwa_atmelavr__ocua_2.h" 1
# 13 "/home/indy/dev/hwa-dev/hwa_atmelavr__c8a_2.h" 2


static inline __attribute__((always_inline)) void __hwa_begin__c8a ( hwa_c8a_t *p, intptr_t a )
{
  _hwa_begin_r8(&((p)->ccra),a+0x50);
  _hwa_begin_r8(&((p)->ccrb),a+0x53);
  _hwa_begin_r8(&((p)->count),a+0x52);
  _hwa_begin_r8(&((p)->ocra),a+0x56);
  _hwa_begin_r8(&((p)->ocrb),a+0x5C);

  _hwa_begin_r8(&((p)->imsk),a+0x59);
  _hwa_begin_r8(&((p)->ifr),a+0x58);


  p->clock = 0xFF ;
  p->countmode = 0xFF ;
  p->top = 0xFF ;
  p->overflow = 0xFF ;
  p->compare0_update = 0xFF ;
  p->compare0_output = 0xFF ;
  p->compare1_update = 0xFF ;
  p->compare1_output = 0xFF ;





}


static inline __attribute__((always_inline)) void __hwa_init__c8a ( hwa_c8a_t *p )
{
  _hwa_set_r8( &p->ccra, 0x00 );
  _hwa_set_r8( &p->ccrb, 0x00 );
  _hwa_set_r8( &p->count, 0x00 );
  _hwa_set_r8( &p->ocra, 0x00 );
  _hwa_set_r8( &p->ocrb, 0x00 );

  _hwa_set_r8( &p->imsk, 0x00 );
  _hwa_set_r8( &p->ifr, 0x00 );

}


static inline __attribute__((always_inline)) void __hwa_commit__c8a ( hwa_t *hwa, hwa_c8a_t *p )
{
  _hwa_commit_r8(&((p)->ccra),0xF3,0x00,hwa->commit);
  _hwa_commit_r8(&((p)->ccrb),0xCF,0x00,hwa->commit);
  _hwa_commit_r8(&((p)->count),0xFF,0x00,hwa->commit);
  _hwa_commit_r8(&((p)->ocra),0xFF,0x00,hwa->commit);
  _hwa_commit_r8(&((p)->ocrb),0xFF,0x00,hwa->commit);

  _hwa_commit_r8(&((p)->imsk),0x07,0x00,hwa->commit);
  _hwa_commit_r8(&((p)->ifr),0x07,0x07,hwa->commit);

}
# 211 "/home/indy/dev/hwa-dev/hwa_atmelavr__c8a_2.h"
static inline __attribute__((always_inline)) void __hwa_solve__c8a ( hwa_t *hwa __attribute__((unused)), hwa_c8a_t *p )
{
  if ( p->clock == 0xFF )
    return ;




  _hwa_write_r8( &((p)->ccrb), 0xCF,0x00, 3,0,p->clock);





  uint8_t overflow = p->overflow ;
  if ( overflow == 0xFF && p->top == 2 ) {
    if ( p->countmode == 1 )
      overflow = 1;
    else
      overflow = 0;
  }




  uint8_t compare_update = 0xFF ;
  if ( p->compare0_update != 0xFF && p->compare1_update != 0xFF
       && p->compare0_update != p->compare1_update )
    do { extern void __attribute__((error("optionnal parameter 'update' of class _c16a counter must be " "'immediately'."))) hwa_error_23(void); hwa_error_23(); } while(0)
                      ;
  compare_update = p->compare0_update ;
# 261 "/home/indy/dev/hwa-dev/hwa_atmelavr__c8a_2.h"
  uint8_t wgm = 0xFF ;
  if ( p->countmode == 1 ) {
    if ( p->top == 1 ) {
      if ( compare_update == 1
    || p->compare0_output == 5
    || p->compare0_output == 4
    || p->compare1_output == 5
    || p->compare1_output == 4)
 wgm = 3 ;
      else
 wgm = 0 ;
    }
    else {






      if ( compare_update == 1
    || overflow == 1
    || p->compare0_output == 5
    || p->compare0_output == 4
    || p->compare1_output == 5
    || p->compare1_output == 4)
 wgm = 7 ;
      else
 wgm = 2 ;
    }
  }
  else {
    if ( p->top == 1 )
      wgm = 1 ;
    else
      wgm = 5 ;
  }

  if (wgm == 0xFF) {
    do { extern void __attribute__((error("WGM value could not be solved for _c8a class counter."))) hwa_error_24(void); hwa_error_24(); } while(0);
    return ;
  }

  do { _hwa_write_r8(&((p)->ccra), 0xF3,0x00, 2,0, ((wgm)>>(0))&((1U<<2)-1)); _hwa_write_r8(&((p)->ccrb), 0xCF,0x00, 1,3, ((wgm)>>(2))&((1U<<1)-1)); } while(0);





  if ( p->compare0_output != 0xFF ) {

    uint8_t mode = 0xFF ;

    if ( p->compare0_output == 0 )
      mode = 0 ;
    else if ( p->compare0_output == 1 )
      mode = 1 ;
    else if ( p->compare0_output == 2
       || p->compare0_output == 4
       || p->compare0_output == 6 )
      mode = 2 ;
    else
      mode = 3 ;

    _hwa_write_r8( &((p)->ccra), 0xF3,0x00, 2,6,mode);

  }




  if ( p->compare1_output != 0xFF ) {

    uint8_t mode = 0xFF ;

    if ( p->compare1_output == 0 )
      mode = 0 ;
    else if ( p->compare1_output == 1 )
      mode = 1 ;
    else if ( p->compare1_output == 2
       || p->compare1_output == 4
       || p->compare1_output == 6 )
      mode = 2 ;
    else
      mode = 3 ;

    _hwa_write_r8( &((p)->ccra), 0xF3,0x00, 2,4,mode);

  }




  if ( p->clock != 0xFF || p->compare0_output != 0xFF || p->compare1_output != 0xFF ) {

    if ( p->clock == 0xFF ) {
      do { extern void __attribute__((error("configuration of counter is required."))) hwa_error_25(void); hwa_error_25(); } while(0);
      return ;
    }



    if ( p->compare0_output != 0xFF ) {
      if ( wgm==0 || wgm==2 ) {
 if ( p->compare0_output != 0
      && p->compare0_output != 1
      && p->compare0_output != 2
      && p->compare0_output != 3)
   do { extern void __attribute__((error("compare output A of class _c8a counter mode must be " "'disconnected', 'toggle_on_match', 'clear_on_match', or " "'set_on_match'."))) hwa_error_26(void); hwa_error_26(); } while(0)

                      ;
      }
      else if ( wgm==3 ) {
 if ( p->compare0_output != 0
      && p->compare0_output != 4
      && p->compare0_output != 5 )
   do { extern void __attribute__((error("compare output A of class _c8a counter mode must be " "'disconnected', 'set_at_bottom_clear_on_match', or " "'clear_at_bottom_set_on_match'."))) hwa_error_27(void); hwa_error_27(); } while(0)

                                      ;
      }
      else if ( wgm==7 ) {
 if ( p->compare0_output != 0
      && p->compare0_output != 1
      && p->compare0_output != 4
      && p->compare0_output != 5 )
   do { extern void __attribute__((error("compare output A of class _c8a counter mode must be " "'disconnected', 'toggle_on_match', " "'set_at_bottom_clear_on_match', or " "'clear_at_bottom_set_on_match'."))) hwa_error_28(void); hwa_error_28(); } while(0)


                                      ;
      }
      else if ( wgm==1 ) {
 if ( p->compare0_output != 0
      && p->compare0_output != 6
      && p->compare0_output != 7 )
   do { extern void __attribute__((error("compare output A of class _c8a counter mode must be " "'disconnected', 'clear_on_match_up_set_on_match_down', " "or 'set_on_match_up_clear_on_match_down'."))) hwa_error_29(void); hwa_error_29(); } while(0)

                                                ;
      }
      else if ( wgm==5 ) {
 if ( p->compare0_output != 0
      && p->compare0_output != 1
      && p->compare0_output != 6
      && p->compare0_output != 7 )
   do { extern void __attribute__((error("compare output A of class _c8a counter mode must be " "'disconnected', 'toggle_on_match', " "'clear_on_match_up_set_on_match_down', " "or 'set_on_match_up_clear_on_match_down'."))) hwa_error_30(void); hwa_error_30(); } while(0)


                                                ;
      }
    }



    if ( p->compare1_output != 0xFF ) {
      if ( wgm==0 || wgm==2 ) {
 if ( p->compare1_output != 0
      && p->compare1_output != 1
      && p->compare1_output != 2
      && p->compare1_output != 3)
   do { extern void __attribute__((error("compare output B of class _c8a counter mode must be " "'disconnected', 'toggle_on_match', 'clear_on_match', or " "'set_on_match'."))) hwa_error_31(void); hwa_error_31(); } while(0)

                      ;
      }
      else if ( wgm==3 || wgm==7 ) {
 if ( p->compare1_output != 0
      && p->compare1_output != 4
      && p->compare1_output != 5 )
   do { extern void __attribute__((error("compare output B of class _c8a counter mode must be " "'disconnected', 'set_at_bottom_clear_on_match', or " "'clear_at_bottom_set_on_match'."))) hwa_error_32(void); hwa_error_32(); } while(0)

                                      ;
      }
      else if ( wgm==1 || wgm==5 ) {
 if ( p->compare1_output != 0
      && p->compare1_output != 6
      && p->compare1_output != 7 )
   do { extern void __attribute__((error("compare output B of class _c8a counter mode must be " "'disconnected', 'clear_on_match_up_set_on_match_down', " "or 'set_on_match_up_clear_on_match_down'."))) hwa_error_33(void); hwa_error_33(); } while(0)

                                                ;
      }
    }



    if ( compare_update != 0xFF ) {
      if ( wgm==0 || wgm==2 ) {
 if ( compare_update != 0 )
   do { extern void __attribute__((error("optionnal parameter 'update' of class _c8a counter must be " "'immediately'."))) hwa_error_34(void); hwa_error_34(); } while(0)
                     ;
      }
      else if ( wgm==3 || wgm==7 ) {
 if ( compare_update != 1 )
   do { extern void __attribute__((error("optionnal parameter 'update' of class _c8a counter must be " "'at_bottom'."))) hwa_error_35(void); hwa_error_35(); } while(0)
                   ;
      }
      else
 if( compare_update != 2 )
   do { extern void __attribute__((error("optionnal parameter 'update' of class _c8a counter must be " "'at_top'."))) hwa_error_36(void); hwa_error_36(); } while(0)
                ;
    }



    if ( overflow != 0xFF ) {
      if ( wgm==7 ) {
 if ( overflow != 1 )
   do { extern void __attribute__((error("optionnal parameter 'overflow' of class _c8a counter must be " "'at_top'."))) hwa_error_37(void); hwa_error_37(); } while(0)
                ;
      }
      else if ( (wgm==1 || wgm==5) ) {
 if ( overflow != 0 )
   do { extern void __attribute__((error("optionnal parameter 'overflow' of class _c8a counter must be " "'at_bottom'."))) hwa_error_38(void); hwa_error_38(); } while(0)
                   ;
      }
      else if ( overflow != 2 )
 do { extern void __attribute__((error("optionnal parameter 'overflow' of class _c8a counter must be " "'at_max'."))) hwa_error_39(void); hwa_error_39(); } while(0)
              ;
    }
  }
}
# 512 "/home/indy/dev/hwa-dev/hwa_atmelavr__c8a_2.h"
  typedef union {
    uint8_t byte ;
    struct {
      unsigned int overflow : 1 ;
      unsigned int compare0 : 1 ;
      unsigned int compare1 : 1 ;
      unsigned int __3to7 : 5 ;
    };
  } _hw_c8a_stat_t ;



static inline __attribute__((always_inline)) _hw_c8a_stat_t _hw_c8a_stat( uint8_t byte )
{
  _hw_c8a_stat_t st ;
  st.byte = byte ;
  return st ;
}
# 13 "/home/indy/dev/hwa-dev/hwa_attinyx4_2.h" 2
# 1 "/home/indy/dev/hwa-dev/hwa_atmelavr__c16a_2.h" 1
# 13 "/home/indy/dev/hwa-dev/hwa_atmelavr__c16a_2.h"
static inline __attribute__((always_inline)) void __hwa_begin__c16a ( hwa_c16a_t *p, intptr_t a )
{
  _hwa_begin_r8(&((p)->ccra),a+0x4F);
  _hwa_begin_r8(&((p)->ccrb),a+0x4E);
  _hwa_begin_r8(&((p)->ccrc),a+0x42);
  _hwa_begin_r16(&((p)->count),a+0x4C);
  _hwa_begin_r16(&((p)->icr),a+0x44);
  _hwa_begin_r16(&((p)->ocra),a+0x4A);
  _hwa_begin_r16(&((p)->ocrb),a+0x48);
  _hwa_begin_r8(&((p)->imsk),a+0x2C);
  _hwa_begin_r8(&((p)->ifr),a+0x2B);

  p->clock = 0xFF ;
  p->countmode = 0xFF ;
  p->top = 0xFF ;
  p->overflow = 0xFF ;
  p->compare0_update = 0xFF ;
  p->compare0_output = 0xFF ;
  p->compare1_update = 0xFF ;
  p->compare1_output = 0xFF ;
  p->icr_input = 0xFF ;
  p->icr_edge = 0xFF ;
  p->icr_filter = 0xFF ;
}


static inline __attribute__((always_inline)) void __hwa_init__c16a ( hwa_c16a_t *p )
{
  _hwa_set_r8( &p->ccra, 0x00 );
  _hwa_set_r8( &p->ccrb, 0x00 );
  _hwa_set_r8( &p->ccrc, 0x00 );
  _hwa_set_r16( &p->count, 0x00 );
  _hwa_set_r16( &p->icr, 0x00 );
  _hwa_set_r16( &p->ocra, 0x00 );
  _hwa_set_r16( &p->ocrb, 0x00 );
  _hwa_set_r8( &p->imsk, 0x00 );
  _hwa_set_r8( &p->ifr, 0x00 );
}


static inline __attribute__((always_inline)) void __hwa_commit__c16a ( hwa_t *hwa, hwa_c16a_t *p )
{
  _hwa_commit_r8(&((p)->ccra),0xF3,0x00,hwa->commit);
  _hwa_commit_r8(&((p)->ccrb),0xDF,0x00,hwa->commit);
  _hwa_commit_r8(&((p)->ccrc),0xC0,0x00,hwa->commit);
  _hwa_commit_r16(&((p)->count),0xFFFF,0x0000,hwa->commit);
  _hwa_commit_r16(&((p)->icr),0xFFFF,0x0000,hwa->commit);
  _hwa_commit_r16(&((p)->ocra),0xFFFF,0x0000,hwa->commit);
  _hwa_commit_r16(&((p)->ocrb),0xFFFF,0x0000,hwa->commit);
  _hwa_commit_r8(&((p)->imsk),0x27,0x00,hwa->commit);
  _hwa_commit_r8(&((p)->ifr),0x27,0x27,hwa->commit);
}
# 169 "/home/indy/dev/hwa-dev/hwa_atmelavr__c16a_2.h"
static inline __attribute__((always_inline)) void __hwa_solve__c16a ( hwa_t *hwa __attribute__((unused)), hwa_c16a_t *p )
{
  if ( p->clock == 0xFF )
    return ;



  _hwa_write_r8( &((p)->ccrb), 0xDF,0x00, 3,0,p->clock);




  uint8_t overflow = p->overflow ;
  if ( overflow == 0xFF && p->top == 6 ) {
    if ( p->countmode == 1 )
      overflow = 1;
    else
      overflow = 0;
  }



  uint8_t compare_update = 0xFF ;
  if ( p->compare0_update != 0xFF && p->compare1_update != 0xFF
       && p->compare0_update != p->compare1_update )
    do { extern void __attribute__((error("optionnal parameter 'update' of class _c16a counter must be " "'immediately'."))) hwa_error_40(void); hwa_error_40(); } while(0)
                      ;
  compare_update = p->compare0_update ;
# 226 "/home/indy/dev/hwa-dev/hwa_atmelavr__c16a_2.h"
  uint8_t wgm = 0xFF ;
  if ( p->countmode == 1
       && p->top == 6
       && overflow == 1 )
    wgm = 15 ;
  else
    if ( p->countmode == 1 ) {
      if ( p->top == 4 )
 wgm = 0 ;
      else if (p->top == 1 )
 wgm = 5 ;
      else if (p->top == 2 )
 wgm = 6 ;
      else if (p->top == 3 )
 wgm = 7 ;
      else if (p->top == 6 ) {
 if ( compare_update == 0
      || overflow == 1
      || p->compare1_output == 4
      || p->compare1_output == 5)
   wgm = 15 ;
 else
   wgm = 4 ;
      }
      else {
 if (compare_update == 2
     || overflow == 1
     || p->compare0_output == 1
     || p->compare0_output == 4
     || p->compare0_output == 5
     || p->compare1_output == 4
     || p->compare1_output == 5)
   wgm = 14 ;
 else
   wgm = 12 ;
      }
    }
    else {
      if (p->top == 1 )
 wgm = 1 ;
      else if (p->top == 2 )
 wgm = 2 ;
      else if (p->top == 3 )
 wgm = 3 ;
      else if (p->top == 6 ) {
 if (compare_update == 1
     || p->compare1_output == 6
     || p->compare1_output == 7)
   wgm = 9 ;
 else
   wgm = 11 ;
      }
      else {
 if (compare_update == 1
     || p->compare0_output == 1
     || p->compare0_output == 6
     || p->compare0_output == 7
     || p->compare1_output == 6
     || p->compare1_output == 7)
   wgm = 8 ;
 else
   wgm = 10 ;
      }
    }

  if (wgm != 0xFF)
    do { _hwa_write_r8(&((p)->ccrb), 0xDF,0x00, 2,3, ((wgm)>>(2))&((1U<<2)-1)); _hwa_write_r8(&((p)->ccra), 0xF3,0x00, 2,0, ((wgm)>>(0))&((1U<<2)-1)); } while(0);
  else {
    do { extern void __attribute__((error("WGM value could not be solved for _c16a class counter."))) hwa_error_41(void); hwa_error_41(); } while(0);
    return ;
  }



  if ( p->compare0_output != 0xFF ) {

    uint8_t mode = 0xFF ;

    if ( p->compare0_output == 0 )
      mode = 0 ;
    else if ( p->compare0_output == 1 )
      mode = 1 ;
    else if ( p->compare0_output == 2
       || p->compare0_output == 4
       || p->compare0_output == 6 )
      mode = 2 ;
    else
      mode = 3 ;

    _hwa_write_r8( &((p)->ccra), 0xF3,0x00, 2,6,mode);
  }



  if ( p->compare1_output != 0xFF ) {

    uint8_t mode = 0xFF ;

    if ( p->compare1_output == 0 )
      mode = 0 ;
    else if ( p->compare1_output == 1 )
      mode = 1 ;
    else if ( p->compare1_output == 2
       || p->compare1_output == 4
       || p->compare1_output == 6 )
      mode = 2 ;
    else
      mode = 3 ;

    _hwa_write_r8( &((p)->ccra), 0xF3,0x00, 2,4,mode);
  }



  if ( p->icr_input != 0xFF ) {
    _hwa_write_r8( &hwa->hw_acmp0.csr, 0xDF,0x10, 1,2,p->icr_input-1);
    _hwa_write_r8( &((p)->ccrb), 0xDF,0x00, 1,6,p->icr_edge-1);
    _hwa_write_r8( &((p)->ccrb), 0xDF,0x00, 1,7,p->icr_filter);
  }




  if ( p->countmode != 0xFF || p->compare0_output != 0xFF || p->compare1_output != 0xFF ) {

    if ( p->countmode == 0xFF ) {
      do { extern void __attribute__((error("configuration of counter is required."))) hwa_error_42(void); hwa_error_42(); } while(0);
      return ;
    }



    if ( p->compare0_output != 0xFF ) {
      if ( wgm==0 || wgm==12 ) {
 if ( p->compare0_output != 0
      && p->compare0_output != 2
      && p->compare0_output != 3
      && p->compare0_output != 1 )
   do { extern void __attribute__((error("compare output A of class _c16a counter mode must be " "'disconnected', 'clear_on_match', 'set_on_match', or " "'toggle_on_match'."))) hwa_error_43(void); hwa_error_43(); } while(0)

                         ;
      }
      else if ( wgm==5 || wgm==6 || wgm==7 ) {
 if ( p->compare0_output != 0
      && p->compare0_output != 4
      && p->compare0_output != 5 )
   do { extern void __attribute__((error("compare output A of class _c16a counter mode must be " "'disconnected', 'set_at_bottom_clear_on_match', or " "'clear_at_bottom_set_on_match'."))) hwa_error_44(void); hwa_error_44(); } while(0)

                                      ;
      }
      else if ( wgm==14 ) {
 if ( p->compare0_output != 0
      && p->compare0_output != 1
      && p->compare0_output != 4
      && p->compare0_output != 5 )
   do { extern void __attribute__((error("compare output A of class _c16a counter mode must be " "'disconnected', 'toggle_on_match', " "'set_at_bottom_clear_on_match', or " "'clear_at_bottom_set_on_match'."))) hwa_error_45(void); hwa_error_45(); } while(0)


                                      ;
      }
      else if ( wgm==1 || wgm==2 || wgm==3 ) {
 if ( p->compare0_output != 0
      && p->compare0_output != 6
      && p->compare0_output != 7 )
   do { extern void __attribute__((error("compare output A of class _c16a counter mode must be " "'disconnected', 'clear_on_match_up_set_on_match_down', " "or 'set_on_match_up_clear_on_match_down'."))) hwa_error_46(void); hwa_error_46(); } while(0)

                                                ;
      }
      else if ( wgm==8 || wgm==10 ) {
 if ( p->compare0_output != 0
      && p->compare0_output != 1
      && p->compare0_output != 6
      && p->compare0_output != 7 )
   do { extern void __attribute__((error("compare output A of class _c16a counter mode must be " "'disconnected', 'toggle_on_match', " "'clear_on_match_up_set_on_match_down', " "or 'set_on_match_up_clear_on_match_down'."))) hwa_error_47(void); hwa_error_47(); } while(0)


                                                ;
      }

      else if ( p->compare0_output ) {
 do { extern void __attribute__((error("can not use of `compare_a` as both top value and output of class _c16a counter."))) hwa_error_48(void); hwa_error_48(); } while(0);
      }
    }



    if ( p->compare1_output != 0xFF ) {
      if ( wgm==0 || wgm==4 || wgm==12 ) {
 if ( p->compare1_output != 0
      && p->compare1_output != 2
      && p->compare1_output != 3
      && p->compare1_output != 1 )
   do { extern void __attribute__((error("compare output B of class _c16a counter mode must be " "'disconnected', 'clear_on_match', 'set_on_match', or " "'toggle_on_match'."))) hwa_error_49(void); hwa_error_49(); } while(0)

                         ;
      }
      else if ( wgm==5 || wgm==6 || wgm==7 || wgm==14 || wgm==15 ) {
 if ( p->compare1_output != 0
      && p->compare1_output != 4
      && p->compare1_output != 5 )
   do { extern void __attribute__((error("compare output B of class _c16a counter mode must be " "'disconnected', 'set_at_bottom_clear_on_match', or " "'clear_at_bottom_set_on_match'."))) hwa_error_50(void); hwa_error_50(); } while(0)

                                      ;
      }
      else {
 if ( p->compare1_output != 0
      && p->compare1_output != 6
      && p->compare1_output != 7 )
   do { extern void __attribute__((error("compare output B of class _c16a counter mode must be " "'disconnected', 'clear_on_match_up_set_on_match_down', " "or 'set_on_match_up_clear_on_match_down'."))) hwa_error_51(void); hwa_error_51(); } while(0)

                                                ;
      }
    }



    if ( compare_update != 0xFF ) {
      if ( wgm==0 || wgm==4 || wgm==12 ) {
 if ( compare_update != 0 )
   do { extern void __attribute__((error("optionnal parameter 'update' of class _c16a counter must be " "'immediately'."))) hwa_error_52(void); hwa_error_52(); } while(0)
                     ;
      }
      else if ( wgm==8 || wgm==9 ) {
 if ( compare_update != 1 )
   do { extern void __attribute__((error("optionnal parameter 'update' of class _c16a counter must be " "'at_bottom'."))) hwa_error_53(void); hwa_error_53(); } while(0)
                   ;
      }
      else
 if( compare_update != 2 )
   do { extern void __attribute__((error("optionnal parameter 'update' of class _c16a counter must be " "'at_top'."))) hwa_error_54(void); hwa_error_54(); } while(0)
                ;
    }



    if ( overflow != 0xFF ) {
      if ( (wgm==0 || wgm==4 || wgm==12) ) {
 if ( overflow != 2 )
   do { extern void __attribute__((error("optionnal parameter 'overflow' of class _c8a counter must be " "'at_max'."))) hwa_error_55(void); hwa_error_55(); } while(0)
                ;
      }
      else if ( (wgm==5 || wgm==6 || wgm==7 || wgm==14 || wgm==15) ) {
 if ( overflow != 1 )
   do { extern void __attribute__((error("optionnal parameter 'overflow' of class _c8a counter must be " "'at_top'."))) hwa_error_56(void); hwa_error_56(); } while(0)
                ;
      }
      else if ( overflow != 0 )
 do { extern void __attribute__((error("optionnal parameter 'overflow' of class _c8a counter must be " "'at_bottom'."))) hwa_error_57(void); hwa_error_57(); } while(0)
                 ;
    }
  }
}
# 510 "/home/indy/dev/hwa-dev/hwa_atmelavr__c16a_2.h"
typedef union {
  uint8_t byte ;
  struct {
    unsigned int overflow : 1 ;
    unsigned int compare0 : 1 ;
    unsigned int compare1 : 1 ;
    unsigned int _34 : 2 ;
    unsigned int capture0 : 1 ;
    unsigned int _76 : 2 ;
  };
} _hw_c16a_stat_t ;



static inline __attribute__((always_inline)) _hw_c16a_stat_t _hw_c16a_stat( uint8_t byte )
{
  _hw_c16a_stat_t st ;
  st.byte = byte ;
  return st ;
}
# 14 "/home/indy/dev/hwa-dev/hwa_attinyx4_2.h" 2

# 1 "/home/indy/dev/hwa-dev/hwa_atmelavr__ad10a_2.h" 1







static inline __attribute__((always_inline)) void __hwa_begin__ad10a ( hwa_ad10a_t *p, intptr_t a )
{
  _hwa_begin_r8(&((p)->admux),a+0x27);
  _hwa_begin_r8(&((p)->sra),a+0x26);
  _hwa_begin_r8(&((p)->srb),a+0x23);
  _hwa_begin_r8(&((p)->did),a+0x21);
}


static inline __attribute__((always_inline)) void __hwa_init__ad10a ( hwa_ad10a_t *p )
{
  _hwa_set_r8( &p->admux, 0x00 );
  _hwa_set_r8( &p->sra, 0x00 );
  _hwa_set_r8( &p->srb, 0x00 );
  _hwa_set_r8( &p->did, 0x00 );
}


static inline __attribute__((always_inline)) void __hwa_commit__ad10a ( hwa_t *hwa, hwa_ad10a_t *p )
{
  _hwa_commit_r8(&((p)->admux),0xFF,0x00,hwa->commit);
  _hwa_commit_r8(&((p)->sra),0xFF,0x10,hwa->commit);
  _hwa_commit_r8(&((p)->srb),0xD7,0x00,hwa->commit);
  _hwa_commit_r8(&((p)->did),0xFF,0x00,hwa->commit);
}
# 282 "/home/indy/dev/hwa-dev/hwa_atmelavr__ad10a_2.h"
static inline __attribute__((always_inline)) uint8_t _hwa_ad10a_compute_mux ( uint8_t pos, uint8_t neg, uint8_t gain )
{
  if ( pos==0 ) {
    if ( neg==0 ) {
      if ( gain != 20 )
 do { extern void __attribute__((error("parameter `gain` must be set to 20 when pin_adc0 is used for both inputs."))) hwa_error_58(void); hwa_error_58(); } while(0);
      else
 return 0x23 ;
    }
    else if ( neg==1 )
      return 0x08 + (gain==20);
    else if ( neg==3 )
      return 0x0A + (gain==20);
    do { extern void __attribute__((error("`negative_input` must be `pin_adc0`, `pin_adc1`, or `pin_adc3`."))) hwa_error_59(void); hwa_error_59(); } while(0);
  }
  else if ( pos==1 ) {
    if ( neg==0 )
      return 0x28 + (gain==20);
    else if ( neg==2 )
      return 0x0C + (gain==20);
    else if ( neg==3 )
      return 0x0E + (gain==20);
    do { extern void __attribute__((error("`negative_input` must be `pin_adc0`, `pin_adc2`, or `pin_adc3`."))) hwa_error_60(void); hwa_error_60(); } while(0);
  }
  else if ( pos==2 ) {
    if ( neg==1 )
      return 0x2C + (gain==20);
    else if ( neg==3 )
      return 0x10 + (gain==20);
    do { extern void __attribute__((error("`negative_input` must be `pin_adc1` or `pin_adc3`."))) hwa_error_61(void); hwa_error_61(); } while(0);
  }
  else if ( pos==3 ) {
    const uint8_t v[8] = { 0x2A, 0x2E, 0x30, 0x24, 0x12, 0x14, 0x16, 0x18 };
    return v[neg] + (gain==20);
  }
  else if ( pos==4 ) {
    if ( neg==3 )
      return 0x32 + (gain==20);
    else if ( neg==5 )
      return 0x1A + (gain==20);
    do { extern void __attribute__((error("`negative_input` must be `pin_adc3` or `pin_adc5`."))) hwa_error_62(void); hwa_error_62(); } while(0);
  }
  else if ( pos==5 ) {
    if ( neg==3 )
      return 0x34 + (gain==20);
    else if ( neg==4 )
      return 0x3A + (gain==20);
    else if ( neg==6 )
      return 0x1C + (gain==20);
    do { extern void __attribute__((error("`negative_input` must be `pin_adc3`, `pin_adc4`, or `pin_adc6`."))) hwa_error_63(void); hwa_error_63(); } while(0);
  }
  else if ( pos==6 ) {
    if ( neg==3 )
      return 0x36 + (gain==20);
    else if ( neg==5 )
      return 0x3C + (gain==20);
    else if ( neg==7 )
      return 0x1E + (gain==20);
    do { extern void __attribute__((error("`negative_input` must be `pin_adc3`, `pin_adc5`, or `pin_adc7`."))) hwa_error_64(void); hwa_error_64(); } while(0);
  }
  else if ( pos==7 ) {
    if ( neg==3 )
      return 0x38 + (gain==20);
    else if ( neg==6 )
      return 0x3E + (gain==20);
    else if ( neg==7 )
      return 0x16 + (gain==20);
    do { extern void __attribute__((error("`negative_input` must be `pin_adc3`, `pin_adc6`, or `pin_adc7`."))) hwa_error_65(void); hwa_error_65(); } while(0);
  }
  else
    do { extern void __attribute__((error("`positive_input` must be between 0 and 7."))) hwa_error_66(void); hwa_error_66(); } while(0);
  return 0;
}




typedef union {
  uint8_t byte ;
  struct {
    unsigned int __0to3 : 4 ;
    unsigned int interrupt : 1 ;
    unsigned int __5 : 1 ;
    unsigned int busy : 1 ;
    unsigned int __7 : 1 ;
  };
} _hw_ad10a_status_t ;





static inline __attribute__((always_inline)) _hw_ad10a_status_t _hw_ad10a_status( uint8_t byte )
{
  _hw_ad10a_status_t st ;
  st.byte = byte ;
  return st ;
}
# 16 "/home/indy/dev/hwa-dev/hwa_attinyx4_2.h" 2
# 1 "/home/indy/dev/hwa-dev/hwa_atmelavr__eeproma_2.h" 1
# 62 "/home/indy/dev/hwa-dev/hwa_atmelavr__eeproma_2.h"
static inline __attribute__((always_inline)) uint8_t _hw_rdeeproma( intptr_t ar,
     intptr_t cr, uint8_t cb,
     intptr_t dr,
     uint16_t a )
{
  *(volatile uint16_t*)ar = a ;
  *(volatile uint8_t*)cr |= (1<<cb) ;
  return *(volatile uint8_t*) dr ;
}
# 108 "/home/indy/dev/hwa-dev/hwa_atmelavr__eeproma_2.h"
static inline __attribute__((always_inline)) void _hw_wreeproma( uint16_t a, uint8_t v,
     intptr_t ar,
     intptr_t dr,
     intptr_t mpe_ra, uint8_t mpe_bp,
     intptr_t pe_ra, uint8_t pe_bp )
{


  *(volatile uint16_t*)ar = a ;
  *(volatile uint8_t*)dr = v ;
  *(volatile uint8_t*)mpe_ra |= (1U<<mpe_bp) ;
  *(volatile uint8_t*)pe_ra |= (1U<<pe_bp) ;
}
# 17 "/home/indy/dev/hwa-dev/hwa_attinyx4_2.h" 2
# 1 "/home/indy/dev/hwa-dev/hwa_atmelavr__flasha_2.h" 1
# 25 "/home/indy/dev/hwa-dev/hwa_atmelavr__flasha_2.h"
static inline __attribute__((always_inline)) uint8_t _hw_flashardbyte( uint16_t a )
{
  uint8_t r ;
  __asm__ __volatile__("    lpm %[r], Z" "\n" : [r] "=&r" (r) : "z" (a))




   ;
  return r ;
}
# 57 "/home/indy/dev/hwa-dev/hwa_atmelavr__flasha_2.h"
static inline __attribute__((always_inline)) void _hw_flashardbytes( uint16_t addr, uint8_t count, uint8_t *dst )
{
  __asm__ __volatile__("1:  lpm  __tmp_reg__, Z+" "\n" "    st   %a2+, __tmp_reg__" "\n" "    dec  %A0" "\n" "    brne  1b" "\n" : "=r" (count), "=z" (addr), "=e" (dst) : "0" (count), "1" (addr), "2" (dst))
# 69 "/home/indy/dev/hwa-dev/hwa_atmelavr__flasha_2.h"
   ;
}
# 160 "/home/indy/dev/hwa-dev/hwa_atmelavr__flasha_2.h"
static inline __attribute__((always_inline)) void _hw_flasha_spm( intptr_t ptr )
{
  __asm__ __volatile__("	spm	\n" :: "z" (ptr) :)

   ;
}
# 182 "/home/indy/dev/hwa-dev/hwa_atmelavr__flasha_2.h"
static inline __attribute__((always_inline)) void __hw_flasha_ldpgbf( void *src )
{
  uint8_t r1 ;





  __asm__ __volatile__("    ldi   %[r1], 1<<BP_RWWSRE|1<<BP_SPMEN	\n" "    .if CSR < 0x40			\n" "    out	CSR, %[r1]		\n" "    .else				\n" "    sts	CSR+0x20, %[r1]		\n" "    .endif				\n" "    clr   r30				\n" "    clr   r31				\n" "1:  ld    r0, %a2+			\n" "    ld    r1, %a2+			\n" "    .if CSR < 0x20			\n" "    sbi	CSR, BP_SPMEN		\n" "    .else				\n" "    ldi	%[r1], 1<<BP_SPMEN	\n" "    .if CSR < 0x40			\n" "    out	CSR, %[r1]		\n" "    .else				\n" "    sts	CSR+0x20, %[r1]	\n" "    .endif				\n" "    .endif				\n" "    spm				\n" "    adiw  r30, 2			\n" "    cpi   r30, PGSIZE			\n" "    brne  1b				\n" : [r1] "=r" (r1), "=e" (src) : "1" (src) : "r0", "r1", "r30", "r31")
# 230 "/home/indy/dev/hwa-dev/hwa_atmelavr__flasha_2.h"
   ;
}
# 18 "/home/indy/dev/hwa-dev/hwa_attinyx4_2.h" 2
# 1 "/home/indy/dev/hwa-dev/hwa_atmelavr__swuarta_2.h" 1
# 111 "/home/indy/dev/hwa-dev/hwa_atmelavr__swuarta_2.h"
static inline __attribute__((always_inline)) void _hw_swuart0_config ( hwa_t *hwa __attribute__((unused)) )
{



  do { hwa->hw_counter1.clock = 1; hwa->hw_counter1.countmode = 1; hwa->hw_counter1.top = 4; } while(0)


                       ;





  do { _hwa_write_r8( &hwa->hw_portb.ddr, 0xFF,0, 1,0, (0?(1U<<1)-1:0)); ; } while(0);
  _hwa_write_r8( &hwa->hw_core0.gifr, 0x70,0x70, 1,5, 1 );
  _hwa_write_r8( &hwa->hw_core0.gimsk, 0x70,0x00, 1,5, 1 );
  _hwa_write_r8( &hwa->hw_pcic0.msk1, 0x0F,0x00, 1,0, 1 );
# 143 "/home/indy/dev/hwa-dev/hwa_atmelavr__swuarta_2.h"
  do { _hwa_write_r8( &hwa->hw_porta.ddr, 0xFF,0, 1,7, (1?(1U<<1)-1:0)); ; } while(0);

}


static inline __attribute__((always_inline)) void _hw_swuart1_config ( hwa_t *hwa __attribute__((unused)) )
{
# 182 "/home/indy/dev/hwa-dev/hwa_atmelavr__swuarta_2.h"
}
# 197 "/home/indy/dev/hwa-dev/hwa_atmelavr__swuarta_2.h"
extern uint8_t _hw_swuart0_getbyte ( ) ;
extern uint8_t _hw_swuart1_getbyte ( ) ;
# 212 "/home/indy/dev/hwa-dev/hwa_atmelavr__swuarta_2.h"
extern void _hw_swuart0_putbyte ( uint8_t byte ) ;
extern void _hw_swuart1_putbyte ( uint8_t byte ) ;
# 244 "/home/indy/dev/hwa-dev/hwa_atmelavr__swuarta_2.h"
typedef struct {
  unsigned int stop : 1 ;
  unsigned int idle : 1 ;
  unsigned int rxc : 1 ;
  unsigned int txc : 1 ;
  unsigned int rxtx : 1 ;
  unsigned int wbtx : 1 ;
  unsigned int synced : 1 ;
  unsigned int __7 : 1 ;
} swuart_status_t ;
# 274 "/home/indy/dev/hwa-dev/hwa_atmelavr__swuarta_2.h"
extern void _hw_swuart0_reset ( ) ;
extern void _hw_swuart1_reset ( ) ;






extern uint16_t _hw_swuart0_dtn ;
extern uint16_t _hw_swuart0_dt0 ;
# 19 "/home/indy/dev/hwa-dev/hwa_attinyx4_2.h" 2


static inline __attribute__((always_inline)) void _hwa_begin_all( hwa_t *hwa )
{
  __hwa_begin__corea(&hwa->hw_core0,0);
  __hwa_begin__io8a(&hwa->hw_porta,0x39);
  __hwa_begin__io8a(&hwa->hw_portb,0x36);
  __hwa_begin__pcica(&hwa->hw_pcic0,0x40);



  __hwa_begin__wdoga(&hwa->hw_watchdog0,0);
  __hwa_begin__c8a(&hwa->hw_counter0,0);
  __hwa_begin__c16a(&hwa->hw_counter1,0);
  __hwa_begin__ad10a(&hwa->hw_adc0,0);
}


static inline __attribute__((always_inline)) void _hwa_init_all( hwa_t *hwa )
{
  __hwa_init__corea(&hwa->hw_core0);
  __hwa_init__io8a(&hwa->hw_porta);
  __hwa_init__io8a(&hwa->hw_portb);
  __hwa_init__pcica(&hwa->hw_pcic0);


  __hwa_init__wdoga(&hwa->hw_watchdog0);
  __hwa_init__c8a(&hwa->hw_counter0);
  __hwa_init__c16a(&hwa->hw_counter1);
  __hwa_init__ad10a(&hwa->hw_adc0);
}


static inline __attribute__((always_inline)) void _hwa_commit_all( hwa_t *hwa )
{
  __hwa_solve__c8a(hwa, &hwa->hw_counter0);
  __hwa_solve__c16a(hwa, &hwa->hw_counter1);



  if ( hwa->hw_counter0.compare0_output != 0xFF
       && hwa->hw_counter0.compare0_output != 0 )
    do { _hwa_write_r8( &hwa->hw_portb.ddr, 0xFF,0, 1,2, (1?(1U<<1)-1:0)); ; } while(0);
  if ( hwa->hw_counter0.compare1_output != 0xFF
       && hwa->hw_counter0.compare1_output != 0 )
    do { _hwa_write_r8( &hwa->hw_porta.ddr, 0xFF,0, 1,7, (1?(1U<<1)-1:0)); ; } while(0);
  if ( hwa->hw_counter1.compare0_output != 0xFF
       && hwa->hw_counter1.compare0_output != 0 )
    do { _hwa_write_r8( &hwa->hw_porta.ddr, 0xFF,0, 1,6, (1?(1U<<1)-1:0)); ; } while(0);
  if ( hwa->hw_counter1.compare1_output != 0xFF
       && hwa->hw_counter1.compare1_output != 0 )
    do { _hwa_write_r8( &hwa->hw_porta.ddr, 0xFF,0, 1,5, (1?(1U<<1)-1:0)); ; } while(0);

  __hwa_commit__corea(hwa,&hwa->hw_core0);
  __hwa_commit__wdoga(hwa,&hwa->hw_watchdog0);
  __hwa_commit__io8a(hwa,&hwa->hw_porta);
  __hwa_commit__io8a(hwa,&hwa->hw_portb);

  __hwa_commit__pcica(hwa,&hwa->hw_pcic0);





  __hwa_commit__c8a(hwa,&hwa->hw_counter0);
  __hwa_commit__c16a(hwa,&hwa->hw_counter1);
  __hwa_commit__ad10a(hwa,&hwa->hw_adc0);
}
# 7 "/home/indy/dev/hwa-dev/hwa_attiny84_2.h" 2
# 494 "/home/indy/dev/hwa-dev/hwa__2.h" 2
# 151 "/home/indy/dev/hwa-dev/hwa.h" 2
# 14 "main.c" 2
# 22 "main.c"
int
main ( )
{
  hwa_check_optimizations(0); hwa_t hwa_st ; hwa_t *hwa = &hwa_st ; _hwa_begin_all(hwa) ; _hwa_init_all(hwa) ; do { hwa->commit = 0 ; _hwa_commit_all(hwa); } while(0) ; uint8_t hwa_xcommit = 0;



  do { _hw_swuart0_config(hwa); } while(0);

  do { _hwa_write_r8( &hwa->hw_porta.ddr, 0xFF,0, 1,6, (1?(1U<<1)-1:0)); ; } while(0);



  do { _hwa_write_r8( &hwa->hw_core0.mcucr, 0xFF,0x00, 1,5, 1 ); _hwa_write_r8( &hwa->hw_core0.mcucr, 0xFF,0x00, 2,3, 0 ); ; } while(0)

                           ;





  do { uint8_t foo __attribute__((unused)) = hwa_xcommit ; hwa->commit = 1 ; _hwa_commit_all(hwa); } while(0);



  __asm__ __volatile__("sei");






  for(;;) {



    _hw_write_r8(0x39 +0x02,0xFF,0x00,1,6,1);
    _hw_swuart0_reset();
    while ( !(*(volatile swuart_status_t*)(0 +0x33)).synced )
      __asm__ __volatile__("sleep");
    _hw_write_r8(0x39 +0x02,0xFF,0x00,1,6,0);



    _hw_swuart0_putbyte('$');

    for(;;) {



      while ( !(*(volatile swuart_status_t*)(0 +0x33)).rxc )
 __asm__ __volatile__("sleep");
      uint8_t byte = _hw_swuart0_getbyte();

      if ( byte=='A' ) {
 _hw_write_r8(0x39 +0x02,0xFF,0x00,1,6,1);



 uint16_t dt ;

 dt = _hw_read_r16(0 +(intptr_t)&_hw_swuart0_dtn,16,0) ;
 _hw_swuart0_putbyte((dt>>0) & 0xFF);
 _hw_swuart0_putbyte((dt>>8) & 0xFF);

 dt = _hw_read_r16(0 +(intptr_t)&_hw_swuart0_dt0,16,0) ;
 _hw_swuart0_putbyte((dt>>0) & 0xFF);
 _hw_swuart0_putbyte((dt>>8) & 0xFF);

 _hw_swuart0_putbyte('$');
 _hw_write_r8(0x39 +0x02,0xFF,0x00,1,6,0);
      }
      else {



 break ;
      }
    }
  }
}
