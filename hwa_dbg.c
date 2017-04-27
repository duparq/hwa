
#include <stdio.h>


#define hwa_dbg(s)	printf(s "\n")


u32	_sbss[1], _ebss[1] ;


static const char* basename ( const char *path )
{
  const char *p = path ;
  do {
    if ( *path == '/' )
      p = path+1 ;
    path++ ;
  } while ( *path ) ;
  return p ;
}


int hwa_dbg_gethr( const char *file, uint line,
		   const char *mname, const char *rname,
		   intptr_t addr )
{
  printf("%s:%d %s %s read 0x%08X\n", basename(file), line, mname, rname, (int)addr);
  return 0 ;
}


void hwa_dbg_sethr( const char *file, uint line,
		    const char *mname, const char *rname,
		    u8 size, intptr_t addr, uint om __attribute__((unused)), uint m, uint val )
{
#if 0
  printf("%s:%d %s %s (0x%0*X) *0x%08X & 0x%0*X = 0x%0*X\n", file, line, mname, rname,
	 2*size, om, (int)addr, 2*size, m, 2*size, val);
#else
  printf("%s:%d %s %s *0x%08X =", basename(file), line, mname, rname, (int)addr);
  size = size * 8 - 1 ;
  for ( uint i=0 ; i<size+1 ; i++ ) {
    if ( i % 8 == 0 )
      putchar(' ');
    if ( m & (1<<(size-i)) )
      putchar( val & (1<<(size-i)) ? '1' : '0' );
    else
      putchar('.');
  }
  putchar('\n');
#endif
}
