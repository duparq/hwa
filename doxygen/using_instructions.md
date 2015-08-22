
Instructions {#using_instructions}
============

Many HWA instructions are generic and accept an object name as first
parameter. Several instructions accept a variable length list of parameters
consisting of key/value pairs.

There are two kinds of instructions:

 * the synchronous instructions, prefixed with `hw_`;

 * the asynchronous instructions, prefixed with `hwa_`.

__Synchronous instructions__ produce an immediate result.

__Asynchronous instructions__ can only be used after a _HWA context_ has been
created with the `hwa_begin()` or `hwa_begin_from_reset()` instruction. The
action of asynchronous instructions is memorized into the context and when the
`hwa_commit()` instruction is met, HWA determines from the context the machine
code to produce.

The `hwa_nocommit()` instruction puts the context in a known state but does not
produce machine code. This is useful to make HWA produce efficient code for
modifying a configuration without rewriting all the hardware registers.

See also:

 * <a href="modules.html">Instructions sorted by category</a>

 * <a href="examples.html">The examples provided with HWA</a>

<br>
