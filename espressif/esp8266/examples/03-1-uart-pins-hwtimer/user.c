
/**
 * @example
 *
 * @par Reconfigure uart0 (pin functions + swap). Configure timer1.
 *
 * The factory firmware sends boot messages on uart0. That can be a problem when
 * a microcontroller is connected to this interface. Reconfiguring the pins used
 * for TXD and RXD lets the microcontroller not receive the boot messages.
 *
 * Reconfigure uart0 to use pin GPIO15 for TXD and GPIO13 for RXD. The uart0
 * sends the uptime about every 100 ms using an OS timer.
 *
 * Configure the timer1 to trigger an IRQ every 100 ms (IRQ or NMI).
 *
 * @par user.c
 */

#include BOARD_H

#define IROM		__attribute__((section (".irom.text")))
#define IRAM

#if !defined PIN_LED
#  define PIN_LED	gpio4
#endif

extern void		user_uart_wait_tx_fifo_empty();
static os_timer_t	os_timer ;


/*  Function called about every 100 ms
 */
void IROM every_100ms ( )
{
  os_printf("Uptime: %u\n", hw_uptime_us());
}


/*  Hardware timer1 ISR
 */
void IRAM ev_timer ( )
{
  hw( toggle, PIN_LED );
}


/*  The UART should be ready for reconfiguration. Configure timer1 too.
 */
void IROM user_init_2 ( )
{
  os_timer_disarm( &os_timer );

  /*  Install user IRQ handlers
   */
  os_set_isr( irq(timer1,irq), ev_timer );
  os_set_isr( irq(timer1,nmi), ev_timer );

  hwa( begin_from_reset );

  hwa( configure, PIN_LED, function, gpio, mode, digital_output );

  /*  Reconfigure the UART
   */
  hwa( configure, gpio15, function, (uart0,txd) );
  hwa( configure, gpio13, function, (uart0,rxd) );

  hwa( configure, uart0,
       baudrate,  115200,
       databits,  8,
       parity,    none,
       stopbits,  1 );

  /*  Configure the timer1 to trigger an interrupt every 10 ms
   */
  hwa( configure, timer1,
       clock,     apb/256,
       direction, down_loop,
       top,       0.5 + 0.1*HW_APBHZ/256,
       action,    irq );

  hwa( commit );

  os_printf("START with user configuration: RXD=GPIO13 TXD=GPIO15\n");

  /*  Trigger a function call every 100 ms (about)
   */
  os_timer_setfn( &os_timer, (os_timer_func_t *)every_100ms, NULL );
  os_timer_arm( &os_timer, 100, 1 );
}


/*  Program starts here
 */
void IROM user_init ( )
{
  os_printf("START with factory configuration: RXD=GPIO3 TXD=GPIO1\n");

  user_uart_wait_tx_fifo_empty();

  /*  Give the UART a bit more time before switching
   */
  os_timer_disarm( &os_timer );
  os_timer_setfn( &os_timer, (os_timer_func_t *)user_init_2, NULL );
  os_timer_arm( &os_timer, 100, 1 );
}
