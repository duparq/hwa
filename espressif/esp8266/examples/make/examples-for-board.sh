#!/bin/bash

examples_for_board() {
    BOARD="$1"
    EXAMPLES=""

    if [ ${BOARD} = "esp-wroom-02" ] ; then
	EXAMPLES="${EXAMPLES} 01-1-blink-soft"
	EXAMPLES="${EXAMPLES} 02-1-uart-pin-txd-function"
	EXAMPLES="${EXAMPLES} 03-1-uart-pins-hwtimer"
    fi
}
