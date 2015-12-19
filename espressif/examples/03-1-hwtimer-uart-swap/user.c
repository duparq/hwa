
#include <hwa/modules/esp-wroom-02.h>

#define LED		hw_pin_gpio4

#define IROM		__attribute__((section (".irom.text")))
#define IRAM

extern void user_uart_wait_tx_fifo_empty();


/*  Function called about every 100 ms
 *   * output count
 */
void IROM every100ms ( )
{
  os_printf("Uptime: %d\n", hw_uptime_us);
}


/*  Hardware timer1 ISR
 */
void IRAM ev_timer ( )
{
  hw_toggle( LED );
}


void IROM user_init()
{
  //  user_uart_wait_tx_fifo_empty();	/* Never returns? */

  /*  Install user IRQ handlers
   */
  os_handle_irq( hw_timer1, irq, ev_timer );
  os_handle_irq( hw_timer1, nmi, ev_timer );

  //  hwa_begin();
  hwa_begin_from_reset();

  hwa_config( LED,
	      function,	gpio,
	      direction, output_when_awake
  	     );

  /*  Configure the UART
   */
  hwa_config( hw_pin_gpio15, function, uart0_txd );
  hwa_config( hw_pin_gpio13, function, uart0_rxd );

  hwa_config( hw_uart0,
	      baudrate,	  115200,
	      databits,	  8,
	      parity,	  none,
	      stopbits,	  1
	      );

  /*  Configure the timer1 to trigger a NMI interrupt every 10 ms
   */
  hwa_config( hw_timer1,
  	      clock,     apb_div_16,
  	      countmode, loop_down,
  	      top,       0.5 + 0.01*hw_apbhz/16,
  	      action,    irq
  	      );

  hwa_commit();

  os_printf("Hello World!\n");

  /*  Trigger a function call every 500 ms (about)
   */
  static os_timer_t timer ;

  os_timer_disarm( &timer );
  os_timer_setfn( &timer, (os_timer_func_t *)every100ms, NULL );
  os_timer_arm( &timer, 100, 1 );
}
