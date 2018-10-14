
/**
 * @example
 *
 * @par Configure timer1, uart0 and uart0 pins using pin functions and swap.
 *
 * The LED is toggled every 10 ms using a timer event (IRQ or NMI).
 * The uart0 sends the uptime about every 100 ms using an OS timer.
 *
 * @par user.c
 */

#include BOARD_H

#define IROM		__attribute__((section (".irom.text")))
#define IRAM

#if !defined PIN_LED
#  define PIN_LED	gpio4
#endif

extern void user_uart_wait_tx_fifo_empty();


/*  Function called about every 100 ms
 *   * output count
 */
void IROM every_100ms ( )
{
  os_printf("Uptime: %d\n", hw_uptime_us);
}


/*  Hardware timer1 ISR
 */
void IRAM ev_timer ( )
{
  hw( toggle, PIN_LED );
}


void IROM user_init()
{
  //  user_uart_wait_tx_fifo_empty();	/* Never returns? */

  /*  Install user IRQ handlers
   */
  os_set_isr( HW_IRQ(timer1, irq), ev_timer );
  os_set_isr( HW_IRQ(timer1, nmi), ev_timer );

  hwa_begin_from_reset();

  hwa( configure, PIN_LED, mode, digital_output );

  /*  Configure the UART
   */
  hwa( configure, gpio15, function, uart0_txd );
  hwa( configure, gpio13, function, uart0_rxd );

  hwa( configure, uart0,
       baudrate,  115200,
       databits,  8,
       parity,    none,
       stopbits,  1 );

  /*  Configure the timer1 to trigger a NMI interrupt every 10 ms
   */
  hwa( configure, timer1,
       clock,     apb_div_16,
       countmode, down_loop,
       top,       0.5 + 0.01*hw_apbhz/16,
       action,    irq );

  hwa_commit();

  os_printf("Hello World!\n");

  /*  Trigger a function call every 100 ms (about)
   */
  static os_timer_t timer ;

  os_timer_disarm( &timer );
  os_timer_setfn( &timer, (os_timer_func_t *)every_100ms, NULL );
  os_timer_arm( &timer, 100, 1 );
}
