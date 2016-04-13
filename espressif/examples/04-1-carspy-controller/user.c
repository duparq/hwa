
#include <hwa/modules/esp-wroom-02.h>
#include <mem.h>

#define LED		hw_pin_gpio4

#define IROM		__attribute__((section (".irom.text")))
#define IRAM

#define UART		hw_uart0
#define TXFIFO		hw_rel( UART, txfifo )

extern void user_uart_wait_tx_fifo_empty();

static uint8_t		seq_phase ;
static _Bool		x_poll ;


#define USER_TASK		USER_TASK_PRIO_0
#define USER_TASK_QUEUE_LEN	4

static os_event_t user_task_queue[USER_TASK_QUEUE_LEN];
//static os_event_t*		user_task_queue ;


/*  Function called about every 100 ms
 *   * output count
 */
void IROM every100ms ( )
{
  os_printf("Uptime: %d\n", hw_uptime_us());
}


/*  UART ISR
 *
 *  Post messages to the user task that will process them is soon as it can.
 */
void IRAM ev_uart ( )
{
  if ( hw_read_reg( UART, iftxq ) ) {
    /*
     *  Remove the parity bit after the first byte has been sent
     */
    hw_config( hw_uart0, parity, none );
    hw_clear_irq( UART, txq );
    hw_turn_irq( UART, txq, off );
  }

  if ( hw_read_reg( UART, ifrxq ) ) {
    /*
     *  Post received byte to the user task
     */
    char c = hw_read_reg( UART, fifo );
    hw_clear_irq( UART, rxq );
    system_os_post( USER_TASK, 1, c );
  }
}


/*  Hardware timer1 ISR
 *
 *  This interrupt is triggered at regular intervals. It starts the polling
 *  sequence.
 */
void IRAM ev_timer ( )
{
  if ( x_poll ) {
    hw_write( LED, 1 );
    hw_write( LED, 0 );

    /*  Broadcast "LATCH" command.
     */
    seq_phase = 0 ;
    hw_config( hw_uart0, parity, even );
    hw_write( hw_uart0, 0 );
    hw_write( hw_uart0, 0x0F );

    /*  Help the handler detect when the first byte has been transmitted so that
     *	it can remove the parity bit for the remaining bytes.
     */
    hw_clear_irq( UART, txq );
    hw_turn_irq( UART, txq, on );
  }
}


void IROM uart1_write_char ( char c )
{
  hw_write_reg( hw_uart1, fifo, c );
}


void IROM user_task ( os_event_t *ev __attribute__((unused)) )
{
  //  poll_sm( ev->par );

  static uint8_t	count ;
  static uint8_t	mod ;
  /* char c ; */

  if ( seq_phase == 0 ) {
    /*
     *  The first byte has been received: the controller is connected to the bus.
     */
    count++ ;
    if ( count == 2 ) {
      count = 0 ;

      hw_write( LED, 1 );
      seq_phase = 1 ;
      mod = 1 ;
    }
    return ;
  }

  /*  Poll each module sequentially
   */
  if ( seq_phase == 1 ) {
    mod++ ;
    if ( mod == 31 ) {
      seq_phase = 2 ;
      return ;
    }

    seq_phase = 2 ;
    hw_write( LED, 1 );
    hw_write( UART, 0x55 );
  }
}


void IROM user_init()
{
  //  user_uart_wait_tx_fifo_empty();	/* Never returns? */

  os_install_putc1((void *)uart1_write_char);//print output at UART1

  /*  Create user task
   */
  //  user_task_queue = (os_event_t *)os_malloc(sizeof(os_event_t)*USER_TASK_QUEUE_LEN);
  system_os_task( user_task, USER_TASK, user_task_queue, USER_TASK_QUEUE_LEN );

  /*  Install user IRQ handlers
   */
  os_handle_irq( hw_timer1, nmi, ev_timer );
  os_handle_irq( hw_uart0, ev_uart );

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

  hwa_config( UART,
	      baudrate,	     100000,
	      databits,	     8,
	      parity,	     none,
	      stopbits,	     1
	      );

  hwa_write_reg( UART, rxqt, 64 );

  hwa_config( hw_pin_gpio2, function, uart1_txd );
  hwa_config( hw_uart1,
	      baudrate,	     115200,
	      databits,	     8,
	      parity,	     none,
	      stopbits,	     1
	      );


  /*  Configure the timer1 to trigger a NMI interrupt every 10 ms
   */
  hwa_config( hw_timer1,
  	      clock,     apb_div(16),
  	      countmode, down_loop,
  	      top,       0.5 + 0.01*hw_apbhz/16,
  	      action,    nmi
  	      );

  hwa_commit();

  hw_turn_irq( UART, on ); //  ETS_UART_INTR_ENABLE();

  //  os_printf("Hello World!\n");

  /*  Trigger a function call every 100 ms (about)
   */
  static os_timer_t timer ;

  os_timer_disarm( &timer );
  os_timer_setfn( &timer, (os_timer_func_t *)every100ms, NULL );
  os_timer_arm( &timer, 100, 1 );

  x_poll = 1 ;
}
