
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Flash memory
 */

/**
 * @page atmelavr_flasha
 * @section atmelavr_eeproma_read Read operations
 *
 * `read`: reads one byte at given memory address:
 *
 * @code
 * uint8_t byte = hw( read, flash0, addr ); // Read byte at address addr
 * @endcode
 */
#define _hw_mtd_hw_read__flasha	, _hw_read_flasha
#define _hw_read_flasha(o,i,a,addr,...)		HW_TX( _hw_flashardbyte((intptr_t)(addr)), __VA_ARGS__)

HW_INLINE uint8_t _hw_flashardbyte( uint16_t a )
{
  /* FIXME: Z (R31:R30) is not modified by LPM but GCC considers it is as it reloads
     Z even if it does not change */
  uint8_t r ;
  hw_asm("    lpm %[r], Z"	"\n"
	 :
	 [r] "=&r" (r)
	 :
	 "z" (a)
	 );
  return r ;
}


/**
 * @page atmelavr_flasha
 *
 * `read_bytes`: reads multiple bytes from given memory address:
 *
 * @code
 * uint8_t dst[10];
 * uint8_t count = sizeof(dst);
 * hw( read_bytes, flash0, dst, addr, count ); // Copy count bytes from Flash address addr to dst
 * @endcode
 */

#define _hw_mtd_hw_read_bytes__flasha	, _hw_read_bytes_flasha

#define _hw_read_bytes_flasha(o,i,a,dst,addr,n,...)	\
  HW_TX( _hw_flashardbytes(dst,addr,n), __VA_ARGS__)

/**
 * @brief Store into dst count bytes read from Flash memory address addr
 */
HW_INLINE void _hw_flashardbytes( uint8_t *dst, uint16_t addr, uint8_t count )
{
  hw_asm("1:  lpm  __tmp_reg__, Z+"		"\n"
	 "    st   %a2+, __tmp_reg__"		"\n"
	 "    dec  %A0"				"\n"
	 "    brne  1b"				"\n"
	 :
	 "=r" (count),
	 "=z" (addr),
	 "=e" (dst)
	 :
	 "0" (count), "1" (addr), "2" (dst)
	 );
}


/**
 * @page atmelavr_flasha
 * @section atmelavr_eeproma_write Write operations
 *
 * Writing into the memory requires a special procedure:
 *
 *  1. Load a page buffer with the content to be
 *     written. `HW_DEVICE_FLASH_PAGE_SIZE` gives the page buffer size.
 *
 *  2. Erase the page to be programmed.
 *
 *  3. Program the page with the content of the page buffer.
 *
 *  Steps 1 & 2 can be done in any order.
 *
 * @code
 * uint8_t page[HW_DEVICE_FLASH_PAGE_SIZE] ;
 * intptr_t zpage = address & ~(HW_DEVICE_FLASH_PAGE_SIZE-1) ;
 *
 * hw( load_buffer, flash0, page );  // Store data into the memory page buffer
 * hw( erase_page, flash0, zpage );  // Erase memory page
 * hw( write_page, flash0, zpage );  // Program memory page with page buffer content
 * @endcode
 */

#define _hw_mtd_hw_load_buffer__flasha	, _hw_flasha_load_buffer
#define _hw_flasha_load_buffer(o,i,a,src,...)	HW_TX(_hw_flasha_ldpgbf(o,src),__VA_ARGS__)

#define _hw_mtd_hw_erase_page__flasha	, _hw_flasha_erase_page
#define _hw_flasha_erase_page(o,i,a,src,...)	HW_TX(_hw_flasha_pgers(o,src),__VA_ARGS__)

#define _hw_mtd_hw_write_page__flasha	, _hw_flasha_write_page
#define _hw_flasha_write_page(o,i,a,src,...)	HW_TX(_hw_flasha_pgwrt(o,src),__VA_ARGS__)


#if !defined HW_DEVICE_FUSE_BOOTRST
/*
 * Device without boot section: the MCU is halted when the flash memory is
 * busy, no need to wait for readiness
 */
#define _hw_flasha_pgers(o, ptr)					\
  do {									\
    _hw_write_reg( o, csr, 1<<_HW_MBP(o, pgers) | 1<<_HW_MBP(o, spmen) ); \
    _hw_flasha_spm( ptr );						\
  }while(0)

#define _hw_flasha_pgwrt(o, ptr)					\
  do {									\
    _hw_write_reg( o, csr, 1<<_HW_MBP(o, pgwrt) | 1<<_HW_MBP(o, spmen) ); \
    _hw_flasha_spm( ptr );						\
  }while(0)


/**
 * @brief  Preload Z register before outputting SPM instruction
 */
HW_INLINE void _hw_flasha_spm( intptr_t ptr )
{
  hw_asm("	spm	\n"
	 :: "z" (ptr) :
	 );
}


#define _hw_flasha_ldpgbf(o, src)				\
  do {								\
    hw_asm("CSR = " HW_QUOTE(_HW_A(_HW_M(o, csr))-0x20) "\n"		\
	   "BP_RWWSRE = " HW_QUOTE(_HW_MBP(o, rwwsre)) "\n"	\
	   "BP_SPMEN = " HW_QUOTE(_HW_MBP(o, spmen)) "\n"	\
	   "PGSIZE = " HW_QUOTE(HW_DEVICE_FLASH_PAGE_SIZE) "\n"	\
	   );							\
    __hw_flasha_ldpgbf( src );					\
  }while(0)


/**
 * @brief Load page buffer with data from src
 */
HW_INLINE void __hw_flasha_ldpgbf( void *src )
{
  uint8_t r1 ;

#if HW_DEVICE_FLASH_PAGE_SIZE > 256
#  error
#endif

  hw_asm(
	 /*  Clear page buffer
	  */
	 "    ldi   %[r1], 1<<BP_RWWSRE|1<<BP_SPMEN	\n"
	 "    .if CSR < 0x40			\n"
	 "    out	CSR, %[r1]		\n"
	 "    .else				\n"
	 "    sts	CSR+0x20, %[r1]		\n"
	 "    .endif				\n"

	 /*  Load page buffer
	  */
	 "    clr   r30				\n"
	 "    clr   r31				\n"
	 "1:  ld    r0, %a2+			\n"
	 "    ld    r1, %a2+			\n"

	 "    .if CSR < 0x20			\n"
	 "    sbi	CSR, BP_SPMEN		\n"
	 "    .else				\n"
	 "    ldi	%[r1], 1<<BP_SPMEN	\n"
	 "    .if CSR < 0x40			\n"
	 "    out	CSR, %[r1]		\n"
	 "    .else				\n"
	 "    sts	CSR+0x20, %[r1]	\n"
	 "    .endif				\n"
	 "    .endif				\n"
	 "    spm				\n"

	 "    adiw  r30, 2			\n"
	 "    cpi   r30, PGSIZE			\n"
	 "    brne  1b				\n"
	 :
	 [r1] "=r" (r1),
	 "=e" (src)
	 :
	 "1" (src)
	 :
	 "r0", "r1",
	 "r30", "r31"
	 );
}

#else
/*
 * Device with boot section: the MCU is not halted when programming a page in
 * the RWW section, must wait the completion of the last SPM operation
 */
#define _hw_flasha_pgers(o, ptr)					\
  do {									\
    hw_asm("wdr");							\
    __hw_flasha_dospm( _HW_A(_HW_M(o,csr)), ptr, 1<<_HW_MBP(o, pgers) | 1<<_HW_MBP(o, spmen) ); \
  }while(0)

#define _hw_flasha_pgwrt(o, ptr)					\
  do {									\
    hw_asm("wdr");							\
    __hw_flasha_dospm( _HW_A(_HW_M(o,csr)), ptr, 1<<_HW_MBP(o, pgwrt) | 1<<_HW_MBP(o, spmen) ); \
  }while(0)

/**
 */
HW_INLINE void __hw_flasha_dospm( intptr_t csr, intptr_t ptr, uint8_t cmd )
{
  if ( csr-0x20 < 0x20 ) {
    hw_asm("	out	CSR, %[r1]				\n"
	   "	spm						\n"
	   "1:	sbic	CSR, BP_SPMEN				\n"
	   "	rjmp	1b					\n"
	   "	out	CSR, 1<<BP_RWWSRE | 1<<BP_SPMEN		\n"
	   "	spm						\n"
	   "1:	sbic	CSR, BP_SPMEN				\n"
	   "	rjmp	1b					\n"
	   : [r1] "=r" (cmd)
	   : "z" (ptr) :
	   );
  }
  else if ( csr-0x20 < 0x40 ) {
    hw_asm("	out	CSR, %[r1]				\n"
	   "	spm						\n"
	   "1:	in	%[r1], CSR				\n"
	   "	sbrc	%[r1], BP_SPMEN				\n"
	   "	rjmp	1b					\n"
	   "	out	CSR, 1<<BP_RWWSRE | 1<<BP_SPMEN		\n"
	   "	spm						\n"
	   "1:	in	%[r1], CSR				\n"
	   "	sbrc	%[r1], BP_SPMEN				\n"
	   "	rjmp	1b					\n"
	   : [r1] "=r" (cmd)
	   : "0" (cmd), "z" (ptr) :
	   );
  }
  else {
    hw_asm("	sts	CSR+0x20, %[r1]				\n"
	   "	spm						\n"
	   "1:	lds	%[r1], CSR+0x20				\n"
	   "	sbrc	%[r1], BP_SPMEN				\n"
	   "	rjmp	1b					\n"
	   "	out	CSR, 1<<BP_RWWSRE | 1<<BP_SPMEN		\n"
	   "	spm						\n"
	   "1:	lds	%[r1], CSR+0x20				\n"
	   "	sbrc	%[r1], BP_SPMEN				\n"
	   "	rjmp	1b					\n"
	   : [r1] "=r" (cmd)
	   : "z" (ptr) :
	   );
  }
}


#define _hw_flasha_ldpgbf(o, src)				\
  do {								\
    hw_asm("CSR = " HW_QUOTE(_HW_A(_HW_M(o, csr))-0x20) "\n"		\
	   "BP_RWWSRE = " HW_QUOTE(_HW_MBP(o, rwwsre)) "\n"	\
	   "BP_SPMEN = " HW_QUOTE(_HW_MBP(o, spmen)) "\n"	\
	   "PGSIZE = " HW_QUOTE(HW_DEVICE_FLASH_PAGE_SIZE) "\n"	\
	   );							\
    __hw_flasha_ldpgbf( src );					\
  }while(0)


/**
 * @brief Load page buffer with data from src
 */
HW_INLINE void __hw_flasha_ldpgbf( void *src )
{
  uint8_t r1 ;

#if HW_DEVICE_FLASH_PAGE_SIZE > 256
#  error
#endif

  hw_asm(/*  Load page buffer
	  */
	 "    clr   r30				\n"
	 "    clr   r31				\n"
	 "1:  ld    r0, %a2+			\n"
	 "    ld    r1, %a2+			\n"

	 "    .if CSR < 0x20			\n"
	 "    sbi	CSR, BP_SPMEN		\n"
	 "    .else				\n"
	 "    ldi	%[r1], 1<<BP_SPMEN	\n"
	 "    .if CSR < 0x40			\n"
	 "    out	CSR, %[r1]		\n"
	 "    .else				\n"
	 "    sts	CSR+0x20, %[r1]	\n"
	 "    .endif				\n"
	 "    .endif				\n"
	 "    spm				\n"

	 "    adiw  r30, 2			\n"
	 "    cpi   r30, PGSIZE			\n"
	 "    brne  1b				\n"
	 :
	 [r1] "=r" (r1),
	 "=e" (src)
	 :
	 "1" (src)
	 :
	 "r0", "r1",
	 "r30", "r31"
	 );
}
#endif /* !defined HW_DEVICE_BOOTRST */


#if 0	/* Alternate version */
HW_INLINE void __hw_flasha_ldpgbf( intptr_t dst, void *src )
{
  uint8_t r1, r2 ;

  hw_asm(
	 /*  Clear page buffer
	  */
	 "    ldi   %[r1], 1<<BP_RWWSRE|1<<BP_SPMEN	\n"
	 "    .if CSR < 0x40			\n"
	 "    out	CSR, %[r1]		\n"
	 "    .else				\n"
	 "    sts	CSR+0x20, %[r1]		\n"
	 "    .endif				\n"

	 /*  Load page buffer
	  */
	 "    ldi   %[r1], " HW_QUOTE(HW_DEVICE_FLASH_PAGE_SIZE/2) "\n"
	 "1:  ld    r0, %a2+			\n"
	 "    ld    r1, %a2+			\n"

	 "    .if CSR < 0x20			\n"
	 "    sbi	CSR, BP_SPMEN		\n"
	 "    .else				\n"
	 "    ldi	%[r2], 1<<BP_SPMEN	\n"
	 "    .if CSR < 0x40			\n"
	 "    out	CSR, %[r2]		\n"
	 "    .else				\n"
	 "    sts	CSR+0x20, %[r2]	\n"
	 "    .endif				\n"
	 "    .endif				\n"
	 "    spm				\n"

	 "    adiw  R30, 2			\n"
	 "    dec   %[r1]			\n"
	 "    brne  1b				\n"
	 :
	 [r1] "=r" (r1),
	 [r2] "=r" (r2),
	 "=e" (src), "=z" (dst)
	 :
	 "2" (src), "3" (dst)
	 :
	 "r0", "r1"
	 );
}
#endif

/**
 * @page atmelavr_flasha
 * <br>
 */
