#!/bin/bash

examples_for_board() {
    BOARD="$1"
    EXAMPLES=""

    if [ ${BOARD} = "mini-stm32-v3.0" ] ; then
	EXAMPLES="${EXAMPLES} 01-1-blink"
	EXAMPLES="${EXAMPLES} 01-2-blink"
	EXAMPLES="${EXAMPLES} 02-1-clocks"
	EXAMPLES="${EXAMPLES} 02-2-clocks"
	EXAMPLES="${EXAMPLES} 03-1-systick"
	EXAMPLES="${EXAMPLES} 03-2-systick-irq"
	EXAMPLES="${EXAMPLES} 04-1-counter"
    fi
    if [ ${BOARD} = "stm32f103c8t6-vcc-gnd" ] ; then
	EXAMPLES="${EXAMPLES} 01-1-blink"
	EXAMPLES="${EXAMPLES} 01-2-blink"
	EXAMPLES="${EXAMPLES} 02-1-clocks"
	EXAMPLES="${EXAMPLES} 02-2-clocks"
	EXAMPLES="${EXAMPLES} 03-1-systick"
	EXAMPLES="${EXAMPLES} 03-2-systick-irq"
	EXAMPLES="${EXAMPLES} 04-1-counter"
    fi
}
