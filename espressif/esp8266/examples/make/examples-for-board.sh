#!/bin/bash

examples_for_board() {
    BOARD="$1"
    EXAMPLES=""

    if [ ${BOARD} = "esp-wroom-02" ] ; then
	EXAMPLES="${EXAMPLES} 01-1-blink-soft"
	EXAMPLES="${EXAMPLES} 02-1-blink-uart"
	EXAMPLES="${EXAMPLES} 03-1-hwtimer-uart-swap"
    fi
}
