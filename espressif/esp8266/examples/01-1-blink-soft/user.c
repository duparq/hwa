
#include BOARD_H

#define IROM		__attribute__((section (".irom.text")))
#define IRAM

#if !defined LED
#  define LED		gpio2
#endif


/*  Function called every 250 ms
 *   * toggle the LED on/off every 200 ms
 */
void IROM every10ms ( )
{
  if ( hw( read, LED ) == 0 )
    hw( write, LED, 1 );
  else
    hw( write, LED, 0 );
}


void IROM user_init()
{
  /*  Configure the LED output
   */
  hw( configure, LED,
      function,	 gpio,			// Optionnal
      direction, output /* output_when_awake */ );

  /*  Trigger a function call every 10 ms (about)
   */
  static os_timer_t timer ;

  os_timer_disarm( &timer );
  os_timer_setfn( &timer, (os_timer_func_t *)every10ms, NULL );
  os_timer_arm( &timer, 10, 1 );
}
