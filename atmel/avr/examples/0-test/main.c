
#define E               _Pragma("GCC error \"This is an error\"")

#define _IS_VOID_       , 1

/*  Return "1" if <c> is "", return "0" otherwise.
 */
#define ISVOID(c)         _ISVOID2(c)
#define _ISVOID2(c)       _ISVOID3(_IS_VOID_##c,0,)
#define _ISVOID3(...)     _ISVOID4(__VA_ARGS__)
#define _ISVOID4(v,x,...) x


"ISVOID(something):" ISVOID(something)
"ISVOID():" ISVOID()
"ISVOID(E):" ISVOID(E)


#if ISVOID(something) == 1
"ISVOID(something)==1: true"
#else
"ISVOID(something)==1: false"
#endif

#if ISVOID() == 1
"ISVOID()==1: true"
#else
"ISVOID()==1: false"
#endif

#if ISVOID(E) == 1
"ISVOID(E)==1: true"
#elif ISVOID(E) == 0
"ISVOID(E)==0: true"
#endif

#if 1 == 1
#endif
