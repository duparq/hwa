
Instructions {#using_instructions}
============

Many HWA instructions are generic and accept @ref using_peripherals "objects" of
various classes as first parameter. Several instructions accept a variable
length list of parameters consisting of key/value pairs.

There are two kinds of instructions:

 * synchronous instructions, with `hw_` prefix;

 * asynchronous instructions, with `hwa_` prefix.

__Synchronous instructions__ produce an immediate action.

__Asynchronous instructions__ can only be used after a HWA context has been created
with an hwa_begin() or hwa_begin_from_reset() instruction. The action of
asynchronous instructions is memorized into the HWA context. When the
hwa_commit() instruction is met, HWA determines from the context the machine
code to produce.

The hwa_nocommit() instruction is used to put the context in a known state
without producing machine code. This can be used to make HWA produce code that
just modifies a known configuration without rewriting the full configuration
into the hardware registers.

See also:

 * @ref public_obj_instructions

 * @ref public_obj_macros

 * @ref public_gen_instructions

 * @ref public_gen_macros

 * <a href="examples.html">The examples provided with HWA</a>
