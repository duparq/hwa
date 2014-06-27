
#include <hwa__apply.h>
#include <hwa__funcs.h>
#include <hwa__is.h>
#include <hwa__macros.h>
#include <hwa__types.h>

#define HW_RA_OFFSET		0
//#define HW_INLINE		static inline __attribute__((always_inline))


#define hw_read(...)	HW_APPLY(hw_read, __VA_ARGS__)
#define hw_read_io_isfn
#define hw_read_io(...) (int)HW_QUOTE(hw_read_io(__VA_ARGS__))
#define hw_read_ctr0a_isfn
#define hw_read_ctr0a(...) (int)HW_QUOTE(hw_read_ctr0a(__VA_ARGS__))

//#define hw_read_ctr1a_reg1_isfn
//#define hw_read_ctr1a_reg1(p,c,a, _reg1_)
//  x = hw_read_ctr1a_reg1(ctr1,ctr1a,0x0200, reg1);

#define hw_read_reg_isfn
#define hw_read_8(...)	(int)HW_QUOTE(hw_read_8(__VA_ARGS__))

#define hw_write(...)	HW_APPLY(hw_write, __VA_ARGS__)
#define hw_write_io_isfn
#define hw_write_io(...) x=(int)HW_QUOTE(hw_write_io(__VA_ARGS__))
#define hw_write_ctr_isfn
#define hw_write_ctr(...) x=(int)HW_QUOTE(hw_write_ctr(__VA_ARGS__))
#define hw_write_reg_isfn
#define hw_write_8(...)	x=(int)HW_QUOTE(hw_write_8(__VA_ARGS__))

#define hw_turn(...)	HW_APPLY(hw_turn, __VA_ARGS__)
#define hw_turn_ctr1a_irq_isfn
#define hw_turn_ctr1a_irq(...)	x=(int)HW_QUOTE(hw_turn_irq_ctr1a(__VA_ARGS__))
#define hw_turn_ctr_isfn
#define hw_turn_ctr(...)	x=(int)HW_QUOTE(hw_turn_ctr(__VA_ARGS__))

//#define hw_turn_ctr_power_isfn
#define hw_turn_ctr_power(...)	x=(int)HW_QUOTE(hw_turn_ctr_power(__VA_ARGS__))

#define hw_config(...)		HW_APPLY(hw_config, __VA_ARGS__)
#define hw_config_ctr1a_isfn
#define hw_config_ctr1a(...)	x=(int)HW_QUOTE(hw_config_ctr1a(__VA_ARGS__))

//#define hw_turn_ctr_power_isfn
#define hw_turn_ctr_power(...)	x=(int)HW_QUOTE(hw_turn_ctr_power(__VA_ARGS__))




/*	Controller		type, name, class, address
 */
#define hw_ctr0			ctr, ctr0, ctr0a, 0x0100


/*	Registers		type, name, rw, ra, riv, rwm
 */
#define hw_ctr0a_reg1		reg, reg1, 8, 0x10, 0x00, 0xFF
#define hw_ctr0a_reg2		reg, reg2, 8, 0x11, 0x00, 0xFF


/*	Pins			type, name, hw_controller, bn, bp
 */
#define hw_pin_p0		io, pin_p0, hw_ctr0, 1, 0
#define hw_pin_p1		io, pin_p1, hw_ctr0, 1, 1


/*	Controller		type, name, class, address
 */
#define hw_ctr1			ctr, ctr1, ctr1a, 0x0200


/*	Registers		type, name, rw, ra, riv, rwm
 */
#define hw_ctr1a_reg1		reg, reg1, 8, 0x20, 0x00, 0xFC
#define hw_ctr1a_bits1		regb, hw_ctr1a_reg1, 4, 4
#define hw_ctr1a_bits2		regb, hw_ctr0, reg1, 2, 2

#define hw_ctr1a_reg2		reg, reg2, 8, 0x21, 0x00, 0x60
#define hw_ctr1a_bits3		regb, hw_ctr1a_reg2, 2, 4
#define hw_ctr1a_bits4		regbb, hw_ctr1a_reg1,2,0,1, hw_ctr1a_reg2,1,2,0


#define hw_max(...)		HW_APPLY(hw_max, __VA_ARGS__)
#define hw_max_ctr0a_isfn
#define hw_max_ctr0a(p,pc,pa)	255
#define hw_max_ctr1a_isfn
#define hw_max_ctr1a(p,pc,pa)	65535



#include <inttypes.h>

#define PIN		hw_pin_p0
#define CTR		hw_ctr1


#define hw_isr_ctr0_overflow	isr, overflow, 10
#define hw_isr_ctr0_all		isr, all, 20

#if (__GNUC__ == 4 && __GNUC_MINOR__ >= 1) || (__GNUC__ > 4)
#  define HW_ISR_ATTRS used, externally_visible
#else /* GCC < 4.1 */
#  define HW_ISR_ATTRS used
#endif


#define _hw_isr_(name, vector, ...)						\
  HW_EXTERN_C void __vector_##vector (void) __attribute__ ((signal, HW_ISR_ATTRS)) __VA_ARGS__ ; \
  void __vector_##vector (void)


#define hw_israttr_interruptible		__attribute__((interrupt))
#define hw_israttr_non_interruptible
#define hw_israttr_naked			__attribute__((naked))


/* hw_isr( hw_ctr0, interruptible ) */
/* { */
/* } */

HW_ISR( hw_ctr0, overflow )
{
}


/* hw_isr( hw_ctrX, interruptible ) */
/* { */
/* } */


int main ( )
{
  int	x ;

  /* x = hw_ra( foo, reg1 ); */
  /* x = hw_ra( CTR, foo ); */
  /* x = hw_ra( reg, reg1 ); */
  /* x = hw_ra( ctr, reg1 ); */

  x = hw_ra( CTR, reg1 );
  x = hw_bn( PIN );
  x = hw_bp( PIN );

  x = (int)HW_QUOTE( hw_name( CTR ) ) ;
  x = (int)HW_QUOTE( hw_name( PIN ) ) ;
  x = (int)HW_QUOTE( hw_ctr( PIN ) ) ;

  x = hw_read( PIN );
  hw_write( PIN, x );

  x = hw_read( hw_ctr0, v );
  //  hw_read( hw_ctr1 );

  hw_write( CTR, value );
  hw_write( CTR, status );

  hw_turn( CTR, irq, overflow, on );
  hw_turn( CTR, off );

  hw_turn( CTR, power, on );

  x = hw_read( CTR, reg1 );
  hw_write( CTR, reg1, x );
  x = hw_read( CTR, bits1 );
  hw_write( CTR, bits1, x );
  x = hw_read( CTR, bits2 );
  hw_write( CTR, bits2, x );
  x = hw_read( CTR, bits3 );
  hw_write( CTR, bits3, x );

  x = hw_read( CTR, bits4 );
  hw_write( CTR, bits4, x );

  //  x = hw_read( CTR, bits5 );

  hw_config( CTR,
	     clock,	prescaler0,
	     direction,	up,
	     top,	hw_max(CTR) );

  *((int*)0)=x;

  if ( (int)HW_QUOTE(hw_name(CTR)) == (int)"ctr1" )
    *((int*)1)=1;

  if ( hw_eq(hw_pin_p0, hw_pin_p1) )
    *((int*)2)=1;


  return 0;
}
