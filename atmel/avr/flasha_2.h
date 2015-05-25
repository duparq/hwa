
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */


/**
 * @page atmelavr_flasha
 * @section atmelavr_flasha_read1 Reading one byte from Flash memory
 *
 * @code
 * uint8_t byte = hw_read( FLASH, addr ); // Read byte at address addr
 * @endcode
 */
#define _hw_mthd_hw_read__flasha		, _hw_read_flasha
#define _hw_read_flasha(p,i,a,addr,...)		HW_TX( _hw_flashardbyte(addr), __VA_ARGS__)

HW_INLINE uint8_t _hw_flashardbyte( uint16_t a )
{
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
 * @section atmelavr_flasha_readx Reading multiple bytes Flash memory
 *
 * @code
 * uint8_t dst[10];
 * uint8_t count = sizeof(dst);
 * hw_read_bytes( FLASH, dst, addr, count ); // Copy count bytes from Flash address addr to dst
 * @endcode
 */

#define _hw_mthd_hw_read_bytes__flasha		, _hw_read_bytes_flasha

#define _hw_read_bytes_flasha(p,i,a,dst,addr,n,...)	\
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
 *
 * @section atmelavr_flasha_loadpage Writing the Flash page buffer
 * This is achieved through the `hw_command(...)` instruction:
 * @code
 * uint8_t page[HW_DEVICE_FLASH_PAGE_SIZE] ;
 * hw_command( hw_flash0, load_page, page );
 * @endcode
 *
 * @section atmelavr_flasha_erasepage Erasing one page of Flash memory
 * This is achieved through the `hw_command(...)` instruction:
 * @code
 * intptr_t zpage = buf.addr & ~(HW_DEVICE_FLASH_PAGE_SIZE-1) ;
 * hw_command( hw_flash0, erase_page, zpage );
 * @endcode
 *
 * @section atmelavr_flasha_writepage Writing the page buffer into Flash memory
 * This is achieved through the `hw_command(...)` instruction:
 * @code
 * intptr_t zpage = buf.addr & ~(HW_DEVICE_FLASH_PAGE_SIZE-1) ;
 * hw_command( hw_flash0, write_page, zpage );
 * @endcode
 *
 * This handles commands that _flasha objects can execute:
 * * load_page
 * * erase_page
 * * write_page
 */
#define _hw_mthd_hw_command__flasha		, _hw_command_flasha

#define _hw_flasha_command_load_page		, load_page
#define _hw_flasha_command_write_page		, write_page
#define _hw_flasha_command_erase_page		, erase_page


#define _hw_command_flasha(p,i,a,...)					\
  HW_G2(_hw_flasha,HW_IS(,_hw_flasha_command_##__VA_ARGS__))(p,__VA_ARGS__)

#define _hw_flasha_1(p,cmd,...)			_hw_flasha_##cmd(p,__VA_ARGS__)

#define _hw_flasha_load_page(p,src,...)		HW_TX(_hw_flasha_ldpgbf(p,src),__VA_ARGS__)
#define _hw_flasha_erase_page(p,ptr,...)	HW_TX(_hw_flasha_pgers(p,ptr),__VA_ARGS__)
#define _hw_flasha_write_page(p,ptr,...)	HW_TX(_hw_flasha_pgwrt(p,ptr),__VA_ARGS__)


#if !defined HW_DEVICE_BOOTRST
/*
 * Device without boot section: the MCU is halted when the flash memory is
 * busy, no need to wait for readiness
 */

/**
 * @page atmelavr_flasha
 * @par Clear page buffer
 *
 * @code
 * hw_command( FLASH, clear_page_buffer );
 * @endcode
 */
#define rem_hw_flasha_clrbf(p)						\
  _hw_write_reg( p, csr, 1<<_hw_rbp(p, rwwsre) | 1<<_hw_rbp(p, spmen) )


/**
 * @page atmelavr_flasha
 * @par Erase page
 *
 * @code
 * intptr_t ptr = page_address ;
 * hw_command( FLASH, erase_page, ptr );
 * @endcode
 */
#define _hw_flasha_pgers(p, ptr)					\
  do {									\
    _hw_write_reg( p, csr, 1<<_hw_rbp(p, pgers) | 1<<_hw_rbp(p, spmen) ); \
    _hw_flasha_spm( ptr );						\
  }while(0)


/**
 * @page atmelavr_flasha
 * @par Write page buffer into Flash memory
 *
 * @code
 * intptr_t ptr = page_address ;
 * hw_command( FLASH, write_page, ptr );
 * @endcode
 */
#define _hw_flasha_pgwrt(p, ptr)					\
  do {									\
    _hw_write_reg( p, csr, 1<<_hw_rbp(p, pgwrt) | 1<<_hw_rbp(p, spmen) ); \
    _hw_flasha_spm( ptr );						\
  }while(0)

#else
/*
 * Device with boot section: the MCU is not halted when programming a page in
 * the RWW section, must wait the completion of SPM operation
 */
#  error
#endif


/**
 * @brief  Preload Z register before outputting SPM instruction
 */
HW_INLINE void _hw_flasha_spm( intptr_t ptr )
{
  hw_asm("	spm	\n"
	 :: "z" (ptr) :
	 );
}


#define _hw_flasha_ldpgbf(p, src)				\
  do {								\
    hw_asm("CSR = " HW_QUOTE(_hw_ra(p, csr)-0x20) "\n"		\
	   "BP_RWWSRE = " HW_QUOTE(_hw_rbp(p, rwwsre)) "\n"	\
	   "BP_SPMEN = " HW_QUOTE(_hw_rbp(p, spmen)) "\n"	\
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
