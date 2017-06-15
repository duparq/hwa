#!/bin/bash

for i in *.h ; do
    echo $i
    perl -i.bak -pe 's/(^#define _hw_def_.*	+_[^,]+), *([^,]+),(.*)/"$1, ".(101+$ii++).",$3"/e' $i ;
done
