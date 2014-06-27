#!/bin/bash
if make results ; then
    cd build
    for i in *.result ; do
	cp $i ../${i/result/valid}
    done
fi
