// 1 "test.c"
// 1 "/home/indy/dev/stm32/dev/64-dso/hwa/attiny45/tests//"
// 1 "<built-in>"
// 1 "<command-line>"
// 1 "test.c"

// 1 "../../hwa.h" 1

// 1 "../../types.h" 1

// 1 "/usr/lib/x86_64-linux-gnu/gcc/x86_64-linux-gnu/4.5.2/include/stdint.h" 1 3 4

// 1 "/usr/include/stdint.h" 1 3 4
// 26 "/usr/include/stdint.h" 3 4
// 1 "/usr/include/features.h" 1 3 4
// 323 "/usr/include/features.h" 3 4
// 1 "/usr/include/bits/predefs.h" 1 3 4
// 324 "/usr/include/features.h" 2 3 4
// 356 "/usr/include/features.h" 3 4
// 1 "/usr/include/sys/cdefs.h" 1 3 4
// 353 "/usr/include/sys/cdefs.h" 3 4
// 1 "/usr/include/bits/wordsize.h" 1 3 4
// 354 "/usr/include/sys/cdefs.h" 2 3 4
// 357 "/usr/include/features.h" 2 3 4
// 388 "/usr/include/features.h" 3 4
// 1 "/usr/include/gnu/stubs.h" 1 3 4

// 1 "/usr/include/bits/wordsize.h" 1 3 4
// 5 "/usr/include/gnu/stubs.h" 2 3 4

// 1 "/usr/include/gnu/stubs-64.h" 1 3 4
// 10 "/usr/include/gnu/stubs.h" 2 3 4
// 389 "/usr/include/features.h" 2 3 4
// 27 "/usr/include/stdint.h" 2 3 4
// 1 "/usr/include/bits/wchar.h" 1 3 4
// 28 "/usr/include/stdint.h" 2 3 4
// 1 "/usr/include/bits/wordsize.h" 1 3 4
// 29 "/usr/include/stdint.h" 2 3 4
// 37 "/usr/include/stdint.h" 3 4
typedef signed char int8_t;

typedef short int int16_t;

typedef int int32_t;

typedef long int int64_t;

typedef unsigned char uint8_t;

typedef unsigned short int uint16_t;

typedef unsigned int uint32_t;

typedef unsigned long int uint64_t;

// 66 "/usr/include/stdint.h" 3 4
typedef signed char int_least8_t;

typedef short int int_least16_t;

typedef int int_least32_t;

typedef long int int_least64_t;

typedef unsigned char uint_least8_t;

typedef unsigned short int uint_least16_t;

typedef unsigned int uint_least32_t;

typedef unsigned long int uint_least64_t;

// 91 "/usr/include/stdint.h" 3 4
typedef signed char int_fast8_t;

typedef long int int_fast16_t;

typedef long int int_fast32_t;

typedef long int int_fast64_t;

// 104 "/usr/include/stdint.h" 3 4
typedef unsigned char uint_fast8_t;

typedef unsigned long int uint_fast16_t;

typedef unsigned long int uint_fast32_t;

typedef unsigned long int uint_fast64_t;

// 120 "/usr/include/stdint.h" 3 4
typedef long int intptr_t;

typedef unsigned long int uintptr_t;

// 135 "/usr/include/stdint.h" 3 4
typedef long int intmax_t;

typedef unsigned long int uintmax_t;

// 4 "/usr/lib/x86_64-linux-gnu/gcc/x86_64-linux-gnu/4.5.2/include/stdint.h" 2 3 4
// 7 "../../types.h" 2

typedef int8_t s8;

typedef int16_t s16;

typedef int32_t s32;

typedef uint8_t u8;

typedef uint16_t u16;

typedef uint32_t u32;

typedef uint64_t u64;

typedef unsigned int uint ;

// 5 "../../hwa.h" 2

extern int hwa_dbg_gethr( const char *file, uint line,
const char *mname, const char *rname,
intptr_t addr ) ;

extern void hwa_dbg_sethr( const char *file, uint line,
const char *mname, const char *rname,
u8 size, intptr_t addr, uint omask, uint mask, uint val ) ;

// 142 "../../hwa.h"
void hwa_warn();

// 444 "../../hwa.h"
inline s8
hwa_log2_ceil ( u32 n )
{
  s8 l2 = 0 ;

  if ( (1UL<<l2) >= n ) return l2 ;
  l2++ ;

  if ( (1UL<<l2) >= n ) return l2 ;
  l2++ ;

  if ( (1UL<<l2) >= n ) return l2 ;
  l2++ ;

  if ( (1UL<<l2) >= n ) return l2 ;
  l2++ ;

  if ( (1UL<<l2) >= n ) return l2 ;
  l2++ ;

  if ( (1UL<<l2) >= n ) return l2 ;
  l2++ ;

  if ( (1UL<<l2) >= n ) return l2 ;
  l2++ ;

  if ( (1UL<<l2) >= n ) return l2 ;
  l2++ ;

  if ( (1UL<<l2) >= n ) return l2 ;
  l2++ ;

  if ( (1UL<<l2) >= n ) return l2 ;
  l2++ ;

  if ( (1UL<<l2) >= n ) return l2 ;
  l2++ ;

  if ( (1UL<<l2) >= n ) return l2 ;
  l2++ ;

  if ( (1UL<<l2) >= n ) return l2 ;
  l2++ ;

  if ( (1UL<<l2) >= n ) return l2 ;
  l2++ ;

  if ( (1UL<<l2) >= n ) return l2 ;
  l2++ ;

  if ( (1UL<<l2) >= n ) return l2 ;
  l2++ ;

  return l2 ;

}


// 479 "../../hwa.h"
// 1 "../../attiny45/hwa_attiny45.h" 1
// 9 "../../attiny45/hwa_attiny45.h"
// 1 "../../attiny45/hwa_attiny45_core.h" 1
// 64 "../../attiny45/hwa_attiny45_core.h"
typedef struct
{
  u8 commit ;

  intptr_t hwaddr ;
  u8 used ;

  u8 HWA_GIMSK_mmask, HWA_GIMSK_mvalue, HWA_GIMSK_omask, HWA_GIMSK_ovalue ;

  u8 HWA_GIFR_mmask, HWA_GIFR_mvalue, HWA_GIFR_omask, HWA_GIFR_ovalue ;

  u8 HWA_MCUCR_mmask, HWA_MCUCR_mvalue, HWA_MCUCR_omask, HWA_MCUCR_ovalue ;

  u8 HWA_ADCSRB_mmask, HWA_ADCSRB_mvalue, HWA_ADCSRB_omask, HWA_ADCSRB_ovalue ;

  u8 HWA_ACSR_mmask, HWA_ACSR_mvalue, HWA_ACSR_omask, HWA_ACSR_ovalue ;

  u8 HWA_DIDR0_mmask, HWA_DIDR0_mvalue, HWA_DIDR0_omask, HWA_DIDR0_ovalue ;

  u32 HWA_XSOHZ_mmask, HWA_XSOHZ_mvalue, HWA_XSOHZ_omask, HWA_XSOHZ_ovalue ;

  u32 HWA_SYSHZ_mmask, HWA_SYSHZ_mvalue, HWA_SYSHZ_omask, HWA_SYSHZ_ovalue ;

} HWA_CORE ;

// 99 "../../attiny45/hwa_attiny45_core.h"
inline void hwa_core_commit ( HWA_CORE *core )
{

  do {
    u8 m = core->HWA_GIMSK_mmask & (-1) ;
    if ( m != 0 ) {
      if ( m != 0x60 && core->HWA_GIMSK_omask != 0x60 ) {
        if ( core->commit && 0x3B != -1 ) {
          core->HWA_GIMSK_ovalue = hwa_dbg_gethr("../../attiny45/hwa_attiny45_core.h", 104, "HWA_CORE", "HWA_GIMSK", core->hwaddr+0x3B) ;
          core->HWA_GIMSK_omask = 0x60 ;
        } core->HWA_GIMSK_mvalue = (core->HWA_GIMSK_ovalue & ~core->HWA_GIMSK_mmask) | (core->HWA_GIMSK_mvalue & core->HWA_GIMSK_mmask) ;
      } core->HWA_GIMSK_ovalue = (core->HWA_GIMSK_ovalue & ~m) | (core->HWA_GIMSK_mvalue & m) ;
      if ( core->commit && 0x3B != -1 ) hwa_dbg_sethr("../../attiny45/hwa_attiny45_core.h", 104, "HWA_CORE", "HWA_GIMSK", sizeof(u8), core->hwaddr+0x3B, core->HWA_GIMSK_omask, m, core->HWA_GIMSK_ovalue);
      core->HWA_GIMSK_mmask &= ~m ;
      core->HWA_GIMSK_omask |= m ;
    }
  } while(0);

  do {
    u8 m = core->HWA_GIFR_mmask & (-1) ;
    if ( m != 0 ) {
      if ( m != 0x60 && core->HWA_GIFR_omask != 0x60 ) {
        if ( core->commit && 0x3A != -1 ) {
          core->HWA_GIFR_ovalue = hwa_dbg_gethr("../../attiny45/hwa_attiny45_core.h", 105, "HWA_CORE", "HWA_GIFR", core->hwaddr+0x3A) ;
          core->HWA_GIFR_omask = 0x60 ;
        } core->HWA_GIFR_mvalue = (core->HWA_GIFR_ovalue & ~core->HWA_GIFR_mmask) | (core->HWA_GIFR_mvalue & core->HWA_GIFR_mmask) ;
      } core->HWA_GIFR_ovalue = (core->HWA_GIFR_ovalue & ~m) | (core->HWA_GIFR_mvalue & m) ;
      if ( core->commit && 0x3A != -1 ) hwa_dbg_sethr("../../attiny45/hwa_attiny45_core.h", 105, "HWA_CORE", "HWA_GIFR", sizeof(u8), core->hwaddr+0x3A, core->HWA_GIFR_omask, m, core->HWA_GIFR_ovalue);
      core->HWA_GIFR_mmask &= ~m ;
      core->HWA_GIFR_omask |= m ;
    }
  } while(0);

  do {
    u8 m = core->HWA_MCUCR_mmask & (-1) ;
    if ( m != 0 ) {
      if ( m != 0x03 && core->HWA_MCUCR_omask != 0x03 ) {
        if ( core->commit && 0x35 != -1 ) {
          core->HWA_MCUCR_ovalue = hwa_dbg_gethr("../../attiny45/hwa_attiny45_core.h", 106, "HWA_CORE", "HWA_MCUCR", core->hwaddr+0x35) ;
          core->HWA_MCUCR_omask = 0x03 ;
        } core->HWA_MCUCR_mvalue = (core->HWA_MCUCR_ovalue & ~core->HWA_MCUCR_mmask) | (core->HWA_MCUCR_mvalue & core->HWA_MCUCR_mmask) ;
      } core->HWA_MCUCR_ovalue = (core->HWA_MCUCR_ovalue & ~m) | (core->HWA_MCUCR_mvalue & m) ;
      if ( core->commit && 0x35 != -1 ) hwa_dbg_sethr("../../attiny45/hwa_attiny45_core.h", 106, "HWA_CORE", "HWA_MCUCR", sizeof(u8), core->hwaddr+0x35, core->HWA_MCUCR_omask, m, core->HWA_MCUCR_ovalue);
      core->HWA_MCUCR_mmask &= ~m ;
      core->HWA_MCUCR_omask |= m ;
    }
  } while(0);

  do {
    u8 m = core->HWA_ADCSRB_mmask & (-1) ;
    if ( m != 0 ) {
      if ( m != 0x40 && core->HWA_ADCSRB_omask != 0x40 ) {
        if ( core->commit && 0x03 != -1 ) {
          core->HWA_ADCSRB_ovalue = hwa_dbg_gethr("../../attiny45/hwa_attiny45_core.h", 108, "HWA_CORE", "HWA_ADCSRB", core->hwaddr+0x03) ;
          core->HWA_ADCSRB_omask = 0x40 ;
        } core->HWA_ADCSRB_mvalue = (core->HWA_ADCSRB_ovalue & ~core->HWA_ADCSRB_mmask) | (core->HWA_ADCSRB_mvalue & core->HWA_ADCSRB_mmask) ;
      } core->HWA_ADCSRB_ovalue = (core->HWA_ADCSRB_ovalue & ~m) | (core->HWA_ADCSRB_mvalue & m) ;
      if ( core->commit && 0x03 != -1 ) hwa_dbg_sethr("../../attiny45/hwa_attiny45_core.h", 108, "HWA_CORE", "HWA_ADCSRB", sizeof(u8), core->hwaddr+0x03, core->HWA_ADCSRB_omask, m, core->HWA_ADCSRB_ovalue);
      core->HWA_ADCSRB_mmask &= ~m ;
      core->HWA_ADCSRB_omask |= m ;
    }
  } while(0);

  do {
    u8 m = core->HWA_ACSR_mmask & (-1) ;
    if ( m != 0 ) {
      if ( m != 0xDB && core->HWA_ACSR_omask != 0xDB ) {
        if ( core->commit && 0x08 != -1 ) {
          core->HWA_ACSR_ovalue = hwa_dbg_gethr("../../attiny45/hwa_attiny45_core.h", 109, "HWA_CORE", "HWA_ACSR", core->hwaddr+0x08) ;
          core->HWA_ACSR_omask = 0xDB ;
        } core->HWA_ACSR_mvalue = (core->HWA_ACSR_ovalue & ~core->HWA_ACSR_mmask) | (core->HWA_ACSR_mvalue & core->HWA_ACSR_mmask) ;
      } core->HWA_ACSR_ovalue = (core->HWA_ACSR_ovalue & ~m) | (core->HWA_ACSR_mvalue & m) ;
      if ( core->commit && 0x08 != -1 ) hwa_dbg_sethr("../../attiny45/hwa_attiny45_core.h", 109, "HWA_CORE", "HWA_ACSR", sizeof(u8), core->hwaddr+0x08, core->HWA_ACSR_omask, m, core->HWA_ACSR_ovalue);
      core->HWA_ACSR_mmask &= ~m ;
      core->HWA_ACSR_omask |= m ;
    }
  } while(0);

  do {
    u8 m = core->HWA_DIDR0_mmask & (-1) ;
    if ( m != 0 ) {
      if ( m != 0x3F && core->HWA_DIDR0_omask != 0x3F ) {
        if ( core->commit && 0x14 != -1 ) {
          core->HWA_DIDR0_ovalue = hwa_dbg_gethr("../../attiny45/hwa_attiny45_core.h", 110, "HWA_CORE", "HWA_DIDR0", core->hwaddr+0x14) ;
          core->HWA_DIDR0_omask = 0x3F ;
        } core->HWA_DIDR0_mvalue = (core->HWA_DIDR0_ovalue & ~core->HWA_DIDR0_mmask) | (core->HWA_DIDR0_mvalue & core->HWA_DIDR0_mmask) ;
      } core->HWA_DIDR0_ovalue = (core->HWA_DIDR0_ovalue & ~m) | (core->HWA_DIDR0_mvalue & m) ;
      if ( core->commit && 0x14 != -1 ) hwa_dbg_sethr("../../attiny45/hwa_attiny45_core.h", 110, "HWA_CORE", "HWA_DIDR0", sizeof(u8), core->hwaddr+0x14, core->HWA_DIDR0_omask, m, core->HWA_DIDR0_ovalue);
      core->HWA_DIDR0_mmask &= ~m ;
      core->HWA_DIDR0_omask |= m ;
    }
  } while(0);

  do {
    u32 m = core->HWA_SYSHZ_mmask & (-1) ;
    if ( m != 0 ) {
      if ( m != 0xFFFFFFFF && core->HWA_SYSHZ_omask != 0xFFFFFFFF ) {
        if ( core->commit && -1 != -1 ) {
          core->HWA_SYSHZ_ovalue = hwa_dbg_gethr("../../attiny45/hwa_attiny45_core.h", 112, "HWA_CORE", "HWA_SYSHZ", core->hwaddr+-1) ;
          core->HWA_SYSHZ_omask = 0xFFFFFFFF ;
        } core->HWA_SYSHZ_mvalue = (core->HWA_SYSHZ_ovalue & ~core->HWA_SYSHZ_mmask) | (core->HWA_SYSHZ_mvalue & core->HWA_SYSHZ_mmask) ;
      } core->HWA_SYSHZ_ovalue = (core->HWA_SYSHZ_ovalue & ~m) | (core->HWA_SYSHZ_mvalue & m) ;
      if ( core->commit && -1 != -1 ) hwa_dbg_sethr("../../attiny45/hwa_attiny45_core.h", 112, "HWA_CORE", "HWA_SYSHZ", sizeof(u32), core->hwaddr+-1, core->HWA_SYSHZ_omask, m, core->HWA_SYSHZ_ovalue);
      core->HWA_SYSHZ_mmask &= ~m ;
      core->HWA_SYSHZ_omask |= m ;
    }
  } while(0);

  do {
    u32 m = core->HWA_XSOHZ_mmask & (-1) ;
    if ( m != 0 ) {
      if ( m != 0xFFFFFFFF && core->HWA_XSOHZ_omask != 0xFFFFFFFF ) {
        if ( core->commit && -1 != -1 ) {
          core->HWA_XSOHZ_ovalue = hwa_dbg_gethr("../../attiny45/hwa_attiny45_core.h", 113, "HWA_CORE", "HWA_XSOHZ", core->hwaddr+-1) ;
          core->HWA_XSOHZ_omask = 0xFFFFFFFF ;
        } core->HWA_XSOHZ_mvalue = (core->HWA_XSOHZ_ovalue & ~core->HWA_XSOHZ_mmask) | (core->HWA_XSOHZ_mvalue & core->HWA_XSOHZ_mmask) ;
      } core->HWA_XSOHZ_ovalue = (core->HWA_XSOHZ_ovalue & ~m) | (core->HWA_XSOHZ_mvalue & m) ;
      if ( core->commit && -1 != -1 ) hwa_dbg_sethr("../../attiny45/hwa_attiny45_core.h", 113, "HWA_CORE", "HWA_XSOHZ", sizeof(u32), core->hwaddr+-1, core->HWA_XSOHZ_omask, m, core->HWA_XSOHZ_ovalue);
      core->HWA_XSOHZ_mmask &= ~m ;
      core->HWA_XSOHZ_omask |= m ;
    }
  } while(0);

}


// 10 "../../attiny45/hwa_attiny45.h" 2
// 1 "../../attiny45/hwa_attiny45_gpio.h" 1

// 1 "../../hwa_gpio.h" 1
// 5 "../../attiny45/hwa_attiny45_gpio.h" 2
// 28 "../../attiny45/hwa_attiny45_gpio.h"
typedef struct
{
  intptr_t hwaddr ;
  u8 used ;

  u8 HWA_DDR_mmask, HWA_DDR_mvalue, HWA_DDR_omask, HWA_DDR_ovalue ;

  u8 HWA_PORT_mmask, HWA_PORT_mvalue, HWA_PORT_omask, HWA_PORT_ovalue ;

} HWA_GPIO ;

// 11 "../../attiny45/hwa_attiny45.h" 2
// 1 "../../attiny45/hwa_attiny45_irq.h" 1
// 12 "../../attiny45/hwa_attiny45.h" 2
// 1 "../../attiny45/hwa_attiny45_timer.h" 1
// 156 "../../attiny45/hwa_attiny45_timer.h"
// 1 "../../attiny45/hwa_attiny45_timer0.h" 1
// 87 "../../attiny45/hwa_attiny45_timer0.h"
typedef struct
{
  intptr_t hwaddr ;
  u8 used ;

  u8 HWA_CCRA_mmask, HWA_CCRA_mvalue, HWA_CCRA_omask, HWA_CCRA_ovalue ;
  ;

  u8 HWA_CCRB_mmask, HWA_CCRB_mvalue, HWA_CCRB_omask, HWA_CCRB_ovalue ;
  ;

  u8 HWA_OCRA_mmask, HWA_OCRA_mvalue, HWA_OCRA_omask, HWA_OCRA_ovalue ;
  ;

  u8 HWA_OCRB_mmask, HWA_OCRB_mvalue, HWA_OCRB_omask, HWA_OCRB_ovalue ;
  ;

  u8 HWA_IMSK_mmask, HWA_IMSK_mvalue, HWA_IMSK_omask, HWA_IMSK_ovalue ;
  ;

  u8 HWA_IFR_mmask, HWA_IFR_mvalue, HWA_IFR_omask, HWA_IFR_ovalue ;
  ;

  u8 HWA_MODE_mmask, HWA_MODE_mvalue, HWA_MODE_omask, HWA_MODE_ovalue ;
  ;

  u8 HWA_CLK_mmask, HWA_CLK_mvalue, HWA_CLK_omask, HWA_CLK_ovalue ;
  ;

  u32 HWA_CLKHZ_mmask, HWA_CLKHZ_mvalue, HWA_CLKHZ_omask, HWA_CLKHZ_ovalue ;
  ;

  u16 HWA_PSC_mmask, HWA_PSC_mvalue, HWA_PSC_omask, HWA_PSC_ovalue ;
  ;

  u16 HWA_MAX_mmask, HWA_MAX_mvalue, HWA_MAX_omask, HWA_MAX_ovalue ;
  ;

  u32 HWA_HZ_mmask, HWA_HZ_mvalue, HWA_HZ_omask, HWA_HZ_ovalue ;
  ;

  u32 HWA_PERIOD_mmask, HWA_PERIOD_mvalue, HWA_PERIOD_omask, HWA_PERIOD_ovalue ;
  ;

} HWA_TIMER0 ;

// 124 "../../attiny45/hwa_attiny45_timer0.h"
inline void
hwa_timer_commit_timer0 ( HWA_CORE *core, HWA_TIMER0 *p )
{
  if ( !p->used )
    return ;

  u8 mode = ((p->HWA_MODE_mmask|p->HWA_MODE_omask) ? p->HWA_MODE_mvalue : 0);

  u8 clk = ((p->HWA_CLK_mmask|p->HWA_CLK_omask) ? p->HWA_CLK_mvalue : 0);

  u32 clkhz = ((p->HWA_CLKHZ_mmask|p->HWA_CLKHZ_omask) ? p->HWA_CLKHZ_mvalue : 0);

  u16 psc = ((p->HWA_PSC_mmask|p->HWA_PSC_omask) ? p->HWA_PSC_mvalue : 0);

  u32 syshz = ((core->HWA_SYSHZ_mmask|core->HWA_SYSHZ_omask) ? core->HWA_SYSHZ_mvalue : 0);

  if ( mode == 0 ) {
    do {
      extern void __attribute__((error("TIMER0: clock source is not set."))) hwa_error_0(void);
      hwa_error_0();
    } while(0);

  }
  else if ( mode == 1 ) {

    do {
      u8 mmask = (0b1) << (3) ;
      u8 vmask = (0) << (3) ;
      if ( (0xCF & mmask) != mmask ) do {
        extern void __attribute__((error("HWA_CCRB" ": try to modify not writeable bits."))) hwa_error_1(void);
        hwa_error_1();
      } while(0);
      if ( (p->HWA_CCRB_mmask & mmask) != 0 && (p->HWA_CCRB_mvalue & mmask) != vmask ) do {
        extern void __attribute__((error("HWA_CCRB" ": previous affectation with different value not committed."))) hwa_error_2(void);
        hwa_error_2();
      } while(0);
      if ( ((p->HWA_CCRB_omask & mmask) == mmask && (p->HWA_CCRB_ovalue & mmask) != vmask) || (p->HWA_CCRB_omask & mmask) != mmask) {
        p->used = 1 ;
        p->HWA_CCRB_mmask |= mmask ;
        p->HWA_CCRB_mvalue = (p->HWA_CCRB_mvalue & ~mmask) | (mmask & vmask) ;
      }
    } while(0);

    do {
      u8 mmask = (0b1) << (1) ;
      u8 vmask = (0) << (1) ;
      if ( (0xF3 & mmask) != mmask ) do {
        extern void __attribute__((error("HWA_CCRA" ": try to modify not writeable bits."))) hwa_error_3(void);
        hwa_error_3();
      } while(0);
      if ( (p->HWA_CCRA_mmask & mmask) != 0 && (p->HWA_CCRA_mvalue & mmask) != vmask ) do {
        extern void __attribute__((error("HWA_CCRA" ": previous affectation with different value not committed."))) hwa_error_4(void);
        hwa_error_4();
      } while(0);
      if ( ((p->HWA_CCRA_omask & mmask) == mmask && (p->HWA_CCRA_ovalue & mmask) != vmask) || (p->HWA_CCRA_omask & mmask) != mmask) {
        p->used = 1 ;
        p->HWA_CCRA_mmask |= mmask ;
        p->HWA_CCRA_mvalue = (p->HWA_CCRA_mvalue & ~mmask) | (mmask & vmask) ;
      }
    } while(0);

    do {
      u8 mmask = (0b1) << (0) ;
      u8 vmask = (0) << (0) ;
      if ( (0xF3 & mmask) != mmask ) do {
        extern void __attribute__((error("HWA_CCRA" ": try to modify not writeable bits."))) hwa_error_5(void);
        hwa_error_5();
      } while(0);
      if ( (p->HWA_CCRA_mmask & mmask) != 0 && (p->HWA_CCRA_mvalue & mmask) != vmask ) do {
        extern void __attribute__((error("HWA_CCRA" ": previous affectation with different value not committed."))) hwa_error_6(void);
        hwa_error_6();
      } while(0);
      if ( ((p->HWA_CCRA_omask & mmask) == mmask && (p->HWA_CCRA_ovalue & mmask) != vmask) || (p->HWA_CCRA_omask & mmask) != mmask) {
        p->used = 1 ;
        p->HWA_CCRA_mmask |= mmask ;
        p->HWA_CCRA_mvalue = (p->HWA_CCRA_mvalue & ~mmask) | (mmask & vmask) ;
      }
    } while(0);

  }
  else
  do {
    extern void __attribute__((error("Timer mode not supported."))) hwa_error_7(void);
    hwa_error_7();
  } while(0);

  if ( clk == 0 ) {
    do {
      extern void __attribute__((error("TIMER0: clock source is not set."))) hwa_error_8(void);
      hwa_error_8();
    } while(0);

  }
  else if ( clk == 1 ) {
    do {
      extern void __attribute__((error(""))) hwa_error_9(void);
      hwa_error_9();
    } while(0);

    psc = 0 ;

  }
  else if ( clk == 2 ) {
    if ( psc == 0 ) {
      if ( clkhz == 0 )
      do {
        extern void __attribute__((error("TIMER0: neither clockhz nor prescaler is set."))) hwa_error_10(void);
        hwa_error_10();
      } while(0);

      if ( clkhz != 2000000 )
      do {
        extern void __attribute__((error(""))) hwa_error_11(void);
        hwa_error_11();
      } while(0);

      if ( syshz != 16000000 )
      do {
        extern void __attribute__((error(""))) hwa_error_12(void);
        hwa_error_12();
      } while(0);

      psc = syshz / clkhz ;

    }

  }
  else
  do {
    extern void __attribute__((error("TIMER0: clock source not supported."))) hwa_error_13(void);
    hwa_error_13();
  } while(0);

  if ( psc == 0 ) do {
    u8 mmask = (0b111) << (0) ;
    u8 vmask = (0b000) << (0) ;
    if ( (0xCF & mmask) != mmask ) do {
      extern void __attribute__((error("HWA_CCRB" ": try to modify not writeable bits."))) hwa_error_14(void);
      hwa_error_14();
    } while(0);
    if ( (p->HWA_CCRB_mmask & mmask) != 0 && (p->HWA_CCRB_mvalue & mmask) != vmask ) do {
      extern void __attribute__((error("HWA_CCRB" ": previous affectation with different value not committed."))) hwa_error_15(void);
      hwa_error_15();
    } while(0);
    if ( ((p->HWA_CCRB_omask & mmask) == mmask && (p->HWA_CCRB_ovalue & mmask) != vmask) || (p->HWA_CCRB_omask & mmask) != mmask) {
      p->used = 1 ;
      p->HWA_CCRB_mmask |= mmask ;
      p->HWA_CCRB_mvalue = (p->HWA_CCRB_mvalue & ~mmask) | (mmask & vmask) ;
    }
  } while(0);

  else if ( psc == 1 ) do {
    u8 mmask = (0b111) << (0) ;
    u8 vmask = (0b001) << (0) ;
    if ( (0xCF & mmask) != mmask ) do {
      extern void __attribute__((error("HWA_CCRB" ": try to modify not writeable bits."))) hwa_error_16(void);
      hwa_error_16();
    } while(0);
    if ( (p->HWA_CCRB_mmask & mmask) != 0 && (p->HWA_CCRB_mvalue & mmask) != vmask ) do {
      extern void __attribute__((error("HWA_CCRB" ": previous affectation with different value not committed."))) hwa_error_17(void);
      hwa_error_17();
    } while(0);
    if ( ((p->HWA_CCRB_omask & mmask) == mmask && (p->HWA_CCRB_ovalue & mmask) != vmask) || (p->HWA_CCRB_omask & mmask) != mmask) {
      p->used = 1 ;
      p->HWA_CCRB_mmask |= mmask ;
      p->HWA_CCRB_mvalue = (p->HWA_CCRB_mvalue & ~mmask) | (mmask & vmask) ;
    }
  } while(0);

  else if ( psc == 8 ) do {
    u8 mmask = (0b111) << (0) ;
    u8 vmask = (0b010) << (0) ;
    if ( (0xCF & mmask) != mmask ) do {
      extern void __attribute__((error("HWA_CCRB" ": try to modify not writeable bits."))) hwa_error_18(void);
      hwa_error_18();
    } while(0);
    if ( (p->HWA_CCRB_mmask & mmask) != 0 && (p->HWA_CCRB_mvalue & mmask) != vmask ) do {
      extern void __attribute__((error("HWA_CCRB" ": previous affectation with different value not committed."))) hwa_error_19(void);
      hwa_error_19();
    } while(0);
    if ( ((p->HWA_CCRB_omask & mmask) == mmask && (p->HWA_CCRB_ovalue & mmask) != vmask) || (p->HWA_CCRB_omask & mmask) != mmask) {
      p->used = 1 ;
      p->HWA_CCRB_mmask |= mmask ;
      p->HWA_CCRB_mvalue = (p->HWA_CCRB_mvalue & ~mmask) | (mmask & vmask) ;
    }
  } while(0);

  else if ( psc == 64 ) do {
    u8 mmask = (0b111) << (0) ;
    u8 vmask = (0b011) << (0) ;
    if ( (0xCF & mmask) != mmask ) do {
      extern void __attribute__((error("HWA_CCRB" ": try to modify not writeable bits."))) hwa_error_20(void);
      hwa_error_20();
    } while(0);
    if ( (p->HWA_CCRB_mmask & mmask) != 0 && (p->HWA_CCRB_mvalue & mmask) != vmask ) do {
      extern void __attribute__((error("HWA_CCRB" ": previous affectation with different value not committed."))) hwa_error_21(void);
      hwa_error_21();
    } while(0);
    if ( ((p->HWA_CCRB_omask & mmask) == mmask && (p->HWA_CCRB_ovalue & mmask) != vmask) || (p->HWA_CCRB_omask & mmask) != mmask) {
      p->used = 1 ;
      p->HWA_CCRB_mmask |= mmask ;
      p->HWA_CCRB_mvalue = (p->HWA_CCRB_mvalue & ~mmask) | (mmask & vmask) ;
    }
  } while(0);

  else if ( psc == 256 ) do {
    u8 mmask = (0b111) << (0) ;
    u8 vmask = (0b100) << (0) ;
    if ( (0xCF & mmask) != mmask ) do {
      extern void __attribute__((error("HWA_CCRB" ": try to modify not writeable bits."))) hwa_error_22(void);
      hwa_error_22();
    } while(0);
    if ( (p->HWA_CCRB_mmask & mmask) != 0 && (p->HWA_CCRB_mvalue & mmask) != vmask ) do {
      extern void __attribute__((error("HWA_CCRB" ": previous affectation with different value not committed."))) hwa_error_23(void);
      hwa_error_23();
    } while(0);
    if ( ((p->HWA_CCRB_omask & mmask) == mmask && (p->HWA_CCRB_ovalue & mmask) != vmask) || (p->HWA_CCRB_omask & mmask) != mmask) {
      p->used = 1 ;
      p->HWA_CCRB_mmask |= mmask ;
      p->HWA_CCRB_mvalue = (p->HWA_CCRB_mvalue & ~mmask) | (mmask & vmask) ;
    }
  } while(0);

  else if ( psc == 1024 ) do {
    u8 mmask = (0b111) << (0) ;
    u8 vmask = (0b101) << (0) ;
    if ( (0xCF & mmask) != mmask ) do {
      extern void __attribute__((error("HWA_CCRB" ": try to modify not writeable bits."))) hwa_error_24(void);
      hwa_error_24();
    } while(0);
    if ( (p->HWA_CCRB_mmask & mmask) != 0 && (p->HWA_CCRB_mvalue & mmask) != vmask ) do {
      extern void __attribute__((error("HWA_CCRB" ": previous affectation with different value not committed."))) hwa_error_25(void);
      hwa_error_25();
    } while(0);
    if ( ((p->HWA_CCRB_omask & mmask) == mmask && (p->HWA_CCRB_ovalue & mmask) != vmask) || (p->HWA_CCRB_omask & mmask) != mmask) {
      p->used = 1 ;
      p->HWA_CCRB_mmask |= mmask ;
      p->HWA_CCRB_mvalue = (p->HWA_CCRB_mvalue & ~mmask) | (mmask & vmask) ;
    }
  } while(0);

  else
  do {
    extern void __attribute__((error("TIMER0: invalid prescaler value."))) hwa_error_26(void);
    hwa_error_26();
  } while(0);

  do {
    u8 m = p->HWA_MODE_mmask & (-1) ;
    if ( m != 0 ) {
      if ( m != 0xFF && p->HWA_MODE_omask != 0xFF ) {
        if ( core->commit && -1 != -1 ) {
          p->HWA_MODE_ovalue = hwa_dbg_gethr("../../attiny45/hwa_attiny45_timer0.h", 193, "HWA_TIMER", "HWA_MODE", p->hwaddr+-1) ;
          p->HWA_MODE_omask = 0xFF ;
        } p->HWA_MODE_mvalue = (p->HWA_MODE_ovalue & ~p->HWA_MODE_mmask) | (p->HWA_MODE_mvalue & p->HWA_MODE_mmask) ;
      } p->HWA_MODE_ovalue = (p->HWA_MODE_ovalue & ~m) | (p->HWA_MODE_mvalue & m) ;
      if ( core->commit && -1 != -1 ) hwa_dbg_sethr("../../attiny45/hwa_attiny45_timer0.h", 193, "HWA_TIMER", "HWA_MODE", sizeof(u8), p->hwaddr+-1, p->HWA_MODE_omask, m, p->HWA_MODE_ovalue);
      p->HWA_MODE_mmask &= ~m ;
      p->HWA_MODE_omask |= m ;
    }
  } while(0);

  do {
    u8 m = p->HWA_CLK_mmask & (-1) ;
    if ( m != 0 ) {
      if ( m != 0xFF && p->HWA_CLK_omask != 0xFF ) {
        if ( core->commit && -1 != -1 ) {
          p->HWA_CLK_ovalue = hwa_dbg_gethr("../../attiny45/hwa_attiny45_timer0.h", 194, "HWA_TIMER", "HWA_CLK", p->hwaddr+-1) ;
          p->HWA_CLK_omask = 0xFF ;
        } p->HWA_CLK_mvalue = (p->HWA_CLK_ovalue & ~p->HWA_CLK_mmask) | (p->HWA_CLK_mvalue & p->HWA_CLK_mmask) ;
      } p->HWA_CLK_ovalue = (p->HWA_CLK_ovalue & ~m) | (p->HWA_CLK_mvalue & m) ;
      if ( core->commit && -1 != -1 ) hwa_dbg_sethr("../../attiny45/hwa_attiny45_timer0.h", 194, "HWA_TIMER", "HWA_CLK", sizeof(u8), p->hwaddr+-1, p->HWA_CLK_omask, m, p->HWA_CLK_ovalue);
      p->HWA_CLK_mmask &= ~m ;
      p->HWA_CLK_omask |= m ;
    }
  } while(0);

  do {
    u32 m = p->HWA_CLKHZ_mmask & (-1) ;
    if ( m != 0 ) {
      if ( m != 0xFFFFFFFF && p->HWA_CLKHZ_omask != 0xFFFFFFFF ) {
        if ( core->commit && -1 != -1 ) {
          p->HWA_CLKHZ_ovalue = hwa_dbg_gethr("../../attiny45/hwa_attiny45_timer0.h", 195, "HWA_TIMER", "HWA_CLKHZ", p->hwaddr+-1) ;
          p->HWA_CLKHZ_omask = 0xFFFFFFFF ;
        } p->HWA_CLKHZ_mvalue = (p->HWA_CLKHZ_ovalue & ~p->HWA_CLKHZ_mmask) | (p->HWA_CLKHZ_mvalue & p->HWA_CLKHZ_mmask) ;
      } p->HWA_CLKHZ_ovalue = (p->HWA_CLKHZ_ovalue & ~m) | (p->HWA_CLKHZ_mvalue & m) ;
      if ( core->commit && -1 != -1 ) hwa_dbg_sethr("../../attiny45/hwa_attiny45_timer0.h", 195, "HWA_TIMER", "HWA_CLKHZ", sizeof(u32), p->hwaddr+-1, p->HWA_CLKHZ_omask, m, p->HWA_CLKHZ_ovalue);
      p->HWA_CLKHZ_mmask &= ~m ;
      p->HWA_CLKHZ_omask |= m ;
    }
  } while(0);

  do {
    u16 m = p->HWA_PSC_mmask & (-1) ;
    if ( m != 0 ) {
      if ( m != 0xFFFF && p->HWA_PSC_omask != 0xFFFF ) {
        if ( core->commit && -1 != -1 ) {
          p->HWA_PSC_ovalue = hwa_dbg_gethr("../../attiny45/hwa_attiny45_timer0.h", 196, "HWA_TIMER", "HWA_PSC", p->hwaddr+-1) ;
          p->HWA_PSC_omask = 0xFFFF ;
        } p->HWA_PSC_mvalue = (p->HWA_PSC_ovalue & ~p->HWA_PSC_mmask) | (p->HWA_PSC_mvalue & p->HWA_PSC_mmask) ;
      } p->HWA_PSC_ovalue = (p->HWA_PSC_ovalue & ~m) | (p->HWA_PSC_mvalue & m) ;
      if ( core->commit && -1 != -1 ) hwa_dbg_sethr("../../attiny45/hwa_attiny45_timer0.h", 196, "HWA_TIMER", "HWA_PSC", sizeof(u16), p->hwaddr+-1, p->HWA_PSC_omask, m, p->HWA_PSC_ovalue);
      p->HWA_PSC_mmask &= ~m ;
      p->HWA_PSC_omask |= m ;
    }
  } while(0);

  do {
    u16 m = p->HWA_MAX_mmask & (-1) ;
    if ( m != 0 ) {
      if ( m != 0xFFFF && p->HWA_MAX_omask != 0xFFFF ) {
        if ( core->commit && -1 != -1 ) {
          p->HWA_MAX_ovalue = hwa_dbg_gethr("../../attiny45/hwa_attiny45_timer0.h", 197, "HWA_TIMER", "HWA_MAX", p->hwaddr+-1) ;
          p->HWA_MAX_omask = 0xFFFF ;
        } p->HWA_MAX_mvalue = (p->HWA_MAX_ovalue & ~p->HWA_MAX_mmask) | (p->HWA_MAX_mvalue & p->HWA_MAX_mmask) ;
      } p->HWA_MAX_ovalue = (p->HWA_MAX_ovalue & ~m) | (p->HWA_MAX_mvalue & m) ;
      if ( core->commit && -1 != -1 ) hwa_dbg_sethr("../../attiny45/hwa_attiny45_timer0.h", 197, "HWA_TIMER", "HWA_MAX", sizeof(u16), p->hwaddr+-1, p->HWA_MAX_omask, m, p->HWA_MAX_ovalue);
      p->HWA_MAX_mmask &= ~m ;
      p->HWA_MAX_omask |= m ;
    }
  } while(0);

  do {
    u32 m = p->HWA_HZ_mmask & (-1) ;
    if ( m != 0 ) {
      if ( m != 0xFFFFFFFF && p->HWA_HZ_omask != 0xFFFFFFFF ) {
        if ( core->commit && -1 != -1 ) {
          p->HWA_HZ_ovalue = hwa_dbg_gethr("../../attiny45/hwa_attiny45_timer0.h", 198, "HWA_TIMER", "HWA_HZ", p->hwaddr+-1) ;
          p->HWA_HZ_omask = 0xFFFFFFFF ;
        } p->HWA_HZ_mvalue = (p->HWA_HZ_ovalue & ~p->HWA_HZ_mmask) | (p->HWA_HZ_mvalue & p->HWA_HZ_mmask) ;
      } p->HWA_HZ_ovalue = (p->HWA_HZ_ovalue & ~m) | (p->HWA_HZ_mvalue & m) ;
      if ( core->commit && -1 != -1 ) hwa_dbg_sethr("../../attiny45/hwa_attiny45_timer0.h", 198, "HWA_TIMER", "HWA_HZ", sizeof(u32), p->hwaddr+-1, p->HWA_HZ_omask, m, p->HWA_HZ_ovalue);
      p->HWA_HZ_mmask &= ~m ;
      p->HWA_HZ_omask |= m ;
    }
  } while(0);

  do {
    u32 m = p->HWA_PERIOD_mmask & (-1) ;
    if ( m != 0 ) {
      if ( m != 0xFFFFFFFF && p->HWA_PERIOD_omask != 0xFFFFFFFF ) {
        if ( core->commit && -1 != -1 ) {
          p->HWA_PERIOD_ovalue = hwa_dbg_gethr("../../attiny45/hwa_attiny45_timer0.h", 199, "HWA_TIMER", "HWA_PERIOD", p->hwaddr+-1) ;
          p->HWA_PERIOD_omask = 0xFFFFFFFF ;
        } p->HWA_PERIOD_mvalue = (p->HWA_PERIOD_ovalue & ~p->HWA_PERIOD_mmask) | (p->HWA_PERIOD_mvalue & p->HWA_PERIOD_mmask) ;
      } p->HWA_PERIOD_ovalue = (p->HWA_PERIOD_ovalue & ~m) | (p->HWA_PERIOD_mvalue & m) ;
      if ( core->commit && -1 != -1 ) hwa_dbg_sethr("../../attiny45/hwa_attiny45_timer0.h", 199, "HWA_TIMER", "HWA_PERIOD", sizeof(u32), p->hwaddr+-1, p->HWA_PERIOD_omask, m, p->HWA_PERIOD_ovalue);
      p->HWA_PERIOD_mmask &= ~m ;
      p->HWA_PERIOD_omask |= m ;
    }
  } while(0);

  do {
    u8 m = p->HWA_CCRA_mmask & (-1) ;
    if ( m != 0 ) {
      if ( m != 0xF3 && p->HWA_CCRA_omask != 0xF3 ) {
        if ( core->commit && 0x2A != -1 ) {
          p->HWA_CCRA_ovalue = hwa_dbg_gethr("../../attiny45/hwa_attiny45_timer0.h", 201, "HWA_TIMER0", "HWA_CCRA", p->hwaddr+0x2A) ;
          p->HWA_CCRA_omask = 0xF3 ;
        } p->HWA_CCRA_mvalue = (p->HWA_CCRA_ovalue & ~p->HWA_CCRA_mmask) | (p->HWA_CCRA_mvalue & p->HWA_CCRA_mmask) ;
      } p->HWA_CCRA_ovalue = (p->HWA_CCRA_ovalue & ~m) | (p->HWA_CCRA_mvalue & m) ;
      if ( core->commit && 0x2A != -1 ) hwa_dbg_sethr("../../attiny45/hwa_attiny45_timer0.h", 201, "HWA_TIMER0", "HWA_CCRA", sizeof(u8), p->hwaddr+0x2A, p->HWA_CCRA_omask, m, p->HWA_CCRA_ovalue);
      p->HWA_CCRA_mmask &= ~m ;
      p->HWA_CCRA_omask |= m ;
    }
  } while(0);

  do {
    u8 m = p->HWA_CCRB_mmask & (-1) ;
    if ( m != 0 ) {
      if ( m != 0xCF && p->HWA_CCRB_omask != 0xCF ) {
        if ( core->commit && 0x33 != -1 ) {
          p->HWA_CCRB_ovalue = hwa_dbg_gethr("../../attiny45/hwa_attiny45_timer0.h", 202, "HWA_TIMER0", "HWA_CCRB", p->hwaddr+0x33) ;
          p->HWA_CCRB_omask = 0xCF ;
        } p->HWA_CCRB_mvalue = (p->HWA_CCRB_ovalue & ~p->HWA_CCRB_mmask) | (p->HWA_CCRB_mvalue & p->HWA_CCRB_mmask) ;
      } p->HWA_CCRB_ovalue = (p->HWA_CCRB_ovalue & ~m) | (p->HWA_CCRB_mvalue & m) ;
      if ( core->commit && 0x33 != -1 ) hwa_dbg_sethr("../../attiny45/hwa_attiny45_timer0.h", 202, "HWA_TIMER0", "HWA_CCRB", sizeof(u8), p->hwaddr+0x33, p->HWA_CCRB_omask, m, p->HWA_CCRB_ovalue);
      p->HWA_CCRB_mmask &= ~m ;
      p->HWA_CCRB_omask |= m ;
    }
  } while(0);

  do {
    u8 m = p->HWA_OCRA_mmask & (-1) ;
    if ( m != 0 ) {
      if ( m != 0xFF && p->HWA_OCRA_omask != 0xFF ) {
        if ( core->commit && 0x29 != -1 ) {
          p->HWA_OCRA_ovalue = hwa_dbg_gethr("../../attiny45/hwa_attiny45_timer0.h", 203, "HWA_TIMER0", "HWA_OCRA", p->hwaddr+0x29) ;
          p->HWA_OCRA_omask = 0xFF ;
        } p->HWA_OCRA_mvalue = (p->HWA_OCRA_ovalue & ~p->HWA_OCRA_mmask) | (p->HWA_OCRA_mvalue & p->HWA_OCRA_mmask) ;
      } p->HWA_OCRA_ovalue = (p->HWA_OCRA_ovalue & ~m) | (p->HWA_OCRA_mvalue & m) ;
      if ( core->commit && 0x29 != -1 ) hwa_dbg_sethr("../../attiny45/hwa_attiny45_timer0.h", 203, "HWA_TIMER0", "HWA_OCRA", sizeof(u8), p->hwaddr+0x29, p->HWA_OCRA_omask, m, p->HWA_OCRA_ovalue);
      p->HWA_OCRA_mmask &= ~m ;
      p->HWA_OCRA_omask |= m ;
    }
  } while(0);

  do {
    u8 m = p->HWA_OCRB_mmask & (-1) ;
    if ( m != 0 ) {
      if ( m != 0xFF && p->HWA_OCRB_omask != 0xFF ) {
        if ( core->commit && 0x28 != -1 ) {
          p->HWA_OCRB_ovalue = hwa_dbg_gethr("../../attiny45/hwa_attiny45_timer0.h", 204, "HWA_TIMER0", "HWA_OCRB", p->hwaddr+0x28) ;
          p->HWA_OCRB_omask = 0xFF ;
        } p->HWA_OCRB_mvalue = (p->HWA_OCRB_ovalue & ~p->HWA_OCRB_mmask) | (p->HWA_OCRB_mvalue & p->HWA_OCRB_mmask) ;
      } p->HWA_OCRB_ovalue = (p->HWA_OCRB_ovalue & ~m) | (p->HWA_OCRB_mvalue & m) ;
      if ( core->commit && 0x28 != -1 ) hwa_dbg_sethr("../../attiny45/hwa_attiny45_timer0.h", 204, "HWA_TIMER0", "HWA_OCRB", sizeof(u8), p->hwaddr+0x28, p->HWA_OCRB_omask, m, p->HWA_OCRB_ovalue);
      p->HWA_OCRB_mmask &= ~m ;
      p->HWA_OCRB_omask |= m ;
    }
  } while(0);

  do {
    u8 m = p->HWA_IFR_mmask & (-1) ;
    if ( m != 0 ) {
      if ( m != 0x1A && p->HWA_IFR_omask != 0x1A ) {
        if ( core->commit && 0x38 != -1 ) {
          p->HWA_IFR_ovalue = hwa_dbg_gethr("../../attiny45/hwa_attiny45_timer0.h", 205, "HWA_TIMER0", "HWA_IFR", p->hwaddr+0x38) ;
          p->HWA_IFR_omask = 0x1A ;
        } p->HWA_IFR_mvalue = (p->HWA_IFR_ovalue & ~p->HWA_IFR_mmask) | (p->HWA_IFR_mvalue & p->HWA_IFR_mmask) ;
      } p->HWA_IFR_ovalue = (p->HWA_IFR_ovalue & ~m) | (p->HWA_IFR_mvalue & m) ;
      if ( core->commit && 0x38 != -1 ) hwa_dbg_sethr("../../attiny45/hwa_attiny45_timer0.h", 205, "HWA_TIMER0", "HWA_IFR", sizeof(u8), p->hwaddr+0x38, p->HWA_IFR_omask, m, p->HWA_IFR_ovalue);
      p->HWA_IFR_mmask &= ~m ;
      p->HWA_IFR_omask |= m ;
    }
  } while(0);

  do {
    u8 m = p->HWA_IMSK_mmask & (-1) ;
    if ( m != 0 ) {
      if ( m != 0x1A && p->HWA_IMSK_omask != 0x1A ) {
        if ( core->commit && 0x39 != -1 ) {
          p->HWA_IMSK_ovalue = hwa_dbg_gethr("../../attiny45/hwa_attiny45_timer0.h", 206, "HWA_TIMER0", "HWA_IMSK", p->hwaddr+0x39) ;
          p->HWA_IMSK_omask = 0x1A ;
        } p->HWA_IMSK_mvalue = (p->HWA_IMSK_ovalue & ~p->HWA_IMSK_mmask) | (p->HWA_IMSK_mvalue & p->HWA_IMSK_mmask) ;
      } p->HWA_IMSK_ovalue = (p->HWA_IMSK_ovalue & ~m) | (p->HWA_IMSK_mvalue & m) ;
      if ( core->commit && 0x39 != -1 ) hwa_dbg_sethr("../../attiny45/hwa_attiny45_timer0.h", 206, "HWA_TIMER0", "HWA_IMSK", sizeof(u8), p->hwaddr+0x39, p->HWA_IMSK_omask, m, p->HWA_IMSK_ovalue);
      p->HWA_IMSK_mmask &= ~m ;
      p->HWA_IMSK_omask |= m ;
    }
  } while(0);

  p->used = 0 ;

}


// 157 "../../attiny45/hwa_attiny45_timer.h" 2
// 13 "../../attiny45/hwa_attiny45.h" 2
// 1 "../../attiny45/hwa_attiny45_usart.h" 1
// 102 "../../attiny45/hwa_attiny45_usart.h"
typedef struct
{
  intptr_t hwaddr ;
  u8 used ;
  ;

  u8 HWA_UCSRA_mmask, HWA_UCSRA_mvalue, HWA_UCSRA_omask, HWA_UCSRA_ovalue ;
  ;

  u8 HWA_UCSRB_mmask, HWA_UCSRB_mvalue, HWA_UCSRB_omask, HWA_UCSRB_ovalue ;
  ;

  u8 HWA_UCSRC_mmask, HWA_UCSRC_mvalue, HWA_UCSRC_omask, HWA_UCSRC_ovalue ;
  ;

  u16 HWA_UBRR_mmask, HWA_UBRR_mvalue, HWA_UBRR_omask, HWA_UBRR_ovalue ;
  ;

  u8 HWA_MODE_mmask, HWA_MODE_mvalue, HWA_MODE_omask, HWA_MODE_ovalue ;
  ;

  u32 HWA_BAUD_mmask, HWA_BAUD_mvalue, HWA_BAUD_omask, HWA_BAUD_ovalue ;
  ;

  u16 HWA_BAUDTOL_mmask, HWA_BAUDTOL_mvalue, HWA_BAUDTOL_omask, HWA_BAUDTOL_ovalue ;
  ;

} HWA_USART ;

// 134 "../../attiny45/hwa_attiny45_usart.h"
inline void
hwa_usart_commit ( HWA_CORE *core, HWA_USART *p )
{
  if ( !p->used )
    return ;

  u32 syshz = ((core->HWA_SYSHZ_mmask|core->HWA_SYSHZ_omask) ? core->HWA_SYSHZ_mvalue : 0);

  // 158 "../../attiny45/hwa_attiny45_usart.h"
  if ( p->HWA_BAUD_mmask ) {
    u32 baud = ((p->HWA_BAUD_mmask|p->HWA_BAUD_omask) ? p->HWA_BAUD_mvalue : 0);

    u32 baudtol = ((p->HWA_BAUDTOL_mmask|p->HWA_BAUDTOL_omask) ? p->HWA_BAUDTOL_mvalue : 0);

    u32 ubrr ;

    u8 u2x ;

    u2x = 0 ;

    ubrr = (syshz + 8 * baud) / (16 * baud);

    if ( ubrr * 16 * baud != syshz &&
    ubrr < 2048 ) {
      u2x = 1 ;

      ubrr = (syshz + 4 * baud) / (8 * baud);

    }

    if ( ubrr < 1 || ubrr > 4096 )
    do {
      extern void __attribute__((error("Usart baudrate unreachable."))) hwa_error_27(void);
      hwa_error_27();
    } while(0);

    s32 b = (syshz + ((4 * (2 - u2x) * ubrr))) / (8 * (2 - u2x) * ubrr) ;

    b = 1000 - (b * 1000 + baud/2) / baud ;

    if ( b < 0 )
      b = -b ;

    if ( (u32)b > baudtol )
    do {
      void __attribute__((noinline, warning("Usart baudrate out of tolerance."))) hwa_warn_28(void) {
        hwa_warn();
      } hwa_warn_28();
    } while(0);

    do {
      u8 mmask = (0b1) << (1) ;
      u8 vmask = (u2x) << (1) ;
      if ( (0x43 & mmask) != mmask ) do {
        extern void __attribute__((error("HWA_UCSRA" ": try to modify not writeable bits."))) hwa_error_29(void);
        hwa_error_29();
      } while(0);
      if ( (p->HWA_UCSRA_mmask & mmask) != 0 && (p->HWA_UCSRA_mvalue & mmask) != vmask ) do {
        extern void __attribute__((error("HWA_UCSRA" ": previous affectation with different value not committed."))) hwa_error_30(void);
        hwa_error_30();
      } while(0);
      if ( ((p->HWA_UCSRA_omask & mmask) == mmask && (p->HWA_UCSRA_ovalue & mmask) != vmask) || (p->HWA_UCSRA_omask & mmask) != mmask) {
        p->used = 1 ;
        p->HWA_UCSRA_mmask |= mmask ;
        p->HWA_UCSRA_mvalue = (p->HWA_UCSRA_mvalue & ~mmask) | (mmask & vmask) ;
      }
    } while(0);

    do {
      u16 mmask = (0x0FFF) << (0) ;
      u16 vmask = (ubrr-1) << (0) ;
      if ( (0x0FFF & mmask) != mmask ) do {
        extern void __attribute__((error("HWA_UBRR" ": try to modify not writeable bits."))) hwa_error_31(void);
        hwa_error_31();
      } while(0);
      if ( (p->HWA_UBRR_mmask & mmask) != 0 && (p->HWA_UBRR_mvalue & mmask) != vmask ) do {
        extern void __attribute__((error("HWA_UBRR" ": previous affectation with different value not committed."))) hwa_error_32(void);
        hwa_error_32();
      } while(0);
      if ( ((p->HWA_UBRR_omask & mmask) == mmask && (p->HWA_UBRR_ovalue & mmask) != vmask) || (p->HWA_UBRR_omask & mmask) != mmask) {
        p->used = 1 ;
        p->HWA_UBRR_mmask |= mmask ;
        p->HWA_UBRR_mvalue = (p->HWA_UBRR_mvalue & ~mmask) | (mmask & vmask) ;
      }
    } while(0);

  }

  do {
    u8 m = p->HWA_MODE_mmask & (0xFF) ;
    if ( m != 0 ) {
      if ( m != 0xFF && p->HWA_MODE_omask != 0xFF ) {
        if ( core->commit && -1 != -1 ) {
          p->HWA_MODE_ovalue = hwa_dbg_gethr("../../attiny45/hwa_attiny45_usart.h", 192, "HWA_USART", "HWA_MODE", p->hwaddr+-1) ;
          p->HWA_MODE_omask = 0xFF ;
        } p->HWA_MODE_mvalue = (p->HWA_MODE_ovalue & ~p->HWA_MODE_mmask) | (p->HWA_MODE_mvalue & p->HWA_MODE_mmask) ;
      } p->HWA_MODE_ovalue = (p->HWA_MODE_ovalue & ~m) | (p->HWA_MODE_mvalue & m) ;
      if ( core->commit && -1 != -1 ) hwa_dbg_sethr("../../attiny45/hwa_attiny45_usart.h", 192, "HWA_USART", "HWA_MODE", sizeof(u8), p->hwaddr+-1, p->HWA_MODE_omask, m, p->HWA_MODE_ovalue);
      p->HWA_MODE_mmask &= ~m ;
      p->HWA_MODE_omask |= m ;
    }
  } while(0);

  do {
    u32 m = p->HWA_BAUD_mmask & (-1) ;
    if ( m != 0 ) {
      if ( m != 0xFFFFFFFF && p->HWA_BAUD_omask != 0xFFFFFFFF ) {
        if ( core->commit && -1 != -1 ) {
          p->HWA_BAUD_ovalue = hwa_dbg_gethr("../../attiny45/hwa_attiny45_usart.h", 193, "HWA_USART", "HWA_BAUD", p->hwaddr+-1) ;
          p->HWA_BAUD_omask = 0xFFFFFFFF ;
        } p->HWA_BAUD_mvalue = (p->HWA_BAUD_ovalue & ~p->HWA_BAUD_mmask) | (p->HWA_BAUD_mvalue & p->HWA_BAUD_mmask) ;
      } p->HWA_BAUD_ovalue = (p->HWA_BAUD_ovalue & ~m) | (p->HWA_BAUD_mvalue & m) ;
      if ( core->commit && -1 != -1 ) hwa_dbg_sethr("../../attiny45/hwa_attiny45_usart.h", 193, "HWA_USART", "HWA_BAUD", sizeof(u32), p->hwaddr+-1, p->HWA_BAUD_omask, m, p->HWA_BAUD_ovalue);
      p->HWA_BAUD_mmask &= ~m ;
      p->HWA_BAUD_omask |= m ;
    }
  } while(0);

  do {
    u16 m = p->HWA_BAUDTOL_mmask & (-1) ;
    if ( m != 0 ) {
      if ( m != 0xFFFF && p->HWA_BAUDTOL_omask != 0xFFFF ) {
        if ( core->commit && -1 != -1 ) {
          p->HWA_BAUDTOL_ovalue = hwa_dbg_gethr("../../attiny45/hwa_attiny45_usart.h", 194, "HWA_USART", "HWA_BAUDTOL", p->hwaddr+-1) ;
          p->HWA_BAUDTOL_omask = 0xFFFF ;
        } p->HWA_BAUDTOL_mvalue = (p->HWA_BAUDTOL_ovalue & ~p->HWA_BAUDTOL_mmask) | (p->HWA_BAUDTOL_mvalue & p->HWA_BAUDTOL_mmask) ;
      } p->HWA_BAUDTOL_ovalue = (p->HWA_BAUDTOL_ovalue & ~m) | (p->HWA_BAUDTOL_mvalue & m) ;
      if ( core->commit && -1 != -1 ) hwa_dbg_sethr("../../attiny45/hwa_attiny45_usart.h", 194, "HWA_USART", "HWA_BAUDTOL", sizeof(u16), p->hwaddr+-1, p->HWA_BAUDTOL_omask, m, p->HWA_BAUDTOL_ovalue);
      p->HWA_BAUDTOL_mmask &= ~m ;
      p->HWA_BAUDTOL_omask |= m ;
    }
  } while(0);

  do {
    u8 m = p->HWA_UCSRA_mmask & (-1) ;
    if ( m != 0 ) {
      if ( m != 0x43 && p->HWA_UCSRA_omask != 0x43 ) {
        if ( core->commit && 0x00 != -1 ) {
          p->HWA_UCSRA_ovalue = hwa_dbg_gethr("../../attiny45/hwa_attiny45_usart.h", 196, "HWA_USART", "HWA_UCSRA", p->hwaddr+0x00) ;
          p->HWA_UCSRA_omask = 0x43 ;
        } p->HWA_UCSRA_mvalue = (p->HWA_UCSRA_ovalue & ~p->HWA_UCSRA_mmask) | (p->HWA_UCSRA_mvalue & p->HWA_UCSRA_mmask) ;
      } p->HWA_UCSRA_ovalue = (p->HWA_UCSRA_ovalue & ~m) | (p->HWA_UCSRA_mvalue & m) ;
      if ( core->commit && 0x00 != -1 ) hwa_dbg_sethr("../../attiny45/hwa_attiny45_usart.h", 196, "HWA_USART", "HWA_UCSRA", sizeof(u8), p->hwaddr+0x00, p->HWA_UCSRA_omask, m, p->HWA_UCSRA_ovalue);
      p->HWA_UCSRA_mmask &= ~m ;
      p->HWA_UCSRA_omask |= m ;
    }
  } while(0);

  do {
    u8 m = p->HWA_UCSRB_mmask & (-1) ;
    if ( m != 0 ) {
      if ( m != 0xFD && p->HWA_UCSRB_omask != 0xFD ) {
        if ( core->commit && 0x01 != -1 ) {
          p->HWA_UCSRB_ovalue = hwa_dbg_gethr("../../attiny45/hwa_attiny45_usart.h", 197, "HWA_USART", "HWA_UCSRB", p->hwaddr+0x01) ;
          p->HWA_UCSRB_omask = 0xFD ;
        } p->HWA_UCSRB_mvalue = (p->HWA_UCSRB_ovalue & ~p->HWA_UCSRB_mmask) | (p->HWA_UCSRB_mvalue & p->HWA_UCSRB_mmask) ;
      } p->HWA_UCSRB_ovalue = (p->HWA_UCSRB_ovalue & ~m) | (p->HWA_UCSRB_mvalue & m) ;
      if ( core->commit && 0x01 != -1 ) hwa_dbg_sethr("../../attiny45/hwa_attiny45_usart.h", 197, "HWA_USART", "HWA_UCSRB", sizeof(u8), p->hwaddr+0x01, p->HWA_UCSRB_omask, m, p->HWA_UCSRB_ovalue);
      p->HWA_UCSRB_mmask &= ~m ;
      p->HWA_UCSRB_omask |= m ;
    }
  } while(0);

  do {
    u8 m = p->HWA_UCSRC_mmask & (-1) ;
    if ( m != 0 ) {
      if ( m != 0xFF && p->HWA_UCSRC_omask != 0xFF ) {
        if ( core->commit && 0x02 != -1 ) {
          p->HWA_UCSRC_ovalue = hwa_dbg_gethr("../../attiny45/hwa_attiny45_usart.h", 198, "HWA_USART", "HWA_UCSRC", p->hwaddr+0x02) ;
          p->HWA_UCSRC_omask = 0xFF ;
        } p->HWA_UCSRC_mvalue = (p->HWA_UCSRC_ovalue & ~p->HWA_UCSRC_mmask) | (p->HWA_UCSRC_mvalue & p->HWA_UCSRC_mmask) ;
      } p->HWA_UCSRC_ovalue = (p->HWA_UCSRC_ovalue & ~m) | (p->HWA_UCSRC_mvalue & m) ;
      if ( core->commit && 0x02 != -1 ) hwa_dbg_sethr("../../attiny45/hwa_attiny45_usart.h", 198, "HWA_USART", "HWA_UCSRC", sizeof(u8), p->hwaddr+0x02, p->HWA_UCSRC_omask, m, p->HWA_UCSRC_ovalue);
      p->HWA_UCSRC_mmask &= ~m ;
      p->HWA_UCSRC_omask |= m ;
    }
  } while(0);

  do {
    u16 m = p->HWA_UBRR_mmask & (-1) ;
    if ( m != 0 ) {
      if ( m != 0x0FFF && p->HWA_UBRR_omask != 0x0FFF ) {
        if ( core->commit && 0x04 != -1 ) {
          p->HWA_UBRR_ovalue = hwa_dbg_gethr("../../attiny45/hwa_attiny45_usart.h", 199, "HWA_USART", "HWA_UBRR", p->hwaddr+0x04) ;
          p->HWA_UBRR_omask = 0x0FFF ;
        } p->HWA_UBRR_mvalue = (p->HWA_UBRR_ovalue & ~p->HWA_UBRR_mmask) | (p->HWA_UBRR_mvalue & p->HWA_UBRR_mmask) ;
      } p->HWA_UBRR_ovalue = (p->HWA_UBRR_ovalue & ~m) | (p->HWA_UBRR_mvalue & m) ;
      if ( core->commit && 0x04 != -1 ) hwa_dbg_sethr("../../attiny45/hwa_attiny45_usart.h", 199, "HWA_USART", "HWA_UBRR", sizeof(u16), p->hwaddr+0x04, p->HWA_UBRR_omask, m, p->HWA_UBRR_ovalue);
      p->HWA_UBRR_mmask &= ~m ;
      p->HWA_UBRR_omask |= m ;
    }
  } while(0);

  p->used = 0 ;

}


// 14 "../../attiny45/hwa_attiny45.h" 2
// 1 "../../attiny45/hwa_attiny45_adc.h" 1
// 81 "../../attiny45/hwa_attiny45_adc.h"
typedef struct
{
  intptr_t hwaddr ;
  u8 used ;
  ;

  u8 HWA_ADMUX_mmask, HWA_ADMUX_mvalue, HWA_ADMUX_omask, HWA_ADMUX_ovalue ;
  ;

  u8 HWA_ADCSRA_mmask, HWA_ADCSRA_mvalue, HWA_ADCSRA_omask, HWA_ADCSRA_ovalue ;
  ;

  u8 HWA_ADCSRB_mmask, HWA_ADCSRB_mvalue, HWA_ADCSRB_omask, HWA_ADCSRB_ovalue ;
  ;

  u8 HWA_DIDR0_mmask, HWA_DIDR0_mvalue, HWA_DIDR0_omask, HWA_DIDR0_ovalue ;
  ;

  u32 HWA_SPS_mmask, HWA_SPS_mvalue, HWA_SPS_omask, HWA_SPS_ovalue ;
  ;

} HWA_ADC ;

// 105 "../../attiny45/hwa_attiny45_adc.h"
inline void
hwa_adc_commit ( HWA_CORE *core, HWA_ADC *p )
{
  if ( !p->used )
    return ;

  u32 syshz = ((core->HWA_SYSHZ_mmask|core->HWA_SYSHZ_omask) ? core->HWA_SYSHZ_mvalue : 0) ;

  u32 adhz = 0 ;

  u32 sps = ((p->HWA_SPS_mmask|p->HWA_SPS_omask) ? p->HWA_SPS_mvalue : 0);

  if ( p->HWA_SPS_mmask || sps==0 ) {
    // 124 "../../attiny45/hwa_attiny45_adc.h"
    if ( sps == 0 )
      adhz = 50000 ;

    else
      adhz = 13 * sps ;

    u32 psc = syshz / adhz ;

    s8 l2 = hwa_log2_ceil(psc);

    if ( l2<2 ) l2 = 2 ;

    if ( l2>7 ) l2 = 7 ;

    psc = 1<<l2 ;

    adhz = syshz / psc ;

    if ( (adhz < 50000 || adhz > 1000000) )
    do {
      extern void __attribute__((error("ADC clock frequency out of 50..1000 kHz."))) hwa_error_33(void);
      hwa_error_33();
    } while(0);

    if ( sps == 0 ) {
      sps = adhz / 13 ;

      do {
        u32 mmask = (-1) << (0) ;
        u32 vmask = (sps) << (0) ;
        if ( (0xFFFFFFFF & mmask) != mmask ) do {
          extern void __attribute__((error("HWA_SPS" ": try to modify not writeable bits."))) hwa_error_34(void);
          hwa_error_34();
        } while(0);
        if ( (p->HWA_SPS_mmask & mmask) != 0 && (p->HWA_SPS_mvalue & mmask) != vmask ) do {
          extern void __attribute__((error("HWA_SPS" ": previous affectation with different value not committed."))) hwa_error_35(void);
          hwa_error_35();
        } while(0);
        if ( ((p->HWA_SPS_omask & mmask) == mmask && (p->HWA_SPS_ovalue & mmask) != vmask) || (p->HWA_SPS_omask & mmask) != mmask) {
          p->used = 1 ;
          p->HWA_SPS_mmask |= mmask ;
          p->HWA_SPS_mvalue = (p->HWA_SPS_mvalue & ~mmask) | (mmask & vmask) ;
        }
      } while(0);

    }

    do {
      u8 mmask = (0b111) << (0) ;
      u8 vmask = (l2) << (0) ;
      if ( (0xFF & mmask) != mmask ) do {
        extern void __attribute__((error("HWA_ADCSRA" ": try to modify not writeable bits."))) hwa_error_36(void);
        hwa_error_36();
      } while(0);
      if ( (p->HWA_ADCSRA_mmask & mmask) != 0 && (p->HWA_ADCSRA_mvalue & mmask) != vmask ) do {
        extern void __attribute__((error("HWA_ADCSRA" ": previous affectation with different value not committed."))) hwa_error_37(void);
        hwa_error_37();
      } while(0);
      if ( ((p->HWA_ADCSRA_omask & mmask) == mmask && (p->HWA_ADCSRA_ovalue & mmask) != vmask) || (p->HWA_ADCSRA_omask & mmask) != mmask) {
        p->used = 1 ;
        p->HWA_ADCSRA_mmask |= mmask ;
        p->HWA_ADCSRA_mvalue = (p->HWA_ADCSRA_mvalue & ~mmask) | (mmask & vmask) ;
      }
    } while(0);

  }

  do {
    u32 m = p->HWA_SPS_mmask & (-1) ;
    if ( m != 0 ) {
      if ( m != 0xFFFFFFFF && p->HWA_SPS_omask != 0xFFFFFFFF ) {
        if ( core->commit && -1 != -1 ) {
          p->HWA_SPS_ovalue = hwa_dbg_gethr("../../attiny45/hwa_attiny45_adc.h", 154, "HWA_ADC", "HWA_SPS", p->hwaddr+-1) ;
          p->HWA_SPS_omask = 0xFFFFFFFF ;
        } p->HWA_SPS_mvalue = (p->HWA_SPS_ovalue & ~p->HWA_SPS_mmask) | (p->HWA_SPS_mvalue & p->HWA_SPS_mmask) ;
      } p->HWA_SPS_ovalue = (p->HWA_SPS_ovalue & ~m) | (p->HWA_SPS_mvalue & m) ;
      if ( core->commit && -1 != -1 ) hwa_dbg_sethr("../../attiny45/hwa_attiny45_adc.h", 154, "HWA_ADC", "HWA_SPS", sizeof(u32), p->hwaddr+-1, p->HWA_SPS_omask, m, p->HWA_SPS_ovalue);
      p->HWA_SPS_mmask &= ~m ;
      p->HWA_SPS_omask |= m ;
    }
  } while(0);

  do {
    u8 m = p->HWA_ADMUX_mmask & (-1) ;
    if ( m != 0 ) {
      if ( m != 0xEF && p->HWA_ADMUX_omask != 0xEF ) {
        if ( core->commit && 0x7C != -1 ) {
          p->HWA_ADMUX_ovalue = hwa_dbg_gethr("../../attiny45/hwa_attiny45_adc.h", 156, "HWA_ADC", "HWA_ADMUX", p->hwaddr+0x7C) ;
          p->HWA_ADMUX_omask = 0xEF ;
        } p->HWA_ADMUX_mvalue = (p->HWA_ADMUX_ovalue & ~p->HWA_ADMUX_mmask) | (p->HWA_ADMUX_mvalue & p->HWA_ADMUX_mmask) ;
      } p->HWA_ADMUX_ovalue = (p->HWA_ADMUX_ovalue & ~m) | (p->HWA_ADMUX_mvalue & m) ;
      if ( core->commit && 0x7C != -1 ) hwa_dbg_sethr("../../attiny45/hwa_attiny45_adc.h", 156, "HWA_ADC", "HWA_ADMUX", sizeof(u8), p->hwaddr+0x7C, p->HWA_ADMUX_omask, m, p->HWA_ADMUX_ovalue);
      p->HWA_ADMUX_mmask &= ~m ;
      p->HWA_ADMUX_omask |= m ;
    }
  } while(0);

  do {
    u8 m = p->HWA_ADCSRA_mmask & (-1) ;
    if ( m != 0 ) {
      if ( m != 0xFF && p->HWA_ADCSRA_omask != 0xFF ) {
        if ( core->commit && 0x7A != -1 ) {
          p->HWA_ADCSRA_ovalue = hwa_dbg_gethr("../../attiny45/hwa_attiny45_adc.h", 157, "HWA_ADC", "HWA_ADCSRA", p->hwaddr+0x7A) ;
          p->HWA_ADCSRA_omask = 0xFF ;
        } p->HWA_ADCSRA_mvalue = (p->HWA_ADCSRA_ovalue & ~p->HWA_ADCSRA_mmask) | (p->HWA_ADCSRA_mvalue & p->HWA_ADCSRA_mmask) ;
      } p->HWA_ADCSRA_ovalue = (p->HWA_ADCSRA_ovalue & ~m) | (p->HWA_ADCSRA_mvalue & m) ;
      if ( core->commit && 0x7A != -1 ) hwa_dbg_sethr("../../attiny45/hwa_attiny45_adc.h", 157, "HWA_ADC", "HWA_ADCSRA", sizeof(u8), p->hwaddr+0x7A, p->HWA_ADCSRA_omask, m, p->HWA_ADCSRA_ovalue);
      p->HWA_ADCSRA_mmask &= ~m ;
      p->HWA_ADCSRA_omask |= m ;
    }
  } while(0);

  do {
    u8 m = p->HWA_ADCSRB_mmask & (-1) ;
    if ( m != 0 ) {
      if ( m != 0x47 && p->HWA_ADCSRB_omask != 0x47 ) {
        if ( core->commit && 0x7B != -1 ) {
          p->HWA_ADCSRB_ovalue = hwa_dbg_gethr("../../attiny45/hwa_attiny45_adc.h", 158, "HWA_ADC", "HWA_ADCSRB", p->hwaddr+0x7B) ;
          p->HWA_ADCSRB_omask = 0x47 ;
        } p->HWA_ADCSRB_mvalue = (p->HWA_ADCSRB_ovalue & ~p->HWA_ADCSRB_mmask) | (p->HWA_ADCSRB_mvalue & p->HWA_ADCSRB_mmask) ;
      } p->HWA_ADCSRB_ovalue = (p->HWA_ADCSRB_ovalue & ~m) | (p->HWA_ADCSRB_mvalue & m) ;
      if ( core->commit && 0x7B != -1 ) hwa_dbg_sethr("../../attiny45/hwa_attiny45_adc.h", 158, "HWA_ADC", "HWA_ADCSRB", sizeof(u8), p->hwaddr+0x7B, p->HWA_ADCSRB_omask, m, p->HWA_ADCSRB_ovalue);
      p->HWA_ADCSRB_mmask &= ~m ;
      p->HWA_ADCSRB_omask |= m ;
    }
  } while(0);

  do {
    u8 m = p->HWA_DIDR0_mmask & (-1) ;
    if ( m != 0 ) {
      if ( m != 0x3F && p->HWA_DIDR0_omask != 0x3F ) {
        if ( core->commit && 0x7E != -1 ) {
          p->HWA_DIDR0_ovalue = hwa_dbg_gethr("../../attiny45/hwa_attiny45_adc.h", 159, "HWA_ADC", "HWA_DIDR0", p->hwaddr+0x7E) ;
          p->HWA_DIDR0_omask = 0x3F ;
        } p->HWA_DIDR0_mvalue = (p->HWA_DIDR0_ovalue & ~p->HWA_DIDR0_mmask) | (p->HWA_DIDR0_mvalue & p->HWA_DIDR0_mmask) ;
      } p->HWA_DIDR0_ovalue = (p->HWA_DIDR0_ovalue & ~m) | (p->HWA_DIDR0_mvalue & m) ;
      if ( core->commit && 0x7E != -1 ) hwa_dbg_sethr("../../attiny45/hwa_attiny45_adc.h", 159, "HWA_ADC", "HWA_DIDR0", sizeof(u8), p->hwaddr+0x7E, p->HWA_DIDR0_omask, m, p->HWA_DIDR0_ovalue);
      p->HWA_DIDR0_mmask &= ~m ;
      p->HWA_DIDR0_omask |= m ;
    }
  } while(0);

  p->used = 0 ;

}


// 240 "../../attiny45/hwa_attiny45_adc.h"
inline u32 hwa_adc_get_sps_(HWA_CORE *c, HWA_ADC *p)
{
  u32 syshz = ((c->HWA_SYSHZ_mmask|c->HWA_SYSHZ_omask) ? c->HWA_SYSHZ_mvalue : 0) ;

  u8 adpsc = 1 << (((p->HWA_ADCSRA_ovalue) & ((0b111)<<(0))) >> (0));

  u32 adhz = syshz / adpsc ;

  return adhz/13 ;

}


// 15 "../../attiny45/hwa_attiny45.h" 2
// 1 "../../attiny45/hwa_attiny45_acmp.h" 1
// 64 "../../attiny45/hwa_attiny45_acmp.h"
typedef struct
{
  intptr_t hwaddr ;
  u8 used ;

  u8 HWA_CONNECT_NEG_mmask, HWA_CONNECT_NEG_mvalue, HWA_CONNECT_NEG_omask, HWA_CONNECT_NEG_ovalue ;

  u8 HWA_CONNECT_POS_mmask, HWA_CONNECT_POS_mvalue, HWA_CONNECT_POS_omask, HWA_CONNECT_POS_ovalue ;

} HWA_ACMP ;

// 83 "../../attiny45/hwa_attiny45_acmp.h"
inline void hwa_acmp_commit ( HWA_CORE *core, HWA_ACMP *p )
{
  if ( p->HWA_CONNECT_NEG_mmask ) {
    u8 con_neg = p->HWA_CONNECT_NEG_mvalue;

    if ( con_neg & 0x10 )
    do {
      u8 mmask = (0b11) << (0) ;
      u8 vmask = (con_neg & 0x03) << (0) ;
      if ( (0xDB & mmask) != mmask ) do {
        extern void __attribute__((error("HWA_ACSR" ": try to modify not writeable bits."))) hwa_error_38(void);
        hwa_error_38();
      } while(0);
      if ( (core->HWA_ACSR_mmask & mmask) != 0 && (core->HWA_ACSR_mvalue & mmask) != vmask ) do {
        extern void __attribute__((error("HWA_ACSR" ": previous affectation with different value not committed."))) hwa_error_39(void);
        hwa_error_39();
      } while(0);
      if ( ((core->HWA_ACSR_omask & mmask) == mmask && (core->HWA_ACSR_ovalue & mmask) != vmask) || (core->HWA_ACSR_omask & mmask) != mmask) {
        core->used = 1 ;
        core->HWA_ACSR_mmask |= mmask ;
        core->HWA_ACSR_mvalue = (core->HWA_ACSR_mvalue & ~mmask) | (mmask & vmask) ;
      }
    } while(0);

    else {

      u8 acme = (((core->HWA_ADCSRB_mmask|core->HWA_ADCSRB_omask) & ((0b1)<<(6))) ? (core->HWA_ADCSRB_mvalue & ((0b1)<<(6))) >> (6) : -1) ;

      if ( acme == 1 )
      do {
        u8 mmask = (0b1) << (7) ;
        u8 vmask = (1) << (7) ;
        if ( (0x40 & mmask) != mmask ) do {
          extern void __attribute__((error("HWA_ADCSRB" ": try to modify not writeable bits."))) hwa_error_40(void);
          hwa_error_40();
        } while(0);
        if ( (core->HWA_ADCSRB_mmask & mmask) != 0 && (core->HWA_ADCSRB_mvalue & mmask) != vmask ) do {
          extern void __attribute__((error("HWA_ADCSRB" ": previous affectation with different value not committed."))) hwa_error_41(void);
          hwa_error_41();
        } while(0);
        if ( ((core->HWA_ADCSRB_omask & mmask) == mmask && (core->HWA_ADCSRB_ovalue & mmask) != vmask) || (core->HWA_ADCSRB_omask & mmask) != mmask) {
          core->used = 1 ;
          core->HWA_ADCSRB_mmask |= mmask ;
          core->HWA_ADCSRB_mvalue = (core->HWA_ADCSRB_mvalue & ~mmask) | (mmask & vmask) ;
        }
      } while(0);

      do {
        u8 mmask = (0b1) << (1) ;
        u8 vmask = (1) << (1) ;
        if ( (0x3F & mmask) != mmask ) do {
          extern void __attribute__((error("HWA_DIDR0" ": try to modify not writeable bits."))) hwa_error_42(void);
          hwa_error_42();
        } while(0);
        if ( (core->HWA_DIDR0_mmask & mmask) != 0 && (core->HWA_DIDR0_mvalue & mmask) != vmask ) do {
          extern void __attribute__((error("HWA_DIDR0" ": previous affectation with different value not committed."))) hwa_error_43(void);
          hwa_error_43();
        } while(0);
        if ( ((core->HWA_DIDR0_omask & mmask) == mmask && (core->HWA_DIDR0_ovalue & mmask) != vmask) || (core->HWA_DIDR0_omask & mmask) != mmask) {
          core->used = 1 ;
          core->HWA_DIDR0_mmask |= mmask ;
          core->HWA_DIDR0_mvalue = (core->HWA_DIDR0_mvalue & ~mmask) | (mmask & vmask) ;
        }
      } while(0);

    }
  }

  if ( p->HWA_CONNECT_POS_mmask ) {
    u8 con = p->HWA_CONNECT_POS_mvalue;

    if ( con == 1 )
    do {
      u8 mmask = (0b1) << (6) ;
      u8 vmask = (0) << (6) ;
      if ( (0xDB & mmask) != mmask ) do {
        extern void __attribute__((error("HWA_ACSR" ": try to modify not writeable bits."))) hwa_error_44(void);
        hwa_error_44();
      } while(0);
      if ( (core->HWA_ACSR_mmask & mmask) != 0 && (core->HWA_ACSR_mvalue & mmask) != vmask ) do {
        extern void __attribute__((error("HWA_ACSR" ": previous affectation with different value not committed."))) hwa_error_45(void);
        hwa_error_45();
      } while(0);
      if ( ((core->HWA_ACSR_omask & mmask) == mmask && (core->HWA_ACSR_ovalue & mmask) != vmask) || (core->HWA_ACSR_omask & mmask) != mmask) {
        core->used = 1 ;
        core->HWA_ACSR_mmask |= mmask ;
        core->HWA_ACSR_mvalue = (core->HWA_ACSR_mvalue & ~mmask) | (mmask & vmask) ;
      }
    } while(0);

    else
    do {
      u8 mmask = (0b1) << (6) ;
      u8 vmask = (1) << (6) ;
      if ( (0xDB & mmask) != mmask ) do {
        extern void __attribute__((error("HWA_ACSR" ": try to modify not writeable bits."))) hwa_error_46(void);
        hwa_error_46();
      } while(0);
      if ( (core->HWA_ACSR_mmask & mmask) != 0 && (core->HWA_ACSR_mvalue & mmask) != vmask ) do {
        extern void __attribute__((error("HWA_ACSR" ": previous affectation with different value not committed."))) hwa_error_47(void);
        hwa_error_47();
      } while(0);
      if ( ((core->HWA_ACSR_omask & mmask) == mmask && (core->HWA_ACSR_ovalue & mmask) != vmask) || (core->HWA_ACSR_omask & mmask) != mmask) {
        core->used = 1 ;
        core->HWA_ACSR_mmask |= mmask ;
        core->HWA_ACSR_mvalue = (core->HWA_ACSR_mvalue & ~mmask) | (mmask & vmask) ;
      }
    } while(0);

  }

  do {
    u8 m = p->HWA_CONNECT_NEG_mmask & (-1) ;
    if ( m != 0 ) {
      if ( m != 0xFF && p->HWA_CONNECT_NEG_omask != 0xFF ) {
        if ( core->commit && -1 != -1 ) {
          p->HWA_CONNECT_NEG_ovalue = hwa_dbg_gethr("../../attiny45/hwa_attiny45_acmp.h", 112, "HWA_ACMP", "HWA_CONNECT_NEG", p->hwaddr+-1) ;
          p->HWA_CONNECT_NEG_omask = 0xFF ;
        } p->HWA_CONNECT_NEG_mvalue = (p->HWA_CONNECT_NEG_ovalue & ~p->HWA_CONNECT_NEG_mmask) | (p->HWA_CONNECT_NEG_mvalue & p->HWA_CONNECT_NEG_mmask) ;
      } p->HWA_CONNECT_NEG_ovalue = (p->HWA_CONNECT_NEG_ovalue & ~m) | (p->HWA_CONNECT_NEG_mvalue & m) ;
      if ( core->commit && -1 != -1 ) hwa_dbg_sethr("../../attiny45/hwa_attiny45_acmp.h", 112, "HWA_ACMP", "HWA_CONNECT_NEG", sizeof(u8), p->hwaddr+-1, p->HWA_CONNECT_NEG_omask, m, p->HWA_CONNECT_NEG_ovalue);
      p->HWA_CONNECT_NEG_mmask &= ~m ;
      p->HWA_CONNECT_NEG_omask |= m ;
    }
  } while(0);

  do {
    u8 m = p->HWA_CONNECT_POS_mmask & (-1) ;
    if ( m != 0 ) {
      if ( m != 0xFF && p->HWA_CONNECT_POS_omask != 0xFF ) {
        if ( core->commit && -1 != -1 ) {
          p->HWA_CONNECT_POS_ovalue = hwa_dbg_gethr("../../attiny45/hwa_attiny45_acmp.h", 113, "HWA_ACMP", "HWA_CONNECT_POS", p->hwaddr+-1) ;
          p->HWA_CONNECT_POS_omask = 0xFF ;
        } p->HWA_CONNECT_POS_mvalue = (p->HWA_CONNECT_POS_ovalue & ~p->HWA_CONNECT_POS_mmask) | (p->HWA_CONNECT_POS_mvalue & p->HWA_CONNECT_POS_mmask) ;
      } p->HWA_CONNECT_POS_ovalue = (p->HWA_CONNECT_POS_ovalue & ~m) | (p->HWA_CONNECT_POS_mvalue & m) ;
      if ( core->commit && -1 != -1 ) hwa_dbg_sethr("../../attiny45/hwa_attiny45_acmp.h", 113, "HWA_ACMP", "HWA_CONNECT_POS", sizeof(u8), p->hwaddr+-1, p->HWA_CONNECT_POS_omask, m, p->HWA_CONNECT_POS_ovalue);
      p->HWA_CONNECT_POS_mmask &= ~m ;
      p->HWA_CONNECT_POS_omask |= m ;
    }
  } while(0);

}


// 16 "../../attiny45/hwa_attiny45.h" 2
// 1 "../../attiny45/hwa_attiny45_exti.h" 1
// 17 "../../attiny45/hwa_attiny45.h" 2
// 1 "../../attiny45/hwa_attiny45_pchg.h" 1
// 15 "../../attiny45/hwa_attiny45_pchg.h"
typedef struct
{
  u8 commit ;

  intptr_t hwaddr ;
  u8 used ;

  u8 HWA_PCMSK_mmask, HWA_PCMSK_mvalue, HWA_PCMSK_omask, HWA_PCMSK_ovalue ;

} HWA_PCHG ;

// 31 "../../attiny45/hwa_attiny45_pchg.h"
inline void hwa_pchg_commit ( HWA_CORE *core, HWA_PCHG *p )
{
  do {
    u8 m = p->HWA_PCMSK_mmask & (-1) ;
    if ( m != 0 ) {
      if ( m != 0x3F && p->HWA_PCMSK_omask != 0x3F ) {
        if ( core->commit && 0x15 != -1 ) {
          p->HWA_PCMSK_ovalue = hwa_dbg_gethr("../../attiny45/hwa_attiny45_pchg.h", 33, "HWA_PCHG", "HWA_PCMSK", p->hwaddr+0x15) ;
          p->HWA_PCMSK_omask = 0x3F ;
        } p->HWA_PCMSK_mvalue = (p->HWA_PCMSK_ovalue & ~p->HWA_PCMSK_mmask) | (p->HWA_PCMSK_mvalue & p->HWA_PCMSK_mmask) ;
      } p->HWA_PCMSK_ovalue = (p->HWA_PCMSK_ovalue & ~m) | (p->HWA_PCMSK_mvalue & m) ;
      if ( core->commit && 0x15 != -1 ) hwa_dbg_sethr("../../attiny45/hwa_attiny45_pchg.h", 33, "HWA_PCHG", "HWA_PCMSK", sizeof(u8), p->hwaddr+0x15, p->HWA_PCMSK_omask, m, p->HWA_PCMSK_ovalue);
      p->HWA_PCMSK_mmask &= ~m ;
      p->HWA_PCMSK_omask |= m ;
    }
  } while(0);

}


// 18 "../../attiny45/hwa_attiny45.h" 2
// 1 "../../attiny45/hwa_attiny45_watchdog.h" 1
// 19 "../../attiny45/hwa_attiny45.h" 2
// 480 "../../hwa.h" 2
// 3 "test.c" 2

int main ( int ac __attribute__((unused)), char **av __attribute__((unused)))
{
  // 30 "test.c"
  do {
    u8 mmask = (-1) << (0) ;
    u8 vmask = (1) << (0) ;
    if ( (0xFF & mmask) != mmask ) do {
      extern void __attribute__((error("HWA_MODE" ": try to modify not writeable bits."))) hwa_error_48(void);
      hwa_error_48();
    } while(0);
    if ( (HWA_TIMER0->HWA_MODE_mmask & mmask) != 0 && (HWA_TIMER0->HWA_MODE_mvalue & mmask) != vmask ) do {
      extern void __attribute__((error("HWA_MODE" ": previous affectation with different value not committed."))) hwa_error_49(void);
      hwa_error_49();
    } while(0);
    if ( ((HWA_TIMER0->HWA_MODE_omask & mmask) == mmask && (HWA_TIMER0->HWA_MODE_ovalue & mmask) != vmask) || (HWA_TIMER0->HWA_MODE_omask & mmask) != mmask) {
      HWA_TIMER0->used = 1 ;
      HWA_TIMER0->HWA_MODE_mmask |= mmask ;
      HWA_TIMER0->HWA_MODE_mvalue = (HWA_TIMER0->HWA_MODE_mvalue & ~mmask) | (mmask & vmask) ;
    }
  } while(0);

  do {
    do {
      u8 mmask = (-1) << (0) ;
      u8 vmask = (2) << (0) ;
      if ( (0xFF & mmask) != mmask ) do {
        extern void __attribute__((error("HWA_CLK" ": try to modify not writeable bits."))) hwa_error_50(void);
        hwa_error_50();
      } while(0);
      if ( (HWA_TIMER0->HWA_CLK_mmask & mmask) != 0 && (HWA_TIMER0->HWA_CLK_mvalue & mmask) != vmask ) do {
        extern void __attribute__((error("HWA_CLK" ": previous affectation with different value not committed."))) hwa_error_51(void);
        hwa_error_51();
      } while(0);
      if ( ((HWA_TIMER0->HWA_CLK_omask & mmask) == mmask && (HWA_TIMER0->HWA_CLK_ovalue & mmask) != vmask) || (HWA_TIMER0->HWA_CLK_omask & mmask) != mmask) {
        HWA_TIMER0->used = 1 ;
        HWA_TIMER0->HWA_CLK_mmask |= mmask ;
        HWA_TIMER0->HWA_CLK_mvalue = (HWA_TIMER0->HWA_CLK_mvalue & ~mmask) | (mmask & vmask) ;
      }
    } while(0);
    do {
      u32 mmask = (-1) << (0) ;
      u32 vmask = (16000000/8) << (0) ;
      if ( (0xFFFFFFFF & mmask) != mmask ) do {
        extern void __attribute__((error("HWA_CLKHZ" ": try to modify not writeable bits."))) hwa_error_52(void);
        hwa_error_52();
      } while(0);
      if ( (HWA_TIMER0->HWA_CLKHZ_mmask & mmask) != 0 && (HWA_TIMER0->HWA_CLKHZ_mvalue & mmask) != vmask ) do {
        extern void __attribute__((error("HWA_CLKHZ" ": previous affectation with different value not committed."))) hwa_error_53(void);
        hwa_error_53();
      } while(0);
      if ( ((HWA_TIMER0->HWA_CLKHZ_omask & mmask) == mmask && (HWA_TIMER0->HWA_CLKHZ_ovalue & mmask) != vmask) || (HWA_TIMER0->HWA_CLKHZ_omask & mmask) != mmask) {
        HWA_TIMER0->used = 1 ;
        HWA_TIMER0->HWA_CLKHZ_mmask |= mmask ;
        HWA_TIMER0->HWA_CLKHZ_mvalue = (HWA_TIMER0->HWA_CLKHZ_mvalue & ~mmask) | (mmask & vmask) ;
      }
    } while(0);
  } while(0);

  do {
    do {
      u32 mmask = (-1) << (0) ;
      u32 vmask = (0) << (0) ;
      if ( (0xFFFFFFFF & mmask) != mmask ) do {
        extern void __attribute__((error("HWA_HZ" ": try to modify not writeable bits."))) hwa_error_54(void);
        hwa_error_54();
      } while(0);
      if ( (HWA_TIMER0->HWA_HZ_mmask & mmask) != 0 && (HWA_TIMER0->HWA_HZ_mvalue & mmask) != vmask ) do {
        extern void __attribute__((error("HWA_HZ" ": previous affectation with different value not committed."))) hwa_error_55(void);
        hwa_error_55();
      } while(0);
      if ( ((HWA_TIMER0->HWA_HZ_omask & mmask) == mmask && (HWA_TIMER0->HWA_HZ_ovalue & mmask) != vmask) || (HWA_TIMER0->HWA_HZ_omask & mmask) != mmask) {
        HWA_TIMER0->used = 1 ;
        HWA_TIMER0->HWA_HZ_mmask |= mmask ;
        HWA_TIMER0->HWA_HZ_mvalue = (HWA_TIMER0->HWA_HZ_mvalue & ~mmask) | (mmask & vmask) ;
      }
    } while(0);
    do {
      u32 mmask = (-1) << (0) ;
      u32 vmask = (65000) << (0) ;
      if ( (0xFFFFFFFF & mmask) != mmask ) do {
        extern void __attribute__((error("HWA_PERIOD" ": try to modify not writeable bits."))) hwa_error_56(void);
        hwa_error_56();
      } while(0);
      if ( (HWA_TIMER0->HWA_PERIOD_mmask & mmask) != 0 && (HWA_TIMER0->HWA_PERIOD_mvalue & mmask) != vmask ) do {
        extern void __attribute__((error("HWA_PERIOD" ": previous affectation with different value not committed."))) hwa_error_57(void);
        hwa_error_57();
      } while(0);
      if ( ((HWA_TIMER0->HWA_PERIOD_omask & mmask) == mmask && (HWA_TIMER0->HWA_PERIOD_ovalue & mmask) != vmask) || (HWA_TIMER0->HWA_PERIOD_omask & mmask) != mmask) {
        HWA_TIMER0->used = 1 ;
        HWA_TIMER0->HWA_PERIOD_mmask |= mmask ;
        HWA_TIMER0->HWA_PERIOD_mvalue = (HWA_TIMER0->HWA_PERIOD_mvalue & ~mmask) | (mmask & vmask) ;
      }
    } while(0);
  } while(0);

  return 0 ;

}
