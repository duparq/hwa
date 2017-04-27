
#include "config.h"
#include "hwa.h"

extern unsigned long _sidata;
extern unsigned long _edata;
extern unsigned long _sdata;
extern unsigned long _ebss;
extern unsigned long _sbss;
extern void (*const isr_vector[]) (void) ;

/* void		hwa_warn_ct ( const char *msg __attribute__((unused)) ) {} */
/* void		hwa_warn_ct_1 ( const char *msg ) { hwa_warn_ct(msg); } */
/* void		hwa_warn_ct_2 ( const char *msg ) { hwa_warn_ct(msg); } */
/* void		hwa_warn_ct_3 ( const char *msg ) { hwa_warn_ct(msg); } */
/* void		hwa_warn_ct_4 ( const char *msg ) { hwa_warn_ct(msg); } */

void		hwa_warn_rt ( const char *msg __attribute__((unused)) ) {}
void		hwa_warn_rt_1 ( const char *msg ) { hwa_warn_rt(msg); }
void		hwa_warn_rt_2 ( const char *msg ) { hwa_warn_rt(msg); }
void		hwa_warn_rt_3 ( const char *msg ) { hwa_warn_rt(msg); }
void		hwa_warn_rt_4 ( const char *msg ) { hwa_warn_rt(msg); }

void		hwa_error_rt ( const char *msg __attribute__((unused)) ) {}
void		hwa_error_rt_1 ( const char *msg ) { hwa_error_rt(msg); }
void		hwa_error_rt_2 ( const char *msg ) { hwa_error_rt(msg); }
void		hwa_error_rt_3 ( const char *msg ) { hwa_error_rt(msg); }
void		hwa_error_rt_4 ( const char *msg ) { hwa_error_rt(msg); }

extern void	main(void);

#define WEAK	__attribute__((weak))

void WEAK	exit ( int status __attribute__((unused)) ) ;


#define ISR_DEFAULT_NULL	0
#define ISR_DEFAULT_LOOP	1
#define ISR_DEFAULT_EXIT	2
#define ISR_DEFAULT_EXIT_N	3


#ifdef ISR_DEFAULT
#  if ISR_DEFAULT == ISR_DEFAULT_NULL
#    define ESR(n) ;
#    define ISR(n) ;
#  elif ISR_DEFAULT == ISR_DEFAULT_LOOP
#    define ESR(n) { isr_loop(); }
#    define ISR(n) { isr_loop(); }
#  elif ISR_DEFAULT == ISR_DEFAULT_EXIT
#    define ESR(n) ;
#    define ISR(n) ;
/* #    define ESR(n) { isr_exit(); } */
/* #    define ISR(n) { isr_exit(); } */
#  elif ISR_DEFAULT == ISR_DEFAULT_EXIT_N
#    define ESR(n) { exit(10000 + n); }
#    define ISR(n) { exit(10000 + n); }
#  else
#    error "Unknown ISR_DEFAULT definition."
#  endif
#else
#  define ESR(n) ;
#  define ISR(n) ;
#endif


void __attribute__((noreturn))
isr_loop ( )
{
  while(1) {}
}


void __attribute__((noreturn))
isr_exit ( )
{
  exit(10000);
}


void __attribute__((noreturn))
assert_failed ( const char *file __attribute__ ((unused)),
		u16 line __attribute__ ((unused)))
{
  exit(1);
}


void __attribute__((noreturn, weak))
exit ( int status __attribute__((unused)) )
{
  while(1) {}
}


/*	Include specific device code
 */
#define HWA_INCC_STM32		"hwa_stm32.c"

#define _HWA_INCC(dev)		HWA_INCC_##dev
#define HWA_INCC(dev)		_HWA_INCC(dev)

#if defined HWA_DEVICE
#include HWA_INCC(HWA_DEVICE)
#else
#error "HWA: undefined symbol HWA_DEVICE."
#endif
