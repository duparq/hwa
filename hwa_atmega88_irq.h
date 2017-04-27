#ifndef HWA_MCU_IRQ_H
#define HWA_MCU_IRQ_H

/************************************************************************
 *									*
 *			User definitions				*
 *									*
 ************************************************************************/

#define HWA_ISR(pname, event, interruptible)				\
  HWA_ISR_(HWA_G4(HWA, ISR, pname, event), HWA_G2(HWA_ISR, interruptible))


/************************************************************************
 *									*
 *			Internal definitions				*
 *									*
 ************************************************************************/

#if (__GNUC__ == 4 && __GNUC_MINOR__ >= 1) || (__GNUC__ > 4)
#  define __INTR_ATTRS used, externally_visible
#else /* GCC < 4.1 */
#  define __INTR_ATTRS used
#endif

#define HWA_ISR_(vector, interruptible)					\
  EXTERN_C void vector (void) __attribute__ ((signal,__INTR_ATTRS)) interruptible ; \
  void vector (void)

#define HWA_ISR_INTERRUPTIBLE
#define HWA_ISR_NON_INTERRUPTIBLE	__attribute__((interrupt))

#define HWA_ISR_TIMER2_OVERFLOW		__vector_9

#endif
