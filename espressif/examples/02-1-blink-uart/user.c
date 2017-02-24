
#include <hwa/modules/esp-wroom-02.h>

#define LED		pin_gpio5

#define IROM		__attribute__((section (".irom.text")))
#define IRAM


/*  Function called every 10 ms
 *   * toggle the LED on/off every 200 ms
 *   * when the LED is turned on, turn TXD low for 100 ms
 *   * when the LED if turned off, send "ON\n" on TXD
 */
void IROM every10ms ( )
{
  static uint8_t	count ;
  static uint8_t	txdlow ;

  if ( txdlow ) {
    txdlow-- ;
    if ( txdlow == 0 )
      /*
       *  TXD has been set low for 100 ms. Release it now: connect pin GPIO1 to
       *  the TXD signal
       */
      hw_config( pin_gpio1, function, hw_uart0_txd );
  }

  count++ ;
  if ( count < 20 )
    return ;

  /*  The following is done once every 200 ms
   */
  count = 0 ;

  if ( hw_read( LED ) == 0 ) {
    /*
     *	Turn LED on
     */
    hw_write( LED, 1 );
    /*
     *	Turn TXD low for 100 ms: connect pin GPIO1 to the GPIO1 signal
     */
    txdlow = 10 ;
    hw_config( pin_gpio1, function, gpio );
  }
  else {
    /*
     *	Turn LED off
     */
    hw_write( LED, 0 );
    /*
     *	Send message
     */
    os_printf("ON\n");
  }
}


void IROM user_init()
{
  hw_config( LED,
	     function,	gpio,			// Optionnal
	     direction, output_when_awake
	     );

  /*  Pin GPIO1 is also used as pin TXD of hw_uart0
   *  We want a low level on that pin when used as a GPIO
   */
  hw_config( pin_gpio1,
	     function,	   gpio,		// Optionnal
	     direction,	   output );
  hw_write( pin_gpio1, 0 );

  /*  Configure the UART
   *	Note: the OS has already configured the RXD and TXD pins
   */
  hw_config( uart0,
	     baudrate,	  9600,
	     databits,	  8,
	     parity,	  none,
	     stopbits,	  1,
	     /* pin_txd,     hw_pin_gpio1, */
	     /* pin_rxd,     hw_pin_gpio3, */
	     );

  os_printf("Hello World!\n");


  /*  Trigger a function call every 10 ms (about)
   */
  static os_timer_t timer ;

  os_timer_disarm( &timer );
  os_timer_setfn( &timer, (os_timer_func_t *)every10ms, NULL );
  os_timer_arm( &timer, 10, 1 );
}
