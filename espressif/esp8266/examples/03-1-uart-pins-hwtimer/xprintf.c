
#include BOARD_H
#include <stdarg.h>
#include <stdint.h>
#include "xprintf.h"

#define IROM		__attribute__((section (".irom.text")))
#define IRAM

#define PAD_RIGHT	1
#define PAD_ZERO	2

/* the following should be enough for 32 bit int */
#define PRINT_BUF_LEN	12


static
void IROM xprint_s ( void (*putchar)(unsigned char), const char *string, int width, int pad)
{
  int padchar = ' ';

  if (width > 0) {
    int len = 0;
    const char *ptr;
    for (ptr = string; *ptr; ++ptr) ++len;
    if (len >= width) width = 0;
    else width -= len;
    if (pad & PAD_ZERO) padchar = '0';
  }
  if (!(pad & PAD_RIGHT)) {
    for ( ; width > 0; --width) {
      putchar(padchar);
    }
  }
  for ( ; *string ; ++string) {
    putchar(*string);
  }
  for ( ; width > 0; --width) {
    putchar(padchar);
  }
}

static
void IROM xprint_i ( void (*putchar)(unsigned char),
		     int32_t i, int b, int sg, int width, int pad, int letbase )
{
  char print_buf[PRINT_BUF_LEN];
  char *s;
  int t, neg = 0;
  /* unsigned int u = i; */
  uint32_t	u = i ;

  if (i == 0) {
    print_buf[0] = '0';
    print_buf[1] = '\0';
    xprint_s( putchar, print_buf, width, pad);
    return ;
  }

  if (sg && b == 10 && i < 0) {
    neg = 1;
    u = -i;
  }

  s = print_buf + PRINT_BUF_LEN-1;
  *s = '\0';

  while (u) {
    t = u % b;
    if( t >= 10 )
      t += letbase - '0' - 10;
#if defined DEBUG
    if ( s == print_buf )
      xexit(EXIT_PRINTBUF_OVERFLOW);
#endif
    *--s = t + '0';
    u /= b;
  }

  if (neg) {
    if( width && (pad & PAD_ZERO) ) {
      putchar('-');
      --width;
    }
    else {
      *--s = '-';
    }
  }
  xprint_s( putchar, s, width, pad);
}


void IROM xprintf ( void (*putchar)(unsigned char), const char *fmt, ... )
{
  va_list	ap ;
  int		width, pad;
  char const	*fsp = (char const*)fmt ;

  va_start( ap, fmt );

  for(;;) {
    char c = *fsp++ ;
    if ( c == 0 )
      break ;

    if ( c != '%' ) {
    out:
      putchar(c);
    }
    else {
      c = *fsp++ ;
      width = pad = 0 ;

      if ( c == '\0' ) break ;

      if ( c == '%' ) goto out ;

      if ( c == '-' ) {
	c = *fsp++ ;
	pad = PAD_RIGHT ;
      }

      while ( c == '0' ) {
	c = *fsp++ ;
	pad |= PAD_ZERO ;
      }

      while ( c >= '0' && c <= '9' ) {
	width *= 10;
	width += c - '0';
	c = *fsp++ ;
      }

      if ( c == 's' ) {
	char *s = va_arg(ap, char*);
	if ( s )
	  xprint_s( putchar, s, width, pad );
	continue;
      }

      if( c == 'd' ) {
	xprint_i( putchar, va_arg(ap,uint32_t), 10, 1, width, pad, 'a' );
	continue;
      }

#if 0
      if( c == 'x' ) {
	xprint_i( putchar, va_arg(ap,uint16_t), 16, 0, width, pad, 'a' );
	continue;
      }
#endif

      if( c == 'X' ) {
	xprint_i( putchar, va_arg(ap,uint32_t), 16, 0, width, pad, 'A' );
	continue;
      }

      if( c == 'u' ) {
	xprint_i( putchar, va_arg(ap,uint32_t), 10, 0, width, pad, 'a' );
	continue;
      }

      if( c == 'c' ) {
	/* char are converted to int then pushed on the stack */
	char scr[2];
	scr[0] = va_arg(ap,int);
	scr[1] = '\0';
	xprint_s( putchar, scr, width, pad );
	continue;
      }
    }
  }
}


/* void xprintf_p ( void (*putchar)(unsigned char), const char *fmt, ... ) */
/* { */
/*   va_list	ap ; */
/*   int		width, pad; */
/*   uint16_t	fsp = (uint16_t)(intptr_t)fmt ; */

/*   va_start( ap, fmt ); */

/*   for(;;) { */
/*     char c = hw( read, flash0, fsp++ ); */
/*     if ( c == 0 ) */
/*       break ; */

/*     if ( c != '%' ) { */
/*     out: */
/*       putchar(c); */
/*     } */
/*     else { */
/*       c = hw( read, flash0, fsp++ ); */
/*       width = pad = 0 ; */

/*       if ( c == '\0' ) break ; */

/*       if ( c == '%' ) goto out ; */

/*       if ( c == '-' ) { */
/* 	c = hw( read, flash0, fsp++ ); */
/* 	pad = PAD_RIGHT ; */
/*       } */

/*       while ( c == '0' ) { */
/* 	c = hw( read, flash0, fsp++ ); */
/* 	pad |= PAD_ZERO ; */
/*       } */

/*       while ( c >= '0' && c <= '9' ) { */
/* 	width *= 10; */
/* 	width += c - '0'; */
/* 	c = hw( read, flash0, fsp++ ); */
/*       } */

/*       if ( c == 's' ) { */
/* 	char *s = va_arg(ap, char*); */
/* 	if ( s ) */
/* 	  xprint_s( putchar, s, width, pad ); */
/* 	continue; */
/*       } */

/*       if( c == 'd' ) { */
/* 	xprint_i( putchar, va_arg(ap,uint16_t), 10, 1, width, pad, 'a' ); */
/* 	continue; */
/*       } */

/* #if 0 */
/*       if( c == 'x' ) { */
/* 	xprint_i( putchar, va_arg(ap,uint16_t), 16, 0, width, pad, 'a' ); */
/* 	continue; */
/*       } */
/* #endif */

/*       if( c == 'X' ) { */
/* 	xprint_i( putchar, va_arg(ap,uint16_t), 16, 0, width, pad, 'A' ); */
/* 	continue; */
/*       } */

/*       if( c == 'u' ) { */
/* 	xprint_i( putchar, va_arg(ap,uint16_t), 10, 0, width, pad, 'a' ); */
/* 	continue; */
/*       } */

/*       if( c == 'c' ) { */
/* 	/\* char are converted to int then pushed on the stack *\/ */
/* 	char scr[2]; */
/* 	scr[0] = va_arg(ap,int); */
/* 	scr[1] = '\0'; */
/* 	xprint_s( putchar, scr, width, pad ); */
/* 	continue; */
/*       } */
/*     } */
/*   } */
/* } */
