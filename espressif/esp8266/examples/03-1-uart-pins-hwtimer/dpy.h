#ifndef DPY_H
#define DPY_H

uint8_t		dpy_init ( ) ;
void		dpybuffer_clear ( ) ;
void		dpybuffer_moveto ( int x, int y ) ;
void		dpybuffer_putchar ( unsigned char c ) ;
void		dpybuffer_show ( ) ;


/*  The linker scripts of avr-gcc/avr-libc put the .progmem section right after
 *  the .vectors section.
 *
 *  The Diabolo bootloader starts the application by jumping to the end of the
 *  .vectors section.
 *
 *  So, we ask GCC to put ROM data in a .flashdata section and use our own
 *  linker script that puts that section after all other sections in .text.
 *
 *  See Makefiles.
 */
#define ROM	__attribute__((section(".flashdata")))
#define P(s)	(__extension__({static const char _s[] ROM = s; _s;}))

#endif
