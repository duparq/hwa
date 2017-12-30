
/*  Counter clocking. Used by: c16a, c16b, c8a
 */
#define _hw_c1clk_none				, _hw_c1ck_none, 0
#define _hw_c1clk_ioclk				, _hw_c1ck_ioclk, 1.0
#define _hw_c1clk_external_rising		, _hw_c1ck_external_rising, 0
#define _hw_c1clk_external_falling		, _hw_c1ck_external_falling, 0

HW_INLINE uint8_t _hw_c1ck_none( float v )
{
  if ( v != 0 )
    HWA_E_NIL(value of `clock`, (`none`, `ioclk [/ 8|64|256|1024]`, `external_falling`, `external_rising`));

  return 0 ;
}

HW_INLINE uint8_t _hw_c1ck_ioclk( float v )
{
  if ( v == 1.0 )
    return 1 ;
  if ( v == 1.0/8 )
    return 2 ;
  if ( v == 1.0/64 )
    return 3 ;
  if ( v == 1.0/256 )
    return 4 ;
  if ( v == 1.0/1024 )
    return 5 ;

  HWA_E_NIL(value of `clock`, (`none`, `ioclk [/ 8|64|256|1024]`, `external_falling`, `external_rising`));
  return 0 ;
}

HW_INLINE uint8_t _hw_c1ck_external_rising( float v )
{
  if ( v != 0 )
    HWA_E_NIL(value of `clock`, (`none`, `ioclk [/ 8|64|256|1024]`, `external_falling`, `external_rising`));

  return 6 ;
}

HW_INLINE uint8_t _hw_c1ck_external_falling( float v )
{
  if ( v != 0 )
    HWA_E_NIL(value of `clock`, (`none`, `ioclk [/ 8|64|256|1024]`, `external_falling`, `external_rising`));

  return 7 ;
}
