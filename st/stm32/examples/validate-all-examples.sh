#!/bin/sh

for i in ??-* ; do
    echo $$i ;
    (cd $$i ; make -s validate ) ;
done
