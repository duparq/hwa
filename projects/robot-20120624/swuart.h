#ifndef SWUART_H
#define SWUART_H

#include "config.h"
#include "hwa.h"

#ifndef __ASSEMBLER__

extern u8	swuart_data ;
extern u16	swuart_sync ( u8 ) ;
extern void	swuart_wait_rxidle ( u8 n ) ;
extern void	swuart_wait_ready ( ) ;
extern void	swuart_set_dt ( u16 ) ;
extern u8	swuart_getbyte ( ) ;
extern void	swuart_putbyte ( u8 byte ) ;
extern u16	swuart_chksync ( u16, u16, u8 ) ;

#if defined SWUART_TIMER
#if hw_max(SWUART_TIMER) == 255
extern u8	swuart_dtn ;
extern u8	swuart_dt0 ;
#elif hw_max(SWUART_TIMER) == 65535
#  if defined SWUART_MATCH && SWUART_MATCH != 16
#    error
#  endif
extern u16	swuart_dtn ;
extern u16	swuart_dt0 ;
#else
#  error
#endif
#endif /* defined SWUART_TIMER */


#if defined SWUART_CALLBACK
extern void	SWUART_CALLBACK( ) ;
#endif

#if defined SWUART_CALLBACK_PTR
extern void	(*SWUART_CALLBACK_PTR)( ) ;
#endif

#endif /* __ASSEMBLER__ */


#define SWUART_START_PIN_INT0			1
#define SWUART_START_PIN_AIN1			2
#define SWUART_START_PIN_PCINT8			3


#if defined SWUART_TIMER
#  define hwa_swuart_timer()  hwa_timer_connect_clock( SWUART_TIMER, SWUART_TIMER_CLKHZ )
#  if defined SWUART_PIN_RX
#    if HW_G2(SWUART_START, SWUART_PIN_RX) == SWUART_START_PIN_INT0
#      define hwa_swuart_start() hwa_write( ISC0, 0b10 )  /* INT0 interrupt on falling edge */
#    elif HW_G2(SWUART_START, SWUART_PIN_RX) == SWUART_START_PIN_AIN1
#      define hwa_swuart_start()					\
  hwa_write( ACIS, 0b11 );	/* IRQ on RX falling edge		*/ \
  hwa_write( ACBG, 1 )		/* Apply band-gap reference to AIN0	*/
#    elif HW_G2(SWUART_START, SWUART_PIN_RX) == SWUART_START_PIN_PCINT8
#      define hwa_swuart_start()					\
  hwa_write( PCINT8, 1 );	/* PCIE1 IRQ on any RX edge		*/
#    else
#      error
#    endif
#  else
#    define hwa_swuart_start()
#  endif
#else
#  define hwa_swuart_timer()
#endif

#if defined SWUART_PIN_RX
#  define hwa_swuart_rx()	hwa_gpio_config_pin(SWUART_PIN_RX, INPUT)
#else
#  define hwa_swuart_rx()
#endif

#if defined SWUART_PIN_TX && \
  (!defined SWUART_PIN_RX || \
   HW_ADDR(HW_GPIOPORT(SWUART_PIN_TX), port)!=HW_ADDR(HW_GPIOPORT(SWUART_PIN_RX), port) || \
   HW_GPIOPIN(SWUART_PIN_TX)!=HW_GPIOPIN(SWUART_PIN_RX))
#  define hwa_swuart_tx()	hwa_gpio_config_pin(SWUART_PIN_TX, OUTPUT)
#else
#  define hwa_swuart_tx()
#endif

#if defined SWUART_PIN_DBG
#  define hwa_swuart_dbg()	hwa_gpio_config_pin(SWUART_PIN_DBG, OUTPUT)
#else
#  define hwa_swuart_dbg()
#endif



#define hwa_swuart()				\
  hwa_swuart_timer();				\
  hwa_swuart_start();				\
  hwa_swuart_rx();				\
  hwa_swuart_tx();				\
  hwa_swuart_dbg()


/* typedef struct { */
/*   uint	stopbit	: 1 ; */
/*   uint	idlebit : 1 ; */
/*   uint	newdata : 1 ; */
/* } swuart_status_t ; */


/* extern volatile swuart_status_t swuart_status ; */

/* typedef struct { */
/*   u8				data ; */
/*   u16				dtn ; */
/*   volatile swuart_status_t	status ; */
/* } swuart_t ; */

/* extern swuart_t swuart ; */

#endif /* SWUART_H */
