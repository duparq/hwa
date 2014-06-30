#ifndef SWUART_H
#define SWUART_H

#include <hwa.h>

extern uint8_t	swuart_data ;
extern uint8_t	swuart_status ;

extern uint8_t	swuart_dtnl ;
extern uint8_t	swuart_dtnh ;

extern uint16_t	swuart_sync ( uint8_t ) ;
extern uint16_t	swuart_sync_10_1 ( ) ;
extern void	swuart_wait_rxidle ( uint8_t n ) ;
/* extern uint8_t	swuart_wait_start ( uint8_t n ) ; */
extern void	swuart_wait ( uint8_t n ) ;
extern void	swuart_wait_ready ( ) ;
extern uint8_t	swuart_is_busy ( void ) ;
extern uint8_t	swuart_is_emitting ( void ) ;
extern uint8_t	swuart_rxq_notempty ( void ) ;
extern uint8_t	swuart_tx_completed ( void ) ;
extern void	swuart_set_dt ( uint16_t ) ;
extern void	swuart_enable_rx ( ) ;
extern uint8_t	swuart_getbyte ( ) ;
#define swuart_rx swuart_getbyte
extern void	swuart_putbyte ( uint8_t byte ) ;
extern void	swuart_putchar ( char ) ;
#define swuart_tx swuart_putbyte
extern void	swuart_brk ( uint8_t n ) ;
extern uint16_t	swuart_chksync ( uint16_t, uint16_t, uint8_t ) ;


#if hw_bn(SWUART_COUNTER) == 8
extern uint8_t	swuart_dtn ;
extern uint8_t	swuart_dt0 ;
#elif hw_bn(SWUART_COUNTER) == 16
#  if defined SWUART_MATCH && SWUART_MATCH != 16
#    error
#  endif
extern uint16_t	swuart_dtn ;
extern uint16_t	swuart_dt0 ;
#else
#  error
#endif


#if defined SWUART_CALLBACK
extern void	SWUART_CALLBACK( ) ;
#endif

#if defined SWUART_CALLBACK_PTR
extern void	(*SWUART_CALLBACK_PTR)( ) ;
#endif


/*	Configuration
 */
HW_INLINE void swuart_hwa(hwa_t *hwa)
{
  /*	Configure counter
   */
#if defined SWUART_COUNTER
  hwa_config( SWUART_COUNTER,
	      clock,		SWUART_COUNTER_CLOCK,
	      countmode,	loop_up,
	      top,		fixed_0xFF );
#endif

  /*	Start condition interrupt
   */
#if hw_eq(SWUART_PIN_RX, hw_pin_int0)
  /*
   *		INT0 interrupt: only on falling edge
   */
  hwa_write( hw_core0, isc0, 2 );
#elif hw_eq(hw_ctr(SWUART_PIN_RX), hw_pcic0) ||	hw_eq(hw_ctr(SWUART_PIN_RX), hw_pcic1)
  /*
   *		Pin-change interrupt: pin-change controller irq must be
   *		enabled. Then, pin-change interrupts will be enabled/disabled as
   *		required by setting the mask associated to the pin.
   */
  hwa_turn_irq( hw_ctr(SWUART_PIN_RX), all, on );
#endif

  /*	RX pin
   */
#if defined SWUART_PIN_RX
  hwa_config(hw_io(SWUART_PIN_RX), input);
#endif

  /*	TX pin
   */
#if defined SWUART_PIN_TX && !hw_eq(SWUART_PIN_TX, SWUART_PIN_RX)
  hwa_config(hw_io(SWUART_PIN_TX), output);
  hwa_write(SWUART_PIN_TX, 1);
#endif

  /*	DBG pin
   */
#if defined SWUART_PIN_DBG
  hwa_config(SWUART_PIN_DBG, output);
#endif
}


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
