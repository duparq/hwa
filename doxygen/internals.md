
Internals {#internals}
=========

A few notes about how HWA works internally.


Call-tree
---------

HWA macros and their dependencies.


  _HW_SPEC  P  _HW_R        HW_ISON(o)
   (f,t,)       (o,r)
    |            |           |--                HW_VOID_ISR(o [,reason])
    |            |           |--                HW_ID(o)
    |            |           |--                HW_RELATIVE(o1,o2)
    |            |           |--HW_RLX(oo)
    |            |--_HW_M    |   |--HW_OD(oo)
    |            |   (o,r)   |   |   |
    |            |    |      |   |   |--        _hw(f,oo,...)
    |            |    |      |   |   |--        _hwa(f,oo,...)
    |            |    |      |   |   |--        hw(f,oo,...)
    |            |    |      |   |   |--        hwa(f,oo,...)
    |            |    |      |   |   |--        HW_REGISTER(oo,r)
    |            |    |      |   |   |--        HW_ISR(oo [,reason] [,naked] ... )
    |            |    |      |   |--HW_aO  /* HW_OD copy */
    |            |    |      |   |   |--HW_IRQ(o [,reason])
    |            |    |--    |   |       |--    HW_IRQMASK(o [,reason])
    |            |    |--    |   |       |--    HW_IRQFLAG(o [,reason])
    |            |    |      |   |--HW_MTD(f,oo)
    |            |    |      |   |   |--        HW_ADDRESS(oo)
    |            |    |      |   |   |--        HW_BIT(oo)
    |            |    |      |   |   |--        HW_POSITION(oo)
    |--          |    |--    |                  _HW_A(rx|mx)
    |--          |    |--    |                  _HW_MBN(o,r)
    |--          |    |--    |                  _HW_MBP(o,r)
    |--          |    |--    |                  _hw_read_reg(o,r)
    |--          |    |--    |                  _hw_atomic_read_reg(o,r)
    |--          |    |--    |                  _hw_write_reg(o,r,v)
    |--          |    |--    |                  _hw_write_reg_m(o,r,m,v)
    |--          |    |--    |                  _hwa_write_reg(o,r,v)
    |--          |    |--    |                  _hwa_write_reg_m(o,r,m,v)
    |--          |    |--    |                  _hwa_commit_reg(o,r)
    |--          |    |--    |                  _hwa_nocommit_reg(o,r)
    |--          |    |--    |                  _hwa_mmask(o,r)
    |--          |    |--    |                  _hwa_mvalue(o,r)
    |--          |    |--    |                  _hwa_ovalue(o,r)
    |--          |    |--    |                  _hwa_set_reg(o,r,v)
                 |--         |                  _hwa_setup_reg(o,r)
                 |--         |                  _hwa_init_reg(o,r,v)

                                                _hwa_setup(o)
                                                _hwa_init(o)
                                                _hwa_solve(o)
                                                _hwa_commit(o)



Macro argument names
--------------------

HWA uses the following standardized argument names in its macro definitions:

 * `o`: name of the object
 * `oo`: path of an object (object name and optionnal list of relatives)
 * `ox`: definition of an object (expansion)
 * `c`: class of the object
 * `i`: id of the object
 * `a`: base address of the object
 * `f`: name of the function
 * `t`: type
 * `r`: name of a register
 * `rx`: definition of a register (expansion)
 * `ra`: relative address of the register 
 * `rwm`: register writeable bits mask
 * `rfm`: register flags mask
 * `bn`: number of bits
 * `bp`: position of least significant bit
 * `rbn`: number of bits of a logical register
 * `rbp`: position of least significant bit of a logical register in the
          hardware register
 * `vbn`: number of bits in the value
 * `vbp`: position of least significant bit in the value
 * `h`: "hw" or "hwa" prefix
 * `mx`: definition of a memory location (expansion)
